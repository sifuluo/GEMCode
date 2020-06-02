import sys
import os

from ROOT import TFile, TDirectory, TTree

## helpers
from style.CMS_lumi import *
from helpers.cuts import *
from helpers.drawPlots import *

## plots -  not work yet
#from efficiency.plots import *
#from timing.plots import *
#from occupancy.plots import *
#from datavsemulator.plots import *

## run quiet mode
sys.argv.append( '-b' )

import ROOT
ROOT.gROOT.SetBatch(1)

from GEMCSCValidation import *

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
    self.tree.AddFriend(self.dirAna.Get("CSCSimHit"))
    self.tree.AddFriend(self.dirAna.Get("CSCDigi"))
    self.tree.AddFriend(self.dirAna.Get("CSCStub"))
    self.tree.AddFriend(self.dirAna.Get("GEMSimHit"))
    self.tree.AddFriend(self.dirAna.Get("GEMDigi"))
    self.tree.AddFriend(self.dirAna.Get("GEMStub"))
    self.tree.AddFriend(self.dirAna.Get("L1Mu"))

## needs to be cleaned up
plotter = GEMCSCStubPlotter()

CSCSimHit(plotter)
CSCStripsWires(plotter)
CSCStripsWires2(plotter)
CSCAlctClct(plotter)
CSCAlctClct2(plotter)
CSCLct(plotter)
