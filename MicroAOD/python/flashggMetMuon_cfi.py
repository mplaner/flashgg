#-----------J. Tao from IHEP-Beijing--------------

import FWCore.ParameterSet.Config as cms

flashggMuonMets = cms.EDProducer('FlashggMetMuonProducer',
                                  patMetTag=cms.InputTag('slimmedMETs'),
                                  flashggMetTag=cms.InputTag('flashggMETs'), 
                                  diMuonTag=cms.InputTag('flashggDiMuons'), 
                                  )
