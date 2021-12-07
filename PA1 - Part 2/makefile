all: collection.o Stress_ball.o
	g++ -g -w -std=c++11 -c main.cpp -o test

collection.o:
	g++ -g -w -std=c++11 -c Collection.cpp

Stress_ball.o:
	g++ -g -w -std=c++11 -c Stress_ball.cpp

clean:
	rm -rf test

run:
	./test