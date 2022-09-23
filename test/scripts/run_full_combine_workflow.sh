#!/bin/bash

python test/scripts/submit_combine_datacards.py
./test/scripts/wait_until_jobs_are_finished.sh
python helpertools/CombineTools/runCombine_condor.py 10 majorana
./test/scripts/wait_until_jobs_are_finished.sh
cd helpertools/CombineTools
./runCombineOutputPrep.sh
./runAnalyzeCombineOutput.sh
