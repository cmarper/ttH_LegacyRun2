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
#include <TStyle.h>


void plothisto ( ){

  vector<TString> infiles;
  //infiles.push_back("/data_CMS/cms/mperez/TauTrigger_data/TauTauJet/Ntuple_MC_MiniAOD_VBFHToTauTau_261210_10_3_X_multipletaus.root");
  infiles.push_back("/data_CMS/cms/mperez/TauTrigger_data/TauTauJet/Ntuple_MC_MiniAOD_GluGluHToTauTau_181210_10_3_X_multipletaus.root");
 
  vector<TH1F*> histograms;
  histograms.push_back(single_plot(infiles,"Ntuplizer_noTagAndProbe_multipleTaus/TagAndProbe","l1tPt[0]","l1tIso[0] && l1tPt[0]<100", 40,20,100));
  histograms.push_back(single_plot(infiles,"Ntuplizer_noTagAndProbe_multipleTaus/TagAndProbe","l1tPt[1]","l1tIso[1] && l1tPt[1]<100", 40,20,100));

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.12);
  c->SetGridx();
  c->SetGridy();

  gStyle->SetOptStat(0);  

  double ymax = 0.1;

  histograms[1]->SetTitle(" ");
  histograms[1]->GetXaxis()->SetTitle("L1 p_{T} [GeV]");
  //histograms[1]->GetYaxis()->SetTitle("Normalized events");
  histograms[1]->GetYaxis()->SetTitle("Events");
  histograms[1]->GetXaxis()->SetRangeUser(0,200);
  histograms[1]->GetYaxis()->SetTitleOffset(1.5);
  histograms[1]->GetXaxis()->SetTitleOffset(1.2);
  histograms[1]->SetLineWidth(2);
  histograms[1]->SetFillColor(0);
  histograms[1]->SetLineColor(kRed);
  histograms[1]->SetFillColor(0);

  TLegend* leg=new TLegend(0.48,0.6,0.83,0.75);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(histograms[0],"Leading L1 #tau_{h}");
  leg->AddEntry(histograms[1],"Subleading L1 #tau_{h}");

  histograms[0]->SetLineWidth(2);
  histograms[0]->SetFillColor(0);
  histograms[0]->SetLineColor(kBlue);
  histograms[0]->SetFillColor(0);

  //histograms[1]->DrawNormalized();
  histograms[1]->Draw();
    
  //histograms[0]->DrawNormalized("same");
  histograms[0]->Draw("same");
  
  leg->Draw("same");

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.20,0.91,"CMS #bf{#it{Simulation}}");
  //tex.DrawLatexNDC(0.50,0.81,"VBF H#rightarrow#tau#tau");
  tex.DrawLatexNDC(0.50,0.81,"ggH H#rightarrow#tau#tau");

  //c->SaveAs("VBF_ditauasym.pdf");
  //c->SaveAs("VBF_ditauasym.png");

  c->SaveAs("ggH_ditauasym.pdf");
  c->SaveAs("ggH_ditauasym.png");

  return;

}
