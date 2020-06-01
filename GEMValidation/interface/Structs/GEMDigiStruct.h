#ifndef GEMCode_GEMValidation_GEMDigiStruct
#define GEMCode_GEMValidation_GEMDigiStruct

#include "TTree.h"
#include <string>

namespace gem {

  struct GEMDigiStruct {

    static const int nStations = 3;

    bool has_gem_dg_even[nStations];
    bool has_gem_dg2_even[nStations];

    bool has_gem_dg_odd[nStations];
    bool has_gem_dg2_odd[nStations];

    Int_t strip_gemdg_odd[nStations];
    Int_t strip_gemdg_even[nStations];

    int bx_dg_odd[nStations];
    int bx_dg_even[nStations];

    void init() {
      for (unsigned i = 0 ; i < nStations; i++) {
        has_gem_dg_even[i] = 0;
        has_gem_dg2_even[i] = 0;

        has_gem_dg_odd[i] = 0;
        has_gem_dg2_odd[i] = 0;

        strip_gemdg_odd[i] = -9;
        strip_gemdg_even[i] = -9;

        bx_dg_odd[i] = -9;
        bx_dg_even[i] = -9;
      }
    };

    void book(TTree* t) {
      t->Branch("has_gem_dg_odd", has_gem_dg_odd, "has_gem_dg_odd[3]/O");
      t->Branch("has_gem_dg2_odd", has_gem_dg2_odd, "has_gem_dg2_odd[3]/O");

      t->Branch("has_gem_dg_even", has_gem_dg_even, "has_gem_dg_even[3]/O");
      t->Branch("has_gem_dg2_even", has_gem_dg2_even, "has_gem_dg2_even[3]/O");

      t->Branch("strip_gemdg_odd", strip_gemdg_odd, "strip_gemdg_odd[3]/I");
      t->Branch("strip_gemdg_even", strip_gemdg_even, "strip_gemdg_even[3]/I");

      t->Branch("bx_dg_odd", bx_dg_odd, "bx_dg_odd[3]/I");
      t->Branch("bx_dg_even", bx_dg_even, "bx_dg_even[3]/I");
    }
  };
}  // namespace

#endif
