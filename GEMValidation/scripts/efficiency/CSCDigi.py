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

def CSCComp(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "CSC Digi matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/CSCDigi/"


    for st in range(0,len(cscStations)):

        h_bins = "(50,%f,%f)"%(cscStations[st].eta_min,cscStations[st].eta_max)
        nBins = int(h_bins[1:-1].split(',')[0])
        minBin = float(h_bins[1:-1].split(',')[1])
        maxBin = float(h_bins[1:-1].split(',')[2])

        c = TCanvas("c","c",700,450)
        c.Clear()
        base  = TH1F("base",title,nBins,minBin,maxBin)
        base.SetMinimum(plotter.yMin)
        base.SetMaximum(plotter.yMax)
        base.Draw("")
        base.GetXaxis().SetLabelSize(0.05)
        base.GetYaxis().SetLabelSize(0.05)
        base.GetXaxis().SetTitleSize(0.05)
        base.GetYaxis().SetTitleSize(0.05)

        h2 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), ok_csc_strip(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h2, "Comparators","l")
        leg.Draw("same")

        csc = drawCSCLabel(cscStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_CSCComp_%s%s"%(plotter.targetDir + subdirectory, cscStations[st].labelc,  plotter.ext))

        del c, base, leg, csc, h2

def CSCWire(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "CSC Digi matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/CSCDigi/"


    for st in range(0,len(cscStations)):

        h_bins = "(50,%f,%f)"%(cscStations[st].eta_min,cscStations[st].eta_max)
        nBins = int(h_bins[1:-1].split(',')[0])
        minBin = float(h_bins[1:-1].split(',')[1])
        maxBin = float(h_bins[1:-1].split(',')[2])

        c = TCanvas("c","c",700,450)
        c.Clear()
        base  = TH1F("base",title,nBins,minBin,maxBin)
        base.SetMinimum(plotter.yMin)
        base.SetMaximum(plotter.yMax)
        base.Draw("")
        base.GetXaxis().SetLabelSize(0.05)
        base.GetYaxis().SetLabelSize(0.05)
        base.GetXaxis().SetTitleSize(0.05)
        base.GetYaxis().SetTitleSize(0.05)

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), ok_csc_wire(st), "same", kRed)

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Wires","l")
        leg.Draw("same")

        csc = drawCSCLabel(cscStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_CSCWire_%s%s"%(plotter.targetDir + subdirectory, cscStations[st].labelc,  plotter.ext))

        del c, base, leg, csc, h1

def CSCCompWire(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "CSC Digi matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/CSCDigi/"


    for st in range(0,len(cscStations)):

        h_bins = "(50,%f,%f)"%(cscStations[st].eta_min,cscStations[st].eta_max)
        nBins = int(h_bins[1:-1].split(',')[0])
        minBin = float(h_bins[1:-1].split(',')[1])
        maxBin = float(h_bins[1:-1].split(',')[2])

        c = TCanvas("c","c",700,450)
        c.Clear()
        base  = TH1F("base",title,nBins,minBin,maxBin)
        base.SetMinimum(plotter.yMin)
        base.SetMaximum(plotter.yMax)
        base.Draw("")
        base.GetXaxis().SetLabelSize(0.05)
        base.GetYaxis().SetLabelSize(0.05)
        base.GetXaxis().SetTitleSize(0.05)
        base.GetYaxis().SetTitleSize(0.05)

        h2 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), AND(ok_csc_wire(st), ok_csc_strip(st)), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC");
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h2, "Wires and comparators","l")
        leg.Draw("same");

        csc = drawCSCLabel(cscStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_CSCCompWire_%s%s"%(plotter.targetDir + subdirectory, cscStations[st].labelc,  plotter.ext))

        del c, base, leg, csc, h2

def CSCDigi(plotter):
    CSCComp(plotter)
    CSCWire(plotter)
    CSCCompWire(plotter)
