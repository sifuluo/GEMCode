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
  // CSC strip digis
  for(const auto& d: match_.chamberIdsStrip(0)) {
    CSCDetId id(d);

    const int st(gem::detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const int nlayers(match_.nLayersWithStripInChamber(d));
    if (nlayers < minNHitsChamber_) continue;

    const bool odd(id.chamber()%2==1);
    if (odd) track[st].has_csc_strips |= 1;
    else track[st].has_csc_strips |= 2;

    if (odd) track[st].nlayers_st_dg_odd = nlayers;
    else track[st].nlayers_st_dg_even = nlayers;

    // case ME11
    if (st==2 or st==3){
      if (odd) track[1].has_csc_strips |= 1;
      else track[1].has_csc_strips |= 2;

      if (odd) track[1].nlayers_st_dg_odd = nlayers;
      else track[1].nlayers_st_dg_even = nlayers;
    }
  }

  // CSC wire digis
  for(const auto& d: match_.chamberIdsWire(0)) {
    CSCDetId id(d);
    const int st(gem::detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const int nlayers(match_.nLayersWithWireInChamber(d));
    if (nlayers < minNHitsChamber_) continue;

    const bool odd(id.chamber()%2==1);
    if (odd) track[st].has_csc_wires |= 1;
    else track[st].has_csc_wires |= 2;

    if (odd) track[st].nlayers_wg_dg_odd = nlayers;
    else track[st].nlayers_wg_dg_even = nlayers;

    // case ME11
    if (st==2 or st==3){
      if (odd) track[1].has_csc_wires |= 1;
      else track[1].has_csc_wires |= 2;

      if (odd) track[1].nlayers_wg_dg_odd = nlayers;
      else track[1].nlayers_wg_dg_even = nlayers;
    }
  }
}
