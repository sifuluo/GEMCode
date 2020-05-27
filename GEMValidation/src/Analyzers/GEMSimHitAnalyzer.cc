#include "GEMCode/GEMValidation/interface/Analyzers/GEMSimHitAnalyzer.h"

GEMSimHitAnalyzer::GEMSimHitAnalyzer(const GEMSimHitMatcher& match_sh)
  :  match_(match_sh)
{
}

void GEMSimHitAnalyzer::analyze(MyTrack track[NumOfTrees])
{
  /*
  //for GEMs in station1, it will be also filled in ME11
  // GEM simhits in superchamber
  GlobalPoint gp_gemsh_odd[12];
  GlobalPoint gp_gemsh_even[12];
  for(const auto& d: match_gem_sh.superChamberIds()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (match_gem_sh.hitsInSuperChamber(d).size() > 0) {

      if (odd) etrk_[st].has_gem_sh |= 1;
      else     etrk_[st].has_gem_sh |= 2;

      const float mean_strip(match_gem_sh.simHitsMeanStrip(match_gem_sh.hitsInSuperChamber(d)));
      if (odd) etrk_[st].strip_gemsh_odd = mean_strip;
      else     etrk_[st].strip_gemsh_even = mean_strip;
    }

    if (match_gem_sh.nLayersWithHitsInSuperChamber(d) > 1) {
      //std::cout <<"GEM detid "<< id <<" has at 2 layer hits "<< std::endl;
      if (odd) etrk_[st].has_gem_sh2 |= 1;
      else     etrk_[st].has_gem_sh2 |= 2;
    }
    const auto& copad_superids (match_gem_sh.superChamberIdsCoincidences());
    if (copad_superids.find(d) != copad_superids.end()) {
      //std::cout <<"GEM detid "<< id <<" has copad hits "<< std::endl;
      if (odd) etrk_[st].has_gemcopad_sh |= 1;
      else     etrk_[st].has_gemcopad_sh |= 2;
    }
    //ME11 Case
    if (st==2 or st==3) {
      if (odd) etrk_[1].has_gem_sh |= 1;
      else     etrk_[1].has_gem_sh |= 2;

      const float mean_strip(match_gem_sh.simHitsMeanStrip(match_gem_sh.hitsInSuperChamber(d)));
      if (odd) etrk_[1].strip_gemsh_odd = mean_strip;
      else     etrk_[1].strip_gemsh_even = mean_strip;

      if (match_gem_sh.nLayersWithHitsInSuperChamber(d) > 1) {
        if (odd) etrk_[1].has_gem_sh2 |= 1;
        else     etrk_[1].has_gem_sh2 |= 2;

      }
      if (copad_superids.find(d) != copad_superids.end()){
        if (odd) etrk_[1].has_gemcopad_sh |= 1;
        else     etrk_[1].has_gemcopad_sh |= 2;
      }
    }//end of ME11 case
  }

   */
}
