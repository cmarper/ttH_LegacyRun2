#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include "headers/Helpers.C"
#include <vector>
#include "TLatex.h"
#include <TGaxis.h>

using namespace std;


void plot_nuisance_variation(TString subcategory = "ttH_3l_0tau_2018_hj_neg"){

  TString file = "/data_CMS/cms/mperez/ttH_Legacy/checks_impacts/"+subcategory+".root";

  //TString subcategory = "ttH_3l_0tau_2018_hj_neg";
  //TString subcategory = "ttH_3l_0tau_2018_hj_pos";
  //TString subcategory = "ttH_3l_0tau_2018_lj_neg";
  //TString subcategory = "ttH_3l_0tau_2018_lj_pos";

  TString nuisance = "CMS_res_j_endcap1_2018";

  vector<TString> process;
  process.clear();

  if(subcategory=="ttH_3l_0tau_2018_hj_neg"){
    process.push_back("ttH_hww");
    process.push_back("ttH_hzz");
    process.push_back("ttH_htt");
    process.push_back("ttH_hmm");
    process.push_back("tHq_hww");
    process.push_back("tHq_hzz");
    process.push_back("tHW_hww");
    process.push_back("tHW_htt");
    process.push_back("TTWW");
    process.push_back("TTW");
    process.push_back("TTZ");
    process.push_back("WZ");
    process.push_back("ZZ");
    process.push_back("Rares");
    process.push_back("Convs");
  }

  else if(subcategory=="ttH_3l_0tau_2018_hj_pos"){

    process.push_back("ttH_hww");
    process.push_back("ttH_hzz");
    process.push_back("ttH_htt");
    process.push_back("ttH_hmm");
    process.push_back("tHq_hww");
    process.push_back("tHq_hzz");
    process.push_back("tHq_htt");
    process.push_back("tHW_hww");
    process.push_back("tHW_hzz");
    process.push_back("tHW_htt");
    process.push_back("WH_hww");
    process.push_back("WH_hzz");
    process.push_back("WH_htt");
    process.push_back("TTWW");
    process.push_back("TTW");
    process.push_back("TTZ");
    process.push_back("WZ");
    process.push_back("ZZ");
    process.push_back("Rares");
    process.push_back("Convs");

  }

  else if(subcategory=="ttH_3l_0tau_2018_lj_neg"){
    process.push_back("ttH_hww");
    process.push_back("ttH_hzz");
    process.push_back("ttH_htt");
    process.push_back("ttH_hmm");
    process.push_back("tHq_hww");
    process.push_back("tHq_hzz");
    process.push_back("tHq_htt");
    process.push_back("tHW_hww");
    process.push_back("tHW_htt");
    process.push_back("WH_hww");
    process.push_back("WH_htt");
    process.push_back("TTWW");
    process.push_back("TTW");
    process.push_back("TTZ");
    process.push_back("WZ");
    process.push_back("ZZ");
    process.push_back("Rares");
    process.push_back("Convs");
  }

  else if(subcategory=="ttH_3l_0tau_2018_lj_pos"){

    process.push_back("ttH_hww");
    process.push_back("ttH_hzz");
    process.push_back("ttH_htt");
    process.push_back("ttH_hmm");
    process.push_back("tHq_hww");
    process.push_back("tHq_hzz");
    process.push_back("tHq_htt");
    process.push_back("tHW_hww");
    process.push_back("tHW_htt");
    process.push_back("ZH_htt");
    process.push_back("WH_hww");
    process.push_back("WH_hzz");
    process.push_back("TTWW");
    process.push_back("TTW");
    process.push_back("TTZ");
    process.push_back("WZ");
    process.push_back("ZZ");
    process.push_back("Rares");
    process.push_back("Convs");

  }

  for(unsigned int i_proc = 0; i_proc<process.size(); i_proc++){

  TString histoname = "x_"+process.at(i_proc);
  TString histonameUp = "x_"+process.at(i_proc)+"_"+nuisance+"Up";
  TString histonameDown = "x_"+process.at(i_proc)+"_"+nuisance+"Down";
      
  TFile *f = new TFile(file);

  TH1D *h1_nominal = (TH1D*)f->Get(histoname);
  TH1D *h1_up = (TH1D*)f->Get(histonameUp);
  TH1D *h1_down = (TH1D*)f->Get(histonameDown);

  // Define the Canvas
  TCanvas *c = new TCanvas("c", "canvas", 800, 800);

  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); 
  //pad1->SetGridx();
  pad1->Draw();
  pad1->cd();
  //h1_up->SetStats(0); 
  h1_up->SetTitle(process.at(i_proc));
  h1_up->Draw();
  h1_down->Draw("same");
  h1_nominal->Draw("same"); 

  auto legend = new TLegend(0.5,0.75,0.65,0.9);
  legend->SetTextSize(0.035);
  legend->AddEntry(h1_nominal,"nominal","l");
  legend->AddEntry(h1_up,"up","l");
  legend->AddEntry(h1_down,"down","l");
  legend->Draw();

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  //h1_up->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->SetTitle("Events");
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  // Define the ratio plot
  TH1F *h1_ratio_up = (TH1F*)h1_up->Clone("h1_ratio_up");
  h1_ratio_up->Divide(h1_nominal);
  h1_ratio_up->SetLineColor(kRed);

  TH1F *h1_ratio_down = (TH1F*)h1_down->Clone("h1_ratio_down");
  h1_ratio_down->Divide(h1_nominal);
  h1_ratio_down->SetLineColor(kBlue);

  TH1F *h1_ratio = (TH1F*)h1_nominal->Clone("h1_ratio");
  h1_ratio->Divide(h1_nominal);
  h1_ratio->SetLineColor(kBlack);
 
  h1_ratio_up->SetMinimum(0.80);  // Define Y ..
  h1_ratio_up->SetMaximum(1.20); // .. range
  h1_ratio_up->Sumw2();
  h1_ratio_up->SetStats(0);      // No statistics on lower plot
  h1_ratio_up->Draw(); //"ep"      // Draw the ratio plot
  h1_ratio_down->Draw("same");   
  h1_ratio->Draw("same");   

  // h1 settings
  h1_nominal->SetLineColor(kBlack);
  h1_nominal->SetLineWidth(2);

  // Y axis h1 plot settings
  h1_nominal->GetYaxis()->SetTitleSize(20);
  h1_nominal->GetYaxis()->SetTitleFont(43);
  h1_nominal->GetYaxis()->SetTitleOffset(1.55);

  // h2 settings
  h1_up->SetLineColor(kRed);
  h1_down->SetLineColor(kBlue);

  h1_up->SetLineWidth(2);
  h1_down->SetLineWidth(2);

  // Ratio plot (h1_ratio_up) settings
  h1_ratio_up->SetTitle(""); // Remove the ratio title
  h1_ratio_up->SetLineWidth(2);
  h1_ratio_down->SetLineWidth(2);
  h1_ratio->SetLineWidth(1);

  // Y axis ratio plot settings
  h1_ratio_up->GetYaxis()->SetTitle("up(down)/nominal");
  //h1_ratio_up->GetYaxis()->SetNdivisions(505);
  h1_ratio_up->GetYaxis()->SetTitleSize(20);
  h1_ratio_up->GetYaxis()->SetTitleFont(43);
  h1_ratio_up->GetYaxis()->SetTitleOffset(1.55);
  h1_ratio_up->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h1_ratio_up->GetYaxis()->SetLabelSize(15);

  // X axis ratio plot settings
  h1_ratio_up->GetXaxis()->SetTitleSize(20);
  h1_ratio_up->GetXaxis()->SetTitleFont(43);
  h1_ratio_up->GetXaxis()->SetTitleOffset(4.);
  h1_ratio_up->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h1_ratio_up->GetXaxis()->SetLabelSize(15);

  c->SaveAs("../plots/impact_tests/"+subcategory+"/pdf/"+subcategory+"_"+process.at(i_proc)+".pdf");
  c->SaveAs("../plots/impact_tests/"+subcategory+"/png/"+subcategory+"_"+process.at(i_proc)+".png");

  }

  return;

}

