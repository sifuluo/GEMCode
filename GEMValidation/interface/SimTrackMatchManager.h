#ifndef GEMCode_GEMValidation_SimTrackMatchManager_h
#define GEMCode_GEMValidation_SimTrackMatchManager_h

#include "Validation/MuonCSCDigis/interface/CSCStubMatcher.h"

class SimTrackMatchManager {
public:
  SimTrackMatchManager(edm::ParameterSet const& iPS, edm::ConsumesCollector&& iC);

  ~SimTrackMatchManager() {}

  void init(const edm::Event& e, const edm::EventSetup& eventSetup);

  /// do the matching
  void match(const SimTrack& t, const SimVertex& v);

  std::shared_ptr<GEMSimHitMatcher> gemsimhits() const { return csc_stubs_->gemDigiMatcher()->muonSimHitMatcher(); }
  std::shared_ptr<CSCSimHitMatcher> cscsimhits() const { return csc_stubs_->cscDigiMatcher()->muonSimHitMatcher(); }

  std::shared_ptr<GEMDigiMatcher> gemDigis() const { return csc_stubs_->gemDigiMatcher(); }
  std::shared_ptr<CSCDigiMatcher> cscDigis() const { return csc_stubs_->cscDigiMatcher(); }

  std::shared_ptr<CSCStubMatcher> cscStubs() const { return csc_stubs_; }

private:
  // top level matcher right now
  std::shared_ptr<CSCStubMatcher> csc_stubs_;
};

#endif
