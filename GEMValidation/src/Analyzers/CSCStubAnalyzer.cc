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

    const int stt( std::find(stations_to_use_.begin(), stations_to_use_.end(), st) - stations_to_use_.begin());

    const bool odd(id.chamber()%2==1);
    const auto& clct = match_->bestClctInChamber(d);

    if (odd) {
      track[stt].has_clct_odd = true;
      track[stt].chamber_dg_odd = id.chamber();
      track[stt].halfstrip_odd = clct.getKeyStrip();
      track[stt].quality_clct_odd = clct.getQuality();
      track[stt].bx_clct_odd = clct.getBX();
    }
    else {
      track[stt].has_clct_even = true;
      track[stt].chamber_dg_even = id.chamber();
      track[stt].halfstrip_even = clct.getKeyStrip();
      track[stt].quality_clct_even = clct.getQuality();
      track[stt].bx_clct_even = clct.getBX();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        track[1].has_clct_odd = true;
        track[1].chamber_dg_odd = id.chamber();
        track[1].halfstrip_odd = clct.getKeyStrip();
        track[1].quality_clct_odd = clct.getQuality();
        track[1].bx_clct_odd = clct.getBX();
      }
      else {
        track[1].has_clct_even = true;
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

    const int stt( std::find(stations_to_use_.begin(), stations_to_use_.end(), st) - stations_to_use_.begin());

    const bool odd(id.chamber()%2==1);
    const auto& alct = match_->bestAlctInChamber(d);

    if (odd) {
      track[stt].has_alct_odd = true;
      track[stt].chamber_dg_odd = id.chamber();
      track[stt].wiregroup_odd = alct.getKeyWG();
      track[stt].quality_alct_odd = alct.getQuality();
      track[stt].bx_alct_odd = alct.getBX();
    }
    else {
      track[stt].has_alct_even = true;
      track[stt].chamber_dg_even = id.chamber();
      track[stt].wiregroup_even = alct.getKeyWG();
      track[stt].quality_alct_even = alct.getQuality();
      track[stt].bx_alct_even = alct.getBX();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        track[1].has_alct_odd = true;
        track[1].chamber_dg_odd = id.chamber();
        track[1].wiregroup_odd = alct.getKeyWG();
        track[1].quality_alct_odd = alct.getQuality();
        track[1].bx_alct_odd = alct.getBX();
      }
      else {
        track[1].has_alct_even = true;
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

    const int stt( std::find(stations_to_use_.begin(), stations_to_use_.end(), st) - stations_to_use_.begin());

      const auto& lct = match_->bestLctInChamber(d);
      const GlobalPoint& gp = match_->getGlobalPosition(d, lct);

      const bool odd(id.chamber()%2==1);
      if (odd) {
        track[stt].has_lct_odd = true;
        track[stt].bend_lct_odd = lct.getPattern();
        track[stt].phi_lct_odd = gp.phi();
        track[stt].eta_lct_odd = gp.eta();
        track[stt].perp_lct_odd = gp.perp();
        track[stt].bx_lct_odd = lct.getBX();
        track[stt].hs_lct_odd = lct.getStrip();
        track[stt].wg_lct_odd = lct.getKeyWG();
        track[stt].quality_odd = lct.getQuality();
      }
      else {
        track[stt].has_lct_even = true;
        track[stt].bend_lct_even = lct.getPattern();
        track[stt].phi_lct_even = gp.phi();
        track[stt].eta_lct_even = gp.eta();
        track[stt].perp_lct_even = gp.perp();
        track[stt].bx_lct_even = lct.getBX();
        track[stt].hs_lct_even = lct.getStrip();
        track[stt].wg_lct_even = lct.getKeyWG();
        track[stt].quality_even = lct.getQuality();
      }
      // case ME11
      if (st==2 or st==3){
        if (odd) {
          track[1].has_lct_odd = true;
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
          track[1].has_lct_even = true;
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
