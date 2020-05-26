#ifndef GEMCode_GEMValidation_SimTrackMatchManager_h
#define GEMCode_GEMValidation_SimTrackMatchManager_h

#include "Validation/MuonCSCDigis/interface/CSCStubMatcher.h"
#include "Validation/MuonGEMRecHits/interface/GEMRecHitMatcher.h"
#include "GEMCode/GEMValidation/interface/L1MuMatcher.h"
#include "GEMCode/GEMValidation/interface/L1TrackMatcher.h"
#include "GEMCode/GEMValidation/interface/ME0DigiMatcher.h"
#include "GEMCode/GEMValidation/interface/RPCDigiMatcher.h"
#include "GEMCode/GEMValidation/interface/DTDigiMatcher.h"
#include "GEMCode/GEMValidation/interface/GenParticleMatcher.h"
#include "GEMCode/GEMValidation/interface/RecoTrackMatcher.h"

class SimTrackMatchManager
{
public:
  SimTrackMatchManager(edm::ParameterSet const& iPS, edm::ConsumesCollector&& iC);

  ~SimTrackMatchManager() {}

  void init(const edm::Event& e, const edm::EventSetup& eventSetup);

  /// do the matching
  void match(const SimTrack& t, const SimVertex& v);

  // accessors
  std::shared_ptr<GenParticleMatcher> genParticles() const { return genParticles_; }

  std::shared_ptr<GEMSimHitMatcher> gemSimHits() const { return gemDigis()->muonSimHitMatcher(); }
  std::shared_ptr<CSCSimHitMatcher> cscSimHits() const { return cscDigis()->muonSimHitMatcher(); }
  std::shared_ptr<RPCSimHitMatcher> rpcSimHits() const { return rpcDigis()->muonSimHitMatcher(); }
  std::shared_ptr<DTSimHitMatcher> dtSimHits() const { return dtDigis()->muonSimHitMatcher(); }
  std::shared_ptr<ME0SimHitMatcher> me0SimHits() const { return me0Digis()->muonSimHitMatcher(); }

  std::shared_ptr<GEMDigiMatcher> gemDigis() const { return cscStubs()->gemDigiMatcher(); }
  std::shared_ptr<CSCDigiMatcher> cscDigis() const { return cscStubs()->cscDigiMatcher(); }
  std::shared_ptr<RPCDigiMatcher> rpcDigis() const { return rpcRecHits()->rpcDigiMatcher(); }
  std::shared_ptr<ME0DigiMatcher> me0Digis() const { return me0_digis_; }
  std::shared_ptr<DTDigiMatcher> dtDigis() const { return dtRecHits()->dtDigiMatcher(); }

  std::shared_ptr<CSCStubMatcher> cscStubs() const { return l1Muons_->cscStubMatcher(); }

  std::shared_ptr<GEMRecHitMatcher> gemRecHits() const { return recoTracks_->gemRecHits(); }
  std::shared_ptr<RPCRecHitMatcher> rpcRecHits() const { return recoTracks_->rpcRecHits(); }
  std::shared_ptr<CSCRecHitMatcher> cscRecHits() const { return recoTracks_->cscRecHits(); }
  std::shared_ptr<DTRecHitMatcher> dtRecHits() const { return recoTracks_->dtRecHits(); }

  std::shared_ptr<L1MuMatcher> l1Muons() const { return l1Muons_; }
  std::shared_ptr<L1TrackMatcher> l1Tracks() const { return l1Tracks_; }
  std::shared_ptr<RecoTrackMatcher> recoTracks() const { return recoTracks_; }

private:
  // top level matcher right now
  std::shared_ptr<GenParticleMatcher> genParticles_;
  std::shared_ptr<ME0DigiMatcher> me0_digis_;
  std::shared_ptr<L1MuMatcher> l1Muons_;
  std::shared_ptr<L1TrackMatcher> l1Tracks_;
  std::shared_ptr<RecoTrackMatcher> recoTracks_;
};

#endif
