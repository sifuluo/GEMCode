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
	fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/d/dildick/public/GEM/BackPortGEMUpdatesL1T/CMSSW_10_6_1_patch2/src/025D27E1-8363-B54D-8E59-15E4E4D8D0A4.root')
)

#InputDir = ['/eos/uscms/store/user/dildick/DarkSUSY_mH_125_mGammaD_20_cT_0_14TeV/DarkSUSY_mH_125_mGammaD_20_cT_0_14TeV_REGEN/170723_232821/0000/']

InputDir = ['/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191002_PU0_CSCTP_ILT/191003_001017/0000']
InputDir = ['/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191002_PU0_CSCTP_NoILT/191003_001112/0000']
InputDir = ['/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191002_PU0_CSCTP_NoSLHC/191003_001204/0000']
InputDir = ['/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191002_PU200_CSCTP_ILT/191003_000951/0000']
InputDir = ['/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191002_PU200_CSCTP_NoILT/191003_001043/0000']
InputDir = ['/store/user/lpcgem/Mu_FlatPt2to100-pythia8-gun/crab_Mu_FlatPt2to100-pythia8-gun_SD20191002_PU200_CSCTP_NoSLHC_v2/191003_014502/0000']

from GEMCode.GEMValidation.InputFileHelpers import *
#process = useInputDir(process, InputDir, True)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

## global tag for upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# the analyzer configuration
def enum(*sequential, **named):
  enums = dict(zip(sequential, range(len(sequential))), **named)
  return type('Enum', (), enums)
Stations = enum('ALL','ME11','ME1a','ME1b','ME12','ME13','ME21','ME22','ME31','ME32','ME41','ME42')

from GEMCode.GEMValidation.simTrackMatching_cfi import SimTrackMatching
process.LCTFakeRateAnalyzer = cms.EDAnalyzer("LCTFakeRateAnalyzer",
    verbose = cms.untracked.int32(0),
    stationsToUse = cms.vint32(Stations.ALL,Stations.ME11,Stations.ME1a,Stations.ME1b,
                              Stations.ME21,Stations.ME31,Stations.ME41),
    simTrackMatching = SimTrackMatching
)
matching = process.LCTFakeRateAnalyzer.simTrackMatching
matching.gemStationsToUse = cms.vint32(-1) ## no GEM station is used
matching.cscStationsToUse = cms.vint32(0,1,2,3,4,5,6,7,8,9,10,11)
matching.l1track.run = cms.bool(False)
matching.l1tkmuon.run = cms.bool(False)
matching.upgradeGMT.run = cms.bool(False)
matching.simTrack.minPt = 5
matching.simTrack.minEta = 0.9
matching.simTrack.maxEta = 2.4
matching.matchprint = cms.bool(False)

#matching.cscALCT.inputTag = cms.InputTag("simCscTriggerPrimitiveDigis","","MyCSC")
#matching.cscCLCT.inputTag = cms.InputTag("simCscTriggerPrimitiveDigis","","MyCSC")
#matching.cscLCT.inputTag = cms.InputTag("simCscTriggerPrimitiveDigis","","MyCSC")


doGem = True
if doGem:
  matching.cscSimHit.minNHitsChamber = 3
  matching.cscStripDigi.minNHitsChamber = 3
  matching.cscWireDigi.minNHitsChamber = 3
  matching.cscCLCT.minNHitsChamber = 3
  matching.cscALCT.minNHitsChamber = 3
  matching.cscLCT.minNHitsChamber = 3
  matching.cscMPLCT.minNHitsChamber = 3

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50000) )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.p = cms.Path(process.LCTFakeRateAnalyzer)

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
