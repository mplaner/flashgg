#-----------J. Tao from IHEP-Beijing--------------

import FWCore.ParameterSet.Config as cms

flashggDiMuons = cms.EDProducer('FlashggDiMuonProducer',
                                  MuonTag=cms.InputTag('flashggSelectedMuons'),
                                  VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'), 
                                  ##Parameters                                                
                                  minMuonPT=cms.double(10.),
                                  maxMuonEta=cms.double(2.4)
                                  )
