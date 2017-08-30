CFLAGS  = -std=c99 -fpic -Wall $(platform) -c -o
INCLUDE = -I../include

all: cut.o libcut.so

cut.o: cut.c
	mkdir -p ../bin
	gcc $(CFLAGS) ../bin/cut.o $< $(INCLUDE)

libcut.so: cut.o
	gcc -shared $(platform) -o ../bin/libcut.so ../bin/cut.o

clean:
	rm -r ../bin
