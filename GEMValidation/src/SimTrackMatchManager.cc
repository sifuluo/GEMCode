#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

SimTrackMatchManager::SimTrackMatchManager(const edm::ParameterSet& iPS, edm::ConsumesCollector&& iC) {
  muons_.reset(new L1MuMatcher(iPS, std::move(iC)));
  //  gem_rechits_.reset(new GEMRecHitMatcher(iPS, std::move(iC)));
}

void SimTrackMatchManager::init(const edm::Event& e, const edm::EventSetup& eventSetup) {
  muons_->init(e, eventSetup);
  //  gem_rechits_->init(e, eventSetup);
}

/// do the matching
void SimTrackMatchManager::match(const SimTrack& t, const SimVertex& v) {
  muons_->match(t, v);
  //  gem_rechits_->match(t, v);
}
