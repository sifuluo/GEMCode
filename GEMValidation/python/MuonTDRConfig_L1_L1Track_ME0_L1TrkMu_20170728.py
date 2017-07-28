# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step2 --conditions 91X_upgrade2023_realistic_v3 -n 10 --era Phase2 --eventcontent FEVTDEBUGHLT -s L1TrackTrigger --datatier GEN-SIM-DIGI-RAW --nThreads 4 --geometry Extended2023D17
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('ReL1TrackTrigger',eras.Phase2)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.L1TrackTrigger_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('file:/uscms_data/d3/dildick/work/ME0TDRStudies/Setup20170124/forCrossCheckCentralProduction/CMSSW_9_1_1_patch3/src/CrabJobs/step2.root'),
    fileNames = cms.untracked.vstring('file:/uscms/home/dildick/nobackup/work/ME0TDRStudies/Setup20170124/forCrossCheckCentralProduction/reTestTemp20170728/CMSSW_9_1_1_patch3/src/out_digi_l1_l1cluster.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(10485760),
    fileName = cms.untracked.string('file:step2.root'),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTTrack*_Level1TTTracks_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTCluster*_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTStub*_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_L1TkMuons_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_*Muon*_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_me0*_*_*')


# Additional output definition
## ME0 segments
process.load("L1Trigger.ME0Trigger.me0TriggerPseudoDigis_cff")
process.simMuonME0PseudoReDigisCoarse.inputCollection = cms.string("simMuonME0Digis")
process.load("L1Trigger.L1TTrackMatch.L1TkObjectProducers_cff")

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '91X_upgrade2023_realistic_v3', '')

# Path and EndPath definitions
process.L1simulation_step = cms.Path(process.SimL1TMuon*process.me0TriggerPseudoDigiSequence)
process.L1TrackTrigger_step = cms.Path(process.L1TrackTrigger)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.L1simulation_step,
                                process.L1TrackTrigger_step,
                                process.pL1TkMuon,
                                process.endjob_step,
                                process.FEVTDEBUGHLToutput_step)

from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(4)
process.options.numberOfStreams=cms.untracked.uint32(0)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
