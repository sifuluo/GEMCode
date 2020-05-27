#include "GEMCode/GEMValidation/interface/Analyzers/GEMDigiAnalyzer.h"

GEMDigiAnalyzer::GEMDigiAnalyzer(const GEMDigiMatcher& match_sh)
  :  match_(match_sh)
{
}

void GEMDigiAnalyzer::analyze(gem::MyTrack track[NumOfTrees])
{
  /*
  // placeholders for best mtching pads
  GlobalPoint best_pad_odd[12];
  GlobalPoint best_pad_even[12];

  // GEM digis and pads in superchambers
  for(const auto& d: match_gd.superChamberIdsDigi()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (match_gd.nLayersWithDigisInSuperChamber(d) > 1) {
      if (odd) etrk_[st].has_gem_dg2 |= 1;
      else     etrk_[st].has_gem_dg2 |= 2;
    }

    const auto& digis = match_gd.digisInSuperChamber(d);
    // const int median_strip(match_gd.median(digis));
    if (odd && digis.size() > 0) {
      etrk_[st].has_gem_dg |= 1;
      // etrk_[st].strip_gemdg_odd = median_strip;
    }
    else if (digis.size() > 0) {
      etrk_[st].has_gem_dg |= 2;
      // etrk_[st].strip_gemdg_even = median_strip;
    }

    if (match_gd.nLayersWithPadsInSuperChamber(d) > 1) {
      if (odd) etrk_[st].has_gem_pad2 |= 1;
      else     etrk_[st].has_gem_pad2 |= 2;
    }
    for (int layer=1; layer<3; layer++){
      GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
      const auto& pads = match_gd.padsInChamber(id_tmp.rawId());
      if(pads.size() == 0) continue;

      const GlobalPoint& keygp = match_gem_sh.simHitsMeanPosition(match_gem_sh.hitsInChamber(id_tmp.rawId()));
      // const auto& bestgem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, keygp);
      if (odd)
        {
          // best_pad_odd[st] = bestgem_dg_and_gp.second;
          etrk_[st].has_gem_pad |= 1;
          etrk_[st].chamber_lct_odd = id.chamber();
          // etrk_[st].pad_odd = digi_channel(bestgem_dg_and_gp.first);
          // etrk_[st].hsfromgem_odd = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
          etrk_[st].z_pad_odd = best_pad_odd[st].z();
          etrk_[st].phi_pad_odd = best_pad_odd[st].phi();
          etrk_[st].eta_pad_odd = best_pad_odd[st].eta();
          //question: ME1a is not included here
          // if (is_valid(lct_odd[st]))
          //   {
          //     // const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
          //     // best_pad_odd[st] = gem_dg_and_gp.second;
          //     // etrk_[st].bx_pad_odd = digi_bx(gem_dg_and_gp.first);
          //     etrk_[st].dphi_pad_odd = deltaPhi(etrk_[st].phi_lct_odd, etrk_[st].phi_pad_odd);
          //     etrk_[st].dphi_pad_fit_odd = deltaPhi(etrk_[st].phi_layer3_fit_odd, etrk_[st].phi_pad_odd);
          //     //std::cout <<"GEMid "<< id << std::endl;
          //     //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< etrk_[st].phi_pad_odd <<" phi_lct "<< etrk_[st].phi_lct_odd <<" phi_fit_lct "<< etrk_[st].phi_layer3_fit_odd <<" dist(GEM, CSC) " << fabs(etrk_[st].z_layer3_fit_odd - etrk_[st].z_pad_odd)<< std::endl;
          //     etrk_[st].deta_pad_odd = etrk_[st].eta_lct_odd - etrk_[st].eta_pad_odd;
          //   }
        }
      else
        {
          // best_pad_even[st] = bestgem_dg_and_gp.second;
          etrk_[st].has_gem_pad |= 2;
          // etrk_[st].pad_even = digi_channel(bestgem_dg_and_gp.first);
          // etrk_[st].hsfromgem_even = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
          etrk_[st].z_pad_even = best_pad_even[st].z();
          etrk_[st].phi_pad_even = best_pad_even[st].phi();
          etrk_[st].eta_pad_even = best_pad_even[st].eta();
          // if (is_valid(lct_even[st]))
          //   {
          //     // const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_even[st]);
          //     // best_pad_even[st] = gem_dg_and_gp.second;
          //     // etrk_[st].bx_pad_even = digi_bx(gem_dg_and_gp.first);
          //     etrk_[st].dphi_pad_even = deltaPhi(etrk_[st].phi_lct_even, etrk_[st].phi_pad_even);
          //     etrk_[st].dphi_pad_fit_even = deltaPhi(etrk_[st].phi_layer3_fit_even, etrk_[st].phi_pad_even);
          //     //std::cout <<"GEMid "<< id << std::endl;
          //     //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< etrk_[st].phi_pad_even <<" phi_lct "<< etrk_[st].phi_lct_even <<" phi_fit_lct "<< etrk_[st].phi_layer3_fit_even <<" dist(GEM, CSC) " <<  fabs(etrk_[st].z_layer3_fit_even - etrk_[st].z_pad_even)<< std::endl;
          //     etrk_[st].deta_pad_even = etrk_[st].eta_lct_even - etrk_[st].eta_pad_even;
          //   }
        }
      if (id_tmp.layer()==1) break;
    }
  }

    if (verbose_) std::cout <<"GEMCSCAnalyzer step6 "<< std::endl;
    for(const auto& d: match_gd.superChamberIdsCoPad())
    {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (odd) etrk_[st].has_gem_copad |= 1;
    else     etrk_[st].has_gem_copad |= 2;

    const auto& copads = match_gd.coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;
    // if (odd) etrk_[st].Copad_odd = digi_channel(copads.at(0));
    // else etrk_[st].Copad_even = digi_channel(copads.at(0));
    if (verbose_) std::cout <<"Matching GEMCopad detid "<< id <<" size "<< copads.size() << std::endl;

    if (st==2 or st==3)
    {
    if (odd) etrk_[1].has_gem_copad |= 1;
    else     etrk_[1].has_gem_copad |= 2;

    const auto& copads = match_gd.coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;
    // if (odd) etrk_[1].Copad_odd = digi_channel(copads.at(0));
    // else etrk_[1].Copad_even = digi_channel(copads.at(0));
    }
    }
*/
}
