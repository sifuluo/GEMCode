void TimingError_ME23_RecHit()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Oct  7 19:53:41 2019) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(-1.428571,-0.1575,10.47619,1.155);
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
   
   TH1F *num__17 = new TH1F("num__17","",10,0,10);
   num__17->SetMinimum(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   num__17->SetLineColor(ci);
   num__17->SetLineStyle(0);
   num__17->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   num__17->SetMarkerColor(ci);
   num__17->SetMarkerStyle(21);
   num__17->GetXaxis()->SetTitle("TimingError");
   num__17->GetXaxis()->SetLabelFont(42);
   num__17->GetXaxis()->SetLabelOffset(0.007);
   num__17->GetXaxis()->SetLabelSize(0.05);
   num__17->GetXaxis()->SetTitleSize(0.06);
   num__17->GetXaxis()->SetTitleOffset(0.9);
   num__17->GetXaxis()->SetTitleFont(42);
   num__17->GetYaxis()->SetTitle("Number of entries");
   num__17->GetYaxis()->SetLabelFont(42);
   num__17->GetYaxis()->SetLabelOffset(0.007);
   num__17->GetYaxis()->SetLabelSize(0.05);
   num__17->GetYaxis()->SetTitleSize(0.06);
   num__17->GetYaxis()->SetTitleOffset(0.9);
   num__17->GetYaxis()->SetTitleFont(42);
   num__17->GetZaxis()->SetLabelFont(42);
   num__17->GetZaxis()->SetLabelOffset(0.007);
   num__17->GetZaxis()->SetLabelSize(0.05);
   num__17->GetZaxis()->SetTitleSize(0.06);
   num__17->GetZaxis()->SetTitleFont(42);
   num__17->Draw("hist");
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
   TText *text = new TText(0.17,0.24,"RE2/3");
   text->SetNDC();
   text->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
