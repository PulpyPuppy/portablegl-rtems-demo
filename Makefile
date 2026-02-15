include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(RTEMS_SHARE)/make/directory.cfg

PROJ_ROOT:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PGL_PATH:=$(PROJ_ROOT)/libs/PortableGL
export PGL_PATH

SUBDIRS=tests

