#ifndef GEMCode_GEMValidation_SimTrackAnalyzer_h
#define GEMCode_GEMValidation_SimTrackAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatchManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class SimTrackAnalyzer
{
public:

  // constructor
  SimTrackAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~SimTrackAnalyzer() {}

  void init();

  // initialize the event
  void analyze(TreeManager& tree, const SimTrack& t);
};

#endif
