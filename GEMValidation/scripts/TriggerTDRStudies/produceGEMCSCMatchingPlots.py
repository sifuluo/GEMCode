import os

from ROOT import *

## run quiet mode
import sys
sys.argv.append( '-b' )

import ROOT
gROOT.SetBatch(1)

from Plotter import *

plotter = TriggerTDREfficiencyPlotter()

for i in range(len(plotter.stationsToUse)):
  st = plotter.stationsToUse[i]
  print "Processing station ", i, plotter.stations.reverse_mapping[st]
  simTrackToCscSimHitMatching(plotter,st)
  #simTrackToCscStripsWiresMatching(plotter,st)
  #simTrackToCscStripsWiresMatching_2(plotter,st)
  #simTrackToCscAlctClctMatching(plotter,st)
  #simTrackToCscAlctClctMatching_2(plotter,st)
  #simTrackToCscLctMatching(plotter,st)
  #simTrackToCscMpLctMatching(plotter,st)
