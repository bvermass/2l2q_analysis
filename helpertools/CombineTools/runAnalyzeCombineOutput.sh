#!/bin/bash
make -f makeAnalyzeOutput

./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_mm__2016_.txt mm_2016
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_ee__2016_.txt ee_2016
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_2l__2016_.txt 2l_2016
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_mm__2017_.txt mm_2017
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_ee__2017_.txt ee_2017
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_2l__2017_.txt 2l_2017
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_mm__2018_.txt mm_2018
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_ee__2018_.txt ee_2018
./analyzeoutput ~/public_html/2l2q_analysis/combine_POGTightID_unparametrized_LowAndHighMass/datacards/_2l__2018_.txt 2l_2018
