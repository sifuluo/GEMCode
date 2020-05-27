#ifndef GEMCode_GEMValidation_CSCSimHitAnalyzer_h
#define GEMCode_GEMValidation_CSCSimHitAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class CSCSimHitAnalyzer
{
public:

  // constructor
  CSCSimHitAnalyzer(const CSCSimHitMatcher& match_sh);

  // destructor
  ~CSCSimHitAnalyzer() {}

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(gem::MyTrack track[NumOfTrees], std::set<int> stations);

 private:

  CSCSimHitMatcher match_;
  int minNHitsChamber_;
};

#endif
