#include "GEMCode/GEMValidation/interface/TFCand.h"

TFCand::TFCand(const l1t::RegionalMuonCand* cand )
{
  //const l1t::RegionalMuonCand* cand(&t);
  eta_ = cand->hwEta() * 0.010875;
  //local phi from GMT
  phi_local_ = cand->hwPhi() * 2.0 * 3.1415926/576.0;
  pt_ = cand->hwPt() * 0.5;
  charge_ = cand->hwSign() == 0? 1 : -1;
  quality_ = cand->hwQual();
  trackType_ = cand->trackFinderType();
  dr_ = 10.0;
  phi_ = -9;

}

TFCand::TFCand(const l1t::Muon* cand )
{
  //const l1t::RegionalMuonCand* cand(&t);
  eta_ = cand->eta();
  //local phi from GMT
  phi_ = cand->phi();
  pt_ = cand->pt();
  charge_ = cand->charge();
  quality_ = cand->hwQual();
//trackType_ = cand->trackFinderType();
  dr_ = 10.0;
  phi_local_ = -9;

}

TFCand::TFCand(const TFCand& rhs)
{}

TFCand::~TFCand()
{}

void
TFCand::setDR(double dr)
{
  dr_ = dr;
}


void
TFCand::print()
{
    std::cout<<"TFCand \t bx:"<<bx_<<" pt: "<<pt_<<"  eta: "<<eta_<<"  phi: "<< phi_<< " local phi "<< phi_local_ <<"  dr: "<<dr_<<" quality "<< quality_ <<std::endl;
}
