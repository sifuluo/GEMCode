#ifndef GEMCode_GEMValidation_SimTrackStruct
#define GEMCode_GEMValidation_SimTrackStruct

#include "TTree.h"
#include <string>

namespace gem {

  struct SimTrackStruct {
    float pt, eta, phi, pz, dxy;
    int charge;
    int endcap;
    int pdgid;

    void init() {
      pt = 0.;
      phi = 0.;
      eta = -9.;
      dxy = -999.;
      charge = -9;
      endcap = -9;
      pdgid = -9999;
    };

    TTree* book(TTree* t, const std::string& name = "track") {
      edm::Service<TFileService> fs;
      t = fs->make<TTree>(name.c_str(), name.c_str());

      t->Branch("pt", &pt);
      t->Branch("pz", &pz);
      t->Branch("eta", &eta);
      t->Branch("dxy", &dxy);
      t->Branch("phi", &phi);
      t->Branch("charge", &charge);
      t->Branch("endcap", &endcap);
      t->Branch("pdgid", &pdgid);

      return t;
    }
  };
}  // namespace

#endif
