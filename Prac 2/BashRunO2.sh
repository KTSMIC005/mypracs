#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partO2.txt
make run >> partO2.txt
echo "" >> partO2.txt

make run >> partO2.txt
echo "" >> partO2.txt

make run >> partO2.txt
echo "" >> partO2.txt

make run >> partO2.txt
echo "" >> partO2.txt

make run >> partO2.txt
echo "" >> partO2.txt

echo "" >> partO2.txt



make threaded

echo "fp16 threaded" >>partO2.txt
make run_threaded >> partO2.txt
echo "" >> partO2.txt

make run_threaded >> partO2.txt
echo "" >> partO2.txt

make run_threaded >> partO2.txt
echo "" >> partO2.txt

make run_threaded >> partO2.txt
echo "" >> partO2.txt

make run_threaded >> partO2.txt
echo "" >> partO2.txt

make run_threaded >> partO2.txt
echo "" >> partO2.txt

