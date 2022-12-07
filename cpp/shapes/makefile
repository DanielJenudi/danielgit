#!/bin/bash

TARGET = $(shell basename  $(CURDIR))
DEPEND = 

LIBS_DIR = ../libs
OBJ_DIR = ../obj

DEBUG_LIBSDIR = $(LIBS_DIR)/debug
RELEASE_LIBSDIR = $(LIBS_DIR)/release

DEBUG_OBJDIR = $(OBJ_DIR)/debug
RELEASE_OBJDIR = $(OBJ_DIR)/release

CC = g++ -std=c++11 
GD_FLAGS = -pedantic-errors -Wall -Wextra -g -pthread
GC_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -pthread
OBJs_FLAGS = -c -fpic -pthread
LD_FLAGS = -L$(DEBUG_LIBSDIR) -Wl,-rpath=$(DEBUG_LIBSDIR)
INCLUDE_FLAG = -I ../include


.PHONY: all	test release debug clean 

test: debug 
	$(CC) $(LD_FLAGS) $(GD_FLAGS) $(INCLUDE_FLAG) -o test_$(TARGET).out \
	$(TARGET)_test.cpp -l$(TARGET) $(patsubst %.o,-l%,$(DEPEND)) 

debug: debug_release_dir
	for i in $(patsubst %.o,../%,$(DEPEND)); do make debug -C $$i; done
	$(CC) $(GD_FLAGS) $(OBJs_FLAGS) $(INCLUDE_FLAG) $(TARGET).cpp
	$(CC) -shared -o lib$(TARGET).so $(TARGET).o
	mv $(TARGET).o $(DEBUG_OBJDIR)
	mv lib$(TARGET).so $(DEBUG_LIBSDIR)

release: debug_release_dir
	for i in $(patsubst %.o,../%,$(DEPEND)); do make release -C $$i; done
	$(CC) $(GC_FLAGS) $(OBJs_FLAGS) $(INCLUDE_FLAG) $(TARGET).cpp 
	$(CC) -shared -o lib$(TARGET).so $(TARGET).o
	mv $(TARGET).o $(RELEASE_OBJDIR)
	mv lib$(TARGET).so $(RELEASE_LIBSDIR)
	
all: debug release

debug_release_dir: 
	mkdir -p $(DEBUG_LIBSDIR)
	mkdir -p $(RELEASE_LIBSDIR)
	mkdir -p $(DEBUG_OBJDIR)
	mkdir -p $(RELEASE_OBJDIR)

clean:
	for i in $(patsubst %.o,../%,$(DEPEND)); do make clean -C $$i; done
	rm -f $(DEBUG_OBJDIR)/$(TARGET).o
	rm -f $(RELEASE_OBJDIR)/$(TARGET).o
	rm -f $(DEBUG_LIBSDIR)/lib$(TARGET).so
	rm -f $(RELEASE_LIBSDIR)/lib$(TARGET).so
	rm -f test_$(TARGET).out


