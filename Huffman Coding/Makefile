root= $(shell git rev-parse --show-toplevel)

output: main.o HuffmanCoding.o HuffmansTree.o Input.o Output.o
	g++ -std=c++17 main.o HuffmanCoding.o HuffmansTree.o Input.o Output.o -o output

main.o: main.cpp HuffmanCoding.h Input.h Output.h
	g++ -c -std=c++17 main.cpp

HuffmanCoding.o: HuffmanCoding.h HuffmanCoding.cpp HuffmansTree.h Input.h Output.h
	g++ -c -std=c++17 HuffmanCoding.cpp

HuffmansTree.o: HuffmansTree.h HuffmansTree.cpp
	g++ -c -std=c++17 HuffmansTree.cpp

Input.o: Input.h Input.cpp
	g++ -c -std=c++17 Input.cpp

Output.o: Output.h Output.cpp
	g++ -c -std=c++17 Output.cpp

build_tests: tests.o HuffmanCoding.o
	g++ tests.o HuffmanCoding.o -o tests.exe

tests.o: tests.cpp
	g++ -I $(root) -c tests.cpp

run_tests:
	./tests.exe 
