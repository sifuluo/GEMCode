//////////////////////////////////////////////////////////////////////
//               Making Ntuples for GEM CSC analysis                //
//               Author: Sifu Luo                                   //
//               sifuluo@tamu.edu                                   //
//////////////////////////////////////////////////////////////////////

// CMSSW
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// GEMCode
#include "GEMCode/GEMValidation/interface/MatcherManager.h"

// Other tools
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// Muons
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "L1Trigger/L1TMuon/interface/MuonRawDigiTranslator.h"
#include "L1Trigger/L1TMuon/interface/RegionalMuonRawDigiTranslator.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCandFwd.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "L1Trigger/L1TMuon/interface/MicroGMTConfiguration.h"

// KBMTF
#include "DataFormats/L1TMuon/interface/L1MuKBMTrack.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"

// ROOT
#include <TROOT.h>
#include <TTree.h>

// STD
#include <iomanip>
#include <sstream>
#include <iostream>
#include <memory>
#include <string>
#include <math.h>
#include <bitset>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <sstream>
#include <stdexcept>

// Unclear headers
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ref.h"

#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"
#include "DataFormats/L1TrackTrigger/interface/TTCluster.h"
#include "DataFormats/L1TrackTrigger/interface/TTStub.h"
#include "DataFormats/L1TrackTrigger/interface/TTTrack.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTClusterAssociationMap.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTStubAssociationMap.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTTrackAssociationMap.h"
#include "Geometry/Records/interface/StackedTrackerGeometryRecord.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/RectangularPixelTopology.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"

#include "Geometry/CommonTopologies/interface/PixelGeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/PixelGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelTopologyBuilder.h"
#include "Geometry/Records/interface/StackedTrackerGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"

#include "DataFormats/CSCDigi/interface/CSCALCTDigi.h"
#include "DataFormats/CSCDigi/interface/CSCCLCTDigi.h"

using namespace std;
using namespace edm;

class NtupleMaker : public edm::EDAnalyzer {
public:
  explicit NtupleMaker(const edm::ParameterSet& iConfig);
  virtual ~NtupleMaker();

  virtual void beginJob();
  virtual void endJob();
  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);

  struct DigiContent{
    int detid;
    int strip;
    int wire;
    int quality;
    std::vector<std::vector<int> > hits2D;
    std::vector<int> hits;
    std::vector<int> positions;
  };
  virtual void PrintHits(int iset, int idigi = -1);
  virtual int SaveHitMatrix(std::vector< std::vector<unsigned short> > hits, std::vector<int>* b_hit, std::vector<int>* b_pos, bool doprint = false, bool isclct = false);
  virtual std::vector<int> IntsToBinary(int n);

protected:

private:
  // ParameterSet passed from python configuration
  edm::ParameterSet config;

  int MyProcess;
  bool DebugMode;
  double TP_minPt;
  double TP_maxEta;
  double TP_maxZ0;
  bool Print_matchCscStubs;
  bool Print_allCscStubs;
  bool Print_all;
  bool Print_ALCT;
  bool Print_CLCT;

  int nEventMultiHitLayer;

  edm::InputTag TrackingParticleInputTag;

  std::string getFloatPointDataWord(const l1t::RegionalMuonCand& l1mu) const;
  std::string getGlobalPhi(const l1t::RegionalMuonCand& l1mu) const;

  edm::EDGetToken m_emtfToken;
  edm::EDGetToken m_bmtfToken;
  edm::EDGetToken m_omtfToken;

  edm::EDGetTokenT< std::vector< TrackingParticle > > TrackingParticleToken_;
  edm::EDGetTokenT<edm::SimVertexContainer> simVertexInput_;

  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lctToken_;
  edm::EDGetTokenT<CSCALCTDigiCollection> alctToken_;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clctToken_;
  edm::EDGetTokenT<GEMDigiCollection> gemDigiToken_;

  // Ntuple
  TTree* eventTree;

  // Tracking particles
  std::vector<float>* m_tp_pt;
  std::vector<float>* m_tp_eta;
  std::vector<float>* m_tp_phi;
  std::vector<float>* m_tp_dxy;
  std::vector<float>* m_tp_d0;
  std::vector<float>* m_tp_z0;
  std::vector<float>* m_tp_d0_prod;
  std::vector<float>* m_tp_z0_prod;
  std::vector<int>*   m_tp_pdgid;
  std::vector<int>*   m_tp_nmatch;
  std::vector<int>*   m_tp_nloosematch;
  std::vector<int>*   m_tp_nstub;
  std::vector<int>*   m_tp_eventid;
  std::vector<int>*   m_tp_charge;

  // Regional Muon candidates
  std::vector<int>*   m_EMTF_muon_n;
  std::vector<float>* m_EMTF_muon_pt;
  std::vector<float>* m_EMTF_muon_eta;
  std::vector<float>* m_EMTF_muon_phi;
  std::vector<int>*   m_EMTF_muon_c;

  std::vector<int>*   m_OMTF_muon_n;
  std::vector<float>* m_OMTF_muon_pt;
  std::vector<float>* m_OMTF_muon_eta;
  std::vector<float>* m_OMTF_muon_phi;
  std::vector<int>*   m_OMTF_muon_c;

  std::vector<int>*   m_BMTF_muon_n;
  std::vector<float>* m_BMTF_muon_pt;
  std::vector<float>* m_BMTF_muon_eta;
  std::vector<float>* m_BMTF_muon_phi;
  std::vector<int>*   m_BMTF_muon_c;

  std::vector<float>* m_cscSimHit_phi;
  std::vector<float>* m_cscSimHit_eta;
  std::vector<float>* m_cscSimHit_z;
  std::vector<float>* m_cscSimHit_r;
  std::vector<int>*   m_cscSimHit_station;
  std::vector<int>*   m_cscSimHit_matchTp;

  std::vector<float>* m_gemSimHit_phi;
  std::vector<float>* m_gemSimHit_eta;
  std::vector<float>* m_gemSimHit_z;
  std::vector<float>* m_gemSimHit_r;
  std::vector<int>*   m_gemSimHit_station;
  std::vector<int>*   m_gemSimHit_matchTp;

  std::vector<float>* m_matchmuon_pt;
  std::vector<float>* m_matchmuon_eta;
  std::vector<float>* m_matchmuon_phi;
  std::vector<int>*   m_matchmuon_charge;
  std::vector<int>*   m_matchmuon_type;
  std::vector<int>*   m_matchmuon_quality;

  std::vector<float>* m_allCscStubsLCT_phi;
  std::vector<float>* m_allCscStubsLCT_eta;
  std::vector<float>* m_allCscStubsLCT_z;
  std::vector<float>* m_allCscStubsLCT_r;
  std::vector<float>* m_allCscStubsLCT_bend;
  std::vector<float>* m_allCscStubsLCT_pattern;
  std::vector<int>*   m_allCscStubsLCT_quality;
  std::vector<int>*   m_allCscStubsLCT_detId;
  std::vector<int>*   m_allCscStubsLCT_keywire;
  std::vector<int>*   m_allCscStubsLCT_strip;
  std::vector<bool>*  m_allCscStubsLCT_valid;
  std::vector<int>*   m_allCscStubsLCT_type;

  std::vector<int>*   m_allCscStubsALCT_detId;
  std::vector<int>*   m_allCscStubsALCT_keywire;
  std::vector<int>*   m_allCscStubsALCT_hit;
  std::vector<int>*   m_allCscStubsALCT_position;
  std::vector<bool>*  m_allCscStubsALCT_valid;

  std::vector<int>*   m_allCscStubsCLCT_detId;
  std::vector<int>*   m_allCscStubsCLCT_strip;
  std::vector<int>*   m_allCscStubsCLCT_hit;
  std::vector<int>*   m_allCscStubsCLCT_position;
  std::vector<bool>*  m_allCscStubsCLCT_valid;

  std::vector<int>*   m_allALCT_detId;
  std::vector<int>*   m_allALCT_keywire;
  std::vector<int>*   m_allALCT_hit;
  std::vector<int>*   m_allALCT_position;
  std::vector<bool>*  m_allALCT_valid;

  std::vector<int>*   m_allCLCT_detId;
  std::vector<int>*   m_allCLCT_strip;
  std::vector<int>*   m_allCLCT_hit;
  std::vector<int>*   m_allCLCT_position;
  std::vector<bool>*  m_allCLCT_valid;

  std::vector<float>* m_allGemDigi_phi;
  std::vector<float>* m_allGemDigi_eta;
  std::vector<float>* m_allGemDigi_z;
  std::vector<float>* m_allGemDigi_r;

  std::vector<float>* m_matchCscStubsLCT_phi;
  std::vector<float>* m_matchCscStubsLCT_eta;
  std::vector<float>* m_matchCscStubsLCT_z;
  std::vector<float>* m_matchCscStubsLCT_r;
  std::vector<float>* m_matchCscStubsLCT_bend;
  std::vector<float>* m_matchCscStubsLCT_pattern;
  std::vector<int>*   m_matchCscStubsLCT_matchTp;
  std::vector<int>*   m_matchCscStubsLCT_quality;
  std::vector<int>*   m_matchCscStubsLCT_detId;
  std::vector<int>*   m_matchCscStubsLCT_keywire;
  std::vector<int>*   m_matchCscStubsLCT_strip;
  std::vector<bool>*  m_matchCscStubsLCT_valid;
  std::vector<int>*   m_matchCscStubsLCT_type;

  std::vector<int>*   m_matchCscStubsALCT_detId;
  std::vector<int>*   m_matchCscStubsALCT_keywire;
  std::vector<int>*   m_matchCscStubsALCT_hit;
  std::vector<int>*   m_matchCscStubsALCT_position;
  std::vector<bool>*  m_matchCscStubsALCT_valid;

  std::vector<int>*   m_matchCscStubsCLCT_detId;
  std::vector<int>*   m_matchCscStubsCLCT_strip;
  std::vector<int>*   m_matchCscStubsCLCT_hit;
  std::vector<int>*   m_matchCscStubsCLCT_position;
  std::vector<bool>*  m_matchCscStubsCLCT_valid;

  std::vector<float>* m_matchGemDigi_phi;
  std::vector<float>* m_matchGemDigi_eta;
  std::vector<float>* m_matchGemDigi_z;
  std::vector<float>* m_matchGemDigi_r;
  std::vector<int>*   m_matchGemDigi_matchTp;

  std::unique_ptr<MatcherManager> match;

  const TrackingGeometry* geometry_;
};


NtupleMaker::NtupleMaker(edm::ParameterSet const& iConfig) :
config(iConfig)
{
  MyProcess = iConfig.getParameter< int >("MyProcess");
  DebugMode        = iConfig.getParameter< bool >("DebugMode");
  TP_minPt         = iConfig.getParameter< double >("TP_minPt");
  TP_maxEta        = iConfig.getParameter< double >("TP_maxEta");
  TP_maxZ0         = iConfig.getParameter< double >("TP_maxZ0");
  Print_matchCscStubs = iConfig.getParameter< bool >("Print_matchCscStubs");
  Print_allCscStubs   = iConfig.getParameter< bool >("Print_allCscStubs");
  Print_all         = iConfig.getParameter< bool >("Print_all");
  Print_ALCT        = iConfig.getParameter< bool >("Print_ALCT");
  Print_CLCT        = iConfig.getParameter< bool >("Print_CLCT");

  TrackingParticleInputTag = iConfig.getParameter<edm::InputTag>("TrackingParticleInputTag");
  TrackingParticleToken_ = consumes< std::vector< TrackingParticle > >(TrackingParticleInputTag);

  m_emtfToken = consumes<l1t::RegionalMuonCandBxCollection>(edm::InputTag("simEmtfDigis","EMTF"));
  m_bmtfToken = consumes<l1t::RegionalMuonCandBxCollection>(edm::InputTag("gmtStage2Digis","BMTF"));
  m_omtfToken = consumes<l1t::RegionalMuonCandBxCollection>(edm::InputTag("gmtStage2Digis","OMTF"));

  const auto& simVertex = iConfig.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("inputTag"));

  const auto& P_cscLCT = iConfig.getParameter<edm::ParameterSet>("cscLCT");
  lctToken_ = consumes<CSCCorrelatedLCTDigiCollection>(P_cscLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& P_cscALCT = iConfig.getParameter<edm::ParameterSet>("cscALCT");
  alctToken_ = consumes<CSCALCTDigiCollection>(P_cscALCT.getParameter<edm::InputTag>("inputTag"));

  const auto& P_cscCLCT = iConfig.getParameter<edm::ParameterSet>("cscCLCT");
  clctToken_ = consumes<CSCCLCTDigiCollection>(P_cscCLCT.getParameter<edm::InputTag>("inputTag"));

  const auto& P_gemDigi = iConfig.getParameter<edm::ParameterSet>("gemStripDigi");
  gemDigiToken_ = consumes<GEMDigiCollection>(P_gemDigi.getParameter<edm::InputTag>("inputTag"));

  match.reset(new MatcherManager(iConfig, consumesCollector()));
}

NtupleMaker::~NtupleMaker()
{
}

void NtupleMaker::endJob()
{
  cerr << "Number of event with layers having multiple hits: " << nEventMultiHitLayer <<endl;
  cerr << "NtupleMaker::endJob" << endl;
}

void NtupleMaker::beginJob()
{
  cerr << "NtupleMaker::beginJob" << endl;

  nEventMultiHitLayer = 0;

  edm::Service<TFileService> fs;

  m_tp_pt      = new std::vector<float>;
  m_tp_eta     = new std::vector<float>;
  m_tp_phi     = new std::vector<float>;
  m_tp_dxy     = new std::vector<float>;
  m_tp_d0      = new std::vector<float>;
  m_tp_z0      = new std::vector<float>;
  m_tp_d0_prod = new std::vector<float>;
  m_tp_z0_prod = new std::vector<float>;
  m_tp_pdgid   = new std::vector<int>;
  m_tp_nmatch  = new std::vector<int>;
  m_tp_nloosematch  = new std::vector<int>;
  m_tp_nstub        = new std::vector<int>;
  m_tp_eventid      = new std::vector<int>;
  m_tp_charge       = new std::vector<int>;

  m_EMTF_muon_n = new std::vector<int>;
  m_EMTF_muon_pt = new std::vector<float>;
  m_EMTF_muon_eta = new std::vector<float>;
  m_EMTF_muon_phi = new std::vector<float>;
  m_EMTF_muon_c = new std::vector<int>;

  m_OMTF_muon_n = new std::vector<int>;
  m_OMTF_muon_pt = new std::vector<float>;
  m_OMTF_muon_eta = new std::vector<float>;
  m_OMTF_muon_phi = new std::vector<float>;
  m_OMTF_muon_c = new std::vector<int>;

  m_BMTF_muon_n = new std::vector<int>;
  m_BMTF_muon_pt = new std::vector<float>;
  m_BMTF_muon_eta = new std::vector<float>;
  m_BMTF_muon_phi = new std::vector<float>;
  m_BMTF_muon_c = new std::vector<int>;

  m_cscSimHit_phi = new std::vector<float>;
  m_cscSimHit_eta = new std::vector<float>;
  m_cscSimHit_z = new std::vector<float>;
  m_cscSimHit_r = new std::vector<float>;
  m_cscSimHit_station = new std::vector<int>;
  m_cscSimHit_matchTp = new std::vector<int>;

  m_gemSimHit_phi = new std::vector<float>;
  m_gemSimHit_eta = new std::vector<float>;
  m_gemSimHit_z = new std::vector<float>;
  m_gemSimHit_r = new std::vector<float>;
  m_gemSimHit_station = new std::vector<int>;
  m_gemSimHit_matchTp = new std::vector<int>;

  m_matchmuon_pt     = new std::vector<float>;
  m_matchmuon_eta    = new std::vector<float>;
  m_matchmuon_phi    = new std::vector<float>;
  m_matchmuon_charge = new std::vector<int>;
  m_matchmuon_type   = new std::vector<int>;
  m_matchmuon_quality= new std::vector<int>;

  m_allCscStubsLCT_phi = new std::vector<float>;
  m_allCscStubsLCT_eta = new std::vector<float>;
  m_allCscStubsLCT_z = new std::vector<float>;
  m_allCscStubsLCT_r = new std::vector<float>;
  m_allCscStubsLCT_bend = new std::vector<float>;
  m_allCscStubsLCT_pattern = new std::vector<float>;
  m_allCscStubsLCT_quality = new std::vector<int>;
  m_allCscStubsLCT_detId = new std::vector<int>;
  m_allCscStubsLCT_keywire = new std::vector<int>;
  m_allCscStubsLCT_strip = new std::vector<int>;
  m_allCscStubsLCT_valid = new std::vector<bool>;
  m_allCscStubsLCT_type = new std::vector<int>;

  m_allCscStubsALCT_detId = new std::vector<int>;
  m_allCscStubsALCT_keywire = new std::vector<int>;
  m_allCscStubsALCT_hit = new std::vector<int>;
  m_allCscStubsALCT_position = new std::vector<int>;
  m_allCscStubsALCT_valid = new std::vector<bool>;

  m_allCscStubsCLCT_detId = new std::vector<int>;
  m_allCscStubsCLCT_strip = new std::vector<int>;
  m_allCscStubsCLCT_hit = new std::vector<int>;
  m_allCscStubsCLCT_position = new std::vector<int>;
  m_allCscStubsCLCT_valid = new std::vector<bool>;

  m_allALCT_detId = new std::vector<int>;
  m_allALCT_keywire = new std::vector<int>;
  m_allALCT_hit = new std::vector<int>;
  m_allALCT_position = new std::vector<int>;
  m_allALCT_valid = new std::vector<bool>;

  m_allCLCT_detId = new std::vector<int>;
  m_allCLCT_strip = new std::vector<int>;
  m_allCLCT_hit = new std::vector<int>;
  m_allCLCT_position = new std::vector<int>;
  m_allCLCT_valid = new std::vector<bool>;

  m_allGemDigi_phi = new std::vector<float>;
  m_allGemDigi_eta = new std::vector<float>;
  m_allGemDigi_z = new std::vector<float>;
  m_allGemDigi_r = new std::vector<float>;

  m_matchCscStubsLCT_phi = new std::vector<float>;
  m_matchCscStubsLCT_eta = new std::vector<float>;
  m_matchCscStubsLCT_z = new std::vector<float>;
  m_matchCscStubsLCT_r = new std::vector<float>;
  m_matchCscStubsLCT_bend = new std::vector<float>;
  m_matchCscStubsLCT_pattern = new std::vector<float>;
  m_matchCscStubsLCT_matchTp = new std::vector<int>;
  m_matchCscStubsLCT_quality = new std::vector<int>;
  m_matchCscStubsLCT_detId = new std::vector<int>;
  m_matchCscStubsLCT_keywire = new std::vector<int>;
  m_matchCscStubsLCT_strip = new std::vector<int>;
  m_matchCscStubsLCT_valid = new std::vector<bool>;
  m_matchCscStubsLCT_type = new std::vector<int>;

  m_matchCscStubsALCT_detId = new std::vector<int>;
  m_matchCscStubsALCT_keywire = new std::vector<int>;
  m_matchCscStubsALCT_hit = new std::vector<int>;
  m_matchCscStubsALCT_position = new std::vector<int>;
  m_matchCscStubsALCT_valid = new std::vector<bool>;

  m_matchCscStubsCLCT_detId = new std::vector<int>;
  m_matchCscStubsCLCT_strip = new std::vector<int>;
  m_matchCscStubsCLCT_hit = new std::vector<int>;
  m_matchCscStubsCLCT_position = new std::vector<int>;
  m_matchCscStubsCLCT_valid = new std::vector<bool>;

  m_matchGemDigi_phi = new std::vector<float>;
  m_matchGemDigi_eta = new std::vector<float>;
  m_matchGemDigi_z = new std::vector<float>;
  m_matchGemDigi_r = new std::vector<float>;
  m_matchGemDigi_matchTp = new std::vector<int>;

  eventTree = fs->make<TTree>("eventTree", "Event tree");

  eventTree->Branch("tp_pt",     &m_tp_pt);
  eventTree->Branch("tp_eta",    &m_tp_eta);
  eventTree->Branch("tp_phi",    &m_tp_phi);
  eventTree->Branch("tp_dxy",    &m_tp_dxy);
  eventTree->Branch("tp_d0",     &m_tp_d0);
  eventTree->Branch("tp_z0",     &m_tp_z0);
  eventTree->Branch("tp_d0_prod",     &m_tp_d0_prod);
  eventTree->Branch("tp_z0_prod",     &m_tp_z0_prod);
  eventTree->Branch("tp_pdgid",       &m_tp_pdgid);
  eventTree->Branch("tp_nmatch",      &m_tp_nmatch);
  eventTree->Branch("tp_nloosematch", &m_tp_nloosematch);
  eventTree->Branch("tp_nstub",       &m_tp_nstub);
  eventTree->Branch("tp_eventid",     &m_tp_eventid);
  eventTree->Branch("tp_charge",      &m_tp_charge);

  eventTree->Branch("EMTF_muon_n",	 &m_EMTF_muon_n);
  eventTree->Branch("EMTF_muon_pt",  	 &m_EMTF_muon_pt);
  eventTree->Branch("EMTF_muon_eta", 	 &m_EMTF_muon_eta);
  eventTree->Branch("EMTF_muon_phi", 	 &m_EMTF_muon_phi);
  eventTree->Branch("EMTF_muon_c", 	 &m_EMTF_muon_c);

  eventTree->Branch("OMTF_muon_n",	 &m_OMTF_muon_n);
  eventTree->Branch("OMTF_muon_pt", 	 &m_OMTF_muon_pt);
  eventTree->Branch("OMTF_muon_eta", 	 &m_OMTF_muon_eta);
  eventTree->Branch("OMTF_muon_phi", 	 &m_OMTF_muon_phi);
  eventTree->Branch("OMTF_muon_c", 	 &m_OMTF_muon_c);

  eventTree->Branch("BMTF_muon_n",	 &m_BMTF_muon_n);
  eventTree->Branch("BMTF_muon_pt", 	 &m_BMTF_muon_pt);
  eventTree->Branch("BMTF_muon_eta", 	 &m_BMTF_muon_eta);
  eventTree->Branch("BMTF_muon_phi", 	 &m_BMTF_muon_phi);
  eventTree->Branch("BMTF_muon_c", 	 &m_BMTF_muon_c);

  eventTree->Branch("cscSimHit_phi",&m_cscSimHit_phi);
  eventTree->Branch("cscSimHit_eta",&m_cscSimHit_eta);
  eventTree->Branch("cscSimHit_z",&m_cscSimHit_z);
  eventTree->Branch("cscSimHit_r",&m_cscSimHit_r);
  eventTree->Branch("cscSimHit_station",&m_cscSimHit_station);
  eventTree->Branch("cscSimHit_matchTp",&m_cscSimHit_matchTp);

  eventTree->Branch("gemSimHit_phi",&m_gemSimHit_phi);
  eventTree->Branch("gemSimHit_eta",&m_gemSimHit_eta);
  eventTree->Branch("gemSimHit_z",&m_gemSimHit_z);
  eventTree->Branch("gemSimHit_r",&m_gemSimHit_r);
  eventTree->Branch("gemSimHit_station",&m_gemSimHit_station);
  eventTree->Branch("gemSimHit_matchTp",&m_gemSimHit_matchTp);

  eventTree->Branch("matchmuon_pt", &m_matchmuon_pt);
  eventTree->Branch("matchmuon_eta", &m_matchmuon_eta);
  eventTree->Branch("matchmuon_phi", &m_matchmuon_phi);
  eventTree->Branch("matchmuon_charge",&m_matchmuon_charge);
  eventTree->Branch("matchmuon_type",&m_matchmuon_type);
  eventTree->Branch("matchmuon_quality",&m_matchmuon_quality);

  eventTree->Branch("allCscStubsLCT_phi", &m_allCscStubsLCT_phi);
  eventTree->Branch("allCscStubsLCT_eta", &m_allCscStubsLCT_eta);
  eventTree->Branch("allCscStubsLCT_z", &m_allCscStubsLCT_z);
  eventTree->Branch("allCscStubsLCT_r", &m_allCscStubsLCT_r);
  eventTree->Branch("allCscStubsLCT_bend", &m_allCscStubsLCT_bend);
  eventTree->Branch("allCscStubsLCT_pattern", &m_allCscStubsLCT_pattern);
  eventTree->Branch("allCscStubsLCT_quality", &m_allCscStubsLCT_quality);
  eventTree->Branch("allCscStubsLCT_detId", &m_allCscStubsLCT_detId);
  eventTree->Branch("allCscStubsLCT_keywire", &m_allCscStubsLCT_keywire);
  eventTree->Branch("allCscStubsLCT_strip", &m_allCscStubsLCT_strip);
  eventTree->Branch("allCscStubsLCT_valid", &m_allCscStubsLCT_valid);
  eventTree->Branch("allCscStubsLCT_type", &m_allCscStubsLCT_type);

  eventTree->Branch("allCscStubsALCT_detId", &m_allCscStubsALCT_detId);
  eventTree->Branch("allCscStubsALCT_keywire", &m_allCscStubsALCT_keywire);
  eventTree->Branch("allCscStubsALCT_hit", &m_allCscStubsALCT_hit);
  eventTree->Branch("allCscStubsALCT_position", &m_allCscStubsALCT_position);
  eventTree->Branch("allCscStubsALCT_valid", &m_allCscStubsALCT_valid);

  eventTree->Branch("allCscStubsCLCT_detId", &m_allCscStubsCLCT_detId);
  eventTree->Branch("allCscStubsCLCT_strip", &m_allCscStubsCLCT_strip);
  eventTree->Branch("allCscStubsCLCT_hit", &m_allCscStubsCLCT_hit);
  eventTree->Branch("allCscStubsCLCT_position", &m_allCscStubsCLCT_position);
  eventTree->Branch("allCscStubsCLCT_valid", &m_allCscStubsCLCT_valid);

  eventTree->Branch("allALCT_detId", &m_allALCT_detId);
  eventTree->Branch("allALCT_keywire", &m_allALCT_keywire);
  eventTree->Branch("allALCT_hit", &m_allALCT_hit);
  eventTree->Branch("allALCT_position", &m_allALCT_position);
  eventTree->Branch("allALCT_valid", &m_allALCT_valid);

  eventTree->Branch("allCLCT_detId", &m_allCLCT_detId);
  eventTree->Branch("allCLCT_strip", &m_allCLCT_strip);
  eventTree->Branch("allCLCT_hit", &m_allCLCT_hit);
  eventTree->Branch("allCLCT_position", &m_allCLCT_position);
  eventTree->Branch("allCLCT_valid", &m_allCLCT_valid);

  eventTree->Branch("allGemDigi_phi", &m_allGemDigi_phi);
  eventTree->Branch("allGemDigi_eta", &m_allGemDigi_eta);
  eventTree->Branch("allGemDigi_z", &m_allGemDigi_z);
  eventTree->Branch("allGemDigi_r", &m_allGemDigi_r);

  eventTree->Branch("matchCscStubsLCT_phi", &m_matchCscStubsLCT_phi);
  eventTree->Branch("matchCscStubsLCT_eta", &m_matchCscStubsLCT_eta);
  eventTree->Branch("matchCscStubsLCT_z", &m_matchCscStubsLCT_z);
  eventTree->Branch("matchCscStubsLCT_r", &m_matchCscStubsLCT_r);
  eventTree->Branch("matchCscStubsLCT_bend", &m_matchCscStubsLCT_bend);
  eventTree->Branch("matchCscStubsLCT_pattern", &m_matchCscStubsLCT_pattern);
  eventTree->Branch("matchCscStubsLCT_matchTp", &m_matchCscStubsLCT_matchTp);
  eventTree->Branch("matchCscStubsLCT_quality", &m_matchCscStubsLCT_quality);
  eventTree->Branch("matchCscStubsLCT_detId", &m_matchCscStubsLCT_detId);
  eventTree->Branch("matchCscStubsLCT_keywire", &m_matchCscStubsLCT_keywire);
  eventTree->Branch("matchCscStubsLCT_strip", &m_matchCscStubsLCT_strip);
  eventTree->Branch("matchCscStubsLCT_valid", &m_matchCscStubsLCT_valid);
  eventTree->Branch("matchCscStubsLCT_type", &m_matchCscStubsLCT_type);

  eventTree->Branch("matchCscStubsALCT_detId", &m_matchCscStubsALCT_detId);
  eventTree->Branch("matchCscStubsALCT_keywire", &m_matchCscStubsALCT_keywire);
  eventTree->Branch("matchCscStubsALCT_hit", &m_matchCscStubsALCT_hit);
  eventTree->Branch("matchCscStubsALCT_position", &m_matchCscStubsALCT_position);
  eventTree->Branch("matchCscStubsALCT_valid", &m_matchCscStubsALCT_valid);

  eventTree->Branch("matchCscStubsCLCT_detId", &m_matchCscStubsCLCT_detId);
  eventTree->Branch("matchCscStubsCLCT_strip", &m_matchCscStubsCLCT_strip);
  eventTree->Branch("matchCscStubsCLCT_hit", &m_matchCscStubsCLCT_hit);
  eventTree->Branch("matchCscStubsCLCT_position", &m_matchCscStubsCLCT_position);
  eventTree->Branch("matchCscStubsCLCT_valid", &m_matchCscStubsCLCT_valid);

  eventTree->Branch("matchGemDigi_phi", &m_matchGemDigi_phi);
  eventTree->Branch("matchGemDigi_eta", &m_matchGemDigi_eta);
  eventTree->Branch("matchGemDigi_z", &m_matchGemDigi_z);
  eventTree->Branch("matchGemDigi_r", &m_matchGemDigi_r);
  eventTree->Branch("matchGemDigi_matchTp", &m_matchGemDigi_matchTp);

}

void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if (DebugMode) cout << "analyze began" << endl;
  if (!(MyProcess==13 || MyProcess==11 || MyProcess==211 || MyProcess==6 || MyProcess==15 || MyProcess==1)) {
    cout << "The specified MyProcess is invalid! Exiting..." << endl;
    return;
  }

  m_tp_pt->clear();
  m_tp_eta->clear();
  m_tp_phi->clear();
  m_tp_dxy->clear();
  m_tp_d0->clear();
  m_tp_z0->clear();
  m_tp_d0_prod->clear();
  m_tp_z0_prod->clear();
  m_tp_pdgid->clear();
  m_tp_nmatch->clear();
  m_tp_nloosematch->clear();
  m_tp_nstub->clear();
  m_tp_eventid->clear();
  m_tp_charge->clear();

  m_EMTF_muon_n->clear();
  m_EMTF_muon_pt->clear();
  m_EMTF_muon_eta->clear();
  m_EMTF_muon_phi->clear();
  m_EMTF_muon_c->clear();

  m_OMTF_muon_n->clear();
  m_OMTF_muon_pt->clear();
  m_OMTF_muon_eta->clear();
  m_OMTF_muon_phi->clear();
  m_OMTF_muon_c->clear();

  m_BMTF_muon_n->clear();
  m_BMTF_muon_pt->clear();
  m_BMTF_muon_eta->clear();
  m_BMTF_muon_phi->clear();
  m_BMTF_muon_c->clear();

  m_cscSimHit_phi->clear();
  m_cscSimHit_eta->clear();
  m_cscSimHit_z->clear();
  m_cscSimHit_r->clear();
  m_cscSimHit_station->clear();
  m_cscSimHit_matchTp->clear();

  m_gemSimHit_phi->clear();
  m_gemSimHit_eta->clear();
  m_gemSimHit_z->clear();
  m_gemSimHit_r->clear();
  m_gemSimHit_station->clear();
  m_gemSimHit_matchTp->clear();

  m_matchmuon_pt->clear();
  m_matchmuon_eta->clear();
  m_matchmuon_phi->clear();
  m_matchmuon_charge->clear();
  m_matchmuon_type->clear();
  m_matchmuon_quality->clear();

  m_allCscStubsLCT_phi->clear();
  m_allCscStubsLCT_eta->clear();
  m_allCscStubsLCT_z->clear();
  m_allCscStubsLCT_r->clear();
  m_allCscStubsLCT_bend->clear();
  m_allCscStubsLCT_pattern->clear();
  m_allCscStubsLCT_quality->clear();
  m_allCscStubsLCT_detId->clear();
  m_allCscStubsLCT_keywire->clear();
  m_allCscStubsLCT_strip->clear();
  m_allCscStubsLCT_valid->clear();
  m_allCscStubsLCT_type->clear();

  m_allCscStubsALCT_detId->clear();
  m_allCscStubsALCT_keywire->clear();
  m_allCscStubsALCT_hit->clear();
  m_allCscStubsALCT_position->clear();
  m_allCscStubsALCT_valid->clear();

  m_allCscStubsCLCT_detId->clear();
  m_allCscStubsCLCT_strip->clear();
  m_allCscStubsCLCT_hit->clear();
  m_allCscStubsCLCT_position->clear();
  m_allCscStubsCLCT_valid->clear();

  m_allALCT_detId->clear();
  m_allALCT_keywire->clear();
  m_allALCT_hit->clear();
  m_allALCT_position->clear();
  m_allALCT_valid->clear();

  m_allCLCT_detId->clear();
  m_allCLCT_strip->clear();
  m_allCLCT_hit->clear();
  m_allCLCT_position->clear();
  m_allCLCT_valid->clear();

  m_allGemDigi_phi->clear();
  m_allGemDigi_eta->clear();
  m_allGemDigi_z->clear();
  m_allGemDigi_r->clear();

  m_matchCscStubsLCT_phi->clear();
  m_matchCscStubsLCT_eta->clear();
  m_matchCscStubsLCT_z->clear();
  m_matchCscStubsLCT_r->clear();
  m_matchCscStubsLCT_bend->clear();
  m_matchCscStubsLCT_pattern->clear();
  m_matchCscStubsLCT_matchTp->clear();
  m_matchCscStubsLCT_quality->clear();
  m_matchCscStubsLCT_detId->clear();
  m_matchCscStubsLCT_keywire->clear();
  m_matchCscStubsLCT_strip->clear();
  m_matchCscStubsLCT_valid->clear();
  m_matchCscStubsLCT_type->clear();


  m_matchCscStubsALCT_detId->clear();
  m_matchCscStubsALCT_keywire->clear();
  m_matchCscStubsALCT_hit->clear();
  m_matchCscStubsALCT_position->clear();
  m_matchCscStubsALCT_valid->clear();

  m_matchCscStubsCLCT_detId->clear();
  m_matchCscStubsCLCT_strip->clear();
  m_matchCscStubsCLCT_hit->clear();
  m_matchCscStubsCLCT_position->clear();
  m_matchCscStubsCLCT_valid->clear();

  m_matchGemDigi_phi->clear();
  m_matchGemDigi_eta->clear();
  m_matchGemDigi_z->clear();
  m_matchGemDigi_r->clear();
  m_matchGemDigi_matchTp->clear();

  if (DebugMode) cout << "Finished branch initialization" << endl;

  edm::Handle< std::vector< TrackingParticle > > TrackingParticleHandle;
  iEvent.getByToken(TrackingParticleToken_, TrackingParticleHandle);

  edm::ESHandle<TrackerGeometry> geometryHandle;
  iSetup.get<TrackerDigiGeometryRecord>().get(geometryHandle);

  edm::ESHandle<TrackerTopology> tTopoHandle;
  iSetup.get<TrackerTopologyRcd>().get(tTopoHandle);

  edm::ESHandle<TrackerGeometry> tGeomHandle;
  iSetup.get<TrackerDigiGeometryRecord>().get(tGeomHandle);
  match->init(iEvent,iSetup);

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  iEvent.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer & sim_vert = *sim_vertices.product();

  int tp_index = 0;
  std::vector< TrackingParticle >::const_iterator iterTP;
  if (DebugMode) cout << "Started TP iteration" << endl;
  for (iterTP = TrackingParticleHandle->begin(); iterTP != TrackingParticleHandle->end(); ++iterTP) {
    edm::Ptr< TrackingParticle > tp_ptr(TrackingParticleHandle, tp_index);

    int tmp_eventid = iterTP->eventId().event();
    if (MyProcess != 1 && tmp_eventid > 0) continue; //only care about tracking particles from the primary interaction (except for MyProcess==1, i.e. looking at all TPs)

    float tmp_tp_pt  = iterTP->pt();
    float tmp_tp_eta = iterTP->eta();
    float tmp_tp_phi = iterTP->phi();
    float tmp_tp_vz  = iterTP->vz();
    float tmp_tp_vx  = iterTP->vx();
    float tmp_tp_vy  = iterTP->vy();
    int tmp_tp_pdgid = iterTP->pdgId();
    float tmp_tp_z0_prod = tmp_tp_vz;
    float tmp_tp_d0_prod = -tmp_tp_vx*sin(tmp_tp_phi) + tmp_tp_vy*cos(tmp_tp_phi);

    if (MyProcess==13 && abs(tmp_tp_pdgid) != 13) continue;
    if (MyProcess==11 && abs(tmp_tp_pdgid) != 11) continue;
    if ((MyProcess==6 || MyProcess==15 || MyProcess==211) && abs(tmp_tp_pdgid) != 211) continue;

    if (tmp_tp_pt < TP_minPt) continue;
    if (fabs(tmp_tp_eta) > TP_maxEta) continue;

    // Calculation of d0 and z0

    float tmp_tp_t = tan(2.0*atan(1.0)-2.0*atan(exp(-tmp_tp_eta)));

    float delx = -tmp_tp_vx;
    float dely = -tmp_tp_vy;

    float A = 0.01*0.5696;
    float Kmagnitude = A / tmp_tp_pt;

    float tmp_tp_charge = tp_ptr->charge();
    float K = Kmagnitude * tmp_tp_charge;
    float d = 0;

    float tmp_tp_x0p = delx - (d + 1./(2. * K)*sin(tmp_tp_phi));
    float tmp_tp_y0p = dely + (d + 1./(2. * K)*cos(tmp_tp_phi));
    float tmp_tp_rp = sqrt(tmp_tp_x0p*tmp_tp_x0p + tmp_tp_y0p*tmp_tp_y0p);
    float tmp_tp_d0 = tmp_tp_charge*tmp_tp_rp - (1. / (2. * K));

    tmp_tp_d0 = tmp_tp_d0*(-1); //fix d0 sign

    static double pi = 4.0*atan(1.0);
    float delphi = tmp_tp_phi-atan2(-K*tmp_tp_x0p,K*tmp_tp_y0p);
    if (delphi<-pi) delphi+=2.0*pi;
    if (delphi>pi) delphi-=2.0*pi;
    float tmp_tp_z0 = tmp_tp_vz+tmp_tp_t*delphi/(2.0*K);
    // ----------------------------------------------------------------------------------------------

    if (fabs(tmp_tp_z0) > TP_maxZ0) continue;

    float dxy = sqrt(tmp_tp_vx*tmp_tp_vx + tmp_tp_vy*tmp_tp_vy);
    float tmp_tp_dxy = dxy;
    if (MyProcess==6 && (dxy > 1.0)) continue;

    m_tp_pt->push_back(tmp_tp_pt);
    m_tp_eta->push_back(tmp_tp_eta);
    m_tp_phi->push_back(tmp_tp_phi);
    m_tp_dxy->push_back(tmp_tp_dxy);
    m_tp_z0->push_back(tmp_tp_z0);
    m_tp_d0->push_back(tmp_tp_d0);
    m_tp_z0_prod->push_back(tmp_tp_z0_prod);
    m_tp_d0_prod->push_back(tmp_tp_d0_prod);
    m_tp_pdgid->push_back(tmp_tp_pdgid);
    m_tp_eventid->push_back(tmp_eventid);
    m_tp_charge->push_back(tmp_tp_charge);

    if (DebugMode) cout << "  Finished TP information and started matcher" <<endl;

    const SimTrack& t(tp_ptr->g4Tracks()[0]);
    if(abs(t.type())==13){
      const SimVertex v = (t.vertIndex() < int(sim_vert.size())) ? sim_vert[t.vertIndex()] : SimVertex();


      match->match(t, v);

      auto cscsimhits = match->cscSimHits();
      auto gemsimhits = match->gemSimHits();

      for (int istation = 1; istation < 5; ++istation) {
        const auto& cscIds = cscsimhits->chamberIdsStation(istation);
        for (const auto& p1 : cscIds) {
          const auto& hits = cscsimhits->hitsInChamber(p1);
          for (auto& hit : hits) {
            PSimHitContainer hitc;
            hitc.push_back(hit);
            GlobalPoint gp = cscsimhits->simHitsMeanPosition(hitc);
            m_cscSimHit_phi->push_back(gp.phi());
            m_cscSimHit_eta->push_back(gp.eta());
            m_cscSimHit_z->push_back(gp.z());
            m_cscSimHit_r->push_back(gp.perp());
            m_cscSimHit_station->push_back(istation);
            m_cscSimHit_matchTp->push_back(tp_index);
          }
        }
      }

      const auto& gemIds = gemsimhits->detIds();
      for (const auto&p1 :gemIds) {
        GEMDetId id1(p1);
        int istation = id1.station();
        const auto& hits = gemsimhits->hitsInDetId(p1);
        for (auto& hit : hits) {
          PSimHitContainer hitc;
          hitc.push_back(hit);
          GlobalPoint gp = gemsimhits->simHitsMeanPosition(hits);
          m_gemSimHit_phi->push_back(gp.phi());
          m_gemSimHit_eta->push_back(gp.eta());
          m_gemSimHit_z->push_back(gp.z());
          m_gemSimHit_r->push_back(gp.perp());
          m_gemSimHit_station->push_back(istation);
          m_gemSimHit_matchTp->push_back(tp_index);
        }
      }

      auto muonCandidate = match->l1Muons()->emtfCand();
      if(muonCandidate){
        //std::cout<<"found match, extract information"<<std::endl;
        m_matchmuon_pt->push_back(muonCandidate->pt());
        m_matchmuon_eta->push_back(muonCandidate->eta());
        m_matchmuon_phi->push_back(muonCandidate->phi());
        m_matchmuon_charge->push_back(muonCandidate->charge());
        m_matchmuon_quality->push_back(muonCandidate->quality());
        int type=-1;
        m_matchmuon_type->push_back(type);
      }
      else{
        m_matchmuon_pt->push_back(-999.);
        m_matchmuon_eta->push_back(-999.);
        m_matchmuon_phi->push_back(-999.);
        m_matchmuon_charge->push_back(-999);
        m_matchmuon_type->push_back(-999);
        m_matchmuon_quality->push_back(-999);
      }

      //CSCStubMatcher
      auto cscStubs = match->cscStubs();
      for (int detid_int : cscStubs->chamberIdsLCT(0)) {
        CSCDetId detid_(detid_int);
        int digi_index = 0;
        bool doprinta = Print_matchCscStubs && Print_ALCT;
        bool doprintc = Print_matchCscStubs && Print_CLCT;
        for (auto digi_ : cscStubs->lctsInChamber(detid_) ){
          auto gp = cscStubs->getGlobalPosition(detid_int,digi_);
          m_matchCscStubsLCT_phi->push_back(gp.phi());
          m_matchCscStubsLCT_eta->push_back(gp.eta());
          m_matchCscStubsLCT_z->push_back(gp.z());
          m_matchCscStubsLCT_r->push_back(gp.perp());
          m_matchCscStubsLCT_bend->push_back(digi_.getBend());
          m_matchCscStubsLCT_pattern->push_back(digi_.getPattern());
          m_matchCscStubsLCT_matchTp->push_back(tp_index);
          m_matchCscStubsLCT_quality->push_back(digi_.getQuality());
          m_matchCscStubsLCT_detId->push_back(detid_.rawId());
          m_matchCscStubsLCT_keywire->push_back(digi_.getKeyWG());
          m_matchCscStubsLCT_strip->push_back(digi_.getStrip());
          m_matchCscStubsLCT_valid->push_back(digi_.isValid());
          m_matchCscStubsLCT_type->push_back(digi_.getType());
          if (Print_matchCscStubs) cout << "detid_int = " <<detid_int<<", detid = " << int(detid_) << ", rawId = " << detid_.rawId() << endl;

          const auto& alctDigi = digi_.getALCT();
          std::vector< std::vector<unsigned short> > alcthits = alctDigi.getHits();
          if (doprinta) cout << "For matchCscStubsALCTs; DetId: "<< detid_.rawId() <<", Digi Index: " << digi_index << ", keywire: "<< alctDigi.getKeyWG()<<" , lctDigiWire = "<<digi_.getKeyWG()<<endl;
          if (alctDigi.getKeyWG() != digi_.getKeyWG() && doprinta) cout << "Inconsistent keywire: alctDigiWire = "<< alctDigi.getKeyWG() <<" , lctDigiWire = "<<digi_.getKeyWG()<<endl;
          SaveHitMatrix(alcthits, m_matchCscStubsALCT_hit, m_matchCscStubsALCT_position,doprinta,false);
          m_matchCscStubsALCT_detId->push_back(detid_.rawId());
          m_matchCscStubsALCT_keywire->push_back(alctDigi.getKeyWG());
          m_matchCscStubsALCT_valid->push_back(alctDigi.isValid());

          const auto& clctDigi = digi_.getCLCT();
          std::vector< std::vector<unsigned short> > clcthits = clctDigi.getHits();
          if (doprintc) cout << "For matchCscStubsCLCTs; DetId: "<< detid_.rawId() <<", Digi Index: " << digi_index << ", strip: "<< clctDigi.getStrip() <<" , lctDigiStrip = "<< digi_.getStrip()<<endl;
          if (clctDigi.getStrip() != digi_.getStrip() && doprintc) cout << "Inconsistent strip: clctDigiStrip = "<< clctDigi.getStrip() <<" , lctDigiStrip = "<< digi_.getStrip() <<endl;
          SaveHitMatrix(clcthits, m_matchCscStubsCLCT_hit, m_matchCscStubsCLCT_position,doprintc,true);
          m_matchCscStubsCLCT_detId->push_back(detid_.rawId());
          m_matchCscStubsCLCT_strip->push_back(clctDigi.getStrip());
          m_matchCscStubsCLCT_valid->push_back(clctDigi.getStrip());

        }
      }

      auto gemDigis_ = match->gemDigis();
      const auto& detidsDigi = gemDigis_->detIdsDigi();
      for (const auto& id : detidsDigi) {
        for (auto gemdigi : gemDigis_->digisInDetId(id) ){
          auto gp = gemDigis_->getGlobalPointDigi(id, gemdigi);
          m_matchGemDigi_phi->push_back(gp.phi());
          m_matchGemDigi_eta->push_back(gp.eta());
          m_matchGemDigi_z->push_back(gp.z());
          m_matchGemDigi_r->push_back(gp.perp());
          m_matchGemDigi_matchTp->push_back(tp_index);
        }
      }
    } // End of Muon Loop

    else{
      m_matchmuon_pt->push_back(-999.);
      m_matchmuon_eta->push_back(-999.);
      m_matchmuon_phi->push_back(-999.);
      m_matchmuon_charge->push_back(-999);
      m_matchmuon_type->push_back(-999);
      m_matchmuon_quality->push_back(-999);
    }

    tp_index++;
  } // End of Tracking Particle Loop

  if (DebugMode) cout << "Finished TP Iteration" << endl;

  Handle< BXVector<l1t::RegionalMuonCand> > emtfs;
  Handle< BXVector<l1t::RegionalMuonCand> > omtfs;
  Handle< BXVector<l1t::RegionalMuonCand> > bmtfs;

  iEvent.getByToken(m_emtfToken,emtfs);
  iEvent.getByToken(m_omtfToken,omtfs);
  iEvent.getByToken(m_bmtfToken,bmtfs);

  int nEMTF=0;
  for (auto it = emtfs->begin(0); it != emtfs->end(0); it++){
    m_EMTF_muon_eta->push_back(it->hwEta()*0.010875);
    int globPhi=l1t::MicroGMTConfiguration::calcGlobalPhi(it->hwPhi(), it->trackFinderType(), it->processor());
    m_EMTF_muon_phi->push_back(globPhi*2*M_PI/576.);
    m_EMTF_muon_pt->push_back(it->hwPt()*0.5);
    if(!it->hwSignValid()) m_EMTF_muon_c->push_back(0);
    else{
      if(it->hwSign())   m_EMTF_muon_c->push_back(-1);
      else 		   m_EMTF_muon_c->push_back(1);
    }
    ++nEMTF;
  }
  m_EMTF_muon_n->push_back(nEMTF);

  int nOMTF=0;
  for (auto it = omtfs->begin(0); it != omtfs->end(0); it++){
    m_OMTF_muon_eta->push_back(it->hwEta()*0.010875);
    m_OMTF_muon_phi->push_back(l1t::MicroGMTConfiguration::calcGlobalPhi(it->hwPhi(), it->trackFinderType(), it->processor())*2*M_PI/576.);
    m_OMTF_muon_pt->push_back(it->hwPt()*0.5);
    if(!it->hwSignValid()) m_OMTF_muon_c->push_back(0);
    else{
      if(it->hwSign())   m_OMTF_muon_c->push_back(-1);
      else 		   m_OMTF_muon_c->push_back(1);
    }
    ++nOMTF;
  }
  m_OMTF_muon_n->push_back(nOMTF);

  int nBMTF=0;
  for (auto it = bmtfs->begin(0); it != bmtfs->end(0); it++){
    m_BMTF_muon_eta->push_back(it->hwEta()*0.010875);
    m_BMTF_muon_phi->push_back(l1t::MicroGMTConfiguration::calcGlobalPhi(it->hwPhi(), it->trackFinderType(), it->processor())*2*M_PI/576.);
    m_BMTF_muon_pt->push_back(it->hwPt()*0.5);
    if(!it->hwSignValid()) m_BMTF_muon_c->push_back(0);
    else{
      if(it->hwSign())   m_BMTF_muon_c->push_back(-1);
      else 		   m_BMTF_muon_c->push_back(1);
    }
    ++nBMTF;
  }
  m_BMTF_muon_n->push_back(nBMTF);

  if (DebugMode) cout << "Finished regional Muons started allCscStubs" << endl;

  edm::Handle<CSCCorrelatedLCTDigiCollection> lctsH_;
  iEvent.getByToken(lctToken_, lctsH_);
  const CSCCorrelatedLCTDigiCollection& lcts = *lctsH_.product();
  for (auto it = lcts.begin(); it != lcts.end(); ++it) {
    const auto& digivec = (*it).second;
    const CSCDetId& detid = (*it).first;
    int digi_index = 0;
    bool doprinta = Print_allCscStubs && Print_ALCT;
    bool doprintc = Print_allCscStubs && Print_CLCT;
    for (auto itdigi = digivec.first; itdigi != digivec.second; ++itdigi) {
      auto gp = match->cscStubs()->getGlobalPosition(detid.rawId(), *itdigi);
      m_allCscStubsLCT_phi->push_back(gp.phi());
      m_allCscStubsLCT_eta->push_back(gp.eta());
      m_allCscStubsLCT_z->push_back(gp.z());
      m_allCscStubsLCT_r->push_back(gp.perp());
      m_allCscStubsLCT_bend->push_back((*itdigi).getBend());
      m_allCscStubsLCT_pattern->push_back((*itdigi).getPattern());
      m_allCscStubsLCT_quality->push_back((*itdigi).getQuality());
      m_allCscStubsLCT_detId->push_back(detid.rawId());
      m_allCscStubsLCT_keywire->push_back((*itdigi).getKeyWG());
      m_allCscStubsLCT_strip->push_back((*itdigi).getStrip());
      m_allCscStubsLCT_valid->push_back((*itdigi).isValid());
      m_allCscStubsLCT_type->push_back((*itdigi).getType());
      // allCscStubsALCTs
      const auto& alctDigi = (*itdigi).getALCT();
      std::vector< std::vector<unsigned short> > alcthits = alctDigi.getHits();
      if (doprinta) cout << "For allCscStubsALCTs; DetId: "<< detid.rawId() <<", Digi Index: " << digi_index << ", keywire: "<< alctDigi.getKeyWG()<<" , lctDigiWire = "<<(*itdigi).getKeyWG() << endl;
      if (alctDigi.getKeyWG() != (*itdigi).getKeyWG() && doprinta) cout << "Inconsistence keywire: alctDigiWire = "<< alctDigi.getKeyWG() <<" , lctDigiWire = "<<(*itdigi).getKeyWG()<<endl;
      SaveHitMatrix(alcthits, m_allCscStubsALCT_hit, m_allCscStubsALCT_position,doprinta,false);
      m_allCscStubsALCT_detId->push_back(detid.rawId());
      m_allCscStubsALCT_keywire->push_back(alctDigi.getKeyWG());
      m_allCscStubsALCT_valid->push_back(alctDigi.isValid());

      // allCscStubsCLCTs
      const auto& clctDigi = (*itdigi).getCLCT();
      std::vector< std::vector<unsigned short> > clcthits = clctDigi.getHits();
      if (doprintc) cout << "For allCscStubsCLCTs; DetId: "<< detid.rawId() <<", Digi Index:" << digi_index << ", strip: "<< clctDigi.getStrip() <<" , lctDigiStrip = "<< (*itdigi).getStrip()<<endl;
      if (clctDigi.getStrip() != (*itdigi).getStrip() && doprintc) cout << "Inconsistence strip: clctDigiStrip = "<< clctDigi.getStrip() <<" , lctDigiStrip = "<< (*itdigi).getStrip() <<endl;
      SaveHitMatrix(clcthits, m_allCscStubsCLCT_hit, m_allCscStubsCLCT_position,doprintc,true);
      m_allCscStubsCLCT_detId->push_back(detid.rawId());
      m_allCscStubsCLCT_strip->push_back(clctDigi.getStrip());
      m_allCscStubsCLCT_valid->push_back(clctDigi.isValid());

      ++digi_index;
    }
  }

  if (DebugMode) cout << "Finished allCscStubs, started allA/CLCT" << endl;

  bool multihit = false;
  // allALCTs
  int digi_index = 0;
  edm::Handle<CSCALCTDigiCollection> alctsH_;
  iEvent.getByToken(alctToken_, alctsH_);
  const CSCALCTDigiCollection& alcts = *alctsH_.product();
  for (auto it = alcts.begin(); it != alcts.end(); ++it) {
    const auto& digivec = (*it).second;
    const auto& detid = (*it).first;
    for (auto itdigi = digivec.first; itdigi != digivec.second; ++itdigi) {
      std::vector< std::vector<unsigned short> > alcthits = ((*itdigi).getHits());
      if (Print_all) cout << "For allALCTs; DetId: "<< detid.rawId() <<", Digi Index:" << digi_index << ", keywire: "<< (*itdigi).getKeyWG()<< endl;
      int alctmultihit = SaveHitMatrix(alcthits, m_allALCT_hit, m_allALCT_position,Print_all&&Print_ALCT,false);
      if (alctmultihit) multihit = true;
      m_allALCT_detId->push_back(detid.rawId());
      m_allALCT_keywire->push_back((*itdigi).getKeyWG());
      m_allALCT_valid->push_back((*itdigi).isValid());
      ++digi_index;
    }
  }

  // allCLCTs
  digi_index = 0;
  edm::Handle<CSCCLCTDigiCollection> clctsH_;
  iEvent.getByToken(clctToken_, clctsH_);
  const CSCCLCTDigiCollection& clcts = *clctsH_.product();
  for (auto it = clcts.begin(); it != clcts.end(); ++it) {
    const auto& digivec = (*it).second;
    const auto& detid = (*it).first;
    for (auto itdigi = digivec.first; itdigi != digivec.second; ++itdigi) {
      std::vector< std::vector<unsigned short> > clcthits = ((*itdigi).getHits());
      if (Print_all) cout << "For allCLCTs; DetId: "<< detid.rawId() <<", Digi Index:" << digi_index<< ", strip: "<< (*itdigi).getStrip() << endl;
      int clctmultihit = SaveHitMatrix(clcthits, m_allCLCT_hit, m_allCLCT_position,Print_all&&Print_CLCT,true);
      if (clctmultihit) multihit = true;
      m_allCLCT_detId->push_back(detid.rawId());
      m_allCLCT_strip->push_back((*itdigi).getStrip());
      m_allCLCT_valid->push_back((*itdigi).isValid());
      ++digi_index;
    }
  }
  if (multihit) nEventMultiHitLayer++;
  // if (floor(double(m_allCLCT_hit->size()) / 6.0 ) != m_allCLCT_detId->size()) {
  //   throw std::runtime_error("Hit size mismatch Digi size");
  // }

  // 0 for allA/CLCT, 1 for allCscStubsA/CLCT, 2 for matchCscStubsA/CLCT
  if (Print_all) PrintHits(0);
  if (Print_allCscStubs) PrintHits(1);
  if (Print_matchCscStubs) PrintHits(2);
  // PrintHits(0);
  // PrintHits(1);
  // PrintHits(2);

  // All GEMDigis
  edm::Handle<GEMDigiCollection> gemDigisH_;
  iEvent.getByToken(gemDigiToken_,gemDigisH_);
  const GEMDigiCollection& gems = *gemDigisH_.product();

  for (auto it = gems.begin(); it != gems.end(); ++it) {
    const auto& digivec = (*it).second;
    const GEMDetId& detid = (*it).first;
    for (auto itdigi = digivec.first; itdigi != digivec.second; ++itdigi) {
      auto gp = match->gemDigis()->getGlobalPointDigi(detid.rawId(), *itdigi);
      m_allGemDigi_phi->push_back(gp.phi());
      m_allGemDigi_eta->push_back(gp.eta());
      m_allGemDigi_z->push_back(gp.z());
      m_allGemDigi_r->push_back(gp.perp());
    }
  }

  eventTree->Fill();
} // End of analyze


void NtupleMaker::PrintHits(int iset, int idigi) {
  vector<vector<int> > SavedallCscStubs{*m_allCscStubsALCT_hit, *m_allCscStubsALCT_position, *m_allCscStubsALCT_detId, *m_allCscStubsALCT_keywire, *m_allCscStubsCLCT_hit, *m_allCscStubsCLCT_position, *m_allCscStubsCLCT_detId, *m_allCscStubsCLCT_strip, *m_allCscStubsLCT_detId, *m_allCscStubsLCT_keywire, *m_allCscStubsLCT_strip};
  vector<vector<int> > SavedmatchCscStubs{*m_matchCscStubsALCT_hit, *m_matchCscStubsALCT_position, *m_matchCscStubsALCT_detId, *m_matchCscStubsALCT_keywire, *m_matchCscStubsCLCT_hit, *m_matchCscStubsCLCT_position, *m_matchCscStubsCLCT_detId, *m_matchCscStubsCLCT_strip, *m_matchCscStubsLCT_detId, *m_matchCscStubsLCT_keywire, *m_matchCscStubsLCT_strip};
  vector<vector<int> > Savedall{*m_allALCT_hit, *m_allALCT_position, *m_allALCT_detId, *m_allALCT_keywire, *m_allCLCT_hit, *m_allCLCT_position, *m_allCLCT_detId, *m_allCLCT_strip};
  vector<string> printtitle{"hits","positions","detids","keywires","hits","positions","detids","strips","LCT Digi detids","LCT Digi keywires","LCT Digi strips"};
  vector<vector<int> > printinfo;
  cout <<endl;
  if (iset == 0) {
    cout << "Saved info in allALCT and allCLCT" <<endl;
    printinfo = Savedall;
  }
  else if (iset == 1){
    cout << "Saved info in allCscStubsALCT and allCscStubsCLCT" <<endl;
    printinfo = SavedallCscStubs;
  }
  else if (iset == 2){
    cout << "Saved info in matchCscStubsALCT and matchCscStubsCLCT" <<endl;
    printinfo = SavedmatchCscStubs;
  }

  if (idigi == -1) {
    for (unsigned iprint = 0; iprint < printinfo.size(); ++iprint) {
      if ((!Print_ALCT) && iprint < 4) continue;
      if ((!Print_CLCT) && iprint >= 4 && iprint < 8) continue;
      if (iprint == 0) cout << "Saved ALCT hits format:" <<endl;
      if (iprint == 4) cout << "Saved CLCT hits format:" <<endl;
      if (iprint == 8) cout << "Saved LCT format:" <<endl;
      cout << printtitle.at(iprint) << ": {";
      vector<int>& vals = printinfo.at(iprint);
      bool printbracket = false;
      if (printtitle.at(iprint) == "hits" || printtitle.at(iprint) == "positions") printbracket = true;
      for (unsigned ival = 0; ival < vals.size(); ++ival) {
        if (ival % 6 == 0 && printbracket) cout << "(";
        cout << vals.at(ival);
        if (ival % 6 == 5 && printbracket) cout << ")";
        if (ival != vals.size() - 1) cout <<", ";
      }
      cout <<"}"<<endl;
    }
  }

}

int NtupleMaker::SaveHitMatrix(std::vector< std::vector<unsigned short> > hits, std::vector<int>* b_hit, std::vector<int>* b_pos, bool doprint, bool isclct) {
  std::vector<int> tmp_hit;
  std::vector<int> tmp_pos;
  int multihit = 0; // number of layers that have more than 1 hits
  if (hits.size() != 6) {
    cout << "nLayer != 6" <<endl;
    int ExceptionCode = -3;
    for (unsigned itlayer = 0; itlayer < 6; ++itlayer) {
      b_hit->push_back(ExceptionCode);
      b_pos->push_back(ExceptionCode);
      if (doprint) {
        tmp_hit.push_back(ExceptionCode);
        tmp_pos.push_back(ExceptionCode);
      }
    }
    return ExceptionCode;
  }

  for (unsigned itlayer = 0; itlayer < hits.size() ; ++itlayer) {
    if (doprint) cout << "layer: " << itlayer << " : ";
    int ncount = 0;
    bool haszero = false;
    bool printzero = false;
    for (unsigned itpos = 0; itpos < hits.at(itlayer).size(); ++itpos) {
      int hitval = hits.at(itlayer).at(itpos);
      if (doprint) cout << " " << hitval << ",";
      if (hitval == 0 && isclct) haszero = true;
      if (hitval != 65535 && hitval != 0) {
        if (ncount == 0) {
          b_hit->push_back(hitval);
          b_pos->push_back(itpos);
          if (doprint) {
            tmp_hit.push_back(hitval);
            tmp_pos.push_back(itpos);
          }
        }
        else {
          int ExceptionCode = -2;
          cout << " Layer with more than 1 hits" <<endl;
          b_hit->back() = ExceptionCode;
          b_pos->back() = ExceptionCode;
          if (doprint) {
            tmp_hit.back() = ExceptionCode;
            tmp_pos.back() = ExceptionCode;
          }
        }
        ncount++;
      }
    }
    if (haszero && printzero) cout << "Emergency!!!!!! CLCT hits contains 0!!!!!!";
    if (ncount > 1) ++multihit;
    if (ncount == 0) {
      b_hit->push_back(-1);
      b_pos->push_back(-1);
      if (doprint) {
        tmp_hit.push_back(-1);
        tmp_pos.push_back(-1);
      }
    }
    if (doprint) cout << endl;
  }

  if (doprint) {
    cout << "Saved Hit for this Digi:";
    for (unsigned iv = 0; iv < tmp_hit.size(); ++ iv) {
      cout <<" "<<tmp_hit.at(iv)<<",";
    }
    if (tmp_hit.size() != 6) cout << "This Digi does not has 6 layers!!!";
    cout <<endl;
    cout << "Saved Position for this Digi:";
    for (unsigned iv = 0; iv < tmp_pos.size(); ++ iv) {
      cout <<" "<<tmp_pos.at(iv)<<",";
    }
    if (tmp_hit.size() != 6) cout << "This Digi does not has 6 layers!!!";
    cout <<endl;
  }
  return multihit;
}

std::vector<int> NtupleMaker::IntsToBinary(int n) {
  std::vector<int> binary_;
  if ( n / 2 != 0) binary_ = IntsToBinary(n/2);
  binary_.push_back(n%2);
  return binary_;
}


DEFINE_FWK_MODULE(NtupleMaker);