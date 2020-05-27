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

  // initialize the event
  void analyze(gem::MyTrack track[NumOfTrees]);

 private:

  GEMSimHitMatcher match_;
};

#endif
