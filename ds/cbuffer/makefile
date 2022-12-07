TARGET = test.out
OBJs = cbuffer.o cbuffer_test.o
HEADERS = cbuffer.h

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

.PHONY : all
all : $(TARGET)
	

$(TARGET) : $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(TARGET) 

$(OBJs): $(HEADERS)


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
	
