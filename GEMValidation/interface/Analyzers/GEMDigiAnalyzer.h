#ifndef GEMCode_GEMValidation_GEMDigiAnalyzer_h
#define GEMCode_GEMValidation_GEMDigiAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class GEMDigiAnalyzer
{
public:

  // constructor
  GEMDigiAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~GEMDigiAnalyzer() {}

  void setMatcher(const GEMDigiMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  int median(const GEMDigiContainer& digis) const;
  GlobalPoint meanPosition(const GEMDetId& id, const GEMDigiContainer& digis) const;

  std::unique_ptr<GEMDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
