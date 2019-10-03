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
def makeEfficiencyPlot(plotter, st, nBins, denom_cut, extra_num_cut, canvastitle):

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

    h1 = draw_geff(plotter.treeEffSt[index], title, h_bins, toPlot,
                   AND(ok_eta,denom_cut), extra_num_cut, "same")

    leg = TLegend(0.45,0.2,.75,0.35, "", "brNDC")
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    leg.AddEntry(h1, canvastitle,"pl")
    leg.Draw("same")

    csc = drawCscLabel(plotter.stationsS.reverse_mapping[st])
    saveAs = "%sEff_%s_%s"%(
        plotter.targetDir,
        plotter.stations.reverse_mapping[st][4:],
        canvastitle,
    )

    c.SaveAs(saveAs + ".C")
    c.SaveAs(saveAs + ".png")
    c.SaveAs(saveAs + ".pdf")


#_______________________________________________________________________________
def simTrackToCscSimHitMatching(plotter,st):
    makeEfficiencyPlot(plotter, st, 25, TCut(""), ok_sh, "SimHit")

#_______________________________________________________________________________
def simTrackToCscStripsWiresMatching(plotter,st=1):
    makeEfficiencyPlot(plotter, st, 25, ok_sh, ok_w, "Wire")
    makeEfficiencyPlot(plotter, st, 25, ok_sh, ok_st, "Comparator")

#_______________________________________________________________________________
def simTrackToCscAlctClctMatching(plotter,st=1):
    makeEfficiencyPlot(plotter, st, 25, ok_sh, ok_alct, "ALCT")
    makeEfficiencyPlot(plotter, st, 25, ok_sh, ok_clct, "CLCT")
    makeEfficiencyPlot(plotter, st, 25, ok_sh,
                       AND(ok_clct,ok_alct), "ALCT+CLCT")

#_______________________________________________________________________________
def simTrackToCscLctMatching(plotter,st=1):
    makeEfficiencyPlot(plotter, st, 25, ok_sh, ok_lct, "LCT")

#_______________________________________________________________________________
def simTrackToGemMatching(plotter,st=1):
    makeEfficiencyPlot(plotter, st, 25, ok_sh, ok_lct, "LCT")
