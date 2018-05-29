#!/bin/bash

echo "Compilando..."
g++ -O3 -c -std=c++11 src/main.cpp src/NumericalSemigroup.cpp
g++ -std=c++11 -o numsem main.o NumericalSemigroup.o
chmod +x numsem
mv main.o NumericalSemigroup.o build/
echo "OK"
