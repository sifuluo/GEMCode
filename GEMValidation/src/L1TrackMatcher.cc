#include "GEMCode/GEMValidation/interface/L1TrackMatcher.h"

using namespace std;

L1TrackMatcher::L1TrackMatcher(const edm::ParameterSet& ps, edm::ConsumesCollector&& iC)
{
  l1MuonMatcher_.reset(new L1MuMatcher(ps, std::move(iC)));

  const auto& l1Track = ps.getParameter<edm::ParameterSet>("l1Track");
  minBXTrack_ = l1Track.getParameter<int>("minBX");
  maxBXTrack_ = l1Track.getParameter<int>("maxBX");
  verboseTrack_ = l1Track.getParameter<int>("verbose");
  deltaRTrack_ = l1Track.getParameter<double>("deltaR");

  const auto& l1TrackMuon = ps.getParameter<edm::ParameterSet>("l1TrackMuon");
  minBXTrackMuon_ = l1TrackMuon.getParameter<int>("minBX");
  maxBXTrackMuon_ = l1TrackMuon.getParameter<int>("maxBX");
  verboseTrackMuon_ = l1TrackMuon.getParameter<int>("verbose");
  deltaRTrackMuon_ = l1TrackMuon.getParameter<double>("deltaR");

  l1TrackToken_ = iC.consumes<L1TTTrackCollectionType>(l1Track.getParameter<edm::InputTag>("inputTag"));
  l1TrackMuonToken_ = iC.consumes<l1t::TkMuonCollection>(l1TrackMuon.getParameter<edm::InputTag>("inputTag"));
}

void L1TrackMatcher::init(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  l1MuonMatcher_->init(iEvent, iSetup);

  iEvent.getByToken(l1TrackToken_, l1TrackHandle_);
  iEvent.getByToken(l1TrackMuonToken_, l1TrackMuonHandle_);
}

void
L1TrackMatcher::clear()
{
  l1Track_ = nullptr;
  l1TrackMuon_ = nullptr;
}


// do the matching
void L1TrackMatcher::match(const SimTrack& t, const SimVertex& v)
{
  clear();

  l1MuonMatcher_->match(t, v);

  matchL1TrackToSimTrack(*l1TrackHandle_.product(), t);
  matchTrackMuonToSimTrack(*l1TrackMuonHandle_.product());
}

void
L1TrackMatcher::matchL1TrackToSimTrack(const L1TTTrackCollectionType& tracks, const SimTrack& trk)
{
  // match the closest track in dR space

  const double sim_eta = trk.momentum().eta();
  const double sim_phi = trk.momentum().phi();
  cout<<"sim_eta "<<sim_eta<<endl;
  cout<<"sim_phi "<<sim_phi<<endl;

  double bestdR  = 999;
  int bestTrackIndex = -1;

  for (unsigned int j=0; j<tracks.size(); ++j) {
    const auto& l1Tk = tracks[j];
    const double l1Tk_eta = l1Tk.momentum().eta();
    const double l1Tk_phi = l1Tk.momentum().barePhi();
    const double dR_l1Tk = reco::deltaR(l1Tk_eta, l1Tk_phi,
                                        sim_eta, sim_phi);
    cout<<"Track "<<j<<endl;
    cout<<"l1Tk_eta "<<l1Tk_eta<<endl;
    cout<<"l1Tk_phi "<<l1Tk_phi<<endl;

    if (dR_l1Tk < bestdR) {
      bestdR = dR_l1Tk;
      bestTrackIndex = j;
    }
  }
  if (bestTrackIndex != -1) {
    const auto& l1Tk = tracks[bestTrackIndex];
    l1Track_.reset(new TTTrack< Ref_Phase2TrackerDigi_ >(l1Tk.rInv(), l1Tk.phi(), l1Tk.tanL(),
                                                         l1Tk.z0(), l1Tk.d0(), l1Tk.chi2(),
                                                         l1Tk.trkMVA1(), l1Tk.trkMVA2(), l1Tk.trkMVA3(),
                                                         l1Tk.hitPattern(), l1Tk.nFitPars(), 0));

    cout<<"Best Track "<<bestTrackIndex<<endl;
    cout<<"Best l1Tk_eta "<<l1Track_->momentum().eta()<<endl;
    cout<<"Best l1Tk_phi "<<l1Track_->momentum().barePhi()<<endl;
  }
}

void
L1TrackMatcher::matchTrackMuonToSimTrack(const l1t::TkMuonCollection& trackmuons)
{
  if (l1MuonMatcher_->muon()) {
    const double best_eta = l1MuonMatcher_->muon()->eta();
    const double best_phi = l1MuonMatcher_->muon()->phi();
    std::cout << "Best matching L1Mu eta " << best_eta << std::endl;
    std::cout << "Best matching L1Mu phi " << best_phi << std::endl;

    // matching depends on the matched track and the matched muon
    for (const auto& trackmuon : trackmuons) {
      const double muon_eta = trackmuon.muRef()->hwEta();
      const double muon_phi = trackmuon.muRef()->hwPhi();
      std::cout << "\tcandidate L1TkMu eta " << muon_eta << std::endl;
      std::cout << "\tcandidate L1TkMu phi " << muon_phi << std::endl;

      // need to do the conversion!!

      if (std::abs(best_eta - muon_eta)<0.01 and std::abs(best_phi - muon_phi)<0.01) {

        l1TrackMuon_.reset(new l1t::TkMuon(trackmuon));

        const double l1Tk_eta = trackmuon.trkPtr()->momentum().eta();
        const double l1Tk_phi = trackmuon.trkPtr()->momentum().barePhi();

         cout<<"\tBest l1Tk_eta "<<l1Tk_eta<<endl;
         cout<<"\tBest l1Tk_phi "<<l1Tk_phi<<endl;
         cout<<"\tBest muon_eta "<<l1TrackMuon_->muRef()->hwEta()<<endl;
         cout<<"\tBest muon_phi "<<l1TrackMuon_->muRef()->hwPhi()<<endl;
      }
    }
  }
  else{
    std::cout << "No Best matching L1Mu" << std::endl;
  }
}
