#export PATH := $(PATH):/home/TPS/gaofei/fanggj-OCTEON-SDK/tools-gcc-4.7/bin/
#export CROSS_COMPILE := mips64-octeon-linux-gnu-
#export CC := $(CROSS_COMPILE)gcc
#export LD := $(CROSS_COMPILE)ld
#export AR := $(CROSS_COMPILE)ar
export PRJ_DIR=$(shell pwd)

version_major  = $(shell egrep "\#define[[:space:]]*MYCODE_VER_MAJOR" ./userAppInit.c | sed -e 's/\#define//g' | sed -e 's/MYCODE_VER_MAJOR//g' | sed -e 's/[\t\ ]//g')
version_uper   = $(shell egrep "\#define[[:space:]]*MYCODE_VER_UPPER" ./userAppInit.c | sed -e 's/\#define//g' | sed -e 's/MYCODE_VER_UPPER//g' | sed -e 's/[\t\ ]//g')
version_middle = $(shell egrep "\#define[[:space:]]*MYCODE_VER_MIDDLE" ./userAppInit.c | sed -e 's/\#define//g' | sed -e 's/MYCODE_VER_MIDDLE//g' | sed -e 's/[\t\ ]//g')
version_minor  = $(shell egrep "\#define[[:space:]]*MYCODE_VER_MINOR" ./userAppInit.c | sed -e 's/\#define//g' | sed -e 's/MYCODE_VER_MINOR//g' | sed -e 's/[\t\ ]//g')
VERSION_ALL    = $(version_major)$(version_uper)$(version_middle)$(version_minor)

SRC_OBJS := $(wildcard *.c)
OBJS := $(SRC_OBJS:.c=.o)

ifeq ($(image), tetratest)

else ifeq ($(image), pdttest)

else ifeq ($(image), tetra)
export TARGET_NAME = Linux_BseyImage_Tetra_$(VERSION_ALL)
LIB_VER = LIB_TETRA_NORMAL
bps_libs := ../build/TETRA_BSR_LINUX.a
bps_libs += ../build/TETRA_BSC_LINUX.a
bps_libs += ../build/fallback_linux_lib.a
bps_libs += ../../../../BPS/build/bsey/bpslib_bsey_tetra.a
else
export TARGET_NAME = linux_mycode_$(VERSION_ALL)

LIB_VER = LIB_PDT_NORMAL
bps_libs := ../codeLIB/mycode.a
#bps_libs += ../build/PDTBSC_LINUX.a
endif

#other module
bps_libs += ../build/Linux_bps_pub_lib_32.a
#bps_libs += ../build/bsc_clk_lib_pdt.a
#bps_libs += ../build/bsc_gps_lib_pdt.a
#-l(上层逻辑lib) -l(中间封装lib) -l(基础lib) -l(系统lib)
#尽量让lib是垂直关系，避免循环依赖

app: userAppInit.o
	@echo "building mycode  app ......"
	@echo "$(Q)$(CC) $(OBJS) $(bps_libs) -lpthread -lrt -rdynamic -ldl -lm -mabi=n32 -o $(TARGET_NAME)"
	@$(Q)$(CC) $(OBJS) $(bps_libs) -lpthread -lrt -rdynamic -ldl -lm  -o $(TARGET_NAME)
	@cp $(TARGET_NAME) apptest
	@rm -rf $(OBJS) $(OBJS:%.o=%.d)
	@echo "building mycode app ok !!!!!"

userAppInit.o:
	#$(CC) -c -D$(LIB_VER) -mabi=n32 userAppInit.c
	$(CC) -c -D$(LIB_VER)  userAppInit.c

clean:
	@rm -rf $(OBJS) $(OBJS:%.o=%.d)
	@echo "rm -rf $(TARGET_NAME)"
	@$(Q)rm -rf $(TARGET_NAME)
	@echo "cleanning mycode app ok ......"