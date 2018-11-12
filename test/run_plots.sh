#!/bin/bash

#Argument 1 must be the txt file with the samples containing histograms
#Argument 2 is the name of the executable a_xxx.out
#Argument 3 is the choice of which type of plots need to be made
headdir=$(pwd)

if [ $# -eq 1 ] ; then
    2=a.out
    read -p "separate plots(1), stack plots(2), multihists(3), analyze_cuts(4), all(5): " choice
elif [ $# -eq 2 ] ; then
    read -p "separate plots(1), stack plots(2), multihists(3), analyze_cuts(4), all(5): " choice
else
    choice=$3
fi

if [[ choice -eq 1 || choice -eq 5 ]]; then
    #Make plots for every file separately
    if g++ -std=c++0x -o $2 "src/plotterfunctions.cc" "src/testplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n///////////////////////////////////////////////"
        echo -e "//SINGLE PROCESS PLOTS COMPILATION SUCCESSFUL//"
        echo -e "///////////////////////////////////////////////\n"
        
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo "white line or comment found!"
            else
                echo "run_test.sh file: "$line
                ./$2 $line
                echo
            fi
        done < "$1"
    rm $2
    else
        echo -e "\n//////////////////////"
        echo -e "//SINGLE PROCESS PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////\n"
    fi
fi
if [[ choice -eq 2 || choice -eq 5 ]]; then
    #run stack plots
    if g++ -std=c++0x -o $2 "src/plotterfunctions.cc" "src/stackplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////////////////"
        echo -e "//STACK PLOTS COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////////////////\n"
    
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
        ./$2 ${samples[@]} ${legend[@]}
        echo
    rm $2
    else
        echo -e "\n//////////////////////////////////"
        echo -e "//STACK PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////////////////\n"
    fi
fi
if [[ choice -eq 3 || choice -eq 5 ]]; then
    #run multi hist plots
    if g++ -std=c++0x -o $2 "src/plotterfunctions.cc" "src/multihistplotterfunctions.cc" `root-config --cflags --glibs`; then
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
        ./$2 ${samples[@]} ${legend[@]}
        echo
    rm $2
    else
        echo -e "\n//////////////////////////////////////"
        echo -e "//MULTIHIST PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////////////////////\n"
    fi
fi
if [[ choice -eq 4 || choice -eq 5 ]]; then
    #run analyze_cuts
    if g++ -std=c++0x -o $2 "src/analyze_cuts.cc" `root-config --cflags --glibs`; then
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
        ./$2 ${samples[@]} ${legend[@]}
        echo
    rm $2    
    else
        echo -e "\n///////////////////////////////////"
        echo -e "//ANALYZE CUTS COMPILATION FAILED//"
        echo -e "///////////////////////////////////\n"
    fi
fi
