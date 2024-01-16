
include colours.mk

# The file extension used for object files
OFX = ".nd.o"

# Main target
_TARGET = train.nd.exe

ifdef CXXFLAGS
	CXXFLAGS += -DNDEBUG=1
else
	CXXFLAGS = -DNDEBUG=1
endif

COL = DRK_GREEN