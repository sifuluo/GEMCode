#ifndef GEMCode_GEMValidation_SimTrackAnalyzerManager_h
#define GEMCode_GEMValidation_SimTrackAnalyzerManager_h

#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"
#include "GEMCode/GEMValidation/interface/Analyzers/CSCSimHitAnalyzer.h"
#include "GEMCode/GEMValidation/interface/Analyzers/GEMSimHitAnalyzer.h"
#include "GEMCode/GEMValidation/interface/Analyzers/GEMDigiAnalyzer.h"
#include "GEMCode/GEMValidation/interface/Analyzers/CSCDigiAnalyzer.h"
#include "GEMCode/GEMValidation/interface/Analyzers/CSCStubAnalyzer.h"

class SimTrackAnalyzerManager
{
public:
  SimTrackAnalyzerManager(const SimTrackMatchManager&);

  ~SimTrackAnalyzerManager() {}

  /// do the matching
  void analyze(MyTrack track[NumOfTrees]);

 private:

  // analyzers
  std::shared_ptr<CSCSimHitAnalyzer> cscsh_;
  std::shared_ptr<GEMSimHitAnalyzer> gemsh_;
  std::shared_ptr<CSCDigiAnalyzer> cscdg_;
  std::shared_ptr<GEMDigiAnalyzer> gemdg_;
  std::shared_ptr<CSCStubAnalyzer> cscstub_;
};

#endif
