#!/bin/bash

#This script submits jobs on the local tier2 cores
#It takes as input 
#   (1): txt file with samples to be run over
#   (2): number of files per job
#   TO BE EXTENDED: ADD CRAB SUBMISSION

headdir=$(pwd)
#execdir=${headdir}"/test/log/"

if g++ -o a_jobs.out ${headdir}"/src/jetID.cc" ${headdir}"/src/leptonID.cc" ${headdir}"/src/histo_functions.cc" ${headdir}"/src/full_analyzer_constructor.cc" ${headdir}"/src/full_analyzer_ee.cc" ${headdir}"/src/full_analyzer.cc" ${headdir}"/src/print_table.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`; then
    echo -e "\n//////////////////////////"
    echo -e "//COMPILATION SUCCESSFUL//"
    echo -e "//////////////////////////\n"

    #mv a.out $execdir 
    log=${headdir}"/test/log/submittedjobs.txt"
    >> $log
    dt=$(date '+%d/%m/%Y %H:%M:%S');
    echo "\n$dt" >> $log
    tmp=${headdir}"/test/sampleLists/tmp/tmp.txt"
    inputtemplate=${headdir}"/test/sampleLists/tmp/LocalJob_"  #samples for 1 subjob will be put in tmp.txt
    jobnametemplate=${headdir}"/test/LocalJob_" #the name for the submitted jobs, numbered for clarity

    submittedjobs=0
    maxfilesperjob=$2
    filesinthisjob=0

    while IFS='' read -r line || [[ -n "$line" ]]; do
        if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
            echo "white line or comment found"
        else
            echo $line >> $tmp
            echo "LocalJob_"$submittedjobs" "$line >> $log
            let "filesinthisjob++"
    
            #only once enough files are added to $tmp will the following be done
            if [ $filesinthisjob -eq $maxfilesperjob ]; then
    
                job=$jobnametemplate$submittedjobs".sh"
                input=$inputtemplate$submittedjobs".txt"
                cp $tmp $input

                #cp a.out $TMPDIR
                #cp $tmp $TMPDIR
                #cp test/scripts/exec_analyzer.sh $TMPDIR
                #cd $TMPDIR
                echo "#!/bin/bash" > $job
                echo "cd "${headdir} >> $job
                echo "sh "${headdir}"/test/scripts/exec_analyzer.sh "$input" a_jobs.out"  >> $job
                echo "rm "$input >> $job
                cat $job
                #if anything needs to be copied to or from scratch, it should happen here
                # - resulting root file with histograms should be copied from scratch to its correct location in public/2l2q_analysis/histograms
    
                qsub $job -l walltime=40:00:00 > scriptlog.txt 2>> scriptlog.txt
                
                while grep "Invalid credential" scriptlog.txt; do
                    echo "Invalid credential caught, resubmitting"
                    sleep 2 #sleep 2 seconds before attempting resubmission
                    qsub $job -l walltime=40:00:00 > scriptlog.txt 2>>scriptlog.txt
                done
                
                cat scriptlog.txt
                rm scriptlog.txt
                > $tmp
                rm $job
                let "submittedjobs++"
                filesinthisjob=0
            fi
        fi
    done < "$1"
    rm $tmp
    #rm a.out
else
    echo -e "\n//////////////////////"
    echo -e "//COMPILATION FAILED//"
    echo -e "//////////////////////\n"
fi
