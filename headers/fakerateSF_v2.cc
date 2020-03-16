#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

// jet->tau fake rates

TFile *f_fakerate_tau = NULL;

TGraphAsymmErrors* gr_fakerate_tau_deepVSjVLoose_barrel = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjVLoose_endcaps = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjLoose_barrel = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjLoose_endcaps = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjMedium_barrel = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjMedium_endcaps = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjVTight_barrel = NULL;
TGraphAsymmErrors* gr_fakerate_tau_deepVSjVTight_endcaps = NULL;

TF1* f_dataMC_fakerate_tau_deepVSjVLoose_barrel = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVLoose_endcaps = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_barrel = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_endcaps = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_barrel = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_endcaps = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_barrel = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_endcaps = NULL;

TF1* f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Up = NULL;

TF1* f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Down = NULL;

TF1* f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Up = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Up = NULL;

TF1* f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Down = NULL;
TF1* f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Down = NULL;

// jet->lepton fake rates

TFile *f_fakerate_lep = NULL;

TH2F* h_fakerate_mu = NULL;
TH2F* h_fakerate_el = NULL;
TH2F* h_fakerate_mu_data_up = NULL;
TH2F* h_fakerate_el_data_up = NULL;
TH2F* h_fakerate_mu_data_down = NULL;
TH2F* h_fakerate_el_data_down = NULL;
TH2F* h_fakerate_mu_data_pt1 = NULL;
TH2F* h_fakerate_el_data_pt1 = NULL;
TH2F* h_fakerate_mu_data_pt2 = NULL;
TH2F* h_fakerate_el_data_pt2 = NULL;
TH2F* h_fakerate_mu_data_be1 = NULL;
TH2F* h_fakerate_el_data_be1 = NULL;
TH2F* h_fakerate_mu_data_be2 = NULL;
TH2F* h_fakerate_el_data_be2 = NULL;
TH2F* h_fakerate_mu_QCD = NULL;
TH2F* h_fakerate_el_QCD = NULL;
TH2F* h_fakerate_mu_TT = NULL;
TH2F* h_fakerate_el_TT = NULL;


void setup_faketauSF_files(int year){

	  if(year==2016) f_fakerate_tau = new TFile("fake_rate_weights/FR_deeptau_2016_v4.root","read");
	  else if(year==2017) f_fakerate_tau = new TFile("fake_rate_weights/FR_deeptau_2017_v4.root","read");
	  else if(year==2018) f_fakerate_tau = new TFile("fake_rate_weights/FR_deeptau_2018_v4.root","read");

	  gr_fakerate_tau_deepVSjVLoose_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjVLoose_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjLoose_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjLoose_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjMedium_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjMedium_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjVTight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  	gr_fakerate_tau_deepVSjVTight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");

  	f_dataMC_fakerate_tau_deepVSjVLoose_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjVLoose_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjLoose_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjLoose_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjMedium_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjMedium_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjVTight_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  	f_dataMC_fakerate_tau_deepVSjVTight_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");

  	f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  	f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Up");

  	f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  	f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Down");

    f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Up");
    f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Up");

    f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Down");
    f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/deepVSjVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Down");

    return;

}

void setup_fakelepSF_files(int year){

	  if(year==2016) f_fakerate_lep = new TFile("fake_rate_weights/fr_2016.root","read");
	  else if(year==2017) f_fakerate_lep = new TFile("fake_rate_weights/fr_2017.root","read");
	  else if(year==2018) f_fakerate_lep = new TFile("fake_rate_weights/fr_2018.root","read");

	  h_fakerate_mu = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb");
  	h_fakerate_mu->SetDirectory(0);
  	h_fakerate_el = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC");
  	h_fakerate_el->SetDirectory(0);

  	h_fakerate_mu_data_up = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb_up");
  	h_fakerate_mu_data_up->SetDirectory(0);
  	h_fakerate_el_data_up = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC_up");
  	h_fakerate_el_data_up->SetDirectory(0);

  	h_fakerate_mu_data_down = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb_down");
  	h_fakerate_mu_data_down->SetDirectory(0);
  	h_fakerate_el_data_down = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC_down");
  	h_fakerate_el_data_down->SetDirectory(0);

  	h_fakerate_mu_data_pt1 = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb_pt1");
  	h_fakerate_mu_data_pt1->SetDirectory(0);
  	h_fakerate_el_data_pt1 = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC_pt1");
  	h_fakerate_el_data_pt1->SetDirectory(0);

  	h_fakerate_mu_data_pt2 = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb_pt2");
  	h_fakerate_mu_data_pt2->SetDirectory(0);
  	h_fakerate_el_data_pt2 = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC_pt2");
  	h_fakerate_el_data_pt2->SetDirectory(0);

  	h_fakerate_mu_data_be1 = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb_be1");
  	h_fakerate_mu_data_be1->SetDirectory(0);
  	h_fakerate_el_data_be1 = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC_be1");
  	h_fakerate_el_data_be1->SetDirectory(0);

  	h_fakerate_mu_data_be2 = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_data_comb_be2");
  	h_fakerate_mu_data_be2->SetDirectory(0);
  	h_fakerate_el_data_be2 = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_data_comb_NC_be2");
  	h_fakerate_el_data_be2->SetDirectory(0);

  	h_fakerate_mu_QCD = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_QCD");
  	h_fakerate_mu_QCD->SetDirectory(0);
  	h_fakerate_el_QCD = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_QCD");
  	h_fakerate_el_QCD->SetDirectory(0);

  	h_fakerate_mu_TT = (TH2F*)f_fakerate_lep->Get("FR_mva085_mu_TT");
  	h_fakerate_mu_TT->SetDirectory(0);
  	h_fakerate_el_TT = (TH2F*)f_fakerate_lep->Get("FR_mva080_el_TT");
  	h_fakerate_el_TT->SetDirectory(0);

    return;

}

void close_faketauSF_files(){

	  f_fakerate_tau->Close();

	  delete f_fakerate_tau;

    delete gr_fakerate_tau_deepVSjVLoose_barrel;
    delete gr_fakerate_tau_deepVSjVLoose_endcaps;
    delete gr_fakerate_tau_deepVSjLoose_barrel;
    delete gr_fakerate_tau_deepVSjLoose_endcaps;
    delete gr_fakerate_tau_deepVSjMedium_barrel;
    delete gr_fakerate_tau_deepVSjMedium_endcaps;
    delete gr_fakerate_tau_deepVSjVTight_barrel;
    delete gr_fakerate_tau_deepVSjVTight_endcaps;

    delete f_dataMC_fakerate_tau_deepVSjVLoose_barrel;
    delete f_dataMC_fakerate_tau_deepVSjVLoose_endcaps;
    delete f_dataMC_fakerate_tau_deepVSjLoose_barrel;
    delete f_dataMC_fakerate_tau_deepVSjLoose_endcaps;
    delete f_dataMC_fakerate_tau_deepVSjMedium_barrel;
    delete f_dataMC_fakerate_tau_deepVSjMedium_endcaps;
    delete f_dataMC_fakerate_tau_deepVSjVTight_barrel;
    delete f_dataMC_fakerate_tau_deepVSjVTight_endcaps;

    delete f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Up;
    delete f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Up;

    delete f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Down;
    delete f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Down;

    delete f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Up;
    delete f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Up;

    delete f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Down;
    delete f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Down;

    return;

}

void close_fakelepSF_files(){

	  f_fakerate_lep->Close();

	  delete f_fakerate_lep;

	  delete h_fakerate_mu;
	  delete h_fakerate_el;
	  delete h_fakerate_mu_data_up;
	  delete h_fakerate_el_data_up;
	  delete h_fakerate_mu_data_down;
	  delete h_fakerate_el_data_down;
	  delete h_fakerate_mu_data_pt1;
	  delete h_fakerate_el_data_pt1;
	  delete h_fakerate_mu_data_pt2;
	  delete h_fakerate_el_data_pt2;
	  delete h_fakerate_mu_data_be1;
	  delete h_fakerate_el_data_be1;
	  delete h_fakerate_mu_data_be2;
	  delete h_fakerate_el_data_be2;
	  delete h_fakerate_mu_QCD;
	  delete h_fakerate_el_QCD;
	  delete h_fakerate_mu_TT;
	  delete h_fakerate_el_TT;

	  return;

}


float fakerate_from_TGraph(TGraphAsymmErrors* graph, float pt){

  int n = graph->GetN();

  double x, y;
  graph->GetPoint(0,x,y);
  if(pt<x)
    return y;

  graph->GetPoint(n-1,x,y);
  if(pt>x)
    return y;
  
  for(int i=0; i<n;i++){

    graph->GetPoint(i,x,y);
    double err_low_x = graph->GetErrorXlow(i);
    double err_high_x = graph->GetErrorXhigh(i);

    if( (x-err_low_x) < pt && pt < (x+err_high_x) )
      return y;

  }

  return -1.;

}

std::tuple< float, float, float, float, float> get_fakerate_tau_VLoose(int year, float tau_pt, float tau_eta){

	setup_faketauSF_files(year);

	  float fakerate_tau_deepVSjVLoose = 0;
   	float fakerate_tau_deepVSjVLoose_par1Up = 0;
    float fakerate_tau_deepVSjVLoose_par1Down = 0;
    float fakerate_tau_deepVSjVLoose_par2Up = 0;
    float fakerate_tau_deepVSjVLoose_par2Down = 0;

	if(abs(tau_eta)<1.479){

		fakerate_tau_deepVSjVLoose = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_barrel,tau_pt);
		fakerate_tau_deepVSjVLoose *= f_dataMC_fakerate_tau_deepVSjVLoose_barrel->Eval(tau_pt);

		fakerate_tau_deepVSjVLoose_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_barrel,tau_pt);
		fakerate_tau_deepVSjVLoose_par1Up *= f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjVLoose_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_barrel,tau_pt);
    fakerate_tau_deepVSjVLoose_par1Down *= f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjVLoose_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_barrel,tau_pt);
    fakerate_tau_deepVSjVLoose_par2Up *= f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjVLoose_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_barrel,tau_pt);
    fakerate_tau_deepVSjVLoose_par2Down *= f_dataMC_fakerate_tau_deepVSjVLoose_barrel_par2Down->Eval(tau_pt);

	}

	else{

		fakerate_tau_deepVSjVLoose = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_endcaps,tau_pt);
		fakerate_tau_deepVSjVLoose *= f_dataMC_fakerate_tau_deepVSjVLoose_endcaps->Eval(tau_pt);

		fakerate_tau_deepVSjVLoose_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_endcaps,tau_pt);
		fakerate_tau_deepVSjVLoose_par1Up *= f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjVLoose_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_endcaps,tau_pt);
    fakerate_tau_deepVSjVLoose_par1Down *= f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjVLoose_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_endcaps,tau_pt);
    fakerate_tau_deepVSjVLoose_par2Up *= f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjVLoose_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVLoose_endcaps,tau_pt);
    fakerate_tau_deepVSjVLoose_par2Down *= f_dataMC_fakerate_tau_deepVSjVLoose_endcaps_par2Down->Eval(tau_pt);

	}

	close_faketauSF_files();

	return std::make_tuple(fakerate_tau_deepVSjVLoose, fakerate_tau_deepVSjVLoose_par1Up, fakerate_tau_deepVSjVLoose_par1Down, fakerate_tau_deepVSjVLoose_par2Up, fakerate_tau_deepVSjVLoose_par2Down);

}

std::tuple< float, float, float, float, float> get_fakerate_tau_Loose(int year, float tau_pt, float tau_eta){

	setup_faketauSF_files(year);

	float fakerate_tau_deepVSjLoose = 0;
  float fakerate_tau_deepVSjLoose_par1Up = 0;
  float fakerate_tau_deepVSjLoose_par1Down = 0;
  float fakerate_tau_deepVSjLoose_par2Up = 0;
  float fakerate_tau_deepVSjLoose_par2Down = 0;

	if(abs(tau_eta)<1.479){

		fakerate_tau_deepVSjLoose = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_barrel,tau_pt);
		fakerate_tau_deepVSjLoose *= f_dataMC_fakerate_tau_deepVSjLoose_barrel->Eval(tau_pt);

		fakerate_tau_deepVSjLoose_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_barrel,tau_pt);
		fakerate_tau_deepVSjLoose_par1Up *= f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjLoose_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_barrel,tau_pt);
    fakerate_tau_deepVSjLoose_par1Down *= f_dataMC_fakerate_tau_deepVSjLoose_barrel_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjLoose_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_barrel,tau_pt);
    fakerate_tau_deepVSjLoose_par2Up *= f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjLoose_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_barrel,tau_pt);
    fakerate_tau_deepVSjLoose_par2Down *= f_dataMC_fakerate_tau_deepVSjLoose_barrel_par2Down->Eval(tau_pt);

	}

	else{

		fakerate_tau_deepVSjLoose = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_endcaps,tau_pt);
		fakerate_tau_deepVSjLoose *= f_dataMC_fakerate_tau_deepVSjLoose_endcaps->Eval(tau_pt);

		fakerate_tau_deepVSjLoose_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_endcaps,tau_pt);
		fakerate_tau_deepVSjLoose_par1Up *= f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjLoose_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_endcaps,tau_pt);
    fakerate_tau_deepVSjLoose_par1Down *= f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjLoose_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_endcaps,tau_pt);
    fakerate_tau_deepVSjLoose_par2Up *= f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjLoose_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjLoose_endcaps,tau_pt);
    fakerate_tau_deepVSjLoose_par2Down *= f_dataMC_fakerate_tau_deepVSjLoose_endcaps_par2Down->Eval(tau_pt);

	}

	close_faketauSF_files();

	return std::make_tuple(fakerate_tau_deepVSjLoose, fakerate_tau_deepVSjLoose_par1Up, fakerate_tau_deepVSjLoose_par1Down, fakerate_tau_deepVSjLoose_par2Up, fakerate_tau_deepVSjLoose_par2Down);

}

std::tuple< float, float, float, float, float> get_fakerate_tau_Medium(int year, float tau_pt, float tau_eta){

	setup_faketauSF_files(year);

	float fakerate_tau_deepVSjMedium = 0;
   	float fakerate_tau_deepVSjMedium_par1Up = 0;
    float fakerate_tau_deepVSjMedium_par1Down = 0;
    float fakerate_tau_deepVSjMedium_par2Up = 0;
    float fakerate_tau_deepVSjMedium_par2Down = 0;

	if(abs(tau_eta)<1.479){

		fakerate_tau_deepVSjMedium = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_barrel,tau_pt);
		fakerate_tau_deepVSjMedium *= f_dataMC_fakerate_tau_deepVSjMedium_barrel->Eval(tau_pt);

		fakerate_tau_deepVSjMedium_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_barrel,tau_pt);
		fakerate_tau_deepVSjMedium_par1Up *= f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjMedium_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_barrel,tau_pt);
    fakerate_tau_deepVSjMedium_par1Down *= f_dataMC_fakerate_tau_deepVSjMedium_barrel_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjMedium_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_barrel,tau_pt);
    fakerate_tau_deepVSjMedium_par2Up *= f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjMedium_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_barrel,tau_pt);
    fakerate_tau_deepVSjMedium_par2Down *= f_dataMC_fakerate_tau_deepVSjMedium_barrel_par2Down->Eval(tau_pt);

	}

	else{

		fakerate_tau_deepVSjMedium = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_endcaps,tau_pt);
		fakerate_tau_deepVSjMedium *= f_dataMC_fakerate_tau_deepVSjMedium_endcaps->Eval(tau_pt);

		fakerate_tau_deepVSjMedium_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_endcaps,tau_pt);
		fakerate_tau_deepVSjMedium_par1Up *= f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjMedium_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_endcaps,tau_pt);
    fakerate_tau_deepVSjMedium_par1Down *= f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjMedium_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_endcaps,tau_pt);
    fakerate_tau_deepVSjMedium_par2Up *= f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjMedium_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjMedium_endcaps,tau_pt);
    fakerate_tau_deepVSjMedium_par2Down *= f_dataMC_fakerate_tau_deepVSjMedium_endcaps_par2Down->Eval(tau_pt);

	}

	close_faketauSF_files();

	return std::make_tuple(fakerate_tau_deepVSjMedium, fakerate_tau_deepVSjMedium_par1Up, fakerate_tau_deepVSjMedium_par1Down, fakerate_tau_deepVSjMedium_par2Up, fakerate_tau_deepVSjMedium_par2Down);

}

std::tuple< float, float, float, float, float> get_fakerate_tau_VTight(int year, float tau_pt, float tau_eta){

	setup_faketauSF_files(year);

	float fakerate_tau_deepVSjVTight = 0;
  float fakerate_tau_deepVSjVTight_par1Up = 0;
  float fakerate_tau_deepVSjVTight_par1Down = 0;
  float fakerate_tau_deepVSjVTight_par2Up = 0;
  float fakerate_tau_deepVSjVTight_par2Down = 0;

	if(abs(tau_eta)<1.479){

		fakerate_tau_deepVSjVTight = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_barrel,tau_pt);
		fakerate_tau_deepVSjVTight *= f_dataMC_fakerate_tau_deepVSjVTight_barrel->Eval(tau_pt);

		fakerate_tau_deepVSjVTight_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_barrel,tau_pt);
		fakerate_tau_deepVSjVTight_par1Up *= f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjVTight_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_barrel,tau_pt);
    fakerate_tau_deepVSjVTight_par1Down *= f_dataMC_fakerate_tau_deepVSjVTight_barrel_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjVTight_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_barrel,tau_pt);
    fakerate_tau_deepVSjVTight_par2Up *= f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjVTight_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_barrel,tau_pt);
    fakerate_tau_deepVSjVTight_par2Down *= f_dataMC_fakerate_tau_deepVSjVTight_barrel_par2Down->Eval(tau_pt);

	}

	else{

		fakerate_tau_deepVSjVTight = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_endcaps,tau_pt);
		fakerate_tau_deepVSjVTight *= f_dataMC_fakerate_tau_deepVSjVTight_endcaps->Eval(tau_pt);

		fakerate_tau_deepVSjVTight_par1Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_endcaps,tau_pt);
		fakerate_tau_deepVSjVTight_par1Up *= f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Up->Eval(tau_pt);

		fakerate_tau_deepVSjVTight_par1Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_endcaps,tau_pt);
    fakerate_tau_deepVSjVTight_par1Down *= f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par1Down->Eval(tau_pt);

    fakerate_tau_deepVSjVTight_par2Up = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_endcaps,tau_pt);
    fakerate_tau_deepVSjVTight_par2Up *= f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Up->Eval(tau_pt);

    fakerate_tau_deepVSjVTight_par2Down = fakerate_from_TGraph(gr_fakerate_tau_deepVSjVTight_endcaps,tau_pt);
    fakerate_tau_deepVSjVTight_par2Down *= f_dataMC_fakerate_tau_deepVSjVTight_endcaps_par2Down->Eval(tau_pt);

	}

	close_faketauSF_files();

	return std::make_tuple(fakerate_tau_deepVSjVTight, fakerate_tau_deepVSjVTight_par1Up, fakerate_tau_deepVSjVTight_par1Down, fakerate_tau_deepVSjVTight_par2Up, fakerate_tau_deepVSjVTight_par2Down);

}


std::tuple< float, float, float, float, float, float, float, float, float > get_fakerate_muon(int year, float mu_pt, float mu_eta){

	  setup_fakelepSF_files(year);

	  float fakerate_mu = 0;
	  float fakerate_mu_up = 0;
	  float fakerate_mu_down = 0;
	  float fakerate_mu_pt1 = 0;
	  float fakerate_mu_pt2 = 0;
	  float fakerate_mu_be1 = 0;
	  float fakerate_mu_be2 = 0;
	  float fakerate_mu_QCD = 0;
	  float fakerate_mu_TT = 0;

	  int bin_FR = h_fakerate_mu->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    float FR = h_fakerate_mu->GetBinContent(bin_FR);
    fakerate_mu = FR;

    bin_FR = h_fakerate_mu_data_up->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_data_up->GetBinContent(bin_FR);
    fakerate_mu_up = FR;

    bin_FR = h_fakerate_mu_data_down->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_data_down->GetBinContent(bin_FR);
    fakerate_mu_down = FR;

    bin_FR = h_fakerate_mu_data_pt1->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_data_pt1->GetBinContent(bin_FR);
    fakerate_mu_pt1 = FR;

    bin_FR = h_fakerate_mu_data_pt2->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_data_pt2->GetBinContent(bin_FR);
    fakerate_mu_pt2 = FR;

    bin_FR = h_fakerate_mu_data_be1->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_data_be1->GetBinContent(bin_FR);
    fakerate_mu_be1 = FR;

    bin_FR = h_fakerate_mu_data_be2->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_data_be2->GetBinContent(bin_FR);
    fakerate_mu_be2 = FR;

    bin_FR = h_fakerate_mu_QCD->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_QCD->GetBinContent(bin_FR);
    fakerate_mu_QCD = FR;

    bin_FR = h_fakerate_mu_TT->FindBin(min(mu_pt,float(99.)), abs(mu_eta));
    FR = h_fakerate_mu_TT->GetBinContent(bin_FR);
    fakerate_mu_TT = FR;

    close_fakelepSF_files();

    return std::make_tuple(fakerate_mu,fakerate_mu_up,fakerate_mu_down,fakerate_mu_pt1,fakerate_mu_pt2,fakerate_mu_be1,fakerate_mu_be2,fakerate_mu_QCD,fakerate_mu_TT);

}


std::tuple< float, float, float, float, float, float, float, float, float > get_fakerate_ele(int year, float ele_pt, float ele_eta){

    setup_fakelepSF_files(year);

    float fakerate_ele = 0;
    float fakerate_ele_up = 0;
    float fakerate_ele_down = 0;
    float fakerate_ele_pt1 = 0;
    float fakerate_ele_pt2 = 0;
    float fakerate_ele_be1 = 0;
    float fakerate_ele_be2 = 0;
    float fakerate_ele_QCD = 0;
    float fakerate_ele_TT = 0;

    int bin_FR = h_fakerate_el->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    float FR = h_fakerate_el->GetBinContent(bin_FR);
    fakerate_ele = FR;

    bin_FR = h_fakerate_el_data_up->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_data_up->GetBinContent(bin_FR);
    fakerate_ele_up = FR;

    bin_FR = h_fakerate_el_data_down->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_data_down->GetBinContent(bin_FR);
    fakerate_ele_down = FR;

    bin_FR = h_fakerate_el_data_pt1->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_data_pt1->GetBinContent(bin_FR);
    fakerate_ele_pt1 = FR;

    bin_FR = h_fakerate_el_data_pt2->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_data_pt2->GetBinContent(bin_FR);
    fakerate_ele_pt2 = FR;

    bin_FR = h_fakerate_el_data_be1->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_data_be1->GetBinContent(bin_FR);
    fakerate_ele_be1 = FR;

    bin_FR = h_fakerate_el_data_be2->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_data_be2->GetBinContent(bin_FR);
    fakerate_ele_be2 = FR;

    bin_FR = h_fakerate_el_QCD->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_QCD->GetBinContent(bin_FR);
    fakerate_ele_QCD = FR;

    bin_FR = h_fakerate_el_TT->FindBin(min(ele_pt,float(99.)), abs(ele_eta));
    FR = h_fakerate_el_TT->GetBinContent(bin_FR);
    fakerate_ele_TT = FR;

    close_fakelepSF_files();

    return std::make_tuple(fakerate_ele,fakerate_ele_up,fakerate_ele_down,fakerate_ele_pt1,fakerate_ele_pt2,fakerate_ele_be1,fakerate_ele_be2,fakerate_ele_QCD,fakerate_ele_TT);

}

