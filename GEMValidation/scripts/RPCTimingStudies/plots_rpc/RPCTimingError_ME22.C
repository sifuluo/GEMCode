void RPCTimingError_ME22()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Oct  7 21:18:02 2019) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(-0.4285714,-30.24,3.142857,221.76);
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
   
   TH1F *num__12 = new TH1F("num__12","",30,0,3);
   num__12->SetBinContent(1,192);
   num__12->SetBinContent(2,2);
   num__12->SetBinContent(3,2);
   num__12->SetBinContent(5,2);
   num__12->SetBinContent(6,2);
   num__12->SetBinContent(7,1);
   num__12->SetBinContent(10,2);
   num__12->SetBinContent(11,2);
   num__12->SetBinContent(12,1);
   num__12->SetBinContent(13,3);
   num__12->SetBinContent(15,1);
   num__12->SetBinContent(17,1);
   num__12->SetBinContent(23,1);
   num__12->SetMinimum(0);
   num__12->SetEntries(212);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   num__12->SetLineColor(ci);
   num__12->SetLineStyle(0);
   num__12->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   num__12->SetMarkerColor(ci);
   num__12->SetMarkerStyle(21);
   num__12->GetXaxis()->SetTitle("RPC hit time error [ns]");
   num__12->GetXaxis()->SetLabelFont(42);
   num__12->GetXaxis()->SetLabelOffset(0.007);
   num__12->GetXaxis()->SetLabelSize(0.05);
   num__12->GetXaxis()->SetTitleSize(0.06);
   num__12->GetXaxis()->SetTitleOffset(0.9);
   num__12->GetXaxis()->SetTitleFont(42);
   num__12->GetYaxis()->SetTitle("Number of entries");
   num__12->GetYaxis()->SetLabelFont(42);
   num__12->GetYaxis()->SetLabelOffset(0.007);
   num__12->GetYaxis()->SetLabelSize(0.05);
   num__12->GetYaxis()->SetTitleSize(0.06);
   num__12->GetYaxis()->SetTitleOffset(0.9);
   num__12->GetYaxis()->SetTitleFont(42);
   num__12->GetZaxis()->SetLabelFont(42);
   num__12->GetZaxis()->SetLabelOffset(0.007);
   num__12->GetZaxis()->SetLabelSize(0.05);
   num__12->GetZaxis()->SetTitleSize(0.06);
   num__12->GetZaxis()->SetTitleFont(42);
   num__12->Draw("hist");
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
   TText *text = new TText(0.17,0.24,"RE2/2");
   text->SetNDC();
   text->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
