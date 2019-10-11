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
CMS_lumi.lumi_sqrtS = "14 TeV, 200 PU"

iPos = 0
if( iPos==0 ): CMS_lumi.relPosX = 0.12

#_______________________________________________________________________________
def makePlot(plotter, st, toPlot, minBin, maxBin,
             nBins, cut, xTitle, canvastitle, labeltitle):

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
    leg.AddEntry(h1, labeltitle,"pl")
    leg.Draw("same")

    rpclabel = drawLabel(plotter.stationsS.reverse_mapping[st])
    #    ctitle = drawLabel(canvastitle)

    saveAs = "%s%s_%s"%(
        plotter.targetDir,
        canvastitle,
        plotter.stations.reverse_mapping[st][4:]
    )

    c.SaveAs(saveAs + ".C")
    c.SaveAs(saveAs + ".png")
    c.SaveAs(saveAs + ".pdf")


#_______________________________________________________________________________
def makePlotTDR(plotter, toPlot, st, minBin, maxBin,
                nBins, cut, xTitle, canvastitle, labeltitle):

    yTitle = "Abitrary Units"
    title = ";%s;%s"%(xTitle,yTitle)

    h_bins = "(%d,%f,%f)"%(nBins, minBin,maxBin)

    c = newCanvas()

    h1 = draw_hist(plotter.treeEffSt['PU200'][st], title, h_bins, toPlot,
                   cut, "hist", color = kRed)


    h2 = draw_hist(plotter.treeEffSt['PU200'][st+1], title, h_bins, toPlot,
                   cut, "histsame")

    print h1.GetRMS(), h2.GetRMS()
#    h2.GetYaxis().SetTitleOffset(-0.5)

    CMS_lumi.CMS_lumi(c, iPeriod, iPos)
    h1.SetMinimum(0)
    h1.GetYaxis().SetTitleOffset(-0.5)

    leg = TLegend(0.65,0.65,.95,0.85, "", "brNDC")
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    if st == 4:
        leg.AddEntry(h1, 'iRPC (RE3/1)', "pl")
        leg.AddEntry(h2, 'RPC  (RE3/2)', "pl")
        saveAs = "%s%s_RE31_RE32_Combination"%(
            plotter.targetDir,
            canvastitle,
        )
    else:
        leg.AddEntry(h1, 'iRPC (RE4/1)', "pl")
        leg.AddEntry(h2, 'RPC  (RE4/2)', "pl")
        saveAs = "%s%s_RE41_RE42_Combination"%(
            plotter.targetDir,
            canvastitle,
        )

    leg.Draw("same")


    c.SaveAs(saveAs + ".C")
    c.SaveAs(saveAs + ".png")
    c.SaveAs(saveAs + ".pdf")
