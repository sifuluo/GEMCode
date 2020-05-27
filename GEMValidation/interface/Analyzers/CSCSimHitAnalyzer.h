#ifndef GEMCode_GEMValidation_CSCSimHitAnalyzer_h
#define GEMCode_GEMValidation_CSCSimHitAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

#include <vector>
#include <map>
#include <set>
#include <unordered_set>

class CSCSimHitAnalyzer
{
public:

  // constructor
  CSCSimHitAnalyzer(const CSCSimHitMatcher& match_sh);

  // destructor
  ~CSCSimHitAnalyzer() {}

  // initialize the event
  void analyze(MyTrack track[]);

 private:

  std::unique_ptr<CSCSimHitMatcher> match_;
};

#endif
