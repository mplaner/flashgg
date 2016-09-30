#ifndef flashgg_TagsDumpers_h
#define flashgg_TagsDumpers_h

#include "flashgg/DataFormats/interface/UntaggedTag.h"
#include "flashgg/DataFormats/interface/VBFTag.h"
#include "flashgg/DataFormats/interface/TTHLeptonicTag.h"
#include "flashgg/DataFormats/interface/TTHHadronicTag.h"
#include "flashgg/DataFormats/interface/VHMetTag.h"
#include "flashgg/DataFormats/interface/WHLeptonicTag.h"
#include "flashgg/DataFormats/interface/ZHLeptonicTag.h"
#include "flashgg/DataFormats/interface/VHHadronicTag.h"
#include "flashgg/DataFormats/interface/ZPlusJetTag.h"

#include "flashgg/Taggers/interface/CollectionDumper.h"

namespace flashgg {
    typedef CollectionDumper<std::vector<UntaggedTag>,
            UntaggedTag,
            CutBasedClassifier<UntaggedTag> > CutBasedUntaggedTagDumper;
    typedef CollectionDumper<std::vector<VBFTag>,
            VBFTag,
            CutBasedClassifier<VBFTag> > CutBasedVBFTagDumper;
    typedef CollectionDumper<std::vector<TTHLeptonicTag>,
            TTHLeptonicTag,
            CutBasedClassifier<TTHLeptonicTag> > CutBasedTTHLeptonicTagDumper;
    typedef CollectionDumper<std::vector<TTHHadronicTag>,
            TTHHadronicTag,
            CutBasedClassifier<TTHHadronicTag> > CutBasedTTHHadronicTagDumper;
    typedef CollectionDumper<std::vector<VHMetTag>,
            VHMetTag,
            CutBasedClassifier<VHMetTag> > CutBasedVHMetTagDumper;
    typedef CollectionDumper<std::vector<WHLeptonicTag>,
            WHLeptonicTag,
            CutBasedClassifier<WHLeptonicTag> > CutBasedWHLeptonicTagDumper;
    typedef CollectionDumper<std::vector<ZHLeptonicTag>,
            ZHLeptonicTag,
            CutBasedClassifier<ZHLeptonicTag> > CutBasedZHLeptonicTagDumper;
    typedef CollectionDumper<std::vector<VHHadronicTag>,
            VHHadronicTag,
            CutBasedClassifier<VHHadronicTag> > CutBasedVHHadronicTagDumper;
    typedef CollectionDumper<std::vector<ZPlusJetTag>,
            ZPlusJetTag,
            CutBasedClassifier<ZPlusJetTag> > CutBasedZPlusJetTagDumper;
}

#endif

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
