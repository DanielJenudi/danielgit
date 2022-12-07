#!/bin/bash

TARGET = $(shell basename  $(CURDIR))
DEPEND = sched.o pq_heap.o heap.o d_vector.o task.o uid.o 
SYS_DEPEND = semaphores.o

LIBS_DIR = ../../../ds/libs
OBJ_DIR = ../../../ds/obj

DEBUG_LIBSDIR = $(LIBS_DIR)/debug
RELEASE_LIBSDIR = $(LIBS_DIR)/release

DEBUG_OBJDIR = $(OBJ_DIR)/debug
RELEASE_OBJDIR = $(OBJ_DIR)/release

CC = gcc
GD_FLAGS = -ansi -pedantic-errors -Wall -Wextra -g -D_POSIX_C_SOURCE -pthread
GC_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -D_POSIX_C_SOURCE -pthread
OBJs_FLAGS = -c -fpic
LD_FLAGS = -L$(DEBUG_LIBSDIR) -Wl,-rpath=$(DEBUG_LIBSDIR)
INCLUDE_FLAG = -I../../../ds/include/

.PHONY: all	test release debug clean

test: debug 
	$(CC) $(LD_FLAGS) $(GD_FLAGS) $(INCLUDE_FLAG) -o watchdog.out -lwatchdog -l$(TARGET) $(patsubst %.o,-l%,$(DEPEND)) $(patsubst %.o,-l%,$(SYS_DEPEND)) 
	$(CC) $(LD_FLAGS) $(GD_FLAGS) $(INCLUDE_FLAG) -o $(TARGET).out $(TARGET)_test.c -l$(TARGET) $(patsubst %.o,-l%,$(DEPEND)) $(patsubst %.o,-l%,$(SYS_DEPEND))

debug: $(TARGET).c |debug_release_dir
	for i in $(patsubst %.o,../../../ds/%,$(DEPEND)); do make debug -C $$i; done
	for i in $(patsubst %.o,../../../system_programming/%,$(SYS_DEPEND)); do make debug -C $$i; done
	$(CC) $(GD_FLAGS) $(OBJs_FLAGS) $(INCLUDE_FLAG) watchdog.c -lpthread -D_POSIX_C_SOURSE
	$(CC) $(GD_FLAGS) $(OBJs_FLAGS) $(INCLUDE_FLAG) $(TARGET).c -lpthread -D_POSIX_C_SOURSE
	$(CC) -shared -o libwatchdog.so watchdog.o
	$(CC) -shared -o lib$(TARGET).so $(TARGET).o
	mv $(TARGET).o $(DEBUG_OBJDIR)
	mv watchdog.o $(DEBUG_OBJDIR)
	mv lib$(TARGET).so $(DEBUG_LIBSDIR)
	mv libwatchdog.so $(DEBUG_LIBSDIR)


release:$(TARGET).c |debug_release_dir
	for i in $(patsubst %.o,../../../ds/%,$(DEPEND)); do make release -C $$i; done
	for i in $(patsubst %.o,../../../system_programming/%,$(SYS_DEPEND)); do make debug -C $$i; done
	$(CC) $(GC_FLAGS) $(OBJs_FLAGS) $(INCLUDE_FLAG) $(TARGET).c
	$(CC) $(GC_FLAGS) $(OBJs_FLAGS) $(INCLUDE_FLAG) watchdog.c
	$(CC) -shared -o lib$(TARGET).so $(TARGET).o
	$(CC) -shared -o libwatchdog.so watchdog.o
	mv $(TARGET).o $(RELEASE_OBJDIR)
	mv watchdog.o $(RELEASE_OBJDIR)
	mv lib$(TARGET).so $(RELEASE_LIBSDIR)
	mv libwatchdog.so $(RELEASE_LIBSDIR)
	
all: debug release

debug_release_dir: 
	mkdir -p $(DEBUG_LIBSDIR)
	mkdir -p $(RELEASE_LIBSDIR)
	mkdir -p $(DEBUG_OBJDIR)
	mkdir -p $(RELEASE_OBJDIR)

clean:
	for i in $(patsubst %.o,../../../ds/%,$(DEPEND)); do make clean -C $$i; done
	for i in $(patsubst %.o,../../../system_programming/%,$(SYS_DEPEND)); do make clean -C $$i; done
	rm -f $(DEBUG_OBJDIR)/$(TARGET).o
	rm -f $(RELEASE_OBJDIR)/$(TARGET).o
	rm -f $(DEBUG_LIBSDIR)/lib$(TARGET).so
	rm -f $(RELEASE_LIBSDIR)/lib$(TARGET).so
	rm -f $(TARGET).out
	rm -f $(DEBUG_OBJDIR)/watchdog.o
	rm -f $(RELEASE_OBJDIR)/watchdog.o
	rm -f $(DEBUG_LIBSDIR)/libwatchdog.so
	rm -f $(RELEASE_LIBSDIR)/libwatchdog.so
	rm -f watchdog.out
