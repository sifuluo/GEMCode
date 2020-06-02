#include "GEMCode/GEMValidation/interface/Analyzers/CSCDigiAnalyzer.h"

CSCDigiAnalyzer::CSCDigiAnalyzer(const edm::ParameterSet& conf)
{
  minNHitsChamber_ = conf.getParameter<int>("minNHitsChamberCSCDigi");
}

void CSCDigiAnalyzer::setMatcher(const CSCDigiMatcher& match_sh)
{
  match_.reset(new CSCDigiMatcher(match_sh));
}

void CSCDigiAnalyzer::analyze(TreeManager& tree)
{
  // CSC strip digis
  for(const auto& d: match_->chamberIdsStrip(0)) {
    CSCDetId id(d);

    cout << "test digi analysis" << endl;

    const int st(gem::detIdToMEStation(id.station(),id.ring()));
    cout << "use this station? " << st << " "  << endl;

    const int nlayers(match_->nLayersWithStripInChamber(d));
    cout << "use this station " << st << " " << nlayers << " " << minNHitsChamber_ << endl;

    if (nlayers < minNHitsChamber_) continue;

    cout << "use this station " << st << " " << nlayers << " " << minNHitsChamber_ << endl;
    cout << "has strip digis " << endl;

    const bool odd(id.chamber()%2==1);

    if (odd) tree.cscDigi().has_csc_strips_odd[st] = true;
    else     tree.cscDigi().has_csc_strips_even[st] = true;

    if (odd) tree.cscDigi().nlayers_st_dg_odd[st] = nlayers;
    else     tree.cscDigi().nlayers_st_dg_even[st] = nlayers;

    // case ME11
    if (st==1 or st==2){
      if (odd) tree.cscDigi().has_csc_strips_odd[0] = true;
      else     tree.cscDigi().has_csc_strips_even[0] = true;

      if (odd) tree.cscDigi().nlayers_st_dg_odd[0] = nlayers;
      else     tree.cscDigi().nlayers_st_dg_even[0] = nlayers;
    }
  }

  // CSC wire digis
  for(const auto& d: match_->chamberIdsWire(0)) {
    CSCDetId id(d);
    const int st(gem::detIdToMEStation(id.station(),id.ring()));

    const int nlayers(match_->nLayersWithWireInChamber(d));
    if (nlayers < minNHitsChamber_) continue;

    const bool odd(id.chamber()%2==1);

    if (odd) tree.cscDigi().has_csc_wires_odd[st] = true;
    else tree.cscDigi().has_csc_wires_even[st] = true;

    if (odd) tree.cscDigi().nlayers_wg_dg_odd[st] = nlayers;
    else tree.cscDigi().nlayers_wg_dg_even[st] = nlayers;

    // case ME11
    if (st==1 or st==2){
      if (odd) tree.cscDigi().has_csc_wires_odd[0] = true;
      else tree.cscDigi().has_csc_wires_even[0] = true;

      if (odd) tree.cscDigi().nlayers_wg_dg_odd[0] = nlayers;
      else tree.cscDigi().nlayers_wg_dg_even[0] = nlayers;
    }
  }
}
