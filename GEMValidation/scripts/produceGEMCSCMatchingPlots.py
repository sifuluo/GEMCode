import sys
import os

from ROOT import TFile, TDirectory, TTree
from style.CMS_lumi import *
from helpers.cuts import *
from helpers.drawPlots import *

## run quiet mode
sys.argv.append( '-b' )

import ROOT
ROOT.gROOT.SetBatch(1)

from GEMCSCValidation import *

class GEMCSCStubPlotter():
  def __init__(self):
    self.inputDir = os.getenv("CMSSW_BASE") + "/src/"
    self.inputFile = self.inputDir + "out_ana.root"
    print self.inputFile

    self.targetDir = "plots/"
    self.ext = ".png"
    self.analyzer = "GEMCSCAnalyzer"
    self.file = TFile.Open(self.inputFile)
    print self.file

    self.dirAna = (self.file).Get(self.analyzer)
    print self.dirAna

    self.tree = self.dirAna.Get("SimTrack")
    print self.tree
    self.yMin = 0.5
    self.yMax = 1.1

    self.tree.AddFriend(self.dirAna.Get("CSCSimHit"))
    self.tree.AddFriend(self.dirAna.Get("CSCDigi"))
    self.tree.AddFriend(self.dirAna.Get("CSCStub"))
    self.tree.AddFriend(self.dirAna.Get("GEMSimHit"))
    self.tree.AddFriend(self.dirAna.Get("GEMDigi"))
    self.tree.AddFriend(self.dirAna.Get("GEMStub"))
    self.tree.AddFriend(self.dirAna.Get("L1Mu"))

plotter = GEMCSCStubPlotter()

CSCSimHit(plotter)
#CSCStripsWires(plotter,st)
#CSCStripsWires2(plotter,st)
#CSCAlctClct(plotter,st)
#CSCAlctClct2(plotter,st)
#CSCLct(plotter,st)
