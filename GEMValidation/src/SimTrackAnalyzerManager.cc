#include "GEMCode/GEMValidation/interface/SimTrackAnalyzerManager.h"

SimTrackAnalyzerManager::SimTrackAnalyzerManager(const SimTrackMatchManager& manager)
{
  cscsh_.reset(new CSCSimHitAnalyzer(*manager.cscSimHits()));
  gemsh_.reset(new GEMSimHitAnalyzer(*manager.gemSimHits()));
  gemdg_.reset(new GEMDigiAnalyzer(*manager.gemDigis()));
  cscdg_.reset(new CSCDigiAnalyzer(*manager.cscDigis()));
  cscstub_.reset(new CSCStubAnalyzer(*manager.cscStubs()));
}

void
SimTrackAnalyzerManager::analyze(MyTrack track[NumOfTrees])
{
  cscsh_->analyze(track);
  gemsh_->analyze(track);
  cscdg_->analyze(track);
  gemdg_->analyze(track);
  cscstub_->analyze(track);
}
