import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG


from os import environ
usePrivateSQlite=True

if usePrivateSQlite:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    import os


#============================================Apply MET correction and syst.=================================================#

def runMETs(process,isMC):
    #================================ Get the most recent JEC ==================================================================#
    # Setup the private SQLite -- Ripped from PhysicsTools/PatAlgos/test/corMETFromMiniAOD.py
    era = "Summer16_23Sep2016"
    if isMC : 
        era += "V4_MC"
    else :
        era += "AllV4_DATA"
        
    dBFile = os.path.expandvars(era+".db")
    
    print dBFile
    if usePrivateSQlite:
        process.jec = cms.ESSource("PoolDBESSource",
                                   CondDBSetup,
                                   connect = cms.string("sqlite_file:"+dBFile),
                                   toGet =  cms.VPSet(
                cms.PSet(
                    record = cms.string("JetCorrectionsRecord"),
                    tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PF"),
                    label= cms.untracked.string("AK4PF")
                    ),
                cms.PSet(
                        record = cms.string("JetCorrectionsRecord"),
                        tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFchs"),
                        label= cms.untracked.string("AK4PFchs")
                        ),
                )
                                   )
        process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')
#===========================================================================================================================#
        
        
        runMetCorAndUncFromMiniAOD(process, metType="PF",
                                   recoMetFromPFCs=False,
                                   postfix="",
                                   isData=(not isMC),
                                   )
        
        corMETFromMuonAndEG(process, 
                            pfCandCollection="", #not needed
                            electronCollection="slimmedElectronsBeforeGSFix",
                            photonCollection="slimmedPhotonsBeforeGSFix",
                            corElectronCollection="slimmedElectrons",
                            corPhotonCollection="slimmedPhotons",
                            allMETEGCorrected=True,
                            muCorrection=False,
                            eGCorrection=True,
                            runOnMiniAOD=True,
                            postfix="FullMETClean"
                            )
        
        process.slimmedMETsFullMETClean = process.slimmedMETs.clone()
        process.slimmedMETsFullMETClean.src = cms.InputTag("patPFMetT1FullMETClean")
        process.slimmedMETsFullMETClean.rawVariation =  cms.InputTag("patPFMetRawFullMETClean")
        process.slimmedMETsFullMETClean.t1Uncertainties = cms.InputTag("patPFMetT1%sFullMETClean")
        del process.slimmedMETsFullMETClean.caloMET
        
        process.egcorrMET = cms.Sequence(
            process.cleanedPhotonsFullMETClean+process.cleanedCorPhotonsFullMETClean+
            process.matchedPhotonsFullMETClean + process.matchedElectronsFullMETClean +
            process.corMETPhotonFullMETClean+process.corMETElectronFullMETClean+
            process.patPFMetT1FullMETClean+process.patPFMetRawFullMETClean+
            process.patPFMetT1SmearFullMETClean+process.patPFMetT1TxyFullMETClean+
            process.patPFMetTxyFullMETClean+process.patPFMetT1JetEnUpFullMETClean+
            process.patPFMetT1JetResUpFullMETClean+process.patPFMetT1SmearJetResUpFullMETClean+
            process.patPFMetT1ElectronEnUpFullMETClean+process.patPFMetT1PhotonEnUpFullMETClean+
            process.patPFMetT1MuonEnUpFullMETClean+process.patPFMetT1TauEnUpFullMETClean+
            process.patPFMetT1UnclusteredEnUpFullMETClean+process.patPFMetT1JetEnDownFullMETClean+
            process.patPFMetT1JetResDownFullMETClean+process.patPFMetT1SmearJetResDownFullMETClean+
            process.patPFMetT1ElectronEnDownFullMETClean+process.patPFMetT1PhotonEnDownFullMETClean+
            process.patPFMetT1MuonEnDownFullMETClean+process.patPFMetT1TauEnDownFullMETClean+
            process.patPFMetT1UnclusteredEnDownFullMETClean+process.slimmedMETsFullMETClean)
#===========================================================================================================================#

def setMetCorr(process, metCorr):
    
    process.pfMEtMultShiftCorr.parameters                 = metCorr
    process.patPFMetTxyCorr.parameters                    = metCorr
   
