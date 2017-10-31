CFLAGS  = -std=c++11 -fpic -Wall $(platform) -c -o
INCLUDE = -I../include

all: cut.o libcut.so

cut.o: cut.cpp
	mkdir -p ../bin
	g++ $(CFLAGS) ../bin/cut.o $< $(INCLUDE)

libcut.so: cut.o
	g++ -shared $(platform) -o ../bin/libcut.so ../bin/cut.o

clean:
	rm -r ../bin
