#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"


TFile *_file_recoToLoose_leptonSF_mu1 = NULL;
TFile *_file_recoToLoose_leptonSF_mu2 = NULL;
TFile *_file_recoToLoose_leptonSF_mu3 = NULL;
TFile *_file_recoToLoose_leptonSF_mu4 = NULL;
TFile *_file_recoToLoose_leptonSF_mu5 = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu1 = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu2 = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu5 = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu3_eta = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu3_pt = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu4_eta = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu4_pt = NULL;

TFile *_file_recoToLoose_leptonSF_el = NULL;
TH2F *_histo_recoToLoose_leptonSF_el1 = NULL;
TH2F *_histo_recoToLoose_leptonSF_el2 = NULL;
TH2F *_histo_recoToLoose_leptonSF_el3 = NULL;
TFile *_file_recoToLoose_leptonSF_gsf1 = NULL;
TFile *_file_recoToLoose_leptonSF_gsf2 = NULL;
TH2F *_histo_recoToLoose_leptonSF_gsf1 = NULL;
TH2F *_histo_recoToLoose_leptonSF_gsf2 = NULL;

float _get_recoToLoose_leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var){

  // nlep is ignored for the loose selection

  if (!_histo_recoToLoose_leptonSF_mu1) {
    _file_recoToLoose_leptonSF_mu1 = new TFile("lepSF/mu_scaleFactors_ptGt30.root","read");
    _file_recoToLoose_leptonSF_mu2 = new TFile("lepSF/mu_scaleFactors_ptLt30.root","read");
    _file_recoToLoose_leptonSF_mu3 = new TFile("lepSF/mu_scaleFactors_trkEff_ptGt10.root","read");
    _file_recoToLoose_leptonSF_mu4 = new TFile("lepSF/mu_scaleFactors_trkEff_ptLt10.root","read");
    _file_recoToLoose_leptonSF_mu5 = new TFile("lepSF/mu_scaleFactors_trkVtxCut_and_isoEff.root","read");
    _histo_recoToLoose_leptonSF_mu1 = (TH2F*)(_file_recoToLoose_leptonSF_mu1->Get("NUM_LooseID_DEN_genTracks_pt_abseta"));
    _histo_recoToLoose_leptonSF_mu2 = (TH2F*)(_file_recoToLoose_leptonSF_mu2->Get("NUM_LooseID_DEN_genTracks_pt_abseta"));
    _histo_recoToLoose_leptonSF_mu3_eta = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu3->Get("ratio_eff_eta3_dr030e030_corr"));
    _histo_recoToLoose_leptonSF_mu4_eta = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu4->Get("ratio_eff_eta3_tk0_dr030e030_corr"));
    _histo_recoToLoose_leptonSF_mu3_pt = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu3->Get("ratio_eff_pt_dr030e030_corr"));
    _histo_recoToLoose_leptonSF_mu4_pt = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu4->Get("ratio_eff_pt_tk0_dr030e030_corr"));
    _histo_recoToLoose_leptonSF_mu5 = (TH2F*)(_file_recoToLoose_leptonSF_mu5->Get("NUM_ttHLoo_DEN_LooseID"));
  }
  if (!_histo_recoToLoose_leptonSF_el1) {
    _file_recoToLoose_leptonSF_el = new TFile("lepSF/el_reco_loose_SF.root","read");
    _histo_recoToLoose_leptonSF_el1 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("EGamma_SF2D"));
//    _histo_recoToLoose_leptonSF_el2 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToMini4"));
//    _histo_recoToLoose_leptonSF_el3 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToConvVetoIHit1"));
  }
  if (!_histo_recoToLoose_leptonSF_gsf1) {
    _file_recoToLoose_leptonSF_gsf1 = new TFile("lepSF/el_scaleFactors_gsf_ptGt20.root","read");
    _file_recoToLoose_leptonSF_gsf2 = new TFile("lepSF/el_scaleFactors_gsf_ptLt20.root","read");
    _histo_recoToLoose_leptonSF_gsf1 = (TH2F*)(_file_recoToLoose_leptonSF_gsf1->Get("EGamma_SF2D"));
    _histo_recoToLoose_leptonSF_gsf2 = (TH2F*)(_file_recoToLoose_leptonSF_gsf2->Get("EGamma_SF2D"));
  }

  if (abs(pdgid)==13){

    TH2F *hist1 = (pt>30) ? _histo_recoToLoose_leptonSF_mu1 : _histo_recoToLoose_leptonSF_mu2;
    int ptbin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(pt)));
    int etabin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(fabs(eta))));
    float out = hist1->GetBinContent(ptbin1,etabin1);

    TGraphAsymmErrors *hist2 = (pt>10) ? _histo_recoToLoose_leptonSF_mu3_eta : _histo_recoToLoose_leptonSF_mu4_eta;
    float eta1 = std::max(float(hist2->GetXaxis()->GetXmin()+1e-5), std::min(float(hist2->GetXaxis()->GetXmax()-1e-5), eta));
    out *= hist2->Eval(eta1);
 
    TGraphAsymmErrors *hist3 = (pt>10) ? _histo_recoToLoose_leptonSF_mu3_pt : _histo_recoToLoose_leptonSF_mu4_pt;
    float pt1 = std::max(float(hist3->GetXaxis()->GetXmin()+1e-5), std::min(float(hist3->GetXaxis()->GetXmax()-1e-5), pt));
    out *= hist3->Eval(pt1);

    TH2F *hist4 = _histo_recoToLoose_leptonSF_mu5;
    int ptbin4  = std::max(1, std::min(hist4->GetNbinsX(), hist4->GetXaxis()->FindBin(pt)));
    int etabin4 = std::max(1, std::min(hist4->GetNbinsY(), hist4->GetYaxis()->FindBin(fabs(eta))));
    out *= hist4->GetBinContent(ptbin4,etabin4);
    
    return out;

  }

  if (abs(pdgid)==11){
    
    TH2F *hist = (pt>20) ? _histo_recoToLoose_leptonSF_gsf1 : _histo_recoToLoose_leptonSF_gsf2;
    int etabin1 = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(eta))); // careful, different convention
    int ptbin1  = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(pt)));
    float out = hist->GetBinContent(etabin1,ptbin1);
 
    TH2F *hist2 =  _histo_recoToLoose_leptonSF_el1;
    int etabin2 = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(eta))); // careful, different convention
    int ptbin2  = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(pt)));
    out *= hist2->GetBinContent(etabin2,ptbin2);
    
    return out;
  }

  assert(0);
  return -999;

}

TFile *_file_looseToTight_leptonSF_mu_2lss = NULL;
TH2F *_histo_looseToTight_leptonSF_mu_2lss = NULL;
TFile *_file_looseToTight_leptonSF_el_2lss = NULL;
TH2F *_histo_looseToTight_leptonSF_el_2lss = NULL;
TFile *_file_looseToTight_leptonSF_mu_3l = NULL;
TH2F *_histo_looseToTight_leptonSF_mu_3l = NULL;
TFile *_file_looseToTight_leptonSF_el_3l = NULL;
TH2F *_histo_looseToTight_leptonSF_el_3l = NULL;

float _get_looseToTight_leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var){

  // var is ignored in all cases (systematics handled in systsEnv.txt)

  if (!_histo_looseToTight_leptonSF_mu_2lss) {
    _file_looseToTight_leptonSF_mu_2lss = new TFile("lepSF/lepMVAEffSF_m_2lss.root","read");
    _histo_looseToTight_leptonSF_mu_2lss = (TH2F*)(_file_looseToTight_leptonSF_mu_2lss->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_el_2lss) {
    _file_looseToTight_leptonSF_el_2lss = new TFile("lepSF/lepMVAEffSF_e_2lss.root","read");
    _histo_looseToTight_leptonSF_el_2lss = (TH2F*)(_file_looseToTight_leptonSF_el_2lss->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_mu_3l) {
    _file_looseToTight_leptonSF_mu_3l = new TFile("lepSF/lepMVAEffSF_m_3l.root","read");
    _histo_looseToTight_leptonSF_mu_3l = (TH2F*)(_file_looseToTight_leptonSF_mu_3l->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_el_3l) {
    _file_looseToTight_leptonSF_el_3l = new TFile("lepSF/lepMVAEffSF_e_3l.root","read");
    _histo_looseToTight_leptonSF_el_3l = (TH2F*)(_file_looseToTight_leptonSF_el_3l->Get("sf"));
  }

  TH2F *hist = 0;
  if (abs(pdgid)==13) hist = (nlep>2) ? _histo_looseToTight_leptonSF_mu_3l : _histo_looseToTight_leptonSF_mu_2lss;
  else if (abs(pdgid)==11) hist = (nlep>2) ? _histo_looseToTight_leptonSF_el_3l : _histo_looseToTight_leptonSF_el_2lss;
  assert(hist);
  int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
  int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
  return hist->GetBinContent(ptbin,etabin);

}


float leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var=0){

  float recoToLoose = _get_recoToLoose_leptonSF_ttH(pdgid,pt,eta,nlep,var);
  float looseToTight = _get_looseToTight_leptonSF_ttH(pdgid,pt,eta,nlep,var);
  float res = recoToLoose*looseToTight;
  assert (res>0);
  return res;

}


/*
//TFile *file_triggerSF_ttH = NULL;
//TH2Poly* t2poly_triggerSF_ttH_mm = NULL;
//TH2Poly* t2poly_triggerSF_ttH_ee = NULL;
//TH2Poly* t2poly_triggerSF_ttH_em = NULL;
//TH2Poly* t2poly_triggerSF_ttH_3l = NULL;

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
TFile *file_triggerSF_ttH_e = NULL;
TFile *file_triggerSF_ttH_m = NULL;
TH2F* h_triggerSF_ttH_e = NULL;
TH2F* h_triggerSF_ttH_m = NULL;

float triggerSF_ttH_1l(int pdgid, float pt, float eta, float var=0){

  if (!(file_triggerSF_ttH_e && file_triggerSF_ttH_m)) {
    file_triggerSF_ttH_e = new TFile("lepSF/ElTriggerPerformance_Sep27.root");
    h_triggerSF_ttH_e = (TH2F*)(file_triggerSF_ttH_e->Get("electrontrig_sf_eta_pt"));
    file_triggerSF_ttH_m = new TFile("lepSF/MuonTriggerPerformance_Sep06.root");
    h_triggerSF_ttH_m = (TH2F*)(file_triggerSF_ttH_m->Get("muontrig_sf_abseta_pt"));

    if (!(h_triggerSF_ttH_e && h_triggerSF_ttH_m)) {
      std::cout << "Impossible to load trigger scale factors!" << std::endl;
      file_triggerSF_ttH_e->ls();
      file_triggerSF_ttH_e = NULL;
      file_triggerSF_ttH_m->ls();
      file_triggerSF_ttH_m = NULL;
    }
  }

  TH2F* hist = NULL;
  if (abs(pdgid)==13) hist = h_triggerSF_ttH_m;
  else if (abs(pdgid)==11) hist = h_triggerSF_ttH_e;

  float searchPt = TMath::Min(pt,float(499.0));
  float searchEta = eta;
  if(abs(pdgid)==13) searchEta = fabs(eta);
  int bin = hist->FindBin(searchEta, searchPt);
  float nomval = hist->GetBinContent(bin);
  float error = hist->GetBinError(bin);
  float SF = nomval + var*error;
  return SF;

}*/
