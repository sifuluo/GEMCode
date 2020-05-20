import FWCore.ParameterSet.Config as cms

muonPSet = cms.PSet(
    emtfTrack = cms.PSet(
        verbose = cms.int32(0),
        run = cms.bool(True),
        inputTag = cms.InputTag("simEmtfDigis"),
        minBX = cms.int32(0),
        maxBX = cms.int32(0),
        deltaR = cms.double(0.5),
    ),
    emtfCand = cms.PSet(
        verbose = cms.int32(0),
        run = cms.bool(True),
        inputTag = cms.InputTag("simEmtfDigis","EMTF"),
        minBX = cms.int32(0),
        maxBX = cms.int32(0),
        deltaR = cms.double(0.5),
    ),
    muon = cms.PSet(
        verbose = cms.int32(0),
        run = cms.bool(True),
        inputTag = cms.InputTag("simGmtStage2Digis"),
        minBX = cms.int32(0),
        maxBX = cms.int32(0),
        deltaR = cms.double(0.5),
    )
)
