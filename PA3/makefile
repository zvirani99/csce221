all: run-trees

BSTree.o: BSTree.cpp
	g++ -c BSTree.cpp -std=c++11

BSTree_main.o: BSTree_main.cpp
	g++ -c BSTree_main.cpp -std=c++11

run-trees: BSTree.o BSTree_main.o
	g++ BSTree.o BSTree_main.o -o run-trees

clean:
	rm *.o run-trees