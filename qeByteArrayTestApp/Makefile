# $File: //ASP/tec/gui/qeByteArrayTest/trunk/qeByteArrayTestApp/Makefile $
# $Revision: #1 $
# $DateTime: 2016/11/06 13:05:22 $
# Last checked in by: $Author: starritt $
#
# This make file is the bridge beween the EPICS build system and the Qt project qmake/make paradigm.
#

TOP=..

# Pick up configure/RELEASE definitions.
#
include $(TOP)/configure/CONFIG
#
# Note: we do not include the rule $(TOP)/configure/RULES

# Create environment variables from Make variable as defined in $(TOP)/configure/RELEASE
# Note use of := which avoids "*** Recursive variable `EPICS_BASE' references itself (eventually)" error
#
export EPICS_BASE := $(EPICS_BASE)
export QE_FRAMEWORK := $(QE_FRAMEWORK)

# Commands
#
NOOP = :

# Directories of interest.
#
SOURCE_DIR = project
TARGET_DIR = $(TOP)/bin/$(EPICS_HOST_ARCH)

# Files
#
MAKEFILE = Makefile.$(EPICS_HOST_ARCH)
PROJECT  = QEByteArrayTestApp.pro

ifeq ($(OS),Windows_NT)
   BINFILE = QEByteArrayTest.exe
else
   BINFILE = QEByteArrayTest
endif

TARGET=$(TARGET_DIR)/$(BINFILE)

.PHONY: all install clean uninstall always

all: $(TARGET)

install: $(TARGET)

# The project file places the executable in bin/architecture directory, no additonal install required.
# Note: we always run this step
#
$(TARGET) : $(SOURCE_DIR)/$(MAKEFILE)  always
	@echo "=== Building $(BINFILE) application"                 && \
	cd  $(SOURCE_DIR)                                           && \
	make -j3  -f $(MAKEFILE)                                    && \
	echo "=== Complete"


$(SOURCE_DIR)/$(MAKEFILE) : $(SOURCE_DIR)/$(PROJECT)
	@echo "=== Running qmake - generating $(MAKEFILE)"          && \
	cd  $(SOURCE_DIR)                                           && \
	qmake -o $(MAKEFILE) $(PROJECT) -r


# Do a qt clean, then delete all qmake generated Makefiles.
# Note the : "command" is a null command in bash.
#
clean:
	cd  $(SOURCE_DIR) && test -f $(MAKEFILE) && make -f $(MAKEFILE) clean && $(RM) $(MAKEFILE) || $(NOOP)


uninstall:
	rm -f $(TARGET)

always:

# end