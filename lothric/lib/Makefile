CC=clang
CFLAGS+=-Wall -Wextra -Werror -I../include

all: linked_list

%: %.c
	mkdir -p bin
	$(CC) $(CFLAGS) $@.c tests/test_$@.c -o bin/test_$@

tests:
	sh scripts/run_tests.sh

.PHONY: clean

clean:
	rm bin/*
