BUILD_DIR = build
PGM = $(BUILD_DIR)/hello.exe

CSRCS = test.c
COBJS = $(CSRCS:%.c=$(BUILD_DIR)/%.o)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CFLAGS += -I$(PGL_PATH)
LINK_LIBS += -lm

OBJS = $(COBJS) $(CXXOBJS) $(ASOBJS)

all: $(BUILD_DIR) $(PGM)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CPU_CFLAGS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(PGM): $(OBJS)
	$(make-exe)

clean:
	rm -rf $(BUILD_DIR)
