#include "GEMCode/GEMValidation/interface/Analyzers/GEMSimHitAnalyzer.h"

GEMSimHitAnalyzer::GEMSimHitAnalyzer(const GEMSimHitMatcher& match_sh)
{
  match_.reset(new GEMSimHitMatcher(match_sh));
}

void GEMSimHitAnalyzer::init(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberGEMSimHit");
}

void GEMSimHitAnalyzer::analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations_to_use_)
{
  // for GEMs in station1, it will be also filled in ME11
  // GEM simhits in superchamber
  for(const auto& d: match_->superChamberIds()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(gem::detIdToMEStation(MEStation,id.ring()));
    if (std::find(stations_to_use_.begin(), stations_to_use_.end(), st) != stations_to_use_.end()) continue;

    const bool odd(id.chamber()%2==1);

    auto& match = match_;
    auto fill = [track, d, match, odd] (int st) mutable {
      if (match->hitsInSuperChamber(d).size() > 0) {
        if (odd) {
          track[st].has_gem_sh_odd = true;
        }
        else {
          track[st].has_gem_sh_even = true;
        }
        const float mean_strip(match->simHitsMeanStrip(match->hitsInSuperChamber(d)));
        if (odd) track[st].strip_gemsh_odd = mean_strip;
        else     track[st].strip_gemsh_even = mean_strip;
      }
      if (match->nLayersWithHitsInSuperChamber(d) >= 2) {
        if (odd) track[st].has_gem_sh2_odd = true;
        else     track[st].has_gem_sh2_even = true;
      }
      const auto& copad_superids (match->superChamberIdsCoincidences());
      if (copad_superids.find(d) != copad_superids.end()) {
        if (odd) track[st].has_gemcopad_sh_odd = true;
        else     track[st].has_gemcopad_sh_even = true;
      }
    };

    fill(st);
    if (st==2 or st==3) {
      fill(1);
    }
  }
}
