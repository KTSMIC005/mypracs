.RECIPEPREFIX +=
CC = arm-linux-gnueabihf-g++
CFLAGS = -lm -lrt -O0 -funroll-loops
INCLUDE = -ITools

PROG = bin/*
OBJS = obj/*


default:
    $(CC) $(INCLUDE) $(CFLAGS) -c src/Prac2.c -o obj/Prac2.o
    $(CC) $(INCLUDE) $(CFLAGS) -c Tools/Timer.cpp -o obj/Timer.o
    $(CC) -o bin/Prac2 obj/Prac2.o obj/Timer.o $(CFLAGS)

threaded2:
    $(CC) $(INCLUDE) $(CFLAGS) -c src/Prac2_threaded2.c -o obj/Prac2_threaded2.o
    $(CC) $(INCLUDE) $(CFLAGS) -c Tools/Timer.cpp -o obj/Timer.o
    $(CC) -o bin/Prac2_threaded2 obj/Prac2_threaded2.o obj/Timer.o $(CFLAGS) -pthread

threaded4:
    $(CC) $(INCLUDE) $(CFLAGS) -c src/Prac2_threaded4.c -o obj/Prac2_threaded4.o
    $(CC) $(INCLUDE) $(CFLAGS) -c Tools/Timer.cpp -o obj/Timer.o
    $(CC) -o bin/Prac2_threaded4 obj/Prac2_threaded4.o obj/Timer.o $(CFLAGS) -pthread

threaded8:
    $(CC) $(INCLUDE) $(CFLAGS) -c src/Prac2_threaded8.c -o obj/Prac2_threaded8.o
    $(CC) $(INCLUDE) $(CFLAGS) -c Tools/Timer.cpp -o obj/Timer.o
    $(CC) -o bin/Prac2_threaded8 obj/Prac2_threaded8.o obj/Timer.o $(CFLAGS) -pthread

threaded16:
    $(CC) $(INCLUDE) $(CFLAGS) -c src/Prac2_threaded16.c -o obj/Prac2_threaded16.o
    $(CC) $(INCLUDE) $(CFLAGS) -c Tools/Timer.cpp -o obj/Timer.o
    $(CC) -o bin/Prac2_threaded16 obj/Prac2_threaded16.o obj/Timer.o $(CFLAGS) -pthread

threaded32:
    $(CC) $(INCLUDE) $(CFLAGS) -c src/Prac2_threaded32.c -o obj/Prac2_threaded32.o
    $(CC) $(INCLUDE) $(CFLAGS) -c Tools/Timer.cpp -o obj/Timer.o
    $(CC) -o bin/Prac2_threaded32 obj/Prac2_threaded32.o obj/Timer.o $(CFLAGS) -pthread

run:
    bin/Prac2

run_threaded2:
    bin/Prac2_threaded2

run_threaded4:
    bin/Prac2_threaded4

run_threaded8:
    bin/Prac2_threaded8

run_threaded16:
    bin/Prac2_threaded16

run_threaded32:
    bin/Prac2_threaded32

clean: 
    rm -rf $(PROG) $(OBJS) 
