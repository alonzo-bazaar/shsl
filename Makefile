#CC = gcc
# please beweare
# the author quite likes having lots of compile time configurability
SHSL_ERR_LOG_DEFS = -DSHSL_LOG_ERROR -DSHSL_LOG_ERROR_EXPR
SHSL_MEM_LOG_DEFS = -DSHSL_LOG_GC -DSHSL_LOG_DEL_REF

TEST_LOG_DEFS = -DSHSL_LOG_TESTS

CFLAGS = -Wall -Wextra -Wpedantic -Wswitch -Werror -Wno-parentheses -O0 -g3 -ggdb
SHSL_CFLAGS = $(CFLAGS)
# log whenver an error value is returned
ifeq ($(LOG_ERR), yes)
	SHSL_CFLAGS += $(SHSL_ERR_LOG_DEFS)
endif
# log all significant memory actions
# if used for regular tests it's gonna turn to logging diarrhea
# recommended you only use this you plan to piecemeal test
# with ./shsl -e or ./shsl -r
ifeq ($(LOG_MEM), yes)
	SHSL_CFLAGS += $(SHSL_MEM_LOG_DEFS) 
endif	

TEST_CFLAGS = $(SHSL_CFLAGS)
ifeq ($(LOG_TESTS), yes)
	TEST_MAIN_CFLAGS += $(TEST_LOG_DEFS)
endif

.PHONY: shsl tests
shsl: shsl.h
	$(CC) $(SHSL_CFLAGS) -o shsl shsl.c
tests: shsl.h tests.c
	$(CC) $(TEST_CFLAGS) -o tests tests.c 
test: tests
	./tests

# https://stackoverflow.com/questions/5553352
# How do I check if file exists in Makefile so I can delete it?
clean:
ifneq ("", "$(wildcard shsl)")
	rm shsl
endif
ifneq ("", "$(wildcard tests)")
	rm tests
endif
