#include "GEMCode/GEMValidation/interface/Analyzers/L1TrackAnalyzer.h"

L1TrackAnalyzer::L1TrackAnalyzer(const edm::ParameterSet& conf)
{
}

void L1TrackAnalyzer::setMatcher(const L1TrackMatcher& match_sh)
{
  match_.reset(new L1TrackMatcher(match_sh));
}

void L1TrackAnalyzer::analyze(TreeManager& tree)
{
  /*
    /*L1TrackTriggerVeto trkVeto2(cfg_, match_sh.eventSetup(), match_sh.event(), trackInputLabel_,
                                etrk_[0].L1Mu_eta, normalizedPhi((float)etrk_[0].L1Mu_phi));
    etrk_[0].isL1LooseVeto  = trkVeto2.isLooseVeto();
    etrk_[0].isL1MediumVeto = trkVeto2.isMediumVeto();
    etrk_[0].isL1TightVeto  = trkVeto2.isTightVeto();
  */
}
