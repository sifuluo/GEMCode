#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"
#include "GEMCode/GEMValidation/interface/SimTrackAnalyzerManager.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"

#include <iomanip>
#include <sstream>
#include <memory>
#include <math.h>
#include <bitset>

using namespace std;

class GEMCSCAnalyzer : public edm::EDAnalyzer {
public:
  explicit GEMCSCAnalyzer(const edm::ParameterSet&);

  ~GEMCSCAnalyzer() {}

  virtual void beginRun(const edm::Run&, const edm::EventSetup&);

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void analyze(const SimTrack& t, const SimVertex& v);
  bool isSimTrackGood(const SimTrack& t);
  int detIdToMEStation(int st, int ri);

  edm::ParameterSet cfg_;

  edm::EDGetTokenT<edm::SimVertexContainer> simVertexInput_;
  edm::EDGetTokenT<edm::SimTrackContainer> simTrackInput_;

  int verboseSimTrack_;
  int verboseL1Track_;
  double simTrackMinPt_;
  double simTrackMinEta_;
  double simTrackMaxEta_;
  int verbose_;
  std::vector<string> cscStations_;
  std::vector<int> stations_to_use_;

  std::vector<TTree*> tree_eff_;
  std::vector<gem::MyTrack> track_;

  std::unique_ptr<SimTrackMatchManager> matcher_;
  std::unique_ptr<SimTrackAnalyzerManager> analyzer_;
};

GEMCSCAnalyzer::GEMCSCAnalyzer(const edm::ParameterSet& ps) :
  verbose_(ps.getUntrackedParameter<int>("verbose", 0))
{
  cfg_ = ps;

  cscStations_ = ps.getParameter<std::vector<string> >("cscStations");

  const auto& simVertex = ps.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("inputTag"));

  const auto& simTrack = ps.getParameter<edm::ParameterSet>("simTrack");
  simTrackInput_ = consumes<edm::SimTrackContainer>(simTrack.getParameter<edm::InputTag>("inputTag"));
  simTrackMinPt_ = simTrack.getParameter<double>("minPt");
  simTrackMinEta_ = simTrack.getParameter<double>("minEta");
  simTrackMaxEta_ = simTrack.getParameter<double>("maxEta");

  // always use all stations
  stations_to_use_ = {0, /*1, 2, 3, */ 4, 5, 6, 7, 8, 9, 10, 11};


  for (unsigned int i = 0; i < stations_to_use_.size(); ++i) {
    int s = stations_to_use_[i];
    stringstream ss;
    ss << "trk_eff_" << cscStations_[s];
    std::cout << "station to use " << i <<  " " << s << "  " << cscStations_[s] << std::endl;
    track_.push_back(gem::MyTrack());
    tree_eff_.push_back(track_[i].book(tree_eff_[i], ss.str()));
  }

  matcher_.reset(new SimTrackMatchManager(ps, consumesCollector()));
}

void GEMCSCAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {}

bool GEMCSCAnalyzer::isSimTrackGood(const SimTrack& t) {
  // SimTrack selection
  if (t.noVertex())
    return false;
  if (t.noGenpart())
    return false;
  // only muons
  if (std::abs(t.type()) != 13)
    return false;
  // pt selection
  if (t.momentum().pt() < simTrackMinPt_)
    return false;
  // eta selection
  const float eta(std::abs(t.momentum().eta()));
  if (eta > simTrackMaxEta_ || eta < simTrackMinEta_)
    return false;
  return true;
}

void GEMCSCAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& es) {
  matcher_->init(ev, es);

  edm::Handle<edm::SimTrackContainer> sim_tracks;
  ev.getByToken(simTrackInput_, sim_tracks);
  const edm::SimTrackContainer& sim_track = *sim_tracks.product();

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  ev.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer& sim_vert = *sim_vertices.product();

  if (verbose_) {
    std::cout << "Total number of SimTrack in this event: " << sim_track.size() << std::endl;
  }

  edm::SimTrackContainer sim_track_selected;
  for (const auto& t : sim_track) {
    if (!isSimTrackGood(t))
      continue;
    sim_track_selected.push_back(t);
  }

  int trk_no = 0;

  for (const auto& t : sim_track_selected) {
    trk_no++;
    if (verbose_) {
      std::cout << "Processing selected SimTrack " << trk_no + 1 << std::endl;
      std::cout << "pt(GeV/c) = " << t.momentum().pt() << ", eta = " << t.momentum().eta()
                << ", phi = " << t.momentum().phi() << ", Q = " << t.charge() << ", PDGiD =  " << t.type() << std::endl;
    }
    analyze(t, sim_vert[t.vertIndex()]);
  }
}

void GEMCSCAnalyzer::analyze(const SimTrack& t, const SimVertex& v)
{
  // reset all structs
  for (auto& p : track_) {
    p.init();
  }

  // track properties
  for (unsigned i = 0; i < stations_to_use_.size(); ++i) {
    track_[i].pt = t.momentum().pt();
    track_[i].pz = t.momentum().pz();
    track_[i].phi = t.momentum().phi();
    track_[i].eta = t.momentum().eta();
    // track_[i].dxy = match.simhits().dxy();
    track_[i].charge = t.charge();
    track_[i].endcap = (track_[i].eta > 0.) ? 1 : -1;
    track_[i].pdgid = t.type();

  }

  // match the track
  matcher_->match(t, v);

  // analyze the track
  analyzer_.reset(new SimTrackAnalyzerManager(*matcher_));
  analyzer_->init(cfg_);

  // for (auto& p : track_){
  //   cout << "before odd " << p.has_csc_sh_odd << " even " << p.has_csc_sh_even << endl;
  // }

  analyzer_->analyze(track_, stations_to_use_);

  // for (auto& p : track_){
  //   cout << "after odd " << p.has_csc_sh_odd << " even " << p.has_csc_sh_even << endl;
  // }
  // fill all trees
  for (const auto& tree : tree_eff_) {
    tree->Fill();
  }
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void GEMCSCAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(GEMCSCAnalyzer);
