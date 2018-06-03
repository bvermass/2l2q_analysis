#!/bin/bash

g++ "src/plotterfunctions.cc" "src/testplotterfunctions.cc" `root-config --cflags --glibs` #WRITE SOMETHING TO CATCH WHEN COMPILATION TERMINATES
echo "everything compiled"

./a.out
