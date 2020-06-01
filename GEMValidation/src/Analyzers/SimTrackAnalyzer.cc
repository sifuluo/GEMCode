#include "GEMCode/GEMValidation/interface/Analyzers/SimTrackAnalyzer.h"

SimTrackAnalyzer::SimTrackAnalyzer(const edm::ParameterSet& conf)
{
}

void SimTrackAnalyzer::init()
{
}

void SimTrackAnalyzer::analyze(TreeManager& tree, const SimTrack& t)
{
  // track properties
  tree.simTrack().pt = t.momentum().pt();
  tree.simTrack().pz = t.momentum().pz();
  tree.simTrack().phi = t.momentum().phi();
  tree.simTrack().eta = t.momentum().eta();
  tree.simTrack().charge = t.charge();
  tree.simTrack().endcap = (tree.simTrack().eta > 0.) ? 1 : -1;
  tree.simTrack().pdgid = t.type();
}
