TARGET = fooer.out
OBJs = foo.o main.o

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g


$(TARGET) : $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(TARGET) 

main.o : 
	$(CC) $(CFLAGS) -c main.c

foo.o : 
	$(CC) $(CFLAGS) -c foo.c


.PHONY : all
all : $(TARGET)

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
