CC = gcc

SHSL_IMPL_DEFS = -DSHSL_IMPLEMENTATION
SHSL_ERR_LOG_DEFS = -DSHSL_LOG_ERROR -DSHSL_LOG_ERROR_EXPR
SHSL_MEM_LOG_DEFS = -DSHSL_LOG_GC -DSHSL_LOG_DEL_REF

TEST_LOG_DEFS = -DSHSL_LOG_TESTS

CFLAGS = -Wall -Wextra -Wpedantic -Wswitch -Werror -Wno-parentheses -O0 -g3 -ggdb
SHSL_LIB_CFLAGS = $(CFLAGS)
# log whenver an error value is returned
ifeq ($(LOG_ERR), yes)
	SHSL_LIB_CFLAGS += $(SHSL_ERR_LOG_DEFS)
endif
# log all significant memory actions
# if used for regular tests it's gonna turn to logging diarrhea
# recommended you only use this you plan to piecemeal test with ./shsl -e or ./shsl -r
ifeq ($(LOG_MEM), yes)
	SHSL_LIB_CFLAGS += $(SHSL_MEM_LOG_DEFS) 
endif	

#SHSL_MAIN_CFLAGS = $(SHSL_LIB_CFLAGS) $(SHSL_IMPL_DEFS) -DSHSL_MAIN -x c
SHSL_MAIN_CFLAGS = $(SHSL_LIB_CFLAGS) $(SHSL_IMPL_DEFS) -x c
TEST_MAIN_CFLAGS = $(SHSL_LIB_CFLAGS)
ifeq ($(LOG_TESTS), yes)
	TEST_MAIN_CFLAGS += $(TEST_LOG_DEFS)
endif

shsl: shsl.h
	$(CC) $(SHSL_MAIN_CFLAGS) -o shsl shsl.h
tests: shsl.h tests.c
	$(CC) $(TEST_MAIN_CFLAGS) -o tests tests.c 
.PHONY: shsl tests

# delete shsl and tests file only if they exist
# https://stackoverflow.com/questions/5553352/how-do-i-check-if-file-exists-in-makefile-so-i-can-delete-it
clean:
ifneq ("", "$(wildcard shsl)")
	rm shsl
endif
ifneq ("", "$(wildcard tests)")
	rm tests
endif
test: tests
	./tests
