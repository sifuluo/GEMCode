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

  void setMatcher(const GEMDigiMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::pair<GEMPadDigi, GlobalPoint>
  bestPad(const GEMDetId& id,
          const GEMPadDigiContainer& digis) const;

  std::pair<GEMCoPadDigi, GlobalPoint>
  bestCoPad(const GEMDetId& id,
            const GEMCoPadDigiContainer& digis) const;

  GlobalPoint
  meanPosition(const GEMDetId& id,
               const GEMPadDigiContainer& digis) const;

  GlobalPoint
  meanPosition(const GEMDetId& id,
               const GEMCoPadDigiContainer& digis) const;

  std::unique_ptr<GEMDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
