#ifndef FLASHgg_MuonMet_h
#define FLASHgg_MuonMet_h

#include "flashgg/DataFormats/interface/DiMuonCandidate.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"
#include "flashgg/DataFormats/interface/Met.h"
#include "flashgg/DataFormats/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"

namespace flashgg {

    class MuonMet : public reco::LeafCandidate, public WeightedObject
    {
        
    public:
        MuonMet();
        MuonMet( edm::Ptr<flashgg::Met>, edm::Ptr<pat::MET>, edm::Ptr<flashgg::DiMuonCandidate> );
        ~MuonMet();
        
        
        const edm::Ptr<flashgg::DiMuonCandidate> dimuon() const{return dimuon_;}
        const edm::Ptr<flashgg::Met>         flashggMET() const{return flashggmet_;}
        const edm::Ptr<pat::MET>                 patMET() const{return patmet_;}
                
    private:
        edm::Ptr<flashgg::DiMuonCandidate>     dimuon_;
        edm::Ptr<flashgg::Met>             flashggmet_;
        edm::Ptr<pat::MET>                     patmet_;
    };
}

#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

