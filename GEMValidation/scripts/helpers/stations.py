class Station:

    ## constructor
    def __init__(self, eta_min, eta_max, label, labelc):
        self.eta_min = eta_min
        self.eta_max = eta_max
        self.label = label
        self.labelc = labelc

## eta-ranges for plots
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

## eta-ranges for plots
ME0 = Station(1.9, 2.9, 'ME0', 'ME0')
GE11 = Station(1.5, 2.2, 'GE1/1', 'GE11')
GE21 = Station(1.5, 2.5, 'GE2/1', 'GE21')

gemStations = [
    ME0,
    GE11,
    GE21
]
