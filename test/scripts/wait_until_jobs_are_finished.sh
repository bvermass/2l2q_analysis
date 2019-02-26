#!/bin/bash
qstatoutput="qstatoutput.txt"
jobsrunning=true
while $jobsrunning; do
    while ! qstat -u bvermass > $qstatoutput; do
        echo -e "caught qstat error, retrying"
        sleep 2
    done
    if cat "$qstatoutput" | grep -q "bvermass"; then
        echo -e "jobs running"
        sleep 60 #wait a minute before trying again
    else 
        echo -e "jobs finished\n"
        jobsrunning=false
    fi
done
rm $qstatoutput
