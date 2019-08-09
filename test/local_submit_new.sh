#!/bin/bash

headdir=$(pwd)

if g++ -Wall -Wno-reorder -Wextra -I/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/python/2.7.14-omkpbe4/include/python2.7 -L/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/python/2.7.14-omkpbe4/lib -lpython2.7  -lboost_python -std=c++0x -o a_jobs.out ${headdir}"/helpertools/LSFReader/LSFReader.cc" ${headdir}"/src/helpertools/LorentzVector/LorentzVector.cc" ${headdir}"/helpertools/PFNEvaluation/PFNReader.cc" ${headdir}"/src/PFNTools.cc" ${headdir}"/src/HNLtagger.cc" ${headdir}"/src/jet_histograms.cc" ${headdir}"/src/gen_histograms.cc" ${headdir}"/src/signal_region.cc" ${headdir}"/src/HLT_eff.cc" ${headdir}"/src/jetID.cc" ${headdir}"/src/leptonID.cc" ${headdir}"/src/histo_functions.cc" ${headdir}"/src/full_analyzer_constructor.cc" ${headdir}"/src/full_analyzer.cc" ${headdir}"/src/print_table.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`; then
    echo -e "\n//////////////////////////"
    echo -e "//COMPILATION SUCCESSFUL//"
    echo -e "//////////////////////////\n"

    log="/user/bvermass/public/2l2q_analysis/log/submittedjobs.txt" #text file that will contain job numbers and their corresponding file
    >> $log
    dt=$(date '+%d/%m/%Y %H:%M:%S'); #also put date in submittedjobs.txt
    echo -e "\n$dt" >> $log
    
    tmp=${headdir}"/test/sampleLists/tmp/tmp.txt"
    inputtemplate=${headdir}"/test/sampleLists/tmp/LocalJob_"  #samples for 1 subjob will be put in tmp.txt, which will then be copied to $input which is this template with a job number attached
    jobnametemplate=${headdir}"/test/LocalJob_" #the name for the submitted jobs, numbered for clarity

    submittedjobs=0
    partitionjobnumber=0

    while IFS='' read -r line || [[ -n "$line" ]]; do
        if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
            echo -e ""
        else
            counter=0
            for val in $line; do 
                if [ $counter -eq 0 ]; then
                    inputfile=$val
                    counter=1
                elif [ $counter -eq 1 ]; then
                    cross_section=$val
                    counter=2
                elif [ $counter -eq 2 ]; then
                    max_entries=$val
                    counter=3
                elif [ $counter -eq 3 ]; then
                    partition=$val
                    counter=4
                else
                    n_samples=$val
                    counter=0
                fi
            done
   
            i_samples=0;
            for i in ${inputfile}* ; do
                echo $i" "$cross_section" "$max_entries" "$partition >> $tmp
                let "i_samples++"
    
                if [ $i_samples -eq $n_samples ]; then

                    job=$jobnametemplate$submittedjobs".sh"
                    input=$inputtemplate$submittedjobs".txt"
                    cp $tmp $input

                    echo "#!/bin/bash" > $job
                    echo "cd "${headdir} >> $job
                    echo "sh "${headdir}"/test/scripts/exec_analyzer.sh "$input" a_jobs.out"  >> $job
                    echo "rm "$input >> $job
                    
                    qsub $job -l walltime=00:30:00 > scriptlog.txt 2>> scriptlog.txt

                    while grep "Invalid credential" scriptlog.txt; do
                        echo "Invalid credential caught, resubmitting"
                        sleep 2 #sleep 2 seconds before attempting resubmission
                        qsub $job -l walltime=00:30:00 > scriptlog.txt 2>> scriptlog.txt
                    done

                    cat scriptlog.txt
                    rm scriptlog.txt
                    rm $job
                    > $tmp
                    let "submittedjobs++"
                    i_samples=0
                fi
            done
        fi
    done < "$1"
    rm $tmp
else
    echo -e "\n//////////////////////"
    echo -e "//COMPILATION FAILED//"
    echo -e "//////////////////////\n"
fi
