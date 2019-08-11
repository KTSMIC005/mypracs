#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partOs.txt
make run >> partOs.txt
echo "" >> partOs.txt

make run >> partOs.txt
echo "" >> partOs.txt

make run >> partOs.txt
echo "" >> partOs.txt

make run >> partOs.txt
echo "" >> partOs.txt

make run >> partOs.txt
echo "" >> partOs.txt

echo "" >> partOs.txt



make threaded

echo "fp16 threaded" >>partOs.txt
make run_threaded >> partOs.txt
echo "" >> partOs.txt

make run_threaded >> partOs.txt
echo "" >> partOs.txt

make run_threaded >> partOs.txt
echo "" >> partOs.txt

make run_threaded >> partOs.txt
echo "" >> partOs.txt

make run_threaded >> partOs.txt
echo "" >> partOs.txt

make run_threaded >> partOs.txt
echo "" >> partOs.txt

