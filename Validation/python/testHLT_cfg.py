import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("hltTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v8'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 10000 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 200 )

DataType = "QCD"
#DataType = "Hgg"

#if DataType == "Hgg":
#    mylist = FileUtils.loadListFromFile ('microAOD_Hgg.txt')
#elif DataType =="QCD":
#    mylist = FileUtils.loadListFromFile ('microAOD_QCD.txt')
#else:
#    mylist = FileUtils.loadListFromFile ('microAOD_QCD.txt')
    
#readFiles = cms.untracked.vstring( *mylist)

process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('ProductNotFound'))
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring("root://eoscms.cern.ch//eos/cms//store/group/phys_higgs/cmshgg/sethzenz/flashgg/ReMiniAOD-03Feb2017-2_5_4/2_5_1/DoubleEG/ReMiniAOD-03Feb2017-2_5_4-2_5_1-v0-Run2016G-03Feb2017-v1/170307_170744/0000/myMicroAODOutputFile_1.root",
                                                              "root://eoscms.cern.ch//eos/cms//store/group/phys_higgs/cmshgg/sethzenz/flashgg/ReMiniAOD-03Feb2017-2_5_4/2_5_1/DoubleEG/ReMiniAOD-03Feb2017-2_5_4-2_5_1-v0-Run2016G-03Feb2017-v1/170307_170744/0000/myMicroAODOutputFile_10.root",
                                                              "root://eoscms.cern.ch//eos/cms//store/group/phys_higgs/cmshgg/sethzenz/flashgg/ReMiniAOD-03Feb2017-2_5_4/2_5_1/DoubleEG/ReMiniAOD-03Feb2017-2_5_4-2_5_1-v0-Run2016G-03Feb2017-v1/170307_170744/0000/myMicroAODOutputFile_100.root",
                                                              "root://eoscms.cern.ch//eos/cms//store/group/phys_higgs/cmshgg/sethzenz/flashgg/ReMiniAOD-03Feb2017-2_5_4/2_5_1/DoubleEG/ReMiniAOD-03Feb2017-2_5_4-2_5_1-v0-Run2016G-03Feb2017-v1/170307_170744/0000/myMicroAODOutputFile_101.root",
                                                              "root://eoscms.cern.ch//eos/cms//store/group/phys_higgs/cmshgg/sethzenz/flashgg/ReMiniAOD-03Feb2017-2_5_4/2_5_1/DoubleEG/ReMiniAOD-03Feb2017-2_5_4-2_5_1-v0-Run2016G-03Feb2017-v1/170307_170744/0000/myMicroAODOutputFile_102.root"
                                                              )
                            #bypassVersionCheck = cms.untracked.bool(True),
                            )


#HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v1
#HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HEloose_R9Id_Mass90_v1
#HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HEloose_R9Idloose_Mass90_v1
#HLT_Diphoton30_18_R9Idloose_OR_IsoCaloId_AND_HEloose_R9Idloose_Mass90_v1

process.hltTest = cms.EDAnalyzer('testHLT',
                                 outputFileName  = cms.string("output.root"),
                                 diphoMVACut     = cms.double(0.05),                                
                                 #diphotons       = cms.InputTag("flashggDiPhotons"),
                                 diphotons       = cms.InputTag("flashggPreselectedDiPhotons"),
                                 genInput        = cms.InputTag("flashggPrunedGenParticles"),
                                 
                                 hltTriggerName   = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90"),
                                 #hltTriggerName   = cms.vstring("HLT_Ele23_WPLoose_Gsf"),
                                 subFilterName   = cms.vstring("hltEG30LIso60CaloId15b35eHE12R9Id50b80eEcalIsoLastFilter",
                                                                "hltEG30LR9Id85b90eHE12R9Id50b80eR9IdLastFilter",
                                                                "hltEG18Iso60CaloId15b35eHE12R9Id50b80eTrackIsoUnseededLastFilter",
                                                                "hltEG18R9Id85b90eHE12R9Id50b80eR9UnseededLastFilter"),
                                 leadFilterName    = cms.vstring("hltEG18Iso60CaloId15b35eHE12R9Id50b80eTrackIsoUnseededLastFilter",
                                                                  "hltEG18R9Id85b90eHE12R9Id50b80eR9UnseededLastFilter"),
                                 
                                 bits            = cms.InputTag('TriggerResults::HLT'),
                                 objects         = cms.InputTag('selectedPatTrigger'),
                                 prescales       = cms.InputTag('patTrigger'),
                                 dataType        = cms.string(DataType)
                                 )

process.load("flashgg/Taggers/flashggUpdatedIdMVADiPhotons_cfi")
process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')
process.load("flashgg/Taggers/flashggPreselectedDiPhotons_cfi")
process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')
#process.patTrigger.processName = cms.string('HLT') #FLASHggMicroAOD                                                                                                                                          
#process.patTrigger.onlyStandAlone = cms.bool(False)
#process.patTrigger.packTriggerPrescales = cms.bool(False)
#process.patTrigger.triggerResults = cms.InputTag( "TriggerResults::HLT" )
#process.patTrigger.triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD::HLT" )


#process.p = cms.Path(process.patTrigger + process.flashggUpdatedIdMVADiPhotons + process.flashggDiPhotonMVA + process.flashggPreselectedDiPhotons + process.hltTest)
process.p = cms.Path(process.flashggUpdatedIdMVADiPhotons + process.flashggDiPhotonMVA + process.flashggPreselectedDiPhotons + process.hltTest)
