#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

// RECO->LOOSE

// ELECTRONS 

// 1. Reco -> Loose1 POG (EGamma POG) 
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

// 2. Reco -> Loose2 POG (Barbara)
TFile *_file_RecoToLoose2_ele_2016 = NULL;
TFile *_file_RecoToLoose2_ele_2017 = NULL;
TFile *_file_RecoToLoose2_ele_2018 = NULL;

TH2F *_histo_RecoToLoose2_ele_2016 = NULL;
TH2F *_histo_RecoToLoose2_ele_2017 = NULL;
TH2F *_histo_RecoToLoose2_ele_2018 = NULL;

// 3. Loose POG -> Loose ttH (Barbara)
TFile *_file_LooseToLooseTTH_ele_2016 = NULL;
TFile *_file_LooseToLooseTTH_ele_2017 = NULL;
TFile *_file_LooseToLooseTTH_ele_2018 = NULL;

TH2F *_histo_LooseToLooseTTH_ele_2016 = NULL;
TH2F *_histo_LooseToLooseTTH_ele_2017 = NULL;
TH2F *_histo_LooseToLooseTTH_ele_2018 = NULL;

// MUONS 

// 1. Reco -> Loose
TFile *_file_RecoToLoose_mu_2016 = NULL;
TFile *_file_RecoToLoose_mu_2017 = NULL;
TFile *_file_RecoToLoose_mu_2018 = NULL;

TH2F *_histo_RecoToLoose_mu_2016 = NULL;
TH2F *_histo_RecoToLoose_mu_2017 = NULL;
TH2F *_histo_RecoToLoose_mu_2018 = NULL;

float get_RecoToLoose_leptonSF(int year,int pdgid, float pt, float eta, int nlep, int var){

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
      float err1 = hist1->GetBinError(etabin1,ptbin1);

      TH2F *hist2 = _histo_RecoToLoose2_ele_2016;
      int etabin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(fabs(eta))));
      int ptbin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(pt)));
      out *= hist2->GetBinContent(etabin2,ptbin2);
      float err2 = hist2->GetBinError(etabin1,ptbin1);

      TH2F *hist3 = _histo_LooseToLooseTTH_ele_2016;
      int etabin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(fabs(eta))));
      int ptbin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(pt)));
      out *= hist3->GetBinContent(etabin3,ptbin3);
      float err3 = hist3->GetBinError(etabin1,ptbin1);

      float err_max1 = std::max(err1,err2);
      float error = std::max(err_max1,err3);

      _file_RecoToLoose1_ele_pt0to20_2016->Close();
      _file_RecoToLoose1_ele_pt20_2016->Close();
      _file_RecoToLoose2_ele_2016->Close();
      _file_LooseToLooseTTH_ele_2016->Close();

      return out + var*error;

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
      float err1 = hist1->GetBinError(etabin1,ptbin1);

      TH2F *hist2 = _histo_RecoToLoose2_ele_2017;
      int etabin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(fabs(eta))));
      int ptbin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(pt)));
      out *= hist2->GetBinContent(etabin2,ptbin2);
      float err2 = hist2->GetBinError(etabin1,ptbin1);

      TH2F *hist3 = _histo_LooseToLooseTTH_ele_2017;
      int etabin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(fabs(eta))));
      int ptbin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(pt)));
      out *= hist3->GetBinContent(etabin3,ptbin3);
      float err3 = hist3->GetBinError(etabin1,ptbin1);

      float err_max1 = std::max(err1,err2);
      float error = std::max(err_max1,err3);

      _file_RecoToLoose1_ele_pt0to20_2017->Close();
      _file_RecoToLoose1_ele_pt20_2017->Close();
      _file_RecoToLoose2_ele_2017->Close();
      _file_LooseToLooseTTH_ele_2017->Close();

      return out + var*error;

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
      float err1 = hist1->GetBinError(etabin1,ptbin1);

      TH2F *hist2 = _histo_RecoToLoose2_ele_2018;
      int etabin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(fabs(eta))));
      int ptbin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(pt)));
      out *= hist2->GetBinContent(etabin2,ptbin2);
      float err2 = hist2->GetBinError(etabin1,ptbin1);

      TH2F *hist3 = _histo_LooseToLooseTTH_ele_2018;
      int etabin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(fabs(eta))));
      int ptbin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(pt)));
      out *= hist3->GetBinContent(etabin3,ptbin3);
      float err3 = hist3->GetBinError(etabin1,ptbin1);

      float err_max1 = std::max(err1,err2);
      float error = std::max(err_max1,err3);

      _file_RecoToLoose1_ele_2018->Close();
      _file_RecoToLoose2_ele_2018->Close();
      _file_LooseToLooseTTH_ele_2018->Close();

      return out + var*error;

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
      float error = hist1->GetBinError(etabin1,ptbin1);

      _file_RecoToLoose_mu_2016->Close();

      return out + var*error;

    }

    else if(year==2017){

      _file_RecoToLoose_mu_2017 = new TFile("lepSF/TnP_loose_muon_2017.root","read");

      _histo_RecoToLoose_mu_2017 = (TH2F*)(_file_RecoToLoose_mu_2017->Get("EGamma_SF2D"));

      TH2F *hist1 = _histo_RecoToLoose_mu_2017;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);
      float error = hist1->GetBinError(etabin1,ptbin1);

      _file_RecoToLoose_mu_2017->Close();

      return out + var*error;

    }

    else if(year==2018){

      _file_RecoToLoose_mu_2018 = new TFile("lepSF/TnP_loose_muon_2018.root","read");

      _histo_RecoToLoose_mu_2018 = (TH2F*)(_file_RecoToLoose_mu_2018->Get("EGamma_SF2D"));

      TH2F *hist1 = _histo_RecoToLoose_mu_2018;
      int etabin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(fabs(eta))));
      int ptbin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(pt)));
      float out = hist1->GetBinContent(etabin1,ptbin1);
      float error = hist1->GetBinError(etabin1,ptbin1);

      _file_RecoToLoose_mu_2018->Close();

      return out + var*error;

    }

  }

  assert(0);
  return -999;

}

// LOOSE->TIGHT

// ELECTRONS

// Loose ttH -> tight with tight charge (Barbara) nlep==2

TFile *_file_LooseTTHToTight_ele_tightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_ele_tightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_ele_tightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_ele_tightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_ele_tightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_ele_tightcharge_2018 = NULL;

// Loose ttH -> tight without tight charge (Barbara) nlep==3

TFile *_file_LooseTTHToTight_ele_notightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_ele_notightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_ele_notightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_ele_notightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_ele_notightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_ele_notightcharge_2018 = NULL;

// MUONS

// Loose ttH -> tight with tight charge (Barbara) nlep==2

TFile *_file_LooseTTHToTight_mu_tightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_mu_tightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_mu_tightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_mu_tightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_mu_tightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_mu_tightcharge_2018 = NULL;

// Loose ttH -> tight without tight charge (Barbara) nlep==3

TFile *_file_LooseTTHToTight_mu_notightcharge_2016 = NULL;
TFile *_file_LooseTTHToTight_mu_notightcharge_2017 = NULL;
TFile *_file_LooseTTHToTight_mu_notightcharge_2018 = NULL;

TH2F *_histo_LooseTTHToTight_mu_notightcharge_2016 = NULL;
TH2F *_histo_LooseTTHToTight_mu_notightcharge_2017 = NULL;
TH2F *_histo_LooseTTHToTight_mu_notightcharge_2018 = NULL;

// Errors

TFile *_file_LooseTTHToTight_ele_errorpT_2016 = NULL;
TFile *_file_LooseTTHToTight_ele_errorpT_2017 = NULL;
TFile *_file_LooseTTHToTight_ele_errorpT_2018 = NULL;

TFile *_file_LooseTTHToTight_mu_errorpT_2016 = NULL;
TFile *_file_LooseTTHToTight_mu_errorpT_2017 = NULL;
TFile *_file_LooseTTHToTight_mu_errorpT_2018 = NULL;

TFile *_file_LooseTTHToTight_ele_errorEta_2016 = NULL;
TFile *_file_LooseTTHToTight_ele_errorEta_2017 = NULL;
TFile *_file_LooseTTHToTight_ele_errorEta_2018 = NULL;

TFile *_file_LooseTTHToTight_mu_errorEta_2016 = NULL;
TFile *_file_LooseTTHToTight_mu_errorEta_2017 = NULL;
TFile *_file_LooseTTHToTight_mu_errorEta_2018 = NULL;

TH1F *_histo_LooseTTHToTight_ele_errorpT_2016 = NULL;
TH1F *_histo_LooseTTHToTight_ele_errorpT_2017 = NULL;
TH1F *_histo_LooseTTHToTight_ele_errorpT_2018 = NULL;

TH1F *_histo_LooseTTHToTight_mu_errorpT_2016 = NULL;
TH1F *_histo_LooseTTHToTight_mu_errorpT_2017 = NULL;
TH1F *_histo_LooseTTHToTight_mu_errorpT_2018 = NULL;

TH1F *_histo_LooseTTHToTight_ele_errorEta_2016 = NULL;
TH1F *_histo_LooseTTHToTight_ele_errorEta_2017 = NULL;
TH1F *_histo_LooseTTHToTight_ele_errorEta_2018 = NULL;

TH1F *_histo_LooseTTHToTight_mu_errorEta_2016 = NULL;
TH1F *_histo_LooseTTHToTight_mu_errorEta_2017 = NULL;
TH1F *_histo_LooseTTHToTight_mu_errorEta_2018 = NULL;


float get_LooseToTight_leptonSF(int year, int pdgid, float pt, float eta, int nlep, int var){

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

      _file_LooseTTHToTight_ele_tightcharge_2016->Close();
      _file_LooseTTHToTight_ele_notightcharge_2016->Close();

      _file_LooseTTHToTight_ele_errorpT_2016 = new TFile("lepSF/ele_loosetotight_pt_2016.root","read");
      _file_LooseTTHToTight_ele_errorEta_2016 = new TFile("lepSF/ele_loosetotight_eta_2016.root","read");

      _histo_LooseTTHToTight_ele_errorpT_2016 = (TH1F*)(_file_LooseTTHToTight_ele_errorpT_2016->Get("histo_eff_data"));
      _histo_LooseTTHToTight_ele_errorEta_2016 = (TH1F*)(_file_LooseTTHToTight_ele_errorEta_2016->Get("histo_eff_data"));

      TH1F *histErrPt = _histo_LooseTTHToTight_ele_errorpT_2016;
      int ptbin = std::max(1, histErrPt->GetXaxis()->FindBin(pt));
      float errpt = fabs(1.0 - (histErrPt->GetBinContent(ptbin)));

      TH1F *histErrEta = _histo_LooseTTHToTight_ele_errorEta_2016;
      int etabin = std::max(1, histErrEta->GetXaxis()->FindBin(fabs(eta)));
      float erreta = fabs(1.0 - (histErrEta->GetBinContent(etabin)));

      float error = std::max(errpt,erreta);

      _file_LooseTTHToTight_ele_errorpT_2016->Close();
      _file_LooseTTHToTight_ele_errorEta_2016->Close();

      return out + var*error;

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

      _file_LooseTTHToTight_ele_tightcharge_2017->Close();
      _file_LooseTTHToTight_ele_notightcharge_2017->Close();

      _file_LooseTTHToTight_ele_errorpT_2017 = new TFile("lepSF/ele_loosetotight_pt_2017.root","read");
      _file_LooseTTHToTight_ele_errorEta_2017 = new TFile("lepSF/ele_loosetotight_eta_2017.root","read");

      _histo_LooseTTHToTight_ele_errorpT_2017 = (TH1F*)(_file_LooseTTHToTight_ele_errorpT_2017->Get("histo_eff_data"));
      _histo_LooseTTHToTight_ele_errorEta_2017 = (TH1F*)(_file_LooseTTHToTight_ele_errorEta_2017->Get("histo_eff_data"));

      TH1F *histErrPt = _histo_LooseTTHToTight_ele_errorpT_2017;
      int ptbin = std::max(1, histErrPt->GetXaxis()->FindBin(pt));
      float errpt = fabs(1.0 - (histErrPt->GetBinContent(ptbin)));

      TH1F *histErrEta = _histo_LooseTTHToTight_ele_errorEta_2017;
      int etabin = std::max(1, histErrEta->GetXaxis()->FindBin(fabs(eta)));
      float erreta = fabs(1.0 - (histErrEta->GetBinContent(etabin)));

      float error = std::max(errpt,erreta);

      _file_LooseTTHToTight_ele_errorpT_2017->Close();
      _file_LooseTTHToTight_ele_errorEta_2017->Close();

      return out + var*error;

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

      _file_LooseTTHToTight_ele_tightcharge_2018->Close();
      _file_LooseTTHToTight_ele_notightcharge_2018->Close();

      _file_LooseTTHToTight_ele_errorpT_2018 = new TFile("lepSF/ele_loosetotight_pt_2018.root","read");
      _file_LooseTTHToTight_ele_errorEta_2018 = new TFile("lepSF/ele_loosetotight_eta_2018.root","read");

      _histo_LooseTTHToTight_ele_errorpT_2018 = (TH1F*)(_file_LooseTTHToTight_ele_errorpT_2018->Get("histo_eff_data"));
      _histo_LooseTTHToTight_ele_errorEta_2018 = (TH1F*)(_file_LooseTTHToTight_ele_errorEta_2018->Get("histo_eff_data"));

      TH1F *histErrPt = _histo_LooseTTHToTight_ele_errorpT_2018;
      int ptbin = std::max(1, histErrPt->GetXaxis()->FindBin(pt));
      float errpt = fabs(1.0 - (histErrPt->GetBinContent(ptbin)));

      TH1F *histErrEta = _histo_LooseTTHToTight_ele_errorEta_2018;
      int etabin = std::max(1, histErrEta->GetXaxis()->FindBin(fabs(eta)));
      float erreta = fabs(1.0 - (histErrEta->GetBinContent(etabin)));

      float error = std::max(errpt,erreta);

      _file_LooseTTHToTight_ele_errorpT_2018->Close();
      _file_LooseTTHToTight_ele_errorEta_2018->Close();

      return out + var*error;

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

      _file_LooseTTHToTight_mu_tightcharge_2016->Close();
      _file_LooseTTHToTight_mu_notightcharge_2016->Close();

      _file_LooseTTHToTight_mu_errorpT_2016 = new TFile("lepSF/mu_loosetotight_pt_2016.root","read");
      _file_LooseTTHToTight_mu_errorEta_2016 = new TFile("lepSF/mu_loosetotight_eta_2016.root","read");

      _histo_LooseTTHToTight_mu_errorpT_2016 = (TH1F*)(_file_LooseTTHToTight_mu_errorpT_2016->Get("histo_eff_data"));
      _histo_LooseTTHToTight_mu_errorEta_2016 = (TH1F*)(_file_LooseTTHToTight_mu_errorEta_2016->Get("histo_eff_data"));

      TH1F *histErrPt = _histo_LooseTTHToTight_mu_errorpT_2016;
      int ptbin = std::max(1, histErrPt->GetXaxis()->FindBin(pt));
      float errpt = fabs(1.0 - (histErrPt->GetBinContent(ptbin)));

      TH1F *histErrEta = _histo_LooseTTHToTight_mu_errorEta_2016;
      int etabin = std::max(1, histErrEta->GetXaxis()->FindBin(fabs(eta)));
      float erreta = fabs(1.0 - (histErrEta->GetBinContent(etabin)));

      float error = std::max(errpt,erreta);

      _file_LooseTTHToTight_mu_errorpT_2016->Close();
      _file_LooseTTHToTight_mu_errorEta_2016->Close();

      return out + var*error;

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

      _file_LooseTTHToTight_mu_tightcharge_2017->Close();
      _file_LooseTTHToTight_mu_notightcharge_2017->Close();

      _file_LooseTTHToTight_mu_errorpT_2017 = new TFile("lepSF/mu_loosetotight_pt_2017.root","read");
      _file_LooseTTHToTight_mu_errorEta_2017 = new TFile("lepSF/mu_loosetotight_eta_2017.root","read");

      _histo_LooseTTHToTight_mu_errorpT_2017 = (TH1F*)(_file_LooseTTHToTight_mu_errorpT_2017->Get("histo_eff_data"));
      _histo_LooseTTHToTight_mu_errorEta_2017 = (TH1F*)(_file_LooseTTHToTight_mu_errorEta_2017->Get("histo_eff_data"));

      TH1F *histErrPt = _histo_LooseTTHToTight_mu_errorpT_2017;
      int ptbin = std::max(1, histErrPt->GetXaxis()->FindBin(pt));
      float errpt = fabs(1.0 - (histErrPt->GetBinContent(ptbin)));

      TH1F *histErrEta = _histo_LooseTTHToTight_mu_errorEta_2017;
      int etabin = std::max(1, histErrEta->GetXaxis()->FindBin(fabs(eta)));
      float erreta = fabs(1.0 - (histErrEta->GetBinContent(etabin)));

      float error = std::max(errpt,erreta);

      _file_LooseTTHToTight_mu_errorpT_2017->Close();
      _file_LooseTTHToTight_mu_errorEta_2017->Close();

      return out + var*error;

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

      _file_LooseTTHToTight_mu_tightcharge_2018->Close();
      _file_LooseTTHToTight_mu_notightcharge_2018->Close();

      _file_LooseTTHToTight_mu_errorpT_2018 = new TFile("lepSF/mu_loosetotight_pt_2018.root","read");
      _file_LooseTTHToTight_mu_errorEta_2018 = new TFile("lepSF/mu_loosetotight_eta_2018.root","read");

      _histo_LooseTTHToTight_mu_errorpT_2018 = (TH1F*)(_file_LooseTTHToTight_mu_errorpT_2018->Get("histo_eff_data"));
      _histo_LooseTTHToTight_mu_errorEta_2018 = (TH1F*)(_file_LooseTTHToTight_mu_errorEta_2018->Get("histo_eff_data"));

      TH1F *histErrPt = _histo_LooseTTHToTight_mu_errorpT_2018;
      int ptbin = std::max(1, histErrPt->GetXaxis()->FindBin(pt));
      float errpt = fabs(1.0 - (histErrPt->GetBinContent(ptbin)));

      TH1F *histErrEta = _histo_LooseTTHToTight_mu_errorEta_2018;
      int etabin = std::max(1, histErrEta->GetXaxis()->FindBin(fabs(eta)));
      float erreta = fabs(1.0 - (histErrEta->GetBinContent(etabin)));

      float error = std::max(errpt,erreta);

      _file_LooseTTHToTight_mu_errorpT_2018->Close();
      _file_LooseTTHToTight_mu_errorEta_2018->Close();

      return out + var*error;

    }

  }

  assert(0);
  return -999; 

}


float get_leptonSF(int year,int pdgid, float pt, float eta, int nlep, float var=0){

  float SF_RecoToLoose = get_RecoToLoose_leptonSF(year,pdgid,pt,eta,nlep,var); 
  float SF_LooseToTight = get_LooseToTight_leptonSF(year,pdgid,pt,eta,nlep,var);
  
  float sf = SF_RecoToLoose*SF_LooseToTight;

  return sf;

}

