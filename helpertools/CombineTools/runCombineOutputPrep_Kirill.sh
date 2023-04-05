#!/bin/bash

python CombineOutputPrep.py /user/kskovpen/analysis/HNL/CMSSW_10_2_13/src/Limits/limit/dirac_comb_Run2/ _mu_ _ Dirac _mm__run2_dirac_comb_
python CombineOutputPrep.py /user/kskovpen/analysis/HNL/CMSSW_10_2_13/src/Limits/limit/dirac_comb2l_Run2/ _mu_ _ Dirac _mm__run2_dirac_comb2l_
python CombineOutputPrep.py /user/kskovpen/analysis/HNL/CMSSW_10_2_13/src/Limits/limit/dirac_comb3l_Run2/ _mu_ _ Dirac _mm__run2_dirac_comb3l_

#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _mm_ SR_16 _mm__2016_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ee_ SR_16 _ee__2016_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ll_ SR_16 _2l__2016_ 
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _mm_ SR_17 _mm__2017_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ee_ SR_17 _ee__2017_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ll_ SR_17 _2l__2017_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _mm_ SR_18 _mm__2018_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ee_ SR_18 _ee__2018_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ll_ SR_18 _2l__2018_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _mm_ SR.As _mm__run2_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ee_ SR.As _ee__run2_
#python CombineOutputPrep.py /user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/ _ll_ SR.As _2l__run2_
