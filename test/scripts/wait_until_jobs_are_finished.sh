#!/bin/bash
qstatoutput="qstatoutput.txt"
jobsrunning=true
njobs=0
nrunning=0
echo -e "\n"
while $jobsrunning; do
    while ! qstat -u bvermass > $qstatoutput; do
        echo -e "caught qstat error, retrying"
        sleep 2
    done
    if [ $njobs -eq 0 ]; then
        njobs=$(grep -c "LocalJob" "$qstatoutput")
    fi
    nrunning=$(grep -c "LocalJob" "$qstatoutput")
    echo -ne "\r\033[0Krunning/total = $nrunning/$njobs"
    if [ $nrunning -eq 0 ]; then
        echo -e "\njobs finished\n"
        jobsrunning=false
    else 
        sleep 60 #wait a minute before trying again
    fi
done
rm $qstatoutput
