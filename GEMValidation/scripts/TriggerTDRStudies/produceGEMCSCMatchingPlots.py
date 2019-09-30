## run quiet mode
import sys
sys.argv.append( '-b' )

import ROOT
ROOT.gROOT.SetBatch(1)

from Plotter import TriggerTDREfficiencyPlotter
from GEMCSCValidation import makeEfficiencyPlot
from GEMCSCValidation import simTrackToCscSimHitMatching
from GEMCSCValidation import simTrackToCscStripsWiresMatching
from GEMCSCValidation import simTrackToCscAlctClctMatching
from GEMCSCValidation import simTrackToCscLctMatching

plotter = TriggerTDREfficiencyPlotter()

for i in range(len(plotter.stationsToUse)):
  st = plotter.stationsToUse[i]
  print "Processing station ", i, plotter.stations.reverse_mapping[st]
  simTrackToCscSimHitMatching(plotter,st)
  simTrackToCscStripsWiresMatching(plotter,st)
  simTrackToCscAlctClctMatching(plotter,st)
  simTrackToCscLctMatching(plotter,st)
