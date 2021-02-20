all:
	g++ traffic.cpp -o traffic -pthread -std=c++11 `pkg-config --cflags --libs opencv`
run:
	.\traffic
