#CROSS_COMPILE=?

#writer: writer.o
#	$(CROSS_COMPILE)gcc -Wall -o writer writer.o
.PHONY: all
all: writer
writer:writer.c
	$(CROSS_COMPILE)gcc  -Wall -o writer writer.c

.PHONY: clean
clean:
	rm -f *.o writer
