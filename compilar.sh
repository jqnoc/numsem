#!/bin/bash

echo "Compilando..."
g++ -O3 -c -std=c++11 src/main.cpp build
g++ -std=c++11 -o bin/numsem main.o
chmod +x bin/numsem
mv main.o build/
echo "OK"
