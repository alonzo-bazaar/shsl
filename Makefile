CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -ggdb
SHSL_DEFINES = -DSHSL_IMPLEMENTATION -DSHSL_MAIN
SHSL_DEFINES += -DSHSL_LOG_RETURN_ERROR -DSHSL_LOG_RETURN_ERROR_EXPR

tests: shsl.h tests.c
	$(CC) $(CFLAGS) -o tests shsl.h tests.c
shsl: shsl.h
	$(CC) $(CFLAGS) $(SHSL_DEFINES) -x c -o shsl shsl.h
all: tests shsl
clean:
	rm shsl tests

test: tests
	./tests
