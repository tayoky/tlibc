# makefile include to generate headers

HEADERS ?= $(wildcard *.h)
INCS ?= $(addprefix $(BUILDDIR)/,$(HEADERS))

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

include $(TMAKE_DIR)/tmake-incs.mk
