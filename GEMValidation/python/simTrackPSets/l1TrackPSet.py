import FWCore.ParameterSet.Config as cms

l1TrackPSet = cms.PSet(
    l1Track = cms.PSet(
        verbose = cms.int32(0),
        inputTag = cms.InputTag("TTTracksFromTracklet","Level1TTTracks"),
    ),
    l1TrackMuon = cms.PSet(
        verbose = cms.int32(0),
        run = cms.bool(True),
        validInputTags = cms.InputTag("L1TkMuons"),
    )
)
