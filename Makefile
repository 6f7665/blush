CC=gcc
CFLAGS=-I.

all: blu.kat blu.imp blu.bmd

blu.kat: kat.o
	$(CC) -o blu.kat kat.o

blu.imp: imp.o
	$(CC) -o blu.imp imp.o

blu.bmd: bmd.o
	$(CC) -o blu.bmd bmd.o

