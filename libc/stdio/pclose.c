#include <stdio-internal.h>
#include <sys/wait.h>
#include <errno.h>

int pclose(FILE *stream) {
	int status;
	struct __pipe_stream *pipe_stream = (struct __pipe_stream *)stream;
	while (waitpid(pipe_stream->pid, &status, 0) < 0) {
		if (errno != EINTR) {
			status = -1;
			break;
		}
	}
	if (__pipe_streams == pipe_stream) {
		__pipe_streams = pipe_stream->next;
	}
	if (pipe_stream->prev) {
		pipe_stream->prev->next = pipe_stream->next;
	}
	if (pipe_stream->next) {
		pipe_stream->next->prev = pipe_stream->prev;
	}
	fclose(stream);
	return status;
}
