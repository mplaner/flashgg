import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("HLTTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_dataRun2_Prompt_v1'

from flashgg.MicroAOD.flashggPreselectedDiPhotons_cfi import flashggPreselectedDiPhotons

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1 )

process.source = cms.Source("PoolSource",
                            inputCommands = cms.untracked.vstring( 'keep *',
                                                                   'drop *_patTrigger_*_*'
                                                                   ),
                            #fileNames = cms.untracked.vstring("file:myMicroAODOutputFile.root")
                            #fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIISpring15-Michael-BetaV7-25ns/Spring15michaelV7/GluGluHToGG_M-125_13TeV_powheg_pythia8/RunIISpring15-Michael-BetaV7-25ns-Spring15michaelV7-v0-RunIISpring15MiniAODv2-AsymptFlat10to50bx25Raw_74X_mcRun2_asymptotic_v2-v1/151216_120601/0000/myMicroAODOutputFile_2.root")
                            #fileNames = cms.untracked.vstring("root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIISpring15-Michael-BetaV72-25ns/Spring15michaelV72/GluGluHToGG_M-125_13TeV_powheg_pythia8/RunIISpring15-Michael-BetaV72-25ns-Spring15michaelV72-v0-RunIISpring15MiniAODv2-AsymptFlat10to50bx25Raw_74X_mcRun2_asymptotic_v2-v1/160104_204957/0000/myMicroAODOutputFile_11.root")
                            fileNames = cms.untracked.vstring("file:myMicroAODOutputFile.root"),
                            #secondaryFileNames= cms.untracked.vstring(        ),
                           # fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIISpring15-Michael-BetaV7-25ns/Spring15michaelV7HLTupdate/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15-Michael-BetaV7-25ns-Spring15michaelV7-v0-RunIISpring15DR74-AsymptFlat10to50bx25Raw_MCRUN2_74_V9-v1_HLTupdate/151217_085646/0000/myMicroAODOutputFile_35.root")
                            #fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/SingleElectron/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-Run2015D-05Oct2015-v1/151021_152553/0000/myMicroAODOutputFile_10.root")
                            #fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151021_151505/0000/myMicroAODOutputFile_10.root")
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/mplaner/CMSSW_7_4_6_patch2/src/flashgg/myMicroAODOutputFile.root")
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

process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.load("flashgg/MicroAOD/flashggPreselectedDiPhotons_cfi")
process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')

process.patTrigger.processName = cms.string('reHLT') #FLASHggMicroAOD
process.patTrigger.onlyStandAlone = cms.bool(False)
process.patTrigger.packTriggerPrescales = cms.bool(False)
process.patTrigger.triggerResults = cms.InputTag( "TriggerResults::reHLT" )
process.patTrigger.triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD::reHLT" )


process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')

#process.outPut = cms.OutputModule("PoolOutputModule",
#                                  fileName = cms.untracked.string("test2.root"),
#                                  outputCommands = cms.untracked.vstring('keep *')
#   )

process.p = cms.Path(process.patTrigger + process.flashggHLTPreselectedDiPhotons + process.flashggDiPhotonMVA + process.hltTest)
#process.outpath = cms.EndPath(process.outPut)



## import flashgg customization
from flashgg.MetaData.JobConfig import customize
customize.tfileOut = ("hltTest","outputFileName")
## set default options if needed
customize.setDefault("maxEvents",1)
customize.setDefault("targetLumi",10e+3)
## call the customization
customize(process)
