import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Phase2C8_timing_layer_bar_cff import Phase2C8_timing_layer_bar

process = cms.Process("ME0ANA", Phase2C8_timing_layer_bar)

## Standard sequence
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2023D41Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi')
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi')

process.source = cms.Source(
  "PoolSource",
  fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/d/dildick/public/GEM/BackPortGEMUpdatesL1T/CMSSW_10_6_1_patch2/src/025D27E1-8363-B54D-8E59-15E4E4D8D0A4.root'),
)

process.TFileService = cms.Service(
  "TFileService",
  fileName = cms.string("out_ana.root")
)

## global tag for upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# the analyzer configuration
from GEMCode.GEMValidation.simTrackMatching_cfi import SimTrackMatching
process.ME0TriggerAnalyzer = cms.EDAnalyzer(
  "ME0TriggerAnalyzer",
    verbose = cms.untracked.int32(1),
  simTrackMatching = SimTrackMatching
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.p = cms.Path(process.ME0TriggerAnalyzer)

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
