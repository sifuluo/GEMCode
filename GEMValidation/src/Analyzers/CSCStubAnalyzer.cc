#include "GEMCode/GEMValidation/interface/Analyzers/CSCStubAnalyzer.h"

CSCStubAnalyzer::CSCStubAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCStub");
}

void CSCStubAnalyzer::setMatcher(const CSCStubMatcher& match_sh)
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
      tree.cscStub().quality_clct_odd[st] = clct.getQuality();
      tree.cscStub().bx_clct_odd[st] = clct.getBX();
      tree.cscStub().hs_clct_odd[st] = clct.getKeyStrip();
      tree.cscStub().qs_clct_odd[st] = clct.getKeyStrip(4);
      tree.cscStub().es_clct_odd[st] = clct.getKeyStrip(8);
    }
    else {
      tree.cscStub().has_clct_even[st] = true;
      // tree.cscStub().chamber_dg_even[st] = id.chamber();
      tree.cscStub().quality_clct_even[st] = clct.getQuality();
      tree.cscStub().bx_clct_even[st] = clct.getBX();
      tree.cscStub().hs_clct_even[st] = clct.getKeyStrip();
      tree.cscStub().qs_clct_even[st] = clct.getKeyStrip(4);
      tree.cscStub().es_clct_even[st] = clct.getKeyStrip(8);
    }

    // case ME11
    if (st==1 or st==2){
      if (odd) {
        tree.cscStub().has_clct_odd[0] = true;
        tree.cscStub().quality_clct_odd[0] = clct.getQuality();
        tree.cscStub().bx_clct_odd[0] = clct.getBX();
        tree.cscStub().hs_clct_odd[0] = clct.getKeyStrip();
        tree.cscStub().qs_clct_odd[0] = clct.getKeyStrip(4);
        tree.cscStub().es_clct_odd[0] = clct.getKeyStrip(8);
      }
      else {
        tree.cscStub().has_clct_even[0] = true;
        tree.cscStub().quality_clct_even[0] = clct.getQuality();
        tree.cscStub().bx_clct_even[0] = clct.getBX();
        tree.cscStub().hs_clct_even[0] = clct.getKeyStrip();
        tree.cscStub().qs_clct_even[0] = clct.getKeyStrip(4);
        tree.cscStub().es_clct_even[0] = clct.getKeyStrip(8);
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
      // tree.cscStub().wiregroup_odd[st] = alct.getKeyWG();
      tree.cscStub().quality_alct_odd[st] = alct.getQuality();
      tree.cscStub().bx_alct_odd[st] = alct.getBX();
    }
    else {
      tree.cscStub().has_alct_even[st] = true;
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
        tree.cscStub().qs_lct_odd[st] = lct.getStrip(4);
        tree.cscStub().es_lct_odd[st] = lct.getStrip(8);
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
        tree.cscStub().qs_lct_odd[st] = lct.getStrip(4);
        tree.cscStub().es_lct_odd[st] = lct.getStrip(8);
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
          tree.cscStub().qs_lct_odd[0] = lct.getStrip(4);
          tree.cscStub().es_lct_odd[0] = lct.getStrip(8);
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
          tree.cscStub().qs_lct_even[0] = lct.getStrip(4);
          tree.cscStub().es_lct_even[0] = lct.getStrip(8);
          tree.cscStub().wg_lct_even[0] = lct.getKeyWG();
          tree.cscStub().quality_even[0] = lct.getQuality();
        }
      }
    }
  }

  // best GEM pads
  for(const auto& d: match_->gemDigiMatcher()->superChamberIdsPad()) {
  }


    // best GEM copads
  for(const auto& d: match_->gemDigiMatcher()->superChamberIdsCoPad()) {
  }
  /*

    const auto& copads = match_->coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;

    if (odd) tree.gemStub().copad_odd[st] = copads.at(0).pad(0);
    else     tree.gemStub().copad_even[st] = copads.at(0).pad(0);

    // best pad properties will be set in CSCStubAnalyzer
    for (int layer=1; layer<=2; layer++){
      GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);

      const auto& pads = match_->padsInChamber(id_tmp.rawId());
      if(pads.size() == 0) continue;

      const auto& collection(match_->muonSimHitMatcher()->hitsInChamber(id_tmp.rawId()));
      const GlobalPoint& keygp = match_->muonSimHitMatcher()->simHitsMeanPosition(collection);

      if (odd) {
        tree.gemStub().has_gem_pad_odd[st] = true;
        tree.gemStub().pad_odd[st] = pads[0].pad();
      }
      else {
        tree.gemStub().has_gem_pad_even[st] = true;
        tree.gemStub().pad_even[st] = pads[0].pad();
      }
    }
*/
}


std::pair<GEMDigi, GlobalPoint>
CSCStubAnalyzer::digiInGEMClosestToCSC(const GEMDigiContainer& gem_digis,
                                       const GlobalPoint& csc_gp) const
{
  GlobalPoint gp;
  GEMDigi best_digi;
  auto emptyValue = make_pair(best_digi, gp);

  // no valid GEM digis
  if (gem_digis.empty()) return emptyValue;

  // invalid CSC stub
  if (std::abs(csc_gp.z()) < 0.001) return emptyValue;

  float bestDr= 9.;
  /*
  for (const auto& d: gem_digis)
    {
      const GEMDigi& t = d;
      const GlobalPoint& curr_gp = digiPosition(d);
      if (std::abs(curr_gp.z()) < 0.001) continue; // invalid position

      // in deltaR calculation, give x20 larger weight to deltaPhi to make them comparable
      // but with slight bias towards dphi:
      float dphi = 20.*deltaPhi(float(csc_gp.phi()), float(curr_gp.phi()));
      float deta = csc_gp.eta() - curr_gp.eta();
      float curr_dr2 = dphi*dphi + deta*deta;
      if (std::abs(gp.z()) < 000.1 || // gp was not assigned yet
          curr_dr2 < prev_dr2 ) // current gp is closer in phi then the previous
        {
          gp = curr_gp;
          best_digi = d;
          prev_dr2 = curr_dr2;
        }
        }
  */
  return emptyValue;
}
