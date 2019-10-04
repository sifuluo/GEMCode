import FWCore.ParameterSet.Config as cms

process = cms.Process("RPCTiming")

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

process.source = cms.Source("PoolSource",
	#fileNames = cms.untracked.vstring('file:step2.root'),
)

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
Stations = enum('ALL','RE12','RE13','RE22','RE23','RE31','RE32','RE33','RE41','RE42','RE43')

from GEMCode.GEMValidation.simTrackMatching_cfi import SimTrackMatching
process.RPCTimingAnalyzer = cms.EDAnalyzer("RPCTimingAnalyzer",
    verbose = cms.untracked.int32(0),
    stationsToUse = cms.vint32(
      Stations.ALL,
      Stations.RE12,
      Stations.RE12,
      Stations.RE13,
      Stations.RE22,
      Stations.RE23,
      Stations.RE31,
      Stations.RE32,
      Stations.RE33,
      Stations.RE41,
      Stations.RE42,
      Stations.RE43
    ),
    simTrackMatching = SimTrackMatching
)
matching = process.RPCTimingAnalyzer.simTrackMatching
matching.rpcStationsToUse = cms.vint32(0,1,2,3,4,5,6,7,8,9,10)
matching.l1track.run = cms.bool(False)
matching.l1tkmuon.run = cms.bool(False)
matching.upgradeGMT.run = cms.bool(False)
matching.simTrack.minPt = 2
matching.simTrack.minEta = 0.9
matching.simTrack.maxEta = 2.4

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50000) )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.p = cms.Path(process.RPCTimingAnalyzer)

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
