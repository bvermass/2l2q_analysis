#!/bin/bash

#script to submit all plot code. stack plots are split up in 10 different jobs since otherwise it's slow.
#full_analyzer plots are split up for every inputfile.
function submitjob {
    qsub $1 -l walltime=00:50:00 > scriptlog.txt 2>> scriptlog.txt
    
    while grep "Invalid credential" scriptlog.txt; do
        echo "Invalid credential caught, resubmitting"
        sleep 2 #sleep 2 seconds before attempting resubmission
        qsub $1 -l walltime=00:50:00 > scriptlog.txt 2>> scriptlog.txt
    done
    cat scriptlog.txt
    rm scriptlog.txt
    rm $job
}

headdir=$(pwd)

#stack plots:
partition=10            #currently only stack plots need to be divided into subjobs, the other plots go fast enough, at a later point it might be interesting to do this partition for all type of plots
partitionjobnumber=0
while [[ ! $partitionjobnumber -eq $partition ]]; do
    
    job=${headdir}"/test/LocalJob_stackplots_"$partitionjobnumber".sh"
    echo "#!/bin/bash" > $job 
    echo "cd "${headdir} >> $job
    echo "sh "${headdir}"/test/run_plots.sh "${headdir}"/test/sampleLists/plots_bkg.txt a_stack_"$partitionjobnumber".out 2 "$partition" "$partitionjobnumber >> $job
    cat $job
    submitjob $job

    let "partitionjobnumber++"
done

#multihist plots:
job=${headdir}"/test/LocalJob_multihistplots258e.sh"
echo "#!/bin/bash" > $job 
echo "cd "${headdir} >> $job
echo "sh "${headdir}"/test/run_plots.sh "${headdir}"/test/sampleLists/plots_HNL258e.txt a_multihist_e.out 3" >> $job
cat $job
submitjob $job

job=${headdir}"/test/LocalJob_multihistplots258mu.sh"
echo "#!/bin/bash" > $job 
echo "cd "${headdir} >> $job
echo "sh "${headdir}"/test/run_plots.sh "${headdir}"/test/sampleLists/plots_HNL258mu.txt a_multihist_mu.out 3" >> $job
cat $job
submitjob $job


#single plots:
jobtemplate=${headdir}"/test/LocalJob_singleplot_"
inputtemplate=${headdir}"/test/sampleLists/tmp/LocalJob_singleplot_"
exectemplate="a_singleplot_"
counter=0
while IFS='' read -r line || [[ -n "$line" ]]; do
    if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
        echo -e ""
    else
        job=$jobtemplate$counter".sh"
        input=$inputtemplate$counter".txt"
        executable=$exectemplate$counter".out"

        echo $line > $input

        echo "#!/bin/bash" > $job 
        echo "cd "${headdir} >> $job
        echo "sh "${headdir}"/test/run_plots.sh "$input" "$executable" 1" >> $job
        echo "rm "$input >> $job
        cat $job
        submitjob $job
        
        let "counter++"
    fi
done < ${headdir}"/test/sampleLists/plots_all.txt"
