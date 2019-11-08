CC=gcc
SRC=$(wildcard src/*.c)
INPUT=input.txt
EXEC=compress

make: 
	mkdir -p bin
	$(CC) $(SRC) -o bin/$(EXEC)

run:
	bin/$(EXEC) $(INPUT)

pq:
	mkdir -p bin
	$(CC) src/pqueue.c pqTest.c -o bin/pq


clean:
	rm -r bin