void ClusterSize_ME42_RecHit()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Oct  7 19:41:01 2019) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(-1.428571,-914.13,10.47619,6703.62);
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
   
   TH1F *num__36 = new TH1F("num__36","",10,0,10);
   num__36->SetBinContent(2,5804);
   num__36->SetBinContent(3,5754);
   num__36->SetBinContent(4,3916);
   num__36->SetBinContent(5,697);
   num__36->SetBinContent(6,267);
   num__36->SetBinContent(7,126);
   num__36->SetBinContent(8,84);
   num__36->SetBinContent(9,56);
   num__36->SetBinContent(10,43);
   num__36->SetBinContent(11,134);
   num__36->SetMinimum(0);
   num__36->SetEntries(16881);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   num__36->SetLineColor(ci);
   num__36->SetLineStyle(0);
   num__36->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   num__36->SetMarkerColor(ci);
   num__36->SetMarkerStyle(21);
   num__36->GetXaxis()->SetTitle("ClusterSize");
   num__36->GetXaxis()->SetLabelFont(42);
   num__36->GetXaxis()->SetLabelOffset(0.007);
   num__36->GetXaxis()->SetLabelSize(0.05);
   num__36->GetXaxis()->SetTitleSize(0.06);
   num__36->GetXaxis()->SetTitleOffset(0.9);
   num__36->GetXaxis()->SetTitleFont(42);
   num__36->GetYaxis()->SetTitle("Number of entries");
   num__36->GetYaxis()->SetLabelFont(42);
   num__36->GetYaxis()->SetLabelOffset(0.007);
   num__36->GetYaxis()->SetLabelSize(0.05);
   num__36->GetYaxis()->SetTitleSize(0.06);
   num__36->GetYaxis()->SetTitleOffset(0.9);
   num__36->GetYaxis()->SetTitleFont(42);
   num__36->GetZaxis()->SetLabelFont(42);
   num__36->GetZaxis()->SetLabelOffset(0.007);
   num__36->GetZaxis()->SetLabelSize(0.05);
   num__36->GetZaxis()->SetTitleSize(0.06);
   num__36->GetZaxis()->SetTitleFont(42);
   num__36->Draw("hist");
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
   TText *text = new TText(0.17,0.24,"RE4/2");
   text->SetNDC();
   text->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
