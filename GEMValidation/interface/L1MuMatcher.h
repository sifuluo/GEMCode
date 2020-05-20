#ifndef GEMCode_GEMValidation_L1MuMatcher_h
#define GEMCode_GEMValidation_L1MuMatcher_h

/**\class L1MuMatcher

 Description: Matching of tracks to SimTrack

 Original Author:  "Sven Dildick"
*/
/* #include "GEMCode/GEMValidation/interface/TFTrack.h" */
/* #include "GEMCode/GEMValidation/interface/TFCand.h" */

#include "Validation/MuonCSCDigis/interface/CSCStubMatcher.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/L1TMuon/interface/EMTFTrack.h"
#include "DataFormats/L1TMuon/interface/EMTFHit.h"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"
#include "DataFormats/L1Trigger/interface/Muon.h"

class L1MuMatcher
{
 public:
  /// constructor
  L1MuMatcher(edm::ParameterSet const& iPS, edm::ConsumesCollector&& iC);

  /// destructor
  ~L1MuMatcher() {}

  /// initialize the event
  void init(const edm::Event& e, const edm::EventSetup& eventSetup);

  /// do the matching
  void match(const SimTrack& t, const SimVertex& v);

  // return best matching tracks
  const l1t::EMTFTrack* emtfTrack() const { return emtfTrack_; }
  const l1t::RegionalMuonCand* emtfCand() const { return emtfCand_; }
  const l1t::Muon* muon() const { return muon_; }

  std::shared_ptr<CSCStubMatcher> cscStubMatcher() { return cscStubMatcher_; }

 private:

  void clear();

  void matchEmtfTrackToSimTrack(const l1t::EMTFTrackCollection&);
  void matchRegionalMuonCandToSimTrack(const l1t::RegionalMuonCandBxCollection&);
  void matchGMTToSimTrack(const l1t::MuonBxCollection&);

  edm::EDGetTokenT<l1t::EMTFTrackCollection> emtfTrackToken_;
  edm::EDGetTokenT<l1t::RegionalMuonCandBxCollection> emtfCandToken_;
  edm::EDGetTokenT<l1t::MuonBxCollection> muonToken_;

  edm::Handle<l1t::EMTFTrackCollection> emtfTrackHandle_;
  edm::Handle<l1t::RegionalMuonCandBxCollection> emtfCandHandle_;
  edm::Handle<l1t::MuonBxCollection> muonHandle_;

  std::shared_ptr<CSCStubMatcher> cscStubMatcher_;

  int minBXEMTFTrack_, maxBXEMTFTrack_;
  int verboseEMTFTrack_;
  double deltaREMTFTrack_;
  bool runEMTFTrack_;

  int minBXRegMuCand_, maxBXRegMuCand_;
  int verboseRegMuCand_;
  double deltaRRegMuCand_;
  bool runRegMuCand_;

  int minBXGMT_, maxBXGMT_;
  int verboseGMT_;
  double deltaRGMT_;
  bool runGMT_;

  const l1t::EMTFTrack* emtfTrack_;
  const l1t::RegionalMuonCand* emtfCand_;
  const l1t::Muon* muon_;
};

#endif
