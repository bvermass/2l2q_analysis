#option = 1: run only full_analyzer part
#option = 2: run only mini_analyzer part
#option = 0: run both
option=$1

if [[ option -eq 1 || option -eq 0 ]]; then
    #./test/local_submit.sh test/sampleLists/full_run2.txt
    python test/submit_full_analyzer_condor.py test/sampleLists/full_run2.txt
    ./test/scripts/wait_until_jobs_are_finished.sh
    python test/scripts/hadd_subfiles_condor.py

    # make plots
    #./quickscript.sh
fi
if [[ option -eq 2 || option -eq 0 ]]; then
    make -f test/make_mini_analyzer
    python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/mini_run2.txt 1
    python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/HNL.txt 4
    python test/submit_mini_analyzer_condor.py test/sampleLists/mini_analyzer/HNL_JECJER.txt 4
    ./test/scripts/wait_until_jobs_are_finished.sh

    # make plots
    #./test/scripts/wait_until_jobs_are_finished.sh
    #./quickminiscript.sh

    # make limits
    ./test/scripts/run_full_combine_workflow.sh
    ./test/scripts/wait_until_jobs_are_finished.sh
fi
