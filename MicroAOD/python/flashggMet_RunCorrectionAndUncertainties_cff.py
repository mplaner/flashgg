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
                            postfix="MuEGClean"
                            )
        
        process.slimmedMETsMuEGClean = process.slimmedMETs.clone()
        process.slimmedMETsMuEGClean.src = cms.InputTag("patPFMetT1MuEGClean")
        process.slimmedMETsMuEGClean.rawVariation =  cms.InputTag("patPFMetRawMuEGClean")
        process.slimmedMETsMuEGClean.t1Uncertainties = cms.InputTag("patPFMetT1%sMuEGClean")
        del process.slimmedMETsMuEGClean.caloMET
        
        process.egcorrMET = cms.Sequence(
            process.cleanedPhotonsMuEGClean+process.cleanedCorPhotonsMuEGClean+
            process.matchedPhotonsMuEGClean + process.matchedElectronsMuEGClean +
            process.corMETPhotonMuEGClean+process.corMETElectronMuEGClean+
            process.patPFMetT1MuEGClean+process.patPFMetRawMuEGClean+
            process.patPFMetT1SmearMuEGClean+process.patPFMetT1TxyMuEGClean+
            process.patPFMetTxyMuEGClean+process.patPFMetT1JetEnUpMuEGClean+
            process.patPFMetT1JetResUpMuEGClean+process.patPFMetT1SmearJetResUpMuEGClean+
            process.patPFMetT1ElectronEnUpMuEGClean+process.patPFMetT1PhotonEnUpMuEGClean+
            process.patPFMetT1MuonEnUpMuEGClean+process.patPFMetT1TauEnUpMuEGClean+
            process.patPFMetT1UnclusteredEnUpMuEGClean+process.patPFMetT1JetEnDownMuEGClean+
            process.patPFMetT1JetResDownMuEGClean+process.patPFMetT1SmearJetResDownMuEGClean+
            process.patPFMetT1ElectronEnDownMuEGClean+process.patPFMetT1PhotonEnDownMuEGClean+
            process.patPFMetT1MuonEnDownMuEGClean+process.patPFMetT1TauEnDownMuEGClean+
            process.patPFMetT1UnclusteredEnDownMuEGClean+process.slimmedMETsMuEGClean)
#===========================================================================================================================#

def setMetCorr(process, metCorr):
    
    process.pfMEtMultShiftCorr.parameters                 = metCorr
    process.patPFMetTxyCorr.parameters                    = metCorr
   
