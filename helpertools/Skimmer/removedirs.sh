#!/bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
    if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
        echo -e ""
    else
        rm -r $line
    fi
done < "$1"
