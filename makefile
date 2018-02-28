all: polygon

polygon: polygon.o primlib.o
	gcc -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

polygon.o: polygon.c primlib.h

clean:
	-rm primlib.o polygon.o polygon
