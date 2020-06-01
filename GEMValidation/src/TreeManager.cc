#include "GEMCode/GEMValidation/interface/TreeManager.h"

void TreeManager::book() {
  edm::Service<TFileService> fs;
  simTrackTree_ = fs->make<TTree>("SimTrack","SimTrack");
  gemSimHitTree_ = fs->make<TTree>("GEMSimHit","GEMSimHit");
  gemDigiTree_ = fs->make<TTree>("GEMDigi","GEMDigi");
  gemStubTree_ = fs->make<TTree>("GEMStub","GEMStub");
  cscSimHitTree_ = fs->make<TTree>("CSCSimHit","CSCSimHit");
  cscDigiTree_ = fs->make<TTree>("CSCDigi","CSCDigi");
  cscStubTree_ = fs->make<TTree>("CSCStub","CSCStub");
  l1MuTree_ = fs->make<TTree>("L1Mu","L1Mu");
  recoTrackTree_ = fs->make<TTree>("RecoTrack","RecoTrack");

  simTrackSt_.book(simTrackTree_);
  gemSimHitSt_.book(gemSimHitTree_);
  gemDigiSt_.book(gemDigiTree_);
  gemStubSt_.book(gemStubTree_);
  cscSimHitSt_.book(cscSimHitTree_);
  cscDigiSt_.book(cscDigiTree_);
  cscStubSt_.book(cscStubTree_);
  l1MuSt_.book(l1MuTree_);
  recoTrackSt_.book(recoTrackTree_);
}

/// initialize
void TreeManager::init() {
  simTrackSt_.init();
  gemSimHitSt_.init();
  gemDigiSt_.init();
  gemStubSt_.init();
  cscSimHitSt_.init();
  cscDigiSt_.init();
  cscStubSt_.init();
  l1MuSt_.init();
  recoTrackSt_.init();
}

void TreeManager::fill() {
  simTrackTree_->Fill();
  gemSimHitTree_->Fill();
  gemDigiTree_->Fill();
  gemStubTree_->Fill();
  cscSimHitTree_->Fill();
  cscDigiTree_->Fill();
  cscStubTree_->Fill();
  l1MuTree_->Fill();
  recoTrackTree_->Fill();
}
