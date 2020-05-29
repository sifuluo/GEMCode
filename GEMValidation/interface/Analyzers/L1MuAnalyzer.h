#ifndef GEMCode_GEMValidation_L1MuAnalyzer_h
#define GEMCode_GEMValidation_L1MuAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class L1MuAnalyzer
{
public:

  // constructor
  L1MuAnalyzer(const L1MuMatcher& match_sh);

  // destructor
  ~L1MuAnalyzer() {}

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(std::vector<gem::MyTrack>& track);

 private:

  std::unique_ptr<L1MuMatcher> match_;
};

#endif
