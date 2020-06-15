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
if not os.path.exists("plots"):
    os.mkdir("plots")
    if not os.path.exists("plots/efficiency"):
        os.mkdir("plots/efficiency")
        if not os.path.exists("plots/efficiency/GEMSimHit"):
            os.mkdir("plots/efficiency/GEMSimHit")
        if not os.path.exists("plots/efficiency/GEMDigi"):
            os.mkdir("plots/efficiency/GEMDigi")
        if not os.path.exists("plots/efficiency/GEMStub"):
            os.mkdir("plots/efficiency/GEMStub")
        if not os.path.exists("plots/efficiency/CSCSimHit"):
            os.mkdir("plots/efficiency/CSCSimHit")
        if not os.path.exists("plots/efficiency/CSCDigi"):
            os.mkdir("plots/efficiency/CSCDigi")
        if not os.path.exists("plots/efficiency/CSCStub"):
            os.mkdir("plots/efficiency/CSCStub")

def makeEfficiencyPlots(plotter):
    """
    CSCSimHit(plotter)
    CSCStripsWires(plotter)
    CSCStripsWires2(plotter)
    CSCAlctClct(plotter)
    CSCAlctClct2(plotter)
    CSCLct(plotter)
    """
    GEMSimHit(plotter)
    """
    GEMDigi(plotter)
    GEMStub(plotter)
    """
