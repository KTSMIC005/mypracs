#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partO1.txt
make run >> partO1.txt
echo "" >> partO1.txt

make run >> partO1.txt
echo "" >> partO1.txt

make run >> partO1.txt
echo "" >> partO1.txt

make run >> partO1.txt
echo "" >> partO1.txt

make run >> partO1.txt
echo "" >> partO1.txt

echo "" >> partO1.txt



make threaded

echo "fp16 threaded" >>partO1.txt
make run_threaded >> partO1.txt
echo "" >> partO1.txt

make run_threaded >> partO1.txt
echo "" >> partO1.txt

make run_threaded >> partO1.txt
echo "" >> partO1.txt

make run_threaded >> partO1.txt
echo "" >> partO1.txt

make run_threaded >> partO1.txt
echo "" >> partO1.txt

make run_threaded >> partO1.txt
echo "" >> partO1.txt

