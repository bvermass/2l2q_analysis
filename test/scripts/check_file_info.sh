#!/bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
    if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
        echo -e ""
    else
        counter=0
        for val in $line; do 
            ls -lh $val
            break
        done
    fi
done < "$1"
