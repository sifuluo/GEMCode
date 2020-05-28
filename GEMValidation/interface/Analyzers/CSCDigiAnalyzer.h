#ifndef GEMCode_GEMValidation_CSCDigiAnalyzer_h
#define GEMCode_GEMValidation_CSCDigiAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class CSCDigiAnalyzer
{
public:

  // constructor
  CSCDigiAnalyzer(const CSCDigiMatcher& match_sh);

  // destructor
  ~CSCDigiAnalyzer() {}

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations);

 private:

  std::unique_ptr<CSCDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
