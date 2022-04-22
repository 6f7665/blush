CC=clang
GXX=clang++
CFLAGS=-I.

all: blu.kat blu.imp blu.bmd main

blu.kat: kat.o
	$(CC) -o blu.kat kat.o

blu.imp: imp.o
	$(CC) -o blu.imp imp.o

blu.bmd: bmd.o
	$(CC) -o blu.bmd bmd.o

main: blush
	$(GXX) -std=c++17 blu.cpp -o blush
