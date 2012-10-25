

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4EmConfigurator.hh"
#include "G4OpticalPhysics.hh"

class G4VPhysicsConstructor;
class StepMax;
class PhysicsListMessenger;
class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpMieHG;
class G4OpBoundaryProcess;
class G4OpWLS;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
public:

  PhysicsList();
  virtual ~PhysicsList();

  void ConstructParticle();
    
  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void SetCutForProton(G4double);
  void ConstructOp();
        
  void AddPhysicsList(const G4String& name);
  void ConstructProcess();
    
  void AddStepMax(); 

private:

  void  AddPAIModel(const G4String&);
  void  NewPAIModel(const G4ParticleDefinition*, const G4String& modname, 
		    const G4String& procname);

  G4EmConfigurator* em_config;

  G4Cerenkov*          theCerenkovProcess;
  G4Scintillation*     theScintillationProcess;
  G4OpAbsorption*      theAbsorptionProcess;
  G4OpRayleigh*        theRayleighScatteringProcess;
  G4OpBoundaryProcess* theBoundaryProcess;
  G4OpWLS*             theWLSProcess;
  G4OpMieHG*		 theMieHGScatteringProcess;

  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;

  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  generalPhysicsList;
  G4VPhysicsConstructor*  particleList;
  G4OpticalPhysics*       opticalPhysics;
  std::vector<G4VPhysicsConstructor*>  hadronPhys;
  G4String emName;
    
  StepMax* stepMaxProcess;
    
  PhysicsListMessenger* pMessenger;

  G4VEmModel* em_model;
  G4VEmFluctuationModel* fm_model;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

