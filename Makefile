# A simple makefile for CSE 100 P4

CC=g++
PROF = -pg
CXXFLAGS= -g $(PROF) -O2 -Wall -pedantic -std=c++11
LDFLAGS= -g $(PROF) -O2 -pthread -std=c++11

all: bogtest

bogtest:  boggleplayer.o boggleutil.o

boggleplayer.o: boggleutil.h 	baseboggleplayer.h 	boggleplayer.h

boggleutil.o: boggleutil.h

clean:
	rm -f bogtest  *.o core* gmon.out


