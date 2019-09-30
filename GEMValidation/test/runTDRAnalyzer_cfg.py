import FWCore.ParameterSet.Config as cms

process = cms.Process("TDRANA")

## Standard sequence
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2023D41Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

## TrackingComponentsRecord required for matchers
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi')
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-100) )

process.source = cms.Source(
  "PoolSource",
  fileNames = cms.untracked.vstring(
    'file:/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_1.root',
    'file:/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_2.root',
    'file:/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_3.root',
    'file:/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_4.root',
    'file:/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_5.root'
  )
)

"""
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_13.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_14.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_15.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_16.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_17.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_18.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_19.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_2.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_20.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_21.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_22.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_23.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_24.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_25.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_3.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_4.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_5.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_6.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_7.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_8.root
/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_9.root
"""

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

## global tag for upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# the analyzer configuration
def enum(*sequential, **named):
  enums = dict(zip(sequential, range(len(sequential))), **named)
  return type('Enum', (), enums)
Stations = enum('ME11','ME12','ME13','ME21','ME22','ME31','ME32','ME41','ME42')

from GEMCode.GEMValidation.simTrackMatching_cfi import SimTrackMatching
process.TDRAnalyzer = cms.EDAnalyzer("TDRAnalyzer",
    verbose = cms.untracked.int32(0),
    stationsToUse = cms.vint32(
      Stations.ME11,
      Stations.ME12,
      Stations.ME13,
      Stations.ME21,
      Stations.ME22,
      Stations.ME31,
      Stations.ME32,
      Stations.ME41,
      Stations.ME42
    ),
    simTrackMatching = SimTrackMatching
)
matching = process.TDRAnalyzer.simTrackMatching
matching.gemStationsToUse = cms.vint32(0,1,2) ## no GEM station is used
matching.cscStationsToUse = cms.vint32(0,1,2,3,4,5,6,7,8)
matching.l1track.run = cms.bool(False)
matching.l1tkmuon.run = cms.bool(False)
matching.upgradeGMT.run = cms.bool(False)
matching.simTrack.minPt = 10
matching.simTrack.minEta = 1.2
matching.simTrack.maxEta = 2.4
matching.matchprint = cms.bool(False)
matching.cscLCT.verbose = 0
matching.cscStations = cms.vstring("CSC_ME11", "CSC_ME12", "CSC_ME13",
                                   "CSC_ME21", "CSC_ME22", "CSC_ME31",
                                   "CSC_ME32", "CSC_ME41", "CSC_ME42")

doGem = True
if doGem:
  matching.cscSimHit.minNHitsChamber = 3
  matching.cscStripDigi.minNHitsChamber = 3
  matching.cscWireDigi.minNHitsChamber = 3
  matching.cscCLCT.minNHitsChamber = 3
  matching.cscALCT.minNHitsChamber = 3
  matching.cscLCT.minNHitsChamber = 3
  matching.cscMPLCT.minNHitsChamber = 3

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.p = cms.Path(process.TDRAnalyzer)

## messages
print
#print 'Input files:'
print '----------------------------------------'
#print process.source.fileNames
#print
print 'Output file:'
print '----------------------------------------'
print process.TFileService.fileName
print
