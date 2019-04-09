#!/bin/bash

#loop over all directories and combine the root files into a dilep.root file, then copy that root file to pnfs
function hadd_subfiles {
    if [[ -d "$1" ]]; then 
        if [ 0 -lt $(ls $1/*_job_* 2>/dev/null | wc -w) ]; then
            echo -e "\n\nhadding subfiles:        "$1
            if hadd -f ${1%%subfiles*}${2}${1#*subfiles/}.root $1/*_job_* ; then
                rm $1/*_job_*
            fi
            echo -e "\n"
        fi
    fi
}

function hadd_specific_backgrounds {
    #ttbar
    if [ 0 -lt $(ls ${1}${2}Background_TTJets_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding ttbar files: \n"
        hadd -f ${1}${2}Background_TTJets.root ${1}${2}Background_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root ${1}${2}Background_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root ${1}${2}Background_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
    fi
    #DY
    if [ 0 -lt $(ls ${1}${2}Background_DYJets_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding DY files: \n"
        hadd -f ${1}${2}Background_DYJets.root ${1}${2}Background_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8* ${1}${2}Background_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*
    fi
    #diboson 
    if [ 0 -lt $(ls ${1}${2}Background_WGToLNuG_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding Diboson files: \n"
        hadd -f ${1}${2}Background_Diboson.root ${1}${2}Background_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1-v1.root ${1}${2}Background_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext1-v1.root ${1}${2}Background_WWTo2L2Nu_13TeV-powheg.root ${1}${2}Background_WWToLNuQQ_13TeV-powheg.root ${1}${2}Background_ZZTo4L_13TeV_powheg_pythia8.root ${1}${2}Background_WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}${2}Background_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8.root ${1}${2}Background_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.root
    fi
}

function hadd_all_backgrounds {
    if [ 0 -lt $(ls ${1}${2}Background_* 2>/dev/null | wc -w) ]; then
        echo -e "Hadd all background"
        hadd -f ${1}${2}Background.root ${1}${2}Background_*
    fi
}

echo -e "\n----------------------------------------------"
echo -e "Looking for standard hists_full_analyzer files\n"
for D in /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/subfiles/*; do
    hadd_subfiles $D hists_full_analyzer_
done
hadd_specific_backgrounds /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/ hists_full_analyzer_

echo -e "\n--------------------------------------"
echo -e "Looking for special dilep_X.root files\n"
for IVFimp in /user/bvermass/public/2l2q_analysis/histograms/*; do
    for D in $IVFimp/full_analyzer/subfiles/*; do
        hadd_subfiles $D hists_full_analyzer_
    done
    IVFimp_full_analyzer=$IVFimp/full_analyzer/
    hadd_specific_backgrounds $IVFimp_full_analyzer hists_full_analyzer_
done

echo -e "\n---------------------------"
echo -e "Looking for HNLtagger files\n"
for D in /user/bvermass/public/2l2q_analysis/trees/HNLtagger/full_analyzer/subfiles/*; do
    hadd_subfiles $D HNLtagger_
done
hadd_all_backgrounds /user/bvermass/public/2l2q_analysis/trees/HNLtagger/full_analyzer/ HNLtagger_
