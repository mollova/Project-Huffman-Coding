output: main.o PairType.o HufmansTree.o
	g++ -std=c++14 main.o PairType.o HufmansTree.o -o output

main.o: main.cpp PairType.h HufmansTree.h
	g++ -c -std=c++14 main.cpp

PairType.o: PairType.h PairType.cpp
	g++ -c -std=c++14 PairType.cpp

HufmansTree.o: HufmansTree.h HufmansTree.cpp
	g++ -c -std=c++14 HufmansTree.cpp
