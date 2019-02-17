EXE=ItsLit
OBJS=$(wildcard src/*.c)

CC=gcc
FLAGS=-lSDL2 -lm -g -O2

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(EXE)

clean:
	rm -f $(EXE)
