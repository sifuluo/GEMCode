#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

SimTrackMatchManager::SimTrackMatchManager(const edm::ParameterSet& iPS, edm::ConsumesCollector&& iC) {
  csc_stubs_.reset(new CSCStubMatcher(iPS, std::move(iC)));
  gem_rechits_.reset(new GEMRecHitMatcher(iPS, std::move(iC)));
}

void SimTrackMatchManager::init(const edm::Event& e, const edm::EventSetup& eventSetup) {
  csc_stubs_->init(e, eventSetup);
  gem_rechits_->init(e, eventSetup);
}

/// do the matching
void SimTrackMatchManager::match(const SimTrack& t, const SimVertex& v) {
  csc_stubs_->match(t, v);
  gem_rechits_->match(t, v);
}
