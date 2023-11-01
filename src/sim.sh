#!/bin/sh

g++ ./*.c -static-libstdc++ -std=c++11 -pthread -g -O0 -o ./sim
./sim ./../inputs/fibonacci.x

