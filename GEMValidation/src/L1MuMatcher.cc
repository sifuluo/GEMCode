#include "GEMCode/GEMValidation/interface/L1MuMatcher.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/normalizedPhi.h"

#include "TLorentzVector.h"
#include <map>

L1MuMatcher::L1MuMatcher(const edm::ParameterSet& ps, edm::ConsumesCollector&& iC)
{
  cscStubMatcher_.reset(new CSCStubMatcher(ps, std::move(iC)));

  const auto& emtfTrack = ps.getParameter<edm::ParameterSet>("emtfTrack");
  minBXEMTFTrack_ = emtfTrack.getParameter<int>("minBX");
  maxBXEMTFTrack_ = emtfTrack.getParameter<int>("maxBX");
  verboseEMTFTrack_ = emtfTrack.getParameter<int>("verbose");
  deltaREMTFTrack_ = emtfTrack.getParameter<double>("deltaR");
  runEMTFTrack_ = emtfTrack.getParameter<bool>("run");

  const auto& emtfCand = ps.getParameter<edm::ParameterSet>("emtfCand");
  minBXRegMuCand_ = emtfCand.getParameter<int>("minBX");
  maxBXRegMuCand_ = emtfCand.getParameter<int>("maxBX");
  verboseRegMuCand_ = emtfCand.getParameter<int>("verbose");
  deltaRRegMuCand_ = emtfCand.getParameter<double>("deltaR");
  runRegMuCand_ = emtfCand.getParameter<bool>("run");

  const auto& muon = ps.getParameter<edm::ParameterSet>("muon");
  minBXGMT_ = muon.getParameter<int>("minBX");
  maxBXGMT_ = muon.getParameter<int>("maxBX");
  verboseGMT_ = muon.getParameter<int>("verbose");
  deltaRGMT_ = muon.getParameter<double>("deltaR");
  runGMT_ = muon.getParameter<bool>("run");

  emtfTrackToken_ = iC.consumes<l1t::EMTFTrackCollection>(emtfTrack.getParameter<edm::InputTag>("inputTag"));
  emtfCandToken_ = iC.consumes<l1t::RegionalMuonCandBxCollection>(emtfCand.getParameter<edm::InputTag>("inputTag"));
  muonToken_ = iC.consumes<l1t::MuonBxCollection>(muon.getParameter<edm::InputTag>("inputTag"));
}

void L1MuMatcher::init(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  cscStubMatcher_->init(iEvent, iSetup);

  iEvent.getByToken(emtfTrackToken_, emtfTrackHandle_);
  iEvent.getByToken(emtfCandToken_, emtfCandHandle_);
  iEvent.getByToken(muonToken_, muonHandle_);
}

void
L1MuMatcher::clear()
{
  emtfTrack_ = nullptr;
  emtfCand_ = nullptr;
  muon_ = nullptr;
}


// do the matching
void L1MuMatcher::match(const SimTrack& t, const SimVertex& v)
{
  clear();

  cscStubMatcher_->match(t, v);

  if (runEMTFTrack_)
    matchEmtfTrackToSimTrack(*emtfTrackHandle_.product());

  if (runRegMuCand_)
    matchRegionalMuonCandToSimTrack(*emtfCandHandle_.product());

  if (runGMT_)
    matchGMTToSimTrack(*muonHandle_.product());
}

void
L1MuMatcher::matchEmtfTrackToSimTrack(const l1t::EMTFTrackCollection& tracks)
{
  for (const auto& trk : tracks) {
    int nMatchingStubs = 0;
    int nMaxMatchingStubs = 0;
    if (verboseEMTFTrack_)
      std::cout <<"track BX "<< trk.BX()
                <<  " pt "<< trk.Pt()
                <<" eta "<< trk.Eta()
                <<" phi "<< emtf::deg_to_rad(trk.Phi_glob())
                <<" phi_local "<< emtf::deg_to_rad(trk.Phi_loc()) << std::endl;
    for (const auto& stub : trk.Hits()){
      const CSCCorrelatedLCTDigi& csc_stub = stub.CreateCSCCorrelatedLCTDigi();
      const CSCDetId& csc_id = stub.CSC_DetId();
      if (verboseEMTFTrack_)
        std::cout << "L1 " << csc_id << " "
                  << csc_stub << " "
                  << cscStubMatcher_->lctsInChamber(csc_id.rawId()).size() << std::endl;
      for (const auto& sim_stub: cscStubMatcher_->lctsInChamber(csc_id.rawId())){
        if (verboseEMTFTrack_) std::cout << "\tSIM " << csc_id << " " << sim_stub << std::endl;
        if (csc_stub == sim_stub) {
          nMatchingStubs++;
        }
      }
      if (nMatchingStubs>=2) {
        if (nMatchingStubs > nMaxMatchingStubs){
          emtfTrack_.reset(new gem::EMTFTrack(trk));
          nMaxMatchingStubs = nMatchingStubs;
        }
      }
    }
  }
}

void L1MuMatcher::matchRegionalMuonCandToSimTrack(const l1t::RegionalMuonCandBxCollection& regMuCands)
{
  // EMTF track properties
  float track_pt = emtfTrack_->pt();
  float track_eta = emtfTrack_->eta();
  float track_phi = emtfTrack_->phi();

  if (verboseRegMuCand_)
    std::cout << "EMTF "<< track_pt << " " << track_eta << " " << track_phi << std::endl;

  float mindPtRel = 0.5;
  float mindRRegMuCand = 1;

  for (int bx = regMuCands.getFirstBX(); bx <= regMuCands.getLastBX(); bx++ ){
    if ( bx < minBXRegMuCand_ or bx > maxBXRegMuCand_) continue;
    for (auto emtfCand = regMuCands.begin(bx); emtfCand != regMuCands.end(bx); ++emtfCand ){

      const gem::EMTFCand& cand(*emtfCand);

      // EMTF candidate properties
      float cand_pt = cand.pt();
      float cand_eta = cand.eta();
      float cand_phi = cand.phi();

      if (verboseRegMuCand_)
        std::cout << "candidate regional muon " << cand_pt << " " << cand_eta << " " << cand_phi << std::endl;

      float dR = deltaR(track_eta, track_phi, cand_eta, cand_phi);

      float dPtRel = std::fabs(track_pt - cand_pt)/cand_pt;
      if (dR < mindRRegMuCand and dPtRel < mindPtRel){
        mindRRegMuCand = dR;
        emtfCand_.reset(new gem::EMTFCand(cand));
      }
    }
  }
}

void L1MuMatcher::matchGMTToSimTrack(const BXVector<l1t::Muon>& gmtCands)
{
  // EMTF candidate properties
  float cand_pt = emtfCand_->pt();
  float cand_eta = emtfCand_->eta();
  float cand_phi = emtfCand_->phi();

  if (verboseRegMuCand_)
    std::cout << "candidate regional muon " << cand_pt << " " << cand_eta << " " << cand_phi << std::endl;

  float mindPtRel = 0.5;
  float mindRGMT = 1;

  for (int bx = gmtCands.getFirstBX(); bx <= gmtCands.getLastBX(); bx++ ){
    if ( bx < minBXGMT_ or bx > maxBXGMT_) continue;
    for (auto emtfCand = gmtCands.begin(bx); emtfCand != gmtCands.end(bx); ++emtfCand ){

      const gem::EMTFCand& cand(*emtfCand);

      // Muon properties
      float muon_pt = cand.pt();
      float muon_eta = cand.eta();
      float muon_phi = cand.phi();

      float dR = deltaR(muon_eta, muon_phi, cand_eta, cand_phi);

      float dPtRel = std::fabs(cand_pt - muon_pt)/muon_pt;
      if (dR < mindRGMT and dPtRel < mindPtRel){
        mindRGMT = dR;
        muon_.reset(new gem::EMTFCand(cand));
      }
    }
  }
}
