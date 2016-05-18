import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("HLTTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_v13'

from flashgg.Taggers.flashggPreselectedDiPhotons_cfi import flashggPreselectedDiPhotons


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1 )

isSignal = True

if isSignal:
    inputFiles = cms.untracked.vstring(
        "root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/openHLThggV3/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLTvarsDumpV3microAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160313_101220/0000/testOpenHLT_Hgg_2.root",
        "root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/openHLThggV3/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLTvarsDumpV3microAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160313_101220/0000/testOpenHLT_Hgg_5.root",
        "root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/openHLThggV3/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLTvarsDumpV3microAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160313_101220/0000/testOpenHLT_Hgg_3.root",
        "root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/openHLThggV3/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLTvarsDumpV3microAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160313_101220/0000/testOpenHLT_Hgg_4.root"
        )
else:
    inputFiles = cms.untracked.vstring(
        #"root://xrootd.unl.edu//store/user/mplaner/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/test/160314_095628/0000/testoutput_28.root"
        "file:testoutput_28.root"
        )

process.source = cms.Source("PoolSource",
                            inputCommands = cms.untracked.vstring( 'keep *',
                                                                   'drop *_patTrigger_*_*'
                                                                   ),
                            
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/m/mplaner/microAOD/testOpenHLT_Hgg.root"),
                            fileNames =  inputFiles,
                            
                            #secondaryFileNames= cms.untracked.vstring(        ),

                            bypassVersionCheck = cms.untracked.bool(True)
                            )

process.hltTest = cms.EDAnalyzer('HLTEfficiency',
                                 outputFileName  = cms.string("outputAAA.root"),
                                 weightsFileName = cms.string("$CMSSW_BASE/src/flashgg/Validation/data/r9_eta_weights.root"),
                                 diphoMVACut     = cms.double(-0.6),                                
                                 diPhotonMVATag     = cms.InputTag("flashggDiPhotonMVA"),
                                 #diphotons       = cms.InputTag("flashggHLTPreselectedDiPhotons"),
                                 diphotons       = cms.InputTag("flashggDiPhotons"),
                                 electrons       = cms.InputTag("flashggElectrons"),
                                 #25ns tag and probe filters
                                 tagFilterName   = cms.vstring("hltEle30WP60Ele8TrackIsoFilter", "hltEle30WP60SC4TrackIsoFilter"),
                                 probeFilterName = cms.vstring("hltEle30WP60Ele8EtUnseededFilter", "hltEle30WP60SC4EtUnseededFilter"),
                                 
                                 #25ns tag filter for singleEG               
                                 tagSingleElectronFilterName   = cms.vstring("hltEle23WPLooseHcalIsoFilter"), #tag filter for photon signal MC
                                 #tagSingleElectronFilterName   = cms.vstring("hltEle23WPLooseGsfTrackIsoFilter"),
                                 useSingleEG   = cms.bool(True),
                                 
                                 #50ns tag and probe filters
                                 #tagFilterName   = cms.vstring("hltEle25WP60Ele8TrackIsoFilter", "hltEle25WP60SC4TrackIsoFilter"),
                                 #probeFilterName = cms.vstring("hltEle25WP60Ele8EtUnseededFilter", "hltEle25WP60SC4EtUnseededFilter"),
                                 filterName      = cms.vstring("hltEG30LIso60CaloId15b35eHE10R9Id50b80eEcalIsoLastFilter", "hltEG30LR9Id85b90eHE10R9Id50b80eR9IdLastFilter",
                                                               "hltEG18R9Id85b90eHE10R9Id50b80eR9UnseededLastFilter", "hltEG18Iso60CaloId15b35eHE10R9Id50b80eTrackIsoUnseededLastFilter"),
                                 l1Iso           = cms.InputTag("l1extraParticles:Isolated"),
                                 l1NonIso        = cms.InputTag("l1extraParticles:NonIsolated"),
                                 #bits            = cms.InputTag('TriggerResults::HLT'),
                                 bits            = cms.InputTag('TriggerResults::reHLT'),
                                 objects         = cms.InputTag('patTrigger'), #selectedPatTrigger
                                 prescales       = cms.InputTag('patTrigger'),
                                 )
#process.load("HLTrigger.HLTanalyzers.HLTAnalyser_cfi")                                                                                                                       
process.load("flashgg.Validation.hltOpen_cfi")                                                                                                                       

#process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.load("flashgg.Taggers.flashggUpdatedIdMVADiPhotons_cfi")
process.load("flashgg/Taggers/flashggPreselectedDiPhotons_cfi")
process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')

#process.analyzeThis = cms.Path(process.hltanalysis )

process.patTrigger.processName = cms.string('TEST') #FLASHggMicroAOD
process.patTrigger.onlyStandAlone = cms.bool(False)
process.patTrigger.packTriggerPrescales = cms.bool(False)
process.patTrigger.triggerResults = cms.InputTag( "TriggerResults::TEST" )
process.patTrigger.triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD::TEST" )


#process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')

#process.outPut = cms.OutputModule("PoolOutputModule",
#                                  fileName = cms.untracked.string("test2.root"),
#                                  outputCommands = cms.untracked.vstring('keep *')
#   )

#process.p = cms.Path(process.patTrigger + process.flashggPreselectedDiPhotons + process.flashggDiPhotonMVA + process.hltanalysis)
process.p = cms.Path(process.flashggUpdatedIdMVADiPhotons + process.flashggPreselectedDiPhotons + process.hltopenanalysis)
#process.p = cms.Path(process.patTrigger + process.flashggHLTPreselectedDiPhotons + process.flashggDiPhotonMVA + process.hltTest)
#process.outpath = cms.EndPath(process.outPut)



## import flashgg customization
from flashgg.MetaData.JobConfig import customize
customize.tfileOut = ("hltTest","outputFileName")
## set default options if needed
customize.setDefault("maxEvents",-1)
customize.setDefault("targetLumi",10e+3)
## call the customization
customize(process)
