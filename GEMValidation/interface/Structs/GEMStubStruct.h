#ifndef GEMCode_GEMValidation_GEMStubStruct
#define GEMCode_GEMValidation_GEMStubStruct

#include "TTree.h"
#include <string>

namespace gem {

  struct GEMStubStruct {

    static const int nStations = 3;

    // bools
    bool has_gem_pad_even[nStations];
    bool has_gem_pad2_even[nStations];
    bool has_gem_copad_even[nStations];

    bool has_gem_pad_odd[nStations];
    bool has_gem_pad2_odd[nStations];
    bool has_gem_copad_odd[nStations];

    // ints
    int pad_odd[nStations];
    int pad_even[nStations];
    int copad_odd[nStations];
    int copad_even[nStations];
    int bx_pad_odd[nStations];
    int bx_pad_even[nStations];

    // floats
    float phi_pad_odd[nStations];
    float phi_pad_even[nStations];
    float z_pad_odd[nStations];
    float z_pad_even[nStations];
    float eta_pad_odd[nStations];
    float eta_pad_even[nStations];

    float dphi_pad_odd[nStations];
    float dphi_pad_even[nStations];
    float deta_pad_odd[nStations];
    float deta_pad_even[nStations];

    void init() {
      for (unsigned i = 0 ; i < nStations; i++) {
        pad_odd[i] = -1;
        pad_even[i] = -1;
        copad_odd[i] = -1;
        copad_even[i] = -1;

        has_gem_pad_even[i] = 0;
        has_gem_pad2_even[i] = 0;
        has_gem_copad_even[i] = 0;

        has_gem_pad_odd[i] = 0;
        has_gem_pad2_odd[i] = 0;
        has_gem_copad_odd[i] = 0;

        bx_pad_odd[i] = -9;
        bx_pad_even[i] = -9;
        phi_pad_odd[i] = -9.;
        phi_pad_even[i] = -9.;
        z_pad_odd[i] = -0.;
        z_pad_even[i] = -0.;
        eta_pad_odd[i] = -9.;
        eta_pad_even[i] = -9.;
        dphi_pad_odd[i] = -9.;
        dphi_pad_even[i] = -9.;
        deta_pad_odd[i] = -9.;
        deta_pad_even[i] = -9.;
      }
    };

    void book(TTree* t) {

      t->Branch("has_gem_pad_odd", has_gem_pad_odd, "has_gem_pad_odd[3]/I");
      t->Branch("has_gem_pad2_odd", has_gem_pad2_odd, "has_gem_pad2_odd[3]/I");
      t->Branch("has_gem_copad_odd", has_gem_copad_odd, "has_gem_copad_odd[3]/I");

      t->Branch("has_gem_pad_even", has_gem_pad_even, "has_gem_pad_even[3]/I");
      t->Branch("has_gem_pad2_even", has_gem_pad2_even, "has_gem_pad2_even[3]/I");
      t->Branch("has_gem_copad_even", has_gem_copad_even, "has_gem_copad_even[3]/I");

      t->Branch("pad_odd", pad_odd, "pad_odd[3]/I");
      t->Branch("pad_even", pad_even, "pad_even[3]/I");

      t->Branch("copad_odd", copad_odd, "copad_odd[3]/I");
      t->Branch("copad_even", copad_even, "copad_odd[3]/I");

      t->Branch("bx_pad_odd", bx_pad_odd, "bx_pad_odd[3]/I");
      t->Branch("bx_pad_even", bx_pad_even, "bx_pad_even[3]/I");

      t->Branch("phi_pad_odd", phi_pad_odd, "phi_pad_odd[3]/F");
      t->Branch("phi_pad_even", phi_pad_even, "phi_pad_even[3]/F");

      t->Branch("z_pad_odd", z_pad_odd, "z_pad_odd[3]/F");
      t->Branch("z_pad_even", z_pad_even, "z_pad_even[3]/F");

      t->Branch("eta_pad_odd", eta_pad_odd, "eta_pad_odd[3]/F");
      t->Branch("eta_pad_even", eta_pad_even, "eta_pad_even[3]/F");

      t->Branch("dphi_pad_odd", dphi_pad_odd, "dphi_pad_odd[3]/F");
      t->Branch("dphi_pad_even", dphi_pad_even, "dphi_pad_even[3]/F");

      t->Branch("deta_pad_odd", deta_pad_odd, "deta_pad_odd[3]/F");
      t->Branch("deta_pad_even", deta_pad_even, "deta_pad_even[3]/F");
    }
  };
}  // namespace

#endif
