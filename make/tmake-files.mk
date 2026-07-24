# makefile include to install files

FILESDIR ?= $(SHAREDIR)
FILESOWN ?= root
FILESGRP ?= root
FILESMODE ?= 0644
FILESGROUPS ?= FILES

define files_template
_$(1)_FILES := $$($1)
_$(1)_DIR   := $$(or $$($(1)DIR),$$(FILESDIR))
_$(1)_OWN   := $$(or $$($(1)OWN),$$(FILESOWN))
_$(1)_GRP   := $$(or $$($(1)GRP),$$(FILESGRP))
_$(1)_MODE  := $$(or $$($(1)MODE),$$(FILESMODE))
_$(1)_LOWER := $$(shell echo "$(1)" | tr 'A-Z_' 'a-z-')

.PHONY : install-$$(_$(1)_LOWER)
install : install-$$(_$(1)_LOWER)
install-$$(_$(1)_LOWER) : all
	@mkdir -p "$(DESTDIR)$$(_$(1)_DIR)"
	@echo "INSTALL $$(_$(1)_FILES)"
	$(Q)cp -r $$(_$(1)_FILES) "$(DESTDIR)$$(_$(1)_DIR)/"

.PHONY : uninstall-$$(_$(1)_LOWER)
uninstall : uninstall-$$(_$(1)_LOWER)
uninstall-$$(_$(1)_LOWER) :
	@echo "UNINSTALL $$(_$(1)_FILES)"
	$(Q)rm -fr $$(addprefix $(DESTDIR)$$(_$(1)_DIR)/,$$(_$(1)_FILES))
endef

$(foreach GROUP,$(FILESGROUPS), $(eval $(call files_template,$(GROUP))))
