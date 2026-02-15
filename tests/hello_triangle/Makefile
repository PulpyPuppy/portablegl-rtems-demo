PGM=${ARCH}/hello_triangle.exe

CSRCS = test.c
COBJS = $(CSRCS:%.c=${ARCH}/%.o)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CFLAGS += -I$(PGL_PATH)
LINK_LIBS += -lm

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:	${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
