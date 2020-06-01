#include "GEMCode/GEMValidation/interface/Analyzers/GEMStubAnalyzer.h"

GEMStubAnalyzer::GEMStubAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberGEMDigi");
}

void GEMStubAnalyzer::init(const GEMDigiMatcher& match_sh)
{
  match_.reset(new GEMDigiMatcher(match_sh));
}

void GEMStubAnalyzer::analyze(TreeManager& tree)
{
  // GEM digis and pads in superchambers
  for(const auto& d: match_->superChamberIdsDigi()) {
    GEMDetId id(d);
    const int st = id.station();

    const bool odd(id.chamber()%2==1);

    if (match_->padsInSuperChamber(d).size() > 0) {
      if (odd) tree.gemStub().has_gem_pad_odd[st] = true;
      else     tree.gemStub().has_gem_pad_even[st] = true;
    }

    if (match_->nLayersWithPadsInSuperChamber(d) >= 2) {
      if (odd) tree.gemStub().has_gem_pad2_odd[st] = true;
      else     tree.gemStub().has_gem_pad2_even[st] = true;
    }

    for (int layer=1; layer<=2; layer++){
      GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);

      const auto& pads = match_->padsInChamber(id_tmp.rawId());
      if(pads.size() == 0) continue;

      const auto& collection(match_->muonSimHitMatcher()->hitsInChamber(id_tmp.rawId()));
      const GlobalPoint& keygp = match_->muonSimHitMatcher()->simHitsMeanPosition(collection);

      if (odd) {
        tree.gemStub().has_gem_pad_odd[st] = true;
        // tree.gemStub().chamber_lct_odd[st] = id.chamber();
        // tree.gemStub().pad_odd = digi_channel(bestgem_dg_and_gp.first);
        // tree.gemStub().hsfromgem_odd = match_->extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
        // tree.gemStub().z_pad_odd[st] = best_pad_odd[st.z();
        // tree.gemStub().phi_pad_odd[st] = best_pad_odd[st.phi();
        // tree.gemStub().eta_pad_odd[st] = best_pad_odd[st.eta();
        //question: ME1a is not included here
        // if (is_valid(lct_odd[st]))
        //   {
        //     // const auto& gem_dg_and_gp = match_->digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
        //     // best_pad_odd[st] = gem_dg_and_gp.second;
        //     // tree.gemStub().bx_pad_odd = digi_bx(gem_dg_and_gp.first);
        //     tree.gemStub().dphi_pad_odd = deltaPhi(tree.gemStub().phi_lct_odd, tree.gemStub().phi_pad_odd);
        //     tree.gemStub().dphi_pad_fit_odd = deltaPhi(tree.gemStub().phi_layer3_fit_odd, tree.gemStub().phi_pad_odd);
        //     //std::cout <<"GEMid "<< id << std::endl;
        //     //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< tree.gemStub().phi_pad_odd <<" phi_lct "<< tree.gemStub().phi_lct_odd <<" phi_fit_lct "<< tree.gemStub().phi_layer3_fit_odd <<" dist(GEM, CSC) " << fabs(tree.gemStub().z_layer3_fit_odd - tree.gemStub().z_pad_odd)<< std::endl;
        //     tree.gemStub().deta_pad_odd = tree.gemStub().eta_lct_odd - tree.gemStub().eta_pad_odd;
        //   }
      }
      else {
        // best_pad_even[st] = bestgem_dg_and_gp.second;
        tree.gemStub().has_gem_pad_even[st] = true;
        // tree.gemStub().pad_even = digi_channel(bestgem_dg_and_gp.first);
        // tree.gemStub().hsfromgem_even = match_->extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
        // tree.gemStub().z_pad_even[st] = best_pad_even[st.z();
        // tree.gemStub().phi_pad_even[st] = best_pad_even[st.phi();
        // tree.gemStub().eta_pad_even[st] = best_pad_even[st.eta();
        // if (is_valid(lct_even[st]))
        //   {
        //     // const auto& gem_dg_and_gp = match_->digiInGEMClosestToCSC(pads, gp_lct_even[st]);
        //     // best_pad_even[st] = gem_dg_and_gp.second;
        //     // tree.gemStub().bx_pad_even = digi_bx(gem_dg_and_gp.first);
        //     tree.gemStub().dphi_pad_even = deltaPhi(tree.gemStub().phi_lct_even, tree.gemStub().phi_pad_even);
        //     tree.gemStub().dphi_pad_fit_even = deltaPhi(tree.gemStub().phi_layer3_fit_even, tree.gemStub().phi_pad_even);
        //     //std::cout <<"GEMid "<< id << std::endl;
        //     //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< tree.gemStub().phi_pad_even <<" phi_lct "<< tree.gemStub().phi_lct_even <<" phi_fit_lct "<< tree.gemStub().phi_layer3_fit_even <<" dist(GEM, CSC) " <<  fabs(tree.gemStub().z_layer3_fit_even - tree.gemStub().z_pad_even)<< std::endl;
        //     tree.gemStub().deta_pad_even = tree.gemStub().eta_lct_even - tree.gemStub().eta_pad_even;
        //   }
      }
    }
  }

  for(const auto& d: match_->superChamberIdsCoPad()) {
    GEMDetId id(d);

    const int st = id.station();

    const bool odd(id.chamber()%2==1);
    if (odd) tree.gemStub().has_gem_copad_odd[st] = true;
    else     tree.gemStub().has_gem_copad_even[st] = true;

    const auto& copads = match_->coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;

    if (odd) tree.gemStub().copad_odd[st] = copads.at(0).pad(0);
    else     tree.gemStub().copad_even[st] = copads.at(0).pad(0);

  }
}
