cd ../../
./test/local_submit.sh test/sampleLists/full_run2.txt
./test/scripts/wait_until_jobs_are_finished.sh

python test/scripts/hadd_subfiles.py
./quickscript.sh
./test/scripts/wait_until_jobs_are_finished.sh


make -f test/make_mini_analyzer
python test/submit_mini_analyzer.py test/sampleLists/mini_analyzer/mini_run2.txt 1
python test/submit_mini_analyzer.py test/sampleLists/mini_analyzer/HNL.txt 8
./test/scripts/wait_until_jobs_are_finished.sh
cd helpertools/HistogramMerger/
#python submit_HistogramMerger.py ../../test/sampleLists/RewVal/mini_analyzer/
python run_HistogramMerger.py ../../test/sampleLists/RewVal/mini_analyzer/POGTightID_unparametrized_LowAndHighMass/
cd ../../
./test/scripts/wait_until_jobs_are_finished.sh

./quickminiscript.sh
./test/scripts/run_full_combine_workflow.sh
./test/scripts/wait_until_jobs_are_finished.sh
