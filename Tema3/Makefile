# make si compileaza main.cpp
objects = main.o produs.o
target = main

start: $(objects)
	g++ $(objects) -o $(target)

main.o: main.cpp
produs.o: produs.cpp

clean:
	rm $(objects) $(target)
