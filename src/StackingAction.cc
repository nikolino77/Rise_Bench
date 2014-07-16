#include "StackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"

#include "CreateTree.hh"
using namespace std;

StackingAction::StackingAction()
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  // ------------ Retrieve tracks and particle history -------------- //

  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
  { 
    if(aTrack -> GetVolume() -> GetName() != "Crystal")
    { 
      cout << aTrack -> GetVolume() -> GetName() << endl;
    }
    
    if(aTrack -> GetVolume() -> GetName() == "Crystal")
    {
      CreateTree::Instance() -> NumPhotons++;
    }
    
    if(CreateTree::Instance() -> Deposition())
    {
      G4ThreeVector pos = aTrack-> GetPosition();
      CreateTree::Instance()-> firstPosX.push_back(pos[0]);
      CreateTree::Instance()-> firstPosY.push_back(pos[1]);
      CreateTree::Instance()-> firstPosZ.push_back(pos[2]); 
    }
	
    if(CreateTree::Instance() -> Production())
    {
     
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
      {
        CreateTree::Instance() -> opticProcess.push_back(2);
        CreateTree::Instance() -> Prod_Time.push_back(aTrack->GetGlobalTime());
        CreateTree::Instance() -> OptPhotonEnergy.push_back(aTrack->GetTotalEnergy());
      }
      else if (aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov") 
      {
        CreateTree::Instance() -> opticProcess.push_back(1);
        CreateTree::Instance() -> Prod_Time.push_back(aTrack->GetGlobalTime());
        CreateTree::Instance() -> OptPhotonEnergy.push_back(aTrack->GetTotalEnergy());   
      }
      else if(aTrack->GetCreatorProcess()->GetProcessName() == "OpWLS")
      {
        CreateTree::Instance() -> opticProcess.push_back(3);
        CreateTree::Instance() -> Prod_Time.push_back(aTrack->GetGlobalTime());
        CreateTree::Instance() -> OptPhotonEnergy.push_back(aTrack->GetTotalEnergy());   
      }
      else
      {
        cout << "Anomalus creation process" << endl;
      }
    }
  } 
  //if(aTrack->GetTrackID() > 1)
  //{cout << aTrack->GetCreatorProcess()->GetProcessName() << endl;}
  /*
  if(aTrack->GetDefinition() == G4Gamma::GammaDefinition()) 
  { 
    if(aTrack->GetTrackID() > 1)
    //if(aTrack->GetTotalEnergy() < 0.5 && aTrack->GetTotalEnergy() > 0.4)
    //{
     // cout << aTrack->GetDefinition() << endl;
    {
    cout << aTrack->GetCreatorProcess()->GetProcessName() << endl;
      cout << aTrack->GetTotalEnergy() << endl;
    }
      //}
  }*/
  
  return fUrgent;

}
