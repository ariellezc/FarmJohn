.DEFAULT_GOAL := all
.PHONY = main game plant link clean cleanObjects 

CC = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lformw -lncursesw -lsqlite3

NAME = FarmJohn

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp 
	mv main.o exec/main.o

game:
	g++ $(CXXFLAGS) -c game.cpp
	mv game.o exec/game.o

plant:
	g++ $(CXXFLAGS) -c plant.cpp
	mv plant.o exec/plant.o

link:
	g++ -o exec/*.o $(LDFLAGS)

run:
	rm -f exec/FarmJohn
	mkdir -p exec
	$(CC) $(CXXFLAGS) main.cpp game.cpp plant.cpp display.cpp clock.cpp -o exec/$(NAME) $(LDFLAGS)
	exec/FarmJohn

cleanObjects:
	rm -f exec/*.o

clean:
	rm -f exec/*

test:
	rm -f exec/unitTests
	mkdir -p exec
	$(CC) $(CXXFLAGS) unitTests.cpp display.cpp plant.cpp game.cpp clock.cpp  -o exec/unitTests $(LDFLAGS)
	exec/unitTests

all: clean
	mkdir -p exec 
	$(CC) $(CXXFLAGS) main.cpp game.cpp plant.cpp display.cpp clock.cpp -o exec/$(NAME) $(LDFLAGS)
