TARGET = test
HEADERS = /home/daniel/git/ds/stack/api_stack.h  min_stack.h
OBJs = test.o min_stack.o /home/daniel/git/ds/stack/stack.o

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

.PHONY : all
all : $(TARGET)
	

$(TARGET) : $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(TARGET) 

$(OBJs):$(HEADERS)


.PHONY : debug	
debug : 
	gdb -tui $(TARGET)
	
.PHONY : libncreat
libcreat :
	ar -r libfoo.ar $(OBJs)
	
.PHONY : clean	
clean :
	rm $(OBJs) $(TARGET)
	
.PHONY : libclean	
libclean :
	rm libfoo.ar
