#----- START OF INPUT BLOCK -----#
TARGET=oostubs

# one of linux, linux64
# the platforms osxcross and windows are also possible but are not supported
PLATFORM=linux

CFLAGS=-Wall -O0 -g -Wpedantic
CXXFLAGS=-std=c++11
LDFLAGS=-O0
ASMFLAGS=-g

OBJECT_IGNORE= 

INCPATHS=
LDPATHS=
LIBS=

GDBFLAGS=
EMUFLAGS=
DEBUGFLAGS=

#----- END OF INPUT BLOCK -----#

include misc/${PLATFORM}/config.mk
include misc/rules.mk
-include misc/${PLATFORM}/rules.mk
