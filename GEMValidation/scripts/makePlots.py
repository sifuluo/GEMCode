import sys
import os

from ROOT import TFile, TDirectory, TTree, gROOT

## run quiet mode
sys.argv.append( '-b' )
gROOT.SetBatch(1)

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
    self.treeFriends = ["CSCSimHit", "CSCDigi", "CSCStub",
                        "GEMSimHit", "GEMDigi", "GEMStub", "L1Mu"]
    for p in self.treeFriends:
      self.tree.AddFriend(self.dirAna.Get(p))
    self.yMin = 0.5
    self.yMax = 1.1


## needs to be cleaned up
plotter = GEMCSCStubPlotter()

## plots - most do not work yet
from efficiency.plots import *
makeEfficiencyPlots(plotter)

#from timing.plots import *
#makeTimingPlots()

#from occupancy.plots import *
#makeOccupancyPlots()

#from resolution.plots import *
#makeResolutionPlots()

#from datavsemulator.plots import *
