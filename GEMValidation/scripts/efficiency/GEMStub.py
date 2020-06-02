def simTrackPadMatchingEta(plotter):
  draw_geff(plotter.targetDir, "eff_eta_track_pad_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, ok_gL1pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_pad_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l2;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, ok_gL2pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_pad_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1 or l2;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, OR(ok_gL2pad,ok_gL1pad), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_eta_track_pad_sh_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", ok_gL1sh, ok_gL1pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_pad_sh_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l2 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", ok_gL2sh, ok_gL2pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_eta_track_pad_sh_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1 or l2 with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", OR(ok_gL1sh,ok_gL2sh),
            OR(ok_gL2pad,ok_gL1pad), "P", kBlue)




def simTrackPadMatchingPhi(plotter):
  draw_geff(plotter.targetDir, "eff_phi_track_pad_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta, ok_gL1pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_pad_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l2;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta, ok_gL2pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_pad_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1 or l2;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta,
            OR(ok_gL2pad,ok_gL1pad), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_phi_track_pad_sh_gem_l1", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,ok_gL1sh), ok_gL1pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_pad_sh_gem_l2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l2 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,ok_gL2sh), ok_gL2pad, "P", kBlue)
  draw_geff(plotter.targetDir, "eff_phi_track_pad_sh_gem_l1or2", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM Pad in l1 or l2 with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,OR(ok_gL1sh,ok_gL2sh)),
            OR(ok_gL2pad,ok_gL1pad), "P", kBlue)



def simTrackCoPadMatchingEta(plotter):
  draw_geff(plotter.targetDir, "eff_eta_track_copad_gem", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM CoPad;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", nocut, AND(ok_gL1pad,ok_gL2pad), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_eta_track_copad_sh_gem", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM CoPad with a matched SimHit;SimTrack |#eta|;Eff.",
	    "h_", "(140,1.5,2.2)", "TMath::Abs(eta)", AND(ok_gL1sh,ok_gL2sh),
            AND(ok_gL1pad,ok_gL2pad), "P", kBlue)

def simTrackCoPadMatchingPhi(plotter):
  draw_geff(plotter.targetDir, "eff_phi_track_copad_gem", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM CoPad;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", ok_eta,AND(ok_gL1pad,ok_gL2pad), "P", kBlue)

  draw_geff(plotter.targetDir, "eff_phi_track_copad_sh_gem", plotter.ext, plotter.treeTracks,
	    "Eff. for a SimTrack to have an associated GEM CoPad with a matched SimHit;SimTrack #phi [rad];Eff.",
	    "h_", "(100,-3.141592654,3.141592654)", "phi", AND(ok_eta,ok_gL1sh,ok_gL2sh),
            AND(ok_gL2pad,ok_gL1pad), "P", kBlue)
