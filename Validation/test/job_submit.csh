#!/bin/csh

# submits a single job to lxbatch queue, should be run by job_looper.sh
# set CMSSW_PROJECT_SRC="CMSSW_7_2_0_pre4/src/Ntuple/Ntuplizer"
set CMSSW_PROJECT_SRC="testa/CMSSW_7_4_15/src/flashgg/Validation/test"
# set CFG_FILE="microAODreHLT_DY.py"
set CFG_FILE="makeTreePhotons.py "
set OUTPUT_FILE="SingleElectronGold_wideEE_egmTP_L1_15_lead_$2.root"
set TOP="$PWD"



    
cd "/afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC"
eval `scramv1 runtime -csh`
cd $TOP
#`cmsRun "/afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC/$CFG_FILE" inputFiles="$1"` 
#`python "/afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC/$CFG_FILE" inputFiles="$1"`
cmsRun /afs/cern.ch/user/m/mplaner/$CMSSW_PROJECT_SRC/$CFG_FILE inputFiles="$1"
#`python makeTreePhotons.py`  
#`python "$CFG_FILE"`
cp output_histos.root /afs/cern.ch/work/m/mplaner/singleEG_egmTP/$OUTPUT_FILE
