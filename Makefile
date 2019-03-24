
CC = gcc
CFLAGS = -g
OBJECTS = postscript.o drawlist.o 
INCLUDES = postscript.h drawlist.h 

TARGET = lista

default: $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $*.o

postscript.o: postscript.c postscript.h

drawlist.o: drawlist.c $(INCLUDES)

tree.o: lista.c $(INCLUDES)

lista: lista.c $(INCLUDES) $(OBJECTS)
	$(CC) $(CFLAGS) lista.c $(OBJECTS) -lm -o lista

clean:
	rm -f *.o

