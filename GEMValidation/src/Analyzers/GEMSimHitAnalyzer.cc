#include "GEMCode/GEMValidation/interface/Analyzers/GEMSimHitAnalyzer.h"

GEMSimHitAnalyzer::GEMSimHitAnalyzer(const GEMSimHitMatcher& match_sh)
  :  match_(match_sh)
{
}

void GEMSimHitAnalyzer::init(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberGEMSimHit");
}

void GEMSimHitAnalyzer::analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations_to_use_)
{
  // for GEMs in station1, it will be also filled in ME11
  // GEM simhits in superchamber
  for(const auto& d: match_.superChamberIds()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(gem::detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (match_.hitsInSuperChamber(d).size() > 0) {

      if (odd) track[st].has_gem_sh |= 1;
      else     track[st].has_gem_sh |= 2;

      const float mean_strip(match_.simHitsMeanStrip(match_.hitsInSuperChamber(d)));
      if (odd) track[st].strip_gemsh_odd = mean_strip;
      else     track[st].strip_gemsh_even = mean_strip;
    }

    if (match_.nLayersWithHitsInSuperChamber(d) >= 2) {
      //std::cout <<"GEM detid "<< id <<" has at 2 layer hits "<< std::endl;
      if (odd) track[st].has_gem_sh2 |= 1;
      else     track[st].has_gem_sh2 |= 2;
    }
    const auto& copad_superids (match_.superChamberIdsCoincidences());
    if (copad_superids.find(d) != copad_superids.end()) {
      //std::cout <<"GEM detid "<< id <<" has copad hits "<< std::endl;
      if (odd) track[st].has_gemcopad_sh |= 1;
      else     track[st].has_gemcopad_sh |= 2;
    }

    //ME11 Case
    if (st==2 or st==3) {
      if (odd) track[1].has_gem_sh |= 1;
      else     track[1].has_gem_sh |= 2;

      const float mean_strip(match_.simHitsMeanStrip(match_.hitsInSuperChamber(d)));
      if (odd) track[1].strip_gemsh_odd = mean_strip;
      else     track[1].strip_gemsh_even = mean_strip;

      if (match_.nLayersWithHitsInSuperChamber(d) >= 2) {
        if (odd) track[1].has_gem_sh2 |= 1;
        else     track[1].has_gem_sh2 |= 2;

      }
      if (copad_superids.find(d) != copad_superids.end()){
        if (odd) track[1].has_gemcopad_sh |= 1;
        else     track[1].has_gemcopad_sh |= 2;
      }
    }//end of ME11 case
  }
}
