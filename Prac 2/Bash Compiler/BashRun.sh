#!bin/bash

set -x

make clean

make threaded2

echo "fp16 threaded2" >>partO0.txt
make run_threaded2 >> partO0.txt
make run_threaded2 >> partO0.txt
make run_threaded2 >> partO0.txt
make run_threaded2 >> partO0.txt
make run_threaded2 >> partO0.txt
echo "" >> partO0.txt

make threaded4

echo "fp16 threaded4" >>partO0.txt
make run_threaded4 >> partO0.txt
make run_threaded4 >> partO0.txt
make run_threaded4 >> partO0.txt
make run_threaded4 >> partO0.txt
make run_threaded4 >> partO0.txt
echo "" >> partO0.txt

make threaded8
echo "fp16 threaded8" >>partO0.txt
make run_threaded8 >> partO0.txt
make run_threaded8 >> partO0.txt
make run_threaded8 >> partO0.txt
make run_threaded8 >> partO0.txt
make run_threaded8 >> partO0.txt
echo "" >> partO0.txt

make threaded16
echo "fp16 threaded16" >>partO0.txt
make run_threaded16 >> partO0.txt
make run_threaded16 >> partO0.txt
make run_threaded16 >> partO0.txt
make run_threaded16 >> partO0.txt
make run_threaded16 >> partO0.txt
echo "" >> partO0.txt

make threaded32
echo "fp16 threaded32" >>partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
make run_threaded32 >> partO0.txt
echo "" >> partO0.txt