#include "GEMCode/GEMValidation/interface/Analyzers/CSCStubAnalyzer.h"

CSCStubAnalyzer::CSCStubAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCStub");
}

void CSCStubAnalyzer::init(const CSCStubMatcher& match_sh)
{
  match_.reset(new CSCStubMatcher(match_sh));
}

void CSCStubAnalyzer::analyze(TreeManager& tree)
{
  // CSC CLCTs
  for(const auto& d: match_->chamberIdsCLCT(0)) {
    CSCDetId id(d);

    const int st(gem::detIdToMEStation(id.station(),id.ring()));

    const bool odd(id.chamber()%2==1);
    const auto& clct = match_->bestClctInChamber(d);

    if (odd) {
      tree.cscStub().has_clct_odd[st] = true;
      // tree.cscStub().chamber_dg_odd[st] = id.chamber();
      // tree.cscStub().halfstrip_odd[st] = clct.getKeyStrip();
      tree.cscStub().quality_clct_odd[st] = clct.getQuality();
      tree.cscStub().bx_clct_odd[st] = clct.getBX();
    }
    else {
      tree.cscStub().has_clct_even[st] = true;
      // tree.cscStub().chamber_dg_even[st] = id.chamber();
      // tree.cscStub().halfstrip_even[st] = clct.getKeyStrip();
      tree.cscStub().quality_clct_even[st] = clct.getQuality();
      tree.cscStub().bx_clct_even[st] = clct.getBX();
    }

    // case ME11
    if (st==1 or st==2){
      if (odd) {
        tree.cscStub().has_clct_odd[0] = true;
        // tree.cscStub().chamber_dg_odd[0] = id.chamber();
        // tree.cscStub().halfstrip_odd[0] = clct.getKeyStrip();
        tree.cscStub().quality_clct_odd[0] = clct.getQuality();
        tree.cscStub().bx_clct_odd[0] = clct.getBX();
      }
      else {
        tree.cscStub().has_clct_even[0] = true;
        // tree.cscStub().chamber_dg_even[0] = id.chamber();
        // tree.cscStub().halfstrip_even[0] = clct.getKeyStrip();
        tree.cscStub().quality_clct_even[0] = clct.getQuality();
        tree.cscStub().bx_clct_even[0] = clct.getBX();
      }
    }
  }

  // CSC ALCTs
  for(const auto& d: match_->chamberIdsALCT(0)) {
    CSCDetId id(d);
    const int st(gem::detIdToMEStation(id.station(),id.ring()));

    const bool odd(id.chamber()%2==1);
    const auto& alct = match_->bestAlctInChamber(d);

    if (odd) {
      tree.cscStub().has_alct_odd[st] = true;
      // tree.cscStub().chamber_dg_odd[st] = id.chamber();
      // tree.cscStub().wiregroup_odd[st] = alct.getKeyWG();
      tree.cscStub().quality_alct_odd[st] = alct.getQuality();
      tree.cscStub().bx_alct_odd[st] = alct.getBX();
    }
    else {
      tree.cscStub().has_alct_even[st] = true;
      // tree.cscStub().chamber_dg_even[st] = id.chamber();
      // tree.cscStub().wiregroup_even[st] = alct.getKeyWG();
      tree.cscStub().quality_alct_even[st] = alct.getQuality();
      tree.cscStub().bx_alct_even[st] = alct.getBX();
    }

    // case ME11
    if (st==1 or st==2){
      if (odd) {
        tree.cscStub().has_alct_odd[0] = true;
        // tree.cscStub().chamber_dg_odd[0] = id.chamber();
        // tree.cscStub().wiregroup_odd[0] = alct.getKeyWG();
        tree.cscStub().quality_alct_odd[0] = alct.getQuality();
        tree.cscStub().bx_alct_odd[0] = alct.getBX();
      }
      else {
        tree.cscStub().has_alct_even[0] = true;
        // tree.cscStub().chamber_dg_even[0] = id.chamber();
        // tree.cscStub().wiregroup_even[0] = alct.getKeyWG();
        tree.cscStub().quality_alct_even[0] = alct.getQuality();
        tree.cscStub().bx_alct_even[0] = alct.getBX();
      }
    }

    // CSC LCTs
    for(const auto& d: match_->chamberIdsLCT(0)) {
      CSCDetId id(d);
      const int st(gem::detIdToMEStation(id.station(),id.ring()));

      const auto& lct = match_->bestLctInChamber(d);
      const GlobalPoint& gp = match_->getGlobalPosition(d, lct);

      const bool odd(id.chamber()%2==1);
      if (odd) {
        tree.cscStub().has_lct_odd[st] = true;
        tree.cscStub().bend_lct_odd[st] = lct.getPattern();
        tree.cscStub().phi_lct_odd[st] = gp.phi();
        tree.cscStub().eta_lct_odd[st] = gp.eta();
        tree.cscStub().perp_lct_odd[st] = gp.perp();
        tree.cscStub().bx_lct_odd[st] = lct.getBX();
        tree.cscStub().hs_lct_odd[st] = lct.getStrip();
        tree.cscStub().wg_lct_odd[st] = lct.getKeyWG();
        tree.cscStub().quality_odd[st] = lct.getQuality();
      }
      else {
        tree.cscStub().has_lct_even[st] = true;
        tree.cscStub().bend_lct_even[st] = lct.getPattern();
        tree.cscStub().phi_lct_even[st] = gp.phi();
        tree.cscStub().eta_lct_even[st] = gp.eta();
        tree.cscStub().perp_lct_even[st] = gp.perp();
        tree.cscStub().bx_lct_even[st] = lct.getBX();
        tree.cscStub().hs_lct_even[st] = lct.getStrip();
        tree.cscStub().wg_lct_even[st] = lct.getKeyWG();
        tree.cscStub().quality_even[st] = lct.getQuality();
      }
      // case ME11
      if (st==1 or st==2){
        if (odd) {
          tree.cscStub().has_lct_odd[0] = true;
          tree.cscStub().bend_lct_odd[0] = lct.getPattern();
          tree.cscStub().phi_lct_odd[0] = gp.phi();
          tree.cscStub().eta_lct_odd[0] = gp.eta();
          tree.cscStub().perp_lct_odd[0] = gp.perp();
          tree.cscStub().bx_lct_odd[0] = lct.getBX();
          tree.cscStub().hs_lct_odd[0] = lct.getStrip();
          tree.cscStub().wg_lct_odd[0] = lct.getKeyWG();
          tree.cscStub().quality_odd[0] = lct.getQuality();
        }
        else {
          tree.cscStub().has_lct_even[0] = true;
          tree.cscStub().bend_lct_even[0] = lct.getPattern();
          tree.cscStub().phi_lct_even[0] = gp.phi();
          tree.cscStub().eta_lct_even[0] = gp.eta();
          tree.cscStub().perp_lct_even[0] = gp.perp();
          tree.cscStub().bx_lct_even[0] = lct.getBX();
          tree.cscStub().hs_lct_even[0] = lct.getStrip();
          tree.cscStub().wg_lct_even[0] = lct.getKeyWG();
          tree.cscStub().quality_even[0] = lct.getQuality();
        }
      }
    }
  }
}
