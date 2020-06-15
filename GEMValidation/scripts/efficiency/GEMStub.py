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

def GEMPadEta(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM Pad matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/GEMStub/"

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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh(st), ok_gem_pad(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Pad","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_GEMPad_eta_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label




def GEMPadPhi(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM Pad matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #phi"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "phi"
    subdirectory = "efficiency/GEMStub/"

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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh(st), ok_gem_pad(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Pad","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)
        c.Print("%sEff_GEMPad_phi_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label


def GEMPadEta2(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM Pad matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/GEMStub/"

    for st in range(1,len(gemStations)):
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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh2(st), ok_gem_pad2(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Two pads","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_GEMPad2_eta_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label




def GEMPadPhi2(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM Pad matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #phi"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "phi"
    subdirectory = "efficiency/GEMStub/"

    for st in range(1,len(gemStations)):
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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh2(st), ok_gem_pad2(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Two pads","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)
        c.Print("%sEff_GEMPad2_phi_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label


def GEMCoPadEta(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM CoPad matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/GEMStub/"

    for st in range(1,len(gemStations)):
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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh2(st), ok_gem_copad(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "CoPad","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_GEMCoPad_eta_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label




def GEMCoPadPhi(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM CoPad matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #phi"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "phi"
    subdirectory = "efficiency/GEMStub/"

    for st in range(1,len(gemStations)):
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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh2(st), ok_gem_copad(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "CoPad","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)
        c.Print("%sEff_GEMCoPad_phi_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label


def GEMClusterEta(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM Cluster matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #eta"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "TMath::Abs(eta)"
    subdirectory = "efficiency/GEMStub/"

    for st in range(1,len(gemStations)):
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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh(st), ok_gem_cluster(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Cluster","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)

        c.Print("%sEff_GEMCluster_eta_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label




def GEMClusterPhi(plotter):

    ## variables for the plot
    topTitle = " " * 11 + "GEM Cluster matching" + " " * 35 + "CMS Simulation Preliminary"
    xTitle = "True muon #phi"
    yTitle = "Efficiency"
    title = "%s;%s;%s"%(topTitle,xTitle,yTitle)
    toPlot = "phi"
    subdirectory = "efficiency/GEMStub/"

    for st in range(1,len(gemStations)):
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

        h1 = draw_geff(plotter.tree, title, h_bins, toPlot, ok_gem_sh(st), ok_gem_cluster(st), "same")

        leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.06)
        leg.AddEntry(h1, "Cluster","l")
        leg.Draw("same")

        label = drawCSCLabel(gemStations[st].label, 0.87,0.87,0.05)
        c.Print("%sEff_GEMCluster_phi_%s%s"%(plotter.targetDir + subdirectory, gemStations[st].labelc,  plotter.ext))

        del c, base, h1, leg, label


def GEMStub(plotter):
    GEMPadEta(plotter)
    GEMPadPhi(plotter)
    return
    #GEMPadEta2(plotter)
    #GEMPadPhi2(plotter)
    #GEMCoPadEta(plotter)
    #GEMCoPadPhi(plotter)
    #GEMClusterEta(plotter)
    #GEMClusterPhi(plotter)
