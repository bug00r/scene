_CFLAGS:=$(CFLAGS)
CFLAGS:=$(_CFLAGS)
_LDFLAGS:=$(LDFLAGS)
LDFLAGS:=$(_LDFLAGS)

ARFLAGS?=rcs
PATHSEP?=/
BUILDROOT?=build

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

ifndef PREFIX
	INSTALL_ROOT=$(BUILDPATH)
else
	INSTALL_ROOT=$(PREFIX)$(PATHSEP)
	ifeq ($(INSTALL_ROOT),/)
	INSTALL_ROOT=$(BUILDPATH)
	endif
endif

ifdef DEBUG
	CFLAGS+=-ggdb
	ifeq ($(DEBUG),)
	CFLAGS+=-Ddebug=1
	else 
	CFLAGS+=-Ddebug=$(DEBUG)
	endif
endif

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

override CFLAGS+=-std=c11 -Wall 
#-Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

override LDFLAGS+=-L/c/dev/lib$(BIT_SUFFIX) -L$(BUILDDIR)
override CFLAGS+=-I. -I/c/dev/include 

NAME=scene
SRC=$(NAME).c scene_builder.c

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)

OBJS=$(BUILDPATH)scene.o $(BUILDPATH)scene_builder.o

TESTBIN=$(BUILDPATH)test_$(NAME).exe

override LDFLAGS+=-l$(NAME) -lr_font -lmesh -ltexture -lshape -lcrgb_array -larray -lcolor -lgeometry -lutilsmath -lmat -lvec -ldl_list  

all: mkbuilddir $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS):
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) font_provider_default.c -o $@ $(LDFLAGS)
	
.PHONY: clean mkbuilddir test

test: mkbuilddir $(TESTBIN)
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
