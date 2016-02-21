#!/bin/csh

# submits a single job to lxbatch queue, should be run by job_looper.sh
# set CMSSW_PROJECT_SRC="CMSSW_7_2_0_pre4/src/Ntuple/Ntuplizer"
set CMSSW_PROJECT_SRC="flashgg/CMSSW_7_6_3/src/flashgg/MicroAOD/test"
# set CFG_FILE="microAODreHLT_DY.py"
set CFG_FILE="microAODreHLT.py"
set OUTPUT_FILE="microAODreHLT_DY_100_200_lead_$2.root"
set TOP="$PWD"

    
cd "/afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC"
eval `scramv1 runtime -csh`
cd $TOP
#`cmsRun "/afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC/$CFG_FILE" inputFiles="$1"` 
#`python "/afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC/$CFG_FILE" inputFiles="$1"`
cmsRun /afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC/$CFG_FILE inputFiles="$1"
#`python makeTreePhotons.py`  
#`python "$CFG_FILE"`
cp output_histos.root /afs/cern.ch/work/m/mplaner/reHLT/$OUTPUT_FILE
