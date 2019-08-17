#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partO3.txt
make run_threaded32 >> partO3.txt
make run_threaded32 >> partO3.txt
make run_threaded32 >> partO3.txt
make run_threaded32 >> partO3.txt
make run_threaded32 >> partO3.txt
echo "" >> partO3.txt