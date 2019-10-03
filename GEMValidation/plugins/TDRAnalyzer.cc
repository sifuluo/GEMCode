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
#include "GEMCode/GEMValidation/interface/PtassignmentHelper.h"
#include "GEMCode/GEMValidation/interface/DisplacedMuonTriggerPtassignment.h"
#include "GEMCode/GEMValidation/interface/L1TrackTriggerVeto.h"
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
// "signed" LCT bend pattern
const int LCT_BEND_PATTERN[11] = { -99,  -5,  4, -4,  3, -3,  2, -2,  1, -1,  0};

// --------------------------- TDRAnalyzer ---------------------------

class TDRAnalyzer : public edm::EDAnalyzer
{
public:

  explicit TDRAnalyzer(const edm::ParameterSet&);

  ~TDRAnalyzer() {}

  virtual void beginRun(const edm::Run&, const edm::EventSetup&);

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  enum {ME0=12};

private:
  int ievent;

  void analyzeTrackEff(SimTrackMatchManager& match, int trk_no);

  bool isSimTrackGood(const SimTrack &t);
  int detIdToMEStation(int st, int ri);

  edm::ParameterSet cfg_;
  edm::ParameterSet displacedMuPt_cfg_;

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

  edm::EDGetTokenT<ME0DigiPreRecoCollection> me0DigiInput_;
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
  bool matchprint_;
  double bendingcutPt_;
  std::vector<string> cscStations_;
  std::vector<std::pair<int,int> > cscStationsCo_;
  std::set<int> stations_to_use_;

  TTree *tree_eff_[NumOfTrees];

  MyTrackEff  etrk_[NumOfTrees];

  int minNHitsChamberCSCSimHit_;
  int minNHitsChamberME0SimHit_;
  int minNHitsChamberCSCWireDigi_;
  int minNHitsChamberCSCStripDigi_;
  int minNHitsChamberME0Digi_;
  int minNHitsChamberME0RecHit_;
  int minNHitsChamberCLCT_;
  int minNHitsChamberALCT_;
  int minNHitsChamberLCT_;
  int minNHitsChamberMPLCT_;
};


TDRAnalyzer::TDRAnalyzer(const edm::ParameterSet& ps)
: cfg_(ps.getParameterSet("simTrackMatching"))
, verbose_(ps.getUntrackedParameter<int>("verbose", 0))
{
  ievent = 0;

  cscStations_ = cfg_.getParameter<std::vector<string> >("cscStations");
  ntupleTrackEff_ = cfg_.getParameter<bool>("ntupleTrackEff");
  //matchprint_ = false;
  matchprint_ =  cfg_.getParameter<bool>("matchprint");
  bendingcutPt_ = cfg_.getUntrackedParameter<double>("bendingcutPt",10);

  displacedMuPt_cfg_ = cfg_.getParameter<edm::ParameterSet>("displacedMuPtAssignment");

  const auto& displacedGenMu = cfg_.getParameter<edm::ParameterSet>("displacedGenMu");
  genParticleInput_ = consumes<reco::GenParticleCollection>(displacedGenMu.getParameter<edm::InputTag>("inputTag"));

  const auto& simVertex = cfg_.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("inputTag"));

  const auto& simTrack = cfg_.getParameter<edm::ParameterSet>("simTrack");
  verboseSimTrack_ = simTrack.getParameter<int>("verbose");
  simTrackInput_ = consumes<edm::SimTrackContainer>(simTrack.getParameter<edm::InputTag>("inputTag"));
  simTrackMinPt_ = simTrack.getParameter<double>("minPt");
  simTrackMinEta_ = simTrack.getParameter<double>("minEta");
  simTrackMaxEta_ = simTrack.getParameter<double>("maxEta");
  simTrackOnlyMuon_ = simTrack.getParameter<bool>("onlyMuon");

  const auto& gemSimHit_ = cfg_.getParameter<edm::ParameterSet>("gemSimHit");
  gemSimHitInput_ = consumes<edm::PSimHitContainer>(gemSimHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& cscSimHit_= cfg_.getParameter<edm::ParameterSet>("cscSimHit");
  cscSimHitInput_ = consumes<edm::PSimHitContainer>(cscSimHit_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberCSCSimHit_ = cscSimHit_.getParameter<int>("minNHitsChamber");

  const auto& me0SimHit_ = cfg_.getParameter<edm::ParameterSet>("me0SimHit");
  me0SimHitInput_ = consumes<edm::PSimHitContainer>(me0SimHit_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberME0SimHit_ = me0SimHit_.getParameter<int>("minNHitsChamber");

  const auto& rpcSimHit_ = cfg_.getParameter<edm::ParameterSet>("rpcSimHit");
  rpcSimHitInput_ = consumes<edm::PSimHitContainer>(rpcSimHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& dtSimHit_ = cfg_.getParameter<edm::ParameterSet>("dtSimHit");
  dtSimHitInput_ = consumes<edm::PSimHitContainer>(dtSimHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemDigi_= cfg_.getParameter<edm::ParameterSet>("gemStripDigi");
  gemDigiInput_ = consumes<GEMDigiCollection>(gemDigi_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemPad_= cfg_.getParameter<edm::ParameterSet>("gemPadDigi");
  gemPadDigiInput_ = consumes<GEMPadDigiCollection>(gemPad_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemCoPad_= cfg_.getParameter<edm::ParameterSet>("gemCoPadDigi");
  gemCoPadDigiInput_ = consumes<GEMCoPadDigiCollection>(gemCoPad_.getParameter<edm::InputTag>("inputTag"));

  const auto& gemRecHit_= cfg_.getParameter<edm::ParameterSet>("gemRecHit");
  gemRecHitInput_ = consumes<GEMRecHitCollection>(gemRecHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& me0Digi_= cfg_.getParameter<edm::ParameterSet>("me0DigiPreReco");
  me0DigiInput_ = consumes<ME0DigiPreRecoCollection>(me0Digi_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberME0Digi_ =  me0Digi_.getParameter<int>("minNHitsChamber");

  const auto& me0RecHit_ = cfg_.getParameter<edm::ParameterSet>("me0RecHit");
  me0RecHitInput_ = consumes<ME0RecHitCollection>(me0RecHit_.getParameter<edm::InputTag>("inputTag"));
  minNHitsChamberME0RecHit_ =  me0RecHit_.getParameter<int>("minNHitsChamber");

  const auto& me0Segment_ = cfg_.getParameter<edm::ParameterSet>("me0Segment");
  me0SegmentInput_ = consumes<ME0SegmentCollection>(me0Segment_.getParameter<edm::InputTag>("inputTag"));

  const auto& cscComparatorDigi = cfg_.getParameter<edm::ParameterSet>("cscStripDigi");
  minNHitsChamberCSCStripDigi_ = cscComparatorDigi.getParameter<int>("minNHitsChamber");
  cscComparatorDigiInput_ = consumes<CSCComparatorDigiCollection>(cscComparatorDigi.getParameter<edm::InputTag>("inputTag"));

  const auto& cscWireDigi = cfg_.getParameter<edm::ParameterSet>("cscWireDigi");
  minNHitsChamberCSCWireDigi_ = cscWireDigi.getParameter<int>("minNHitsChamber");
  cscWireDigiInput_ = consumes<CSCWireDigiCollection>(cscWireDigi.getParameter<edm::InputTag>("inputTag"));

  const auto& cscCLCT = cfg_.getParameter<edm::ParameterSet>("cscCLCT");
  minNHitsChamberCLCT_ = cscCLCT.getParameter<int>("minNHitsChamber");
  clctInputs_ = consumes<CSCCLCTDigiCollection>(cscCLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscALCT = cfg_.getParameter<edm::ParameterSet>("cscALCT");
  minNHitsChamberALCT_ = cscALCT.getParameter<int>("minNHitsChamber");
  alctInputs_ = consumes<CSCALCTDigiCollection>(cscALCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscLCT = cfg_.getParameter<edm::ParameterSet>("cscLCT");
  minNHitsChamberLCT_ = cscLCT.getParameter<int>("minNHitsChamber");
  lctInputs_ = consumes<CSCCorrelatedLCTDigiCollection>(cscLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscMPLCT = cfg_.getParameter<edm::ParameterSet>("cscMPLCT");
  minNHitsChamberMPLCT_ = cscMPLCT.getParameter<int>("minNHitsChamber");
  mplctInputs_ = consumes<CSCCorrelatedLCTDigiCollection>(cscMPLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& cscRecHit2D = cfg_.getParameter<edm::ParameterSet>("cscRecHit");
  cscRecHit2DInput_ = consumes<CSCRecHit2DCollection>(cscRecHit2D.getParameter<edm::InputTag>("inputTag"));

  const auto& cscSegment2D = cfg_.getParameter<edm::ParameterSet>("cscSegment");
  cscSegmentInput_ = consumes<CSCSegmentCollection>(cscSegment2D.getParameter<edm::InputTag>("inputTag"));

  const auto& dtDigi_= cfg_.getParameter<edm::ParameterSet>("dtDigi");
  dtDigiInput_ = consumes<DTDigiCollection>(dtDigi_.getParameter<edm::InputTag>("inputTag"));

  const auto& dtStub_= cfg_.getParameter<edm::ParameterSet>("dtLocalTrigger");
  dtStubInput_ = consumes<DTLocalTriggerCollection>(dtStub_.getParameter<edm::InputTag>("inputTag"));

  const auto& dtRecHit1DPair = cfg_.getParameter<edm::ParameterSet>("dtRecHit");
  dtRecHit1DPairInput_ = consumes<DTRecHitCollection>(dtRecHit1DPair.getParameter<edm::InputTag>("inputTag"));

  const auto& dtSegment2D = cfg_.getParameter<edm::ParameterSet>("dtRecSegment2D");
  dtRecSegment2DInput_ = consumes<DTRecSegment2DCollection>(dtSegment2D.getParameter<edm::InputTag>("inputTag"));

  const auto& dtSegment4D = cfg_.getParameter<edm::ParameterSet>("dtRecSegment4D");
  dtRecSegment4DInput_ = consumes<DTRecSegment4DCollection>(dtSegment4D.getParameter<edm::InputTag>("inputTag"));

  const auto& rpcDigi_= cfg_.getParameter<edm::ParameterSet>("rpcStripDigi");
  rpcDigiInput_ = consumes<RPCDigiCollection>(rpcDigi_.getParameter<edm::InputTag>("inputTag"));

  const auto& rpcRecHit_= cfg_.getParameter<edm::ParameterSet>("rpcRecHit");
  rpcRecHitInput_ = consumes<RPCRecHitCollection>(rpcRecHit_.getParameter<edm::InputTag>("inputTag"));

  const auto& emtfTrack = cfg_.getParameter<edm::ParameterSet>("upgradeEmtfTrack");
  emtfTrackInputLabel_ = consumes<l1t::EMTFTrackCollection>(emtfTrack.getParameter<edm::InputTag>("inputTag"));

  const auto& upgradeemtfCand = cfg_.getParameter<edm::ParameterSet>("upgradeEmtfCand");
  regMuonCandInputLabel_ = consumes< BXVector<l1t::RegionalMuonCand> >(upgradeemtfCand.getParameter<edm::InputTag>("inputTag"));

  const auto& upgradegmt = cfg_.getParameter<edm::ParameterSet>("upgradeGMT");
  gmtInputLabel_ = consumes< BXVector<l1t::Muon> >(upgradegmt.getParameter<edm::InputTag>("inputTag"));

  //const auto& l1Track = cfg_.getParameter<edm::ParameterSet>("l1track");
  //trackInputLabel_ = consumes<L1TTTrackCollectionType>(l1Track.getParameter<edm::InputTag>("inputTag"));
  //verboseL1Track_ = l1Track.getParameter<int>("verbose");

  //const auto& l1TrackMuon = cfg_.getParameter<edm::ParameterSet>("l1tkmuon");
  //trackMuonInputLabel_ = consumes<l1t::L1TkMuonParticleCollection>(l1TrackMuon.getParameter<edm::InputTag>("inputTag"));

  const auto& recoTrackExtra = cfg_.getParameter<edm::ParameterSet>("recoTrackExtra");
  recoTrackExtraInputLabel_ = consumes<reco::TrackExtraCollection>(recoTrackExtra.getParameter<edm::InputTag>("inputTag"));

  const auto& recoTrack = cfg_.getParameter<edm::ParameterSet>("recoTrack");
  recoTrackInputLabel_ = consumes<reco::TrackCollection>(recoTrack.getParameter<edm::InputTag>("inputTag"));

  const auto& recoChargedCandidate = cfg_.getParameter<edm::ParameterSet>("recoChargedCandidate");
  recoChargedCandidateInputLabel_ = consumes<reco::RecoChargedCandidateCollection>(recoChargedCandidate.getParameter<edm::InputTag>("inputTag"));


  if (ntupleTrackEff_)
  {
    vector<int> stations = cfg_.getParameter<vector<int> >("cscStationsToUse");
    copy(stations.begin(), stations.end(), inserter(stations_to_use_, stations_to_use_.end()) );

    for(const auto& s: stations_to_use_)
    {
      stringstream ss;
      ss << "trk_eff_"<< cscStations_[s];
      std::cout <<"station to use "<< s << " " << cscStations_[s]  << std::endl;
      tree_eff_[s] = etrk_[s].book(tree_eff_[s], ss.str());
    }
  }

  std::cout << "Done initializing trees" << std::endl;

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


int TDRAnalyzer::detIdToMEStation(int st, int ri)
{
  const auto& p(std::make_pair(st, ri));
  return std::find(cscStationsCo_.begin(), cscStationsCo_.end(), p) - cscStationsCo_.begin();
}


void TDRAnalyzer::beginRun(const edm::Run &iRun, const edm::EventSetup &iSetup)
{
}


bool TDRAnalyzer::isSimTrackGood(const SimTrack &t)
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


void TDRAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  ievent ++;
  edm::Handle<edm::SimTrackContainer> sim_tracks;
  ev.getByToken(simTrackInput_, sim_tracks);
  const edm::SimTrackContainer & sim_track = *sim_tracks.product();

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  ev.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer & sim_vert = *sim_vertices.product();

  // first select the simtracks
  edm::SimTrackContainer sim_track_selected;
  for (const auto& t: sim_track)
  {
    // do not select bad simtracks
    if (!isSimTrackGood(t)) continue;

    sim_track_selected.push_back(t);
  }

  if (verboseSimTrack_){
    std::cout << "Number of total SimTrack:    " << sim_track.size() << std::endl;
    std::cout << "Number of selected SimTrack: " << sim_track_selected.size() << std::endl;
  }

  // now run over the selected simtracks
  for (unsigned iTrack = 0; iTrack < sim_track_selected.size(); iTrack++) {

    const auto& t = sim_track_selected.at(iTrack);

    if (verboseSimTrack_){
      std::cout << "Processing SimTrack " << iTrack
                << ": pt = " << t.momentum().pt()
                << " GeV, eta = " << t.momentum().eta()
                << ", phi = " << t.momentum().phi()
                << ", Q = " << t.charge() << std::endl;
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

    if (ntupleTrackEff_) analyzeTrackEff(match, iTrack);
  }
}



void TDRAnalyzer::analyzeTrackEff(SimTrackMatchManager& match, int trk_no)
{
  const SimHitMatcher& match_sh = match.simhits();
  const GEMDigiMatcher& match_gd = match.gemDigis();
  const CSCDigiMatcher& match_cd = match.cscDigis();
  const CSCStubMatcher& match_lct = match.cscStubs();
  //const ME0DigiMatcher& match_me0digi = match.me0Digis();
  //const ME0RecHitMatcher& match_me0rh = match.me0RecHits();
  const SimTrack &t = match_sh.trk();

  float randtest1 = CLHEP::RandFlat::shoot(0.0,1.0) ;
  float randtest2 = CLHEP::RandFlat::shoot(0.0,1.0) ;
  if (verbose_) std::cout <<"TDRAnalyzer step1 "<< std::endl;
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

  int chargesign = (t.charge()>0? 1:0);
  float pt = t.momentum().pt();
  // SimHits
  GlobalPoint gp_sh_odd[NumOfTrees];
  GlobalPoint gp_sh_even[NumOfTrees];
  GlobalVector gv_sh_odd[NumOfTrees];
  GlobalVector gv_sh_even[NumOfTrees];
  const auto& csc_simhits(match_sh.chamberIdsCSC(0));
  for(const auto& d: csc_simhits)
    {
      CSCDetId id(d);

      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      int nlayers(match_sh.nLayersWithHitsInSuperChamber(d));

      // case ME11
      if (id.station()==1 and (id.ring()==4 or id.ring()==1)){
        // get the detId of the pairing subchamber
        int other_ring(id.ring()==4 ? 1 : 4);
        CSCDetId co_id(id.endcap(), id.station(), other_ring, id.chamber());
        // check if co_id occurs in the list
        const auto& rawId(co_id.rawId());
        if (csc_simhits.find(rawId) != csc_simhits.end()) {
          nlayers += match_sh.nLayersWithHitsInSuperChamber(rawId);
        }
      }
      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].chamber_sh_odd = id.chamber();
      else etrk_[st].chamber_sh_even = id.chamber();

      if (odd) etrk_[st].nlayers_csc_sh_odd = nlayers;
      else etrk_[st].nlayers_csc_sh_even = nlayers;

      const GlobalPoint& keygp(match_sh.simHitPositionKeyLayer(id));

      if (odd) gp_sh_odd[st] = keygp;
      else gp_sh_even[st] = keygp;

      if (odd) etrk_[st].eta_cscsh_odd = keygp.eta();
      else     etrk_[st].eta_cscsh_even = keygp.eta();

      if (odd) etrk_[st].phi_cscsh_odd = keygp.phi();
      else     etrk_[st].phi_cscsh_even = keygp.phi();

      if (odd) etrk_[st].perp_cscsh_odd = keygp.perp();
      else     etrk_[st].perp_cscsh_even = keygp.perp();

      if (odd) etrk_[st].has_csc_sh |= 1;
      else etrk_[st].has_csc_sh |= 2;

    }

  if (verbose_) std::cout <<"TDRAnalyzer step2 "<< std::endl;
  // CSC strip digis
  for(const auto& d: match_cd.chamberIdsStrip(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      int nlayers(match_cd.nLayersWithStripInChamber(d));
      // std::cout <<"CSC strip digi, CSCid "<< id <<" nlayer "<< nlayers << std::endl;

      if (nlayers < minNHitsChamberCSCStripDigi_) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_csc_strips |= 1;
      else etrk_[st].has_csc_strips |= 2;

      if (odd) etrk_[st].nlayers_st_dg_odd = nlayers;
      else etrk_[st].nlayers_st_dg_even = nlayers;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_csc_strips |= 1;
        else etrk_[1].has_csc_strips |= 2;

        if (odd) etrk_[1].nlayers_st_dg_odd = nlayers;
        else etrk_[1].nlayers_st_dg_even = nlayers;
      }
    }

  // CSC wire digis
  for(const auto& d: match_cd.chamberIdsWire(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      int nlayers(match_cd.nLayersWithWireInChamber(d));

      // std::cout <<"CSC wire digi, CSCid "<< id <<" nlayer "<< nlayers << std::endl;
      if (nlayers < minNHitsChamberCSCWireDigi_) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_csc_wires |= 1;
      else etrk_[st].has_csc_wires |= 2;

      if (odd) etrk_[st].nlayers_wg_dg_odd = nlayers;
      else etrk_[st].nlayers_wg_dg_even = nlayers;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_csc_wires |= 1;
        else etrk_[1].has_csc_wires |= 2;

        if (odd) etrk_[1].nlayers_wg_dg_odd = nlayers;
        else etrk_[1].nlayers_wg_dg_even = nlayers;
      }
    }

  // CSC CLCTs
  for(const auto& d: match_lct.chamberIdsCLCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      const auto& clct = match_lct.clctInChamber(d);

      //std::cout <<"CSC CLCT, CSCid "<< id <<" clct "<< clct << std::endl;
      if (odd) etrk_[st].chamber_dg_odd = id.chamber();
      else etrk_[st].chamber_dg_even = id.chamber();
      if (odd) etrk_[st].halfstrip_odd = digi_channel(clct);
      else etrk_[st].halfstrip_even = digi_channel(clct);

      if (odd) etrk_[st].quality_clct_odd = digi_quality(clct);
      else etrk_[st].quality_clct_even = digi_quality(clct);

      if (odd) etrk_[st].bx_clct_odd = digi_bx(clct);
      else etrk_[st].bx_clct_even = digi_bx(clct);

      if (odd) etrk_[st].has_clct |= 1;
      else etrk_[st].has_clct |= 2;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].halfstrip_odd = digi_channel(clct);
        else etrk_[1].halfstrip_even = digi_channel(clct);

        if (odd) etrk_[1].quality_clct_odd = digi_quality(clct);
        else etrk_[1].quality_clct_even = digi_quality(clct);

        if (odd) etrk_[1].bx_clct_odd = digi_bx(clct);
        else etrk_[1].bx_clct_even = digi_bx(clct);

        if (odd) etrk_[1].has_clct |= 1;
        else etrk_[1].has_clct |= 2;
      }
    }

  // CSC ALCTs
  for(const auto& d: match_lct.chamberIdsALCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      const auto& alct = match_lct.alctInChamber(d);

      //std::cout <<"CSC ALCT, CSCid "<< id <<" alct "<< alct << std::endl;
      if (odd) etrk_[st].wiregroup_odd = digi_channel(alct);
      else etrk_[st].wiregroup_even = digi_channel(alct);

      if (odd) etrk_[st].quality_alct_odd = digi_quality(alct);
      else etrk_[st].quality_alct_even = digi_quality(alct);

      if (odd) etrk_[st].bx_alct_odd = digi_bx(alct);
      else etrk_[st].bx_alct_even = digi_bx(alct);

      if (odd) etrk_[st].has_alct |= 1;
      else etrk_[st].has_alct |= 2;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].wiregroup_odd = digi_channel(alct);
        else etrk_[1].wiregroup_even = digi_channel(alct);

        if (odd) etrk_[1].quality_alct_odd = digi_quality(alct);
        else etrk_[1].quality_alct_even = digi_quality(alct);

        if (odd) etrk_[1].bx_alct_odd = digi_bx(alct);
        else etrk_[1].bx_alct_even = digi_bx(alct);

        if (odd) etrk_[1].has_alct |= 1;
        else etrk_[1].has_alct |= 2;
      }
    }

  if (verbose_) std::cout <<"TDRAnalyzer step3 "<< std::endl;
  // holders for track's LCTs
  Digi lct_odd[NumOfTrees];
  Digi lct_even[NumOfTrees];
  GlobalPoint gp_lct_odd[NumOfTrees];
  GlobalPoint gp_lct_even[NumOfTrees];
  GlobalPoint gp_fit_odd[NumOfTrees];
  GlobalPoint gp_fit_even[NumOfTrees];
  for (const auto& s: stations_to_use_)
    {
      lct_odd[s] = make_digi();
      lct_even[s] = make_digi();
    }


  // LCT stubs
  for(const auto& d: match_lct.chamberIdsLCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      if (odd) etrk_[st].has_lct |= 1;
      else etrk_[st].has_lct |= 2;

      // case ME11
      if (st==2 or st==3){
        if (odd) etrk_[1].has_lct |= 1;
        else etrk_[1].has_lct |= 2;
      }

      const auto& lct = match_lct.lctInChamber(d);
      const int bend(LCT_BEND_PATTERN[digi_pattern(lct)]);
      const auto& gp = match_lct.digiPosition(lct);

      if (match_lct.cscLctsInChamber(d).size()>0) {
        etrk_[st].lct_type = match_lct.cscLctsInChamber(d)[0].getType();
        // std::cout << "Printing best LCT " << match_lct.cscLctsInChamber(d)[0] << " " << etrk_[st].lct_type << " " << match_lct.cscLctsInChamber(d)[0].getType() << std::endl;
      }

      //std::cout <<"CSC LCT, CSCid "<< id <<" lct "<< lct <<" gp eta "<< gp.eta()<<" phi "<< gp.phi() <<" perp "<< gp.perp()<<std::endl;
      if (csc_simhits.find(d) == csc_simhits.end())
        std::cout <<"failed to find simhits in CSCid "<< id <<" but find LCT" << lct << std::endl;
      if (odd)
        {
          lct_odd[st] = lct;
          gp_lct_odd[st] = gp;
          etrk_[st].bend_lct_odd = bend;
          etrk_[st].phi_lct_odd = gp.phi();
          etrk_[st].eta_lct_odd = gp.eta();
          etrk_[st].perp_lct_odd = gp.perp();
          if (fabs(etrk_[st].perp_lct_odd-etrk_[st].perp_cscsh_odd)>5.0 and etrk_[st].perp_cscsh_odd>10.0)
            std::cout <<"CSCid "<< id <<" perp_cscsh_odd "<< etrk_[st].perp_cscsh_odd<<" perp_lct_odd "<< etrk_[st].perp_lct_odd<<" csc_phi "<< etrk_[st].phi_cscsh_odd<<" phi_lct_odd "<< etrk_[st].phi_lct_odd << std::endl;

          etrk_[st].dphi_lct_odd = digi_dphi(lct);
          etrk_[st].bx_lct_odd = digi_bx(lct);
          etrk_[st].hs_lct_odd = digi_channel(lct);
          etrk_[st].wg_lct_odd = digi_wg(lct);
          etrk_[st].chamber_lct_odd = id.chamber() ;
          etrk_[st].quality_odd = digi_quality(lct);
          etrk_[st].passdphi_odd = match_lct.passDPhicut(id, chargesign, digi_dphi(lct), pt);
        }
      else
        {
          lct_even[st] = lct;
          gp_lct_even[st] = gp;
          etrk_[st].bend_lct_even = bend;
          etrk_[st].phi_lct_even = gp.phi();
          etrk_[st].eta_lct_even = gp.eta();
          etrk_[st].perp_lct_even = gp.perp();
          if (fabs(etrk_[st].perp_lct_even-etrk_[st].perp_cscsh_even)>5.0 and etrk_[st].perp_cscsh_even>10.0)
            std::cout <<"CSCid "<< id <<" perp_cscsh_even "<< etrk_[st].perp_cscsh_even <<" perp_lct_even "<< etrk_[st].perp_lct_even <<" csc_phi "<< etrk_[st].phi_cscsh_even <<" phi_lct_even "<< etrk_[st].phi_lct_even << std::endl;
          etrk_[st].dphi_lct_even = digi_dphi(lct);
          etrk_[st].bx_lct_even = digi_bx(lct);
          etrk_[st].hs_lct_even = digi_channel(lct);
          etrk_[st].wg_lct_even = digi_wg(lct);
          etrk_[st].chamber_lct_even = id.chamber();
          etrk_[st].quality_even = digi_quality(lct);
          etrk_[st].passdphi_even = match_lct.passDPhicut(id, chargesign, digi_dphi(lct), pt);
        }
      }


 if (verbose_) std::cout <<"TDRAnalyzer step10 "<< std::endl;
 for (const auto& s: stations_to_use_)
   {
     tree_eff_[s]->Fill();
   }
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TDRAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(TDRAnalyzer);
