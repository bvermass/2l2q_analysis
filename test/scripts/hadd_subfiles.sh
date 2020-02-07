#!/bin/bash

#loop over all directories and combine the root files into a dilep.root file, then copy that root file to pnfs
function hadd_subfiles {
    if [[ -d "$1" ]]; then 
        if [ 0 -lt $(ls $1/*_job_* 2>/dev/null | wc -w) ]; then
            echo -e "\n\nhadding subfiles:        "$1
            if hadd -f ${1%%subfiles*}${2}${1#*subfiles/}.root $1/$2*_job_* ; then
                rm $1/$2*_job_*
            else
                exit 1
            fi
            echo -e "\n"
        fi
    fi
}

function hadd_specific_backgrounds {
    #ttbar
    echo -e "----------------------------------\nCollecting similar backgrounds"
    if [ 0 -lt $(ls ${1}${2}Background_TTJets_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding ttbar files: \n"
        hadd -f ${1}${2}Background_TTJets.root ${1}${2}Background_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root ${1}${2}Background_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root ${1}${2}Background_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
    fi
    #DY
    if [ 0 -lt $(ls ${1}${2}Background_DYJetsToLL_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding DY files: \n"
        hadd -f ${1}${2}Background_DYJets.root ${1}${2}Background_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}${2}Background_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root
    fi
    #diboson 
    if [ 0 -lt $(ls ${1}${2}Background_WGToLNuG_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding Diboson files: \n"
        hadd -f ${1}${2}Background_Diboson.root ${1}${2}Background_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}${2}Background_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}${2}Background_WWTo2L2Nu_13TeV-powheg.root ${1}${2}Background_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8.root ${1}${2}Background_ZZTo4L_13TeV-amcatnloFXFX-pythia8.root ${1}${2}Background_ZZTo2L2Q_13TeV_powheg_pythia8.root ${1}${2}Background_ZZTo2L2Nu_13TeV_powheg_pythia8.root ${1}${2}Background_WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root ${1}${2}Background_WZToLNu2Q_13TeV_powheg_pythia8.root ${1}${2}Background_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.root
    fi
    #QCD
    if [ 0 -lt $(ls ${1}${2}Background_QCD_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding QCD files: \n"
        hadd -f ${1}${2}Background_QCD.root ${1}${2}Background_QCD*
    fi
    #single top
    if [ 0 -lt $(ls ${1}${2}Background_ST_* 2>/dev/null | wc -w) ]; then
        echo -e "\nhadding Single top files: \n"
        hadd -f ${1}${2}Background_ST.root ${1}${2}Background_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8.root ${1}${2}Background_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1.root ${1}${2}Background_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1.root ${1}${2}Background_ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1.root ${1}${2}Background_ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1.root
    fi

    #Run2016 Data
    hadd -f ${1}${2}SingleMuon_Run2016.root ${1}${2}SingleMuon_Run2016B.root ${1}${2}SingleMuon_Run2016C.root ${1}${2}SingleMuon_Run2016D.root ${1}${2}SingleMuon_Run2016E.root ${1}${2}SingleMuon_Run2016F.root ${1}${2}SingleMuon_Run2016G.root ${1}${2}SingleMuon_Run2016H.root

    #all backgrounds together
    hadd -f ${1}${2}Background.root ${1}${2}Background_DYJets.root ${1}${2}Background_Diboson.root ${1}${2}Background_TTJets.root ${1}${2}Background_ST.root ${1}${2}Background_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root
    hadd -f ${1}${2}Background_Top.root ${1}${2}Background_ST.root ${1}${2}Background_TTJets.root
    hadd -f ${1}${2}Background_allWJets.root ${1}${2}Background_DYJets.root ${1}${2}Background_Diboson.root ${1}${2}Background_TTJets.root ${1}${2}Background_WJetsToLNu_*
}

#function hadd_all_backgrounds_and_signal_for_HNLtagger {
#    if [ 0 -lt $(ls ${1}${2}Background_* 2>/dev/null | wc -w) ]; then
#        echo -e "Hadd all background for HNL tagger"
#        hadd -f ${1}${2}Background.root ${1}${2}Background_*
#    fi
#
#    if [ 0 -lt $(ls ${1}${2}HeavyNeutrino_lljj_M-5_* 2>/dev/null | wc -w) ]; then
#        echo -e "Hadd 5 GeV signal e or mu for HNL tagger"
#        hadd -f ${1}${2}HeavyNeutrino_lljj_M-5_mu.root ${1}${2}HeavyNeutrino_lljj_M-5_*_mu_*
#        hadd -f ${1}${2}HeavyNeutrino_lljj_M-5_e.root ${1}${2}HeavyNeutrino_lljj_M-5_*_e_*
#    fi
#}

if [ $# -eq 0 ]; then
    read -p " 'all' or 'specific tag': " tag
elif [ $# -eq 1 ]; then
    tag=$1
fi
if [ $tag == "all" ]; then
    echo -e "\n----------------------------------------------"
    echo -e "hadd subfiles without tag\n"
    for D in /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/subfiles/*; do
        hadd_subfiles $D hists_full_analyzer_
    done
    hadd_specific_backgrounds /user/bvermass/public/2l2q_analysis/histograms/full_analyzer/ hists_full_analyzer_
    
    echo -e "\n--------------------------------------"
    echo -e "hadd subfiles for specific tags\n"
    for IVFimp in /user/bvermass/public/2l2q_analysis/histograms/*; do
        for D in $IVFimp/full_analyzer/subfiles/*; do
            hadd_subfiles $D hists_full_analyzer_
        done
        IVFimp_full_analyzer=$IVFimp/full_analyzer/
        hadd_specific_backgrounds $IVFimp_full_analyzer hists_full_analyzer_
    done
    echo 'successfully done!'
    
    #echo -e "\n---------------------------"
    #echo -e "Looking for HNLtagger files\n"
    #for D in /user/bvermass/public/2l2q_analysis/trees/HNLtagger/full_analyzer/subfiles/*; do
    #    hadd_subfiles $D HNLtagger_electron_
    #    hadd_subfiles $D HNLtagger_muon_
    #done
    #hadd_all_backgrounds_and_signal_for_HNLtagger /user/bvermass/public/2l2q_analysis/trees/HNLtagger/full_analyzer/ HNLtagger_electron_
    #hadd_all_backgrounds_and_signal_for_HNLtagger /user/bvermass/public/2l2q_analysis/trees/HNLtagger/full_analyzer/ HNLtagger_muon_
    #for D in /user/bvermass/public/2l2q_analysis/trees/HNLtagger/*; do
    #    for E in $D/full_analyzer/subfiles/*; do
    #        hadd_subfiles $E HNLtagger_electron_
    #        hadd_subfiles $E HNLtagger_muon_
    #    done
    #    hadd_all_backgrounds_and_signal_for_HNLtagger $D/full_analyzer/ HNLtagger_electron_
    #    hadd_all_backgrounds_and_signal_for_HNLtagger $D/full_analyzer/ HNLtagger_muon_
    #done
else
    echo -e "\n-------------------------------------"
    echo -e "hadd subfiles with specific tag "$tag": "
    
    tagdir=/user/bvermass/public/2l2q_analysis/histograms/${tag}
    for D in $tagdir/full_analyzer/subfiles/*; do
        hadd_subfiles $D hists_full_analyzer_
    done
    tagdir_full_analyzer=$tagdir/full_analyzer/
    hadd_specific_backgrounds $tagdir_full_analyzer hists_full_analyzer_
    
    HNLtreetagdir=/user/bvermass/public/2l2q_analysis/trees/HNLtagger/${tag}
    for D in $HNLtreetagdir/full_analyzer/subfiles/*; do
        hadd_subfiles $D HNLtagger_electron_
        hadd_subfiles $D HNLtagger_muon_
    done
    HNLBDTtreetagdir=/user/bvermass/public/2l2q_analysis/trees/HNLBDTtagger/${tag}
    for D in $HNLBDTtreetagdir/full_analyzer/subfiles/*; do
        hadd_subfiles $D HNLBDTtagger_electron_
        hadd_subfiles $D HNLBDTtagger_muon_
    done
    bkgestimatordir=/user/bvermass/public/2l2q_analysis/trees/BkgEstimator/${tag}
    for D in $bkgestimatordir/full_analyzer/subfiles/*; do
        hadd_subfiles $D BkgEstimator_
    done
    bkgestimatorfulldir=$bkgestimatordir/full_analyzer/
    hadd_specific_backgrounds $bkgestimatorfulldir BkgEstimator_
    echo 'successfully done!'

    #hadd_all_backgrounds_and_signal_for_HNLtagger $treetagdir/full_analyzer/ HNLtagger_electron_
    #hadd_all_backgrounds_and_signal_for_HNLtagger $treetagdir/full_analyzer/ HNLtagger_muon_
fi
