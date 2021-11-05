CC = gcc

CFLAGS = -w

LFLAGS = -lSDL2

all: helloSDL

helloSDL: helloSDL.c
	$(CC) helloSDL.c $(CFLAGS) $(LFLAGS) -o helloSDL
