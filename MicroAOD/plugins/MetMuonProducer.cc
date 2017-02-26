// system include files
#include <memory>
// user include file
#include "flashgg/DataFormats/interface/MuonMet.h"
//#include "DataFormats/PatCandidates/interface/MET.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

namespace flashgg {

    class MetMuonProducer : public edm::EDProducer
    {
    public:
        MetMuonProducer( const edm::ParameterSet & );

    private:
        void produce( edm::Event &, const edm::EventSetup & );

        edm::EDGetTokenT<edm::View<pat::MET> > metToken_;
        edm::EDGetTokenT<edm::View<flashgg::Met> > flashggMetToken_;
        edm::EDGetTokenT<edm::View<flashgg::DiMuonCandidate> > dimuonToken_;
    };

    MetMuonProducer::MetMuonProducer( const edm::ParameterSet &iConfig ):
        metToken_( consumes<edm::View<pat::MET> >( iConfig.getParameter<edm::InputTag>( "patMetTag" ) ) ),
        flashggMetToken_( consumes<edm::View<flashgg::Met> >( iConfig.getParameter<edm::InputTag>( "flashggMetTag" ) ) ),
        dimuonToken_( consumes<edm::View<flashgg::DiMuonCandidate> >( iConfig.getParameter<edm::InputTag>( "diMuonTag" ) ) )
    {
        produces<vector<flashgg::MuonMet> >();
    }

    void MetMuonProducer::produce( edm::Event &evt, const edm::EventSetup & )
    {
        edm::Handle<edm::View<pat::MET> >  pmets;
        evt.getByToken( metToken_, pmets );
        edm::Handle<edm::View<flashgg::Met> >  fmets;
        evt.getByToken( flashggMetToken_, fmets );
        edm::Handle<edm::View<flashgg::DiMuonCandidate> >  dimu;
        evt.getByToken( dimuonToken_, dimu );
        
        std::auto_ptr<vector<flashgg::MuonMet> > metColl( new vector<flashgg::MuonMet> );

        if(pmets->size()==1&&fmets->size()==1&&dimu->size()==1)
            {
                edm::Ptr<pat::MET>                  pmet = pmets->ptrAt( 0 );
                edm::Ptr<flashgg::Met>            fggmet = fmets->ptrAt( 0 );
                edm::Ptr<flashgg::DiMuonCandidate> fdimu =  dimu->ptrAt( 0 );
                
                flashgg::MuonMet fmet = flashgg::MuonMet(fggmet, pmet,fdimu );
                metColl->push_back(fmet);
            }
        evt.put(metColl );
    }
}

typedef flashgg::MetMuonProducer FlashggMetMuonProducer;
DEFINE_FWK_MODULE( FlashggMetMuonProducer );

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

