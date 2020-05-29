#ifndef GEMCode_GEMValidation_SimHitStruct
#define GEMCode_GEMValidation_SimHitStruct

#include "TTree.h"
#include <string>

namespace gem {

  struct SimHitStruct {

    bool chamber_ME1_csc_sh_odd;
    bool chamber_ME1_csc_sh_even;

    bool chamber_ME2_csc_sh_even;
    bool chamber_ME2_csc_sh_odd;

    Int_t nlayers_csc_sh_even;
    Int_t nlayers_csc_sh_odd;

    bool has_csc_sh_odd;
    bool has_csc_sh_even;

    Float_t dphi_sh_even;
    Float_t dphi_sh_odd;

    Float_t dphipositionpt_cscsh_even, dphipositionpt_cscsh_odd, dphipositionpt_gemsh_even, dphipositionpt_gemsh_odd;

    Float_t bending_sh;
    Float_t phi_cscsh_even, phi_cscsh_odd;
    float eta_cscsh_even, eta_cscsh_odd;

    Float_t phi_layer1_sh_even, eta_layer1_sh_even;
    float phi_layer1_sh_odd, eta_layer1_sh_odd;
    float perp_layer1_sh_odd, perp_layer1_sh_even;
    Float_t z_layer1_sh_odd, z_layer1_sh_even;
    Float_t phi_layer6_sh_even, eta_layer6_sh_even;
    float phi_layer6_sh_odd, eta_layer6_sh_odd;
    float perp_layer6_sh_odd, perp_layer6_sh_even;
    Float_t z_layer6_sh_odd, z_layer6_sh_even;
    Float_t perp_gemsh_even, perp_gemsh_odd;
    float perp_cscsh_even, perp_cscsh_odd;
    float centralperp_gemsh_even, centralperp_gemsh_odd;

    bool has_gem_sh_even;
    bool has_gem_sh_odd;

    bool has_gem_sh2_even;
    bool has_gem_sh2_odd;

    bool has_gemcopad_sh_even;
    bool has_gemcopad_sh_odd;

    Float_t strip_gemsh_odd;  // average hits' strip
    Float_t strip_gemsh_even;

    Float_t eta_gemsh_odd;
    Float_t eta_gemsh_even;

    Float_t phi_gemsh_odd;
    Float_t phi_gemsh_even;

    Char_t has_rpc_sh;      // bit1: in odd, bit2: even

    int chamber_sh_odd;
    int chamber_sh_even;

    void init() {
      bending_sh = -10;

      chamber_ME1_csc_sh_even = 0;
      chamber_ME1_csc_sh_odd = 0;

      chamber_ME2_csc_sh_even = 0;
      chamber_ME2_csc_sh_odd = 0;

      chamber_sh_odd = -1;
      chamber_sh_even = -1;

      nlayers_csc_sh_odd = -1;
      nlayers_csc_sh_even = -1;

      perp_cscsh_odd = -0.0;
      perp_cscsh_even = -0.0;

      perp_gemsh_odd = -0.0;
      perp_gemsh_even = -0.0;

      centralperp_gemsh_odd = -0.0;
      centralperp_gemsh_even = -0.0;

      phi_cscsh_even = -9.0;
      phi_cscsh_odd = -9.0;

      eta_cscsh_even = -9.0;
      eta_cscsh_odd = -9.0;

      has_csc_sh_even = false;
      has_csc_sh_odd = false;

      has_gem_sh_even = false;
      has_gem_sh_odd = false;

      has_gem_sh2_even = false;
      has_gem_sh2_odd = false;

      has_gemcopad_sh_even = false;
      has_gemcopad_sh_odd = false;

      strip_gemsh_odd = -9.;
      strip_gemsh_even = -9.;

      eta_gemsh_odd = -9.;
      eta_gemsh_even = -9.;

      phi_gemsh_odd = -9.;
      phi_gemsh_even = -9.;

      dphi_sh_odd = -9;
      dphi_sh_even = -9;
    };

    TTree* book(TTree* t) {

      t->Branch("bending_sh", &bending_sh);

      t->Branch("has_csc_sh_even", &has_csc_sh_even);
      t->Branch("has_csc_sh_odd", &has_csc_sh_odd);

      t->Branch("chamber_ME1_csc_sh_odd", &chamber_ME1_csc_sh_odd);
      t->Branch("chamber_ME1_csc_sh_even", &chamber_ME1_csc_sh_even);

      t->Branch("chamber_ME2_csc_sh_odd", &chamber_ME2_csc_sh_odd);
      t->Branch("chamber_ME2_csc_sh_even", &chamber_ME2_csc_sh_even);

      t->Branch("chamber_sh_odd", &chamber_sh_odd);
      t->Branch("chamber_sh_even", &chamber_sh_even);

      t->Branch("nlayers_csc_sh_odd", &nlayers_csc_sh_odd);
      t->Branch("nlayers_csc_sh_even", &nlayers_csc_sh_even);

      t->Branch("perp_cscsh_odd", &perp_cscsh_odd);
      t->Branch("perp_cscsh_even", &perp_cscsh_even);

      t->Branch("perp_gemsh_odd", &perp_gemsh_odd);
      t->Branch("perp_gemsh_even", &perp_gemsh_even);

      t->Branch("centralperp_gemsh_odd", &centralperp_gemsh_odd);
      t->Branch("centralperp_gemsh_even", &centralperp_gemsh_even);

      t->Branch("phi_cscsh_even", &phi_cscsh_even);
      t->Branch("phi_cscsh_odd", &phi_cscsh_odd);

      t->Branch("eta_cscsh_even", &eta_cscsh_even);
      t->Branch("eta_cscsh_odd", &eta_cscsh_odd);
      /* t->Branch("pt_sh_even", &pt_sh_even); */
      /* t->Branch("pteta_sh_even", &pteta_sh_even); */
      /* t->Branch("ptphi_sh_even", &ptphi_sh_even); */
      /* t->Branch("pt_sh_odd", &pt_sh_odd); */
      /* t->Branch("pteta_sh_odd", &pteta_sh_odd); */
      /* t->Branch("ptphi_sh_odd", &ptphi_sh_odd); */

      t->Branch("has_gem_sh_odd", &has_gem_sh_odd);
      t->Branch("has_gem_sh_even", &has_gem_sh_even);

      t->Branch("has_gem_sh2_odd", &has_gem_sh2_odd);
      t->Branch("has_gem_sh2_even", &has_gem_sh2_even);

      t->Branch("has_gemcopad_sh_even", &has_gemcopad_sh_even);
      t->Branch("has_gemcopad_sh_odd", &has_gemcopad_sh_odd);

      t->Branch("strip_gemsh_odd", &strip_gemsh_odd);
      t->Branch("strip_gemsh_even", &strip_gemsh_even);

      t->Branch("eta_gemsh_odd", &eta_gemsh_odd);
      t->Branch("eta_gemsh_even", &eta_gemsh_even);

      t->Branch("phi_gemsh_odd", &phi_gemsh_odd);
      t->Branch("phi_gemsh_even", &phi_gemsh_even);

      t->Branch("dphi_sh_odd", &dphi_sh_odd);
      t->Branch("dphi_sh_even", &dphi_sh_even);

      return t;
    }
  };
}  // namespace

#endif
