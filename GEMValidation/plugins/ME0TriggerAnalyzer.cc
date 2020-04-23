#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/MuonDetId/interface/CSCTriggerNumbering.h"

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"

#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"
#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/MyTrackEff.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/Randomize.h"

#include "TTree.h"

#include <iomanip>
#include <sstream>
#include <memory>
#include <math.h>
#include <bitset>
#include <vector>

using namespace std;
using namespace matching;

const int nMaxME0Hits = 8 * 384 * 6;

namespace {

struct MyTrack
{
  void init(); // initialize to default values
  TTree* book(TTree *t, const std::string & name = "trk");

  Int_t lumi;
  Int_t run;
  Int_t event;

  Float_t pt, eta, phi, pz, dxy;
  int charge;
  int endcap;
  Int_t pdgid;
  int chamber;
  int pad1;
  int pad6;
};



void MyTrack::init()
{
  lumi = -99;
  run = -99;
  event = -99;

  pt = 0.;
  phi = 0.;
  eta = -9.;
  dxy = -999.;
  charge = -9;
  endcap = -9;
  pdgid = -9999;
  chamber = -1;
  pad1 = -1;
  pad6 = -1;
}


TTree* MyTrack::book(TTree *t, const std::string & name)
{
  edm::Service< TFileService > fs;
  t = fs->make<TTree>(name.c_str(), name.c_str());

  t->Branch("lumi", &lumi);
  t->Branch("run", &run);
  t->Branch("event", &event);

  t->Branch("pt", &pt);
  t->Branch("pz", &pz);
  t->Branch("eta", &eta);
  t->Branch("dxy", &dxy);
  t->Branch("phi", &phi);
  t->Branch("charge", &charge);
  t->Branch("endcap", &endcap);
  t->Branch("pdgid", &pdgid);
  t->Branch("chamber", &chamber);
  t->Branch("pad1", &pad1);
  t->Branch("pad6", &pad6);
  return t;
}


struct MyHits
{
  void init(); // initialize to default values
  TTree* book(TTree *t, const std::string & name = "hits");

  int nME0 = 0;
  int endcap[nMaxME0Hits];
  int chamber[nMaxME0Hits];
  int layer[nMaxME0Hits];
  int pad[nMaxME0Hits];
  int part[nMaxME0Hits];
  int isMu[nMaxME0Hits];
  int bx[nMaxME0Hits];

  float global_x[nMaxME0Hits];
  float global_y[nMaxME0Hits];
  float global_z[nMaxME0Hits];

  float local_x[nMaxME0Hits];
  float local_y[nMaxME0Hits];
  float local_z[nMaxME0Hits];

  int nCSC = 0;
  float csc_global_x[nMaxME0Hits];
  float csc_global_y[nMaxME0Hits];
  float csc_global_z[nMaxME0Hits];

  float csc_local_x[nMaxME0Hits];
  float csc_local_y[nMaxME0Hits];
  float csc_local_z[nMaxME0Hits];
};



void MyHits::init()
{
  nME0 = 0;

  for (int i=0; i<nME0; ++i) {
    endcap[i] = -1;
    chamber[i] = -1;
    layer[i] = -1;
    pad[i] = -1;
    part[i] = -1;
    isMu[i] = 0;
    bx[i] = -9;

    global_x[i] = -999;
    global_y[i] = -999;
    global_z[i] = -999;

    local_x[i] = -999;
    local_y[i] = -999;
    local_z[i] = -999;

    csc_global_x[i] = -999;
    csc_global_y[i] = -999;
    csc_global_z[i] = -999;

    csc_local_x[i] = -999;
    csc_local_y[i] = -999;
    csc_local_z[i] = -999;
  }
}


TTree* MyHits::book(TTree *t, const std::string & name)
{
  edm::Service< TFileService > fs;
  t = fs->make<TTree>(name.c_str(), name.c_str());

  t->Branch("nME0", &nME0);
  t->Branch("endcap", endcap, "endcap[nME0]/I");
  t->Branch("chamber", chamber, "chamber[nME0]/I");
  t->Branch("layer", layer, "layer[nME0]/I");
  t->Branch("pad", pad, "pad[nME0]/I");
  t->Branch("part", part, "part[nME0]/I");
  t->Branch("isMu", isMu, "isMu[nME0]/I");
  t->Branch("bx", isMu, "bx[nME0]/I");

  t->Branch("global_x", global_x, "global_x[nME0]/F");
  t->Branch("global_y", global_y, "global_y[nME0]/F");
  t->Branch("global_z", global_z, "global_z[nME0]/F");

  t->Branch("local_x", local_x, "local_x[nME0]/F");
  t->Branch("local_y", local_y, "local_y[nME0]/F");
  t->Branch("local_z", local_z, "local_z[nME0]/F");


  t->Branch("nCSC", &nCSC);
  t->Branch("csc_global_x", csc_global_x, "csc_global_x[nCSC]/F");
  t->Branch("csc_global_y", csc_global_y, "csc_global_y[nCSC]/F");
  t->Branch("csc_global_z", csc_global_z, "csc_global_z[nCSC]/F");

  t->Branch("csc_local_x", csc_local_x, "csc_local_x[nCSC]/F");
  t->Branch("csc_local_y", csc_local_y, "csc_local_y[nCSC]/F");
  t->Branch("csc_local_z", csc_local_z, "csc_local_z[nCSC]/F");

  return t;
}

}


// --------------------------- ME0TriggerAnalyzer ---------------------------
class ME0TriggerAnalyzer : public edm::EDAnalyzer
{
public:

  explicit ME0TriggerAnalyzer(const edm::ParameterSet&);

  ~ME0TriggerAnalyzer() {}

  virtual void beginRun(const edm::Run&, const edm::EventSetup&);

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

private:
  int ievent;

  void bookSimTracksDeltaTree();

  void analyzeTrackChamberDeltas(SimTrackMatchManager& match, int trk_no);
  void analyzeTrackEff(SimTrackMatchManager& match, int trk_no);
  void printout(SimTrackMatchManager& match, int trk_no, const char msg[300]);

  bool isSimTrackGood(const SimTrack &t);
  int detIdToMEStation(int st, int ri);

  edm::ParameterSet cfg_;

  edm::EDGetTokenT<reco::GenParticleCollection> genParticleInput_;
  edm::EDGetTokenT<edm::SimVertexContainer> simVertexInput_;
  edm::EDGetTokenT<edm::SimTrackContainer> simTrackInput_;

  edm::EDGetTokenT<edm::PSimHitContainer> gemSimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> cscSimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> rpcSimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> me0SimHitInput_;
  edm::EDGetTokenT<edm::PSimHitContainer> dtSimHitInput_;

  edm::EDGetTokenT<GEMDigiCollection> gemDigiInput_;
  edm::EDGetTokenT<GEMPadDigiCollection> gemPadDigiInput_;
  edm::EDGetTokenT<GEMCoPadDigiCollection> gemCoPadDigiInput_;
  edm::EDGetTokenT<GEMRecHitCollection> gemRecHitInput_;

  edm::EDGetTokenT<ME0DigiCollection> me0DigiInput_;
  edm::EDGetTokenT<ME0PadDigiCollection> me0PadDigiInput_;
  edm::EDGetTokenT<ME0RecHitCollection> me0RecHitInput_;
  edm::EDGetTokenT<ME0SegmentCollection> me0SegmentInput_;

  edm::EDGetTokenT<CSCComparatorDigiCollection> cscComparatorDigiInput_;
  edm::EDGetTokenT<CSCWireDigiCollection> cscWireDigiInput_;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clctInputs_;
  edm::EDGetTokenT<CSCALCTDigiCollection> alctInputs_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lctInputs_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> mplctInputs_;
  edm::EDGetTokenT<CSCRecHit2DCollection> cscRecHit2DInput_;
  edm::EDGetTokenT<CSCSegmentCollection> cscSegmentInput_;

  edm::EDGetTokenT<DTDigiCollection> dtDigiInput_;
  edm::EDGetTokenT<DTLocalTriggerCollection> dtStubInput_;
  edm::EDGetTokenT<DTRecHitCollection> dtRecHit1DPairInput_;
  edm::EDGetTokenT<DTRecSegment2DCollection> dtRecSegment2DInput_;
  edm::EDGetTokenT<DTRecSegment4DCollection> dtRecSegment4DInput_;

  edm::EDGetTokenT<RPCDigiCollection> rpcDigiInput_;
  edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitInput_;

  edm::EDGetTokenT<l1t::EMTFTrackCollection> emtfTrackInputLabel_;
  edm::EDGetTokenT<BXVector<l1t::RegionalMuonCand>> regMuonCandInputLabel_;
  edm::EDGetTokenT<BXVector<l1t::Muon>> gmtInputLabel_;

  edm::EDGetTokenT<reco::TrackExtraCollection> recoTrackExtraInputLabel_;
  edm::EDGetTokenT<reco::TrackCollection> recoTrackInputLabel_;
  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> recoChargedCandidateInputLabel_;

  int verboseSimTrack_;
  int verboseL1Track_;
  double simTrackMinPt_;
  double simTrackMinEta_;
  double simTrackMaxEta_;
  double simTrackOnlyMuon_;
  int verbose_;
  bool ntupleTrackChamberDelta_;
  bool ntupleTrackEff_;

  TTree *tree_eff_;
  TTree *tree_hit_;

  MyTrackEff  etrk_;
  MyHits  hits_;

  edm::Handle<ME0PadDigiCollection> all_me0sh;
};


ME0TriggerAnalyzer::ME0TriggerAnalyzer(const edm::ParameterSet& ps)
: cfg_(ps.getParameterSet("simTrackMatching"))
, verbose_(ps.getUntrackedParameter<int>("verbose", 0))
{
  ievent = 0;

  ntupleTrackEff_ = cfg_.getParameter<bool>("ntupleTrackEff");

  const auto& displacedGenMu = cfg_.getParameter<edm::ParameterSet>("displacedGenMu");
  genParticleInput_ = consumes<reco::GenParticleCollection>(displacedGenMu.getParameter<edm::InputTag>("validInputTags"));

  const auto& simVertex = cfg_.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("validInputTags"));

  const auto& simTrack = cfg_.getParameter<edm::ParameterSet>("simTrack");
  verboseSimTrack_ = simTrack.getParameter<int>("verbose");
  simTrackInput_ = consumes<edm::SimTrackContainer>(simTrack.getParameter<edm::InputTag>("validInputTags"));
  simTrackMinPt_ = simTrack.getParameter<double>("minPt");
  simTrackMinEta_ = simTrack.getParameter<double>("minEta");
  simTrackMaxEta_ = simTrack.getParameter<double>("maxEta");
  simTrackOnlyMuon_ = simTrack.getParameter<bool>("onlyMuon");

  const auto& gemSimHit_ = cfg_.getParameter<edm::ParameterSet>("gemSimHit");
  gemSimHitInput_ = consumes<edm::PSimHitContainer>(gemSimHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscSimHit_= cfg_.getParameter<edm::ParameterSet>("cscSimHit");
  cscSimHitInput_ = consumes<edm::PSimHitContainer>(cscSimHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& me0SimHit_ = cfg_.getParameter<edm::ParameterSet>("me0SimHit");
  me0SimHitInput_ = consumes<edm::PSimHitContainer>(me0SimHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& rpcSimHit_ = cfg_.getParameter<edm::ParameterSet>("rpcSimHit");
  rpcSimHitInput_ = consumes<edm::PSimHitContainer>(rpcSimHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& dtSimHit_ = cfg_.getParameter<edm::ParameterSet>("dtSimHit");
  dtSimHitInput_ = consumes<edm::PSimHitContainer>(dtSimHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& gemDigi_= cfg_.getParameter<edm::ParameterSet>("gemStripDigi");
  gemDigiInput_ = consumes<GEMDigiCollection>(gemDigi_.getParameter<edm::InputTag>("validInputTags"));

  const auto& gemPad_= cfg_.getParameter<edm::ParameterSet>("gemPadDigi");
  gemPadDigiInput_ = consumes<GEMPadDigiCollection>(gemPad_.getParameter<edm::InputTag>("validInputTags"));

  const auto& gemCoPad_= cfg_.getParameter<edm::ParameterSet>("gemCoPadDigi");
  gemCoPadDigiInput_ = consumes<GEMCoPadDigiCollection>(gemCoPad_.getParameter<edm::InputTag>("validInputTags"));

  const auto& gemRecHit_= cfg_.getParameter<edm::ParameterSet>("gemRecHit");
  gemRecHitInput_ = consumes<GEMRecHitCollection>(gemRecHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& me0Digi_= cfg_.getParameter<edm::ParameterSet>("me0StripDigi");
  me0DigiInput_ = consumes<ME0DigiCollection>(me0Digi_.getParameter<edm::InputTag>("validInputTags"));

  const auto& me0Pad_= cfg_.getParameter<edm::ParameterSet>("me0PadDigi");
  me0PadDigiInput_ = consumes<ME0PadDigiCollection>(me0Pad_.getParameter<edm::InputTag>("validInputTags"));

  const auto& me0RecHit_ = cfg_.getParameter<edm::ParameterSet>("me0RecHit");
  me0RecHitInput_ = consumes<ME0RecHitCollection>(me0RecHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& me0Segment_ = cfg_.getParameter<edm::ParameterSet>("me0Segment");
  me0SegmentInput_ = consumes<ME0SegmentCollection>(me0Segment_.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscComparatorDigi = cfg_.getParameter<edm::ParameterSet>("cscStripDigi");
  cscComparatorDigiInput_ = consumes<CSCComparatorDigiCollection>(cscComparatorDigi.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscWireDigi = cfg_.getParameter<edm::ParameterSet>("cscWireDigi");
  cscWireDigiInput_ = consumes<CSCWireDigiCollection>(cscWireDigi.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscCLCT = cfg_.getParameter<edm::ParameterSet>("cscCLCT");
  clctInputs_ = consumes<CSCCLCTDigiCollection>(cscCLCT.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscALCT = cfg_.getParameter<edm::ParameterSet>("cscALCT");
  alctInputs_ = consumes<CSCALCTDigiCollection>(cscALCT.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscLCT = cfg_.getParameter<edm::ParameterSet>("cscLCT");
  lctInputs_ = consumes<CSCCorrelatedLCTDigiCollection>(cscLCT.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscMPLCT = cfg_.getParameter<edm::ParameterSet>("cscMPLCT");
  mplctInputs_ = consumes<CSCCorrelatedLCTDigiCollection>(cscMPLCT.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscRecHit2D = cfg_.getParameter<edm::ParameterSet>("cscRecHit");
  cscRecHit2DInput_ = consumes<CSCRecHit2DCollection>(cscRecHit2D.getParameter<edm::InputTag>("validInputTags"));

  const auto& cscSegment2D = cfg_.getParameter<edm::ParameterSet>("cscSegment");
  cscSegmentInput_ = consumes<CSCSegmentCollection>(cscSegment2D.getParameter<edm::InputTag>("validInputTags"));

  const auto& dtDigi_= cfg_.getParameter<edm::ParameterSet>("dtDigi");
  dtDigiInput_ = consumes<DTDigiCollection>(dtDigi_.getParameter<edm::InputTag>("validInputTags"));

  const auto& dtStub_= cfg_.getParameter<edm::ParameterSet>("dtLocalTrigger");
  dtStubInput_ = consumes<DTLocalTriggerCollection>(dtStub_.getParameter<edm::InputTag>("validInputTags"));

  const auto& dtRecHit1DPair = cfg_.getParameter<edm::ParameterSet>("dtRecHit");
  dtRecHit1DPairInput_ = consumes<DTRecHitCollection>(dtRecHit1DPair.getParameter<edm::InputTag>("validInputTags"));

  const auto& dtSegment2D = cfg_.getParameter<edm::ParameterSet>("dtRecSegment2D");
  dtRecSegment2DInput_ = consumes<DTRecSegment2DCollection>(dtSegment2D.getParameter<edm::InputTag>("validInputTags"));

  const auto& dtSegment4D = cfg_.getParameter<edm::ParameterSet>("dtRecSegment4D");
  dtRecSegment4DInput_ = consumes<DTRecSegment4DCollection>(dtSegment4D.getParameter<edm::InputTag>("validInputTags"));

  const auto& rpcDigi_= cfg_.getParameter<edm::ParameterSet>("rpcStripDigi");
  rpcDigiInput_ = consumes<RPCDigiCollection>(rpcDigi_.getParameter<edm::InputTag>("validInputTags"));

  const auto& rpcRecHit_= cfg_.getParameter<edm::ParameterSet>("rpcRecHit");
  rpcRecHitInput_ = consumes<RPCRecHitCollection>(rpcRecHit_.getParameter<edm::InputTag>("validInputTags"));

  const auto& emtfTrack = cfg_.getParameter<edm::ParameterSet>("upgradeEmtfTrack");
  emtfTrackInputLabel_ = consumes<l1t::EMTFTrackCollection>(emtfTrack.getParameter<edm::InputTag>("validInputTags"));

  const auto& upgradeemtfCand = cfg_.getParameter<edm::ParameterSet>("upgradeEmtfCand");
  regMuonCandInputLabel_ = consumes< BXVector<l1t::RegionalMuonCand> >(upgradeemtfCand.getParameter<edm::InputTag>("validInputTags"));

  const auto& upgradegmt = cfg_.getParameter<edm::ParameterSet>("upgradeGMT");
  gmtInputLabel_ = consumes< BXVector<l1t::Muon> >(upgradegmt.getParameter<edm::InputTag>("validInputTags"));

  const auto& recoTrackExtra = cfg_.getParameter<edm::ParameterSet>("recoTrackExtra");
  recoTrackExtraInputLabel_ = consumes<reco::TrackExtraCollection>(recoTrackExtra.getParameter<edm::InputTag>("validInputTags"));

  const auto& recoTrack = cfg_.getParameter<edm::ParameterSet>("recoTrack");
  recoTrackInputLabel_ = consumes<reco::TrackCollection>(recoTrack.getParameter<edm::InputTag>("validInputTags"));

  const auto& recoChargedCandidate = cfg_.getParameter<edm::ParameterSet>("recoChargedCandidate");
  recoChargedCandidateInputLabel_ = consumes<reco::RecoChargedCandidateCollection>(recoChargedCandidate.getParameter<edm::InputTag>("validInputTags"));

  tree_eff_ = etrk_.book(tree_eff_, "ME0Track");
  tree_hit_ = hits_.book(tree_hit_, "ME0Hit");
}


void ME0TriggerAnalyzer::beginRun(const edm::Run &iRun, const edm::EventSetup &iSetup)
{
}


bool ME0TriggerAnalyzer::isSimTrackGood(const SimTrack &t)
{
  // SimTrack selection
  if (t.noVertex()) return false;
  if (t.noGenpart()) return false;
  // only muons
  if (std::abs(t.type()) != 13 and simTrackOnlyMuon_) return false;
  // pt selection
  if (t.momentum().pt() < simTrackMinPt_) return false;
  // eta selection
  const float eta(std::abs(t.momentum().eta()));
  if (eta > simTrackMaxEta_ || eta < simTrackMinEta_) return false;
  return true;
}


void ME0TriggerAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  ievent ++;
  edm::Handle<edm::SimTrackContainer> sim_tracks;
  ev.getByToken(simTrackInput_, sim_tracks);
  const edm::SimTrackContainer & sim_track = *sim_tracks.product();

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  ev.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer & sim_vert = *sim_vertices.product();

  ev.getByToken(me0PadDigiInput_, all_me0sh);

  // geometry
  const ME0Geometry* me0_geometry_;
  edm::ESHandle<ME0Geometry> me0_geom_;
  es.get<MuonGeometryRecord>().get(me0_geom_);
  me0_geometry_ = &*me0_geom_;

  /*
  const CSCGeometry* csc_geometry_;
  edm::ESHandle<CSCGeometry> csc_geom_;
  es.get<MuonGeometryRecord>().get(csc_geom_);
  csc_geometry_ = &*csc_geom_;
  */

  if (verboseSimTrack_){
    std::cout << "Total number of SimTrack in this event: " << sim_track.size() << std::endl;
  }

  edm::SimTrackContainer sim_track_selected;
  for (const auto& t: sim_track)
    {
      if (!isSimTrackGood(t)) continue;
      sim_track_selected.push_back(t);
    }

  int trk_no=0;

  std::vector<ME0PadDigi> allMatchedME0Pads;
  for (const auto& t: sim_track_selected) {

    if (verboseSimTrack_){
      std::cout << "Processing selected SimTrack " << trk_no + 1 << std::endl;
      std::cout << "pt(GeV/c) = " << t.momentum().pt() << ", eta = " << t.momentum().eta()
                << ", phi = " << t.momentum().phi() << ", Q = " << t.charge() << ", PDGiD =  " << t.type() << std::endl;
    }

    SimTrackMatchManager match(t, sim_vert[t.vertIndex()], cfg_, ev, es,
                               genParticleInput_,
                               simVertexInput_,
                               simTrackInput_,
                               gemSimHitInput_,
                               cscSimHitInput_,
                               rpcSimHitInput_,
                               me0SimHitInput_,
                               dtSimHitInput_,
                               gemDigiInput_,
                               gemPadDigiInput_,
                               gemCoPadDigiInput_,
                               gemRecHitInput_,
                               me0DigiInput_,
                               me0PadDigiInput_,
                               me0RecHitInput_,
                               me0SegmentInput_,
                               cscComparatorDigiInput_,
                               cscWireDigiInput_,
                               clctInputs_,
                               alctInputs_,
                               lctInputs_,
                               mplctInputs_,
                               cscRecHit2DInput_,
                               cscSegmentInput_,
                               dtDigiInput_,
                               dtStubInput_,
                               dtRecHit1DPairInput_,
                               dtRecSegment2DInput_,
                               dtRecSegment4DInput_,
                               rpcDigiInput_,
                               rpcRecHitInput_,
                               emtfTrackInputLabel_,
                               regMuonCandInputLabel_,
                               gmtInputLabel_,
                               recoTrackExtraInputLabel_,
                               recoTrackInputLabel_,
                               recoChargedCandidateInputLabel_
                               );

    if (ntupleTrackEff_) analyzeTrackEff(match, trk_no);
    auto temp3 = match.me0Digis().pads();
    allMatchedME0Pads.insert(std::end(allMatchedME0Pads), std::begin(temp3), std::end(temp3));
    ++trk_no;
  }

  const ME0PadDigiCollection* all_me0 = all_me0sh.product();

  // do a loop over the ME0 pad collection
  int nME0Pad = 0;
  for (auto adetUnitIt = all_me0->begin(); adetUnitIt != all_me0->end(); adetUnitIt++) {
    const ME0DetId& id = (*adetUnitIt).first;
    int ch = id.chamber() ;

    const auto& part = me0_geometry_->etaPartition(id);

    const auto& digis_in_det = all_me0->get(id);
    for (auto digiIt = digis_in_det.first; digiIt != digis_in_det.second; digiIt++) {
      const auto& lct = *digiIt;
      std::cout << id << " " << lct << std::endl;
      hits_.endcap[nME0Pad] = id.region();
      hits_.chamber[nME0Pad] = id.chamber();
      hits_.layer[nME0Pad] = id.layer();
      hits_.part[nME0Pad] = id.roll();
      hits_.pad[nME0Pad] = lct.pad();
      hits_.bx[nME0Pad] = lct.bx();
      //x check if originating from real muon or not
      if(std::find(allMatchedME0Pads.begin(), allMatchedME0Pads.end(), lct) != allMatchedME0Pads.end()) {
        hits_.isMu[nME0Pad] = 1;
        std::cout << "is muon " << std::endl;
      }

      // geometry
      const auto& lp = part->centreOfPad(lct.pad());
      hits_.local_x[nME0Pad] = lp.x();
      hits_.local_y[nME0Pad] = lp.y();
      hits_.local_z[nME0Pad] = lp.z();

      const auto& gp = part->toGlobal(lp);
      hits_.global_x[nME0Pad] = gp.x();
      hits_.global_y[nME0Pad] = gp.y();
      hits_.global_z[nME0Pad] = gp.z();

      nME0Pad++;
    }
  }
  hits_.nME0 = nME0Pad;
  tree_hit_->Fill();

}



void ME0TriggerAnalyzer::analyzeTrackEff(SimTrackMatchManager& match, int trk_no)
{
  const SimHitMatcher& match_sh = match.simhits();
  const ME0DigiMatcher& match_me0digi = match.me0Digis();
  const SimTrack &t = match_sh.trk();

  if (verbose_) std::cout <<"ME0TriggerAnalyzer step1 "<< std::endl;

  etrk_.init();

  etrk_.run = match.simhits().event().id().run();
  etrk_.lumi = match.simhits().event().id().luminosityBlock();
  etrk_.event = match.simhits().event().id().event();
  etrk_.pt = t.momentum().pt();
  etrk_.pz = t.momentum().pz();
  etrk_.phi = t.momentum().phi();
  etrk_.eta = t.momentum().eta();
  etrk_.dxy = match.simhits().dxy();
  etrk_.charge = t.charge();
  etrk_.endcap = (etrk_.eta > 0.) ? 1 : -1;
  etrk_.pdgid = t.type();

  // hits at the ME0 chamber

  tree_eff_->Fill();
}

DEFINE_FWK_MODULE(ME0TriggerAnalyzer);
