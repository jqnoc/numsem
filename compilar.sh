#!/bin/bash

echo "Compilando..."
g++ -O3 -c -std=c++11 main.cpp
g++ -std=c++11 -o main.exe main.o
chmod +x main.exe
echo "OK"