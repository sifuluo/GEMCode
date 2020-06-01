#ifndef GEMCode_GEMValidation_RPCRecHitAnalyzer_h
#define GEMCode_GEMValidation_RPCRecHitAnalyzer_h

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MatchManager.h"
#include "GEMCode/GEMValidation/interface/TreeManager.h"

class RPCRecHitAnalyzer
{
public:

  // constructor
  RPCRecHitAnalyzer(const edm::ParameterSet& conf);

  // destructor
  ~RPCRecHitAnalyzer() {}

  void init(const RPCRecHitMatcher& match_sh);

  // initialize the event
  void analyze(TreeManager& tree);

 private:

  std::unique_ptr<RPCRecHitMatcher> match_;
};

#endif
