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
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <TFrame.h>

using namespace std;


void plot_2lss0tau(){

	vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb.root");

  vector<TString> tHq_files;
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp.root");
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp.root");
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp.root");

  vector<TString> ttW_files;
  ttW_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu.root");
  ttW_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu.root");
  ttW_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu.root");

  vector<TString> ttZ_files;
  ttZ_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2.root");
  ttZ_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10.root");
  ttZ_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10.root");

  vector<TString> tt_files;
  tt_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept.root");
  tt_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept.root");
  tt_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept.root");
 
 	vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_2lss_SR","recoPFJet_pt[2]","MC_weight",10,20,140));
  h.push_back(single_plot(tHq_files,"HTauTauTree_2lss_SR","recoPFJet_pt[2]","MC_weight",10,20,140));
  h.push_back(single_plot(ttW_files,"HTauTauTree_2lss_SR","recoPFJet_pt[2]","MC_weight",10,20,140));
  h.push_back(single_plot(ttZ_files,"HTauTauTree_2lss_SR","recoPFJet_pt[2]","MC_weight",10,20,140));
  h.push_back(single_plot(tt_files,"HTauTauTree_2lss_SR","recoPFJet_pt[2]","MC_weight",10,20,140));

  TLegend* leg=new TLegend(0.7,0.60,0.85,0.87);
  leg->SetHeader("2lss + 0#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tHq");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");
  leg_entry.push_back("ttbar");


  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>3){
      h[i]->SetLineColor(i+2);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(20,140);
  h[0]->GetYaxis()->SetRangeUser(0,1.6*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Trailing jet p_{T} [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(20,0.33,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="2lss_0tau_jet3pt";
  c->SaveAs("plots_dnn/"+filename+".pdf");

  return;

}

void plot_2lss1tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_DNN_vbles_2lss1tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_DNN_vbles_2lss1tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_DNN_vbles_2lss1tau.root");

  vector<TString> tHq_files;
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_DNN_vbles_2lss1tau.root");
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_DNN_vbles_2lss1tau.root");
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_DNN_vbles_2lss1tau.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_DNN_vbles_2lss1tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_DNN_vbles_2lss1tau.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","avg_dr_jet","MC_weight",12,0,6));
  h.push_back(single_plot(tHq_files,"HTauTauTree_2lss1tau_SR","avg_dr_jet","MC_weight",12,0,6));
  h.push_back(single_plot(bkg_files,"HTauTauTree_2lss1tau_SR","avg_dr_jet","MC_weight",12,0,6));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("2lss + 1#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tHq");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(0,6);
  h[0]->GetYaxis()->SetRangeUser(0,1.3*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Average #DeltaR between jets");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,0.64,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="2lss_1tau_avrgjet";
  c->SaveAs("plots_dnn/"+filename+".pdf");

  return;

}

void plot_3l(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_DNN_vbles_3l.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_DNN_vbles_3l.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_DNN_vbles_3l.root");

  vector<TString> tHq_files;
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_DNN_vbles_3l.root");
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_DNN_vbles_3l.root");
  tHq_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_DNN_vbles_3l.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_DNN_vbles_3l.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_DNN_vbles_3l.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_3l_SR","recolep_sel_conept[0]","MC_weight",10,20,340));
  h.push_back(single_plot(tHq_files,"HTauTauTree_3l_SR","recolep_sel_conept[0]","MC_weight",10,20,340));
  h.push_back(single_plot(bkg_files,"HTauTauTree_3l_SR","recolep_sel_conept[0]","MC_weight",10,20,340));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("3l + 0#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tHq");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(20,340);
  h[0]->GetYaxis()->SetRangeUser(0,1.3*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Leading lepton p_{T} [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(20,0.45,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="3l_0tau_ptlep1";
  c->SaveAs("plots_dnn/"+filename+".pdf");

  return;

}

void plot_2tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-10to50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-10to50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-10to50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-50_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_2tau_SR","BDTscore_res_HTT","MC_weight",10,0,1));
  h.push_back(single_plot(bkg_files,"HTauTauTree_2tau_SR","BDTscore_res_HTT","MC_weight",10,0,1));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("0l + 2#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(0,1);
  h[0]->GetYaxis()->SetRangeUser(0,0.05*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Hadronic top tagger score");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0,0.87,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="0l2tau_htt";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}

void plot_1l1tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-10to50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-10to50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-10to50_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-50_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_1l1tau_SR","charge_lep_tau","MC_weight",5,-2,3));
  h.push_back(single_plot(bkg_files,"HTauTauTree_1l1tau_SR","charge_lep_tau","MC_weight",5,-2,3));

  TLegend* leg=new TLegend(0.63,0.68,0.83,0.87);
  leg->SetHeader("1l + 1#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(-2,3);
  h[0]->GetYaxis()->SetRangeUser(0,0.02*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Charge sum lepton and #tau_{h}");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(-2,1.18,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="1l1tau_chargesum";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}

void plot_1l2tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles_1l2tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles_1l2tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles_1l2tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles_1l2tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles_1l2tau.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles_1l2tau.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles_1l2tau.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles_1l2tau.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_1l2tau_SR","mTauTauVis","MC_weight",10,0,200));
  h.push_back(single_plot(bkg_files,"HTauTauTree_1l2tau_SR","mTauTauVis","MC_weight",10,0,200));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("1l + 2#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(0,200);
  h[0]->GetYaxis()->SetRangeUser(0,1.3*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Visible mass of #tau_{h}#tau_{h} pair [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0,0.435,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="1l2tau_mtautauvis";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}

void plot_2los1tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_2los1tau_SR","recotauh_sel_pt[0]","MC_weight",10,20,160));
  h.push_back(single_plot(bkg_files,"HTauTauTree_2los1tau_SR","recotauh_sel_pt[0]","MC_weight",10,20,160));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("2l os + 1#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(20,160);
  h[0]->GetYaxis()->SetRangeUser(0,1.6*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Leading #tau_{h} p_{T} [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(20,0.51,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="2los1tau_tau1pt";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}

void plot_2l2tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_2l2tau_SR","recotauh_sel_pt[0]","MC_weight",10,20,220));
  h.push_back(single_plot(bkg_files,"HTauTauTree_2l2tau_SR","recotauh_sel_pt[0]","MC_weight",10,20,220));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("2l + 2#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(20,220);
  h[0]->GetYaxis()->SetRangeUser(0,1.3*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Leading #tau_{h} p_{T} [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(20,0.415,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="2l2tau_taupt1";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}

void plot_3l1tau(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_3l1tau_SR","massL","MC_weight",10,0,200));
  h.push_back(single_plot(bkg_files,"HTauTauTree_3l1tau_SR","massL","MC_weight",10,0,200));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("3l + 1#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(0,200);
  h[0]->GetYaxis()->SetRangeUser(0,1.3*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Minimum invariant mass lepton pairs [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0,0.44,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="3l1tau_mll";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}

void plot_4l(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_BDT_vbles.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_BDT_vbles.root");

  vector<TString> bkg_files;
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_BDT_vbles.root");
  bkg_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_BDT_vbles.root");
 
  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree_4l_SR","massL4","MC_weight",10,0,500));
  h.push_back(single_plot(bkg_files,"HTauTauTree_4l_SR","massL4","MC_weight",10,0,500));

  TLegend* leg=new TLegend(0.60,0.68,0.8,0.87);
  leg->SetHeader("4l + 0#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Signals");
  leg_entry.push_back("Backgrounds");

  float mymax = 0;
  for(unsigned int i=0;i<h.size();i++){
    cout<<h[i]->GetMaximum()<<endl;
    h[i]->SetLineColor(i+1);
    if(i>1){
      h[i]->SetLineColor(i+4);
    }
    h[i]->SetLineWidth(2);
    h[i]->SetFillColor(0);
    leg->AddEntry(h[i],leg_entry[i]);

    if(h[i]->GetMaximum() > mymax) 
      mymax = h[i]->GetMaximum();
  }

  //cout<<"mymax "<<mymax<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  //h[0]->SetMaximum(1);
  //h[0]->SetMinimum(0);

  h[0]->SetStats(0);
  h[0]->GetXaxis()->SetRangeUser(0,500);
  h[0]->GetYaxis()->SetRangeUser(0,1.3*mymax);
  //h[0]->SetMaximum(0.5);
  h[0]->GetXaxis()->SetTitle("Invariant mass of 4-lepton system [GeV]");
  h[0]->GetYaxis()->SetTitle("Normalized events");
  h[0]->GetXaxis()->SetTitleOffset(1.2);
  h[0]->GetYaxis()->SetTitleOffset(1.8);
  gPad->SetTicks(1,1);
  gStyle->SetOptStat(0);

  h[0]->SetTitle(" ");
  h[0]->DrawNormalized("hist");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->DrawNormalized("histsame");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0,0.32,"CMS #bf{#it{Preliminary}}, #bf{MC simulation (13 TeV)}");
  texl->SetTextSize(0.035);
  texl->Draw("same");

  TString filename="4l_m4l";
  c->SaveAs("plots_bdt/"+filename+".pdf");

  return;

}
