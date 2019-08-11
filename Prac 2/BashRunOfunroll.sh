#!bin/bash

set -x

make clean

make

echo "fp16 unthreaded" >> partfunroll.txt
make run >> partfunroll.txt
echo "" >> partfunroll.txt

make run >> partfunroll.txt
echo "" >> partfunroll.txt

make run >> partfunroll.txt
echo "" >> partfunroll.txt

make run >> partfunroll.txt
echo "" >> partfunroll.txt

make run >> partfunroll.txt
echo "" >> partfunroll.txt

echo "" >> partfunroll.txt



make threaded

echo "fp16 threaded" >>partfunroll.txt
make run_threaded >> partfunroll.txt
echo "" >> partfunroll.txt

make run_threaded >> partfunroll.txt
echo "" >> partfunroll.txt

make run_threaded >> partfunroll.txt
echo "" >> partfunroll.txt

make run_threaded >> partfunroll.txt
echo "" >> partfunroll.txt

make run_threaded >> partfunroll.txt
echo "" >> partfunroll.txt

make run_threaded >> partfunroll.txt
echo "" >> partfunroll.txt

