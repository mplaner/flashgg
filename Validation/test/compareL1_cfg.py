import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("L1Test")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_v12'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 200 )

stage1only = FileUtils.loadListFromFile ('/afs/cern.ch/user/m/mplaner/flashgg/CMSSW_7_6_3_patch2/src/flashgg/microAOD_stage1_hgg.txt')
stage2only = FileUtils.loadListFromFile ('/afs/cern.ch/user/m/mplaner/flashgg/CMSSW_7_6_3_patch2/src/flashgg/microAOD_Hgg_l1Study.txt')
read2Files = cms.untracked.vstring( *stage2only)
readFiles = cms.untracked.vstring( *stage1only)

process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring("file:myMicroAODOutputFile.root")
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/m/mplaner/myMicroAODOutputFile.root")
                            #fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/HLTtestPathsStage1e/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-stage1L1e-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160509_115031/0000/STAGE1_RAW2DIGI_9.root"),
                            fileNames = readFiles,
                            secondaryFileNames = read2Files,
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/mplaner/flashgg/CMSSW_7_6_3_patch2/src/flashgg/testOpenHLT_Hgg.root"),
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/mplaner/CMSSW_8_0_6/src/STAGE1_RAW2DIGI.root"),
                            #fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/HLTtestPathsStage1c/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-stage1L1c-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160509_091648/0000/STAGE1_RAW2DIGI_13.root"),
                            eventsToSkip = cms.untracked.VEventRange('1:1662:331781-1:1662:332381'),
                            bypassVersionCheck = cms.untracked.bool(True),
                            )

process.l1Test = cms.EDAnalyzer('L1Compare',
                                outputFileName  = cms.string("output.root"),
                                diphotons       = cms.InputTag("flashggPreselectedDiPhotons"),
                                genInput        = cms.InputTag("flashggPrunedGenParticles"),
                                
                                l1Iso           = cms.InputTag('l1extraParticles','Isolated','RAW2DIGI'),
                                l1NonIso        = cms.InputTag('l1extraParticles','NonIsolated','RAW2DIGI'),
                                l1IsoOld        = cms.InputTag('l1extraParticles','Isolated','RECO'),
                                l1NonIsoOld     = cms.InputTag('l1extraParticles','NonIsolated','RECO'),
                                newL1           = cms.InputTag("hltCaloStage2Digis:EGamma"),
                                bits            = cms.InputTag('TriggerResults::HLT'),
                                objects         = cms.InputTag('selectedPatTrigger'),
                                prescales       = cms.InputTag('patTrigger'),
                                )

process.load("flashgg/Taggers/flashggUpdatedIdMVADiPhotons_cfi")
process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')
process.load("flashgg/Taggers/flashggPreselectedDiPhotons_cfi")
process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')
process.patTrigger.processName = cms.string('TEST') #FLASHggMicroAOD
process.patTrigger.onlyStandAlone = cms.bool(False)
process.patTrigger.packTriggerPrescales = cms.bool(False)
process.patTrigger.triggerResults = cms.InputTag( "TriggerResults::TEST" )
process.patTrigger.triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD::TEST" )

process.p = cms.Path(process.patTrigger + process.flashggUpdatedIdMVADiPhotons + process.flashggDiPhotonMVA + process.flashggPreselectedDiPhotons + process.l1Test)

