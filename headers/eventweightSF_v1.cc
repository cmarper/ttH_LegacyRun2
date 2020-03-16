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

void setup_faketauSF_files(int year){

	if(year==2016) f_fakerate_tau = new TFile("fake_rate_weights/FR_deeptau_2016_v3.root","read");
	else if(year==2017) f_fakerate_tau = new TFile("fake_rate_weights/FR_deeptau_2017_v3.root","read");
	else if(year==2018) f_fakerate_tau = new TFile("fake_rate_weights/FR_deeptau_2018_v3.root","read");

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
	else if(year==2017) f_fakerate_lep = new TFile("fake_rate_weights/fr_2016.root","read");
	else if(year==2018) f_fakerate_lep = new TFile("fake_rate_weights/fr_2016.root","read");

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


