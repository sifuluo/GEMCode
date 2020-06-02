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
  for(const auto& d: match_->chamberIdsDigi()) {
    GEMDetId id(d);
    GEMDetId scid(id.superChamberId());

    const int st = id.station();
    const bool odd(id.chamber()%2==1);

    const int median_strip(median(match_->digisInChamber(d)));
    if (match_->digisInChamber(d).size() >= 1) {
      if (odd) {
        tree.gemDigi().has_gem_dg_odd[st] = true;
        tree.gemDigi().strip_gemdg_odd[st] = median_strip;
      }
      else {
        tree.gemDigi().has_gem_dg_even[st] = true;
        tree.gemDigi().strip_gemdg_even[st] = median_strip;
      }
    }

    if (match_->nLayersWithDigisInSuperChamber(scid.rawId()) == 2) {
      if (odd) tree.gemDigi().has_gem_dg2_odd[st] = true;
      else     tree.gemDigi().has_gem_dg2_even[st] = true;
    }

    // find the best matching GEM pad

  }
}

int GEMDigiAnalyzer::median(const GEMDigiContainer& digis) const
{
  size_t sz = digis.size();
  vector<int> strips(sz);
  std::transform(digis.begin(), digis.end(),
                 strips.begin(), [](const GEMDigi& d) {return d.strip();} );
  std::sort(strips.begin(), strips.end());
  if ( sz % 2 == 0 ) {
    return (strips[sz/2 - 1] + strips[sz/2])/2;
  }
  else {
    return strips[sz/2];
  }
}

GlobalPoint
GEMDigiAnalyzer::meanPosition(const GEMDetId& id,
                              const GEMDigiContainer& digis) const
{
  GlobalPoint point_zero;
  if (digis.empty()) return point_zero; // point "zero"

  float sumx, sumy, sumz;
  sumx = sumy = sumz = 0.f;
  size_t n = 0;
  for (auto& d: digis){
    const GlobalPoint& gp = match_->getGlobalPointDigi(id, d);
    if (gp == point_zero) continue;

    sumx += gp.x();
    sumy += gp.y();
    sumz += gp.z();
    ++n;
  }
  if (n == 0) return GlobalPoint();
  return GlobalPoint(sumx/n, sumy/n, sumz/n);
}

GlobalPoint
GEMDigiAnalyzer::meanPosition(const GEMDetId& id,
                              const GEMPadDigiContainer& digis) const
{
  GlobalPoint point_zero;
  if (digis.empty()) return point_zero; // point "zero"

  float sumx, sumy, sumz;
  sumx = sumy = sumz = 0.f;
  size_t n = 0;
  for (auto& d: digis){
    const GlobalPoint& gp = match_->getGlobalPointPad(id, d);
    if (gp == point_zero) continue;

    sumx += gp.x();
    sumy += gp.y();
    sumz += gp.z();
    ++n;
  }
  if (n == 0) return GlobalPoint();
  return GlobalPoint(sumx/n, sumy/n, sumz/n);
}
