import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
usePrivateSQlite=True

if usePrivateSQlite:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    import os


#============================================Apply MET correction and syst.=================================================#

def runMETs(process,isMC):
    #================================ Get the most recent JEC ==================================================================#
    # Setup the private SQLite -- Ripped from PhysicsTools/PatAlgos/test/corMETFromMiniAOD.py
    era = "Fall15_25nsV2"
    if isMC : 
        era += "_MC"
    else :
        era += "_DATA"
    dBFile = os.path.expandvars("flashgg/MicraAOD/data/"+era+".db")

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
                                   jetCollUnskimmed="slimmedJets",
                                   electronColl="slimmedElectrons",
                                   photonColl="slimmedPhotons",
                                   muonColl="slimmedMuons",
                                   tauColl="slimmedTaus",
                                   reclusterJets = False,
                                   pfCandColl = "packedPFCandidates",
                                   postfix="",
                                   isData=True,
                                   )
        
#===========================================================================================================================#
