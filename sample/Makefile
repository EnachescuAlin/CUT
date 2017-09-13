CFLAGS = -std=c99 -Wall

all: test module_sample1 module_sample2

test: test.c
	gcc $(CFLAGS) -o $@ $< -lcut

module_sample1:
	gcc $(CFLAGS) -o module_sample1 module1.c module2.c main1.c -lcut

module_sample2:
	gcc $(CFLAGS) -o module_sample2 module1.c module2.c main2.c -lcut

clean:
	rm test
	rm module_sample1
	rm module_sample2
