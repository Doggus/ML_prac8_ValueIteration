compile: main.cpp grid.h
	g++ -o main main.cpp -std=c++11

run: main
	./main

clean: main
	rm main
