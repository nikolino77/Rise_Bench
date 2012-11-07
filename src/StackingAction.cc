#include "StackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"

#include "CreateTree.hh"
using namespace std;

StackingAction::StackingAction() : gammaCounter(0)
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  // ------------ Retrieve tracks and particle history -------------- //


// ------------------------ MIA PARTE ------------------------- //

if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
{
	G4ThreeVector pos = aTrack-> GetPosition();
	G4ThreeVector ver = aTrack-> GetVertexPosition();
	CreateTree::Instance()-> opticProcess.push_back(aTrack->GetCreatorProcess()->GetProcessName());
	CreateTree::Instance()-> OptPhotonEnergy.push_back(aTrack->GetTotalEnergy());
	CreateTree::Instance()-> firstPosX.push_back(pos[0]);
	CreateTree::Instance()-> firstPosY.push_back(pos[1]);
	CreateTree::Instance()-> firstPosZ.push_back(pos[2]); 

	if(aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov")
    {
      	cerenkovCounter++;
		CreateTree::Instance() -> Cer_Time_prod.push_back(aTrack->GetGlobalTime());
	}
    if(aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName()=="Scintillation")
    {
		scintCounter++;
		CreateTree::Instance() -> Scint_Time_prod.push_back(aTrack->GetGlobalTime());
	}
    if(aTrack->GetParentID()>0)
    {
      	gammaCounter++;
	}
}

  return fUrgent;

}


void StackingAction::NewStage()
{
  //G4cout<<"Number of optical photons produces in this event : "<<gammaCounter<<G4endl;
  CreateTree::Instance()-> NumOptPhotons = gammaCounter;
  CreateTree::Instance()-> NumCerenkovPhotons = cerenkovCounter;
  CreateTree::Instance()-> NumScintPhotons = scintCounter;
}


void StackingAction::PrepareNewEvent()
{ 
  gammaCounter = 0;
  cerenkovCounter = 0;
  scintCounter = 0;
}

