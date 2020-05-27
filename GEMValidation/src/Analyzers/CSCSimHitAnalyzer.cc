#include "GEMCode/GEMValidation/interface/Analyzers/CSCSimHitAnalyzer.h"

CSCSimHitAnalyzer::CSCSimHitAnalyzer(const CSCSimHitMatcher& match_sh)
  :  match_(match_sh)
{
}

void CSCSimHitAnalyzer::analyze(gem::MyTrack track[NumOfTrees])
{
  /*
  const auto& csc_simhits(match_csc_sh.chamberIds(0));
  for(const auto& d: match_csc_sh.chamberIds(0)) {

    CSCDetId id(d);
    const int st(detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;
    int nlayers(match_csc_sh.nLayersWithHitsInChamber(d));
    // case ME11
    if (id.station()==1 and (id.ring()==4 or id.ring()==1)){
      // get the detId of the pairing subchamber
      int other_ring(id.ring()==4 ? 1 : 4);
      CSCDetId co_id(id.endcap(), id.station(), other_ring, id.chamber());
      // check if co_id occurs in the list
      // add the hit layers

      const auto& rawId(co_id.rawId());
      if (csc_simhits.find(rawId) != csc_simhits.end()) {
        nlayers = nlayers+match_csc_sh.nLayersWithHitsInChamber(rawId);
      }
    }

    if (nlayers < minNHitsChamberCSCSimHit_) continue;

    match_csc_sh.LocalBendingInChamber(d);

    const bool odd(id.chamber()%2==1);
    const auto& simhits = match_csc_sh.hitsInDetId(id);
    const GlobalPoint& keygp(match_csc_sh.simHitsMeanPosition(simhits));

    if (odd) {
      etrk_[st].chamber_sh_odd = id.chamber();
      etrk_[st].nlayers_csc_sh_odd = nlayers;
      etrk_[st].has_csc_sh |= 1;
      etrk_[st].eta_cscsh_odd = keygp.eta();
      etrk_[st].phi_cscsh_odd = keygp.phi();
      etrk_[st].perp_cscsh_odd = keygp.perp();
    }
    else {
      etrk_[st].chamber_sh_even = id.chamber();
      etrk_[st].nlayers_csc_sh_even = nlayers;
      etrk_[st].has_csc_sh |= 2;
      etrk_[st].eta_cscsh_even = keygp.eta();
      etrk_[st].phi_cscsh_even = keygp.phi();
      etrk_[st].perp_cscsh_even = keygp.perp();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        etrk_[1].chamber_sh_odd = id.chamber();
        etrk_[1].nlayers_csc_sh_odd = nlayers;
        etrk_[1].has_csc_sh |= 1;
        etrk_[1].eta_cscsh_odd = keygp.eta();
        etrk_[1].phi_cscsh_odd = keygp.phi();
        etrk_[1].perp_cscsh_odd = keygp.perp();
      }
      else {
        etrk_[1].chamber_sh_even = id.chamber();
        etrk_[1].nlayers_csc_sh_even = nlayers;
        etrk_[1].has_csc_sh |= 2;
        etrk_[1].eta_cscsh_even = keygp.eta();
        etrk_[1].phi_cscsh_even = keygp.phi();
        etrk_[1].perp_cscsh_even = keygp.perp();
      }
    }
  }
  */
}
