import FWCore.ParameterSet.Config as cms


flashggMetsMuons = cms.EDProducer('FlashggMetProducer',
                             verbose = cms.untracked.bool(False),
                             metTag = cms.InputTag('slimmedMETs'),
                             )

flashggMetsEG = cms.EDProducer('FlashggMetProducer',
                             verbose = cms.untracked.bool(False),
                             metTag = cms.InputTag('slimmedMETsEGClean'),
                             )
flashggMetsEGmuon = cms.EDProducer('FlashggMetProducer',
                             verbose = cms.untracked.bool(False),
                             #metTag = cms.InputTag('slimmedMETsMuEGClean'),
                             #metTag = cms.InputTag('slimmedMETsMuEGClean:FLASHggMicroAOD'),
                             metTag = cms.InputTag('slimmedMETsFullMETClean'),
                             )
flashggMets = cms.EDProducer('FlashggMetProducer',
                             verbose = cms.untracked.bool(False),
                             metTag = cms.InputTag('slimmedMETsMuEGClean'),
                             )
flashggMetsUncorr = cms.EDProducer('FlashggMetProducer',
                             verbose = cms.untracked.bool(False),
                             metTag = cms.InputTag('slimmedMETsUncorrected'),
                             )

