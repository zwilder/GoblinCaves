CC = gcc

CFLAGS = -lncurses -lm -I./include/ -g

SOURCES = ./src/*.c

all: GoblinCaves 

GoblinCaves: 
	$(CC) $(SOURCES) $(CFLAGS) -o GoblinCaves 

run:
	./GoblinCaves

clean:
	rm GoblinCaves

fresh: clean GoblinCaves run
