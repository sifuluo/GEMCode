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

  /// initialize
  void init(const edm::ParameterSet& conf);

  /// do the matching
  void analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations);

 private:

  // analyzers
  std::unique_ptr<CSCSimHitAnalyzer> cscsh_;
  std::unique_ptr<GEMSimHitAnalyzer> gemsh_;
  std::unique_ptr<CSCDigiAnalyzer> cscdg_;
  std::unique_ptr<GEMDigiAnalyzer> gemdg_;
  std::unique_ptr<CSCStubAnalyzer> cscstub_;
};

#endif
