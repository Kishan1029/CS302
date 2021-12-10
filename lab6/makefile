
CC = g++
CFLAGS = -g -Wall
BIN = Mazemake Mazesolve 

all: $(BIN)

Mazemake: Mazemake.cpp
	$(CC) $(CFLAGS) -o Mazemake Mazemake.cpp dset.cpp
Mazesolve: Mazesolve.cpp
	$(CC) $(CFLAGS) -o Mazesolve Mazesolve.cpp 
clean:
	@rm -f $(BIN)
