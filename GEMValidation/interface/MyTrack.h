#ifndef GEMCode_GEMValidation_MyTrack
#define GEMCode_GEMValidation_MyTrack

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "GEMCode/GEMValidation/interface/Structs/SimTrackStruct.h"
#include "GEMCode/GEMValidation/interface/Structs/SimHitStruct.h"
#include "GEMCode/GEMValidation/interface/Structs/L1MuStruct.h"
#include "GEMCode/GEMValidation/interface/Structs/RecoTrackStruct.h"
#include "GEMCode/GEMValidation/interface/Structs/DigiStruct.h"
#include "GEMCode/GEMValidation/interface/Structs/StubStruct.h"

#include "TTree.h"
#include <vector>
#include <string>

static const int NumOfTrees = 13;

namespace gem {

  struct MyTrack :
    gem::SimTrackStruct,
    gem::SimHitStruct,
    gem::DigiStruct,
    gem::StubStruct,
    gem::L1MuStruct,
    gem::RecoTrackStruct {

    // initialize to default values
    void init() {
      gem::SimTrackStruct::init();
      gem::SimHitStruct::init();
      gem::DigiStruct::init();
      gem::StubStruct::init();
      gem::L1MuStruct::init();
      gem::RecoTrackStruct::init();
    };

    TTree* book(TTree* t, const std::string& name = "track") {

      edm::Service<TFileService> fs;
      t = fs->make<TTree>(name.c_str(), name.c_str());

      t = gem::SimTrackStruct::book(t, name);
      t = gem::SimHitStruct::book(t, name);
      t = gem::DigiStruct::book(t, name);
      t = gem::StubStruct::book(t, name);
      t = gem::L1MuStruct::book(t, name);
      t = gem::RecoTrackStruct::book(t, name);

      return t;
    }
  };
}  // namespace

#endif
