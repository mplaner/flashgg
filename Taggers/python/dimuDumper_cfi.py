#-----------J. Tao from IHEP-Beijing--------------

import FWCore.ParameterSet.Config as cms

from flashgg.Taggers.dimuDumpConfig_cff import dimuDumpConfig,metDumpConfig

dimuDumper = cms.EDAnalyzer('CutBasedDiMuonDumper',
                                **dimuDumpConfig.parameters_()
                                )

metDumper = cms.EDAnalyzer('CutBasedMETDumper',
                                **metDumpConfig.parameters_()
                                )
