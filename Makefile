all: main

main: project.o
	g++ -o main project.o

project.o: project.cpp infixToPostfix.h StackADT.h
	g++ -std=c++17 -g -c project.cpp

run:
	./main

clean:
	rm -rf *.0 main
