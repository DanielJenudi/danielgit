TARGET = test
OBJs = test.o queue.o /home/daniel/git/ds/queue/link_list/link_list.o
HEADERS = link_list.h  queue.h

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

.PHONY : all
all : $(TARGET)
	

$(TARGET) : $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(TARGET) 

$(OBJs): /home/daniel/git/ds/queue/link_list/$(HEADERS)


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
