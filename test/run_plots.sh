#!/bin/bash

#Argument 1 must be the txt file with the samples containing histograms
#Argument 2 is the name of the executable a_xxx.out
#Argument 3 is the choice of which type of plots need to be made
headdir=$(pwd)

if [ $# -eq 1 ] ; then
    exec_name=a_plots.out
    read -p "separate plots(1), stack plots(2), multihists(3), analyze_cuts(4), all(5): " choice
elif [ $# -eq 2 ] ; then
    exec_name=$2
    read -p "separate plots(1), stack plots(2), multihists(3), analyze_cuts(4), all(5): " choice
else
    exec_name=$2
    choice=$3
fi

if [[ choice -eq 1 || choice -eq 5 ]]; then
    #Make plots for every file separately
    if g++ -std=c++0x -o $exec_name "src/plotterfunctions.cc" "src/testplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n///////////////////////////////////////////////"
        echo -e "//SINGLE PROCESS PLOTS COMPILATION SUCCESSFUL//"
        echo -e "///////////////////////////////////////////////\n"
        
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo "white line or comment found!"
            else
                ./$exec_name $line
                echo
            fi
        done < "$1"
    rm $exec_name
    else
        echo -e "\n//////////////////////"
        echo -e "//SINGLE PROCESS PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////\n"
    fi
fi
if [[ choice -eq 2 || choice -eq 5 ]]; then
    #run stack plots
    if g++ -std=c++0x -o $exec_name "src/plotterfunctions.cc" "src/stackplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////////////////"
        echo -e "//STACK PLOTS COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////////////////\n"
    
        #if no partition info is given to this script, then assume no partition is necessary.
        if [ $# -eq 5 ] ; then
            partition=$4
            partitionjobnumber=$5
        else
            partition=1
            partitionjobnumber=0
        fi

        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo "white line or comment found!"
            else
                counter=0
                for val in $line; do
                    if [ $counter -eq 0 ]; then
                        samples+=($val)
                        counter=1
                    else 
                        legend+=($val)
                        counter=0
                    fi
                done
            fi
        done < "$1"
        #IFS=$'\n' read -d '' -r -a samples < $1
        #IFS=$'\n' read -d '' -r -a legend < $exec_name
        ./$exec_name $partition $partitionjobnumber ${samples[@]} ${legend[@]} 
        echo
    rm $exec_name
    else
        echo -e "\n//////////////////////////////////"
        echo -e "//STACK PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////////////////\n"
    fi
fi
if [[ choice -eq 3 || choice -eq 5 ]]; then
    #run multi hist plots
    if g++ -std=c++0x -o $exec_name "src/plotterfunctions.cc" "src/multihistplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////////////////////"
        echo -e "//MULTIHIST PLOTS COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////////////////////\n"
    
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo "white line or comment found!"
            else
                counter=0
                for val in $line; do
                    if [ $counter -eq 0 ]; then
                        samples+=($val)
                        counter=1
                    else 
                        legend+=($val)
                        counter=0
                    fi
                done
            fi
        done < "$1"
        #IFS=$'\n' read -d '' -r -a samples < $1
        #IFS=$'\n' read -d '' -r -a legend < $2
        ./$exec_name ${samples[@]} ${legend[@]}
        echo
    rm $exec_name
    else
        echo -e "\n//////////////////////////////////////"
        echo -e "//MULTIHIST PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////////////////////\n"
    fi
fi
if [[ choice -eq 4 || choice -eq 5 ]]; then
    #run analyze_cuts
    if g++ -std=c++0x -o $exec_name "src/analyze_cuts.cc" `root-config --cflags --glibs`; then
        echo -e "\n///////////////////////////////////////"
        echo -e "//ANALYZE CUTS COMPILATION SUCCESSFUL//"
        echo -e "///////////////////////////////////////\n"
    
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo "white line or comment found!"
            else
                counter=0
                for val in $line; do
                    if [ $counter -eq 0 ]; then
                        samples+=($val)
                        counter=1
                    else 
                        legend+=($val)
                        counter=0
                    fi
                done
            fi
        done < "$1"
        #IFS=$'\n' read -d '' -r -a samples < $1
        #IFS=$'\n' read -d '' -r -a legend < $2
        ./$exec_name ${samples[@]} ${legend[@]}
        echo
    rm $exec_name
    else
        echo -e "\n///////////////////////////////////"
        echo -e "//ANALYZE CUTS COMPILATION FAILED//"
        echo -e "///////////////////////////////////\n"
    fi
fi
