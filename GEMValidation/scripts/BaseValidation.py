import os
from ROOT import TFile

class GEMCSCStubPlotter():
  def __init__(self):
    self.inputDir = os.getenv("CMSSW_BASE") + "/src/"
    self.inputFile = self.inputDir + "out_ana.root"
    self.targetDir = "plots/"
    self.ext = ".png"
    self.analyzer = "GEMCSCAnalyzer"
    self.file = TFile.Open(self.inputFile)
    self.dirAna = (self.file).Get(self.analyzer)
    self.tree = self.dirAna.Get("SimTrack")
    self.yMin = 0.5
    self.yMax = 1.1
    self.etaMin = 0.9
    self.etaMax = 2.4
    self.pu = 140

    self.tree.AddFriend(self.dirAna.Get("CSCSimHit"))
    self.tree.AddFriend(self.dirAna.Get("CSCDigi"))
    self.tree.AddFriend(self.dirAna.Get("CSCStub"))
    self.tree.AddFriend(self.dirAna.Get("GEMSimHit"))
    self.tree.AddFriend(self.dirAna.Get("GEMDigi"))
    self.tree.AddFriend(self.dirAna.Get("GEMStub"))
    self.tree.AddFriend(self.dirAna.Get("L1Mu"))
