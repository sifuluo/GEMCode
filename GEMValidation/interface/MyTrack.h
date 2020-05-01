#ifndef GEMCode_GEMValidation_MyTrack
#define GEMCode_GEMValidation_MyTrack

#include "TTree.h"
#include <vector>
#include <string>

namespace{

struct MyTrack
{
  void init(); // initialize to default values
  TTree* book(TTree *t, const std::string & name = "track");

  float pt, eta, phi, pz, dxy;
  int charge;
  int endcap;
  int pdgid;

  Char_t chamber_ME1_csc_sh;//bit1:odd, bit2:even
  Char_t chamber_ME2_csc_sh;
  Int_t nlayers_csc_sh_odd;
  Int_t nlayers_csc_sh_even;
  Int_t chamber_lct_odd, chamber_dg_odd, chamber_sh_odd; //
  Int_t chamber_lct_even, chamber_dg_even, chamber_sh_even; //
  Float_t bending_sh;
  Float_t phi_cscsh_even, phi_cscsh_odd, eta_cscsh_even, eta_cscsh_odd;
  Float_t phi_layer1_sh_even, eta_layer1_sh_even, phi_layer1_sh_odd,eta_layer1_sh_odd, perp_layer1_sh_odd, perp_layer1_sh_even;
  Float_t z_layer1_sh_odd, z_layer1_sh_even;
  Float_t phi_layer6_sh_even, eta_layer6_sh_even, phi_layer6_sh_odd,eta_layer6_sh_odd, perp_layer6_sh_odd, perp_layer6_sh_even;
  Float_t z_layer6_sh_odd, z_layer6_sh_even;
  Float_t perp_gemsh_even, perp_gemsh_odd, perp_cscsh_even, perp_cscsh_odd,centralperp_gemsh_even, centralperp_gemsh_odd;
  Float_t dphi_sh_even,dphi_sh_odd;
  Float_t dphipositionpt_cscsh_even, dphipositionpt_cscsh_odd, dphipositionpt_gemsh_even,dphipositionpt_gemsh_odd;

  Char_t has_csc_sh; // #layers with SimHits > minHitsChamber    bit1: in odd, bit2: even
  Char_t has_csc_strips; // #layers with comparator digis > minHitsChamber    bit1: in odd, bit2: even
  Char_t has_csc_wires; // #layers with wire digis > minHitsChamber    bit1: in odd, bit2: even
  Int_t nlayers_wg_dg_odd;
  Int_t nlayers_st_dg_odd;
  Int_t nlayers_wg_dg_even;
  Int_t nlayers_st_dg_even;

  Char_t has_rechits;
  Int_t nlayers_rechits_odd;
  Int_t nlayers_rechits_even;

  Char_t has_clct; // bit1: in odd, bit2: even
  Char_t has_alct; // bit1: in odd, bit2: even
  Char_t has_lct; // bit1: in odd, bit2: even

  Float_t phi_layer1_fit_even, phi_layer3_fit_even, phi_layer6_fit_even, phi_layer1_fit_odd, phi_layer3_fit_odd, phi_layer6_fit_odd;
  Float_t z_layer3_fit_even, z_layer3_fit_odd;
  Char_t bend_lct_odd;
  Char_t bend_lct_even;
  Char_t bx_lct_odd, bx_alct_odd, bx_clct_odd;
  Char_t bx_lct_even, bx_alct_even, bx_clct_even;


  UChar_t hs_lct_odd;
  UChar_t wg_lct_odd;
  UChar_t hs_lct_even;
  UChar_t wg_lct_even;

  Float_t phi_lct_odd;
  Float_t phi_lct_even;
  Float_t eta_lct_odd;
  Float_t eta_lct_even;
  Float_t phi_me0_st2_odd;
  Float_t phi_me0_st2_even;
  Float_t eta_me0_st2_odd;
  Float_t eta_me0_st2_even;
  Float_t dphi_lct_odd; // dphi stored as data member in LCT
  Float_t dphi_lct_even;
  Float_t chi2_lct_odd, chi2_lct_even;
  Float_t timeErr_lct_odd, timeErr_lct_even;
  Int_t nHits_lct_odd, nHits_lct_even;
  Float_t dR_sim_lct_odd, dR_sim_lct_even;
  Float_t me0_st1_dphi_odd, me0_st1_dphi_even;
  Bool_t me0_st1_isEven_odd, me0_st1_isEven_even;
  Float_t perp_lct_odd;
  Float_t perp_lct_even;
  Bool_t passdphi_odd;
  Bool_t passdphi_even;
  Float_t fitperp_lct_odd;
  Float_t fitperp_lct_even;

  Int_t wiregroup_odd;
  Int_t wiregroup_even;
  Int_t halfstrip_odd;
  Int_t halfstrip_even;

  Int_t quality_clct_odd;
  Int_t quality_clct_even;
  Int_t quality_alct_odd;
  Int_t quality_alct_even;

  Int_t pad_odd;
  Int_t pad_even;
  Int_t Copad_odd;
  Int_t Copad_even;
  Int_t hsfromgem_odd;
  Int_t hsfromgem_even;

  Char_t has_gem_sh; // bit1: in odd, bit2: even
  Char_t has_gem_sh2; // has SimHits in 2 layers  bit1: in odd, bit2: even
  Char_t has_gemcopad_sh; // has SimHits in 2 layers  bit1: in odd, bit2: even
  Char_t has_gem_dg; // bit1: in odd, bit2: even
  Char_t has_gem_dg2; // has pads in 2 layers  bit1: in odd, bit2: even
  Char_t has_gem_pad; // bit1: in odd, bit2: even
  Char_t has_gem_pad2; // has pads in 2 layers  bit1: in odd, bit2: even
  Char_t has_gem_copad; // bit1: in odd, bit2: even

  Float_t strip_gemsh_odd; // average hits' strip
  Float_t strip_gemsh_even;
  Float_t eta_gemsh_odd;
  Float_t eta_gemsh_even;
  Float_t phi_gemsh_odd;
  Float_t phi_gemsh_even;
  Int_t strip_gemdg_odd; // median digis' strip
  Int_t strip_gemdg_even;


  Char_t has_rpc_sh; // bit1: in odd, bit2: even
  Char_t has_rpc_dg; // bit1: in odd, bit2: even
  Char_t has_rpc_rh; // bit1: in odd, bit2: even
  Int_t strip_rpcdg_odd; // median digis' strip
  Int_t strip_rpcdg_even;

  int rpc_BunchX;
  int rpc_firstClusterStrip;
  int rpc_clusterSize;
  float rpc_time;
  float rpc_timeError;

  Int_t lct_type;

  Char_t bx_pad_odd;
  Char_t bx_pad_even;
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

  Float_t phi_1strippad_odd;
  Float_t phi_1strippad_even;
  Float_t phi_2strippad_odd;
  Float_t phi_2strippad_even;
  Float_t phi_4strippad_odd;
  Float_t phi_4strippad_even;
  Float_t phi_8strippad_odd;
  Float_t phi_8strippad_even;
  Float_t dphi_1strippad_odd;
  Float_t dphi_1strippad_even;
  Float_t dphi_2strippad_odd;
  Float_t dphi_2strippad_even;
  Float_t dphi_4strippad_odd;
  Float_t dphi_4strippad_even;
  Float_t dphi_8strippad_odd;
  Float_t dphi_8strippad_even;
  Float_t dphi_1strippad_fit_odd;
  Float_t dphi_1strippad_fit_even;
  Float_t dphi_2strippad_fit_odd;
  Float_t dphi_2strippad_fit_even;
  Float_t dphi_4strippad_fit_odd;
  Float_t dphi_4strippad_fit_even;
  Float_t dphi_8strippad_fit_odd;
  Float_t dphi_8strippad_fit_even;

  Int_t quality_odd;
  Int_t quality_even;

  Int_t hsfromrpc_odd; // extraplotate hs from rpc
  Int_t hsfromrpc_even;

  Char_t bx_rpcstrip_odd;
  Char_t bx_rpcstrip_even;
  Float_t phi_rpcstrip_odd;
  Float_t phi_rpcstrip_even;
  Float_t eta_rpcstrip_odd;
  Float_t eta_rpcstrip_even;

  Float_t dphi_rpcstrip_odd;
  Float_t dphi_rpcstrip_even;
  Float_t deta_rpcstrip_odd;
  Float_t deta_rpcstrip_even;

  // Track properties
  Int_t has_tfTrack;
  Int_t has_tfCand;
  Int_t has_gmtRegCand;
  Int_t has_gmtCand;

  //csctf
  Float_t trackpt, tracketa, trackphi;
  UInt_t quality_packed, pt_packed, eta_packed, phi_packed;
  UInt_t chargesign;
  UInt_t rank;
  UInt_t nstubs;
  UInt_t deltaphi12, deltaphi23;
  Bool_t hasME1,hasME2, hasME3, hasME4;
  Char_t chamberME1,chamberME2;//bit1: odd, bit2: even
  Int_t ME1_ring, ME2_ring;
  Int_t ME1_hs, ME2_hs, ME1_wg,ME2_wg;
  Float_t dphiGE11,dphiGE21;
  Bool_t passGE11,passGE21;
  Bool_t passGE11_pt5, passGE11_pt7, passGE11_pt10, passGE11_pt15, passGE11_pt20, passGE11_pt30, passGE11_pt40;
  Bool_t passGE21_pt5, passGE21_pt7, passGE21_pt10, passGE21_pt15, passGE21_pt20, passGE21_pt30, passGE21_pt40;
  Bool_t passGE11_simpt, passGE21_simpt;
  Float_t deltaR;
  Float_t lctdphi12;


  // pt assginment
  Int_t meRing;
  Float_t phiM_gemcsc_even,phiM_gemcsc_odd;
  Float_t phiM_st1_sh, phiM_st2_sh;
  Float_t phiM_st12_sh, phiM_st23_sh;
  Float_t phiM_fitxyz_even,phiM_fitxyz_odd;
  Float_t phiM_st1_L1, phiM_st2_L1;
  Float_t phiM_st12_L1, phiM_st23_L1;
  Float_t phiM_ME11only_L1, phiM_ME21only_L1;
  Float_t phiM_GE11_L1, phiM_ME0_L1, dphi_dir_GE11_st2_L1, dphi_dir_ME0_st2_L1;
  Float_t dphi_dir_ME11only_st2_L1, dphi_dir_st1_ME21only_L1, dphi_dir_ME11only_ME21only_L1;
  Float_t pt_sh_even,pt_sh_odd,ptphi_sh_even,ptphi_sh_odd,pteta_sh_even,pteta_sh_odd;
  Float_t ptphi_gemsh_odd, ptphi_gemsh_even;
  Float_t dphi_dir_st1_st2_sh, dphi_dir_st1_st2_L1, dphi_dir_st1_st2_L1_csc;
  Float_t dphi_dir_st1_st12_sh,dphi_dir_st2_st23_sh, dphi_dir_st12_st23_sh;
  Float_t dphi_dir_st1_st12_L1,dphi_dir_st2_st23_L1,dphi_dir_st1_st12_L1_csc,dphi_dir_st2_st23_L1_csc, dphi_dir_st12_st23_L1;
  Float_t hybrid_pt, hybrid_noge21_pt, position_pt, direction_ge21_pt, direction_noge21_pt;
  //Float_t ptphi_diff_sh_11,ptphi_diff_sh_12,ptphi_diff_sh_21,ptphi_diff_sh_22;
  Float_t ptphi_diff_sh;
  Float_t deltay12_fit, deltay23_fit;
  Float_t deltay12_lct, deltay23_lct;
  Float_t deltay12_sim, deltay23_sim;
  Float_t deltay12_test, deltay23_test, deltay123_test;
  Float_t eta_st2_sh, eta_st2_L1, eta_st1_L1;
  Bool_t isMe0Region;
  Int_t npar_L1, npar_sim;
  Float_t eta_st1_sim, eta_st2_sim;
  Float_t pt_position_sh, pt_direction_sh;
  Float_t pt_position, pt_direction_gemcsc, pt_direction_gemcsc_central, pt_direction_xfactor;
  Float_t pt_position_fit;
  Int_t npar;
  Int_t npar_lct;
  Bool_t hasSt1St2St3;
  Bool_t hasSt3orSt4_sh;
};

void MyTrack::init()
{
  pt = 0.;
  phi = 0.;
  eta = -9.;
  dxy = -999.;
  charge = -9;
  endcap = -9;
  pdgid = -9999;

  chamber_ME1_csc_sh=0;
  chamber_ME2_csc_sh=0;
  chamber_sh_odd = -1;
  chamber_sh_even = -1;
  nlayers_csc_sh_odd = -1;
  nlayers_csc_sh_even = -1;
  quality_odd = 0;
  quality_even = 0;
  bending_sh = -10;
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
  /* pt_sh_even = -9.0; */
  /* pteta_sh_even = 0; */
  /* ptphi_sh_even = -9.0; */
  /* pt_sh_odd = -9.0; */
  /* pteta_sh_odd = 0; */
  /* ptphi_sh_odd = -9.0; */
  /* ptphi_gemsh_even = -9.0; */
  /* ptphi_gemsh_odd = -9.0; */


  has_csc_strips = 0;
  has_csc_wires = 0;
  nlayers_wg_dg_odd = -1;
  nlayers_st_dg_odd = -1;
  nlayers_wg_dg_even = -1;
  nlayers_st_dg_even = -1;


  phi_layer1_fit_even =-9.0;
  phi_layer1_fit_odd =-9.0;
  z_layer3_fit_even =-9.0;
  z_layer3_fit_odd =-9.0;
  phi_layer3_fit_even =-9.0;
  phi_layer3_fit_odd =-9.0;
  phi_layer6_fit_even =-9.0;
  phi_layer6_fit_odd =-9.0;
  has_csc_sh = 0;
  chamber_dg_odd = -1;
  chamber_dg_even = -1;
  has_alct = 0;
  has_clct = 0;
  has_lct = 0;
  chamber_lct_odd = -1;
  chamber_lct_even = -1;
  bend_lct_odd = -9;
  bend_lct_even = -9;
  dphi_lct_odd = -9;
  dphi_lct_even = -9;
  bx_lct_odd = -9;
  bx_lct_even = -9;
  hs_lct_odd = 0;
  hs_lct_even = 0;
  wg_lct_odd = 0;
  wg_lct_even = 0;
  phi_lct_odd = -9.;
  phi_lct_even = -9.;
  eta_lct_odd = -9.;
  eta_lct_even = -9.;
  chi2_lct_odd = -99999;
  chi2_lct_even = -99999;
  timeErr_lct_odd = -9999;
  timeErr_lct_even = -9999;
  nHits_lct_odd = 0;
  nHits_lct_even = 0;
  dR_sim_lct_odd = 10;
  dR_sim_lct_even = 10;
  passdphi_odd = false;
  passdphi_even = false;
  perp_lct_odd = -1;
  perp_lct_even = -1;
  fitperp_lct_odd = -1;
  fitperp_lct_even = -1;

  wiregroup_odd = -1;
  wiregroup_even =-1;
  halfstrip_odd =-1;
  halfstrip_even = -1;
  quality_clct_odd = -1;
  quality_clct_even = -1;
  quality_alct_odd = -1;
  quality_alct_even = -1;
  bx_clct_odd = -9;
  bx_clct_even = -9;
  bx_alct_odd = -9;
  bx_alct_even = -9;
  pad_odd = -1;
  pad_even = -1;
  Copad_odd = -1;
  Copad_even = -1;

  hsfromgem_odd = -1;
  hsfromgem_even = -1;

  has_gem_sh = 0;
  has_gem_sh2 = 0;
  has_gemcopad_sh = 0;
  has_gem_dg = 0;
  has_gem_dg2 = 0;
  has_gem_pad = 0;
  has_gem_pad2 = 0;
  has_gem_copad = 0;
  strip_gemsh_odd = -9.;
  strip_gemsh_even = -9.;
  eta_gemsh_odd = -9.;
  eta_gemsh_even = -9.;
  phi_gemsh_odd = -9.;
  phi_gemsh_even = -9.;
  dphi_sh_odd = -9;
  dphi_sh_even = -9;
  /* phiM_gemcsc_odd = -9; */
  /* phiM_gemcsc_even =-9; */
  /* phiM_fitxyz_odd = -9; */
  /* phiM_fitxyz_even =-9; */

  strip_gemdg_odd = -9;
  strip_gemdg_even = -9;

  lct_type = -1;

  hsfromrpc_odd = 0;
  hsfromrpc_even = 0;

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
}


TTree* MyTrack::book(TTree *t, const std::string & name)
{
  edm::Service< TFileService > fs;
  t = fs->make<TTree>(name.c_str(), name.c_str());

  t->Branch("pt", &pt);
  t->Branch("pz", &pz);
  t->Branch("eta", &eta);
  t->Branch("dxy", &dxy);
  t->Branch("phi", &phi);
  t->Branch("charge", &charge);
  t->Branch("endcap", &endcap);
  t->Branch("pdgid", &pdgid);


  t->Branch("chamber_ME1_csc_sh", &chamber_ME1_csc_sh);
  t->Branch("chamber_ME2_csc_sh", &chamber_ME2_csc_sh);
  t->Branch("chamber_sh_odd", &chamber_sh_odd);
  t->Branch("chamber_sh_even", &chamber_sh_even);
  t->Branch("nlayers_csc_sh_odd", &nlayers_csc_sh_odd);
  t->Branch("nlayers_csc_sh_even", &nlayers_csc_sh_even);
  t->Branch("quality_odd", &quality_odd);
  t->Branch("quality_even", &quality_even);
  t->Branch("bending_sh", &bending_sh);
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

  t->Branch("chamber_dg_odd", &chamber_dg_odd);
  t->Branch("chamber_dg_even", &chamber_dg_even);
  t->Branch("has_csc_sh", &has_csc_sh);
  t->Branch("has_csc_strips", &has_csc_strips);
  t->Branch("has_csc_wires", &has_csc_wires);
  t->Branch("nlayers_wg_dg_odd", &nlayers_wg_dg_odd);
  t->Branch("nlayers_wg_dg_even", &nlayers_wg_dg_even);
  t->Branch("nlayers_st_dg_odd", &nlayers_st_dg_odd);
  t->Branch("nlayers_st_dg_even", &nlayers_st_dg_even);


  t->Branch("has_clct", &has_clct);
  t->Branch("has_alct", &has_alct);
  t->Branch("has_lct", &has_lct);

  t->Branch("quality_clct_odd", &quality_clct_odd);
  t->Branch("quality_clct_even", &quality_clct_even);
  t->Branch("bx_clct_odd", &bx_clct_odd);
  t->Branch("bx_clct_even", &bx_clct_even);
  t->Branch("quality_alct_odd", &quality_alct_odd);
  t->Branch("quality_alct_even", &quality_alct_even);
  t->Branch("bx_alct_odd", &bx_alct_odd);
  t->Branch("bx_alct_even", &bx_alct_even);


  t->Branch("chamber_lct_odd", &chamber_lct_odd);
  t->Branch("chamber_lct_even", &chamber_lct_even);
  t->Branch("z_layer3_fit_even", &z_layer3_fit_even);
  t->Branch("z_layer3_fit_odd", &z_layer3_fit_odd);
  t->Branch("phi_layer1_fit_even", &phi_layer1_fit_even);
  t->Branch("phi_layer1_fit_odd", &phi_layer1_fit_odd);
  t->Branch("phi_layer3_fit_even", &phi_layer3_fit_even);
  t->Branch("phi_layer3_fit_odd", &phi_layer3_fit_odd);
  t->Branch("phi_layer6_fit_even", &phi_layer6_fit_even);
  t->Branch("phi_layer6_fit_odd", &phi_layer6_fit_odd);
  t->Branch("bend_lct_odd", &bend_lct_odd);
  t->Branch("bend_lct_even", &bend_lct_even);
  t->Branch("bx_lct_odd", &bx_lct_odd);
  t->Branch("bx_lct_even", &bx_lct_even);
  t->Branch("hs_lct_odd", &hs_lct_odd);
  t->Branch("hs_lct_even", &hs_lct_even);
  t->Branch("wg_lct_even", &wg_lct_even);
  t->Branch("wg_lct_odd", &wg_lct_odd);
  t->Branch("phi_lct_odd", &phi_lct_odd);
  t->Branch("phi_lct_even", &phi_lct_even);
  t->Branch("eta_lct_odd", &eta_lct_odd);
  t->Branch("eta_lct_even", &eta_lct_even);
  t->Branch("perp_lct_odd", &perp_lct_odd);
  t->Branch("perp_lct_even", &perp_lct_even);
  t->Branch("fitperp_lct_odd", &fitperp_lct_odd);
  t->Branch("fitperp_lct_even", &fitperp_lct_even);
  t->Branch("dphi_lct_odd", &dphi_lct_odd);
  t->Branch("dphi_lct_even", &dphi_lct_even);
  t->Branch("chi2_lct_odd", &chi2_lct_odd);
  t->Branch("chi2_lct_even", &chi2_lct_even);
  t->Branch("timeErr_lct_odd", &timeErr_lct_odd);
  t->Branch("timeErr_lct_even", &timeErr_lct_even);
  t->Branch("nHits_lct_odd", &nHits_lct_odd);
  t->Branch("nHits_lct_even", &nHits_lct_even);
  t->Branch("dR_sim_lct_odd", &dR_sim_lct_odd);
  t->Branch("dR_sim_lct_even", &dR_sim_lct_even);
  t->Branch("passdphi_odd", &passdphi_odd);
  t->Branch("passdphi_even", &passdphi_even);

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

  t->Branch("has_gem_sh", &has_gem_sh);
  t->Branch("has_gem_sh2", &has_gem_sh2);
  t->Branch("has_gemcopad_sh", &has_gemcopad_sh);
  t->Branch("has_gem_dg", &has_gem_dg);
  t->Branch("has_gem_dg2", &has_gem_dg2);
  t->Branch("has_gem_pad", &has_gem_pad);
  t->Branch("has_gem_pad2", &has_gem_pad2);
  t->Branch("has_gem_copad", &has_gem_copad);
  t->Branch("strip_gemsh_odd", &strip_gemsh_odd);
  t->Branch("strip_gemsh_even", &strip_gemsh_even);
  t->Branch("eta_gemsh_odd", &eta_gemsh_odd);
  t->Branch("eta_gemsh_even", &eta_gemsh_even);
  t->Branch("phi_gemsh_odd", &phi_gemsh_odd);
  t->Branch("phi_gemsh_even", &phi_gemsh_even);
  t->Branch("dphi_sh_odd", &dphi_sh_odd);
  t->Branch("dphi_sh_even", &dphi_sh_even);
  /* t->Branch("phiM_gemcsc_odd", &phiM_gemcsc_odd); */
  /* t->Branch("phiM_gemcsc_even", &phiM_gemcsc_even); */
  /* t->Branch("phiM_fitxyz_odd", &phiM_fitxyz_odd); */
  /* t->Branch("phiM_fitxyz_even", &phiM_fitxyz_even); */
  t->Branch("strip_gemdg_odd", &strip_gemdg_odd);
  t->Branch("strip_gemdg_even", &strip_gemdg_even);

  t->Branch("lct_type", &lct_type);

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

}

#endif
