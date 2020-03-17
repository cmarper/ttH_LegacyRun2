#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>
#include <TH2F.h>

#include "headers/triggerSF_v1.cc"
#include "headers/leptonSF_v1.cc"
#include "headers/tauIDSF_v1.cc"
#include "headers/tauESSF_v1.cc"
#include "headers/fakerateSF_v3.cc"

using namespace std;

void add_SFs(TString filein, TString fileout, vector<TString> treename, bool isMC, int year){

  TString pu_file_name;

  if (year==2016) pu_file_name = "PU_weights/pu_weights_2016.root";
  else if (year==2017) pu_file_name = "PU_weights/pu_weights_2017.root";
  else if (year==2018) pu_file_name = "PU_weights/pu_weights_2018.root";

  TFile* pu_file = TFile::Open(pu_file_name);
  TH1F* pu_histo = (TH1F*)pu_file->Get("weights");

  TFile* f_new = TFile::Open(fileout);
  /*if(f_new!=0){
  	cout<<fileout<<" already exists, please delete it before converting again"<<endl;
  	return;
  }*/
  
  f_new = TFile::Open(fileout,"RECREATE");
  
  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filein);
    
    Long64_t nentries = tree->GetEntries();
    cout<<", nentries="<<tree->GetEntries()<<endl;

    // old branches used

    int _category;
    int _year;

    Long64_t _triggerbit; 

    vector<int> 	  *_recolep_sel_pdg;    
    vector<float> 	*_recolep_sel_conept;
    vector<float> 	*_recolep_sel_pt;
    vector<float> 	*_recolep_sel_eta;
    vector<float> 	*_recolep_sel_phi;
    vector<bool>    *_recolep_sel_ismvasel;
    vector<int>     *_recolep_sel_charge;

    vector<float> 	*_recotauh_sel_pt;
    vector<float> 	*_recotauh_sel_eta;
    vector<float> 	*_recotauh_sel_phi;
    vector<int> 	  *_recotauh_sel_decayMode;
    vector<int>     *_recotauh_sel_byVVLooseDeepTau2017v2p1VSjet;
    vector<int>     *_recotauh_sel_byVLooseDeepTau2017v2p1VSjet;
    vector<int>     *_recotauh_sel_byLooseDeepTau2017v2p1VSjet;
    vector<int>     *_recotauh_sel_byMediumDeepTau2017v2p1VSjet;
    vector<int>     *_recotauh_sel_byVTightDeepTau2017v2p1VSjet;
    vector<int>     *_recotauh_sel_isGenMatched;
    vector<int>     *_recotauh_sel_charge;

    tree->SetBranchAddress("category",&_category);
    tree->SetBranchAddress("year",&_year);
    tree->SetBranchAddress("npu",&_npu);

    tree->SetBranchAddress("triggerbit",&_triggerbit);

    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree->SetBranchAddress("recolep_sel_phi",&_recolep_sel_phi);
    tree->SetBranchAddress("recolep_sel_ismvasel",&_recolep_sel_ismvasel);
    tree->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);

    tree->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
    tree->SetBranchAddress("recotauh_sel_eta",&_recotauh_sel_eta);
    tree->SetBranchAddress("recotauh_sel_phi",&_recotauh_sel_phi);
    tree->SetBranchAddress("recotauh_sel_decayMode",&_recotauh_sel_decayMode);
    tree->SetBranchAddress("recotauh_sel_byVVLooseDeepTau2017v2p1VSjet",&_recotauh_sel_byVVLooseDeepTau2017v2p1VSjet);
    tree->SetBranchAddress("recotauh_sel_byVLooseDeepTau2017v2p1VSjet",&_recotauh_sel_byVLooseDeepTau2017v2p1VSjet);
    tree->SetBranchAddress("recotauh_sel_byLooseDeepTau2017v2p1VSjet",&_recotauh_sel_byLooseDeepTau2017v2p1VSjet);
    tree->SetBranchAddress("recotauh_sel_byMediumDeepTau2017v2p1VSjet",&_recotauh_sel_byMediumDeepTau2017v2p1VSjet);
    tree->SetBranchAddress("recotauh_sel_byVTightDeepTau2017v2p1VSjet",&_recotauh_sel_byVTightDeepTau2017v2p1VSjet);
    tree->SetBranchAddress("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);
    tree->SetBranchAddress("recotauh_sel_charge",&_recotauh_sel_charge);

    // new branches

    TTree* tree_new=tree->GetTree()->CloneTree(0);

    float _PU_weight_v1;
    float _trigger_weight_v1;
    float _leptonID_weight_v1;
    float _tauID_weight_v3;
    float _tauES_weight_v1;

    tree_new->Branch("PU_weight_v1",&_PU_weight_v1,"PU_weight_v1/F");
    tree_new->Branch("trigger_weight_v1",&_trigger_weight_v1,"trigger_weight_v1/F");
    tree_new->Branch("leptonID_weight_v1",&_leptonID_weight_v1,"leptonID_weight_v1/F");
    tree_new->Branch("tauID_weight_v3",&_tauID_weight_v3,"tauID_weight_v3/F");
    tree_new->Branch("tauES_weight_v1",&_tauES_weight_v1,"tauES_weight_v1/F");

    for(int i=0;i<nentries;i++){
      
      if(i%1000==0)
	      cout<<"i="<<i<<endl;

	    // Old variables

	    _category = 0;
      _year = 0;

      _triggerbit = 0;

      _recolep_sel_pdg = 0;
      _recolep_sel_conept = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;
      _recolep_sel_phi = 0;
      _recolep_sel_ismvasel = 0;
      _recolep_sel_charge = 0;

      _recotauh_sel_pt = 0;
      _recotauh_sel_eta = 0;
      _recotauh_sel_phi = 0;
      _recotauh_sel_decayMode = 0;
      _recotauh_sel_byVVLooseDeepTau2017v2p1VSjet = 0;
      _recotauh_sel_byVLooseDeepTau2017v2p1VSjet = 0;
      _recotauh_sel_byLooseDeepTau2017v2p1VSjet = 0;
      _recotauh_sel_byMediumDeepTau2017v2p1VSjet = 0;
      _recotauh_sel_byVTightDeepTau2017v2p1VSjet = 0;
      _recotauh_sel_isGenMatched = 0;
      _recotauh_sel_charge = 0;

      //////////

      _PU_weight_v1 = 0;
      _trigger_weight_v1 = 0;
      _leptonID_weight_v1 = 0;
      _tauID_weight_v3 = 0;
      _tauES_weight_v1 = 0;

      tree->GetEntry(i);

      if(i==(nentries-1)) cout<<"FINISHED!!!"<<endl;

      _PU_weight_v1 = 1.;
      _trigger_weight_v1 = 1.;
      _leptonID_weight_v1 = 1.;
      _tauID_weight_v3 = 1.;
      _tauES_weight_v1 = 1.;

      // New variables

      bool cat_2lss1tau = (_category == 3110 || _category==3120 || _category==3130);

      if (!cat_2lss1tau) continue;

      int xbin = pu_histo->FindBin(_npu);
      _PU_weight_v1 = pu_histo->GetBinContent(xbin);

      _trigger_weight_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,0,_year); 

      if((*_recolep_sel_ismvasel)[0])
        _leptonID_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 

      else
        _leptonID_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0);

      if((*_recolep_sel_ismvasel)[1])
        _leptonID_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0);

      else
        _leptonID_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0);

      TString wp;
      if((*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]==1) wp = "VLoose";
      else wp = "VVLoose";

      if( (*_recotauh_sel_isGenMatched)[0] ) {

        _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,0);
        _tauES_weight_v1 *= get_tauESSF(_year, (*_recotauh_sel_decayMode)[0],0);

      }

      else if(!(*_recotauh_sel_isGenMatched)[0]){

        _tauID_weight_v3 *= std::get<0>(tau_fakerate);

      }

      /////////////////////////////////////////////////////////////

      tree_new->Fill();

		}

		f_new->cd();
    tree_new->Write();

	}

	f_new->Close();
  pu_file->Close();

  return;

}


void loadsample(TString sample, int year, TString type, bool ismc){

    cout<<"Processing SR sample: "<<sample;

    TString year_s = std::to_string(year);

  	TString filein;
    filein = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/"+year_s+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR.root";

    TString fileout;
    fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR_SF_v1.root";

  	vector<TString> tree;
    tree.push_back("HTauTauTree_2lss1tau_SR");

    add_SFs(filein,fileout,tree,ismc,year);


}

void test_2016(TString region = "SR"){

  //loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12",2016,"HH",true);

}

void test_2017(TString region = "SR"){

  //loadsample("Oct19v2_MC_2017_GluGluToHHTo4V_node_12",2017,"HH",true);

}

void test_2018(TString region = "SR"){

  //loadsample("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_11",2018,"HH",true);

}