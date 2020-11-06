#include <TFile.h>
#include <TGraph.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH3F.h>
#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TF1.h>
#include "Helpers.C"
#include <TSystem.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <THStack.h>
#include <TStyle.h>

void plot_categories(){

  TString category[10] = { "2lss+0#tau_{h}","3l+0#tau_{h}","4l+0#tau_{h}","2lss+1#tau_{h}","3l+1#tau_{h}","2los+1#tau_{h}","1l+1#tau_{h}","2l+2#tau_{h}","1l+2#tau_{h}","0l+2#tau_{h}" };

  //float hww[10] = {0.82505734,0.799805672,0.771111111,0.468261151,0.453150912,0.335187494,0.331946812,0.080346106,0.053015982,0.036075896};
  //float hzz[10] = {0.022901119,0.049013963,0.071111111,0.015578539,0.044776119,0.021962213,0.026116604,0.014833127,0.006874033,0.006296265};
  //float htt[10] = {0.152041541,0.151180366,0.157777778,0.51616031,0.502072968,0.642850293,0.641936584,0.904820766,0.940109985,0.95762784};

  float hww[10] = {0.755724638,0.762359124,0.701672574,0.427681156,0.401171236,0.297276578,0.263993244,0.047349163,0,0.006207959};
  float hzz[10] = {0.017733606,0.04203419,0.105844464,0.014726785,0.038367133,0.015886982,0.020391346,0.017346052,0,0};
  float htt[10] = {0.143417095,0.14324678,0.173508868,0.492076728,0.527242564,0.649162687,0.661989973,0.910801779,0.97936419,0.899087914};
  float th[10] = {0.083124662,0.052359907,0.018974094,0.06551533,0.033219067,0.037673754,0.053625437,0.024503006,0.02063581,0.094704127};

  TH1F *h_hww = new TH1F("h_hww","h_hww",10,0,10);
  for (int i=0; i<10; i++){
    h_hww->AddBinContent(i+1,hww[i]);
    h_hww->SetBinError(i+1,0.000001);
    h_hww->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_hzz = new TH1F("h_hzz","h_hzz",10,0,10);
  for (int i=0; i<10; i++){
    h_hzz->AddBinContent(i+1,hzz[i]);
    h_hzz->SetBinError(i+1,0.000001);
    h_hzz->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_htt = new TH1F("h_htt","h_htt",10,0,10);
  for (int i=0; i<10; i++){
    h_htt->AddBinContent(i+1,htt[i]);
    h_htt->SetBinError(i+1,0.000001);
    h_htt->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_th = new TH1F("h_th","h_th",10,0,10);
  for (int i=0; i<10; i++){
    h_th->AddBinContent(i+1,th[i]);
    h_th->SetBinError(i+1,0.000001);
    h_th->GetXaxis()->SetBinLabel(i+1,category[i]);
  }


  TLatex *texl1 = new TLatex(0.1,1.03,"#bf{CMS} #it{Preliminary}");
  texl1->SetTextSize(0.05);
  texl1->SetTextFont(42);

  TLatex *texl2 = new TLatex(6.9,1.03,"137 fb^{-1} (13 TeV)");
  texl2->SetTextSize(0.05);
  texl2->SetTextFont(42);

  //TLatex tex;
  //tex.SetTextSize(1); //0.04
  //tex.DrawLatexNDC(1,0.91,"CMS #bf{#it{Preliminary}}");
  //tex.DrawLatexNDC(1,0.91,"#bf{137 fb^{-1} (13 TeV)}");

  TCanvas* c=new TCanvas("c","c",800,600);
  c->SetLeftMargin(0.10);
  c->SetBottomMargin(0.15);
  //c->SetLogy();

  h_hww->SetLineColor(1);
  h_hzz->SetLineColor(1);
  h_htt->SetLineColor(1);
  h_th->SetLineColor(1);

  THStack *hs = new THStack("hs","");
  hs->SetMaximum(1.0);
  h_hww->SetFillColor(kRed);
  h_hww->SetMaximum(1.0);
  hs->Add(h_hww);
  h_hzz->SetMaximum(1.0);
  h_hzz->SetFillColor(94);
  hs->Add(h_hzz);
  h_htt->SetMaximum(1.0);
  h_htt->SetFillColor(90);
  hs->Add(h_htt);
  h_th->SetMaximum(1.0);
  h_th->SetFillColor(4);
  hs->Add(h_th);

  hs->SetMaximum(1.0);

  hs->Draw("hist");

  gStyle->SetHistTopMargin(0.);

  hs->GetYaxis()->SetTitle("Signal fraction");
  hs->GetYaxis()->SetLabelSize(0.045);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleOffset(1.0);
  hs->GetXaxis()->SetLabelOffset(0.015);

  hs->GetYaxis()->SetRangeUser(0,1.0);
  hs->GetYaxis()->SetRange(0,1.0);
  hs->SetMaximum(1.0);

  hs->GetXaxis()->SetLabelSize(0.063);

  h_hww->SetTitle(" ");
  h_hww->SetStats(0);

  TLegend* leg=new TLegend(0.63,0.5,0.87,0.74);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  //leg->SetFillColor(0);

  leg->AddEntry(h_hww, "ttH, H #rightarrow WW", "f");
  leg->AddEntry(h_hzz, "ttH, H #rightarrow ZZ", "f");
  leg->AddEntry(h_htt, "ttH, H #rightarrow #tau#tau", "f");
  leg->AddEntry(h_th, "tHq / tHW", "f");

  leg->Draw("same");
  texl1->Draw("same");
  texl2->Draw("same");

  TString filename="channels_higgs";
  c->SaveAs(filename+".pdf");
  c->SaveAs(filename+".root");

}
