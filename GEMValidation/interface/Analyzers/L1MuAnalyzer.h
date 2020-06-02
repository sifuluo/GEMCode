#ifndef GEMCode_GEMValidation_L1MuAnalyzer_h
#define GEMCode_GEMValidation_L1MuAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class L1MuAnalyzer
{
public:

  // constructor
  L1MuAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~L1MuAnalyzer() {}

  void setMatcher(const L1MuMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::unique_ptr<L1MuMatcher> match_;
};

#endif
