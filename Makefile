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

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 

LIB?=-L/c/dev/lib
INCLUDE?=-I/c/dev/include -I.

SRC=scene.c scene_builder.c

INCLUDEDIR=$(INCLUDE) -I.

LIBNAME=libscene.a
OBJS=$(BUILDPATH)scene.o $(BUILDPATH)scene_builder.o

TESTSRC=test_scene.c
TESTBIN=test_scene.exe
TESTLIB=-lscene -lmesh -lshape -lcolor -lutilsmath -lmat -lvec  
TESTLIBDIR=-L$(BUILDDIR) $(LIB)

all: mkbuilddir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(OBJS)

$(BUILDPATH)scene_builder.o: scene_builder.c scene_builder.h
	$(CC) $(CFLAGS) -c scene_builder.c -o $(BUILDPATH)scene_builder.o  $(INCLUDEDIR) $(debug)

$(BUILDPATH)scene.o: scene.c scene.h
	$(CC) $(CFLAGS) -c scene.c -o $(BUILDPATH)scene.o $(INCLUDEDIR) $(debug)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)
	
.PHONY: clean mkbuilddir test

test:
	./$(BUILDPATH)$(TESTBIN)

mkbuilddir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dfr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib
	cp ./scene.h $(INSTALL_ROOT)include/scene.h
	cp ./scene_builder.h $(INSTALL_ROOT)include/scene_builder.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib/$(LIBNAME)
