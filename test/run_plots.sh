#!/bin/bash

#First argument must be the txt file with the samples containing histograms
headdir=$(pwd)

if [ $# -eq 1 ] ; then
    read -p "separate plots(1), stack plots(2), multihists(3), analyze_cuts(4), all(5): " choice
else
    choice=$2
fi

if [[ choice -eq 1 || choice -eq 5 ]]; then
    #Make plots for every file separately
    if g++ -std=c++0x "src/plotterfunctions.cc" "src/testplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////"
        echo -e "//COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////\n"
        
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo "white line or comment found!"
            else
                echo "run_test.sh file: "$line
                ./a.out $line
                echo
            fi
        done < "$1"
    rm a.out
    else
        echo -e "\n//////////////////////"
        echo -e "//COMPILATION FAILED//"
        echo -e "//////////////////////\n"
    fi
fi
if [[ choice -eq 2 || choice -eq 5 ]]; then
    #run stack plots
    if g++ -std=c++0x "src/plotterfunctions.cc" "src/stackplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////"
        echo -e "//COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////\n"
    
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
        ./a.out ${samples[@]} ${legend[@]}
        echo
    rm a.out    
    else
        echo -e "\n//////////////////////"
        echo -e "//COMPILATION FAILED//"
        echo -e "//////////////////////\n"
    fi
fi
if [[ choice -eq 3 || choice -eq 5 ]]; then
    #run multi hist plots
    if g++ -std=c++0x "src/plotterfunctions.cc" "src/multihistplotterfunctions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////"
        echo -e "//COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////\n"
    
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
        ./a.out ${samples[@]} ${legend[@]}
        echo
    rm a.out    
    else
        echo -e "\n//////////////////////"
        echo -e "//COMPILATION FAILED//"
        echo -e "//////////////////////\n"
    fi
fi
if [[ choice -eq 4 || choice -eq 5 ]]; then
    #run analyze_cuts
    if g++ -std=c++0x "src/analyze_cuts.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////"
        echo -e "//COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////\n"
    
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
        ./a.out ${samples[@]} ${legend[@]}
        echo
    rm a.out    
    else
        echo -e "\n//////////////////////"
        echo -e "//COMPILATION FAILED//"
        echo -e "//////////////////////\n"
    fi

fi
