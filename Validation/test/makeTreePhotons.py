import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("tnp")

###################################################################
options = dict()

isMC=False


options['HLTProcessName']        = "HLT"

#options['PHOTON_COLL']           = "slimmedPhotons"
#options['DIPHOTON_COLL']         = "flashggPreselectedDiPhotons"
options['DIPHOTON_COLL']         = "flashggDiPhotons"
#options['PHOTON_CUTS']           = ""
#options['PHOTON_PROBE_CUTS']           = ""
#options['PHOTON_TAG_CUTS']       = ""

#options['PHOTON_CUTS']           = "(abs(eta)<2.5) && (pt)>15.0)"
options['PHOTON_CUTS']           = "(abs(eta)<2.5) && (pt>15)"
options['PHOTON_PROBE_CUTS']           = "(abs(eta)<2.5) && (pt>30.0)"
options['PHOTON_TAG_CUTS']       = "(abs(eta)<=2.1) && !(1.4442<=abs(eta)<=1.566) && (pt>30.0)"

#options['PHOTON_CUTS']           = "(abs(superCluster.eta)<2.5) && ((superCluster.energy*sin(superCluster.position.theta))>15.0)"
#options['PHOTON_PROBE_CUTS']           = "(abs(superCluster.eta)<2.5) && ((superCluster.energy*sin(superCluster.position.theta))>20.0)"
#options['PHOTON_TAG_CUTS']       = "(abs(superCluster.eta)<=2.1) && !(1.4442<=abs(superCluster.eta)<=1.566) && (superCluster.energy*sin(superCluster.position.theta))>30.0"

options['MAXEVENTS']             = cms.untracked.int32(-1) 
options['useAOD']                = cms.bool(False)
options['OUTPUTEDMFILENAME']     = 'edmFile.root'
options['DEBUG']                 = cms.bool(False)
options['LEADING_PRESELECTION']  = """
                                                    (abs(leadingPhoton.superCluster.eta) < 2.5 && abs(subLeadingPhoton.superCluster.eta) < 2.5) &&
                                    (leadingPhoton.pt > 20) &&
                                    (  leadingPhoton.hadronicOverEm < 0.1) &&
                                    (( leadingPhoton.full5x5_r9 > 0.5 && leadingPhoton.isEB) || (leadingPhoton.full5x5_r9 > 0.8 && leadingPhoton.isEE)) &&
                                    (( subLeadingPhoton.full5x5_r9 > 0.5 && subLeadingPhoton.isEB) || (subLeadingPhoton.full5x5_r9 > 0.8 && subLeadingPhoton.isEE)) &&
                                    (
                                        ( leadingPhoton.isEB &&
                                        (leadingPhoton.full5x5_r9>0.85 || 
                                        (leadingPhoton.full5x5_sigmaIetaIeta < 0.015 && 
                                         leadingPhoton.pfPhoIso03 < 4.0 && 
                                         leadingPhoton.trkSumPtHollowConeDR03 < 6.0 )))  ||
                                        ( leadingPhoton.isEE &&
                                        (leadingPhoton.full5x5_r9>0.9 || 
                                        (leadingPhoton.full5x5_sigmaIetaIeta < 0.035 && 
                                         leadingPhoton.pfPhoIso03 < 4.0 && 
                                         leadingPhoton.trkSumPtHollowConeDR03 < 6.0 ))) 
                                     )
                                        &&
                                     (leadingPhoton.pt > 14 && leadingPhoton.hadTowOverEm()<0.15 && 
                                     (leadingPhoton.r9()>0.8 || leadingPhoton.chargedHadronIso()<20 
                                      || leadingPhoton.chargedHadronIso()<0.3*leadingPhoton.pt())) 
""" 

options['SUBLEADING_PRESELECTION'] = """
                                                    (abs(leadingPhoton.superCluster.eta) < 2.5 && abs(subLeadingPhoton.superCluster.eta) < 2.5) &&
                                    (subLeadingPhoton.pt > 20) &&
                                    ( subLeadingPhoton.hadronicOverEm < 0.1) &&
                                    (( leadingPhoton.full5x5_r9 > 0.5 && leadingPhoton.isEB) || (leadingPhoton.full5x5_r9 > 0.8 && leadingPhoton.isEE)) &&
                                    (( subLeadingPhoton.full5x5_r9 > 0.5 && subLeadingPhoton.isEB) || (subLeadingPhoton.full5x5_r9 > 0.8 && subLeadingPhoton.isEE)) &&
                                    (
                                        ( subLeadingPhoton.isEB &&
                                        (subLeadingPhoton.full5x5_r9>0.85 || 
                                        (subLeadingPhoton.full5x5_sigmaIetaIeta < 0.015 && 
                                         subLeadingPhoton.pfPhoIso03 < 4.0 && 
                                         subLeadingPhoton.trkSumPtHollowConeDR03 < 6.0 )))  ||
                                        ( subLeadingPhoton.isEE &&
                                        (subLeadingPhoton.full5x5_r9>0.9 || 
                                        (subLeadingPhoton.full5x5_sigmaIetaIeta < 0.035 && 
                                         subLeadingPhoton.pfPhoIso03 < 6.0 && 
                                         subLeadingPhoton.trkSumPtHollowConeDR03 < 6.0 ))) 
                                     )
                                        &&
                                     (subLeadingPhoton.pt > 14 && subLeadingPhoton.hadTowOverEm()<0.15 &&
                                     (subLeadingPhoton.r9()>0.8 || subLeadingPhoton.chargedHadronIso()<20 
                                      || subLeadingPhoton.chargedHadronIso()<0.3*subLeadingPhoton.pt()))               
"""


from flashgg.Validation.treeMakerOptionsPhotons_cfi import *

if (isMC):
    options['INPUT_FILE_NAME']       = ("/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV6-25ns/Spring15BetaV6/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8//RunIISpring15-ReMiniAOD-BetaV6-25ns-Spring15BetaV6-v1-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151015_170625/0000/myMicroAODOutputFile_1.root")

    options['OUTPUT_FILE_NAME']      = "TnPTree_mc.root"
    options['TnPPATHS']              = cms.vstring("HLT_Ele22_eta2p1_WP75_Gsf_v*")
    options['TnPHLTTagFilters']      = cms.vstring()#"hltEle22eta2p1WP75GsfTrackIsoFilter")
    options['TnPHLTProbeFilters']    = cms.vstring()
    options['HLTFILTERTOMEASURE']    = cms.vstring("")
    options['GLOBALTAG']             = 'MCRUN2_74_V9'
    options['EVENTSToPROCESS']       = cms.untracked.VEventRange()
else:
    options['INPUT_FILE_NAME']       = ("/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/SingleElectron/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-Run2015D-05Oct2015-v1/151021_152553/0000/myMicroAODOutputFile_10.root")
    options['OUTPUT_FILE_NAME']      = "TnPTree_data.root"
    options['TnPPATHS']              = cms.vstring("HLT_Ele23_WPLoose_Gsf_v*")
    options['TnPHLTTagFilters']      = cms.vstring("hltEle23WPLooseGsfTrackIsoFilter")   
    options['TnPHLTProbeFilters']    = cms.vstring()
    #options['TagLeadMatchFilters']    = cms.vstring("hltEG30LIso60CaloId15b35eHE10R9Id50b80eEcalIsoLastFilter", "hltEG30LR9Id85b90eHE10R9Id50b80eR9IdLastFilter")  #sublead eff only
    options['TagLeadMatchFilters']    = cms.vstring()  #lead eff only
    options['HLTFILTERTOMEASURE']    = cms.vstring("hltEG30LIso60CaloId15b35eHE10R9Id50b80eEcalIsoLastFilter", "hltEG30LR9Id85b90eHE10R9Id50b80eR9IdLastFilter")  #lead eff only
    #options['HLTFILTERTOMEASURE']    = cms.vstring("hltEG18Iso60CaloId15b35eHE10R9Id50b80eTrackIsoUnseededLastFilter", "hltEG18R9Id85b90eHE10R9Id50b80eR9UnseededLastFilter")  #sublead eff only
    options['GLOBALTAG']             = 'MCRUN2_74_V9'
    options['EVENTSToPROCESS']       = cms.untracked.VEventRange()

###################################################################

setModules(process, options)
from PhysicsTools.TagAndProbe.treeContentPhotons_cfi import *

process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = options['GLOBALTAG']

process.load('FWCore.MessageService.MessageLogger_cfi')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(options['INPUT_FILE_NAME']),
                            eventsToProcess = options['EVENTSToPROCESS']
                            )

process.maxEvents = cms.untracked.PSet( input = options['MAXEVENTS'])

###################################################################
## ID
###################################################################

from PhysicsTools.TagAndProbe.photonIDModules_cfi import *
setIDs(process, options)

###################################################################
## SEQUENCES
###################################################################

process.egmPhotonIDs.physicsObjectSrc = cms.InputTag("photonFromDiPhotons")

process.pho_sequence = cms.Sequence(
    process.photonFromDiPhotons +
    process.goodPhotonTags +
    process.goodPhotonProbes +
    process.goodPhotonProbesIDMVA +
    process.goodPhotonTagsIDMVA +
    process.goodPhotonProbesL1 +
    process.goodPhotonProbesPreselection +
    process.goodPhotonTagsPreselection +
    process.goodPhotonsTagLeadMatch +
    process.goodPhotonsTagLeadMatchPre +
    process.goodPhotonProbesHLT +
    process.goodPhotonsTagHLT +
    process.goodPhotonsProbeHLT +
    process.goodPhotonsTagHLTpre +
    process.goodPhotonsProbeHLTpre 

    )

###################################################################
## TnP PAIRS
###################################################################

process.allTagsAndProbes = cms.Sequence()
process.allTagsAndProbes *= process.tagL1RECO
process.allTagsAndProbes *= process.tagHLTRECO
process.allTagsAndProbes *= process.tagHLTpreRECO

process.mc_sequence = cms.Sequence()

if (isMC):
    process.mc_sequence *= (process.McMatchTag + process.McMatchRECO)

##########################################################################
## TREE MAKER OPTIONS
##########################################################################
if (not isMC):
    mcTruthCommonStuff = cms.PSet(
        isMC = cms.bool(False)
        )
    
process.PhotonToRECO = cms.EDAnalyzer("TagProbeFitTreeProducer",
                                      mcTruthCommonStuff, CommonStuffForPhotonProbe,
                                      tagProbePairs = cms.InputTag("tagHLTRECO"),
                                      #tagProbePairs = cms.InputTag("tagL1RECO"),
                                      arbitration   = cms.string("None"),
                                      flags         = cms.PSet(passingPresel  = cms.InputTag("goodPhotonProbesPreselection"),
                                                               passingHLT     = cms.InputTag("goodPhotonProbesHLT"),
                                                               ),                                               
                                      allProbes     = cms.InputTag("goodPhotonsProbeHLT"),
                                      )

process.PhotonToRECOpre = cms.EDAnalyzer("TagProbeFitTreeProducer",
                                      mcTruthCommonStuff, CommonStuffForPhotonProbe,
                                      tagProbePairs = cms.InputTag("tagHLTpreRECO"),
                                      #arbitration   = cms.string("None"),
                                      arbitration   = cms.string("OneProbe"),
                                      flags         = cms.PSet(passingHLTpre     = cms.InputTag("goodPhotonProbesHLT"),
                                                               ),                                               
                                      allProbes     = cms.InputTag("goodPhotonsProbeHLTpre"),
                                      )

if (isMC):
    process.PhotonToRECO.probeMatches  = cms.InputTag("McMatchRECO")
    process.PhotonToRECO.eventWeight   = cms.InputTag("generator")
    process.PhotonToRECO.PUWeightSrc   = cms.InputTag("pileupReweightingProducer","pileupWeights")
    process.PhotonToRECO.variables.Pho_dRTau  = cms.InputTag("GsfDRToNearestTauProbe")
    process.PhotonToRECO.tagVariables.probe_dRTau    = cms.InputTag("GsfDRToNearestTauProbe")

process.tree_sequence = cms.Sequence(process.PhotonToRECO)

process.tree_sequence2 = cms.Sequence(process.PhotonToRECOpre)

##########################################################################
## PATHS
##########################################################################

process.out = cms.OutputModule("PoolOutputModule", 
                               fileName = cms.untracked.string(options['OUTPUTEDMFILENAME']),
                               SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("p"))
                               )
process.outpath = cms.EndPath(process.out)
if (not options['DEBUG']):
    process.outpath.remove(process.out)

##########################################################################################
###### MICROAOD STUFF
##########################################################################################

process.load("flashgg/Taggers/flashggDiPhotonMVA_cfi")
process.flashggDiPhotonMVA.DiPhotonTag = cms.InputTag('flashggDiPhotons')

if (isMC):
    process.p = cms.Path(
        process.flashggDiPhotonMVA +
        process.sampleInfo +
        process.hltFilter +
        process.pho_sequence + 
        process.allTagsAndProbes +
        #process.pileupReweightingProducer +
        process.mc_sequence + 
        process.GsfDRToNearestTauProbe + 
        process.GsfDRToNearestTauTag + 
        process.tree_sequence +
        process.tree_sequence2
        )
else:
    process.p = cms.Path(
        process.flashggDiPhotonMVA +
        process.sampleInfo +
        process.hltFilter +
        process.pho_sequence + 
        process.allTagsAndProbes +
        process.mc_sequence +
        process.tree_sequence +
        process.tree_sequence2
        )

process.TFileService = cms.Service(
    "TFileService", fileName = cms.string(options['OUTPUT_FILE_NAME']),
    closeFileFast = cms.untracked.bool(True)
    )

# import flashgg customization
from flashgg.MetaData.JobConfig import customize
# set default options if needed
customize.setDefault("maxEvents",-1)
customize.setDefault("targetLumi",10e+3)
# call the customization
customize(process)
