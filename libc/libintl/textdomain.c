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

struct text_domain {
	char *data;
	size_t size;
	char *dir;
	char *codepoint;
	char *name;
	mo_desc_t *orig_table;
	mo_desc_t *trans_table;
	uint32_t *hash_table;
};

#define MO_MAGIC 0x950412de

static struct text_domain *domains[LC_ALL] = {0};
static size_t domains_count[LC_ALL] = {0};
static char global_domain[256] = "messages";

static struct text_domain *get_domain(const char *domainname, int category) {
	if (category < 0 || category >= LC_ALL) {
		return NULL;
	}
	if (!domainname) {
		domainname = global_domain;
	}
	for (size_t i=0; i<domains_count[category]; i++) {
		if (!strcmp(domains[category][i].name, domainname)) {
			return &domains[category][i];
		}
	}
	struct text_domain *new_domains = realloc(domains[category], sizeof(struct text_domain) * (domains_count[category] + 1));
	if (!new_domains) return NULL;
	domains[category] = new_domains;
	memset(&domains[category][domains_count[category]], 0, sizeof(struct text_domain));
	domains[category][domains_count[category]].name = strdup(domainname);
	return &domains[category][domains_count[category]++];
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

static int load_domain(struct text_domain *domain, int category) {
	if (domain->data) {
		//already loaded
		return 0;
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
	if (fd < 0) return -1;

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

	domain->size = buf.st_size;
	domain->data = mmap(NULL, domain->size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (domain->data == MAP_FAILED) {
		return -1;
	}
	domain->orig_table  = (mo_desc_t*)(domain->data + header.orig_table_offset);
	domain->trans_table = (mo_desc_t*)(domain->data + header.trans_table_offset);
	domain->hash_table  = (uint32_t*)(domain->data + header.hash_offset);
	return 0;
err_close:
	close(fd);
	return -1;
}

static const char *get_str(struct text_domain *domain, mo_desc_t *table, size_t index) {
	mo_desc_t *desc = &table[index];
	if (desc->offset + desc->length + 1 > domain->size) {
		return NULL;
	}
	const char *str = domain->data + desc->offset;
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

static const char *bsearch_lookup(struct text_domain *domain, const char *msgid) {
	mo_header_t *header = (mo_header_t*)domain->data;
	if (header->num_strings == 0) return NULL;
	size_t start = 0;
	size_t end = header->num_strings - 1;
	while (end >= start) {
		size_t i = (start + end) / 2;
		const char *candidate = get_str(domain, domain->orig_table, i);
		if (!candidate) break;
		int cmp = strcmp(candidate, msgid);
		if (cmp == 0) {
			return get_str(domain, domain->trans_table, i);
		} else if (cmp < 0) {
			start = i + 1;
		} else {
			if (i == 0) break;
			end = i - 1;
		}
	}
	return NULL;
}

static const char *hash_lookup(struct text_domain *domain, const char *msgid) {
	mo_header_t *header = (mo_header_t*)domain->data;
	uint32_t hash = hash_pjw(msgid);
	uint32_t index = hash % header->hash_size;
	uint32_t incr = 1 + (hash % (header->hash_size - 2));
	size_t max_iter = header->hash_size;
	while (domain->hash_table[index] && (max_iter--) > 0) {
		size_t str_idx = domain->hash_table[index] - 1;
		if (str_idx >= header->num_strings) return NULL;
		const char *candidate = get_str(domain, domain->orig_table, str_idx);
		if (!candidate) return NULL;
		if (!strcmp(candidate, msgid)) {
			return get_str(domain, domain->trans_table, str_idx);
		}
		index = (index + incr) % header->hash_size;
	}
	return NULL;
}

static const char *lookup_msgid(struct text_domain *domain, const char *msgid) {
	mo_header_t *header = (mo_header_t*)domain->data;
	const char *msg;
	if (header->hash_size <= 2) {
		msg = bsearch_lookup(domain, msgid);
	} else {
		msg = hash_lookup(domain, msgid);
	}
	return msg ? msg : msgid;
}

char *dcgettext(const char *domainname, const char *msgid, int category) {
	struct text_domain *domain = get_domain(domainname, category);
	if (!domain) return (char*)msgid;
	if (load_domain(domain, category) < 0) return (char *)msgid;
	return (char *)lookup_msgid(domain, msgid);
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
