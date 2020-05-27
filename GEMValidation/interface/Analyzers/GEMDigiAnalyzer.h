#ifndef GEMCode_GEMValidation_GEMDigiAnalyzer_h
#define GEMCode_GEMValidation_GEMDigiAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class GEMDigiAnalyzer
{
public:

  // constructor
  GEMDigiAnalyzer(const GEMDigiMatcher& match_sh);

  // destructor
  ~GEMDigiAnalyzer() {}

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations);

 private:

  GEMDigiMatcher match_;
  int minNHitsChamber_;
};

#endif
