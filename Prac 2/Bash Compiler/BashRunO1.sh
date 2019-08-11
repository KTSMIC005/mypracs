#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partO1.txt
make run_threaded32 >> partO1.txt
make run_threaded32 >> partO1.txt
make run_threaded32 >> partO1.txt
make run_threaded32 >> partO1.txt
make run_threaded32 >> partO1.txt
echo "" >> partO1.txt