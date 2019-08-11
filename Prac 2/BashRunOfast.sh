#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partOfast.txt
make run >> partOfast.txt
echo "" >> partOfast.txt

make run >> partOfast.txt
echo "" >> partOfast.txt

make run >> partOfast.txt
echo "" >> partOfast.txt

make run >> partOfast.txt
echo "" >> partOfast.txt

make run >> partOfast.txt
echo "" >> partOfast.txt

echo "" >> partOfast.txt



make threaded

echo "fp16 threaded" >>partOfast.txt
make run_threaded >> partOfast.txt
echo "" >> partOfast.txt

make run_threaded >> partOfast.txt
echo "" >> partOfast.txt

make run_threaded >> partOfast.txt
echo "" >> partOfast.txt

make run_threaded >> partOfast.txt
echo "" >> partOfast.txt

make run_threaded >> partOfast.txt
echo "" >> partOfast.txt

make run_threaded >> partOfast.txt
echo "" >> partOfast.txt

