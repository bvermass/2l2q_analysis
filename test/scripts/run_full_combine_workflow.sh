#!/bin/bash

./test/scripts/run_combine_datacards_all.sh
./test/scripts/wait_until_jobs_are_finished.sh
cd helpertools/CombineTools/
python runCombine.py 5
./../../test/scripts/wait_until_jobs_are_finished.sh
./runCombineOutputPrep.sh
./runAnalyzeCombineOutput.sh
