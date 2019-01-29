CC=gcc
CFLAGS=-Wall -O3 -g
TARGET=libpmi.so pmiserver test_value

all: $(TARGET)

libpmi.so: ./libpmi/pmi.c
	$(CC) $(CFLAGS) -shared -fpic $^ -o $@

pmiserver: ./server/main.c
	$(CC) $(CFLAGS) -o $@ $^

test_value: libpmi.so test/test_values.c
	$(CC) $(CFLAGS) -Wl,-rpath,$(PWD) -L. -lpmi -o $@ -I$(PWD)/libpmi/ $^

clean:
	rm -fr $(TARGET)

