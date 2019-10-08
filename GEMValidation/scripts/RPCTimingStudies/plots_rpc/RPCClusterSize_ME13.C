void RPCClusterSize_ME13()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Oct  7 22:46:41 2019) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(-1.428571,-709.38,10.47619,5202.12);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.12);
   c->SetRightMargin(0.04);
   c->SetTopMargin(0.08);
   c->SetBottomMargin(0.12);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   TH1F *num__10 = new TH1F("num__10","",10,0,10);
   num__10->SetBinContent(2,4504);
   num__10->SetBinContent(3,4384);
   num__10->SetBinContent(4,3012);
   num__10->SetBinContent(5,465);
   num__10->SetBinContent(6,159);
   num__10->SetBinContent(7,65);
   num__10->SetBinContent(8,31);
   num__10->SetBinContent(9,38);
   num__10->SetBinContent(10,34);
   num__10->SetBinContent(11,72);
   num__10->SetMinimum(0);
   num__10->SetEntries(12764);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   num__10->SetLineColor(ci);
   num__10->SetLineStyle(0);
   num__10->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   num__10->SetMarkerColor(ci);
   num__10->SetMarkerStyle(21);
   num__10->GetXaxis()->SetTitle("RPC cluster size");
   num__10->GetXaxis()->SetLabelFont(42);
   num__10->GetXaxis()->SetLabelOffset(0.007);
   num__10->GetXaxis()->SetLabelSize(0.05);
   num__10->GetXaxis()->SetTitleSize(0.06);
   num__10->GetXaxis()->SetTitleOffset(0.9);
   num__10->GetXaxis()->SetTitleFont(42);
   num__10->GetYaxis()->SetTitle("Number of entries");
   num__10->GetYaxis()->SetLabelFont(42);
   num__10->GetYaxis()->SetLabelOffset(0.007);
   num__10->GetYaxis()->SetLabelSize(0.05);
   num__10->GetYaxis()->SetTitleSize(0.06);
   num__10->GetYaxis()->SetTitleOffset(0.9);
   num__10->GetYaxis()->SetTitleFont(42);
   num__10->GetZaxis()->SetLabelFont(42);
   num__10->GetZaxis()->SetLabelOffset(0.007);
   num__10->GetZaxis()->SetLabelSize(0.05);
   num__10->GetZaxis()->SetTitleSize(0.06);
   num__10->GetZaxis()->SetTitleFont(42);
   num__10->Draw("hist");
   TLatex *   tex = new TLatex(0.96,0.936,"14 TeV");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.048);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.12,0.936,"CMS");
tex->SetNDC();
   tex->SetTextFont(61);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.2208,0.936,"Phase-2 Simulation");
tex->SetNDC();
   tex->SetTextFont(52);
   tex->SetTextSize(0.0456);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0,0,0,0,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("num","RecHit","pl");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   TText *text = new TText(0.17,0.24,"RE1/3");
   text->SetNDC();
   text->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
