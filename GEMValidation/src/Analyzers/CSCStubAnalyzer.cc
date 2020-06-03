#include "GEMCode/GEMValidation/interface/Analyzers/CSCStubAnalyzer.h"
#include "L1Trigger/CSCCommonTrigger/interface/CSCPatternLUT.h"

CSCStubAnalyzer::CSCStubAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCStub");
}

void CSCStubAnalyzer::init(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  iSetup.get<MuonGeometryRecord>().get(csc_geom_);
  if (csc_geom_.isValid()) {
  cscGeometry_ = &*csc_geom_;
  } else {
    std::cout << "+++ Info: CSC geometry is unavailable. +++\n";
  }

  iSetup.get<MuonGeometryRecord>().get(gem_geom_);
  if (gem_geom_.isValid()) {
  gemGeometry_ = &*gem_geom_;
  } else {
    std::cout << "+++ Info: GEM geometry is unavailable. +++\n";
  }
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
      const int gemstation(id.station());

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
        tree.cscStub().quality_lct_odd[st] = lct.getQuality();
        tree.cscStub().dphi_lct_odd[st] =
          reco::deltaPhi(float(tree.cscStub().phi_lct_odd[st]),
                         float(tree.cscSimHit().phi_csc_sh_odd[st]));
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
        tree.cscStub().quality_lct_even[st] = lct.getQuality();
        tree.cscStub().dphi_lct_even[st] =
          reco::deltaPhi(float(tree.cscStub().phi_lct_even[st]),
                         float(tree.cscSimHit().phi_csc_sh_even[st]));
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
          tree.cscStub().quality_lct_odd[0] = lct.getQuality();
          tree.cscStub().dphi_lct_odd[0] =
            reco::deltaPhi(float(tree.cscStub().phi_lct_odd[0]),
                           float(tree.cscSimHit().phi_csc_sh_odd[0]));
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
          tree.cscStub().quality_lct_even[0] = lct.getQuality();
          tree.cscStub().dphi_lct_even[0] =
            reco::deltaPhi(float(tree.cscStub().phi_lct_even[0]),
                           float(tree.cscSimHit().phi_csc_sh_even[0]));
        }
      }

      // only for ME1/1 and ME2/1
      if (st==1 or st==2 or st==5) continue;

      // require at least one GEM pad present...
      if (! (tree.gemStub().has_gem_pad_even[gemstation] or
             tree.gemStub().has_gem_pad_odd[gemstation] ) ) continue;

      if (odd) {
        tree.gemStub().dphi_lct_pad1_odd[gemstation]
          = reco::deltaPhi(float(tree.gemStub().phi_pad1_odd[st]),
                           float(tree.cscStub().phi_lct_odd[gemstation]));
        tree.gemStub().dphi_lct_pad2_odd[gemstation]
          = reco::deltaPhi(float(tree.gemStub().phi_pad2_odd[st]),
                           float(tree.cscStub().phi_lct_odd[gemstation]));
      } else {
        tree.gemStub().dphi_lct_pad1_even[gemstation]
          = reco::deltaPhi(float(tree.gemStub().phi_pad1_even[st]),
                           float(tree.cscStub().phi_lct_even[gemstation]));
        tree.gemStub().dphi_lct_pad2_even[gemstation]
          = reco::deltaPhi(float(tree.gemStub().phi_pad2_even[st]),
                           float(tree.cscStub().phi_lct_even[gemstation]));
      }

      // require at least one GEM pad present...
      if (! (tree.gemStub().has_gem_copad_even[gemstation] or
             tree.gemStub().has_gem_copad_odd[gemstation] ) ) continue;

      if (odd) {
        tree.gemStub().dphi_lct_copad_odd[gemstation]
          = reco::deltaPhi(float(tree.gemStub().phi_copad_odd[st]),
                           float(tree.cscStub().phi_lct_odd[gemstation]));
      } else {
        tree.gemStub().dphi_lct_copad_even[gemstation]
          = reco::deltaPhi(float(tree.gemStub().phi_copad_even[st]),
                           float(tree.cscStub().phi_lct_even[gemstation]));
      }
    }
  }
}

float CSCStubAnalyzer::getPositionOffset(int pattern, int compCode) const
{
  if (compCode == -1) return getPositionOffsetLegacy(pattern);
  else return getPositionOffsetRun3(pattern, compCode);
}

float CSCStubAnalyzer::getPositionOffsetLegacy(int pattern) const
{
  return CSCPatternLUT::get2007Position(pattern);
}

float CSCStubAnalyzer::getPositionOffsetRun3(int pattern, int compCode) const
{
  // need to access the LUTs in CMSSW!
  std::string lutstring("L1Trigger/CSCTriggerPrimitives/data/CSCComparatorCodePosOffsetLUT_pat" + std::to_string(pattern) + "_ideal_v1.txt");
  std::unique_ptr<CSCComparatorCodeLUT> lut = new CSCComparatorCodeLUT(lutstring);
  return lut.lookup(compCode);
}

float CSCStubAnalyzer::getSlope(int pattern, int compCode) const
{
  if (compCode == -1) return getAverageSlopeLegacy(pattern);
  else return getSlopeRun3(pattern, compCode);
}

float CSCStubAnalyzer::getMaxSlopeLegacy(int pattern) const
{
  // slope in number of strips/layer
  int slope[CSCConstants::NUM_CLCT_PATTERNS] = {
    0, 0, 5, -5, 4, -4, 3, -3, 2, -2, 1};
  return float(slope[pattern]/5.);
}

float CSCStubAnalyzer::getMinSlopeLegacy(int pattern) const
{
  // slope in number of strips/layer
  int slope[CSCConstants::NUM_CLCT_PATTERNS] = {
    0, 0, 3, -3, 2, -2, 1, -1, 0, 0, -1};
  return float(slope[pattern]/5.);
}

float CSCStubAnalyzer::getAverageSlopeLegacy(int pattern) const
{
  // slope in number of strips/layer
  int slope[CSCConstants::NUM_CLCT_PATTERNS] = {
    0, 0, 4, -4, 3, -3, 2, -2, 1, -1, 0};
  return float(slope[pattern]/5.);

}

float CSCStubAnalyzer::getSlopeRun3(int pattern, int compCode) const
{
  // need to access the LUTs in CMSSW!
  std::string lutstring("L1Trigger/CSCTriggerPrimitives/data/CSCComparatorCodeSlopeLUT_pat" + std::to_string(pattern) + "_v1.txt");
  std::unique_ptr<CSCComparatorCodeLUT> lut = new CSCComparatorCodeLUT(lutstring);
  return lut.lookup(compCode);
}


std::pair<GEMDigi, GlobalPoint>
CSCStubAnalyzer::bestGEMDigi(const GEMDetId& gemId,
                             const GEMDigiContainer& gem_digis,
                             const GlobalPoint& csc_gp) const
{
  GlobalPoint gp;
  GEMDigi best_digi;
  auto emptyValue = make_pair(best_digi, gp);

  // no valid GEM digis
  if (gem_digis.empty()) return emptyValue;

  // invalid CSC stub
  if (std::abs(csc_gp.z()) < 0.001) return emptyValue;

  float bestDR2 = 999.;
  for (const auto& d: gem_digis) {
    const LocalPoint& lp = gemGeometry_->etaPartition(gemId)->centreOfStrip(d.strip());
    const GlobalPoint& gem_gp = gemGeometry_->idToDet(gemId)->surface().toGlobal(lp);

    // in deltaR calculation, give x20 larger weight to deltaPhi to make them comparable
    // but with slight bias towards dphi:
    float dphi = 20. * reco::deltaPhi(float(csc_gp.phi()), float(gem_gp.phi()));
    float deta = csc_gp.eta() - gem_gp.eta();
    float dR2 = dphi*dphi + deta*deta;
    // current gp is closer in phi then the previous
    if (dR2 < bestDR2) {
      gp = gem_gp;
      best_digi = d;
      bestDR2 = dR2;
    }
  }
  return emptyValue;
}


std::pair<GEMPadDigi, GlobalPoint>
CSCStubAnalyzer::bestGEMPadDigi(const GEMDetId& gemId,
                                const GEMPadDigiContainer& gem_digis,
                                const GlobalPoint& csc_gp) const
{
  GlobalPoint gp;
  GEMPadDigi best_digi;
  auto emptyValue = make_pair(best_digi, gp);

  // no valid GEM digis
  if (gem_digis.empty()) return emptyValue;

  // invalid CSC stub
  if (std::abs(csc_gp.z()) < 0.001) return emptyValue;

  float bestDR2 = 999.;
  for (const auto& d: gem_digis) {
    const LocalPoint& lp = gemGeometry_->etaPartition(gemId)->centreOfPad(d.pad());
    const GlobalPoint& gem_gp = gemGeometry_->idToDet(gemId)->surface().toGlobal(lp);

    // in deltaR calculation, give x20 larger weight to deltaPhi to make them comparable
    // but with slight bias towards dphi:
    float dphi = 20. * reco::deltaPhi(float(csc_gp.phi()), float(gem_gp.phi()));
    float deta = csc_gp.eta() - gem_gp.eta();
    float dR2 = dphi*dphi + deta*deta;
    // current gp is closer in phi then the previous
    if (dR2 < bestDR2) {
      gp = gem_gp;
      best_digi = d;
      bestDR2 = dR2;
    }
  }
  return emptyValue;
}


std::pair<GEMCoPadDigi, GlobalPoint>
CSCStubAnalyzer::bestGEMCoPadDigi(const GEMDetId& gemId,
                                  const GEMCoPadDigiContainer& gem_digis,
                                  const GlobalPoint& csc_gp) const
{
  GlobalPoint gp;
  GEMCoPadDigi best_digi;
  auto emptyValue = make_pair(best_digi, gp);

  // no valid GEM digis
  if (gem_digis.empty()) return emptyValue;

  // invalid CSC stub
  if (std::abs(csc_gp.z()) < 0.001) return emptyValue;

  float bestDR2 = 999.;
  for (const auto& d: gem_digis) {
    const LocalPoint& lp = gemGeometry_->etaPartition(gemId)->centreOfPad(d.pad(1));
    const GlobalPoint& gem_gp = gemGeometry_->idToDet(gemId)->surface().toGlobal(lp);

    // in deltaR calculation, give x20 larger weight to deltaPhi to make them comparable
    // but with slight bias towards dphi:
    float dphi = 20. * reco::deltaPhi(float(csc_gp.phi()), float(gem_gp.phi()));
    float deta = csc_gp.eta() - gem_gp.eta();
    float dR2 = dphi*dphi + deta*deta;
    // current gp is closer in phi then the previous
    if (dR2 < bestDR2) {
      gp = gem_gp;
      best_digi = d;
      bestDR2 = dR2;
    }
  }
  return emptyValue;
}
