#ifndef GEMCode_GEMValidation_CSCStubAnalyzer_h
#define GEMCode_GEMValidation_CSCStubAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatcherManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class CSCStubAnalyzer
{
public:

  // constructor
  CSCStubAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~CSCStubAnalyzer() {}

  void setMatcher(const CSCStubMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:
  std::pair<GEMDigi, GlobalPoint>
    digiInGEMClosestToCSC(const GEMDigiContainer& gem_digis,
                          const GlobalPoint& csc_gp) const;

  edm::ESHandle<CSCGeometry> csc_geom_;
  edm::ESHandle<GEMGeometry> gem_geom_;

  const CSCGeometry* cscGeometry_;
  const GEMGeometry* gemGeometry_;

  std::unique_ptr<CSCStubMatcher> match_;
  int minNHitsChamber_;
};

#endif
