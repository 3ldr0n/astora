CC=clang
CFLAGS+=-Wall -Wextra -Werror -I../include -lm

all: list map

%: %.c
	mkdir -p bin
	$(CC) $(CFLAGS) commons.c $@.c tests/test_$@.c -o bin/test_$@

tests:
	sh scripts/run_tests.sh

.PHONY: clean

clean:
	rm bin/*
