#!/bin/bash

#This script submits jobs on the local tier2 cores
#It takes as input 
#   (1): txt file with samples to be run over
#   (2): number of files per job

headdir=$(pwd)
tmp=${headdir}"/test/sampleLists/tmp.txt"  #the samples for 1 job as determined by $2 are put in tmp.txt from $1
> $tmp
localjob=${headdir}"/test/LocalJob_" #the name for the submitted jobs, will be numbered
submittedjobs=0

maxfilesperjob=$2
filesinthisjob=0
while IFS='' read -r line || [[ -n "$line" ]]; do
    echo $line >> $tmp
    echo "submit.sh: "$line

    let "filesinthisjob++"
    if [ $filesinthisjob -eq $maxfilesperjob ]; then
        localjobsubmit=$localjob$submittedjobs".txt"
        echo "#!/bin/bash" > $localjobsubmit
        echo "."${headdir}"/test/run.sh "$tmp >> $localjobsubmit
        #while IFS='' read -r line || [[ -n "$linetwo" ]]; do
        #    echo $linetwo
        #done < $localjobsubmit

        qsub $localjobsubmit -l walltime=40:00:00 > scriptlog.txt 2>> scriptlog.txt
        
        while grep "Invalid credential" scriptlog.txt; do
            echo "Invalid credential caught, resubmitting"
            sleep 2 #sleep 2 seconds before attempting resubmission
            qsub $localjobsubmit -l walltime=40:00:00 > scriptlog.txt 2>>scriptlog.txt
        done
        cat scriptlog.txt
        rm scriptlog.txt
        > $tmp
        rm $localjobsubmit
        let "submittedjobs++"
        filesinthisjob=0
    fi
done < "$1"
rm $tmp
