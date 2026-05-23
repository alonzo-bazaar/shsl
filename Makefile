CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -g3 -ggdb

tests:
	$(CC) $(CFLAGS) -o tests shsl.h tests.c
shsl:
	$(CC) $(CFLAGS) -x c -DSHSL_MAIN -o shsl shsl.h
test: tests
	./tests
all: tests shsl

clean:
	rm shsl tests

build: shsl tests
.PHONY: all test build
