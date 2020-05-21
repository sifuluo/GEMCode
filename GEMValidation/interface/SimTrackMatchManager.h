#ifndef GEMCode_GEMValidation_SimTrackMatchManager_h
#define GEMCode_GEMValidation_SimTrackMatchManager_h

#include "Validation/MuonCSCDigis/interface/CSCStubMatcher.h"
#include "Validation/MuonGEMRecHits/interface/GEMRecHitMatcher.h"
#include "GEMCode/GEMValidation/interface/L1MuMatcher.h"
#include "GEMCode/GEMValidation/interface/L1TrackMatcher.h"
#include "GEMCode/GEMValidation/interface/ME0DigiMatcher.h"

class SimTrackMatchManager
{
public:
  SimTrackMatchManager(edm::ParameterSet const& iPS, edm::ConsumesCollector&& iC);

  ~SimTrackMatchManager() {}

  void init(const edm::Event& e, const edm::EventSetup& eventSetup);

  /// do the matching
  void match(const SimTrack& t, const SimVertex& v);

  // accessors
  std::shared_ptr<GEMSimHitMatcher> gemSimHits() const { return gemDigis()->muonSimHitMatcher(); }
  std::shared_ptr<CSCSimHitMatcher> cscSimHits() const { return cscDigis()->muonSimHitMatcher(); }

  std::shared_ptr<GEMDigiMatcher> gemDigis() const { return cscStubs()->gemDigiMatcher(); }
  std::shared_ptr<CSCDigiMatcher> cscDigis() const { return cscStubs()->cscDigiMatcher(); }
  std::shared_ptr<ME0DigiMatcher> me0Digis() const { return me0_digis_; }

  std::shared_ptr<CSCStubMatcher> cscStubs() const { return muons_->cscStubMatcher(); }

  std::shared_ptr<GEMRecHitMatcher> gemRecHits() const { return gem_rechits_; }

  std::shared_ptr<L1MuMatcher> l1Muons() const { return muons_; }

  std::shared_ptr<L1TrackMatcher> l1Tracks() const { return tracks_; }

private:
  // top level matcher right now
  std::shared_ptr<L1MuMatcher> muons_;
  std::shared_ptr<L1TrackMatcher> tracks_;
  std::shared_ptr<GEMRecHitMatcher> gem_rechits_;
  std::shared_ptr<ME0DigiMatcher> me0_digis_;
};

#endif
