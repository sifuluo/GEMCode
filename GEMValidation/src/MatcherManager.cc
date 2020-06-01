#include "GEMCode/GEMValidation/interface/MatcherManager.h"

MatcherManager::MatcherManager(const edm::ParameterSet& iPS, edm::ConsumesCollector&& iC) {
  l1Muons_.reset(new L1MuMatcher(iPS, std::move(iC)));
  // tracks_.reset(new L1TrackMatcher(iPS, std::move(iC)));
  // gem_rechits_.reset(new GEMRecHitMatcher(iPS, std::move(iC)));
}

void MatcherManager::init(const edm::Event& e, const edm::EventSetup& eventSetup) {
  l1Muons_->init(e, eventSetup);
  // tracks_->init(e, eventSetup);
  // gem_rechits_->init(e, eventSetup);
}

/// do the matching
void MatcherManager::match(const SimTrack& t, const SimVertex& v) {
  l1Muons_->match(t, v);
  // tracks_->match(t, v);
  // gem_rechits_->match(t, v);
}
