#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partOg.txt
make run >> partOg.txt
echo "" >> partOg.txt

make run >> partOg.txt
echo "" >> partOg.txt

make run >> partOg.txt
echo "" >> partOg.txt

make run >> partOg.txt
echo "" >> partOg.txt

make run >> partOg.txt
echo "" >> partOg.txt

echo "" >> partOg.txt



make threaded

echo "fp16 threaded" >>partOg.txt
make run_threaded >> partOg.txt
echo "" >> partOg.txt

make run_threaded >> partOg.txt
echo "" >> partOg.txt

make run_threaded >> partOg.txt
echo "" >> partOg.txt

make run_threaded >> partOg.txt
echo "" >> partOg.txt

make run_threaded >> partOg.txt
echo "" >> partOg.txt

make run_threaded >> partOg.txt
echo "" >> partOg.txt

