#include "GEMCode/GEMValidation/interface/Analyzers/CSCSimHitAnalyzer.h"

CSCSimHitAnalyzer::CSCSimHitAnalyzer(const CSCSimHitMatcher& match_sh)
{
  match_.reset(new CSCSimHitMatcher(match_sh));
}

void CSCSimHitAnalyzer::init(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCSimHit");
}

void CSCSimHitAnalyzer::analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations_to_use_)
{
  const auto& csc_simhits(match_->chamberIds(0));
  for(const auto& d: match_->chamberIds(0)) {

    CSCDetId id(d);

    const int st(gem::detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

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

    if (nlayers < minNHitsChamber_) continue;

    match_->LocalBendingInChamber(d);

    const bool odd(id.chamber()%2==1);
    const auto& simhits = match_->hitsInDetId(id);
    const GlobalPoint& keygp(match_->simHitsMeanPosition(simhits));

    if (odd) {
      track[st].chamber_sh_odd = id.chamber();
      track[st].nlayers_csc_sh_odd = nlayers;
      track[st].has_csc_sh |= 1;
      track[st].eta_cscsh_odd = keygp.eta();
      track[st].phi_cscsh_odd = keygp.phi();
      track[st].perp_cscsh_odd = keygp.perp();
    }
    else {
      track[st].chamber_sh_even = id.chamber();
      track[st].nlayers_csc_sh_even = nlayers;
      track[st].has_csc_sh |= 2;
      track[st].eta_cscsh_even = keygp.eta();
      track[st].phi_cscsh_even = keygp.phi();
      track[st].perp_cscsh_even = keygp.perp();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        track[1].chamber_sh_odd = id.chamber();
        track[1].nlayers_csc_sh_odd = nlayers;
        track[1].has_csc_sh |= 1;
        track[1].eta_cscsh_odd = keygp.eta();
        track[1].phi_cscsh_odd = keygp.phi();
        track[1].perp_cscsh_odd = keygp.perp();
      }
      else {
        track[1].chamber_sh_even = id.chamber();
        track[1].nlayers_csc_sh_even = nlayers;
        track[1].has_csc_sh |= 2;
        track[1].eta_cscsh_even = keygp.eta();
        track[1].phi_cscsh_even = keygp.phi();
        track[1].perp_cscsh_even = keygp.perp();
      }
    }
  }
}
