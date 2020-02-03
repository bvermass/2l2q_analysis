#!/bin/bash
temp="jobs.txt"
if [[ -e $temp ]]; then
    rm $temp
fi
touch $temp
qstat -u bvermass > $temp

read -p "delete all jobs(1), delete queueing jobs(2): " choice
if [[ choice -eq 1 ]]; then
    echo "deleting all jobs"
elif [[ choice -eq 2 ]]; then
    echo "deleting queueing jobs"
fi

while IFS='' read -r line || [[ -n "$line" ]]; do
    if echo "$line" | grep -q "bvermass"; then
        jobnumber=$(echo ${line}| cut -d'.' -f 1)
        if [[ choice -eq 1 ]]; then
            qdel "$jobnumber"
        elif [[ choice -eq 2 ]]; then
            running=$(echo ${line:86:1}) #86 is position of R or Q indicating if job is running
            if echo "$running" | grep -q "Q"; then
                qdel "$jobnumber"
            fi
        fi
    fi
done < "$temp"
rm $temp
