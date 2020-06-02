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
    int pad1_odd[nStations];
    int pad1_even[nStations];
    int bx_pad1_odd[nStations];
    int bx_pad1_even[nStations];

    int pad2_odd[nStations];
    int pad2_even[nStations];
    int bx_pad2_odd[nStations];
    int bx_pad2_even[nStations];

    int copad_odd[nStations];
    int copad_even[nStations];
    int bx_copad_odd[nStations];
    int bx_copad_even[nStations];

    // floats - this is based on mean GEM position
    float z_pad1_odd[nStations];
    float z_pad1_even[nStations];
    float eta_pad1_odd[nStations];
    float eta_pad1_even[nStations];
    float phi_pad1_odd[nStations];
    float phi_pad1_even[nStations];

    float z_pad2_odd[nStations];
    float z_pad2_even[nStations];
    float eta_pad2_odd[nStations];
    float eta_pad2_even[nStations];
    float phi_pad2_odd[nStations];
    float phi_pad2_even[nStations];

    float z_copad_odd[nStations];
    float z_copad_even[nStations];
    float eta_copad_odd[nStations];
    float eta_copad_even[nStations];
    float phi_copad_odd[nStations];
    float phi_copad_even[nStations];

    // floats - between GEM and CSC
    float dphi_pad1_odd[nStations];
    float dphi_pad1_even[nStations];
    float deta_pad1_odd[nStations];
    float deta_pad1_even[nStations];

    float dphi_pad2_odd[nStations];
    float dphi_pad2_even[nStations];
    float deta_pad2_odd[nStations];
    float deta_pad2_even[nStations];

    float dphi_copad_odd[nStations];
    float dphi_copad_even[nStations];
    float deta_copad_odd[nStations];
    float deta_copad_even[nStations];

    void init() {
      for (unsigned i = 0 ; i < nStations; i++) {

        has_gem_pad_even[i] = 0;
        has_gem_pad2_even[i] = 0;
        has_gem_copad_even[i] = 0;

        has_gem_pad_odd[i] = 0;
        has_gem_pad2_odd[i] = 0;
        has_gem_copad_odd[i] = 0;

        pad1_odd[i] = -1;
        pad1_even[i] = -1;

        bx_pad1_odd[i] = -1;
        bx_pad1_even[i] = -1;

        pad2_odd[i] = -1;
        pad2_even[i] = -1;

        bx_pad2_odd[i] = -1;
        bx_pad2_even[i] = -1;

        copad_odd[i] = -1;
        copad_even[i] = -1;

        bx_copad_odd[i] = -1;
        bx_copad_even[i] = -1;

        z_pad1_odd[i] = -0.;
        z_pad1_even[i] = -0.;
        eta_pad1_odd[i] = -9.;
        eta_pad1_even[i] = -9.;
        phi_pad1_odd[i] = -9.;
        phi_pad1_even[i] = -9.;

        z_pad2_odd[i] = -0.;
        z_pad2_even[i] = -0.;
        eta_pad2_odd[i] = -9.;
        eta_pad2_even[i] = -9.;
        phi_pad2_odd[i] = -9.;
        phi_pad2_even[i] = -9.;

        z_copad_odd[i] = -0.;
        z_copad_even[i] = -0.;
        eta_copad_odd[i] = -9.;
        eta_copad_even[i] = -9.;
        phi_copad_odd[i] = -9.;
        phi_copad_even[i] = -9.;

        deta_pad1_odd[i] = -9.;
        deta_pad1_even[i] = -9.;
        dphi_pad1_odd[i] = -9.;
        dphi_pad1_even[i] = -9.;

        deta_pad2_odd[i] = -9.;
        deta_pad2_even[i] = -9.;
        dphi_pad2_odd[i] = -9.;
        dphi_pad2_even[i] = -9.;

        deta_copad_odd[i] = -9.;
        deta_copad_even[i] = -9.;
        dphi_copad_odd[i] = -9.;
        dphi_copad_even[i] = -9.;
      }
    };

    void book(TTree* t) {

      t->Branch("has_gem_pad_odd", has_gem_pad_odd, "has_gem_pad_odd[3]/I");
      t->Branch("has_gem_pad2_odd", has_gem_pad2_odd, "has_gem_pad2_odd[3]/I");
      t->Branch("has_gem_copad_odd", has_gem_copad_odd, "has_gem_copad_odd[3]/I");

      t->Branch("has_gem_pad_even", has_gem_pad_even, "has_gem_pad_even[3]/I");
      t->Branch("has_gem_pad2_even", has_gem_pad2_even, "has_gem_pad2_even[3]/I");
      t->Branch("has_gem_copad_even", has_gem_copad_even, "has_gem_copad_even[3]/I");

      t->Branch("pad1_odd", pad1_odd, "pad1_odd[3]/I");
      t->Branch("pad1_even", pad1_even, "pad1_even[3]/I");
      t->Branch("pad2_odd", pad2_odd, "pad2_odd[3]/I");
      t->Branch("pad2_even", pad2_even, "pad2_even[3]/I");

      t->Branch("bx_pad1_odd", bx_pad1_odd, "bx_pad1_odd[3]/I");
      t->Branch("bx_pad1_even", bx_pad1_even, "bx_pad1_even[3]/I");
      t->Branch("bx_pad2_odd", bx_pad2_odd, "bx_pad2_odd[3]/I");
      t->Branch("bx_pad2_even", bx_pad2_even, "bx_pad2_even[3]/I");

      t->Branch("copad_odd", copad_odd, "copad_odd[3]/I");
      t->Branch("copad_even", copad_even, "copad_odd[3]/I");
      t->Branch("bx_copad_odd", bx_copad_odd, "bx_copad_odd[3]/I");
      t->Branch("bx_copad_even", bx_copad_even, "bx_copad_odd[3]/I");



      t->Branch("z_pad1_odd", z_pad1_odd, "z_pad1_odd[3]/F");
      t->Branch("z_pad1_even", z_pad1_even, "z_pad1_even[3]/F");
      t->Branch("eta_pad1_odd", eta_pad1_odd, "eta_pad1_odd[3]/F");
      t->Branch("eta_pad1_even", eta_pad1_even, "eta_pad1_even[3]/F");
      t->Branch("phi_pad1_odd", phi_pad1_odd, "phi_pad1_odd[3]/F");
      t->Branch("phi_pad1_even", phi_pad1_even, "phi_pad1_even[3]/F");

      t->Branch("dphi_pad1_odd", dphi_pad1_odd, "dphi_pad1_odd[3]/F");
      t->Branch("dphi_pad1_even", dphi_pad1_even, "dphi_pad1_even[3]/F");
      t->Branch("deta_pad1_odd", deta_pad1_odd, "deta_pad1_odd[3]/F");
      t->Branch("deta_pad1_even", deta_pad1_even, "deta_pad1_even[3]/F");


      t->Branch("z_pad2_odd", z_pad2_odd, "z_pad2_odd[3]/F");
      t->Branch("z_pad2_even", z_pad2_even, "z_pad2_even[3]/F");
      t->Branch("eta_pad2_odd", eta_pad2_odd, "eta_pad2_odd[3]/F");
      t->Branch("eta_pad2_even", eta_pad2_even, "eta_pad2_even[3]/F");
      t->Branch("phi_pad2_odd", phi_pad2_odd, "phi_pad2_odd[3]/F");
      t->Branch("phi_pad2_even", phi_pad2_even, "phi_pad2_even[3]/F");

      t->Branch("dphi_pad2_odd", dphi_pad2_odd, "dphi_pad2_odd[3]/F");
      t->Branch("dphi_pad2_even", dphi_pad2_even, "dphi_pad2_even[3]/F");
      t->Branch("deta_pad2_odd", deta_pad2_odd, "deta_pad2_odd[3]/F");
      t->Branch("deta_pad2_even", deta_pad2_even, "deta_pad2_even[3]/F");


      t->Branch("z_copad_odd", z_copad_odd, "z_copad_odd[3]/F");
      t->Branch("z_copad_even", z_copad_even, "z_copad_even[3]/F");
      t->Branch("eta_copad_odd", eta_copad_odd, "eta_copad_odd[3]/F");
      t->Branch("eta_copad_even", eta_copad_even, "eta_copad_even[3]/F");
      t->Branch("phi_copad_odd", phi_copad_odd, "phi_copad_odd[3]/F");
      t->Branch("phi_copad_even", phi_copad_even, "phi_copad_even[3]/F");

      t->Branch("dphi_copad_odd", dphi_copad_odd, "dphi_copad_odd[3]/F");
      t->Branch("dphi_copad_even", dphi_copad_even, "dphi_copad_even[3]/F");
      t->Branch("deta_copad_odd", deta_copad_odd, "deta_copad_odd[3]/F");
      t->Branch("deta_copad_even", deta_copad_even, "deta_copad_even[3]/F");
    }
  };
}  // namespace

#endif
