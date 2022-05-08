CC=clang
GXX=clang++
CFLAGS=-I.

all: cshg-imp cshg-md cshg

main.o: main.cpp
	$(GXX) -std=c++17 -g -c blu.cpp
builddata.o: builddata.cpp
	$(GXX) -std=c++17 -g -c builddata.cpp
scanpage.o: scanpage.cpp
	$(GXX) -std=c++17 -g -c scanpage.cpp
cshg: main.o scanpage.o builddata.o
	$(GXX) -std=c++17 -g blu.o scanpage.o builddata.o -o blush

##//import program

imp.o: imp.cpp
	$(GXX) -std=c++17 -c imp.cpp
cshg-imp: imp.o
	$(GXX) -std=c++17 -g imp.o -o cshg-imp

##//markdown processor

cshg-md: bmd.o
	$(CC) -o blu.bmd bmd.o
