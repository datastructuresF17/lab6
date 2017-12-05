output: sortedtree.o
	g++ sortedtree.o -o run

sortedtree.o: sortedtree.cpp
	g++ -c -std=c++14 sortedtree.cpp

clean:
	rm *.o run
