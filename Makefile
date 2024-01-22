# If the user has defined the variable NDEBUG and NDEBUG is true, include ndebug.mk
# else, include debug.mk
ifdef NDEBUG
	DEBUG_NDEBUG_MAKEFILE = ndebug.mk
else
	DEBUG_NDEBUG_MAKEFILE = debug.mk
endif
include $(DEBUG_NDEBUG_MAKEFILE)

include universal.mk
