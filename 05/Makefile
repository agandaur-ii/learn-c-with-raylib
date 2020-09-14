# build a program from 2 files and one shared header
CC = gcc
CFLAGS = -g -Wall

LIBRARIES = `pkg-config --libs --cflags raylib`

program:
	$(CC) $(CFLAGS) snake.c $(LIBRARIES)
