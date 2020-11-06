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

  TString category[10] = {"0l+2#tau_{h}", "1l+1#tau_{h}", "1l+2#tau_{h}", "2l+2#tau_{h}", "2los+1#tau_{h}", "3l+1#tau_{h}", "4l+0#tau_{h}", "3l+0#tau_{h}", "2lss+0#tau_{h}", "2lss+1#tau_{h}"};

  float ttH[10] = {27.7, 192.9, 21.8, 2.4, 21.2, 4.6, 2.0, 60.5, 219.4, 33.6};
  float tH[10] = {2.9, 10.9, 0.5, 0, 0.8, 0.2, 0, 3.3, 19.9, 2.4};
  float ttZ[10] = {26.9, 187.2,20.3, 2.5, 26.5,6.7,5.6, 131.3, 292.2, 31.4};
  float ttW[10] = { 2.7, 177.7, 2.0, 0, 13.0,1.0,0.1, 113.0, 766.4, 38.0};
  float WZ[10] = {30.2, 131.1, 8.4, 0,5.6,0.4, 0, 63.0, 219.0, 15.1};
  float ZZ[10] = {25.2, 64.9,1.2,0.1,1.2,0.2,0.3, 10.2, 18.6,1.1};
  float DY[10] = {1112.1, 3539.4, 0, 0, 0, 0, 0, 0, 0, 0};
  float ttbar[10] = {888.1, 39811.7, 0, 0, 0, 0, 0, 0, 0, 0};
  float Fakes[10] = {3637.3, 23602.0, 241.6,3.9, 410.3,1.3, 0, 175.1, 1539.2, 54.7};
  float Flips[10] = {0, 0, 0, 0, 0, 0, 0, 0, 139.5,1.0};
  float Rares[10] = {57.7, 1738.9,5.5,0.3,5.6,1.0,0.6, 37.7, 197.7, 13.4};
  float Higgs[10] = {24.2, 34.0, 0, 0,0.8, 0, 0,3.3, 29.8,1.8};
  float Total[10] = {5807.4, 69297.8, 279.5,6.9, 464.0, 10.7,6.7, 537.0, 3222.3, 158.8};

  TH1F *h_ttH = new TH1F("h_ttH","h_ttH",10,0,10);
  for (int i=0; i<10; i++){
    h_ttH->AddBinContent(i+1,ttH[i]);
    h_ttH->SetBinError(i+1,0.000001);
    h_ttH->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_tH = new TH1F("h_tH","h_tH",10,0,10);
  for (int i=0; i<10; i++){
    h_tH->AddBinContent(i+1,tH[i]);
    h_tH->SetBinError(i+1,0.000001);
    h_tH->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_ttZ = new TH1F("h_ttZ","h_ttZ",10,0,10);
  for (int i=0; i<10; i++){
    h_ttZ->AddBinContent(i+1,ttZ[i]);
    h_ttZ->SetBinError(i+1,0.000001);
    h_ttZ->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_ttW = new TH1F("h_ttW","h_ttW",10,0,10);
  for (int i=0; i<10; i++){
    h_ttW->AddBinContent(i+1,ttW[i]);
    h_ttW->SetBinError(i+1,0.000001);
    h_ttW->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_WZ = new TH1F("h_WZ","h_WZ",10,0,10);
  for (int i=0; i<10; i++){
    h_WZ->AddBinContent(i+1,WZ[i]);
    h_WZ->SetBinError(i+1,0.000001);
    h_WZ->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_ZZ = new TH1F("h_ZZ","h_ZZ",10,0,10);
  for (int i=0; i<10; i++){
    h_ZZ->AddBinContent(i+1,ZZ[i]);
    h_ZZ->SetBinError(i+1,0.000001);
    h_ZZ->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_DY = new TH1F("h_DY","h_DY",10,0,10);
  for (int i=0; i<10; i++){
    h_DY->AddBinContent(i+1,DY[i]);
    h_DY->SetBinError(i+1,0.000001);
    h_DY->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_ttbar = new TH1F("h_ttbar","h_ttbar",10,0,10);
  for (int i=0; i<10; i++){
    h_ttbar->AddBinContent(i+1,ttbar[i]);
    h_ttbar->SetBinError(i+1,0.000001);
    h_ttbar->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_Fakes = new TH1F("h_Fakes","h_Fakes",10,0,10);
  for (int i=0; i<10; i++){
    h_Fakes->AddBinContent(i+1,Fakes[i]);
    h_Fakes->SetBinError(i+1,0.000001);
    h_Fakes->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_Flips = new TH1F("h_Flips","h_Flips",10,0,10);
  for (int i=0; i<10; i++){
    h_Flips->AddBinContent(i+1,Flips[i]);
    h_Flips->SetBinError(i+1,0.000001);
    h_Flips->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_Rares = new TH1F("h_Rares","h_Rares",10,0,10);
  for (int i=0; i<10; i++){
    h_Rares->AddBinContent(i+1,Rares[i]);
    h_Rares->SetBinError(i+1,0.000001);
    h_Rares->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TH1F *h_Higgs = new TH1F("h_Higgs","h_Higgs",10,0,10);
  for (int i=0; i<10; i++){
    h_Higgs->AddBinContent(i+1,Higgs[i]);
    h_Higgs->SetBinError(i+1,0.000001);
    h_Higgs->GetXaxis()->SetBinLabel(i+1,category[i]);
  }

  TLatex *texl1 = new TLatex(0.1,240000,"#bf{CMS} #it{Preliminary}");
  texl1->SetTextSize(0.05);
  texl1->SetTextFont(42);

  TLatex *texl2 = new TLatex(6.9,240000,"137 fb^{-1} (13 TeV)");
  texl2->SetTextSize(0.05);
  texl2->SetTextFont(42);

  TCanvas* c=new TCanvas("c","c",800,600);
  c->SetLeftMargin(0.10);
  c->SetBottomMargin(0.15);
  c->SetLogy();

  h_ttH->SetLineColor(1);
  h_tH->SetLineColor(1);
  h_ttZ->SetLineColor(1);
  h_ttW->SetLineColor(1);
  h_WZ->SetLineColor(1);
  h_ZZ->SetLineColor(1);
  h_DY->SetLineColor(1);
  h_ttbar->SetLineColor(1);
  h_Fakes->SetLineColor(1);
  h_Flips->SetLineColor(1);
  h_Rares->SetLineColor(1);
  h_Higgs->SetLineColor(1);

  h_ttH->SetLineWidth(1);
  h_tH->SetLineWidth(1);
  h_ttZ->SetLineWidth(1);
  h_ttW->SetLineWidth(1);
  h_WZ->SetLineWidth(1);
  h_ZZ->SetLineWidth(1);
  h_DY->SetLineWidth(1);
  h_ttbar->SetLineWidth(1);
  h_Fakes->SetLineWidth(1);
  h_Flips->SetLineWidth(1);
  h_Rares->SetLineWidth(1);
  h_Higgs->SetLineWidth(1);

  h_ttH->SetMinimum(1.0);
  h_tH->SetMinimum(1.0);
  h_ttZ->SetMinimum(1.0);
  h_ttW->SetMinimum(1.0);
  h_WZ->SetMinimum(1.0);
  h_ZZ->SetMinimum(1.0);
  h_DY->SetMinimum(1.0);
  h_ttbar->SetMinimum(1.0);
  h_Fakes->SetMinimum(1.0);
  h_Flips->SetMinimum(1.0);
  h_Rares->SetMinimum(1.0);
  h_Higgs->SetMinimum(1.0);

  h_ttH->SetFillColor(2);
  h_tH->SetFillColor(4);
  h_ttZ->SetFillColor(822);
  h_ttW->SetFillColor(823);
  h_WZ->SetFillColor(6);
  h_ZZ->SetFillColor(52);
  h_DY->SetFillColor(221);
  h_ttbar->SetFillColor(17);
  h_Fakes->SetFillColor(12);
  h_Fakes->SetFillStyle(3345);
  h_Flips->SetFillColor(1);
  h_Flips->SetFillStyle(3006);
  h_Rares->SetFillColor(851);
  h_Higgs->SetFillColor(208);

  THStack *hs = new THStack("hs","");

  hs->SetMaximum(100000);
  hs->SetMinimum(1.0);

  hs->Add(h_tH);
  hs->Add(h_ttH);
  hs->Add(h_ttZ);
  hs->Add(h_ttW);
  hs->Add(h_WZ);
  hs->Add(h_ZZ);
  hs->Add(h_DY);
  hs->Add(h_ttbar);
  hs->Add(h_Fakes);
  hs->Add(h_Flips);
  hs->Add(h_Rares);
  hs->Add(h_Higgs);

  hs->Draw("hist");

  gStyle->SetHistTopMargin(0.);

  hs->GetYaxis()->SetTitle("Yields");
  hs->GetYaxis()->SetLabelSize(0.045);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleOffset(1.0);
  hs->GetXaxis()->SetLabelOffset(0.015);
  hs->GetXaxis()->SetLabelSize(0.063);

  //hs->GetYaxis()->SetRangeUser(0.5,100000);
  //hs->GetYaxis()->SetRange(0.5,100000);

  h_ttH->SetTitle(" ");
  h_ttH->SetStats(0);

  TLegend* leg=new TLegend(0.3,0.63,0.45,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  //leg->SetFillColor(0);

  leg->AddEntry(h_tH,"tH", "f");
  leg->AddEntry(h_ttH,"t#bar{t}H", "f");
  leg->AddEntry(h_ttZ,"t#bar{t}Z / t#bar{t}#gamma*", "f");
  leg->AddEntry(h_ttW,"t#bar{t}W(W)", "f");
  leg->AddEntry(h_WZ,"WZ", "f");
  leg->AddEntry(h_ZZ,"ZZ", "f");

  TLegend* leg2=new TLegend(0.45,0.63,0.60,0.88);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->AddEntry(h_DY,"DY", "f");
  leg2->AddEntry(h_ttbar,"t#bar{t}+jets", "f");
  leg2->AddEntry(h_Fakes,"Fakes", "f");
  leg2->AddEntry(h_Flips,"Flips", "f");
  leg2->AddEntry(h_Rares,"Rares", "f");
  leg2->AddEntry(h_Higgs,"Other Higgs proc.", "f");

  leg->Draw("same");
  leg2->Draw("same");
  texl1->Draw("same");
  texl2->Draw("same");

  TString filename="yields_ttH";
  c->SaveAs(filename+".pdf");
  c->SaveAs(filename+".root");

}
