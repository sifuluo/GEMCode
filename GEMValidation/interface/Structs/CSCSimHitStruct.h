#ifndef GEMCode_GEMValidation_CSCSimHitStruct
#define GEMCode_GEMValidation_CSCSimHitStruct

#include "TTree.h"

namespace gem {

  struct CSCSimHitStruct {

    static const int nStations = 11;

    // bools
    bool has_csc_sh_odd[nStations];
    bool has_csc_sh_even[nStations];

    // ints
    int nlayers_csc_sh_even[nStations];
    int nlayers_csc_sh_odd[nStations];

    int chamber_sh_odd[nStations];
    int chamber_sh_even[nStations];

    // floats
    float dphi_sh_even[nStations];
    float dphi_sh_odd[nStations];

    float dphipositionpt_cscsh_even[nStations];
    float dphipositionpt_cscsh_odd[nStations];

    float bending_sh[nStations];
    float phi_cscsh_even[nStations];
    float phi_cscsh_odd[nStations];
    float eta_cscsh_even[nStations];
    float eta_cscsh_odd[nStations];
    float perp_cscsh_even[nStations];
    float perp_cscsh_odd[nStations];

    float phi_layer1_sh_even[nStations];
    float eta_layer1_sh_even[nStations];
    float phi_layer1_sh_odd[nStations];
    float eta_layer1_sh_odd[nStations];
    float perp_layer1_sh_odd[nStations];
    float perp_layer1_sh_even[nStations];
    float z_layer1_sh_odd[nStations];
    float z_layer1_sh_even[nStations];

    float phi_layer6_sh_even[nStations];
    float eta_layer6_sh_even[nStations];
    float phi_layer6_sh_odd[nStations];
    float eta_layer6_sh_odd[nStations];
    float perp_layer6_sh_odd[nStations];
    float perp_layer6_sh_even[nStations];
    float z_layer6_sh_odd[nStations];
    float z_layer6_sh_even[nStations];

    void init() {
      for (unsigned i = 0 ; i < nStations; i++) {

        has_csc_sh_even[i] = false;
        has_csc_sh_odd[i] = false;

        chamber_sh_odd[i] = -1;
        chamber_sh_even[i] = -1;

        nlayers_csc_sh_odd[i] = -1;
        nlayers_csc_sh_even[i] = -1;

        perp_cscsh_odd[i] = -0.0;
        perp_cscsh_even[i] = -0.0;

        phi_cscsh_even[i] = -9.0;
        phi_cscsh_odd[i] = -9.0;

        eta_cscsh_even[i] = -9.0;
        eta_cscsh_odd[i] = -9.0;

        dphi_sh_odd[i] = -9;
        dphi_sh_even[i] = -9;

        bending_sh[i] = -10;
      }
    };

    void book(TTree* t) {

      t->Branch("has_csc_sh_even", has_csc_sh_even, "has_csc_sh_even[11]/O");
      t->Branch("has_csc_sh_odd", has_csc_sh_odd, "has_csc_sh_odd[11]/O");

      t->Branch("chamber_sh_odd", chamber_sh_odd, "chamber_sh_odd[11]/I");
      t->Branch("chamber_sh_even", chamber_sh_even, "chamber_sh_even[11]/I");

      t->Branch("nlayers_csc_sh_odd", nlayers_csc_sh_odd, "nlayers_csc_sh_odd[11]/I");
      t->Branch("nlayers_csc_sh_even", nlayers_csc_sh_even, "nlayers_csc_sh_even[11]/I");

      t->Branch("bending_sh", bending_sh, "bending_sh[11]/I");

      t->Branch("perp_cscsh_odd", perp_cscsh_odd, "perp_cscsh_odd[11]/F");
      t->Branch("perp_cscsh_even", perp_cscsh_even, "perp_cscsh_even[11]/F");

      t->Branch("phi_cscsh_even", phi_cscsh_even, "phi_cscsh_even[11]/F");
      t->Branch("phi_cscsh_odd", phi_cscsh_odd, "phi_cscsh_odd[11]/F");

      t->Branch("eta_cscsh_even", eta_cscsh_even, "eta_cscsh_even[11]/F");
      t->Branch("eta_cscsh_odd", eta_cscsh_odd, "eta_cscsh_odd[11]/F");

      t->Branch("dphi_sh_odd", dphi_sh_odd, "dphi_sh_odd[11]/F");
      t->Branch("dphi_sh_even", dphi_sh_even, "dphi_sh_even[11]/F");
    }
  };
}  // namespace

#endif
