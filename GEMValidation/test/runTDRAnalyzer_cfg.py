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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(25000) )

process.source = cms.Source(
  "PoolSource",
  fileNames = cms.untracked.vstring(
    'file:input.root',
  )
)

#InputDir = ['/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20191001_ILT/191001_042512/0000/']; fileN = "out_ana_PU0_ILT.root"
#InputDir = ['/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU200_REL1_20191001_ILT/191001_042733/0000/']; fileN = "out_ana_PU200_ILT.root"
#InputDir = ['/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20191001_NoILT_v2/191001_045123/0000/']; fileN = "out_ana_PU0_noILT.root"
#InputDir = ['/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU200_REL1_20191001_NoILT_v2/191001_045913/0000/']; fileN = "out_ana_PU200_noILT.root"
InputDir = ['/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU200_REL1_20191001_NoSLHC_v2/191002_063536/0000/']; fileN = "out_ana_PU200_noSLHC.root"

from GEMCode.GEMValidation.InputFileHelpers import *
process = useInputDir(process, InputDir, True)

process.TFileService = cms.Service(
  "TFileService",
  fileName = cms.string(fileN)
)

## global tag for upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# the analyzer configuration
def enum(*sequential, **named):
  enums = dict(zip(sequential, range(len(sequential))), **named)
  return type('Enum', (), enums)
Stations = enum('ALL','ME11','ME1a','ME1b','ME12','ME13','ME21','ME22','ME31','ME32','ME41','ME42','ME0')

from GEMCode.GEMValidation.simTrackMatching_cfi import SimTrackMatching
process.TDRAnalyzer = cms.EDAnalyzer(
  "TDRAnalyzer",
  verbose = cms.untracked.int32(0),
  stationsToUse = cms.vint32(
    Stations.ALL,
    Stations.ME11,
    Stations.ME1a,
    Stations.ME1b,
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
matching.l1track.run = cms.bool(False)
matching.l1tkmuon.run = cms.bool(False)
matching.upgradeGMT.run = cms.bool(False)
matching.simTrack.minPt = 5
matching.simTrack.minEta = 0.9
matching.simTrack.maxEta = 2.4
matching.matchprint = cms.bool(False)
matching.cscStripDigi.verbose = 0
matching.gemStripDigi.verbose = 0
matching.gemPadDigi.verbose = 0
matching.gemCoPadDigi.verbose = 0
matching.cscCLCT.verbose = 0
matching.cscLCT.verbose = 0

matching.cscALCT.inputTag = cms.InputTag("simCscTriggerPrimitiveDigis","","MyCSC")
matching.cscCLCT.inputTag = cms.InputTag("simCscTriggerPrimitiveDigis","","MyCSC")
matching.cscLCT.inputTag = cms.InputTag("simCscTriggerPrimitiveDigis","","MyCSC")

doGem = False
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
