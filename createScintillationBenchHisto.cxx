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
int createScintillationBenchHisto() 
{

  cout << "File to open " << endl;
  std::string rootInputFileName;
  getline( std::cin, rootInputFileName);

  string rootOutputFileName = "./data_" + rootInputFileName;	
  
  cout << "Writing file " << rootOutputFileName << endl;
  TFile * f 	= new TFile(rootInputFileName.c_str(),"OPEN");
  TTree *Singles 	= (TTree*)f->Get("tree");
  cout << "Tree " << Singles -> GetName() << endl;

	Int_t            NumCerenkovPhotons;
	Int_t            NumScintPhotons;
	Int_t            NumOptPhotonsExit;
	Int_t            NumOptPhotonsInterface;
	Int_t            NumOptPhotons;
		
	Int_t hits = 1;
	Int_t control = 1;
	Int_t deposit = 0;
	
	if (deposit == 1)
	{
	  vector<string> *depositionProcess 	= new vector<string>();
	  vector<float> *energyDeposited 	= new vector<float>();
	  vector<float> *depositionX 		= new vector<float>();
	  vector<float> *depositionY 		= new vector<float>();
	  vector<float> *depositionZ 		= new vector<float>();
	  vector<float> *firstPosX 		= new vector<float>();
	  vector<float> *firstPosY 		= new vector<float>();
	  vector<float> *firstPosZ 		= new vector<float>();
	  
	  Singles->SetBranchAddress("depositionProcess",&depositionProcess);
	  Singles->SetBranchAddress("energyDeposited",&energyDeposited);
	  Singles->SetBranchAddress("depositionX",&depositionX);
	  Singles->SetBranchAddress("depositionY",&depositionY);
	  Singles->SetBranchAddress("depositionZ",&depositionZ);
	  Singles->SetBranchAddress("firstPosX",&firstPosX);
	  Singles->SetBranchAddress("firstPosY",&firstPosY);
	  Singles->SetBranchAddress("firstPosZ",&firstPosZ);
	} 

	if (control == 1)
	{
	  vector<double> *Time 			= new vector<double>();	// Bool value (0 for rebounced, 1 for exit)
	  vector<double> *Wglth_ex 		= new vector<double>();	// Bool value (0 for rebounced, 1 for exit)
	  vector<int> *Parent 			= new vector<int>();	// Production process (1 for Cerenkov, 2 for Scintillation, 0 for unknown)
	  
	  Singles->SetBranchAddress("Time",&Time);
	  Singles->SetBranchAddress("Wglth_ex",&Wglth_ex);
	  Singles->SetBranchAddress("Parent",&Parent);
	}

	vector<int> *Extraction		= new vector<int>();	// Interface		
	vector<int> *opticProcess 		= new vector<int>();
	vector<double> *Prod_Time		= new vector<double>();
	vector<double> *OptPhotonEnergy 	= new vector<double>();	
        Singles->SetBranchAddress("Extraction",&Extraction);
	Singles->SetBranchAddress("opticProcess",&opticProcess);
	Singles->SetBranchAddress("OptPhotonEnergy",&OptPhotonEnergy);
	Singles->SetBranchAddress("Prod_Time",&Prod_Time);
	
	vector<int> *Volume			= new vector<int>();		
	vector<double> *Wglth_ex_det		= new vector<double>();
	vector<double> *Time_det		= new vector<double>();	
	vector<int> *Parent_det			= new vector<int>();			
	Singles->SetBranchAddress("Time_det",&Time_det);
	Singles->SetBranchAddress("Parent_det",&Parent_det);
	Singles->SetBranchAddress("Wglth_ex_det", &Wglth_ex_det);
	Singles->SetBranchAddress("Volume",&Volume);
	
	Int_t            NumGammaEnter;
	Singles	-> SetBranchAddress("NumGammaEnter",&NumGammaEnter);
	
	Int_t nentries = Singles->GetEntries(); 
	cout<<nentries<<endl;	
	
	// Production info
	
	TH1F* numCerenkov	 	= new TH1F("numCerenkov","NumCerenkov",100,0,100);
	TH1F* numScintillation 		= new TH1F("numScintillation","NumScintillation",1000,0,80000);
	TH1F* numOptical 		= new TH1F("numOptical","NumOptical",100,0,100);
	TH1F* numopt	 		= new TH1F("numopt","numopt",1000,0,10000);
	TH1F* numcer_pr 		= new TH1F("numcer_pr","numcer_pr",1000,0,10000);
	TH1F* numsc_pr 			= new TH1F("numsc_pr","numsc_pr",1000,0,10000);
	
	TH1F* wlgth_cer_prod 		= new TH1F("wlgth_cer_prod","wlgth_cer_prod",100,0,1e-05);
	TH1F* wlgth_sc_prod 		= new TH1F("wlgth_sc_prod","wlgth_sc_prod",100,0,1e-05);
	
	TH1F* ScintTime_prod 		= new TH1F("ScintTime_prod","ScintTime_prod",80,0,4);
	TH1F* CerTime_prod 		= new TH1F("CerTime_prod","CerTime_prod",300,0,0.3);

	int NumOptPhotons 	= 0;
	int NumCerenkovPhotons 	= 0;
	int NumScintPhotons 	= 0;
	
	int opt 	= 0;
	int cer_pr 	= 0;
	int sc_pr	= 0;
	int num_event_no = 0;
	int num_gamma_enter = 0;
	
	ofstream myfile1;
	ofstream myfile2;
	myfile1.open ("LSO_number.txt");
        myfile2.open ("LSO_wavelength.txt");
	
	for (Int_t i=0; i<nentries; i++)
        {   
	  if(i%10000000 == 0 && i!=0)
	  {
	    cout << "Events analyzed    " << i << endl;
	  }			
	  Singles->GetEntry(i);
	  cout<<NumGammaEnter<<endl;
	  if (NumGammaEnter == 1)
	  {num_gamma_enter++;}
	  if(opticProcess->size() != 0)
	  {
	    NumOptPhotons = NumOptPhotons + opticProcess->size();	 
	    opt++;
	    int contr1 = 0;
	    int contr2 = 0; 
	    for(int j=0; j<OptPhotonEnergy->size(); j++)
	    {
	      if (opticProcess->at(j) == 1)
	      {
		if (contr1 == 0)
		{
		  cer_pr++;
		  contr1 = 1;
		}
	        wlgth_cer_prod	-> Fill(OptPhotonEnergy->at(j));
		myfile2 << OptPhotonEnergy->at(j) << endl;
		CerTime_prod	-> Fill(Prod_Time->at(j));
		NumCerenkovPhotons++;
	      }
	      if (opticProcess->at(j) == 2)
	      {
		if (contr2 == 0)
		{
		  sc_pr++;
		  contr2 = 1;
		}
	        wlgth_sc_prod  	-> Fill(OptPhotonEnergy->at(j));
		ScintTime_prod 	-> Fill(Prod_Time->at(j));
		NumScintPhotons++;
	      }
	    }	
	    numCerenkov		-> Fill(NumCerenkovPhotons);
	    myfile1 << NumCerenkovPhotons << endl;

	    numScintillation 	-> Fill(NumScintPhotons);
	    numOptical 		-> Fill(NumOptPhotons);
	  }
	  else {num_event_no++;}
	  NumOptPhotons 	= 0;
	  NumCerenkovPhotons 	= 0;
       	  NumScintPhotons 	= 0;
	}

	cout << "Processes = " << opt << endl;
	cout << "Scintillation processes = " << cer_pr << endl;
	cout << "Gamma enter = " << num_gamma_enter << endl;
	cout << "No processes = " << num_event_no << endl;

	
	numopt		-> Fill(opt);	
	numcer_pr 	-> Fill(cer_pr);	
	numsc_pr 	-> Fill(sc_pr);	

	myfile1.close();
	myfile2.close();
	
	// Info at exit
	
	if(control == 1)
	{
	  cout << "Exit begins" << endl;
	  
	  TH1F* numextracted 		= new TH1F("numextracted","Numextracted",5000,0,5000);
	  TH1F* numextracted_side 	= new TH1F("numextracted_side","Numextracted_side",5000,0,5000);
	  TH1F* numextracted_source 	= new TH1F("numextracted_source","Numextracted_source",5000,0,5000);
	  TH1F* numextracted_opposite 	= new TH1F("numextracted_opposite","Numextracted_opposite",5000,0,5000);
		
	  TH1F* numScint_ex 		= new TH1F("numScint_ex","NumScint_ex",1000,0,4000);
	  TH1F* numCer_ex 		= new TH1F("numCer_ex","NumCer_ex",100,0,100);
	  TH1F* numCer_ex_norm 		= new TH1F("numCer_ex_norm","NumCer_ex_norm",100,0,100);
	  TH1F* CerTime_ex 		= new TH1F("CerTime_ex","CerTime_ex",400,0,0.4);
	  TH1F* ScintTime_ex 		= new TH1F("ScintTime_ex","ScintTime_ex",4000,0,4);
	  TH1F* Time_ex 		= new TH1F("Time_ex","Time_ex",4000,0,4);

	  TH1F* wlgth_cer_exit 		= new TH1F("wlgth_cer_exit","wlgth_cer_exit",100,0,1e-05);
	  TH1F* wlgth_sc_exit 		= new TH1F("wlgth_sc_exit","wlgth_sc_exit",100,0,1e-05); 
	
	  int NumExtracted_tot 			= 0;
	  int NumExtracted_Side_tot		= 0;
	  int NumExtracted_Source_tot   	= 0;
 	  int NumExtracted_Opposite_tot 	= 0;
	  int numScint_tot 			= 0;
	  int numCer_tot 			= 0; 
	  int numCer_norm_tot 			= 0;	
	
	  for (int i=0; i<nentries; i++)
	  {
	    int NumExtracted 		= 0;
	    int NumExtracted_Side	= 0;
	    int NumExtracted_Source   	= 0;
	    int NumExtracted_Opposite 	= 0;
	    int numScint 		= 0;
	    int numCer 			= 0; 
	    int numCer_norm 		= 0;
	  
	    Singles->GetEntry(i);
	    if(Extraction->size() != 0)
	    {
	      NumExtracted = Extraction -> size();
	      for(int j=0; j<Extraction->size(); j++)
	      {
	        if(Extraction -> at(j) == 1)
	        {
		  NumExtracted_Opposite++;
	        }
	        else if(Extraction -> at(j) == 2)
	        {
		  NumExtracted_Source++;
	        }
	        else if(Extraction -> at(j) == 3)
	        {
		  NumExtracted_Side++;
	        }
	        else
	        {
		  cout << "Anomalous extraction" << endl;
	        }
	
	        if(Parent->at(j) == 2)		
	        {
  	          numScint++;
	          ScintTime_ex -> Fill(Time->at(j));
	          Time_ex -> Fill(Time->at(j));
	          wlgth_sc_exit -> Fill(Wglth_ex->at(j));
	        }
	        else if(Parent->at(j) == 1)
                {
                  numCer++;
	          if(Wglth_ex->at(j) < 3e-06 && Wglth_ex->at(j) > 2e-06)
	          {
	            numCer_norm++;
	          } 
	          CerTime_ex -> Fill(Time->at(j));
		  Time_ex -> Fill(Time->at(j));
		  wlgth_cer_exit -> Fill(Wglth_ex->at(j));
	        }
	        else
	        {
	          cout << Parent->at(j) <<endl;
	        }
              }
	      numextracted ->Fill(NumExtracted);
	      if(NumExtracted_Opposite != 0)
	      {
	        numextracted_opposite ->Fill(NumExtracted_Opposite);
	      }
	      if(NumExtracted_Side != 0)
	      {  
	        numextracted_side ->Fill(NumExtracted_Side);
	      }
	      if(NumExtracted_Source != 0)
	      {
	        numextracted_source ->Fill(NumExtracted_Source);
	      }
	      numScint_ex -> Fill(numScint);		
	      numCer_ex -> Fill(numCer);
	      if(numCer_norm != 0)
	      {
	        numCer_ex_norm -> Fill(numCer_norm);
	      }
	    }
	    NumExtracted_tot 		= NumExtracted_tot + NumExtracted;
	    NumExtracted_Side_tot	= NumExtracted_Side_tot + NumExtracted_Side;
	    NumExtracted_Source_tot   	= NumExtracted_Source_tot + NumExtracted_Source;
	    NumExtracted_Opposite_tot 	= NumExtracted_Opposite_tot + NumExtracted_Opposite;
	    numScint_tot 		= numScint_tot + numScint;
	    numCer_tot 			= numCer_tot + numCer; 
	    numCer_norm_tot 		= numCer_norm_tot + numCer_norm;
	  }
	
	  cout << "NumExtracted_tot = " 		<< NumExtracted_tot		<< endl;
	  cout << "NumExtracted_Side_tot = " 		<< NumExtracted_Side_tot 	<< endl;
	  cout << "NumExtracted_Source_tot = " 	<< NumExtracted_Source_tot 	<< endl;
	  cout << "NumExtracted_Opposite_tot = " 	<< NumExtracted_Opposite_tot 	<< endl;
	  cout << "numScint_tot = " 			<< numScint_tot 		<< endl;
	  cout << "numCer_tot = " 			<< numCer_tot 			<< endl; 
	  cout << "numCer_norm_tot = " 		<< numCer_norm_tot 		<< endl;
        }
	
	
	if(hits == 1)
	{
          TH1F* num_detector 		= new TH1F("num_detector","Num_detector",5000,0,5000);
	  TH1F* num_det_win 		= new TH1F("num_det_win","num_det_win",5000,0,5000);
	  TH1F* num_det_cry 		= new TH1F("num_det_cry","num_det_cry",5000,0,5000);
	  TH1F* time_det_win		= new TH1F("time_det_win","time_det_win",4000,0,4);
	  TH1F* time_det_cry 		= new TH1F("time_det_cry","time_det_cry",4000,0,4);
	  TH1F* time_det_tot 		= new TH1F("time_det_tot","time_det_tot",4000,0,4);
	  TH1F* wlgth_det		= new TH1F("wlgth_det","wlgth_det",100,0,1e-05);

	  int NumDet_tot		= 0;
	  int NumDetWin_tot		= 0;
	  int NumDetCry_tot		= 0;
	  int Num_norm_tot		= 0;
	
	  for (int i=0; i<nentries; i++)
	  {
	    if(i%10000000 == 0 && i!=0)
	    {
	      cout << "Events analyzed    " << i << endl;
	    }
	 
	    int NumDet		= 0;
	    int NumDetWin	= 0;
	    int NumDetCry	= 0;
	    int Num_norm	= 0;
	  
	    Singles->GetEntry(i);
	  
	    //if(Volume -> size() != 0)
	    //{
	      NumDet = Volume -> size();
	      for(int j=0; j<Volume -> size(); j++)
	      {
	        if(Volume -> at(j) == 1)
	        {
	          NumDetCry++;
	        }
	        else if(Volume -> at(j) == 2)
	        {
	          NumDetWin++;
	        }
	        else
	        {
	          cout << "Anomalous extraction" << endl;
	        }
	      
	        if(Parent_det->at(j) == 1)		
	        { 
		  if(Volume -> at(j) == 1)
	          {
	            time_det_cry -> Fill(Time_det->at(j));
		  }
		  else if(Volume -> at(j) == 2)
	          {
		    time_det_win -> Fill(Time_det->at(j));
		  }
		  time_det_tot -> Fill(Time_det->at(j));
		  wlgth_det    -> Fill(Wglth_ex_det->at(j));
	          if(Wglth_ex_det->at(j) < 3e-06 && Wglth_ex_det->at(j) > 2e-06)
	          {
	            Num_norm++;
	          }
	        }
	      }
	 
	      //if(NumDet != 0)
	      //{
	        num_detector -> Fill(NumDet);
	      //}
	      //if(NumDetCry != 0)
	      //{  
	        num_det_cry -> Fill(NumDetCry);
	      //}
	      //if(NumDetWin != 0)
	      //{
	        num_det_win -> Fill(NumDetWin);
	      //}
	    //}
	    NumDet_tot		= NumDet_tot + NumDet;
	    NumDetWin_tot   	= NumDetWin_tot + NumDetWin;
	    NumDetCry_tot 	= NumDetCry_tot + NumDetCry;
	    Num_norm_tot 	= Num_norm_tot + Num_norm;
	  }
	
	  cout << "NumDet_tot = "		<< NumDet_tot		<< endl;
	  cout << "NumDetWin_tot = "		<< NumDetWin_tot 	<< endl;
	  cout << "NumDetCry_tot = "		<< NumDetCry_tot 	<< endl;
	  cout << "Num_norm_tot = "		<< Num_norm_tot 	<< endl;	
	}
	
	TFile * data 	= new TFile(rootOutputFileName.c_str(),"RECREATE");

        numCerenkov 		-> Write();
	numScintillation 	-> Write();
	numOptical		-> Write();
	wlgth_cer_prod		-> Write();
	wlgth_sc_prod		-> Write();
	CerTime_prod 		-> Write();	
	ScintTime_prod 		-> Write();
	
	numopt			-> Write();	
	numcer_pr 		-> Write();	
	numsc_pr 		-> Write();	
	
	if(control == 1)
	{
	  numextracted		 -> Write();
	  numScint_ex		 -> Write();
	  numCer_ex		 -> Write();
	  numCer_ex_norm	 -> Write();
	  CerTime_ex 		 -> Write();	
	  ScintTime_ex 		 -> Write();
	  Time_ex 		 -> Write();
	  wlgth_cer_exit	 -> Write();
	  wlgth_sc_exit		 -> Write();
	  numextracted 		 -> Write();
	  numextracted_side 	 -> Write();
	  numextracted_source 	 -> Write();
	  numextracted_opposite -> Write();
	}
	  
	if(hits == 1)
	{
	  num_detector 		-> Write();
	  num_det_win 		-> Write();
	  num_det_cry 		-> Write();
	  time_det_win		-> Write();
	  time_det_cry 		-> Write();
	  time_det_tot 		-> Write();
	  wlgth_det		-> Write();
	}
	  
	return 0;
}
