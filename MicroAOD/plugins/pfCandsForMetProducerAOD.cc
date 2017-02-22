// system include files
#include <memory>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "flashgg/DataFormats/interface/DiMuonCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

using namespace std;
using namespace edm;

namespace flashgg {

    class PatForMetProducer : public edm::EDProducer
    {
    public:
        PatForMetProducer( const edm::ParameterSet & );

    private:
        void produce( edm::Event &, const edm::EventSetup & );
        edm::EDGetTokenT<View<pat::PackedCandidate> > pfcandidateToken_;
        edm::EDGetTokenT<View<flashgg::DiMuonCandidate> > diMuonToken_;
        edm::EDGetTokenT<View<reco::GenParticle> > genParticleToken_;
    };

    PatForMetProducer::PatForMetProducer( const ParameterSet &iConfig ):
        pfcandidateToken_( consumes<View<pat::PackedCandidate> >( iConfig.getParameter<InputTag> ( "pfCandidatesTag" ) ) ),
        diMuonToken_( consumes<View<flashgg::DiMuonCandidate> >( iConfig.getParameter<InputTag>( "diMuonTag" ) ) ),
        genParticleToken_( consumes<View<reco::GenParticle> >( iConfig.getParameter<InputTag> ( "GenParticleTag" ) ) )
    {
        produces<vector<pat::PackedCandidate> >();
        //produces<vector<flashgg::DiMuonCandidate>>().setBranchAlias("diMuonsforMET");
    }

    void PatForMetProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<pat::PackedCandidate> > pfcandidates;
        evt.getByToken( pfcandidateToken_, pfcandidates );
        Handle<View<flashgg::DiMuonCandidate> >  dmuons;
        evt.getByToken( diMuonToken_, dmuons );
        const std::vector<edm::Ptr<pat::PackedCandidate> > &pfcands = pfcandidates->ptrs();
        std::auto_ptr<vector<pat::PackedCandidate> > muColl( new vector<pat::PackedCandidate> );
        //        std::auto_ptr<vector<flashgg::DiMuonCandidate> > diMuonColl( new vector<flashgg::DiMuonCandidate> );
        

        //        std::auto_ptr<vector<flashgg::DiMuonCandidate> > dimuons( new vector<flashgg::DiMuonCandidate> );
        /*
        Handle<View<reco::GenParticle> > genParticles;
        int genID=-1;
        if( ! evt.isRealData() )
            {
                evt.getByToken( genParticleToken_, genParticles );
                for( unsigned int genLoop = 0 ; genLoop < genParticles->size(); genLoop++ )
                    {
                        int pdgid = genParticles->ptrAt( genLoop )->pdgId();
                        if(pdgid ==23) //z-boson                                                                                                                                                      
                            {
                                if( genParticles->ptrAt( genLoop )->numberOfDaughters()==2&&fabs(genParticles->ptrAt(genLoop)->daughter(0)->pdgId())==13) //tag muons from Z-boson                    
                                    {
                                        genID=genLoop;
                                    }
                            }

                    }
            }

        if(genID>-1 && fabs(genParticles->ptrAt(genID)->daughter(0)->eta())<2.4&& fabs(genParticles->ptrAt(genID)->daughter(1)->eta())<2.4)
            std::cout  << "generator muons " << std::endl;
            //std::cout << "gen muons eta1: " << genParticles->ptrAt(genID)->daughter(0)->eta() << "  eta2: " << genParticles->ptrAt(genID)->daughter(1)->eta() << std::endl;
        */
        float bestmuonmass=0;
        unsigned int bestmuonindex = 0;
        bool goodDiMuons = false;
        if(dmuons->size()>0)
            {
                //find muon pair with closest mass to Z.
                for( unsigned int muIndex = 0; muIndex <dmuons->size(); muIndex++)
                    {
                        //std::cout << "dimuon mass: " << dmuons->ptrAt(muIndex)->mass() << std::endl;
                        if(!dmuons->ptrAt( muIndex )->IfBothTightMu())
                            continue;
                        //std::cout << "both tight muons " << std::endl;
                        if(dmuons->ptrAt( muIndex )->mass()>70&&dmuons->ptrAt( muIndex )->mass()<110)
                            if(fabs(dmuons->ptrAt( muIndex )->mass()-91.2)<fabs(bestmuonmass-91.2))
                                {
                                    bestmuonmass = dmuons->ptrAt( muIndex )->mass();
                                    bestmuonindex = muIndex;
                                    goodDiMuons = true;
                                }
                    }
            }
        //if(bestmuonmass>0)
        //   std::cout << "Best muons eta1: " << dmuons->ptrAt(bestmuonindex)->leadingMuon()->eta() << "  eta2: " << dmuons->ptrAt(bestmuonindex)->subleadingMuon()->eta()  << std::endl;
        //        flashgg::DiMuonCandidate dimuon = flashgg::DiMuonCandidate(*dmuons->ptrAt(bestmuonindex));
        //        diMuonColl->push_back(dimuon);
        //diMuonColl->push_back(dmuons->ptrAt(bestmuonindex));
        //        if(bestmuonmass>0)
        //  std::cout << "Best muons pt1: " << dmuons->ptrAt(bestmuonindex)->leadingMuon()->pt() << "  pt2: " << dmuons->ptrAt(bestmuonindex)->subleadingMuon()->pt()  << std::endl;
        for( unsigned int ipfc = 0 ; ipfc < pfcands.size() ; ipfc++ ) 
            {
                //Ptr<pat::PackedCandidate> ppfc = pfcands.ptrAt( ipfc );
                Ptr<pat::PackedCandidate> ppfc = pfcands[ ipfc ];
                pat::PackedCandidate pfc = pat::PackedCandidate( *ppfc);
                //make muon candidates
                if(goodDiMuons && fabs(ppfc->pdgId())==13 && ppfc->pt()>10 &&
                   (deltaR(ppfc->p4(),dmuons->ptrAt(bestmuonindex)->leadingMuon()->p4())<0.1||deltaR(ppfc->p4(),dmuons->ptrAt(bestmuonindex)->subleadingMuon()->p4())<0.1))
                    {
                        //std::cout << "dimuon pT: " << dmuons->ptrAt(bestmuonindex)->pt() << std::endl;
                        //std::cout << "dimuon mass: " << dmuons->ptrAt(bestmuonindex)->mass() << std::endl;
                        //std::cout << "pT : " << ppfc->pt() << std::endl;
                        //continue;  //skip objects which match Z->mumu
                        //muColl->push_back(pfc);
                    }
                else
                    {
                        muColl->push_back(pfc);
                    }
            }
        //if(dmuons->size()>0)
        evt.put( muColl );
        //evt.put( diMuonColl );
    }
}

typedef flashgg::PatForMetProducer FlashggPatForMetProducer;
DEFINE_FWK_MODULE( FlashggPatForMetProducer );

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

