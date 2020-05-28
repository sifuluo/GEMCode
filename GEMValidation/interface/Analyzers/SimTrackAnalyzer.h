#ifndef GEMCode_GEMValidation_SimTrackAnalyzer_h
#define GEMCode_GEMValidation_SimTrackAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"

class SimTrackAnalyzer
{
public:

  // constructor
  SimTrackAnalyzer(const SimTrackMatcher& match_sh);

  // destructor
  ~SimTrackAnalyzer() {}

  // initialize the event
  void analyze(std::vector<gem::MyTrack>& track) {
    /* track_[i].pt = t.momentum().pt(); */
    /* track_[i].pz = t.momentum().pz(); */
    /* track_[i].phi = t.momentum().phi(); */
    /* track_[i].eta = t.momentum().eta(); */
    /* track_[i].charge = t.charge(); */
    /* track_[i].endcap = (track_[i].eta > 0.) ? 1 : -1; */
    /* track_[i].pdgid = t.type(); */
  }

 private:
};

#endif
