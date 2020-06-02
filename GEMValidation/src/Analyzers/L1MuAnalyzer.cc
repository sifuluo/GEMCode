#include "GEMCode/GEMValidation/interface/Analyzers/L1MuAnalyzer.h"

L1MuAnalyzer::L1MuAnalyzer(const edm::ParameterSet& conf)
{
}

void L1MuAnalyzer::setMatcher(const L1MuMatcher& match_sh)
{
  match_.reset(new L1MuMatcher(match_sh));
}

void L1MuAnalyzer::analyze(TreeManager& tree)
{
  const auto& emtfTrack = match_->emtfTrack();
  const auto& muon = match_->muon();

  if (emtfTrack != nullptr) {
    tree.l1mu().has_emtfTrack = 1;
    tree.l1mu().emtf_pt = emtfTrack->pt();
    tree.l1mu().emtf_eta = emtfTrack->eta();
    tree.l1mu().emtf_phi = emtfTrack->phi();

    tree.l1mu().hasME1 = emtfTrack->hasStub(1);
    tree.l1mu().hasME2 = emtfTrack->hasStub(2);
    tree.l1mu().hasME3 = emtfTrack->hasStub(3);
    tree.l1mu().hasME4 = emtfTrack->hasStub(4);
    tree.l1mu().nstubs = emtfTrack->nStubs();
    tree.l1mu().deltaR = emtfTrack->dR();
    tree.l1mu().chargesign = emtfTrack->charge();
  }

  if (muon != nullptr) {
    tree.l1mu().has_gmtCand = 1;
    tree.l1mu().bestdRGmtCand = muon->dR();
    tree.l1mu().L1Mu_pt = muon->pt();
    tree.l1mu().L1Mu_eta = muon->eta();
    tree.l1mu().L1Mu_phi = muon->phi();
    tree.l1mu().L1Mu_charge = muon->charge();
    tree.l1mu().L1Mu_bx = muon->bx();
    tree.l1mu().L1Mu_quality = muon->quality();
  }
}
