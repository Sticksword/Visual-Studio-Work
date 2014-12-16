#!/bin/bash
# this compiles and runs my main program
# I did not install packages, I just loaded my 2150 virtual box

clang++ -o ./a.out ./MainProgram.cpp ./Point.cpp
./a.out
