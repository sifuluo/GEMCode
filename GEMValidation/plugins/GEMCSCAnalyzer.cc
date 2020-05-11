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

#include "GEMCode/GEMValidation/interface/Helpers.h"
#include "GEMCode/GEMValidation/interface/SimTrackMatchManager.h"
#include "GEMCode/GEMValidation/interface/MyTrack.h"

#include <iomanip>
#include <sstream>
#include <memory>
#include <math.h>
#include <bitset>

using namespace std;

static const int NumOfTrees = 13;

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

  edm::EDGetTokenT<reco::GenParticleCollection> genParticleInput_;
  edm::EDGetTokenT<edm::SimVertexContainer> simVertexInput_;
  edm::EDGetTokenT<edm::SimTrackContainer> simTrackInput_;

  int verboseSimTrack_;
  int verboseL1Track_;
  double simTrackMinPt_;
  double simTrackMinEta_;
  double simTrackMaxEta_;
  double simTrackOnlyMuon_;
  int verbose_;
  std::vector<string> cscStations_;
  std::vector<std::pair<int, int> > cscStationsCo_;
  std::set<int> stations_to_use_;

  TTree* tree_eff_[NumOfTrees];
  MyTrack etrk_[NumOfTrees];

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
  std::unique_ptr<SimTrackMatchManager> matcher_;
};

GEMCSCAnalyzer::GEMCSCAnalyzer(const edm::ParameterSet& ps)
    : cfg_(ps.getParameterSet("simTrackMatching")), verbose_(ps.getUntrackedParameter<int>("verbose", 0)) {
  cscStations_ = cfg_.getParameter<std::vector<string> >("cscStations");

  const auto& simVertex = cfg_.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("validInputTags"));

  const auto& simTrack = cfg_.getParameter<edm::ParameterSet>("simTrack");
  verboseSimTrack_ = simTrack.getParameter<int>("verbose");
  simTrackInput_ = consumes<edm::SimTrackContainer>(simTrack.getParameter<edm::InputTag>("validInputTags"));
  simTrackMinPt_ = simTrack.getParameter<double>("minPt");
  simTrackMinEta_ = simTrack.getParameter<double>("minEta");
  simTrackMaxEta_ = simTrack.getParameter<double>("maxEta");
  simTrackOnlyMuon_ = simTrack.getParameter<bool>("onlyMuon");

  const auto& cscSimHit_= cfg_.getParameter<edm::ParameterSet>("cscSimHit");
  const auto& cscComparatorDigi = cfg_.getParameter<edm::ParameterSet>("cscStripDigi");
  const auto& cscWireDigi = cfg_.getParameter<edm::ParameterSet>("cscWireDigi");
  const auto& cscCLCT = cfg_.getParameter<edm::ParameterSet>("cscCLCT");
  const auto& cscALCT = cfg_.getParameter<edm::ParameterSet>("cscALCT");
  const auto& cscLCT = cfg_.getParameter<edm::ParameterSet>("cscLCT");

  minNHitsChamberCSCSimHit_ = cscSimHit_.getParameter<int>("minNHitsChamber");
  minNHitsChamberCSCStripDigi_ = cscComparatorDigi.getParameter<int>("minNHitsChamber");
  minNHitsChamberCSCWireDigi_ = cscWireDigi.getParameter<int>("minNHitsChamber");
  minNHitsChamberCLCT_ = cscCLCT.getParameter<int>("minNHitsChamber");
  minNHitsChamberALCT_ = cscALCT.getParameter<int>("minNHitsChamber");
  minNHitsChamberLCT_ = cscLCT.getParameter<int>("minNHitsChamber");

  vector<int> stations = cfg_.getParameter<vector<int> >("cscStationsToUse");
  copy(stations.begin(), stations.end(), inserter(stations_to_use_, stations_to_use_.end()));

  for (const auto& s : stations_to_use_) {
    stringstream ss;
    ss << "trk_eff_" << cscStations_[s];
    std::cout << "station to use " << cscStations_[s] << std::endl;
    tree_eff_[s] = etrk_[s].book(tree_eff_[s], ss.str());
  }

  cscStationsCo_.push_back(std::make_pair(-99, -99));
  cscStationsCo_.push_back(std::make_pair(1, -99));
  cscStationsCo_.push_back(std::make_pair(1, 4));
  cscStationsCo_.push_back(std::make_pair(1, 1));
  cscStationsCo_.push_back(std::make_pair(1, 2));
  cscStationsCo_.push_back(std::make_pair(1, 3));
  cscStationsCo_.push_back(std::make_pair(2, 1));
  cscStationsCo_.push_back(std::make_pair(2, 2));
  cscStationsCo_.push_back(std::make_pair(3, 1));
  cscStationsCo_.push_back(std::make_pair(3, 2));
  cscStationsCo_.push_back(std::make_pair(4, 1));
  cscStationsCo_.push_back(std::make_pair(4, 2));

  matcher_.reset(new SimTrackMatchManager(ps, consumesCollector()));
}

int GEMCSCAnalyzer::detIdToMEStation(int st, int ri) {
  const auto& p(std::make_pair(st, ri));
  return std::find(cscStationsCo_.begin(), cscStationsCo_.end(), p) - cscStationsCo_.begin();
}

void GEMCSCAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {}

bool GEMCSCAnalyzer::isSimTrackGood(const SimTrack& t) {
  // SimTrack selection
  if (t.noVertex())
    return false;
  if (t.noGenpart())
    return false;
  // only muons
  if (std::abs(t.type()) != 13 and simTrackOnlyMuon_)
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

  if (verboseSimTrack_) {
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
    if (verboseSimTrack_) {
      std::cout << "Processing selected SimTrack " << trk_no + 1 << std::endl;
      std::cout << "pt(GeV/c) = " << t.momentum().pt() << ", eta = " << t.momentum().eta()
                << ", phi = " << t.momentum().phi() << ", Q = " << t.charge() << ", PDGiD =  " << t.type() << std::endl;
    }
    analyze(t, sim_vert[t.vertIndex()]);
  }
}

void GEMCSCAnalyzer::analyze(const SimTrack& t, const SimVertex& v) {
  // do the match for each simtrack
  matcher_->match(t, v);

  // get the objects
  const GEMSimHitMatcher& match_gem_sh = *(matcher_->gemsimhits());
  const CSCSimHitMatcher& match_csc_sh = *(matcher_->cscsimhits());
  const GEMDigiMatcher& match_gd = *(matcher_->gemDigis());
  const CSCDigiMatcher& match_cd = *(matcher_->cscDigis());
  const CSCStubMatcher& match_lct = *(matcher_->cscStubs());

  // tracks
  for (const auto& s : stations_to_use_) {
    etrk_[s].init();
    etrk_[s].pt = t.momentum().pt();
    etrk_[s].pz = t.momentum().pz();
    etrk_[s].phi = t.momentum().phi();
    etrk_[s].eta = t.momentum().eta();
    // etrk_[s].dxy = match.simhits().dxy();
    etrk_[s].charge = t.charge();
    etrk_[s].endcap = (etrk_[s].eta > 0.) ? 1 : -1;
    etrk_[s].pdgid = t.type();
  }

  // CSC SimHit
  const auto& csc_simhits(match_csc_sh.chamberIds(0));
  for(const auto& d: match_csc_sh.chamberIds(0)) {

    CSCDetId id(d);
    const int st(detIdToMEStation(id.station(),id.ring()));
    if (stations_to_use_.count(st) == 0) continue;
    int nlayers(match_csc_sh.nLayersWithHitsInChamber(d));
    // case ME11
    if (id.station()==1 and (id.ring()==4 or id.ring()==1)){
      // get the detId of the pairing subchamber
      int other_ring(id.ring()==4 ? 1 : 4);
      CSCDetId co_id(id.endcap(), id.station(), other_ring, id.chamber());
      // check if co_id occurs in the list
      // add the hit layers

      const auto& rawId(co_id.rawId());
      if (csc_simhits.find(rawId) != csc_simhits.end()) {
        nlayers = nlayers+match_csc_sh.nLayersWithHitsInChamber(rawId);
      }
    }

    if (nlayers < minNHitsChamberCSCSimHit_) continue;

    match_csc_sh.LocalBendingInChamber(d);

    const bool odd(id.chamber()%2==1);
    const auto& simhits = match_csc_sh.hitsInDetId(id);
    const GlobalPoint& keygp(match_csc_sh.simHitsMeanPosition(simhits));

    if (odd) {
      etrk_[st].chamber_sh_odd = id.chamber();
      etrk_[st].nlayers_csc_sh_odd = nlayers;
      etrk_[st].has_csc_sh |= 1;
      etrk_[st].eta_cscsh_odd = keygp.eta();
      etrk_[st].phi_cscsh_odd = keygp.phi();
      etrk_[st].perp_cscsh_odd = keygp.perp();
    }
    else {
      etrk_[st].chamber_sh_even = id.chamber();
      etrk_[st].nlayers_csc_sh_even = nlayers;
      etrk_[st].has_csc_sh |= 2;
      etrk_[st].eta_cscsh_even = keygp.eta();
      etrk_[st].phi_cscsh_even = keygp.phi();
      etrk_[st].perp_cscsh_even = keygp.perp();
    }

    // case ME11
    if (st==2 or st==3){
      if (odd) {
        etrk_[1].chamber_sh_odd = id.chamber();
        etrk_[1].nlayers_csc_sh_odd = nlayers;
        etrk_[1].has_csc_sh |= 1;
        etrk_[1].eta_cscsh_odd = keygp.eta();
        etrk_[1].phi_cscsh_odd = keygp.phi();
        etrk_[1].perp_cscsh_odd = keygp.perp();
      }
      else {
        etrk_[1].chamber_sh_even = id.chamber();
        etrk_[1].nlayers_csc_sh_even = nlayers;
        etrk_[1].has_csc_sh |= 2;
        etrk_[1].eta_cscsh_even = keygp.eta();
        etrk_[1].phi_cscsh_even = keygp.phi();
        etrk_[1].perp_cscsh_even = keygp.perp();
      }
    }
  }

  // CSC strip digis
  for(const auto& d: match_cd.chamberIdsStrip(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const int nlayers(match_cd.nLayersWithStripInChamber(d));
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

      const int nlayers(match_cd.nLayersWithWireInChamber(d));
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
      const auto& clct = match_lct.bestClctInChamber(d);

      if (odd) {
        etrk_[st].has_clct |= 1;
        etrk_[st].chamber_dg_odd = id.chamber();
        etrk_[st].halfstrip_odd = clct.getKeyStrip();
        etrk_[st].quality_clct_odd = clct.getQuality();
        etrk_[st].bx_clct_odd = clct.getBX();
      }
      else {
        etrk_[st].has_clct |= 2;
        etrk_[st].chamber_dg_even = id.chamber();
        etrk_[st].halfstrip_even = clct.getKeyStrip();
        etrk_[st].quality_clct_even = clct.getQuality();
        etrk_[st].bx_clct_even = clct.getBX();
      }

      // case ME11
      if (st==2 or st==3){
        if (odd) {
          etrk_[1].has_clct |= 1;
          etrk_[1].chamber_dg_odd = id.chamber();
          etrk_[1].halfstrip_odd = clct.getKeyStrip();
          etrk_[1].quality_clct_odd = clct.getQuality();
          etrk_[1].bx_clct_odd = clct.getBX();
        }
        else {
          etrk_[1].has_clct |= 2;
          etrk_[1].chamber_dg_even = id.chamber();
          etrk_[1].halfstrip_even = clct.getKeyStrip();
          etrk_[1].quality_clct_even = clct.getQuality();
          etrk_[1].bx_clct_even = clct.getBX();
        }
      }
    }

  // CSC ALCTs
  for(const auto& d: match_lct.chamberIdsALCT(0))
    {
      CSCDetId id(d);
      const int st(detIdToMEStation(id.station(),id.ring()));
      if (stations_to_use_.count(st) == 0) continue;

      const bool odd(id.chamber()%2==1);
      const auto& alct = match_lct.bestAlctInChamber(d);

      if (odd) {
        etrk_[st].has_alct |= 1;
        etrk_[st].chamber_dg_odd = id.chamber();
        etrk_[st].wiregroup_odd = alct.getKeyWG();
        etrk_[st].quality_alct_odd = alct.getQuality();
        etrk_[st].bx_alct_odd = alct.getBX();
      }
      else {
        etrk_[st].has_alct |= 2;
        etrk_[st].chamber_dg_even = id.chamber();
        etrk_[st].wiregroup_even = alct.getKeyWG();
        etrk_[st].quality_alct_even = alct.getQuality();
        etrk_[st].bx_alct_even = alct.getBX();
      }

      // case ME11
      if (st==2 or st==3){
        if (odd) {
          etrk_[1].has_alct |= 1;
          etrk_[1].chamber_dg_odd = id.chamber();
          etrk_[1].wiregroup_odd = alct.getKeyWG();
          etrk_[1].quality_alct_odd = alct.getQuality();
          etrk_[1].bx_alct_odd = alct.getBX();
        }
        else {
          etrk_[1].has_alct |= 2;
          etrk_[1].chamber_dg_even = id.chamber();
          etrk_[1].wiregroup_even = alct.getKeyWG();
          etrk_[1].quality_alct_even = alct.getQuality();
          etrk_[1].bx_alct_even = alct.getBX();
        }
      }



      // CSC LCTs
      for(const auto& d: match_lct.chamberIdsLCT(0))
        {
          CSCDetId id(d);
          const int st(detIdToMEStation(id.station(),id.ring()));
          if (stations_to_use_.count(st) == 0) continue;

          const auto& lct = match_lct.bestLctInChamber(d);
          const GlobalPoint& gp = match_lct.getGlobalPosition(d, lct);

          const bool odd(id.chamber()%2==1);
          if (odd) {
            etrk_[st].has_lct |= 1;
            etrk_[st].bend_lct_odd = lct.getPattern();
            etrk_[st].phi_lct_odd = gp.phi();
            etrk_[st].eta_lct_odd = gp.eta();
            etrk_[st].perp_lct_odd = gp.perp();
            etrk_[st].bx_lct_odd = lct.getBX();
            etrk_[st].hs_lct_odd = lct.getStrip();
            etrk_[st].wg_lct_odd = lct.getKeyWG();
            etrk_[st].quality_odd = lct.getQuality();
          }
          else {
            etrk_[st].has_lct |= 2;
            etrk_[st].bend_lct_even = lct.getPattern();
            etrk_[st].phi_lct_even = gp.phi();
            etrk_[st].eta_lct_even = gp.eta();
            etrk_[st].perp_lct_even = gp.perp();
            etrk_[st].bx_lct_even = lct.getBX();
            etrk_[st].hs_lct_even = lct.getStrip();
            etrk_[st].wg_lct_even = lct.getKeyWG();
            etrk_[st].quality_even = lct.getQuality();
          }
          // case ME11
          if (st==2 or st==3){
            if (odd) {
              etrk_[1].has_lct |= 1;
              etrk_[1].bend_lct_odd = lct.getPattern();
              etrk_[1].phi_lct_odd = gp.phi();
              etrk_[1].eta_lct_odd = gp.eta();
              etrk_[1].perp_lct_odd = gp.perp();
              etrk_[1].bx_lct_odd = lct.getBX();
              etrk_[1].hs_lct_odd = lct.getStrip();
              etrk_[1].wg_lct_odd = lct.getKeyWG();
              etrk_[1].quality_odd = lct.getQuality();
            }
            else {
              etrk_[1].has_lct |= 2;
              etrk_[1].bend_lct_even = lct.getPattern();
              etrk_[1].phi_lct_even = gp.phi();
              etrk_[1].eta_lct_even = gp.eta();
              etrk_[1].perp_lct_even = gp.perp();
              etrk_[1].bx_lct_even = lct.getBX();
              etrk_[1].hs_lct_even = lct.getStrip();
              etrk_[1].wg_lct_even = lct.getKeyWG();
              etrk_[1].quality_even = lct.getQuality();
            }
          }
        }
    }

  /*

    if (verbose_) std::cout <<"GEMCSCAnalyzer step4 "<< std::endl;
    //for GEMs in station1, it will be also filled in ME11
    // GEM simhits in superchamber
    GlobalPoint gp_gemsh_odd[12];
    GlobalPoint gp_gemsh_even[12];
    for(const auto& d: match_sh.superChamberIdsGEM())
    {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (match_sh.hitsInSuperChamber(d).size() > 0)
    {
    if (odd) etrk_[st].has_gem_sh |= 1;
    else     etrk_[st].has_gem_sh |= 2;

    for (int layer=1; layer<3; layer++){
    GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
    const GlobalPoint& keygp = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
    const GlobalVector& keygv = match_sh.simHitsMeanMomentum(match_sh.hitsInChamber(id_tmp.rawId()));
    float centralperp_gemsh = match_sh.simHitsGEMCentralPosition(match_sh.hitsInChamber(id_tmp.rawId()));match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
    if(match_sh.hitsInChamber(id_tmp).size()==0) continue;
    if (odd) gp_gemsh_odd[st] = keygp;
    else gp_gemsh_even[st] = keygp;
    if (odd) etrk_[st].eta_gemsh_odd = keygp.eta();
    else     etrk_[st].eta_gemsh_even = keygp.eta();
    if (odd) etrk_[st].phi_gemsh_odd = keygp.phi();
    else     etrk_[st].phi_gemsh_even = keygp.phi();
    if (odd) etrk_[st].ptphi_gemsh_odd = keygv.phi();
    else     etrk_[st].ptphi_gemsh_even = keygv.phi();
    if (odd) etrk_[st].perp_gemsh_odd = keygp.perp();
    else     etrk_[st].perp_gemsh_even = keygp.perp();
    if (odd) etrk_[st].centralperp_gemsh_odd = centralperp_gemsh;
    else     etrk_[st].centralperp_gemsh_even = centralperp_gemsh;
    float phi_m = -9;
    int st_csc = (st==3 and (etrk_[st].has_csc_sh&3)==0)? 1:st;
    if (st==2 or st==3){
    if (odd) gp_gemsh_odd[1] = keygp;
    else gp_gemsh_even[1] = keygp;
    if (odd) etrk_[1].eta_gemsh_odd = keygp.eta();
    else     etrk_[1].eta_gemsh_even = keygp.eta();
    if (odd) etrk_[1].phi_gemsh_odd = keygp.phi();
    else     etrk_[1].phi_gemsh_even = keygp.phi();
    if (odd) etrk_[1].ptphi_gemsh_odd = keygv.phi();
    else     etrk_[1].ptphi_gemsh_even = keygv.phi();
    if (odd) etrk_[1].perp_gemsh_odd = keygp.perp();
    else     etrk_[1].perp_gemsh_even = keygp.perp();
    if (odd) etrk_[1].centralperp_gemsh_odd = centralperp_gemsh;
    else     etrk_[1].centralperp_gemsh_even = centralperp_gemsh;
    if (odd and etrk_[1].phi_cscsh_odd>-9) etrk_[1].dphi_sh_odd = deltaPhi(etrk_[1].phi_cscsh_odd,float(keygp.phi()));
    else if (etrk_[1].phi_cscsh_even>-9)     etrk_[1].dphi_sh_even = deltaPhi(etrk_[1].phi_cscsh_even,float(keygp.phi()));
    if (odd) etrk_[1].phiM_gemcsc_odd = phi_m;
    else etrk_[1].phiM_gemcsc_even = phi_m;
    if (odd) etrk_[1].dphipositionpt_gemsh_odd = deltaPhi(float(keygp.phi()),etrk_[1].ptphi_sh_odd);
    else etrk_[1].dphipositionpt_gemsh_even = deltaPhi(float(keygp.phi()),etrk_[1].ptphi_sh_even);
    }
    //std::cout <<"dphi(GEM, CSC) at sim "<<(odd? etrk_[st].dphi_sh_odd:etrk_[st].dphi_sh_even) <<" phi_csc "<< (odd? etrk_[st_csc].phi_cscsh_odd:etrk_[st_csc].phi_cscsh_even) <<" phi_gp "<< keygp.phi()<< std::endl;
    if (id_tmp.layer()==1) break;

    }

    const float mean_strip(match_sh.simHitsMeanStrip(match_sh.hitsInSuperChamber(d)));
    if (odd) etrk_[st].strip_gemsh_odd = mean_strip;
    else     etrk_[st].strip_gemsh_even = mean_strip;
    }

    if (match_sh.nLayersWithHitsInSuperChamber(d) > 1)
    {
    //std::cout <<"GEM detid "<< id <<" has at 2 layer hits "<< std::endl;
    if (odd) etrk_[st].has_gem_sh2 |= 1;
    else     etrk_[st].has_gem_sh2 |= 2;
    }
    const auto& copad_superids (match_sh.superChamberIdsGEMCoincidences());
    if (copad_superids.find(d) != copad_superids.end()){
    //std::cout <<"GEM detid "<< id <<" has copad hits "<< std::endl;
    if (odd) etrk_[st].has_gemcopad_sh |= 1;
    else     etrk_[st].has_gemcopad_sh |= 2;
    }
    //ME11 Case
    if (st==2 or st==3)
    {
    if (odd) etrk_[1].has_gem_sh |= 1;
    else     etrk_[1].has_gem_sh |= 2;

    const float mean_strip(match_sh.simHitsMeanStrip(match_sh.hitsInSuperChamber(d)));
    if (odd) etrk_[1].strip_gemsh_odd = mean_strip;
    else     etrk_[1].strip_gemsh_even = mean_strip;

    if (match_sh.nLayersWithHitsInSuperChamber(d) > 1)
    {
    if (odd) etrk_[1].has_gem_sh2 |= 1;
    else etrk_[1].has_gem_sh2 |= 2;

    }
    if (copad_superids.find(d) != copad_superids.end()){
    if (odd) etrk_[1].has_gemcopad_sh |= 1;
    else     etrk_[1].has_gemcopad_sh |= 2;
    }
    }//end of ME11 case

    }

    if (verbose_) std::cout <<"GEMCSCAnalyzer step5 "<< std::endl;
    // placeholders for best mtching pads
    GlobalPoint best_pad_odd[12];
    GlobalPoint best_pad_even[12];

    // GEM digis and pads in superchambers
    for(const auto& d: match_gd.superChamberIdsDigi())
    {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (match_gd.nLayersWithDigisInSuperChamber(d) > 1)
    {
    if (odd) etrk_[st].has_gem_dg2 |= 1;
    else     etrk_[st].has_gem_dg2 |= 2;
    }

    const auto& digis = match_gd.digisInSuperChamber(d);
    const int median_strip(match_gd.median(digis));
    if (odd && digis.size() > 0)
    {
    etrk_[st].has_gem_dg |= 1;
    etrk_[st].strip_gemdg_odd = median_strip;
    }
    else if (digis.size() > 0)
    {
    etrk_[st].has_gem_dg |= 2;
    etrk_[st].strip_gemdg_even = median_strip;
    }

    if (match_gd.nLayersWithPadsInSuperChamber(d) > 1)
    {
    if (odd) etrk_[st].has_gem_pad2 |= 1;
    else     etrk_[st].has_gem_pad2 |= 2;
    }
    for (int layer=1; layer<3; layer++){
    GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
    const auto& pads = match_gd.padsInChamber(id_tmp.rawId());
    if(pads.size() == 0) continue;

    const GlobalPoint& keygp = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
    const auto& bestgem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, keygp);
    if (odd)
    {
    best_pad_odd[st] = bestgem_dg_and_gp.second;
    etrk_[st].has_gem_pad |= 1;
    etrk_[st].chamber_lct_odd = id.chamber();
    // etrk_[st].pad_odd = digi_channel(bestgem_dg_and_gp.first);
    etrk_[st].hsfromgem_odd = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
    etrk_[st].z_pad_odd = best_pad_odd[st].z();
    etrk_[st].phi_pad_odd = best_pad_odd[st].phi();
    etrk_[st].eta_pad_odd = best_pad_odd[st].eta();
    //question: ME1a is not included here
    if (is_valid(lct_odd[st]))
    {
    const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
    best_pad_odd[st] = gem_dg_and_gp.second;
    // etrk_[st].bx_pad_odd = digi_bx(gem_dg_and_gp.first);
    etrk_[st].dphi_pad_odd = deltaPhi(etrk_[st].phi_lct_odd, etrk_[st].phi_pad_odd);
    etrk_[st].dphi_pad_fit_odd = deltaPhi(etrk_[st].phi_layer3_fit_odd, etrk_[st].phi_pad_odd);
    //std::cout <<"GEMid "<< id << std::endl;
    //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< etrk_[st].phi_pad_odd <<" phi_lct "<< etrk_[st].phi_lct_odd <<" phi_fit_lct "<< etrk_[st].phi_layer3_fit_odd <<" dist(GEM, CSC) " << fabs(etrk_[st].z_layer3_fit_odd - etrk_[st].z_pad_odd)<< std::endl;
    etrk_[st].deta_pad_odd = etrk_[st].eta_lct_odd - etrk_[st].eta_pad_odd;
    }
    }
    else
    {
    best_pad_even[st] = bestgem_dg_and_gp.second;
    etrk_[st].has_gem_pad |= 2;
    // etrk_[st].pad_even = digi_channel(bestgem_dg_and_gp.first);
    // etrk_[st].hsfromgem_even = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
    etrk_[st].z_pad_even = best_pad_even[st].z();
    etrk_[st].phi_pad_even = best_pad_even[st].phi();
    etrk_[st].eta_pad_even = best_pad_even[st].eta();
    if (is_valid(lct_even[st]))
    {
    const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_even[st]);
    best_pad_even[st] = gem_dg_and_gp.second;
    // etrk_[st].bx_pad_even = digi_bx(gem_dg_and_gp.first);
    etrk_[st].dphi_pad_even = deltaPhi(etrk_[st].phi_lct_even, etrk_[st].phi_pad_even);
    etrk_[st].dphi_pad_fit_even = deltaPhi(etrk_[st].phi_layer3_fit_even, etrk_[st].phi_pad_even);
    //std::cout <<"GEMid "<< id << std::endl;
    //std::cout <<"GEM sim phi "<< keygp.phi() <<" pad phi "<< etrk_[st].phi_pad_even <<" phi_lct "<< etrk_[st].phi_lct_even <<" phi_fit_lct "<< etrk_[st].phi_layer3_fit_even <<" dist(GEM, CSC) " <<  fabs(etrk_[st].z_layer3_fit_even - etrk_[st].z_pad_even)<< std::endl;
    etrk_[st].deta_pad_even = etrk_[st].eta_lct_even - etrk_[st].eta_pad_even;
    }
    }
    if (id_tmp.layer()==1) break;
    }
    }

    //ME11Case
    for(const auto& d: match_gd.superChamberIdsDigi())
    {
    GEMDetId id(d);
    int MEStation = id.station();

    const int stations(detIdToMEStation(MEStation,id.ring()));
    int st;
    if (stations==2 or stations==3) st=1;//ME1a,ME1b->ME11
    else continue;

    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (match_gd.nLayersWithDigisInSuperChamber(d) > 1)
    {
    if (odd) etrk_[st].has_gem_dg2 |= 1;
    else     etrk_[st].has_gem_dg2 |= 2;
    }

    const auto& digis = match_gd.digisInSuperChamber(d);
    const int median_strip(match_gd.median(digis));
    if (odd && digis.size() > 0)
    {
    etrk_[st].has_gem_dg |= 1;
    etrk_[st].strip_gemdg_odd = median_strip;
    }
    else if (digis.size() > 0)
    {
    etrk_[st].has_gem_dg |= 2;
    etrk_[st].strip_gemdg_even = median_strip;
    }

    if (match_gd.nLayersWithPadsInSuperChamber(d) > 1)
    {
    if (odd) etrk_[st].has_gem_pad2 |= 1;
    else     etrk_[st].has_gem_pad2 |= 2;
    }

    for (int layer=1; layer<3; layer++){
    GEMDetId id_tmp(id.region(), id.ring(), id.station(), layer, id.chamber(), 0);
    const auto& pads = match_gd.padsInChamber(id_tmp.rawId());
    if(pads.size() == 0) continue;
    const GlobalPoint& keygp = match_sh.simHitsMeanPosition(match_sh.hitsInChamber(id_tmp.rawId()));
    const auto& bestgem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, keygp);

    if (odd)
    {
    best_pad_odd[st] = bestgem_dg_and_gp.second;
    etrk_[st].has_gem_pad |= 1;
    // etrk_[st].pad_odd = digi_channel(bestgem_dg_and_gp.first);
    // etrk_[st].hsfromgem_odd = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
    etrk_[st].phi_pad_odd = best_pad_odd[st].phi();
    etrk_[st].eta_pad_odd = best_pad_odd[st].eta();
    if (is_valid(lct_odd[st]))
    {
    const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_odd[st]);
    best_pad_odd[st] = gem_dg_and_gp.second;
    // etrk_[st].bx_pad_odd = digi_bx(gem_dg_and_gp.first);
    etrk_[st].dphi_pad_odd = deltaPhi(etrk_[st].phi_lct_odd, etrk_[st].phi_pad_odd);
    etrk_[st].dphi_pad_fit_odd = deltaPhi(etrk_[st].phi_layer3_fit_odd, etrk_[st].phi_pad_odd);
    etrk_[st].deta_pad_odd = etrk_[st].eta_lct_odd - etrk_[st].eta_pad_odd;
    }
    }
    else
    {
    best_pad_even[st] = bestgem_dg_and_gp.second;
    etrk_[st].has_gem_pad |= 2;
    // etrk_[st].pad_even = digi_channel(bestgem_dg_and_gp.first);
    // etrk_[st].hsfromgem_even = match_gd.extrapolateHsfromGEMPad( d, digi_channel(bestgem_dg_and_gp.first));
    etrk_[st].phi_pad_even = best_pad_even[st].phi();
    etrk_[st].eta_pad_even = best_pad_even[st].eta();
    if (is_valid(lct_even[st]))
    {
    const auto& gem_dg_and_gp = match_gd.digiInGEMClosestToCSC(pads, gp_lct_even[st]);
    best_pad_even[st] = gem_dg_and_gp.second;
    // etrk_[st].bx_pad_even = digi_bx(gem_dg_and_gp.first);
    etrk_[st].dphi_pad_even = deltaPhi(etrk_[st].phi_lct_even, etrk_[st].phi_pad_even);
    etrk_[st].dphi_pad_fit_even = deltaPhi(etrk_[st].phi_layer3_fit_even, etrk_[st].phi_pad_even);
    etrk_[st].deta_pad_even = etrk_[st].eta_lct_even - etrk_[st].eta_pad_even;
    }
    }
    if (id_tmp.layer()==1) break;
    }
    }

    if (verbose_) std::cout <<"GEMCSCAnalyzer step6 "<< std::endl;
    for(const auto& d: match_gd.superChamberIdsCoPad())
    {
    GEMDetId id(d);
    int MEStation = id.station();

    const int st(detIdToMEStation(MEStation,id.ring()));
    if (stations_to_use_.count(st) == 0) continue;

    const bool odd(id.chamber()%2==1);
    if (odd) etrk_[st].has_gem_copad |= 1;
    else     etrk_[st].has_gem_copad |= 2;

    const auto& copads = match_gd.coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;
    // if (odd) etrk_[st].Copad_odd = digi_channel(copads.at(0));
    // else etrk_[st].Copad_even = digi_channel(copads.at(0));
    if (verbose_) std::cout <<"Matching GEMCopad detid "<< id <<" size "<< copads.size() << std::endl;

    if (st==2 or st==3)
    {
    if (odd) etrk_[1].has_gem_copad |= 1;
    else     etrk_[1].has_gem_copad |= 2;

    const auto& copads = match_gd.coPadsInSuperChamber(d);
    if (copads.size() == 0) continue;
    // if (odd) etrk_[1].Copad_odd = digi_channel(copads.at(0));
    // else etrk_[1].Copad_even = digi_channel(copads.at(0));
    }
    }
  */

  for (const auto& s : stations_to_use_) {
    tree_eff_[s]->Fill();
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
