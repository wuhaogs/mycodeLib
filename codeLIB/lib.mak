SRCDIR = ./
INCDIR = ./
COMDIR = $(PRJ_HOME)/common
OBJDIR = $(PRJ_HOME)/obj
LIBDIR = $(PRJ_HOME)/lib

#CC    = /usr/bin/cc
#AR    = /usr/bin/ar
#RANLIB = /home/TPS/gaofei/fanggj-OCTEON-SDK/tools-gcc-4.7/bin/mips64-octeon-linux-gnu-ranlib



ifeq ($(bps), tetratest)
CFLAGS = -ggdb -c -Wall -DLINUX -I$(INCDIR) -I$(COMDIR) $(INC) -DET_BIG_ENDIAN -mabi=n32 -DTESTMODE
else ifeq ($(bps), pdttest)
CFLAGS = -ggdb -c -Wall -DLINUX -I$(INCDIR) -I$(COMDIR) $(INC) -DET_BIG_ENDIAN -mabi=n32 -DTESTMODE -DLIB_PDT
else ifeq ($(bps), tetra)
CFLAGS = -ggdb -c -Wall -DLINUX -I$(INCDIR) -I$(COMDIR) $(INC) -DET_BIG_ENDIAN -mabi=n32
else
# my test
#CFLAGS = -Os -ggdb -c -Wall -DLINUX -I$(INCDIR) -I$(COMDIR) $(INC) -DET_BIG_ENDIAN
CFLAGS = -Os -ggdb -c -fno-strict-aliasing -Wall -DLINUX -I$(INCDIR) -I$(COMDIR) $(INC) -DET_BIG_ENDIAN
#-O2  -fno-strict-aliasing -Wall
endif

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)


all: $(LIBDIR)/lib$(LIB).a
$(LIBDIR)/lib$(LIB).a: $(LIBDIR) $(OBJDIR) $(OBJS)
	@$(AR) -crus $@ $(OBJS)

	#@$(RANLIB) $@       #del by creater

$(OBJDIR):
	@test -d $@ || mkdir $@

$(LIBDIR):
	@test -d $@ || mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -o $@ $<

cleann:
	@rm -rf $(OBJDIR) $(LIBDIR)/lib$(LIB).a
