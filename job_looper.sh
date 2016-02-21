#!/bin/bash  
#used to submit large number of jobs to the batch queue via job_submit.csh.  1 job per input file.
#don't change count and nJob they are just for initialization of labels
let count=0
let nJob=1
#can use this line instead to run over particluar set of files without setting up filelist
#for line in `cat /afs/cern.ch/user/m/mplaner/flashgg/CMSSW_7_6_3/src/flashgg/FileList.txt`
for line in `cat /afs/cern.ch/user/m/mplaner/flashgg/CMSSW_7_6_3/src/flashgg/testFileList.txt`
#for line in `cat /afs/cern.ch/user/m/mplaner/testa/CMSSW_7_4_15/src/flashgg/MetaData/work/RunIISpring15-Michael-BetaV75-25ns/eosDYList.txt`
    do
    ((count++))
  #  echo "job_submit.csh $line $count"
    bsub -J "test$count" -q 8nh "job_submit.csh $line $count"
done
