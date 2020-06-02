#ifndef GEMCode_GEMValidation_CSCDigiAnalyzer_h
#define GEMCode_GEMValidation_CSCDigiAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class CSCDigiAnalyzer
{
public:

  // constructor
  CSCDigiAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~CSCDigiAnalyzer() {}

  void setMatcher(const CSCDigiMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::unique_ptr<CSCDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
