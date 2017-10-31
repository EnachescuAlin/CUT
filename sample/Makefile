CFLAGS = -std=c99 -Wall

all: test module_sample1 module_sample2 assert_sample test_threads

test: test.c
	gcc $(CFLAGS) -o $@ $< -lcut -lpthread

module_sample1:
	gcc $(CFLAGS) -o module_sample1 module1.c module2.c main1.c -lcut -lpthread

module_sample2:
	gcc $(CFLAGS) -o module_sample2 module1.c module2.c main2.c -lcut -lpthread

assert_sample:
	gcc $(CFLAGS) -o assert_sample assert.c -lcut -lpthread

test_threads:
	gcc $(CFLAGS) -o test_threads test_threads.c -lcut -lpthread

clean:
	rm test
	rm module_sample1
	rm module_sample2
	rm assert_sample
	rm test_threads
