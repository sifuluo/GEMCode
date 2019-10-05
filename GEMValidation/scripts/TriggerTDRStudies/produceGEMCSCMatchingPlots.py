## run quiet mode
import sys
sys.argv.append( '-b' )

import ROOT
ROOT.gROOT.SetBatch(1)

from cuts import *
from Plotter import TriggerTDREfficiencyPlotter
from GEMCSCValidation import makeEfficiencyPlot
from GEMCSCValidation import makeEfficiencyPlotTDR
from GEMCSCValidation import makeEfficiencyPlotTDR2
from GEMCSCValidation import simTrackToCscSimHitMatching
from GEMCSCValidation import simTrackToCscStripsWiresMatching
from GEMCSCValidation import simTrackToCscAlctClctMatching
from GEMCSCValidation import simTrackToCscLctMatching

plotter = TriggerTDREfficiencyPlotter()

for i in range(len(plotter.stationsToUse)):
  continue
  st = plotter.stationsToUse[i]
  print "Processing station ", i, plotter.stations.reverse_mapping[st]
  simTrackToCscSimHitMatching(plotter,st)
  simTrackToCscStripsWiresMatching(plotter,st)
  simTrackToCscAlctClctMatching(plotter,st)
  simTrackToCscLctMatching(plotter,st)

makeEfficiencyPlotTDR(plotter, 0, 25, ok_sh, ok_lct,  "LCT")
makeEfficiencyPlotTDR(plotter, 5, 25, ok_sh, ok_lct,  "LCT")

for i in range(0,11):
  makeEfficiencyPlotTDR2(plotter, i, 25, ok_sh, ok_alct, "ALCT")
  makeEfficiencyPlotTDR2(plotter, i, 25, ok_sh, ok_clct, "CLCT")
  makeEfficiencyPlotTDR2(plotter, i, 25, ok_sh, ok_lct, "LCT")


"""
makeEfficiencyPlotTDR2(plotter, 3, 25, ok_sh, ok_alct, "ALCT")
makeEfficiencyPlotTDR2(plotter, 4, 25, ok_sh, ok_alct, "ALCT")
makeEfficiencyPlotTDR2(plotter, 5, 25, ok_sh, ok_alct, "ALCT")
makeEfficiencyPlotTDR2(plotter, 6, 25, ok_sh, ok_alct, "ALCT")

makeEfficiencyPlotTDR2(plotter, 3, 25, ok_sh, ok_clct, "CLCT")
makeEfficiencyPlotTDR2(plotter, 4, 25, ok_sh, ok_clct, "CLCT")
makeEfficiencyPlotTDR2(plotter, 5, 25, ok_sh, ok_clct, "CLCT")
makeEfficiencyPlotTDR2(plotter, 6, 25, ok_sh, ok_clct, "CLCT")
"""
