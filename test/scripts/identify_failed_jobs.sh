#!/bin/bash
#this script goes through the error output files and summarizes what jobs succeeded and which ones failed

headdir="/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_9_4_0/src/2l2q_analysis/"
errorstmp="test/log/errors_tmp.txt"
errors="test/log/errors.txt"
cd $headdir

grep -F "segmentation violation" LocalJob_* > $errorstmp

echo "segmentation violations: " > $errors

while IFS='' read -r line || [[ -n "$line" ]]; do
    joberrname=$( echo $line | cut -d ':' -f 1 )
    joboutname=$( echo $joberrname | cut -d 'e' -f 1 )"o"$( echo $joberrname | cut -d 'e' -f 2 )
    filename=$( grep -F "inputfile" $joboutname | cut -d ':' -f 2 )

    echo $joboutname":"$filename >> $errors

done < "$errorstmp"
rm $errorstmp
