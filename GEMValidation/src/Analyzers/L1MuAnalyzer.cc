#include "GEMCode/GEMValidation/interface/Analyzers/L1MuAnalyzer.h"

L1MuAnalyzer::L1MuAnalyzer(const L1MuMatcher& match_sh)
{
  match_.reset(new L1MuMatcher(match_sh));
}

void L1MuAnalyzer::init(const edm::ParameterSet& conf)
{
}

void L1MuAnalyzer::analyze(std::vector<gem::MyTrack>& track)
{
  const auto& emtfTrack = match_->emtfTrack();
  const auto& muon = match_->muon();

  if (emtfTrack != nullptr) {
    track[0].has_emtfTrack = 1;
    track[0].emtf_pt = emtfTrack->pt();
    track[0].emtf_eta = emtfTrack->eta();
    track[0].emtf_phi = emtfTrack->phi();

    track[0].hasME1 = emtfTrack->hasStub(1);
    track[0].hasME2 = emtfTrack->hasStub(2);
    track[0].hasME3 = emtfTrack->hasStub(3);
    track[0].hasME4 = emtfTrack->hasStub(4);
    track[0].nstubs = emtfTrack->nStubs();
    track[0].deltaR = emtfTrack->dR();
    track[0].chargesign = emtfTrack->charge();
  }

  if (muon != nullptr) {
    track[0].has_gmtCand = 1;
    track[0].bestdRGmtCand = muon->dR();
    track[0].L1Mu_pt = muon->pt();
    track[0].L1Mu_eta = muon->eta();
    track[0].L1Mu_phi = muon->phi();
    track[0].L1Mu_charge = muon->charge();
    track[0].L1Mu_bx = muon->bx();
    track[0].L1Mu_quality = muon->quality();
  }
}
