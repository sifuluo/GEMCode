from ROOT import *
import sys
sys.argv.append( '-b' )
import ROOT
ROOT.gROOT.SetBatch(1)
#ROOT.gErrorIgnoreLevel=1001

cscstations = [ [0,0], 
                [1,1], [1,2], [1,3], [1,4],
                [2,1], [2,2],
                [3,1], [3,2],
                [4,1], [4,2],]
csclabel = {
    1 : {
        0 : {
            0 : ["pAll", 'ME+'] 
            },
        1 : {
            1 : ["pME1b","ME+1/1b"],
            2 : ["pME12","ME+1/2"],
            3 : ["pME13","ME+1/3"],
            4 : ["pME1a","ME+1/1a"]
            },
        2 : {
            1 : ["pME21","ME+2/1"],
            2 : ["pME22","ME+2/2"]
            },
        3 : {
            1 : ["pME31","ME+3/1"],
            2 : ["pME32","ME+3/2"]
            },
        4 : {
            1 : ["pME41","ME+4/1"],
            2 : ["pME42","ME+4/2"]
            },
        },
    2 : {
        0 : {
            0 : ["mAll","ME-"]
            },
        1 : {
            1 : ["mME1b","ME-1/1b"],
            2 : ["mME12","ME-1/2"],
            3 : ["mME13","ME-1/3"],
            4 : ["mME1a","ME-1/1a"],
            },
        2 : {
            1 : ["mME21","ME-2/1"],
            2 : ["mME22","ME-2/2"]
            },
        3 : {
            1 : ["mME31","ME-3/1"],
            2 : ["mME32","ME-3/2"]
            },
        4 : {
            1 : ["mME41","ME-4/1"],
            2 : ["mME42","ME-4/2"]
            },
        },
    }
gROOT.SetBatch(1)
gStyle.SetStatStyle(0)
gStyle.SetOptStat("nemr")

ch = TChain("Events")
fc = TFileCollection("dum")
#fc.Add("/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v2/160811_011552/0000/*.root")
fc.Add("SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_backup.root")
#SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_backup.root
print fc
fc.Print()
ch.AddFileInfoList(fc.GetList())
#exit(1)
#file = TFile("SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_backup.root")
outputdirectory = "2016_mc_SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_20160810/"
"""
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_1.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_10.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_11.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_12.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_13.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_14.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_15.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_16.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_17.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_18.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_19.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_2.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_20.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_3.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_4.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_5.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_6.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_7.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_8.root
/eos/uscms/store/user/lpcgem/SingleMuonPt100_MC/SingleMuonPt100_MC_L1REPACK_DIGI2RAW_v1/160810_231409/0000/SingleMuPt100_cfi_L1REPACK_RAW2DIGI_10k_Baseline_9.root
"""
tree = ch#.Get("Events")

csccorrelatedlctdigi = {
    0 : ["trknmb", "trknmb",10,0,10],
    1 : ["valid", "valid",20,0,20],
    2 : ["quality", "quality",20,0,20],
    3 : ["keywire", "keywire",150,0,150],
    4 : ["strip", "strip",224,0,224],
    5 : ["pattern", "pattern",16,0,16],
    6 : ["bend", "bend",10,0,10],
    7 : ["bx", "bx",16,0,16],
    8 : ["mpclink", "mpclink",5,0,5],
    9 : ["bx0", "bx0",10,0,10],
    10 : ["syncErr", "syncErr",10,0,10],
    11 : ["cscID", "cscID",15,0,15],
    }

cscalctdigi = {
#    0 : ["valid_", "valid",10,0,10],
#    1 : ["quality_", "quality",20,0,20],
#    2 : ["accel_", "accelerator",10,0,10],
#    3 : ["patternb_", "patternb",10,0,10],
#    4 : ["keywire_", "keywire",150,0,150],
    5 : ["bx_", "bx",12,0,12],
#    6 : ["trknmb_", "trknmb",10,0,10],
#   7 : ["fullbx_", "fullbx",10,0,10],
}

cscclctdigi = {
#    0 : ["valid_", "valid",10,0,10],
#    1 : ["quality_", "quality",16,0,16],
#    2 : ["pattern_", "pattern",20,0,20],
#    3 : ["striptype_", "striptype",10,0,10],
#    4 : ["bend_", "bend",10,0,10],
#    5 : ["cfeb_", "cfeb",10,0,10],
#    6 : ["strip_", "strip",32,0,32],
    7 : ["bx_", "bx",12,0,12],
#    8 : ["trknmb_", "trknmb",10,0,10],
#    9 : ["fullbx_", "fullbx",10,0,10],
#    10 : ["getKeyStrip()", "keyStrip",224,0,224],
    }

colors = [kRed, kBlue, kBlack, kGreen+2, kOrange+2, kPink+1, 28]

def yRanges(nCollections):
    yrange = 1.0-0.1
    ydelta = yrange/nCollections
    ymins = []
    ymaxs = []
    for d in range(0,nCollections):
        ymins.append(1.0-(1+d)*ydelta)
        ymaxs.append(1.0-d*ydelta)
    return ymins, ymaxs

    
def compareLCTs(collections, endcap, station, ring, variable):

    nCollections = len(collections)
    ymins, ymaxs = yRanges(nCollections)

    var = csccorrelatedlctdigi[variable][0]
    varstr = csccorrelatedlctdigi[variable][1]
    varnbin = csccorrelatedlctdigi[variable][2]
    varminbin = csccorrelatedlctdigi[variable][3]
    varmaxbin = csccorrelatedlctdigi[variable][4]

    extraCut = "strip >= 0"
    realRing = ring
    
    if station==1 and ring==1:
        extraCut = "strip < 128"

    if station==1 and ring==4:
        extraCut = "strip >= 128"
        realRing = 1

    c = TCanvas("c","c",800,800)
    c.cd()

    def addCollection(collection, index):
        collection_substring = collection[len('CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_'):] + "_" + varstr + "_" + csclabel[endcap][station][ring][0] 
        hist = TH1D(collection_substring,"CSCCorrelatedLCTDigi " + varstr + " " + 
                   csclabel[endcap][station][ring][1] + "; " + varstr + "; Entries",varnbin,varminbin,varmaxbin)

        if station==0 and realRing==0:
            tree.Draw(collection + ".obj.data_.second." + var + ">>" + hist.GetName(),
                      collection + ".obj.data_.first.endcap() == %d"%(endcap))
        else:
            tree.Draw(collection + ".obj.data_.second." + var + ">>" + hist.GetName(),
                      collection + ".obj.data_.first.endcap() == %d && "%(endcap) +
                      collection + ".obj.data_.first.station()==%d && "%(station) + 
                      collection + ".obj.data_.first.ring()==%d && "%(realRing) +
                      collection + ".obj.data_.second." + extraCut)
            
        hist.SetLineColor(colors[index])
        
        
        if varstr is 'bx':
            if hist.GetEntries()!=0:
                print '|', csclabel[endcap][station][ring][1], '|', hist.GetBinContent(6)/hist.GetEntries(), '|', hist.GetBinContent(7)/hist.GetEntries(), '|', hist.GetBinContent(8)/hist.GetEntries(), '|' 
  
        if index==0:
            hist.Draw()
        else:
            hist.Draw("sames")
        gPad.Update()
        hist_st = hist.FindObject("stats");
        hist_st.SetY1NDC(ymins[index]);
        hist_st.SetY2NDC(ymaxs[index])
        hist_st.SetTextColor(colors[index]);
        SetOwnership(hist, False)
        SetOwnership(hist_st, False)
        return hist, hist_st

    def plotCollection(hist, stats, index):
        if index==0: hist.Draw()
        else:        hist.Draw("sames")
        stats.Draw("same")
    
    ## add the histograms and the stat boxes
    hists = []
    stats = []
    for i in range(0,nCollections):
        hist, stat = addCollection(collections[i],i)
        hists.append(hist)
        stats.append(stat)

    for i in range(0,nCollections):
        plotCollection(hists[i], stats[i], i)
    
    c.SaveAs(outputdirectory  + "comparison_lct_" + varstr + "_" + csclabel[endcap][station][ring][0] + ".png")


def compareALCTs(collections, endcap, station, ring, variable):

    nCollections = len(collections)
    ymins, ymaxs = yRanges(nCollections)
        
    var = cscalctdigi[variable][0]
    varstr = cscalctdigi[variable][1]
    varnbin = cscalctdigi[variable][2]
    varminbin = cscalctdigi[variable][3]
    varmaxbin = cscalctdigi[variable][4]

    c = TCanvas("c","c",800,800)
    c.cd()

    def addCollection(collection, index):
        collection_substring = collection[len('CSCDetIdCSCALCTDigiMuonDigiCollection_'):] + "_" + varstr + "_" + csclabel[endcap][station][ring][0]
        hist = TH1D(collection_substring,"CSCALCTDigi " + varstr + " " + 
                   csclabel[endcap][station][ring][1] + "; " + varstr + "; Entries",varnbin,varminbin,varmaxbin)

        if station==0 and ring==0:
            tree.Draw(collection + ".obj.data_.second." + var + ">>" + hist.GetName(),
                      collection + ".obj.data_.first.endcap() == %d"%(endcap))
        else:
            tree.Draw(collection + ".obj.data_.second." + var + ">>" + hist.GetName(),
                      collection + ".obj.data_.first.endcap() == %d && "%(endcap) +
                      collection + ".obj.data_.first.station()==%d && "%(station) + 
                      collection + ".obj.data_.first.ring()==%d"%(ring))
            
        hist.SetLineColor(colors[index])
        if varstr is 'bx':
            if hist.GetEntries()!=0:
                print '|', csclabel[endcap][station][ring][1], '|', hist.GetBinContent(6)/hist.GetEntries(), '|', hist.GetBinContent(7)/hist.GetEntries(), '|', hist.GetBinContent(8)/hist.GetEntries(), '|' 
        if index==0:
            hist.Draw()
        else:
            hist.Draw("sames")
        gPad.Update()
        hist_st = hist.FindObject("stats");
        hist_st.SetY1NDC(ymins[index]);
        hist_st.SetY2NDC(ymaxs[index])
        hist_st.SetTextColor(colors[index]);
        SetOwnership(hist, False)
        SetOwnership(hist_st, False)
        return hist, hist_st

    def plotCollection(hist, stats, index):
        if index==0: hist.Draw()
        else:        hist.Draw("sames")
        stats.Draw("same")
        
    ## add the histograms and the stat boxes
    hists = []
    stats = []
    for i in range(0,nCollections):
        hist, stat = addCollection(collections[i],i)
        hists.append(hist)
        stats.append(stat)

    for i in range(0,nCollections):
        plotCollection(hists[i], stats[i], i)

    c.SaveAs(outputdirectory  + "comparison_alct_" + varstr + "_" + csclabel[endcap][station][ring][0] + ".png")


def compareCLCTs(collections, endcap, station, ring, variable):

    nCollections = len(collections)
    ymins, ymaxs = yRanges(nCollections)
        
    var = cscclctdigi[variable][0]
    varstr = cscclctdigi[variable][1]
    varnbin = cscclctdigi[variable][2]
    varminbin = cscclctdigi[variable][3]
    varmaxbin = cscclctdigi[variable][4]

    c = TCanvas("c","c",800,800)
    c.cd()

    def addCollection(collection, index):
        collection_substring = collection[len('CSCDetIdCSCCLCTDigiMuonDigiCollection_'):] + "_" + varstr + "_" + csclabel[endcap][station][ring][0]
        hist = TH1D(collection_substring,"CSCCLCTDigi " + varstr + " " + 
                   csclabel[endcap][station][ring][1] + "; " + varstr + "; Entries",varnbin,varminbin,varmaxbin)

        extraCut = "getKeyStrip() >=0"
        realRing = ring

        if station==1 and ring==1:
            extraCut = "getKeyStrip() <128"

        if station==1 and ring==4:
            realRing = 1
            extraCut = "getKeyStrip() >=128"

        if station==0 and realRing==0:
            tree.Draw(collection + ".obj.data_.second." + var + ">>" + hist.GetName(),
                      collection + ".obj.data_.first.endcap() == %d"%(endcap))
        else:
            tree.Draw(collection + ".obj.data_.second." + var + ">>" + hist.GetName(),
                      collection + ".obj.data_.first.endcap() == %d && "%(endcap) +
                      collection + ".obj.data_.first.station()==%d && "%(station) + 
                      collection + ".obj.data_.first.ring()==%d && "%(realRing) +
                      collection + ".obj.data_.second." + extraCut)
            
        hist.SetLineColor(colors[index])
        if varstr is 'bx':
            if hist.GetEntries()!=0:
                print '|', csclabel[endcap][station][ring][1], '|', hist.GetBinContent(6)/hist.GetEntries(), '|', hist.GetBinContent(7)/hist.GetEntries(), '|', hist.GetBinContent(8)/hist.GetEntries(), '|' 
        if index==0:
            hist.Draw()
        else:
            hist.Draw("sames")
        gPad.Update()
        hist_st = hist.FindObject("stats");
        hist_st.SetY1NDC(ymins[index]);
        hist_st.SetY2NDC(ymaxs[index])
        hist_st.SetTextColor(colors[index]);
        SetOwnership(hist, False)
        SetOwnership(hist_st, False)
        return hist, hist_st

    def plotCollection(hist, stats, index):
        if index==0: hist.Draw()
        else:        hist.Draw("sames")
        stats.Draw("same")
        
    ## add the histograms and the stat boxes
    hists = []
    stats = []
    for i in range(0,nCollections):
        hist, stat = addCollection(collections[i],i)
        hists.append(hist)
        stats.append(stat)

    for i in range(0,nCollections):
        plotCollection(hists[i], stats[i], i)

    c.SaveAs(outputdirectory  + "comparison_clct_" + varstr + "_" + csclabel[endcap][station][ring][0] + ".png")


def compareLCTsAll(collections):
    for i in range(7,8):
        for p in cscstations:
            compareLCTs(collections,1,p[0],p[1],i)
        for p in cscstations:
            compareLCTs(collections,2,p[0],p[1],i)

def compareALCTsAll(collections):
    for i in range(5,6):
        for p in cscstations:
            if p[0]==1 and p[1]==4 : continue
            compareALCTs(collections,1,p[0],p[1],i)
        for p in cscstations:
            if p[0]==1 and p[1]==4 : continue
            compareALCTs(collections,2,p[0],p[1],i)
        
def compareCLCTsAll(collections):
    for i in range(7,8):
        for p in cscstations:
            compareCLCTs(collections,1,p[0],p[1],i)
        for p in cscstations:
            compareCLCTs(collections,2,p[0],p[1],i)
        
lct_collections = [
    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis__DIGI2RAW',
#    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis_MPCSORTED_DIGI2RAW',
#    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_unpackCSC_MuonCSCCorrelatedLCTDigi_reL1T',
#    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis__reL1T',
#    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis_MPCSORTED_reL1T',
#    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_csctfUnpacker__reL1T',
#    'CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCCorrelatedLCTDigi_reL1T'
]

alct_collections = [
    'CSCDetIdCSCALCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis__DIGI2RAW',
#    'CSCDetIdCSCALCTDigiMuonDigiCollection_unpackCSC_MuonCSCALCTDigi_reL1T',
#    'CSCDetIdCSCALCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis__reL1T',
#    'CSCDetIdCSCALCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCALCTDigi_reL1T'
]

clct_collections = [
    'CSCDetIdCSCCLCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis__DIGI2RAW',
#    'CSCDetIdCSCCLCTDigiMuonDigiCollection_unpackCSC_MuonCSCCLCTDigi_reL1T',
#    'CSCDetIdCSCCLCTDigiMuonDigiCollection_simCscTriggerPrimitiveDigis__reL1T',
#    'CSCDetIdCSCCLCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCCLCTDigi_reL1T'
]
 
#compareLCTsAll(lct_collections)
#compareALCTsAll(alct_collections)
compareCLCTsAll(clct_collections)
