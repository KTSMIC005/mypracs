#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partO2.txt
make run_threaded32 >> partO2.txt
make run_threaded32 >> partO2.txt
make run_threaded32 >> partO2.txt
make run_threaded32 >> partO2.txt
make run_threaded32 >> partO2.txt
echo "" >> partO2.txt