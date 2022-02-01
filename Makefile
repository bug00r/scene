#MAKE?=mingw32-make
AR?=ar
ARFLAGS?=rcs
PATHSEP?=/
CC=gcc
BUILDROOT?=build

ifeq ($(CLANG),1)
	export CC=clang
endif

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

INSTALL_ROOT?=$(BUILDPATH)

ifeq ($(DEBUG),1)
	export debug=-ggdb -Ddebug=1
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-ggdb -Ddebug=2
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-ggdb -Ddebug=3
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg= -Doutput=1
endif

BIT_SUFFIX=

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra $(debug)
#-ggdb
#-pg for profiling 

LIBSDIR?=-L/c/dev/lib$(BIT_SUFFIX)
INCLUDE?=-I/c/dev/include -I.

NAME=scene
SRC=$(NAME).c scene_builder.c

INCLUDEDIR=$(INCLUDE) -I.

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)

OBJS=$(BUILDPATH)scene.o $(BUILDPATH)scene_builder.o

TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB=-l$(NAME) -lr_font -lmesh -ltexture -lshape -lcrgb_array -larray -lcolor -lgeometry -lutilsmath -lmat -lvec -ldl_list  
TESTLIBDIR=-L$(BUILDDIR) $(LIBSDIR)

all: mkbuilddir $(LIB) $(TESTBIN)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS):
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@ $(INCLUDEDIR)
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) font_provider_default.c -o $@ $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB)
	
.PHONY: clean mkbuilddir test

test:
	./$(TESTBIN)

mkbuilddir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dfr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./$(NAME).h $(INSTALL_ROOT)include$(PATHSEP)$(NAME).h
	cp ./$(NAME)_builder.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_builder.h
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)
