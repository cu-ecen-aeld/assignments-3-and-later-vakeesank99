#CROSS_COMPILE=aarch64-linux-gnu-
CC ?= $(CROSS_COMPILE)gcc
.PHONY: all clean

all: writer

writer: writer.c
	$(CC) -Wall -c -o writer writer.c

clean:
	rm -f *.o writer
