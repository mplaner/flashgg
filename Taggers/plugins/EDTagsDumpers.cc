#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h"

#include "flashgg/Taggers/interface/TagsDumpers.h"

typedef edm::AnalyzerWrapper<flashgg::CutBasedUntaggedTagDumper> CutBasedUntaggedTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedVBFTagDumper> CutBasedVBFTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedTTHLeptonicTagDumper> CutBasedTTHLeptonicTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedTTHHadronicTagDumper> CutBasedTTHHadronicTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedWHLeptonicTagDumper> CutBasedWHLeptonicTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedVHMetTagDumper> CutBasedVHMetTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedZHLeptonicTagDumper> CutBasedZHLeptonicTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedVHHadronicTagDumper> CutBasedVHHadronicTagDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedZPlusJetTagDumper> CutBasedZPlusJetTagDumper;

DEFINE_FWK_MODULE( CutBasedUntaggedTagDumper );
DEFINE_FWK_MODULE( CutBasedVBFTagDumper );
DEFINE_FWK_MODULE( CutBasedTTHLeptonicTagDumper );
DEFINE_FWK_MODULE( CutBasedTTHHadronicTagDumper );
DEFINE_FWK_MODULE( CutBasedWHLeptonicTagDumper );
DEFINE_FWK_MODULE( CutBasedZHLeptonicTagDumper );
DEFINE_FWK_MODULE( CutBasedVHMetTagDumper );
DEFINE_FWK_MODULE( CutBasedVHHadronicTagDumper );
DEFINE_FWK_MODULE( CutBasedZPlusJetTagDumper );

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
