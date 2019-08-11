#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partO0.txt
make run >> partO0.txt
echo "" >> partO0.txt

make run >> partO0.txt
echo "" >> partO0.txt

make run >> partO0.txt
echo "" >> partO0.txt

make run >> partO0.txt
echo "" >> partO0.txt

make run >> partO0.txt
echo "" >> partO0.txt

echo "" >> partO0.txt



make threaded

echo "fp16 threaded" >>partO0.txt
make run_threaded >> partO0.txt
echo "" >> partO0.txt

make run_threaded >> partO0.txt
echo "" >> partO0.txt

make run_threaded >> partO0.txt
echo "" >> partO0.txt

make run_threaded >> partO0.txt
echo "" >> partO0.txt

make run_threaded >> partO0.txt
echo "" >> partO0.txt

make run_threaded >> partO0.txt
echo "" >> partO0.txt

