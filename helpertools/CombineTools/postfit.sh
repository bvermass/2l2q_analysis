#!/bin/bash

#This script gets the postfit results for all search categories
workingdir=/user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/postfit/
#workingdir=/storage_mnt/storage/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/helpertools/CombineTools/

#initialize combine
#cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit
cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit
eval `scram runtime -sh`

mkdir -p $workingdir 
cd $workingdir

#perform fitdiagnostics to get postfit results
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _mm_M-3_V2-4e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-3_mu_run2_majorana/_mm_M-3_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _mm_M-5_V2-4e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-5_mu_run2_majorana/_mm_M-5_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _mm_M-6_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-6_mu_run2_majorana/_mm_M-6_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _mm_M-10_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-10_mu_run2_majorana/_mm_M-10_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _mm_M-12_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-12_mu_run2_majorana/_mm_M-12_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_mm_M-3_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-3_mu_run2_dirac/_OS_mm_M-3_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_mm_M-5_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-5_mu_run2_dirac/_OS_mm_M-5_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_mm_M-6_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-6_mu_run2_dirac/_OS_mm_M-6_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_mm_M-10_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-10_mu_run2_dirac/_OS_mm_M-10_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_mm_M-12_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-12_mu_run2_dirac/_OS_mm_M-12_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _ee_M-3_V2-4e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-3_e_run2_majorana/_ee_M-3_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _ee_M-5_V2-4e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-5_e_run2_majorana/_ee_M-5_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _ee_M-6_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-6_e_run2_majorana/_ee_M-6_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _ee_M-10_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-10_e_run2_majorana/_ee_M-10_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _ee_M-12_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-12_e_run2_majorana/_ee_M-12_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_ee_M-3_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-3_e_run2_dirac/_OS_ee_M-3_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_ee_M-5_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-5_e_run2_dirac/_OS_ee_M-5_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_ee_M-6_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-6_e_run2_dirac/_OS_ee_M-6_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_ee_M-10_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-10_e_run2_dirac/_OS_ee_M-10_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_ee_M-12_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-12_e_run2_dirac/_OS_ee_M-12_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _2l_M-3_V2-4e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-3_2l_run2_majorana/_2l_M-3_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _2l_M-5_V2-4e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-5_2l_run2_majorana/_2l_M-5_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _2l_M-6_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-6_2l_run2_majorana/_2l_M-6_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _2l_M-10_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-10_2l_run2_majorana/_2l_M-10_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _2l_M-12_V2-2e-06_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-12_2l_run2_majorana/_2l_M-12_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_2l_M-3_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-3_2l_run2_dirac/_OS_2l_M-3_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_2l_M-5_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-5_2l_run2_dirac/_OS_2l_M-5_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_2l_M-6_V2-4e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-6_2l_run2_dirac/_OS_2l_M-6_V2-4e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_2l_M-10_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-10_2l_run2_dirac/_OS_2l_M-10_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
combine --cminDefaultMinimizerStrategy 0 --ignoreCovWarning --saveShapes --saveWithUncertainties --name _OS_2l_M-12_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-12_2l_run2_dirac/_OS_2l_M-12_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt
#combine --cminDefaultMinimizerStrategy 0 --saveShapes --saveWithUncertainties --name _OS_2l_M-14_V2-2e-06_run2_dirac -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/M-14_2l_run2_dirac/_OS_2l_M-14_V2-2e-06_cutNTightmlSV_quadA_Shape_SR.txt

#python diffNuisances.py /user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/postfit/fitDiagnostics_OS_mm_M-6_V2-2e-06_run2_dirac.root

#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed_Tight/datacards/M-5_mu_run2_majorana/_mm_M-5_V2-6e-06_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-6e-06_cutTightmlSV_quadA_Shape_SR

#combine --saveShapes --name M-2_V2-5e-05_mu_run2_majorana -M FitDiagnostics /user/bvermass/public_html/2l2q_analysis/combine_observed_Tight/datacards/M-2_mu_run2_majorana/_mm_M-2_V2-5e-05_cutTightmlSV_quadA_Shape_SR.txt
