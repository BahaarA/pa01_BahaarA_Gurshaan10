all: cards.o main.o
	g++ -o game cards.o main.o

test: test.o cards.o
	g++ -o test cards.o test.o

cards.o: cards.cpp cards.h
	g++ -c cards.cpp

main.o: main.cpp cards.h
	g++ -c main.cpp

test.o: test.cpp cards.h
	g++ -c test.cpp

clean:
	rm game test main.o cards.o test.o
