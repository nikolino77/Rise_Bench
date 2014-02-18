#include "CreateTree.hh"
#include <vector>

CreateTree* CreateTree::fInstance = NULL;

using namespace std;

CreateTree::CreateTree(TString name, Bool_t hits, Bool_t window, Bool_t crystal, Bool_t control, Bool_t deposition, Bool_t production, Bool_t electrons)
{
	
	if(fInstance) 
	{
    	  return;
  	}

	this->HITS		= hits;
	this->WINDOW		= window;
	this->CRYSTAL		= crystal;
	this->CONTROL		= control;
	this->DEPOSITION	= deposition;
	this->PRODUCTION	= production;
	this->ELECTRONS		= electrons;

  	this->fInstance = this;
  	this->fname = name;
  	this->ftree = new TTree("tree","name");
 
  	this->GetTree()->Branch("Run",&this->Run,"Run/I");
  	this->GetTree()->Branch("Event",&this->Event,"Event/I");
	
  	this->GetTree()->Branch("NumOptPhotonsAbsorbed",&this->NumOptPhotonsAbsorbed,"NumOptPhotonsAbsorbed/I");
  	this->GetTree()->Branch("NumGammaEnter",&this->NumGammaEnter,"NumGammaEnter/I");  
  	this->GetTree()->Branch("NumPhotons",&this->NumPhotons,"NumPhotons/I");
	
	this->GetTree()->Branch("Enter_Time",&this->Enter_Time,"Enter_Time/D");

	if(this->ELECTRONS)
	{
	  this->GetTree()->Branch("E_End_Time",&E_End_Time);
	}
	
	if(this->DEPOSITION)
	{
	  this->GetTree()->Branch("depositionProcess",&depositionProcess);
	  this->GetTree()->Branch("energyDeposited",&energyDeposited);
	  this->GetTree()->Branch("depositionX",&depositionX);
	  this->GetTree()->Branch("depositionY",&depositionY);
	  this->GetTree()->Branch("depositionZ",&depositionZ);
	  this->GetTree()->Branch("firstPosX",&firstPosX);
	  this->GetTree()->Branch("firstPosY",&firstPosY);
	  this->GetTree()->Branch("firstPosZ",&firstPosZ);
	}
	  
	if(this->PRODUCTION)
	{
 	  this->GetTree()->Branch("opticProcess",&opticProcess);
	  this->GetTree()->Branch("Prod_Time",&Prod_Time);
	  this->GetTree()->Branch("OptPhotonEnergy",&OptPhotonEnergy);
	}
	  
  	// Photons at exit interface

	if(this->CONTROL)
	{
          this->GetTree()->Branch("Extraction",&Extraction);		
          this->GetTree()->Branch("Time",&Time);	
          this->GetTree()->Branch("Parent",&Parent);
	  this->GetTree()->Branch("Wglth_ex", &Wglth_ex);
	}
	
	// Photons at detector
	if(this->HITS)
	{	
          this->GetTree()->Branch("Time_det",&Time_det);	
          this->GetTree()->Branch("Parent_det",&Parent_det);
	  this->GetTree()->Branch("Wglth_ex_det", &Wglth_ex_det);
	  this->GetTree()->Branch("Volume",&Volume);		
	}
	
  	this->Clear();
}

CreateTree::~CreateTree()
{

}

Bool_t CreateTree::Write()
{
  	TString filename = this -> GetName();
  	filename += ".root";
  	TFile* file = new TFile(filename,"RECREATE");
  	this -> GetTree() -> Write();
  	file -> Write();
  	file -> Close();
  	return true;
}

void CreateTree::Clear()
{
  	Run			= 0;
  	Event			= 0;
  	NumOptPhotonsAbsorbed	= 0;
  	NumGammaEnter 		= 0;
	NumPhotons		= 0;
	
	Enter_Time		= 0;
	
	if(this->ELECTRONS)
	{
	  E_End_Time.clear();
	}
	
	if(this->DEPOSITION)
	{
	  firstPosX.clear();
	  firstPosY.clear();
	  firstPosZ.clear();
	  depositionProcess.clear();
	  energyDeposited.clear();
	  depositionX.clear();		
	  depositionY.clear();		
	  depositionZ.clear();	
	}
	
	if(this->PRODUCTION)
	{
	  opticProcess.clear();
	  OptPhotonEnergy.clear();
	  Prod_Time.clear();
	}
	
	if(this->CONTROL)
	{
	  Extraction.clear();
	  Parent.clear();
	  Wglth_ex.clear();
	  Time.clear();
	}
	
	if(this->HITS)
	{
	  Time_det.clear();
	  Parent_det.clear();
	  Wglth_ex_det.clear();
	  Volume.clear();
	}
	
}
