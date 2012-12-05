#include "CreateTree.hh"
#include <vector>

CreateTree* CreateTree::fInstance = NULL;

using namespace std;

CreateTree::CreateTree(TString name, Bool_t hits, Bool_t window, Bool_t crystal, Bool_t control, Bool_t deposition)
{
	
	if(fInstance) 
	{
    		return;
  	}

	this->HITS=hits;
	this->WINDOW=window;
	this->CRYSTAL=crystal;
	this->CONTROL=control;
	this->DEPOSITION=deposition;

  	this->fInstance = this;
  	this->fname = name;
  	this->ftree = new TTree("tree","name");
 
  	this->GetTree()->Branch("Run",&this->Run,"Run/I");
  	this->GetTree()->Branch("Event",&this->Event,"Event/I");
	
  	this->GetTree()->Branch("NumOptPhotonsAbsorbed",&this->NumOptPhotonsAbsorbed,"NumOptPhotonsAbsorbed/I");
  	this->GetTree()->Branch("NumGammaEnter",&this->NumGammaEnter,"NumGammaEnter/I");  
  
  	this->GetTree()->Branch("ScintillationYield",&this->ScintillationYield,"ScintillationYield/F");
  	this->GetTree()->Branch("RiseTime",&this->RiseTime,"RiseTime/F"); 
  	this->GetTree()->Branch("Reflectivity",&this->Reflectivity,"Reflectivity/F");
  	this->GetTree()->Branch("CrystalHeight",&this->CrystalHeight,"CrystalHeight/F");
  	this->GetTree()->Branch("CrystalDiameter",&this->CrystalDiameter,"CrystalDiameter/F");
  	this->GetTree()->Branch("CrystalX",&this->CrystalX,"CrystalX/F");
  	this->GetTree()->Branch("CrystalY",&this->CrystalY,"CrystalY/F");   
  	this->GetTree()->Branch("Gap",&this->Gap,"Gap/F");
  	this->GetTree()->Branch("GapMaterial",&this->GapMaterial,"GapMaterial/F");
  	this->GetTree()->Branch("GapRefIndex",&this->GapRefIndex,"GapRefIndex/F");
  	this->GetTree()->Branch("AbsLength",&this->AbsLength,"AbsLength/F");
  
  	this->GetTree()->Branch("Shape",&this->Shape,"Shape/F");
	
  	this->GetTree()->Branch("ScMaterial",&this->ScMaterial,"ScMaterial/F");

	/*--------------------MY STUFF-----------------*/

	this->GetTree()->Branch("depositionProcess",&depositionProcess);
	this->GetTree()->Branch("energyDeposited",&energyDeposited);
	this->GetTree()->Branch("depositionX",&depositionX);
	this->GetTree()->Branch("depositionY",&depositionY);
	this->GetTree()->Branch("depositionZ",&depositionZ);

	this->GetTree()->Branch("opticProcess",&opticProcess);
	this->GetTree()->Branch("firstPosX",&firstPosX);
	this->GetTree()->Branch("firstPosY",&firstPosY);
	this->GetTree()->Branch("firstPosZ",&firstPosZ);
	
	this->GetTree()->Branch("Prod_Time",&Prod_Time);
	this->GetTree()->Branch("OptPhotonEnergy",&OptPhotonEnergy);

  	// Photons at exit interface

        this->GetTree()->Branch("Extraction",&Extraction);		
        this->GetTree()->Branch("Time",&Time);	
        this->GetTree()->Branch("Parent",&Parent);
	this->GetTree()->Branch("Wglth_ex", &Wglth_ex);
	
	// Photons at detector
	if(this->HITS)
	{	
          this->GetTree()->Branch("Time_det",&Time_det);	
          this->GetTree()->Branch("Parent_det",&Parent_det);
	  this->GetTree()->Branch("Wglth_ex_det", &Wglth_ex_det);
	  if(this->WINDOW)
	  {
	    this->GetTree()->Branch("Volume",&Volume);		
	  }
	}
	
  	this->Clear();
}

CreateTree::~CreateTree()
{

}

Bool_t CreateTree::Write()
{
  	TString filename = this->GetName();
  	filename+=".root";
  	TFile* file = new TFile(filename,"RECREATE");
  	this->GetTree()->Write();
  	file->Write();
  	file->Close();
  	return true;
}

void CreateTree::Clear()
{
  	Run			= 0;
  	Event			= 0;
  	NumOptPhotonsAbsorbed	= 0;
  	NumGammaEnter 		= 0;
  	
	opticProcess.clear();
	firstPosX.clear();
	firstPosY.clear();
	firstPosZ.clear();
	
	depositionProcess.clear();
	energyDeposited.clear();
	depositionX.clear();		
	depositionY.clear();		
	depositionZ.clear();	
	Extraction.clear();
	Parent.clear();
	Wglth_ex.clear();
	OptPhotonEnergy.clear();
	Prod_Time.clear();
	Time.clear();
	
	Volume.clear();

	Time_det.clear();
	Parent_det.clear();
	Wglth_ex_det.clear();
}
