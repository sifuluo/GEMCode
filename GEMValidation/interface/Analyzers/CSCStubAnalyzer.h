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

  void init(const edm::Event& iEvent, const edm::EventSetup& iSetup);

  void setMatcher(const CSCStubMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:
  // best here means "closest in phi"
  std::pair<GEMDigi, GlobalPoint>
  bestGEMDigi(const GEMDetId& gemId,
              const GEMDigiContainer& gem_digis,
              const GlobalPoint& csc_gp) const;

  std::pair<GEMPadDigi, GlobalPoint>
  bestGEMPadDigi(const GEMDetId& gemId,
                 const GEMPadDigiContainer& gem_digis,
                 const GlobalPoint& csc_gp) const;

  std::pair<GEMCoPadDigi, GlobalPoint>
  bestGEMCoPadDigi(const GEMDetId& gemId,
                   const GEMCoPadDigiContainer& gem_digis,
                   const GlobalPoint& csc_gp) const;

  edm::ESHandle<CSCGeometry> csc_geom_;
  edm::ESHandle<GEMGeometry> gem_geom_;

  const CSCGeometry* cscGeometry_;
  const GEMGeometry* gemGeometry_;

  std::unique_ptr<CSCStubMatcher> match_;
  int minNHitsChamber_;
};

#endif
