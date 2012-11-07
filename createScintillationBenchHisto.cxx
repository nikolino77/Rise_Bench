#include <cmath>
#include "TGraph.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TH2F.h"
#include "TApplication.h"
#include <cstdlib>
using namespace std;

#define PI 3.14159265
int createScintillationBenchHisto() {

	string pathName = "./";
	string length = "out";
	string finish = "";
	string rootInputFileName = "./" + length + "" + finish + ".root";
	string rootOutputFileName = "./data_" + length + "_" + finish + ".root";
	cout << "Opening file " << rootInputFileName << endl;
	cout << "Writing file " << rootOutputFileName << endl;
	TFile * f 	= new TFile(rootInputFileName.c_str(),"OPEN");
	TTree *Singles 	= (TTree*)f->Get("tree");
	cout << "Tree " << Singles -> GetName() << endl;

  	Int_t               NumCerenkovPhotons;
  	Int_t               NumScintPhotons;
	Int_t	            NumOptPhotonsExit;
	Int_t	            NumOptPhotonsInterface;
	Int_t		        NumOptPhotons;

	vector<string> *depositionProcess = new vector<string>();
	vector<float> *energyDeposited 	= new vector<float>();
	vector<float> *depositionX = new vector<float>();
	vector<float> *depositionY = new vector<float>();
	vector<float> *depositionZ = new vector<float>();

	vector<string> *opticProcess = new vector<string>();
	vector<float> *firstPosX = new vector<float>();
	vector<float> *firstPosY = new vector<float>();
	vector<float> *firstPosZ = new vector<float>();
	vector<float> *Cer_Time = new vector<float>();
	vector<float> *Scint_Time = new vector<float>();
	vector<float> *Cer_Time_prod = new vector<float>();
	vector<float> *Scint_Time_prod = new vector<float>();

	vector<float> *Time = new vector<float>();	// Bool value (0 for rebounced, 1 for exit)
	vector<double> *Wglth_ex = new vector<double>();	// Bool value (0 for rebounced, 1 for exit)
	vector<double> *OptPhotonEnergy = new vector<double>();	
	vector<int> *IntOut = new vector<int>();	// Time at interface	
	vector<int> *Parent = new vector<int>();	// Production process (1 for Cerenkov, 2 for Scintillation, 0 for unknown)
	vector<int> *ID = new vector<int>();		// ID of the particle

	Singles->SetBranchAddress("depositionProcess",&depositionProcess);
	Singles->SetBranchAddress("energyDeposited",&energyDeposited);
	Singles->SetBranchAddress("depositionX",&depositionX);
	Singles->SetBranchAddress("depositionY",&depositionY);
	Singles->SetBranchAddress("depositionZ",&depositionZ);

	Singles->SetBranchAddress("NumCerenkovPhotons",&NumCerenkovPhotons);
	Singles->SetBranchAddress("NumScintPhotons",&NumScintPhotons);
	Singles->SetBranchAddress("NumOptPhotonsExit",&NumOptPhotonsExit);
	Singles->SetBranchAddress("NumOptPhotonsInterface",&NumOptPhotonsInterface);
	Singles->SetBranchAddress("NumOptPhotons",&NumOptPhotons);

	Singles->SetBranchAddress("Time",&Time);
	Singles->SetBranchAddress("IntOut",&IntOut);
	Singles->SetBranchAddress("Parent",&Parent);
	Singles->SetBranchAddress("ID",&ID);
	
	Singles->SetBranchAddress("opticProcess",&opticProcess);
	Singles->SetBranchAddress("firstPosX",&firstPosX);
	Singles->SetBranchAddress("firstPosY",&firstPosY);
	Singles->SetBranchAddress("firstPosZ",&firstPosZ);
	Singles->SetBranchAddress("Scint_Time",&Scint_Time);
	Singles->SetBranchAddress("Cer_Time",&Cer_Time);
	Singles->SetBranchAddress("Scint_Time_prod",&Scint_Time_prod);
	Singles->SetBranchAddress("Cer_Time_prod",&Cer_Time_prod);
	Singles->SetBranchAddress("OptPhotonEnergy",&OptPhotonEnergy);
	Singles->SetBranchAddress("Wglth_ex",&Wglth_ex);
	
	TH1F* numCerenkov = new TH1F("numCerenkov","NumCerenkov",60,0,60);
	TH1F* numScintillation = new TH1F("numScintillation","NumScintillation",1000,0,80000);

	TH1F* wlgth_cer_prod = new TH1F("wlgth_cer_prod","wlgth_cer_prod",100,0,1e-05);
	TH1F* wlgth_sc_prod = new TH1F("wlgth_sc_prod","wlgth_sc_prod",100,2e-05,4e-05);
	   

	Int_t nentries = Singles->GetEntries(); 
	cout<<nentries<<endl;

	for (Int_t i=0; i<nentries; i++)
    {			
	  Singles->GetEntry(i);
	  if(NumOptPhotons != 0)
	  {
	    numCerenkov -> Fill(NumCerenkovPhotons);
	    numScintillation -> Fill(NumScintPhotons);
	    for(int j=0; j<OptPhotonEnergy->size(); j++)
	    {
	      if (opticProcess->at(j) == "Cerenkov")
	      {
	        wlgth_cer_prod -> Fill(OptPhotonEnergy->at(j));
	      }
	      if (opticProcess->at(j) == "Scintillation")
	      {
	        wlgth_sc_prod -> Fill(OptPhotonEnergy->at(j));
	      }
	    }	
	  }
	}

	TH1F* numextracted = new TH1F("numextracted","Numextracted",1000,0,5000);
	TH1F* numScint_ex = new TH1F("numScint_ex","NumScint_ex",1000,0,4000);
	TH1F* numCer_ex = new TH1F("numCer_ex","NumCer_ex",15,0,15);
	TH1F* CerTime_ex = new TH1F("CerTime_ex","CerTime_ex",400,0,0.4);
	TH1F* ScintTime_ex = new TH1F("ScintTime_ex","ScintTime_ex",4000,0,4);
	TH1F* Time_ex = new TH1F("Time_ex","Time_ex",4000,0,4);
	TH1F* ScintTime_prod = new TH1F("ScintTime_prod","ScintTime_prod",80,0,4);
	TH1F* CerTime_prod = new TH1F("CerTime_prod","CerTime_prod",100,0,0.3);
	TH1F* ScintTime = new TH1F("ScintTime","ScintTime",1000,0,1);
	TH1F* CerTime = new TH1F("CerTime","CerTime",100,0,0.3);
    TH1F* wlgth_cer_exit = new TH1F("wlgth_cer_exit","wlgth_cer_exit",100,0,1e-05);
     
	for (Int_t i=0; i<nentries; i++)
	{	
	  Singles->GetEntry(i);
      
      for(j = 0; j<Scint_Time_prod->size(); j++))
	  {
	    ScintTime_prod -> Fill(Scint_Time_prod->at(j));
	  }
	  for(j = 0; j<Cer_Time_prod->size(); j++))
	  {
	    CerTime_prod -> Fill(Cer_Time_prod->at(j));
	  }

	  if (NumOptPhotonsExit!=0)
      {
	    numextracted -> Fill(NumOptPhotonsExit);
      }
	  for(j = 0; j<Scint_Time->size(); j++))
	  {
	    ScintTime -> Fill(Scint_Time->at(j));
	  }
	  for(j = 0; j<Cer_Time->size(); j++))
	  {
	    CerTime -> Fill(Cer_Time->at(j));
	  }

	  int numScint, numCer;
	  int j;	
      if (NumOptPhotonsExit!=0)
      {	
        for(j = 0; j<Wglth_ex->size(); j++)
        {
          wlgth_cer_exit -> Fill(Wglth_ex->at(j));   
        }
	    for(j = 0; j<IntOut->size(); j++)
	    {	
	      if(IntOut->at(j) == 1)
	      {	
	        if(Parent->at(j) == 2)		
	        {
  	          numScint++;
	          ScintTime_ex -> Fill(Time->at(j));
	          Time_ex -> Fill(Time->at(j));	
	        }
	        else if(Parent->at(j) == 1)
                {
	          numCer++;
	          CerTime_ex -> Fill(Time->at(j));
		  Time_ex -> Fill(Time->at(j));
	        }
	        else
	        {
	          cout << Parent->at(j) <<endl;
	        }
              }		
	    }    
	    numScint_ex -> Fill(numScint);		
	    numCer_ex -> Fill(numCer);
	  }
	  numScint = 0;
	  numCer = 0;
	}
	
	TFile * data 	= new TFile(rootOutputFileName.c_str(),"RECREATE");

	numextracted 		-> Write();
    numScint_ex			-> Write();
	numCer_ex			-> Write();
	numCerenkov 		-> Write();
	numScintillation 	-> Write();
	ScintTime 			-> Write();
	CerTime				-> Write(); 
	CerTime_ex 			-> Write();	
	ScintTime_ex 		-> Write();
	CerTime_prod 		-> Write();	
	ScintTime_prod 		-> Write();
	Time_ex 			-> Write();
	wlgth_cer_exit		-> Write();
	wlgth_cer_prod		-> Write();
	wlgth_sc_prod		-> Write();

	return 0;
}
