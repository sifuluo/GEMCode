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
  // GEM digis and pads in superchambers
  for(const auto& d: match_->superChamberIdsPad()) {
    GEMDetId id(d);
    const int st = id.station();
    const bool odd(id.chamber()%2==1);
    const int nlayers(match_->nLayersWithPadsInSuperChamber(d));

    if (nlayers >= 1) {
      if (odd) tree.gemStub().has_gem_pad_odd[st] = true;
      else     tree.gemStub().has_gem_pad_even[st] = true;
    }

    if (nlayers >= 2) {
      if (odd) tree.gemStub().has_gem_pad2_odd[st] = true;
      else     tree.gemStub().has_gem_pad2_even[st] = true;
    }
  }

  for(const auto& d: match_->superChamberIdsCoPad()) {
    GEMDetId id(d);
    const int st = id.station();
    const bool odd(id.chamber()%2==1);
    if (odd) tree.gemStub().has_gem_copad_odd[st] = true;
    else     tree.gemStub().has_gem_copad_even[st] = true;
  }
}
