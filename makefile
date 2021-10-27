CC=g++

malcolm: poly.cpp malcolmPolyTest.cpp
	$(CC) poly.cpp malcolmPolyTest.cpp -g -o malcolm

official: poly.cpp intr_poly_tester.cpp #polygif.cpp
	$(CC) poly.cpp intr_poly_tester.cpp -g -o ./Official

