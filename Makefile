MAKE?=mingw32-make
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

ifeq ($(DEBUG),1)
	export debug=-Ddebug=1 -ggdb
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-Ddebug=2 -ggdb
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-Ddebug=3 -ggdb
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg=-Doutput=1
endif

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 
SRC=scene.c scene_builder.c

INCLUDEDIR=-I./../math/vec -I./../math/mat -I./../math/utils -I./../color -I./../shape -I./../mesh -I.

LIBNAME=libscene.a
OBJS=$(BUILDPATH)scene.o $(BUILDPATH)scene_builder.o

TESTSRC=test_scene.c
TESTBIN=test_scene.exe
TESTLIB=-lscene -lmesh -lshape -lcolor -lutilsmath -lmat -lvec  
TESTLIBDIR=-L$(BUILDDIR) \
		   -L./../mesh/$(BUILDDIR) \
		   -L./../shape/$(BUILDDIR) \
		   -L./../color/$(BUILDDIR) \
		   -L./../math/utils/$(BUILDDIR) \
		   -L./../math/mat/$(BUILDDIR) \
		   -L./../math/vec/$(BUILDDIR)

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
	