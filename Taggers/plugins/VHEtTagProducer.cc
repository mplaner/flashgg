#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "flashgg/DataFormats/interface/VBFDiPhoDiJetMVAResult.h"
//#include "flashgg/DataFormats/interface/VBFMVAResult.h"
#include "flashgg/DataFormats/interface/VHEtTag.h"

#include "flashgg/DataFormats/interface/VHEtTagTruth.h"
#include "DataFormats/Common/interface/RefToPtr.h"

#include <vector>
#include <algorithm>

using namespace std;
using namespace edm;

namespace flashgg {

    class VHEtTagProducer : public EDProducer
    {

    public:
        typedef math::XYZPoint Point;

        VHEtTagProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;


        EDGetTokenT<View<DiPhotonCandidate> > diPhotonToken_;
        EDGetTokenT<View<DiPhotonMVAResult> > mvaResultToken_;
        EDGetTokenT<View<pat::MET> > METToken_;
        EDGetTokenT<View<reco::GenParticle> > genParticleToken_;
        string systLabel_;
        edm::InputTag photonCollection_;

        //configurable selection variables
        double leadPhoOverMassThreshold_;
        double subleadPhoOverMassThreshold_;
        double diphoMVAThreshold_;
        double metPtThreshold_;
        double phoIdMVAThreshold_;
    };

    VHEtTagProducer::VHEtTagProducer( const ParameterSet &iConfig ) :
        diPhotonToken_( consumes<View<flashgg::DiPhotonCandidate> >( iConfig.getParameter<InputTag> ( "DiPhotonTag" ) ) ),
        mvaResultToken_( consumes<View<flashgg::DiPhotonMVAResult> >( iConfig.getParameter<InputTag> ( "MVAResultTag" ) ) ),
        METToken_( consumes<View<pat::MET> >( iConfig.getParameter<InputTag> ( "METTag" ) ) ),
        genParticleToken_( consumes<View<reco::GenParticle> >( iConfig.getParameter<InputTag> ( "GenParticleTag" ) ) ),
        systLabel_( iConfig.getParameter<string> ( "SystLabel" ) )
    {
        leadPhoOverMassThreshold_    = iConfig.getParameter<double>( "leadPhoOverMassThreshold" );
        subleadPhoOverMassThreshold_ = iConfig.getParameter<double>( "subleadPhoOverMassThreshold" );
        diphoMVAThreshold_           = iConfig.getParameter<double>( "diphoMVAThreshold" );
        metPtThreshold_              = iConfig.getParameter<double>( "metPtThreshold" );
        phoIdMVAThreshold_           = iConfig.getParameter<double>( "phoIdMVAThreshold" );

        produces<vector<VHEtTag> >();
        produces<vector<VHEtTagTruth> >();
        photonCollection_=iConfig.getParameter<InputTag> ( "DiPhotonTag" );

    }

    void VHEtTagProducer::produce( Event &evt, const EventSetup & )
    {
        //        std::cout << "starting met tagger" << std::endl;
        Handle<View<flashgg::DiPhotonCandidate> > diPhotons;
        evt.getByToken( diPhotonToken_, diPhotons );



        //        std::cout << " diphoton collection " <<  photonCollection_.label() << std::endl;

        Handle<View<flashgg::DiPhotonMVAResult> > mvaResults;
        evt.getByToken( mvaResultToken_, mvaResults );

        Handle<View<pat::MET> > METs;
        evt.getByToken( METToken_, METs );

        if( METs->size() != 1 )
        { std::cout << "WARNING number of MET is not equal to 1" << std::endl; }
        Ptr<pat::MET> theMET = METs->ptrAt( 0 );

        Handle<View<reco::GenParticle> > genParticles;

        std::auto_ptr<vector<VHEtTag> > vhettags( new vector<VHEtTag> );
        std::auto_ptr<vector<VHEtTagTruth> > truths( new vector<VHEtTagTruth> );
        
        Point higgsVtx;
        bool associatedZ=0;
        bool associatedW=0;
        bool VhasDaughters=0;
        bool VhasNeutrinos=0;
        bool VhasMissingLeptons=0;
        float Vpt=0;
        
        if( ! evt.isRealData() ) {
            evt.getByToken( genParticleToken_, genParticles );
            for( unsigned int genLoop = 0 ; genLoop < genParticles->size(); genLoop++ ) 
                {
                    int pdgid = genParticles->ptrAt( genLoop )->pdgId();
                    //std::cout << "pdgID: " << pdgid << std::endl;
                    if(pdgid ==23) //z-boson
                        {
                            associatedZ=1;
                            if( genParticles->ptrAt( genLoop )->numberOfDaughters())
                                VhasDaughters=1;  
                            Vpt=genParticles->ptrAt( genLoop )->pt();
                        }
                    if(pdgid==24||pdgid==-24) //look for W
                        {
                            associatedW=1;
                            if( genParticles->ptrAt( genLoop )->numberOfDaughters())
                                VhasDaughters=1;
                            Vpt=genParticles->ptrAt( genLoop )->pt();
                        }
                    if(fabs(pdgid)==12||fabs(pdgid)==14||fabs(pdgid)==16) //look for lepton decay of W
                        {
                            if(fabs(genParticles->ptrAt( genLoop )->mother()->pdgId())==23)
                                {
                                    VhasNeutrinos=1;
                                }
                        }
                    if(fabs(pdgid==11)||fabs(pdgid)==13||fabs(pdgid)==13) //look for lepton decay of W
                        {
                            if(fabs(genParticles->ptrAt( genLoop )->mother()->pdgId())==24)
                                {
                                    if(fabs(genParticles->ptrAt( genLoop )->eta())>2.5) //lepton outside of eta range
                                        VhasMissingLeptons=1;
                                    if(fabs(genParticles->ptrAt( genLoop )->eta())>1.455&&fabs(genParticles->ptrAt( genLoop )->eta())<1.566) //lepton in gap
                                        VhasMissingLeptons=1;
                                }
                        }
                    
                    if( pdgid == 25 || pdgid == 22 ) 
                        {
                            higgsVtx = genParticles->ptrAt( genLoop )->vertex();
                            continue;
                        }
                }
        }
        
        edm::RefProd<vector<VHEtTagTruth> > rTagTruth = evt.getRefBeforePut<vector<VHEtTagTruth> >();
        unsigned int idx = 0;


        assert( diPhotons->size() ==
                mvaResults->size() ); // We are relying on corresponding sets - update this to give an error/exception
        
        //        std::cout << "has z: " << associatedZ << std::endl;
        for( unsigned int candIndex = 0; candIndex < diPhotons->size() ; candIndex++ ) {


            edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt( candIndex );
            edm::Ptr<flashgg::DiPhotonCandidate> dipho = diPhotons->ptrAt( candIndex );

            //diphoton pt cuts
            if( dipho->leadingPhoton()->pt() < ( dipho->mass() )*leadPhoOverMassThreshold_ )
            { continue; }
            if( dipho->subLeadingPhoton()->pt() < ( dipho->mass() )*subleadPhoOverMassThreshold_ )
            { continue; }
            //photon mva preselection
            if( dipho->leadingPhoton()->phoIdMvaDWrtVtx( dipho->vtx() ) <= phoIdMVAThreshold_ )
            { continue; }
            if( dipho->subLeadingPhoton()->phoIdMvaDWrtVtx( dipho->vtx() ) <= phoIdMVAThreshold_ )
            { continue; }
            //diphoton MVA preselection
            if( mvares->result < diphoMVAThreshold_ )
            { continue; }



            VHEtTag tag_obj( dipho, mvares );
            tag_obj.includeWeights( *dipho );
            tag_obj.setDiPhotonIndex( candIndex );
            tag_obj.setSystLabel( systLabel_ );
            tag_obj.setMet( theMET );


            //MetCorrections2012_Simple(leadp4,subleadp4);
            //if(diphoton.mass()>100&&diphoton.mass()<180)
            {
                //calculate met
            }
            //std::cout << "Met: " << theMET->pt() << std::endl;
            if( theMET->pt() > metPtThreshold_ ) {
                //setdiphotonindex
                //setMET
                vhettags->push_back( tag_obj );
                if( ! evt.isRealData() ) {
                    VHEtTagTruth truth_obj;
                    truth_obj.setGenPV( higgsVtx );
                    truth_obj.setAssociatedZ( associatedZ );
                    truth_obj.setAssociatedW( associatedW );
                    truth_obj.setVhasDaughters( VhasDaughters );
                    truth_obj.setVhasNeutrinos( VhasNeutrinos );
                    truth_obj.setVhasMissingLeptons( VhasMissingLeptons );
                    truth_obj.setVpt( Vpt );
                    
                    truths->push_back( truth_obj );
                    vhettags->back().setTagTruth( edm::refToPtr( edm::Ref<vector<VHEtTagTruth> >( rTagTruth, idx++ ) ) );
                }
            }
        }
        evt.put( vhettags );
        evt.put( truths );
    }
}

typedef flashgg::VHEtTagProducer FlashggVHEtTagProducer;
DEFINE_FWK_MODULE( FlashggVHEtTagProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

