CC=g++

malcolm: poly.cpp malcolmPolyTest.cpp
	$(CC) poly.cpp malcolmPolyTest.cpp -g -o malcolm

official: poly.cpp
	$(CC) poly.cpp -g -o ./Official

