////////////////////////////////////////////////////////////////////////
// Class:       signalntuple
// Plugin Type: analyzer (Unknown Unknown)
// File:        signalntuple_module.cc
//
// Generated at Wed Jul 31 13:36:32 2024 by Yeon-jae Jwa using cetskelgen
// from cetlib version 3.18.02.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "art_root_io/TFileService.h"
#include "lardataobj/RawData/RawDigit.h"

#include "TTree.h"


namespace signalntuple {
  class signalntuple;
}


class signalntuple::signalntuple : public art::EDAnalyzer {
public:
  explicit signalntuple(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  signalntuple(signalntuple const&) = delete;
  signalntuple(signalntuple&&) = delete;
  signalntuple& operator=(signalntuple const&) = delete;
  signalntuple& operator=(signalntuple&&) = delete;

  // Required functions.
  void analyze(art::Event const& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:

  // Declare member data here.
  // Fcl parameters.                                                                            
  std::vector<art::InputTag>  fRawDigitProducerLabelVec;
  mutable std::vector<float>   fRawDigitWW;
  mutable std::vector<float>   fChannelWW;
  mutable std::vector<float>   fPedestalWW;
  mutable std::vector<float>   fRawDigitWE;
  mutable std::vector<float>   fChannelWE;
  mutable std::vector<float>   fPedestalWE;
  mutable std::vector<float>   fRawDigitEW;
  mutable std::vector<float>   fChannelEW;
  mutable std::vector<float>   fPedestalEW;
  mutable std::vector<float>   fRawDigitEE;
  mutable std::vector<float>   fChannelEE;
  mutable std::vector<float>   fPedestalEE;
  // TTree variables                                                                            
  TTree*             fTree;
  int fEvent;        ///< number of the event being processed                                   
  int fRun;          ///< number of the run being processed                                     
  int fSubRun;       ///< number of the sub-run being processed          
};


signalntuple::signalntuple::signalntuple(fhicl::ParameterSet const& p)
  : EDAnalyzer{p}  // ,
  // More initializers here.
{
  // Call appropriate consumes<>() for any products to be retrieved by this module.
  //fTree     = tfs->make<TTree>("signalntuple",   "RawDigittree");
  //fTree->Branch("Event",           &fEvent,           "Event/I");
  //fTree->Branch("SubRun",          &fSubRun,          "SubRun/I");
  //fTree->Branch("Run",             &fRun,             "Run/I");
  //fTree->Branch("RawDigitWW", "std::vector<float>", fRawDigitWW);
  //unsigned int  fDataSize;
  //std::vector<short> rawadc;      //UNCOMPRESSED ADC VALUES.   
}

void signalntuple::signalntuple::analyze(art::Event const& e)
{
  // Implementation of required member function here.
  fRawDigitWW.clear();
  fChannelWW.clear();
  fPedestalWW.clear();
  fRawDigitWE.clear();
  fChannelWE.clear();
  fPedestalWE.clear();
  fRawDigitEW.clear();
  fChannelEW.clear();
  fPedestalEW.clear();
  fRawDigitEE.clear();
  fChannelEE.clear();
  fPedestalEE.clear();

  fEvent  = e.id().event();
  fRun    = e.run();
  fSubRun = e.subRun();

  std::vector<raw::RawDigit> const& rawDigitsWW = e.getProduct<std::vector<raw::RawDigit>>("daq:TPCWW");
  for (auto const& rd : rawDigitsWW)
  {
    // loop over the ADCs in the RawDigit
    for (size_t sample = 0; sample < rd.Samples(); ++sample)
      {
	fRawDigitWW.push_back(rd.ADC(sample));
      }
    fChannelWW.push_back(rd.Channel());
    fPedestalWW.push_back(rd.GetPedestal());
  }

  std::vector<raw::RawDigit> const& rawDigitsWE = e.getProduct<std::vector<raw::RawDigit>>("daq:TPCWE");
  for (auto const& rd : rawDigitsWE)
    {
      // loop over the ADCs in the RawDigit                                                                                                               
      for (size_t sample = 0; sample < rd.Samples(); ++sample)
	{
	  fRawDigitWE.push_back(rd.ADC(sample));
	}
      fChannelWE.push_back(rd.Channel());
      fPedestalWE.push_back(rd.GetPedestal());
    }

  std::vector<raw::RawDigit> const& rawDigitsEW = e.getProduct<std::vector<raw::RawDigit>>("daq:TPCEW");
  for (auto const& rd : rawDigitsEW)
    {
      // loop over the ADCs in the RawDigit                                                                                                               
      for (size_t sample = 0; sample < rd.Samples(); ++sample)
	{
	  fRawDigitEW.push_back(rd.ADC(sample));
	}
      fChannelEW.push_back(rd.Channel());
      fPedestalEW.push_back(rd.GetPedestal());
    }

  std::vector<raw::RawDigit> const& rawDigitsEE = e.getProduct<std::vector<raw::RawDigit>>("daq:TPCEE");
  for (auto const& rd : rawDigitsEE)
    {
      // loop over the ADCs in the RawDigit                                                                                                               
      for (size_t sample = 0; sample < rd.Samples(); ++sample)
	{
	  fRawDigitEE.push_back(rd.ADC(sample));
	}
      fChannelEE.push_back(rd.Channel());
      fPedestalEE.push_back(rd.GetPedestal());
    }

  fTree->Fill();
  //std::vector<const raw::RawDigit*> rawDigitVec;
  //e.getByLabel(fRawDigitProducerLabelVec, rawDigitVec);
  //for(const auto& rawDigit : rawDigitVec){
  //  fDataSize = rawDigit->Samples();
  //  std::cout<<"raw digit sample size: " << fDataSize << std::endl;
  //}

}

void signalntuple::signalntuple::beginJob()
{
  // Implementation of optional member function here.
  art::ServiceHandle<art::TFileService> tfs;
  fTree     = tfs->make<TTree>("signalntuple",   "RawDigittree");
  fTree->Branch("Event",           &fEvent,           "Event/I");
  fTree->Branch("SubRun",          &fSubRun,          "SubRun/I");
  fTree->Branch("Run",             &fRun,             "Run/I");
  fTree->Branch("RawDigitWW", "std::vector<float>", &fRawDigitWW);
  fTree->Branch("ChannelWW", "std::vector<float>", &fChannelWW);
  fTree->Branch("PedestalWW", "std::vector<float>", &fPedestalWW);

  fTree->Branch("RawDigitWE", "std::vector<float>", &fRawDigitWE);
  fTree->Branch("ChannelWE", "std::vector<float>", &fChannelWE);
  fTree->Branch("PedestalWE", "std::vector<float>", &fPedestalWE);

  fTree->Branch("RawDigitEW", "std::vector<float>", &fRawDigitEW);
  fTree->Branch("ChannelEW", "std::vector<float>", &fChannelEW);
  fTree->Branch("PedestalEW", "std::vector<float>", &fPedestalEW);

  fTree->Branch("RawDigitEE", "std::vector<float>", &fRawDigitEE);
  fTree->Branch("ChannelEE", "std::vector<float>", &fChannelEE);
  fTree->Branch("PedestalEE", "std::vector<float>", &fPedestalEE);

}

void signalntuple::signalntuple::endJob()
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(signalntuple::signalntuple)
