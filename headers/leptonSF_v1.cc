#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

// RECO->LOOSE

// Reco electrons -> EGamma 
TFile *_file_RecoToLoose1_ele_pt0to20_2016 = NULL;
TFile *_file_RecoToLoose1_ele_pt20_2016 = NULL;
TFile *_file_RecoToLoose1_ele_pt0to20_2017 = NULL;
TFile *_file_RecoToLoose1_ele_pt20_2017 = NULL;
TFile *_file_RecoToLoose1_ele_2018 = NULL;

TH2F *_histo_RecoToLoose1_ele_pt0to20_2016 = NULL;
TH2F *_histo_RecoToLoose1_ele_pt20_2016 = NULL;
TH2F *_histo_RecoToLoose1_ele_pt0to20_2017 = NULL;
TH2F *_histo_RecoToLoose1_ele_pt20_2017 = NULL;
TH2F *_histo_RecoToLoose1_ele_2018 = NULL;

// Loose electrons -> Barbara
TFile *_file_RecoToLoose2_ele_2016 = NULL;
TFile *_file_RecoToLoose2_ele_2017 = NULL;
TFile *_file_RecoToLoose2_ele_2018 = NULL;

TH2F *_histo_RecoToLoose2_ele_2016 = NULL;
TH2F *_histo_RecoToLoose2_ele_2017 = NULL;
TH2F *_histo_RecoToLoose2_ele_2018 = NULL;

// Loose to loose ttH electrons -> Barbara
TFile *_file_LooseToLooseTTH_ele_2016 = NULL;
TFile *_file_LooseToLooseTTH_ele_2017 = NULL;
TFile *_file_LooseToLooseTTH_ele_2018 = NULL;

TH2F *_histo_LooseToLooseTTH_ele_2016 = NULL;
TH2F *_histo_LooseToLooseTTH_ele_2017 = NULL;
TH2F *_histo_LooseToLooseTTH_ele_2018 = NULL;

// Loose muons
TFile *_file_RecoToLoose_mu_2016 = NULL;
TFile *_file_RecoToLoose_mu_2017 = NULL;
TFile *_file_RecoToLoose_mu_2018 = NULL;

TH2F *_histo_RecoToLoose_mu_2016 = NULL;
TH2F *_histo_RecoToLoose_mu_2017 = NULL;
TH2F *_histo_RecoToLoose_mu_2018 = NULL;

float get_RecoToLoose_leptonSF(int year,int pdgid, float pt, float eta, int nlep, float var){

  if (abs(pdgid)==11){

    if(year==2016){

      _file_RecoToLoose1_ele_pt0to20_2016 = new TFile("lepSF/el_scaleFactors_gsf_ptLt20.root","read");
      _file_RecoToLoose1_ele_pt20_2016 = new TFile("lepSF/el_scaleFactors_gsf_ptGt20.root","read");
      _file_RecoToLoose2_ele_2016 = new TFile("lepSF/TnP_loose_ele_2016.root","read");
      _file_LooseToLooseTTH_ele_2016 = new TFile("lepSF/TnP_loosettH_ele_2016.root","read");

      _histo_RecoToLoose1_ele_pt0to20_2016 = (TH2F*)(_file_RecoToLoose1_ele_pt0to20_2016->Get("EGamma_SF2D"));
      _histo_RecoToLoose1_ele_pt20_2016 = (TH2F*)(_file_RecoToLoose1_ele_pt20_2016->Get("EGamma_SF2D"));
      _histo_RecoToLoose2_ele_2016 = (TH2F*)(_file_RecoToLoose2_ele_2016->Get("EGamma_SF2D"));
      _histo_LooseToLooseTTH_ele_2016 = (TH2F*)(_file_LooseToLooseTTH_ele_2016->Get("EGamma_SF2D"));

      TH2F *hist1 = (pt>20) ? _histo_RecoToLoose1_ele_pt20_2016 : _histo_RecoToLoose1_ele_pt0to20_2016;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(eta)));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      TH2F *hist2 = _histo_RecoToLoose2_ele_2016;
      int etabin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(fabs(eta))));
      int ptbin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(pt)));
      out *= hist2->GetBinContent(etabin2,ptbin2);

      TH2F *hist3 = _histo_LooseToLooseTTH_ele_2016;
      int etabin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(fabs(eta))));
      int ptbin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(pt)));
      out *= hist3->GetBinContent(etabin3,ptbin3);

      return out;

    }

    else if(year==2017){

      _file_RecoToLoose1_ele_pt0to20_2017 = new TFile("lepSF/el_scaleFactors_gsf_ptLt20.root","read");
      _file_RecoToLoose1_ele_pt20_2017 = new TFile("lepSF/el_scaleFactors_gsf_ptGt20.root","read");
      _file_RecoToLoose2_ele_2017 = new TFile("lepSF/TnP_loose_ele_2017.root","read");
      _file_LooseToLooseTTH_ele_2017 = new TFile("lepSF/TnP_loosettH_ele_2017.root","read");

      _histo_RecoToLoose1_ele_pt0to20_2017 = (TH2F*)(_file_RecoToLoose1_ele_pt0to20_2017->Get("EGamma_SF2D"));
      _histo_RecoToLoose1_ele_pt20_2017 = (TH2F*)(_file_RecoToLoose1_ele_pt20_2017->Get("EGamma_SF2D"));
      _histo_RecoToLoose2_ele_2017 = (TH2F*)(_file_RecoToLoose2_ele_2017->Get("EGamma_SF2D"));
      _histo_LooseToLooseTTH_ele_2017 = (TH2F*)(_file_LooseToLooseTTH_ele_2017->Get("EGamma_SF2D")); 

      TH2F *hist1 = (pt>20) ? _histo_RecoToLoose1_ele_pt20_2017 : _histo_RecoToLoose1_ele_pt0to20_2017;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(eta)));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      TH2F *hist2 = _histo_RecoToLoose2_ele_2017;
      int etabin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(fabs(eta))));
      int ptbin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(pt)));
      out *= hist2->GetBinContent(etabin2,ptbin2);

      TH2F *hist3 = _histo_LooseToLooseTTH_ele_2017;
      int etabin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(fabs(eta))));
      int ptbin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(pt)));
      out *= hist3->GetBinContent(etabin3,ptbin3);

      return out;

    }

    else if(year==2018){

      _file_RecoToLoose1_ele_2018 = new TFile("lepSF/el_scaleFactors_gsf.root","read");
      _file_RecoToLoose2_ele_2018 = new TFile("lepSF/TnP_loose_ele_2018.root","read");
      _file_LooseToLooseTTH_ele_2018 = new TFile("lepSF/TnP_loosettH_ele_2018.root","read");

      _histo_RecoToLoose1_ele_2018 = (TH2F*)(_file_RecoToLoose1_ele_2018->Get("EGamma_SF2D"));
      _histo_RecoToLoose2_ele_2018 = (TH2F*)(_file_RecoToLoose2_ele_2018->Get("EGamma_SF2D"));
      _histo_LooseToLooseTTH_ele_2018 = (TH2F*)(_file_LooseToLooseTTH_ele_2018->Get("EGamma_SF2D"));

      TH2F *hist1 = _histo_RecoToLoose1_ele_2018;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(eta)));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      TH2F *hist2 = _histo_RecoToLoose2_ele_2018;
      int etabin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(fabs(eta))));
      int ptbin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(pt)));
      out *= hist2->GetBinContent(etabin2,ptbin2);

      TH2F *hist3 = _histo_LooseToLooseTTH_ele_2018;
      int etabin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(fabs(eta))));
      int ptbin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(pt)));
      out *= hist3->GetBinContent(etabin3,ptbin3);

      return out;

    }

  }

  if (abs(pdgid)==13){

    if(year==2016){

      _file_RecoToLoose_mu_2016 = new TFile("lepSF/TnP_loose_muon_2016.root","read");
      _histo_RecoToLoose_mu_2016 = (TH2F*)(_file_RecoToLoose_mu_2016->Get("EGamma_SF2D"));

      TH2F *hist1 = _histo_RecoToLoose_mu_2016;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

    else if(year==2017){

      _file_RecoToLoose_mu_2017 = new TFile("lepSF/TnP_loose_muon_2017.root","read");
      _histo_RecoToLoose_mu_2017 = (TH2F*)(_file_RecoToLoose_mu_2017->Get("EGamma_SF2D"));

      TH2F *hist1 = _histo_RecoToLoose_mu_2017;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

    else if(year==2018){

      _file_RecoToLoose_mu_2018 = new TFile("lepSF/TnP_loose_muon_2018.root","read");
      _histo_RecoToLoose_mu_2018 = (TH2F*)(_file_RecoToLoose_mu_2018->Get("EGamma_SF2D"));

      TH2F *hist1 = _histo_RecoToLoose_mu_2018;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

  }

  assert(0);
  return -999;

}

// LOOSE->TIGHT

// Loose ttH to tight electrons -> Barbara
TFile *_file_LooseTTHToTight_ele_tightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_ele_tightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_ele_tightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_ele_tightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_ele_tightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_ele_tightcharge_2018 = NULL;

TFile *_file_LooseTTHToTight_ele_notightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_ele_notightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_ele_notightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_ele_notightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_ele_notightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_ele_notightcharge_2018 = NULL;

// Loose ttH to tight muons -> Barbara
TFile *_file_LooseTTHToTight_mu_tightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_mu_tightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_mu_tightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_mu_tightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_mu_tightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_mu_tightcharge_2018 = NULL;

TFile *_file_LooseTTHToTight_mu_notightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_mu_notightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_mu_notightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_mu_notightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_mu_notightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_mu_notightcharge_2018 = NULL;


float get_LooseToTight_leptonSF(int year, int pdgid, float pt, float eta, int nlep, float var){

  if (abs(pdgid)==11){

    if(year==2016){

      _file_LooseTTHToTight_ele_tightcharge_2016 = new TFile("lepSF/ele_loosetotight_tightcharge_2016.root","read");
      _file_LooseTTHToTight_ele_notightcharge_2016 = new TFile("lepSF/ele_loosetotight_notightcharge_2016.root","read");

      _histo_LooseTTHToTight_ele_tightcharge_2016 = (TH2F*)(_file_LooseTTHToTight_ele_tightcharge_2016->Get("EGamma_SF2D"));
      _histo_LooseTTHToTight_ele_notightcharge_2016 = (TH2F*)(_file_LooseTTHToTight_ele_notightcharge_2016->Get("EGamma_SF2D"));

      TH2F *hist1 = (nlep==2) ? _histo_LooseTTHToTight_ele_tightcharge_2016 : _histo_LooseTTHToTight_ele_notightcharge_2016;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

    else if(year==2017){

      _file_LooseTTHToTight_ele_tightcharge_2017 = new TFile("lepSF/ele_loosetotight_tightcharge_2017.root","read");
      _file_LooseTTHToTight_ele_notightcharge_2017 = new TFile("lepSF/ele_loosetotight_notightcharge_2017.root","read");

      _histo_LooseTTHToTight_ele_tightcharge_2017 = (TH2F*)(_file_LooseTTHToTight_ele_tightcharge_2017->Get("EGamma_SF2D"));
      _histo_LooseTTHToTight_ele_notightcharge_2017 = (TH2F*)(_file_LooseTTHToTight_ele_notightcharge_2017->Get("EGamma_SF2D"));

      TH2F *hist1 = (nlep==2) ? _histo_LooseTTHToTight_ele_tightcharge_2017 : _histo_LooseTTHToTight_ele_notightcharge_2017;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

    else if(year==2018){

      _file_LooseTTHToTight_ele_tightcharge_2018 = new TFile("lepSF/ele_loosetotight_tightcharge_2018.root","read");
      _file_LooseTTHToTight_ele_notightcharge_2018 = new TFile("lepSF/ele_loosetotight_notightcharge_2018.root","read");

      _histo_LooseTTHToTight_ele_tightcharge_2018 = (TH2F*)(_file_LooseTTHToTight_ele_tightcharge_2018->Get("EGamma_SF2D"));
      _histo_LooseTTHToTight_ele_notightcharge_2018 = (TH2F*)(_file_LooseTTHToTight_ele_notightcharge_2018->Get("EGamma_SF2D"));

      TH2F *hist1 = (nlep==2) ? _histo_LooseTTHToTight_ele_tightcharge_2018 : _histo_LooseTTHToTight_ele_notightcharge_2018;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

  }

  if (abs(pdgid)==13){

    if(year==2016){

      _file_LooseTTHToTight_mu_tightcharge_2016 = new TFile("lepSF/mu_loosetotight_tightcharge_2016.root","read");
      _file_LooseTTHToTight_mu_notightcharge_2016 = new TFile("lepSF/mu_loosetotight_notightcharge_2016.root","read");

      _histo_LooseTTHToTight_mu_tightcharge_2016 = (TH2F*)(_file_LooseTTHToTight_mu_tightcharge_2016->Get("EGamma_SF2D"));
      _histo_LooseTTHToTight_mu_notightcharge_2016 = (TH2F*)(_file_LooseTTHToTight_mu_notightcharge_2016->Get("EGamma_SF2D"));

      TH2F *hist1 = (nlep==2) ? _histo_LooseTTHToTight_mu_tightcharge_2016 : _histo_LooseTTHToTight_mu_notightcharge_2016;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

    else if(year==2017){

      _file_LooseTTHToTight_mu_tightcharge_2017 = new TFile("lepSF/mu_loosetotight_tightcharge_2017.root","read");
      _file_LooseTTHToTight_mu_notightcharge_2017 = new TFile("lepSF/mu_loosetotight_notightcharge_2017.root","read");

      _histo_LooseTTHToTight_mu_tightcharge_2017 = (TH2F*)(_file_LooseTTHToTight_mu_tightcharge_2017->Get("EGamma_SF2D"));
      _histo_LooseTTHToTight_mu_notightcharge_2017 = (TH2F*)(_file_LooseTTHToTight_mu_notightcharge_2017->Get("EGamma_SF2D"));

      TH2F *hist1 = (nlep==2) ? _histo_LooseTTHToTight_mu_tightcharge_2017 : _histo_LooseTTHToTight_mu_notightcharge_2017;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

    else if(year==2018){

      _file_LooseTTHToTight_mu_tightcharge_2018 = new TFile("lepSF/mu_loosetotight_tightcharge_2018.root","read");
      _file_LooseTTHToTight_mu_notightcharge_2018 = new TFile("lepSF/mu_loosetotight_notightcharge_2018.root","read");

      _histo_LooseTTHToTight_mu_tightcharge_2018 = (TH2F*)(_file_LooseTTHToTight_mu_tightcharge_2018->Get("EGamma_SF2D"));
      _histo_LooseTTHToTight_mu_notightcharge_2018 = (TH2F*)(_file_LooseTTHToTight_mu_notightcharge_2018->Get("EGamma_SF2D"));

      TH2F *hist1 = (nlep==2) ? _histo_LooseTTHToTight_mu_tightcharge_2018 : _histo_LooseTTHToTight_mu_notightcharge_2018;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);

      return out;

    }

  }

  assert(0);
  return -999; 

}


float get_leptonSF(int year,int pdgid, float pt, float eta, int nlep, float var=0){

  float SF_RecoToLoose = get_RecoToLoose_leptonSF(year,pdgid,pt,eta,nlep,var); 
  float SF_LooseToTight = get_LooseToTight_leptonSF(year,pdgid,pt,eta,nlep,var);
  float res = SF_RecoToLoose*SF_LooseToTight;
  assert (res>0);
  return res;

}

