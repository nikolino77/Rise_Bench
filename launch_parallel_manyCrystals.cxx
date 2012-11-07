#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "TFile.h"
#include <cstdlib> 
#include "ConfigFile.cc"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <threadpool.hpp>

using namespace std;
using boost::mutex;
using boost::thread;

//TO COMPILE "from6to5Root" 
//g++ -Wall -ansi launch_parallel_manyCrystals.cxx -o launchParallelManyCrystalsEXE `root-config --cflags --glibs` -lboost_thread




void myThread(int filenum) {
	//COPY CFG FILE
	ostringstream temp;
	temp << filenum;
	
	string code = "_" + filenum.str() + "_";
	string newConfigFile = "crystal" + code + ".cfg";

	//string command = "cp ../crystal.cfg " + newConfigFile;
	//cout<<command<<endl;
	//system(command.c_str());

	//MODIFY PARAMETERS
	newConfigFile = "./" + newConfigFile;
	ConfigFile reconCfg(newConfigFile.c_str());	

	ostringstream buffer;
	buffer <<xDim;
	reconCfg.setValue("crystalx",buffer.str());
	ostringstream buffer1;
	buffer1 <<yDim;
	reconCfg.setValue("crystaly",buffer1.str());
	reconCfg.setValue("treatedFaces",temp1.str());
	reconCfg.setValue("sensorCoupling",temp2.str());

	string rootFile = "out"+code+".root";
	command = "./crystal "+newConfigFile+" "+rootFile;
	cout<<command<<endl;
	system(command.c_str());

	//CANCEL NEW CONFIG FILE
	/*command = "rm "+newConfigFile;
	cout<<command<<endl;
	system(command.c_str());*/

	cout<<"done "<<boost::this_thread::get_id()<<endl;
};



int main(int argc, char** argv) {

	Float_t xVector[7] = {2.25,2.50,2.90,4.20,5.20,5.60,5.20,10,20};
	Float_t yVector[7] = {2.25,2.20,2.65,4.20,4.25,4.25,5.20,10,20};

	boost::threadpool::thread_pool<> tpool(7);
	for(int j=4; j<5; j++){//FACES
	
		for(int k=1; k<3; k++){//COUPLING
			
			for (int i=0; i<7; i++){//CRYSTAL DIMENSION

				tpool.schedule(boost::bind(myThread, j,k,i,xVector[i],yVector[i]));
			}
		}
	}
	tpool.wait();
	cout<<"Done"<<endl;

	return 0;
}
