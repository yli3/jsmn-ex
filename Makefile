CC = gcc
CFLAGS = -Wall -g3
EXEC = app

$(EXEC): main.o
	$(CC) main.c -o $(EXEC) $(CFLAGS)

clean::
	rm *.o $(EXEC)
