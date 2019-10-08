from ROOT import *
from cuts import *
from Helpers import drawLabel
from Helpers import drawEtaLabel
from Helpers import drawPuLabel
from Helpers import draw_hist
from Helpers import newCanvas
import tdrstyle
import CMS_lumi

iPeriod = 0

tdrstyle.setTDRStyle()
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Phase-2 Simulation"
CMS_lumi.lumi_sqrtS = "14 TeV"

iPos = 0
if( iPos==0 ): CMS_lumi.relPosX = 0.12

#_______________________________________________________________________________
def makePlot(plotter, st, toPlot, minBin, maxBin,
             nBins, cut, xTitle, canvastitle):

    index = plotter.stationsToUse.index(st)

    yTitle = "Number of entries"
    title = ";%s;%s"%(xTitle,yTitle)

    h_bins = "(%d,%f,%f)"%(nBins, minBin,maxBin)

    c = newCanvas()

    h1 = draw_hist(plotter.treeEffSt['PU0'][index], title, h_bins, toPlot,
                   cut, "hist")

    CMS_lumi.CMS_lumi(c, iPeriod, iPos)

    h1.SetMinimum(0)
    h1.GetYaxis().SetTitleOffset(0.9)

    #c.SetLogy(1)

    leg = TLegend(0.45,0.2,.75,0.4, "", "brNDC")
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    leg.AddEntry(h1, canvastitle,"pl")
    leg.Draw("same")

    rpclabel = drawLabel(plotter.stationsS.reverse_mapping[st])
    #    ctitle = drawLabel(canvastitle)

    saveAs = "%s%s_%s_%s"%(
        plotter.targetDir,
        xTitle,
        plotter.stations.reverse_mapping[st][4:],
        canvastitle,
    )

    c.SaveAs(saveAs + ".C")
    c.SaveAs(saveAs + ".png")
    c.SaveAs(saveAs + ".pdf")
