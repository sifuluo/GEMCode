#include "GEMCode/GEMValidation/interface/Analyzers/RecoTrackAnalyzer.h"

RecoTrackAnalyzer::RecoTrackAnalyzer(const RecoTrackMatcher& match_sh)
{
  match_.reset(new RecoTrackMatcher(match_sh));
}

void RecoTrackAnalyzer::init(const edm::ParameterSet& conf)
{
}

void RecoTrackAnalyzer::analyze(gem::MyTrack track[NumOfTrees])
{
  // RecoTrackExtra
  const auto& recoTrackExtra(match_->getMatchedRecoTrackExtra());
  if (recoTrackExtra != nullptr) {
    track[0].has_recoTrackExtra = 1;
    track[0].recoTrackExtra_pt_inner = recoTrackExtra->innerMomentum().Rho();
    track[0].recoTrackExtra_eta_inner = recoTrackExtra->innerPosition().eta();
    track[0].recoTrackExtra_phi_inner = recoTrackExtra->innerPosition().phi();
    track[0].recoTrackExtra_pt_outer = recoTrackExtra->outerMomentum().Rho();
    track[0].recoTrackExtra_eta_outer = recoTrackExtra->outerPosition().eta();
    track[0].recoTrackExtra_phi_outer = recoTrackExtra->outerPosition().phi();
  }

  // RecoTrack
  const auto& recoTrack(match_->getMatchedRecoTrack());
  if (recoTrack != nullptr) {
    track[0].has_recoTrack = 1;
    track[0].recoTrack_pt_outer = recoTrack->outerPt();
    track[0].recoTrack_eta_outer = recoTrack->outerEta();
    track[0].recoTrack_phi_outer = recoTrack->outerPhi();
  }

  // RecoChargedCandidate
  const auto& recoChargedCandidate(match_->getMatchedRecoChargedCandidate());
  if (recoChargedCandidate != nullptr) {
    track[0].has_recoChargedCandidate = 1;
    track[0].recoChargedCandidate_pt = recoChargedCandidate->pt();
    track[0].recoChargedCandidate_eta = recoChargedCandidate->eta();
    track[0].recoChargedCandidate_phi = recoChargedCandidate->phi();
    track[0].recoChargedCandidate_nValidDTHits = (recoChargedCandidate->track().get())->hitPattern().numberOfValidMuonDTHits();
    track[0].recoChargedCandidate_nValidCSCHits = (recoChargedCandidate->track().get())->hitPattern().numberOfValidMuonCSCHits();
    track[0].recoChargedCandidate_nValidRPCHits = (recoChargedCandidate->track().get())->hitPattern().numberOfValidMuonRPCHits();
    /*
    if (verbose_) {
      std::cout << "recoChargedCandidate_pt " << track[0].recoChargedCandidate_pt << std::endl;
      std::cout << "recoChargedCandidate_eta " << track[0].recoChargedCandidate_eta << std::endl;
      std::cout << "recoChargedCandidate_phi " << track[0].recoChargedCandidate_phi << std::endl;
      std::cout << "nValidHits:"
                << " DT " << track[0].recoChargedCandidate_nValidDTHits
                << " CSC " << track[0].recoChargedCandidate_nValidCSCHits
                << " RPC " << track[0].recoChargedCandidate_nValidRPCHits << std::endl;
    }
    */
  }
}
