#include "GEMCode/GEMValidation/interface/UpgradeL1TrackMatcher.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "TLorentzVector.h"
#include <map>

UpgradeL1TrackMatcher::UpgradeL1TrackMatcher(
    UpgradeL1MuMatcher& matcher,
    edm::EDGetTokenT<L1TTTrackCollectionType>& trackLabel,
    edm::EDGetTokenT<l1t::L1TkMuonParticleCollection>& tkmuons) :
  BaseMatcher(matcher.trk(),
              matcher.vtx(),
              matcher.conf(),
              matcher.event(),
              matcher.eventSetup())
  , matcher_(&matcher)
{
  const auto& tfTrack = conf().getParameter<edm::ParameterSet>("l1track");
  minBXTrack_ = tfTrack.getParameter<int>("minBX");
  maxBXTrack_ = tfTrack.getParameter<int>("maxBX");
  verboseTrack_ = tfTrack.getParameter<int>("verbose");
  deltaRTrack_ = tfTrack.getParameter<double>("deltaR");

  const auto& trackMuon = conf().getParameter<edm::ParameterSet>("l1tkmuon");
  minBXTrackMuon_ = trackMuon.getParameter<int>("minBX");
  maxBXTrackMuon_ = trackMuon.getParameter<int>("maxBX");
  verboseTrackMuon_ = trackMuon.getParameter<int>("verbose");
  deltaRTrackMuon_ = trackMuon.getParameter<double>("deltaR");

  //std::cout<<" UpgradeL1TrackMatcher constructor" <<std::endl;
  // clear();
  // simPt = trk().momentum().pt();
  // simEta = trk().momentum().eta();
  // simPhi = trk().momentum().phi();
  // simE = trk().momentum().E();
  // simCharge = trk().charge();

  // // tracks produced by EMEMTF
  // edm::Handle<l1t::EMTFTrackCollection> hl1Tracks;
  // if (gemvalidation::getByToken(emtfTrackInputLabel_,hl1Tracks, event()))
  //   matchEmtfTrackToSimTrack(*hl1Tracks.product());
  // else
  //   std::cout  <<"failed readout EMTFTracks " << std::endl;

  // edm::Handle<BXVector<l1t::RegionalMuonCand>> hRegMuonCand;
  // if (gemvalidation::getByToken(regionalMuonCandInputLabel_,hRegMuonCand, event()))
  //   matchRegionalMuonCandToSimTrack(*hRegMuonCand.product());
  // else
  //   std::cout  <<"failed readout RegionalMuonCand " << std::endl;
}

UpgradeL1TrackMatcher::~UpgradeL1TrackMatcher()
{
}

void
UpgradeL1TrackMatcher::clear()
{
  bestTrackMuon_ = NULL;
  bestTrack_ = NULL;
}
