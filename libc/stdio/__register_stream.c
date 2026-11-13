#include <stdio-internal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *__streams;

void __register_stream(FILE *stream) {
	stream->unget = EOF;

	// link in the list
	if (__streams) {
		__streams->prev = stream;
	}
	stream->next = __streams;
	__streams = stream;
}
