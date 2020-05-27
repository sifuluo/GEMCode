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

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations);

 private:

  CSCStubMatcher match_;
  int minNHitsChamber_;
};

#endif
