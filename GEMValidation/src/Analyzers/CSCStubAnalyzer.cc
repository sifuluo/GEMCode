#include "GEMCode/GEMValidation/interface/Analyzers/CSCStubAnalyzer.h"

CSCStubAnalyzer::CSCStubAnalyzer(const CSCStubMatcher& match_sh)
{
  match_.reset(new CSCStubMatcher(match_sh));
}

void CSCStubAnalyzer::init(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCStub");
}

void CSCStubAnalyzer::analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations_to_use_)
{
  // CSC CLCTs
  for(const auto& d: match_->chamberIdsCLCT(0)) {
    CSCDetId id(d);

    const int st(gem::detIdToMEStation(id.station(),id.ring()));
    if (std::find(stations_to_use_.begin(), stations_to_use_.end(), st) != stations_to_use_.end()) continue;

    const bool odd(id.chamber()%2==1);
    const auto& clct = match_->bestClctInChamber(d);

    if (odd) {
      track[st].has_clct |= 1;
      track[st].chamber_dg_odd = id.chamber();
      track[st].halfstrip_odd = clct.getKeyStrip();
      track[st].quality_clct_odd = clct.getQuality();
      track[st].bx_clct_odd = clct.getBX();
    }
    else {
      track[st].has_clct |= 2;
      track[st].chamber_dg_even = id.chamber();
      track[st].halfstrip_even = clct.getKeyStrip();
      track[st].quality_clct_even = clct.getQuality();
      track[st].bx_clct_even = clct.getBX();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        track[1].has_clct |= 1;
        track[1].chamber_dg_odd = id.chamber();
        track[1].halfstrip_odd = clct.getKeyStrip();
        track[1].quality_clct_odd = clct.getQuality();
        track[1].bx_clct_odd = clct.getBX();
      }
      else {
        track[1].has_clct |= 2;
        track[1].chamber_dg_even = id.chamber();
        track[1].halfstrip_even = clct.getKeyStrip();
        track[1].quality_clct_even = clct.getQuality();
        track[1].bx_clct_even = clct.getBX();
      }
    }
  }

  // CSC ALCTs
  for(const auto& d: match_->chamberIdsALCT(0)) {
    CSCDetId id(d);
    const int st(gem::detIdToMEStation(id.station(),id.ring()));
    if (std::find(stations_to_use_.begin(), stations_to_use_.end(), st) != stations_to_use_.end()) continue;

    const bool odd(id.chamber()%2==1);
    const auto& alct = match_->bestAlctInChamber(d);

    if (odd) {
      track[st].has_alct |= 1;
      track[st].chamber_dg_odd = id.chamber();
      track[st].wiregroup_odd = alct.getKeyWG();
      track[st].quality_alct_odd = alct.getQuality();
      track[st].bx_alct_odd = alct.getBX();
    }
    else {
      track[st].has_alct |= 2;
      track[st].chamber_dg_even = id.chamber();
      track[st].wiregroup_even = alct.getKeyWG();
      track[st].quality_alct_even = alct.getQuality();
      track[st].bx_alct_even = alct.getBX();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        track[1].has_alct |= 1;
        track[1].chamber_dg_odd = id.chamber();
        track[1].wiregroup_odd = alct.getKeyWG();
        track[1].quality_alct_odd = alct.getQuality();
        track[1].bx_alct_odd = alct.getBX();
      }
      else {
        track[1].has_alct |= 2;
        track[1].chamber_dg_even = id.chamber();
        track[1].wiregroup_even = alct.getKeyWG();
        track[1].quality_alct_even = alct.getQuality();
        track[1].bx_alct_even = alct.getBX();
      }
    }

    // CSC LCTs
    for(const auto& d: match_->chamberIdsLCT(0)) {
      CSCDetId id(d);
      const int st(gem::detIdToMEStation(id.station(),id.ring()));
      if (std::find(stations_to_use_.begin(), stations_to_use_.end(), st) != stations_to_use_.end()) continue;

      const auto& lct = match_->bestLctInChamber(d);
      const GlobalPoint& gp = match_->getGlobalPosition(d, lct);

      const bool odd(id.chamber()%2==1);
      if (odd) {
        track[st].has_lct |= 1;
        track[st].bend_lct_odd = lct.getPattern();
        track[st].phi_lct_odd = gp.phi();
        track[st].eta_lct_odd = gp.eta();
        track[st].perp_lct_odd = gp.perp();
        track[st].bx_lct_odd = lct.getBX();
        track[st].hs_lct_odd = lct.getStrip();
        track[st].wg_lct_odd = lct.getKeyWG();
        track[st].quality_odd = lct.getQuality();
      }
      else {
        track[st].has_lct |= 2;
        track[st].bend_lct_even = lct.getPattern();
        track[st].phi_lct_even = gp.phi();
        track[st].eta_lct_even = gp.eta();
        track[st].perp_lct_even = gp.perp();
        track[st].bx_lct_even = lct.getBX();
        track[st].hs_lct_even = lct.getStrip();
        track[st].wg_lct_even = lct.getKeyWG();
        track[st].quality_even = lct.getQuality();
      }
      // case ME11
      if (st==2 or st==3){
        if (odd) {
          track[1].has_lct |= 1;
          track[1].bend_lct_odd = lct.getPattern();
          track[1].phi_lct_odd = gp.phi();
          track[1].eta_lct_odd = gp.eta();
          track[1].perp_lct_odd = gp.perp();
          track[1].bx_lct_odd = lct.getBX();
          track[1].hs_lct_odd = lct.getStrip();
          track[1].wg_lct_odd = lct.getKeyWG();
          track[1].quality_odd = lct.getQuality();
        }
        else {
          track[1].has_lct |= 2;
          track[1].bend_lct_even = lct.getPattern();
          track[1].phi_lct_even = gp.phi();
          track[1].eta_lct_even = gp.eta();
          track[1].perp_lct_even = gp.perp();
          track[1].bx_lct_even = lct.getBX();
          track[1].hs_lct_even = lct.getStrip();
          track[1].wg_lct_even = lct.getKeyWG();
          track[1].quality_even = lct.getQuality();
        }
      }
    }
  }
}
