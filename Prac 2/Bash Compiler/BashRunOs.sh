#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partOs.txt
make run_threaded32 >> partOs.txt
make run_threaded32 >> partOs.txt
make run_threaded32 >> partOs.txt
make run_threaded32 >> partOs.txt
make run_threaded32 >> partOs.txt
echo "" >> partOs.txt