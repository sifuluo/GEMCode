import sys

from ROOT import *
from style.CMS_lumi import *
from helpers.cuts import *
from helpers.drawPlots import *

## run quiet mode
import sys
sys.argv.append( '-b' )

import ROOT
ROOT.gROOT.SetBatch(1)

from BaseValidation import *
from GEMCSCValidation import *

plotter = GEMCSCStubPlotter()


CSCSimHit(plotter)
#CSCStripsWires(plotter,st)
#CSCStripsWires2(plotter,st)
#CSCAlctClct(plotter,st)
#CSCAlctClct2(plotter,st)
#CSCLct(plotter,st)
