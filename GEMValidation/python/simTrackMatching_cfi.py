import FWCore.ParameterSet.Config as cms

## in CMSSW
from Validation.MuonHits.muonSimHitMatcherPSet import muonSimHitMatcherPSet
from Validation.MuonCSCDigis.muonCSCDigiPSet import muonCSCDigiPSet
from Validation.MuonCSCDigis.muonCSCStubPSet import muonCSCStubPSet
from Validation.MuonGEMDigis.muonGEMDigiPSet import muonGEMDigiPSet
from Validation.MuonGEMRecHits.muonGEMRecHitPSet import gemRecHit

## in GEMCode
from GEMCode.GEMValidation.simTrackPSets import genParticlePSet
from GEMCode.GEMValidation.simTrackPSets import me0HitPSet
from GEMCode.GEMValidation.simTrackPSets import muonRPCDigiPSet
from GEMCode.GEMValidation.simTrackPSets import muonDTDigisPSet
from GEMCode.GEMValidation.simTrackPSets import muonDTStubPSet
from GEMCode.GEMValidation.simTrackPSets import muonPSet
from GEMCode.GEMValidation.simTrackPSets import l1TrackPSet
from GEMCode.GEMValidation.simTrackPSets import rpcRecHitPSet
from GEMCode.GEMValidation.simTrackPSets import cscRecHitPSet
from GEMCode.GEMValidation.simTrackPSets import recoTrackPSet
