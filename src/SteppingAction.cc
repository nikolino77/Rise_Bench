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

  G4Track* theTrack = theStep->GetTrack();
  G4ParticleDefinition* particleType = theTrack->GetDefinition();

  
  // ------------------------ STORING PARTICLE AND PROCESSES ------------------------- //
  
  // Storing time, energy and position of optical photons absorbed
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
  {        theTrack->SetTrackStatus(fStopAndKill);

    if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption")
    {
      CreateTree::Instance()->NumOptPhotonsAbsorbed++;
    }
  }

  
  // ------------------------ Energy deposition info ------------------------- //
  if(CreateTree::Instance() -> Deposition())
  {
    if(theStep->GetTotalEnergyDeposit()!=0)
    { 
      CreateTree::Instance()-> depositionProcess.push_back(thePostPoint-> GetProcessDefinedStep()-> GetProcessName());
      CreateTree::Instance()-> energyDeposited.push_back(-theStep-> GetTotalEnergyDeposit());
      CreateTree::Instance()-> depositionX.push_back(thePostPoint-> GetPosition().x());
      CreateTree::Instance()-> depositionY.push_back(thePostPoint-> GetPosition().y());
      CreateTree::Instance()-> depositionZ.push_back(thePostPoint-> GetPosition().z());
    } 
  }
  
  if(thePostPV && particleType==G4Gamma::GammaDefinition())
  { 
    if(CreateTree::Instance() -> Crystal() && CreateTree::Instance() -> Control())
    {
      if(thePrePV->GetName()=="Air_source" &&  thePostPV->GetName()=="Crystal")
      {
        CreateTree::Instance()-> NumGammaEnter = 1;
	CreateTree::Instance()-> Enter_Time = theStep-> GetTrack()-> GetGlobalTime();
      }
    }
  }
  
  
  // ---------- INFO AT CONTROL VOLUME ---------- //
  if(CreateTree::Instance() -> Crystal() && CreateTree::Instance() -> Control())
  {
    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
    {
      if ((thePrePV->GetName()=="Air_opposite" &&  thePostPV->GetName()=="World")
	  || (thePrePV->GetName()=="Air_source" &&  thePostPV->GetName()=="World")
	  || (thePrePV->GetName()=="Air_side" &&  thePostPV->GetName()=="World"))
      { 	
        CreateTree::Instance()-> Time.push_back(theStep-> GetTrack()-> GetGlobalTime());
        CreateTree::Instance()-> Wglth_ex.push_back(theStep -> GetTrack() ->GetTotalEnergy());
	
        if (thePrePV->GetName()=="Air_opposite" &&  thePostPV->GetName()=="World")
        {
          CreateTree::Instance()-> Extraction.push_back(1);
        }
        else if(thePrePV->GetName()=="Air_source" &&  thePostPV->GetName()=="World")
        {
	  CreateTree::Instance()-> Extraction.push_back(2);
        }
        else if(thePrePV->GetName()=="Air_side" &&  thePostPV->GetName()=="World")
        {
	  CreateTree::Instance()-> Extraction.push_back(3);
        }
	
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
        else if(theStep-> GetTrack()-> GetCreatorProcess() 
           && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="OpWLS")
        { 
          CreateTree::Instance()-> Parent.push_back(3);
        }
        else
        { 
          CreateTree::Instance()-> Parent.push_back(4);
	  cout << "boh" <<endl;
        }
      }
    }
  }
  
  // ---------- INFO AT DETECTOR ---------- //
  if(CreateTree::Instance() -> Hits())
  {
    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition() )
    {  
      if ((thePrePV->GetName()=="Detector" &&  thePostPV->GetName()=="World"))
      { 	    	   
	if(CreateTree::Instance() -> Crystal())
	{
	  if(theTrack -> GetLogicalVolumeAtVertex() -> GetName() == "Crystal")
	  {
	    CreateTree::Instance()-> Volume.push_back(1);
	  }
	}
	if(CreateTree::Instance() -> Window())
	{
          if(theTrack -> GetLogicalVolumeAtVertex() -> GetName() == "Window")
	  {
	    CreateTree::Instance()-> Volume.push_back(2);
	  }
	}	
 
        CreateTree::Instance()-> Time_det.push_back(theStep-> GetTrack()-> GetGlobalTime());
        CreateTree::Instance()-> Wglth_ex_det.push_back(theStep -> GetTrack() ->GetTotalEnergy());
		
        if(theStep-> GetTrack()-> GetCreatorProcess() 
           && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="Cerenkov") 
        {
          CreateTree::Instance()->Parent_det.push_back(1);
        }     
        else if(theStep-> GetTrack()-> GetCreatorProcess() 
           && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="Scintillation")
        { 
          CreateTree::Instance()-> Parent_det.push_back(2);
        }
        else if(theStep-> GetTrack()-> GetCreatorProcess() 
           && theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName()=="OpWLS")
        { 
          CreateTree::Instance()-> Parent_det.push_back(3);
        }
        else
        { 
          CreateTree::Instance()-> Parent_det.push_back(4);
	  cout << "Anomaly (production process)" <<endl;
        }
      }
    }  
  }

  // ---------- PARTICLE DYING ----------
  if(CreateTree::Instance() -> Electrons())
  {
    if (theStep-> GetTrack() -> GetTrackStatus() == 2)
    { 
      if(particleType!=G4OpticalPhoton::OpticalPhotonDefinition())
      {
        /*
        cout << "--------------step ----------" <<endl;
        cout << theStep-> GetTrack() -> GetTrackID() <<endl;
        cout << particleType->GetParticleName() << endl;
        cout << thePostPoint-> GetProcessDefinedStep()-> GetProcessName() << endl; 
        cout << "traccia parente " << theStep-> GetTrack() -> GetParentID() << endl; 
        if(theStep-> GetTrack() -> GetParentID() != 0)
	{
	  cout << "processo parente " << theStep-> GetTrack()-> GetCreatorProcess()-> GetProcessName() << endl;
	}
        cout << theStep-> GetTrack() -> GetKineticEnergy() << endl;
        cout << theStep-> GetTrack() -> GetTotalEnergy() << endl;
        cout << theStep-> GetTrack() -> GetTrackStatus() << endl;
	G4cout << theStep-> GetTrack() -> GetGlobalTime() << endl;
        */
        CreateTree::Instance()-> E_End_Time.push_back(theStep-> GetTrack() -> GetGlobalTime());
      }
    }
  }
  
}

