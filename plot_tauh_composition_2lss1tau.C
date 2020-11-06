#include <TFile.h>
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

void get_tau_composition(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root");
  ttH_files.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root");
  
  TString hww = "(genH_decayMode[1]>5 && n_genW==4)";
  TString hzz = "(genH_decayMode[1]>5 && n_genZ==2)";
  TString htt = "(genH_decayMode[1]<=5)";

  vector<TH1F*> h_hww_tot;
  h_hww_tot.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hww+" && recotauh_dR_closest_genpart<0.3 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));

  vector<TH1F*> h_hww;
  h_hww.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hww+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==15 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hww.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hww+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==66615 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hww.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hww+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<7 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hww.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hww+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hww.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hww+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));

  cout<<"------------------------"<<endl;
  cout<<" ttH H WW 2lSS1tau"<<endl;
  for(unsigned int i=0;i<h_hww.size();i++){
    cout<<"   i = "<<i<<endl;
    cout<<"      numerator: "<<h_hww[i]->GetEntries()<<endl;  
    cout<<"      denominator: "<<h_hww_tot[0]->GetEntries()<<endl; 
    cout<<"      fraction: "<<h_hww[i]->GetEntries()/h_hww_tot[0]->GetEntries()<<endl;    
  }
  cout<<"------------------------"<<endl;

  vector<TH1F*> h_hzz_tot;
  h_hzz_tot.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hzz+" && recotauh_dR_closest_genpart<0.3 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));

  vector<TH1F*> h_hzz;
  h_hzz.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hzz+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==15 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hzz.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hzz+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==66615 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hzz.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hzz+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<7 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hzz.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hzz+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_hzz.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+hzz+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));

  cout<<"------------------------"<<endl;
  cout<<" ttH H ZZ 2lSS1tau"<<endl;
  for(unsigned int i=0;i<h_hzz.size();i++){
    cout<<"   i = "<<i<<endl;
    cout<<"      numerator: "<<h_hzz[i]->GetEntries()<<endl;  
    cout<<"      denominator: "<<h_hzz_tot[0]->GetEntries()<<endl; 
    cout<<"      fraction: "<<h_hzz[i]->GetEntries()/h_hzz_tot[0]->GetEntries()<<endl;    
  }
  cout<<"------------------------"<<endl;

  vector<TH1F*> h_htt_tot;
  h_htt_tot.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+htt+" && recotauh_dR_closest_genpart<0.3 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));

  vector<TH1F*> h_htt;
  h_htt.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+htt+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==15 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_htt.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+htt+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==66615 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_htt.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+htt+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<7 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_htt.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+htt+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));
  h_htt.push_back(single_plot(ttH_files,"HTauTauTree_2lss1tau_SR","genpart_pt[recotauh_i_closest_genpart]","MC_weight*("+htt+" && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3)",10,20,220));

  cout<<"------------------------"<<endl;
  cout<<" ttH H tautau 2lSS1tau"<<endl;
  for(unsigned int i=0;i<h_htt.size();i++){
    cout<<"   i = "<<i<<endl;
    cout<<"      numerator: "<<h_htt[i]->GetEntries()<<endl;  
    cout<<"      denominator: "<<h_htt_tot[0]->GetEntries()<<endl; 
    cout<<"      fraction: "<<h_htt[i]->GetEntries()/h_htt_tot[0]->GetEntries()<<endl;    
  }
  cout<<"------------------------"<<endl;

  return;

}



void plot_fractions(){

  TString antiMu_WP[3] = { "H #rightarrow #tau#tau", "H #rightarrow WW", "H #rightarrow ZZ"};

  //good none, loose, tight
  float ttH_gentau[3] = {0.107767+0.734582, 0.0664376+0.391011,0.0561594+0.376812};
  float ttH_faketaufromjet[3] = {0.074879, 0.410821, 0.273551};
  float ttH_faketaufromele[3] = {0.0214165, 0.0641466, 0.17029};
  float ttH_faketaufrommu[3] = {0.0232583, 0.0309952, 0.0942029};

  TH1F *h_ttH_gentau = new TH1F("h_ttH_gentau","h_ttH_gentau",3,0,3);
  for (int i=0; i<3; i++){
    h_ttH_gentau->AddBinContent(i+1,ttH_gentau[i]);
    h_ttH_gentau->SetBinError(i+1,0.000001);
    h_ttH_gentau->GetXaxis()->SetBinLabel(i+1,antiMu_WP[i]);
  }

  TH1F *h_ttH_faketaufromjet = new TH1F("h_ttH_faketaufromjet","h_ttH_faketaufromjet",3,0,3);
  for (int i=0; i<3; i++){
    h_ttH_faketaufromjet->AddBinContent(i+1,ttH_faketaufromjet[i]);
    h_ttH_faketaufromjet->SetBinError(i+1,0.000001);
    h_ttH_faketaufromjet->GetXaxis()->SetBinLabel(i+1,antiMu_WP[i]);
  }

  TH1F *h_ttH_faketaufromele = new TH1F("h_ttH_faketaufromele","h_ttH_faketaufromele",3,0,3);
  for (int i=0; i<3; i++){
    h_ttH_faketaufromele->AddBinContent(i+1,ttH_faketaufromele[i]);
    h_ttH_faketaufromele->SetBinError(i+1,0.000001);
    h_ttH_faketaufromele->GetXaxis()->SetBinLabel(i+1,antiMu_WP[i]);
  }

  TH1F *h_ttH_faketaufrommu = new TH1F("h_ttH_faketaufrommu","h_ttH_faketaufrommu",3,0,3);
  for (int i=0; i<3; i++){
    h_ttH_faketaufrommu->AddBinContent(i+1,ttH_faketaufrommu[i]);
    h_ttH_faketaufrommu->SetBinError(i+1,0.000001);
    h_ttH_faketaufrommu->GetXaxis()->SetBinLabel(i+1,antiMu_WP[i]);
  }

  TLatex *texl1 = new TLatex(0.1,1.02,"#bf{CMS} #it{Preliminary}");
  texl1->SetTextSize(0.04);
  texl1->SetTextFont(42);

  TLatex *texl2 = new TLatex(2.5,1.02,"(13 TeV)");
  texl2->SetTextSize(0.04);
  texl2->SetTextFont(42);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH_gentau->SetMaximum(1);
  h_ttH_gentau->SetMinimum(0);
  h_ttH_gentau->SetTitle(" ");
  h_ttH_gentau->SetStats(0);

  h_ttH_gentau->SetLineColor(1);
  h_ttH_faketaufromjet->SetLineColor(2);
  h_ttH_faketaufromele->SetLineColor(3);
  h_ttH_faketaufrommu->SetLineColor(4);

  h_ttH_gentau->SetMarkerColor(1);
  h_ttH_faketaufromjet->SetMarkerColor(2);
  h_ttH_faketaufromele->SetMarkerColor(3);
  h_ttH_faketaufrommu->SetMarkerColor(4);

  h_ttH_gentau->SetMarkerStyle(20);
  h_ttH_faketaufromjet->SetMarkerStyle(21);
  h_ttH_faketaufromele->SetMarkerStyle(22);
  h_ttH_faketaufrommu->SetMarkerStyle(23);

  h_ttH_gentau->SetLineWidth(2);
  h_ttH_faketaufromjet->SetLineWidth(2);
  h_ttH_faketaufromele->SetLineWidth(2);
  h_ttH_faketaufrommu->SetLineWidth(2);

  h_ttH_gentau->SetFillColor(0);
  h_ttH_faketaufromjet->SetFillColor(0);
  h_ttH_faketaufromele->SetFillColor(0);
  h_ttH_faketaufrommu->SetFillColor(0);

  h_ttH_gentau->GetYaxis()->SetTitle("Fraction");
  h_ttH_gentau->GetXaxis()->SetLabelSize(0.06);
  h_ttH_gentau->GetYaxis()->SetTitleSize(0.05);
  //h_ttH_gentau->GetXaxis()->SetTitle("Anti-muon MVA 3 WP");

  h_ttH_gentau->Draw("E");
  h_ttH_faketaufromjet->Draw("E same");
  h_ttH_faketaufromele->Draw("E same");
  h_ttH_faketaufrommu->Draw("E same");

  TLegend* leg=new  TLegend(0.45,0.65,0.85,0.85);
  leg->SetHeader("t#bar{t}H, 2lss+1#tau_{h}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  leg->AddEntry(h_ttH_gentau, "Genuine #tau_{h}", "apl");
  leg->AddEntry(h_ttH_faketaufromjet, "Fake #tau_{h} from jet", "apl");
  leg->AddEntry(h_ttH_faketaufromele, "Fake #tau_{h} from electron", "apl");
  leg->AddEntry(h_ttH_faketaufrommu, "Fake #tau_{h} from muon", "apl");

  leg->Draw("same");
  texl1->Draw("same");
  texl2->Draw("same");

  TString filename="tauscomposition_ttH_2lss1tau";
  c->SaveAs(filename+".pdf");
  c->SaveAs(filename+".root");

}
