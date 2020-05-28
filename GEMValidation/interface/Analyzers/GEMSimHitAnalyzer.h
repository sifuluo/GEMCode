#ifndef GEMCode_GEMValidation_GEMSimHitAnalyzer_h
#define GEMCode_GEMValidation_GEMSimHitAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class GEMSimHitAnalyzer
{
public:

  // constructor
  GEMSimHitAnalyzer(const GEMSimHitMatcher& match_sh);

  // destructor
  ~GEMSimHitAnalyzer() {}

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations);

 private:

  std::shared_ptr<GEMSimHitMatcher> match_;
  int minNHitsChamber_;
};

#endif
