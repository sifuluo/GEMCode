from ROOT import gStyle, TH1F, TCanvas, TLegend, kRed, kBlue, kOrange, kGreen

from helpers.cuts import *
from helpers.Helpers import *
from helpers.stations import *


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

def GEMSimHitEta(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM SimHit matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/GEMSimHit/"

    for st in range(0,len(gemStations)):
        c = TCanvas("c","c",700,450)
        c.Clear()

        h_bins = "(50,%f,%f)"%(gemStations[st].eta_min,gemStations[st].eta_max)
        nBins = int(h_bins[1:-1].split(',')[0])
        minBin = float(h_bins[1:-1].split(',')[1])
        maxBin = float(h_bins[1:-1].split(',')[2])

        base = TH1F("base",title,nBins,minBin,maxBin)
        base.SetMinimum(plotter.yMin)
        base.SetMaximum(plotter.yMax)
        base.Draw("")
        base.GetXaxis().SetLabelSize(0.05)
        base.GetYaxis().SetLabelSize(0.05)
        base.GetXaxis().SetTitleSize(0.05)
        base.GetYaxis().SetTitleSize(0.05)

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_eta(gemStations[st].eta_min, gemStations[st].eta_max), ok_gem_sh(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "SimHit","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_GEMSimHit_eta_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label




def GEMSimHitPhi(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM SimHit matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #phi"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "phi"
    subdirectory = "efficiency/GEMSimHit/"

    for st in range(0,len(gemStations)):
        c = TCanvas("c","c",700,450)
        c.Clear()

        h_bins = "(50,%f,%f)"%(gemStations[st].phi_min,gemStations[st].phi_max)
        nBins = int(h_bins[1:-1].split(',')[0])
        minBin = float(h_bins[1:-1].split(',')[1])
        maxBin = float(h_bins[1:-1].split(',')[2])

        base = TH1F("base",title,nBins,minBin,maxBin)
        base.SetMinimum(plotter.yMin)
        base.SetMaximum(plotter.yMax)
        base.Draw("")
        base.GetXaxis().SetLabelSize(0.05)
        base.GetYaxis().SetLabelSize(0.05)
        base.GetXaxis().SetTitleSize(0.05)
        base.GetYaxis().SetTitleSize(0.05)

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_eta(gemStations[st].eta_min, gemStations[st].eta_max), ok_gem_sh(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "SimHit","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_GEMSimHit_phi_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label


def GEMSimHit(plotter):
    GEMSimHitEta(plotter)
    GEMSimHitPhi(plotter)
