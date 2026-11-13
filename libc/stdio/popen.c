#include <stdio-internal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

struct __pipe_stream *__pipe_streams = NULL;

FILE *popen(const char *command, const char *type) {
	// validate the type
	if (strcmp(type, "r") && strcmp(type, "w")) {
		errno = -EINVAL;
		return NULL;
	}

	int pipefd[2];
	if (pipe(pipefd) < 0) return NULL;

	struct __pipe_stream *pipe_stream = calloc(1, sizeof(struct __pipe_stream));
	if (!pipe_stream) goto close_pipe;

	pid_t child = fork();
	if (!child) {
		// close already open pipe streams
		for (struct __pipe_stream *current = __pipe_streams; current; current = current->next) {
			close(current->file.fd);
		}
		if (!strcmp(type, "r")) {
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
		} else {
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
		}
		execl("/bin/sh", "/bin/sh", "-c", (char*)command, NULL);
		_exit(127);
	}

	if (child < 0) {
		free(pipe_stream);
close_pipe:
		close(pipefd[0]);
		close(pipefd[1]);
		return NULL;
	}

	pipe_stream->pid = child;
	if (!strcmp(type, "r")) {
		pipe_stream->file.fd = pipefd[0];
		close(pipefd[1]);
	} else {
		close(pipefd[0]);
		pipe_stream->file.fd = pipefd[1];
	}
	setvbuf(&pipe_stream->file, NULL, _IOFBF, 0);

	if (__pipe_streams) {
		__pipe_streams->prev = pipe_stream;
	}
	pipe_stream->next = __pipe_streams;
	__pipe_streams = pipe_stream;
	__register_stream(&pipe_stream->file);
	return &pipe_stream->file;
}
