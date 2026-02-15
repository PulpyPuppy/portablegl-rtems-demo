PGM=${ARCH}/hello.exe

CSRCS = test.c
COBJS = $(CSRCS:%.c=${ARCH}/%.o)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CFLAGS += -I$(PGL_PATH)

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:	${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
