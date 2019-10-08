## run quiet mode
import sys
sys.argv.append( '-b' )

import ROOT
ROOT.gROOT.SetBatch(1)

from cuts import *
from Plotter import RPCTimingPlotter
from RPCValidation import makePlot

plotter = RPCTimingPlotter()

print plotter.stationsToUse

for i in range(len(plotter.stationsToUse)):

  st = plotter.stationsToUse[i]

  print "Processing station ", i, plotter.stations.reverse_mapping[st]
  makePlot(plotter, st, "rpc_time", -5, 5, 100, AND(has_rpc, TCut("pt>10")), "Timing", "RecHit")
  makePlot(plotter, st, "rpc_timeError", 0, 10, 10, AND(has_rpc, TCut("pt>10")), "TimingError", "RecHit")
  makePlot(plotter, st, "rpc_bunchX", -5, 5, 100, AND(has_rpc, TCut("pt>10")), "BunchX", "RecHit")
  makePlot(plotter, st, "rpc_firstClusterStrip", 0, 100, 100, AND(has_rpc, TCut("pt>10")), "FirstClusterStrip", "RecHit")
  makePlot(plotter, st, "rpc_clusterSize", 0, 10, 10, AND(has_rpc, TCut("pt>10")), "ClusterSize", "RecHit")
