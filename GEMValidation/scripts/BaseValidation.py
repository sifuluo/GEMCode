import os
from ROOT import TFile

def enum(*sequential, **named):
  enums = dict(zip(sequential, range(len(sequential))), **named)
  reverse = dict((value, key) for key, value in enums.iteritems())
  enums['reverse_mapping'] = reverse
  return type('Enum', (), enums)

class GEMCSCStubPlotter():
  def __init__(self):
    self.inputDir = os.getenv("CMSSW_BASE") + "/src/"
    self.inputFile = "out_ana.root"
    self.targetDir = "gem_csc_matching/"
    self.ext = ".pdf"
    self.analyzer = "GEMCSCAnalyzer"
    self.effSt = "trk_eff_"
    self.stations = enum('CSC_ALL','CSC_ME11','CSC_ME1a','CSC_ME1b','CSC_ME12','CSC_ME13',
                         'CSC_ME21','CSC_ME22','CSC_ME31','CSC_ME32','CSC_ME41','CSC_ME42')
    self.stationsToUse = [self.stations.CSC_ME11,
                          self.stations.CSC_ME1a,
                          self.stations.CSC_ME1b,
                          self.stations.CSC_ME12,
                          self.stations.CSC_ME13,
                          self.stations.CSC_ME21,
                          self.stations.CSC_ME22,
                          self.stations.CSC_ME31,
                          self.stations.CSC_ME32,
                          self.stations.CSC_ME41,
                          self.stations.CSC_ME42
    ]
    self.file = TFile.Open(self.inputDir + self.inputFile)
    self.dirAna = (self.file).Get(self.analyzer)
    self.treeEffSt = []
    for x in self.stationsToUse:
      self.treeEffSt.append(self.dirAna.Get(self.effSt + self.stations.reverse_mapping[x]))
    self.yMin = 0.5
    self.yMax = 1.1
    self.etaMin = 0.9
    self.etaMax = 2.4
    self.pu = 140
    self.matchAlctGem = True
