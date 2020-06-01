#ifndef GEMCode_GEMValidation_GEMSimHitStruct
#define GEMCode_GEMValidation_GEMSimHitStruct

#include "TTree.h"

namespace gem {

  struct GEMSimHitStruct {

    static const int nStations = 3;

    // bools
    bool has_gem_sh_even[nStations];
    bool has_gem_sh_odd[nStations];

    bool has_gem_sh2_even[nStations];
    bool has_gem_sh2_odd[nStations];

    bool has_gemcopad_sh_even[nStations];
    bool has_gemcopad_sh_odd[nStations];

    // ints
    int chamber_sh_odd[nStations];
    int chamber_sh_even[nStations];

    // floats
    float dphi_sh_even[nStations];
    float dphi_sh_odd[nStations];

    float dphipositionpt_gemsh_even[nStations];
    float dphipositionpt_gemsh_odd[nStations];

    float bending_sh[nStations];

    float perp_gemsh_even[nStations];
    float perp_gemsh_odd[nStations];

    float centralperp_gemsh_even[nStations];
    float centralperp_gemsh_odd[nStations];

    float strip_gemsh_odd[nStations];
    float strip_gemsh_even[nStations];

    float eta_gemsh_odd[nStations];
    float eta_gemsh_even[nStations];

    float phi_gemsh_odd[nStations];
    float phi_gemsh_even[nStations];


    void init() {
      for (unsigned i = 0 ; i < nStations; i++) {

        has_gem_sh_even[i] = false;
        has_gem_sh_odd[i] = false;

        has_gem_sh2_even[i] = false;
        has_gem_sh2_odd[i] = false;

        has_gemcopad_sh_even[i] = false;
        has_gemcopad_sh_odd[i] = false;

        chamber_sh_odd[i] = -1;
        chamber_sh_even[i] = -1;

        bending_sh[i] = -10;

        perp_gemsh_odd[i] = -0.0;
        perp_gemsh_even[i] = -0.0;

        centralperp_gemsh_odd[i] = -0.0;
        centralperp_gemsh_even[i] = -0.0;

        strip_gemsh_odd[i] = -9.;
        strip_gemsh_even[i] = -9.;

        eta_gemsh_odd[i] = -9.;
        eta_gemsh_even[i] = -9.;

        phi_gemsh_odd[i] = -9.;
        phi_gemsh_even[i] = -9.;

        dphi_sh_odd[i] = -9;
        dphi_sh_even[i] = -9;
      }
    };

    void book(TTree* t) {

      t->Branch("has_gem_sh_odd", has_gem_sh_odd, "has_gem_sh_odd[3]/O");
      t->Branch("has_gem_sh_even", has_gem_sh_even, "has_gem_sh_even[3]/O");

      t->Branch("has_gem_sh2_odd", has_gem_sh2_odd, "has_gem_sh2_odd[3]/O");
      t->Branch("has_gem_sh2_even", has_gem_sh2_even, "has_gem_sh2_even[3]/O");

      t->Branch("has_gemcopad_sh_even", has_gemcopad_sh_even, "has_gemcopad_sh_even[3]/O");
      t->Branch("has_gemcopad_sh_odd", has_gemcopad_sh_odd, "has_gemcopad_sh_odd[3]/O");

      t->Branch("chamber_sh_odd", chamber_sh_odd, "chamber_sh_odd[3]/I");
      t->Branch("chamber_sh_even", chamber_sh_even, "chamber_sh_even[3]/I");

      t->Branch("bending_sh", bending_sh, "bending_sh[3]/F");

      t->Branch("perp_gemsh_odd", perp_gemsh_odd, "perp_gemsh_odd[3]/F");
      t->Branch("perp_gemsh_even", perp_gemsh_even, "perp_gemsh_even[3]/F");

      t->Branch("centralperp_gemsh_odd", centralperp_gemsh_odd, "centralperp_gemsh_odd[3]/F");
      t->Branch("centralperp_gemsh_even", centralperp_gemsh_even, "centralperp_gemsh_even[3]/F");

      t->Branch("strip_gemsh_odd", strip_gemsh_odd, "strip_gemsh_odd[3]/F");
      t->Branch("strip_gemsh_even", strip_gemsh_even, "strip_gemsh_even[3]/F");

      t->Branch("eta_gemsh_odd", eta_gemsh_odd, "eta_gemsh_odd[3]/F");
      t->Branch("eta_gemsh_even", eta_gemsh_even, "eta_gemsh_even[3]/F");

      t->Branch("phi_gemsh_odd", phi_gemsh_odd, "phi_gemsh_odd[3]/F");
      t->Branch("phi_gemsh_even", phi_gemsh_even, "phi_gemsh_even[3]/F");

      t->Branch("dphi_sh_odd", dphi_sh_odd, "dphi_sh_odd[3]/F");
      t->Branch("dphi_sh_even", dphi_sh_even, "dphi_sh_even[3]/F");
    }
  };
}  // namespace

#endif
