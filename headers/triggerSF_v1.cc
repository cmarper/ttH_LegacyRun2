#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

#include "/home/llr/cms/mperez/ttH/Legacy/macros/TauTriggerSFs/src/SFProvider.cc"
#include "/home/llr/cms/mperez/ttH/Legacy/macros/TauTriggerSFs/interface/SFProvider.h"

using namespace tau_trigger;

float get_triggerSF_leptonic(int pdgid1, float pt1, int pdgid2, float pt2, int nlep, float shift = 0, int year = 2016){

    int comb = abs(pdgid1)+abs(pdgid2);

    if(year==2016){

      if (nlep>=3) return 1.0+shift*0.01;

      if (comb==22) return (pt2<25) ? (0.98+shift*0.02) : (1.00+shift*0.02); // ee
      else if (comb==24) return 1.00+shift*0.01; // em
      else if (comb==26) return 0.99+shift*0.01; // mm

    }

    else if(year==2017) { 

      if (nlep>=3) return 1.0+shift*0.01;

      if (comb==22) return (pt2<40) ? (0.98+shift*0.01) : (1.00+shift*0.01); // ee
      else if (comb==24) return (pt2<40) ? (0.98+shift*0.01) : (0.99+shift*0.01); // em
      else if (comb==26) { // mm
          if (pt2<40) return 0.97+shift*0.02;
          else if (pt2<55) return 0.995+shift*0.02;
          else if (pt2<70) return 0.96+shift*0.02;
          else return 0.94+shift*0.02;
      }

    }

    else if(year==2018) { 

      if (nlep>=3) return 1.0+shift*0.01;

      if (comb==22) return (pt2<25) ? (0.98+shift*0.01) : (1.0+shift*0.01); // ee
      else if (comb==24) return (pt2<25) ? (0.98+shift*0.01) : (1.00+shift*0.01); // em
      else if (comb==26) { // mm
          if (pt1<40) return 1.01+shift*0.01;
          else if (pt1<70) return 0.995+shift*0.01;
          else return 0.98+shift*0.01;
      }

    }

    std::cout << "ERROR: triggerSF_ttH called with wrong input, returning 1" << std::endl;
    return 1;

}


//Trigger SF for 1l+2tau, 1l+1tau, 0l+2tau

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
SFProvider* tauTrigSFhelper_mutau_VVLWP = NULL;
SFProvider* tauTrigSFhelper_mutau_MWP = NULL;
SFProvider* tauTrigSFhelper_etau_VVLWP = NULL;
SFProvider* tauTrigSFhelper_etau_MWP = NULL;
SFProvider* tauTrigSFhelper_ditau_VVLWP = NULL;
SFProvider* tauTrigSFhelper_ditau_LWP = NULL;


void setup_triggerSF_files(int year){

  file_Mu_SingleMu_hlt_eff = new TFile("lepSF/Muon_Mu22OR_eta2p1_eff.root","read");
  if(year==2017) file_Mu_SingleMu_hlt_eff = new TFile("lepSF/Muon_IsoMu24orIsoMu27_eff.root","read");
  if(year==2018) file_Mu_SingleMu_hlt_eff = new TFile("lepSF/Muon_Run2018_IsoMu24orIsoMu27.root","read");

  g_Mu_ZMassEtaLt0p9_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaLt0p9_MC");
  g_Mu_ZMassEta0p9to1p2_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta0p9to1p2_MC");
  g_Mu_ZMassEta1p2to2p1_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta1p2to2p1_MC");
  g_Mu_ZMassEtaGt2p1_MC = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaGt2p1_MC");
  g_Mu_ZMassEtaLt0p9_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaLt0p9_Data");
  g_Mu_ZMassEta0p9to1p2_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta0p9to1p2_Data");
  g_Mu_ZMassEta1p2to2p1_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEta1p2to2p1_Data");
  g_Mu_ZMassEtaGt2p1_Data = (TGraphAsymmErrors*)file_Mu_SingleMu_hlt_eff->Get("ZMassEtaGt2p1_Data");

  file_Ele_SingleElE_hlt_eff = new TFile("lepSF/Electron_Ele25WPTight_eff.root","read");
  if(year==2017) file_Ele_SingleElE_hlt_eff = new TFile("lepSF/Electron_Ele32orEle35_eff.root","read");
  if(year==2018) file_Ele_SingleElE_hlt_eff = new TFile("lepSF/Electron_Run2018_Ele32orEle35.root","read");

  g_Ele_ZMassEtaLt1p48_MC = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEtaLt1p48_MC");
  g_Ele_ZMassEta1p48to2p1_MC = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEta1p48to2p1_MC");
  g_Ele_ZMassEtaLt1p48_Data = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEtaLt1p48_Data");
  g_Ele_ZMassEta1p48to2p1_Data = (TGraphAsymmErrors*)file_Ele_SingleElE_hlt_eff->Get("ZMassEta1p48to2p1_Data");

  file_Mu_MuTau_hlt_eff = new TFile("lepSF/Muon_Mu19leg_2016BtoH_eff.root","read");
  if(year==2017) file_Mu_MuTau_hlt_eff = new TFile("lepSF/Muon_MuTau_IsoMu20_eff.root","read");
  if(year==2018) file_Mu_MuTau_hlt_eff = new TFile("lepSF/Muon_Run2018_IsoMu20.root","read");

  g_Muleg_ZMassEtaLt0p9_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaLt0p9_MC");
  g_Muleg_ZMassEta0p9to1p2_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta0p9to1p2_MC");
  g_Muleg_ZMassEta1p2to2p1_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta1p2to2p1_MC");
  g_Muleg_ZMassEtaGt2p1_MC = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaGt2p1_MC");
  g_Muleg_ZMassEtaLt0p9_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaLt0p9_Data");
  g_Muleg_ZMassEta0p9to1p2_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta0p9to1p2_Data");
  g_Muleg_ZMassEta1p2to2p1_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEta1p2to2p1_Data");
  g_Muleg_ZMassEtaGt2p1_Data = (TGraphAsymmErrors*)file_Mu_MuTau_hlt_eff->Get("ZMassEtaGt2p1_Data");

  file_Ele_EleTau_hlt_eff = new TFile("lepSF/Electron_Ele24_eff.root","read"); 
  if(year==2017) file_Ele_EleTau_hlt_eff = new TFile("lepSF/Electron_EleTau_Ele24_eff.root","read"); 
  if(year==2018) file_Ele_EleTau_hlt_eff = new TFile("lepSF/Electron_Run2018_Ele24.root","read"); 
  g_Eleleg_ZMassEtaLt1p48_MC = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEtaLt1p48_MC");
  g_Eleleg_ZMassEta1p48to2p1_MC = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEta1p48to2p1_MC");
  g_Eleleg_ZMassEtaLt1p48_Data = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEtaLt1p48_Data");
  g_Eleleg_ZMassEta1p48to2p1_Data = (TGraphAsymmErrors*)file_Ele_EleTau_hlt_eff->Get("ZMassEta1p48to2p1_Data");

  std::string dirtauSF = "TauTriggerSFs/data/";

  tauTrigSFhelper_mutau_VVLWP = new SFProvider(dirtauSF+"2016_tauTriggerEff_DeepTau2017v2p1.root","mutau","VVLoose");   
  if(year==2017) tauTrigSFhelper_mutau_VVLWP = new SFProvider(dirtauSF+"2017_tauTriggerEff_DeepTau2017v2p1.root","mutau","VVLoose");   
  if(year==2018) tauTrigSFhelper_mutau_VVLWP = new SFProvider(dirtauSF+"2018_tauTriggerEff_DeepTau2017v2p1.root","mutau","VVLoose");

  tauTrigSFhelper_mutau_MWP = new SFProvider(dirtauSF+"2016_tauTriggerEff_DeepTau2017v2p1.root","mutau","Medium");   
  if(year==2017) tauTrigSFhelper_mutau_MWP = new SFProvider(dirtauSF+"2017_tauTriggerEff_DeepTau2017v2p1.root","mutau","Medium");   
  if(year==2018) tauTrigSFhelper_mutau_MWP = new SFProvider(dirtauSF+"2018_tauTriggerEff_DeepTau2017v2p1.root","mutau","Medium"); 

  tauTrigSFhelper_etau_VVLWP = new SFProvider(dirtauSF+"2016_tauTriggerEff_DeepTau2017v2p1.root","etau","VVLoose");   
  if(year==2017) tauTrigSFhelper_etau_VVLWP = new SFProvider(dirtauSF+"2017_tauTriggerEff_DeepTau2017v2p1.root","etau","VVLoose");   
  if(year==2018) tauTrigSFhelper_etau_VVLWP = new SFProvider(dirtauSF+"2018_tauTriggerEff_DeepTau2017v2p1.root","etau","VVLoose"); 

  tauTrigSFhelper_etau_MWP = new SFProvider(dirtauSF+"2016_tauTriggerEff_DeepTau2017v2p1.root","etau","Medium");   
  if(year==2017) tauTrigSFhelper_etau_MWP = new SFProvider(dirtauSF+"2017_tauTriggerEff_DeepTau2017v2p1.root","etau","Medium");   
  if(year==2018) tauTrigSFhelper_etau_MWP = new SFProvider(dirtauSF+"2018_tauTriggerEff_DeepTau2017v2p1.root","etau","Medium"); 

  tauTrigSFhelper_ditau_VVLWP = new SFProvider(dirtauSF+"2016_tauTriggerEff_DeepTau2017v2p1.root","ditau","VVLoose");   
  if(year==2017) tauTrigSFhelper_ditau_VVLWP = new SFProvider(dirtauSF+"2017_tauTriggerEff_DeepTau2017v2p1.root","ditau","VVLoose");   
  if(year==2018) tauTrigSFhelper_ditau_VVLWP = new SFProvider(dirtauSF+"2018_tauTriggerEff_DeepTau2017v2p1.root","ditau","VVLoose");  

  tauTrigSFhelper_ditau_LWP = new SFProvider(dirtauSF+"2016_tauTriggerEff_DeepTau2017v2p1.root","ditau","Loose");   
  if(year==2017) tauTrigSFhelper_ditau_LWP = new SFProvider(dirtauSF+"2017_tauTriggerEff_DeepTau2017v2p1.root","ditau","Loose");   
  if(year==2018) tauTrigSFhelper_ditau_LWP = new SFProvider(dirtauSF+"2018_tauTriggerEff_DeepTau2017v2p1.root","ditau","Loose");      

}

void close_triggerSF_files(){

  file_Mu_SingleMu_hlt_eff->Close();
  file_Ele_SingleElE_hlt_eff->Close();
  file_Mu_MuTau_hlt_eff->Close();
  file_Ele_EleTau_hlt_eff->Close();

  delete file_Mu_SingleMu_hlt_eff;
  delete file_Ele_SingleElE_hlt_eff;
  delete file_Mu_MuTau_hlt_eff;
  delete file_Ele_EleTau_hlt_eff;
  delete tauTrigSFhelper_mutau_VVLWP;
  delete tauTrigSFhelper_mutau_MWP;
  delete tauTrigSFhelper_etau_VVLWP;
  delete tauTrigSFhelper_etau_MWP;
  delete tauTrigSFhelper_ditau_VVLWP;
  delete tauTrigSFhelper_ditau_LWP;

}

float compute_eff_1l1tau(float eff_L, float eff_l, float eff_tau1, bool passHLT1l, bool passHLT1l1tau)
{
  if (passHLT1l and !passHLT1l1tau) { // only the single lepton trigger fires
    return std::max( 1.e-2f, eff_L-std::min(eff_L,eff_l)*eff_tau1 );
  }
  else if (!passHLT1l and passHLT1l1tau) { // only cross trigger fires
    return std::max( 1.e-2f, (eff_l-eff_L)*eff_tau1 );
  }
  else if (passHLT1l and passHLT1l1tau) { // both triggers fire
    return std::min(eff_L, eff_l) * eff_tau1;
  }

  return 0.;
}

float compute_eff_1l2tau(float eff_L, float eff_l, float eff_tau1, float eff_tau2, bool passHLT1l, bool passHLT1l1tau)
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


float get_eff_single_lepton(float pt, float eta, int pdgid, bool isdata)
{
  float eff = 0.;

  if(abs(pdgid)==11){
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

  if(abs(pdgid)==13){
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



float get_eff_lepton_crosstrigger(float pt, float eta, int pdgid, bool isdata)
{
  float eff = 0.;

  if(abs(pdgid)==11){
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
  if(abs(pdgid)==13){
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


float get_triggerSF_1lep2tau( double lep_pt, double lep_eta, double lep_pdg, 
                      double tau1_pt, double tau1_eta, double tau1_phi, double tau1_dm, TString tau1_WP,
                      double tau2_pt, double tau2_eta, double tau2_phi, double tau2_dm, TString tau2_WP,
                      bool passHLT1l, bool passHLT1l1tau, int year, int shift) {

  setup_triggerSF_files(year); 

  // NOMINAL
  
  float eff_L_data = get_eff_single_lepton(lep_pt, lep_eta,lep_pdg, true);
  float eff_L_mc = get_eff_single_lepton(lep_pt, lep_eta,lep_pdg, false);
  float eff_l_data = get_eff_lepton_crosstrigger(lep_pt, lep_eta,lep_pdg, true);
  float eff_l_mc = get_eff_lepton_crosstrigger(lep_pt, lep_eta,lep_pdg, false);

  float eff_t1_data = 1.;
  float eff_t1_mc = 1.;
  float eff_t2_data = 1.;
  float eff_t2_mc = 1.;
  float eff_t1_data_up = 1.;
  float eff_t1_mc_up = 1.;
  float eff_t2_data_up = 1.;
  float eff_t2_mc_up = 1.;
  float eff_t1_data_down = 1.;
  float eff_t1_mc_down = 1.;
  float eff_t2_data_down = 1.;
  float eff_t2_mc_down = 1.;

  if ( tau1_dm == 5 || tau1_dm == 6) tau1_dm = 10; //dummy new DMs
  if ( tau2_dm == 5 || tau2_dm == 6) tau2_dm = 10; //dummy new DMs
  
  if (fabs(lep_pdg)==11) { // ele+tau

    if(tau1_WP=="VVLoose"){

      eff_t1_data = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

    else if(tau1_WP=="Medium"){

      eff_t1_data = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

    if(tau2_WP=="VVLoose"){

      eff_t2_data = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau2_pt,tau2_dm); 
      eff_t2_mc = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau2_pt,tau2_dm);
      eff_t2_data_up = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau2_pt,tau2_dm,+1); 
      eff_t2_mc_up = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau2_pt,tau2_dm,+1);
      eff_t2_data_down = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau2_pt,tau2_dm,-1); 
      eff_t2_mc_down = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau2_pt,tau2_dm,-1);

    }

    else if(tau2_WP=="Medium"){

      eff_t2_data = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau2_pt,tau2_dm); 
      eff_t2_mc = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau2_pt,tau2_dm);
      eff_t2_data_up = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau2_pt,tau2_dm,+1); 
      eff_t2_mc_up = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau2_pt,tau2_dm,+1);
      eff_t2_data_down = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau2_pt,tau2_dm,-1); 
      eff_t2_mc_down = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau2_pt,tau2_dm,-1);

    }

  }

  else {

    if(tau1_WP=="VVLoose"){

      eff_t1_data = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

    else if(tau1_WP=="Medium"){

      eff_t1_data = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

    if(tau2_WP=="VVLoose"){

      eff_t2_data = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau2_pt,tau2_dm); 
      eff_t2_mc = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau2_pt,tau2_dm);
      eff_t2_data_up = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau2_pt,tau2_dm,+1); 
      eff_t2_mc_up = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau2_pt,tau2_dm,+1);
      eff_t2_data_down = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau2_pt,tau2_dm,-1); 
      eff_t2_mc_down = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau2_pt,tau2_dm,-1);

    }

    else if(tau2_WP=="Medium"){

      eff_t2_data = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau2_pt,tau2_dm); 
      eff_t2_mc = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau2_pt,tau2_dm);
      eff_t2_data_up = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau2_pt,tau2_dm,+1); 
      eff_t2_mc_up = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau2_pt,tau2_dm,+1);
      eff_t2_data_down = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau2_pt,tau2_dm,-1); 
      eff_t2_mc_down = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau2_pt,tau2_dm,-1);

    }

  }
 
  float eff_data, eff_mc;
  float eff_data_up, eff_mc_up;
  float eff_data_down, eff_mc_down;

  eff_data = compute_eff_1l2tau(eff_L_data,eff_l_data,eff_t1_data, eff_t2_data, passHLT1l, passHLT1l1tau);
  eff_mc = compute_eff_1l2tau(eff_L_mc, eff_l_mc, eff_t1_mc, eff_t2_mc, passHLT1l, passHLT1l1tau);
  eff_data_up = compute_eff_1l2tau(eff_L_data,eff_l_data,eff_t1_data_up, eff_t2_data_up, passHLT1l, passHLT1l1tau);
  eff_mc_up = compute_eff_1l2tau(eff_L_mc, eff_l_mc, eff_t1_mc_up, eff_t2_mc_up, passHLT1l, passHLT1l1tau);
  eff_data_down = compute_eff_1l2tau(eff_L_data,eff_l_data,eff_t1_data_down, eff_t2_data_down, passHLT1l, passHLT1l1tau);
  eff_mc_down = compute_eff_1l2tau(eff_L_mc, eff_l_mc, eff_t1_mc_down, eff_t2_mc_down, passHLT1l, passHLT1l1tau);

  float sf_nominal = std::min( eff_data/std::max(1.e-6f, eff_mc), 1.e+1f);
  float sf_up = std::min( eff_data_up/std::max(1.e-6f, eff_mc_down), 1.e+1f);
  float sf_down = std::min( eff_data_down/std::max(1.e-6f, eff_mc_up), 1.e+1f);

  close_triggerSF_files();

  float sf = 1.;

  if(shift==0)  sf  = sf_nominal;
  if(shift==+1) sf = sf_up;
  if(shift==-1) sf = sf_down;

  return sf;
 
}


float get_triggerSF_1lep1tau( double lep_pt, double lep_eta, double lep_pdg, 
                      double tau1_pt, double tau1_eta, double tau1_phi, double tau1_dm, TString tau1_WP,
                      bool passHLT1l, bool passHLT1l1tau, int year, int shift) {

  setup_triggerSF_files(year); 

  // NOMINAL
  
  float eff_L_data = get_eff_single_lepton(lep_pt, lep_eta,lep_pdg, true);
  float eff_L_mc = get_eff_single_lepton(lep_pt, lep_eta,lep_pdg, false);
  float eff_l_data = get_eff_lepton_crosstrigger(lep_pt, lep_eta,lep_pdg, true);
  float eff_l_mc = get_eff_lepton_crosstrigger(lep_pt, lep_eta,lep_pdg, false);

  float eff_t1_data = 1.;
  float eff_t1_mc = 1.;
  float eff_t1_data_up = 1.;
  float eff_t1_mc_up = 1.;
  float eff_t1_data_down = 1.;
  float eff_t1_mc_down = 1.;

  if ( tau1_dm == 5 || tau1_dm == 6) tau1_dm = 10; //dummy new DMs
  
  if (fabs(lep_pdg)==11) { // ele+tau

    if(tau1_WP=="VVLoose"){

      eff_t1_data = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_etau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_etau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

    else if(tau1_WP=="Medium"){

      eff_t1_data = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_etau_MWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_etau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

  }

  else {

    if(tau1_WP=="VVLoose"){

      eff_t1_data = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_mutau_VVLWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_mutau_VVLWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }

    else if(tau1_WP=="Medium"){

      eff_t1_data = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau1_pt,tau1_dm); 
      eff_t1_mc = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau1_pt,tau1_dm);
      eff_t1_data_up = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau1_pt,tau1_dm,+1); 
      eff_t1_mc_up = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,+1);
      eff_t1_data_down = tauTrigSFhelper_mutau_MWP->getEfficiencyData(tau1_pt,tau1_dm,-1); 
      eff_t1_mc_down = tauTrigSFhelper_mutau_MWP->getEfficiencyMC(tau1_pt,tau1_dm,-1);

    }
  }
 
  float eff_data, eff_mc;
  float eff_data_up, eff_mc_up;
  float eff_data_down, eff_mc_down;

  eff_data = compute_eff_1l1tau(eff_L_data,eff_l_data,eff_t1_data, passHLT1l, passHLT1l1tau);
  eff_mc = compute_eff_1l1tau(eff_L_mc, eff_l_mc, eff_t1_mc, passHLT1l, passHLT1l1tau);
  eff_data_up = compute_eff_1l1tau(eff_L_data,eff_l_data,eff_t1_data_up, passHLT1l, passHLT1l1tau);
  eff_mc_up = compute_eff_1l1tau(eff_L_mc, eff_l_mc, eff_t1_mc_up, passHLT1l, passHLT1l1tau);
  eff_data_down = compute_eff_1l1tau(eff_L_data,eff_l_data,eff_t1_data_down, passHLT1l, passHLT1l1tau);
  eff_mc_down = compute_eff_1l1tau(eff_L_mc, eff_l_mc, eff_t1_mc_down, passHLT1l, passHLT1l1tau);

  float sf_nominal = std::min( eff_data/std::max(1.e-6f, eff_mc), 1.e+1f);
  float sf_up = std::min( eff_data_up/std::max(1.e-6f, eff_mc_down), 1.e+1f);
  float sf_down = std::min( eff_data_down/std::max(1.e-6f, eff_mc_up), 1.e+1f);

  close_triggerSF_files();

  float sf = 1.;

  if(shift==0)  sf  = sf_nominal;
  if(shift==+1) sf = sf_up;
  if(shift==-1) sf = sf_down;

  return sf;
 
}

float get_triggerSF_ditau ( double tau1_pt, double tau1_eta, double tau1_phi, double tau1_dm, TString tau1_WP,
                           double tau2_pt, double tau2_eta, double tau2_phi, double tau2_dm, TString tau2_WP,
                           int year, int shift) {

  setup_triggerSF_files(year);

  if ( tau1_dm == 5 || tau1_dm == 6) tau1_dm = 10; //dummy new DMs
  if ( tau2_dm == 5 || tau2_dm == 6) tau2_dm = 10; //dummy new DMs

  float sf_nominal_tau1 = 1.;
  float sf_up_tau1 = 1.;
  float sf_down_tau1 = 1.;

  float sf_nominal_tau2 = 1.;
  float sf_up_tau2 = 1.;
  float sf_down_tau2 = 1.;

  if(tau1_WP=="VVLoose"){

    sf_nominal_tau1 = tauTrigSFhelper_ditau_VVLWP->getSF(tau1_pt, tau1_dm);
    sf_up_tau1 = tauTrigSFhelper_ditau_VVLWP->getSF(tau1_pt, tau1_dm, +1);
    sf_down_tau1 = tauTrigSFhelper_ditau_VVLWP->getSF(tau1_pt, tau1_dm, -1);

  }
  else if(tau1_WP=="Loose"){

    sf_nominal_tau1 = tauTrigSFhelper_ditau_LWP->getSF(tau1_pt, tau1_dm);
    sf_up_tau1 = tauTrigSFhelper_ditau_LWP->getSF(tau1_pt, tau1_dm, +1);
    sf_down_tau1 = tauTrigSFhelper_ditau_LWP->getSF(tau1_pt, tau1_dm, -1);

  }

  if(tau2_WP=="VVLoose"){

    sf_nominal_tau2 = tauTrigSFhelper_ditau_VVLWP->getSF(tau2_pt, tau2_dm);
    sf_up_tau2 = tauTrigSFhelper_ditau_VVLWP->getSF(tau2_pt, tau2_dm, +1);
    sf_down_tau2 = tauTrigSFhelper_ditau_VVLWP->getSF(tau2_pt, tau2_dm, -1);

  }
  else if(tau2_WP=="Loose"){

    sf_nominal_tau2 = tauTrigSFhelper_ditau_LWP->getSF(tau2_pt, tau2_dm);
    sf_up_tau2 = tauTrigSFhelper_ditau_LWP->getSF(tau2_pt, tau2_dm, +1);
    sf_down_tau2 = tauTrigSFhelper_ditau_LWP->getSF(tau2_pt, tau2_dm, -1);

  }

  float sf_nominal = sf_nominal_tau1*sf_nominal_tau2;
  float sf_up = sf_up_tau1*sf_up_tau2;
  float sf_down = sf_down_tau1*sf_down_tau2;

  float sf = 1.;

  if(shift==0)  sf = sf_nominal;
  if(shift==+1) sf = sf_up;
  if(shift==-1) sf = sf_down;

  return sf;

}
