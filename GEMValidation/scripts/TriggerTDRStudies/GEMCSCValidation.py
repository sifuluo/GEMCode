from ROOT import *
from cuts import *
from Helpers import drawCscLabel
from Helpers import drawEtaLabel
from Helpers import drawPuLabel
from Helpers import draw_geff
from Helpers import newCanvas
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
def makeEfficiencyPlot(plotter, st, nBins, denom_cut, extra_num_cut):

    index = plotter.stationsToUse.index(st)
    minEta = plotter.stationEtaLimits[index][0]
    maxEta = plotter.stationEtaLimits[index][1]
    ok_eta = TCut("TMath::Abs(eta)>%f && TMath::Abs(eta)<%f"%(minEta,maxEta))
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = ";%s;%s"%(xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(minEta,maxEta)
    nBins = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    c = newCanvas()
    base = TH1F("base",title,nBins,minBin,maxBin)
    base.SetMinimum(0)
    base.SetMaximum(plotter.yMax)
    base.GetYaxis().SetTitleOffset(0.9)
    base.Draw("")
    CMS_lumi.CMS_lumi(c, iPeriod, iPos)

    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_eta, ok_sh1, "same")

    leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    leg.AddEntry(h1, "SimHits","pl")
    leg.Draw("same")

    csc = drawCscLabel(plotter.stationsS.reverse_mapping[st])
    c.SaveAs("%scsc_simhit_matching_efficiency_%s.C"%(plotter.targetDir, plotter.stations.reverse_mapping[st]))
    c.SaveAs("%scsc_simhit_matching_efficiency_%s.pdf"%(plotter.targetDir, plotter.stations.reverse_mapping[st]))
    c.SaveAs("%scsc_simhit_matching_efficiency_%s.png"%(plotter.targetDir, plotter.stations.reverse_mapping[st]))


def simTrackToCscSimHitMatching(plotter,st):
    makeEfficiencyPlot(plotter, st, 25, ok_eta, ok_sh1)


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
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
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
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
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
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
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
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
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
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
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

    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1), "same", kBlue)
#    h9 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<1 && lct_type!=-1")), "same", kGreen+4)
    h8 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<2 && lct_type!=-1")), "same", kGreen+2)
    h7 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<3 && lct_type!=-1")), "same", kOrange+2)
#    h6 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<4 && lct_type!=-1")), "same", kMagenta+2)
    h5 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<5 && lct_type!=-1")), "same", kMagenta)
#    h4 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<6 && lct_type!=-1")), "same", kOrange)
#    h3 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<7 && lct_type!=-1")), "same", kGreen)
    h2 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot, ok_sh1, AND(ok_lct1,TCut("lct_type<8 && lct_type!=-1")), "same", kRed)

    leg = TLegend(0.10,0.6,.75,0.35, "", "brNDC");
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)

    leg.AddEntry(h1, "LCT all","l")

    leg.AddEntry(h2, "LCT<8","l")
    #leg.AddEntry(h3, "LCT<7","l")
    #leg.AddEntry(h4, "LCT<6","l")
    leg.AddEntry(h5, "LCT<5","l")
    #leg.AddEntry(h6, "LCT<4","l")
    leg.AddEntry(h7, "LCT<3","l")
    leg.AddEntry(h8, "LCT<2","l")
    #leg.AddEntry(h9, "LCT<1","l")

    #else:
#    leg.AddEntry(h1, "LCT 0","l")
#    leg.AddEntry(h2, "LCT >=0","l")
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
    xTitle = "True muon |#eta|"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    h_bins = "(25,%f,%f)"%(plotter.etaMin,plotter.etaMax)
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
