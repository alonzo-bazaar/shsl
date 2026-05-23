CC = gcc
# removed pedantic flag because current style kinda requires I forward declare enums
# might readd at a later date :/
#CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -ggdb
CFLAGS = -Wall -Wextra -Werror -g3 -ggdb
SHSL_DEFINES = -DSHSL_IMPLEMENTATION -DSHSL_MAIN
SHSL_DEFINES += -DSHSL_LOG_RETURN_ERROR -DSHSL_LOG_RETURN_ERROR_EXPR

tests:
	$(CC) $(CFLAGS) -o tests shsl.h tests.c
shsl:
	$(CC) $(CFLAGS) $(SHSL_DEFINES) -x c -o shsl shsl.h
all: tests shsl
clean:
	rm shsl tests

test: tests
	./tests
