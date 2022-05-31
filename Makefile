CC=clang
GXX=clang++
CFLAGS=-I.

all: cshg-imp cshg-md cshg

main.o: main.cpp
	$(GXX) -std=c++17 -g -c main.cpp
commandtostring.o: commandtostring.cpp
	$(GXX) -std=c++17 -g -c commandtostring.cpp
builddata.o: builddata.cpp
	$(GXX) -std=c++17 -g -c builddata.cpp
scanpage.o: scanpage.cpp
	$(GXX) -std=c++17 -g -c scanpage.cpp
cshg: main.o scanpage.o builddata.o commandtostring.o
	$(GXX) -std=c++17 -g main.o commandtostring.o scanpage.o builddata.o -o cshg

##//import program

imp.o: imp.cpp
	$(GXX) -std=c++17 -c imp.cpp
cshg-imp: imp.o
	$(GXX) -std=c++17 -g imp.o -o cshg-imp

##//markdown processor

cshg-md: bmd.o
	$(CC) -o cshg-md bmd.o
