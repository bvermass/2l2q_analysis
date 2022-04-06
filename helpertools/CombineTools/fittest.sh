#!/bin/bash
cd /storage_mnt/storage/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/helpertools
#cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit
cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit
eval `scram runtime -sh`
cd /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana

#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR
#combine -M MultiDimFit -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR
#combine -M MultiDimFit --cminPreFit 1 -v 3 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR
#combine --rMin 0.00001 --cminPreFit 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-1e-04_cutTightmlSV_quadA_Shape_SR

#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR
#combine -M MultiDimFit -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR
#combine -M MultiDimFit --cminPreFit 1 -v 3 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR
#combine --cminPreFit 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR
#combine --rMin 0.00001 --cminPreFit 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-3e-04_cutTightmlSV_quadA_Shape_SR


#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR
#combine -M MultiDimFit --cminPreFit 1 -v 3 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR
#combine --cminPreFit 2 -v 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR
#combine --rMin 0.00001 --cminPreFit 2 -v 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-3_e_1718_majorana/_ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-3_V2-7e-04_cutTightmlSV_quadA_Shape_SR



#combine --rMin 0.00001 --cminPreFit 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-10_e_1718_majorana/_ee_M-10_V2-3e-05_cutTightmlSV_quadA_Shape_SR.txt -n _ee_M-10_V2-3e-05_cutTightmlSV_quadA_Shape_SR

#cd /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-14_mu_1718_majorana
#combine --rMin 0.00001 --cminPreFit 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-14_mu_1718_majorana/_mm_M-14_V2-5e-05_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-14_V2-5e-05_cutTightmlSV_quadA_Shape_SR

#cd /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-8_mu_1718_majorana
#combine --cminPreFit 2 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-8_mu_1718_majorana/_mm_M-8_V2-9e-05_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-8_V2-9e-05_cutTightmlSV_quadA_Shape_SR
#combine --rMin 0.001 --cminPreFit 2 -v 3 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-8_mu_1718_majorana/_mm_M-8_V2-7e-05_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-8_V2-7e-05_cutTightmlSV_quadA_Shape_SR

cd /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana
#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana/_mm_M-5_V2-1e-04_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-1e-04_cutTightmlSV_quadA_Shape_SR
combine -v 3 -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana/_mm_M-5_V2-3e-04_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-3e-04_cutTightmlSV_quadA_Shape_SR
#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana/_mm_M-5_V2-5e-04_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-5e-04_cutTightmlSV_quadA_Shape_SR
#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana/_mm_M-5_V2-7e-04_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-7e-04_cutTightmlSV_quadA_Shape_SR
#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana/_mm_M-5_V2-9e-04_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-9e-04_cutTightmlSV_quadA_Shape_SR
#combine -d /user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/M-5_mu_1718_majorana/_mm_M-5_V2-1e-03_cutTightmlSV_quadA_Shape_SR.txt -n _mm_M-5_V2-1e-03_cutTightmlSV_quadA_Shape_SR


cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/helpertools/CombineTools
