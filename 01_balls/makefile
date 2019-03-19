main:	main.o
	g++ -lpthread -lncurses Ball.o main.o -o main

main.o: main.cpp
	g++ -c src/Ball.cpp main.cpp

clean:
	rm *.o