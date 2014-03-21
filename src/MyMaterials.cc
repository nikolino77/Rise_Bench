#include "MyMaterials.hh"


MyMaterials::MyMaterials()
{
}

MyMaterials::~MyMaterials()
{
}

G4Material *MyMaterials::Air()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *N = new G4Element ("Nitrogen", "N", z = 7 , a = 14.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);

    G4Material *Air = new G4Material ("Air", density = 1.29 * mg / cm3, nelements = 2);
    Air->AddElement (N, 70.*perCent);
    Air->AddElement (O, 30.*perCent);

    const G4int nEntries = 35;

    G4double PhotonEnergy[nEntries] = {
        0.0001 * eV, 1.00 * eV,  2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV, 6.1742 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003
    };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);

    Air->SetMaterialPropertiesTable (myMPT);

    return Air;
}

G4Material *MyMaterials::SensorAir()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *N = new G4Element ("Nitrogen", "N", z = 7 , a = 14.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);

    G4Material *SensorAir = new G4Material ("SensorAir", density = 1.29 * mg / cm3, nelements = 2);
    SensorAir->AddElement (N, 70.*perCent);
    SensorAir->AddElement (O, 30.*perCent);

    const G4int nEntries = 35;

    G4double PhotonEnergy[nEntries] = {
        0.0001 * eV, 1.00 * eV,  2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV, 6.1742 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003
    };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);

    SensorAir->SetMaterialPropertiesTable (myMPT);

    return SensorAir;
}


G4Material *MyMaterials::Water()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *H = new G4Element ("Hydrogen", "H", z = 1 , a = 1.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);
    G4Material *Water = new G4Material ("Water", density = 1.0 * g / cm3, nelements = 2);
    Water->AddElement (H, 2);
    Water->AddElement (O, 1);

    const G4int nEntries = 33;

    G4double PhotonEnergy[nEntries] = {
        0.1 * eV, 2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.3435, 1.3435, 1.344,  1.3445, 1.345,  1.3455,
        1.346,  1.3465, 1.347,  1.3475, 1.348,
        1.3485, 1.3492, 1.35,   1.3505, 1.351,
        1.3518, 1.3522, 1.3530, 1.3535, 1.354,
        1.3545, 1.355,  1.3555, 1.356,  1.3568,
        1.3572, 1.358,  1.3585, 1.359,  1.3595,
        1.36,   1.3608
    };

    G4double Absorption[nEntries] = {
        3.448, 3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m, 12.346 * m, 13.889 * m,
        15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,
        45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,
        52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
        30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,
        17.500 * m, 14.500 * m
    };

    G4double ScintilFast[nEntries] = {
        1.00,   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00
    };
    G4double ScintilSlow[nEntries] = {
        0.01,   0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
        7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
        3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
        4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
        7.00, 6.00, 5.00, 4.00
    };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX",       PhotonEnergy, RefractiveIndex, nEntries);
    myMPT->AddProperty ("ABSLENGTH",    PhotonEnergy, Absorption,      nEntries);
    //myMPT->AddProperty ("FASTCOMPONENT", PhotonEnergy, ScintilFast,     nEntries);
    //myMPT->AddProperty ("SLOWCOMPONENT", PhotonEnergy, ScintilSlow,     nEntries);

    //myMPT->AddConstProperty ("SCINTILLATIONYIELD", 50. / MeV);
    //myMPT->AddConstProperty ("RESOLUTIONSCALE", 1.0);
    //myMPT->AddConstProperty ("FASTTIMECONSTANT", 1.*ns);
    //myMPT->AddConstProperty ("SLOWTIMECONSTANT", 10.*ns);
    //myMPT->AddConstProperty ("YIELDRATIO", 0.8);

    Water->SetMaterialPropertiesTable (myMPT);

    return Water;
}

G4Material *MyMaterials::Vacuum()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *N = new G4Element ("Nitrogen", "N", z = 7 , a = 14.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);

    G4Material *Air = new G4Material ("Air", density =  1e-25 * g / cm3, nelements = 2);
    Air->AddElement (N, 70.*perCent);
    Air->AddElement (O, 30.*perCent);

    const G4int nEntries = 35;

    G4double PhotonEnergy[nEntries] = {
        0.0001 * eV, 1.00 * eV,  2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV, 6.1742 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003
    };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);

    Air->SetMaterialPropertiesTable (myMPT);

    return Air;
}

G4Material *MyMaterials::Silicon()
{
    G4double a, z, density;

    G4Element *Si = new G4Element ("Silicon",    "Si", z = 14., a = 28.09 * g / mole);
    G4Material *Silicon = new G4Material ("Silicon", density = 2.33 * g / cm3, 1);
    Silicon->AddElement (Si, 1);

    const G4int NUM = 5;

    G4double Energy[NUM]         = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV,  6.26 * eV};
    G4double RIND_INDEX[NUM]     = { 4.0, 4.0, 4.0, 4.0, 4.0 };
    G4double ABS_LENGTH[NUM]     = { 0.1 * mm, 0.1 * mm, 0.1 * mm, 0.1 * mm, 0.1 * mm};

    G4MaterialPropertiesTable *Si_mt = new G4MaterialPropertiesTable();
    Si_mt->AddProperty ("RINDEX",        Energy,  RIND_INDEX,     NUM);
    Si_mt->AddProperty ("ABSLENGTH",     Energy,  ABS_LENGTH,     NUM);

    Silicon->SetMaterialPropertiesTable (Si_mt);

    return Silicon;

}

G4Material *MyMaterials::Quartz()
{
    G4double a, z, density;
    G4Element *Si = new G4Element ("Silicon",    "Si", z = 14., a = 28.09 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);
    
    G4Material *Quartz = new G4Material ("Quartz", density = 2.65 * g / cm3, 2);
    Quartz->AddElement (Si, 1);
    Quartz->AddElement (O, 2);

    const G4int nEntries_RI = 11;
    G4double PhotonEnergy[nEntries_RI] = {
        1.0 * eV, 2.0 * eV, 2.5 * eV, 3.0 * eV, 3.5 * eV,
        4.0 * eV, 4.5 * eV, 5.0 * eV, 5.5 * eV, 6.0 * eV, 6.26 * eV       
    };
    G4double RefractiveIndex[nEntries_RI] = {
        1.53, 1.54, 1.55, 1.56, 1.56, 1.57, 1.59, 1.60, 1.62,
	1.64, 1.65
    };

    const G4int nEntries_ABS = 4;
    G4double ABS_Energy[nEntries_ABS]       = { 1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV };
    G4double ABS_LENGTH[nEntries_ABS]       = { 138.*mm, 138.*mm, 138.*mm, 138. *mm };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergy, RefractiveIndex, nEntries_RI);
    myMPT->AddProperty ("ABSLENGTH", ABS_Energy, ABS_LENGTH, nEntries_ABS);
    Quartz->SetMaterialPropertiesTable (myMPT);
    return Quartz;
}

G4Material *MyMaterials::OpticalGrease()
{
    G4double a, z, density;
    G4Element *H = new G4Element ("Hydrogen", "H", z = 1 , a = 1.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);
    G4Element *C = new G4Element ("Carbon"  , "C", z = 6 , a = 12.01 * g / mole);

    G4Material *Grease = new G4Material ("Grease", density = 1.0 * g / cm3, 3);
    Grease->AddElement (C, 1);
    Grease->AddElement (H, 1);
    Grease->AddElement (O, 1);

    const G4int nEntries = 34;

    G4double PhotonEnergy[nEntries] = {
        0.0001 * eV, 1.0 * eV, 2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41,
        1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41,
        1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41,
        1.41, 1.41, 1.41, 1.41, 1.41, 1.41, 1.41,
        1.41, 1.41, 1.41, 1.41
    };

//   G4double Absorption[nEntries] =
//    { 3.448*m, 3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
//            15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
//            45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
//            52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
//            30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
//            17.500*m, 14.500*m };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX",       PhotonEnergy, RefractiveIndex, nEntries);
//   myMPT->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption,      nEntries);
    Grease->SetMaterialPropertiesTable (myMPT);
    return Grease;
}


G4Material *MyMaterials::LUAGCE()  // Lutetium Aluminum Garnet
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71, a = 174.97 * g / mole);
    G4Element *Al = new G4Element ("Aluminum",  "Al",  z = 27, a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LUAG", density = 6.7 * g / cm3, 3);
    mat->AddElement (Lu, 3);
    mat->AddElement (Al, 12);
    mat->AddElement (O, 5);


    // large band between 470 (2.64 eV) and 630 nm (1.97 eV) (mean 535 nm, 2.32)
    const G4int NUMENTRIES_1 = 6;
    G4double FAST_Energy[NUMENTRIES_1]    = {1.0 * eV, 1.90 * eV, 1.97 * eV, 2.64 * eV, 2.70 * eV, 4.08 * eV};
    G4double FAST_COMPONENT[NUMENTRIES_1] = {0.00, 0.00, 1.0, 1.0, 0.00, 0.00};


    const G4int NUMENTRIES_2 = 3;
    G4double RIND_Energy[NUMENTRIES_2]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]     = { 1.82, 1.82, 1.82 };
    G4double ABS_Energy[NUMENTRIES_2]     = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    //G4double ABS_LENGTH[NUMENTRIES_2]     = { 50.*m, 50.*m, 50.*m};
    G4double ABS_LENGTH[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm };
    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_2);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 15000 / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 8.5);
    mt->AddConstProperty ("FASTTIMECONSTANT", 60.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.5 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}
G4Material *MyMaterials::LUAGPR()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71, a = 174.97 * g / mole);
    G4Element *Al = new G4Element ("Aluminum",  "Al",  z = 27, a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LUAG", density = 6.7 * g / cm3, 3);
    mat->AddElement (Lu, 3);
    mat->AddElement (Al, 12);
    mat->AddElement (O, 5);

    //  2 bands at 290nm (4.28eV) and 350nm (3.54eV) about 50% of the light in each.
    const G4int NUMENTRIES_1 = 8;
    G4double FAST_Energy[NUMENTRIES_1]    = {1.0 * eV, 3.4 * eV, 3.5 * eV, 3.60 * eV, 3.90 * eV, 3.91 * eV,4.07 * eV, 4.08 * eV};
    G4double FAST_COMPONENT[NUMENTRIES_1] = {0.00  , 0.00,  1.00,  0.0,    0.0,    1.0,    0.0,    0.0    };

    const G4int NUMENTRIES_2 = 3;
    G4double RIND_Energy[NUMENTRIES_2]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]     = { 1.82, 1.82, 1.82 };
    G4double ABS_Energy[NUMENTRIES_2]     = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double ABS_LENGTH[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm };
    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_2);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 7000 / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 6.4);
    mt->AddConstProperty ("FASTTIMECONSTANT", 20.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.5 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}
G4Material *MyMaterials::LYSO()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71., a = 174.97 * g / mole);
    G4Element *Si = new G4Element ("Silicon",   "Si",  z = 14., a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LYSO", density = 7.1 * g / cm3, 3, kStateSolid);
    mat->AddElement (Lu, 2);
    mat->AddElement (Si, 1);
    mat->AddElement (O, 5);

    const G4int NUMENTRIES_1 = 200;
    G4double FAST_Energy[NUMENTRIES_1] = {1.239 * eV,1.2638 * eV,1.2886 * eV,1.3134 * eV,1.3382 * eV,1.363 * eV,1.3878 * eV,
					   1.4126 * eV,1.4374 * eV,1.4622 * eV,1.487 * eV,1.5118 * eV,1.5366 * eV,1.5614 * eV,
					   1.5862 * eV,1.611 * eV,1.6358 * eV,1.6606 * eV,1.6854 * eV,1.7102 * eV,1.735 * eV,
					   1.7598 * eV,1.7846 * eV,1.8094 * eV,1.8342 * eV,1.859 * eV,1.8838 * eV,1.9086 * eV,
					   1.9334 * eV,1.9582 * eV,1.983 * eV,2.0078 * eV,2.0326 * eV,2.0574 * eV,2.0822 * eV,
					   2.107 * eV,2.1318 * eV,2.1566 * eV,2.1814 * eV,2.2062 * eV,2.231 * eV,2.2558 * eV,
					   2.2806 * eV,2.3054 * eV,2.3302 * eV,2.355 * eV,2.3798 * eV,2.4046 * eV,2.4294 * eV,
					   2.4542 * eV,2.479 * eV,2.5038 * eV,2.5286 * eV,2.5534 * eV,2.5782 * eV,2.603 * eV,
					   2.6278 * eV,2.6526 * eV,2.6774 * eV,2.7022 * eV,2.727 * eV,2.7518 * eV,2.7766 * eV,
					   2.8014 * eV,2.8262 * eV,2.851 * eV,2.8758 * eV,2.9006 * eV,2.9254 * eV,2.9502 * eV,
					   2.975 * eV,2.9998 * eV,3.0246 * eV,3.0494 * eV,3.0742 * eV,3.099 * eV,3.1238 * eV,
					   3.1486 * eV,3.1734 * eV,3.1982 * eV,3.223 * eV,3.2478 * eV,3.2726 * eV,3.2974 * eV,
					   3.3222 * eV,3.347 * eV,3.3718 * eV,3.3966 * eV,3.4214 * eV,3.4462 * eV,3.471 * eV,
					   3.4958 * eV,3.5206 * eV,3.5454 * eV,3.5702 * eV,3.595 * eV,3.6198 * eV,3.6446 * eV,
					   3.6694 * eV,3.6942 * eV,3.719 * eV,3.7438 * eV,3.7686 * eV,3.7934 * eV,3.8182 * eV,
					   3.843 * eV,3.8678 * eV,3.8926 * eV,3.9174 * eV,3.9422 * eV,3.967 * eV,3.9918 * eV,
					   4.0166 * eV,4.0414 * eV,4.0662 * eV,4.091 * eV,4.1158 * eV,4.1406 * eV,4.1654 * eV,
					   4.1902 * eV,4.215 * eV,4.2398 * eV,4.2646 * eV,4.2894 * eV,4.3142 * eV,4.339 * eV,
					   4.3638 * eV,4.3886 * eV,4.4134 * eV,4.4382 * eV,4.463 * eV,4.4878 * eV,4.5126 * eV,
					   4.5374 * eV,4.5622 * eV,4.587 * eV,4.6118 * eV,4.6366 * eV,4.6614 * eV,4.6862 * eV,
					   4.711 * eV,4.7358 * eV,4.7606 * eV,4.7854 * eV,4.8102 * eV,4.835 * eV,4.8598 * eV,
					   4.8846 * eV,4.9094 * eV,4.9342 * eV,4.959 * eV,4.9838 * eV,5.0086 * eV,5.0334 * eV,
					   5.0582 * eV,5.083 * eV,5.1078 * eV,5.1326 * eV,5.1574 * eV,5.1822 * eV,5.207 * eV,
					   5.2318 * eV,5.2566 * eV,5.2814 * eV,5.3062 * eV,5.331 * eV,5.3558 * eV,5.3806 * eV,
					   5.4054 * eV,5.4302 * eV,5.455 * eV,5.4798 * eV,5.5046 * eV,5.5294 * eV,5.5542 * eV,
					   5.579 * eV,5.6038 * eV,5.6286 * eV,5.6534 * eV,5.6782 * eV,5.703 * eV,5.7278 * eV,
					   5.7526 * eV,5.7774 * eV,5.8022 * eV,5.827 * eV,5.8518 * eV,5.8766 * eV,5.9014 * eV,
					   5.9262 * eV,5.951 * eV,5.9758 * eV,6.0006 * eV,6.0254 * eV,6.0502 * eV,6.075 * eV,
					   6.0998 * eV,6.1246 * eV,6.1494 * eV,6.1742 * eV};
    G4double FAST_COMPONENT[NUMENTRIES_1] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0.000425522 ,0.000967993 ,0.00114271 ,0.00110889 ,0.00127938 ,
					      0.00162459 ,0.00182749 ,0.00190781 ,0.00210929 ,0.00236292 ,0.00316606 ,0.00305474 ,
					      0.00404669 ,0.00464411 ,0.00493578 ,0.00506118 ,0.00552897 ,0.00632647 ,0.00663505 ,
					      0.00742691 ,0.0079398 ,0.00976447 ,0.0104563 ,0.0128375 ,0.015168 ,0.018103 ,0.0203419 ,
					      0.0237687 ,0.0272278 ,0.0320156 ,0.0368669 ,0.0407698 ,0.0437978 ,0.0477163 ,0.0513219 ,
					      0.0508795 ,0.0520701 ,0.0509316 ,0.0507217 ,0.0494536 ,0.0465172 ,0.0454013 ,0.0428679 ,
					      0.0365005 ,0.0311082 ,0.0242491 ,0.0177423 ,0.0118273 ,0.00785103 ,0.005908 ,0.0044384 ,
					      0.00246437 ,0.00220511 ,0.00154992 ,0.00100322 ,0.000631238 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
    
    const G4int NUMENTRIES_2 = 5;
    G4double RIND_Energy[NUMENTRIES_2]      = { 1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]       = { 1.8, 1.8, 1.81, 1.83, 1.85 };
    G4double ABS_Energy[NUMENTRIES_2]       = { 1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV };
    G4double ABS_LENGTH[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm, 138.*mm, 138.*mm };
    
    //const G4int NUMENTRIES_3 = 3;
    //G4double ABS_Energy[NUMENTRIES_3]     = { 1.0*eV, 1.84*eV, 4.08*eV };
    //G4double ABS_LENGTH[NUMENTRIES_3]       = { 138000.*mm, 138000.*mm, 138000.*mm };
    //G4double ABS_LENGTH[NUMENTRIES_3]       = { 500.*mm, 500.*mm, 500.*mm };

    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_2);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 40000. / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 3.4);
    mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}
G4Material *MyMaterials::LSO()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71., a = 174.97 * g / mole);
    G4Element *Si = new G4Element ("Silicon",   "Si",  z = 14., a = 28.09 * g / mole);

    G4Material *LSO = new G4Material ("LSO", density = 7.4 * g / cm3, 3);
    LSO->AddElement (Lu, 2);
    LSO->AddElement (Si, 1);
    LSO->AddElement (O, 5);
    const G4int LSO_NUMENTRIES_1 = 200;
    G4double LSO_FAST_Energy[LSO_NUMENTRIES_1] = {1.239 * eV,1.2638 * eV,1.2886 * eV,1.3134 * eV,1.3382 * eV,1.363 * eV,1.3878 * eV,
					   1.4126 * eV,1.4374 * eV,1.4622 * eV,1.487 * eV,1.5118 * eV,1.5366 * eV,1.5614 * eV,
					   1.5862 * eV,1.611 * eV,1.6358 * eV,1.6606 * eV,1.6854 * eV,1.7102 * eV,1.735 * eV,
					   1.7598 * eV,1.7846 * eV,1.8094 * eV,1.8342 * eV,1.859 * eV,1.8838 * eV,1.9086 * eV,
					   1.9334 * eV,1.9582 * eV,1.983 * eV,2.0078 * eV,2.0326 * eV,2.0574 * eV,2.0822 * eV,
					   2.107 * eV,2.1318 * eV,2.1566 * eV,2.1814 * eV,2.2062 * eV,2.231 * eV,2.2558 * eV,
					   2.2806 * eV,2.3054 * eV,2.3302 * eV,2.355 * eV,2.3798 * eV,2.4046 * eV,2.4294 * eV,
					   2.4542 * eV,2.479 * eV,2.5038 * eV,2.5286 * eV,2.5534 * eV,2.5782 * eV,2.603 * eV,
					   2.6278 * eV,2.6526 * eV,2.6774 * eV,2.7022 * eV,2.727 * eV,2.7518 * eV,2.7766 * eV,
					   2.8014 * eV,2.8262 * eV,2.851 * eV,2.8758 * eV,2.9006 * eV,2.9254 * eV,2.9502 * eV,
					   2.975 * eV,2.9998 * eV,3.0246 * eV,3.0494 * eV,3.0742 * eV,3.099 * eV,3.1238 * eV,
					   3.1486 * eV,3.1734 * eV,3.1982 * eV,3.223 * eV,3.2478 * eV,3.2726 * eV,3.2974 * eV,
					   3.3222 * eV,3.347 * eV,3.3718 * eV,3.3966 * eV,3.4214 * eV,3.4462 * eV,3.471 * eV,
					   3.4958 * eV,3.5206 * eV,3.5454 * eV,3.5702 * eV,3.595 * eV,3.6198 * eV,3.6446 * eV,
					   3.6694 * eV,3.6942 * eV,3.719 * eV,3.7438 * eV,3.7686 * eV,3.7934 * eV,3.8182 * eV,
					   3.843 * eV,3.8678 * eV,3.8926 * eV,3.9174 * eV,3.9422 * eV,3.967 * eV,3.9918 * eV,
					   4.0166 * eV,4.0414 * eV,4.0662 * eV,4.091 * eV,4.1158 * eV,4.1406 * eV,4.1654 * eV,
					   4.1902 * eV,4.215 * eV,4.2398 * eV,4.2646 * eV,4.2894 * eV,4.3142 * eV,4.339 * eV,
					   4.3638 * eV,4.3886 * eV,4.4134 * eV,4.4382 * eV,4.463 * eV,4.4878 * eV,4.5126 * eV,
					   4.5374 * eV,4.5622 * eV,4.587 * eV,4.6118 * eV,4.6366 * eV,4.6614 * eV,4.6862 * eV,
					   4.711 * eV,4.7358 * eV,4.7606 * eV,4.7854 * eV,4.8102 * eV,4.835 * eV,4.8598 * eV,
					   4.8846 * eV,4.9094 * eV,4.9342 * eV,4.959 * eV,4.9838 * eV,5.0086 * eV,5.0334 * eV,
					   5.0582 * eV,5.083 * eV,5.1078 * eV,5.1326 * eV,5.1574 * eV,5.1822 * eV,5.207 * eV,
					   5.2318 * eV,5.2566 * eV,5.2814 * eV,5.3062 * eV,5.331 * eV,5.3558 * eV,5.3806 * eV,
					   5.4054 * eV,5.4302 * eV,5.455 * eV,5.4798 * eV,5.5046 * eV,5.5294 * eV,5.5542 * eV,
					   5.579 * eV,5.6038 * eV,5.6286 * eV,5.6534 * eV,5.6782 * eV,5.703 * eV,5.7278 * eV,
					   5.7526 * eV,5.7774 * eV,5.8022 * eV,5.827 * eV,5.8518 * eV,5.8766 * eV,5.9014 * eV,
					   5.9262 * eV,5.951 * eV,5.9758 * eV,6.0006 * eV,6.0254 * eV,6.0502 * eV,6.075 * eV,
					   6.0998 * eV,6.1246 * eV,6.1494 * eV,6.1742 * eV};
    G4double LSO_FAST_COMPONENT[LSO_NUMENTRIES_1] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0.000425522 ,0.000967993 ,0.00114271 ,0.00110889 ,0.00127938 ,
					      0.00162459 ,0.00182749 ,0.00190781 ,0.00210929 ,0.00236292 ,0.00316606 ,0.00305474 ,
					      0.00404669 ,0.00464411 ,0.00493578 ,0.00506118 ,0.00552897 ,0.00632647 ,0.00663505 ,
					      0.00742691 ,0.0079398 ,0.00976447 ,0.0104563 ,0.0128375 ,0.015168 ,0.018103 ,0.0203419 ,
					      0.0237687 ,0.0272278 ,0.0320156 ,0.0368669 ,0.0407698 ,0.0437978 ,0.0477163 ,0.0513219 ,
					      0.0508795 ,0.0520701 ,0.0509316 ,0.0507217 ,0.0494536 ,0.0465172 ,0.0454013 ,0.0428679 ,
					      0.0365005 ,0.0311082 ,0.0242491 ,0.0177423 ,0.0118273 ,0.00785103 ,0.005908 ,0.0044384 ,
					      0.00246437 ,0.00220511 ,0.00154992 ,0.00100322 ,0.000631238 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
					      0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
    const G4int LSO_NUMENTRIES_2 = 8;
    G4double LSO_RIND_Energy[LSO_NUMENTRIES_2]      = { 1.5 * eV, 1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV , 4.13 * eV, 6.1742 * eV};
    G4double LSO_RIND_INDEX[LSO_NUMENTRIES_2]       = { 1.8, 1.8,  1.8, 1.81, 1.83, 1.85, 1.85, 2.10 };
    G4double LSO_ABS_Energy[LSO_NUMENTRIES_2]       = { 1.5 * eV,1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV , 4.13 * eV, 6.1742 *eV};
    G4double LSO_ABS_LENGTH[LSO_NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm, 138.*mm, 138.*mm , 138.*mm , 138.*mm, 138.*mm };
    
    const G4int LSO_NUMENTRIES_3 = 8;
    G4double LSO_ABS_WLS[LSO_NUMENTRIES_3]     = {138.*mm, 138.*mm, 138.*mm, 138.*mm, 138.*mm , 138.*mm , 138.*mm, 138.*mm };
    G4double LSO_WLS_Energy[LSO_NUMENTRIES_3]  = {  1.5 * eV,1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV , 4.13 * eV, 6.1742 * eV};

    
    /*
    const G4int LSO_NUMENTRIES_2 = 7;
    G4double LSO_RIND_Energy[LSO_NUMENTRIES_2]      = { 0.1 * eV, 1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV, 10 * eV };
    G4double LSO_RIND_INDEX[LSO_NUMENTRIES_2]       = { 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82 };
    G4double LSO_ABS_Energy[LSO_NUMENTRIES_2]       = { 0.1 * eV, 1.91 * eV, 2.06 * eV, 2.27 * eV, 3.06 * eV, 3.54 * eV, 10 * eV };
    G4double LSO_ABS_LENGTH[LSO_NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm, 138.*mm, 138.*mm, 138.*mm, 138.*mm };
    */

    G4MaterialPropertiesTable *LSO_mt = new G4MaterialPropertiesTable();
    LSO_mt->AddProperty ("FASTCOMPONENT", LSO_FAST_Energy, LSO_FAST_COMPONENT, LSO_NUMENTRIES_1);
    LSO_mt->AddProperty ("RINDEX",        LSO_RIND_Energy, LSO_RIND_INDEX,     LSO_NUMENTRIES_2);
    LSO_mt->AddProperty ("ABSLENGTH",     LSO_ABS_Energy,  LSO_ABS_LENGTH,     LSO_NUMENTRIES_2);

    LSO_mt->AddProperty("WLSABSLENGTH",LSO_WLS_Energy,LSO_ABS_WLS,LSO_NUMENTRIES_3);
    LSO_mt->AddProperty("WLSCOMPONENT",LSO_FAST_Energy,LSO_FAST_COMPONENT, LSO_NUMENTRIES_1);
    LSO_mt->AddConstProperty ("WLSTIMECONSTANT", 40*ns);
    
    LSO_mt->AddConstProperty ("SCINTILLATIONYIELD", 50000. / MeV);
    LSO_mt->AddConstProperty ("RESOLUTIONSCALE", 3.2);
    LSO_mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    LSO_mt->AddConstProperty ("YIELDRATIO", 1.0);
    LSO_mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);

    LSO->SetMaterialPropertiesTable (LSO_mt);

    return LSO;
}

/*============PbWO===================*/
G4Material *MyMaterials::PbWO()
{
    G4double a, z, density;
    G4Element *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Pb = new G4Element ("Lead",     "Pb",  z = 82., a = 207.21 * g / mole);
    G4Element *W = new G4Element ("Tungsten",  "W",   z = 74., a = 183.85 * g / mole);

    G4Material *PbWO = new G4Material ("PbWO", density = 8.28 * g / cm3, 3);
    PbWO->AddElement (Pb, 1);
    PbWO->AddElement (W, 1);
    PbWO->AddElement (O, 4);

    const G4int PbWO_NUMENTRIES_1 = 501;
    G4double PbWO_FAST_Energy[PbWO_NUMENTRIES_1] = {
        1.7712026714 * eV,
1.7737365808 * eV,
1.7762777507 * eV,
1.7788262123 * eV,
1.7813819971 * eV,
1.7839451367 * eV,
1.7865156628 * eV,
1.7890936075 * eV,
1.7916790029 * eV,
1.7942718813 * eV,
1.7968722754 * eV,
1.7994802177 * eV,
1.8020957413 * eV,
1.8047188792 * eV,
1.8073496647 * eV,
1.8099881314 * eV,
1.8126343129 * eV,
1.815288243 * eV,
1.817949956 * eV,
1.820619486 * eV,
1.8232968676 * eV,
1.8259821355 * eV,
1.8286753245 * eV,
1.8313764697 * eV,
1.8340856065 * eV,
1.8368027704 * eV,
1.839527997 * eV,
1.8422613224 * eV,
1.8450027827 * eV,
1.8477524143 * eV,
1.8505102537 * eV,
1.8532763378 * eV,
1.8560507036 * eV,
1.8588333883 * eV,
1.8616244294 * eV,
1.8644238647 * eV,
1.8672317319 * eV,
1.8700480694 * eV,
1.8728729154 * eV,
1.8757063086 * eV,
1.8785482879 * eV,
1.8813988923 * eV,
1.8842581611 * eV,
1.8871261339 * eV,
1.8900028506 * eV,
1.8928883511 * eV,
1.8957826758 * eV,
1.8986858652 * eV,
1.9015979601 * eV,
1.9045190015 * eV,
1.9074490308 * eV,
1.9103880894 * eV,
1.9133362191 * eV,
1.9162934621 * eV,
1.9192598607 * eV,
1.9222354574 * eV,
1.925220295 * eV,
1.9282144168 * eV,
1.931217866 * eV,
1.9342306864 * eV,
1.9372529219 * eV,
1.9402846166 * eV,
1.943325815 * eV,
1.946376562 * eV,
1.9494369025 * eV,
1.9525068819 * eV,
1.9555865457 * eV,
1.95867594 * eV,
1.9617751108 * eV,
1.9648841046 * eV,
1.9680029683 * eV,
1.9711317488 * eV,
1.9742704936 * eV,
1.9774192504 * eV,
1.9805780671 * eV,
1.983746992 * eV,
1.9869260737 * eV,
1.9901153612 * eV,
1.9933149035 * eV,
1.9965247504 * eV,
1.9997449516 * eV,
2.0029755574 * eV,
2.0062166181 * eV,
2.0094681848 * eV,
2.0127303084 * eV,
2.0160030407 * eV,
2.0192864332 * eV,
2.0225805383 * eV,
2.0258854085 * eV,
2.0292010966 * eV,
2.0325276557 * eV,
2.0358651396 * eV,
2.039213602 * eV,
2.0425730972 * eV,
2.0459436799 * eV,
2.049325405 * eV,
2.0527183278 * eV,
2.0561225041 * eV,
2.05953799 * eV,
2.0629648419 * eV,
2.0664031167 * eV,
2.0698528715 * eV,
2.0733141639 * eV,
2.0767870519 * eV,
2.080271594 * eV,
2.0837678487 * eV,
2.0872758754 * eV,
2.0907957336 * eV,
2.0943274831 * eV,
2.0978711844 * eV,
2.1014268983 * eV,
2.1049946859 * eV,
2.1085746088 * eV,
2.1121667291 * eV,
2.1157711092 * eV,
2.119387812 * eV,
2.1230169007 * eV,
2.1266584391 * eV,
2.1303124914 * eV,
2.1339791222 * eV,
2.1376583966 * eV,
2.14135038 * eV,
2.1450551384 * eV,
2.1487727383 * eV,
2.1525032465 * eV,
2.1562467304 * eV,
2.1600032578 * eV,
2.163772897 * eV,
2.1675557168 * eV,
2.1713517863 * eV,
2.1751611754 * eV,
2.1789839543 * eV,
2.1828201937 * eV,
2.1866699647 * eV,
2.1905333392 * eV,
2.1944103894 * eV,
2.1983011879 * eV,
2.2022058082 * eV,
2.2061243238 * eV,
2.2100568093 * eV,
2.2140033393 * eV,
2.2179639893 * eV,
2.2219388351 * eV,
2.2259279533 * eV,
2.2299314209 * eV,
2.2339493153 * eV,
2.2379817148 * eV,
2.242028698 * eV,
2.2460903442 * eV,
2.2501667332 * eV,
2.2542579455 * eV,
2.2583640619 * eV,
2.2624851642 * eV,
2.2666213346 * eV,
2.2707726557 * eV,
2.274939211 * eV,
2.2791210846 * eV,
2.283318361 * eV,
2.2875311255 * eV,
2.291759464 * eV,
2.296003463 * eV,
2.3002632096 * eV,
2.3045387918 * eV,
2.308830298 * eV,
2.3131378172 * eV,
2.3174614393 * eV,
2.3218012547 * eV,
2.3261573546 * eV,
2.3305298308 * eV,
2.3349187759 * eV,
2.339324283 * eV,
2.3437464461 * eV,
2.3481853598 * eV,
2.3526411195 * eV,
2.3571138213 * eV,
2.3616035619 * eV,
2.3661104389 * eV,
2.3706345507 * eV,
2.3751759962 * eV,
2.3797348752 * eV,
2.3843112885 * eV,
2.3889053372 * eV,
2.3935171236 * eV,
2.3981467505 * eV,
2.4027943217 * eV,
2.4074599417 * eV,
2.412143716 * eV,
2.4168457505 * eV,
2.4215661523 * eV,
2.4263050294 * eV,
2.4310624902 * eV,
2.4358386444 * eV,
2.4406336024 * eV,
2.4454474753 * eV,
2.4502803755 * eV,
2.4551324158 * eV,
2.4600037103 * eV,
2.4648943738 * eV,
2.4698045219 * eV,
2.4747342715 * eV,
2.47968374 * eV,
2.4846530461 * eV,
2.4896423092 * eV,
2.4946516499 * eV,
2.4996811895 * eV,
2.5047310505 * eV,
2.5098013563 * eV,
2.5148922312 * eV,
2.5200038008 * eV,
2.5251361914 * eV,
2.5302895306 * eV,
2.5354639468 * eV,
2.5406595697 * eV,
2.5458765298 * eV,
2.5511149588 * eV,
2.5563749897 * eV,
2.5616567562 * eV,
2.5669603934 * eV,
2.5722860373 * eV,
2.5776338254 * eV,
2.5830038958 * eV,
2.5883963883 * eV,
2.5938114435 * eV,
2.5992492034 * eV,
2.6047098109 * eV,
2.6101934105 * eV,
2.6157001477 * eV,
2.6212301691 * eV,
2.6267836229 * eV,
2.6323606582 * eV,
2.6379614255 * eV,
2.6435860768 * eV,
2.649234765 * eV,
2.6549076445 * eV,
2.6606048712 * eV,
2.6663266022 * eV,
2.6720729957 * eV,
2.6778442117 * eV,
2.6836404113 * eV,
2.689461757 * eV,
2.695308413 * eV,
2.7011805447 * eV,
2.7070783188 * eV,
2.7130019037 * eV,
2.7189514693 * eV,
2.7249271868 * eV,
2.7309292291 * eV,
2.7369577704 * eV,
2.7430129867 * eV,
2.7490950554 * eV,
2.7552041556 * eV,
2.7613404677 * eV,
2.7675041741 * eV,
2.7736954586 * eV,
2.7799145067 * eV,
2.7861615056 * eV,
2.7924366441 * eV,
2.7987401129 * eV,
2.8050721041 * eV,
2.8114328118 * eV,
2.8178224318 * eV,
2.8242411617 * eV,
2.8306892009 * eV,
2.8371667506 * eV,
2.8436740138 * eV,
2.8502111954 * eV,
2.8567785023 * eV,
2.8633761432 * eV,
2.8700043287 * eV,
2.8766632715 * eV,
2.883353186 * eV,
2.890074289 * eV,
2.8968267991 * eV,
2.9036109368 * eV,
2.9104269249 * eV,
2.9172749882 * eV,
2.9241553538 * eV,
2.9310682506 * eV,
2.93801391 * eV,
2.9449925653 * eV,
2.9520044524 * eV,
2.9590498091 * eV,
2.9661288756 * eV,
2.9732418945 * eV,
2.9803891106 * eV,
2.9875707711 * eV,
2.9947871256 * eV,
3.0020384262 * eV,
3.0093249272 * eV,
3.0166468856 * eV,
3.024004561 * eV,
3.0313982152 * eV,
3.0388281127 * eV,
3.0462945209 * eV,
3.0537977094 * eV,
3.0613379506 * eV,
3.0689155198 * eV,
3.0765306948 * eV,
3.0841837562 * eV,
3.0918749875 * eV,
3.099604675 * eV,
3.1073731078 * eV,
3.1151805779 * eV,
3.1230273804 * eV,
3.1309138131 * eV,
3.1388401772 * eV,
3.1468067766 * eV,
3.1548139186 * eV,
3.1628619133 * eV,
3.1709510742 * eV,
3.1790817179 * eV,
3.1872541645 * eV,
3.1954687371 * eV,
3.2037257623 * eV,
3.2120255699 * eV,
3.2203684935 * eV,
3.2287548698 * eV,
3.2371850392 * eV,
3.2456593455 * eV,
3.2541781365 * eV,
3.2627417632 * eV,
3.2713505805 * eV,
3.2800049471 * eV,
3.2887052255 * eV,
3.2974517819 * eV,
3.3062449867 * eV,
3.3150852139 * eV,
3.3239728418 * eV,
3.3329082527 * eV,
3.3418918329 * eV,
3.350923973 * eV,
3.3600050678 * eV,
3.3691355163 * eV,
3.3783157221 * eV,
3.3875460929 * eV,
3.3968270411 * eV,
3.4061589835 * eV,
3.4155423416 * eV,
3.4249775414 * eV,
3.4344650139 * eV,
3.4440051944 * eV,
3.4535985237 * eV,
3.4632454469 * eV,
3.4729464146 * eV,
3.482701882 * eV,
3.4925123099 * eV,
3.5023781638 * eV,
3.512299915 * eV,
3.5222780398 * eV,
3.5323130199 * eV,
3.5424053429 * eV,
3.5525555014 * eV,
3.5627639943 * eV,
3.5730313256 * eV,
3.5833580058 * eV,
3.5937445507 * eV,
3.6041914826 * eV,
3.6146993294 * eV,
3.6252686257 * eV,
3.635899912 * eV,
3.6465937353 * eV,
3.657350649 * eV,
3.668171213 * eV,
3.6790559941 * eV,
3.6900055655 * eV,
3.7010205075 * eV,
3.7121014072 * eV,
3.7232488589 * eV,
3.7344634639 * eV,
3.7457458308 * eV,
3.7570965758 * eV,
3.7685163222 * eV,
3.7800057012 * eV,
3.7915653517 * eV,
3.8031959202 * eV,
3.8148980615 * eV,
3.8266724383 * eV,
3.8385197214 * eV,
3.8504405901 * eV,
3.8624357321 * eV,
3.8745058438 * eV,
3.8866516301 * eV,
3.898873805 * eV,
3.9111730915 * eV,
3.9235502215 * eV,
3.9360059365 * eV,
3.9485409873 * eV,
3.9611561342 * eV,
3.9738521474 * eV,
3.9866298071 * eV,
3.9994899032 * eV,
4.0124332362 * eV,
4.0254606169 * eV,
4.0385728664 * eV,
4.051770817 * eV,
4.0650553115 * eV,
4.0784272039 * eV,
4.0918873597 * eV,
4.1054366556 * eV,
4.1190759801 * eV,
4.1328062333 * eV,
4.1466283278 * eV,
4.1605431879 * eV,
4.1745517508 * eV,
4.1886549662 * eV,
4.2028537966 * eV,
4.2171492177 * eV,
4.2315422184 * eV,
4.2460338014 * eV,
4.2606249828 * eV,
4.2753167931 * eV,
4.2901102768 * eV,
4.3050064931 * eV,
4.3200065157 * eV,
4.3351114336 * eV,
4.3503223509 * eV,
4.3656403873 * eV,
4.3810666784 * eV,
4.3966023759 * eV,
4.4122486477 * eV,
4.4280066786 * eV,
4.4438776703 * eV,
4.4598628417 * eV,
4.4759634296 * eV,
4.4921806884 * eV,
4.5085158909 * eV,
4.5249703285 * eV,
4.5415453114 * eV,
4.5582421691 * eV,
4.5750622509 * eV,
4.5920069259 * eV,
4.6090775836 * eV,
4.6262756343 * eV,
4.6436025094 * eV,
4.6610596617 * eV,
4.678648566 * eV,
4.6963707197 * eV,
4.7142276426 * eV,
4.7322208779 * eV,
4.7503519923 * eV,
4.7686225769 * eV,
4.7870342471 * eV,
4.8055886434 * eV,
4.8242874319 * eV,
4.8431323047 * eV,
4.8621249804 * eV,
4.8812672047 * eV,
4.900560751 * eV,
4.9200074206 * eV,
4.9396090438 * eV,
4.95936748 * eV,
4.9792846185 * eV,
4.999362379 * eV,
5.0196027126 * eV,
5.0400076016 * eV,
5.0605790612 * eV,
5.0813191393 * eV,
5.1022299177 * eV,
5.1233135124 * eV,
5.1445720747 * eV,
5.1660077917 * eV,
5.187622887 * eV,
5.2094196218 * eV,
5.2314002954 * eV,
5.2535672458 * eV,
5.2759228511 * eV,
5.2984695299 * eV,
5.3212097425 * eV,
5.3441459914 * eV,
5.3672808225 * eV,
5.3906168261 * eV,
5.4141566376 * eV,
5.4379029386 * eV,
5.4618584581 * eV,
5.4860259735 * eV,
5.5104083111 * eV,
5.5350083482 * eV,
5.5598290135 * eV,
5.5848732883 * eV,
5.6101442081 * eV,
5.6356448636 * eV,
5.6613784018 * eV,
5.6873480275 * eV,
5.7135570046 * eV,
5.7400086574 * eV,
5.7667063721 * eV,
5.7936535981 * eV,
5.8208538498 * eV,
5.8483107075 * eV,
5.8760278199 * eV,
5.9040089048 * eV,
5.9322577512 * eV,
5.9607782212 * eV,
5.9895742512 * eV,
6.0186498544 * eV,
6.048009122 * eV,
6.0776562255 * eV,
6.1075954187 * eV,
6.1378310396 * eV,
6.1683675124 * eV,
6.19920935 * eV

    };
    G4double PbWO_FAST_COMPONENT[PbWO_NUMENTRIES_1] = {
        5.483032797e-45	,
1.102767892e-44	,
2.212389792e-44	,
4.427447731e-44	,
8.838112051e-44	,
1.759866919e-43	,
3.495541125e-43	,
6.925693504e-43	,
1.368757096e-42	,
2.698384064e-42	,
5.30634407e-42	,
1.040881558e-41	,
2.036673839e-41	,
3.975171954e-41	,
7.739352331e-41	,
1.503029763e-40	,
2.9116878e-40	,
5.626473746e-40	,
1.0845312e-39	,
2.085268909e-39	,
3.999413879e-39	,
7.651470258e-39	,
1.460184397e-38	,
2.779615829e-38	,
5.278081751e-38	,
9.997276711e-38	,
1.888867861e-37	,
3.559882839e-37	,
6.692433996e-37	,
1.255008745e-36	,
2.347597679e-36	,
4.380410936e-36	,
8.153053674e-36	,
1.513700701e-35	,
2.803328463e-35	,
5.178717548e-35	,
9.542995673e-35	,
1.754128855e-34	,
3.216270167e-34	,
5.882444195e-34	,
1.073191868e-33	,
1.953040252e-33	,
3.545351334e-33	,
6.41980191e-33	,
1.159573389e-32	,
2.089243772e-32	,
3.754864386e-32	,
6.731528054e-32	,
1.203780566e-31	,
2.147312534e-31	,
3.820827706e-31	,
6.78162722e-31	,
1.2006727e-30	,
2.120457745e-30	,
3.735501138e-30	,
6.564208803e-30	,
1.150615354e-29	,
2.011834294e-29	,
3.508879971e-29	,
6.104626279e-29	,
1.059409627e-28	,
1.833931086e-28	,
3.166768911e-28	,
5.454613679e-28	,
9.371862012e-28	,
1.606208936e-27	,
2.745948916e-27	,
4.682708604e-27	,
7.965555664e-27	,
1.351603427e-26	,
2.287687795e-26	,
3.862411043e-26	,
6.5048081e-26	,
1.092759904e-25	,
1.831172584e-25	,
3.060892433e-25	,
5.103652797e-25	,
8.488450867e-25	,
1.408283272e-24	,
2.330589932e-24	,
3.847299313e-24	,
6.335200261e-24	,
1.04058841e-23	,
1.704950933e-23	,
2.786500011e-23	,
4.542767156e-23	,
7.387477464e-23	,
1.198356745e-22	,
1.939055966e-22	,
3.129744085e-22	,
5.038967697e-22	,
8.092609511e-22	,
1.296432351e-21	,
2.071692997e-21	,
3.30228993e-21	,
5.250724915e-21	,
8.327940162e-21	,
1.317559357e-20	,
2.07929949e-20	,
3.2732424e-20	,
5.139886786e-20	,
8.050877189e-20	,
1.257902888e-19	,
1.960492976e-19	,
3.047879065e-19	,
4.726551941e-19	,
7.311481788e-19	,
1.128185813e-18	,
1.736481374e-18	,
2.666084368e-18	,
4.083117816e-18	,
6.237695898e-18	,
9.50540769e-18	,
1.444879279e-17	,
2.190819718e-17	,
3.313568728e-17	,
4.999189374e-17	,
7.523457259e-17	,
1.129404702e-16	,
1.691203966e-16	,
2.526135542e-16	,
3.763843645e-16	,
5.593978107e-16	,
8.293239635e-16	,
1.226427643e-15	,
1.809147226e-15	,
2.662074186e-15	,
3.907335126e-15	,
5.720782451e-15	,
8.354961785e-15	,
1.217160267e-14	,
1.768745424e-14	,
2.563876818e-14	,
3.70717635e-14	,
5.346918936e-14	,
7.692689753e-14	,
1.103994982e-13	,
1.580411731e-13	,
2.256771839e-13	,
3.214543645e-13	,
4.567360204e-13	,
6.473295969e-13	,
9.151661085e-13	,
1.290591072e-12	,
1.815480751e-12	,
2.547468979e-12	,
3.565664062e-12	,
4.978358953e-12	,
6.933399971e-12	,
9.63209074e-12	,
1.334778307e-11	,
1.845066308e-11	,
2.544070141e-11	,
3.499132974e-11	,
4.800716685e-11	,
6.570009091e-11	,
8.96891954e-11	,
1.221317413e-10	,
1.658942122e-10	,
2.247750916e-10	,
3.037941425e-10	,
4.095669202e-10	,
5.507881812e-10	,
7.388539793e-10	,
9.886598203e-10	,
1.319621602e-09	,
1.756977547e-09	,
2.333443399e-09	,
3.09131025e-09	,
4.085095189e-09	,
5.384880021e-09	,
7.080503565e-09	,
9.286809223e-09	,
1.215019271e-08	,
1.585674608e-08	,
2.064235494e-08	,
2.680517672e-08	,
3.472101177e-08	,
4.486217581e-08	,
5.782059518e-08	,
7.433597574e-08	,
9.533004516e-08	,
1.219480373e-07	,
1.55608779e-07	,
1.980649546e-07	,
2.514753644e-07	,
3.184912589e-07	,
4.023591228e-07	,
5.070426033e-07	,
6.373666191e-07	,
7.991870553e-07	,
9.995898353e-07	,
1.247123565e-06	,
1.552070353e-06	,
1.926759837e-06	,
2.385931827e-06	,
2.947153388e-06	,
3.631296515e-06	,
4.463082859e-06	,
5.471702172e-06	,
6.691511288e-06	,
8.162820438e-06	,
9.93277357e-06	,
1.205632901e-05	,
1.459734629e-05	,
1.762978412e-05	,
2.123901353e-05	,
2.552324872e-05	,
3.059509651e-05	,
3.658322314e-05	,
4.363413475e-05	,
5.191406478e-05	,
6.161095842e-05	,
7.293654023e-05	,
8.612844695e-05	,
0.0001015	,
0.0001192	,
0.0001397	,
0.0001633	,
0.0001905	,
0.0002216	,
0.0002571	,
0.0002976	,
0.0003436	,
0.0003958	,
0.0004547	,
0.0005210	,
0.0005956	,
0.0006791	,
0.0007725	,
0.0008764	,
0.0009919	,
0.0011197	,
0.0012609	,
0.0014164	,
0.0015870	,
0.0017737	,
0.0019775	,
0.0021992	,
0.0024396	,
0.0026995	,
0.0029797	,
0.0032808	,
0.0036032	,
0.0039475	,
0.0043139	,
0.0047025	,
0.0051132	,
0.0055460	,
0.0060005	,
0.0064759	,
0.0069715	,
0.0074864	,
0.0080192	,
0.0085684	,
0.0091325	,
0.0097093	,
0.0102968	,
0.0108926	,
0.0114941	,
0.0120985	,
0.0127030	,
0.0133043	,
0.0138992	,
0.0144846	,
0.0150569	,
0.0156127	,
0.0161486	,
0.0166612	,
0.0171472	,
0.0176033	,
0.0180263	,
0.0184135	,
0.0187620	,
0.0190694	,
0.0193334	,
0.0195521	,
0.0197240	,
0.0198476	,
0.0199222	,
0.0199471	,
0.0199222	,
0.0198476	,
0.0197240	,
0.0195521	,
0.0193334	,
0.0190694	,
0.0187620	,
0.0184135	,
0.0180263	,
0.0176033	,
0.0171472	,
0.0166612	,
0.0161486	,
0.0156127	,
0.0150569	,
0.0144846	,
0.0138992	,
0.0133043	,
0.0127030	,
0.0120985	,
0.0114941	,
0.0108926	,
0.0102968	,
0.0097093	,
0.0091325	,
0.0085684	,
0.0080192	,
0.0074864	,
0.0069715	,
0.0064759	,
0.0060005	,
0.0055460	,
0.0051132	,
0.0047025	,
0.0043139	,
0.0039475	,
0.0036032	,
0.0032808	,
0.0029797	,
0.0026995	,
0.0024396	,
0.0021992	,
0.0019775	,
0.0017737	,
0.0015870	,
0.0014164	,
0.0012609	,
0.0011197	,
0.0009919	,
0.0008764	,
0.0007725	,
0.0006791	,
0.0005956	,
0.0005210	,
0.0004547	,
0.0003958	,
0.0003436	,
0.0002976	,
0.0002571	,
0.0002216	,
0.0001905	,
0.0001633	,
0.0001397	,
0.0001192	,
0.0001015	,
8.612844695e-05	,
7.293654023e-05	,
6.161095842e-05	,
5.191406478e-05	,
4.363413475e-05	,
3.658322314e-05	,
3.059509651e-05	,
2.552324872e-05	,
2.123901353e-05	,
1.762978412e-05	,
1.459734629e-05	,
1.205632901e-05	,
9.93277357e-06	,
8.162820438e-06	,
6.691511288e-06	,
5.471702172e-06	,
4.463082859e-06	,
3.631296515e-06	,
2.947153388e-06	,
2.385931827e-06	,
1.926759837e-06	,
1.552070353e-06	,
1.247123565e-06	,
9.995898353e-07	,
7.991870553e-07	,
6.373666191e-07	,
5.070426033e-07	,
4.023591228e-07	,
3.184912589e-07	,
2.514753644e-07	,
1.980649546e-07	,
1.55608779e-07	,
1.219480373e-07	,
9.533004516e-08	,
7.433597574e-08	,
5.782059518e-08	,
4.486217581e-08	,
3.472101177e-08	,
2.680517672e-08	,
2.064235494e-08	,
1.585674608e-08	,
1.215019271e-08	,
9.286809223e-09	,
7.080503565e-09	,
5.384880021e-09	,
4.085095189e-09	,
3.09131025e-09	,
2.333443399e-09	,
1.756977547e-09	,
1.319621602e-09	,
9.886598203e-10	,
7.388539793e-10	,
5.507881812e-10	,
4.095669202e-10	,
3.037941425e-10	,
2.247750916e-10	,
1.658942122e-10	,
1.221317413e-10	,
8.96891954e-11	,
6.570009091e-11	,
4.800716685e-11	,
3.499132974e-11	,
2.544070141e-11	,
1.845066308e-11	,
1.334778307e-11	,
9.63209074e-12	,
6.933399971e-12	,
4.978358953e-12	,
3.565664062e-12	,
2.547468979e-12	,
1.815480751e-12	,
1.290591072e-12	,
9.151661085e-13	,
6.473295969e-13	,
4.567360204e-13	,
3.214543645e-13	,
2.256771839e-13	,
1.580411731e-13	,
1.103994982e-13	,
7.692689753e-14	,
5.346918936e-14	,
3.70717635e-14	,
2.563876818e-14	,
1.768745424e-14	,
1.217160267e-14	,
8.354961785e-15	,
5.720782451e-15	,
3.907335126e-15	,
2.662074186e-15	,
1.809147226e-15	,
1.226427643e-15	,
8.293239635e-16	,
5.593978107e-16	,
3.763843645e-16	,
2.526135542e-16	,
1.691203966e-16	,
1.129404702e-16	,
7.523457259e-17	,
4.999189374e-17	,
3.313568728e-17	,
2.190819718e-17	,
1.444879279e-17	,
9.50540769e-18	,
6.237695898e-18	,
4.083117816e-18	,
2.666084368e-18	,
1.736481374e-18	,
1.128185813e-18	,
7.311481788e-19	,
4.726551941e-19	,
3.047879065e-19	,
1.960492976e-19	,
1.257902888e-19	,
8.050877189e-20	,
5.139886786e-20	,
3.2732424e-20	,
2.07929949e-20	,
1.317559357e-20	,
8.327940162e-21	,
5.250724915e-21	,
3.30228993e-21	,
2.071692997e-21	,
1.296432351e-21	,
8.092609511e-22	,
5.038967697e-22	,
3.129744085e-22	,
1.939055966e-22	,
1.198356745e-22	,
7.387477464e-23	,
4.542767156e-23	,
2.786500011e-23	,
1.704950933e-23	,
1.04058841e-23	,
6.335200261e-24	,
3.847299313e-24	,
2.330589932e-24	,
1.408283272e-24	,
8.488450867e-25	,
5.103652797e-25	,
3.060892433e-25	,
1.831172584e-25	,
1.092759904e-25	,
6.5048081e-26	,
3.862411043e-26	,
2.287687795e-26	,
1.351603427e-26	,
7.965555664e-27	,
4.682708604e-27	,
2.745948916e-27	,
1.606208936e-27	,
9.371862012e-28	,
5.454613679e-28	,
3.166768911e-28	,
1.833931086e-28	,
1.059409627e-28	
    };

    G4double PbWO_indexZero     = 1.5861;
    G4double PbWO_nVec[1]       = { 1.1062 };
    G4double PbWO_lVec[1]       = { 270.63 };

    const G4int PbWO_NUMENTRIES_2 = 5;
    G4double PbWO_RIND_Energy[PbWO_NUMENTRIES_2]      = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 2.952 * eV, 4.08 * eV };
    //G4double PbWO_RIND_INDEX[PbWO_NUMENTRIES_2]       = { 2.325, 2.325, 2.325, 2.325, 2.325};
    //G4double PbWO_RIND_INDEX[PbWO_NUMENTRIES_2]       = { 2.368, 2.368, 2.368, 2.368, 2.368};

    int sizeVect = sizeof(PbWO_nVec)/sizeof(*PbWO_nVec);
    G4double PbWO_RIND_INDEX[PbWO_NUMENTRIES_2]       = {
    CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(0.0001)),
    CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(1.0)),
    CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(1.84)),
    CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(2.952)),
    CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(4.08)),
    };

    const G4int PbWO_ABS_entries = 70;
    G4double PbWO_ABS_Energy[PbWO_ABS_entries]       = {
        1.25237 * eV, 1.26514 * eV, 1.27819 * eV, 1.2915 * eV, 1.3051 * eV, 1.31898 * eV, 1.33316 * eV, 1.34765 * eV, 1.36246 * eV, 1.3776 * eV,
        1.39308 * eV, 1.40891 * eV, 1.42511 * eV, 1.44168 * eV, 1.45864 * eV, 1.476 * eV, 1.49379 * eV, 1.512 * eV, 1.53067 * eV, 1.5498 * eV,
        1.56942 * eV, 1.58954 * eV, 1.61018 * eV, 1.63137 * eV, 1.65312 * eV, 1.67546 * eV, 1.69841 * eV, 1.722 * eV, 1.74626 * eV, 1.7712 * eV,
        1.79687 * eV, 1.8233 * eV, 1.85051 * eV, 1.87855 * eV, 1.90745 * eV, 1.93725 * eV, 1.968 * eV, 1.99974 * eV, 2.03253 * eV, 2.0664 * eV,
        2.10143 * eV, 2.13766 * eV, 2.17516 * eV, 2.214 * eV, 2.25426 * eV, 2.296 * eV, 2.33932 * eV, 2.38431 * eV, 2.43106 * eV, 2.47968 * eV,
        2.53029 * eV, 2.583 * eV, 2.63796 * eV, 2.69531 * eV, 2.7552 * eV, 2.81782 * eV, 2.88335 * eV, 2.952 * eV, 3.024 * eV, 3.0996 * eV,
        3.17908 * eV, 3.26274 * eV, 3.35092 * eV, 3.44401 * eV, 3.54241 * eV, 3.64659 * eV, 3.7571 * eV, 3.87451 * eV, 3.99949 * eV, 4.13281 * eV,


    };

    G4double PbWO_ABS_LENGTH[PbWO_ABS_entries] = {
        3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm,
        3105 * mm, 2745 * mm, 2460 * mm, 2230 * mm, 2039 * mm, 1877 * mm, 1859 * mm, 1826 * mm, 1764 * mm, 1760 * mm,
        1664 * mm, 1585 * mm, 1471 * mm, 1376 * mm, 1272 * mm, 1187 * mm, 1114 * mm, 1046 * mm, 993.2 * mm, 942.9 * mm,
        898.8 * mm, 856.9 * mm, 821.7 * mm, 794.2 * mm, 767.7 * mm, 746.5 * mm, 725.6 * mm, 710.7 * mm, 695.3 * mm, 686.2 * mm,
        674.8 * mm, 663.5 * mm, 648.3 * mm, 633.4 * mm, 622.3 * mm, 607.8 * mm, 590.9 * mm, 568.9 * mm, 541.4 * mm, 502.9 * mm,
        467 * mm, 430.2 * mm, 390.1 * mm, 345.3 * mm, 298.9 * mm, 256.7 * mm, 219.8 * mm, 185.4 * mm, 150.9 * mm, 116.4 * mm,
        84.8 * mm, 59.4 * mm, 41.1 * mm, 27.5 * mm, 24.2 * mm, 24.2 * mm, 24.3 * mm, 24.3 * mm, 24.4 * mm, 24.6 * mm
    };
    

/*
    const G4int PbWO_ABS_entries = 4;
    G4double PbWO_ABS_Energy[PbWO_ABS_entries]       = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double PbWO_ABS_LENGTH[PbWO_ABS_entries] 	= { 185.4 * mm, 185.4 * mm, 185.4 * mm, 185.4 * mm};
    //G4double PbWO_ABS_LENGTH[PbWO_ABS_entries] 	= { 5 * mm, 5 * mm, 5 * mm, 5 * mm};
*/
    G4MaterialPropertiesTable *PbWO_mt = new G4MaterialPropertiesTable();
    PbWO_mt->AddProperty ("FASTCOMPONENT", PbWO_FAST_Energy, PbWO_FAST_COMPONENT, PbWO_NUMENTRIES_1);
    PbWO_mt->AddProperty ("RINDEX",        PbWO_RIND_Energy, PbWO_RIND_INDEX,     PbWO_NUMENTRIES_2);
    PbWO_mt->AddProperty ("ABSLENGTH",      PbWO_ABS_Energy,  PbWO_ABS_LENGTH,  PbWO_ABS_entries);

    PbWO_mt->AddConstProperty ("SCINTILLATIONYIELD", 60000. / MeV);
    PbWO_mt->AddConstProperty ("RESOLUTIONSCALE", 3.2);
    PbWO_mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    PbWO_mt->AddConstProperty ("YIELDRATIO", 1.0);
    PbWO_mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);

    const G4int PbWO_SCY_NUMENTRIES = 12;
    G4double PbWO_SCY_Energy[PbWO_SCY_NUMENTRIES] = { 0.000 * MeV, 0.015 * MeV, 0.020 * MeV, 0.030 * MeV, 0.040 * MeV, 0.060 * MeV,
            0.080 * MeV, 0.090 * MeV, 0.105 * MeV, 0.300 * MeV, 0.500 * MeV, 1.000 * MeV
                                                    };
    G4double PbWO_SCY[PbWO_SCY_NUMENTRIES]        = { 0.10, 0.46, 0.60, 0.68, 0.74, 0.80, 0.82,
            0.84, 0.87,  0.96,  0.98,  1.00
                                                    };
    for (int i = 0; i < PbWO_SCY_NUMENTRIES; i++) {
        PbWO_SCY[i] = 60000.0 * MeV * PbWO_SCY[i] * PbWO_SCY_Energy[i];
    }
    PbWO_mt->AddProperty ("ELECTRONSCINTILLATIONYIELD", PbWO_SCY_Energy, PbWO_SCY, PbWO_SCY_NUMENTRIES);

    PbWO->SetMaterialPropertiesTable (PbWO_mt);

    return PbWO;
}

G4double MyMaterials::CalculateSellmeier (int size, G4double indexZero, G4double *nVec, G4double *lVec, G4double wavelength)
{

    /*------http://gentitfx.fr/SLitrani/code/SLitraniCode/TLitSellmeier.html----*/

    float partial = indexZero * indexZero;
    float sum = 0;
    for (int i = 0; i < size; i++) {

        sum += nVec[i] * nVec[i] / (1 - lVec[i] * lVec[i] / (wavelength*wavelength));

    }

    partial += sum;
    partial += 1;

    G4cout << "Wavelength: " << wavelength << " -> rifr. index: " << sqrt (partial) << G4endl;

    return sqrt (partial);
}

G4double MyMaterials::fromEvToNm (G4double energy)
{

    return 1239.84187 / energy;

}

G4double MyMaterials::fromNmToEv (G4double wavelength)
{


    return 1239.84187 / wavelength;

}

