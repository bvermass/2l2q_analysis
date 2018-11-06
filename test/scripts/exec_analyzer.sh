#!/bin/bash
#executes
while IFS='' read -r line || [[ -n "$line" ]]; do
    if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
        echo -e "comment or whitespace"
    else
        #split sample name, cross section and max_entries that are currently on single line
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
                partitionjobnumber=$val
                counter=0
            fi
        done
        #root -l -b -q ${headdir}"src/full_analyzer.cc+" ${headdir}"test/mainroot.cc(\"$line\")" #maybe add an option to compile using this line, meaning Aclic(but why?)
    
        echo "inputfile      :  "$inputfile
        echo "cross section  :  "$cross_section
        echo "max_entries    :  "$max_entries
        echo "partition      :  "$partition
        echo "partitionjobnr :  "$partitionjobnumber

        ./$2 $inputfile $cross_section $max_entries $partition $partitionjobnumber
        echo 
    
    fi
done < "$1"
