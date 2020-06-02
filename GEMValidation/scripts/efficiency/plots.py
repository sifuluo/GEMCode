from efficiency.CSCSimHit import *
from efficiency.CSCDigi import *
from efficiency.CSCStub import *

from efficiency.GEMSimHit import *
from efficiency.GEMDigi import *
from efficiency.GEMStub import *
from efficiency.GEMRecHit import *

from efficiency.L1Mu import *

def makeEfficiencyPlots(plotter):
    CSCSimHit(plotter)
    CSCStripsWires(plotter)
    CSCStripsWires2(plotter)
    CSCAlctClct(plotter)
    CSCAlctClct2(plotter)
    CSCLct(plotter)

    GEMSimHitEta(plotter)
    GEMSimHitPhi(plotter)
