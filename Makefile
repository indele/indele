EXEC = LO
CC = g++

all : main Functions Light LightsOut Node QueueStack
	$(CC) $^ -o $(EXEC)
main : main.cpp
	$(CC) -c $^ -o $@
Functions : Functions.cpp
	$(CC) -c $^ -o $@
Light : Light.cpp
	$(CC) -c $^ -o $@
LightsOut : LightsOut.cpp
	$(CC) -c $^ -o $@
Node : Node.cpp
	$(CC) -c $^ -o $@
QueueStack : QueueStack.cpp
	$(CC) -c $^ -o $@

clean :
	rm -rf main Functions Light LightsOut Node QueueStack $(EXEC)
