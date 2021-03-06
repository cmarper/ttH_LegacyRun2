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

void add_SFs(TString filein, TString fileout, vector<TString> treename, int year){

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
    float _npu;

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
      _npu = 0;

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

      //bool cat_2lss1tau = (_category == 3110 || _category==3120 || _category==3130);
      //if (!cat_2lss1tau) continue;

      int xbin = pu_histo->FindBin(_npu);
      _PU_weight_v1 = pu_histo->GetBinContent(xbin);

      ///////////

      _trigger_weight_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,0,_year); 

      ///////////

      if((*_recolep_sel_ismvasel)[0])
        _leptonID_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
      else
        _leptonID_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0);

      ///////////

      if((*_recolep_sel_ismvasel)[1])
        _leptonID_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0);
      else
        _leptonID_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0);

      ///////////

      TString wp;
      if((*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]==1) wp = "VLoose";
      else wp = "VVLoose";

      if( (*_recotauh_sel_isGenMatched)[0] ) {
        _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,0);
        _tauES_weight_v1 *= get_tauESSF(_year, (*_recotauh_sel_decayMode)[0],0);
      }
      else if(!(*_recotauh_sel_isGenMatched)[0]){
        std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
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


void loadsample(TString sample, int year, TString type){

    cout<<"Processing SR sample: "<<sample;

    TString year_s = std::to_string(year);

  	TString filein;
    filein = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/"+year_s+"/JECdown/"+type+"/ntuple_"+sample+"_MEM_SR_JECdown.root";

    TString fileout;
    fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/JECdown/"+type+"/ntuple_"+sample+"_MEM_SR_JECdown_SF_v1.root";

  	vector<TString> tree;
    tree.push_back("HTauTauTree_2lss1tau_SR");

    add_SFs(filein,fileout,tree,year);


}

void test_ttH(){

  loadsample("Oct19v1_MC_2016_ttHJetToNonbb",2016,"ttH");
  loadsample("Oct19v1_MC_2016_THQ_ctcvcp",2016,"ttH");
  loadsample("Oct19v1_MC_2016_THW_ctcvcp",2016,"ttH");
  loadsample("Oct19v1_MC_2017_ttHJetToNonbb",2017,"ttH");
  loadsample("Oct19v1_MC_2017_THQ_ctcvcp",2017,"ttH");
  loadsample("Oct19v3_MC_2017_THW_ctcvcp",2017,"ttH");
  loadsample("Oct19v2_MC_2018_ttHJetToNonbb",2018,"ttH");
  loadsample("Oct19v1_MC_2018_THQ_ctcvcp",2018,"ttH");
  loadsample("Oct19v1_MC_2018_THW_ctcvcp",2018,"ttH");

}

void test_ttV(){

  loadsample("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",2016,"ttV");
  loadsample("Oct19v1_MC_2016_TTZToLL_M-1to10",2016,"ttV");
  loadsample("Oct19v1_MC_2016_TTWJetsToLNu",2016,"ttV");
  loadsample("Oct19v1_MC_2016_TTWW",2016,"ttV");
  loadsample("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",2017,"ttV");
  loadsample("Oct19v1_MC_2017_TTZToLL_M-1to10",2017,"ttV");
  loadsample("Oct19v1_MC_2017_TTWJetsToLNu",2017,"ttV");
  loadsample("Oct19v1_MC_2017_TTWW",2017,"ttV");
  loadsample("Oct19v1_MC_2018_TTZToLLNuNu_M-10",2018,"ttV");
  loadsample("Oct19v1_MC_2018_TTZToLL_M-1to10",2018,"ttV");
  loadsample("Oct19v1_MC_2018_TTWJetsToLNu",2018,"ttV");
  loadsample("Oct19v1_MC_2018_TTWW_ext2",2018,"ttV");

}

void test_EWK(){

  loadsample("Oct19v1_MC_2016_WZTo3LNu",2016,"EWK");
  loadsample("Oct19v1_MC_2016_ZZTo4L",2016,"EWK");
  loadsample("Oct19v1_MC_2017_WZTo3LNu",2017,"EWK");
  loadsample("Oct19v1_MC_2017_ZZTo4L_ext1",2017,"EWK");
  loadsample("Oct19v2_MC_2018_WZTo3LNu_ext1",2018,"EWK");
  loadsample("Oct19v4_MC_2018_ZZTo4L_ext2",2018,"EWK");

}

void test_Rares(){

  /*loadsample("Oct19v1_MC_2016_WWW",2016,"Rares");
  loadsample("Oct19v1_MC_2016_WWZ",2016,"Rares");
  loadsample("Oct19v1_MC_2016_WZZ",2016,"Rares");
  loadsample("Oct19v1_MC_2016_ZZZ",2016,"Rares");
  loadsample("Oct19v1_MC_2016_WZG",2016,"Rares");
  loadsample("Oct19v1_MC_2016_WGToLNuG_ext1",2016,"Rares");
  loadsample("Oct19v1_MC_2016_ZGTo2LG",2016,"Rares");
  loadsample("Oct19v1_MC_2016_TGJets_leptonDecays",2016,"Rares");
  loadsample("Oct19v1_MC_2016_TTGJets",2016,"Rares");
  loadsample("Oct19v1_MC_2016_tZq_ll_PS",2016,"Rares");
  loadsample("Oct19v1_MC_2016_WpWpJJ",2016,"Rares");
  loadsample("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering",2016,"Rares");
  loadsample("Oct19v1_MC_2016_TTTT",2016,"Rares");
  loadsample("Oct19v1_MC_2017_WWW",2017,"Rares");
  loadsample("Oct19v1_MC_2017_WWZ",2017,"Rares");
  loadsample("Oct19v2_MC_2017_WZZ",2017,"Rares");
  loadsample("Oct19v2_MC_2017_ZZZ",2017,"Rares");
  loadsample("Oct19v1_MC_2017_WZG",2017,"Rares");
  loadsample("Oct19v1_MC_2017_WGToLNuG",2017,"Rares");
  loadsample("Oct19v1_MC_2017_ZGToLLG",2017,"Rares");
  loadsample("Oct19v1_MC_2017_TGJets",2017,"Rares");
  loadsample("Oct19v1_MC_2017_TTGJets_ext1",2017,"Rares");*/
  loadsample("Oct19v1_MC_2017_tZq_ll",2017,"Rares");
  loadsample("Oct19v2_MC_2017_WpWpJJ",2017,"Rares");
  loadsample("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering",2017,"Rares");
  loadsample("Oct19v1_MC_2017_TTTT",2017,"Rares");
  loadsample("Oct19v2_MC_2018_WWW",2018,"Rares");
  loadsample("Oct19v2_MC_2018_WWZ",2018,"Rares");
  loadsample("Oct19v1_MC_2018_WZZ",2018,"Rares");
  loadsample("Oct19v1_MC_2018_ZZZ",2018,"Rares");
  loadsample("Oct19v1_MC_2018_WZG",2018,"Rares");
  loadsample("Oct19v1_MC_2018_WGToLNuG",2018,"Rares");
  loadsample("Oct19v2_MC_2018_ZGToLLG",2018,"Rares");
  loadsample("Oct19v1_MC_2018_TGJets",2018,"Rares");
  loadsample("Oct19v1_MC_2018_tZq_ll",2018,"Rares");
  loadsample("Oct19v1_MC_2018_WpWpJJ",2018,"Rares");
  loadsample("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering",2018,"Rares");

}

void test_ttbar(){

  //MISSING TTBAR 2016
  loadsample("Oct19v1_MC_2017_TTJets_DiLept",2017,"ttbar");
  loadsample("Oct19v1_MC_2017_TTJets_SingleLeptFromT",2017,"ttbar");
  loadsample("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar",2017,"ttbar");
  loadsample("Oct19v1_MC_2018_TTJets_DiLept",2018,"ttbar");
  loadsample("Oct19v1_MC_2018_TTJets_SingleLeptFromT",2018,"ttbar");
  loadsample("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar",2018,"ttbar");

}
