#include "DetectorConstruction.hh"
#include "CreateTree.hh"
#include "MyMaterials.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"

#include "G4OpBoundaryProcess.hh"
#include "G4SDManager.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SubtractionSolid.hh"

using namespace std;

DetectorConstruction::DetectorConstruction()
{
	// set defaults for geometry and material properties
	//detectorMessenger = new DetectorMessenger(this);
  
	expHall_x = expHall_y = expHall_z = 400*cm;
	crystal_abslength    = -1;
	updated = true;
}

DetectorConstruction::~DetectorConstruction(){;}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	readConfigFile("crystal.cfg");
	initializeMaterials();

	//
	// C O M M O N   V O L U M E S 
	//
	
	/*-------EXPERIMENTAL HALL-------*/

  	G4Box* expHall_box = new G4Box("World",expHall_x,expHall_y,expHall_z);
  	G4LogicalVolume* expHall_log = new G4LogicalVolume(expHall_box,Vacuum,"World",0,0,0);
  	G4VPhysicalVolume* expHall_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),expHall_log,"World",0,false,0);

	G4LogicalVolume*   Crystal_log    = NULL;
  	G4VPhysicalVolume* Crystal_phys   = NULL;

	/*-------CRYSTAL-------*/
	if(CreateTree::Instance()->Crystal())
	{  
	  G4Box* Crystal_box = new G4Box("Crystal",0.5*crystal_x,0.5*crystal_y,0.5*crystal_height);
          Crystal_log = new G4LogicalVolume(Crystal_box,ScMaterial,"Crystal",0,0,0);
          Crystal_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),Crystal_log,"Crystal",expHall_log,false,0);

	  /*-------TOP AIR LAYERS/DETECTOR-------*/
	  if(CreateTree::Instance()->Control())
	  {
            G4Box* opp_box = new G4Box("Air_opposite",0.5*crystal_x,0.5*crystal_y,0.5*depth);
	    G4LogicalVolume* opp_log  = new G4LogicalVolume(opp_box,Vacuum,"Air_opposite",0,0,0);
	    G4VPhysicalVolume* opp_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5*crystal_height-0.5*depth),opp_log,"Air_opposite",expHall_log,false,0);
	
	    G4Box* source_box = new G4Box("Air_source",0.5*crystal_x,0.5*crystal_y,0.5*depth);
	    G4LogicalVolume* source_log  = new G4LogicalVolume(source_box,Vacuum,"Air_source",0,0,0);
	    G4VPhysicalVolume* source_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.5*crystal_height+0.5*depth),opp_log,"Air_source",expHall_log,false,0);

	    G4Box* side_box = new G4Box("side_box",0.5*crystal_x+0.5*depth,0.5*crystal_y+0.5*depth,0.5*crystal_height);
	    G4Box* side_empty_box = new G4Box("side_empty_box",0.5*crystal_x,0.5*crystal_y,0.5*crystal_height);
	    G4SubtractionSolid* side = new G4SubtractionSolid("side", side_box, side_empty_box);
	    G4LogicalVolume* side_log  = new G4LogicalVolume(side,Vacuum,"Air_side",0,0,0);
	    G4VPhysicalVolume* side_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),side_log,"Air_side",expHall_log,false,0);
	  }
	}
	  
	if(CreateTree::Instance()->Hits())
	{
	  G4Box* det_box = new G4Box("Detector",0.5*det_d,0.5*det_d,0.5*det_d);
	  G4LogicalVolume* det_log  = new G4LogicalVolume(det_box,Vacuum,"Detector",0,0,0);
	  G4VPhysicalVolume* det_phys = new G4PVPlacement(0,G4ThreeVector(win_x,win_y + 1.9,win_z),det_log,"Detector",expHall_log,false,0);
	}
	
	if(CreateTree::Instance()->Window())
	{
	  G4Tubs* win_tub = new G4Tubs("Window",0.0,0.5*win_diam,0.5*win_depth,0,360);
	  G4LogicalVolume* win_log  = new G4LogicalVolume(win_tub,WiMaterial,"Window",0,0,0);
	  G4RotationMatrix* rot_win = new G4RotationMatrix();
	  rot_win->rotateX(rot_ang*deg);
	  G4VPhysicalVolume* win_phys = new G4PVPlacement(rot_win,G4ThreeVector(win_x,win_y,win_z),win_log,"Window",expHall_log,false,0);
	}
	
	//
	// Visualization attributes
	//
  	expHall_log->SetVisAttributes(G4VisAttributes::Invisible);
  
	//always return the physical World
  	return expHall_phys;
}

//
// Update geometry
// 
void DetectorConstruction::UpdateGeometry()
{
  	G4cout<<"Updating detector ..."<<G4endl;
  	// clean-up previous geometry
  	G4GeometryManager::GetInstance()->OpenGeometry();
  	G4PhysicalVolumeStore::GetInstance()->Clean();
  	G4LogicalVolumeStore::GetInstance()->Clean();
  	G4SolidStore::GetInstance()->Clean();
  	G4LogicalSkinSurface::CleanSurfaceTable();
  	G4LogicalBorderSurface::CleanSurfaceTable();

  	//define new one
  	G4RunManager::GetRunManager()->DefineWorldVolume(this->Construct());
  	G4RunManager::GetRunManager()->GeometryHasBeenModified();

  	CreateTree::Instance()->CrystalHeight = crystal_height;
  	updated=false;
}

G4bool DetectorConstruction::GetUpdated() const { return updated; }


void DetectorConstruction::initializeMaterials(){

	//
  	// Materials
  	//
  	Air        = MyMaterials::Air();
  	Water      = MyMaterials::Water();  
  	Vacuum     = MyMaterials::Vacuum();
  	Silicon    = MyMaterials::Silicon();
  	OptGrease  = MyMaterials::OpticalGrease();
  	ScMaterial = NULL;
	WiMaterial = NULL;

  	if(crystal_material==1)        ScMaterial = MyMaterials::LSO();
  	else if(crystal_material==2)   ScMaterial = MyMaterials::LYSO();
  	else if(crystal_material==3)   ScMaterial = MyMaterials::LUAGCE();  
  	else if(crystal_material==4)   ScMaterial = MyMaterials::LUAGPR();
  	else if(crystal_material==5)   ScMaterial = MyMaterials::PbWO();
	else if(crystal_material==6)   ScMaterial = MyMaterials::Air();
	else if(crystal_material==7)   ScMaterial = MyMaterials::Quartz();
  	else if(crystal_material>7 || crystal_material<=0) 
	{
    	  G4cerr<<"<DetectorConstruction::Construct>: Invalid material specifier "<<crystal_material<<G4endl;
   	  exit(0);
  	}
  	G4cout<<"Sc. material: "<<ScMaterial<<G4endl;
	
	if(win_material == 7) WiMaterial = MyMaterials::Quartz();
  	else if(win_material > 7 || win_material < 7) 
	{
    	  G4cerr << "<DetectorConstruction::Construct>: Invalid material specifier " << win_material << G4endl;
   	  exit(0);
  	}
	
	//
  	// modify default properties of the scintillator
  	//
  	if(crystal_lightyield>=0) 
	{
    	  ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("SCINTILLATIONYIELD");
    	  ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("SCINTILLATIONYIELD",crystal_lightyield/MeV);  
  	} 
	else 
	{
    	  CreateTree::Instance()->ScintillationYield = ScMaterial->GetMaterialPropertiesTable()->GetConstProperty("SCINTILLATIONYIELD");
  	}
  	if(crystal_risetime>=0) 
	{
    	  ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("FASTSCINTILLATIONRISETIME");
    	  ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("FASTSCINTILLATIONRISETIME",crystal_risetime/ns);  
	} 
	else 
	{
    	  CreateTree::Instance()->RiseTime = ScMaterial->GetMaterialPropertiesTable()->GetConstProperty("FASTSCINTILLATIONRISETIME");
  	}
}

void DetectorConstruction::readConfigFile(string configFileName)
{	
	ConfigFile config(configFileName);
	config.readInto(crystal_height,"height");
	config.readInto(crystal_x,"crystalx");
	config.readInto(crystal_y,"crystaly");

	config.readInto(depth,"depth");
	config.readInto(det_mat,"det_mat");
        config.readInto(det_d,"det_d");
	config.readInto(det_x,"det_x");
	config.readInto(det_y,"det_y");
	config.readInto(det_z,"det_z");

	config.readInto(rot_ang,"rot_ang");
	config.readInto(win_diam, "win_diam");
	config.readInto(win_depth, "win_depth");
	config.readInto(win_x, "win_x");
	config.readInto(win_y, "win_y");
	config.readInto(win_z, "win_z");
	config.readInto(win_material, "win_material");
		
	config.readInto(crystal_material,"scmaterial");
	config.readInto(crystal_risetime,"risetime");
	config.readInto(crystal_lightyield,"lightyield");
}










