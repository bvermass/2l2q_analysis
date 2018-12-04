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

#Now do specific hadding of different background files:
cd /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/
#ttbar
hadd -f hists_full_analyzer_Background_TTJets.root hists_full_analyzer_Background_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root hists_full_analyzer_Background_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root hists_full_analyzer_Background_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
#DY
hadd -f hists_full_analyzer_Background_DYJets.root hists_full_analyzer_Background_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root hists_full_analyzer_Background_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1-v2.root
#diboson - ADD OTHERS WHEN THEY ARE WORKING
hadd -f hists_full_analyzer_Background_Diboson.root hists_full_analyzer_Background_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1-v1.root hists_full_analyzer_Background_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1-v1.root

