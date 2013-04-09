#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "TFile.h"
#include <cstdlib> 
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <bind.hpp>
#include <thread.hpp>
#include <thread/mutex.hpp>
#include <threadpool.hpp>


using namespace std;
using boost::mutex;
using boost::thread;

//TO COMPILE "from6to5Root" 
//g++ -Wall -ansi launch_parallel_manyCrystals.cxx -o launchParallelManyCrystalsEXE `root-config --cflags --glibs` -lboost_thread


void myThread(int number, string name) 
{	
	ostringstream temp1;
	temp1 << number;
	string command;	
	
	string rootFile = name + temp1.str();
	command = "$G4WORKDIR/bin/Linux-g++/H2_cer " + rootFile + " ";
	cout << command << endl;
	system(command.c_str());
};



int main(int argc, char** argv) 
{

    int n_cpu          = atoi(argv[1]);
    int n_processi     = atoi(argv[2]);
    string filename    = argv[3];
    	
    boost::threadpool::thread_pool<> tpool(n_cpu);
    for(int j=0; j<n_processi; j++)
    {
      tpool.schedule(boost::bind(myThread, j, filename));
    }
    tpool.wait();
    cout << "Done" << endl;

    return 0;
}
