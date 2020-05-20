import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_cff import Run3

from Validation.MuonHits.muonSimHitMatcherPSet import muonSimHitMatcherPSet
from Validation.MuonCSCDigis.muonCSCDigiPSet import muonCSCDigiPSet
from Validation.MuonCSCDigis.muonCSCStubPSet import muonCSCStubPSet
from Validation.MuonGEMDigis.muonGEMDigiPSet import muonGEMDigiPSet
from Validation.MuonGEMRecHits.muonGEMRecHitPSet import gemRecHit
from GEMCode.GEMValidation.muonPSet import muonPSet

process = cms.Process("GEMCSCANA", Run3)

## Standard sequence
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

## TrackingComponentsRecord required for matchers
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi')
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi')

process.source = cms.Source(
  "PoolSource",
  fileNames = cms.untracked.vstring('file:step2bis.root'),
#  fileNames = cms.untracked.vstring('/store/user/awarden/MiniBias/SingleMu_May2020_MC_step2/200512_202254/0000/step2_1.root')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

## global tag for upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2021_realistic', '')

# the analyzer configuration
#muonGEMDigiPSet.gemStripDigi.inputTag = "muonGEMDigis"
muonGEMDigiPSet.gemStripDigi.verbose = 1
muonCSCStubPSet.cscALCT.verbose = 1
muonCSCStubPSet.cscALCT.minBX = 3
muonCSCStubPSet.cscALCT.maxBX = 3
muonCSCStubPSet.cscCLCT.verbose = 1
muonCSCStubPSet.cscCLCT.minBX = 7
muonCSCStubPSet.cscCLCT.maxBX = 7
muonCSCStubPSet.cscLCT.verbose = 0

process.GEMCSCAnalyzer = cms.EDAnalyzer(
    "GEMCSCAnalyzer",
    muonSimHitMatcherPSet,
    muonCSCDigiPSet,
    muonCSCStubPSet,
    muonGEMDigiPSet,
    muonPSet,
    gemRecHit = gemRecHit,
    verbose = cms.untracked.int32(0),
    cscStations = cms.vstring("CSC_ALL","CSC_ME11", "CSC_ME1a", "CSC_ME1b", "CSC_ME12", "CSC_ME13",
                              "CSC_ME21", "CSC_ME22", "CSC_ME31", "CSC_ME32", "CSC_ME41", "CSC_ME42")
)

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.p = cms.Path(process.GEMCSCAnalyzer)

## messages
print
#print 'Input files:'
print '----------------------------------------'
print process.source.fileNames
print
print 'Output file:'
print '----------------------------------------'
print process.TFileService.fileName
print
