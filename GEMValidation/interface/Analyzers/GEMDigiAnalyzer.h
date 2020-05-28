#ifndef GEMCode_GEMValidation_GEMDigiAnalyzer_h
#define GEMCode_GEMValidation_GEMDigiAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class GEMDigiAnalyzer
{
public:

  // constructor
  GEMDigiAnalyzer(const GEMDigiMatcher& match_sh);

  // destructor
  ~GEMDigiAnalyzer() {}

  void init(const edm::ParameterSet& conf);

  // initialize the event
  void analyze(std::vector<gem::MyTrack>& track, std::vector<int> stations);

 private:

  int median(const GEMDigiContainer& digis) const;

  std::unique_ptr<GEMDigiMatcher> match_;
  int minNHitsChamber_;
};

#endif
