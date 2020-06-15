class Station:

    ## constructor
    def __init__(self, eta_min, eta_max, label, labelc):
        self.eta_min = eta_min
        self.eta_max = eta_max
        self.label = label
        self.labelc = labelc
        self.phi_min = -3.2
        self.phi_max = 3.2

## csc
ME11 = Station(1.5, 2.5, 'ME1/1', 'ME11')
ME1a = Station(2.1, 2.5, 'ME1/a', 'ME1a')
ME1b = Station(1.5, 2.2, 'ME1/b', 'ME1b')
ME12 = Station(1.2, 1.6, 'ME1/2', 'ME12')
ME13 = Station(0.9, 1.2, 'ME1/3', 'ME13')
ME21 = Station(1.5, 2.5, 'ME2/1', 'ME21')
ME22 = Station(1.2, 2.5, 'ME2/2', 'ME22')
ME31 = Station(1.5, 2.5, 'ME3/1', 'ME31')
ME32 = Station(1.2, 2.5, 'ME3/2', 'ME32')
ME41 = Station(1.5, 2.5, 'ME4/1', 'ME41')
ME42 = Station(1.2, 2.5, 'ME4/2', 'ME42')

cscStations = [
    ME11, ME1a, ME1b, ME12, ME13,
    ME21, ME22, ME31, ME32, ME41, ME42
]

## gem
ME0 = Station(2, 2.8, 'ME0', 'ME0')
GE11 = Station(1.6, 2.15, 'GE1/1', 'GE11')
GE21 = Station(1.6, 2.4, 'GE2/1', 'GE21')

gemStations = [
    ME0,
    GE11,
    GE21
]

## rpc
RE12 = Station(1.2, 1.6, 'RE1/2', 'RE12')
RE13 = Station(0.9, 1.2, 'RE1/3', 'RE13')
RE22 = Station(1.2, 2.5, 'RE2/2', 'RE22')
RE23 = Station(1.5, 2.5, 'RE2/3', 'RE23')
RE31 = Station(1.5, 2.5, 'RE3/1', 'RE31')
RE32 = Station(1.2, 2.5, 'RE3/2', 'RE32')
RE33 = Station(1.2, 2.5, 'RE3/3', 'RE33')
RE41 = Station(1.5, 2.5, 'RE4/1', 'RE41')
RE42 = Station(1.2, 2.5, 'RE4/2', 'RE42')
RE43 = Station(1.2, 2.5, 'RE4/3', 'RE43')

rpcStations = [
    RE12, RE13,
    RE22, RE23,
    RE31, RE32, RE33,
    RE41, RE42, RE43
]
