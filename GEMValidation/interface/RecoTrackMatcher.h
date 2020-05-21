#ifndef GEMCode_GEMValidation_RecoTrackMatcher_h
#define GEMCode_GEMValidation_RecoTrackMatcher_h

/**\class RecoTrackMatcher

 Description: Matching of tracks to SimTrack

 Original Author:  "Sven Dildick"
*/

#include "GEMCode/GEMValidation/interface/CSCRecHitMatcher.h"
#include "GEMCode/GEMValidation/interface/DTRecHitMatcher.h"
#include "GEMCode/GEMValidation/interface/RPCRecHitMatcher.h"
#include "Validation/MuonGEMRecHits/interface/GEMRecHitMatcher.h"

#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/TrackReco/interface/TrackExtraFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

class RecoTrackMatcher
{
 public:
  /// constructor
  RecoTrackMatcher(edm::ParameterSet const& iPS, edm::ConsumesCollector&& iC);

  /// destructor
  ~RecoTrackMatcher() {}

  /// initialize the event
  void init(const edm::Event& e, const edm::EventSetup& eventSetup);

  /// do the matching
  void match(const SimTrack& t, const SimVertex& v);

  const reco::TrackExtraCollection& getMatchedRecoTrackExtras() const {return matchedRecoTrackExtras_;}
  const reco::TrackCollection& getMatchedRecoTracks() const {return matchedRecoTracks_;}
  const reco::RecoChargedCandidateCollection& getMatchedRecoChargedCandidates() const {return matchedRecoChargedCandidates_;}

 private:

  void clear();

  void matchRecoTrackExtraToSimTrack(const reco::TrackExtraCollection&);
  void matchRecoTrackToSimTrack(const reco::TrackCollection&);
  void matchRecoChargedCandidateToSimTrack(const reco::RecoChargedCandidateCollection&);

  template<typename T>
  bool areRecoTrackSame(const T&, const T&) const;

  edm::EDGetTokenT<reco::TrackExtraCollection> &recoTrackExtraInputLabel_;
  edm::EDGetTokenT<reco::TrackCollection> &recoTrackInputLabel_;
  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> &recoChargedCandidateInputLabel_;

  std::shared_ptr<GEMRecHitMatcher> gem_rechit_matcher_;
  std::shared_ptr<DTRecHitMatcher> dt_rechit_matcher_;
  std::shared_ptr<RPCRecHitMatcher> rpc_rechit_matcher_;
  std::shared_ptr<CSCRecHitMatcher> csc_rechit_matcher_;

  int minBXRecoTrackExtra_, maxBXRecoTrackExtra_;
  int verboseRecoTrackExtra_;
  bool runRecoTrackExtra_;

  int minBXRecoTrack_, maxBXRecoTrack_;
  int verboseRecoTrack_;
  bool runRecoTrack_;

  int minBXRecoChargedCandidate_, maxBXRecoChargedCandidate_;
  int verboseRecoChargedCandidate_;
  bool runRecoChargedCandidate_;

  reco::TrackExtraCollection matchedRecoTrackExtras_;
  reco::TrackCollection matchedRecoTracks_;
  reco::RecoChargedCandidateCollection matchedRecoChargedCandidates_;
};

#endif
