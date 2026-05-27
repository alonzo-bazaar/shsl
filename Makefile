CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -ggdb
SHSL_DEFINES = -DSHSL_IMPLEMENTATION -DSHSL_MAIN
SHSL_LOG_DEFINES += -DSHSL_LOG_RETURN_ERROR -DSHSL_LOG_RETURN_ERROR_EXPR

ifeq ($(LOG_GC), yes)
	SHSL_LOG_DEFINES += -DSHSL_LOG_GC
endif	

tests: shsl.h tests.c
	$(CC) $(CFLAGS) -O0 $(SHSL_LOG_DEFINES) -o tests shsl.h tests.c
shsl: shsl.h
	$(CC) $(CFLAGS) $(SHSL_DEFINES) $(SHSL_LOG_DEFINES) -x c -o shsl shsl.h
clean:
	(test -a shsl) && rm shsl
	(test -a tests) && rm tests
test: tests
	./tests
