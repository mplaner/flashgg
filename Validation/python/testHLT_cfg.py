import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("hltTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_v12'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 200 )

DataType = "QCD"
#DataType = "Hgg"

if DataType == "Hgg":
    mylist = FileUtils.loadListFromFile ('microAOD_Hgg.txt')
elif DataType =="QCD":
    mylist = FileUtils.loadListFromFile ('microAOD_QCD.txt')
else:
    mylist = FileUtils.loadListFromFile ('microAOD_QCD.txt')
    
readFiles = cms.untracked.vstring( *mylist)

process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('ProductNotFound'))
process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring("file:myMicroAODOutputFile.root")
                            #fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/m/mplaner/myMicroAODOutputFile.root")
                            fileNames = readFiles,
                            #fileNames = cms.untracked.vstring(
        #"file:testOpenHLT_Hgg.root",
        #"/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/2016c/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLT_2016cmicroAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160418_085554/0000/testOpenHLT_Hgg_1.root",
        #"/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/2016c/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLT_2016cmicroAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160418_085554/0000/testOpenHLT_Hgg_3.root",
        #"/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/2016c/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLT_2016cmicroAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160418_085554/0000/testOpenHLT_Hgg_4.root",
        #"/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/2016c/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLT_2016cmicroAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160418_085554/0000/testOpenHLT_Hgg_5.root",
        #"/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/2016c/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLT_2016cmicroAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160418_085554/0000/testOpenHLT_Hgg_6.root",
        #"/store/group/phys_higgs/cmshgg/mplaner/flashgg/RunIIFall15-ReHLT-25ns/2016c/microAOD/GluGluHToGG_M-125_13TeV_powheg_pythia8/ReHLT-HLT_2016cmicroAOD-25ns-Hgg-RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/160418_085554/0000/testOpenHLT_Hgg_7.root"
                            #),
                            bypassVersionCheck = cms.untracked.bool(True),
                            )


#HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v1
#HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HEloose_R9Id_Mass90_v1
#HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HEloose_R9Idloose_Mass90_v1
#HLT_Diphoton30_18_R9Idloose_OR_IsoCaloId_AND_HEloose_R9Idloose_Mass90_v1

process.hltTest = cms.EDAnalyzer('testHLT',
                                 outputFileName  = cms.string("output.root"),
                                 diphoMVACut     = cms.double(0.05),                                
                                 diphotons       = cms.InputTag("flashggDiPhotons"),
                                 #diphotons       = cms.InputTag("flashggPreselectedDiPhotons"),
                                 genInput        = cms.InputTag("flashggPrunedGenParticles"),
                                 
                                 hltTriggerName95   = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95"),
                                 #hltTriggerName95   = cms.vstring("HLT_Ele23_WPLoose_Gsf"),
                                 leadFilterName95   = cms.vstring("hltEG30LIso60CaloId15b35eHE10R9Id50b80eEcalIsoLastFilter",
                                                                  "hltEG30LR9Id85b90eHE10R9Id50b80eR9IdLastFilter"),
                                 subFilterName95    = cms.vstring("hltEG18Iso60CaloId15b35eHE10R9Id50b80eTrackIsoUnseededLastFilter",
                                                                  "hltEG18R9Id85b90eHE10R9Id50b80eR9UnseededLastFilter"),
                                 
                                 hltTriggerName90      = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90"),
                                 leadFilterName90      = cms.vstring("hltEG30LIso60CaloId15b35eHE10R9Id50b80eEcalIsoLastFilter", 
                                                                     "hltEG30LR9Id85b90eHE10R9Id50b80eR9IdLastFilter"),
                                 subFilterName90       = cms.vstring("hltEG18Iso60CaloId15b35eHE10R9Id50b80eTrackIsoUnseededLastFilter",
                                                                     "hltEG18R9Id85b90eHE10R9Id50b80eR9UnseededLastFilter"),
                                 
                                 
                                 hltTriggerNameLoose     = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HEloose_R9Idloose_Mass90"),
                                 leadFilterNameLoose      = cms.vstring("hltEG30LIso60CaloId15b35eHE12R9Id45b75eEcalIsoLastFilter",
                                                                        "hltEG30LR9Id80b85eHE12R9Id45b75eR9IdLastFilter"),
                                 subFilterNameLoose      = cms.vstring("hltEG18R9Id80b85eHE12R9Id45b75eR9UnseededLastFilter",
                                                                       "hltEG18Iso60CaloId15b35eHE12R9Id45b75eTrackIsoUnseededLastFilter"),
                                 
                                 hltTriggerNameHE      = cms.vstring("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HEloose_R9Id_Mass90"),
                                 leadFilterNameHE      = cms.vstring("hltEG30LIso60CaloId15b35eHE12R9Id50b80eEcalIsoLastFilter", 
                                                                     "hltEG30LR9Id85b90eHE12R9Id50b80eR9IdLastFilter"),
                                 subFilterNameHE       = cms.vstring("hltEG18Iso60CaloId15b35eHE12R9Id50b80eTrackIsoUnseededLastFilter",
                                                                     "hltEG18R9Id85b90eHE12R9Id50b80eR9UnseededLastFilter"),
                                 
                                 hltTriggerNameHElowR9     = cms.vstring("HLT_Diphoton30_18_R9Idloose_OR_IsoCaloId_AND_HEloose_R9Idloose_Mass90"),
                                 leadFilterNameHElowR9     = cms.vstring("hltEG30LIso60CaloId15b35eHE12R9Id45b75eEcalIsoLastFilter",
                                                                         "hltEG30LR9Id85b90eHE12R9Id45b75eR9IdLastFilter"),
                                 subFilterNameHElowR9      = cms.vstring("hltEG18Iso60CaloId15b35eHE12R9Id45b75eTrackIsoUnseededLastFilter",
                                                                         "hltEG18R9Id85b90eHE12R9Id45b75eR9UnseededLastFilter"),

                                 bits            = cms.InputTag('TriggerResults::TEST'),
                                 objects         = cms.InputTag('selectedPatTrigger'),
                                 prescales       = cms.InputTag('patTrigger'),
                                 dataType        = cms.string(DataType)
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


process.p = cms.Path(process.patTrigger + process.flashggUpdatedIdMVADiPhotons + process.flashggDiPhotonMVA + process.flashggPreselectedDiPhotons + process.hltTest)

