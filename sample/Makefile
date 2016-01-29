CFLAGS = -std=c99 -Wall

all: test

test: test.c
	gcc $(CFLAGS) -o $@ $< -lcut

clean:
	rm test
