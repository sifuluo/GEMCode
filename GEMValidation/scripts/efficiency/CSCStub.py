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

def CSCAlctClct(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "CSC Stub matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "CSCStub/"

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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), ok_csc_alct(st), "same", kRed)
        h11 = draw_geff(plotter.tree, title, h_bins, toPlot, AND(ok_csc_sh(st),ok_csc_wire(st)), ok_csc_alct(st), "same", kOrange+1)
        h2 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), ok_csc_clct(st), "same",kBlue)
        h21 = draw_geff(plotter.tree, title, h_bins, toPlot, AND(ok_csc_sh(st),ok_csc_strip(st)), ok_csc_clct(st), "same",kGreen+1)

        leg = TLegend(0.45,0.2,.75,0.5, "", "brNDC");
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "ALCT","l")
        leg.AddEntry(h11, "ALCT and wires","l")
        leg.AddEntry(h2, "CLCT","l")
        leg.AddEntry(h21, "CLCT and strips","l")
        leg.Draw("same");

        csc = drawCSCLabel(cscStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_CSCStub_%s%s"%(plotter.targetDir + subdirectory, cscStations[st].labelc,  plotter.ext))


def CSCAlctClct2(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "CSC Stub matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "CSCStub/"

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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), OR(ok_csc_alct(st), ok_csc_clct(st)), "same", kRed)
        h11 = draw_geff(plotter.tree, title, h_bins, toPlot, AND(ok_csc_sh(st), ok_csc_wire(st), ok_csc_strip(st)),
                        OR(ok_csc_alct(st), ok_csc_clct(st)), "same", kOrange)
        h2 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), AND(ok_csc_alct(st), ok_csc_clct(st)), "same",kBlue)
        h21 = draw_geff(plotter.tree, title, h_bins, toPlot, AND(ok_csc_sh(st), ok_csc_wire(st), ok_csc_strip(st)),
                        AND(ok_csc_alct(st), ok_csc_clct(st)), "same",kGreen+1)

        leg = TLegend(0.45,0.2,.75,0.5, "", "brNDC");
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "ALCT OR CLCT","l")
        leg.AddEntry(h11, "ALCT OR CLCT (wires and strips)","l")
        leg.AddEntry(h2, "ALCT AND CLCT","l")
        leg.AddEntry(h21, "ALCT AND CLCT (wires and strips)","l")
        leg.Draw("same");

        csc = drawCSCLabel(cscStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_CSCStub2_%s%s"%(plotter.targetDir + subdirectory, cscStations[st].labelc,  plotter.ext))


def CSCLct(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "CSC Stub matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "CSCStub/"

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

        def ok_gem_pad_csc_lct(st):
            if st <= 2:
                return AND(ok_gem_pad(st), ok_csc_lct(st))
            else:
                return  ok_csc_lct(st)

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, AND(ok_csc_sh(st), ok_csc_alct(st), ok_csc_clct(st)), ok_csc_lct(st), "same", kRed)
        h2 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_csc_sh(st), ok_csc_lct(st), "same", kBlue)

        leg = TLegend(0.10,0.2,.75,0.35, "", "brNDC");
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.04)
        if st<=2:
            leg.AddEntry(h1, "LCT matched to ALCT and (CLCT or GEM)","l")
            leg.AddEntry(h2, "LCT","l")
        else:
            leg.AddEntry(h1, "LCT matched to ALCT and CLCT","l")
            leg.AddEntry(h2, "LCT","l")
        leg.Draw("same");

        csc = drawCSCLabel(cscStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_CSCStub3_%s%s"%(plotter.targetDir + subdirectory, cscStations[st].labelc,  plotter.ext))
