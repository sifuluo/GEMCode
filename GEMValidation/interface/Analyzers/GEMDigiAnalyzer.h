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

  // initialize the event
  void analyze(MyTrack track[NumOfTrees]);

 private:

  GEMDigiMatcher match_;
};

#endif
