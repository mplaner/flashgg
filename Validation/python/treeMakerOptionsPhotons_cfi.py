import FWCore.ParameterSet.Config as cms

def setModules(process, options):

    process.sampleInfo = cms.EDAnalyzer("tnp::SampleInfoTree",
                                        vertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                        genInfo = cms.InputTag("generator")
                                        )

    from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
    process.hltFilter = hltHighLevel.clone()
    process.hltFilter.throw = cms.bool(True)
    process.hltFilter.HLTPaths = options['TnPPATHS']
    
    process.pileupReweightingProducer = cms.EDProducer("PileupWeightProducer",
                                                       hardcodedWeights = cms.untracked.bool(True)
                                                       )
    
    process.GsfDRToNearestTauProbe = cms.EDProducer("DeltaRNearestGenPComputer",
                                                    probes = cms.InputTag("photonFromDiPhotons"),
                                                    objects = cms.InputTag('flashggPrunedGenParticles'),
                                                    objectSelection = cms.string("abs(pdgId)==15"),
                                                    )
    
    process.GsfDRToNearestTauSC = cms.EDProducer("DeltaRNearestGenPComputer",
                                                 probes = cms.InputTag("superClusterCands"),
                                                 objects = cms.InputTag('flashggPrunedGenParticles'),
                                                 objectSelection = cms.string("abs(pdgId)==15"),
                                                 )
    
    process.GsfDRToNearestTauTag = cms.EDProducer("DeltaRNearestGenPComputer",
                                                  probes = cms.InputTag("photonFromDiPhotons"),
                                                  objects = cms.InputTag('flashggPrunedGenParticles'),
                                                  objectSelection = cms.string("abs(pdgId)==15"),
                                                  )
    ###################################################################
    ## ELECTRON MODULES
    ###################################################################
    
    #produces photons for tag+probe
    process.photonFromDiPhotons = cms.EDProducer("FlashggPhotonFromDiPhotonProducer",
                                                 src = cms.InputTag(options['DIPHOTON_COLL']),
                                                 cut = cms.string(options['PHOTON_CUTS']),
                                                 leadingPreselection = cms.string(options['LEADING_PRESELECTION']),
                                                 subleadingPreselection = cms.string(options['SUBLEADING_PRESELECTION']),
                                                 vertexSelection = cms.int32(-1), # -1 means take the chosen vertex, otherwise use the index to select 2it
                                                 diPhotonMVATag = cms.InputTag("flashggDiPhotonMVA"),
                                                 diphotonMVAThreshold = cms.double(-0.6)
                                                 )
    
    #produces tag collection matching to l1
    process.goodPhotonTagL1 = cms.EDProducer("FlashggPhotonL1CandProducer",
                                             inputs = cms.InputTag("goodPhotonTags"),
                                             isoObjects = cms.InputTag("goodPhotonTags"),
                                             nonIsoObjects = cms.InputTag(""),
                                             minET = cms.double(25),
                                             dRmatch = cms.double(0.2),
                                             isolatedOnly = cms.bool(False)
                                             )
    #produces tag collection from diphotons
    process.goodPhotonTags = cms.EDFilter("FlashggPhotonRefSelector",
                                          src = cms.InputTag("photonFromDiPhotons"),
                                          cut = cms.string(options['PHOTON_TAG_CUTS'])
                                          )
    
    #produces probe collection from diphotons
    process.goodPhotonProbes = cms.EDFilter("FlashggPhotonRefSelector",
                                            src = cms.InputTag("photonFromDiPhotons"),
                                            cut = cms.string(options['PHOTON_PROBE_CUTS'])
                                            )
    
    ###################################################################
    
    #IDMVA for probes
    process.goodPhotonProbesIDMVA = cms.EDProducer("FlashggPhotonSelectorByDoubleValueMap",
                                                   input     = cms.InputTag("goodPhotonProbes"),
                                                   cut       = cms.string(options['PHOTON_PROBE_CUTS']),
                                                   selection = cms.InputTag("photonFromDiPhotons:idmva"),
                                                   id_cut    = cms.double(-0.8)
                                                   )
    #numerator for Preselection
    process.goodPhotonProbesPreselection = cms.EDProducer("FlashggPhotonSelectorByValueMap",
                                                          input     = cms.InputTag("goodPhotonProbesL1"),
                                                          cut       = cms.string(options['PHOTON_PROBE_CUTS']),
                                                          selection = cms.InputTag("photonFromDiPhotons:preselection"),
                                                          id_cut    = cms.bool(True)
                                                          )
    #numerator passing HLT
    process.goodPhotonProbesHLT = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                                 filterNames = options['HLTFILTERTOMEASURE'],
                                                 inputs      = cms.InputTag("goodPhotonProbesIDMVA"),
                                                 bits        = cms.InputTag('TriggerResults::HLT'),
                                                 objects     = cms.InputTag('selectedPatTrigger'),
                                                 dR          = cms.double(0.3),
                                                 isAND       = cms.bool(False)
                                                 )

    #numerator passing HLT requiring preselection
    process.goodPhotonProbesHLTpre = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                                 filterNames = options['HLTFILTERTOMEASURE'],
                                                 inputs      = cms.InputTag("goodPhotonProbesPreselection"),
                                                 bits        = cms.InputTag('TriggerResults::HLT'),
                                                 objects     = cms.InputTag('selectedPatTrigger'),
                                                 dR          = cms.double(0.3),
                                                 isAND       = cms.bool(False)
                                                 )
    

    #IDMVA for tags
    process.goodPhotonTagsIDMVA = cms.EDProducer("FlashggPhotonSelectorByDoubleValueMap",
                                                 input     = cms.InputTag("goodPhotonTags"),
                                                 cut       = cms.string(options['PHOTON_TAG_CUTS']),
                                                 selection = cms.InputTag("photonFromDiPhotons:idmva"),
                                                 id_cut    = cms.double(-0.5)
                                                 )
    #preselection for tags
    process.goodPhotonTagsPreselection = cms.EDProducer("FlashggPhotonSelectorByValueMap",
                                                          input     = cms.InputTag("goodPhotonTagsIDMVA"),
                                                          cut       = cms.string(options['PHOTON_TAG_CUTS']),
                                                          selection = cms.InputTag("photonFromDiPhotons:preselection"),
                                                          id_cut    = cms.bool(True)
                                                          )

    
    ###################################################################

    #good match to lead HggFilter tag photons for denominator
    process.goodPhotonsTagLeadMatch = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                              filterNames = options['TagLeadMatchFilters'],
                                              inputs      = cms.InputTag("goodPhotonTagsIDMVA"),
                                              bits        = cms.InputTag('TriggerResults::HLT'),
                                              objects     = cms.InputTag('selectedPatTrigger'),
                                              dR          = cms.double(0.3),
                                              isAND       = cms.bool(False)
                                              )

    #good match to lead HggFilter tag photons for denominator PRESELECTED
    process.goodPhotonsTagLeadMatchPre = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                                        filterNames = options['TagLeadMatchFilters'],
                                                        inputs      = cms.InputTag("goodPhotonTagsPreselection"),
                                                        bits        = cms.InputTag('TriggerResults::HLT'),
                                                        objects     = cms.InputTag('selectedPatTrigger'),
                                                        dR          = cms.double(0.3),
                                                        isAND       = cms.bool(False)
                                                        )
    #good tag photons for denominator
    process.goodPhotonsTagHLT = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                               filterNames = options['TnPHLTTagFilters'],
                                               #inputs      = cms.InputTag("goodPhotonTagsIDMVA"),
                                               inputs      = cms.InputTag("goodPhotonsTagLeadMatch"),
                                               bits        = cms.InputTag('TriggerResults::HLT'),
                                               objects     = cms.InputTag('selectedPatTrigger'),
                                               dR          = cms.double(0.3),
                                               isAND       = cms.bool(False)
                                               )
    #good preselected tag photons for denominator
    process.goodPhotonsTagHLTpre = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                                  filterNames = options['TnPHLTTagFilters'],
                                                  #inputs      = cms.InputTag("goodPhotonTagsPreselection"),
                                                  inputs      = cms.InputTag("goodPhotonsTagLeadMatchPre"),
                                                  bits        = cms.InputTag('TriggerResults::HLT'),
                                                  objects     = cms.InputTag('selectedPatTrigger'),
                                                  dR          = cms.double(0.3),
                                                  isAND       = cms.bool(False)
                                                  )

        
    #good probe photons for denominator
    process.goodPhotonsProbeHLT = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                                 filterNames = options['TnPHLTProbeFilters'],
                                                 inputs      = cms.InputTag("goodPhotonProbesL1"),
                                                 bits        = cms.InputTag('TriggerResults::HLT'),
                                                 objects     = cms.InputTag('selectedPatTrigger'),
                                                 dR          = cms.double(0.3),
                                                 isAND       = cms.bool(False)
                                                 )
        
    #preselected photons for denominator
    process.goodPhotonsProbeHLTpre = cms.EDProducer("FlashggPhotonTriggerCandProducer",
                                                 filterNames = options['TnPHLTProbeFilters'],
                                                 inputs      = cms.InputTag("goodPhotonProbesPreselection"),
                                                 bits        = cms.InputTag('TriggerResults::HLT'),
                                                 objects     = cms.InputTag('selectedPatTrigger'),
                                                 dR          = cms.double(0.3),
                                                 isAND       = cms.bool(False)
                                                 )
    #probes match to l1
    process.goodPhotonProbesL1 = cms.EDProducer("FlashggPhotonL1CandProducer",
                                                inputs = cms.InputTag("goodPhotonProbesIDMVA"),
                                                isoObjects = cms.InputTag("l1extraParticles:Isolated"),
                                                nonIsoObjects = cms.InputTag("l1extraParticles:NonIsolated"),
                                                #minET = cms.double(22), #lead eff only
                                                minET = cms.double(10), #sublead eff only
                                                dRmatch = cms.double(0.2),
                                                isolatedOnly = cms.bool(False)
                                                )
    
    ###################################################################
    ## PHOTON ISOLATION
    ###################################################################
    process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")

    process.tagL1RECO = cms.EDProducer("CandViewShallowCloneCombiner",
                                      decay = cms.string("goodPhotonsTagHLT goodPhotonProbesL1"), 
                                      checkCharge = cms.bool(False),
                                      cut = cms.string("60<mass<120"),
                                      )

    #efficiency for HLT convolved with L1
    process.tagHLTRECO = cms.EDProducer("CandViewShallowCloneCombiner",
                                        decay = cms.string("goodPhotonsTagHLT goodPhotonsProbeHLT"), 
                                        checkCharge = cms.bool(False),
                                        cut = cms.string("60<mass<120"),
                                        )

    #efficiency for HLT convolved with L1
    process.tagHLTpreRECO = cms.EDProducer("CandViewShallowCloneCombiner",
                                        decay = cms.string("goodPhotonsTagHLTpre goodPhotonsProbeHLTpre"), 
                                        checkCharge = cms.bool(False),
                                        cut = cms.string("60<mass<120"),
                                        )
    
    
    ###################################################################
    ## MC MATCHING
    ###################################################################

    process.McMatchTag = cms.EDProducer("MCTruthDeltaRMatcherNew",
                                        matchPDGId = cms.vint32(11),
                                        src = cms.InputTag("goodPhotonTags"),
                                        distMin = cms.double(0.2),
                                        matched = cms.InputTag("flashggPrunedGenParticles"),
                                        checkCharge = cms.bool(False)
                                        )
    
    process.McMatchRECO = cms.EDProducer("MCTruthDeltaRMatcherNew",
                                         matchPDGId = cms.vint32(11),
                                         src = cms.InputTag("goodPhotonProbes"),
                                         distMin = cms.double(0.2),
                                         matched = cms.InputTag("flashggPrunedGenParticles"),
                                         checkCharge = cms.bool(False)
                                         )
