#!/bin/bash

if g++ -std=c++0x -o b.out "get_hist_yields.cc" `root-config --cflags --glibs`; then
    ./b.out $1
    rm b.out
fi
