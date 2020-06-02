#ifndef GEMCode_GEMValidation_CSCStubStruct
#define GEMCode_GEMValidation_CSCStubStruct

#include "TROOT.h"
#include "TTree.h"

namespace gem {

  struct CSCStubStruct {

    static const int nStations = 11;

    // bools
    bool has_clct_odd[nStations];
    bool has_alct_odd[nStations];
    bool has_lct_odd[nStations];

    bool has_clct_even[nStations];
    bool has_alct_even[nStations];
    bool has_lct_even[nStations];

    // ints
    int bx_lct_odd[nStations];
    int bx_alct_odd[nStations];
    int bx_clct_odd[nStations];
    int bx_lct_even[nStations];
    int bx_alct_even[nStations];
    int bx_clct_even[nStations];

    int hs_clct_odd[nStations];
    int hs_clct_even[nStations];

    int qs_clct_odd[nStations];
    int qs_clct_even[nStations];

    int es_clct_odd[nStations];
    int es_clct_even[nStations];

    int hs_lct_odd[nStations];
    int hs_lct_even[nStations];

    int qs_lct_odd[nStations];
    int qs_lct_even[nStations];

    int es_lct_odd[nStations];
    int es_lct_even[nStations];

    int wg_lct_odd[nStations];
    int wg_lct_even[nStations];

    int chamber_lct_odd[nStations];
    int chamber_lct_even[nStations];

    int bend_lct_odd[nStations];
    int bend_lct_even[nStations];

    int passdphi_odd[nStations];
    int passdphi_even[nStations];

    int quality_clct_odd[nStations];
    int quality_clct_even[nStations];
    int quality_alct_odd[nStations];
    int quality_alct_even[nStations];
    int quality_lct_odd[nStations];
    int quality_lct_even[nStations];

    int lct_type[nStations];

    // floats
    float phi_lct_odd[nStations];
    float phi_lct_even[nStations];
    float eta_lct_odd[nStations];
    float eta_lct_even[nStations];
    float dphi_lct_odd[nStations];
    float dphi_lct_even[nStations];
    float chi2_lct_odd[nStations];
    float chi2_lct_even[nStations];

    float timeErr_lct_odd[nStations];
    float timeErr_lct_even[nStations];

    float perp_lct_odd[nStations];
    float perp_lct_even[nStations];

    // bending resolution
    float dbend_lct_odd[nStations];
    float dbend_lct_even[nStations];

    void init() {
      for (unsigned i = 0 ; i < nStations; i++) {

        has_alct_even[i] = 0;
        has_clct_even[i] = 0;
        has_lct_even[i] = 0;
        has_alct_odd[i] = 0;
        has_clct_odd[i] = 0;
        has_lct_odd[i] = 0;

        chamber_lct_odd[i] = -1;
        chamber_lct_even[i] = -1;

        bend_lct_odd[i] = -9;
        bend_lct_even[i] = -9;
        dphi_lct_odd[i] = -9;
        dphi_lct_even[i] = -9;

        bx_lct_odd[i] = -9;
        bx_lct_even[i] = -9;

        hs_lct_odd[i] = 0;
        hs_lct_even[i] = 0;

        qs_lct_odd[i] = 0;
        qs_lct_even[i] = 0;

        es_lct_odd[i] = 0;
        es_lct_even[i] = 0;

        hs_clct_odd[i] = 0;
        hs_clct_even[i] = 0;

        qs_clct_odd[i] = 0;
        qs_clct_even[i] = 0;

        es_clct_odd[i] = 0;
        es_clct_even[i] = 0;

        wg_lct_odd[i] = 0;
        wg_lct_even[i] = 0;

        eta_lct_odd[i] = -9.;
        eta_lct_even[i] = -9.;

        phi_lct_odd[i] = -9.;
        phi_lct_even[i] = -9.;

        chi2_lct_odd[i] = -99999;
        chi2_lct_even[i] = -99999;

        timeErr_lct_odd[i] = -9999;
        timeErr_lct_even[i] = -9999;

        passdphi_odd[i] = 0;
        passdphi_even[i] = 0;

        perp_lct_odd[i] = -1;
        perp_lct_even[i] = -1;

        quality_clct_odd[i] = -1;
        quality_clct_even[i] = -1;
        quality_alct_odd[i] = -1;
        quality_alct_even[i] = -1;
        quality_lct_odd[i] = -1;
        quality_lct_even[i] = -1;

        bx_clct_odd[i] = -9;
        bx_clct_even[i] = -9;
        bx_alct_odd[i] = -9;
        bx_alct_even[i] = -9;

        lct_type[i] = -1;

        dbend_lct_odd[i] = -9;
        dbend_lct_even[i] = -9;
      }
    };

    void book(TTree* t) {

      /* t->Branch("ALCT", &alct); */

      t->Branch("has_clct_odd", has_clct_odd, "has_clct_odd[11]/O");
      t->Branch("has_alct_odd", has_alct_odd, "has_alct_odd[11]/O");
      t->Branch("has_lct_odd", has_lct_odd, "has_lct_odd[11]/O");

      t->Branch("has_clct_even", has_clct_even, "has_clct_even[11]/O");
      t->Branch("has_alct_even", has_alct_even, "has_alct_even[11]/O");
      t->Branch("has_lct_even", has_lct_even, "has_lct_even[11]/O");


      t->Branch("bx_clct_odd", bx_clct_odd, "bx_clct_odd[11]/I");
      t->Branch("bx_clct_even", bx_clct_even, "bx_clct_even[11]/I");

      t->Branch("quality_clct_odd", quality_clct_odd, "quality_clct_odd[11]/I");
      t->Branch("quality_clct_even", quality_clct_even, "quality_clct_even[11]/I");
      t->Branch("quality_alct_odd", quality_alct_odd, "quality_alct_odd[11]/I");
      t->Branch("quality_alct_even", quality_alct_even, "quality_alct_even[11]/I");
      t->Branch("quality_lct_odd", quality_lct_odd, "quality_lct_odd[11]/I");
      t->Branch("quality_lct_even", quality_lct_even, "quality_lct_even[11]/I");

      t->Branch("bx_alct_odd", bx_alct_odd, "bx_alct_odd[11]/I");
      t->Branch("bx_alct_even", bx_alct_even, "bx_alct_even[11]/I");

      t->Branch("chamber_lct_odd", chamber_lct_odd, "chamber_lct_odd[11]/I");
      t->Branch("chamber_lct_even", chamber_lct_even, "chamber_lct_even[11]/I");

      t->Branch("bend_lct_odd", bend_lct_odd, "bend_lct_odd[11]/I");
      t->Branch("bend_lct_even", bend_lct_even, "bend_lct_even[11]/I");

      t->Branch("bx_lct_odd", bx_lct_odd, "bx_lct_odd[11]/I");
      t->Branch("bx_lct_even", bx_lct_even, "bx_lct_even[11]/I");

      t->Branch("hs_lct_odd", hs_lct_odd, "hs_lct_odd[11]/I");
      t->Branch("hs_lct_even", hs_lct_even, "hs_lct_even[11]/I");

      t->Branch("qs_lct_odd", qs_lct_odd, "qs_lct_odd[11]/I");
      t->Branch("qs_lct_even", qs_lct_even, "qs_lct_even[11]/I");

      t->Branch("es_lct_odd", es_lct_odd, "es_lct_odd[11]/I");
      t->Branch("es_lct_even", es_lct_even, "es_lct_even[11]/I");

      t->Branch("hs_clct_odd", hs_clct_odd, "hs_clct_odd[11]/I");
      t->Branch("hs_clct_even", hs_clct_even, "hs_clct_even[11]/I");

      t->Branch("qs_clct_odd", qs_clct_odd, "qs_clct_odd[11]/I");
      t->Branch("qs_clct_even", qs_clct_even, "qs_clct_even[11]/I");

      t->Branch("es_clct_odd", es_clct_odd, "es_clct_odd[11]/I");
      t->Branch("es_clct_even", es_clct_even, "es_clct_even[11]/I");

      t->Branch("wg_lct_odd", wg_lct_odd, "wg_lct_odd[11]/I");
      t->Branch("wg_lct_even", wg_lct_even, "wg_lct_even[11]/I");

      t->Branch("perp_lct_odd", perp_lct_odd, "perp_lct_odd[11]/F");
      t->Branch("perp_lct_even", perp_lct_even, "perp_lct_even[11]/F");

      t->Branch("eta_lct_odd", eta_lct_odd, "eta_lct_odd[11]/F");
      t->Branch("eta_lct_even", eta_lct_even, "eta_lct_even[11]/F");

      t->Branch("phi_lct_odd", phi_lct_odd, "phi_lct_odd[11]/F");
      t->Branch("phi_lct_even", phi_lct_even, "phi_lct_even[11]/F");

      t->Branch("dphi_lct_odd", dphi_lct_odd, "dphi_lct_odd[11]/F");
      t->Branch("dphi_lct_even", dphi_lct_even, "dphi_lct_even[11]/F");

      t->Branch("chi2_lct_odd", chi2_lct_odd, "chi2_lct_odd[11]/F");
      t->Branch("chi2_lct_even", chi2_lct_even, "chi2_lct_even[11]/F");

      t->Branch("timeErr_lct_odd", timeErr_lct_odd, "timeErr_lct_odd[11]/F");
      t->Branch("timeErr_lct_even", timeErr_lct_even, "timeErr_lct_even[11]/F");

      t->Branch("passdphi_odd", passdphi_odd, "passdphi_odd[11]/F");
      t->Branch("passdphi_even", passdphi_even, "passdphi_even[11]/F");

      t->Branch("lct_type", lct_type, "lct_type[11]/I");

      t->Branch("dbend_lct_odd", dbend_lct_odd, "dbend_lct_odd[11]/I");
      t->Branch("dbend_lct_even", dbend_lct_even, "dbend_lct_even[11]/I");
    }
  };
}  // namespace

#endif
