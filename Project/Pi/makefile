.RECIPEPREFIX +=
CC = g++
CFLAGS = -Wall -lm -lrt -lwiringPi -lpthread

PROG = bin/*
OBJS = obj/*

default:
    mkdir -p bin obj
    $(CC) $(CFLAGS) -c src/Main.cpp -o obj/Main
    $(CC) $(CFLAGS) obj/Main -o bin/Main

run:
    sudo ./bin/Main

clean:
    rm $(PROG) $(OBJS)
