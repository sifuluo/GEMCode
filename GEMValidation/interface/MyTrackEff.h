#ifndef GEMCode_GEMValidation_MyTrackEff
#define GEMCode_GEMValidation_MyTrackEff

#include "TTree.h"
#include <vector>
#include <string>

namespace{

struct MyTrackEff
{
  void init(); // initialize to default values
  TTree* book(TTree *t, const std::string & name = "trk_eff");

  Int_t lumi;
  Int_t run;
  Int_t event;
  Float_t rand01_v1;
  Float_t rand01_v2;

  Float_t pt, eta, phi, pz, dxy;
  Char_t charge;
  Char_t endcap;
  Int_t pdgid;

  // Dark photon
  Float_t genGd_m;
  Float_t genGd_E;
  Float_t genGd_p;
  Float_t genGd_pt;
  Float_t genGd_px;
  Float_t genGd_py;
  Float_t genGd_pz;
  Float_t genGd_eta;
  Float_t genGd_phi;
  Float_t genGd_vx;
  Float_t genGd_vy;
  Float_t genGd_vz;
  Float_t genGd_vLx;
  Float_t genGd_vLy;
  Float_t genGd_vLz;
  Float_t genGd_lxy;
  Float_t genGd_l;
  Float_t genGd_dxy;
  Float_t genGd0Gd1_dR;
  Float_t genGd0Gd1_m;

  Float_t genGdMu_dxy_max;
  Float_t genGdMu_eta_max;

  // Gen level muon
  Int_t genGd_index;
  Int_t genGdMu_index;
  Float_t genGdMu_p;
  Float_t genGdMu_pt;
  Float_t genGdMu_px;
  Float_t genGdMu_py;
  Float_t genGdMu_pz;
  Float_t genGdMu_eta;
  Float_t genGdMu_phi;
  Float_t genGdMu_phi_corr;
  Float_t genGdMu_vx;
  Float_t genGdMu_vy;
  Float_t genGdMu_vz;
  Float_t genGdMu_dxy;
  Float_t genGdMu_dR;
  Float_t genGdMu_lxy;

  Float_t beamSpot_x;
  Float_t beamSpot_y;
  Float_t beamSpot_z;


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
  Int_t strip_rpcdg_odd; // median digis' strip
  Int_t strip_rpcdg_even;

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
  /*
  Float_t eta_propagated_ME1;
  Float_t eta_propagated_ME2;
  Float_t eta_propagated_ME3;
  Float_t eta_propagated_ME4;
  Float_t phi_propagated_ME1;
  Float_t phi_propagated_ME2;
  Float_t phi_propagated_ME3;
  Float_t phi_propagated_ME4;
  Float_t eta_ME1_TF;
  Float_t eta_ME2_TF;
  Float_t eta_ME3_TF;
  Float_t eta_ME4_TF;
  Float_t phi_ME1_TF;
  Float_t phi_ME2_TF;
  Float_t phi_ME3_TF;
  Float_t phi_ME4_TF;

  Float_t eta_interStat12;
  Float_t phi_interStat12;
  Float_t eta_interStat23;
  Float_t phi_interStat23;
  Float_t eta_interStat13;
  Float_t phi_interStat13;
  */

  Bool_t allstubs_matched_TF;
  //L1Mu
  Float_t bestdRGmtCand;
  Float_t L1Mu_pt, L1Mu_eta, L1Mu_phi, L1Mu_quality, L1Mu_bx;
  Int_t L1Mu_charge;
  Float_t L1Mu_me0_eta, L1Mu_me0_phi, L1Mu_me0_dPhi, L1Mu_me0_mindPhi1, L1Mu_me0_mindPhi2, L1Mu_me0_dR, L1Mu_me0_st1_dphi, L1Mu_me0_st2_eta, L1Mu_me0_st2_phi;
  Bool_t L1Mu_me0_st1_isEven;
  Float_t L1Mu_st1_eta, L1Mu_st1_phi, L1Mu_st1_dR;
  Bool_t L1Mu_st1_isEven;

  Int_t has_l1Extra;
  Float_t l1Extra_pt;
  Float_t l1Extra_eta;
  Float_t l1Extra_phi;
  Float_t l1Extra_dR;
  Int_t has_recoTrackExtra;
  Float_t recoTrackExtra_pt_inner;
  Float_t recoTrackExtra_eta_inner;
  Float_t recoTrackExtra_phi_inner;
  Float_t recoTrackExtra_pt_outer;
  Float_t recoTrackExtra_eta_outer;
  Float_t recoTrackExtra_phi_outer;
  Int_t has_recoTrack;
  Float_t recoTrack_pt_outer;
  Float_t recoTrack_eta_outer;
  Float_t recoTrack_phi_outer;
  Int_t has_recoChargedCandidate;
  Float_t recoChargedCandidate_pt;
  Float_t recoChargedCandidate_eta;
  Float_t recoChargedCandidate_phi;

  Int_t recoChargedCandidate_nValidCSCHits;
  Int_t recoChargedCandidate_nValidRPCHits;
  Int_t recoChargedCandidate_nValidDTHits;


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

  // track veto
  Bool_t isSimLooseVeto;
  Bool_t isSimMediumVeto;
  Bool_t isSimTightVeto;
  Bool_t isL1LooseVeto;
  Bool_t isL1MediumVeto;
  Bool_t isL1TightVeto;
  Int_t nTrackTriggers;

  // track-match
  float L1Track_eta;
  float L1Track_phi;
  float L1TrackMuon_eta;
  float L1TrackMuon_phi;
  float GMTCand_eta;
  float GMTCand_phi;
  float sim_st2_eta;
  float sim_st2_phi;
  float sim_prop_eta;
  float sim_prop_phi;
  float dR_prop_L1TrackMuon;
  float dR_st2_L1TrackMuon;
  float dR_L1Track;
};

void MyTrackEff::init()
{
  lumi = -99;
  run = -99;
  event = -99;
  rand01_v1 = 99;
  rand01_v2 = 99;

  pt = 0.;
  phi = 0.;
  eta = -9.;
  dxy = -999.;
  charge = -9;
  endcap = -9;
  pdgid = -9999;

  // Dark photon
  genGd_m =0.0;
  genGd_E =0.0;
  genGd_p =0.0;
  genGd_pt =0.0;
  genGd_px =0.0;
  genGd_py =0.0;
  genGd_pz =0.0;
  genGd_eta =0.0;
  genGd_phi =0.0;
  genGd_vx =0.0;
  genGd_vy =0.0;
  genGd_vz =0.0;
  genGd_vLx = -0.;
  genGd_vLy = -0;
  genGd_vLz= -0;
  genGd_lxy = -0.;
  genGd_l =-0.;
  genGd_dxy =-1;
  genGd0Gd1_dR =-1;
  genGd0Gd1_m = 0;

  genGdMu_dxy_max =0.0;
  genGdMu_eta_max =0.0;

  // Gen level muon
  genGd_index = -99;
  genGdMu_index = -99;
  genGdMu_p =0.0;
  genGdMu_pt =0.0;
  genGdMu_px =0.0;
  genGdMu_py =0.0;
  genGdMu_pz =0.0;
  genGdMu_eta =0.0;
  genGdMu_phi =0.0;
  genGdMu_phi_corr =0.0;
  genGdMu_vx =0.0;
  genGdMu_vy =0.0;
  genGdMu_vz =0.0;
  genGdMu_dxy =0.0;
  genGdMu_dR = 10.0;
  genGdMu_lxy = 0.0;

  beamSpot_x =0.0;
  beamSpot_y =0.0;
  beamSpot_z =0.0;


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
  phi_layer1_sh_even =-9.0;
  phi_layer1_sh_odd =-9.0;
  eta_layer1_sh_even =-9.0;
  eta_layer1_sh_odd =-9.0;
  perp_layer1_sh_even = -1;
  perp_layer1_sh_odd = -1;
  z_layer1_sh_even = 0.0;
  z_layer1_sh_odd = 0.0;
  phi_layer6_sh_even =-9.0;
  phi_layer6_sh_odd =-9.0;
  eta_layer6_sh_even =-9.0;
  eta_layer6_sh_odd =-9.0;
  perp_layer6_sh_even = -1;
  perp_layer6_sh_odd = -1;
  z_layer6_sh_even = 0.0;
  z_layer6_sh_odd = 0.0;
  pt_sh_even = -9.0;
  pteta_sh_even = 0;
  ptphi_sh_even = -9.0;
  pt_sh_odd = -9.0;
  pteta_sh_odd = 0;
  ptphi_sh_odd = -9.0;
  ptphi_gemsh_even = -9.0;
  ptphi_gemsh_odd = -9.0;


  has_csc_strips = 0;
  has_csc_wires = 0;
  has_rechits = 0;
  nlayers_wg_dg_odd = -1;
  nlayers_st_dg_odd = -1;
  nlayers_wg_dg_even = -1;
  nlayers_st_dg_even = -1;
  nlayers_rechits_odd = -1;
  nlayers_rechits_even = -1;


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
  phi_me0_st2_odd = -9.;
  phi_me0_st2_even = -9.;
  eta_me0_st2_odd = -9.;
  eta_me0_st2_even = -9.;
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
  me0_st1_dphi_odd = -9;
  me0_st1_dphi_even = -9;
  me0_st1_isEven_odd = false;
  me0_st1_isEven_even = false;



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
  dphipositionpt_gemsh_even = -9;
  dphipositionpt_gemsh_odd = -9;
  dphipositionpt_cscsh_even = -9;
  dphipositionpt_cscsh_odd = -9;
  phiM_gemcsc_odd = -9;
  phiM_gemcsc_even =-9;
  phiM_fitxyz_odd = -9;
  phiM_fitxyz_even =-9;



  strip_gemdg_odd = -9;
  strip_gemdg_even = -9;

  has_rpc_sh = 0;
  has_rpc_dg = 0; // bit1: in odd, bit2: even
  strip_rpcdg_odd = -1;
  strip_rpcdg_even = -1;

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

  phi_1strippad_odd = -9.0;
  phi_1strippad_even = -9.0;
  phi_2strippad_odd = -9.0;
  phi_2strippad_even = -9.0;
  phi_4strippad_odd = -9.0;
  phi_4strippad_even = -9.0;
  phi_8strippad_odd = -9.0;
  phi_8strippad_even = -9.0;
  dphi_1strippad_odd = -9.0;
  dphi_1strippad_even = -9.0;
  dphi_2strippad_odd = -9.0;
  dphi_2strippad_even = -9.0;
  dphi_4strippad_odd = -9.0;
  dphi_4strippad_even = -9.0;
  dphi_8strippad_odd = -9.0;
  dphi_8strippad_even = -9.0;
  dphi_1strippad_fit_odd = -9.0;
  dphi_1strippad_fit_even = -9.0;
  dphi_2strippad_fit_odd = -9.0;
  dphi_2strippad_fit_even = -9.0;
  dphi_4strippad_fit_odd = -9.0;
  dphi_4strippad_fit_even = -9.0;
  dphi_8strippad_fit_odd = -9.0;
  dphi_8strippad_fit_even = -9.0;

  bx_rpcstrip_odd = -9;
  bx_rpcstrip_even = -9;
  phi_rpcstrip_odd = -9.;
  phi_rpcstrip_even = -9.;
  eta_rpcstrip_odd = -9.;
  eta_rpcstrip_even = -9.;
  dphi_rpcstrip_odd = -9.;
  dphi_rpcstrip_even = -9.;
  deta_rpcstrip_odd = -9.;
  deta_rpcstrip_even = -9.;

  // Track properties
  has_tfTrack = -99;
  has_tfCand = -99;
  has_gmtRegCand = -99;
  has_gmtCand = -99;

  //csctf
  trackpt = -1;
  tracketa = -9;
  trackphi = -9;
  quality_packed = 0;
  pt_packed = 0;
  eta_packed = 0;
  phi_packed = 0;
  ME1_hs = -1;
  ME1_wg = -1;
  ME2_hs = -1;
  ME2_wg = -1;
  chargesign =99;
  rank = 0;
  deltaphi12 = 0;
  deltaphi23 = 0;;
  hasME1 = false;
  hasME2 = false;
  hasME3 = false;
  hasME4 = false;
  ME1_ring = -1;
  ME2_ring = -1;
  chamberME1 = 0;
  chamberME2 = 0;
  dphiGE11 = -99.0;
  dphiGE21 = -99.0;
  passGE11 = false;
  passGE11_pt5 = false;
  passGE11_pt7 = false;
  passGE11_pt10 = false;
  passGE11_pt15 = false;
  passGE11_pt20 = false;
  passGE11_pt30 = false;
  passGE11_pt40 = false;
  passGE21 = false;
  passGE21_pt5 = false;
  passGE21_pt7 = false;
  passGE21_pt10 = false;
  passGE21_pt15 = false;
  passGE21_pt20 = false;
  passGE21_pt30 = false;
  passGE21_pt40 = false;
  passGE11_simpt = false;
  passGE21_simpt = false;//to debug dphi cut eff
  nstubs = 0;
  deltaR = 10;
  lctdphi12 = -99;
  /*
  eta_propagated_ME1 = -9;
  eta_propagated_ME2 = -9;
  eta_propagated_ME3 = -9;
  eta_propagated_ME4 = -9;
  phi_propagated_ME1 = -9;
  phi_propagated_ME2 = -9;
  phi_propagated_ME3 = -9;
  phi_propagated_ME4 = -9;
  eta_ME1_TF = -9;
  eta_ME2_TF = -9;
  eta_ME3_TF = -9;
  eta_ME4_TF = -9;
  phi_ME1_TF = -9;
  phi_ME2_TF = -9;
  phi_ME3_TF = -9;
  phi_ME4_TF = -9;

  eta_interStat12 = -9;
  phi_interStat12 = -9;
  eta_interStat23 = -9;
  phi_interStat23 = -9;
  eta_interStat13 = -9;
  phi_interStat13 = -9;
  */

  allstubs_matched_TF = false;

  bestdRGmtCand = 99;
  L1Mu_pt = -99;
  L1Mu_eta = -99;
  L1Mu_phi = -99;
  L1Mu_quality = -99;
  L1Mu_bx = -99;
  L1Mu_charge = -99;
  L1Mu_me0_eta = -9;
  L1Mu_me0_phi = -9;
  L1Mu_me0_st2_eta = -9;
  L1Mu_me0_st2_phi = -9;
  L1Mu_me0_dPhi = -9;
  L1Mu_me0_dR = 10;
  L1Mu_me0_mindPhi1 = 10;
  L1Mu_me0_mindPhi2 = 10;
  L1Mu_me0_st1_dphi = -9;
  L1Mu_me0_st1_isEven = false;
  L1Mu_st1_dR = 10;
  L1Mu_st1_eta = -9;
  L1Mu_st1_phi = -9;
  L1Mu_st1_isEven = -9;


  has_l1Extra = 0;
  l1Extra_pt = -99;
  l1Extra_eta = -99;
  l1Extra_phi = -99;
  l1Extra_dR = -99;
  has_recoTrackExtra = 0;
  recoTrackExtra_pt_inner = - 99.;
  recoTrackExtra_eta_inner = - 99.;
  recoTrackExtra_phi_inner = - 99.;
  recoTrackExtra_pt_outer = - 99.;
  recoTrackExtra_eta_outer = - 99.;
  recoTrackExtra_phi_outer = - 99.;
  has_recoTrack = 0;
  recoTrack_pt_outer = - 99.;
  recoTrack_eta_outer = - 99.;
  recoTrack_phi_outer = - 99.;
  has_recoChargedCandidate = 0;
  recoChargedCandidate_pt = - 99.;
  recoChargedCandidate_eta = - 99.;
  recoChargedCandidate_phi = - 99.;

  recoChargedCandidate_nValidDTHits = 0;
  recoChargedCandidate_nValidCSCHits = 0;
  recoChargedCandidate_nValidRPCHits = 0;

  npar = -1;
  npar_lct = -1;
  meRing = -1;
  npar_L1 = -1;
  npar_sim = -1;
  eta_st1_sim = -9;
  eta_st2_sim = -9;
  eta_st2_L1 = -9;
  eta_st1_L1 = -9;
  eta_st2_sh = -9;
  isMe0Region = false;
  ptphi_diff_sh = -9;
  phiM_st1_sh = -9;
  phiM_st2_sh = -9;
  phiM_st12_sh = -9;
  phiM_st23_sh = -9;
  phiM_st1_L1 = -9;
  phiM_st2_L1 = -9;
  phiM_GE11_L1 = -9;
  phiM_ME0_L1 = -9;
  dphi_dir_GE11_st2_L1 = -9;
  dphi_dir_ME0_st2_L1 = -9;
  phiM_st12_L1 = -9;
  phiM_st23_L1 = -9;
  phiM_ME11only_L1 = -9;
  phiM_ME21only_L1 = -9;
  dphi_dir_st1_st2_sh = -9;
  dphi_dir_st1_st2_L1 = -9;
  dphi_dir_ME11only_st2_L1 = -9;
  dphi_dir_st1_ME21only_L1 = -9;
  dphi_dir_ME11only_ME21only_L1 = -9;
  dphi_dir_st1_st2_L1_csc = -9;
  dphi_dir_st1_st12_sh = -9;
  dphi_dir_st2_st23_sh = -9;
  dphi_dir_st12_st23_sh = -9;
  dphi_dir_st1_st12_L1 = -9;
  dphi_dir_st2_st23_L1 = -9;
  dphi_dir_st1_st12_L1_csc = -9;
  dphi_dir_st2_st23_L1_csc = -9;
  dphi_dir_st12_st23_L1 = -9;
  hybrid_pt = 0.0;
  hybrid_noge21_pt = 0.0;
  position_pt = 0.0;
  direction_noge21_pt = 0.0;
  direction_ge21_pt = 0.0;
  deltay12_sim = -99;
  deltay23_sim = -99;
  deltay12_fit = -99;
  deltay23_fit = -99;
  deltay12_lct = -99;
  deltay23_lct = -99;
  deltay12_test = -99;
  deltay23_test = -99;
  deltay123_test = -99;
  pt_position_sh=-1;
  pt_position=-1;
  pt_position_fit =-1;
  pt_direction_gemcsc = -1;
  pt_direction_sh=-1;
  hasSt1St2St3=false;
  hasSt3orSt4_sh=false;

  isSimLooseVeto = false;
  isSimMediumVeto = false;
  isSimTightVeto = false;
  isL1LooseVeto = false;
  isL1MediumVeto = false;
  isL1TightVeto = false;
  nTrackTriggers = 0;

  L1Track_eta = -99;
  L1Track_phi = -99;
  L1TrackMuon_eta = -99;
  L1TrackMuon_phi = -99;
  GMTCand_eta = -99;
  GMTCand_phi = -99;
  sim_st2_eta = -99;
  sim_st2_phi = -99;
  sim_prop_eta = -99;
  sim_prop_phi = -99;
  dR_prop_L1TrackMuon = -99;
  dR_st2_L1TrackMuon = -99;
  dR_L1Track = -99;
}


TTree* MyTrackEff::book(TTree *t, const std::string & name)
{
  edm::Service< TFileService > fs;
  t = fs->make<TTree>(name.c_str(), name.c_str());

  t->Branch("lumi", &lumi);
  t->Branch("run", &run);
  t->Branch("event", &event);
  t->Branch("rand01_v1", &rand01_v1);
  t->Branch("rand01_v2", &rand01_v2);

  t->Branch("pt", &pt);
  t->Branch("pz", &pz);
  t->Branch("eta", &eta);
  t->Branch("dxy", &dxy);
  t->Branch("phi", &phi);
  t->Branch("charge", &charge);
  t->Branch("endcap", &endcap);
  t->Branch("pdgid", &pdgid);

  t->Branch("genGd_m",   &genGd_m,   "genGd_m/F");
  t->Branch("genGd_E",   &genGd_E,   "genGd_E/F");
  t->Branch("genGd_p",   &genGd_p,   "genGd_p/F");
  t->Branch("genGd_pt",  &genGd_pt,  "genGd_pt/F");
  t->Branch("genGd_px",  &genGd_px,  "genGd_px/F");
  t->Branch("genGd_py",  &genGd_py,  "genGd_py/F");
  t->Branch("genGd_pz",  &genGd_pz,  "genGd_pz/F");
  t->Branch("genGd_eta", &genGd_eta, "genGd_eta/F");
  t->Branch("genGd_phi", &genGd_phi, "genGd_phi/F");
  t->Branch("genGd_vx",  &genGd_vx,  "genGd_vx/F");
  t->Branch("genGd_vy",  &genGd_vy,  "genGd_vy/F");
  t->Branch("genGd_vz",  &genGd_vz,  "genGd_vz/F");
  t->Branch("genGd_vLx",  &genGd_vLx,  "genGd_vLx/F");
  t->Branch("genGd_vLy",  &genGd_vLy,  "genGd_vLy/F");
  t->Branch("genGd_vLz",  &genGd_vLz,  "genGd_vLz/F");
  t->Branch("genGd_lxy",  &genGd_lxy,  "genGd_lxy/F");
  t->Branch("genGd_l",  &genGd_l,  "genGd_l/F");
  t->Branch("genGd_dxy",  &genGd_dxy,  "genGd_dxy/F");
  t->Branch("genGd0Gd1_dR",  &genGd0Gd1_dR,  "genGd0Gd1_dR/F");
  t->Branch("genGd0Gd1_m",  &genGd0Gd1_m,  "genGd0Gd1_m/F");
  t->Branch("genGdMu_dxy_max",  &genGdMu_dxy_max,  "genGdMu_dxy_max/F");
  t->Branch("genGdMu_eta_max",  &genGdMu_eta_max,  "genGdMu_eta_max/F");

  t->Branch("genGd_index", &genGd_index, "genGd_index/F");
  t->Branch("genGdMu_index", &genGdMu_index, "genGdMu_index/F");
  t->Branch("genGdMu_p", &genGdMu_p, "genGdMu_p/F");
  t->Branch("genGdMu_pt", &genGdMu_pt, "genGdMu_pt/F");
  t->Branch("genGdMu_px", &genGdMu_px, "genGdMu_px/F");
  t->Branch("genGdMu_py", &genGdMu_py, "genGdMu_py/F");
  t->Branch("genGdMu_pz", &genGdMu_pz, "genGdMu_pz/F");
  t->Branch("genGdMu_eta",& genGdMu_eta, "genGdMu_eta/F");
  t->Branch("genGdMu_phi", &genGdMu_phi, "genGdMu_phi/F");
  t->Branch("genGdMu_phi_corr", &genGdMu_phi_corr, "genGdMu_phi_corr/F");
  t->Branch("genGdMu_vx", &genGdMu_vx, "genGdMu_vx/F");
  t->Branch("genGdMu_vy", &genGdMu_vy, "genGdMu_vy/F");
  t->Branch("genGdMu_vz", &genGdMu_vz, "genGdMu_vz/F");
  t->Branch("genGdMu_dxy", &genGdMu_dxy, "genGdMu_dxy/F");
  t->Branch("genGdMu_lxy", &genGdMu_lxy, "genGdMu_lxy/F");
  t->Branch("genGdMu_dR", &genGdMu_dR, "genGdMu_dR/F");


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
  t->Branch("phi_layer1_sh_even", &phi_layer1_sh_even);
  t->Branch("phi_layer1_sh_odd", &phi_layer1_sh_odd);
  t->Branch("eta_layer1_sh_even", &eta_layer1_sh_even);
  t->Branch("eta_layer1_sh_odd", &eta_layer1_sh_odd);
  t->Branch("perp_layer1_sh_even", &perp_layer1_sh_even);
  t->Branch("perp_layer1_sh_odd", &perp_layer1_sh_odd);
  t->Branch("z_layer1_sh_even", &z_layer1_sh_even);
  t->Branch("z_layer1_sh_odd", &z_layer1_sh_odd);
  t->Branch("phi_layer6_sh_even", &phi_layer6_sh_even);
  t->Branch("phi_layer6_sh_odd", &phi_layer6_sh_odd);
  t->Branch("eta_layer6_sh_even", &eta_layer6_sh_even);
  t->Branch("eta_layer6_sh_odd", &eta_layer6_sh_odd);
  t->Branch("perp_layer6_sh_even", &perp_layer6_sh_even);
  t->Branch("perp_layer6_sh_odd", &perp_layer6_sh_odd);
  t->Branch("z_layer6_sh_even", &z_layer6_sh_even);
  t->Branch("z_layer6_sh_odd", &z_layer6_sh_odd);
  t->Branch("eta_cscsh_even", &eta_cscsh_even);
  t->Branch("eta_cscsh_odd", &eta_cscsh_odd);
  t->Branch("pt_sh_even", &pt_sh_even);
  t->Branch("pteta_sh_even", &pteta_sh_even);
  t->Branch("ptphi_sh_even", &ptphi_sh_even);
  t->Branch("pt_sh_odd", &pt_sh_odd);
  t->Branch("pteta_sh_odd", &pteta_sh_odd);
  t->Branch("ptphi_sh_odd", &ptphi_sh_odd);

  t->Branch("chamber_dg_odd", &chamber_dg_odd);
  t->Branch("chamber_dg_even", &chamber_dg_even);
  t->Branch("has_csc_sh", &has_csc_sh);
  t->Branch("has_csc_strips", &has_csc_strips);
  t->Branch("has_csc_wires", &has_csc_wires);
  t->Branch("has_rechits", &has_rechits);
  t->Branch("nlayers_wg_dg_odd", &nlayers_wg_dg_odd);
  t->Branch("nlayers_wg_dg_even", &nlayers_wg_dg_even);
  t->Branch("nlayers_st_dg_odd", &nlayers_st_dg_odd);
  t->Branch("nlayers_st_dg_even", &nlayers_st_dg_even);
  t->Branch("nlayers_rechits_odd", &nlayers_rechits_odd);
  t->Branch("nlayers_rechits_even", &nlayers_rechits_even);


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
  t->Branch("phi_me0_st2_odd", &phi_me0_st2_odd);
  t->Branch("phi_me0_st2_even", &phi_me0_st2_even);
  t->Branch("eta_me0_st2_odd", &eta_me0_st2_odd);
  t->Branch("eta_me0_st2_even", &eta_me0_st2_even);
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
  t->Branch("me0_st1_dphi_odd", &me0_st1_dphi_odd);
  t->Branch("me0_st1_dphi_even", &me0_st1_dphi_even);
  t->Branch("me0_st1_isEven_odd", &me0_st1_isEven_odd);
  t->Branch("me0_st1_isEven_even", &me0_st1_isEven_even);
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
  t->Branch("dphipositionpt_gemsh_even", &dphipositionpt_gemsh_even);
  t->Branch("dphipositionpt_gemsh_odd", &dphipositionpt_gemsh_odd);
  t->Branch("dphipositionpt_cscsh_even", &dphipositionpt_cscsh_even);
  t->Branch("dphipositionpt_cscsh_odd", &dphipositionpt_cscsh_odd);
  t->Branch("phiM_gemcsc_odd", &phiM_gemcsc_odd);
  t->Branch("phiM_gemcsc_even", &phiM_gemcsc_even);
  t->Branch("phiM_fitxyz_odd", &phiM_fitxyz_odd);
  t->Branch("phiM_fitxyz_even", &phiM_fitxyz_even);
  t->Branch("strip_gemdg_odd", &strip_gemdg_odd);
  t->Branch("strip_gemdg_even", &strip_gemdg_even);

  t->Branch("has_rpc_sh", &has_rpc_sh);
  t->Branch("has_rpc_dg", &has_rpc_dg);
  t->Branch("strip_rpcdg_odd", &strip_rpcdg_odd);
  t->Branch("strip_rpcdg_even", &strip_rpcdg_even);
  t->Branch("hsfromrpc_odd", &hsfromrpc_odd);
  t->Branch("hsfromrpc_even", &hsfromrpc_even);

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

  t->Branch("phi_1strippad_odd", &phi_1strippad_odd);
  t->Branch("phi_1strippad_even", &phi_1strippad_even);
  t->Branch("phi_2strippad_odd", &phi_2strippad_odd);
  t->Branch("phi_2strippad_even", &phi_2strippad_even);
  t->Branch("phi_4strippad_odd", &phi_4strippad_odd);
  t->Branch("phi_4strippad_even", &phi_4strippad_even);
  t->Branch("phi_8strippad_odd", &phi_8strippad_odd);
  t->Branch("phi_8strippad_even", &phi_8strippad_even);
  t->Branch("dphi_1strippad_odd", &dphi_1strippad_odd);
  t->Branch("dphi_1strippad_even", &dphi_1strippad_even);
  t->Branch("dphi_2strippad_odd", &dphi_2strippad_odd);
  t->Branch("dphi_2strippad_even", &dphi_2strippad_even);
  t->Branch("dphi_4strippad_odd", &dphi_4strippad_odd);
  t->Branch("dphi_4strippad_even", &dphi_4strippad_even);
  t->Branch("dphi_8strippad_odd", &dphi_8strippad_odd);
  t->Branch("dphi_8strippad_even", &dphi_8strippad_even);
  t->Branch("dphi_1strippad_fit_odd", &dphi_1strippad_fit_odd);
  t->Branch("dphi_1strippad_fit_even", &dphi_1strippad_fit_even);
  t->Branch("dphi_2strippad_fit_odd", &dphi_2strippad_fit_odd);
  t->Branch("dphi_2strippad_fit_even", &dphi_2strippad_fit_even);
  t->Branch("dphi_4strippad_fit_odd", &dphi_4strippad_fit_odd);
  t->Branch("dphi_4strippad_fit_even", &dphi_4strippad_fit_even);
  t->Branch("dphi_8strippad_fit_odd", &dphi_8strippad_fit_odd);
  t->Branch("dphi_8strippad_fit_even", &dphi_8strippad_fit_even);

  t->Branch("bx_rpcstrip_odd", &bx_rpcstrip_odd);
  t->Branch("bx_rpcstrip_even", &bx_rpcstrip_even);
  t->Branch("phi_rpcstrip_odd", &phi_rpcstrip_odd);
  t->Branch("phi_rpcstrip_even", &phi_rpcstrip_even);
  t->Branch("eta_rpcstrip_odd", &eta_rpcstrip_odd);
  t->Branch("eta_rpcstrip_even", &eta_rpcstrip_even);
  t->Branch("dphi_rpcstrip_odd", &dphi_rpcstrip_odd);
  t->Branch("dphi_rpcstrip_even", &dphi_rpcstrip_even);
  t->Branch("deta_rpcstrip_odd", &deta_rpcstrip_odd);
  t->Branch("deta_rpcstrip_even", &deta_rpcstrip_even);

  //t->Branch("", &);
  t->Branch("has_tfTrack", &has_tfTrack);
  t->Branch("has_tfCand", &has_tfCand);
  t->Branch("has_gmtRegCand", &has_gmtRegCand);
  t->Branch("has_gmtCand", &has_gmtCand);

  //csctftrack
  t->Branch("trackpt", &trackpt);
  t->Branch("tracketa", &tracketa);
  t->Branch("trackphi", &trackphi);
  t->Branch("quality_packed",&quality_packed);
  t->Branch("rank",&rank);
  t->Branch("pt_packed",&pt_packed);
  t->Branch("eta_packed",&eta_packed);
  t->Branch("phi_packed",&phi_packed);
  t->Branch("chargesign",&chargesign);
  t->Branch("deltaphi12",&deltaphi12);
  t->Branch("deltaphi23",&deltaphi23);
  t->Branch("hasME1",&hasME1);
  t->Branch("hasME2",&hasME2);
  t->Branch("hasME3",&hasME3);
  t->Branch("hasME4",&hasME4);
  t->Branch("ME1_ring",&ME1_ring);
  t->Branch("ME2_ring",&ME2_ring);
  t->Branch("chamberME1",&chamberME1);
  t->Branch("chamberME2",&chamberME2);
  t->Branch("ME1_hs",&ME1_hs);
  t->Branch("ME1_wg",&ME1_wg);
  t->Branch("ME2_hs",&ME2_hs);
  t->Branch("ME2_wg",&ME2_wg);
  t->Branch("dphiGE11",&dphiGE11);
  t->Branch("dphiGE21",&dphiGE21);
  t->Branch("passGE11",&passGE11);
  t->Branch("passGE11_pt5",&passGE11_pt5);
  t->Branch("passGE11_pt7",&passGE11_pt7);
  t->Branch("passGE11_pt10",&passGE11_pt10);
  t->Branch("passGE11_pt15",&passGE11_pt15);
  t->Branch("passGE11_pt20",&passGE11_pt20);
  t->Branch("passGE11_pt30",&passGE11_pt30);
  t->Branch("passGE11_pt40",&passGE11_pt40);
  t->Branch("passGE21",&passGE21);
  t->Branch("passGE21_pt5",&passGE21_pt5);
  t->Branch("passGE21_pt7",&passGE21_pt7);
  t->Branch("passGE21_pt10",&passGE21_pt10);
  t->Branch("passGE21_pt15",&passGE21_pt15);
  t->Branch("passGE21_pt20",&passGE21_pt20);
  t->Branch("passGE21_pt30",&passGE21_pt30);
  t->Branch("passGE21_pt40",&passGE21_pt40);
  t->Branch("passGE11_simpt",&passGE11_simpt);
  t->Branch("passGE21_simpt",&passGE21_simpt);
  t->Branch("nstubs",&nstubs);
  t->Branch("deltaR",&deltaR);
  t->Branch("lctdphi12",&lctdphi12);

  /*
  t->Branch("eta_propagated_ME1",&eta_propagated_ME1);
  t->Branch("eta_propagated_ME2",&eta_propagated_ME2);
  t->Branch("eta_propagated_ME3",&eta_propagated_ME3);
  t->Branch("eta_propagated_ME4",&eta_propagated_ME4);
  t->Branch("phi_propagated_ME1",&phi_propagated_ME1);
  t->Branch("phi_propagated_ME2",&phi_propagated_ME2);
  t->Branch("phi_propagated_ME3",&phi_propagated_ME3);
  t->Branch("phi_propagated_ME4",&phi_propagated_ME4);
  t->Branch("eta_ME1_TF",&eta_ME1_TF);
  t->Branch("eta_ME2_TF",&eta_ME2_TF);
  t->Branch("eta_ME3_TF",&eta_ME3_TF);
  t->Branch("eta_ME4_TF",&eta_ME4_TF);
  t->Branch("phi_ME1_TF",&phi_ME1_TF);
  t->Branch("phi_ME2_TF",&phi_ME2_TF);
  t->Branch("phi_ME3_TF",&phi_ME3_TF);
  t->Branch("phi_ME4_TF",&phi_ME4_TF);

  t->Branch("eta_interStat12",&eta_interStat12);
  t->Branch("phi_interStat12",&phi_interStat12);
  t->Branch("eta_interStat23",&eta_interStat23);
  t->Branch("phi_interStat23",&phi_interStat23);
  t->Branch("eta_interStat13",&eta_interStat13);
  t->Branch("phi_interStat13",&phi_interStat13);
  */

  t->Branch("allstubs_matched_TF",&allstubs_matched_TF);

  t->Branch("bestdRGmtCand", &bestdRGmtCand);
  t->Branch("L1Mu_pt", &L1Mu_pt);
  t->Branch("L1Mu_eta", &L1Mu_eta);
  t->Branch("L1Mu_phi", &L1Mu_phi);
  t->Branch("L1Mu_quality", &L1Mu_quality);
  t->Branch("L1Mu_bx", &L1Mu_bx);
  t->Branch("L1Mu_charge", &L1Mu_charge);
  t->Branch("L1Mu_me0_eta", &L1Mu_me0_eta);
  t->Branch("L1Mu_me0_phi", &L1Mu_me0_phi);
  t->Branch("L1Mu_me0_st2_eta", &L1Mu_me0_st2_eta);
  t->Branch("L1Mu_me0_st2_phi", &L1Mu_me0_st2_phi);
  t->Branch("L1Mu_me0_dPhi", &L1Mu_me0_dPhi);
  t->Branch("L1Mu_me0_dR", &L1Mu_me0_dR);
  t->Branch("L1Mu_me0_mindPhi1", &L1Mu_me0_mindPhi1);
  t->Branch("L1Mu_me0_mindPhi2", &L1Mu_me0_mindPhi2);
  t->Branch("L1Mu_me0_st1_dphi", &L1Mu_me0_st1_dphi);
  t->Branch("L1Mu_me0_st1_isEven", &L1Mu_me0_st1_isEven);

  t->Branch("L1Mu_st1_eta", &L1Mu_st1_eta);
  t->Branch("L1Mu_st1_phi", &L1Mu_st1_phi);
  t->Branch("L1Mu_st1_dR", &L1Mu_st1_dR);
  t->Branch("L1Mu_st1_isEven", &L1Mu_st1_isEven);


  t->Branch("has_l1Extra", &has_l1Extra);
  t->Branch("l1Extra_pt", &l1Extra_pt);
  t->Branch("l1Extra_eta", &l1Extra_eta);
  t->Branch("l1Extra_phi", &l1Extra_phi);
  t->Branch("l1Extra_dR", &l1Extra_dR);
  t->Branch("has_recoTrackExtra", &has_recoTrackExtra);
  t->Branch("recoTrackExtra_pt_inner", &recoTrackExtra_pt_inner);
  t->Branch("recoTrackExtra_eta_inner", &recoTrackExtra_eta_inner);
  t->Branch("recoTrackExtra_phi_inner", &recoTrackExtra_phi_inner);
  t->Branch("recoTrackExtra_pt_outer", &recoTrackExtra_pt_outer);
  t->Branch("recoTrackExtra_eta_outer", &recoTrackExtra_eta_outer);
  t->Branch("recoTrackExtra_phi_outer", &recoTrackExtra_phi_outer);
  t->Branch("has_recoTrack", &has_recoTrack);
  t->Branch("recoTrack_pt_outer", &recoTrack_pt_outer);
  t->Branch("recoTrack_eta_outer", &recoTrack_eta_outer);
  t->Branch("recoTrack_phi_outer", &recoTrack_phi_outer);
  t->Branch("has_recoChargedCandidate", &has_recoChargedCandidate);
  t->Branch("recoChargedCandidate_pt", &recoChargedCandidate_pt);
  t->Branch("recoChargedCandidate_eta", &recoChargedCandidate_eta);
  t->Branch("recoChargedCandidate_phi", &recoChargedCandidate_phi);

  t->Branch("recoChargedCandidate_nValidDTHits", &recoChargedCandidate_nValidDTHits);
  t->Branch("recoChargedCandidate_nValidCSCHits", &recoChargedCandidate_nValidCSCHits);
  t->Branch("recoChargedCandidate_nValidRPCHits", &recoChargedCandidate_nValidRPCHits);


  t->Branch("meRing", &meRing);
  t->Branch("npar", &npar);
  t->Branch("npar_L1", &npar_L1);
  t->Branch("npar_sim", &npar_sim);
  t->Branch("eta_st2_sim", &eta_st2_sim);
  t->Branch("eta_st1_sim", &eta_st1_sim);
  t->Branch("eta_st2_L1", &eta_st2_L1);
  t->Branch("eta_st1_L1", &eta_st1_L1);
  t->Branch("eta_st2_sh", &eta_st2_sh);
  t->Branch("isMe0Region", &isMe0Region);
  t->Branch("ptphi_gemsh_even", &ptphi_gemsh_even);
  t->Branch("ptphi_gemsh_odd", &ptphi_gemsh_odd);
  t->Branch("ptphi_diff_sh", &ptphi_diff_sh);
  t->Branch("phiM_st1_sh", &phiM_st1_sh);
  t->Branch("phiM_st2_sh", &phiM_st2_sh);
  t->Branch("phiM_st12_sh", &phiM_st12_sh);
  t->Branch("phiM_st23_sh", &phiM_st23_sh);
  t->Branch("phiM_st12_L1", &phiM_st12_L1);
  t->Branch("phiM_st23_L1", &phiM_st23_L1);
  t->Branch("phiM_st1_L1", &phiM_st1_L1);
  t->Branch("phiM_st2_L1", &phiM_st2_L1);
  t->Branch("phiM_GE11_L1", &phiM_GE11_L1);
  t->Branch("phiM_ME0_L1", &phiM_ME0_L1);
  t->Branch("phiM_ME11only_L1", &phiM_ME11only_L1);
  t->Branch("phiM_ME21only_L1", &phiM_ME21only_L1);
  t->Branch("dphi_dir_st1_st2_sh", &dphi_dir_st1_st2_sh);
  t->Branch("dphi_dir_st1_st2_L1", &dphi_dir_st1_st2_L1);
  t->Branch("dphi_dir_GE11_st2_L1", &dphi_dir_GE11_st2_L1);
  t->Branch("dphi_dir_ME0_st2_L1", &dphi_dir_ME0_st2_L1);
  t->Branch("dphi_dir_st1_st2_L1_csc", &dphi_dir_st1_st2_L1_csc);
  t->Branch("dphi_dir_ME11only_st2_L1", &dphi_dir_ME11only_st2_L1);
  t->Branch("dphi_dir_st1_ME21only_L1", &dphi_dir_st1_ME21only_L1);
  t->Branch("dphi_dir_ME11only_ME21only_L1", &dphi_dir_ME11only_ME21only_L1);
  t->Branch("dphi_dir_st1_st12_sh", &dphi_dir_st1_st12_sh);
  t->Branch("dphi_dir_st12_st23_sh", &dphi_dir_st12_st23_sh);
  t->Branch("dphi_dir_st2_st23_sh", &dphi_dir_st2_st23_sh);
  t->Branch("dphi_dir_st1_st12_L1", &dphi_dir_st1_st12_L1);
  t->Branch("dphi_dir_st2_st23_L1", &dphi_dir_st2_st23_L1);
  t->Branch("dphi_dir_st12_st23_L1", &dphi_dir_st12_st23_L1);
  t->Branch("dphi_dir_st1_st12_L1_csc", &dphi_dir_st1_st12_L1_csc);
  t->Branch("dphi_dir_st2_st23_L1_csc", &dphi_dir_st2_st23_L1_csc);
  t->Branch("position_pt", &position_pt);
  t->Branch("direction_noge21_pt", &direction_noge21_pt);
  t->Branch("direction_ge21_pt", &direction_ge21_pt);
  t->Branch("hybrid_pt", &hybrid_pt);
  t->Branch("hybrid_noge21_pt", &hybrid_noge21_pt);
  t->Branch("deltay12_sim", &deltay12_sim);
  t->Branch("deltay23_sim", &deltay23_sim);
  t->Branch("deltay12_fit", &deltay12_fit);
  t->Branch("deltay23_fit", &deltay23_fit);
  t->Branch("deltay12_lct", &deltay12_lct);
  t->Branch("deltay23_lct", &deltay23_lct);
  t->Branch("deltay12_test", &deltay12_test);
  t->Branch("deltay23_test", &deltay23_test);
  t->Branch("deltay123_test", &deltay123_test);
  t->Branch("npar_lct", &npar_lct);
  t->Branch("pt_position_sh", &pt_position_sh);
  t->Branch("pt_position", &pt_position);
  t->Branch("pt_position_fit", &pt_position_fit);
  t->Branch("pt_direction_sh", &pt_direction_sh);
  t->Branch("pt_direction_gemcsc", &pt_direction_gemcsc);
  t->Branch("hasSt1St2St3", &hasSt1St2St3);
  t->Branch("hasSt3orSt4_sh", &hasSt3orSt4_sh);

  // track trigger veto
  t->Branch("isSimLooseVeto", &isSimLooseVeto);
  t->Branch("isSimMediumVeto", &isSimMediumVeto);
  t->Branch("isSimTightVeto", &isSimTightVeto);
  t->Branch("isL1LooseVeto", &isL1LooseVeto);
  t->Branch("isL1MediumVeto", &isL1MediumVeto);
  t->Branch("isL1TightVeto", &isL1TightVeto);
  t->Branch("nTrackTriggers", &nTrackTriggers);

  t->Branch("L1Track_eta", &L1Track_eta);
  t->Branch("L1Track_phi", &L1Track_phi);
  t->Branch("L1TrackMuon_eta", &L1TrackMuon_eta);
  t->Branch("L1TrackMuon_phi", &L1TrackMuon_phi);
  t->Branch("GMTCand_eta", &GMTCand_eta);
  t->Branch("GMTCand_phi", &GMTCand_phi);
  t->Branch("sim_st2_eta", &sim_st2_eta);
  t->Branch("sim_st2_phi", &sim_st2_phi);
  t->Branch("sim_prop_eta", &sim_prop_eta);
  t->Branch("sim_prop_phi", &sim_prop_phi);
  t->Branch("dR_prop_L1TrackMuon", &dR_prop_L1TrackMuon);
  t->Branch("dR_st2_L1TrackMuon", &dR_st2_L1TrackMuon);
  t->Branch("dR_L1Track", &dR_L1Track);

  return t;
}

}

#endif
