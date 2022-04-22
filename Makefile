CC=clang
GXX=clang++
CFLAGS=-I.

all: blu.kat blu.imp blu.bmd blush

blu.kat: kat.o
	$(CC) -o blu.kat kat.o

blu.imp: imp.o
	$(CC) -o blu.imp imp.o

blu.bmd: bmd.o
	$(CC) -o blu.bmd bmd.o

blu.o: blu.cpp
	$(GXX) -std=c++17 -c blu.cpp

scanpage.o: scanpage.cpp
	$(GXX) -std=c++17 -c scanpage.cpp

blush: blu.o scanpage.o
	$(GXX) -std=c++17 blu.o scanpage.o -o blush


