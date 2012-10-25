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
	string rootInputFileName = "./out.root";
	TFile * f 	= new TFile(rootInputFileName.c_str(),"UPDATE");
	TTree *Singles 	= (TTree*)f->Get("tree");

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

	vector<float> *Time = new vector<float>();	// Bool value (0 for rebounced, 1 for exit)
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
	
        TH2F* energy_dep_xy = new TH2F("Energy deposition x-y","Energy deposition x-y",100,-50,50,100,-20,100);
        TH2F* cerenkovDensity = new TH2F("cerenkovDensity","cerenkovDensity",100,-20,20,100,-20,70);
        TH2F* scintillationDensity = new TH2F("scintillationDensity","scintillationDensity",100,-50,50,100,-20,100);
        TH1F* depY = new TH1F("depY","depY",1000,-20,100);
	
	Float_t x[100000000], y[100000000], x1[100000000], y1[100000000], x2[100000000], y2[100000000], x3[100000000], y3[100000000],x4[100000000], y4[100000000];
	Float_t ox[100000000], oy[100000000], ox1[100000000], oy1[100000000];
	Int_t on=0;
	Int_t on1=0;

	Int_t n=0;
	Int_t n1=0;
	Int_t n2=0;
	Int_t n3=0;
	Int_t n4=0;

	Int_t nentries = Singles->GetEntries(); 
	cout<<nentries<<endl;

	for (Int_t i=0; i<nentries; i++){	
		Singles->GetEntry(i);
		if(depositionProcess->size()>0){
			for(int j = 0; j<depositionX->size(); j++){

                                energy_dep_xy -> Fill(depositionX->at(j), depositionZ->at(j), - energyDeposited->at(j));
				depY -> Fill(depositionZ -> at(j), -energyDeposited -> at(j));
                                
				if(depositionProcess->at(j)=="Cerenkov"){
					x3[n3] = depositionX->at(j);
					y3[n3] = depositionZ->at(j);
					n3++;
				}else if(depositionProcess->at(j)=="Scintillation"){
					x4[n3] = depositionX->at(j);
					y4[n3] = depositionZ->at(j);
					n4++;
				}else{
					//cout<<depositionProcess->at(j)<<endl;
				}
			}

		}

		if(opticProcess->size()>0){
		  for(int j = 0; j<opticProcess->size(); j++){
		    if(opticProcess->at(j)=="Cerenkov"){
		      ox[on] = firstPosX->at(j);
		      oy[on] = firstPosZ->at(j);
		      on++;
		      cerenkovDensity->Fill(firstPosX->at(j),firstPosZ->at(j));
		    }else if(opticProcess->at(j)=="Scintillation"){
		      ox1[on1] = firstPosX->at(j);
		      oy1[on1] = firstPosZ->at(j);
		      on1++;
		      scintillationDensity->Fill(firstPosX->at(j),firstPosZ->at(j));
		    }else {
		      cout<<opticProcess->at(j)<<endl; 
		    }
		  }
		}
	}

        TH1F* numCerenkov = new TH1F("numCerenkov","NumCerenkov",30,0,60);
	TH1F* numScintillation = new TH1F("numScintillation","NumScintillation",1000,0,12000);
	for (Int_t i=0; i<nentries; i++)
	{	
		Singles->GetEntry(i);
		if (NumOptPhotons != 0)
		{
		numCerenkov -> Fill(NumCerenkovPhotons);
		cout << i << "\t" << "Cerenkov "<< "\t" << NumCerenkovPhotons << endl;
		numScintillation -> Fill(NumScintPhotons);	
		cout << i << "\t" << "Scint "<< "\t" << NumScintPhotons << endl;	
		}		
	}

	TH1F* numextracted = new TH1F("numextracted","Numextracted",100,0,10000);
	TH1F* numScint_ex = new TH1F("numScint_ex","NumScint_ex",100,0,10000);
	TH1F* numCer_ex = new TH1F("numCer_ex","NumCer_ex",100,0,100);
	TH1F* CerTime_ex = new TH1F("CerTime_ex","CerTime_ex",100,0,0.3);
	TH1F* ScintTime_ex = new TH1F("ScintTime_ex","ScintTime_ex",100,0,100);
	for (Int_t i=0; i<nentries; i++)
	{	
		Singles->GetEntry(i);
		numextracted -> Fill(NumOptPhotonsExit);
		//cout << "Event " << i << endl;
		//cout << "Exit photons " << NumOptPhotonsExit << endl;
		//cout << "Size " << IntOut->size() << endl;
		int numScint, numCer;
		int j;		
		for(j = 0; j<IntOut->size(); j++))
		{	
		  if(IntOut->at(j) == 1 && NumOptPhotonsExit!=0)
		  {	
	            //cout << "ciao "<< endl;		
		    if(Parent->at(j) == 2)		
		    {
  		      numScint++;
		      ScintTime_ex -> Fill(Time->at(j));	
		    }
		    else if(Parent->at(j) == 1)
		    {
		      numCer++;
		      CerTime_ex -> Fill(Time->at(j));
		      //cout<<Time->at(j)<<endl;
		    }
		    else
		    {
		      cout << Parent->at(j) <<endl;
		    }
		  }		
		}
		//cout << "Numero intout" << endl;
		//cout << j << endl;
		//cout << "at interface " << NumOptPhotonsInterface <<endl;
		//cout << "-------------" << endl;
		numScint_ex -> Fill(numScint);
		//cout << "Exit photons scint " << numScint << endl;
		numCer_ex -> Fill(numCer);
		//cout << "Exit photons cer " << numCer << endl;
		numScint = 0;
		numCer = 0;
	}
	
	depY -> Scale(1./depY->Integral());
	
	TF1 *attenuation = new TF1("attenuation","[0]*exp(-x/[1])", 1., 90.);
	attenuation -> SetParameters(0.01, 40.);

	TCanvas *c12 = new TCanvas("c12","Cerenkov",600,400);
	//cerenkovDensity->Draw("lego2");
	numCerenkov -> Draw();
	TCanvas *c1 = new TCanvas("c1","Scintillation",600,400);
	//scintillationDensity->Draw("lego2");
	//TCanvas *c66 = new TCanvas("c66","y deposition",600,400);
	//depY ->Fit("attenuation", "R");
        //depY->Draw();	
	numScintillation -> Draw();
	/*
	TGraph *gr = new TGraph(n,x,y);
	TGraph *gr1 = new TGraph(n1,x1,y1);
	TGraph *gr2 = new TGraph(n2,x2,y2);
	TGraph *gr3 = new TGraph(n3,x3,y3);
	TGraph *gr4 = new TGraph(n4,x4,y4);
	gr->SetMarkerColor(4);
	gr1->SetMarkerColor(3);
	gr2->SetMarkerColor(2);
	gr3->SetMarkerColor(5);
	*/
        TCanvas *c8 = new TCanvas("c8","energy_histo",300,300);
	//energy_dep_xy->Draw("lego2");
	numextracted->Draw();
	TCanvas *c = new TCanvas("c","phot",300,300);
	CerTime_ex->Draw();
	//gr->Draw("AP");
       TCanvas *cciao = new TCanvas("cciao","scint",300,300);
	ScintTime_ex->Draw();
	/*	
	TCanvas *c1 = new TCanvas("c1","eIoni",300,300);
	gr1->Draw("AP");
	TCanvas *c2 = new TCanvas("c2","eBrem",300,300);
	gr2->Draw("AP");
	TCanvas *c3 = new TCanvas("c3","Cerenkov",300,300);
	gr3->Draw("AP");
	TCanvas *cAll = new TCanvas("cAll","Single",600,600);
       	gr->Draw("AP");
	gr1->Draw("P");
	gr2->Draw("P");
	gr3->Draw("P");*/
	return 0;
}
