#############################################
#validate displaced Muon Sample at Gen Level
#############################################
import ROOT
import numpy as n
import os
from DataFormats.FWLite import Events, Handle
ROOT.gSystem.Load("libFWCoreFWLite")
ROOT.AutoLibraryLoader.enable()

# Make VarParsing object
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideAboutPythonConfigFile#VarParsing_Example
from FWCore.ParameterSet.VarParsing import VarParsing
#options = VarParsing ('python')
#options.parseArguments()
## helper for files on dCache/EOS (LPC)
def userInputDir(inputDir):
    theInputFiles = []
    for d in range(len(inputDir)):
        my_dir = inputDir[d]
        if not os.path.isdir(my_dir):
            print "ERROR: This is not a valid directory: ", my_dir
            if d==len(inputDir)-1:
                print "ERROR: No input files were selected"
                exit()
            continue
        ls = os.listdir(my_dir)
	theInputFiles.extend([my_dir + x for x in ls if x.endswith('root')])
    return theInputFiles   
inputdir = ['/eos/uscms/store/user/tahuang/DispalcedMuonGun_1M_FlatPt1_50_FlatDxy0_50CM_GEN_SIM_CMSSW620SLHC/DispalcedMuonGun_1M_FlatPt1_50_FlatDxy0_50CM_GEN_SIM_CMSSW620SLHC/170216_235620/0000/']
inputdir = ['/eos/uscms/store/user/tahuang/DispalcedMuonGun_1M_FlatPt1_50_FlatDxy0_50CM_GEN_SIM_CMSSW620SLHC_v3/DispalcedMuonGun_1M_FlatPt1_50_FlatDxy0_50CM_GEN_SIM_CMSSW620SLHC_v3/170217_224804/0000/']
filelist = userInputDir(inputdir)
events = Events ('out_sim.root')
#events = Events (filelist)
# create handle outside of loop
handle  = Handle ('std::vector<reco::GenParticle>')

# a label is just a tuple of strings that is initialized just
# like and edm::InputTag
label = ("genParticles")

ROOT.gROOT.SetBatch()        # don't pop up canvases
f = ROOT.TFile("flatDxyDistribution_cmssw_v4.root", "recreate")
t = ROOT.TTree("displacedMuon", "tree title")


# create 1 dimensional float arrays (python's float datatype corresponds to c++ doubles)
# as fill variables
pdgid = n.zeros(1, dtype=int)
charge = n.zeros(1, dtype=int)
pt = n.zeros(1, dtype=float)
px = n.zeros(1, dtype=float)
py = n.zeros(1, dtype=float)
pz = n.zeros(1, dtype=float)
p = n.zeros(1, dtype=float)
m = n.zeros(1, dtype=float)
vx = n.zeros(1, dtype=float)
vy = n.zeros(1, dtype=float)
vz = n.zeros(1, dtype=float)
phi = n.zeros(1, dtype=float)
eta = n.zeros(1, dtype=float)
dxy = n.zeros(1, dtype=float)
lxy = n.zeros(1, dtype=float)
#check position in st1 
x_st1 = n.zeros(1, dtype=float)
y_st1 = n.zeros(1, dtype=float)
z_st1 = n.zeros(1, dtype=float)
r_st1 = n.zeros(1, dtype=float)
phi_st1 = n.zeros(1, dtype=float)
eta_st1 = n.zeros(1, dtype=float)
h_r = ROOT.TH1F("h_r","h_r",1000, 0, 1000)


# create the branches and assign the fill-variables to them
t.Branch('pdgid', pdgid, 'pdgid/I')
t.Branch('charge', charge, 'charge/I')
t.Branch('px', px, 'px/D')
t.Branch('py', py, 'py/D')
t.Branch('pz', pz, 'pz/D')
t.Branch('p', p, 'p/D')
t.Branch('pt', pt, 'pt/D')
t.Branch('vx', vx, 'vx/D')
t.Branch('vy', vy, 'vy/D')
t.Branch('vz', vz, 'vz/D')
t.Branch('dxy', dxy, 'dxy/D')
t.Branch('lxy', lxy, 'lxy/D')
t.Branch('phi', phi, 'phi/D')
t.Branch('eta', eta, 'eta/D')

t.Branch('x_st1', x_st1, 'x_st1/D')
t.Branch('y_st1', y_st1, 'y_st1/D')
t.Branch('z_st1', z_st1, 'z_st1/D')
t.Branch('r_st1', r_st1, 'r_st1/D')
t.Branch('phi_st1', phi_st1, 'phi_st1/D')
t.Branch('eta_st1', eta_st1, 'eta_st1/D')
runEvents = 100000
nevent = 0
# loop over events
for event in events:
    if (runEvents>0 and nevent >= runEvents):
	break
 # use getByLabel, just like in cmsRun
    event.getByLabel (label, handle)
    # get the product
    genplist = handle.product()
    for genp in genplist:
	if abs(genp.pdgId()) != 13:
	    continue
	#print "genp id ",genp.pdgId()," vx ",genp.vx()," vy ", genp.vy()," pt ",genp.pt()
	pdgid[0] = genp.pdgId()
    	charge[0] = genp.charge()
    	vx[0] = genp.vx()
	vy[0] = genp.vy()
	vz[0] = genp.vz()
	px[0] = genp.px()
	py[0] = genp.py()
	pz[0] = genp.pz()
	pt[0] = genp.pt()
	eta[0] = genp.eta()
	phi[0] = genp.phi()
	dxy[0]= (-vx[0]*py[0]+vy[0]*px[0])/pt[0] 
        lxy[0] = n.sqrt(vx[0]*vx[0] + vy[0]*vy[0])
    	t.Fill()
    nevent +=  1

f.Write()
f.Close()
