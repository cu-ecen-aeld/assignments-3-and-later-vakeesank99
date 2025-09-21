CROSS_COMPILE=aarch64-linux-gnu-

all: writer
writer: writer.o
	$(CROSS_COMPILE)gcc -Wall -o writer writer.o

writer:writer.c
	$(CROSS_COMPILE)gcc  -Wall -o writer.o writer.c

.PHONY: clean
clean:
	rm -f *.o writer
