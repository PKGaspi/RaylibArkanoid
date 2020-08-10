CC=gcc
CFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11


run: compile exec

compile: game

game: main.c bar.o brick.o ball.o common.o
	$(CC) main.c $(CFLAGS) -o game bar.o brick.o ball.o common.o

bar: bar.c
	$(CC) -c bar.c

brick: brick.c
	$(CC) -c brick.c

ball: ball.c
	$(CC) -c ball.c

common: common.c
	$(CC) -c common.c

exec: game
	./game

clean:
	rm -f game *.o