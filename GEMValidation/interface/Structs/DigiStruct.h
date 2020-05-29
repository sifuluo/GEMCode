#ifndef GEMCode_GEMValidation_DigiStruct
#define GEMCode_GEMValidation_DigiStruct

#include "TTree.h"
#include <string>

namespace gem {

  struct DigiStruct {

    // CSC
    bool has_csc_strips_even;
    bool has_csc_strips_odd;

    bool has_csc_wires_even;
    bool has_csc_wires_odd;

    Int_t nlayers_wg_dg_odd;
    Int_t nlayers_st_dg_odd;

    Int_t nlayers_wg_dg_even;
    Int_t nlayers_st_dg_even;

    int chamber_dg_odd, chamber_dg_even;
    Int_t wiregroup_odd;
    Int_t wiregroup_even;

    Int_t halfstrip_odd;
    Int_t halfstrip_even;

    // GEM
    Int_t pad_odd;
    Int_t pad_even;
    Int_t Copad_odd;
    Int_t Copad_even;
    Int_t hsfromgem_odd;
    Int_t hsfromgem_even;

    bool has_gem_dg_even;
    bool has_gem_dg2_even;
    bool has_gem_pad_even;
    bool has_gem_pad2_even;
    bool has_gem_copad_even;

    bool has_gem_dg_odd;
    bool has_gem_dg2_odd;
    bool has_gem_pad_odd;
    bool has_gem_pad2_odd;
    bool has_gem_copad_odd;

    Int_t strip_gemdg_odd;
    Int_t strip_gemdg_even;

    bool bx_pad_odd;
    bool bx_pad_even;
    Float_t phi_pad_odd;
    Float_t phi_pad_even;
    Float_t z_pad_odd;
    Float_t z_pad_even;
    Float_t eta_pad_odd;
    Float_t eta_pad_even;

    Float_t dphi_pad_odd;
    Float_t dphi_pad_even;
    Float_t deta_pad_odd;
    Float_t deta_pad_even;
    Float_t dphi_pad_fit_odd;
    Float_t dphi_pad_fit_even;

    void init() {
      has_csc_strips_even = 0;
      has_csc_strips_odd = 0;

      has_csc_wires_even = 0;
      has_csc_wires_odd = 0;

      nlayers_wg_dg_odd = -1;
      nlayers_st_dg_odd = -1;
      nlayers_wg_dg_even = -1;
      nlayers_st_dg_even = -1;

      chamber_dg_odd = -1;
      chamber_dg_even = -1;
      wiregroup_odd = -1;
      wiregroup_even = -1;
      halfstrip_odd = -1;
      halfstrip_even = -1;

      pad_odd = -1;
      pad_even = -1;
      Copad_odd = -1;
      Copad_even = -1;

      hsfromgem_odd = -1;
      hsfromgem_even = -1;

      has_gem_dg_even = 0;
      has_gem_dg2_even = 0;
      has_gem_pad_even = 0;
      has_gem_pad2_even = 0;
      has_gem_copad_even = 0;

      has_gem_dg_odd = 0;
      has_gem_dg2_odd = 0;
      has_gem_pad_odd = 0;
      has_gem_pad2_odd = 0;
      has_gem_copad_odd = 0;

      strip_gemdg_odd = -9;
      strip_gemdg_even = -9;
      bx_pad_odd = -9;
      bx_pad_even = -9;
      phi_pad_odd = -9.;
      phi_pad_even = -9.;
      z_pad_odd = -0.;
      z_pad_even = -0.;
      eta_pad_odd = -9.;
      eta_pad_even = -9.;
      dphi_pad_odd = -9.;
      dphi_pad_even = -9.;
      dphi_pad_fit_odd = -9.;
      dphi_pad_fit_even = -9.;
      deta_pad_odd = -9.;
      deta_pad_even = -9.;

    };

    TTree* book(TTree* t) {

      t->Branch("chamber_dg_odd", &chamber_dg_odd);
      t->Branch("chamber_dg_even", &chamber_dg_even);

      t->Branch("nlayers_wg_dg_odd", &nlayers_wg_dg_odd);
      t->Branch("nlayers_wg_dg_even", &nlayers_wg_dg_even);
      t->Branch("nlayers_st_dg_odd", &nlayers_st_dg_odd);
      t->Branch("nlayers_st_dg_even", &nlayers_st_dg_even);

      t->Branch("wiregroup_odd", &wiregroup_odd);
      t->Branch("wiregroup_even", &wiregroup_even);
      t->Branch("halfstrip_odd", &halfstrip_odd);
      t->Branch("halfstrip_even", &halfstrip_even);

      t->Branch("pad_odd", &pad_odd);
      t->Branch("pad_even", &pad_even);
      t->Branch("Copad_odd", &Copad_odd);
      t->Branch("copad_even", &Copad_even);

      t->Branch("hsfromgem_odd", &hsfromgem_odd);
      t->Branch("hsfromgem_even", &hsfromgem_even);

      t->Branch("has_csc_strips_odd", &has_csc_strips_odd);
      t->Branch("has_csc_wires_odd", &has_csc_wires_odd);

      t->Branch("has_gem_dg_odd", &has_gem_dg_odd);
      t->Branch("has_gem_dg2_odd", &has_gem_dg2_odd);
      t->Branch("has_gem_pad_odd", &has_gem_pad_odd);
      t->Branch("has_gem_pad2_odd", &has_gem_pad2_odd);
      t->Branch("has_gem_copad_odd", &has_gem_copad_odd);

      t->Branch("has_csc_strips_even", &has_csc_strips_even);
      t->Branch("has_csc_wires_even", &has_csc_wires_even);

      t->Branch("has_gem_dg_even", &has_gem_dg_even);
      t->Branch("has_gem_dg2_even", &has_gem_dg2_even);
      t->Branch("has_gem_pad_even", &has_gem_pad_even);
      t->Branch("has_gem_pad2_even", &has_gem_pad2_even);
      t->Branch("has_gem_copad_even", &has_gem_copad_even);

      t->Branch("strip_gemdg_odd", &strip_gemdg_odd);
      t->Branch("strip_gemdg_even", &strip_gemdg_even);

      t->Branch("bx_pad_odd", &bx_pad_odd);
      t->Branch("bx_pad_even", &bx_pad_even);
      t->Branch("phi_pad_odd", &phi_pad_odd);
      t->Branch("phi_pad_even", &phi_pad_even);
      t->Branch("z_pad_odd", &z_pad_odd);
      t->Branch("z_pad_even", &z_pad_even);
      t->Branch("eta_pad_odd", &eta_pad_odd);
      t->Branch("eta_pad_even", &eta_pad_even);

      t->Branch("dphi_pad_odd", &dphi_pad_odd);
      t->Branch("dphi_pad_even", &dphi_pad_even);
      t->Branch("dphi_pad_fit_odd", &dphi_pad_fit_odd);
      t->Branch("dphi_pad_fit_even", &dphi_pad_fit_even);
      t->Branch("deta_pad_odd", &deta_pad_odd);
      t->Branch("deta_pad_even", &deta_pad_even);

      return t;
    }
  };
}  // namespace

#endif
