#include "GEMCode/GEMValidation/interface/Analyzers/CSCStubAnalyzer.h"

CSCStubAnalyzer::CSCStubAnalyzer(const CSCStubMatcher& match_sh)
  :  match_(match_sh)
{
}

void CSCStubAnalyzer::analyze(MyTrack track[NumOfTrees])
{
  /*
  // CSC CLCTs
  for(const auto& d: match_lct.chamberIdsCLCT(0)) {
    CSCDetId id(d);
    const int st(detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    const auto& clct = match_lct.bestClctInChamber(d);

    if (odd) {
      etrk_[st].has_clct |= 1;
      etrk_[st].chamber_dg_odd = id.chamber();
      etrk_[st].halfstrip_odd = clct.getKeyStrip();
      etrk_[st].quality_clct_odd = clct.getQuality();
      etrk_[st].bx_clct_odd = clct.getBX();
    }
    else {
      etrk_[st].has_clct |= 2;
      etrk_[st].chamber_dg_even = id.chamber();
      etrk_[st].halfstrip_even = clct.getKeyStrip();
      etrk_[st].quality_clct_even = clct.getQuality();
      etrk_[st].bx_clct_even = clct.getBX();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        etrk_[1].has_clct |= 1;
        etrk_[1].chamber_dg_odd = id.chamber();
        etrk_[1].halfstrip_odd = clct.getKeyStrip();
        etrk_[1].quality_clct_odd = clct.getQuality();
        etrk_[1].bx_clct_odd = clct.getBX();
      }
      else {
        etrk_[1].has_clct |= 2;
        etrk_[1].chamber_dg_even = id.chamber();
        etrk_[1].halfstrip_even = clct.getKeyStrip();
        etrk_[1].quality_clct_even = clct.getQuality();
        etrk_[1].bx_clct_even = clct.getBX();
      }
    }
  }

  // CSC ALCTs
  for(const auto& d: match_lct.chamberIdsALCT(0)) {
    CSCDetId id(d);
    const int st(detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    const auto& alct = match_lct.bestAlctInChamber(d);

    if (odd) {
      etrk_[st].has_alct |= 1;
      etrk_[st].chamber_dg_odd = id.chamber();
      etrk_[st].wiregroup_odd = alct.getKeyWG();
      etrk_[st].quality_alct_odd = alct.getQuality();
      etrk_[st].bx_alct_odd = alct.getBX();
    }
    else {
      etrk_[st].has_alct |= 2;
      etrk_[st].chamber_dg_even = id.chamber();
      etrk_[st].wiregroup_even = alct.getKeyWG();
      etrk_[st].quality_alct_even = alct.getQuality();
      etrk_[st].bx_alct_even = alct.getBX();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        etrk_[1].has_alct |= 1;
        etrk_[1].chamber_dg_odd = id.chamber();
        etrk_[1].wiregroup_odd = alct.getKeyWG();
        etrk_[1].quality_alct_odd = alct.getQuality();
        etrk_[1].bx_alct_odd = alct.getBX();
      }
      else {
        etrk_[1].has_alct |= 2;
        etrk_[1].chamber_dg_even = id.chamber();
        etrk_[1].wiregroup_even = alct.getKeyWG();
        etrk_[1].quality_alct_even = alct.getQuality();
        etrk_[1].bx_alct_even = alct.getBX();
      }
    }

    // CSC LCTs
    for(const auto& d: match_lct.chamberIdsLCT(0)) {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const auto& lct = match_lct.bestLctInChamber(d);
      const GlobalPoint& gp = match_lct.getGlobalPosition(d, lct);

      const bool odd(id.chamber()%2==1);
      if (odd) {
        etrk_[st].has_lct |= 1;
        etrk_[st].bend_lct_odd = lct.getPattern();
        etrk_[st].phi_lct_odd = gp.phi();
        etrk_[st].eta_lct_odd = gp.eta();
        etrk_[st].perp_lct_odd = gp.perp();
        etrk_[st].bx_lct_odd = lct.getBX();
        etrk_[st].hs_lct_odd = lct.getStrip();
        etrk_[st].wg_lct_odd = lct.getKeyWG();
        etrk_[st].quality_odd = lct.getQuality();
      }
      else {
        etrk_[st].has_lct |= 2;
        etrk_[st].bend_lct_even = lct.getPattern();
        etrk_[st].phi_lct_even = gp.phi();
        etrk_[st].eta_lct_even = gp.eta();
        etrk_[st].perp_lct_even = gp.perp();
        etrk_[st].bx_lct_even = lct.getBX();
        etrk_[st].hs_lct_even = lct.getStrip();
        etrk_[st].wg_lct_even = lct.getKeyWG();
        etrk_[st].quality_even = lct.getQuality();
      }
      // case ME11
      if (st==2 or st==3){
        if (odd) {
          etrk_[1].has_lct |= 1;
          etrk_[1].bend_lct_odd = lct.getPattern();
          etrk_[1].phi_lct_odd = gp.phi();
          etrk_[1].eta_lct_odd = gp.eta();
          etrk_[1].perp_lct_odd = gp.perp();
          etrk_[1].bx_lct_odd = lct.getBX();
          etrk_[1].hs_lct_odd = lct.getStrip();
          etrk_[1].wg_lct_odd = lct.getKeyWG();
          etrk_[1].quality_odd = lct.getQuality();
        }
        else {
          etrk_[1].has_lct |= 2;
          etrk_[1].bend_lct_even = lct.getPattern();
          etrk_[1].phi_lct_even = gp.phi();
          etrk_[1].eta_lct_even = gp.eta();
          etrk_[1].perp_lct_even = gp.perp();
          etrk_[1].bx_lct_even = lct.getBX();
          etrk_[1].hs_lct_even = lct.getStrip();
          etrk_[1].wg_lct_even = lct.getKeyWG();
          etrk_[1].quality_even = lct.getQuality();
        }
      }
    }
  }

   */
}
