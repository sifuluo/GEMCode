#include "GEMCode/GEMValidation/interface/Analyzers/GEMDigiAnalyzer.h"

GEMDigiAnalyzer::GEMDigiAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberGEMDigi");
}

void GEMDigiAnalyzer::setMatcher(const GEMDigiMatcher& match_sh)
{
  match_.reset(new GEMDigiMatcher(match_sh));
}

void GEMDigiAnalyzer::analyze(TreeManager& tree)
{
  for(const auto& d: match_->superChamberIdsDigi()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(gem::detIdToMEStation(MEStation,id.ring()));

    const bool odd(id.chamber()%2==1);

    const int median_strip(median(match_->digisInSuperChamber(d)));
    if (match_->digisInSuperChamber(d).size() > 0) {
      if (odd) {
        tree.gemDigi().has_gem_dg_odd[st] = true;
        tree.gemDigi().strip_gemdg_odd[st] = median_strip;
      }
      else {
        tree.gemDigi().has_gem_dg_even[st] = true;
        tree.gemDigi().strip_gemdg_even[st] = median_strip;
      }
    }

    if (match_->nLayersWithDigisInSuperChamber(d) >= 2) {
      if (odd) tree.gemDigi().has_gem_dg2_odd[st] = true;
      else     tree.gemDigi().has_gem_dg2_even[st] = true;
    }
  }
}

int GEMDigiAnalyzer::median(const GEMDigiContainer& digis) const
{
  size_t sz = digis.size();
  vector<int> strips(sz);
  std::transform(digis.begin(), digis.end(), strips.begin(), [](const GEMDigi& d) {return d.strip();} );
  std::sort(strips.begin(), strips.end());
  if ( sz % 2 == 0 ) // even
    {
      return (strips[sz/2 - 1] + strips[sz/2])/2;
    }
  else
    {
      return strips[sz/2];
    }
}
