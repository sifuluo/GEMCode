#ifndef GEMCode_GEMValidation_UpgradeL1TrackMatcher_h
#define GEMCode_GEMValidation_UpgradeL1TrackMatcher_h

/**\class UpgradeL1TrackMatcher

 Description: Matching of tracks to SimTrack

 Original Author:  "Sven Dildick"
*/
#include "GEMCode/GEMValidation/interface/BaseMatcher.h"
#include "GEMCode/GEMValidation/interface/UpgradeL1MuMatcher.h"
#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"
//#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticleFwd.h"
//#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticle.h"

typedef TTTrack<Ref_Phase2TrackerDigi_> L1TTTrackType;
typedef std::vector<L1TTTrackType> L1TTTrackCollectionType;

class UpgradeL1TrackMatcher : public BaseMatcher {
public:
  UpgradeL1TrackMatcher(UpgradeL1MuMatcher&);

  /// destructor
  ~UpgradeL1TrackMatcher();
  /*
  /// constructor
  UpgradeL1TrackMatcher(
      UpgradeL1MuMatcher&,
      edm::EDGetTokenT<L1TTTrackCollectionType>&,
      edm::EDGetTokenT<l1t::L1TkMuonParticleCollection>&);


  L1TTTrackType* bestL1Track() const { return bestTrack_; }
  l1t::L1TkMuonParticle* bestTrackMuon() const { return bestTrackMuon_; }

 private:

  void clear();

  void matchL1TrackToSimTrack(const L1TTTrackCollectionType&);
  void matchTrackMuonToSimTrack(const l1t::L1TkMuonParticleCollection&);

  int minBXTrack_, maxBXTrack_;
  int verboseTrack_;
  double deltaRTrack_;

  int minBXTrackMuon_, maxBXTrackMuon_;
  int verboseTrackMuon_;
  double deltaRTrackMuon_;

  L1TTTrackType* bestTrack_;
  l1t::L1TkMuonParticle* bestTrackMuon_;
  */
  UpgradeL1MuMatcher* matcher_;
};

#endif
