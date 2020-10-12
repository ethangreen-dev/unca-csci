CC = gcc
CFLAGS = -O -Wall -g
LFLAGS =
OUT = mygrep

all: mygrep

mygrep: mygrep.c mygrep.h linked_list.c linked_list.h freader.c freader.h
	$(CC) $(CFLAGS) -c -o mygrep.o mygrep.c
	$(CC) $(CFLAGS) -c -o freader.o freader.c
	# $(CC) $(CFLAGS) -c -o linked_list.o linked_list.c
	# $(CC) $(CFLAGS) -c -o console.o console.c

	$(CC) $(LFLAGS) -o $(OUT) mygrep.o freader.o

clean:
	rm -f mygrep.o linked_list.o console.o $(OUT)