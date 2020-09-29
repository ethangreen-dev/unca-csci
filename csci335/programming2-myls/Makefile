CC = gcc
CFLAGS = -O -Wall -g
LFLAGS = 

all: myls

myls: myls.c linked_list.c linked_list.h console.c console.h
	$(CC) $(CFLAGS) -c -o myls.o myls.c
	$(CC) $(CFLAGS) -c -o linked_list.o linked_list.c
	$(CC) $(CFLAGS) -c -o console.o console.c
	$(CC) $(CFLAGS) -c -o shelper.o shelper.c
	
	$(CC) $(CFLAGS) -o myls linked_list.o console.o shelper.o myls.o
	
clean:
	rm -f myls.o linked_list.o console.o shelper.o myls