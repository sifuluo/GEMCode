#ifndef GEMCode_GEMValidation_CSCSimHitAnalyzer_h
#define GEMCode_GEMValidation_CSCSimHitAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class CSCSimHitAnalyzer
{
public:

  // constructor
  CSCSimHitAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~CSCSimHitAnalyzer() {}

  void init(const CSCSimHitMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::shared_ptr<CSCSimHitMatcher> match_;
  int minNHitsChamber_;
};

#endif
