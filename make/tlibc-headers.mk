# makefile include to generate headers

FILESGROUPS += HEADERS
HEADERS_SRCS ?= $(wildcard *.h)
HEADERS ?= $(addprefix $(BUILDDIR)/,$(HEADERS_SRCS))
HEADERSDIR ?= $(INCLUDEDIR)

.PHONY : all
all : $(HEADERS)

# cdefs contain the guards itself
$(BUILDDIR)/cdefs.h : cdefs.h
	@mkdir -p "$(@D)"
	@echo "GEN $@"
	$(Q)cat $^ > $@

$(BUILDDIR)/%.h : %.h
	@mkdir -p "$(@D)"
	@echo "GEN $@"
	$(Q)cat "$(TOP)/prologue.h" $^ "$(TOP)/epilogue.h" > $@

include $(TMAKE_DIR)/tmake-files.mk
