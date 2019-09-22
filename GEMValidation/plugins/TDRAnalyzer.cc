#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/MuonDetId/interface/CSCTriggerNumbering.h"

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"

#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"
#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/PtassignmentHelper.h"
#include "GEMCode/GEMValidation/interface/DisplacedMuonTriggerPtassignment.h"
#include "GEMCode/GEMValidation/interface/L1TrackTriggerVeto.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/Randomize.h"

#include "TTree.h"

#include <iomanip>
#include <sstream>
#include <memory>
#include <math.h>
#include <bitset>
#include <vector>

using namespace std;
using namespace matching;

static const int NumOfTrees = 13;
// "signed" LCT bend pattern
const int LCT_BEND_PATTERN[11] = { -99,  -5,  4, -4,  3, -3,  2, -2,  1, -1,  0};

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


  Int_t quality_odd;
  Int_t quality_even;

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

  lct_type = -1;

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

// --------------------------- TDRAnalyzer ---------------------------

class TDRAnalyzer : public edm::EDAnalyzer
{
public:

  explicit TDRAnalyzer(const edm::ParameterSet&);

  ~TDRAnalyzer() {}

  virtual void beginRun(const edm::Run&, const edm::EventSetup&);

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  enum {ME0=12};


private:
  int ievent;

  void analyzeTrackEff(SimTrackMatchManager& match, int trk_no);

  bool isSimTrackGood(const SimTrack &t);
  int detIdToMEStation(int st, int ri);

  edm::ParameterSet cfg_;
  edm::ParameterSet displacedMuPt_cfg_;

  edm::EDGetTokenT<reco::GenParticleCollection> genParticleInput_;
  edm::EDGetTokenT<edm::SimVertexContainer> simVertexInput_;
  edm::EDGetTokenT<edm::SimTrackContainer> simTrackInput_;

  edm::EDGetTokenT<edm::PSimHitContainer> gemSimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> cscSimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> rpcSimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> me0SimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> dtSimHitInput_;

  edm::EDGetTokenT<GEMDigiCollection> gemDigiInput_;
  edm::EDGetTokenT<GEMPadDigiCollection> gemPadDigiInput_;
  edm::EDGetTokenT<GEMCoPadDigiCollection> gemCoPadDigiInput_;
  edm::EDGetTokenT<GEMRecHitCollection> gemRecHitInput_;

  edm::EDGetTokenT<ME0DigiPreRecoCollection> me0DigiInput_;
  edm::EDGetTokenT<ME0RecHitCollection> me0RecHitInput_;
  edm::EDGetTokenT<ME0SegmentCollection> me0SegmentInput_;

  edm::EDGetTokenT<CSCComparatorDigiCollection> cscComparatorDigiInput_;
  edm::EDGetTokenT<CSCWireDigiCollection> cscWireDigiInput_;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clctInputs_;
  edm::EDGetTokenT<CSCALCTDigiCollection> alctInputs_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lctInputs_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> mplctInputs_;
  edm::EDGetTokenT<CSCRecHit2DCollection> cscRecHit2DInput_;
  edm::EDGetTokenT<CSCSegmentCollection> cscSegmentInput_;

  edm::EDGetTokenT<DTDigiCollection> dtDigiInput_;
  edm::EDGetTokenT<DTLocalTriggerCollection> dtStubInput_;
  edm::EDGetTokenT<DTRecHitCollection> dtRecHit1DPairInput_;
  edm::EDGetTokenT<DTRecSegment2DCollection> dtRecSegment2DInput_;
  edm::EDGetTokenT<DTRecSegment4DCollection> dtRecSegment4DInput_;

  edm::EDGetTokenT<RPCDigiCollection> rpcDigiInput_;
  edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitInput_;

  edm::EDGetTokenT<l1t::EMTFTrackCollection> emtfTrackInputLabel_;
  edm::EDGetTokenT<BXVector<l1t::RegionalMuonCand>> regMuonCandInputLabel_;
  edm::EDGetTokenT<BXVector<l1t::Muon>> gmtInputLabel_;

  //edm::EDGetTokenT<L1TTTrackCollectionType> trackInputLabel_;
  //edm::EDGetTokenT<l1t::L1TkMuonParticleCollection> trackMuonInputLabel_;

  edm::EDGetTokenT<reco::TrackExtraCollection> recoTrackExtraInputLabel_;
  edm::EDGetTokenT<reco::TrackCollection> recoTrackInputLabel_;
  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> recoChargedCandidateInputLabel_;


  int verboseSimTrack_;
  int verboseL1Track_;
  double simTrackMinPt_;
  double simTrackMinEta_;
  double simTrackMaxEta_;
  double simTrackOnlyMuon_;
  int verbose_;
  bool ntupleTrackEff_;
  bool matchprint_;
  double bendingcutPt_;
  std::vector<string> cscStations_;
  std::vector<std::pair<int,int> > cscStationsCo_;
  std::set<int> stations_to_use_;

  TTree *tree_eff_[NumOfTrees];

  MyTrackEff  etrk_[NumOfTrees];

  int minNHitsChamberCSCSimHit_;
  int minNHitsChamberME0SimHit_;
  int minNHitsChamberCSCWireDigi_;
  int minNHitsChamberCSCStripDigi_;
  int minNHitsChamberME0Digi_;
  int minNHitsChamberME0RecHit_;
  int minNHitsChamberCLCT_;
  int minNHitsChamberALCT_;
  int minNHitsChamberLCT_;
  int minNHitsChamberMPLCT_;
};


TDRAnalyzer::TDRAnalyzer(const edm::ParameterSet& ps)
: cfg_(ps.getParameterSet("simTrackMatching"))
, verbose_(ps.getUntrackedParameter<int>("verbose", 0))
{
  ievent = 0;

  cscStations_ = cfg_.getParameter<std::vector<string> >("cscStations");
  ntupleTrackEff_ = cfg_.getParameter<bool>("ntupleTrackEff");
  //matchprint_ = false;
  matchprint_ =  cfg_.getParameter<bool>("matchprint");
  bendingcutPt_ = cfg_.getUntrackedParameter<double>("bendingcutPt",10);

  displacedMuPt_cfg_ = cfg_.getParameter<edm::ParameterSet>("displacedMuPtAssignment");

  const auto& displacedGenMu = cfg_.getParameter<edm::ParameterSet>("displacedGenMu");
  genParticleInput_ = consumes<reco::GenParticleCollection>(displacedGenMu.getParameter<edm::InputTag>("inputTag"));

  const auto& simVertex = cfg_.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("inputTag"));

  const auto& simTrack = cfg_.getParameter<edm::ParameterSet>("simTrack");
  verboseSimTrack_ = simTrack.getParameter<int>("verbose");
  simTrackInput_ = consumes<edm::SimTrackContainer>(simTrack.getParameter<edm::InputTag>("inputTag"));
  simTrackMinPt_ = simTrack.getParameter<double>("minPt");
  simTrackMinEta_ = simTrack.getParameter<double>("minEta");
  simTrackMaxEta_ = simTrack.getParameter<double>("maxEta");
  simTrackOnlyMuon_ = simTrack.getParameter<bool>("onlyMuon");

  const auto& gemSimHit_ = cfg_.getParameter<edm::ParameterSet>("gemSimHit");
  gemSimHitInput_ = consumes<edm::PSimHitContainer>(gemSimHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& cscSimHit_= cfg_.getParameter<edm::ParameterSet>("cscSimHit");
  cscSimHitInput_ = consumes<edm::PSimHitContainer>(cscSimHit_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberCSCSimHit_ = cscSimHit_.getParameter<int>("minNHitsChamber");

  const auto& me0SimHit_ = cfg_.getParameter<edm::ParameterSet>("me0SimHit");
  me0SimHitInput_ = consumes<edm::PSimHitContainer>(me0SimHit_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberME0SimHit_ = me0SimHit_.getParameter<int>("minNHitsChamber");

  const auto& rpcSimHit_ = cfg_.getParameter<edm::ParameterSet>("rpcSimHit");
  rpcSimHitInput_ = consumes<edm::PSimHitContainer>(rpcSimHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& dtSimHit_ = cfg_.getParameter<edm::ParameterSet>("dtSimHit");
  dtSimHitInput_ = consumes<edm::PSimHitContainer>(dtSimHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemDigi_= cfg_.getParameter<edm::ParameterSet>("gemStripDigi");
  gemDigiInput_ = consumes<GEMDigiCollection>(gemDigi_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemPad_= cfg_.getParameter<edm::ParameterSet>("gemPadDigi");
  gemPadDigiInput_ = consumes<GEMPadDigiCollection>(gemPad_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemCoPad_= cfg_.getParameter<edm::ParameterSet>("gemCoPadDigi");
  gemCoPadDigiInput_ = consumes<GEMCoPadDigiCollection>(gemCoPad_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemRecHit_= cfg_.getParameter<edm::ParameterSet>("gemRecHit");
  gemRecHitInput_ = consumes<GEMRecHitCollection>(gemRecHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& me0Digi_= cfg_.getParameter<edm::ParameterSet>("me0DigiPreReco");
  me0DigiInput_ = consumes<ME0DigiPreRecoCollection>(me0Digi_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberME0Digi_ =  me0Digi_.getParameter<int>("minNHitsChamber");

  const auto& me0RecHit_ = cfg_.getParameter<edm::ParameterSet>("me0RecHit");
  me0RecHitInput_ = consumes<ME0RecHitCollection>(me0RecHit_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberME0RecHit_ =  me0RecHit_.getParameter<int>("minNHitsChamber");

  const auto& me0Segment_ = cfg_.getParameter<edm::ParameterSet>("me0Segment");
  me0SegmentInput_ = consumes<ME0SegmentCollection>(me0Segment_.getParameter<edm::InputTag>("inputTag"));

  const auto& cscComparatorDigi = cfg_.getParameter<edm::ParameterSet>("cscStripDigi");
  minNHitsChamberCSCStripDigi_ = cscComparatorDigi.getParameter<int>("minNHitsChamber");
  cscComparatorDigiInput_ = consumes<CSCComparatorDigiCollection>(cscComparatorDigi.getParameter<edm::InputTag>("inputTag"));

  const auto& cscWireDigi = cfg_.getParameter<edm::ParameterSet>("cscWireDigi");
  minNHitsChamberCSCWireDigi_ = cscWireDigi.getParameter<int>("minNHitsChamber");
  cscWireDigiInput_ = consumes<CSCWireDigiCollection>(cscWireDigi.getParameter<edm::InputTag>("inputTag"));

  const auto& cscCLCT = cfg_.getParameter<edm::ParameterSet>("cscCLCT");
  minNHitsChamberCLCT_ = cscCLCT.getParameter<int>("minNHitsChamber");
  clctInputs_ = consumes<CSCCLCTDigiCollection>(cscCLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscALCT = cfg_.getParameter<edm::ParameterSet>("cscALCT");
  minNHitsChamberALCT_ = cscALCT.getParameter<int>("minNHitsChamber");
  alctInputs_ = consumes<CSCALCTDigiCollection>(cscALCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscLCT = cfg_.getParameter<edm::ParameterSet>("cscLCT");
  minNHitsChamberLCT_ = cscLCT.getParameter<int>("minNHitsChamber");
  lctInputs_ = consumes<CSCCorrelatedLCTDigiCollection>(cscLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscMPLCT = cfg_.getParameter<edm::ParameterSet>("cscMPLCT");
  minNHitsChamberMPLCT_ = cscMPLCT.getParameter<int>("minNHitsChamber");
  mplctInputs_ = consumes<CSCCorrelatedLCTDigiCollection>(cscMPLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscRecHit2D = cfg_.getParameter<edm::ParameterSet>("cscRecHit");
  cscRecHit2DInput_ = consumes<CSCRecHit2DCollection>(cscRecHit2D.getParameter<edm::InputTag>("inputTag"));

  const auto& cscSegment2D = cfg_.getParameter<edm::ParameterSet>("cscSegment");
  cscSegmentInput_ = consumes<CSCSegmentCollection>(cscSegment2D.getParameter<edm::InputTag>("inputTag"));

  const auto& dtDigi_= cfg_.getParameter<edm::ParameterSet>("dtDigi");
  dtDigiInput_ = consumes<DTDigiCollection>(dtDigi_.getParameter<edm::InputTag>("inputTag"));

  const auto& dtStub_= cfg_.getParameter<edm::ParameterSet>("dtLocalTrigger");
  dtStubInput_ = consumes<DTLocalTriggerCollection>(dtStub_.getParameter<edm::InputTag>("inputTag"));

  const auto& dtRecHit1DPair = cfg_.getParameter<edm::ParameterSet>("dtRecHit");
  dtRecHit1DPairInput_ = consumes<DTRecHitCollection>(dtRecHit1DPair.getParameter<edm::InputTag>("inputTag"));

  const auto& dtSegment2D = cfg_.getParameter<edm::ParameterSet>("dtRecSegment2D");
  dtRecSegment2DInput_ = consumes<DTRecSegment2DCollection>(dtSegment2D.getParameter<edm::InputTag>("inputTag"));

  const auto& dtSegment4D = cfg_.getParameter<edm::ParameterSet>("dtRecSegment4D");
  dtRecSegment4DInput_ = consumes<DTRecSegment4DCollection>(dtSegment4D.getParameter<edm::InputTag>("inputTag"));

  const auto& rpcDigi_= cfg_.getParameter<edm::ParameterSet>("rpcStripDigi");
  rpcDigiInput_ = consumes<RPCDigiCollection>(rpcDigi_.getParameter<edm::InputTag>("inputTag"));

  const auto& rpcRecHit_= cfg_.getParameter<edm::ParameterSet>("rpcRecHit");
  rpcRecHitInput_ = consumes<RPCRecHitCollection>(rpcRecHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& emtfTrack = cfg_.getParameter<edm::ParameterSet>("upgradeEmtfTrack");
  emtfTrackInputLabel_ = consumes<l1t::EMTFTrackCollection>(emtfTrack.getParameter<edm::InputTag>("inputTag"));

  const auto& upgradeemtfCand = cfg_.getParameter<edm::ParameterSet>("upgradeEmtfCand");
  regMuonCandInputLabel_ = consumes< BXVector<l1t::RegionalMuonCand> >(upgradeemtfCand.getParameter<edm::InputTag>("inputTag"));

  const auto& upgradegmt = cfg_.getParameter<edm::ParameterSet>("upgradeGMT");
  gmtInputLabel_ = consumes< BXVector<l1t::Muon> >(upgradegmt.getParameter<edm::InputTag>("inputTag"));

  //const auto& l1Track = cfg_.getParameter<edm::ParameterSet>("l1track");
  //trackInputLabel_ = consumes<L1TTTrackCollectionType>(l1Track.getParameter<edm::InputTag>("inputTag"));
  //verboseL1Track_ = l1Track.getParameter<int>("verbose");

  //const auto& l1TrackMuon = cfg_.getParameter<edm::ParameterSet>("l1tkmuon");
  //trackMuonInputLabel_ = consumes<l1t::L1TkMuonParticleCollection>(l1TrackMuon.getParameter<edm::InputTag>("inputTag"));

  const auto& recoTrackExtra = cfg_.getParameter<edm::ParameterSet>("recoTrackExtra");
  recoTrackExtraInputLabel_ = consumes<reco::TrackExtraCollection>(recoTrackExtra.getParameter<edm::InputTag>("inputTag"));

  const auto& recoTrack = cfg_.getParameter<edm::ParameterSet>("recoTrack");
  recoTrackInputLabel_ = consumes<reco::TrackCollection>(recoTrack.getParameter<edm::InputTag>("inputTag"));

  const auto& recoChargedCandidate = cfg_.getParameter<edm::ParameterSet>("recoChargedCandidate");
  recoChargedCandidateInputLabel_ = consumes<reco::RecoChargedCandidateCollection>(recoChargedCandidate.getParameter<edm::InputTag>("inputTag"));


  if (ntupleTrackEff_)
  {
    vector<int> stations = cfg_.getParameter<vector<int> >("cscStationsToUse");
    copy(stations.begin(), stations.end(), inserter(stations_to_use_, stations_to_use_.end()) );

    for(const auto& s: stations_to_use_)
    {
      stringstream ss;
      ss << "trk_eff_"<< cscStations_[s];
      std::cout <<"station to use "<< cscStations_[s]  << std::endl;
      tree_eff_[s] = etrk_[s].book(tree_eff_[s], ss.str());
    }
  }

  cscStationsCo_.push_back(std::make_pair(-99,-99));
  cscStationsCo_.push_back(std::make_pair(1,-99));
  cscStationsCo_.push_back(std::make_pair(1,4));
  cscStationsCo_.push_back(std::make_pair(1,1));
  cscStationsCo_.push_back(std::make_pair(1,2));
  cscStationsCo_.push_back(std::make_pair(1,3));
  cscStationsCo_.push_back(std::make_pair(2,1));
  cscStationsCo_.push_back(std::make_pair(2,2));
  cscStationsCo_.push_back(std::make_pair(3,1));
  cscStationsCo_.push_back(std::make_pair(3,2));
  cscStationsCo_.push_back(std::make_pair(4,1));
  cscStationsCo_.push_back(std::make_pair(4,2));
  cscStationsCo_.push_back(std::make_pair(0,1));
}


int TDRAnalyzer::detIdToMEStation(int st, int ri)
{
  const auto& p(std::make_pair(st, ri));
  return std::find(cscStationsCo_.begin(), cscStationsCo_.end(), p) - cscStationsCo_.begin();
}


void TDRAnalyzer::beginRun(const edm::Run &iRun, const edm::EventSetup &iSetup)
{
}


bool TDRAnalyzer::isSimTrackGood(const SimTrack &t)
{
  // SimTrack selection
  if (t.noVertex()) return false;
  if (t.noGenpart()) return false;
  // only muons
  if (std::abs(t.type()) != 13 and simTrackOnlyMuon_) return false;
  // pt selection
  if (t.momentum().pt() < simTrackMinPt_) return false;
  // eta selection
  const float eta(std::abs(t.momentum().eta()));
  if (eta > simTrackMaxEta_ || eta < simTrackMinEta_) return false;
  return true;
}


void TDRAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  ievent ++;
  edm::Handle<edm::SimTrackContainer> sim_tracks;
  ev.getByToken(simTrackInput_, sim_tracks);
  const edm::SimTrackContainer & sim_track = *sim_tracks.product();

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  ev.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer & sim_vert = *sim_vertices.product();

  if (verboseSimTrack_){
    std::cout << "Total number of SimTrack in this event: " << sim_track.size() << std::endl;
  }

  int trk_no=0;
  for (const auto& t: sim_track)
  {
    if (!isSimTrackGood(t)) continue;
    if (verboseSimTrack_){
      std::cout << "Processing SimTrack " << trk_no + 1 << std::endl;
      std::cout << "pt(GeV/c) = " << t.momentum().pt() << ", eta = " << t.momentum().eta()
                << ", phi = " << t.momentum().phi() << ", Q = " << t.charge() << std::endl;
    }

    SimTrackMatchManager match(t, sim_vert[t.vertIndex()], cfg_, ev, es,
                               genParticleInput_,
                               simVertexInput_,
                               simTrackInput_,
                               gemSimHitInput_,
                               cscSimHitInput_,
                               rpcSimHitInput_,
                               me0SimHitInput_,
                               dtSimHitInput_,
                               gemDigiInput_,
                               gemPadDigiInput_,
                               gemCoPadDigiInput_,
                               gemRecHitInput_,
                               me0DigiInput_,
                               me0RecHitInput_,
                               me0SegmentInput_,
                               cscComparatorDigiInput_,
                               cscWireDigiInput_,
                               clctInputs_,
                               alctInputs_,
                               lctInputs_,
                               mplctInputs_,
                               cscRecHit2DInput_,
                               cscSegmentInput_,
                               dtDigiInput_,
                               dtStubInput_,
                               dtRecHit1DPairInput_,
                               dtRecSegment2DInput_,
                               dtRecSegment4DInput_,
                               rpcDigiInput_,
                               rpcRecHitInput_,
                               emtfTrackInputLabel_,
                               regMuonCandInputLabel_,
                               gmtInputLabel_,
                               //trackInputLabel_,
                               //trackMuonInputLabel_,
                               recoTrackExtraInputLabel_,
                               recoTrackInputLabel_,
                               recoChargedCandidateInputLabel_
			       );

    if (ntupleTrackEff_) analyzeTrackEff(match, trk_no);
    ++trk_no;
  }
}



void TDRAnalyzer::analyzeTrackEff(SimTrackMatchManager& match, int trk_no)
{
  const DisplacedGENMuonMatcher& match_gen = match.genMuons();
  const SimHitMatcher& match_sh = match.simhits();
  const GEMDigiMatcher& match_gd = match.gemDigis();
  const CSCDigiMatcher& match_cd = match.cscDigis();
  const ME0DigiMatcher& match_me0digi = match.me0Digis();
  const CSCStubMatcher& match_lct = match.cscStubs();
  const ME0RecHitMatcher& match_me0rh = match.me0RecHits();
  const SimTrack &t = match_sh.trk();

  float randtest1 = CLHEP::RandFlat::shoot(0.0,1.0) ;
  float randtest2 = CLHEP::RandFlat::shoot(0.0,1.0) ;
  if (verbose_) std::cout <<"TDRAnalyzer step1 "<< std::endl;
  for (const auto& s: stations_to_use_)
    {
      etrk_[s].init();

      etrk_[s].run = match.simhits().event().id().run();
      etrk_[s].lumi = match.simhits().event().id().luminosityBlock();
      etrk_[s].event = match.simhits().event().id().event();
      etrk_[s].rand01_v1 = randtest1;
      etrk_[s].rand01_v2 = randtest2;
      etrk_[s].pt = t.momentum().pt();
      etrk_[s].pz = t.momentum().pz();
      etrk_[s].phi = t.momentum().phi();
      etrk_[s].eta = t.momentum().eta();
      etrk_[s].dxy = match.simhits().dxy();
      etrk_[s].charge = t.charge();
      etrk_[s].endcap = (etrk_[s].eta > 0.) ? 1 : -1;
      }


  int chargesign = (t.charge()>0? 1:0);
  float pt = t.momentum().pt();
  // SimHits
  const auto& csc_simhits(match_sh.chamberIdsCSC(0));
  GlobalPoint gp_sh_odd[NumOfTrees];
  GlobalPoint gp_sh_even[NumOfTrees];
  GlobalVector gv_sh_odd[NumOfTrees];
  GlobalVector gv_sh_even[NumOfTrees];
  for(const auto& d: csc_simhits)
    {

      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;
      int nlayers(match_sh.nLayersWithHitsInSuperChamber(d));
      if (id.station() == 1 and id.chamber()%2 == 1) etrk_[0].chamber_ME1_csc_sh |= 1;
      if (id.station() == 1 and id.chamber()%2 == 0) etrk_[0].chamber_ME1_csc_sh |= 2;
      if (id.station() == 2 and id.chamber()%2 == 1) etrk_[0].chamber_ME2_csc_sh |= 1;
      if (id.station() == 2 and id.chamber()%2 == 0) etrk_[0].chamber_ME2_csc_sh |= 2;
      // case ME11
      if (id.station()==1 and (id.ring()==4 or id.ring()==1)){
        // get the detId of the pairing subchamber
        int other_ring(id.ring()==4 ? 1 : 4);
        CSCDetId co_id(id.endcap(), id.station(), other_ring, id.chamber());
        // check if co_id occurs in the list
        // add the hit layers

        const auto& rawId(co_id.rawId());
        if (csc_simhits.find(rawId) != csc_simhits.end()) {
          nlayers = nlayers+match_sh.nLayersWithHitsInSuperChamber(rawId);

        }

      }
      //std::cout <<"CSCid with simhits "<< id << " nlayer "<< nlayers << std::endl;
      if (nlayers < minNHitsChamberCSCSimHit_) continue;
      const GlobalVector& ym = match_sh.simHitsMeanMomentum(match_sh.hitsInChamber(d));
      etrk_[st].bending_sh = match_sh.LocalBendingInChamber(d);
      const CSCDetId id1(id.endcap(), id.station(), id.ring(), id.chamber(), 1);
      const CSCDetId id6(id.endcap(), id.station(), id.ring(), id.chamber(), 6);
      const GlobalPoint& gp1 = match_sh.simHitsMeanPosition(match_sh.hitsInDetId(id1.rawId()));
      const GlobalPoint& gp6 = match_sh.simHitsMeanPosition(match_sh.hitsInDetId(id6.rawId()));
      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_csc_sh |= 1;
      else etrk_[st].has_csc_sh |= 2;
      if (odd){
        etrk_[st].pteta_sh_odd = ym.eta();
        etrk_[st].ptphi_sh_odd = ym.phi();
        etrk_[st].pt_sh_odd = ym.perp();
      }else{
        etrk_[st].pteta_sh_even = ym.eta();
        etrk_[st].ptphi_sh_even = ym.phi();
        etrk_[st].pt_sh_even = ym.perp();
      }
      if (odd){
        if (match_sh.hitsInDetId(id1.rawId()).size()>0){
          etrk_[st].eta_layer1_sh_odd = gp1.eta();
          etrk_[st].phi_layer1_sh_odd = gp1.phi();
          etrk_[st].perp_layer1_sh_odd = gp1.perp();
          etrk_[st].z_layer1_sh_odd = gp1.z();
          //std::cout <<"layer1 id "<< id1 <<" phi "<< gp1.phi() <<" eta "<< gp1.eta() <<" x "<< gp1.x()<<" y "<< gp1.y()<<" z "<< gp1.z() <<" perp "<< gp1.perp() << std::endl;
        }
        if (match_sh.hitsInDetId(id6.rawId()).size()>0){
          etrk_[st].eta_layer6_sh_odd = gp6.eta();
          etrk_[st].phi_layer6_sh_odd = gp6.phi();
          etrk_[st].perp_layer6_sh_odd = gp6.perp();
          etrk_[st].z_layer6_sh_odd = gp6.z();
          //std::cout <<"layer6 id "<< id6 <<" phi "<< gp6.phi() <<" eta "<< gp6.eta() <<" x "<< gp6.x()<<" y "<< gp6.y()<<" z "<< gp6.z() <<" perp "<< gp6.perp() << std::endl;
        }
      }else{
        if (match_sh.hitsInDetId(id1.rawId()).size()>0){
          etrk_[st].eta_layer1_sh_even = gp1.eta();
          etrk_[st].phi_layer1_sh_even = gp1.phi();
          etrk_[st].perp_layer1_sh_even = gp1.perp();
          etrk_[st].z_layer1_sh_even = gp1.z();
          //std::cout <<"layer1 id "<< id1 <<" phi "<< gp1.phi() <<" eta "<< gp1.eta() <<" x "<< gp1.x()<<" y "<< gp1.y()<<" z "<< gp1.z() <<" perp "<< gp1.perp() << std::endl;
        }
        if (match_sh.hitsInDetId(id6.rawId()).size()>0){
          etrk_[st].eta_layer6_sh_even = gp6.eta();
          etrk_[st].phi_layer6_sh_even = gp6.phi();
          etrk_[st].perp_layer6_sh_even = gp6.perp();
          etrk_[st].z_layer6_sh_even = gp6.z();
          //std::cout <<"layer6 id "<< id6 <<" phi "<< gp6.phi() <<" eta "<< gp6.eta() <<" x "<< gp6.x()<<" y "<< gp6.y()<<" z "<< gp6.z() <<" perp "<< gp6.perp() << std::endl;
        }
      }

      if (odd) etrk_[st].chamber_sh_odd = id.chamber();
      else etrk_[st].chamber_sh_even = id.chamber();
      if (odd) etrk_[st].nlayers_csc_sh_odd = nlayers;
      else etrk_[st].nlayers_csc_sh_even = nlayers;

      if (odd) gv_sh_odd[st] = ym;
      else gv_sh_even[st] = ym;
      const GlobalPoint& keygp(match_sh.simHitPositionKeyLayer(id));
      if (odd) gp_sh_odd[st] = keygp;
      else gp_sh_even[st] = keygp;
      if (odd) etrk_[st].eta_cscsh_odd = keygp.eta();
      else     etrk_[st].eta_cscsh_even = keygp.eta();
      if (odd) etrk_[st].phi_cscsh_odd = keygp.phi();
      else     etrk_[st].phi_cscsh_even = keygp.phi();
      if (odd) etrk_[st].perp_cscsh_odd = keygp.perp();
      else     etrk_[st].perp_cscsh_even = keygp.perp();
      if (odd) etrk_[st].dphipositionpt_cscsh_odd = deltaPhi(float(keygp.phi()),etrk_[st].ptphi_sh_odd);
      else     etrk_[st].dphipositionpt_cscsh_even = deltaPhi(float(keygp.phi()),etrk_[st].ptphi_sh_even);

      if (st==2 or st==3){
      	if (odd) etrk_[1].eta_cscsh_odd = keygp.eta();
      	else     etrk_[1].eta_cscsh_even = keygp.eta();
      	if (odd) etrk_[1].phi_cscsh_odd = keygp.phi();
      	else     etrk_[1].phi_cscsh_even = keygp.phi();
      	if (odd) etrk_[1].perp_cscsh_odd = keygp.perp();
      	else     etrk_[1].perp_cscsh_even = keygp.perp();
        if (odd) etrk_[1].dphipositionpt_cscsh_odd = deltaPhi(float(keygp.phi()),etrk_[st].ptphi_sh_odd);
        else     etrk_[1].dphipositionpt_cscsh_even = deltaPhi(float(keygp.phi()),etrk_[st].ptphi_sh_even);
      }

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_csc_sh |= 1;
        else etrk_[1].has_csc_sh |= 2;

        if (odd) etrk_[1].nlayers_csc_sh_odd = nlayers;
        else etrk_[1].nlayers_csc_sh_even = nlayers;

        if (odd) etrk_[st].chamber_sh_odd = id.chamber();
        else etrk_[st].chamber_sh_even = id.chamber();
        if (odd) gp_sh_odd[1] = keygp;
        else gp_sh_even[1] = keygp;
        if (odd) gv_sh_odd[1] = ym;
        else gv_sh_even[1] = ym;


        if (odd){
          etrk_[1].pt_sh_odd = ym.perp();
          etrk_[1].pteta_sh_odd = ym.eta();
          etrk_[1].ptphi_sh_odd = ym.phi();
        }else {
          etrk_[1].pt_sh_even = ym.perp();
          etrk_[1].pteta_sh_even = ym.eta();
          etrk_[1].ptphi_sh_even = ym.phi();
        }
        if (odd){
          if (match_sh.hitsInDetId(id1.rawId()).size()>0){
            etrk_[1].eta_layer1_sh_odd = gp1.eta();
            etrk_[1].phi_layer1_sh_odd = gp1.phi();
            etrk_[1].perp_layer1_sh_odd = gp1.perp();
            etrk_[1].z_layer1_sh_odd = gp1.z();
          }
          if (match_sh.hitsInDetId(id6.rawId()).size()>0){
            etrk_[1].eta_layer6_sh_odd = gp6.eta();
            etrk_[1].phi_layer6_sh_odd = gp6.phi();
            etrk_[1].perp_layer6_sh_odd = gp6.perp();
            etrk_[1].z_layer6_sh_odd = gp6.z();
          }
        }else{
          if (match_sh.hitsInDetId(id1.rawId()).size()>0){
            etrk_[1].eta_layer1_sh_even = gp1.eta();
            etrk_[1].phi_layer1_sh_even = gp1.phi();
            etrk_[1].perp_layer1_sh_even = gp1.perp();
            etrk_[1].z_layer1_sh_even = gp1.z();
          }
          if (match_sh.hitsInDetId(id6.rawId()).size()>0){
            etrk_[1].eta_layer6_sh_even = gp6.eta();
            etrk_[1].phi_layer6_sh_even = gp6.phi();
            etrk_[1].perp_layer6_sh_even = gp6.perp();
            etrk_[1].z_layer6_sh_even = gp6.z();
          }
        }
        etrk_[1].bending_sh = match_sh.LocalBendingInChamber(d);
      }

    }

  //ME0 simhits
  const auto& me0_simhits(match_sh.superChamberIdsME0());
  if (verbose_) std::cout <<"me0 simthits , chamber id size "<< me0_simhits.size() << std::endl;
  for (const auto& d : me0_simhits){
    const ME0DetId id(d);
    int nlayers = match_sh.nLayersWithHitsInSuperChamber(d);
    if (verbose_) std::cout <<"ME0 Detid "<< id <<" nlayer hits "<< nlayers << std::endl;
    if (nlayers < minNHitsChamberME0SimHit_) continue;
    bool odd(id.chamber()%2 == 1);
    //ME0DetId(int region, int layer,int chamber, int roll)
    const GlobalVector& ym = match_sh.simHitsMeanMomentum(match_sh.hitsInSuperChamber(d));
    const GlobalPoint& keygp(match_sh.simHitsMeanPosition(match_sh.hitsInSuperChamber(d)));
    //etrk_[ME0].bending_sh = match_sh.LocalBendingInChamber(d);
    const ME0DetId id1(id.region(), 1, id.chamber(), 0);
    const ME0DetId id6(id.region(), 6, id.chamber(), 0);
    const GlobalPoint& gp1 = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id1.rawId()));
    const GlobalPoint& gp6 = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id6.rawId()));
    if (odd)  etrk_[ME0].nlayers_csc_sh_odd = nlayers;
    else  etrk_[ME0].nlayers_csc_sh_even = nlayers;
    if (odd) etrk_[ME0].has_csc_sh |= 1;
    else etrk_[ME0].has_csc_sh |= 2;
    if (odd) etrk_[ME0].chamber_sh_odd = id.chamber();
    else etrk_[ME0].chamber_sh_even = id.chamber();
    if (odd) etrk_[ME0].eta_cscsh_odd = keygp.eta();
    else     etrk_[ME0].eta_cscsh_even = keygp.eta();
    if (odd) etrk_[ME0].phi_cscsh_odd = keygp.phi();
    else     etrk_[ME0].phi_cscsh_even = keygp.phi();
    if (odd) etrk_[ME0].perp_cscsh_odd = keygp.perp();
    if (odd) etrk_[ME0].perp_cscsh_even = keygp.perp();
    if (odd){
    	etrk_[ME0].pteta_sh_odd = ym.eta();
    	etrk_[ME0].ptphi_sh_odd = ym.phi();
    	etrk_[ME0].pt_sh_odd = ym.perp();
    }else{
    	etrk_[ME0].pteta_sh_even = ym.eta();
    	etrk_[ME0].ptphi_sh_even = ym.phi();
    	etrk_[ME0].pt_sh_even = ym.perp();
    }
    if (odd){
    	if (match_sh.hitsInChamber(id1.rawId()).size()>0){
        etrk_[ME0].eta_layer1_sh_odd = gp1.eta();
        etrk_[ME0].phi_layer1_sh_odd = gp1.phi();
        etrk_[ME0].perp_layer1_sh_odd = gp1.perp();
        etrk_[ME0].z_layer1_sh_odd = gp1.z();
        //std::cout <<"layer1 id "<< id1 <<" phi "<< gp1.phi() <<" eta "<< gp1.eta() <<" x "<< gp1.x()<<" y "<< gp1.y()<<" z "<< gp1.z() <<" perp "<< gp1.perp() << " z "<< gp1.z() << std::endl;
      }
    	if (match_sh.hitsInChamber(id6.rawId()).size()>0){
        etrk_[ME0].eta_layer6_sh_odd = gp6.eta();
        etrk_[ME0].phi_layer6_sh_odd = gp6.phi();
        etrk_[ME0].perp_layer6_sh_odd = gp6.perp();
        etrk_[ME0].z_layer6_sh_odd = gp6.z();
        //std::cout <<"layer6 id "<< id6 <<" phi "<< gp6.phi() <<" eta "<< gp6.eta() <<" x "<< gp6.x()<<" y "<< gp6.y()<<" z "<< gp6.z() <<" perp "<< gp6.perp()<< " z "<< gp6.z() << std::endl;
      }
    }else{
    	if (match_sh.hitsInChamber(id1.rawId()).size()>0){
        etrk_[ME0].eta_layer1_sh_even = gp1.eta();
        etrk_[ME0].phi_layer1_sh_even = gp1.phi();
        etrk_[ME0].perp_layer1_sh_even = gp1.perp();
        etrk_[ME0].z_layer1_sh_even = gp1.z();
        //std::cout <<"layer1 id "<< id1 <<" phi "<< gp1.phi() <<" eta "<< gp1.eta() <<" x "<< gp1.x()<<" y "<< gp1.y()<<" z "<< gp1.z() <<" perp "<< gp1.perp() << " z "<< gp1.z() << std::endl;
      }
    	if (match_sh.hitsInChamber(id6.rawId()).size()>0){
        etrk_[ME0].eta_layer6_sh_even = gp6.eta();
        etrk_[ME0].phi_layer6_sh_even = gp6.phi();
        etrk_[ME0].perp_layer6_sh_even = gp6.perp();
        etrk_[ME0].z_layer6_sh_even = gp6.z();
        //std::cout <<"layer6 id "<< id6 <<" phi "<< gp6.phi() <<" eta "<< gp6.eta() <<" x "<< gp6.x()<<" y "<< gp6.y()<<" z "<< gp6.z() <<" perp "<< gp6.perp() << " z "<< gp6.z() << std::endl;
      }
    }

  }
  if (verbose_) std::cout <<"TDRAnalyzer step2 "<< std::endl;
  // CSC strip digis
  for(const auto& d: match_cd.chamberIdsStrip(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const int nlayers(match_cd.nLayersWithStripInChamber(d));
      //std::cout <<"CSC strip digi, CSCid "<< id <<" nlayer "<< nlayers << std::endl;
      if (nlayers < minNHitsChamberCSCStripDigi_) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_csc_strips |= 1;
      else etrk_[st].has_csc_strips |= 2;

      if (odd) etrk_[st].nlayers_st_dg_odd = nlayers;
      else etrk_[st].nlayers_st_dg_even = nlayers;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_csc_strips |= 1;
        else etrk_[1].has_csc_strips |= 2;

        if (odd) etrk_[1].nlayers_st_dg_odd = nlayers;
        else etrk_[1].nlayers_st_dg_even = nlayers;
      }
    }

  // CSC wire digis
  for(const auto& d: match_cd.chamberIdsWire(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const int nlayers(match_cd.nLayersWithWireInChamber(d));
      //std::cout <<"CSC wire digi, CSCid "<< id <<" nlayer "<< nlayers << std::endl;
      if (nlayers < minNHitsChamberCSCWireDigi_) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_csc_wires |= 1;
      else etrk_[st].has_csc_wires |= 2;

      if (odd) etrk_[st].nlayers_wg_dg_odd = nlayers;
      else etrk_[st].nlayers_wg_dg_even = nlayers;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_csc_wires |= 1;
        else etrk_[1].has_csc_wires |= 2;

        if (odd) etrk_[1].nlayers_wg_dg_odd = nlayers;
        else etrk_[1].nlayers_wg_dg_even = nlayers;
      }
    }

  // CSC CLCTs
  for(const auto& d: match_lct.chamberIdsCLCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      const auto& clct = match_lct.clctInChamber(d);

      //std::cout <<"CSC CLCT, CSCid "<< id <<" clct "<< clct << std::endl;
      if (odd) etrk_[st].chamber_dg_odd = id.chamber();
      else etrk_[st].chamber_dg_even = id.chamber();
      if (odd) etrk_[st].halfstrip_odd = digi_channel(clct);
      else etrk_[st].halfstrip_even = digi_channel(clct);

      if (odd) etrk_[st].quality_clct_odd = digi_quality(clct);
      else etrk_[st].quality_clct_even = digi_quality(clct);

      if (odd) etrk_[st].bx_clct_odd = digi_bx(clct);
      else etrk_[st].bx_clct_even = digi_bx(clct);

      if (odd) etrk_[st].has_clct |= 1;
      else etrk_[st].has_clct |= 2;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].halfstrip_odd = digi_channel(clct);
        else etrk_[1].halfstrip_even = digi_channel(clct);

        if (odd) etrk_[1].quality_clct_odd = digi_quality(clct);
        else etrk_[1].quality_clct_even = digi_quality(clct);

        if (odd) etrk_[1].bx_clct_odd = digi_bx(clct);
        else etrk_[1].bx_clct_even = digi_bx(clct);

        if (odd) etrk_[1].has_clct |= 1;
        else etrk_[1].has_clct |= 2;
      }
    }

  // CSC ALCTs
  for(const auto& d: match_lct.chamberIdsALCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      const auto& alct = match_lct.alctInChamber(d);

      //std::cout <<"CSC ALCT, CSCid "<< id <<" alct "<< alct << std::endl;
      if (odd) etrk_[st].wiregroup_odd = digi_channel(alct);
      else etrk_[st].wiregroup_even = digi_channel(alct);

      if (odd) etrk_[st].quality_alct_odd = digi_quality(alct);
      else etrk_[st].quality_alct_even = digi_quality(alct);

      if (odd) etrk_[st].bx_alct_odd = digi_bx(alct);
      else etrk_[st].bx_alct_even = digi_bx(alct);

      if (odd) etrk_[st].has_alct |= 1;
      else etrk_[st].has_alct |= 2;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].wiregroup_odd = digi_channel(alct);
        else etrk_[1].wiregroup_even = digi_channel(alct);

        if (odd) etrk_[1].quality_alct_odd = digi_quality(alct);
        else etrk_[1].quality_alct_even = digi_quality(alct);

        if (odd) etrk_[1].bx_alct_odd = digi_bx(alct);
        else etrk_[1].bx_alct_even = digi_bx(alct);

        if (odd) etrk_[1].has_alct |= 1;
        else etrk_[1].has_alct |= 2;
      }
    }

  if (verbose_) std::cout <<"TDRAnalyzer step3 "<< std::endl;
  // holders for track's LCTs
  Digi lct_odd[12];
  Digi lct_even[12];
  GlobalPoint gp_lct_odd[12];
  GlobalPoint gp_lct_even[12];
  GlobalPoint gp_fit_odd[12];
  GlobalPoint gp_fit_even[12];
  for (const auto& s: stations_to_use_)
    {
      lct_odd[s] = make_digi();
      lct_even[s] = make_digi();

      // case ME11
      if (s==2 or s==3){
        lct_odd[1] = make_digi();
        lct_even[1] = make_digi();
      }
    }

  // LCT stubs
  for(const auto& d: match_lct.chamberIdsLCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_lct |= 1;
      else etrk_[st].has_lct |= 2;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_lct |= 1;
        else etrk_[1].has_lct |= 2;
      }


      const auto& lct = match_lct.lctInChamber(d);
      const int bend(LCT_BEND_PATTERN[digi_pattern(lct)]);
      const auto& gp = match_lct.digiPosition(lct);

      if (match_lct.cscLctsInChamber(d).size()>0) {
        etrk_[st].lct_type = match_lct.cscLctsInChamber(d)[0].getType();
        std::cout << "Printing best LCT " << match_lct.cscLctsInChamber(d)[0] << " " << etrk_[st].lct_type << " " << match_lct.cscLctsInChamber(d)[0].getType() << std::endl;
      }

      //std::cout <<"CSC LCT, CSCid "<< id <<" lct "<< lct <<" gp eta "<< gp.eta()<<" phi "<< gp.phi() <<" perp "<< gp.perp()<<std::endl;
      if (csc_simhits.find(d) == csc_simhits.end())
        std::cout <<"failed to find simhits in CSCid "<< id <<" but find LCT" << lct << std::endl;
      if (odd)
        {
          lct_odd[st] = lct;
          gp_lct_odd[st] = gp;
          etrk_[st].bend_lct_odd = bend;
          etrk_[st].phi_lct_odd = gp.phi();
          etrk_[st].eta_lct_odd = gp.eta();
          etrk_[st].perp_lct_odd = gp.perp();
          if (fabs(etrk_[st].perp_lct_odd-etrk_[st].perp_cscsh_odd)>5.0 and etrk_[st].perp_cscsh_odd>10.0)
            std::cout <<"CSCid "<< id <<" perp_cscsh_odd "<< etrk_[st].perp_cscsh_odd<<" perp_lct_odd "<< etrk_[st].perp_lct_odd<<" csc_phi "<< etrk_[st].phi_cscsh_odd<<" phi_lct_odd "<< etrk_[st].phi_lct_odd << std::endl;

          etrk_[st].dphi_lct_odd = digi_dphi(lct);
          etrk_[st].bx_lct_odd = digi_bx(lct);
          etrk_[st].hs_lct_odd = digi_channel(lct);
          etrk_[st].wg_lct_odd = digi_wg(lct);
          etrk_[st].chamber_lct_odd = id.chamber() ;
          etrk_[st].quality_odd = digi_quality(lct);
          etrk_[st].passdphi_odd = match_lct.passDPhicut(id, chargesign, digi_dphi(lct), pt);
        }
      else
        {
          lct_even[st] = lct;
          gp_lct_even[st] = gp;
          etrk_[st].bend_lct_even = bend;
          etrk_[st].phi_lct_even = gp.phi();
          etrk_[st].eta_lct_even = gp.eta();
          etrk_[st].perp_lct_even = gp.perp();
          if (fabs(etrk_[st].perp_lct_even-etrk_[st].perp_cscsh_even)>5.0 and etrk_[st].perp_cscsh_even>10.0)
            std::cout <<"CSCid "<< id <<" perp_cscsh_even "<< etrk_[st].perp_cscsh_even <<" perp_lct_even "<< etrk_[st].perp_lct_even <<" csc_phi "<< etrk_[st].phi_cscsh_even <<" phi_lct_even "<< etrk_[st].phi_lct_even << std::endl;
          etrk_[st].dphi_lct_even = digi_dphi(lct);
          etrk_[st].bx_lct_even = digi_bx(lct);
          etrk_[st].hs_lct_even = digi_channel(lct);
          etrk_[st].wg_lct_even = digi_wg(lct);
          etrk_[st].chamber_lct_even = id.chamber();
          etrk_[st].quality_even = digi_quality(lct);
          etrk_[st].passdphi_even = match_lct.passDPhicut(id, chargesign, digi_dphi(lct), pt);
        }

      // case ME11
      if (st==2 or st==3){
        if (odd)
          {
            lct_odd[1] = lct;
            gp_lct_odd[1] = gp;
            etrk_[1].bend_lct_odd = bend;
            etrk_[1].phi_lct_odd = gp.phi();
            etrk_[1].eta_lct_odd = gp.eta();
            etrk_[1].perp_lct_odd = gp.perp();
            etrk_[1].dphi_lct_odd = digi_dphi(lct);
            etrk_[1].bx_lct_odd = digi_bx(lct);
            etrk_[1].hs_lct_odd = digi_channel(lct);
            etrk_[1].wg_lct_odd = digi_wg(lct);
            etrk_[1].chamber_lct_odd = id.chamber();
            etrk_[1].quality_odd = digi_quality(lct);
            etrk_[1].passdphi_odd = match_lct.passDPhicut(id, chargesign, digi_dphi(lct), pt);
          }
        else
          {
            lct_even[1] = lct;
            gp_lct_even[1] = gp;
            etrk_[1].bend_lct_even = bend;
            etrk_[1].phi_lct_even = gp.phi();
            etrk_[1].eta_lct_even = gp.eta();
            etrk_[1].perp_lct_even = gp.perp();
            etrk_[1].dphi_lct_even = digi_dphi(lct);
            etrk_[1].bx_lct_even = digi_bx(lct);
            etrk_[1].hs_lct_even = digi_channel(lct);
            etrk_[1].wg_lct_even = digi_wg(lct);
            etrk_[1].chamber_lct_even = id.chamber();
            etrk_[1].quality_even = digi_quality(lct);
            etrk_[1].passdphi_even = match_lct.passDPhicut(id, chargesign, digi_dphi(lct), pt);
          }

      }
    }

  if (verbose_) std::cout <<"TDRAnalyzer step4 "<< std::endl;
  //for GEMs in station1, it will be also filled in ME11
  // GEM simhits in superchamber
  GlobalPoint gp_gemsh_odd[12];
  GlobalPoint gp_gemsh_even[12];
  for(const auto& d: match_sh.superChamberIdsGEM())
    {
      GEMDetId id(d);
      int MEStation = id.station();

      const int st(detIdToMEStation(MEStation,id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      if (match_sh.hitsInSuperChamber(d).size() > 0)
        {
          if (odd) etrk_[st].has_gem_sh |= 1;
          else     etrk_[st].has_gem_sh |= 2;

          for (int layer=1; layer<3; layer++){
            GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
            const GlobalPoint& keygp = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
            const GlobalVector& keygv = match_sh.simHitsMeanMomentum(match_sh.hitsInChamber(id_tmp.rawId()));
            float centralperp_gemsh = match_sh.simHitsGEMCentralPosition(match_sh.hitsInChamber(id_tmp.rawId()));match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
            if(match_sh.hitsInChamber(id_tmp).size()==0) continue;
            if (odd) gp_gemsh_odd[st] = keygp;
            else gp_gemsh_even[st] = keygp;
            //std::cout <<"Matching GEMHits GEM Id "<< id <<" gp.eta "<< keygp.eta() <<" gp.phi "<< keygp.phi() << std::endl;
            //std::cout <<" GEM Id "<< id_tmp <<" eta "<< keygp.eta() <<" phi "<< keygp.phi()<<" perp "<< keygp.perp() <<" x " << keygp.x() <<" y "<< keygp.y() << " z "<< keygp.z()<< std::endl;
            if (odd) etrk_[st].eta_gemsh_odd = keygp.eta();
            else     etrk_[st].eta_gemsh_even = keygp.eta();
            if (odd) etrk_[st].phi_gemsh_odd = keygp.phi();
            else     etrk_[st].phi_gemsh_even = keygp.phi();
            if (odd) etrk_[st].ptphi_gemsh_odd = keygv.phi();
            else     etrk_[st].ptphi_gemsh_even = keygv.phi();
            if (odd) etrk_[st].perp_gemsh_odd = keygp.perp();
            else     etrk_[st].perp_gemsh_even = keygp.perp();
            if (odd) etrk_[st].centralperp_gemsh_odd = centralperp_gemsh;
            else     etrk_[st].centralperp_gemsh_even = centralperp_gemsh;
            float phi_m = -9;
            int st_csc = (st==3 and (etrk_[st].has_csc_sh&3)==0)? 1:st;
            if (odd and etrk_[st_csc].phi_cscsh_odd>-9){
              etrk_[st].dphi_sh_odd = deltaPhi(etrk_[st_csc].phi_cscsh_odd, float(keygp.phi()));// here should we use st or st_csc?
              etrk_[st].dphipositionpt_gemsh_odd = deltaPhi(float(keygp.phi()),etrk_[st_csc].ptphi_sh_odd);
              phi_m =  PtassignmentHelper::PhiMomentum_Radius(etrk_[st].dphi_sh_odd, etrk_[st].phi_gemsh_odd, etrk_[st_csc].perp_cscsh_odd, etrk_[st].perp_gemsh_odd);
              etrk_[st].phiM_gemcsc_odd = phi_m;
              //std::cout <<"dphi(M,P) "<< deltaPhi(etrk_[st].phi_gemsh_odd, gv_sh_odd[st_csc].phi())<<" momentum phi from simhits "<< gv_sh_odd[st_csc].phi() <<" phi from gem-csc "<< phi_m << std::endl;
            }
            else if (not(odd) and etrk_[st_csc].phi_cscsh_even>-9) {
              etrk_[st].dphi_sh_even = deltaPhi(etrk_[st_csc].phi_cscsh_even, float(keygp.phi()));
              etrk_[st].dphipositionpt_gemsh_even = deltaPhi(float(keygp.phi()),etrk_[st_csc].ptphi_sh_even);
              phi_m =  PtassignmentHelper::PhiMomentum_Radius(etrk_[st].dphi_sh_even, etrk_[st].phi_gemsh_even, etrk_[st_csc].perp_cscsh_even, etrk_[st].perp_gemsh_even);
              etrk_[st].phiM_gemcsc_even = phi_m;
              //std::cout <<"dphi(M,P) "<< deltaPhi(etrk_[st].phi_gemsh_even, gv_sh_even[st_csc].phi())<<" momentum phi from simhits "<< gv_sh_even[st_csc].phi() <<" phi from gem-csc "<< phi_m << std::endl;
            }
            if (st==2 or st==3){
              if (odd) gp_gemsh_odd[1] = keygp;
              else gp_gemsh_even[1] = keygp;
              if (odd) etrk_[1].eta_gemsh_odd = keygp.eta();
              else     etrk_[1].eta_gemsh_even = keygp.eta();
              if (odd) etrk_[1].phi_gemsh_odd = keygp.phi();
              else     etrk_[1].phi_gemsh_even = keygp.phi();
              if (odd) etrk_[1].ptphi_gemsh_odd = keygv.phi();
              else     etrk_[1].ptphi_gemsh_even = keygv.phi();
              if (odd) etrk_[1].perp_gemsh_odd = keygp.perp();
              else     etrk_[1].perp_gemsh_even = keygp.perp();
              if (odd) etrk_[1].centralperp_gemsh_odd = centralperp_gemsh;
              else     etrk_[1].centralperp_gemsh_even = centralperp_gemsh;
              if (odd and etrk_[1].phi_cscsh_odd>-9) etrk_[1].dphi_sh_odd = deltaPhi(etrk_[1].phi_cscsh_odd,float(keygp.phi()));
              else if (etrk_[1].phi_cscsh_even>-9)     etrk_[1].dphi_sh_even = deltaPhi(etrk_[1].phi_cscsh_even,float(keygp.phi()));
              if (odd) etrk_[1].phiM_gemcsc_odd = phi_m;
              else etrk_[1].phiM_gemcsc_even = phi_m;
              if (odd) etrk_[1].dphipositionpt_gemsh_odd = deltaPhi(float(keygp.phi()),etrk_[1].ptphi_sh_odd);
              else etrk_[1].dphipositionpt_gemsh_even = deltaPhi(float(keygp.phi()),etrk_[1].ptphi_sh_even);
            }
            //std::cout <<"dphi(GEM, CSC) at sim "<<(odd? etrk_[st].dphi_sh_odd:etrk_[st].dphi_sh_even) <<" phi_csc "<< (odd? etrk_[st_csc].phi_cscsh_odd:etrk_[st_csc].phi_cscsh_even) <<" phi_gp "<< keygp.phi()<< std::endl;
            if (id_tmp.layer()==1) break;

          }

          const float mean_strip(match_sh.simHitsMeanStrip(match_sh.hitsInSuperChamber(d)));
          if (odd) etrk_[st].strip_gemsh_odd = mean_strip;
          else     etrk_[st].strip_gemsh_even = mean_strip;
        }

      if (match_sh.nLayersWithHitsInSuperChamber(d) > 1)
        {
          //std::cout <<"GEM detid "<< id <<" has at 2 layer hits "<< std::endl;
          if (odd) etrk_[st].has_gem_sh2 |= 1;
          else     etrk_[st].has_gem_sh2 |= 2;
        }
      const auto& copad_superids (match_sh.superChamberIdsGEMCoincidences());
      if (copad_superids.find(d) != copad_superids.end()){
        //std::cout <<"GEM detid "<< id <<" has copad hits "<< std::endl;
        if (odd) etrk_[st].has_gemcopad_sh |= 1;
        else     etrk_[st].has_gemcopad_sh |= 2;
      }
      //ME11 Case
      if (st==2 or st==3)
        {
          if (odd) etrk_[1].has_gem_sh |= 1;
          else     etrk_[1].has_gem_sh |= 2;

          const float mean_strip(match_sh.simHitsMeanStrip(match_sh.hitsInSuperChamber(d)));
          if (odd) etrk_[1].strip_gemsh_odd = mean_strip;
          else     etrk_[1].strip_gemsh_even = mean_strip;

          if (match_sh.nLayersWithHitsInSuperChamber(d) > 1)
            {
              if (odd) etrk_[1].has_gem_sh2 |= 1;
              else etrk_[1].has_gem_sh2 |= 2;

            }
          if (copad_superids.find(d) != copad_superids.end()){
            if (odd) etrk_[1].has_gemcopad_sh |= 1;
            else     etrk_[1].has_gemcopad_sh |= 2;
          }
        }//end of ME11 case

    }

  if (verbose_) std::cout <<"TDRAnalyzer step5 "<< std::endl;
  // placeholders for best mtching pads
  GlobalPoint best_pad_odd[12];
  GlobalPoint best_pad_even[12];

  // GEM digis and pads in superchambers
  for(const auto& d: match_gd.superChamberIdsDigi())
    {
      GEMDetId id(d);
      int MEStation = id.station();

      const int st(detIdToMEStation(MEStation,id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      if (match_gd.nLayersWithDigisInSuperChamber(d) > 1)
        {
          if (odd) etrk_[st].has_gem_dg2 |= 1;
          else     etrk_[st].has_gem_dg2 |= 2;
        }

      const auto& digis = match_gd.digisInSuperChamber(d);
      const int median_strip(match_gd.median(digis));
      if (odd && digis.size() > 0)
        {
          etrk_[st].has_gem_dg |= 1;
          etrk_[st].strip_gemdg_odd = median_strip;
        }
      else if (digis.size() > 0)
        {
          etrk_[st].has_gem_dg |= 2;
          etrk_[st].strip_gemdg_even = median_strip;
        }

      if (match_gd.nLayersWithPadsInSuperChamber(d) > 1)
        {
          if (odd) etrk_[st].has_gem_pad2 |= 1;
          else     etrk_[st].has_gem_pad2 |= 2;
        }
      for (int layer=1; layer<3; layer++){
        GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
        const auto& pads = match_gd.padsInChamber(id_tmp.rawId());
        if(pads.size() == 0) continue;

        const GlobalPoint& keygp = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
        const auto& bestgem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, keygp);
        if (odd)
          {
            best_pad_odd[st] = bestgem_dg_and_gp.second;
            etrk_[st].has_gem_pad |= 1;
            etrk_[st].chamber_lct_odd = id.chamber();
            etrk_[st].pad_odd = digi_channel(bestgem_dg_and_gp.first);
            etrk_[st].hsfromgem_odd = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
            etrk_[st].z_pad_odd = best_pad_odd[st].z();
            etrk_[st].phi_pad_odd = best_pad_odd[st].phi();
            etrk_[st].eta_pad_odd = best_pad_odd[st].eta();
            //question: ME1a is not included here
            if (is_valid(lct_odd[st]))
              {
                const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
                best_pad_odd[st] = gem_dg_and_gp.second;
                etrk_[st].bx_pad_odd = digi_bx(gem_dg_and_gp.first);
                etrk_[st].dphi_pad_odd = deltaPhi(etrk_[st].phi_lct_odd, etrk_[st].phi_pad_odd);
                etrk_[st].dphi_pad_fit_odd = deltaPhi(etrk_[st].phi_layer3_fit_odd, etrk_[st].phi_pad_odd);
                etrk_[st].deta_pad_odd = etrk_[st].eta_lct_odd - etrk_[st].eta_pad_odd;
              }
          }
        else
          {
            best_pad_even[st] = bestgem_dg_and_gp.second;
            etrk_[st].has_gem_pad |= 2;
            etrk_[st].pad_even = digi_channel(bestgem_dg_and_gp.first);
            etrk_[st].hsfromgem_even = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
            etrk_[st].z_pad_even = best_pad_even[st].z();
            etrk_[st].phi_pad_even = best_pad_even[st].phi();
            etrk_[st].eta_pad_even = best_pad_even[st].eta();
            if (is_valid(lct_even[st]))
              {
                const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_even[st]);
                best_pad_even[st] = gem_dg_and_gp.second;
                etrk_[st].bx_pad_even = digi_bx(gem_dg_and_gp.first);
                etrk_[st].dphi_pad_even = deltaPhi(etrk_[st].phi_lct_even, etrk_[st].phi_pad_even);
                etrk_[st].dphi_pad_fit_even = deltaPhi(etrk_[st].phi_layer3_fit_even, etrk_[st].phi_pad_even);
                //std::cout <<"GEMid "<< id << std::endl;
                //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< etrk_[st].phi_pad_even <<" phi_lct "<< etrk_[st].phi_lct_even <<" phi_fit_lct "<< etrk_[st].phi_layer3_fit_even <<" dist(GEM, CSC) " <<  fabs(etrk_[st].z_layer3_fit_even - etrk_[st].z_pad_even)<< std::endl;
                etrk_[st].deta_pad_even = etrk_[st].eta_lct_even - etrk_[st].eta_pad_even;
              }
          }
        if (id_tmp.layer()==1) break;
      }
    }

  //ME11Case
  for(const auto& d: match_gd.superChamberIdsDigi())
    {
      GEMDetId id(d);
      int MEStation = id.station();

      const int stations(detIdToMEStation(MEStation,id.ring()));
      int st;
      if (stations==2 or stations==3) st=1;//ME1a,ME1b->ME11
      else continue;

      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      if (match_gd.nLayersWithDigisInSuperChamber(d) > 1)
        {
          if (odd) etrk_[st].has_gem_dg2 |= 1;
          else     etrk_[st].has_gem_dg2 |= 2;
        }

      const auto& digis = match_gd.digisInSuperChamber(d);
      const int median_strip(match_gd.median(digis));
      if (odd && digis.size() > 0)
        {
          etrk_[st].has_gem_dg |= 1;
          etrk_[st].strip_gemdg_odd = median_strip;
        }
      else if (digis.size() > 0)
        {
          etrk_[st].has_gem_dg |= 2;
          etrk_[st].strip_gemdg_even = median_strip;
        }

      if (match_gd.nLayersWithPadsInSuperChamber(d) > 1)
        {
          if (odd) etrk_[st].has_gem_pad2 |= 1;
          else     etrk_[st].has_gem_pad2 |= 2;
        }

      for (int layer=1; layer<3; layer++){
        GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
        const auto& pads = match_gd.padsInChamber(id_tmp.rawId());
        if(pads.size() == 0) continue;
        const GlobalPoint& keygp = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
        const auto& bestgem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, keygp);

        if (odd)
          {
            best_pad_odd[st] = bestgem_dg_and_gp.second;
            etrk_[st].has_gem_pad |= 1;
            etrk_[st].pad_odd = digi_channel(bestgem_dg_and_gp.first);
            etrk_[st].hsfromgem_odd = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
            etrk_[st].phi_pad_odd = best_pad_odd[st].phi();
            etrk_[st].eta_pad_odd = best_pad_odd[st].eta();
            if (is_valid(lct_odd[st]))
              {
                const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
                best_pad_odd[st] = gem_dg_and_gp.second;
                etrk_[st].bx_pad_odd = digi_bx(gem_dg_and_gp.first);
                etrk_[st].dphi_pad_odd = deltaPhi(etrk_[st].phi_lct_odd, etrk_[st].phi_pad_odd);
                etrk_[st].dphi_pad_fit_odd = deltaPhi(etrk_[st].phi_layer3_fit_odd, etrk_[st].phi_pad_odd);
                etrk_[st].deta_pad_odd = etrk_[st].eta_lct_odd - etrk_[st].eta_pad_odd;
              }
          }
        else
          {
            best_pad_even[st] = bestgem_dg_and_gp.second;
            etrk_[st].has_gem_pad |= 2;
            etrk_[st].pad_even = digi_channel(bestgem_dg_and_gp.first);
            etrk_[st].hsfromgem_even = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
            etrk_[st].phi_pad_even = best_pad_even[st].phi();
            etrk_[st].eta_pad_even = best_pad_even[st].eta();
            if (is_valid(lct_even[st]))
              {
                const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_even[st]);
                best_pad_even[st] = gem_dg_and_gp.second;
                etrk_[st].bx_pad_even = digi_bx(gem_dg_and_gp.first);
                etrk_[st].dphi_pad_even = deltaPhi(etrk_[st].phi_lct_even, etrk_[st].phi_pad_even);
                etrk_[st].dphi_pad_fit_even = deltaPhi(etrk_[st].phi_layer3_fit_even, etrk_[st].phi_pad_even);
                etrk_[st].deta_pad_even = etrk_[st].eta_lct_even - etrk_[st].eta_pad_even;
              }
          }
        if (id_tmp.layer()==1) break;
      }
    }

  if (verbose_) std::cout <<"TDRAnalyzer step6 "<< std::endl;
  for(const auto& d: match_gd.superChamberIdsCoPad())
    {
      GEMDetId id(d);
      int MEStation = id.station();

      const int st(detIdToMEStation(MEStation,id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_gem_copad |= 1;
      else     etrk_[st].has_gem_copad |= 2;

      const auto& copads = match_gd.coPadsInSuperChamber(d);
      if (copads.size() == 0) continue;
      if (odd) etrk_[st].Copad_odd = digi_channel(copads.at(0));
      else etrk_[st].Copad_even = digi_channel(copads.at(0));
      if (verbose_) std::cout <<"Matching GEMCopad detid "<< id <<" size "<< copads.size() << std::endl;

      if (st==2 or st==3)
        {
          if (odd) etrk_[1].has_gem_copad |= 1;
          else     etrk_[1].has_gem_copad |= 2;

          const auto& copads = match_gd.coPadsInSuperChamber(d);
          if (copads.size() == 0) continue;
          if (odd) etrk_[1].Copad_odd = digi_channel(copads.at(0));
          else etrk_[1].Copad_even = digi_channel(copads.at(0));
        }
    }

 if (verbose_) std::cout <<"TDRAnalyzer step10 "<< std::endl;
 for (const auto& s: stations_to_use_)
   {
     tree_eff_[s]->Fill();
   }
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TDRAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(TDRAnalyzer);
