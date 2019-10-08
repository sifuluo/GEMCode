void Timing_ME41_RecHit()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Oct  7 19:41:01 2019) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(-6.428571,-3276.787,5.47619,24029.77);
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
   
   TH1F *num__29 = new TH1F("num__29","",100,-5,5);
   num__29->SetBinContent(11,5);
   num__29->SetBinContent(21,95);
   num__29->SetBinContent(31,915);
   num__29->SetBinContent(41,4725);
   num__29->SetBinContent(51,20805);
   num__29->SetBinContent(61,4321);
   num__29->SetBinContent(71,912);
   num__29->SetBinContent(81,83);
   num__29->SetBinContent(91,2);
   num__29->SetMinimum(0);
   num__29->SetEntries(31863);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   num__29->SetLineColor(ci);
   num__29->SetLineStyle(0);
   num__29->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   num__29->SetMarkerColor(ci);
   num__29->SetMarkerStyle(21);
   num__29->GetXaxis()->SetTitle("Timing");
   num__29->GetXaxis()->SetLabelFont(42);
   num__29->GetXaxis()->SetLabelOffset(0.007);
   num__29->GetXaxis()->SetLabelSize(0.05);
   num__29->GetXaxis()->SetTitleSize(0.06);
   num__29->GetXaxis()->SetTitleOffset(0.9);
   num__29->GetXaxis()->SetTitleFont(42);
   num__29->GetYaxis()->SetTitle("Number of entries");
   num__29->GetYaxis()->SetLabelFont(42);
   num__29->GetYaxis()->SetLabelOffset(0.007);
   num__29->GetYaxis()->SetLabelSize(0.05);
   num__29->GetYaxis()->SetTitleSize(0.06);
   num__29->GetYaxis()->SetTitleOffset(0.9);
   num__29->GetYaxis()->SetTitleFont(42);
   num__29->GetZaxis()->SetLabelFont(42);
   num__29->GetZaxis()->SetLabelOffset(0.007);
   num__29->GetZaxis()->SetLabelSize(0.05);
   num__29->GetZaxis()->SetTitleSize(0.06);
   num__29->GetZaxis()->SetTitleFont(42);
   num__29->Draw("hist");
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
   TText *text = new TText(0.17,0.24,"RE4/1");
   text->SetNDC();
   text->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
