import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("FLASHggTagAndDump")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'POSTLS170_V5::All'
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 10000 )

# Uncomment the following if you notice you have a memory leak
# This is a lightweight tool to digg further
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                        ignoreTotal = cms.untracked.int32(1),
#                                        monitorPssAndPrivate = cms.untracked.bool(True)
#                                       )

process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(
        #"file:myMicroAODOutputFile.root"
        #"file:vhSignalMicroAOD.root"
        "file:../../../../CMSSW_8_0_8_patch1/src/flashgg/VHtestfiles.root"
        #"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_1_0-25ns_ICHEP16/2_1_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16DR80X-2_1_0-25ns_ICHEP16-2_1_0-v0-RunIISpring16MiniAODv1-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_v3-v1/160618_081222/0000/myMicroAODOutputFile_1.root"
        #"/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_1_0-25ns_ICHEP16/2_1_0/GluGluHToGG_M-125_13TeV_powheg_pythia8/RunIISpring16DR80X-2_1_0-25ns_ICHEP16-2_1_0-v0-RunIISpring16MiniAODv1-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_v3-v1/160618_074258/0000/myMicroAODOutputFile_1.root"
        #"root://eoscms//eos/cms/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_1_0-25ns_ICHEP16/2_1_0/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8/RunIISpring16DR80X-2_1_0-25ns_ICHEP16-2_1_0-v0-RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v1/160618_074506/0000/myMicroAODOutputFile_100.root"
        ))
process.load("flashgg/Taggers/flashggTagSequence_cfi")
process.load("flashgg/Taggers/flashggTagTester_cfi")
process.load("flashgg/Systematics/flashggMetSystematics_cfi")
# For debugging
switchToUnPreselected = False
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
    process.source.fileNames=cms.untracked.vstring(
        #"file:../../../../CMSSW_8_0_8_patch1/src/flashgg/VHtestfiles.root")
        "root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/GluGluHToGG_M-125_13TeV_powheg_pythia8/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151021_152108/0000/myMicroAODOutputFile_2.root")
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

#process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('/tmp/nancy/vhEtTagOutputFile_Data.root'),
#                               outputCommands = tagDefaultOutputCommand			       
#                               )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("test.root"))

from flashgg.Taggers.tagsDumpers_cfi import createTagDumper
import flashgg.Taggers.dumperConfigTools as cfgTools

process.untaggedDumper = createTagDumper("UntaggedTag")
process.vbfTagDumper = createTagDumper("VBFTag")
process.tthLeptonicTagDumper = createTagDumper("TTHLeptonicTag")
process.tthHadronicTagDumper = createTagDumper("TTHHadronicTag")
process.vhEtTagDumper = createTagDumper("VHMetTag")
process.vhHadronicTagDumper = createTagDumper("VHHadronicTag")
process.vhLooseTagDumper = createTagDumper("WHLeptonicTag")
process.vhTightTagDumper = createTagDumper("ZHLeptonicTag")
process.untaggedDumper.dumpTrees = True
process.vbfTagDumper.dumpTrees = True
process.tthLeptonicTagDumper.dumpTrees = True
process.tthHadronicTagDumper.dumpTrees = True
process.vhEtTagDumper.dumpTrees =  True
process.vhEtTagDumper.dumpHistos = True
process.vhHadronicTagDumper.dumpTrees =  True
process.vhLooseTagDumper.dumpTrees =  True
process.vhTightTagDumper.dumpTrees =  True



dipho_variables=["dipho_sumpt      := diPhoton.sumPt",
                 "dipho_pt         := diPhoton.pt",
                 "dipho_cosphi     := cos(diPhoton.leadingPhoton.phi - diPhoton.subLeadingPhoton.phi)",
                 "dipho_nvtx       := diPhoton.vertexIndex",
                 "mass             := diPhoton.mass",
                 "phi              := diPhoton.momentum.phi",
                 "leadPt           := diPhoton.leadingPhoton.pt",
                 "leadEt           := diPhoton.leadingPhoton.et",
                 "leadEta          := diPhoton.leadingPhoton.eta",
                 "leadPhi          := diPhoton.leadingPhoton.phi",
                 "lead_sieie       := diPhoton.leadingPhoton.full5x5_sigmaIetaIeta",
                 "lead_oldhoe      := diPhoton.leadingPhoton.hadronicOverEm",
                 "lead_hoe         := diPhoton.leadingPhoton.hadTowOverEm",
                 "lead_sigmaEoE    := diPhoton.leadingPhoton.sigEOverE",
                 "lead_ptoM        := diPhoton.leadingPhoton.pt/diPhoton.mass",
                 "leadR9           := diPhoton.leadingPhoton.full5x5_r9",
                 "subleadPt        := diPhoton.subLeadingPhoton.pt",
                 "subleadEt        := diPhoton.subLeadingPhoton.et",
                 "subleadEta       := diPhoton.subLeadingPhoton.eta",
                 "subleadPhi       := diPhoton.subLeadingPhoton.phi",
                 "sublead_sieie    := diPhoton.subLeadingPhoton.full5x5_sigmaIetaIeta",
                 "sublead_oldhoe   := diPhoton.subLeadingPhoton.hadronicOverEm",
                 "sublead_hoe      := diPhoton.leadingPhoton.hadTowOverEm",
                 "sublead_sigmaEoE := diPhoton.subLeadingPhoton.sigEOverE",
                 "sublead_ptoM     := diPhoton.subLeadingPhoton.pt/diPhoton.mass",
                 "subleadR9        := diPhoton.subLeadingPhoton.full5x5_r9",
                 "leadIDMVA        := diPhoton.leadingView.phoIdMvaWrtChosenVtx",
                 "subleadIDMVA     := diPhoton.subLeadingView.phoIdMvaWrtChosenVtx",
                 "diPhoMVA         := diPhotonMVA.result",]



cfgTools.addCategories(process.untaggedDumper,
                       ## categories definition
                       [("all","1",0)
                        ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables,
                       histograms=[]
)

cfgTools.addCategories(process.vbfTagDumper,
                       ## categories definition
                       [("all","1",0)
                        ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables,
                       histograms=[]
)

cfgTools.addCategories(process.tthLeptonicTagDumper,
                       ## categories definition
                       [("all","1",0)
                        ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables,
                       histograms=[]
)

cfgTools.addCategories(process.tthHadronicTagDumper,
                       ## categories definition
                       [("all","1",0)
                        ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables,
                       histograms=[]
)

cfgTools.addCategories(process.vhHadronicTagDumper,
                       ## categories definition
                       [("all","1",0)
                        ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["dRphoLeadJ    := min(deltaR(leadingJet.eta, leadingJet.phi, diPhoton.leadingPhoton.eta, diPhoton.leadingPhoton.phi), deltaR(leadingJet.eta, leadingJet.phi, diPhoton.subLeadingPhoton.eta, diPhoton.subLeadingPhoton.phi))",
                        "dRphoSubleadJ := min(deltaR(subLeadingJet.eta, subLeadingJet.phi, diPhoton.leadingPhoton.eta, diPhoton.leadingPhoton.phi), deltaR(subLeadingJet.eta, subLeadingJet.phi, diPhoton.subLeadingPhoton.eta, diPhoton.subLeadingPhoton.phi))",
                        "leadJPt       := leadingJet.pt",
                        "leadJEta      := leadingJet.eta",
                        "subleadJPt    := subLeadingJet.pt",
                        "subleadJEta   := leadingJet.eta",
                        "Mjj           := sqrt((leadingJet.energy+subLeadingJet.energy)^2-(leadingJet.px+subLeadingJet.px)^2-(leadingJet.py+subLeadingJet.py)^2-(leadingJet.pz+subLeadingJet.pz)^2)",
                        "tagType := tagEnum()",
                        "hasZ := tagTruth().associatedZ",
                        "hasW := tagTruth().associatedW",
                        "VhasDaughters := tagTruth().VhasDaughters",
                        "VhasNeutrinos := tagTruth().VhasNeutrinos",
                        "VhasLeptons := tagTruth().VhasLeptons",
                        "VhasHadrons := tagTruth().VhasHadrons",
                        "VhasMissingLeptons := tagTruth().VhasMissingLeptons",
                        "genZ := tagTruth().genPV().z",
                        "Vpt := tagTruth().Vpt"
                        ],
                       ## histograms
                       histograms=[]
)


cfgTools.addCategories(process.vhLooseTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["pfMET_rawPt        := met().uncorPt",
                        "pfMET_rawPhi       := met().uncorPhi",
                        "pfMET_rawSumEt     := met().uncorSumEt",
                        "tagged_met         := met().getCorPt()",
                        "tagged_phi         := met().getCorPhi()",
                        "pfMET_corPt        := met().corPt",
                        "pfMET_corPhi       := met.corPhi",
                        "pfMET_corSumEt     := met.corSumEt",
                        "caloMET_rawPt      := met.caloMETPt",
                        "caloMET_rawPhi     := met.caloMETPhi",
                        "caloMET_rawSumEt   := met.caloMETSumEt",
                        #"pfMET_rawPt        := ?met.size>0? met.at(0).uncorPt : -1",
                        #"pfMET_rawPhi       := ?met.size>0? met.at(0).uncorPhi : -1",
                        #"pfMET_rawSumEt     := ?met.size>0? met.at(0).uncorSumEt : -1",
                        #"pfMET_corPt        := ?met.size>0? met.at(0).corPt : -1",
                        #"pfMET_corPhi       := ?met.size>0? met.at(0).corPhi : -1",
                        #"pfMET_corSumEt     := ?met.size>0? met.at(0).corSumEt : -1",
                        "n_ele    := electrons.size",
                        "ele1_pt  := ?(electrons.size>0)? electrons.at(0).pt : -1",
                        "ele2_pt  := ?(electrons.size>1)? electrons.at(1).pt : -1",
                        "n_muons  := muons.size",
                        "muon1_pt := ?(muons.size>0)? muons.at(0).pt : -1",
                        "muon2_pt := ?(muons.size>1)? muons.at(1).pt : -1",
                        "n_jets   := jets.size",
                        "jet1_pt  := ?(jets.size>0)? jets.at(0).pt : -1",
                        "jet2_pt  := ?(jets.size>1)? jets.at(1).pt : -1",
                        "Mjj      := ?(jets.size>1)?"
                        +"sqrt((jets.at(0).energy+jets.at(1).energy)^2-(jets.at(0).px+jets.at(1).px)^2-(jets.at(0).py+jets.at(1).py)^2-(jets.at(0).pz+jets.at(1).pz)^2)"
                        +": -1",
                        #"hasZ := tagTruth().associatedZ",
                        #"hasW := tagTruth().associatedW",
                        #"VhasDaughters := tagTruth().VhasDaughters",
                        #"VhasNeutrinos := tagTruth().VhasNeutrinos",
                        #"VhasLeptons := tagTruth().VhasLeptons",
                        #"VhasHadrons := tagTruth().VhasHadrons",
                        #"VhasMissingLeptons := tagTruth().VhasMissingLeptons",
                        #"genZ := tagTruth().genPV().z",
                        #"Vpt := tagTruth().Vpt"
                    ],
                       ## histograms
                       histograms=[]
)


cfgTools.addCategories(process.vhTightTagDumper,
                        ## categories definition
                       [("all","1",0)
                        ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["pfMET_rawPt        := met().uncorPt",
                        "pfMET_rawPhi       := met().uncorPhi",
                        "pfMET_rawSumEt     := met().uncorSumEt",
                        "tagged_met         := met().getCorPt()",
                        "tagged_phi         := met().getCorPhi()",
                        "pfMET_corPt        := met().corPt",
                        "pfMET_corPhi       := met.corPhi",
                        "pfMET_corSumEt     := met.corSumEt",
                        "caloMET_rawPt      := met.caloMETPt",
                        "caloMET_rawPhi     := met.caloMETPhi",
                        "caloMET_rawSumEt   := met.caloMETSumEt",
                        #"pfMET_rawPt        := ?met.size>0? met.at(0).uncorPt : -1",
                        #"pfMET_rawPhi       := ?met.size>0? met.at(0).uncorPhi : -1",
                        #"pfMET_rawSumEt     := ?met.size>0? met.at(0).uncorSumEt : -1",
                        #"pfMET_corPt        := ?met.size>0? met.at(0).corPt : -1",
                        #"pfMET_corPhi       := ?met.size>0? met.at(0).corPhi : -1",
                        #"pfMET_corSumEt     := ?met.size>0? met.at(0).corSumEt : -1",
                        "n_ele    := electrons.size",
                        "ele1_pt  := ?(electrons.size>0)? electrons.at(0).pt : -1",
                        "ele2_pt  := ?(electrons.size>1)? electrons.at(1).pt : -1",
                        "n_muons  := muons.size",
                        # "muon1_pt := ?(muons.size>0)? muons.at(0).pt : -1",
                        # "muon2_pt := ?(muons.size>1)? muons.at(1).pt : -1",
                        "n_jets   := jets.size",
                        "jet1_pt  := ?(jets.size>0)? jets.at(0).pt : -1",
                        "jet2_pt  := ?(jets.size>1)? jets.at(1).pt : -1",
                        "Mjj      := ?(jets.size>1)?"
                        +"sqrt((jets.at(0).energy+jets.at(1).energy)^2-(jets.at(0).px+jets.at(1).px)^2-(jets.at(0).py+jets.at(1).py)^2-(jets.at(0).pz+jets.at(1).pz)^2)"
                        +": -1",
                        "hasZ := tagTruth().associatedZ",
                        "hasW := tagTruth().associatedW",
                        "VhasDaughters := tagTruth().VhasDaughters",
                        "VhasNeutrinos := tagTruth().VhasNeutrinos",
                        "VhasLeptons := tagTruth().VhasLeptons",
                        "VhasHadrons := tagTruth().VhasHadrons",
                        "VhasMissingLeptons := tagTruth().VhasMissingLeptons",
                        "genZ := tagTruth().genPV().z",
                        ],
                       ## histograms
                       histograms=[]
                       )

cfgTools.addCategories(process.vhEtTagDumper,
                       ## categories definition                                                                                                                                                                                  
                       [("all","1",0)
                    ],
                       ## variables to be dumped in trees/datasets. Same variables for all categories                                                                                                                            
                       variables=dipho_variables+
                       [
                        "pfMET_rawPt        := met().uncorPt",
                        "pfMET_rawPhi       := met().uncorPhi",
                        "pfMET_rawSumEt     := met().uncorSumEt",
                        "pfMET_corPt        := met().corPt",
                        "tagged_met         := met().getCorPt()",
                        "tagged_phi         := met().getCorPhi()",
                        "pfMET_corPhi       := met.corPhi",
                        "pfMET_corSumEt     := met.corSumEt",
                        "caloMET_rawPt      := met.caloMETPt",
                        "caloMET_rawPhi     := met.caloMETPhi",
                        "caloMET_rawSumEt   := met.caloMETSumEt",
                        #"genMET_pt          := met.genMET.pt",
                        #"genMET_phi         := met.genMET.phi",
                        #"genMET_sumEt       := met.genMET.sumEt",
                        #"pfNeutralEMFraction := met.NeutralEMFraction",
                        #"pfNeutralHadEtFraction := met.NeutralHadEtFraction",
                        #"pfChargedEMEtFraction := met.ChargedEMEtFraction",
                        #"pfChargedHadEtFraction := met.ChargedHadEtFraction",
                        "hasZ := tagTruth().associatedZ",
                        "hasW := tagTruth().associatedW",
                        "VhasDaughters := tagTruth().VhasDaughters",
                        "VhasNeutrinos := tagTruth().VhasNeutrinos",
                        "VhasLeptons := tagTruth().VhasLeptons",
                        "VhasHadrons := tagTruth().VhasHadrons",
                        "VhasMissingLeptons := tagTruth().VhasMissingLeptons",
                        "genZ := tagTruth().genPV().z",
                        "Vpt := tagTruth().Vpt"
                        ],
                       histograms=["mass>>mass(160,100,180)",
                                   "subleadPt:leadPt>>ptLeadvsSub(180,20,200:180,20,200)",
                                   "leadIDMVA>>leadIDMVA(50,0,1)",
                                   "subleadIDMVA>>subleadIDMVA(50,0,1)",
                                   "pfMET_rawPt>>pfMET_rawPt(250,0,500)",
                                   "pfMET_corPt>>pfMET_corPt(250,0,500)",
                                   "pfMET_rawSumEt>>pfMET_rawSumEt(400,200,2000)",
                                   "pfMET_corSumEt>>pfMET_corSumEt(400,200,2000)",
                                   "caloMET_rawPt>>caloMET_rawPt(250,0,500)",
                                   "caloMET_rawSumEt>>caloMET_rawSumEt(400,200,2000)",
                                   "pfMET_rawPhi>>pfMET_rawPhi(100,-3.14,3.14)",
                                   "pfMET_corPhi>>pfMET_corPhi(100,-3.14,3.14)",
                                   "caloMET_rawPhi>>caloMET_rawPhi(100,-3.14,3.14)",
                                   #"genMET_pt>>genMET_pt(250,0,500)",
                                   #"genMET_phi>>genMET_phi(100,-3.14,3.14)",
                                   #"genMET_sumEt>>genMET_sumEt(400,200,2000)"
                                  ]
                       )





#process.p = cms.Path(process.flashggTagSequence*process.flashggTagTester*process.vhEtTagDumper*process.vhHadronicTagDumper*process.vhTightTagDumper*process.vhLooseTagDumper)
#process.p = cms.Path(process.flashggMetSystematics*process.flashggTagSequence*process.flashggTagTester*process.vhEtTagDumper*process.vhTightTagDumper*process.vhLooseTagDumper*process.tthLeptonicTagDumper*process.tthHadronicTagDumper*process.untaggedDumper*process.vbfTagDumper)a
#process.p = cms.Path(process.flashggMetSystematics*process.flashggTagSequence*process.vhEtTagDumper*process.vhTightTagDumper*process.vhLooseTagDumper*process.tthLeptonicTagDumper*process.tthHadronicTagDumper*process.vbfTagDumper)

process.p = cms.Path(process.flashggTagSequence*process.vhEtTagDumper*process.vhTightTagDumper*process.vhLooseTagDumper*process.tthLeptonicTagDumper*process.tthHadronicTagDumper*process.vbfTagDumper)
#process.p = cms.Path(process.flashggTagSequence*process.flashggTagTester*process.vhEtTagDumper*process.vhTightTagDumper*process.vhLooseTagDumper)
#process.p = cms.Path(process.flashggTagSequence)
print process.vhEtTagDumper.src
#process.p = cms.Path(process.flashggTagSequence)

#process.e = cms.EndPath(process.out)

# import flashgg customization
from flashgg.MetaData.JobConfig import customize
# set default options if needed
customize.setDefault("maxEvents",-1)
customize.setDefault("targetLumi",10e+5)
#customize.setDefault("targetLumi",10e+3)
customize.setDefault("puTarget",'1.34e+05,6.34e+05,8.42e+05,1.23e+06,2.01e+06,4.24e+06,1.26e+07,4.88e+07,1.56e+08,3.07e+08,4.17e+08,4.48e+08,4.04e+08,3.05e+08,1.89e+08,9.64e+07,4.19e+07,1.71e+07,7.85e+06,4.2e+06,2.18e+06,9.43e+05,3.22e+05,8.9e+04,2.16e+04,5.43e+03,1.6e+03,551,206,80.1,31.2,11.9,4.38,1.54,0.518,0.165,0.0501,0.0144,0.00394,0.00102,0.000251,5.87e-05,1.3e-05,2.74e-06,5.47e-07,1.04e-07,1.86e-08,3.18e-09,5.16e-10,9.35e-11,0,0')


# OLD customize.setDefault("puTarget", '1.435e+05,6.576e+05,8.781e+05,1.304e+06,2.219e+06,5.052e+06,1.643e+07,6.709e+07,1.975e+08,3.527e+08,4.44e+08,4.491e+08,3.792e+08,2.623e+08,1.471e+08,6.79e+07,2.748e+07,1.141e+07,5.675e+06,3.027e+06,1.402e+06,5.119e+05,1.467e+05,3.53e+04,8270,2235,721.3,258.8,97.27,36.87,13.73,4.932,1.692,0.5519,0.1706,0.04994,0.01383,0.003627,0.0008996,0.0002111,4.689e-05,9.854e-06,1.959e-06,3.686e-07,6.562e-08,1.105e-08,1.762e-09,2.615e-10,4.768e-11,0,0,0')


# call the customization
customize(process)
