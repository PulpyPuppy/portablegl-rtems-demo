include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(RTEMS_SHARE)/make/directory.cfg

SUBDIRS=hello

ifeq ($(RTEMS_HAS_POSIX_API),yes)
SUBDIRS += hello_triangle
endif
