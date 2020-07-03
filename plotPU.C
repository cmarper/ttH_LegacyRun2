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
#include <TRatioPlot.h>

void plot_pu( ){

  TString dirin = "/home/llr/cms/mperez/ttH/Legacy/macros/PU_weights/";

  TString file_2016 = dirin+"pu_weights_2016.root";
  TString file_2017 = dirin+"pu_weights_2017.root";
  TString file_2018 = dirin+"pu_weights_2018.root";

  TFile *f_2016 = new TFile(file_2016);
  TFile *f_2017 = new TFile(file_2017);
  TFile *f_2018 = new TFile(file_2018);

  TH1F *hdata_2016 = new TH1F("hData16","hData16", 80, 0, 80);
  TH1F *hdata_2017 = new TH1F("hData17","hData17", 80, 0, 80);
  TH1F *hdata_2018 = new TH1F("hData18","hData18", 80, 0, 80);

  hdata_2016 = (TH1F*)f_2016->Get("Data");
  hdata_2017 = (TH1F*)f_2017->Get("Data");
  hdata_2018 = (TH1F*)f_2018->Get("Data");

  TH1F *hdata = new TH1F("hData","hData", 80, 0, 80);
  hdata->Add(hdata_2016);
  hdata->Add(hdata_2017);
  hdata->Add(hdata_2018);

  TH1F *hmc_2016 = new TH1F("hMC16","hMC16", 80, 0, 80);
  TH1F *hmc_2017 = new TH1F("hMC17","hMC17", 80, 0, 80);
  TH1F *hmc_2018 = new TH1F("hMC18","hMC18", 80, 0, 80);

  hmc_2016 = (TH1F*)f_2016->Get("MC_out_of_the_box");
  hmc_2017 = (TH1F*)f_2017->Get("MC_out_of_the_box");
  hmc_2018 = (TH1F*)f_2018->Get("MC_out_of_the_box");

  TH1F *hmc = new TH1F("hMC","hMC", 80, 0, 80);
  hmc->Add(hmc_2016);
  hmc->Add(hmc_2017);
  hmc->Add(hmc_2018);


  TLegend* leg=new TLegend(0.68,0.7,0.85,0.87);
  leg->SetHeader(" ");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.045);
  leg->SetFillColor(0);
  leg->AddEntry(hdata,"Data");
  leg->AddEntry(hmc,"Simulation");

  hdata->SetStats(0);
  hdata->SetTitle(" ");
  hdata->SetLineColor(2);
  hdata->SetMarkerSize(1);
  hdata->SetMarkerStyle(2);
  hdata->SetMarkerColor(2);
  hdata->SetLineWidth(4);
  hdata->SetFillColor(0);

  hmc->SetLineColor(4);
  hmc->SetMarkerColor(4);
  hmc->SetMarkerSize(1);
  hmc->SetMarkerStyle(2);
  hmc->SetLineWidth(4);
  hmc->SetFillColor(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetTitle(" ");

  TPad* main = new TPad("main", "", 0., 0.25, 1., 1);
  main->Draw();
  //main->SetBottomMargin(0.1);
  main->SetLeftMargin(0.15);
  main->cd();

  hdata->Draw("P");
  hmc->Draw("P same");

  //hdata->GetXaxis()->SetTitle("Number of pileup interactions");
  hdata->GetYaxis()->SetTitle("a. u.");
  hdata->GetXaxis()->SetTitleOffset(1.2);
  hdata->GetYaxis()->SetTitleOffset(0.9);
  hdata->GetYaxis()->SetLabelSize(0.04);
  hdata->GetYaxis()->SetTitleSize(0.06);
  hdata->SetTitle(" ");
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0,0.13,"CMS #bf{#it{Preliminary}}");
  texl->SetTextSize(0.045);
  texl->Draw("same");

  TLatex *texl2 = new TLatex(70,0.13,"#bf{137 fb^{-1} (13 TeV)}");
  texl2->SetTextSize(0.045);
  texl2->Draw("same");

  c->cd();

  TPad* ratio = new TPad("ratio", "", 0., 0.0, 1., 0.32);
  ratio->Draw();
  //ratio->SetTopMargin(0.01);
  ratio->SetBottomMargin(0.3);
  ratio->SetLeftMargin(0.15);
  ratio->cd();

  TH1D *hratio = (TH1D*)hdata->Clone("ratio");
  hratio->SetMarkerColor(kBlack);
  hratio->SetMarkerSize(1);
  hratio->SetMarkerStyle(2);
  hratio->SetLineWidth(4);
  hratio->SetStats(0);
  hratio->Divide(hdata, hmc, 1., 1.);
  hratio->SetTitle("");
  hratio->GetXaxis()->SetTitle("Number of pileup interactions");
  hratio->GetYaxis()->SetTitle("Data/MC");
  hratio->GetYaxis()->SetTitleOffset(0.5);
  hratio->GetXaxis()->SetTitleSize(0.12);
  hratio->GetYaxis()->SetTitleSize(0.12);
  hratio->GetXaxis()->SetLabelSize(0.1);
  hratio->GetYaxis()->SetLabelSize(0.1);
  hratio->SetMinimum(0.);
  hratio->SetMaximum(3.);
  hratio->Draw("P");

  TString filename="pileup";
  c->SaveAs(dirin+filename+".pdf");

  return;

}

