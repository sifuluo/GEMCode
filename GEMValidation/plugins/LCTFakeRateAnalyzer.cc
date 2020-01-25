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

static const int NumOfTrees = 13;

typedef std::vector<CSCALCTDigi> CSCALCTDigiContainer;
typedef std::vector<CSCCLCTDigi> CSCCLCTDigiContainer;
typedef std::vector<CSCCorrelatedLCTDigi> CSCCorrelatedLCTDigiContainer;

struct ChamberOccupancy
{
  int nME0p[18];
  int nME0m[18];

  int nME0p_mu[18];
  int nME0m_mu[18];

  int nLCT_ME11p[36];
  int nLCT_ME11m[36];

  int nLCT_ME12p[36];
  int nLCT_ME12m[36];

  int nLCT_ME13p[36];
  int nLCT_ME13m[36];

  int nLCT_ME21p[18];
  int nLCT_ME21m[18];

  int nLCT_ME22p[36];
  int nLCT_ME22m[36];

  int nLCT_ME31p[18];
  int nLCT_ME31m[18];

  int nLCT_ME32p[36];
  int nLCT_ME32m[36];

  int nLCT_ME41p[18];
  int nLCT_ME41m[18];

  int nLCT_ME42p[36];
  int nLCT_ME42m[36];

  int nLCT_ME11p_mu[36];
  int nLCT_ME11m_mu[36];

  int nLCT_ME12p_mu[36];
  int nLCT_ME12m_mu[36];

  int nLCT_ME13p_mu[36];
  int nLCT_ME13m_mu[36];

  int nLCT_ME21p_mu[18];
  int nLCT_ME21m_mu[18];

  int nLCT_ME22p_mu[36];
  int nLCT_ME22m_mu[36];

  int nLCT_ME31p_mu[18];
  int nLCT_ME31m_mu[18];

  int nLCT_ME32p_mu[36];
  int nLCT_ME32m_mu[36];

  int nLCT_ME41p_mu[18];
  int nLCT_ME41m_mu[18];

  int nLCT_ME42p_mu[36];
  int nLCT_ME42m_mu[36];

  void init();
  TTree* book(TTree *t);
};

void ChamberOccupancy::init()
{
  for (unsigned i = 0; i<18; i++){
    nME0p[i] = 0;
    nME0m[i] = 0;

    nLCT_ME21p[i] = 0;
    nLCT_ME21m[i] = 0;

    nLCT_ME31p[i] = 0;
    nLCT_ME31m[i] = 0;

    nLCT_ME41p[i] = 0;
    nLCT_ME41m[i] = 0;
  }
  for (unsigned i = 0; i<36; i++){
    nLCT_ME11p[i] = 0;
    nLCT_ME11m[i] = 0;

    nLCT_ME12p[i] = 0;
    nLCT_ME12m[i] = 0;

    nLCT_ME13p[i] = 0;
    nLCT_ME13m[i] = 0;

    nLCT_ME22p[i] = 0;
    nLCT_ME22m[i] = 0;

    nLCT_ME32p[i] = 0;
    nLCT_ME32m[i] = 0;

    nLCT_ME42p[i] = 0;
    nLCT_ME42m[i] = 0;
  }


  for (unsigned i = 0; i<18; i++){
    nLCT_ME21p_mu[i] = 0;
    nLCT_ME21m_mu[i] = 0;

    nLCT_ME31p_mu[i] = 0;
    nLCT_ME31m_mu[i] = 0;

    nLCT_ME41p_mu[i] = 0;
    nLCT_ME41m_mu[i] = 0;

    nME0p_mu[i] = 0;
    nME0m_mu[i] = 0;
  }
  for (unsigned i = 0; i<36; i++){
    nLCT_ME11p_mu[i] = 0;
    nLCT_ME11m_mu[i] = 0;

    nLCT_ME12p_mu[i] = 0;
    nLCT_ME12m_mu[i] = 0;

    nLCT_ME13p_mu[i] = 0;
    nLCT_ME13m_mu[i] = 0;

    nLCT_ME22p_mu[i] = 0;
    nLCT_ME22m_mu[i] = 0;

    nLCT_ME32p_mu[i] = 0;
    nLCT_ME32m_mu[i] = 0;

    nLCT_ME42p_mu[i] = 0;
    nLCT_ME42m_mu[i] = 0;
  }
}

TTree * ChamberOccupancy::book(TTree *t)
{
  edm::Service< TFileService > fs;
  t = fs->make<TTree>("ChamberOccupancy", "ChamberOccupancy");

  t->Branch("nLCT_ME11p", &nLCT_ME11p, "nLCT_ME11p[36]/I");
  t->Branch("nLCT_ME11m", &nLCT_ME11m, "nLCT_ME11m[36]/I");

  t->Branch("nLCT_ME12p", &nLCT_ME12p, "nLCT_ME12p[36]/I");
  t->Branch("nLCT_ME12m", &nLCT_ME12m, "nLCT_ME12m[36]/I");

  t->Branch("nLCT_ME13p", &nLCT_ME13p, "nLCT_ME13p[36]/I");
  t->Branch("nLCT_ME13m", &nLCT_ME13m, "nLCT_ME13m[36]/I");

  t->Branch("nLCT_ME21p", &nLCT_ME21p, "nLCT_ME21p[18]/I");
  t->Branch("nLCT_ME21m", &nLCT_ME21m, "nLCT_ME21m[18]/I");

  t->Branch("nLCT_ME22p", &nLCT_ME22p, "nLCT_ME22p[36]/I");
  t->Branch("nLCT_ME22m", &nLCT_ME22m, "nLCT_ME22m[36]/I");

  t->Branch("nLCT_ME31p", &nLCT_ME31p, "nLCT_ME31p[18]/I");
  t->Branch("nLCT_ME31m", &nLCT_ME31m, "nLCT_ME31m[18]/I");

  t->Branch("nLCT_ME32p", &nLCT_ME32p, "nLCT_ME32p[36]/I");
  t->Branch("nLCT_ME32m", &nLCT_ME32m, "nLCT_ME32m[36]/I");

  t->Branch("nLCT_ME41p", &nLCT_ME41p, "nLCT_ME41p[18]/I");
  t->Branch("nLCT_ME41m", &nLCT_ME41m, "nLCT_ME41m[18]/I");

  t->Branch("nLCT_ME42p", &nLCT_ME42p, "nLCT_ME42p[36]/I");
  t->Branch("nLCT_ME42m", &nLCT_ME42m, "nLCT_ME42m[36]/I");


  t->Branch("nLCT_ME11p_mu", &nLCT_ME11p_mu, "nLCT_ME11p_mu[36]/I");
  t->Branch("nLCT_ME11m_mu", &nLCT_ME11m_mu, "nLCT_ME11m_mu[36]/I");

  t->Branch("nLCT_ME12p_mu", &nLCT_ME12p_mu, "nLCT_ME12p_mu[36]/I");
  t->Branch("nLCT_ME12m_mu", &nLCT_ME12m_mu, "nLCT_ME12m_mu[36]/I");

  t->Branch("nLCT_ME13p_mu", &nLCT_ME13p_mu, "nLCT_ME13p_mu[36]/I");
  t->Branch("nLCT_ME13m_mu", &nLCT_ME13m_mu, "nLCT_ME13m_mu[36]/I");

  t->Branch("nLCT_ME21p_mu", &nLCT_ME21p_mu, "nLCT_ME21p_mu[18]/I");
  t->Branch("nLCT_ME21m_mu", &nLCT_ME21m_mu, "nLCT_ME21m_mu[18]/I");

  t->Branch("nLCT_ME22p_mu", &nLCT_ME22p_mu, "nLCT_ME22p_mu[36]/I");
  t->Branch("nLCT_ME22m_mu", &nLCT_ME22m_mu, "nLCT_ME22m_mu[36]/I");

  t->Branch("nLCT_ME31p_mu", &nLCT_ME31p_mu, "nLCT_ME31p_mu[18]/I");
  t->Branch("nLCT_ME31m_mu", &nLCT_ME31m_mu, "nLCT_ME31m_mu[18]/I");

  t->Branch("nLCT_ME32p_mu", &nLCT_ME32p_mu, "nLCT_ME32p_mu[36]/I");
  t->Branch("nLCT_ME32m_mu", &nLCT_ME32m_mu, "nLCT_ME32m_mu[36]/I");

  t->Branch("nLCT_ME41p_mu", &nLCT_ME41p_mu, "nLCT_ME41p_mu[18]/I");
  t->Branch("nLCT_ME41m_mu", &nLCT_ME41m_mu, "nLCT_ME41m_mu[18]/I");

  t->Branch("nLCT_ME42p_mu", &nLCT_ME42p_mu, "nLCT_ME42p_mu[36]/I");
  t->Branch("nLCT_ME42m_mu", &nLCT_ME42m_mu, "nLCT_ME42m_mu[36]/I");



  t->Branch("nME0p", &nME0p, "nME0p[18]/I");
  t->Branch("nME0m", &nME0m, "nME0m[18]/I");

  t->Branch("nME0p_mu", &nME0p_mu, "nME0p_mu[18]/I");
  t->Branch("nME0m_mu", &nME0m_mu, "nME0m_mu[18]/I");

  return t;
}

// --------------------------- LCTFakeRateAnalyzer ---------------------------
class LCTFakeRateAnalyzer : public edm::EDAnalyzer
{
public:

  explicit LCTFakeRateAnalyzer(const edm::ParameterSet&);

  ~LCTFakeRateAnalyzer() {}

  virtual void beginRun(const edm::Run&, const edm::EventSetup&);

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  enum {ME0=12};


private:
  int ievent;

  void analyzeTrackEff(SimTrackMatchManager& match, int trk_no);
  void printout(SimTrackMatchManager& match, int trk_no, const char msg[300]);

  bool isSimTrackGood(const SimTrack &t);
  int detIdToMEStation(int st, int ri);

  edm::ParameterSet cfg_;
  edm::ParameterSet displacedMuPt_cfg_;

  edm::EDGetTokenT<CSCALCTDigiCollection> alcts_d_token_;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clcts_d_token_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lcts_tmb_d_token_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lcts_mpc_d_token_;
  edm::EDGetTokenT<ME0SegmentCollection> me0_token_;

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

  //edm::EDGetTokenT<L1TTTrackCollectionType> trackInputLabel_;
  //edm::EDGetTokenT<l1t::L1TkMuonParticleCollection> trackMuonInputLabel_;

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
  bool ntupleTrackEff_;
  double bendingcutPt_;
  std::vector<string> cscStations_;
  std::vector<std::pair<int,int> > cscStationsCo_;
  std::set<int> stations_to_use_;

  TTree *tree_eff_[NumOfTrees];
  MyTrackEff  etrk_[NumOfTrees];

  TTree *tree_occ_;
  ChamberOccupancy occ_;
};


LCTFakeRateAnalyzer::LCTFakeRateAnalyzer(const edm::ParameterSet& ps)
: cfg_(ps.getParameterSet("simTrackMatching"))
, verbose_(ps.getUntrackedParameter<int>("verbose", 0))
{
  ievent = 0;

  std::string lctProducerData_ = "simCscTriggerPrimitiveDigis";
  alcts_d_token_ = consumes<CSCALCTDigiCollection>(edm::InputTag(lctProducerData_,"","MyCSC"));
  clcts_d_token_ = consumes<CSCCLCTDigiCollection>(edm::InputTag(lctProducerData_,"","MyCSC"));
  lcts_tmb_d_token_ = consumes<CSCCorrelatedLCTDigiCollection>(edm::InputTag(lctProducerData_,"","MyCSC"));

  cscStations_ = cfg_.getParameter<std::vector<string> >("cscStations");
  ntupleTrackEff_ = cfg_.getParameter<bool>("ntupleTrackEff");
  bendingcutPt_ = cfg_.getUntrackedParameter<double>("bendingcutPt",10);

  displacedMuPt_cfg_ = cfg_.getParameter<edm::ParameterSet>("displacedMuPtAssignment");

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

  //const auto& l1Track = cfg_.getParameter<edm::ParameterSet>("l1track");
  //trackInputLabel_ = consumes<L1TTTrackCollectionType>(l1Track.getParameter<edm::InputTag>("validInputTags"));
  //verboseL1Track_ = l1Track.getParameter<int>("verbose");

  //const auto& l1TrackMuon = cfg_.getParameter<edm::ParameterSet>("l1tkmuon");
  //trackMuonInputLabel_ = consumes<l1t::L1TkMuonParticleCollection>(l1TrackMuon.getParameter<edm::InputTag>("validInputTags"));

  const auto& recoTrackExtra = cfg_.getParameter<edm::ParameterSet>("recoTrackExtra");
  recoTrackExtraInputLabel_ = consumes<reco::TrackExtraCollection>(recoTrackExtra.getParameter<edm::InputTag>("validInputTags"));

  const auto& recoTrack = cfg_.getParameter<edm::ParameterSet>("recoTrack");
  recoTrackInputLabel_ = consumes<reco::TrackCollection>(recoTrack.getParameter<edm::InputTag>("validInputTags"));

  const auto& recoChargedCandidate = cfg_.getParameter<edm::ParameterSet>("recoChargedCandidate");
  recoChargedCandidateInputLabel_ = consumes<reco::RecoChargedCandidateCollection>(recoChargedCandidate.getParameter<edm::InputTag>("validInputTags"));


  if (ntupleTrackEff_)
  {
    vector<int> stations = cfg_.getParameter<vector<int> >("cscStationsToUse");
    copy(stations.begin(), stations.end(), inserter(stations_to_use_, stations_to_use_.end()) );

    for(const auto& s: stations_to_use_)
    {
      stringstream ss;
      ss << "trk_eff_"<< cscStations_[s];
      // std::cout <<"station to use "<< cscStations_[s]  << std::endl;
      tree_eff_[s] = etrk_[s].book(tree_eff_[s], ss.str());
    }
  }

  tree_occ_ = occ_.book(tree_occ_);

  cscStationsCo_.push_back(std::make_pair(-99,-99));
  cscStationsCo_.push_back(std::make_pair(1,-99));
  cscStationsCo_.push_back(std::make_pair(1,4));
  cscStationsCo_.push_back(std::make_pair(1,1));
  cscStationsCo_.push_back(std::make_pair(1,2));
  cscStationsCo_.push_back(std::make_pair(1,3));
  cscStationsCo_.push_back(std::make_pair(2,1));
  cscStationsCo_.push_back(std::make_pair(2,2));
  cscStationsCo_.push_back(std::make_pair(3,1));
  cscStationsCo_.push_back(std::make_pair(3,2));
  cscStationsCo_.push_back(std::make_pair(4,1));
  cscStationsCo_.push_back(std::make_pair(4,2));
  cscStationsCo_.push_back(std::make_pair(0,1));
}


int LCTFakeRateAnalyzer::detIdToMEStation(int st, int ri)
{
  const auto& p(std::make_pair(st, ri));
  return std::find(cscStationsCo_.begin(), cscStationsCo_.end(), p) - cscStationsCo_.begin();
}


void LCTFakeRateAnalyzer::beginRun(const edm::Run &iRun, const edm::EventSetup &iSetup)
{
}


bool LCTFakeRateAnalyzer::isSimTrackGood(const SimTrack &t)
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


void LCTFakeRateAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  occ_.init();

  ievent ++;
  edm::Handle<edm::SimTrackContainer> sim_tracks;
  ev.getByToken(simTrackInput_, sim_tracks);
  const edm::SimTrackContainer & sim_track = *sim_tracks.product();

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  ev.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer & sim_vert = *sim_vertices.product();

  // load the alct, clct and lct collection
  edm::Handle<CSCALCTDigiCollection> all_alctsh;
  edm::Handle<CSCCLCTDigiCollection> all_clctsh;
  edm::Handle<CSCCorrelatedLCTDigiCollection> all_lctsh;
  edm::Handle<ME0SegmentCollection> all_me0sh;

  ev.getByToken(alcts_d_token_, all_alctsh);
  ev.getByToken(clcts_d_token_, all_clctsh);
  ev.getByToken(lcts_tmb_d_token_, all_lctsh);
  ev.getByToken(me0_token_, all_me0sh);

  const CSCALCTDigiCollection* all_alcts = all_alctsh.product();
  const CSCCLCTDigiCollection* all_clcts = all_clctsh.product();
  const CSCCorrelatedLCTDigiCollection* all_lcts = all_lctsh.product();
  const ME0SegmentCollection* all_me0 = all_me0sh.product();

  if (verboseSimTrack_){
    std::cout << "Total number of SimTrack in this event: " << sim_track.size() << std::endl;
  }

  std::vector<SimTrackMatchManager> matchercontainer;

  CSCALCTDigiContainer allMatchedALCTs;
  CSCCLCTDigiContainer allMatchedCLCTs;
  CSCCorrelatedLCTDigiContainer allMatchedLCTs;

  int trk_no=0;
  for (const auto& t: sim_track)
  {
    if (!isSimTrackGood(t)) continue;
    if (verboseSimTrack_){
      std::cout << "Processing SimTrack " << trk_no + 1 << std::endl;
      std::cout << "pt(GeV/c) = " << t.momentum().pt() << ", eta = " << t.momentum().eta()
                << ", phi = " << t.momentum().phi() << ", Q = " << t.charge() << std::endl;
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
                               //trackInputLabel_,
                               //trackMuonInputLabel_,
                               recoTrackExtraInputLabel_,
                               recoTrackInputLabel_,
                               recoChargedCandidateInputLabel_
                               );
    //    matchercontainer.push_back(match);
    auto temp = match.cscStubs().cscAlcts();
    allMatchedALCTs.insert(std::end(allMatchedALCTs), std::begin(temp), std::end(temp));

    auto temp2 = match.cscStubs().cscClcts();
    allMatchedCLCTs.insert(std::end(allMatchedCLCTs), std::begin(temp2), std::end(temp2));

    auto temp3 = match.cscStubs().cscLcts();
    allMatchedLCTs.insert(std::end(allMatchedLCTs), std::begin(temp3), std::end(temp3));

    if (ntupleTrackEff_) analyzeTrackEff(match, trk_no);

    ++trk_no;
  }

  // analyze the ME0 rate
  for(auto iC = all_me0->id_begin(); iC != all_me0->id_end(); ++iC){
    const auto& ch_segs = all_me0->get(*iC);
    for(auto iS = ch_segs.first; iS != ch_segs.second; ++iS){
      int region = iS->me0DetId().region();
      int chamber = iS->me0DetId().chamber() - 1;
      if (region == -1) {
        occ_.nME0m[chamber]++;
      }
      else {
        occ_.nME0p[chamber]++;
      }
    }
  }


  // // analyze the ALCT rate
  // for (auto adetUnitIt = all_alcts->begin(); adetUnitIt != all_alcts->end(); adetUnitIt++) {
  //   const CSCDetId& id = (*adetUnitIt).first;
  //     int ch = id.chamber() - 1;

  //   const auto& range = (*adetUnitIt).second;
  //   for (auto digiIt = range.first; digiIt != range.second; digiIt++) {
  //     bool lct_valid = (*digiIt).isValid();
  //     const auto& lct = *digiIt;

  //     if (!lct_valid) continue;

  //     if (std::abs(lct.getBX() - CSCConstants::LCT_CENTRAL_BX) > 1) continue;

  //     if (id.zendcap() == 1) {
  //       if (id.station() == 1) {
  //         if (id.ring() == 1) occ_.nLCT_ME11p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME12p[ch]++;
  //         if (id.ring() == 3) occ_.nLCT_ME13p[ch]++;
  //       }
  //       else if (id.station() == 2) {
  //         if (id.ring() == 1) occ_.nLCT_ME21p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME22p[ch]++;
  //       }
  //       else if (id.station() == 3) {
  //         if (id.ring() == 1) occ_.nLCT_ME31p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME32p[ch]++;
  //       }
  //       else if (id.station() == 4){
  //         if (id.ring() == 1) occ_.nLCT_ME41p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME42p[ch]++;
  //       }
  //     }
  //     else {
  //       if (id.station() == 1) {
  //         if (id.ring() == 1) occ_.nLCT_ME11m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME12m[ch]++;
  //         if (id.ring() == 3) occ_.nLCT_ME13m[ch]++;
  //       }
  //       else if (id.station() == 2) {
  //         if (id.ring() == 1) occ_.nLCT_ME21m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME22m[ch]++;
  //       }
  //       else if (id.station() == 3) {
  //         if (id.ring() == 1) occ_.nLCT_ME31m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME32m[ch]++;
  //       }
  //       else if (id.station() == 4){
  //         if (id.ring() == 1) occ_.nLCT_ME41m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME42m[ch]++;
  //       }
  //     }

  //     // if contained in matched stubs
  //     if(std::find(allMatchedLCTs.begin(), allMatchedLCTs.end(), lct) != allMatchedLCTs.end()) {

  //       if (id.zendcap() == 1) {
  //         if (id.station() == 1) {
  //           if (id.ring() == 1) occ_.nLCT_ME11p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME12p_mu[ch]++;
  //           if (id.ring() == 3) occ_.nLCT_ME13p_mu[ch]++;
  //         }
  //         else if (id.station() == 2) {
  //           if (id.ring() == 1) occ_.nLCT_ME21p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME22p_mu[ch]++;
  //         }
  //         else if (id.station() == 3) {
  //           if (id.ring() == 1) occ_.nLCT_ME31p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME32p_mu[ch]++;
  //         }
  //         else if (id.station() == 4){
  //           if (id.ring() == 1) occ_.nLCT_ME41p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME42p_mu[ch]++;
  //         }
  //       }
  //       else {
  //         if (id.station() == 1) {
  //           if (id.ring() == 1) occ_.nLCT_ME11m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME12m_mu[ch]++;
  //           if (id.ring() == 3) occ_.nLCT_ME13m_mu[ch]++;
  //         }
  //         else if (id.station() == 2) {
  //           if (id.ring() == 1) occ_.nLCT_ME21m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME22m_mu[ch]++;
  //         }
  //         else if (id.station() == 3) {
  //           if (id.ring() == 1) occ_.nLCT_ME31m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME32m_mu[ch]++;
  //         }
  //         else if (id.station() == 4){
  //           if (id.ring() == 1) occ_.nLCT_ME41m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME42m_mu[ch]++;
  //         }
  //       }


  //     }

  //   }
  //   //std::cout << "CSC Occ ME+1/1/" << ch+1 << ": " << occ_.nLCT_ME11p[ch] << std::endl;
  // }


  // // analyze the CLCT rate
  // for (auto adetUnitIt = all_lcts->begin(); adetUnitIt != all_lcts->end(); adetUnitIt++) {
  //   const CSCDetId& id = (*adetUnitIt).first;
  //     int ch = id.chamber() - 1;

  //   const auto& range = (*adetUnitIt).second;
  //   for (auto digiIt = range.first; digiIt != range.second; digiIt++) {
  //     bool lct_valid = (*digiIt).isValid();
  //     const auto& lct = *digiIt;

  //     if (!lct_valid) continue;

  //     if (std::abs(lct.getBX() - CSCConstants::LCT_CENTRAL_BX) > 1) continue;

  //     if (id.zendcap() == 1) {
  //       if (id.station() == 1) {
  //         if (id.ring() == 1) occ_.nLCT_ME11p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME12p[ch]++;
  //         if (id.ring() == 3) occ_.nLCT_ME13p[ch]++;
  //       }
  //       else if (id.station() == 2) {
  //         if (id.ring() == 1) occ_.nLCT_ME21p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME22p[ch]++;
  //       }
  //       else if (id.station() == 3) {
  //         if (id.ring() == 1) occ_.nLCT_ME31p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME32p[ch]++;
  //       }
  //       else if (id.station() == 4){
  //         if (id.ring() == 1) occ_.nLCT_ME41p[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME42p[ch]++;
  //       }
  //     }
  //     else {
  //       if (id.station() == 1) {
  //         if (id.ring() == 1) occ_.nLCT_ME11m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME12m[ch]++;
  //         if (id.ring() == 3) occ_.nLCT_ME13m[ch]++;
  //       }
  //       else if (id.station() == 2) {
  //         if (id.ring() == 1) occ_.nLCT_ME21m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME22m[ch]++;
  //       }
  //       else if (id.station() == 3) {
  //         if (id.ring() == 1) occ_.nLCT_ME31m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME32m[ch]++;
  //       }
  //       else if (id.station() == 4){
  //         if (id.ring() == 1) occ_.nLCT_ME41m[ch]++;
  //         if (id.ring() == 2) occ_.nLCT_ME42m[ch]++;
  //       }
  //     }

  //     // if contained in matched stubs
  //     if(std::find(allMatchedLCTs.begin(), allMatchedLCTs.end(), lct) != allMatchedLCTs.end()) {

  //       if (id.zendcap() == 1) {
  //         if (id.station() == 1) {
  //           if (id.ring() == 1) occ_.nLCT_ME11p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME12p_mu[ch]++;
  //           if (id.ring() == 3) occ_.nLCT_ME13p_mu[ch]++;
  //         }
  //         else if (id.station() == 2) {
  //           if (id.ring() == 1) occ_.nLCT_ME21p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME22p_mu[ch]++;
  //         }
  //         else if (id.station() == 3) {
  //           if (id.ring() == 1) occ_.nLCT_ME31p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME32p_mu[ch]++;
  //         }
  //         else if (id.station() == 4){
  //           if (id.ring() == 1) occ_.nLCT_ME41p_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME42p_mu[ch]++;
  //         }
  //       }
  //       else {
  //         if (id.station() == 1) {
  //           if (id.ring() == 1) occ_.nLCT_ME11m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME12m_mu[ch]++;
  //           if (id.ring() == 3) occ_.nLCT_ME13m_mu[ch]++;
  //         }
  //         else if (id.station() == 2) {
  //           if (id.ring() == 1) occ_.nLCT_ME21m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME22m_mu[ch]++;
  //         }
  //         else if (id.station() == 3) {
  //           if (id.ring() == 1) occ_.nLCT_ME31m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME32m_mu[ch]++;
  //         }
  //         else if (id.station() == 4){
  //           if (id.ring() == 1) occ_.nLCT_ME41m_mu[ch]++;
  //           if (id.ring() == 2) occ_.nLCT_ME42m_mu[ch]++;
  //         }
  //       }


  //     }

  //   }
  //   //std::cout << "CSC Occ ME+1/1/" << ch+1 << ": " << occ_.nLCT_ME11p[ch] << std::endl;
  // }


  // analyze the LCT rate
  for (auto adetUnitIt = all_lcts->begin(); adetUnitIt != all_lcts->end(); adetUnitIt++) {
    const CSCDetId& id = (*adetUnitIt).first;
      int ch = id.chamber() - 1;

    const auto& range = (*adetUnitIt).second;
    for (auto digiIt = range.first; digiIt != range.second; digiIt++) {
      bool lct_valid = (*digiIt).isValid();
      const auto& lct = *digiIt;

      if (!lct_valid) continue;

      if (std::abs(lct.getBX() - CSCConstants::LCT_CENTRAL_BX) > 1) continue;

      if (id.zendcap() == 1) {
        if (id.station() == 1) {
          if (id.ring() == 1) occ_.nLCT_ME11p[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME12p[ch]++;
          if (id.ring() == 3) occ_.nLCT_ME13p[ch]++;
        }
        else if (id.station() == 2) {
          if (id.ring() == 1) occ_.nLCT_ME21p[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME22p[ch]++;
        }
        else if (id.station() == 3) {
          if (id.ring() == 1) occ_.nLCT_ME31p[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME32p[ch]++;
        }
        else if (id.station() == 4){
          if (id.ring() == 1) occ_.nLCT_ME41p[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME42p[ch]++;
        }
      }
      else {
        if (id.station() == 1) {
          if (id.ring() == 1) occ_.nLCT_ME11m[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME12m[ch]++;
          if (id.ring() == 3) occ_.nLCT_ME13m[ch]++;
        }
        else if (id.station() == 2) {
          if (id.ring() == 1) occ_.nLCT_ME21m[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME22m[ch]++;
        }
        else if (id.station() == 3) {
          if (id.ring() == 1) occ_.nLCT_ME31m[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME32m[ch]++;
        }
        else if (id.station() == 4){
          if (id.ring() == 1) occ_.nLCT_ME41m[ch]++;
          if (id.ring() == 2) occ_.nLCT_ME42m[ch]++;
        }
      }

      // if contained in matched stubs
      if(std::find(allMatchedLCTs.begin(), allMatchedLCTs.end(), lct) != allMatchedLCTs.end()) {

        if (id.zendcap() == 1) {
          if (id.station() == 1) {
            if (id.ring() == 1) occ_.nLCT_ME11p_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME12p_mu[ch]++;
            if (id.ring() == 3) occ_.nLCT_ME13p_mu[ch]++;
          }
          else if (id.station() == 2) {
            if (id.ring() == 1) occ_.nLCT_ME21p_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME22p_mu[ch]++;
          }
          else if (id.station() == 3) {
            if (id.ring() == 1) occ_.nLCT_ME31p_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME32p_mu[ch]++;
          }
          else if (id.station() == 4){
            if (id.ring() == 1) occ_.nLCT_ME41p_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME42p_mu[ch]++;
          }
        }
        else {
          if (id.station() == 1) {
            if (id.ring() == 1) occ_.nLCT_ME11m_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME12m_mu[ch]++;
            if (id.ring() == 3) occ_.nLCT_ME13m_mu[ch]++;
          }
          else if (id.station() == 2) {
            if (id.ring() == 1) occ_.nLCT_ME21m_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME22m_mu[ch]++;
          }
          else if (id.station() == 3) {
            if (id.ring() == 1) occ_.nLCT_ME31m_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME32m_mu[ch]++;
          }
          else if (id.station() == 4){
            if (id.ring() == 1) occ_.nLCT_ME41m_mu[ch]++;
            if (id.ring() == 2) occ_.nLCT_ME42m_mu[ch]++;
          }
        }


      }

    }
    //std::cout << "CSC Occ ME+1/1/" << ch+1 << ": " << occ_.nLCT_ME11p[ch] << std::endl;
  }

  tree_occ_->Fill();
}



void LCTFakeRateAnalyzer::analyzeTrackEff(SimTrackMatchManager& match, int trk_no)
{
  const DisplacedGENMuonMatcher& match_gen = match.genMuons();
  const SimHitMatcher& match_sh = match.simhits();
  const CSCStubMatcher& match_csc = match.cscStubs();
  const SimTrack &t = match_sh.trk();

  float randtest1 = CLHEP::RandFlat::shoot(0.0,1.0) ;
  float randtest2 = CLHEP::RandFlat::shoot(0.0,1.0) ;
  if (verbose_) std::cout <<"LCTFakeRateAnalyzer step1 "<< std::endl;
  for (const auto& s: stations_to_use_)
  {
    etrk_[s].init();

    etrk_[s].run = match.simhits().event().id().run();
    etrk_[s].lumi = match.simhits().event().id().luminosityBlock();
    etrk_[s].event = match.simhits().event().id().event();
    etrk_[s].rand01_v1 = randtest1;
    etrk_[s].rand01_v2 = randtest2;
    etrk_[s].pt = t.momentum().pt();
    etrk_[s].pz = t.momentum().pz();
    etrk_[s].phi = t.momentum().phi();
    etrk_[s].eta = t.momentum().eta();
    etrk_[s].dxy = match.simhits().dxy();
    etrk_[s].charge = t.charge();
    etrk_[s].endcap = (etrk_[s].eta > 0.) ? 1 : -1;
  }

  if (verbose_) std::cout <<"LCTFakeRateAnalyzer step10 "<< std::endl;
  for (const auto& s: stations_to_use_)
    {
      tree_eff_[s]->Fill();
    }
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void LCTFakeRateAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(LCTFakeRateAnalyzer);
