#include "CreateTree.hh"
#include <vector>

CreateTree* CreateTree::fInstance = NULL;

using namespace std;

CreateTree::CreateTree(TString name,Bool_t hits,Bool_t absorptions)
{
	

	if(fInstance) 
	{
    		return;
  	}

  	this->HITS=hits;
  	this->ABSORPTIONS=absorptions;

  	this->fInstance = this;
  	this->fname = name;
  	this->ftree = new TTree("tree","name");
 
  	this->GetTree()->Branch("Run",&this->Run,"Run/I");
  	this->GetTree()->Branch("Event",&this->Event,"Event/I");
	this->GetTree()->Branch("NumOptPhotons",&this->NumOptPhotons,"NumOptPhotons/I");
  	this->GetTree()->Branch("NumCerenkovPhotons",&this->NumCerenkovPhotons,"NumCerenkovPhotons/I");
  	this->GetTree()->Branch("NumScintPhotons",&this->NumScintPhotons,"NumScintPhotons/I");
  	this->GetTree()->Branch("NumOptPhotonsAbsorbed",&this->NumOptPhotonsAbsorbed,"NumOptPhotonsAbsorbed/I");
  	this->GetTree()->Branch("NumOptPhotonsRayleigh",&this->NumOptPhotonsRayleigh,"NumOptPhotonsRayleigh/I");
  	this->GetTree()->Branch("NumCherenkovPr",&this->NumCherenkovPr,"NumCherenkovPr/I");
  	this->GetTree()->Branch("NumeBrem",&this->NumeBrem,"NumeBrem/I");  
  	this->GetTree()->Branch("NumGammaEnter",&this->NumGammaEnter,"NumGammaEnter/I");  
  
  	this->GetTree()->Branch("NumBoundaryAbsorption",&this->NumBoundaryAbsorption,"NumBoundaryAbsorption/I");
  	this->GetTree()->Branch("NumBoundaryReflection",&this->NumBoundaryReflection,"NumBoundaryReflection/I");

  	this->GetTree()->Branch("NumBoundaryFresnelRefraction",&this->NumBoundaryFresnelRefraction,"NumBoundaryFresnelRefraction/I");
  	this->GetTree()->Branch("NumBoundaryStepTooSmall",&this->NumBoundaryStepTooSmall,"NumBoundaryStepTooSmall/I");
  	this->GetTree()->Branch("NumBoundaryFresnelReflection",&this->NumBoundaryFresnelReflection,"NumBoundaryFresnelReflection/I");
  	this->GetTree()->Branch("NumBoundaryLobeReflection",&this->NumBoundaryLobeReflection,"NumBoundaryLobeReflection/I");
  	this->GetTree()->Branch("NumBoundarySpikeReflection",&this->NumBoundarySpikeReflection,"NumBoundarySpikeReflection/I");
  	this->GetTree()->Branch("NumBoundaryTotalInternalReflection",&this->NumBoundaryTotalInternalReflection,"NumBoundaryTotalInternalReflection/I");
  	this->GetTree()->Branch("NumBoundaryLambertianReflection",&this->NumBoundaryLambertianReflection,"NumBoundaryLambertianReflection/I");
  	this->GetTree()->Branch("NumBoundaryBackScattering",&this->NumBoundaryBackScattering,"NumBoundaryBackScattering/I");

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

  	this->GetTree()->Branch("ReflBackside",&this->ReflBackside,"ReflBackside/I");

  	this->GetTree()->Branch("AirLayer",&this->AirLayer,"AirLayer/I");
  	this->GetTree()->Branch("AirGap",&this->AirGap,"AirGap/F");
  	this->GetTree()->Branch("AirLayerSigmaAlpha",&this->AirLayerSigmaAlpha,"AirLayerSigmaAlpha/F");


/*--------------------MY STUFF-----------------*/

  	this->GetTree()->Branch("OutSurface",&this->OutSurface,"OutSurface/I");

	this->GetTree()->Branch("depositionProcess",&depositionProcess);
	this->GetTree()->Branch("energyDeposited",&energyDeposited);
	this->GetTree()->Branch("depositionX",&depositionX);
	this->GetTree()->Branch("depositionY",&depositionY);
	this->GetTree()->Branch("depositionZ",&depositionZ);
  	this->GetTree()->Branch("energyTot",&this->energyTot,"energyTot/F");

	this->GetTree()->Branch("opticProcess",&opticProcess);
	this->GetTree()->Branch("firstPosX",&firstPosX);
	this->GetTree()->Branch("firstPosY",&firstPosY);
	this->GetTree()->Branch("firstPosZ",&firstPosZ);
	
	this->GetTree()->Branch("Cer_Time",&Cer_Time);
	this->GetTree()->Branch("Scint_Time",&Scint_Time);
	this->GetTree()->Branch("Cer_Time_prod",&Cer_Time_prod);
	this->GetTree()->Branch("Scint_Time_prod",&Scint_Time_prod);
	this->GetTree()->Branch("OptPhotonEnergy_scint",&OptPhotonEnergy_scint);
	this->GetTree()->Branch("OptPhotonEnergy_cer",&OptPhotonEnergy_cer);

  	// Photons at exit interface

	this->GetTree()->Branch("NumOptPhotonsExit",&this->NumOptPhotonsExit,"NumOptPhotonsExit/I");  
	this->GetTree()->Branch("NumOptPhotonsInterface",&this->NumOptPhotonsInterface,"NumOptPhotonsInterface/I");  
    this->GetTree()->Branch("IntOut",&IntOut);		
    this->GetTree()->Branch("Time",&Time);	
    this->GetTree()->Branch("Parent",&Parent);
    this->GetTree()->Branch("ID",&ID);	
	this->GetTree()->Branch("Wglth_ex", &Wglth_ex);	
  		
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

  	Run=0;
  	Event=0;
  	NumOptPhotons=0;
	NumCerenkovPhotons=0;
	NumScintPhotons=0;
  	NumOptPhotonsAbsorbed=0;
  	NumOptPhotonsRayleigh=0;
  	NumCherenkovPr=0;
  	NumeBrem=0;
  	NumOptPhotonsInterface = 0;
  	NumOptPhotonsExit	 = 0;
  	NumGammaEnter = 0;

  	NumBoundaryAbsorption=0;
  	NumBoundaryReflection=0;
  	NumBoundaryStepTooSmall=0;
  	NumBoundaryFresnelRefraction=0;

  	NumBoundaryFresnelReflection=0;
  	NumBoundaryLobeReflection=0;
  	NumBoundarySpikeReflection=0;
  	NumBoundaryTotalInternalReflection=0;
  	NumBoundaryLambertianReflection=0;
  	NumBoundaryBackScattering=0;

	OutSurface=0;
	opticProcess.clear();
	firstPosX.clear();
	firstPosY.clear();
	firstPosZ.clear();
	
	depositionProcess.clear();
	energyDeposited.clear();
	depositionX.clear();		
	depositionY.clear();		
	depositionZ.clear();	
    IntOut.clear();
    Time.clear();
    Parent.clear();
    ID.clear();
	Wglth_ex.clear();
	OptPhotonEnergy_scint.clear();
	OptPhotonEnergy_cer.clear();
	Scint_Time.clear();
	Cer_Time.clear();
	Scint_Time_prod.clear();
	Cer_Time_prod.clear();

	energyTot = 0;	
}
