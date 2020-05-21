#include "GEMCode/GEMValidation/interface/EMTFTrack.h"

gem::EMTFTrack::EMTFTrack(const l1t::EMTFTrack& t)
{
  emtfHits_ = t.Hits();
  emtfTrack_ = t;
  pt_ = t.Pt();
  eta_ = t.Eta();
  phi_ = emtf::deg_to_rad(t.Phi_glob());
  phi_local_ = emtf::deg_to_rad(t.Phi_loc());
  charge_ = t.Charge();
  quality_ = t.GMT_quality();
  bx_ = t.BX();
  dr_ = 10.0;
}

gem::EMTFTrack::EMTFTrack(const gem::EMTFTrack& rhs)
{}

gem::EMTFTrack::~EMTFTrack()
{
  emtfTrack_ = l1t::EMTFTrack();
  emtfHits_.clear();
}

unsigned int gem::EMTFTrack::nStubs() const
{
  unsigned returnValue;
  for (const auto& stub : emtfHits_) {
    if (stub.Is_CSC()) returnValue++;
  }
  return returnValue;
}

bool
gem::EMTFTrack::hasStub(int st) const
{
  for (const auto& stub : emtfHits_) {
    if (stub.Is_CSC() and stub.Station() == st) return true;
  }
  return false;
}

bool
gem::EMTFTrack::hasStub(int st, int ri) const
{
  for (const auto& stub : emtfHits_) {
    if (stub.Is_CSC() and
        stub.Station() == st and
        stub.Ring() == ri) return true;
  }
  return false;
}

l1t::EMTFHit gem::EMTFTrack::stub(int st, int ri) const
{
  for (const auto& stub : emtfHits_) {
    if (stub.Is_CSC() and
        stub.Station() == st and
        stub.Ring() == ri) return stub;
  }
  return l1t::EMTFHit();;

}

gem::EMTFCand::EMTFCand(const l1t::RegionalMuonCand& cand)
{
  pt_ = cand.hwPt() * 0.5;
  eta_ = cand.hwEta() * 0.010875;
  //local phi from GMT
  phi_local_ = cand.hwPhi() * 2.0 * 3.1415926/576.0;
  phi_ = normalizedPhi((((cand.hwPhi() + cand.processor() * 96 + 576 + 24) % 576) / 576.) * 2.0 * 3.1415926);
  charge_ = cand.hwSign() == 0? 1 : -1;
  quality_ = cand.hwQual();
  dr_ = 10.0;
}

gem::EMTFCand::EMTFCand(const l1t::Muon& cand)
{
  pt_ = cand.pt();
  eta_ = cand.eta();
  phi_local_ = -9;
  phi_ = cand.phi();
  charge_ = cand.charge();
  quality_ = cand.hwQual();
  dr_ = 10.0;
}

gem::EMTFCand::~EMTFCand()
{
}
