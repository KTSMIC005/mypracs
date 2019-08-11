#!bin/bash

set -x

N = (1 2 3 4 5)

make clean

make

for n in {0..5}
do
    echo "${N[n]} fp16 unthreaded" >> part1.txt
    make run >> part1.txt
    echo "" >>part12.txt
done

make threaded

for n in {0..5}
do

    echo "${N[n]} fp16 threaded" >> part1.txt
    make run_threaded >> part1.txt
    echo "" >>part12.txt
done    
