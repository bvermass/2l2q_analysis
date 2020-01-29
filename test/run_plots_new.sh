#!/bin/bash

#Argument 1 must be the txt file with the samples containing histograms
#Argument 2 is the name of the executable a_xxx.out
#Argument 3 is the choice of which type of plots need to be made
headdir=$(pwd)

if [ $# -eq 1 ] ; then
    exec_name=a_plots.out
    read -p "separate plots(1), multihists(2), stack plots(3), roc curves(4): " choice
elif [ $# -eq 2 ] ; then
    exec_name=$2
    read -p "separate plots(1), multihists(2), stack plots(3), roc curves(4): " choice
else
    exec_name=$2
    choice=$3
fi

if [[ choice -eq 1 ]]; then
    if g++ -std=c++0x -o $exec_name "plotting/singlehistplotter.cc" "plotting/tdrStyle.cc" "plotting/helper_plotter_functions.cc" `root-config --cflags --glibs`; then
        echo -e "\n///////////////////////////////////////////////"
        echo -e "//SINGLE PROCESS PLOTS COMPILATION SUCCESSFUL//"
        echo -e "///////////////////////////////////////////////\n"
        
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo ""
            else
                counter=0
                for val in $line; do
                    if [ $counter -eq 0 ]; then
                        sample=($val)
                        counter=1
                    elif [ $counter -eq 1 ]; then
                        legend=($val)
                        counter=0
                    fi
                done
                ./$exec_name $sample $legend
                echo
            fi
        done < "$1"
        rm $exec_name
    else
        echo -e "\n///////////////////////////////////////////"
        echo -e "//SINGLE PROCESS PLOTS COMPILATION FAILED//"
        echo -e "///////////////////////////////////////////\n"
    fi
fi
if [[ choice -eq 2 ]]; then
    if g++ -std=c++0x -o $exec_name "plotting/multihistplotter.cc" "plotting/tdrStyle.cc" "plotting/helper_plotter_functions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////////////////////"
        echo -e "//MULTIHIST PLOTS COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////////////////////\n"
        
        firstline=0
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo ""
            else
                counter=0
                for val in $line; do
                    if [ $firstline -eq 0 ]; then
                        subdirectory_name=($val)
                        firstline=1
                    elif [ $counter -eq 0 ]; then
                        samples+=($val)
                        counter=1
                    elif [ $counter -eq 1 ]; then
                        legends+=($val)
                        counter=0
                    fi
                done
            fi
        done < "$1"
        ./$exec_name $subdirectory_name ${samples[@]} ${legends[@]}
        echo
        rm $exec_name
    else
        echo -e "\n//////////////////////////////////////"
        echo -e "//MULTIHIST PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////////////////////\n"
    fi
fi
if [[ choice -eq 3 ]]; then
    if g++ -std=c++0x -o $exec_name "plotting/stackhistplotter.cc" "plotting/tdrStyle.cc" "plotting/helper_plotter_functions.cc" `root-config --cflags --glibs`; then
        echo -e "\n//////////////////////////////////////"
        echo -e "//STACK PLOTS COMPILATION SUCCESSFUL//"
        echo -e "//////////////////////////////////////\n"
        
        firstline=0
        while IFS='' read -r line || [[ -n "$line" ]]; do
            if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then #CHANGE THIS TO SKIP THIS PRINT MESSAGE AND ONLY EXECUTE COMMANDS
                echo ""
            else
                counter=0
                for val in $line; do
                    if [ $firstline -eq 0 ]; then
                        subdirectory_name=($val)
                        firstline=1
                    elif [ $counter -eq 0 ]; then
                        samples+=($val)
                        counter=1
                    elif [ $counter -eq 1 ]; then
                        legends+=($val)
                        counter=0
                    fi
                done
            fi
        done < "$1"
        ./$exec_name $subdirectory_name ${samples[@]} ${legends[@]}
        echo
        rm $exec_name
    else
        echo -e "\n//////////////////////////////////////"
        echo -e "//MULTIHIST PLOTS COMPILATION FAILED//"
        echo -e "//////////////////////////////////////\n"
    fi
fi