proj4.x: proj4_driver.o
	g++ -g -std=c++11 proj4_driver.o -o proj4.x

proj4_driver.o: proj4_driver.cpp bet.h
	g++ -g -c -std=c++11 proj4_driver.cpp

clean:
	rm -f proj4.x *.o
