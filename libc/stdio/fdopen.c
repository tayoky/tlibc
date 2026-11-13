#include <stdio-internal.h>
#include <errno.h>
#include <stdlib.h>

FILE *fdopen(int handle, const char *type) {
	(void)type;
	if (handle < 0) {
		__set_errno(-EBADF);
		return NULL;
	}

	FILE *stream = calloc(1, sizeof(FILE));
	if (!stream) return NULL;
	stream->fd = handle;
	setvbuf(stream, NULL, _IOFBF, 0);
	__register_stream(stream);

	return stream;
}
