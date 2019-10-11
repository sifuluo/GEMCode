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

process.source = cms.Source(
  "PoolSource",
  fileNames = cms.untracked.vstring('/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191003_PU300_CSCTP_ILT/191004_040002/0000/step3_995.root'),
  #fileNames = cms.untracked.vstring('/store/mc/PhaseIITDRSpring19DR/Mu_FlatPt2to100-pythia8-gun/AODSIM/PU200_106X_upgrade2023_realistic_v3-v2/70000/FF7CFD15-2ABF-244F-9000-C04C4BC596DC.root'),
)

InputDir = ['/eos/uscms/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191007_PU0_CSCTP_ILT/191007_174529/0000/']

from GEMCode.GEMValidation.InputFileHelpers import *
process = useInputDir(process, InputDir, True)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana_PU0_RPC.root")
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
matching.simTrack.minPt = 5
matching.simTrack.minEta = 1.6
matching.simTrack.maxEta = 2.4
matching.simTrack.verbose = True
matching.rpcSimHit.verbose = True
matching.rpcRecHit.verbose = True
matching.rpcStripDigi.verbose = True

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## run RPC rechits
process.load("RecoLocalMuon.RPCRecHit.rpcRecHits_cfi")
process.rpcRecHits.rpcDigiLabel = cms.InputTag('simMuonRPCDigis')
#process.p = cms.Path(process.rpcRecHits)

process.p = cms.Path(process.rpcRecHits * process.RPCTimingAnalyzer)

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
