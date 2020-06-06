#ifndef GEMCode_GEMValidation_DataEmulatorFilter_h
#define GEMCode_GEMValidation_DataEmulatorFilter_h

#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/CSCDigi/interface/CSCALCTDigiCollection.h"
#include "DataFormats/CSCDigi/interface/CSCCLCTDigiCollection.h"
#include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h"
#include "CondFormats/CSCObjects/interface/CSCBadChambers.h"
#include "CondFormats/DataRecord/interface/CSCBadChambersRcd.h"

class DataEmulatorFilter : public edm::EDFilter {
public:
  /// Constructor
  explicit DataEmulatorFilter(const edm::ParameterSet &conf);

  /// Destructor
  ~DataEmulatorFilter() override {};

  /// Does the job
  bool filter(edm::Event &event, const edm::EventSetup &setup) override;

private:

  template <class T>
  int countStubs(const T&) const;

  template <class T>
  bool areSame(const T& X, const T& Y) const;

  // whether to perform check against known "bad chambers" list
  bool checkBadChambers_;

  // Cache conditions data for bad chambers
  const CSCBadChambers *badChambers_;

  edm::InputTag alcts_d_tag_;
  edm::InputTag clcts_d_tag_;
  edm::InputTag lcts_d_tag_;
  edm::InputTag alcts_e_tag_;
  edm::InputTag clcts_e_tag_;
  edm::InputTag lcts_e_tag_;

  edm::EDGetTokenT<CSCALCTDigiCollection> alcts_d_token_;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clcts_d_token_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lcts_d_token_;
  edm::EDGetTokenT<CSCALCTDigiCollection> alcts_e_token_;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clcts_e_token_;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> lcts_e_token_;
};

template <class T>
int DataEmulatorFilter::countStubs(const T& lcts) const
{
  int nValidLcts = 0;
  for (auto detUnitIt = lcts.begin(); detUnitIt != lcts.end(); detUnitIt++) {
    const CSCDetId& id = (*detUnitIt).first;
    // ignore bad chambers
    if (checkBadChambers_ && badChambers_->isInBadChamber(id)) {
      continue;
    }
    const auto& range = (*detUnitIt).second;
    for (auto digiIt = range.first; digiIt != range.second; digiIt++) {
      if ((*digiIt).isValid()) {
        nValidLcts++;
      }
    }
  }
  return nValidLcts;
}

template <class T>
bool DataEmulatorFilter::areSame(const T& lcts, const T& lcts2) const
{
  for (auto detUnitIt = lcts.begin(); detUnitIt != lcts.end(); detUnitIt++) {
    const CSCDetId& id = (*detUnitIt).first;
    // ignore bad chambers
    if (checkBadChambers_ && badChambers_->isInBadChamber(id)) {
      continue;
    }
    const auto& range = (*detUnitIt).second;
    const auto& lcts2_range = lcts2.get(id);
    // now compare each
    for (auto digiIt = range.first; digiIt != range.second; digiIt++) {
      if ((*digiIt).isValid()) {
        bool isMatched = false;
        for (auto digiIt2 = lcts2_range.first; digiIt2 != lcts2_range.second; digiIt2++) {
          if (*digiIt == *digiIt2 and !isMatched) isMatched = true;
        }
        if (not isMatched) return false;
      }
    }
  }
  return true;
}

#endif

DataEmulatorFilter::DataEmulatorFilter(const edm::ParameterSet& conf) {
  alcts_d_tag_ = conf.getParameter<edm::InputTag>("alctData");
  clcts_d_tag_ = conf.getParameter<edm::InputTag>("clctData");
  lcts_d_tag_ = conf.getParameter<edm::InputTag>("lctData");

  alcts_e_tag_ = conf.getParameter<edm::InputTag>("alctEmul");
  clcts_e_tag_ = conf.getParameter<edm::InputTag>("clctEmul");
  lcts_e_tag_ = conf.getParameter<edm::InputTag>("lctEmul");

  alcts_d_token_ = consumes<CSCALCTDigiCollection>(alcts_d_tag_);
  clcts_d_token_ = consumes<CSCCLCTDigiCollection>(clcts_d_tag_);
  lcts_d_token_ = consumes<CSCCorrelatedLCTDigiCollection>(lcts_d_tag_);

  alcts_e_token_ = consumes<CSCALCTDigiCollection>(alcts_e_tag_);
  clcts_e_token_ = consumes<CSCCLCTDigiCollection>(clcts_e_tag_);
  lcts_e_token_ = consumes<CSCCorrelatedLCTDigiCollection>(lcts_e_tag_);

  checkBadChambers_ = conf.getUntrackedParameter<bool>("checkBadChambers", true);
}

bool DataEmulatorFilter::filter(edm::Event& ev, const edm::EventSetup& setup)
{
  // Find conditions data for bad chambers & cache it.  Needed for efficiency
  // calculations.
  if (checkBadChambers_) {
    edm::ESHandle<CSCBadChambers> pBad;
    setup.get<CSCBadChambersRcd>().get(pBad);
    badChambers_ = pBad.product();
  }

  // Get the collections of ALCTs, CLCTs, and correlated LCTs from event.
  edm::Handle<CSCALCTDigiCollection> alcts_data;
  edm::Handle<CSCCLCTDigiCollection> clcts_data;
  edm::Handle<CSCCorrelatedLCTDigiCollection> lcts_data;

  edm::Handle<CSCALCTDigiCollection> alcts_emul;
  edm::Handle<CSCCLCTDigiCollection> clcts_emul;
  edm::Handle<CSCCorrelatedLCTDigiCollection> lcts_emul;

  ev.getByToken(alcts_d_token_, alcts_data);
  ev.getByToken(clcts_d_token_, clcts_data);
  ev.getByToken(lcts_d_token_, lcts_data);

  ev.getByToken(alcts_e_token_, alcts_emul);
  ev.getByToken(clcts_e_token_, clcts_emul);
  ev.getByToken(lcts_e_token_, lcts_emul);

  int nValidALCTsData = countStubs(*alcts_data.product());
  int nValidCLCTsData = countStubs(*clcts_data.product());
  int nValidLCTsData = countStubs(*lcts_data.product());

  int nValidALCTsEmul = countStubs(*alcts_emul.product());
  int nValidCLCTsEmul = countStubs(*clcts_emul.product());
  int nValidLCTsEmul = countStubs(*lcts_emul.product());

  // check 1: same number of LCTs
  if (nValidALCTsData != nValidALCTsEmul) return true;
  if (nValidCLCTsData != nValidCLCTsEmul) return true;
  if (nValidLCTsData != nValidLCTsEmul) return true;

  // check 2: check each LCT
  if (!areSame(*alcts_data.product(), *alcts_emul.product())) return true;
  if (!areSame(*clcts_data.product(), *clcts_emul.product())) return true;
  if (!areSame(*lcts_data.product(), *lcts_emul.product())) return true;

  // do not filter all other events
  return false;
}


DEFINE_FWK_MODULE(DataEmulatorFilter);
