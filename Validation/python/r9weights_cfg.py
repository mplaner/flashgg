import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("HLTTest")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_dataRun2_Prompt_v1'
from flashgg.MicroAOD.flashggPreselectedDiPhotons_cfi import flashggPreselectedDiPhotons

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 200 )
process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring("file:myMicroAODOutputFile.root")
                            #fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/SingleElectron/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-Run2015D-05Oct2015-v1/151021_152553/0000/myMicroAODOutputFile_10.root")
                            fileNames = cms.untracked.vstring("/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151021_151505/0000/myMicroAODOutputFile_10.root")
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/m/mplaner/CMSSW_7_4_6_patch2/src/flashgg/myMicroAODOutputFile.root")
                            )

process.hltTest = cms.EDAnalyzer('r9Weights',
                                 outputFileName  = cms.string("outputAAA.root"),
                                 diphoMVACut     = cms.double(-1.0),                                
                                 diPhotonMVATag     = cms.InputTag("flashggDiPhotonMVA"),
                                 diphotons       = cms.InputTag("flashggPreselectedDiPhotons"),
                                 #diphotons       = cms.InputTag("flashggDiPhotons"),
                                 electrons       = cms.InputTag("flashggElectrons"),
                                 genphotons      = cms.InputTag('flashggPrunedGenParticles'),
                                 #genphotons      = cms.InputTag('flashggGenPhotons'),
                                 )

process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.load("flashgg/MicroAOD/flashggPreselectedDiPhotons_cfi")
process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')

process.p = cms.Path( flashggPreselectedDiPhotons + process.flashggDiPhotonMVA + process.hltTest)
#process.p = cms.Path(  process.flashggDiPhotonMVA + process.hltTest)

## import flashgg customization
from flashgg.MetaData.JobConfig import customize
customize.tfileOut = ("hltTest","outputFileName")
## set default options if needed
customize.setDefault("maxEvents",-1)
customize.setDefault("targetLumi",10e+3)
## call the customization
customize(process)
