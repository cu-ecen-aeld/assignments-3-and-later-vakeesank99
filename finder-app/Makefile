#CROSS_COMPILE=aarch64-linux-gnu-
CC ?= $(CROSS_COMPILE)gcc
.PHONY: all clean

all: writer

writer: writer.o
	$(CC) -Wall -o writer writer.o

writer.o: writer.c
	$(CC) -Wall -o writer.o writer.c

clean:
	rm -f *.o writer
