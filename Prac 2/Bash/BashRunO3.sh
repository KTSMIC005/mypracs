#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partO3.txt
make run >> partO3.txt
echo "" >> partO3.txt

make run >> partO3.txt
echo "" >> partO3.txt

make run >> partO3.txt
echo "" >> partO3.txt

make run >> partO3.txt
echo "" >> partO3.txt

make run >> partO3.txt
echo "" >> partO3.txt

echo "" >> partO3.txt



make threaded

echo "fp16 threaded" >>partO3.txt
make run_threaded >> partO3.txt
echo "" >> partO3.txt

make run_threaded >> partO3.txt
echo "" >> partO3.txt

make run_threaded >> partO3.txt
echo "" >> partO3.txt

make run_threaded >> partO3.txt
echo "" >> partO3.txt

make run_threaded >> partO3.txt
echo "" >> partO3.txt

make run_threaded >> partO3.txt
echo "" >> partO3.txt

