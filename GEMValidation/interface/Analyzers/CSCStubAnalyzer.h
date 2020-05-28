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
  void analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations);

 private:

  std::unique_ptr<CSCStubMatcher> match_;
  int minNHitsChamber_;
};

#endif
