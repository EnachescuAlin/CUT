CFLAGS = -std=c99 -Wall
INCLUDE = -I../include

all: test

test: test.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

clean:
	rm test
