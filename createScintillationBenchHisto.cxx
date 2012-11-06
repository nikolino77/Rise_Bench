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
	Int_t		    NumOptPhotons;

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
	vector<float> *Wglth_ex = new vector<float>();	// Bool value (0 for rebounced, 1 for exit)
	vector<float> *OptPhotonEnergy = new vector<float>();	// Bool value (0 for rebounced, 1 for exit)
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
	//Singles->SetBranchAddress("OptPhotonEnergy",&OptPhotonEnergy);
	//Singles->SetBranchAddress("Wglth_ex",&Wglth_ex);
	
	TH1F* numCerenkov = new TH1F("numCerenkov","NumCerenkov",60,0,60);
	TH1F* numScintillation = new TH1F("numScintillation","NumScintillation",1000,0,80000);

	TH1F* wlgth_cer_prod = new TH1F("wlgth_cer_prod","wlgth_cer_prod",100,0,1e-05);
	TH1F* wlgth_sc_prod = new TH1F("wlgth_sc_prod","wlgth_sc_prod",100,2e-05,4e-05);
	TH1F* wlgth_cer_exit = new TH1F("wlgth_cer_exit","wlgth_cer_exit",100,0,10e-05);
        
/*
        TH2F* energy_dep_xy = new TH2F("Energy deposition x-y","Energy deposition x-y",100,-3,3,100,-5,5);
        TH2F* cerenkovDensity = new TH2F("cerenkovDensity","cerenkovDensity",100,-3,3,100,-5,5);
        TH2F* scintillationDensity = new TH2F("scintillationDensity","scintillationDensity",100,-3,3,100,-5,5);
	
	Float_t x[100000000], y[100000000], x1[100000000], y1[100000000], x2[100000000], y2[100000000], x3[100000000], y3[100000000],x4[100000000], y4[100000000];
	Float_t ox[100000000], oy[100000000], ox1[100000000], oy1[100000000];
	Int_t on=0;
	Int_t on1=0;

	Int_t n=0;
	Int_t n1=0;
	Int_t n2=0;
	Int_t n3=0;
	Int_t n4=0;
*/
	Int_t nentries = Singles->GetEntries(); 
	cout<<nentries<<endl;

	for (Int_t i=0; i<nentries; i++)
        {			
	  Singles->GetEntry(i);
	
	  for(int j=0; j<OptPhotonEnergy->size(); j++)
	  {
		
	    if (NumOptPhotonsExit!=0 && opticProcess->at(j) == "Cerenkov")
	    {
	      cout << OptPhotonEnergy->at(j) << endl;
	      wlgth_cer_prod -> Fill(OptPhotonEnergy->at(j));
	    }
	    if (NumOptPhotonsExit!=0 && opticProcess->at(j) == "Scintillation")
	    {
	      wlgth_sc_prod -> Fill(OptPhotonEnergy->at(j));
	    }
	  }	  

	/*  
	  if(depositionProcess->size()>0)
          {
	    for(int j = 0; j<depositionX->size(); j++)
            {
		                //cout << "----------- energy -------------" << endl;
              energy_dep_xy -> Fill(depositionX->at(j), depositionZ->at(j), - energyDeposited->at(j));                  
	      if(depositionProcess->at(j)=="Cerenkov")
              {
		               // cout << "----------- energy cer -------------" << endl;
	        x3[n3] = depositionX->at(j);
		y3[n3] = depositionZ->at(j);
		n3++;
	      }
              else if(depositionProcess->at(j)=="Scintillation")
              {
                x4[n3] = depositionX->at(j);
		y4[n3] = depositionZ->at(j);
		n4++;
	      }
              else
              {
	        //cout<<depositionProcess->at(j)<<endl;
	      }
	    }
	  }   
          
          if(opticProcess->size()>0)
          {
            for(int j = 0; j<opticProcess->size(); j++)
            {
              if(opticProcess->at(j)=="Cerenkov")
              {
                ox[on] = firstPosX->at(j);
		oy[on] = firstPosZ->at(j);
		on++;
		cerenkovDensity->Fill(firstPosX->at(j),firstPosZ->at(j));
	      }
              else if(opticProcess->at(j)=="Scintillation")
              {
	        ox1[on1] = firstPosX->at(j);
		oy1[on1] = firstPosZ->at(j);
		on1++;
		scintillationDensity->Fill(firstPosX->at(j),firstPosZ->at(j));
	      }
              else 
              {
                cout<<opticProcess->at(j)<<endl; 
	      }
            }
	  }
	*/	  

          if (NumOptPhotons != 0)
	  {
	    numCerenkov -> Fill(NumCerenkovPhotons);
	    //cout << i << "\t" << "Cerenkov "<< "\t" << NumCerenkovPhotons << endl;
	    numScintillation -> Fill(NumScintPhotons);	
            //cout << i << "\t" << "Scint "<< "\t" << NumScintPhotons << endl;	
	  }
	}

	cout<<nentries<<endl;
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
	TH1F* CerTime_ex_smear = new TH1F("CerTime_ex_smear","CerTime_ex_smear",300,0,0.3);
	TH1F* Time_ex_smear = new TH1F("Time_ex_smear","Time_ex_smear",10000,0,10);

	TRandom3 *rand = new TRandom3();

        for (Int_t i=0; i<nentries; i++)
	{	
	  Singles->GetEntry(i);
          //for(j = 0; j<Scint_Time_prod->size(); j++))
	  //{
	  //  ScintTime_prod -> Fill(Scint_Time_prod->at(j));
	  //}

	  for(j = 0; j<Cer_Time_prod->size(); j++))
	  {
	    CerTime_prod -> Fill(Cer_Time_prod->at(j));
	  }

	  if (NumOptPhotonsExit!=0)
          {
	    numextracted -> Fill(NumOptPhotonsExit);
          }
	  //for(j = 0; j<Scint_Time->size(); j++))
	  //{
	  //  ScintTime -> Fill(Scint_Time->at(j));
	  //}
	  for(j = 0; j<Cer_Time->size(); j++))
	  {
	    CerTime -> Fill(Cer_Time->at(j));
	  }
//cout<<"gigi"<<endl;
	  int numScint, numCer;
	  int j;	
if (NumOptPhotonsExit!=0){	
	  for(j = 0; j<IntOut->size(); j++))
	  {	
	    if(IntOut->at(j) == 1)
	    {	
	      if(Parent->at(j) == 2)		
	      {
  	      //  numScint++;
		//ScintTime_ex -> Fill(Time->at(j));
		//Time_ex_smear -> Fill(Time->at(j) /*+ rand->Gaus(0, 0.075)*/);
		//Time_ex -> Fill(Time->at(j));	
	      }
	      else if(Parent->at(j) == 1)
              {
	        numCer++;
	        //wlgth_cer_exit -> Fill(Wglth_ex->at(j));
		CerTime_ex -> Fill(Time->at(j));
		//Time_ex_smear -> Fill(Time->at(j) /*+ rand->Gaus(0, 0.030)*/);
		//CerTime_ex_smear -> Fill(Time->at(j) + rand->Gaus(0, 0.030));
		Time_ex -> Fill(Time->at(j));
	      }
	      else
	      {
	        cout << Parent->at(j) <<endl;
	      }
            }		
	  }//cout<<"gigi2"<<endl;
}
	  if (NumOptPhotonsExit!=0)
          {
	    //numScint_ex -> Fill(numScint);		
	    numCer_ex -> Fill(numCer);
	  }
	  //numScint = 0;
	  numCer = 0;
	}
	//cout<<"gigi3"<<endl;

	TFile * data 	= new TFile(rootOutputFileName.c_str(),"RECREATE");

	//energy_dep_xy 		-> Write();	


	numextracted 		-> Write();
        numScint_ex		-> Write();
	numCer_ex		-> Write();
	
	//cerenkovDensity		-> Write();
	numCerenkov 		-> Write();
	
	//scintillationDensity	-> Write();
	numScintillation 	-> Write();

	ScintTime 		-> Write();
	CerTime			-> Write(); 
	CerTime_ex 		-> Write();	
	ScintTime_ex 		-> Write();
	CerTime_prod 		-> Write();	
	ScintTime_prod 		-> Write();
	Time_ex 		-> Write();
	CerTime_ex_smear	-> Write();
	Time_ex_smear	-> Write();

	wlgth_cer_exit		-> Write();
	wlgth_cer_prod		-> Write();
	wlgth_sc_prod		-> Write();

	return 0;
}
