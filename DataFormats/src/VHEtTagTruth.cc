#include "flashgg/DataFormats/interface/VHEtTagTruth.h"
#include <iostream>

using namespace flashgg;

VHEtTagTruth::VHEtTagTruth() {}

VHEtTagTruth::~VHEtTagTruth() {}

/*
VHEtTagTruth::VHEtTagTruth(const VHEtTagTruth &b) : TagTruthBase::TagTruthBase(b)
{
    std::cout << " Derived copy constructor!" << std::endl;
    setClosestGenJetToLeadingJet(b.closestGenJetToLeadingJet());
    setClosestGenJetToSubLeadingJet(b.closestGenJetToSubLeadingJet());
    setClosestParticleToLeadingJet(b.closestParticleToLeadingJet());
    setClosestParticleToSubLeadingJet(b.closestParticleToSubLeadingJet());
    setClosestParticleToLeadingPhoton(b.closestParticleToLeadingPhoton());
    setClosestParticleToSubLeadingPhoton(b.closestParticleToSubLeadingPhoton());
    setLeadingQuark(b.leadingParton());
    setSubLeadingQuark(b.subLeadingParton());
}
*/

VHEtTagTruth *VHEtTagTruth::clone() const
{
    //    return (new VHEtTagTruth(*this));
    VHEtTagTruth *result = new VHEtTagTruth;
    result->setAssociatedZ( associatedZ() );
    result->setAssociatedW( associatedW() );
    result->setVhasDaughters( VhasDaughters() );
    result->setVhasNeutrinos( VhasNeutrinos() );
    result->setVhasMissingLeptons( VhasMissingLeptons() );
    result->setVpt( Vpt() );
    return result;

}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
