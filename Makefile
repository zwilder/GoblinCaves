CC = gcc

CFLAGS = -lncurses -lm -I./include/

OFLAGS = -O2

GFLAGS = -g -Wall

SOURCES = ./src/*.c

all: GoblinCaves 

GoblinCaves: ctags
	$(CC) $(SOURCES) $(CFLAGS) $(GFLAGS) -o GoblinCaves 

run:
	./GoblinCaves

clean:
	rm GoblinCaves

fresh: clean GoblinCaves run

optimized:
	$(CC) $(SOURCES) $(CFLAGS) $(OFLAGS) -o GoblinCaves

ctags: 
	ctags -R *
