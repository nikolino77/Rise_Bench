// Martin Goettlich @ DESY
//
#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
using namespace std;


class CreateTree
{
  private:

  TTree*              ftree;
  TString             fname;
  Bool_t              HITS;
  Bool_t              WINDOW;
  Bool_t              CRYSTAL;
  Bool_t              CONTROL;
  Bool_t              DEPOSITION;
  Bool_t              PRODUCTION;
  Bool_t              GREASE;
  Bool_t              ELECTRONS;

  static const Int_t  MaxNum = 2000000;
  static const Int_t  MaxNumPro = 1000;

  public:

  CreateTree(TString name,Bool_t hits, Bool_t window, Bool_t crystal, Bool_t control, Bool_t deposition, Bool_t production, Bool_t electrons, Bool_t grease);
  ~CreateTree();

  TTree*              	GetTree() const { return ftree; };
  TString             	GetName() const { return fname;};
  Int_t               	Fill() { return this->GetTree()->Fill(); };
  Bool_t              	Write();
  void                	Clear();
  static CreateTree*  	Instance() { return fInstance; };
  static CreateTree*  	fInstance;
  Bool_t              	Hits() const { return this->HITS; };
  Bool_t              	Window() const { return this->WINDOW; };
  Bool_t              	Crystal() const { return this->CRYSTAL; };
  Bool_t              	Control() const { return this->CONTROL; };
  Bool_t              	Deposition() const { return this->DEPOSITION; };
  Bool_t              	Production() const { return this->PRODUCTION; };
  Bool_t              	Electrons() const { return this->ELECTRONS; };
  Bool_t              	Grease() const { return this->GREASE; };
  
  Int_t			Run;
  Int_t			Event;
  
  Int_t			NumOptPhotonsAbsorbed;
  Int_t			NumGammaEnter;
  Int_t			NumPhotons;
  Double_t		Enter_Time;
  Double_t		Energy_Sum;
  vector<double>	E_End_Time;

  vector<float>		energyDeposited;
  vector<string>	depositionProcess;
  vector<float>		depositionX;
  vector<float>		depositionY;
  vector<float>		depositionZ;
  vector<int>		opticProcess;
  vector<float>		firstPosX;
  vector<float>		firstPosY;
  vector<float>		firstPosZ;
  
  vector<double>	Prod_Time;

  vector<double>	Wglth_ex;
  vector<double>	OptPhotonEnergy;
  
  vector<int>		Volume;		

  vector<double>	Time;		// Time at interface
  vector<int>		Extraction;	// Extraction face	
  vector<int>		Parent;		// Production process (1 for Cerenkov, 2 for Scintillation, 0 for unknown)

  vector<double>	Wglth_ex_det;
  vector<double>	Time_det;	
  vector<int>		Parent_det;		
  
};