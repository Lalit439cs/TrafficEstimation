all:
	g++ traffic.cpp -o traffic.o -pthread -std=c++11 `pkg-config --cflags --libs opencv`
run:
	./traffic.o
clean:
	rm *.o
