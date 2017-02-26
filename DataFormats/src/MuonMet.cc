#include "flashgg/DataFormats/interface/MuonMet.h"
#include "flashgg/DataFormats/interface/Met.h"
using namespace flashgg;

flashgg::MuonMet::MuonMet()
{}

flashgg::MuonMet::~MuonMet()
{}

flashgg::MuonMet::MuonMet( edm::Ptr<flashgg::Met> flashMET, edm::Ptr<pat::MET> patMET, edm::Ptr<flashgg::DiMuonCandidate> diMUON) 
{
    dimuon_ = diMUON;
    patmet_ = patMET;
    flashggmet_ = flashMET;    
    
    std::cout << "dimuon pt " << dimuon_->pt() << std::endl;
    std::cout << "patmet pt " << patmet_->pt() << std::endl;
    std::cout << "fggmet pt " << flashggmet_->pt() << std::endl;
}




// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

