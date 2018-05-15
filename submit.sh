#!/bin/bash

#First argument must be the txt file containing the samples that have to be run
while IFS='' read -r line || [[ -n "$line" ]]; do
    root -l -b -q full_analyzer.cc "mainroot.cc(\"$line\")"
done < "$1"
