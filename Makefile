all: encoder decoder
#above declares that we have two executables

#Name: Sandesh Banskota; ID: sb3vf
CXX=clang++ $(CXXFLAGS)

CXXFLAGS= -Wall

OFILES1 = heap.o huffmanenc.o
OFILES2 = heap.o huffmandec.o

DEBUG= -g

.SUFFIXES: .o .cpp



encoder: $(OFILES1)
	$(CXX) $(DEBUG) -o encoder $(OFILES1)

decoder: $(OFILES2)
	$(CXX) $(DEBUG) -o decoder $(OFILES2)

heap.o: heap.cpp heap.h
huffmandec.o: huffmandec.cpp heap.cpp heap.h
huffmanenc.o: huffmanenc.cpp heap.cpp heap.h


clean:
	-rm -f *.o encoder decoder
