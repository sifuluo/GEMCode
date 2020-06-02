from ROOT import TCut
from logic import ANDtwo, ORtwo, AND, OR


nocut = TCut("")

## simtrack cuts
eta_min = 1.6
eta_max = 2.4
ok_eta_min = TCut("TMath::Abs(eta) > %f"%(eta_min))
ok_eta_max = TCut("TMath::Abs(eta) < %f"%(eta_max))
ok_eta = AND(ok_eta_min,ok_eta_max)
ok_Qp = TCut("charge > 0")
ok_Qn = TCut("charge < 0")
Ep = TCut("endcap > 0")
En = TCut("endcap < 0")


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
ok_gem_sh = TCut("has_gem_sh_even || has_gem_sh_odd")
ok_gem_sh2 = TCut("has_gem_sh2_even || has_gem_sh2_odd")
ok_gem_sh_eta = AND(ok_gem_sh, ok_eta)

## GEM digi
ok_gem_digi = TCut("has_gem_dg_even || has_gem_dg_odd")
ok_gem_digi2 = TCut("has_gem_dg2_even || has_gem_dg2_odd")
def ok_gem_pad(st):
    return TCut("GEMStub.has_gem_pad_even[st] || GEMStub.has_gem_pad_odd[st]"%(st,st))
ok_gem_pad2 = TCut("has_gem_pad2_even || has_gem_pad2_odd")
ok_gem_copad = TCut("has_gem_copad_even || has_gem_copad_odd")
ok_gem_digi_eta = AND(ok_gem_digi, ok_eta)

#ok_dphi1 = TCut("dphi_pad_odd < 10.")
#ok_dphi2 = TCut("dphi_pad_even < 10.")
#ok_gem_pad_dphi = AND(ok_gem_pad,ok_dphi)
"""
def ok_gem_pad_csc_lct(st):
    return AND(ok_gem_pad(st),ok_csc_lct(st))
ok_csc_lct_eta = AND(ok_eta,ok_csc_lct)
ok_gem_sh_csc_lct_eta = AND(ok_gem_sh, ok_csc_lct, ok_eta)
ok_gem_pad_csc_lct_eta = AND(ok_gem_pad, ok_csc_lct, ok_eta)

#ok_lct_eta_Qn = AND(ok_lct,ok_eta,ok_Qn)
#ok_lct_eta_Qp = AND(ok_lct,ok_eta,ok_Qp)
"""
