#!/bin/bash

#First argument must be the txt file containing: SAMPLENAME max_entries partition
headdir=$(pwd)

while IFS='' read -r line || [[ -n "$line" ]]; do
    if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
        echo -e ""
    else
        counter=0
        for val in $line; do 
            if [ $counter -eq 0 ]; then
                inputfile=$val
                counter=1
            elif [ $counter -eq 1 ]; then
                max_entries=$val
                counter=2
            else 
                partition=$val
                counter=0
            fi
        done
         
        partitionjobnumber=0
        while [[ ! $partitionjobnumber -eq $partition ]]; do
            ./execMiniAnalyzer $inputfile $max_entries $partition $partitionjobnumber
            let "partitionjobnumber++"
        done
    fi
done < "$1"
