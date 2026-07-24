TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk

CRTS = $(BUILDDIR)/crt0.o $(BUILDDIR)/crti.o $(BUILDDIR)/crtn.o

.PHONY : all install uninstall clean
all : $(CRTS)

$(BUILDDIR)/crt%.o : $(ARCH)/crt%.s
	@mkdir -p "$(@D)"
	@echo "AS $<"
	$(Q) $(AS) $(ASFLAGS) -o $@ $<

$(BUILDDIR)/crt0.o : $(ARCH)/crt0-$(TARGET).s
	@mkdir -p "$(@D)"
	@echo "AS $<"
	$(Q) $(AS) $(ASFLAGS) -o $@ $<

clean :
	@echo "CLEAN $(BUILDDIR)"
	@rm -fr "$(BUILDDIR)"

FILES = $(CRTS)
FILESDIR = $(LIBDIR)
include $(TMAKE_DIR)/tmake-files.mk
