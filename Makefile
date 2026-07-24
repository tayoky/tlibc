TOP = $(CURDIR)
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk

VERSION := $(shell git describe --tags --always 2>/dev/null || echo unknown)

DOCS = COPYING.txt README.md
DOCSDIR = $(DOCDIR)/$(PACKAGE)

FILESGROUPS = DOCS
include $(TMAKE_DIR)/tmake-files.mk

SUBDIRS = include libk libc libm linker stub crt
include $(TMAKE_DIR)/tmake-subdir.mk

# dependency
all-libm : all-libc

SRCS = $(wildcard linker/*.c libc/*/*.c)
include $(TMAKE_DIR)/tmake-locale.mk
