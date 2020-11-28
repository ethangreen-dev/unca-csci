CC = gcc
CFLAGS = -O -Wall -g
LFLAGS =
OUT = my-pi

all: mypy

mypy: my-pi.c picalc.c picalc.h
	$(CC) $(CFLAGS) -c -o my-pi.o my-pi.c
	$(CC) $(CFLAGS) -c -o picalc.o picalc.c

	$(CC) $(LFLAGS) -o $(OUT) my-pi.o picalc.o