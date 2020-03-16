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

using namespace std;


void plot_time_ttH_per_weight(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH)","1",10,0,10));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH)","1",10,0,10));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH)","1",10,0,10));

  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttZ)","1",10,0,10));
  h[1]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttZ)","1",10,0,10));
  h[1]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttZ)","1",10,0,10));

  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttZ_Zll)","1",10,0,10));
  h[2]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttZ_Zll)","1",10,0,10));
  h[2]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttZ_Zll)","1",10,0,10));

  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",10,0,10));
  h[3]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",10,0,10));
  h[3]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",10,0,10));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau weight");
  leg_entry.push_back("ttZ Z#rightarrowll weight");
  leg_entry.push_back("t#bar{t} weight");

  TLegend* leg=new TLegend(0.5,0.65,0.8,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    //h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);

    //cout<<leg_entry[i]<<endl;
    //cout<<"Average time:"<<h[i]->GetMean()<<endl;
    //cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Computational time / event / weight [s]");
  h[0]->GetYaxis()->SetTitle("Events");
  h[0]->GetYaxis()->SetTitleOffset(1.9);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, MC t#bar{t}H 2lss+1#tau_{h} (2016+2017+2018)");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_per_weight";
  c->SaveAs("../plots/comp_time/pdf/"+filename+".pdf");
  c->SaveAs("../plots/comp_time/png/"+filename+".png");

  return;

}

void plot_time_ttH_all_weights(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  
  h[0]->SetLineColor(2);
  h[0]->SetLineWidth(2);
  h[0]->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Computational time / event [s]");
  h[0]->GetYaxis()->SetTitle("Events");
  h[0]->GetYaxis()->SetTitleOffset(1.9);

  TLegend* leg=new TLegend(0.5,0.65,0.8,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h[0],"All weights");

  h[0]->Draw();
  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, MC t#bar{t}H 2lss+1#tau_{h} (2016+2017+2018)");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_all_weights";

  c->SaveAs("../plots/comp_time/pdf/"+filename+".pdf");
  c->SaveAs("../plots/comp_time/png/"+filename+".png");

  return;

}

void plot_time_all_weights_all_processes(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
 
  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[1]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[1]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));

  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_ext1_MEM_fake.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[2]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_MEM_fake.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));
  h[2]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_MEM_fake.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","1",16,0,40));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH process");
  leg_entry.push_back("ttZ process");
  leg_entry.push_back("t#bar{t} process");

  TLegend* leg=new TLegend(0.6,0.65,0.9,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    //h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);

    //cout<<leg_entry[i]<<endl;
    //cout<<"Average time:"<<h[i]->GetMean()<<endl;
    //cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Computational time / event [s]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetYaxis()->SetTitleOffset(1.6);

  h[0]->DrawNormalized();

  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,0.32,"CMS Preliminary, #sqrt{s}=13 TeV, MC 2lss+1#tau_{h} (2016+2017+2018)");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_all_weights_all_processes";
  c->SaveAs("../plots/comp_time/pdf/"+filename+".pdf");
  c->SaveAs("../plots/comp_time/png/"+filename+".png");

  return;

}

void plot_time_ttH_all_weights_miss_nomiss(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","integration_type==0",16,0,40));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","integration_type==0",16,0,40));
  h[0]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","integration_type==0",16,0,40));
  
  h.push_back(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","integration_type==1",16,0,40));
  h[1]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","integration_type==1",16,0,40));
  h[1]->Add(single_plot("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttZ_Zll+CompTime_ttbar_DL_fakelep_ttau+CompTime_ttbar_DL_fakelep_tlep)","integration_type==1",16,0,40));
  
  vector<TString> leg_entry;
  leg_entry.push_back("No-missing-jet");
  leg_entry.push_back("Missing-jet");

  TLegend* leg=new TLegend(0.5,0.7,0.8,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlue);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    //h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);

    //cout<<leg_entry[i]<<endl;
    //cout<<"Average time:"<<h[i]->GetMean()<<endl;
    //cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Computational time / event [s]");
  h[0]->GetYaxis()->SetTitle("Events");
  h[0]->GetYaxis()->SetTitleOffset(1.9);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, MC t#bar{t}H 2lss+1#tau_{h} (2016+2017+2018)");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_all_weights_miss_nomiss";

  c->SaveAs("../plots/comp_time/pdf/"+filename+".pdf");
  c->SaveAs("../plots/comp_time/png/"+filename+".png");

  return;

}