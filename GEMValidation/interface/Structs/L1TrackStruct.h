#ifndef GEMCode_GEMValidation_L1TrackStruct
#define GEMCode_GEMValidation_L1TrackStruct

#include "TTree.h"

namespace gem {

  struct L1TrackStruct {
    float L1Track_pt;
    float L1Track_eta;
    float L1Track_phi;
    int L1Track_charge;
    int L1Track_endcap;

    void init() {
      L1Track_pt = 0.;
      L1Track_phi = 0.;
      L1Track_eta = -9.;
      L1Track_charge = -9;
      L1Track_endcap = -9;
    };

    void book(TTree* t) {
      t->Branch("L1Track_pt", &L1Track_pt);
      t->Branch("L1Track_eta", &L1Track_eta);
      t->Branch("L1Track_phi", &L1Track_phi);
      t->Branch("L1Track_charge", &L1Track_charge);
      t->Branch("L1Track_endcap", &L1Track_endcap);
    }
  };
}  // namespace

#endif
