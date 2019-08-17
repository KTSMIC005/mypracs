#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partOg.txt
make run_threaded32 >> partOg.txt
make run_threaded32 >> partOg.txt
make run_threaded32 >> partOg.txt
make run_threaded32 >> partOg.txt
make run_threaded32 >> partOg.txt
echo "" >> partOg.txt