output: ch16-binaryNodeTree-driver.o
	g++ ch16-binaryNodeTree-driver.o -o run

ch16-binaryNodeTree-driver.o: ch16-binaryNodeTree-driver.cpp
	g++ -c -std=c++14 ch16-binaryNodeTree-driver.cpp

clean:
	rm *.o run
