#!/bin/bash
if [ $# -eq 0 ] ; then
    tag="bvermass "
else
    tag=$1
fi

qstatoutput="qstatoutput.txt"
jobsrunning=true
njobs=0
nrunning=0
nwaiting=0
echo -e "\n"
while $jobsrunning; do
    while ! condor_q -nobatch > $qstatoutput; do
        echo -e "caught qstat error, retrying"
        sleep 2
    done
    nrunning=0
    nwaiting=0
    while IFS='' read -r line || [[ -n "$line" ]]; do
        if echo "$line" | grep -q "$tag"; then
            RorI=$(echo ${line:53:1}) #86 is position of R or Q indicating if job is running
            if echo "$RorI" | grep -q "I"; then
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
