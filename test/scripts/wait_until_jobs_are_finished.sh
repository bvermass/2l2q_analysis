#!/bin/bash
if [ $# -eq 1 ] ; then
    tag="bvermass"
else
    tag=$2
fi

qstatoutput="qstatoutput.txt"
jobsrunning=true
njobs=0
nrunning=0
nwaiting=0
echo -e "\n"
while $jobsrunning; do
    while ! qstat -u bvermass > $qstatoutput; do
        echo -e "caught qstat error, retrying"
        sleep 2
    done
    nrunning=0
    nwaiting=0
    while IFS='' read -r line || [[ -n "$line" ]]; do
        if echo "$line" | grep -q "$tag"; then
            RorQ=$(echo ${line:86:1}) #86 is position of R or Q indicating if job is running
            if echo "$RorQ" | grep -q "Q"; then
                ((nwaiting+=1))
            else
                ((nrunning+=1))
            fi
        fi
    done < "$qstatoutput"
    rm $qstatoutput
    if [ $njobs -eq 0 ]; then
        ((njobs=$nrunning+$nwaiting))
    fi
    ((nfinished=$njobs-$nrunning-$nwaiting))
    echo -ne "\r\033[0Kwaiting = $nwaiting, running = $nrunning, finished = $nfinished"
    if [[ $nrunning -eq 0 && $nwaiting -eq 0 ]]; then
        echo -e "\njobs finished\n"
        jobsrunning=false
    else 
        sleep 60 #wait a minute before trying again
    fi
done
