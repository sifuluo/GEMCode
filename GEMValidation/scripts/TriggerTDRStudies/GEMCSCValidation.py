from ROOT import *
from cuts import *
from Helpers import drawCscLabel
from Helpers import drawEtaLabel
from Helpers import drawPuLabel
from Helpers import draw_geff
import tdrstyle
import CMS_lumi

iPeriod = 0

tdrstyle.setTDRStyle()
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Simulation Preliminary"
CMS_lumi.lumi_sqrtS = "14 TeV"

iPos = 0
if( iPos==0 ): CMS_lumi.relPosX = 0.12



#_______________________________________________________________________________
def simTrackToCscSimHitMatching(plotter,st=1):

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plo
    #topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    #title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    H_ref = 600;
    W_ref = 800;
    W = W_ref
    H  = H_ref

    # references for T, B, L, R
    T = 0.08*H_ref
    B = 0.12*H_ref
    L = 0.12*W_ref
    R = 0.04*W_ref

    c = TCanvas("c","c",50,50,800,600)
    c.Clear()
    c.SetLeftMargin( L/W )
    c.SetRightMargin( R/W )
    c.SetTopMargin( T/H )
    c.SetBottomMargin( B/H )
    base = TH1F("base","",nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.Draw("")
    CMS_lumi.CMS_lumi(c, iPeriod, iPos)

    index = plotter.stationsToUse.index(st)

    h1 = draw_geff(plotter.treeEffSt[index], "", h_bins, toPlot, nocut, ok_sh1, "same")
    """
    leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.06)
    leg.AddEntry(h1, "SimHits","l")
    leg.Draw("same")
    """
    #    csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #    tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_simhit_matching_efficiency_%s%s"%(plotter.targetDir, plotter.stations.reverse_mapping[st], plotter.ext))

#_______________________________________________________________________________
def simTrackToCscStripsWiresMatching(plotter,st=1):

    gStyle.SetTitleStyle(0);
    gStyle.SetTitleAlign(13); ##coord in top left
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize(0);

    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.04);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetOptStat(0);
    gStyle.SetMarkerStyle(1);

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plot
    topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(100,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = TCanvas("c","c",800,600)
    c.Clear()
    base  = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.Draw("")
    base.GetXaxis().SetLabelSize(0.05)
    base.GetYaxis().SetLabelSize(0.05)
    base.GetXaxis().SetTitleSize(0.05)
    base.GetYaxis().SetTitleSize(0.05)

    index = plotter.stationsToUse.index(st)

    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, ok_w1, "same", kRed)
    h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, ok_st1, "same")

    leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.06)
    leg.AddEntry(h1, "Wires","l")
    leg.AddEntry(h2, "Strips","l")
    leg.Draw("same")

    csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_digi_matching_efficiency_%s%s"%(plotter.targetDir,plotter.stations.reverse_mapping[st],plotter.ext))


#_______________________________________________________________________________
def simTrackToCscStripsWiresMatching_2(plotter,st=1):

    """
    gStyle.SetTitleStyle(0)
    gStyle.SetTitleAlign(13) ##coord in top left
    gStyle.SetTitleX(0.)
    gStyle.SetTitleY(1.)
    gStyle.SetTitleW(1)
    gStyle.SetTitleH(0.058)
    gStyle.SetTitleBorderSize(0)

    gStyle.SetPadLeftMargin(0.126)
    gStyle.SetPadRightMargin(0.04)
    gStyle.SetPadTopMargin(0.06)
    gStyle.SetPadBottomMargin(0.13)
    gStyle.SetOptStat(0)
    gStyle.SetMarkerStyle(1)
    """

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plot
    topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(100,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = TCanvas("c","c",800,600)
    c.Clear()
    base  = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.GetXaxis().SetLabelSize(0.05)
    base.GetYaxis().SetLabelSize(0.05)
    base.GetXaxis().SetTitleSize(0.05)
    base.GetYaxis().SetTitleSize(0.05)
    base.SetTitle(topTitle)
    base.Draw("")

    index = plotter.stationsToUse.index(st)

    h1 = draw_geff(plotter.treeEffSt[index], topTitle, h_bins, toPlot, ok_sh1, OR(ok_w1,ok_st1), "same", kRed)
    h2 = draw_geff(plotter.treeEffSt[index], topTitle, h_bins, toPlot, ok_sh1, AND(ok_w1,ok_st1), "same")

    leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC");
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.06)
    leg.AddEntry(h1, "Wires OR strips","l")
    leg.AddEntry(h2, "Wires AND strips","l")
    leg.Draw("same");

    #csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_combined_digi_matching_efficiency_%s%s"%(plotter.targetDir,plotter.stations.reverse_mapping[st],plotter.ext))


#_______________________________________________________________________________
def simTrackToCscAlctClctMatching(plotter,st=1):

    gStyle.SetTitleStyle(0);
    gStyle.SetTitleAlign(13); ##coord in top left
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize(0);

    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.04);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetOptStat(0);
    gStyle.SetMarkerStyle(1);

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plot
    topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(100,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = TCanvas("c","c",800,600)
    c.Clear()
    base  = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.Draw("")
    base.GetXaxis().SetLabelSize(0.05)
    base.GetYaxis().SetLabelSize(0.05)
    base.GetXaxis().SetTitleSize(0.05)
    base.GetYaxis().SetTitleSize(0.05)

    index = plotter.stationsToUse.index(st)

    #h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, ok_alct1, "same", kRed)
    h11 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1,ok_w1), ok_alct1, "same", kRed)
    #h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, ok_clct1, "same",kBlue)
    h21 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1,ok_st1), ok_clct1, "same",kBlue)

    leg = TLegend(0.45,0.2,.75,0.5, "", "brNDC");
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.06)
    #leg.AddEntry(h1, "ALCT","l")
    leg.AddEntry(h11, "ALCT provided wires","l")
    #leg.AddEntry(h2, "CLCT","l")
    leg.AddEntry(h21, "CLCT provided strips","l")
    base.SetTitle(topTitle)
    leg.Draw("same");

    #csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_stub_matching_efficiency_%s%s"%(plotter.targetDir,plotter.stations.reverse_mapping[st],plotter.ext))


#_______________________________________________________________________________
def simTrackToCscAlctClctMatching_2(plotter,st=1):

    gStyle.SetTitleStyle(0);
    gStyle.SetTitleAlign(13); ##coord in top left
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize(0);

    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.04);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetOptStat(0);
    gStyle.SetMarkerStyle(1);

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plot
    topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(100,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = TCanvas("c","c",800,600)
    c.Clear()
    base  = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.GetXaxis().SetLabelSize(0.05)
    base.GetYaxis().SetLabelSize(0.05)
    base.GetXaxis().SetTitleSize(0.05)
    base.GetYaxis().SetTitleSize(0.05)
    base.SetTitle(topTitle)
    base.Draw("")

    index = plotter.stationsToUse.index(st)

    #h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, OR(ok_alct1,ok_clct1), "same", kRed)
    h11 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1,ok_st1,ok_w1), OR(ok_alct1,ok_clct1), "same", kRed)
    #h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_alct1,ok_clct1), "same",kBlue)
    h21 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1,ok_st1,ok_w1), AND(ok_alct1,ok_clct1), "same",kBlue)

    leg = TLegend(0.45,0.2,.75,0.5, "", "brNDC");
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.06)
    #leg.AddEntry(h1, "ALCT OR CLCT","l")
    leg.AddEntry(h11, "ALCT OR CLCT provided wires and strips","l")
    #leg.AddEntry(h2, "ALCT AND CLCT","l")
    leg.AddEntry(h21, "ALCT AND CLCT provided wires and strips","l")
    leg.Draw("same");

    #csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_combined_stub_matching_efficiency_%s%s"%(plotter.targetDir,plotter.stations.reverse_mapping[st],plotter.ext))


#_______________________________________________________________________________
def simTrackToCscLctMatching(plotter,st=1):

    gStyle.SetTitleStyle(0);
    gStyle.SetTitleAlign(13); ##coord in top left
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize(0);

    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.04);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetOptStat(0);
    gStyle.SetMarkerStyle(1);

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plot
    topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(50,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = TCanvas("c","c",800,600)
    c.Clear()
    base  = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.GetXaxis().SetLabelSize(0.05)
    base.GetYaxis().SetLabelSize(0.05)
    base.GetXaxis().SetTitleSize(0.05)
    base.GetYaxis().SetTitleSize(0.05)
    base.SetTitle(topTitle)
    base.Draw("")

    index = plotter.stationsToUse.index(st)

    """
    if plotter.matchAlctGem:
    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1, ok_alct1,OR(ok_clct1,ok_pad1)), ok_lct1, "same", kRed)
    h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, ok_lct1, "same", kBlue)
    else:
    """

    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1,ok_st1,ok_w1,OR(ok_alct1, ok_clct1)), AND(ok_lct1,TCut("lct_type==0")), "same", kRed)
    h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1,ok_st1,ok_w1,OR(ok_alct1, ok_clct1)), AND(ok_lct1), "same", kBlue)

    leg = TLegend(0.10,0.2,.75,0.35, "", "brNDC");
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)
    """
    if plotter.matchAlctGem:
    leg.AddEntry(h1, "LCT matched to ALCT and (CLCT or GEM)","l")
    leg.AddEntry(h2, "LCT","l")
    """
    #else:
    leg.AddEntry(h1, "LCT 0","l")
    leg.AddEntry(h2, "LCT >=0","l")
    leg.Draw("same");

    #csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_lct_matching_efficiency_%s%s"%(plotter.targetDir,plotter.stations.reverse_mapping[st],plotter.ext))

#_______________________________________________________________________________
def simTrackToCscMpLctMatching(plotter,st=1):

    gStyle.SetTitleStyle(0);
    gStyle.SetTitleAlign(13); ##coord in top left
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize(0);

    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.04);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetOptStat(0);
    gStyle.SetMarkerStyle(1);

    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(plotter.etaMin,plotter.etaMax))

    ## variables for the plot
    topTitle = " " * 11 + "CMS Simulation Preliminary" + " " * 35 + "14 TeV, PU0"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(100,%f,%f)"%(plotter.etaMin,plotter.etaMax)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = TCanvas("c","c",800,600)
    c.Clear()
    base  = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(plotter.yMin)
    base.SetMaximum(plotter.yMax)
    base.Draw("")
    base.GetXaxis().SetLabelSize(0.05)
    base.GetYaxis().SetLabelSize(0.05)
    base.GetXaxis().SetTitleSize(0.05)
    base.GetYaxis().SetTitleSize(0.05)

    index = plotter.stationsToUse.index(st)

    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, AND(ok_sh1, ok_alct1, ok_clct1), ok_mplct1, "same", kRed)
    h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, ok_mplct1, "same", kBlue)

    leg = TLegend(0.10,0.2,.75,0.35, "", "brNDC");
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)
    leg.AddEntry(h1, "MPLCT matched to ALCT and CLCT","l")
    leg.AddEntry(h2, "MPLCT","l")
    leg.Draw("same");

    csc = drawCscLabel(plotter.stations.reverse_mapping[st], 0.17,0.17,0.05)
    #pul = drawPuLabel(plotter.pu,0.17,0.17,0.05)
    #tex = drawEtaLabel(plotter.etaMin,plotter.etaMax,0.2,0.8,0.05)

    c.SaveAs("%scsc_mplct_matching_efficiency_%s%s"%(plotter.targetDir,plotter.stations.reverse_mapping[st],plotter.ext))
