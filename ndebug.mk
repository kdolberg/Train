
include colours.mk

# The file extension used for object files
OFX = .nd.o

# Main target
_TARGET = train.nd

ifdef CXXFLAGS
	CXXFLAGS += -DNDEBUG=1
else
	CXXFLAGS = -DNDEBUG=1
endif

COL = $(DRK_GREEN) 

# Output filenames for testing
OUT_NET_FILENAME = ndebug_out.nn
LOG_FILE = ndebug_log.txt
