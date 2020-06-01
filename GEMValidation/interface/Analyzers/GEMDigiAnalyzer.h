#ifndef GEMCode_GEMValidation_GEMDigiAnalyzer_h
#define GEMCode_GEMValidation_GEMDigiAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatchManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class GEMDigiAnalyzer
{
public:

  // constructor
  GEMDigiAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~GEMDigiAnalyzer() {}

  void init(const GEMDigiMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  int median(const GEMDigiContainer& digis) const;

  std::unique_ptr<GEMDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
