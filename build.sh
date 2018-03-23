#!/bin/bash

g++ main.cpp -o main -O2 -std=gnu++17

[ "$1" == "-r" ] && cat /dev/stdin | ./main
exit $?
