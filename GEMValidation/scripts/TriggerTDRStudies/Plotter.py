import os
import ROOT

def enum(*sequential, **named):
  enums = dict(zip(sequential, range(len(sequential))), **named)
  reverse = dict((value, key) for key, value in enums.iteritems())
  enums['reverse_mapping'] = reverse
  return type('Enum', (), enums)

class TriggerTDREfficiencyPlotter():
  def __init__(self):
    self.inputDir = os.getenv("CMSSW_BASE") + "/src/GEMCode/GEMValidation/scripts/TriggerTDRStudies/"
    self.inputFile = "../../../../out_ana_PU200_noupgrade.root"
    self.targetDir = "plots_PU200_noupgrade/"
    self.ext = ".png"
    self.analyzer = "TDRAnalyzer"
    self.effSt = "trk_eff_"
    self.stations = enum('CSC_ME11','CSC_ME1a','CSC_ME1b',
                         'CSC_ME12','CSC_ME13','CSC_ME21','CSC_ME22',
                         'CSC_ME31','CSC_ME32','CSC_ME41','CSC_ME42',
                         'GEM_ME11','GEM_ME21'
                       )
    self.stationsS = enum('ME1/1','ME1/a','ME1/b',
                          'ME1/2','ME1/3','ME2/1','ME2/2',
                          'ME3/1','ME3/2','ME4/1','ME4/2',
                          'GE1/1','GE2/1'
    )
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
                          self.stations.GEM_ME11,
                          self.stations.GEM_ME21,
    ]
    self.stationEtaLimits = [
      [1.5,2.4],
      [2.1,2.4],
      [1.5,2.2],
      [1.2,1.7],
      [0.9,1.1],

      [1.6,2.4],
      [1.0,1.6],

      [1.7,2.4],
      [1.1,1.7],

      [1.8,2.4],
      [1.1,1.8],

      [1.55,2.15],
      [1.6,2.4],
    ]
    self.file = ROOT.TFile.Open(self.inputDir + self.inputFile)
    self.dirAna = (self.file).Get(self.analyzer)
    self.treeEffSt = []
    for x in self.stationsToUse:
      self.treeEffSt.append(self.dirAna.Get(self.effSt + self.stations.reverse_mapping[x]))
    self.yMin = 0.5
    self.yMax = 1.025
    self.etaMin = 0.9
    self.etaMax = 2.4
    self.pu = 0
    self.matchAlctGem = True