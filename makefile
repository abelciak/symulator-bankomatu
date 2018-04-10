CC=gcc
CFLAGS=-ansi 

all: main.c funkcje.c biblioteka.h
	$(CC) $(CFLAGS) -o bankomat main.c funkcje.c -lm

main.o: main.c biblioteka.h
	$(CC) $(CFLAGS) -c main.c

funkcje.o: funkcje.c biblioteka.h
	$(CC) $(CFLAGS) -c funkcje.c

