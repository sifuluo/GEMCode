#include "GEMCode/GEMValidation/interface/Analyzers/GEMStubAnalyzer.h"

GEMStubAnalyzer::GEMStubAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberGEMDigi");
}

void GEMStubAnalyzer::setMatcher(const GEMDigiMatcher& match_sh)
{
  match_.reset(new GEMDigiMatcher(match_sh));
}

void GEMStubAnalyzer::analyze(TreeManager& tree)
{
  // GEM pads in superchambers
  for(const auto& d: match_->chamberIdsPad()) {
    GEMDetId id(d);
    const int st = id.station();
    const bool odd(id.chamber()%2==1);
    const int nlayers(match_->nLayersWithPadsInSuperChamber(d));
    const int ilayer(id.layer());

    if (nlayers >= 1) {
      if (odd) tree.gemStub().has_gem_pad_odd[st] = true;
      else     tree.gemStub().has_gem_pad_even[st] = true;
    }

    if (nlayers >= 2) {
      if (odd) tree.gemStub().has_gem_pad2_odd[st] = true;
      else     tree.gemStub().has_gem_pad2_even[st] = true;
    }

    // best matching pad
    const auto& bestP(bestPad(id, match_->padsInChamber(id)).first);
    const auto& bestGP(bestPad(id, match_->padsInChamber(id)).second);

    if (ilayer == 1) {
      if (odd) {
        tree.gemStub().pad1_odd[st] = bestP.pad();
        tree.gemStub().bx_pad1_odd[st] = bestP.bx();
        tree.gemStub().z_pad1_odd[st] = bestGP.z();
        tree.gemStub().eta_pad1_odd[st] = bestGP.eta();
        tree.gemStub().phi_pad1_odd[st] = bestGP.phi();
      }
      else {
        tree.gemStub().pad1_even[st] = bestP.pad();
        tree.gemStub().bx_pad1_even[st] = bestP.bx();
        tree.gemStub().z_pad1_even[st] = bestGP.z();
        tree.gemStub().eta_pad1_even[st] = bestGP.eta();
        tree.gemStub().phi_pad1_even[st] = bestGP.phi();
      }
    }
    else {
      if (odd) {
        tree.gemStub().pad2_odd[st] = bestP.pad();
        tree.gemStub().bx_pad2_odd[st] = bestP.bx();
        tree.gemStub().z_pad2_odd[st] = bestGP.z();
        tree.gemStub().eta_pad2_odd[st] = bestGP.eta();
        tree.gemStub().phi_pad2_odd[st] = bestGP.phi();

      }
      else {
        tree.gemStub().pad2_even[st] = bestP.pad();
        tree.gemStub().bx_pad2_even[st] = bestP.bx();
        tree.gemStub().z_pad2_even[st] = bestGP.z();
        tree.gemStub().eta_pad2_even[st] = bestGP.eta();
        tree.gemStub().phi_pad2_even[st] = bestGP.phi();
      }
    }
  }

  for(const auto& d: match_->superChamberIdsCoPad()) {
    GEMDetId id(d);
    const int st = id.station();
    const bool odd(id.chamber()%2==1);
    if (odd) tree.gemStub().has_gem_copad_odd[st] = true;
    else     tree.gemStub().has_gem_copad_even[st] = true;

    // best matching coincidence pad
    const auto& bestP(bestCoPad(id, match_->coPadsInSuperChamber(id)).first);
    const auto& bestGP(bestCoPad(id, match_->coPadsInSuperChamber(id)).second);

    if (odd) {
      tree.gemStub().copad_odd[st] = bestP.pad(1);
      tree.gemStub().bx_copad_odd[st] = bestP.bx(1);
      tree.gemStub().z_copad_odd[st] = bestGP.z();
      tree.gemStub().eta_copad_odd[st] = bestGP.eta();
      tree.gemStub().phi_copad_odd[st] = bestGP.phi();
    }
    else {
      tree.gemStub().copad_even[st] = bestP.pad(1);
      tree.gemStub().bx_copad_even[st] = bestP.bx(1);
      tree.gemStub().z_copad_even[st] = bestGP.z();
      tree.gemStub().eta_copad_even[st] = bestGP.eta();
      tree.gemStub().phi_copad_even[st] = bestGP.phi();
    }
  }
}

std::pair<GEMPadDigi, GlobalPoint>
GEMStubAnalyzer::bestPad(const GEMDetId& id,
                         const GEMPadDigiContainer& digis) const
{
  const auto& mean(meanPosition(id, digis));
  float bestDPhi = 99;
  GEMPadDigi bestDigi;
  GlobalPoint bestGP;
  for(const auto& d: match_->padsInChamber(id.rawId())) {
    const GlobalPoint& gp = match_->getGlobalPointPad(id, d);
    const float dPhi = reco::deltaPhi(float(gp.phi()),float(mean.phi()));
    if (dPhi < bestDPhi) {
      bestDigi = d;
      bestDPhi = dPhi;
      bestGP = gp;
    }
  }
  return std::make_pair(bestDigi, bestGP);
}


std::pair<GEMCoPadDigi, GlobalPoint>
GEMStubAnalyzer::bestCoPad(const GEMDetId& id,
                           const GEMCoPadDigiContainer& digis) const
{
  const auto& mean(meanPosition(id, digis));
  float bestDPhi = 99;
  GEMCoPadDigi bestDigi;
  GlobalPoint bestGP;
  for(const auto& d: match_->coPadsInSuperChamber(id.rawId())) {
    const GlobalPoint& gp = match_->getGlobalPointPad(id, d.first());
    const float dPhi = reco::deltaPhi(float(gp.phi()),float(mean.phi()));
    if (dPhi < bestDPhi) {
      bestDigi = d;
      bestDPhi = dPhi;
      bestGP = gp;
    }
  }
  return std::make_pair(bestDigi, bestGP);
}


GlobalPoint
GEMStubAnalyzer::meanPosition(const GEMDetId& id,
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


GlobalPoint
GEMStubAnalyzer::meanPosition(const GEMDetId& id,
                              const GEMCoPadDigiContainer& digis) const
{
  GlobalPoint point_zero;
  if (digis.empty()) return point_zero; // point "zero"

  float sumx, sumy, sumz;
  sumx = sumy = sumz = 0.f;
  size_t n = 0;
  for (auto& d: digis){
    const GlobalPoint& gp = match_->getGlobalPointPad(id, d.first());
    if (gp == point_zero) continue;

    sumx += gp.x();
    sumy += gp.y();
    sumz += gp.z();
    ++n;
  }
  if (n == 0) return GlobalPoint();
  return GlobalPoint(sumx/n, sumy/n, sumz/n);
}
