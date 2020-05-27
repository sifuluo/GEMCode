#include "GEMCode/GEMValidation/interface/Analyzers/CSCSimHitAnalyzer.h"

CSCSimHitAnalyzer::CSCSimHitAnalyzer(const CSCSimHitMatcher& match_sh)
{
  match_.reset(new CSCSimHitMatcher(match_sh));
}

void CSCSimHitAnalyzer::analyze(MyTrack track[])
{

}
