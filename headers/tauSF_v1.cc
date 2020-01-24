#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"

// Tau ID and ES SFs

#include "/home/llr/cms/mperez/ttH/Legacy/macros/TauPOG/TauIDSFs/src/TauIDSFTool.cc"
#include "/home/llr/cms/mperez/ttH/Legacy/macros/TauPOG/TauIDSFs/interface/TauIDSFTool.h"

TauIDSFTool* tauIDSFHelper_DeepTauVsJet_VVLoose = NULL;
TauIDSFTool* tauIDSFHelper_DeepTauVsJet_VLoose = NULL;
TauIDSFTool* tauIDSFHelper_DeepTauVsJet_Loose = NULL;
TauIDSFTool* tauIDSFHelper_DeepTauVsJet_Medium = NULL;

//TauIDSFTool* tauIDSFHelper_DeepTauVsEle_VVVLoose = NULL; // no SF
//TauIDSFTool* tauIDSFHelper_DeepTauVsMu_VLoose = NULL;

void setup_tauSF_files(int year){

	tauIDSFHelper_DeepTauVsJet_VVLoose = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSjet","VVLoose",true);
  	if(year==2017) tauIDSFHelper_DeepTauVsJet_VVLoose = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSjet","VVLoose",true);
  	if(year==2018) tauIDSFHelper_DeepTauVsJet_VVLoose = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSjet","VVLoose",true);

  	tauIDSFHelper_DeepTauVsJet_VLoose = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSjet","VLoose",true);
  	if(year==2017) tauIDSFHelper_DeepTauVsJet_VLoose = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSjet","VLoose",true);
  	if(year==2018) tauIDSFHelper_DeepTauVsJet_VLoose = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSjet","VLoose",true);

  	tauIDSFHelper_DeepTauVsJet_Loose = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSjet","Loose",true);
  	if(year==2017) tauIDSFHelper_DeepTauVsJet_Loose = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSjet","Loose",true);
  	if(year==2018) tauIDSFHelper_DeepTauVsJet_Loose = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSjet","Loose",true);

	tauIDSFHelper_DeepTauVsJet_Medium = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSjet","Medium",true);
  	if(year==2017) tauIDSFHelper_DeepTauVsJet_Medium = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSjet","Medium",true);
  	if(year==2018) tauIDSFHelper_DeepTauVsJet_Medium = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSjet","Medium",true);

  	//tauIDSFHelper_DeepTauVsEle_VVVLoose = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSe","VVVLoose");
  	//if(year==2017) tauIDSFHelper_DeepTauVsEle_VVVLoose = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSe","VVVLoose");
  	//if(year==2018) tauIDSFHelper_DeepTauVsEle_VVVLoose = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSe","VVVLoose");

  	//tauIDSFHelper_DeepTauVsMu_VLoose = new TauIDSFTool("2016Legacy","DeepTau2017v2p1VSmu","VLoose");
  	//if(year==2017) tauIDSFHelper_DeepTauVsMu_VLoose = new TauIDSFTool("2017ReReco","DeepTau2017v2p1VSmu","VLoose");
  	//if(year==2018) tauIDSFHelper_DeepTauVsMu_VLoose = new TauIDSFTool("2018ReReco","DeepTau2017v2p1VSmu","VLoose");

  	return;

}


void close_tauSF_files(){

	delete tauIDSFHelper_DeepTauVsJet_VVLoose;
	delete tauIDSFHelper_DeepTauVsJet_VLoose;
	delete tauIDSFHelper_DeepTauVsJet_Loose;
	delete tauIDSFHelper_DeepTauVsJet_Medium;

	//delete tauIDSFHelper_DeepTauVsEle_VVVLoose;
	//delete tauIDSFHelper_DeepTauVsMu_VLoose;

	return;

}

float get_tauSF(int year, float tau_pt, float tau_eta, float tau_dm, TString tau_wpVsJets, int shift = 0){

	setup_tauSF_files(year);

	float sf_nominal = 1.;
	float sf_up = 1.;
	float sf_down = 1.;

	if(tau_wpVsJets=="VVLoose") {

		sf_nominal 	= tauIDSFHelper_DeepTauVsJet_VVLoose->getSFvsDM(tau_pt,tau_dm,5);
		sf_up 		= tauIDSFHelper_DeepTauVsJet_VVLoose->getSFvsDM(tau_pt,tau_dm,5,"Up");
		sf_down 	= tauIDSFHelper_DeepTauVsJet_VVLoose->getSFvsDM(tau_pt,tau_dm,5,"Down");

	}

	else if(tau_wpVsJets=="VLoose") {

		sf_nominal 	= tauIDSFHelper_DeepTauVsJet_VLoose->getSFvsDM(tau_pt,tau_dm,5);
		sf_up 		= tauIDSFHelper_DeepTauVsJet_VLoose->getSFvsDM(tau_pt,tau_dm,5,"Up");
		sf_down 	= tauIDSFHelper_DeepTauVsJet_VLoose->getSFvsDM(tau_pt,tau_dm,5,"Down");

	}

	else if(tau_wpVsJets=="Loose") {

		sf_nominal 	= tauIDSFHelper_DeepTauVsJet_Loose->getSFvsDM(tau_pt,tau_dm,5);
		sf_up 		= tauIDSFHelper_DeepTauVsJet_Loose->getSFvsDM(tau_pt,tau_dm,5,"Up");
		sf_down 	= tauIDSFHelper_DeepTauVsJet_Loose->getSFvsDM(tau_pt,tau_dm,5,"Down");

	}

	else if(tau_wpVsJets=="Medium") {

		sf_nominal 	= tauIDSFHelper_DeepTauVsJet_Medium->getSFvsDM(tau_pt,tau_dm,5);
		sf_up 		= tauIDSFHelper_DeepTauVsJet_Medium->getSFvsDM(tau_pt,tau_dm,5,"Up");
		sf_down 	= tauIDSFHelper_DeepTauVsJet_Medium->getSFvsDM(tau_pt,tau_dm,5,"Down");

	}

	//float sf_nominal_mu = tauIDSFHelper_DeepTauVsMu_VLoose->getSFvsEta(tau_eta);
	//sf_nominal *= sf_nominal_mu;

	close_tauSF_files();

	float sf = 1.;

  	if(shift==0)  sf = sf_nominal;
  	if(shift==+1) sf = sf_up;
  	if(shift==-1) sf = sf_down;

  	return sf;

}