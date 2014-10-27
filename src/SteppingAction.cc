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
  {  theStep-> GetTrack() -> SetTrackStatus(fStopAndKill);    
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
	
	if(CreateTree::Instance() -> Production())
        {
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
  }
  
  if(CreateTree::Instance() -> Crystal() && CreateTree::Instance() -> Grease())
  {
    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
    {
      if ((thePrePV->GetName()=="Air_opposite" &&  thePostPV->GetName()=="help_g_temp_g")
	  || (thePrePV->GetName()=="Air_source" &&  thePostPV->GetName()=="World")
	  || (thePrePV->GetName()=="Air_side" &&  thePostPV->GetName()=="World"))
      { 	
        CreateTree::Instance()-> Time.push_back(theStep-> GetTrack()-> GetGlobalTime());
        CreateTree::Instance()-> Wglth_ex.push_back(theStep -> GetTrack() ->GetTotalEnergy());
	
        if (thePrePV->GetName()=="Air_opposite" &&  thePostPV->GetName()=="help_g_temp_g")
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
	
	if(CreateTree::Instance() -> Production())
        {
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
  }
  
  
  if(CreateTree::Instance() -> Crystal() && CreateTree::Instance() -> Wrapping())
  {
    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
    {
      if ((thePrePV->GetName()=="Air_opposite" &&  thePostPV->GetName()=="World"))
      { 	
        CreateTree::Instance()-> Time.push_back(theStep-> GetTrack()-> GetGlobalTime());
        CreateTree::Instance()-> Wglth_ex.push_back(theStep -> GetTrack() ->GetTotalEnergy());
	
        if (thePrePV->GetName()=="Air_opposite" &&  thePostPV->GetName()=="World")
        {
          CreateTree::Instance()-> Extraction.push_back(1);
        }
        else
        {
          CreateTree::Instance()-> Extraction.push_back(10);
        }
        
	if(CreateTree::Instance() -> Production())
        {
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
    if (theStep-> GetTrack() -> GetTrackStatus() != 2)
    { 
      if(particleType!=G4OpticalPhoton::OpticalPhotonDefinition())
      {
        CreateTree::Instance() -> E_End_Time.push_back(theStep-> GetTrack() -> GetGlobalTime());
	CreateTree::Instance() -> E_End_Energy.push_back(theStep-> GetTrack() -> GetKineticEnergy());
      }
    }
  }
  
  // ---------- TOTAL ENERGY ----------
  CreateTree::Instance() -> Energy_Sum += theStep-> GetTotalEnergyDeposit();

  // -------- TEMP--------
//   if (thePrePV->GetName()=="Crystal" && thePostPV->GetName()=="World" && particleType==G4Gamma::GammaDefinition())
//   {
//     if(theStep-> GetTrack() -> GetTotalEnergy() < 0.07 && theStep-> GetTrack() -> GetTotalEnergy() > 0){
//         //  theStep-> GetTrack() -> SetTrackStatus(fStopAndKill);
// //CreateTree::Instance() -> Energy_Sum +=  theStep->GetTrack() -> GetTotalEnergy();
// if(theStep->GetTrack()->GetTrackID() > 1)
// {
// cout << theStep->GetTrack()->GetCreatorProcess()->GetProcessName() << endl;
// }
// else{cout << "ciao" << endl;}
// //       cout << theStep-> GetTrack() -> GetTrackID() <<endl;
// //     cout << particleType->GetParticleName() << endl;
// //     cout << thePostPoint-> GetProcessDefinedStep()-> GetProcessName() << endl;     
// //     cout << theStep-> GetTrack() -> GetTotalEnergy() << endl;
//     }
//   }
  
  //---------- PRINT STEP INFO -----------
  int r = 0;
  if(r == 1)
  {
  // Print info
  G4cout << "-----------------------------------------------" << G4endl;
  G4cout << "Step is limited by "
   << theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()
   << G4endl;
  G4cout << "Processes involved to the step" << G4endl;
  G4StepStatus stepStatus = fpSteppingManager->GetfStepStatus();

  if(stepStatus==fAtRestDoItProc)
  {
    G4ProcessVector* procAtRest = fpSteppingManager->GetfAtRestDoItVector();
    G4SelectedAtRestDoItVector* selProcAtRest
     = fpSteppingManager->GetfSelectedAtRestDoItVector();
    size_t MAXofAtRestLoops = fpSteppingManager->GetMAXofAtRestLoops();
    for(size_t i1=0;i1<MAXofAtRestLoops;i1++)
    {
      if((*selProcAtRest)[MAXofAtRestLoops-i1-1]==2)
      { G4cout << "  At rest : " << (*procAtRest)[i1]->GetProcessName() << " (forced)" << G4endl; }
      else if((*selProcAtRest)[MAXofAtRestLoops-i1-1]==1)
      { G4cout << "  At rest : " << (*procAtRest)[i1]->GetProcessName() << G4endl; }
    }
  }

  if(stepStatus!=fExclusivelyForcedProc && stepStatus!=fAtRestDoItProc)
  {
    G4ProcessVector* procAlong = fpSteppingManager->GetfAlongStepDoItVector();
    size_t MAXofAlongStepLoops = fpSteppingManager->GetMAXofAlongStepLoops();
    for(size_t i2=0;i2<MAXofAlongStepLoops;i2++)
    {
      if((*procAlong)[i2]!=0)
      G4cout << "  Along step : " << (*procAlong)[i2]->GetProcessName() << G4endl;
    }
  }

  if(stepStatus!=fAtRestDoItProc)
  {
    G4ProcessVector* procPost = fpSteppingManager->GetfPostStepDoItVector();
    G4SelectedPostStepDoItVector* selProcPost
     = fpSteppingManager->GetfSelectedPostStepDoItVector();
    size_t MAXofPostStepLoops = fpSteppingManager->GetMAXofPostStepLoops();
    for(size_t i3=0;i3<MAXofPostStepLoops;i3++)
    {
      if((*selProcPost)[MAXofPostStepLoops-i3-1]==2)
      { G4cout << "  Post step : " << (*procPost)[i3]->GetProcessName() << " (forced)" << G4endl; }
      else if((*selProcPost)[MAXofPostStepLoops-i3-1]==1)
      { G4cout << "  Post step : " << (*procPost)[i3]->GetProcessName() << G4endl; }
    }
  }

  G4int nSecAtRest = fpSteppingManager->GetfN2ndariesAtRestDoIt();
  G4int nSecAlong  = fpSteppingManager->GetfN2ndariesAlongStepDoIt();
  G4int nSecPost   = fpSteppingManager->GetfN2ndariesPostStepDoIt();
  G4int nSecTotal  = nSecAtRest+nSecAlong+nSecPost;
  G4TrackVector* secVec = fpSteppingManager->GetfSecondary();

  if(nSecTotal>0)
  {
    G4cout << "  :----- List of 2ndaries - " << std::setw(3) << nSecTotal
           << " (Rest=" << std::setw(2) << nSecAtRest
           << ",Along=" << std::setw(2) << nSecAlong
           << ",Post="  << std::setw(2) << nSecPost << ")" << G4endl;

    for(size_t lp1=(*secVec).size()-nSecTotal; lp1<(*secVec).size(); lp1++)
    {
      G4cout << "    : "
             << G4BestUnit((*secVec)[lp1]->GetPosition(), "Length") << " "
             << std::setw( 9) << G4BestUnit((*secVec)[lp1]->GetKineticEnergy() , "Energy") << " "
             << std::setw(18) << (*secVec)[lp1]->GetDefinition()->GetParticleName()
             << " generated by " << (*secVec)[lp1]->GetCreatorProcess()->GetProcessName() << G4endl;
    }
  }
  
  G4cout << "-----------------------------------------------" << G4endl;
  }
  
}

