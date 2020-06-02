#include "GEMCode/GEMValidation/interface/Analyzers/CSCSimHitAnalyzer.h"

using namespace std;

CSCSimHitAnalyzer::CSCSimHitAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCSimHit");
}

void CSCSimHitAnalyzer::setMatcher(const CSCSimHitMatcher& match_sh)
{
  match_.reset(new CSCSimHitMatcher(match_sh));
}

void CSCSimHitAnalyzer::analyze(TreeManager& tree)
{
  const auto& csc_simhits(match_->chamberIds(0));

  for(const auto& d: match_->chamberIds(0)) {

    CSCDetId id(d);

    const int st(gem::detIdToMEStation(id.station(),id.ring()));

    // calculate hit layers
    int nlayers(match_->nLayersWithHitsInChamber(d));

    // case ME11
    if (id.station()==1 and (id.ring()==4 or id.ring()==1)){
      // get the detId of the pairing subchamber
      int other_ring(id.ring()==4 ? 1 : 4);
      CSCDetId co_id(id.endcap(), id.station(), other_ring, id.chamber());
      // check if co_id occurs in the list
      // add the hit layers

      const auto& rawId(co_id.rawId());
      if (csc_simhits.find(rawId) != csc_simhits.end()) {
        nlayers = nlayers+match_->nLayersWithHitsInChamber(rawId);
      }
    }

    // layer requirement (typically 4)
    if (nlayers < minNHitsChamber_) continue;

    match_->LocalBendingInChamber(d);

    const bool odd(id.chamber()%2==1);
    const auto& simhits = match_->hitsInDetId(id);
    const auto& keygp(match_->simHitsMeanPosition(simhits));
    const auto& csc_simhits_gv = match_->simHitsMeanMomentum(simhits);

    if (odd) {
      tree.cscSimHit().chamber_sh_odd[st] = id.chamber();
      tree.cscSimHit().nlayers_csc_sh_odd[st] = nlayers;
      tree.cscSimHit().has_csc_sh_odd[st] = true;
      tree.cscSimHit().eta_csc_sh_odd[st] = keygp.eta();
      tree.cscSimHit().phi_csc_sh_odd[st] = keygp.phi();
      tree.cscSimHit().perp_csc_sh_odd[st] = keygp.perp();
      tree.cscSimHit().bend_csc_sh_odd[st] = csc_simhits_gv.phi();
    }
    else {
      tree.cscSimHit().chamber_sh_even[st] = id.chamber();
      tree.cscSimHit().nlayers_csc_sh_even[st] = nlayers;
      tree.cscSimHit().has_csc_sh_even[st] = true;
      tree.cscSimHit().eta_csc_sh_even[st] = keygp.eta();
      tree.cscSimHit().phi_csc_sh_even[st] = keygp.phi();
      tree.cscSimHit().perp_csc_sh_even[st] = keygp.perp();
      tree.cscSimHit().bend_csc_sh_even[st] = csc_simhits_gv.phi();
    }

    // case ME11
    if (st==1 or st==2){
      if (odd) {
        tree.cscSimHit().chamber_sh_odd[0] = id.chamber();
        tree.cscSimHit().nlayers_csc_sh_odd[0] = nlayers;
        tree.cscSimHit().has_csc_sh_odd[0] = true;
        tree.cscSimHit().eta_csc_sh_odd[0] = keygp.eta();
        tree.cscSimHit().phi_csc_sh_odd[0] = keygp.phi();
        tree.cscSimHit().perp_csc_sh_odd[0] = keygp.perp();
        tree.cscSimHit().bend_csc_sh_odd[0] = csc_simhits_gv.phi();
      }
      else {
        tree.cscSimHit().chamber_sh_even[0] = id.chamber();
        tree.cscSimHit().nlayers_csc_sh_even[0] = nlayers;
        tree.cscSimHit().has_csc_sh_even[0] = true;
        tree.cscSimHit().eta_csc_sh_even[0] = keygp.eta();
        tree.cscSimHit().phi_csc_sh_even[0] = keygp.phi();
        tree.cscSimHit().perp_csc_sh_even[0] = keygp.perp();
        tree.cscSimHit().bend_csc_sh_odd[0] = csc_simhits_gv.phi();
      }
    }
  }
}
