CC=clang
GXX=clang++
CFLAGS=-I.

all: imp blu.bmd blush

blu.o: blu.cpp
	$(GXX) -std=c++17 -g -c blu.cpp
builddata.o: builddata.cpp
	$(GXX) -std=c++17 -g -c builddata.cpp
scanpage.o: scanpage.cpp
	$(GXX) -std=c++17 -g -c scanpage.cpp
blush: blu.o scanpage.o builddata.o
	$(GXX) -std=c++17 -g blu.o scanpage.o builddata.o -o blush

##//import program

imp.o: imp.cpp
	$(GXX) -std=c++17 -c imp.cpp
imp: imp.o
	$(GXX) -std=c++17 -g imp.o -o imp

##//markdown processor

blu.bmd: bmd.o
	$(CC) -o blu.bmd bmd.o
