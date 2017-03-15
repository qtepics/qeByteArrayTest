# $File: //ASP/tec/gui/qeByteArrayTest/trunk/qeByteArrayTestApp/project/QEByteArrayTestApp.pro $
# $Revision: #2 $
# $DateTime: 2016/11/06 13:05:22 $
# Last checked in by: $Author: starritt $
#
#
# Simple console application to demonstrate programatically using a QEByteArray class to write and read to an EPICS record
#
#  Author:
#    Andrew Rhyder
#  Contact details:
#    andrew.rhyder@synchrotron.org.au
#

# Points to the target directoy in which bin/EPICS_HOST_ARCH/QEByteArrayTest
# will be created. This follows the regular EPICS Makefile paradigm.
#
TOP=../..

message ("QT_MAJOR_VERSION = " $$QT_MAJOR_VERSION )

QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle

TARGET = QEByteArrayTest
TEMPLATE = app

# Determine EPICS_BASE
_EPICS_BASE = $$(EPICS_BASE)

# Check EPICS dependancies
isEmpty( _EPICS_BASE ) {
    error( "EPICS_BASE must be defined. Ensure EPICS is installed and EPICS_BASE environment variable is defined." )
}

_EPICS_HOST_ARCH = $$(EPICS_HOST_ARCH)
isEmpty( _EPICS_HOST_ARCH ) {
    error( "EPICS_HOST_ARCH must be defined. Ensure EPICS is installed and EPICS_HOST_ARCH environment variable is defined." )
}

# Determine QE framework library
#
_QE_FRAMEWORK = $$(QE_FRAMEWORK)
isEmpty( _QE_FRAMEWORK ) {
    error( "QE_FRAMEWORK must be defined. Ensure EPICS is installed and EPICS_HOST_ARCH environment variable is defined." )
}

# Install the generated plugin library and include files in QE_TARGET_DIR if defined.
_QE_TARGET_DIR = $$(QE_TARGET_DIR)
isEmpty( _QE_TARGET_DIR ) {
    INSTALL_DIR = $$TOP
    message( "QE_TARGET_DIR is not defined. The QE GUI application will be installed into the <top> directory." )
} else {
    INSTALL_DIR = $$(QE_TARGET_DIR)
    message( "QE_TARGET_DIR is defined. The QE GUI application will be installed directly into" $$INSTALL_DIR )
}

# The APPLICATION ends up here.
#
DESTDIR = $$INSTALL_DIR/bin/$$(EPICS_HOST_ARCH)

# Place all intermediate generated files in architecture specific locations
#
MOC_DIR        = O.$$(EPICS_HOST_ARCH)/moc
OBJECTS_DIR    = O.$$(EPICS_HOST_ARCH)/obj
UI_DIR         = O.$$(EPICS_HOST_ARCH)/ui
RCC_DIR        = O.$$(EPICS_HOST_ARCH)/rcc
MAKEFILE       = Makefile.$$(EPICS_HOST_ARCH)

# We don't get this include path for free - need to be explicit.
#
INCLUDEPATH += O.$$(EPICS_HOST_ARCH)/ui

# Project source files
#
SOURCES += main.cpp \
    arraywriter.cpp

HEADERS += \
    arraywriter.h

INCLUDEPATH += .

# Include header files from the QE framework
#
INCLUDEPATH += $$(QE_FRAMEWORK)/include

LIBS += -L$$(EPICS_BASE)/lib/$$(EPICS_HOST_ARCH) -lca -lCom

# Set run time path for shared libraries
#
unix: QMAKE_LFLAGS += -Wl,-rpath,$$(EPICS_BASE)/lib/$$(EPICS_HOST_ARCH)

LIBS += -L$$(QE_FRAMEWORK)/lib/$$(EPICS_HOST_ARCH) -lQEPlugin
unix: QMAKE_LFLAGS += -Wl,-rpath,$$(QE_FRAMEWORK)/lib/$$(EPICS_HOST_ARCH)

# end
