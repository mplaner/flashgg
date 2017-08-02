import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
import FWCore.ParameterSet.VarParsing as VarParsing

options = VarParsing.VarParsing ('analysis')
options.parseArguments()



process = cms.Process("HLTTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '92X_dataRun2_Prompt_v4'

from flashgg.Taggers.flashggPreselectedDiPhotons_cfi import flashggPreselectedDiPhotons

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 200 )

import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('uAODfull.txt') 
#readFiles = cms.untracked.vstring( *mylist)

process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring("file:myMicroAODOutputFile.root")

                            fileNames = cms.untracked.vstring(#"file:testout19.root"
        #                                  "file:testout20.root"
#        options.inputFiles
        *mylist
        )
                            )

#process.hltTest = cms.EDAnalyzer('HLTEfficiency',
process.hltTest = cms.EDAnalyzer('HLTtest',
                                 outputFileName  = cms.string("outputAAA.root"),
                                 weightsFileName = cms.string(""),
                                 diphoMVACut     = cms.double(-0.6),                                
                                 diPhotonMVATag     = cms.InputTag("flashggDiPhotonMVA"),
                                 diphotons       = cms.InputTag("flashggPreselectedDiPhotons"),
                                 #diphotons       = cms.InputTag("flashggDiPhotons"),
                                 electrons       = cms.InputTag("flashggElectrons"),
                                 #25ns tag and probe filters
                                 tagFilterName   = cms.vstring("hltEle30WP60Ele8TrackIsoFilter", "hltEle30WP60SC4TrackIsoFilter"),
                                 probeFilterName = cms.vstring("hltEle30WP60Ele8EtUnseededFilter", "hltEle30WP60SC4EtUnseededFilter"),
                                 #tagFilterName = cms.vstring("hltEle27WPTightGsfTrackIsoFilter")
                                 #probeFilterName = cms.vstring()
                                 
                                 #25ns tag filter for singleEG              
                                 tagSingleElectronFilterName   = cms.vstring("hltEle27WPTightGsfTrackIsoFilter"),
                                 #tagSingleElectronFilterName   = cms.vstring("hltEle27WPTightGsfTrackIsoFilter"),
                                 #tagSingleElectronFilterName   = cms.vstring("hltEle35noerWPTightGsfTrackIsoFilter"),
                                 useSingleEG   = cms.bool(True),
                                 
                                 #2017ns tag and probe filters   hltDiEG22R9Id50b80eR9IdUnseededFilter
                                 #filterName      = cms.vstring("hltEG30LRId85ORIso60CaloId15b35eANDHE12R9Id50b80eLegCombLastFilter", "hltEG30LRId85ORIso60CaloId15b35eANDHE12R9Id50b80eLegCombLastFilter",
                                  #                             "hltDiEG22R9Id85b90eORIso60CaloId15b35eANDHE12R9Id50b80eMass90CombMassLastFilter", "hltDiEG22R9Id85b90eORIso60CaloId15b35eANDHE12R9Id50b80eMass90CombMassLastFilter"),
                                 filterName      = cms.vstring("hltEG30LIso60CaloId15b35eHE12R9Id50b80eEcalIsoLastFilter", "hltEG30LR9Id85b90eHE12R9Id50b80eR9IdLastFilter",
                                                               "hltEG22R9Id85b90eHE12R9Id50b80eR9UnseededLastFilter", "hltEG22Iso60CaloId15b35eHE12R9Id50b80eTrackIsoUnseededLastFilter"),
                                 l1              = cms.InputTag("caloStage2Digis:EGamma"),
                                 bits            = cms.InputTag('TriggerResults::HLT'),
                                 #objects         = cms.InputTag('selectedPatTrigger'),
                                 #objects         = cms.InputTag('slimmedPatTrigger'),
                                 objects         = cms.InputTag('patTriggerUnpacker'),
                                 prescales       = cms.InputTag('patTrigger'),
                                 )
process.load("flashgg/Taggers/flashggUpdatedIdMVADiPhotons_cfi")
process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.load("flashgg/Taggers/flashggPreselectedDiPhotons_cfi")
process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')

process.patTriggerUnpacker = cms.EDProducer("PATTriggerObjectStandAloneUnpacker",
                                            patTriggerObjectsStandAlone = cms.InputTag("slimmedPatTrigger"),
                                            triggerResults = cms.InputTag('TriggerResults'      , '', 'HLT'),
                                            unpackFilterLabels = cms.bool(True)
                                            )

#process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')
#process.patTrigger.processName = cms.string('HLT') #FLASHggMicroAOD      
#process.patTrigger.onlyStandAlone = cms.bool(False)
#process.patTrigger.packTriggerPrescales = cms.bool(False)
#process.patTrigger.triggerResults = cms.InputTag( "TriggerResults::HLT" )
#process.patTrigger.triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD::HLT" )

#process.p = cms.Path(process.patTriggerUnpacker)
#process.p = cms.Path(process.patTrigger)
#process.p = cms.Path(process.flashggUpdatedIdMVADiPhotons + process.flashggPreselectedDiPhotons + process.flashggDiPhotonMVA + process.hltTest)
process.p = cms.Path(process.patTriggerUnpacker + process.flashggUpdatedIdMVADiPhotons + process.flashggPreselectedDiPhotons + process.flashggDiPhotonMVA + process.hltTest)

## import flashgg customization
from flashgg.MetaData.JobConfig import customize
customize.tfileOut = ("hltTest","outputFileName")
## set default options if needed
customize.setDefault("maxEvents",-1)
customize.setDefault("targetLumi",10e+3)
## call the customization
customize(process)
