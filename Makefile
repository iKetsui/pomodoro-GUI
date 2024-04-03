CC=gcc
CFLAGS = -I/usr/local/include -I. -L/usr/local/lib -lraylib -lm -lpthread -ldl -lrt -lX11

all: run

run: getopt.c raylib_game.c 
		$(CC) raylib_game.c getopt.c -o POMODORO $(CFLAGS)