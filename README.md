# 2l2q analysis
Repository for analysis code for 2l2q HNL search. The framework consists of several parts that need to be run consecutively to arrive at final results.
An example 

# FullAnalyzer: run baseline selection

```
python test/submit_full_analyzer_condor.py test/sampleLists/full_run2.txt
python test/scripts/hadd_subfiles_condor.py
```

# MiniAnalyzer: run ABCD estimation

```
make -f test/make_mini_analyzer
python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/mini_run2.txt 1
python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/HNL.txt 4
python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/HNL_JECJER.txt 4
```

# make plots

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

# run code on m machines

# helpful scripts
Script that tracks submitted jobs and finishes when all jobs are done. Useful for commands that need to run consecutively:
```
./test/scripts/wait_until_jobs_are_finished.sh
```
