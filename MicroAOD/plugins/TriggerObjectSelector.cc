#include <vector>
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"


class TriggerObjectSelector : public edm::EDProducer
{

public:
  TriggerObjectSelector( const edm::ParameterSet&);
  //~TriggerObjectSelector();                                                                                                                                                                 
private:
  //void beginJob( const edm::EventSetup & );                                                                                                                                                 
  void produce( edm::Event& , const edm::EventSetup&);
  //virtual void endJob();                                                                                                                                                                    

  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> tagTriggerObjects_;
  std::vector<std::string> filterLabels_;
  bool saveAll_;
};

TriggerObjectSelector::TriggerObjectSelector(const edm::ParameterSet& iConfig):
  tagTriggerObjects_( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>( "inputTriggerObjects" ) ) ),
  filterLabels_( iConfig.getParameter<std::vector<std::string>>( "filterLabels" ) ),
  saveAll_(iConfig.getParameter<bool>("saveAllFilters"))
{
  //  if ( iConfig.exists( "inputTriggerObjects" ) ) tagTriggerObjects_ = iConfig.getParameter< edm::InputTag >( "inputTriggerObjects" );                                                       
  //if ( iConfig.exists( "filterLabels" ) ) tagFilterLabels_ = iConfig.getParameter< std::vector< std::string > >( "filterLabels" );                                                            
  produces< pat::TriggerObjectStandAloneCollection >();
}



void TriggerObjectSelector::produce(edm::Event& iEvent, const edm::EventSetup& iConfig)
{
  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  iEvent.getByToken(tagTriggerObjects_,triggerObjects);

  std::auto_ptr< pat::TriggerObjectStandAloneCollection > triggerObjectsStandAlone( new pat::TriggerObjectStandAloneCollection() );
  //const unsigned sizeObjects( tagTriggerObjects_[0]->sizeObjects() );                                                                                                                         
  //triggerObjectsStandAlone->reserve( sizeObjects );                                                                                                                                           

  for (pat::TriggerObjectStandAlone obj: *triggerObjects)
    {
      //obj.unpackPathNames (triggerNames);                                                                                                                                                     
      bool pushed_HLT_obj =false;
      if(saveAll_) // save all hlt objects regardless of filters                                                                                                                                
        {
          //std::cout << "save_all set to true;" << std::endl;                                                                                                                                  
          triggerObjectsStandAlone->push_back( obj );
        }
      else  //save all hlt objects that have at least one of the chosen filters                                                                                                                 
        for( std::string filter : filterLabels_ )
          {
            if(obj.hasFilterLabel(filter)&&pushed_HLT_obj==false) //if objects has interesting filter && hasn't been saved yet                                                                  
              {
                triggerObjectsStandAlone->push_back( obj );
                pushed_HLT_obj= true;
              }
          }
    }
  iEvent.put(triggerObjectsStandAlone);
}

DEFINE_FWK_MODULE(TriggerObjectSelector);
