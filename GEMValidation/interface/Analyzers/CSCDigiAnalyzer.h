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

  // initialize the event
  void analyze(gem::MyTrack track[NumOfTrees]);

 private:

  CSCDigiMatcher match_;
};

#endif
