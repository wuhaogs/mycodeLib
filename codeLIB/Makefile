export PRJ_HOME = $(shell pwd)
#please add other dir
SUBDIRS	= core test
LIBPATH = $(PRJ_HOME)/lib
OBJDIR = ./obj


#AR     = /usr/bin/ar
#RANLIB = /home/TPS/gaofei/fanggj-OCTEON-SDK/tools-gcc-4.7/bin/mips64-octeon-linux-gnu-ranlib


OBJS = $(foreach dir,$(SUBDIRS),$(subst $(dir)/,$(OBJDIR)/,$(subst .c,.o,$(wildcard $(dir)/*.c))))

ifeq ($(bps), tetratest)
TARGET = bpslib_bsey_tetratest.a
else ifeq ($(bps), pdttest)
TARGET = bpslib_bsey_pdttest.a
else ifeq ($(bps), tetra)
TARGET = bpslib_bsey_tetra.a
else
# for my test
TARGET = mycode.a
endif


all:main_all post_build

app:all	
	$(MAKE) -C ../main
	#cd ../main; make; \	
	cp ../main/apptest ./
main_all:
	mkdir -p $(LIBPATH)
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) ;)
	@$(AR) rv $(TARGET) $(OBJS)
	#$(RANLIB) $(TARGET)   #wuh del
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBPATH)

post_build:
	echo "do the next step"

clean:
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) cleann ;)
	@rm -rf $(TARGET)
	@rm -rf $(LIBPATH)
	@rm -rf apptest