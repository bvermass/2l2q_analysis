#!/bin/bash

g++ "src/plotterfunctions.cc" "src/testplotterfunctions.cc" `root-config --cflags --glibs`
echo "everything compiled"

./a.out
