#!/usr/bin/env cmsRun

import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.source = cms.Source("PoolSource",
                            fileNames=cms.untracked.vstring(
        "file:myMicroAODOutputFile.root"
        #"file:noMuonMicroAOD.root"
        )
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1000 )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("test_mm.root")
)


process.load("flashgg.MicroAOD.flashggMetMuon_cfi")

process.load("flashgg.Taggers.dimuDumper_cfi") ##  import mumugammaDumper 
import flashgg.Taggers.dumperConfigTools as cfgTools


#process.mumugammaDumper.src = "kinPreselDiPhotons"


process.metDumper.dumpTrees = True
process.metDumper.dumpWorkspace = False
process.metDumper.quietRooFit = True
process.metDumper.nameTemplate ="METTag"


cfgTools.addCategories(process.metDumper,
                       [("EB","",0)],
                       variables=[
                                  "Mass_mumu           :=dimuon().mass",
                                  "PT_mumu             :=dimuon().pt",
                                  "leadPt              :=dimuon().leadingMuon.pt",
                                  "subleadPt           :=dimuon().subleadingMuon.pt",
                                  "met                 :=flashggMET().pt", 
                                  "met_phi             :=flashggMET().phi", 
                                  "sumEt               :=flashggMET().sumEt"
                                  ],
                         ## histograms to be plotted. 
                       ## the variables need to be defined first
                       histograms=[]
                       )


process.p1 = cms.Path(
       process.flashggMuonMets*process.metDumper
    )



from flashgg.MetaData.JobConfig import customize
customize.setDefault("maxEvents",-1)
customize(process)

