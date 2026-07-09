#include <sys/select.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

#define FD_PER_ENTRY 32

void FD_CLR(int fd, fd_set *set) {
	if (fd >= FD_SETSIZE) return;
	set->data[fd / FD_PER_ENTRY] &= ~(1UL << (fd % FD_PER_ENTRY));
}

int FD_ISSET(int fd, const fd_set *set) {
	if (fd >= FD_SETSIZE) return 0;
	if (set->data[fd / FD_PER_ENTRY] & (1UL << (fd % FD_PER_ENTRY))) {
		return 1;
	}
	return 0;
}

void FD_SET(int fd, fd_set *set) {
	if (fd >= FD_SETSIZE) return;
	set->data[fd / FD_PER_ENTRY] |= 1UL << (fd % FD_PER_ENTRY);
}

void FD_ZERO(fd_set *set) {
	memset(set, 0, sizeof(fd_set));
}


static void add_fd(struct pollfd **pollfds, size_t *count, size_t *capacity, struct pollfd *pollfd) {
	if (*count >= *capacity) {
		*capacity *= 2;
		*pollfds = realloc(*pollfds, sizeof(struct pollfd) * (*capacity));
	} 
	memcpy(&(*pollfds)[(*count)++], pollfd, sizeof(struct pollfd));
}

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds,
                  fd_set *restrict exceptfds, struct timeval *restrict timeout) {
	struct pollfd *pollfds = malloc(sizeof(struct pollfd));
	size_t count = 0;
	size_t capacity = 1;


	if (readfds) {
		for (int i=0; i<nfds; i++) {
			if (FD_ISSET(i, readfds)) {
				struct pollfd pollfd = {
					.events = POLLIN | POLLHUP,
					.fd = i,
				};
				add_fd(&pollfds, &count, &capacity, &pollfd);
			}
		}
	}
	if (writefds) {
		for (int i=0; i<nfds; i++) {
			if (FD_ISSET(i, writefds)) {
				struct pollfd pollfd = {
					.events = POLLOUT | POLLHUP,
					.fd = i,
				};
				add_fd(&pollfds, &count, &capacity, &pollfd);
			}
		}
	}

	if (exceptfds) {
		for (int i=0; i<nfds; i++) {
			if (FD_ISSET(i, readfds)) {
				struct pollfd pollfd = {
					.events = POLLHUP,
					.fd = i,
				};
				add_fd(&pollfds, &count, &capacity, &pollfd);
			}
		}
	}

	int ret = poll(pollfds, count, timeout->tv_sec * 1000 + timeout->tv_usec / 1000000);

	free(pollfds);
	return ret;
}
