#ifndef GEMCode_GEMValidation_L1MuStruct
#define GEMCode_GEMValidation_L1MuStruct

#include "TTree.h"
#include "TROOT.h"
#include "TObject.h"

namespace gem {

  class Event : public TObject {

    int event;
    int lumi;
    int run;
    int nVtx;

    Event() {
      event = -1;
      lumi = -1;
      run  = -1;
      nVtx = -1;
    }

    ClassDef(Event, 1)
  };

  // average of simhits in a chamber
  class Hit : public TObject {
    int region;
    int station;
    int ring;
    int chamber;
    int layer;
    int roll;
    // tracking particle ID
    int tpid;

    Hit() {
      region = -1;
      station = -1;
      ring = -1;
      chamber = -1;
      layer = -1;
      roll = -1;
      tpid = -1;
    }
  };

  class Track : public TObject {
    float pt, eta, phi;
    int charge;
    // tracking particle ID
    int tpid;

    Track() {
      pt = -1;
      eta = -9;
      phi = -9;
      charge = -9
      tpid = -1;
    }
  };

  class SimHit : public Hit {
    ClassDef(SimHit, 1);
  };

  class GEMSimHit : public Hit {
    ClassDef(GEMSimHit, 1);
  };

  class CSCSimHit : public Hit {
    ClassDef(CSCSimHit, 1);
  };

  class GEMPad : public Hit  {
    ClassDef(GEMSimHit, 1);
  };

  class GEMCoPad : public Hit {
    ClassDef(GEMCoPad, 1);
  };

  class GEMCluster : public Hit {
    ClassDef(GEMCluster, 1);
  };

  class CSCWire : public Hit {
    ClassDef(CSCWire, 1);
  };

  class CSCCompator : public Hit {
    ClassDef(CSCCompator, 1);
  };

  class CSCALCT : public Hit {
    ClassDef(CSCALCT, 1);
  };

  class CSCCLCT : public Hit {
    ClassDef(CSCCLCT, 1);
  };

  class CSCLCT : public Hit {
    ClassDef(CSCLCT, 1);
  };

  class GEMCSCLCT : public Hit {
    ClassDef(GEMCSCLCT, 1);
  };

  class EMTF : public Track {
    ClassDef(EMTF, 1);
  };

  class GMTRegCand : public Track {
    ClassDef(GMTRegCand, 1);
  };

  class L1Mu : public Track {
    ClassDef(L1Mu, 1);
  };

}  // namespace

#endif
