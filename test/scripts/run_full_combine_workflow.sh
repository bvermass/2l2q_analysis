#!/bin/bash

python test/scripts/submit_combine_datacards.py
./test/scripts/wait_until_jobs_are_finished.sh
cd helpertools/CombineTools/
python runCombine.py 10 0
./../../test/scripts/wait_until_jobs_are_finished.sh
./runCombineOutputPrep.sh
./runAnalyzeCombineOutput.sh
