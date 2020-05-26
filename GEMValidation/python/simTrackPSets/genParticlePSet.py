import FWCore.ParameterSet.Config as cms

genParticle = cms.PSet(
    inputTag = cms.InputTag("genParticles"),
    verbose = cms.int32(0),
    run = cms.bool(True),
)
