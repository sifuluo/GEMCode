import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_cff import Run3

process = cms.Process("GEMCSCANA", Run3)

## Standard sequence
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi')
process.load('TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi')

"""
process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring("debug"),
    debug = cms.untracked.PSet(
 #       extension = cms.untracked.string(".txt"),
        threshold = cms.untracked.string("DEBUG"),
        # threshold = cms.untracked.string("WARNING"),
        lineLength = cms.untracked.int32(132),
        noLineBreaks = cms.untracked.bool(True)
    ),
    debugModules = cms.untracked.vstring("GEMCSCAnalyzer")
)
"""
process.source = cms.Source(
  "PoolSource",
  fileNames = cms.untracked.vstring('file:step2bis.root'),
#  fileNames = cms.untracked.vstring('/store/user/awarden/MiniBias/SingleMu_May2020_MC_step2/200512_202254/0000/step2_1.root')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(30) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

## global tag for upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2021_realistic', '')

# the analyzer configuration
from GEMCode.GEMValidation.simTrackMatching_cfi import simTrackPSet
process.GEMCSCAnalyzer = cms.EDAnalyzer(
    "GEMCSCAnalyzer",
    simTrackPSet,
    runSim = cms.bool(True),
    runDigi = cms.bool(True),
    runStub = cms.bool(True),
    runL1 = cms.bool(True),
    runReco = cms.bool(False),
    verbose = cms.untracked.int32(1),
    minNHitsChamberGEMSimHit = cms.int32(1),
    minNHitsChamberCSCSimHit = cms.int32(4),
    minNHitsChamberCSCDigi = cms.int32(4),
    minNHitsChamberGEMDigi = cms.int32(1),
    minNHitsChamberCSCStub = cms.int32(4),
    cscStations = cms.vstring("CSC_ALL","CSC_ME11", "CSC_ME1a",
                              "CSC_ME1b", "CSC_ME12", "CSC_ME13",
                              "CSC_ME21", "CSC_ME22", "CSC_ME31",
                              "CSC_ME32", "CSC_ME41", "CSC_ME42")
)

ana = process.GEMCSCAnalyzer
ana.simTrack.minEta = 1.2
ana.simTrack.maxEta = 2.4
ana.gemStripDigi.inputTag = "muonGEMDigis"
ana.gemStripDigi.verbose = 0
ana.cscALCT.verbose = 0
ana.cscALCT.minBX = 3
ana.cscALCT.maxBX = 3
ana.cscCLCT.verbose = 0
ana.cscCLCT.minBX = 7
ana.cscCLCT.maxBX = 7
ana.cscLCT.verbose = 0

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
