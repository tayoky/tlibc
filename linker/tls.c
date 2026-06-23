#include <string.h>
#include <tlibc.h>
#include "linker.h"

void *__tls_get_addr(struct tls_index *ti) {
	struct __uthread *uthread = __get_uthread();
	if (uthread->dtv_size < ti->ti_module + 1) {
		// grow the array
		size_t new_size = ti->ti_module + 1;
		void **new_dtv = dl_alloc(sizeof(void *) * new_size);
		memset(new_dtv, 0, sizeof(void *) * new_size);
		memcpy(new_dtv, uthread->dtv, sizeof(void *) * uthread->dtv_size);
		dl_free(uthread->dtv);
		uthread->dtv      = new_dtv;
		uthread->dtv_size = new_size;
	}

	if (!uthread->dtv[ti->ti_module]) {
		// allocate the tls block
		struct elf_object *object = cache_find_id(ti->ti_module);
		if (object->tls_size == 0) {
			// no tls in this object
			return NULL;
		}
		char *tls_block = dl_alloc(object->tls_size);
		if (!tls_block) return NULL;
		memcpy(tls_block, object->tls, object->tls_filesz);
		memset(tls_block + object->tls_filesz, 0, object->tls_size - object->tls_filesz);
		uthread->dtv[ti->ti_module] = tls_block;
	}
	return (char*)uthread->dtv[ti->ti_module] + ti->ti_offset;
}
