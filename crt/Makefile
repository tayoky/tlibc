TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk

CRT = $(BUILDDIR)/crt0.o $(BUILDDIR)/crti.o $(BUILDDIR)/crtn.o
CRTDIR ?= $(LIBDIR)
CRTCLEANFILES = $(CRT)
FILESGROUPS = CRT
include $(TMAKE_DIR)/tmake-files.mk

$(BUILDDIR)/crt%.o : $(ARCH)/crt%.s
	@mkdir -p "$(@D)"
	@echo "AS $<"
	$(Q)$(AS) $(ASFLAGS) -o "$@" -c $<

$(BUILDDIR)/crt0.o : $(ARCH)/crt0-$(TARGET).s
	@mkdir -p "$(@D)"
	@echo "AS $<"
	$(Q) $(AS) $(ASFLAGS) -o $@ $<
