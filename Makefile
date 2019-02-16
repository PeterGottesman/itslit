EXE=ItsLit
OBJS=src/main.c src/window.c src/game.c

CC=gcc
FLAGS=-lSDL2 -g -O2

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(EXE)

clean:
	rm -f $(EXE)
