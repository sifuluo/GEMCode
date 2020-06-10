import os

from efficiency.CSCSimHit import *
from efficiency.CSCDigi import *
from efficiency.CSCStub import *

from efficiency.GEMSimHit import *
from efficiency.GEMDigi import *
from efficiency.GEMStub import *
from efficiency.GEMRecHit import *

from efficiency.L1Mu import *

## need to create directory structure - assume it does not exist yet
os.mkdir("plots")
os.mkdir("plots/efficiency")
os.mkdir("plots/efficiency/GEMSimHit")
os.mkdir("plots/efficiency/GEMDigi")
os.mkdir("plots/efficiency/GEMStub")
os.mkdir("plots/efficiency/CSCSimHit")
os.mkdir("plots/efficiency/CSCDigi")
os.mkdir("plots/efficiency/CSCStub")

def makeEfficiencyPlots(plotter):
    CSCSimHit(plotter)
    CSCStripsWires(plotter)
    CSCStripsWires2(plotter)
    CSCAlctClct(plotter)
    CSCAlctClct2(plotter)
    CSCLct(plotter)

    GEMSimHitEta(plotter)
    GEMSimHitPhi(plotter)
    GEMDigiEta(plotter)
    GEMDigiPhi(plotter)
    GEMPadEta(plotter)
    GEMPadPhi(plotter)
    GEMPad2Eta(plotter)
    GEMPad2Phi(plotter)
    GEMCoPadEta(plotter)
    GEMCoPadPhi(plotter)
