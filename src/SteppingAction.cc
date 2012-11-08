#include "SteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <fstream>
#include "CreateTree.hh"
using namespace std;

SteppingAction::SteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step * theStep)
{
  
  G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();
  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4OpBoundaryProcess* boundary=NULL;

  G4Track* theTrack = theStep->GetTrack();
  G4ParticleDefinition* particleType = theTrack->GetDefinition();

  // ------------------------ STORING PARTICLE AND PROCESSES ------------------------- //
  
  // Storing time, energy and position of optical photons absorbed
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
  {
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption")
    {
      CreateTree::Instance()->NumOptPhotonsAbsorbed++;
    }
  }

  // Printing out the processes step by step
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Transportation"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="OpAbsorption" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="phot" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="compt" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="eIoni" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Scintillation" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Cerenkov" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="OpRayleigh"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="eBrem"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="UserMaxStep" // !!!!!!!!!!!!!!!!!
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="msc"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Rayl") 
  {
    G4cout<<thePostPoint->GetProcessDefinedStep()->GetProcessName()<<G4endl;
  }
  
  // Storing Rayleigh processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="OpRayleigh" )
  {
    CreateTree::Instance()-> NumOptPhotonsRayleigh++;
  }

  // Storing Cerenkov processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="Cerenkov" )
  {
    CreateTree::Instance()-> NumCherenkovPr++;
    CreateTree::Instance()-> Cer_Time.push_back(theStep-> GetTrack()-> GetGlobalTime());
  }
  
  // Storing Brem processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="eBrem" )
  {
    CreateTree::Instance()-> NumeBrem++;
  }

  // ------------------------ Energy deposition info ------------------------- //
  if(theStep->GetTotalEnergyDeposit()!=0)
  {
    CreateTree::Instance()-> depositionProcess.push_back(thePostPoint-> GetProcessDefinedStep()-> GetProcessName());
    CreateTree::Instance()-> energyDeposited.push_back(-theStep-> GetTotalEnergyDeposit());
    CreateTree::Instance()-> depositionX.push_back(thePostPoint-> GetPosition().x());
    CreateTree::Instance()-> depositionY.push_back(thePostPoint-> GetPosition().y());
    CreateTree::Instance()-> depositionZ.push_back(thePostPoint-> GetPosition().z());
    CreateTree::Instance()-> energyTot = CreateTree::Instance()-> energyTot - theStep-> GetTotalEnergyDeposit();
  } 

  
  // ---------- INFO AT DETECTOR ---------- //
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
  {
    if (thePrePV->GetName()=="TopAir" &&  thePostPV->GetName()=="Crystal")
    {	
      CreateTree::Instance()-> NumOptPhotonsInterface++;
      CreateTree::Instance()-> Time.push_back(theStep-> GetTrack()-> GetGlobalTime());      
      CreateTree::Instance()-> ID.push_back(theStep-> GetTrack()-> GetTrackID());
      CreateTree::Instance()-> IntOut.push_back(0);
      CreateTree::Instance()-> Wglth_ex.push_back(theStep -> GetTrack() ->GetTotalEnergy());

      if(theStep->GetTrack()-> GetCreatorProcess() 
         && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="Cerenkov")  
      {
        CreateTree::Instance()-> Parent.push_back(1);  
      }    
      else if(theStep-> GetTrack()-> GetCreatorProcess() 
         && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="Scintillation")
      { 
        CreateTree::Instance()-> Parent.push_back(2);
      }
      else
      { 
        CreateTree::Instance()-> Parent.push_back(3);
		cout << "boh" <<endl;
      }

    }

    else if (thePrePV->GetName()=="TopAir" &&  thePostPV->GetName()=="World")
    { 	
      CreateTree::Instance()-> NumOptPhotonsInterface++;
      CreateTree::Instance()-> NumOptPhotonsExit++;
      CreateTree::Instance()-> Time.push_back(theStep-> GetTrack()-> GetGlobalTime());
      CreateTree::Instance()-> ID.push_back(theStep -> GetTrack() -> GetTrackID());
      CreateTree::Instance()-> IntOut.push_back(1);
      CreateTree::Instance()-> Wglth_ex.push_back(theStep -> GetTrack() ->GetTotalEnergy());
	
      if(theStep-> GetTrack()-> GetCreatorProcess() 
         && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="Cerenkov") 
      {
        CreateTree::Instance()->Parent.push_back(1);
      }     
      else if(theStep-> GetTrack()-> GetCreatorProcess() 
         && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="Scintillation")
      { 
        CreateTree::Instance()-> Parent.push_back(2);
      }
      else
      { 
        CreateTree::Instance()-> Parent.push_back(3);
	    cout << "boh" <<endl;
      }
    }

  }  



}

