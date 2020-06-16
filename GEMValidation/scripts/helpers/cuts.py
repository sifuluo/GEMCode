from ROOT import TCut
from logic import ANDtwo, ORtwo, AND, OR


nocut = TCut("")

## eta for a station
def ok_eta(eta_min, eta_max):
    ok_eta_min = TCut("TMath::Abs(eta) > %f"%(eta_min))
    ok_eta_max = TCut("TMath::Abs(eta) < %f"%(eta_max))
    ok_eta = AND(ok_eta_min,ok_eta_max)
    return ok_eta

def ok_phi(phi_min, phi_max):
    ok_phi_min = TCut("phi > %f"%(phi_min))
    ok_phi_max = TCut("phi < %f"%(phi_max))
    ok_phi = AND(ok_phi_min,ok_phi_max)
    return ok_phi

## CSC simhits & digis
def ok_csc_sh(st):
    return TCut("CSCSimHit.has_csc_sh_even[%d] || CSCSimHit.has_csc_sh_odd[%d]"%(st,st))

def ok_csc_strip(st):
    return TCut("CSCDigi.has_csc_strips_even[%d] || CSCDigi.has_csc_strips_odd[%d]"%(st,st))

def ok_csc_wire(st):
    return TCut("CSCDigi.has_csc_wires_even[%d] || CSCDigi.has_csc_wires_odd[%d]"%(st,st))

def ok_csc_digi(st):
    return AND(ok_csc_strip(st), ok_csc_wire(st))

## CSC stub
def ok_csc_lct(st):
    return TCut("CSCStub.has_lct_even[%d] || CSCStub.has_lct_odd[%d]"%(st,st))

def ok_csc_alct(st):
    return TCut("CSCStub.has_alct_even[%d] || CSCStub.has_alct_odd[%d]"%(st,st))

def ok_csc_clct(st):
    return TCut("CSCStub.has_clct_even[%d] || CSCStub.has_clct_odd[%d]"%(st,st))

#ok_lct_hs_min = TCut("hs_lct_odd > 4")
#ok_lct_hs_max = TCut("hs_lct_odd < 125")
#ok_lct_hs = AND(ok_lct_hs_min,ok_lct_hs_max)
#ok_lct_hs = AND(ok_lct,ok_lct_hs)

## GEM simhit
def ok_gem_sh(st):
    return TCut("GEMSimHit.has_gem_sh_even[%d] || GEMSimHit.has_gem_sh_odd[%d]"%(st,st))

def ok_gem_sh2(st):
    return TCut("GEMSimHit.has_gem_sh2_even[%d] || GEMSimHit.has_gem_sh2_odd[%d]"%(st,st))

## GEM digi
def ok_gem_dg(st):
    return TCut("GEMDigi.has_gem_dg_even[%d] || GEMDigi.has_gem_dg_odd[%d]"%(st,st))

def ok_gem_dg2(st):
    return TCut("GEMDigi.has_gem_dg2_even[%d] || GEMDigi.has_gem_dg2_odd[%d]"%(st,st))

## GEM stub
def ok_gem_pad(st):
    return TCut("GEMStub.has_gem_pad_even[%d] || GEMStub.has_gem_pad_odd[%d]"%(st,st))

def ok_gem_pad2(st):
    return TCut("GEMStub.has_gem_pad2_even[%d] || GEMStub.has_gem_pad2_odd[%d]"%(st,st))

def ok_gem_copad(st):
    return TCut("GEMStub.has_gem_copad_even[%d] || GEMStub.has_gem_copad_odd[%d]"%(st,st))

def ok_gem_cluster(st):
    return TCut("GEMStub.has_gem_cluster_even[%d] || GEMStub.has_gem_cluster_odd[%d]"%(st,st))

## L1Mu
def ok_emtf():
    return TCut("L1MuStruct.has_emtfTrack")

def ok_emtf():
    return TCut("L1MuStruct.has_emtfRegCand")

def ok_l1mu():
    return TCut("L1MuStruct.has_gmtCand")
