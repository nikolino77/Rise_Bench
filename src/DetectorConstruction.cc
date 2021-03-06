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
#include "G4SubtractionSolid.hh"

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
	  Crystal_log->SetVisAttributes(G4Colour(0, 0, 255));
	  
	  if(CreateTree::Instance()->Wrapping())
	  {
            G4Box* opp_box = new G4Box("Air_opposite",0.5*crystal_x,0.5*crystal_y,0.5*depth);	    
	    G4LogicalVolume* opp_log  = new G4LogicalVolume(opp_box,Vacuum,"Air_opposite",0,0,0);
	    G4VPhysicalVolume* opp_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5*crystal_height-0.5*depth),opp_log,"Air_opposite",expHall_log,false,0);
	    opp_log->SetVisAttributes(G4Colour(150,150,150));
	    
	    G4OpticalSurface* WrapSurface = new G4OpticalSurface("WrapSurface");
	    WrapSurface -> SetModel(unified);
	    WrapSurface -> SetType(dielectric_dielectric);
	    //WrapSurface -> SetType(dielectric_metal);
	    WrapSurface -> SetFinish(groundbackpainted);
	    //WrapSurface -> SetFinish(polishedbackpainted);
	    
	    G4MaterialPropertiesTable *myST = new G4MaterialPropertiesTable();
	    
	    const G4int NUM1 = 3;
	    G4double GapEnergy[NUM1] = {0.0001 * eV, 1.00 * eV, 6.1742 * eV};
	    G4double GapRealIndex[NUM1] = {1.0003, 1.0003, 1.0003};
	    myST->AddProperty("RINDEX", GapEnergy, GapRealIndex, NUM1);
	    
	    const G4int NUM2 = 10;
	    G4double WrapRealEnergy[NUM2] 	= { 0.0001 * eV, 1.2398 *eV, 1.3776 *eV, 1.5498 *eV, 1.7712 *eV, 2.0664 *eV, 2.4796 *eV, 3.0996 *eV, 4.1328 *eV, 6.1742 * eV};
	    G4double WrapRealIndex[NUM2] 	= {1.339, 1.339, 1.341, 1.343, 1.345, 1.348, 1.351, 1.355, 1.36, 1.36};
	    myST->AddProperty("REALRINDEX", WrapRealEnergy, WrapRealIndex, NUM2);

	    const G4int NUM3 = 13;
	    G4double WrapComplexEnergy[NUM3] = { 0.0001 * eV,1.2398*eV, 1.5498*eV, 2.0664*eV, 2.4796*eV, 2.6953*eV, 2.9520*eV,3.0996*eV, 3.1790*eV, 3.2627*eV, 3.4440*eV, 3.6465*eV, 6.1742 * eV};
	    G4double WrapComplexIndex[NUM3] = { 23.75/1.0003, 23.75/1.0003, 23.50/1.0003, 23.00/1.0003, 22.00/1.0003,21.00/1.0003,17.50/1.0003,15.00/1.0003, 13.75/1.0003, 12.00/1.0003, 8.50/1.0003, 5.00/1.0003, 3.00/1.0003};
	    myST->AddProperty("IMAGINARYRINDEX", WrapComplexEnergy, WrapComplexIndex, NUM3);

	    WrapSurface->SetMaterialPropertiesTable(myST);
	     
	    G4LogicalBorderSurface *CrystalWrap  = new G4LogicalBorderSurface("CrystalWrap", Crystal_phys, expHall_phys, WrapSurface);
	  }
	  
	  /*-------TOP AIR LAYERS/DETECTOR-------*/
	  if(CreateTree::Instance()->Control())
	  {
            G4Box* opp_box = new G4Box("Air_opposite",0.5*crystal_x,0.5*crystal_y,0.5*depth);
	    G4LogicalVolume* opp_log  = new G4LogicalVolume(opp_box,Vacuum,"Air_opposite",0,0,0);
	    G4VPhysicalVolume* opp_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5*crystal_height-0.5*depth),opp_log,"Air_opposite",expHall_log,false,0);
	    opp_log->SetVisAttributes(G4Colour(150,150,150));

	
	    G4Box* source_box = new G4Box("Air_source",0.5*crystal_x,0.5*crystal_y,0.5*depth);
	    G4LogicalVolume* source_log  = new G4LogicalVolume(source_box,Vacuum,"Air_source",0,0,0);
	    G4VPhysicalVolume* source_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.5*crystal_height+0.5*depth),opp_log,"Air_source",expHall_log,false,0);

	    G4Box* side_box = new G4Box("side_box",0.5*crystal_x+0.5*depth,0.5*crystal_y+0.5*depth,0.5*crystal_height);
	    G4Box* side_empty_box = new G4Box("side_empty_box",0.5*crystal_x,0.5*crystal_y,0.5*crystal_height);
	    G4SubtractionSolid* side = new G4SubtractionSolid("side", side_box, side_empty_box);
	    G4LogicalVolume* side_log  = new G4LogicalVolume(side,Vacuum,"Air_side",0,0,0);
	    G4VPhysicalVolume* side_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),side_log,"Air_side",expHall_log,false,0);
	  }
	  /*-------TOP AIR LAYERS/DETECTOR-------*/
	  else if(CreateTree::Instance()->Grease())
	  {
	    G4Box* opp_box = new G4Box("Air_opposite",0.5*crystal_x,0.5*crystal_y,0.5*depth);
	    G4LogicalVolume* opp_log  = new G4LogicalVolume(opp_box,OptGrease,"Air_opposite",0,0,0);
	    G4VPhysicalVolume* opp_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5*crystal_height-0.5*depth),opp_log,"Air_opposite",expHall_log,false,0);
	
	    double help_l = 10*mm;
	    G4VSolid* help_g = new G4Box("help_g",0.5*crystal_x+0.5*depth,0.5*crystal_y+0.5*depth,0.5*help_l);
	    G4VSolid* temp_g = new G4Box("temp_g",0.5*crystal_x,0.5*crystal_y,0.5*depth);
	    
	    G4VSolid* subtract = new G4SubtractionSolid("help_g_temp_g", help_g, temp_g, 0, G4ThreeVector(0, 0, 0.5*help_l - 0.5*depth));
	    G4LogicalVolume* help_log  = new G4LogicalVolume(subtract,OptGrease,"help_g_temp_g",0,0,0);
	    G4VPhysicalVolume* help_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5*crystal_height-0.5*help_l),help_log,"help_g_temp_g",expHall_log,false,0);

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
	  G4Tubs* det_box = new G4Tubs("Detector",0.0,0.5*win_diam,0.5*det_dx,0,360);
	  G4LogicalVolume* det_log  = new G4LogicalVolume(det_box,Vacuum,"Detector",0,0,0);
	  G4RotationMatrix* rot_det = new G4RotationMatrix();
	  rot_det->rotateX(rot_ang*deg);
	  G4VPhysicalVolume* det_phys = new G4PVPlacement(rot_det,G4ThreeVector(det_x,det_y,det_z),det_log,"Detector",expHall_log,false,0);
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
	Teflon     = MyMaterials::Teflon();
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
	if(crystal_lightyield != -1)
	{
    	  ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("SCINTILLATIONYIELD");
    	  ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("SCINTILLATIONYIELD",crystal_lightyield/MeV);  
	}
	if(crystal_risetime != -1)
	{	
        cout << "Set rise time: "<< ScMaterial->GetMaterialPropertiesTable()->GetConstProperty("FASTSCINTILLATIONRISETIME") << endl;

	  ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("FASTSCINTILLATIONRISETIME");
    	  ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("FASTSCINTILLATIONRISETIME",crystal_risetime*ns); 
	}
	if(crystal_decaytime != -1)
	{	
	  ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("FASTTIMECONSTANT");
    	  ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("FASTTIMECONSTANT",crystal_decaytime*ns); 
	}
	if(crystal_abslength != -1)
	{
	  const G4int sc_entries = 8;
	  G4double v = crystal_abslength;
	  G4double sc_energy[sc_entries]       = { 1.5 * eV,1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV , 4.13 * eV, 6.1742 *eV};
	  G4double sc_abslength[sc_entries]    = { v*mm, v*mm, v*mm, v*mm, v*mm , v*mm , v*mm, v*mm };
    
	  ScMaterial->GetMaterialPropertiesTable()->RemoveProperty("ABSLENGTH");
    	  ScMaterial->GetMaterialPropertiesTable()->AddProperty("ABSLENGTH",sc_energy,sc_abslength,sc_entries); 
	}
	 
	if(crystal_decaytime != -1)
	{ 
	  ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("WLSTIMECONSTANT");
    	  ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("WLSTIMECONSTANT",crystal_decaytime*ns); 
	}

	ScMaterial->GetMaterialPropertiesTable()->GetProperty("ABSLENGTH")->DumpValues();
	cout << "Set rise time: "<< ScMaterial->GetMaterialPropertiesTable()->GetConstProperty("FASTSCINTILLATIONRISETIME") << endl;
	  
}

void DetectorConstruction::readConfigFile(string configFileName)
{	
	ConfigFile config(configFileName);
	config.readInto(crystal_height,"height");
	config.readInto(crystal_x,"crystalx");
	config.readInto(crystal_y,"crystaly");

	config.readInto(depth,"depth");
	config.readInto(det_mat,"det_mat");
	config.readInto(det_dx,"det_dx");
	config.readInto(det_dy,"det_dy");
	config.readInto(det_dz,"det_dz");
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
	config.readInto(crystal_decaytime,"decaytime");
	config.readInto(crystal_abslength,"abslength");
	config.readInto(crystal_lightyield,"lightyield");
}










