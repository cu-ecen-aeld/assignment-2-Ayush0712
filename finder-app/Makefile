all: writer.c
	gcc writer.c -o writer

clean: writer
	rm -r writer

CROSS_COMPILE:
	aarch64-none-linux-gnu-gcc writer.c -o writer
