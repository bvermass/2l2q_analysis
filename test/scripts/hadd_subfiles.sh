#!/bin/bash

#loop over all directories and combine the root files into a dilep.root file, then copy that root file to pnfs
function hadd_all {
    if [[ -d "$1" ]]; then 
        if [ ! -z "$(ls -A $1)" ]; then
            echo -e "\n\nhadding:        "$1
            if hadd -f ${1%%subfiles*}hists_full_analyzer_${1#*subfiles/}.root $1/*_job_* ; then
                rm $1/*_job_*
            fi
            echo -e "\n"
        fi
    fi
}

function hadd_specific_backgrounds {
    echo -e "*********************"
    echo -e "**Hadd specific bkg**"
    echo -e "*********************"
    #ttbar
    echo -e "\nhadding ttbar files: \n"
    hadd -f ${1}hists_full_analyzer_Background_TTJets.root ${1}hists_full_analyzer_Background_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root ${1}hists_full_analyzer_Background_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root ${1}hists_full_analyzer_Background_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
    #DY
    echo -e "\nhadding DY files: \n"
    hadd -f ${1}hists_full_analyzer_Background_DYJets.root ${1}hists_full_analyzer_Background_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}hists_full_analyzer_Background_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1-v2.root
    #diboson 
    echo -e "\nhadding Diboson files: \n"
    hadd -f ${1}hists_full_analyzer_Background_Diboson.root ${1}hists_full_analyzer_Background_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1-v1.root ${1}hists_full_analyzer_Background_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1-v1.root ${1}hists_full_analyzer_Background_WWTo2L2Nu_13TeV-powheg.root ${1}hists_full_analyzer_Background_WWToLNuQQ_13TeV-powheg.root ${1}hists_full_analyzer_Background_ZZTo4L_13TeV_powheg_pythia8.root ${1}hists_full_analyzer_Background_WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}hists_full_analyzer_Background_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8.root ${1}hists_full_analyzer_Background_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.root
}

echo -e "\nHadd standard dilep.root files\n"
for D in /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/subfiles/*; do
    hadd_all $D 
done
hadd_specific_backgrounds /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/

echo -e "\nHadd special dilep_X.root files\n"
for IVFimp in /user/bvermass/public/2l2q_analysis/histograms/*; do
    for D in $IVFimp/full_analyzer/subfiles/*; do
        hadd_all $D
    done
    IVFimp_full_analyzer=$IVFimp/full_analyzer/
    hadd_specific_backgrounds $IVFimp_full_analyzer
done

