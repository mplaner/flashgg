import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("FLASHggMicroAOD")
from FWCore.ParameterSet.VarParsing import VarParsing
process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'PLS170_V7AN1::All'
#process.GlobalTag.globaltag = 'auto:run2_mc'
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
options = VarParsing ('analysis')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1 )

#process.GlobalTag = GlobalTag(process.GlobalTag, 'MCRUN2_74_V9')
process.GlobalTag = GlobalTag(process.GlobalTag, '76X_mcRun2_asymptotic_v13')

# Fix because auto:run2_mc points to MCRUN2_74_V9::All
current_gt = process.GlobalTag.globaltag.value()
if current_gt.count("::All"):
    new_gt = current_gt.replace("::All","")
    print 'Removing "::All" from GlobalTag by hand for condDBv2: was %s, now %s' % (current_gt,new_gt)
    process.GlobalTag.globaltag = new_gt


process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService")
process.RandomNumberGeneratorService.flashggRandomizedPhotons = cms.PSet(
          initialSeed = cms.untracked.uint32(16253245)
        )

mylist = FileUtils.loadListFromFile('FileList.txt')
readFiles = cms.untracked.vstring(*mylist)

process.source = cms.Source("PoolSource",
                            inputCommands=cms.untracked.vstring("keep *",
                                                                #'drop *_l1extraParticles_*_*',
                                                                'drop *_selectedPatTrigger_*_*',
                                                                #'drop *_hltTriggerSummaryAOD_*_*'
                                                                ),
                            
                            fileNames=readFiles,
                            #fileNames=cms.untracked.vstring(options.inputFiles),
                            #fileNames=cms.untracked.vstring("root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/Fall15reHLTV0/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ReHLTmassScan-25ns-CHILD-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160217_054942/0000/flashggReHLTout_1.root"),
                            
                            secondaryFileNames=cms.untracked.vstring( 
        "/store/mc/RunIIFall15DR76/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/10000/14E60946-E08E-E511-AE09-005056020789.root",
        "/store/mc/RunIIFall15DR76/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/10000/20836FD1-DC8E-E511-8B78-005056020781.root",
        "/store/mc/RunIIFall15DR76/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/10000/3A15695D-1A93-E511-8BA3-02163E0167CF.root",
        "/store/mc/RunIIFall15DR76/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/10000/725A39D4-DC8E-E511-A2E2-00505602077B.root",
        "/store/mc/RunIIFall15DR76/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/10000/A09CE786-5793-E511-82A9-02163E00EB28.root"),
                            
                            #fileNames=cms.untracked.vstring("root://xrootd.unl.edu//store/mc/RunIISpring15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/AsymptFlat10to50bx25Raw_74X_mcRun2_asymptotic_v2-v1/10000/1AE0EE35-B47C-E511-AC17-002618943875.root"),
                            #fileNames=cms.untracked.vstring("root://xrootd.unl.edu//store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/Fall15reHLTV0/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ReHLTmassScan-25ns-CHILD-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160217_054942/0000/flashggReHLTout_1.root"),
                            
                            #secondaryFileNames=cms.untracked.vstring(#"file:/tmp/mplaner/329CE056-7101-E511-9EB4-002618943947.root",
                            #"root://xrootd.unl.edu//store/mc/RunIIFall15DR76/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/10000/3A15695D-1A93-E511-8BA3-02163E0167CF.root")
                            #"/store/mc/RunIISpring15MiniAODv2/GluGluHToGG_M-125_13TeV_powheg_pythia8/MINIAODSIM/AsymptFlat10to50bx25Raw_74X_mcRun2_asymptotic_v2-v1/10000/18BD08CD-097D-E511-9704-842B2B298D0B.root")
                            #"root://xrootd.unl.edu//store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM-RAW/AsymptFlat10to50bx25Raw_MCRUN2_74_V9-v1/10000/185A7855-7801-E511-A4FB-0025905A60F2.root",)
                            )

process.MessageLogger.cerr.threshold = 'ERROR' # can't get suppressWarning to work: disable all warnings for now
#process.MessageLogger.categories.append('TriggerSummaryProducerAOD')
#process.MessageLogger.categories.append('L1GtTrigReport')
#process.MessageLogger.categories.append('HLTrigReport')
#process.MessageLogger.categories.append('FastReport')

process.load("flashgg/MicroAOD/flashggMicroAODSequence_cff")
#process.weightsCount.pileupInfo = "addPileupInfo"  #for DY
process.weightsCount.pileupInfo = "slimmedAddPileupInfo"  #for Hgg

from flashgg.MicroAOD.flashggMicroAODOutputCommands_cff import microAODHLTOutputCommand
from flashgg.MicroAOD.flashggMicroAODOutputCommands_cff import microAODDefaultOutputCommand
process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('/afs/cern.ch/work/m/mplaner/microAOD/dyM100-200.root'),
                               outputCommands = microAODDefaultOutputCommand 
                               #microAODHLTOutputCommand+microAODDefaultOutputCommand  
                               #microAODDefaultOutputCommand + 
)


#process.load('HLTrigger.Configuration.hlt_hgg_cff')
#process.load( 'Configuration.StandardSequences.RawToDigi_cff' )
#process.load( 'Configuration.StandardSequences.SimL1Emulator_cff' )
#process.load('Configuration.StandardSequences.EndOfProcess_cff')

#process.L1simulation_step = cms.Path((process.simRctDigis+process.simGctDigis+process.SimL1MuTriggerPrimitives+process.simCsctfTrackDigis+process.simDttfDigis+process.simCsctfDigis+process.simRpcTriggerDigis+process.simGmtDigis+process.SimL1TechnicalTriggers+process.simGtDigis))

process.output = cms.EndPath(process.out)
#process.endjob_step = cms.EndPath(process.endOfProcess)

#process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')
#process.patTrigger.processName = cms.string('FLASHggMicroAOD')
#process.patTrigger.onlyStandAlone = cms.bool(True)
#process.patTrigger.packTriggerPrescales = cms.bool(False)
process.p1 = cms.Path(process.flashggMicroAODSequence)

#process.schedule = cms.Schedule(process.L1simulation_step)
#process.schedule = cms.Schedule()
#process.schedule.extend(process.HLTSchedule)

#process.schedule.extend([process.p1,process.endjob_step,process.output])



