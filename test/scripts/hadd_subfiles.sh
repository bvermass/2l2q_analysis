#!/bin/bash

cd /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/subfiles/
#loop over all directories and combine the root files into a dilep.root file, then copy that root file to pnfs
function hadd_all {
    if [[ -d "$1" ]]; then 
        if [ -z "$(ls -A $1)" ]; then
            echo -e "\n\nalready hadded: "$1
        else
            echo -e "\n\nhadding:        "$1
            if hadd -f ../hists_full_analyzer_${1}.root $1/*_job_* ; then
                rm $1/*_job_*
            fi
        fi
    fi
}
for D in *; do
    hadd_all $D 
done
