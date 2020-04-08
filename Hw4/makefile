proj4_driver.x: proj4_driver.o bet.o
	g++ -std=c++11 -o proj4_driver.x proj4_driver.o bet.o

proj4_driver.o: proj4_driver.cpp bet.h
	g++ -std=c++11 -c proj4_driver.cpp

bet.o: bet.cpp bet.h
	g++ -std=c++11 -c bet.cpp

clean:
	rm *.o proj4_driver.x
