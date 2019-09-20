#include "SampleAnalyzer/User/Analyzer/Particle_level.h"
#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>

using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------



bool Particle_level::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  // initialize variables, histos

  hist = new TH1F("malp_350","",100,0,1000);

  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------




void Particle_level::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{

  TCanvas* c = new TCanvas("c1","");
  gPad -> SetLogy();
  hist -> GetXaxis() -> SetTitle("M_{jj}[GeV]");
  hist -> GetYaxis() -> SetTitle("Events/Bin");
  hist -> SetLineWidth(4);
  hist -> Draw();
  c -> SaveAs("Histogram.pdf");
  // Save histo in file

  TFile* file = new TFile("particle_level.root","RECREATE");
  hist -> Write();
  file -> Close();



  cout << "END   Finalization" << endl;
}




// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------




bool Particle_level::Execute(SampleFormat& sample, const EventFormat& event)
{
  // Event weight
  
  //double myEventWeight;
  //if(Configuration().IsNoEventWeight()) myEventWeight=1.;
  //else if(event.rec()->weight()!=0.) myEventWeight=event.rec()->weight();
  //else
  //{
  //  WARNING << "Found one event with a zero weight. Skipping..." << endmsg;
  //  return false;
  //}
  //Manager()->InitializeForNewEvent(myEventWeight);

  if (event.rec()==0) {return true;}
  EventFormat myEvent;
  myEvent = event;
  // Looking through the reconstructed jet collection
    
    
  vector<const RecJetFormat*> SignalJets;
  for(unsigned int ij=0; ij<event.rec()->jets().size(); ij++)
     {
      const RecJetFormat * CurrentJet = &(event.rec()->jets()[ij]);
      //if ( CurrentJet->pt() > 30.0 && abs(CurrentJet->eta())<2.8)
      //SignalJets.push_back(CurrentJet);
      SignalJets.push_back(CurrentJet);
     }
       
  // Sorting jets in order of PT
  SORTER->sort(SignalJets, PTordering);

  //Make sure to have atleast two signal jets
  int  NumSignalJets = SignalJets.size();
  if (NumSignalJets >= 2)
  {
     const RecJetFormat *jet0 = SignalJets[0];
     const RecJetFormat *jet1 = SignalJets[1];
     const MAfloat32 pt0 = jet0->pt();
     const MAfloat32 pt1 = jet1->pt();
     const MAfloat32 eta0 = jet0 -> eta();
     const MAfloat32 eta1 = jet1 -> eta();
     const MAfloat32 phi0 = jet0 -> phi();
     const MAfloat32 phi1 = jet1 -> phi();
      
     // invariant mass calculation
     const MAfloat32 M = sqrt(2*pt0*pt1*(cosh(eta0-eta1)-cos(phi0-phi1)));
     cout << "invariant mass" << M <<endl;
       
       
     //Fill histo 
     hist -> Fill(M);
  } 

  
return true;

} 

