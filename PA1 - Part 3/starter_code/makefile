all: Stress_ball.o Jeans_test.o Stress_ball_test.o
	g++ -g -w -std=c++11 -c Jeans.cpp -o test

Stress_ball.o:
	g++ -g -w -std=c++11 -c Stress_ball.cpp

Jeans_test.o:
	g++ -g -w -std=c++11 -c Jeans_test.cpp

Stress_ball_test.o:
	g++ -g -w -std=c++11 -c Stress_ball_test.cpp

clean:
	rm -rf test

run:
	./test