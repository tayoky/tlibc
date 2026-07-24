# makefile include to find sysdeps

TARGET_SYSDEPS = $(wildcard $(TOP)/sysdeps/$(TARGET)/*.[cs] $(TOP)/sysdeps/$(TARGET)/*/*.[cs] $(TOP)/sysdeps/$(TARGET)/$(ARCH)/*.[cs])
GENERIC_SYSDEPS += $(wildcard $(TOP)/sysdeps/generic/*.[cs] $(TOP)/sysdeps/generic/*/*.[cs] $(TOP)/sysdeps/generic/$(ARCH)/*.[cs])
SYSDEPS = $(TARGET_SYSDEPS) $(GENERIC_SYSDEPS)

SRCS    = $(sort $(notdir $(SYSDEPS)))
SRCDIRS = $(sort $(dir $(TARGET_SYSDEPS))) $(sort $(dir $(GENERIC_SYSDEPS)))
