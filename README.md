# 2l2q analysis
Repository for analysis code for 2l2q HNL search. The framework consists of several parts that need to be run consecutively to arrive at final results.
An example of the full analysis chain can be found in the test/scripts/run_all.sh script that performs each step sequentially.
This framework is meant to be used on tier2. 

# FullAnalyzer: run baseline selection
This is the first step in the analysis chain. It runs on skimmed root files produced by the code in helpertools/Skimmer/. These input root files have a TTree with all relevant variables for the analysis.
This analyzer runs the baseline selection, calculates proper event weights per event, calculates the PFN predictions per event and produces several useful outputs. It produces root files containing histograms that can be plotted for a variety of event selections. It produces rootfiles with a TTree with maximally reduced variables that can be used as input by MiniAnalyzer to do the ABCD prediction and produce signal region and control region results. It produces rootfiles that can be used to train PFNs. There is a script to run a single rootfile locally and a script to submit all necessary files at once using condor.
```
make -f test/make_full_analyzer
python test/submit_full_analyzer_condor.py test/sampleLists/full_run2.txt
python test/scripts/hadd_subfiles_condor.py
```
Step one compiles the code, step two submits all samples that are listed in test/sampleLists/full_run2.txt to condor and step three combines files again, because a single sample can be divided over multiple jobs and the output needs to be combined again afterwards.
The contents of a sampleList are lines like the following:
```
/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/SingleMuon/Run2016B/dilep_final.root   1   -1   12
/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MiniAOD2016/dilep_final.root     61334.9     -1      2
```
First has to be the filename for the sample you want to run, then the first number is the cross section of the MC process (1 for data, also 1 for HNL because HNL samples retrieve their xsec from somewhere else). The second number specifies how many events of the sample to run, -1 means all events and is the default. The last number specifies into how many jobs you want to split the sample, so the first sample here will be split up over 12 condor jobs. test/sampleLists/full_run2.txt contains all relevant HNL, MC bkg and data samples for the analysis, with numbers for division per job adapted to arrive at roughy equal runtime for all files.
Lines in a sampleList can be commented out with a '#' and will then be ignored by the script.

The following allows you to run a sampleList locally, useful for testing, it works in the same way with sampleLists:
```
python test/run_analyzer.py test/sampleLists/test.txt
```

# MiniAnalyzer: run ABCD estimation
MiniAnalyzer runs on output root files with a TTree from FullAnalyzer. It applies the final selection for the signal region and for the ABCD control regions. It performs also the ABCD background estimation. It produces output root files with histograms that can be used for plotting and for calculating the limits. The samples are again contained in sampleLists. There are three relevant sampleLists in test/sampleLists/mini_analyzer/: mini_run2.txt contains the MC background and data samples. HNL.txt contains the HNL samples and HNL_JECJER.txt contains HNL samples with varied JEC and JER variations that are necessary to run for the JEC/JER systematic uncertainties.
```
make -f test/make_mini_analyzer
python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/mini_run2.txt 1
python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/HNL.txt 4
python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/HNL_JECJER.txt 4
```

# make plots
Plotting code is contained in the plotting/ directory. There are a few modes of plotting that can be used: single hist (plotting option 1) which produces plots for individual histograms, multihist which plots histograms with the same name from different samples in a sampleList together (plotting option 2) and stack plotting, which produces plots with MC bkg stacked, with or without data, and possible HNL samples, also based on a samplelist (plotting option 3). Since the sample root files usually contain tens of thousands of histograms for a variety of scenarios, it is important to work with the plotting/identifiers.txt (which is a file ignored by github thus might need to be created). Histograms will only be plotted if their name matches one of the identifiers in this file. This gives you a versatile control on deciding which plots to make. Each line has separate identifiers that will all be considered. If you want 2 or more identifiers to be matched with the same name, separate them by comma on the same line. test/run_plots.sh can be used for making plots locally, test/submit_plots.sh can be used to submit to condor when you need to produce a lot of plots.

```
./test/run_plots.sh <samplelist> <plotting option> <executablename.out>
./test/submit_plots.sh <samplelist> <plotting option> <executablename.out>
# examples:
./test/run_plots.sh test/sampleLists/mini_analyzer/plots_SingleLeptonRun2016.txt 1 lepton2016.out
./test/run_plots.sh test/sampleLists/data_and_stack/Run2_SingleLepton_vsBkg.txt 3 datavsbkg2lsubmit2.out
```

# calculate limits
All limit calculation code is contained in helpertools/CombineTools/. It works with rootfiles containing histograms, produced by MiniAnalyzer. An example of a full run through of the different steps can be found in test/scripts/run_full_combine_workflow.sh. The following commands have to be run consecutively.
```
python test/scripts/submit_combine_datacards.py
```
submit_combine_datacards.py creates datacards from histograms. It submits jobs through condor on tier2. It creates datacards for 2016 and for 1718 first. After these are finished, it merges them to create run2 datacards.

```
python helpertools/CombineTools/runCombine_condor.py 10 majorana
```
runCombine_condor.py runs combine on the created datacards. It also submits jobs through condor. The argument '10' refers to the number of datacards processed per job and can be changed. The argument 'majorana' means it will produce majorana limits. change it to 'dirac' to produce dirac limits.

```
./helpertools/CombineTools/runCombineOutputPrep.sh
```
runCombineOutputPrep.sh is a preparation script that gathers the produced limit files in some txt files for easy processing by the final limit plotting script.

```
./helpertools/CombineTools/runAnalyzeCombineOutput.sh
```
runAnalyzeCombineOutput.sh is the final limit plotting script. It produces signal strength plots and limit plots.

# create new skims

# helpful scripts
Script that tracks submitted jobs and finishes when all jobs are done. Useful for commands that need to run consecutively:
```
./test/scripts/wait_until_jobs_are_finished.sh
```
