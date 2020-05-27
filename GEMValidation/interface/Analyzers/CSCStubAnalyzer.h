#ifndef GEMCode_GEMValidation_CSCStubAnalyzer_h
#define GEMCode_GEMValidation_CSCStubAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class CSCStubAnalyzer
{
public:

  // constructor
  CSCStubAnalyzer(const CSCStubMatcher& match_sh);

  // destructor
  ~CSCStubAnalyzer() {}

  // initialize the event
  void analyze(gem::MyTrack track[NumOfTrees]);

 private:

  CSCStubMatcher match_;
};

#endif
