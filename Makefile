all:
	g++ -std=c++11 -Wall -o main.exe main.cpp calculator.cpp

clean:
	rm -f main.exe *.o
