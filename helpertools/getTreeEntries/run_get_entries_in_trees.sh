#!/bin/bash

if g++ -std=c++0x -o a.out "get_entries_in_trees.cc" `root-config --cflags --glibs`; then
    ./a.out
    rm a.out
fi
