import os
import ROOT

def enum(*sequential, **named):
  enums = dict(zip(sequential, range(len(sequential))), **named)
  reverse = dict((value, key) for key, value in enums.iteritems())
  enums['reverse_mapping'] = reverse
  return type('Enum', (), enums)

inputFiles = {
  'PU0'    : "out_ana_PU0_RPC.root",
#  'PU200'  : "out_ana_PU200_RPC.root",
#  'PU300'  : "out_ana_PU300_RPC.root",
}

class RPCTimingPlotter():
  def __init__(self):
    self.inputDir = os.getenv("CMSSW_BASE") + "/src/GEMCode/GEMValidation/scripts/RPCTimingStudies/"
    self.inputFiles = inputFiles
    self.targetDir = "plots_rpc/"
    self.analyzer = "RPCTimingAnalyzer"
    self.effSt = "trk_eff_"
    self.stations = enum(
      'RPC_ME12',
      'RPC_ME13',
      'RPC_ME22',
      'RPC_ME23',
      'RPC_ME31',
      'RPC_ME32',
      'RPC_ME33',
      'RPC_ME41',
      'RPC_ME42',
      'RPC_ME43',
    )
    self.stationsS = enum(
      'RE1/2',
      'RE1/3',
      'RE2/2',
      'RE2/3',
      'RE3/1',
      'RE3/2',
      'RE3/3',
      'RE4/1',
      'RE4/2',
      'RE4/3',
    )
    self.stationsToUse = [
      self.stations.RPC_ME12,
      self.stations.RPC_ME13,
      self.stations.RPC_ME22,
      self.stations.RPC_ME23,
      self.stations.RPC_ME31,
      self.stations.RPC_ME32,
      self.stations.RPC_ME33,
      self.stations.RPC_ME41,
      self.stations.RPC_ME42,
      self.stations.RPC_ME43,
    ]
    self.stationEtaLimits = [
      [1.2,1.7],
      [0.9,1.1],
      [1.0,1.25],
      [1.25,1.6],
      [1.8,2.4],
      [1.4,1.8],
      [1.1,1.4],
      [1.9,2.4],
      [1.5,1.9],
      [1.2,1.5],
    ]
    self.files = {}
    self.dirAna = {}
    self.treeEffSt = {}
    for p in inputFiles:
      self.files[p] = ROOT.TFile.Open(self.inputDir + inputFiles[p])
      print self.files[p], self.analyzer
      self.dirAna[p] = (self.files[p]).Get(self.analyzer)
      self.treeEffSt[p] = []
      for x in self.stationsToUse:
        print "branch", self.effSt + self.stations.reverse_mapping[x]
        self.treeEffSt[p].append(self.dirAna[p].Get(self.effSt + self.stations.reverse_mapping[x]))
    self.yMin = 0.5
    self.yMax = 1.025
    self.etaMin = 0.9
    self.etaMax = 2.4
    self.pu = 0
