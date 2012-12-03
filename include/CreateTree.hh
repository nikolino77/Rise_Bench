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
  
  static const Int_t  MaxNum = 2000000;
  static const Int_t  MaxNumPro = 1000;

  public:

  CreateTree(TString name,Bool_t hits, Bool_t window);
  ~CreateTree();

  TTree*              GetTree() const { return ftree; };
  TString             GetName() const { return fname;};
  Int_t               Fill() { return this->GetTree()->Fill(); };
  Bool_t              Write();
  void                Clear();
  static CreateTree*  Instance() { return fInstance; };
  static CreateTree*  fInstance;
  Bool_t              Hits() const { return this->HITS; };
  Bool_t              Window() const { return this->WINDOW; };

  Float_t             ScintillationYield;
  Float_t             RiseTime;
  Float_t             CrystalHeight;
  Float_t             CrystalDiameter;
  Float_t             CrystalY;
  Float_t             CrystalX; 
  Float_t             Reflectivity;
  Float_t             AbsLength;  
  Float_t             Gap;
  Float_t             GapMaterial;
  Float_t             GapRefIndex;
  Float_t             Shape; 
  Float_t             ScMaterial; 
  
  Int_t			Run;
  Int_t			Event;
  
  Int_t               NumOptPhotonsAbsorbed;
  Int_t		      NumGammaEnter;

  vector<float>       energyDeposited;
  vector<string>      depositionProcess;
  vector<float>       depositionX;
  vector<float>       depositionY;
  vector<float>       depositionZ;
  vector<string>      opticProcess;
  vector<float>       firstPosX;
  vector<float>       firstPosY;
  vector<float>       firstPosZ;
  
  vector<double>       Prod_Time;

  vector<double>      Wglth_ex;
  vector<double>      OptPhotonEnergy;
  
  vector<int>         Volume;		

  vector<double>      Time;		// Time at interface
  vector<int>         Extraction;	// Extraction face	
  vector<int>         Parent;		// Production process (1 for Cerenkov, 2 for Scintillation, 0 for unknown)
  vector<int>         ID;		// ID of the particle

  vector<double>      Wglth_ex_det;
  vector<double>      Time_det;	
  vector<int>         Parent_det;		
  vector<int>         ID_det;		
  
};