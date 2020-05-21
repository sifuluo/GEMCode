#ifndef GEMCode_GEMValidation_EMTFTrack_h
#define GEMCode_GEMValidation_EMTFTrack_h

// system include files
#include <memory>
#include <cmath>
#include <vector>
#include <tuple>
#include <iostream>

// user include files
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/L1TMuon/interface/EMTFTrack.h"
#include "DataFormats/L1TMuon/interface/EMTFHit.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/Math/interface/normalizedPhi.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

namespace gem {

class EMTFTrack
{
 public:
  /// constructor
  EMTFTrack(const l1t::EMTFTrack& t);
  /// copy constructor
  EMTFTrack(const gem::EMTFTrack& t);
  /// destructor
  ~EMTFTrack();

  /// collection of hits
  const l1t::EMTFTrack* emtfTrack() const { return &emtfTrack_; }
  const l1t::EMTFHitCollection* emtfHits() const {return &emtfHits_;}

  unsigned int nStubs() const;
  bool hasStub(int station) const;
  bool hasStub(int station, int ring) const;
  l1t::EMTFHit stub(int station, int ring) const;

  double pt() const {return pt_;}
  double eta() const {return eta_;}
  double phi() const {return phi_;}
  int charge() const {return charge_;}
  double phi_local() const {return phi_local_;}
  double dR() const {return dr_;}
  int quality() const {return quality_;}
  int bx() const {return bx_;}

  void setDR(double dr) { dr_ = dr; }

 private:
  l1t::EMTFTrack emtfTrack_;
  l1t::EMTFHitCollection emtfHits_;
  int charge_;
  double phi_;
  double phi_local_;
  double eta_;
  double pt_;
  double dr_;
  int quality_;
  int bx_;
};


class EMTFCand
{
 public:
  /// constructor
  EMTFCand(const l1t::RegionalMuonCand& t);
  /// copy constructor
  EMTFCand(const l1t::Muon& t);
  /// destructor
  ~EMTFCand();

  double pt() const {return pt_;}
  double eta() const {return eta_;}
  double phi() const {return phi_;}
  int charge() const {return charge_;}
  double phi_local() const {return phi_local_;}
  double dR() const {return dr_;}
  int quality() const {return quality_;}
  int bx() const {return bx_;}

  void setDR(double dr) { dr_ = dr; }

 private:
  int charge_;
  double phi_;
  double phi_local_;
  double eta_;
  double pt_;
  double dr_;
  int quality_;
  int bx_;
};

}

#endif
