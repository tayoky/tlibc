#include <sys/mman.h>
#include <sys/stat.h>
#include <libintl.h>
#include <locale.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef LOCALEDIR
#define LOCALEDIR "/usr/share/locale"
#endif

typedef struct mo_header {
	uint32_t magic;
	uint32_t revision;
	uint32_t num_strings;
	uint32_t orig_table_offset;
	uint32_t trans_table_offset;
	uint32_t hash_size;
	uint32_t hash_offset;
} __attribute__((packed)) mo_header_t;

typedef struct mo_desc {
	uint32_t length;
	uint32_t offset;
} __attribute__((packed)) mo_desc_t;

typedef struct mo_file {
	size_t size;
	char *data;
	mo_desc_t *orig_table;
	mo_desc_t *trans_table;
	uint32_t *hash_table;
} mo_file_t;

typedef struct text_domain {
	char *dir;
	char *codepoint;
	char *name;
	mo_file_t files[LC_ALL];
} text_domain_t;

#define MO_MAGIC 0x950412de

static text_domain_t *domains;
static size_t domains_count;
static char global_domain[256] = "messages";

static text_domain_t *get_domain(const char *domainname) {
	if (!domainname) {
		domainname = global_domain;
	}
	for (size_t i=0; i<domains_count; i++) {
		if (!strcmp(domains[i].name, domainname)) {
			return &domains[i];
		}
	}
	text_domain_t *new_domains = realloc(domains, sizeof(struct text_domain) * (domains_count + 1));
	if (!new_domains) return NULL;
	domains = new_domains;
	memset(&domains[domains_count], 0, sizeof(struct text_domain));
	domains[domains_count].name = strdup(domainname);
	return &domains[domains_count++];
}

static const char *category2str(int category) {
	switch (category) {
	case LC_MESSAGES:
		return "LC_MESSAGES";
	default:
		return "LC_UNKNOWN";
	}
}

static const char *get_locale(int category) {
	const char *name = getenv(category2str(category));
	if (!name) name = getenv("LC_ALL");
	if (!name) name = getenv("LANG");
	if (!name) name = "en_US";
	return name;
}

static mo_file_t *load_domain(text_domain_t *domain, int category) {
	if (category < 0 || category >= LC_ALL) {
		return NULL;
	}

	mo_file_t *file = &domain->files[category];
	if (file->data) {
		// already loaded
		return file;
	}

	const char *locale_name = get_locale(category);
	char locale[64] = {0};
	strncpy(locale, locale_name, sizeof(locale)-1);
	if (strchr(locale, '.')) *strchr(locale, '.') = '\0';
	const char *dir = domain->dir ? domain->dir : LOCALEDIR;
	char path[PATH_MAX];
	snprintf(path, sizeof(path), "%s/%s/%s/%s.mo", dir, locale, category2str(category), domain->name);
	int fd = open(path, O_RDONLY);
	if (fd < 0 && strchr(locale, '_')) {
		// retry with generic language without region
		*strchr(locale, '_') = '\0';
		snprintf(path, sizeof(path), "%s/%s/%s/%s.mo", dir, locale, category2str(category), domain->name);
		fd = open(path, O_RDONLY);
	}
	if (fd < 0) return NULL;

	mo_header_t header = {0};
	if (read(fd, &header, sizeof(mo_header_t)) < (ssize_t)sizeof(mo_header_t)) goto err_close;
	if (header.magic != MO_MAGIC) goto err_close;

	struct stat buf;
	if (fstat(fd, &buf) < 0) {
		goto err_close;
	}

	// check bounds
	size_t table_size = sizeof(mo_desc_t) * header.num_strings;
	if (header.orig_table_offset + table_size > (size_t)buf.st_size) {
		goto err_close;
	}
	if (header.trans_table_offset + table_size > (size_t)buf.st_size) {
		goto err_close;
	}
	if (header.hash_offset + header.hash_size > (size_t)buf.st_size) {
		goto err_close;
	}

	// check alignement
	if ((header.orig_table_offset & 3) != 0) {
		goto err_close;
	}
	if ((header.trans_table_offset & 3) != 0) {
		goto err_close;
	}
	if ((header.hash_offset & 3) != 0) {
		goto err_close;
	}

	file->size = buf.st_size;
	file->data = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (file->data == MAP_FAILED) {
		file->data = NULL;
		return NULL;
	}
	file->orig_table  = (mo_desc_t*)(file->data + header.orig_table_offset);
	file->trans_table = (mo_desc_t*)(file->data + header.trans_table_offset);
	file->hash_table  = (uint32_t*)(file->data + header.hash_offset);
	return file;

err_close:
	close(fd);
	return NULL;
}

static const char *get_str(mo_file_t *file, mo_desc_t *table, size_t index) {
	mo_desc_t *desc = &table[index];
	if (desc->offset + desc->length + 1 > file->size) {
		return NULL;
	}
	const char *str = file->data + desc->offset;
	if (str[desc->length] != '\0') {
		return NULL;
	}
	return str;
}

// GNU gettext string hashing algorithm
uint32_t hash_pjw(const char *str) {
	uint32_t hval = 0;
	while (*str) {
	        hval = (hval << 4) + *str;
		uint32_t g = hval & 0xF0000000;
		if (g != 0) {
			hval ^= g >> 24;
		}
		hval ^= g;
		str++;
	}
	return hval;
}

static const char *bsearch_lookup(mo_file_t *data, const char *msgid) {
	mo_header_t *header = (mo_header_t*)data->data;
	if (header->num_strings == 0) return NULL;
	size_t start = 0;
	size_t end = header->num_strings - 1;
	while (end >= start) {
		size_t i = (start + end) / 2;
		const char *candidate = get_str(data, data->orig_table, i);
		if (!candidate) break;
		int cmp = strcmp(candidate, msgid);
		if (cmp == 0) {
			return get_str(data, data->trans_table, i);
		} else if (cmp < 0) {
			start = i + 1;
		} else {
			if (i == 0) break;
			end = i - 1;
		}
	}
	return NULL;
}

static const char *hash_lookup(mo_file_t *data, const char *msgid) {
	mo_header_t *header = (mo_header_t*)data->data;
	uint32_t hash = hash_pjw(msgid);
	uint32_t index = hash % header->hash_size;
	uint32_t incr = 1 + (hash % (header->hash_size - 2));
	size_t max_iter = header->hash_size;
	while (data->hash_table[index] && (max_iter--) > 0) {
		size_t str_idx = data->hash_table[index] - 1;
		if (str_idx >= header->num_strings) return NULL;
		const char *candidate = get_str(data, data->orig_table, str_idx);
		if (!candidate) return NULL;
		if (!strcmp(candidate, msgid)) {
			return get_str(data, data->trans_table, str_idx);
		}
		index = (index + incr) % header->hash_size;
	}
	return NULL;
}

static const char *lookup_msgid(mo_file_t *file, const char *msgid, int category) {
	mo_header_t *header = (mo_header_t*)file->data;
	const char *msg;
	if (header->hash_size <= 2) {
		msg = bsearch_lookup(file, msgid);
	} else {
		msg = hash_lookup(file, msgid);
	}
	return msg ? msg : msgid;
}

char *dcgettext(const char *domainname, const char *msgid, int category) {
	text_domain_t *domain = get_domain(domainname);
	if (!domain) return (char*)msgid;
	mo_file_t *file = load_domain(domain, category);
	if (!file) return (char *)msgid;
	return (char *)lookup_msgid(file, msgid, category);
}

char *dcngettext(const char *domainname, const char *msgid1, const char *msgid2, unsigned long n, int category) {
	// TODO
	return (char*)msgid2;
}

char *textdomain(const char *domainname) {
	if (domainname) {
		snprintf(global_domain, sizeof(global_domain), "%s", domainname);
	}
	return global_domain;
}

char *bindtextdomain(const char *domainname, const char *dirname) {
	text_domain_t *domain = get_domain(domainname);
	if (!domain) return NULL;
	if (dirname) domain->dir = (char*)dirname;
	return domain->dir ? domain->dir : LOCALEDIR;
}
