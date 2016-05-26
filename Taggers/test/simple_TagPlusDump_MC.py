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
#process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 100 )

# Uncomment the following if you notice you have a memory leak
# This is a lightweight tool to digg further
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                        ignoreTotal = cms.untracked.int32(1),
#                                        monitorPssAndPrivate = cms.untracked.bool(True)
#                                       )

process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(
        "file:microAOD_1000_wz.root"
        
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_1.root",
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_2.root",
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_3.root",
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_4.root",
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_5.root",
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_6.root",
#"/store/group/phys_higgs/cmshgg/nancy/flashgg/RunIIFall15DR76-1_4_0-25ns/1_4_0/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15DR76-1_4_0-25ns-1_4_0-v0-RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/160512_140422/0000/myMicroAODOutputFile_7.root"

))

process.load("flashgg/Taggers/flashggTagSequence_cfi")
process.load("flashgg/Taggers/flashggTagTester_cfi")


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

#process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('/tmp/nancy/vhEtTagOutputFile_Data.root'),
#                               outputCommands = tagDefaultOutputCommand			       
#                               )




process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("test.root"))

from flashgg.Taggers.tagsDumpers_cfi import createTagDumper
import flashgg.Taggers.dumperConfigTools as cfgTools

process.vhEtTagDumper = createTagDumper("VHEtTag")
process.vhEtTagDumper.dumpTrees =  True
process.vhEtTagDumper.dumpHistos = True



dipho_variables=["dipho_sumpt      := diPhoton.sumPt",
                 "dipho_pt         := diPhoton.pt",
                 "dipho_cosphi     := cos(diPhoton.leadingPhoton.phi - diPhoton.subLeadingPhoton.phi)",
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

cfgTools.addCategories(process.vhEtTagDumper,
                       ## categories definition                                                                                                                                                                                  
                       [("all","1",0)
                    ],
                       ## variables to be dumped in trees/datasets. Same variables for all categories                                                                                                                            
                       variables=dipho_variables+
                       ["pfMET_rawPt        := met.uncorPt",
                        "pfMET_rawPhi       := met.uncorPhi",
                        "pfMET_rawSumEt     := met.uncorSumEt",
                        "pfMET_corPt        := met.corPt",
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




process.p = cms.Path(process.flashggTagSequence*process.flashggTagTester*process.vhEtTagDumper)
#process.p = cms.Path(process.flashggTagSequence)

#process.e = cms.EndPath(process.out)

# import flashgg customization
from flashgg.MetaData.JobConfig import customize
# set default options if needed
customize.setDefault("maxEvents",100)
customize.setDefault("targetLumi",10e+3)
customize.setDefault("puTarget",'1.34e+05,6.34e+05,8.42e+05,1.23e+06,2.01e+06,4.24e+06,1.26e+07,4.88e+07,1.56e+08,3.07e+08,4.17e+08,4.48e+08,4.04e+08,3.05e+08,1.89e+08,9.64e+07,4.19e+07,1.71e+07,7.85e+06,4.2e+06,2.18e+06,9.43e+05,3.22e+05,8.9e+04,2.16e+04,5.43e+03,1.6e+03,551,206,80.1,31.2,11.9,4.38,1.54,0.518,0.165,0.0501,0.0144,0.00394,0.00102,0.000251,5.87e-05,1.3e-05,2.74e-06,5.47e-07,1.04e-07,1.86e-08,3.18e-09,5.16e-10,9.35e-11,0,0')


# OLD customize.setDefault("puTarget", '1.435e+05,6.576e+05,8.781e+05,1.304e+06,2.219e+06,5.052e+06,1.643e+07,6.709e+07,1.975e+08,3.527e+08,4.44e+08,4.491e+08,3.792e+08,2.623e+08,1.471e+08,6.79e+07,2.748e+07,1.141e+07,5.675e+06,3.027e+06,1.402e+06,5.119e+05,1.467e+05,3.53e+04,8270,2235,721.3,258.8,97.27,36.87,13.73,4.932,1.692,0.5519,0.1706,0.04994,0.01383,0.003627,0.0008996,0.0002111,4.689e-05,9.854e-06,1.959e-06,3.686e-07,6.562e-08,1.105e-08,1.762e-09,2.615e-10,4.768e-11,0,0,0')


# call the customization
customize(process)
