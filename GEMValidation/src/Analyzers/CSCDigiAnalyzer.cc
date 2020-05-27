#include "GEMCode/GEMValidation/interface/Analyzers/CSCDigiAnalyzer.h"

CSCDigiAnalyzer::CSCDigiAnalyzer(const CSCDigiMatcher& match_sh)
  :  match_(match_sh)
{
}

void CSCDigiAnalyzer::init(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCDigi");
}

void CSCDigiAnalyzer::analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations_to_use_)
{
  /*
  // CSC strip digis
  for(const auto& d: match_cd.chamberIdsStrip(0)) {
    CSCDetId id(d);
    const int st(detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const int nlayers(match_cd.nLayersWithStripInChamber(d));
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
  for(const auto& d: match_cd.chamberIdsWire(0)) {
    CSCDetId id(d);
    const int st(detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const int nlayers(match_cd.nLayersWithWireInChamber(d));
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
  */
}
