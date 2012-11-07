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
int checK_ratio() {


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
	      
	Int_t nentries = Singles->GetEntries(); 
	cout<<nentries<<endl;

	TH1F* t_c_50 = new TH1F("t_c_50","t_c_50",50,0,50);
	TH1F* t_sc_50 = new TH1F("t_sc_50","t_sc_50",50,0,50);
	TH1F* t_c_100 = new TH1F("Cerenkov","Cerenkov",50,0,50);
	TH1F* t_sc_100 = new TH1F("Scintillation","Scintillation",50,0,50);
	TH1F* t_c_100_norm = new TH1F("t_c_100_norm","t_c_100_norm",50,0,50);
	TH1F* t_sc_100_norm = new TH1F("t_sc_100_norm","t_sc_100_norm",50,0,50);
	TH1F* t_c_150 = new TH1F("t_c_150","t_c_150",50,0,50);
	TH1F* t_sc_150 = new TH1F("t_sc_150","t_sc_150",50,0,50);
	TH1F* t_c_200 = new TH1F("t_c_200","t_c_200",50,0,50);
	TH1F* t_sc_200 = new TH1F("t_sc_200","t_sc_200",50,0,50);
	TH1F* t_c_200_norm = new TH1F("t_c_200_norm","t_c_200_norm",50,0,50);
	TH1F* t_sc_200_norm = new TH1F("t_sc_200_norm","t_sc_200_norm",50,0,50);
	TH1F* t_c_300 = new TH1F("t_c_300","t_c_300",50,0,50);
	TH1F* t_sc_300 = new TH1F("t_sc_300","t_sc_300",50,0,50);	

  	int num_ce_50 = 0;
	int num_sc_50 = 0;
	int num_ce_100 = 0;
        int num_sc_100 = 0;
	int num_ce_100_norm = 0;
        int num_sc_100_norm = 0;
	int num_ce_150 = 0;
	int num_sc_150 = 0;
  	int num_ce_200 = 0;
	int num_sc_200 = 0;
  	int num_ce_200_norm = 0;
	int num_sc_200_norm = 0;
	int num_ce_300 = 0;
	int num_sc_300 = 0;	
	double start   = 0.06;

	int j;
        for (Int_t i=0; i<nentries; i++)
	{	
	  Singles->GetEntry(i);		
	  int extr = 0;
          for(j = 0; j<IntOut->size(); j++))
	  {	
	    if(IntOut->at(j) == 1 && NumOptPhotonsExit!=0)
	    {
	      wlgth = Wglth -> at(extr);
	      extr++;
	      if(Parent->at(j) == 2)		
	      {
		if (Time->at(j) < 0.05 +start)
		{
		  num_sc_50 ++;
		}
		if (Time->at(j) < 0.1 + start)
		{
		  num_sc_100 ++;
		}
		if (Time->at(j) < 0.15 + start)
		{
		  num_sc_150 ++;
		}
		if (Time->at(j) < 0.2 + start)
		{
		  num_sc_200 ++;
		}
		if (Time->at(j) < 0.3 + start)
		{
		  num_sc_300 ++;
		}      
              }
	      else if(Parent->at(j) == 1)
              {
	        if (Time->at(j) < 0.05 +start)
		{
		  num_ce_50 ++;
		}
		if (Time->at(j) < 0.1 + start)
		{
		  num_ce_100 ++;
		}
		if (Time->at(j) < 0.15 + start)
		{
		  num_ce_150 ++;
		}
		if (Time->at(j) < 0.2 + start)
		{
		  num_ce_200 ++;
		}
		if (Time->at(j) < 0.3 + start)
		{
		  num_ce_300 ++;
		}
	      }
	      else
	      {
	        cout << "Anomaly -> " << Parent->at(j) <<endl;
	      }
	      if(Parent->at(j) == 1 && wlgth < && wlgth >)
              {
		if (Time->at(j) < 0.1 + start)
		{
		  num_ce_100_norm ++;
		}
		if (Time->at(j) < 0.2 + start)
		{
		  num_ce_200_norm ++;
		}
	      }
            }		
	  }

	  if (NumOptPhotonsExit!=0)
          {
	    t_c_50 -> Fill(num_ce_50);
	    t_sc_50 -> Fill(num_sc_50);
	    t_c_100 -> Fill(num_ce_100);
	    t_sc_100 -> Fill(num_sc_100);
	    t_c_100_norm -> Fill(num_ce_100_norm);
	    t_sc_100_norm -> Fill(num_sc_100_norm);
	    t_c_150 -> Fill(num_ce_150);
	    t_sc_150 -> Fill(num_sc_150);
	    t_c_200 -> Fill(num_ce_200);
	    t_sc_200 -> Fill(num_sc_200);
	    t_c_200_norm -> Fill(num_ce_200_norm);
	    t_sc_200_norm -> Fill(num_sc_200_norm);
	    t_c_300 -> Fill(num_ce_300);
	    t_sc_300 -> Fill(num_sc_300);
	  }
	
	num_ce_50 = 0;
	num_sc_50 = 0;
	num_ce_100 = 0;
        num_sc_100 = 0;
	num_ce_100_norm = 0;
        num_sc_100_norm = 0;
	num_ce_150 = 0;
	num_sc_150 = 0;
  	num_ce_200 = 0;
	num_sc_200 = 0;
	num_ce_200_norm = 0;
	num_sc_200_norm = 0;
        num_ce_300 = 0;
	num_sc_300 = 0;
	}
	

	TFile * data 	= new TFile("data.root","RECREATE");

	t_c_50			-> Write();
	t_sc_50			-> Write();
	t_c_100			-> Write();
	t_sc_100		-> Write();
	t_c_100_norm		-> Write();
	t_sc_100_norm		-> Write();
	t_c_150			-> Write();
	t_sc_150		-> Write();
	t_c_200			-> Write();
	t_sc_200		-> Write();
	t_c_200_norm		-> Write();
	t_sc_200_norm		-> Write();
	t_c_300			-> Write();
	t_sc_300		-> Write();

	TCanvas *c1 = new TCanvas("c1");
	TLegend *leg1 = new TLegend(0.1,0.7,0.48,0.9);
	leg1 -> AddEntry(t_c_100, "Cerenkov", "l");
	leg1 -> AddEntry(t_sc_100, "Scintillation", "l");
	t_c_100			-> SetLineColor(kRed);
	t_sc_100		-> SetLineColor(kBlue);
	t_sc_100			-> Draw();
	t_c_100		-> Draw("same");
	leg1			-> Draw();
	c1			-> Write();	

	TCanvas *c2 = new TCanvas("c2");
	t_c_200			-> SetLineColor(kRed);
	t_sc_200		-> SetLineColor(kBlue);
	t_c_200			-> Draw();
	t_sc_200		-> Draw("same");
	c2			-> Write();

	TCanvas *c3 = new TCanvas("c3");
	t_c_100_norm		-> SetLineColor(kRed);
	t_sc_100_norm		-> SetLineColor(kBlue);
	t_c_100_norm		-> Draw();
	t_sc_100_norm		-> Draw("same");
	c3			-> Write();
	
	TCanvas *c4 = new TCanvas("c4");
	t_c_200_norm		-> SetLineColor(kRed);
	t_sc_200_norm		-> SetLineColor(kBlue);
	t_c_200_norm		-> Draw();
	t_sc_200_norm		-> Draw("same");
	c4			-> Write();

	TGraph* cer = new TGraph(5);
	cer -> SetPoint (1, 50, t_c_50->Integral(2, 50)/t_sc_300->Integral(2, 50));
	cer -> SetPoint (2, 100, t_c_100->Integral(2, 50)/t_sc_300->Integral(2, 50));
	cer -> SetPoint (3, 150, t_c_150->Integral(2, 50)/t_sc_300->Integral(2, 50));
	cer -> SetPoint (4, 200, t_c_200->Integral(2, 50)/t_sc_300->Integral(2, 50));
	cer -> SetPoint (5, 300, t_c_300->Integral(2, 50)/t_sc_300->Integral(2, 50));
	cer -> SetMarkerColor(kRed);
	
	TGraph* cer_norm = new TGraph(2);
	cer_norm -> SetPoint (1, 100, t_c_100_norm->Integral(2, 50)/t_sc_200_norm->Integral(2, 50));
	cer_norm -> SetPoint (2, 200, t_c_200_norm->Integral(2, 50)/t_sc_200_norm->Integral(2, 50));
	cer_norm -> SetMarkerColor(kRed);

	TGraph* sc = new TGraph(5);
	sc -> SetPoint (1, 50, t_sc_50->Integral(2, 50)/t_sc_300->Integral(2, 50));
	sc -> SetPoint (2, 100, t_sc_100->Integral(2, 50)/t_sc_300->Integral(2, 50));
	sc -> SetPoint (3, 150, t_sc_150->Integral(2, 50)/t_sc_300->Integral(2, 50));
	sc -> SetPoint (4, 200, t_sc_200->Integral(2, 50)/t_sc_300->Integral(2, 50));
	sc -> SetPoint (5, 300, t_sc_300->Integral(2, 50)/t_sc_300->Integral(2, 50));
	sc -> SetMarkerColor(kBlue);
	
	TGraph* sc_norm = new TGraph(2);
	sc_norm -> SetPoint (1, 100, t_sc_100_norm->Integral(2, 50)/t_sc_200_norm->Integral(2, 50));
	sc_norm -> SetPoint (2, 200, t_sc_200_norm->Integral(2, 50)/t_sc_200_norm->Integral(2, 50));
	sc_norm -> SetMarkerColor(kRed);

	TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
	leg -> AddEntry(cer, "Cerenkov", "l");
	leg -> AddEntry(sc, "Scintillation", "l");

	TLegend *leg_norm = new TLegend(0.1,0.7,0.48,0.9);
	leg_norm -> AddEntry(cer_norm, "Cerenkov", "l");
	leg_norm -> AddEntry(sc_norm, "Scintillation", "l");
	
	TCanvas *c5 = new TCanvas("c5");
	sc  -> Draw("APL");
	cer -> Draw("SAME");
	leg -> Draw();
	
	TCanvas *c6 = new TCanvas("c6");
	sc_norm  -> Draw("APL");
	cer_norm -> Draw("SAME");
	leg -> Draw();
	
	return 0;
}
