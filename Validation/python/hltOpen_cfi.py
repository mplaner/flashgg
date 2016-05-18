import FWCore.ParameterSet.Config as cms

hltopenanalysis = cms.EDAnalyzer("HLTOpen",
                                 
                                 HLTProcessName                  = cms.string("TEST"),
                                 Rho                             = cms.InputTag("fixedGridRhoAll"),
                                 DiPhotons                       = cms.InputTag("flashggPreselectedDiPhotons"),
                                 #DiPhotons                       = cms.InputTag("flashggDiPhotons"),
                                 ECALActivity                    = cms.InputTag("hltEgammaCandidatesUnseeded"),
                                 ActivityEcalIso                 = cms.InputTag("hltEgammaEcalPFClusterIsoUnseeded"),
                                 ActivityTrackIso                = cms.InputTag("hltEgammaHollowTrackIsoUnseeded"),
                                 ActivityR9                      = cms.InputTag("hltEgammaR9IDUnseeded"), 
                                 ActivityHcalForHoverE           = cms.InputTag("hltEgammaHToverETUnseeded")
                                 )
