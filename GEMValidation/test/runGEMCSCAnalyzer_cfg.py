import FWCore.ParameterSet.Config as cms

process = cms.Process("GEMCSCANA")

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
	fileNames = cms.untracked.vstring('file:/eos/uscms/store/user/dildick/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gunPU0_REL1_20190921_v2/190922_041957/0000/step3_1.root')
)

#InputDir = ['/eos/uscms/store/user/dildick/DarkSUSY_mH_125_mGammaD_20_cT_0_14TeV/DarkSUSY_mH_125_mGammaD_20_cT_0_14TeV_REGEN/170723_232821/0000/']
#InputDir = ['/fdata/hepx/store/user/tahuang/SingleMu_100X_Run2MC_CSC_CentralBX_GEN_SIM_DIGI_L1/SingleMu_100X_Run2MC_CSC_CentralBX_GEN_SIM_DIGI_L1/180212_131435/0000/']
#InputDir = ['/fdata/hepx/store/user/tahuang/SingleMu_100X_Run2MC_CSC_CentralBX_GEN_SIM_DIGI_L1_20180212/SingleMu_100X_Run2MC_CSC_CentralBX_GEN_SIM_DIGI_L1_20180212/180213_092307/0000/']
#from GEMCode.GEMValidation.InputFileHelpers import *
#process = useInputDir(process, InputDir, True)

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
Stations = enum('ALL','ME11','ME1a','ME1b','ME12','ME13','ME21','ME22','ME31','ME32','ME41','ME42')

from GEMCode.GEMValidation.simTrackMatching_cfi import SimTrackMatching
process.GEMCSCAnalyzer = cms.EDAnalyzer("GEMCSCAnalyzer",
    verbose = cms.untracked.int32(0),
    stationsToUse = cms.vint32(Stations.ALL,Stations.ME11,Stations.ME1a,Stations.ME1b,
                              Stations.ME21,Stations.ME31,Stations.ME41),
    simTrackMatching = SimTrackMatching
)
matching = process.GEMCSCAnalyzer.simTrackMatching
matching.gemStationsToUse = cms.vint32(0,1,2) ## no GEM station is used
matching.cscStationsToUse = cms.vint32(0,1,2,3,4,5,6,7,8,9,10,11)
matching.l1track.run = cms.bool(False)
matching.l1tkmuon.run = cms.bool(False)
matching.upgradeGMT.run = cms.bool(False)
matching.simTrack.minPt = 1.5
matching.matchprint = cms.bool(False)

doGem = True
if doGem:
  matching.cscSimHit.minNHitsChamber = 3
  matching.cscStripDigi.minNHitsChamber = 3
  matching.cscWireDigi.minNHitsChamber = 3
  matching.cscCLCT.minNHitsChamber = 3
  matching.cscALCT.minNHitsChamber = 3
  matching.cscLCT.minNHitsChamber = 3
  matching.cscMPLCT.minNHitsChamber = 3

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.p = cms.Path(process.GEMCSCAnalyzer)

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
