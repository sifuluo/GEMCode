#include "GEMCode/GEMValidation/interface/Analyzers/GEMDigiAnalyzer.h"

GEMDigiAnalyzer::GEMDigiAnalyzer(const GEMDigiMatcher& match_sh)
  :  match_(match_sh)
{
}

void GEMDigiAnalyzer::init(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberGEMDigi");
}

void GEMDigiAnalyzer::analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations_to_use_)
{
  // placeholders for best mtching pads
  GlobalPoint best_pad_odd[12];
  GlobalPoint best_pad_even[12];

  // GEM digis and pads in superchambers
  for(const auto& d: match_.superChamberIdsDigi()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(gem::detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);

    if (match_.digisInSuperChamber(d).size() > 0) {
      if (odd) track[st].has_gem_dg |= 1;
      else     track[st].has_gem_dg |= 2;
    }

    if (match_.nLayersWithDigisInSuperChamber(d) >= 2) {
      if (odd) track[st].has_gem_dg2 |= 1;
      else     track[st].has_gem_dg2 |= 2;
    }

    if (match_.padsInSuperChamber(d).size() > 0) {
      if (odd) track[st].has_gem_pad |= 1;
      else     track[st].has_gem_pad |= 2;
    }

    if (match_.nLayersWithPadsInSuperChamber(d) >= 2) {
      if (odd) track[st].has_gem_pad2 |= 1;
      else     track[st].has_gem_pad2 |= 2;
    }

    // // const int median_strip(match_.median(digis));
    // if (odd && digis.size() > 0) {
    //   // track[st].strip_gemdg_odd = median_strip;
    // }
    // else if (digis.size() > 0) {
    //   // track[st].strip_gemdg_even = median_strip;
    // }

    for (int layer=1; layer<=2; layer++){
      GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);

      const auto& pads = match_.padsInChamber(id_tmp.rawId());
      if(pads.size() == 0) continue;

      const auto& collection(match_.muonSimHitMatcher()->hitsInChamber(id_tmp.rawId()));
      const GlobalPoint& keygp = match_.muonSimHitMatcher()->simHitsMeanPosition(collection);

      // const auto& bestgem_dg_and_gp = match_.digiInGEMClosestToCSC(pads, keygp);
      if (odd) {
        // best_pad_odd[st] = bestgem_dg_and_gp.second;
        track[st].has_gem_pad |= 1;
        track[st].chamber_lct_odd = id.chamber();
        // track[st].pad_odd = digi_channel(bestgem_dg_and_gp.first);
        // track[st].hsfromgem_odd = match_.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
        track[st].z_pad_odd = best_pad_odd[st].z();
        track[st].phi_pad_odd = best_pad_odd[st].phi();
        track[st].eta_pad_odd = best_pad_odd[st].eta();
        //question: ME1a is not included here
        // if (is_valid(lct_odd[st]))
        //   {
        //     // const auto& gem_dg_and_gp = match_.digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
        //     // best_pad_odd[st] = gem_dg_and_gp.second;
        //     // track[st].bx_pad_odd = digi_bx(gem_dg_and_gp.first);
        //     track[st].dphi_pad_odd = deltaPhi(track[st].phi_lct_odd, track[st].phi_pad_odd);
        //     track[st].dphi_pad_fit_odd = deltaPhi(track[st].phi_layer3_fit_odd, track[st].phi_pad_odd);
        //     //std::cout <<"GEMid "<< id << std::endl;
        //     //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< track[st].phi_pad_odd <<" phi_lct "<< track[st].phi_lct_odd <<" phi_fit_lct "<< track[st].phi_layer3_fit_odd <<" dist(GEM, CSC) " << fabs(track[st].z_layer3_fit_odd - track[st].z_pad_odd)<< std::endl;
        //     track[st].deta_pad_odd = track[st].eta_lct_odd - track[st].eta_pad_odd;
        //   }
      }
      else {
        // best_pad_even[st] = bestgem_dg_and_gp.second;
        track[st].has_gem_pad |= 2;
        // track[st].pad_even = digi_channel(bestgem_dg_and_gp.first);
        // track[st].hsfromgem_even = match_.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
        track[st].z_pad_even = best_pad_even[st].z();
        track[st].phi_pad_even = best_pad_even[st].phi();
        track[st].eta_pad_even = best_pad_even[st].eta();
        // if (is_valid(lct_even[st]))
        //   {
        //     // const auto& gem_dg_and_gp = match_.digiInGEMClosestToCSC(pads, gp_lct_even[st]);
        //     // best_pad_even[st] = gem_dg_and_gp.second;
        //     // track[st].bx_pad_even = digi_bx(gem_dg_and_gp.first);
        //     track[st].dphi_pad_even = deltaPhi(track[st].phi_lct_even, track[st].phi_pad_even);
        //     track[st].dphi_pad_fit_even = deltaPhi(track[st].phi_layer3_fit_even, track[st].phi_pad_even);
        //     //std::cout <<"GEMid "<< id << std::endl;
        //     //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< track[st].phi_pad_even <<" phi_lct "<< track[st].phi_lct_even <<" phi_fit_lct "<< track[st].phi_layer3_fit_even <<" dist(GEM, CSC) " <<  fabs(track[st].z_layer3_fit_even - track[st].z_pad_even)<< std::endl;
        //     track[st].deta_pad_even = track[st].eta_lct_even - track[st].eta_pad_even;
        //   }
      }
      if (id_tmp.layer()==1) break;
    }
  }

  for(const auto& d: match_.superChamberIdsCoPad()) {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(gem::detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (odd) track[st].has_gem_copad |= 1;
    else     track[st].has_gem_copad |= 2;

    const auto& copads = match_.coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;
    // if (odd) track[st].Copad_odd = digi_channel(copads.at(0));
    // else track[st].Copad_even = digi_channel(copads.at(0));
    // if (verbose_) std::cout <<"Matching GEMCopad detid "<< id <<" size "<< copads.size() << std::endl;

    if (st==2 or st==3) {
      if (odd) track[1].has_gem_copad |= 1;
      else     track[1].has_gem_copad |= 2;

      const auto& copads = match_.coPadsInSuperChamber(d);
      if (copads.size() == 0) continue;
      // if (odd) track[1].Copad_odd = digi_channel(copads.at(0));
      // else track[1].Copad_even = digi_channel(copads.at(0));
    }
  }
}
