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
ok_csc_sh = TCut("has_csc_sh_even || has_csc_sh_odd")
ok_csc_strip = TCut("has_csc_strips_even || has_csc_strips_odd")
ok_csc_wire = TCut("has_csc_wires_even || has_csc_wires_odd")
ok_csc_digi = AND(ok_csc_strip, ok_csc_wire)

## CSC stub
ok_csc_lct = TCut("has_lct_even || has_lct_odd")
ok_csc_alct = TCut("has_alct_even || has_alct_odd")
ok_csc_clct = TCut("has_clct_even || has_clct_odd")
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
ok_gem_pad = TCut("has_gem_pad_even || has_gem_pad_odd")
ok_gem_pad2 = TCut("has_gem_pad2_even || has_gem_pad2_odd")
ok_gem_copad = TCut("has_gem_copad_even || has_gem_copad_odd")
ok_gem_digi_eta = AND(ok_gem_digi, ok_eta)

#ok_dphi1 = TCut("dphi_pad_odd < 10.")
#ok_dphi2 = TCut("dphi_pad_even < 10.")
#ok_gem_pad_dphi = AND(ok_gem_pad,ok_dphi)

ok_gem_pad_csc_lct = AND(ok_gem_pad,ok_csc_lct)
ok_csc_lct_eta = AND(ok_eta,ok_csc_lct)
ok_gem_sh_csc_lct_eta = AND(ok_gem_sh, ok_csc_lct, ok_eta)
ok_gem_pad_csc_lct_eta = AND(ok_gem_pad, ok_csc_lct, ok_eta)

#ok_lct_eta_Qn = AND(ok_lct,ok_eta,ok_Qn)
#ok_lct_eta_Qp = AND(ok_lct,ok_eta,ok_Qp)
