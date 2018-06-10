#!/bin/bash

if g++ "src/plotterfunctions.cc" "src/testplotterfunctions.cc" `root-config --cflags --glibs`; then
    echo -e "COMPILATION SUCCESSFUL\n"
    while IFS='' read -r line || [[ -n "$line" ]]; do
        echo "run_test.sh file: "$line
        ./a.out $line
        echo
    done < "$1"
else
    echo -e "COMPILATION FAILED\n"
fi
