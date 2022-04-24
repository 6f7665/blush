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
	$(GXX) -std=c++17 -g -c blu.cpp

builddata.o: builddata.cpp
	$(GXX) -std=c++17 -g -c builddata.cpp

scanpage.o: scanpage.cpp
	$(GXX) -std=c++17 -g -c scanpage.cpp

blush: blu.o scanpage.o builddata.o
	$(GXX) -std=c++17 -g blu.o scanpage.o builddata.o -o blush


