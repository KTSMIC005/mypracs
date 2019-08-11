#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
echo "" >> partO0.txt