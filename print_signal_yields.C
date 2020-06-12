#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

using namespace std;

void print_events(TString category, bool isTLL){
	
	TString dirin = "/Users/cmartinp/Desktop/datacards/";

	float yield_ttHhww = 0.;
	float yield_ttHhzz = 0.;
	float yield_ttHhtt = 0.;
	float yield_tH = 0.;


	vector<TString> years;

	years.clear();

	years.push_back("2016");
	years.push_back("2017");
	years.push_back("2018");

	for (unsigned int iyear=0; iyear<years.size(); iyear++){

		TFile* filein = new TFile(dirin+"ttH_"+category+"_"+years.at(iyear)+".root");

		//cout<<"YEAR: "<<years.at(iyear)<<endl;

		if(isTLL){

			TH1F* h_ttHhww = (TH1F*)filein->Get("ttH_"+category+"/ttH_hww");
			if(h_ttHhww) yield_ttHhww = yield_ttHhww+h_ttHhww->Integral();

			TH1F* h_ttHhzz = (TH1F*)filein->Get("ttH_"+category+"/ttH_hzz");
			if(h_ttHhzz) yield_ttHhzz = yield_ttHhzz+h_ttHhzz->Integral();

			TH1F* h_ttHhtt = (TH1F*)filein->Get("ttH_"+category+"/ttH_htt");
			if(h_ttHhtt) yield_ttHhtt = yield_ttHhtt+h_ttHhtt->Integral();

			TH1F* h_tHqhww = (TH1F*)filein->Get("ttH_"+category+"/tHq_hww");
			if(h_tHqhww) yield_tH = yield_tH+h_tHqhww->Integral();

			TH1F* h_tHqhzz = (TH1F*)filein->Get("ttH_"+category+"/tHq_hzz");
			if(h_tHqhzz) yield_tH = yield_tH+h_tHqhzz->Integral();

			TH1F* h_tHqhtt = (TH1F*)filein->Get("ttH_"+category+"/tHq_htt");
			if(h_tHqhtt) yield_tH = yield_tH+h_tHqhtt->Integral();

			TH1F* h_tHWhww = (TH1F*)filein->Get("ttH_"+category+"/tHW_hww");
			if(h_tHWhww) yield_tH = yield_tH+h_tHWhww->Integral();

			TH1F* h_tHWhzz = (TH1F*)filein->Get("ttH_"+category+"/tHW_hzz");
			if(h_tHWhzz) yield_tH = yield_tH+h_tHWhzz->Integral();

			TH1F* h_tHWhtt = (TH1F*)filein->Get("ttH_"+category+"/tHW_htt");
			if(h_tHWhtt) yield_tH = yield_tH+h_tHWhtt->Integral();

		}

		else if(!isTLL){

			TH1F* h_ttHhww = (TH1F*)filein->Get("x_ttH_hww");
			if(h_ttHhww) yield_ttHhww = yield_ttHhww+h_ttHhww->Integral();

			TH1F* h_ttHhzz = (TH1F*)filein->Get("x_ttH_hzz");
			if(h_ttHhzz) yield_ttHhzz = yield_ttHhzz+h_ttHhzz->Integral();

			TH1F* h_ttHhtt = (TH1F*)filein->Get("x_ttH_htt");
			if(h_ttHhtt) yield_ttHhtt = yield_ttHhtt+h_ttHhtt->Integral();

			TH1F* h_tHqhww = (TH1F*)filein->Get("x_tHq_hww");
			if(h_tHqhww) yield_tH = yield_tH+h_tHqhww->Integral();

			TH1F* h_tHqhzz = (TH1F*)filein->Get("x_tHq_hzz");
			if(h_tHqhzz) yield_tH = yield_tH+h_tHqhzz->Integral();

			TH1F* h_tHqhtt = (TH1F*)filein->Get("x_tHq_htt");
			if(h_tHqhtt) yield_tH = yield_tH+h_tHqhtt->Integral();

			TH1F* h_tHWhww = (TH1F*)filein->Get("x_tHW_hww");
			if(h_tHWhww) yield_tH = yield_tH+h_tHWhww->Integral();

			TH1F* h_tHWhzz = (TH1F*)filein->Get("x_tHW_hzz");
			if(h_tHWhzz) yield_tH = yield_tH+h_tHWhzz->Integral();

			TH1F* h_tHWhtt = (TH1F*)filein->Get("x_tHW_htt");
			if(h_tHWhtt) yield_tH = yield_tH+h_tHWhtt->Integral();

		}
				
	}

	//cout<<"ttH Hww: "<<yield_ttHhww<<endl;
	//cout<<"ttH Hzz: "<<yield_ttHhzz<<endl;
	//cout<<"ttH Htt: "<<yield_ttHhtt<<endl;
	//cout<<"tH : "<<yield_tH<<endl;

	float total = yield_ttHhww+yield_ttHhzz+yield_ttHhtt+yield_tH;

	float fraction_ttHhww = yield_ttHhww/total;
	float fraction_ttHhzz = yield_ttHhzz/total;
	float fraction_ttHhtt = yield_ttHhtt/total;
	float fraction_tH = yield_tH/total;

	cout<<category<<" 	"<<yield_ttHhww<<"	"<<yield_ttHhzz<<"	"<<yield_ttHhtt<<"	"<<yield_tH<<endl;

}

void test_multilep(){

	vector<TString> categories;

	categories.push_back("2lss_0tau_mm_ttWnode");
	categories.push_back("2lss_0tau_mm_ttHnode");
	categories.push_back("2lss_0tau_mm_tHQnode");
	categories.push_back("2lss_0tau_mm_Restnode");
	categories.push_back("2lss_0tau_em_ttWnode");
	categories.push_back("2lss_0tau_em_ttHnode");
	categories.push_back("2lss_0tau_em_tHQnode");
	categories.push_back("2lss_0tau_em_Restnode");
	categories.push_back("2lss_0tau_ee_ttWnode");
	categories.push_back("2lss_0tau_ee_ttHnode");
	categories.push_back("2lss_0tau_ee_tHQnode");
	categories.push_back("2lss_0tau_ee_Restnode");
	categories.push_back("3l_0tau_rest_mmm_bt");
	categories.push_back("3l_0tau_rest_mmm_bl");
	categories.push_back("3l_0tau_rest_emm_bt");
	categories.push_back("3l_0tau_rest_emm_bl");
	categories.push_back("3l_0tau_rest_eem_bt");
	categories.push_back("3l_0tau_rest_eem_bl");
	categories.push_back("3l_0tau_rest_eee");
	categories.push_back("3l_0tau_ttH_bt");
	categories.push_back("3l_0tau_ttH_bl");
	categories.push_back("3l_0tau_tH_bt");
	categories.push_back("3l_0tau_tH_bl");
	categories.push_back("4l");

	for (unsigned int icat=0; icat<categories.size(); icat++){

		print_events(categories.at(icat), false);

	}

}

void test_tau(){

	vector<TString> categories;

	categories.push_back("3l_1tau");
	categories.push_back("2lss_1tau_ttH");
	categories.push_back("2lss_1tau_tH");
	categories.push_back("2lss_1tau_rest");
	categories.push_back("2los_1tau");
	categories.push_back("2l_2tau");
	categories.push_back("1l_2tau");
	categories.push_back("1l_1tau");
	categories.push_back("0l_2tau");

	for (unsigned int icat=0; icat<categories.size(); icat++){

		print_events(categories.at(icat), true);

	}

}