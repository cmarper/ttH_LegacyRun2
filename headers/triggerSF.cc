#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

#include "TauTriggerSFs2017/src/TauTriggerSFs2017.cc"


float triggerSF_ttH(int pdgid1, float pt1, int pdgid2, float pt2, int nlep, float shift = 0){

  if (nlep>=3) return 1.0+shift*0.05;

  int comb = abs(pdgid1)+abs(pdgid2);

  if (comb==22) return (pt1<30) ? (0.937+shift*0.027) : (0.991+shift*0.002); // ee
  else if (comb==24) { // em
    if (pt1<35) return 0.952+shift*0.008;
    else if (pt1<50) return 0.983+shift*0.003;
    else return 1.0+shift*0.001;
  }
  else if (comb==26) return (pt1<35) ? (0.972+shift*0.006) : (0.994+shift*0.001); // mm

  std::cout << "ERROR: triggerSF_ttH called with wrong input, returning 1" << std::endl;
  return 1;

}



//Trigger SF for 1l+2tau

// Single Muon triggers
TFile *file_Mu_SingleMu_hlt_eff = NULL;
TGraphAsymmErrors *g_Mu_ZMassEtaLt0p9_MC = NULL;
TGraphAsymmErrors *g_Mu_ZMassEta0p9to1p2_MC = NULL;
TGraphAsymmErrors *g_Mu_ZMassEta1p2to2p1_MC = NULL;
TGraphAsymmErrors *g_Mu_ZMassEtaGt2p1_MC = NULL;
TGraphAsymmErrors *g_Mu_ZMassEtaLt0p9_Data = NULL;
TGraphAsymmErrors *g_Mu_ZMassEta0p9to1p2_Data = NULL;
TGraphAsymmErrors *g_Mu_ZMassEta1p2to2p1_Data = NULL;
TGraphAsymmErrors *g_Mu_ZMassEtaGt2p1_Data= NULL;

// Single Ele triggers
TFile *file_Ele_SingleElE_hlt_eff = NULL;
TGraphAsymmErrors *g_Ele_ZMassEtaLt1p48_MC = NULL;
TGraphAsymmErrors *g_Ele_ZMassEta1p48to2p1_MC = NULL;
TGraphAsymmErrors *g_Ele_ZMassEtaLt1p48_Data = NULL;
TGraphAsymmErrors *g_Ele_ZMassEta1p48to2p1_Data = NULL;

// Muon leg of MuTau cross triggers
TFile *file_Mu_MuTau_hlt_eff = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEtaLt0p9_MC = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEta0p9to1p2_MC = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEta1p2to2p1_MC = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEtaGt2p1_MC = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEtaLt0p9_Data = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEta0p9to1p2_Data = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEta1p2to2p1_Data = NULL;
TGraphAsymmErrors *g_Muleg_ZMassEtaGt2p1_Data = NULL;

// Electron leg of EleTau cross triggers
TFile *file_Ele_EleTau_hlt_eff = NULL;
TGraphAsymmErrors *g_Eleleg_ZMassEtaLt1p48_MC = NULL;
TGraphAsymmErrors *g_Eleleg_ZMassEta1p48to2p1_MC = NULL;
TGraphAsymmErrors *g_Eleleg_ZMassEtaLt1p48_Data = NULL;
TGraphAsymmErrors *g_Eleleg_ZMassEta1p48to2p1_Data = NULL;

// tau leg of lepton-tau cross triggers
TauTriggerSFs2017* tauTrigSFhelper = NULL;


void setup_triggerSF_ttH_1l(){

  file_Mu_SingleMu_hlt_eff = new TFile("lepSF/Muon_IsoMu24orIsoMu27_eff.root","read");
  g_Mu_ZMassEtaLt0p9_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaLt0p9_MC");
  g_Mu_ZMassEta0p9to1p2_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta0p9to1p2_MC");
  g_Mu_ZMassEta1p2to2p1_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta1p2to2p1_MC");
  g_Mu_ZMassEtaGt2p1_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaGt2p1_MC");
  g_Mu_ZMassEtaLt0p9_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaLt0p9_Data");
  g_Mu_ZMassEta0p9to1p2_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta0p9to1p2_Data");
  g_Mu_ZMassEta1p2to2p1_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta1p2to2p1_Data");
  g_Mu_ZMassEtaGt2p1_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaGt2p1_Data");

  file_Ele_SingleElE_hlt_eff = new TFile("lepSF/Electron_Ele32orEle35_eff.root","read");
  g_Ele_ZMassEtaLt1p48_MC = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEtaLt1p48_MC");
  g_Ele_ZMassEta1p48to2p1_MC = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEta1p48to2p1_MC");
  g_Ele_ZMassEtaLt1p48_Data = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEtaLt1p48_Data");
  g_Ele_ZMassEta1p48to2p1_Data = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEta1p48to2p1_Data");

  file_Mu_MuTau_hlt_eff = new TFile("lepSF/Muon_MuTau_IsoMu20_eff.root","read");
  g_Muleg_ZMassEtaLt0p9_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaLt0p9_MC");
  g_Muleg_ZMassEta0p9to1p2_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta0p9to1p2_MC");
  g_Muleg_ZMassEta1p2to2p1_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta1p2to2p1_MC");
  g_Muleg_ZMassEtaGt2p1_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaGt2p1_MC");
  g_Muleg_ZMassEtaLt0p9_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaLt0p9_Data");
  g_Muleg_ZMassEta0p9to1p2_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta0p9to1p2_Data");
  g_Muleg_ZMassEta1p2to2p1_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta1p2to2p1_Data");
  g_Muleg_ZMassEtaGt2p1_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaGt2p1_Data");

  file_Ele_EleTau_hlt_eff = new TFile("lepSF/Electron_EleTau_Ele24_eff.root","read"); 
  g_Eleleg_ZMassEtaLt1p48_MC = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEtaLt1p48_MC");
  g_Eleleg_ZMassEta1p48to2p1_MC = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEta1p48to2p1_MC");
  g_Eleleg_ZMassEtaLt1p48_Data = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEtaLt1p48_Data");
  g_Eleleg_ZMassEta1p48to2p1_Data = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEta1p48to2p1_Data");

  tauTrigSFhelper = new TauTriggerSFs2017("TauTriggerSFs2017/data/tauTriggerEfficiencies2017.root","medium");     

}

void close_triggerSF_ttH_1l(){

  file_Mu_SingleMu_hlt_eff->Close();
  file_Ele_SingleElE_hlt_eff->Close();
  file_Mu_MuTau_hlt_eff->Close();
  file_Ele_EleTau_hlt_eff->Close();

  delete file_Mu_SingleMu_hlt_eff;
  delete file_Ele_SingleElE_hlt_eff;
  delete file_Mu_MuTau_hlt_eff;
  delete file_Ele_EleTau_hlt_eff;
  delete tauTrigSFhelper;

}

float compute_trig_eff_OR_1l2tau(float eff_L, float eff_l, float eff_tau1, float eff_tau2, bool passHLT1l, bool passHLT1l1tau)
{
  if (passHLT1l and !passHLT1l1tau) { // only the single lepton trigger fires
    return std::max(1.e-2f,
           eff_L-std::min(eff_L,eff_l)*(1-(1-eff_tau1)*(1-eff_tau2)));
  }
  else if (!passHLT1l and passHLT1l1tau) { // only cross trigger fires
    return std::max(1.e-2f, (eff_l-eff_L)*(1-(1-eff_tau1)*(1-eff_tau2)));
  }
  else if (passHLT1l and passHLT1l1tau) { // both triggers fire
    return std::min(eff_L, eff_l)*(1-(1-eff_tau1)*(1-eff_tau2));
  }

  return 0.;
}


float get_trig_eff_singleLep(float pt, float eta, int pdgid, bool isdata)
{
  float eff = 0.;

  if(pdgid==11){
    if(fabs(eta)<1.48) {
      TGraphAsymmErrors *hist = (isdata) ? g_Ele_ZMassEtaLt1p48_Data : g_Ele_ZMassEtaLt1p48_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else if (fabs(eta)<2.1) {
      TGraphAsymmErrors *hist = (isdata) ? g_Ele_ZMassEta1p48to2p1_Data : g_Ele_ZMassEta1p48to2p1_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else { 
      assert(0);
    }
  }

  if(pdgid==13){
    if(fabs(eta)<0.9) {
      TGraphAsymmErrors *hist = (isdata) ? g_Mu_ZMassEtaLt0p9_Data : g_Mu_ZMassEtaLt0p9_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else if (fabs(eta)<1.2) {
      TGraphAsymmErrors *hist = (isdata) ? g_Mu_ZMassEta0p9to1p2_Data : g_Mu_ZMassEta0p9to1p2_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else if (fabs(eta)<2.1) {
      TGraphAsymmErrors *hist = (isdata) ? g_Mu_ZMassEta1p2to2p1_Data : g_Mu_ZMassEta1p2to2p1_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else { 
      assert(0);
    }
  }

  return eff;
}



float get_trig_eff_lepLeg_crossTrigger(float pt, float eta, int pdgid, bool isdata)
{
  float eff = 0.;

  if(pdgid==11){
    if(fabs(eta)<1.48) {
      TGraphAsymmErrors *hist = (isdata) ? g_Eleleg_ZMassEtaLt1p48_Data : g_Eleleg_ZMassEtaLt1p48_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else if (fabs(eta)<2.1) {
      TGraphAsymmErrors *hist = (isdata) ? g_Eleleg_ZMassEta1p48to2p1_Data : g_Eleleg_ZMassEta1p48to2p1_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else { 
      assert(0);
    }
  }
  if(pdgid==13){
    if(fabs(eta)<0.9) {
      TGraphAsymmErrors *hist = (isdata) ? g_Muleg_ZMassEtaLt0p9_Data : g_Muleg_ZMassEtaLt0p9_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else if (fabs(eta)<1.2) {
      TGraphAsymmErrors *hist = (isdata) ? g_Muleg_ZMassEta0p9to1p2_Data : g_Muleg_ZMassEta0p9to1p2_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else if (fabs(eta)<2.1) {
      TGraphAsymmErrors *hist = (isdata) ? g_Muleg_ZMassEta1p2to2p1_Data : g_Muleg_ZMassEta1p2to2p1_MC;
      float pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt));
      eff = hist->Eval(pt1);
    }
    else { 
      assert(0);
    }
  }

  return eff;
}


float triggerSF_ttH_1l(double lep_pt, double lep_eta, double lep_pdg, 
                      double tau1_pt, double tau1_eta, double tau1_phi, 
                      double tau2_pt, double tau2_eta, double tau2_phi, 
                      bool passHLT1l, bool passHLT1l1tau) {

  setup_triggerSF_ttH_1l();
  
  float eff_L_data = get_trig_eff_singleLep(lep_pt, lep_eta,lep_pdg, true);
  float eff_L_mc = get_trig_eff_singleLep(lep_pt, lep_eta,lep_pdg, false);
  float eff_l_data = get_trig_eff_lepLeg_crossTrigger(lep_pt, lep_eta,lep_pdg, true);
  float eff_l_mc = get_trig_eff_lepLeg_crossTrigger(lep_pt, lep_eta,lep_pdg, false);
  float eff_t1_data, eff_t1_mc, eff_t2_data, eff_t2_mc;
  
  if (fabs(lep_pdg)==11) { // ele+tau
    eff_t1_data = tauTrigSFhelper->getETauEfficiencyData(tau1_pt,tau1_eta,tau1_phi);
    eff_t1_mc = tauTrigSFhelper->getETauEfficiencyMC(tau1_pt,tau1_eta,tau1_phi);
    eff_t2_data = tauTrigSFhelper->getETauEfficiencyData(tau2_pt,tau2_eta,tau2_phi);
    eff_t2_mc = tauTrigSFhelper->getETauEfficiencyMC(tau2_pt,tau2_eta,tau2_phi);
  }
  else { // mu+tau
    eff_t1_data = tauTrigSFhelper->getMuTauEfficiencyData(tau1_pt,tau1_eta,tau1_phi);
    eff_t1_mc = tauTrigSFhelper->getMuTauEfficiencyMC(tau1_pt,tau1_eta,tau1_phi);
    eff_t2_data = tauTrigSFhelper->getMuTauEfficiencyData(tau2_pt,tau2_eta,tau2_phi);
    eff_t2_mc = tauTrigSFhelper->getMuTauEfficiencyMC(tau2_pt,tau2_eta,tau2_phi);
  }
  
  // compute trigger efficiency based on triggered HLT paths
  float eff_data = compute_trig_eff_OR_1l2tau(eff_L_data,eff_l_data,eff_t1_data, eff_t2_data, passHLT1l, passHLT1l1tau);
  float eff_mc = compute_trig_eff_OR_1l2tau(eff_L_mc, eff_l_mc, eff_t1_mc, eff_t2_mc, passHLT1l,passHLT1l1tau);
  
  // scale factor
  return std::min( eff_data/std::max(1.e-6f, eff_mc), 1.e+1f);

 
}


