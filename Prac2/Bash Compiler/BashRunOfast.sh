#!bin/bash

set -x

make clean

make threaded32
echo "fp16 threaded32" >>partOfast.txt
make run_threaded32 >> partOfast.txt
make run_threaded32 >> partOfast.txt
make run_threaded32 >> partOfast.txt
make run_threaded32 >> partOfast.txt
make run_threaded32 >> partOfast.txt
echo "" >> partOfast.txt