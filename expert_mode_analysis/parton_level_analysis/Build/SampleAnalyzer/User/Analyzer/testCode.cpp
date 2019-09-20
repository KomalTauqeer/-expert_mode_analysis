#include "SampleAnalyzer/User/Analyzer/testCode.h"
using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool testCode::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;
  // initialize variables, histos
  MAfloat32 tempMass ;
  Mass = new TH1F("malp_80","",25,0,500);
  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void testCode::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histos
  TCanvas* myCanvas = new TCanvas("myCanvas","");
  gPad -> SetLogy();
  
  
  Mass -> GetXaxis() -> SetTitle("M_{jj} [GeV]");
  Mass -> GetYaxis() -> SetTitle("Events / (20 GeV)");
  Mass -> SetLineWidth(3);

  
 // cout << Mass -> Integral() << endl;
 

  Mass -> Draw();
  myCanvas->SaveAs("test.pdf");
  
  
  TFile* f = new TFile("Parton_level.root","RECREATE");
  Mass -> Write();
  f -> Close();
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool testCode::Execute(SampleFormat& sample, const EventFormat& event)
{
  // ***************************************************************************
  // Example of analysis with generated particles
  // Concerned samples : LHE/STDHEP/HEPMC
  // ***************************************************************************
  double myWeight;
  if (event.mc()!=0)
  {
    cout << "---------------NEW EVENT-------------------" << endl;
    
    // Event weight
    double myWeight=1.;
    if (!Configuration().IsNoEventWeight()) myWeight=event.mc()->weight();
    Manager()->InitializeForNewEvent(myWeight);
    }

    //double myEventWeight;
    //if(Configuration().IsNoEventWeight()) myEventWeight=1.;
    //else if(event.mc()->weight()!=0.) myEventWeight=event.mc()->weight();
    //else
    //{
    //  WARNING << "Found one event with a zero weight. Skipping..." << endmsg;
    // return false;
    //}
    //Manager()->InitializeForNewEvent(myEventWeight);
    vector <const MCParticleFormat*> SignalParticles;
    // Initial state
    for (MAuint32 i=0;i<event.mc()->particles().size();i++)
    {
     
      const MCParticleFormat* part = &(event.mc()->particles()[i]);
      if(PHYSICS->Id->IsFinalState(part)&& (part->pdgid()==21)){
      SignalParticles.push_back(part);}
    }

    SORTER->sort(SignalParticles,PTordering);
    int  num_signalParticles = SignalParticles.size();
    if (num_signalParticles >=2){
    const MCParticleFormat *g0 = SignalParticles[0];
    const MCParticleFormat *g1 = SignalParticles[1];
    const MAfloat32 pt0 = g0->pt();
    const MAfloat32 pt1 = g1->pt();
    const MAfloat32 eta0 = g0 -> eta();
    const MAfloat32 eta1 = g1 -> eta();
    const MAfloat32 phi0 = g0 -> phi();
    const MAfloat32 phi1 = g1 -> phi();
    const MAfloat32 M = sqrt(2*pt0*pt1*(cosh(eta0-eta1)-cos(phi0-phi1)));
    cout << "invariant mass" << M <<endl;
    //Fill histo 
     Mass -> Fill(M);

    }

/*
      // display the status code
      cout << "Status Code=" << part.statuscode() << endl;
      if (PHYSICS->Id->IsInitialState(part)) cout << " (Initial state) ";
      else if (PHYSICS->Id->IsFinalState(part)) cout << " (Final state) ";
      else cout << " (Intermediate state) ";
      cout << endl;

      // pdgid
      cout << "pdg id=" << part.pdgid() << endl;
      if (PHYSICS->Id->IsInvisible(part)) cout << " (invisible particle) ";
      else cout << " (visible particle) ";
      cout << endl;

      // display kinematics information
      cout << "px=" << part.px()
                << " py=" << part.py()
                << " pz=" << part.pz()
                << " e="  << part.e()
                << " m="  << part.m() << endl;
     // MAfloat32 tempMass = part.m();
     // cout << " temp Mass = " << tempMass << endl;
     // Mass -> Fill(tempMass);       
       
      cout << "pt=" << part.pt() 
                << " eta=" << part.eta() 
                << " phi=" << part.phi() << endl;
      
      // display particle mother id
      if (part.mothers().empty()) 
      {
        cout << "particle with no mother." << endl;
      }
      else
      {
        std::cout << "particle coming from the decay of";
        for(MAuint32 j=0;j<part.mothers().size();j++)
        {
         const MCParticleFormat* mother = part.mothers()[j];
         if ( mother ->pdgid() == 9000005)
         {
           cout << " particles coming from ALPs" << endl;
           MAfloat32 tempMass = part.m();
           cout << " temp Mass = " << tempMass << endl;
           Mass -> Fill(tempMass);     
         }
          cout << " " << mother->pdgid();
        }
        std::cout << "." << endl;
      }
     
    }
  

    // Transverse missing energy (MET)
    cout << "MET pt=" << event.mc()->MET().pt()
         << " phi=" << event.mc()->MET().phi() << endl;
    cout << endl;

    // Transverse missing hadronic energy (MHT)
    cout << "MHT pt=" << event.mc()->MHT().pt()
              << " phi=" << event.mc()->MHT().phi() << endl;
    cout << endl;

    // Total transverse energy (TET)
    cout << "TET=" << event.mc()->TET() << endl;
    cout << endl;

    // Total transverse hadronic energy (THT)
    cout << "THT=" << event.mc()->THT() << endl; 
    cout << endl;
   
  */ 
    return true;
  }
 

