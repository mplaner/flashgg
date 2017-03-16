#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/VHMetTag.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

using namespace flashgg;

VHMetTag::VHMetTag() {}

VHMetTag::~VHMetTag() {}

VHMetTag::VHMetTag( edm::Ptr<flashgg::DiPhotonCandidate> diPho, edm::Ptr<DiPhotonMVAResult> mvaRes ) :
    VHMetTag::VHMetTag( diPho, *mvaRes ) {}

VHMetTag::VHMetTag( edm::Ptr<DiPhotonCandidate> dipho, DiPhotonMVAResult mvares ) :
    DiPhotonTagBase::DiPhotonTagBase( dipho, mvares ) {}


void VHMetTag::setIsVtx0(bool val )
{
    isVtx0_ = val;
}

double VHMetTag::getMetUnc( string type )
{
    if(type=="unc")
        return(uncUnc);
    else if( type=="jer")
        return(jerUnc);
    else if(type=="jen")
        return(jenUnc);
    else if(type=="pho")
        return(phoUnc);
    else if(type=="ele")
        return(eleUnc);
    else
        {
            std::cout << "invalid Met uncertainty" << std::endl;
            return(-1000);
        }
    }


void VHMetTag::setMet( edm::Ptr<flashgg::Met> met )
{
    //(pat::MET::UnclusteredEnUp,pat::MET::Type1XY)>y.shiftedPt(pat::MET::UnclusteredEnDown,pat::MET::Type1XY)
        
    theMet_ = met;
    metPt = met->corPt(pat::MET::Type1);
    metPhi = met->corPhi(pat::MET::Type1);
    //metPt = met->corPt(pat::MET::Type1XY);
    //metPhi = met->corPhi(pat::MET::Type1XY);
    uncUnc = abs(met->shiftedPt(pat::MET::UnclusteredEnUp,pat::MET::Type1) - met->shiftedPt(pat::MET::UnclusteredEnDown,pat::MET::Type1))/2;
    jerUnc = abs(met->shiftedPt(pat::MET::JetResUp,pat::MET::Type1) - met->shiftedPt(pat::MET::JetResDown,pat::MET::Type1))/2;
    jenUnc = abs(met->shiftedPt(pat::MET::JetEnUp,pat::MET::Type1) - met->shiftedPt(pat::MET::JetEnDown,pat::MET::Type1))/2;
    phoUnc = abs(met->shiftedPt(pat::MET::PhotonEnUp,pat::MET::Type1) - met->shiftedPt(pat::MET::PhotonEnDown,pat::MET::Type1))/2;
    eleUnc = abs(met->shiftedPt(pat::MET::ElectronEnUp,pat::MET::Type1) - met->shiftedPt(pat::MET::ElectronEnDown,pat::MET::Type1))/2;
}
void VHMetTag::setMetUncor( edm::Ptr<flashgg::Met> met )
{
     theMetUncor_ = met;
}
void VHMetTag::setMetMuon( edm::Ptr<flashgg::Met> met )
{
     theMetMuon_ = met;
}

void VHMetTag::setJet( edm::Ptr<flashgg::Jet> jet )
{
    theJet_ = jet;
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

