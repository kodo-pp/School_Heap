#!/bin/bash

g++ main.cpp -o main -O2 -std=c++11

[ "$1" == "-r" ] && cat /dev/stdin | ./main
exit $?
