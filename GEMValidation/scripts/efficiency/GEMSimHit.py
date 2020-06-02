from helpers.cuts import *
from helpers.Helpers import *
from helpers.stations import *






def gemSimTrackToSimHitMatchingLX(plotter):
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l1_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, ok_trk_gL1sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, ok_trk_gL2sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l1or2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 or GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, OR(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l1and2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 and GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, AND(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l1_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, ok_trk_gL1sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, ok_trk_gL2sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l1or2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 or GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, OR(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_sh_gem_l1and2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 and GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, AND(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)

def gemSimTrackToSimHitMatchingLY(plotter):
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l1_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", ok_lx_even, ok_trk_gL1sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", ok_lx_even, ok_trk_gL2sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l1or2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 or GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", ok_lx_even, OR(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l1and2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 and GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", ok_lx_even, AND(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l1_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", ok_lx_odd, ok_trk_gL1sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", ok_lx_odd, ok_trk_gL2sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l1or2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 or GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", ok_lx_odd, OR(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_sh_gem_l1and2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 and GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", ok_lx_odd, AND(ok_trk_gL1sh,ok_trk_gL2sh), "P", kBlue)

def gemSimTrackToSimHitMatchingEta(plotter):
  draw_geff(plotter.targetDir, "eff_eta_track_sh_gem_l1or2", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 or GEMl2;SimTrack |#eta|;Eff.",
            "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, OR(ok_gL1sh,ok_gL2sh), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_sh_gem_l1", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1;SimTrack |#eta|;Eff.",
            "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, ok_gL1sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_sh_gem_l2", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl2;SimTrack |#eta|;Eff.",
            "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, ok_gL2sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_sh_gem_l1and2", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 and GEMl2;SimTrack |#eta|;Eff.",
            "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, AND(ok_gL1sh,ok_gL2sh), "P", kBlue)

def gemSimTrackToSimHitMatchingPhi(plotter):
  draw_geff(plotter.targetDir, "eff_phi_track_sh_gem_l1or2", plotter.ext, plotter.treeTracks,
  	    "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 or GEMl2;SimTrack #phi [rad];Eff.",
  	    "h_", "(100,-3.14159265358979312,3.14159265358979312)", "phi", ok_eta, OR(ok_gL1sh,ok_gL2sh), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_sh_gem_l1", plotter.ext, plotter.treeTracks,
  	    "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1;SimTrack #phi [rad];Eff.",
  	    "h_", "(100,-3.14159265358979312,3.14159265358979312)", "phi", ok_eta, ok_gL1sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_sh_gem_l2", plotter.ext, plotter.treeTracks,
  	    "Eff. for a SimTrack to have an associated GEM SimHit in GEMl2;SimTrack #phi [rad];Eff.",
  	    "h_", "(100,-3.14159265358979312,3.14159265358979312)", "phi", ok_eta, ok_gL2sh, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_sh_gem_l1and2", plotter.ext, plotter.treeTracks,
  	    "Eff. for a SimTrack to have an associated GEM SimHit in GEMl1 and GEMl2;SimTrack #phi [rad];Eff.",
  	    "h_", "(100,-3.14159265358979312,3.14159265358979312)", "phi", ok_eta, AND(ok_gL1sh,ok_gL2sh), "P", kBlue)
