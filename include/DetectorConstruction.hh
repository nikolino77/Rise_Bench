// Martin Goettlich @ DESY
//

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "ConfigFile.hh"
#include "TString.h"

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4OpBoundaryProcess.hh"


class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();
   		~DetectorConstruction();

    		// World dimensions
    		G4double expHall_x;
    		G4double expHall_y;
    		G4double expHall_z;
    		// Crystal parameters
    		G4double crystal_x;    
    		G4double crystal_y;
    		G4double crystal_height;
    		G4double depth;
		G4double det_dx;
		G4double det_dy;
		G4double det_dz;
		G4double det_x;
		G4double det_y;
		G4double det_z;
		G4double rot_ang;
		
		G4double win_diam;
		G4double win_depth;
		G4double win_x;
		G4double win_y;
		G4double win_z;
		
		int	 det_mat;
		int      crystal_material;
		int      win_material;
    		int      crystal_lightyield;
    		int 	 crystal_risetime;
		int 	 crystal_decaytime;
    		int	 crystal_abslength;

		//Materials
		G4Material* Air;
		G4Material* Water;
		G4Material* Vacuum;
		G4Material* Silicon;
		G4Material* OptGrease;
		G4Material* ScMaterial;
		G4Material* WiMaterial;
		G4Material* Quartz;
		G4Material* Teflon;


    		G4VPhysicalVolume* Construct();

    		//
		// Update geometry
		// 
    		void     UpdateGeometry();
    		G4bool   GetUpdated() const;
    		G4bool 	 updated;

    		//DetectorMessenger* detectorMessenger;
		void readConfigFile(string configFileName);
		void initializeMaterials();
};



#endif /*DetectorConstruction_h*/
