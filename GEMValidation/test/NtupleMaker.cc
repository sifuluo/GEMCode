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

using namespace std;
using namespace edm;

class NtupleMaker : public edm::EDAnalyzer {
public:
  explicit NtupleMaker(const edm::ParameterSet& iConfig);
  virtual ~NtupleMaker();

  virtual void beginJob();
  virtual void endJob();
  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);

protected:

private:
  // ParameterSet passed from python configuration
  edm::ParameterSet config;

  int MyProcess;
  bool DebugMode;
  double TP_minPt;
  double TP_maxEta;
  double TP_maxZ0;

  edm::InputTag TrackingParticleInputTag;

  std::string getFloatPointDataWord(const l1t::RegionalMuonCand& l1mu) const;
  std::string getGlobalPhi(const l1t::RegionalMuonCand& l1mu) const;

  edm::EDGetToken m_emtfToken;
  edm::EDGetToken m_bmtfToken;
  edm::EDGetToken m_omtfToken;

  edm::EDGetTokenT< std::vector< TrackingParticle > > TrackingParticleToken_;
  edm::EDGetTokenT<edm::SimVertexContainer> simVertexInput_;

  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lctToken_;

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

  std::vector<float>* m_matchmuon_pt;
  std::vector<float>* m_matchmuon_eta;
  std::vector<float>* m_matchmuon_phi;
  std::vector<int>*   m_matchmuon_charge;
  std::vector<int>*   m_matchmuon_type;
  std::vector<int>*   m_matchmuon_quality;

  std::vector<float>* m_AllcscStubsLCT_phi;
  std::vector<float>* m_AllcscStubsLCT_eta;
  std::vector<float>* m_AllcscStubsLCT_z;
  std::vector<bool>*  m_AllcscStubsLCT_matched;

  //CSCStubs
  std::vector<float>* m_cscStubsLCT_phi;
  std::vector<float>* m_cscStubsLCT_eta;
  std::vector<float>* m_cscStubsLCT_z;
  std::vector<bool>*  m_cscStubsLCT_matched;

  // GEMDigi Variables
  std::vector<float>* m_gemDigi_phi;
  std::vector<float>* m_gemDigi_eta;
  std::vector<float>* m_gemDigi_z;
  std::vector<float>* m_gemDigi_xx_err;
  std::vector<float>* m_gemDigi_xy_err;
  std::vector<float>* m_gemDigi_yy_err;

  std::unique_ptr<MatcherManager> match;

};


NtupleMaker::NtupleMaker(edm::ParameterSet const& iConfig) :
config(iConfig)
{
  MyProcess = iConfig.getParameter< int >("MyProcess");
  DebugMode        = iConfig.getParameter< bool >("DebugMode");
  TP_minPt         = iConfig.getParameter< double >("TP_minPt");
  TP_maxEta        = iConfig.getParameter< double >("TP_maxEta");
  TP_maxZ0         = iConfig.getParameter< double >("TP_maxZ0");
  TrackingParticleInputTag = iConfig.getParameter<edm::InputTag>("TrackingParticleInputTag");

  TrackingParticleToken_ = consumes< std::vector< TrackingParticle > >(TrackingParticleInputTag);

  m_emtfToken = consumes<l1t::RegionalMuonCandBxCollection>(edm::InputTag("simEmtfDigis","EMTF"));
  m_bmtfToken = consumes<l1t::RegionalMuonCandBxCollection>(edm::InputTag("gmtStage2Digis","BMTF"));
  m_omtfToken = consumes<l1t::RegionalMuonCandBxCollection>(edm::InputTag("gmtStage2Digis","OMTF"));

  const auto& simVertex = iConfig.getParameter<edm::ParameterSet>("simVertex");
  simVertexInput_ = consumes<edm::SimVertexContainer>(simVertex.getParameter<edm::InputTag>("inputTag"));

  const auto& cscLCT = iConfig.getParameter<edm::ParameterSet>("cscLCT");
  lctToken_ = consumes<CSCCorrelatedLCTDigiCollection>(cscLCT.getParameter<edm::InputTag>("inputTag"));

  match.reset(new MatcherManager(iConfig, consumesCollector()));
}

NtupleMaker::~NtupleMaker()
{
}

void NtupleMaker::endJob()
{
  cerr << "NtupleMaker::endJob" << endl;
}

void NtupleMaker::beginJob()
{
  cerr << "NtupleMaker::beginJob" << endl;

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

  m_matchmuon_pt     = new std::vector<float>;
  m_matchmuon_eta    = new std::vector<float>;
  m_matchmuon_phi    = new std::vector<float>;
  m_matchmuon_charge = new std::vector<int>;
  m_matchmuon_type   = new std::vector<int>;
  m_matchmuon_quality= new std::vector<int>;

  m_AllcscStubsLCT_phi = new std::vector<float>;
  m_AllcscStubsLCT_eta = new std::vector<float>;
  m_AllcscStubsLCT_z = new std::vector<float>;
  m_AllcscStubsLCT_matched = new std::vector<bool>;

  m_cscStubsLCT_phi = new std::vector<float>;
  m_cscStubsLCT_eta = new std::vector<float>;
  m_cscStubsLCT_z = new std::vector<float>;
  m_cscStubsLCT_matched = new std::vector<bool>;

  m_gemDigi_phi = new std::vector<float>;
  m_gemDigi_eta = new std::vector<float>;
  m_gemDigi_z = new std::vector<float>;
  m_gemDigi_xx_err = new std::vector<float>;
  m_gemDigi_xy_err = new std::vector<float>;
  m_gemDigi_yy_err = new std::vector<float>;

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

  eventTree->Branch("matchmuon_pt", &m_matchmuon_pt);
  eventTree->Branch("matchmuon_eta", &m_matchmuon_eta);
  eventTree->Branch("matchmuon_phi", &m_matchmuon_phi);
  eventTree->Branch("matchmuon_charge",&m_matchmuon_charge);
  eventTree->Branch("matchmuon_type",&m_matchmuon_type);
  eventTree->Branch("matchmuon_quality",&m_matchmuon_quality);

  eventTree->Branch("AllcscStubsLCT_phi", &m_AllcscStubsLCT_phi);
  eventTree->Branch("AllcscStubsLCT_eta", &m_AllcscStubsLCT_eta);
  eventTree->Branch("AllcscStubsLCT_z", &m_AllcscStubsLCT_z);
  eventTree->Branch("AllcscStubsLCT_matched", &m_AllcscStubsLCT_matched);

  // cscStubs
  eventTree->Branch("cscStubsLCT_phi", &m_cscStubsLCT_phi);
  eventTree->Branch("cscStubsLCT_eta", &m_cscStubsLCT_eta);
  eventTree->Branch("cscStubsLCT_z", &m_cscStubsLCT_z);
  eventTree->Branch("cscStubsLCT_matched", &m_cscStubsLCT_matched);

  // GemDigi
  eventTree->Branch("gemDigi_phi", &m_gemDigi_phi);
  eventTree->Branch("gemDigi_eta", &m_gemDigi_eta);
  eventTree->Branch("gemDigi_z", &m_gemDigi_z);
  eventTree->Branch("gemDigi_xx_err", &m_gemDigi_xx_err);
  eventTree->Branch("gemDigi_xy_err", &m_gemDigi_xy_err);
  eventTree->Branch("gemDigi_yy_err", &m_gemDigi_yy_err);

}

void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
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

  m_matchmuon_pt->clear();
  m_matchmuon_eta->clear();
  m_matchmuon_phi->clear();
  m_matchmuon_charge->clear();
  m_matchmuon_type->clear();
  m_matchmuon_quality->clear();

  m_AllcscStubsLCT_phi->clear();
  m_AllcscStubsLCT_eta->clear();
  m_AllcscStubsLCT_z->clear();
  m_AllcscStubsLCT_matched->clear();

  m_cscStubsLCT_phi->clear();
  m_cscStubsLCT_eta->clear();
  m_cscStubsLCT_z->clear();
  m_cscStubsLCT_matched->clear();

  m_gemDigi_phi->clear();
  m_gemDigi_eta->clear();
  m_gemDigi_z->clear();
  m_gemDigi_xx_err->clear();
  m_gemDigi_xy_err->clear();
  m_gemDigi_yy_err->clear();

  edm::Handle< std::vector< TrackingParticle > > TrackingParticleHandle;
  iEvent.getByToken(TrackingParticleToken_, TrackingParticleHandle);

  edm::ESHandle<TrackerGeometry> geometryHandle;
  iSetup.get<TrackerDigiGeometryRecord>().get(geometryHandle);

  edm::ESHandle<TrackerTopology> tTopoHandle;
  iSetup.get<TrackerTopologyRcd>().get(tTopoHandle);

  edm::ESHandle<TrackerGeometry> tGeomHandle;
  iSetup.get<TrackerDigiGeometryRecord>().get(tGeomHandle);

  edm::Handle<edm::SimVertexContainer> sim_vertices;
  iEvent.getByToken(simVertexInput_, sim_vertices);
  const edm::SimVertexContainer & sim_vert = *sim_vertices.product();

  int this_tp = 0;
  std::vector< TrackingParticle >::const_iterator iterTP;
  for (iterTP = TrackingParticleHandle->begin(); iterTP != TrackingParticleHandle->end(); ++iterTP) {
    edm::Ptr< TrackingParticle > tp_ptr(TrackingParticleHandle, this_tp);
    this_tp++;

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


    const SimTrack& t(tp_ptr->g4Tracks()[0]);
    if(abs(t.type())==13){
      const SimVertex v = (t.vertIndex() < int(sim_vert.size())) ? sim_vert[t.vertIndex()] : SimVertex();

      match->init(iEvent,iSetup);
      match->match(t, v);

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
      cout << "chambers:" << cscStubs->chamberIdsAllLCT(0).size()<<endl;
      for (int detid_int : cscStubs->chamberIdsAllLCT(0)) {
        CSCDetId detid_(detid_int);
        for (auto digi_ : cscStubs->allLCTsInChamber(detid_) ){
          auto gp = cscStubs->getGlobalPosition(detid_,digi_);
          m_cscStubsLCT_phi->push_back(gp.phi());
          m_cscStubsLCT_eta->push_back(gp.eta());
          m_cscStubsLCT_z->push_back(gp.z());
          m_cscStubsLCT_matched->push_back(cscStubs->lctInChamber(detid_, digi_));
        }
      }

      auto gemDigi = match->gemDigis();
      const auto& detidsDigi = gemDigi->detIdsDigi();
      for (const auto& id : detidsDigi) {
        for (auto gemdigi : gemDigi->digisInDetId(id) ){
          auto gp = gemDigi->getGlobalPointDigi(id, gemdigi);
          m_gemDigi_phi->push_back(gp.phi());
          m_gemDigi_eta->push_back(gp.eta());
          m_gemDigi_z->push_back(gp.z());
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

  } // End of Tracking Particle Loop

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

  edm::Handle<CSCCorrelatedLCTDigiCollection> lctsH_;
  iEvent.getByToken(lctToken_, lctsH_);
  const CSCCorrelatedLCTDigiCollection& lcts = *lctsH_.product();

  for (auto it = lcts.begin(); it != lcts.end(); ++it) {
    const auto& digivec = (*it).second;
    const auto& detid = (*it).first;
    for (auto itdigi = digivec.first; itdigi != digivec.second; ++itdigi) {
      auto gp = match->cscStubs()->getGlobalPosition(detid, *itdigi);
      m_AllcscStubsLCT_phi->push_back(gp.phi());
      m_AllcscStubsLCT_eta->push_back(gp.eta());
      m_AllcscStubsLCT_z->push_back(gp.z());
    }
  }

  eventTree->Fill();

} // End of analyze


DEFINE_FWK_MODULE(NtupleMaker);
