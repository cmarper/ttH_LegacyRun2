#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

using namespace std;

void print_cutoff(TString file, bool ismiss){

	TString filein = file;
    TFile *f = new TFile(filein);
    
    TString category;
    if(!ismiss) category = "ttH_2lss_1tau_nomiss";
    else if(ismiss) category = "ttH_2lss_1tau_miss";

    TH1F* histo_ttH_hww = new TH1F("ttH_hww","ttH_hww",10,0,1);
    TH1F* histo_ttH_hzz = new TH1F("ttH_hzz","ttH_hzz",10,0,1);
    TH1F* histo_ttH_htt = new TH1F("ttH_htt","ttH_htt",10,0,1);
    TH1F* histo_tHq_hww = new TH1F("tHq_hww","tHq_hww",10,0,1);
    TH1F* histo_tHq_hzz = new TH1F("tHq_hzz","tHq_hzz",10,0,1);
    TH1F* histo_tHq_htt = new TH1F("tHq_htt","tHq_htt",10,0,1);
    TH1F* histo_tHW_hww = new TH1F("tHW_hww","tHW_hww",10,0,1);
    TH1F* histo_tHW_hzz = new TH1F("tHW_hzz","tHW_hzz",10,0,1);
    TH1F* histo_tHW_htt = new TH1F("tHW_htt","tHW_htt",10,0,1);
    TH1F* histo_ZH_hww = new TH1F("ZH_hww","ZH_hww",10,0,1);
    TH1F* histo_ZH_hzz = new TH1F("ZH_hzz","ZH_hzz",10,0,1);
    TH1F* histo_ZH_htt = new TH1F("ZH_htt","ZH_htt",10,0,1);
    TH1F* histo_WH_hww = new TH1F("WH_hww","WH_hww",10,0,1);
    TH1F* histo_WH_hzz = new TH1F("WH_hzz","WH_hzz",10,0,1);
    TH1F* histo_WH_htt = new TH1F("WH_htt","WH_htt",10,0,1);
    TH1F* histo_TTZH_hww = new TH1F("TTZH_hww","TTZH_hww",10,0,1);
    TH1F* histo_TTZH_hzz = new TH1F("TTZH_hzz","TTZH_hzz",10,0,1);
    TH1F* histo_TTZH_htt = new TH1F("TTZH_htt","TTZH_htt",10,0,1);
    TH1F* histo_TTWH_hww = new TH1F("TTWH_hww","TTWH_hww",10,0,1);
    TH1F* histo_TTWH_hzz = new TH1F("TTWH_hzz","TTWH_hzz",10,0,1);
    TH1F* histo_TTWH_htt = new TH1F("TTWH_htt","TTWH_htt",10,0,1);
    TH1F* histo_TTZ = new TH1F("TTZ","TTZ",10,0,1);
    TH1F* histo_TTW = new TH1F("TTW","TTW",10,0,1);
    TH1F* histo_TTWW = new TH1F("TTWW","TTWW",10,0,1);
    TH1F* histo_WZ = new TH1F("WZ","WZ",10,0,1);
    TH1F* histo_ZZ = new TH1F("ZZ","ZZ",10,0,1);
    TH1F* histo_Rares = new TH1F("Rares","Rares",10,0,1);
    TH1F* histo_Convs = new TH1F("Convs","Convs",10,0,1);
    TH1F* histo_data_fakes = new TH1F("data_fakes","data_fakes",10,0,1);
    TH1F* histo_data_flips = new TH1F("data_flips","data_flips",10,0,1);

    histo_ttH_hww = (TH1F*)f->Get(category+"/ttH_hww");
    histo_ttH_hzz = (TH1F*)f->Get(category+"/ttH_hzz");
    histo_ttH_htt = (TH1F*)f->Get(category+"/ttH_htt");
    histo_tHq_hww = (TH1F*)f->Get(category+"/tHq_hww");
    histo_tHq_hzz = (TH1F*)f->Get(category+"/tHq_hzz");
    histo_tHq_htt = (TH1F*)f->Get(category+"/tHq_htt");
    histo_tHW_hww = (TH1F*)f->Get(category+"/tHW_hww");
    histo_tHW_hzz = (TH1F*)f->Get(category+"/tHW_hzz");
    histo_tHW_htt = (TH1F*)f->Get(category+"/tHW_htt");
    histo_ZH_hww = (TH1F*)f->Get(category+"/ZH_hww");
    histo_ZH_hzz = (TH1F*)f->Get(category+"/ZH_hzz");
    histo_ZH_htt = (TH1F*)f->Get(category+"/ZH_htt");
    histo_WH_hww = (TH1F*)f->Get(category+"/WH_hww");
    histo_WH_hzz = (TH1F*)f->Get(category+"/WH_hzz");
    histo_WH_htt = (TH1F*)f->Get(category+"/WH_htt");
    histo_TTZH_hww = (TH1F*)f->Get(category+"/TTZH_hww");
    histo_TTZH_hzz = (TH1F*)f->Get(category+"/TTZH_hzz");
    histo_TTZH_htt = (TH1F*)f->Get(category+"/TTZH_htt");
    histo_TTWH_hww = (TH1F*)f->Get(category+"/TTWH_hww");
    histo_TTWH_hzz = (TH1F*)f->Get(category+"/TTWH_hzz");
    histo_TTWH_htt = (TH1F*)f->Get(category+"/TTWH_htt");
    histo_TTZ = (TH1F*)f->Get(category+"/TTZ");
    histo_TTW = (TH1F*)f->Get(category+"/TTW");
    histo_TTWW = (TH1F*)f->Get(category+"/TTWW");
    histo_WZ = (TH1F*)f->Get(category+"/WZ");
    histo_ZZ = (TH1F*)f->Get(category+"/ZZ");
    histo_Rares = (TH1F*)f->Get(category+"/Rares");
    histo_Convs = (TH1F*)f->Get(category+"/Convs");
    histo_data_fakes = (TH1F*)f->Get(category+"/data_fakes");
    histo_data_flips = (TH1F*)f->Get(category+"/data_flips");

    vector<TH1F*> histos_signal;
    histos_signal.clear();

    histos_signal.push_back(histo_ttH_hww);
    histos_signal.push_back(histo_ttH_hzz);
    histos_signal.push_back(histo_ttH_htt);
    histos_signal.push_back(histo_tHq_hww);
    histos_signal.push_back(histo_tHq_hzz);
    histos_signal.push_back(histo_tHq_htt);
    histos_signal.push_back(histo_tHW_hww);
    histos_signal.push_back(histo_tHW_hzz);
    histos_signal.push_back(histo_tHW_htt);

    vector<TH1F*> histos_bkg;
    histos_bkg.clear();
    histos_bkg.push_back(histo_ZH_hww);
    histos_bkg.push_back(histo_ZH_hzz);
    histos_bkg.push_back(histo_ZH_htt);
    histos_bkg.push_back(histo_WH_hww);
    histos_bkg.push_back(histo_WH_hzz);
    histos_bkg.push_back(histo_WH_htt);
    histos_bkg.push_back(histo_TTZH_hww);
    histos_bkg.push_back(histo_TTZH_hzz);
    histos_bkg.push_back(histo_TTZH_htt);
    histos_bkg.push_back(histo_TTWH_hww);
    histos_bkg.push_back(histo_TTWH_hzz);
    histos_bkg.push_back(histo_TTWH_htt);
    histos_bkg.push_back(histo_TTZ);
    histos_bkg.push_back(histo_TTW);
    histos_bkg.push_back(histo_TTWW);
    histos_bkg.push_back(histo_WZ);
    histos_bkg.push_back(histo_ZZ);
    histos_bkg.push_back(histo_Rares);
    histos_bkg.push_back(histo_Convs);
    histos_bkg.push_back(histo_data_fakes);
    histos_bkg.push_back(histo_data_flips);

    cout<<" --- "<<endl;
    cout<<file<<endl;
    for(unsigned int i=0; i<histos_signal.size(); i++){
        if(histos_signal.at(i)->Integral()>=0.01)
            cout<<"\""<<histos_signal.at(i)->GetName()<<"\",";
    }

    cout<<endl;
    for(unsigned int i=0; i<histos_bkg.size(); i++){
        if(histos_bkg.at(i)->Integral()>=0.01)
            cout<<"\""<<histos_bkg.at(i)->GetName()<<"\",";
    }
    cout<<endl;


}

void test(){

    TString dirin = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/";

    print_cutoff(dirin+"datacard_MEM_nomiss_2lss1tau_2016.root",false);
    print_cutoff(dirin+"datacard_MEM_nomiss_2lss1tau_2017.root",false);
    print_cutoff(dirin+"datacard_MEM_nomiss_2lss1tau_2018.root",false);

    print_cutoff(dirin+"datacard_MEM_miss_2lss1tau_2016.root",true);
    print_cutoff(dirin+"datacard_MEM_miss_2lss1tau_2017.root",true);
    print_cutoff(dirin+"datacard_MEM_miss_2lss1tau_2018.root",true);

}

