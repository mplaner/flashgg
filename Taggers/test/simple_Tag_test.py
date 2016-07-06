import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("FLASHggTag")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'POSTLS170_V5::All'
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 100 )

# Uncomment the following if you notice you have a memory leak
# This is a lightweight tool to digg further
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                        ignoreTotal = cms.untracked.int32(1),
#                                        monitorPssAndPrivate = cms.untracked.bool(True)
#                                       )

process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(

"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_1.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_2.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_3.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_4.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_5.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_6.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_7.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_8.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_9.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_10.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_11.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_12.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_13.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_14.root",
"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-50ns/Spring15BetaV5/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-50ns-Spring15BetaV5-v0-RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/150925_095732/0000/myMicroAODOutputFile_15.root"

))

process.load("flashgg/Taggers/flashggTagSequence_cfi")
process.load("flashgg/Taggers/flashggTagTester_cfi")

# For debugging
switchToPreselected = True
switchToFinal = False
switchToPuppi = False
switchToReadOld = False
assert(not switchToUnPreselected or not switchToFinal)
assert(not switchToReadOld or not switchToUnPreselected)
assert(not switchToReadOld or not switchToFinal)

if switchToReadOld:
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggPreselectedDiPhotons"),cms.InputTag("flashggDiPhotonsWithAddedDz"))
    process.flashggDiPhotonsWithAddedDz = cms.EDProducer('FlashggDiPhotonGenZProducer',
                                                 DiPhotonTag=cms.InputTag('flashggPreselectedDiPhotons'),
                                                 GenParticleTag=cms.InputTag( "flashggPrunedGenParticles" ))
    process.flashggNewPreselectedDiPhotons = cms.Sequence(process.flashggPreselectedDiPhotons*process.flashggDiPhotonsWithAddedDz)
    process.flashggTagSequence.replace(process.flashggPreselectedDiPhotons,process.flashggNewPreselectedDiPhotons)
    process.source.fileNames=cms.untracked.vstring("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/GluGluHToGG_M-125_13TeV_powheg_pythia8/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151021_152108/0000/myMicroAODOutputFile_2.root")
    print process.flashggTagSequence

if switchToUnPreselected:
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggPreselectedDiPhotons"),cms.InputTag("flashggDiPhotons"))

if switchToFinal:
    from flashgg.MicroAOD.flashggFinalEGamma_cfi import flashggFinalEGamma
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggPreselectedDiPhotons"),cms.InputTag("flashggFinalEGamma",flashggFinalEGamma.DiPhotonCollectionName.value()))

if switchToPuppi:
    process.flashggUnpackedJets.JetsTag = cms.InputTag("flashggFinalPuppiJets")

from flashgg.Taggers.flashggTagOutputCommands_cff import tagDefaultOutputCommand

process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('/tmp/nancy/vhEtTagOutputFile.root'),
                               outputCommands = tagDefaultOutputCommand			       
                               )

process.p = cms.Path(process.flashggTagSequence*process.flashggTagTester)

process.e = cms.EndPath(process.out)

# import flashgg customization
from flashgg.MetaData.JobConfig import customize
# set default options if needed
customize.setDefault("maxEvents",100)
customize.setDefault("targetLumi",10e+3)
# call the customization
customize(process)
