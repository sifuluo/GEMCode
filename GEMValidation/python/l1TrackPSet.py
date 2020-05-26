import FWCore.ParameterSet.Config as cms

l1TrackrpcRecHit = cms.PSet(
    verbose = cms.int32(0),
    inputTag = cms.InputTag("TTTracksFromTracklet","Level1TTTracks"),
)
