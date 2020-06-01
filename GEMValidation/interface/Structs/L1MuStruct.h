#ifndef GEMCode_GEMValidation_L1MuStruct
#define GEMCode_GEMValidation_L1MuStruct

#include "TTree.h"

namespace gem {

  struct L1MuStruct {

    // Track properties
    Int_t has_emtfTrack;
    Int_t has_gmtRegCand;
    Int_t has_gmtCand;

    //csctf
    float emtf_pt, emtf_eta, emtf_phi;
    UInt_t chargesign;
    UInt_t rank;
    UInt_t nstubs;
    UInt_t deltaphi12, deltaphi23;
    bool hasME1, hasME2, hasME3, hasME4;
    Char_t chamberME1, chamberME2;  //bit1: odd, bit2: even
    Int_t ME1_ring, ME2_ring;
    Int_t ME1_hs, ME2_hs, ME1_wg, ME2_wg;
    float dphiGE11, dphiGE21;
    bool passGE11, passGE21;
    bool passGE11_pt5, passGE11_pt7, passGE11_pt10, passGE11_pt15, passGE11_pt20, passGE11_pt30, passGE11_pt40;
    bool passGE21_pt5, passGE21_pt7, passGE21_pt10, passGE21_pt15, passGE21_pt20, passGE21_pt30, passGE21_pt40;
    bool passGE11_simpt, passGE21_simpt;
    float deltaR;
    float lctdphi12;

    bool allstubs_matched_TF;
    //L1Mu
    float bestdRGmtCand;
    float L1Mu_pt, L1Mu_eta, L1Mu_phi, L1Mu_quality, L1Mu_bx;
    Int_t L1Mu_charge;

    void init() {
      // Track properties
      has_emtfTrack = -99;
      has_gmtRegCand = -99;
      has_gmtCand = -99;

      //csctf
      emtf_pt = -1;
      emtf_eta = -9;
      emtf_phi = -9;
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

      allstubs_matched_TF = false;

      bestdRGmtCand = 99;
      L1Mu_pt = -99;
      L1Mu_eta = -99;
      L1Mu_phi = -99;
      L1Mu_quality = -99;
      L1Mu_bx = -99;
      L1Mu_charge = -99;
    };

    void book(TTree* t) {

      //t->Branch("", &);
      t->Branch("has_emtfTrack", &has_emtfTrack);
      t->Branch("has_gmtRegCand", &has_gmtRegCand);
      t->Branch("has_gmtCand", &has_gmtCand);

      //csctftrack
      t->Branch("emtf_pt", &emtf_pt);
      t->Branch("emtf_eta", &emtf_eta);
      t->Branch("emtf_phi", &emtf_phi);
      t->Branch("rank",&rank);
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


      t->Branch("allstubs_matched_TF",&allstubs_matched_TF);

      t->Branch("bestdRGmtCand", &bestdRGmtCand);
      t->Branch("L1Mu_pt", &L1Mu_pt);
      t->Branch("L1Mu_eta", &L1Mu_eta);
      t->Branch("L1Mu_phi", &L1Mu_phi);
      t->Branch("L1Mu_quality", &L1Mu_quality);
      t->Branch("L1Mu_bx", &L1Mu_bx);
      t->Branch("L1Mu_charge", &L1Mu_charge);
    }
  };
}  // namespace

#endif
