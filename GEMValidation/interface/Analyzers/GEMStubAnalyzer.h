#ifndef GEMCode_GEMValidation_GEMStubAnalyzer_h
#define GEMCode_GEMValidation_GEMStubAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class GEMStubAnalyzer
{
public:

  // constructor
  GEMStubAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~GEMStubAnalyzer() {}

  void init(const GEMDigiMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::unique_ptr<GEMDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
