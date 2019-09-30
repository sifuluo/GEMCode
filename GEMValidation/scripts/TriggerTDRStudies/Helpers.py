from ROOT import *
from cuts import *
from ROOT import TStyle

def newCanvas():
    H_ref = 600;
    W_ref = 800;
    H  = H_ref
    W = W_ref

    # references for T, B, L, R
    T = 0.08*H_ref
    B = 0.12*H_ref
    L = 0.12*W_ref
    R = 0.04*W_ref

    c = TCanvas("c","c",50,50,W,H)
    c.Clear()
    c.SetLeftMargin( L/W )
    c.SetRightMargin( R/W )
    c.SetTopMargin( T/H )
    c.SetBottomMargin( B/H )

    SetOwnership(c, False)
    return c


#_______________________________________________________________________________
def drawCscLabel(title, x=0.17, y=0.17, font_size=0.):
    tex = TText(x, y, title)
    tex.SetTextSize(0.05)
    tex.SetNDC()
    tex.Draw()
    SetOwnership(tex, False)
    return tex


#_______________________________________________________________________________
def drawEtaLabel(minEta, maxEta, x=0.17, y=0.35, font_size=0.):
    tex = TLatex(x, y,"%.2f < |#eta| < %.2f"%(minEta,maxEta))
    tex.SetTextSize(font_size)
    tex.SetTextSize(0.05)
    tex.SetNDC()
    tex.Draw()
    SetOwnership(tex, False)
    return tex


#_______________________________________________________________________________
def drawPuLabel(pu, x=0.17, y=0.35, font_size=0.):
    tex = TLatex(x, y,"<PU> = %d"%(pu))
    tex.SetTextSize(font_size)
    tex.SetTextSize(0.05)
    tex.SetNDC()
    tex.Draw()
    SetOwnership(tex, False)
    return tex

#_______________________________________________________________________________
def draw_geff(t, title, h_bins, to_draw, den_cut, extra_num_cut,
              opt = "", color = kBlue, marker_st = 21, marker_sz = 1.):
    """Make an efficiency plot"""

    ## total numerator selection cut
    ## the extra brackets around the extra_num_cut are necessary !!
    num_cut = AND(den_cut,extra_num_cut)
    debug = False
    if debug:
        print "Denominator cut", den_cut
        print "Numerator cut", num_cut

    ## PyROOT works a little different than ROOT when you are plotting
    ## histograms directly from tree. Hence, this work-around
    nBins  = int(h_bins[1:-1].split(',')[0])
    minBin = float(h_bins[1:-1].split(',')[1])
    maxBin = float(h_bins[1:-1].split(',')[2])

    num = TH1F("num",title, nBins, minBin, maxBin)
    den = TH1F("den",title, nBins, minBin, maxBin)

    print t
    t.Draw(to_draw + ">>num", num_cut, "goff")
    t.Draw(to_draw + ">>den", den_cut, "goff")

    ## check if the number of passed entries larger than total entries
    doConsistencyCheck = False
    if doConsistencyCheck:
        for i in range(0,nBins):
            print i, num.GetBinContent(i), den.GetBinContent(i)
            if num.GetBinContent(i) > den.GetBinContent(i):
                print ">>>Error: passed entries > total entries"

    eff = TEfficiency(num, den)

    ## plotting options
    if not "same" in opt:
        num.Reset()
        num.GetYaxis().SetRangeUser(0.5,1.1)
        num.SetStats(0)
        num.SetTitle(title)
        num.Draw()

    eff.SetLineWidth(2)
    eff.SetLineColor(color)
    eff.Draw(opt + " same")
    eff.SetMarkerStyle(marker_st)
    eff.SetMarkerColor(color)
    eff.SetMarkerSize(marker_sz)

    SetOwnership(eff, False)
    return eff
