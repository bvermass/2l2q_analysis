#!/bin/bash

if g++ -std=c++0x -o a.out "get_entries_in_trees.cc" `root-config --cflags --glibs`; then
    while IFS='' read -r line || [[ -n "$line" ]]; do
        if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then       #ignore empty or commented lines
            echo -e ""
        else
            for val in $line; do 
                ./a.out $val
                break                   # line contains more info than just the filename (which is first) therefore break before going to the second value
            done
        fi
    done < "$1"
    rm a.out
fi
