from helpers.cuts import *
from helpers.drawPlots import *
from helpers.Helpers import *
from helpers.stations import *

def simTrackDigiMatchingEta(plotter):
  ## digis
  draw_geff(plotter.targetDir, "eff_eta_track_dg_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l2;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, ok_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_dg_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l2;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, ok_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_dg_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 or l2;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, OR(ok_gL2dg,ok_gL1dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_dg_gem_l1and2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 and l2;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, AND(ok_gL2dg,ok_gL1dg), "P", kBlue)

  ## digis with matched simhits
  draw_geff(plotter.targetDir, "eff_eta_track_dg_sh_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", ok_gL1sh, ok_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_dg_sh_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l2 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", ok_gL2sh, ok_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_dg_sh_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 or l2 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", OR(ok_gL2sh,ok_gL1sh),
            OR(ok_gL2dg,ok_gL1dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_dg_sh_gem_l1and2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 and l2 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", AND(ok_gL2sh,ok_gL1sh),
            AND(ok_gL2dg,ok_gL1dg), "P", kBlue)

def simTrackDigiMatchingPhi(plotter):
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta, ok_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l2;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta, ok_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 or l2;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta, OR(ok_gL2dg,ok_gL1dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l1and2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 and l2;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta, AND(ok_gL2dg,ok_gL1dg), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,ok_gL1sh), ok_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l2 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,ok_gL2sh), ok_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 or l2 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,OR(ok_gL1sh,ok_gL2sh)),
            OR(ok_gL2dg,ok_gL1dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_dg_gem_l1and2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Digi in l1 and l2 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,ok_gL1sh,ok_gL2sh),
            AND(ok_gL2dg,ok_gL1dg), "P", kBlue)


def simTrackDigiMatchingLX(plotter):
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l1_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, ok_trk_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, ok_trk_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l1or2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 or GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, OR(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l1and2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 and GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_even", nocut, AND(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l1_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, ok_trk_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, ok_trk_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l1or2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 or GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, OR(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_lx_track_dg_gem_l1and2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 and GEMl2;SimTrack localX [cm];Eff.",
            "h_", "(100,-100,100)", "gem_lx_odd", nocut, AND(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)

def simTrackDigiMatchingLY(plotter):
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l1_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", nocut, ok_trk_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", nocut, ok_trk_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l1or2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 or GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", nocut, OR(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l1and2_even", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 and GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_even", nocut, AND(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l1_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", nocut, ok_trk_gL1dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", nocut, ok_trk_gL2dg, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l1or2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 or GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", nocut, OR(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)
  draw_geff(plotter.targetDir, "eff_ly_track_dg_gem_l1and2_odd", plotter.ext, plotter.treeTracks,
            "Eff. for a SimTrack to have an associated GEM Digi in GEMl1 and GEMl2;SimTrack localy [cm];Eff.",
            "h_", "(100,-100,100)", "gem_ly_odd", nocut, AND(ok_trk_gL1dg,ok_trk_gL2dg), "P", kBlue)
