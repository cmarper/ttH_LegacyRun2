#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"
#include <algorithm>
#include <iostream>

using namespace std;

TFile *f_fliprate = NULL;

TH2D *h_fliprate = NULL;

void setup_flipSF_files(int year){

	if(year==2016) f_fliprate = new TFile("charge_flip_weights/ElectronChargeMisIdRates_era2016_2020Jan15.root","read");
	else if(year==2017) f_fliprate = new TFile("charge_flip_weights/ElectronChargeMisIdRates_era2017_2020Jan15.root","read");
	else if(year==2018) f_fliprate = new TFile("charge_flip_weights/ElectronChargeMisIdRates_era2018_2020Jan15.root","read");

	h_fliprate = (TH2D*)f_fliprate->Get("eChargeMisIdRates");
	h_fliprate->SetDirectory(0);

	return;

}

void close_flipSF_files(){

	f_fliprate->Close();

	delete f_fliprate;
	delete h_fliprate;

}

float get_fliprate(int year, float ele_pt, float ele_eta){

	setup_flipSF_files(year);

	if(ele_pt<15) ele_pt = 16;

	int bin_QF = h_fliprate->FindBin( ele_pt, abs(ele_eta) );
    float fliprate = h_fliprate->GetBinContent(bin_QF);

	close_flipSF_files();

	return fliprate;

}

