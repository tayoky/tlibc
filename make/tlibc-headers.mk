# makefile include to generate headers

HEADERS ?= $(wildcard $(SRCDIR)/*.h)
INCS ?= $(HEADERS:$(SRCDIR)/%=$(BUILDDIR)/%)

all : $(HEADERS)

# cdefs contain the guards itself
$(BUILDDIR)/cdefs.h : $(SRCDIR)/cdefs.h
	@mkdir -p "$(@D)"
	@echo "GEN $@"
	$(Q)cat $^ > $@

$(BUILDDIR)/%.h : $(SRCDIR)/%.h
	@mkdir -p "$(@D)"
	@echo "GEN $@"
	$(Q)cat "$(TOP)/prologue.h" $^ "$(TOP)/epilogue.h" > $@

include $(TMAKE_DIR)/tmake-incs.mk
