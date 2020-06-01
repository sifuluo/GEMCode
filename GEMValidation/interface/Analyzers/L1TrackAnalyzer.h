#ifndef GEMCode_GEMValidation_L1TrackAnalyzer_h
#define GEMCode_GEMValidation_L1TrackAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class L1TrackAnalyzer
{
public:

  // constructor
  L1TrackAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~L1TrackAnalyzer() {}

  void init(const L1TrackMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::unique_ptr<L1TrackMatcher> match_;
};

#endif
