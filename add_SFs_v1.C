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
#include "headers/tauSF_v1.cc"
#include "headers/fakerateSF_v1.cc"
#include "headers/fliprateSF_v1.cc"

using namespace std;

void add_SFs(TString filein, TString fileout, vector<TString> treename, bool isMC){

	  /*
	  1010 2tau_SR
	  1020 2tau_fake

	  2010 1l1tau_SR
	  2020 1l1tau_fake
	  2030 1l1tau_flip

	  2110 1l2tau_SR
	  2120 1l2tau_fake

	  3010 2lss_SR
	  3020 2lss_fake
	  3030 2lss_flip

	  3110 2lss1tau_SR
	  3120 2lss1tau_fake
	  3130 2lss1tau_flip

	  3210 2los1tau_SR
	  3220 2los1tau_fake

	  3310 2l2tau_SR
	  3320 2l2tau_fake

	  4010 3l_SR
	  4020 3l_fake

	  4110 3l1tau_SR
	  4120 3l1tau_fake

	  5010 4l_SR
	  5020 4l_fake

	  6010 ttW_CR_SR
	  6020 ttW_CR_fake
	  6030 ttW_CR_flip

	  7010 ttZ_CR_SR
	  7020 ttZ_CR_fake

	  8010 WZ_CR_SR
	  8020 WZ_CR_fake

	  9010 ZZ_CR_SR
	  9020 ZZ_CR_fake

	  10010 3l_CR_SR
	  10020 3l_CR_fake

  	11010 4l_CR_SR
  	11020 4l_CR_fake
  	*/

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
      //nentries = 10;
      cout<<treename[i_tree]<<", nentries="<<tree->GetEntries()<<endl;

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

      float _triggerSF_weight_v1;
      float _triggerSF_weight_up_v1;
      float _triggerSF_weight_down_v1;

      float _leptonSF_weight_v1;

      float _tauSF_weight_v1;
      float _tauSF_weight_up_v1;
      float _tauSF_weight_down_v1;

      float _tauSF_weight_tauNormUp_v1;
      float _tauSF_weight_tauNormDown_v1;
      float _tauSF_weight_tauShapeUp_v1;
      float _tauSF_weight_tauShapeDown_v1;

      float _event_weight_ttH_v1;

      float _event_weight_ttH_ele_up_v1;
      float _event_weight_ttH_ele_down_v1;
      float _event_weight_ttH_ele_pt1_v1;
      float _event_weight_ttH_ele_pt2_v1;
      float _event_weight_ttH_ele_be1_v1;
      float _event_weight_ttH_ele_be2_v1;

      float _event_weight_ttH_mu_up_v1;
      float _event_weight_ttH_mu_down_v1;
      float _event_weight_ttH_mu_pt1_v1;
      float _event_weight_ttH_mu_pt2_v1;
      float _event_weight_ttH_mu_be1_v1;
      float _event_weight_ttH_mu_be2_v1;

      float _event_weight_ttH_FR_QCD_MC_v1;
      float _event_weight_ttH_FR_TT_MC_v1;
      float _event_weight_ttH_ele_FR_QCD_MC_v1;
      float _event_weight_ttH_ele_FR_TT_MC_v1;
      float _event_weight_ttH_mu_FR_QCD_MC_v1;
      float _event_weight_ttH_mu_FR_TT_MC_v1;

    	TTree* tree_new=tree->GetTree()->CloneTree(0);

    	tree_new->Branch("triggerSF_weight_v1",&_triggerSF_weight_v1,"triggerSF_weight_v1/F");
    	tree_new->Branch("triggerSF_weight_up_v1",&_triggerSF_weight_up_v1,"triggerSF_weight_up_v1/F");
    	tree_new->Branch("triggerSF_weight_down_v1",&_triggerSF_weight_down_v1,"triggerSF_weight_down_v1/F");

    	tree_new->Branch("leptonSF_weight_v1",&_leptonSF_weight_v1,"leptonSF_weight_v1/F");

      tree_new->Branch("tauSF_weight_v1",&_tauSF_weight_v1,"tauSF_weight_v1/F");
      tree_new->Branch("tauSF_weight_up_v1",&_tauSF_weight_up_v1,"tauSF_weight_up_v1/F");
      tree_new->Branch("tauSF_weight_down_v1",&_tauSF_weight_down_v1,"tauSF_weight_down_v1/F");

      tree_new->Branch("tauSF_weight_tauNormUp_v1",&_tauSF_weight_tauNormUp_v1,"tauSF_weight_tauNormUp_v1/F");
      tree_new->Branch("tauSF_weight_tauNormDown_v1",&_tauSF_weight_tauNormDown_v1,"tauSF_weight_tauNormDown_v1/F");
      tree_new->Branch("tauSF_weight_tauShapeUp_v1",&_tauSF_weight_tauShapeUp_v1,"tauSF_weight_tauShapeUp_v1/F");
      tree_new->Branch("tauSF_weight_tauShapeDown_v1",&_tauSF_weight_tauShapeDown_v1,"tauSF_weight_tauShapeDown_v1/F");

      tree_new->Branch("event_weight_ttH_v1",&_event_weight_ttH_v1,"event_weight_ttH_v1/F");

      tree_new->Branch("event_weight_ttH_ele_up_v1",&_event_weight_ttH_ele_up_v1,"event_weight_ttH_ele_up_v1/F");
      tree_new->Branch("event_weight_ttH_ele_down_v1",&_event_weight_ttH_ele_down_v1,"event_weight_ttH_ele_down_v1/F");
      tree_new->Branch("event_weight_ttH_ele_pt1_v1",&_event_weight_ttH_ele_pt1_v1,"event_weight_ttH_ele_pt1_v1/F");
      tree_new->Branch("event_weight_ttH_ele_pt2_v1",&_event_weight_ttH_ele_pt2_v1,"event_weight_ttH_ele_pt2_v1/F");
      tree_new->Branch("event_weight_ttH_ele_be1_v1",&_event_weight_ttH_ele_be1_v1,"event_weight_ttH_ele_be1_v1/F");
      tree_new->Branch("event_weight_ttH_ele_be2_v1",&_event_weight_ttH_ele_be2_v1,"event_weight_ttH_ele_be2_v1/F");

      tree_new->Branch("event_weight_ttH_mu_up_v1",&_event_weight_ttH_mu_up_v1,"event_weight_ttH_mu_up_v1/F");
      tree_new->Branch("event_weight_ttH_mu_down_v1",&_event_weight_ttH_mu_down_v1,"event_weight_ttH_mu_down_v1/F");
      tree_new->Branch("event_weight_ttH_mu_pt1_v1",&_event_weight_ttH_mu_pt1_v1,"event_weight_ttH_mu_pt1_v1/F");
      tree_new->Branch("event_weight_ttH_mu_pt2_v1",&_event_weight_ttH_mu_pt2_v1,"event_weight_ttH_mu_pt2_v1/F");
      tree_new->Branch("event_weight_ttH_mu_be1_v1",&_event_weight_ttH_mu_be1_v1,"event_weight_ttH_mu_be1_v1/F");
      tree_new->Branch("event_weight_ttH_mu_be2_v1",&_event_weight_ttH_mu_be2_v1,"event_weight_ttH_mu_be2_v1/F");

      tree_new->Branch("event_weight_ttH_FR_QCD_MC_v1",&_event_weight_ttH_FR_QCD_MC_v1,"event_weight_ttH_FR_QCD_MC_v1/F");
      tree_new->Branch("event_weight_ttH_FR_TT_MC_v1",&_event_weight_ttH_FR_TT_MC_v1,"event_weight_ttH_FR_TT_MC_v1/F");
      tree_new->Branch("event_weight_ttH_ele_FR_QCD_MC_v1",&_event_weight_ttH_ele_FR_QCD_MC_v1,"event_weight_ttH_ele_FR_QCD_MC_v1/F");
      tree_new->Branch("event_weight_ttH_ele_FR_TT_MC_v1",&_event_weight_ttH_ele_FR_TT_MC_v1,"event_weight_ttH_ele_FR_TT_MC_v1/F");
      tree_new->Branch("event_weight_ttH_mu_FR_QCD_MC_v1",&_event_weight_ttH_mu_FR_QCD_MC_v1,"event_weight_ttH_mu_FR_QCD_MC_v1/F");
      tree_new->Branch("event_weight_ttH_mu_FR_TT_MC_v1",&_event_weight_ttH_mu_FR_TT_MC_v1,"event_weight_ttH_mu_FR_TT_MC_v1/F");

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

        _triggerSF_weight_v1 = 1.;
        _triggerSF_weight_up_v1 = 1.;
        _triggerSF_weight_down_v1 = 1.;

        _leptonSF_weight_v1 = 1.;

        _tauSF_weight_v1 = 1.;
        _tauSF_weight_up_v1 = 1.;
        _tauSF_weight_down_v1 = 1.;

        _tauSF_weight_tauNormUp_v1 = 1.;
        _tauSF_weight_tauNormDown_v1 = 1.;
        _tauSF_weight_tauShapeUp_v1 = 1.;
        _tauSF_weight_tauShapeDown_v1 = 1.;

        _event_weight_ttH_v1 = 1.;

        _event_weight_ttH_ele_up_v1 = 1.;
        _event_weight_ttH_ele_down_v1 = 1.;
        _event_weight_ttH_ele_pt1_v1 = 1.;
        _event_weight_ttH_ele_pt2_v1 = 1.;
        _event_weight_ttH_ele_be1_v1 = 1.;
        _event_weight_ttH_ele_be2_v1 = 1.;

        _event_weight_ttH_mu_up_v1 = 1.;
        _event_weight_ttH_mu_down_v1 = 1.;
        _event_weight_ttH_mu_pt1_v1 = 1.;
        _event_weight_ttH_mu_pt2_v1 = 1.;
        _event_weight_ttH_mu_be1_v1 = 1.;
        _event_weight_ttH_mu_be2_v1 = 1.;

        _event_weight_ttH_FR_QCD_MC_v1 = 1.;
        _event_weight_ttH_FR_TT_MC_v1 = 1.;
        _event_weight_ttH_ele_FR_QCD_MC_v1 = 1.;
        _event_weight_ttH_ele_FR_TT_MC_v1 = 1.;
        _event_weight_ttH_mu_FR_QCD_MC_v1 = 1.;
        _event_weight_ttH_mu_FR_TT_MC_v1 = 1.;

      	tree->GetEntry(i);

        // New variables

      	bool cat_2tau = 	  (_category == 1010 || _category==1020);
      	bool cat_1l1tau = 	(_category == 2010 || _category==2020 || _category==2030);
      	bool cat_1l2tau = 	(_category == 2110 || _category==2120);
      	bool cat_2lss1tau = (_category == 3110 || _category==3120 || _category==3130);
      	bool cat_2los1tau = (_category == 3210 || _category==3220);
      	bool cat_2l2tau = 	(_category == 3310 || _category==3320);
      	bool cat_3l1tau = 	(_category == 4110 || _category==4120);


      	///////////////////////////////////////////////////////////
      	/////////////////////// TRIGGER SFS ///////////////////////
      	///////////////////////////////////////////////////////////

      	Long64_t bitdigit = 1;

    		bool pass_HLT_IsoMu22_v = _triggerbit & (bitdigit << 0);
    		bool pass_HLT_IsoTkMu22_v = _triggerbit & (bitdigit << 1);
    		bool pass_HLT_IsoMu22_eta2p1_v = _triggerbit & (bitdigit << 2);
    		bool pass_HLT_IsoTkMu22_eta2p1_v = _triggerbit & (bitdigit << 3);
    		bool pass_HLT_IsoMu24_v = _triggerbit & (bitdigit << 4);
    		bool pass_HLT_IsoTkMu24_v = _triggerbit & (bitdigit << 5);
    		bool pass_HLT_IsoMu27_v = _triggerbit & (bitdigit << 6);
    		bool pass_HLT_Ele25_eta2p1_WPTight_Gsf_v = _triggerbit & (bitdigit << 7);
    		bool pass_HLT_Ele27_WPTight_Gsf_v = _triggerbit & (bitdigit << 8);
    		bool pass_HLT_Ele27_eta2p1_WPLoose_Gsf_v = _triggerbit & (bitdigit << 9);
    		bool pass_HLT_Ele32_WPTight_Gsf_v = _triggerbit & (bitdigit << 10);
    		bool pass_HLT_Ele35_WPTight_Gsf_v = _triggerbit & (bitdigit << 11);
    		bool pass_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v = _triggerbit & (bitdigit << 12);
    		bool pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 13);
    		bool pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 14);
    		bool pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v = _triggerbit & (bitdigit << 15);
    		bool pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v = _triggerbit & (bitdigit << 16);
    		bool pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v = _triggerbit & (bitdigit << 17);
    		bool pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 18);
    		bool pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 19);
    		bool pass_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 20);
    		bool pass_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 21);
    		bool pass_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 22);
    		bool pass_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v = _triggerbit & (bitdigit << 23);
    		bool pass_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v = _triggerbit & (bitdigit << 24);
    		bool pass_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 25);
    		bool pass_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 26);
    		bool pass_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 27);
    		bool pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 28);
    		bool pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 29);
    		bool pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 30);
    		bool pass_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 31);
    		bool pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 32);
    		bool pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 33);
    		bool pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 34);
    		bool pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 35);
    		bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v = _triggerbit & (bitdigit << 36);
    		bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v = _triggerbit & (bitdigit << 37);
    		bool pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v = _triggerbit & (bitdigit << 38);
    		bool pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v = _triggerbit & (bitdigit << 39);
    		bool pass_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v = _triggerbit & (bitdigit << 40);
    		bool pass_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v = _triggerbit & (bitdigit << 41);
    		bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v = _triggerbit & (bitdigit << 42);
    		bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v = _triggerbit & (bitdigit << 43);
    		bool pass_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 44);
    		bool pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 45);
    		bool pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 46);
    		bool pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v = _triggerbit & (bitdigit << 47);
    		bool pass_HLT_TripleMu_12_10_5_v = _triggerbit & (bitdigit << 48);
    		bool pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v = _triggerbit & (bitdigit << 49);
    		bool pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v = _triggerbit & (bitdigit << 50);
    		bool pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v = _triggerbit & (bitdigit << 51);
    		bool pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v  = _triggerbit & (bitdigit << 52);

    		bool pass_m = false;
    		if(_year==2016) pass_m = ( pass_HLT_IsoMu22_v || pass_HLT_IsoTkMu22_v || pass_HLT_IsoMu22_eta2p1_v || pass_HLT_IsoTkMu22_eta2p1_v || pass_HLT_IsoMu24_v || pass_HLT_IsoTkMu24_v );
    		else if(_year==2017) pass_m = ( pass_HLT_IsoMu24_v || pass_HLT_IsoMu27_v );
    		else if(_year==2018) pass_m = ( pass_HLT_IsoMu24_v || pass_HLT_IsoMu27_v );

    		bool pass_e = false;
    		if(_year==2016) pass_e = ( pass_HLT_Ele27_WPTight_Gsf_v || pass_HLT_Ele25_eta2p1_WPTight_Gsf_v || pass_HLT_Ele27_eta2p1_WPLoose_Gsf_v );
    		else if(_year==2017) pass_e = ( pass_HLT_Ele35_WPTight_Gsf_v || pass_HLT_Ele32_WPTight_Gsf_v );
    		else if(_year==2018) pass_e = ( pass_HLT_Ele32_WPTight_Gsf_v );
    
    		bool pass_2e = false;
    		if(_year==2016) pass_2e = pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v;
    		else if(_year==2017) pass_2e = pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v;
    		else if(_year==2018) pass_2e = pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v;

    		bool pass_2m = false;
    		if(_year==2016) pass_2m = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v || pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v || pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v || pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v);
    		else if(_year==2017) pass_2m = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v || pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v);
    		else if(_year==2018) pass_2m = pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v;

    		bool pass_em = false;
    		if(_year==2016) pass_em = (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v || pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v || pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v);
    		else if(_year==2017) pass_em = (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v || pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v);
    		else if(_year==2018) pass_em = (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v);

    		bool pass_et = false;
    		if(_year==2016) pass_et = (pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v || pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v || pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v);
    		else if(_year==2017) pass_et = pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v;
    		else if(_year==2018) pass_et = (pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v || pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_v);

    		bool pass_mt = false;
    		if(_year==2016) pass_mt = pass_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v;
    		else if(_year==2017) pass_mt = pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v;
    		else if(_year==2018) pass_mt = (pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v || pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v);

    		bool pass_2t = false;
    		if(_year==2016) pass_2t = (pass_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v || pass_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v );
    		else if(_year==2017) pass_2t = (pass_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_v || pass_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v);
    		else if(_year==2018) pass_2t = (pass_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v || pass_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v);

    		bool pass_3e = false;
    		if(_year==2016) pass_3e = pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v;
    		else if(_year==2017) pass_3e = pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v;
    		else if(_year==2018) pass_3e = pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v;

    		bool pass_3m = false;
    		if(_year==2016) pass_3m = pass_HLT_TripleMu_12_10_5_v;
    		else if(_year==2017) pass_3m = pass_HLT_TripleMu_12_10_5_v;
    		else if(_year==2018) pass_3m = pass_HLT_TripleMu_12_10_5_v;

    		bool pass_m2e = false;
    		if(_year==2016) pass_m2e = pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v;
    		else if(_year==2017) pass_m2e = pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v;
    		else if(_year==2018) pass_m2e = pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v;

    		bool pass_2me = false;
    		if(_year==2016) pass_2me = pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v;
    		else if(_year==2017) pass_2me = pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v;
    		else if(_year==2018) pass_2me = pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v;

      	if ( cat_2tau ){ // ditau trigger

            TString wp1;
            if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[0]==1) wp1 = "Loose";
            else wp1 = "VVLoose";

            TString wp2;
            if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[1]==1) wp2 = "Loose";
            else wp2 = "VVLoose";

            _triggerSF_weight_v1 = get_triggerSF_ditau((*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp1,
                                           (*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1],(*_recotauh_sel_phi)[1],(*_recotauh_sel_decayMode)[1],wp2,
                                           _year, 0 );
            _triggerSF_weight_up_v1 = get_triggerSF_ditau((*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp1,
                                           (*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1],(*_recotauh_sel_phi)[1],(*_recotauh_sel_decayMode)[1],wp2,
                                           _year, +1 );
            _triggerSF_weight_down_v1 = get_triggerSF_ditau((*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp1,
                                           (*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1],(*_recotauh_sel_phi)[1],(*_recotauh_sel_decayMode)[1],wp2,
                                           _year, -1 );

        }

        else if ( cat_1l1tau ){ // cross-trigger with one tau

            bool passHLT1l = (pass_m || pass_e);
            bool passHLT1l1tau = (pass_et || pass_mt);

            TString wp;
            if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]==1) wp = "Medium";
            else wp = "VVLoose";

            _triggerSF_weight_v1 = get_triggerSF_1lep1tau((*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],(*_recolep_sel_pdg)[0],
                                           (*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp,
                                           passHLT1l, passHLT1l1tau, _year, 0 );
            _triggerSF_weight_up_v1 = get_triggerSF_1lep1tau((*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],(*_recolep_sel_pdg)[0],
                                           (*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp,
                                           passHLT1l, passHLT1l1tau, _year, +1 );
            _triggerSF_weight_down_v1 = get_triggerSF_1lep1tau((*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],(*_recolep_sel_pdg)[0],
                                           (*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp,
                                           passHLT1l, passHLT1l1tau, _year, -1 );

        }

        else if ( cat_2lss1tau || cat_2los1tau || cat_2l2tau ) { // 2-lepton triggers

            _triggerSF_weight_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,0,_year);
            _triggerSF_weight_up_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,+1,_year);
            _triggerSF_weight_down_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,-1,_year);

        }

        else if ( cat_3l1tau ){ // 3-lepton triggers

            _triggerSF_weight_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],3,0,_year);
            _triggerSF_weight_up_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],3,+1,_year);
            _triggerSF_weight_down_v1 = get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],3,-1,_year);

        }

        else if ( cat_1l2tau ){ // cross-trigger with 2 taus

            bool passHLT1l = (pass_m || pass_e);
            bool passHLT1l1tau = (pass_et || pass_mt);

            TString wp1;
            if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]==1) wp1 = "Medium";
            else wp1 = "VVLoose";

            TString wp2;
            if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[1]==1) wp2 = "Medium";
            else wp2 = "VVLoose";

            _triggerSF_weight_v1 = get_triggerSF_1lep2tau((*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],(*_recolep_sel_pdg)[0],
                                           (*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp1,
                                           (*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1],(*_recotauh_sel_phi)[1],(*_recotauh_sel_decayMode)[1],wp2,
                                           passHLT1l, passHLT1l1tau, _year, 0 );
            _triggerSF_weight_up_v1 = get_triggerSF_1lep2tau((*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],(*_recolep_sel_pdg)[0],
                                           (*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp1,
                                           (*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1],(*_recotauh_sel_phi)[1],(*_recotauh_sel_decayMode)[1],wp2,
                                           passHLT1l, passHLT1l1tau, _year, +1 );
            _triggerSF_weight_down_v1 = get_triggerSF_1lep2tau((*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],(*_recolep_sel_pdg)[0],
                                           (*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0],(*_recotauh_sel_phi)[0],(*_recotauh_sel_decayMode)[0],wp1,
                                           (*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1],(*_recotauh_sel_phi)[1],(*_recotauh_sel_decayMode)[1],wp2,
                                           passHLT1l, passHLT1l1tau, _year, -1 );

        }


      	/////////////////////////////////////////////////////////////
      	/////////////////////// LEPTON ID SFS ///////////////////////
      	/////////////////////////////////////////////////////////////

      	if ( cat_1l1tau || cat_1l2tau ){ // 1 lepton no tight charge

      			if((*_recolep_sel_ismvasel)[0])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3); 
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0);

      	}

      	else if ( cat_2lss1tau ){ // 2 leptons tight charge

      		  if((*_recolep_sel_ismvasel)[0])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2); 
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,2);

      			if((*_recolep_sel_ismvasel)[1])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2);
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,2);

        }

      	else if ( cat_2l2tau || cat_2los1tau ){ // 2 leptons not tight charge

      		  if((*_recolep_sel_ismvasel)[0])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3); 
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0);

      			if((*_recolep_sel_ismvasel)[1])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3);
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0);

        }

        else if ( cat_3l1tau ){ // 3 leptons no tight charge

      		  if((*_recolep_sel_ismvasel)[0])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3); 
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0);

      			if((*_recolep_sel_ismvasel)[1])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3);
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0);

        		if((*_recolep_sel_ismvasel)[2])
        			_leptonSF_weight_v1 *= get_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3);
      			else
        			_leptonSF_weight_v1 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0);

        }


        //////////////////////////////////////////////////////////
        /////////////////////// TAU ID SFS ///////////////////////
        //////////////////////////////////////////////////////////

        if(isMC){

          if ( cat_2lss1tau || cat_3l1tau ){ // 1-tau VLoose WP

            if( isMC && (*_recotauh_sel_isGenMatched)[0] ) {

                TString wp;
                if((*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]==1) wp = "VLoose";
                else wp = "VVLoose";

                _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp);
                _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
                _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

            }

            else{

                _tauSF_weight_v1 = 1.;
                _tauSF_weight_up_v1 = 0.;
                _tauSF_weight_down_v1 = 0.;

            }

            if(isMC){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                _tauSF_weight_tauNormUp_v1 = std::get<1>(tau_fakerate);
                _tauSF_weight_tauNormDown_v1 = std::get<2>(tau_fakerate);
                _tauSF_weight_tauShapeUp_v1 = std::get<3>(tau_fakerate);
                _tauSF_weight_tauShapeDown_v1 = std::get<4>(tau_fakerate);

            }

          }

          else if ( cat_1l1tau ){ // 1-tau Medium WP

            if( isMC && (*_recotauh_sel_isGenMatched)[0] ) {

                TString wp;
                if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]==1) wp = "Medium";
                else wp = "VVLoose";

                _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp);
                _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
                _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

            }

            else{

                _tauSF_weight_v1 = 1.;
                _tauSF_weight_up_v1 = 0.;
                _tauSF_weight_down_v1 = 0.;

            }

            if(isMC){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                _tauSF_weight_tauNormUp_v1 = std::get<1>(tau_fakerate);
                _tauSF_weight_tauNormDown_v1 = std::get<2>(tau_fakerate);
                _tauSF_weight_tauShapeUp_v1 = std::get<3>(tau_fakerate);
                _tauSF_weight_tauShapeDown_v1 = std::get<4>(tau_fakerate);

            }

          }

          else if ( cat_2los1tau ){ // 1-tau VTight WP

            if( isMC && (*_recotauh_sel_isGenMatched)[0] ) {

                TString wp;
                if((*_recotauh_sel_byVTightDeepTau2017v2p1VSjet)[0]==1) wp = "VTight";
                else wp = "VVLoose";

                _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp);
                _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
                _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

            }

            else{

                _tauSF_weight_v1 = 1.;
                _tauSF_weight_up_v1 = 0.;
                _tauSF_weight_down_v1 = 0.;

            }

            if(isMC){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                _tauSF_weight_tauNormUp_v1 = std::get<1>(tau_fakerate);
                _tauSF_weight_tauNormDown_v1 = std::get<2>(tau_fakerate);
                _tauSF_weight_tauShapeUp_v1 = std::get<3>(tau_fakerate);
                _tauSF_weight_tauShapeDown_v1 = std::get<4>(tau_fakerate);

            }

          }

          else if ( cat_2tau ){ // 2-tau Loose WP

            if( isMC && ( (*_recotauh_sel_isGenMatched)[0] || (*_recotauh_sel_isGenMatched)[1] ) ) {

              if( (*_recotauh_sel_isGenMatched)[0] ) {

                  TString wp;
                  if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[0]==1) wp = "Loose";
                  else wp = "VVLoose";

                  _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp);
                  _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
                  _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

              }

              if( (*_recotauh_sel_isGenMatched)[1] ) {

                  TString wp;
                  if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[1]==1) wp = "Loose";
                  else wp = "VVLoose";

                  _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp);
                  _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp,+1);
                  _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp,-1);

              }

            }

            else{

                _tauSF_weight_v1 = 1.;
                _tauSF_weight_up_v1 = 0.;
                _tauSF_weight_down_v1 = 0.;

            }

            if(isMC){

                std::tuple<float, float, float, float, float> tau_fakerate1 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                std::tuple<float, float, float, float, float> tau_fakerate2 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

                _tauSF_weight_tauNormUp_v1 = std::get<1>(tau_fakerate1);
                _tauSF_weight_tauNormDown_v1 = std::get<2>(tau_fakerate1);
                _tauSF_weight_tauShapeUp_v1 = std::get<3>(tau_fakerate1);
                _tauSF_weight_tauShapeDown_v1 = std::get<4>(tau_fakerate1);

                _tauSF_weight_tauNormUp_v1 *= std::get<1>(tau_fakerate2);
                _tauSF_weight_tauNormDown_v1 *= std::get<2>(tau_fakerate2);
                _tauSF_weight_tauShapeUp_v1 *= std::get<3>(tau_fakerate2);
                _tauSF_weight_tauShapeDown_v1 *= std::get<4>(tau_fakerate2);

            }

          }

          else if ( cat_1l2tau || cat_2l2tau ){ // 2-tau Medium WP

            if( isMC && ((*_recotauh_sel_isGenMatched)[0] || (*_recotauh_sel_isGenMatched)[1]) ) {

              if( (*_recotauh_sel_isGenMatched)[0] ) {

                  TString wp;
                  if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]==1) wp = "Medium";
                  else wp = "VVLoose";

                  _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp);
                  _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
                  _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

              }

              if( (*_recotauh_sel_isGenMatched)[1] ) {

                  TString wp;
                  if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[1]==1) wp = "Medium";
                  else wp = "VVLoose";

                  _tauSF_weight_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp);
                  _tauSF_weight_up_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp,+1);
                  _tauSF_weight_down_v1 *= get_tauSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp,-1);

              }

            }

            else{

                _tauSF_weight_v1 = 1.;
                _tauSF_weight_up_v1 = 0.;
                _tauSF_weight_down_v1 = 0.;

            }

            if(isMC){

                std::tuple<float, float, float, float, float> tau_fakerate1 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                std::tuple<float, float, float, float, float> tau_fakerate2 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

                _tauSF_weight_tauNormUp_v1 = std::get<1>(tau_fakerate1);
                _tauSF_weight_tauNormDown_v1 = std::get<2>(tau_fakerate1);
                _tauSF_weight_tauShapeUp_v1 = std::get<3>(tau_fakerate1);
                _tauSF_weight_tauShapeDown_v1 = std::get<4>(tau_fakerate1);

                _tauSF_weight_tauNormUp_v1 *= std::get<1>(tau_fakerate2);
                _tauSF_weight_tauNormDown_v1 *= std::get<2>(tau_fakerate2);
                _tauSF_weight_tauShapeUp_v1 *= std::get<3>(tau_fakerate2);
                _tauSF_weight_tauShapeDown_v1 *= std::get<4>(tau_fakerate2);

            }

          }

        }

        ////////////////////////////////////////////////////////////
        /////////////////////// FAKE WEIGHTS ///////////////////////
        ////////////////////////////////////////////////////////////

        if( _category == 1020 ){ // 2 tau WP Loose, 0 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[1]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

                float fakerate_nominal = std::get<0>(tau_fakerate);

                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                if(isMC){

                  float tauNormUp = std::get<1>(tau_fakerate);
                  float tauNormDown = std::get<2>(tau_fakerate);
                  float tauShapeUp = std::get<3>(tau_fakerate);
                  float tauShapeDown = std::get<4>(tau_fakerate);

                }

                n_fake++;

            }


            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }
             
        }

        else if( _category == 2020 ){ // 1 tau WP Medium, 1 lepton

            int n_fake = 0;

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(abs((*_recolep_sel_pdg)[0])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);

                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[0])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

                

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }

        }

        else if( _category == 2120 ){ // 2 tau WP Medium, 1 lepton

            int n_fake = 0;

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[1]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(abs((*_recolep_sel_pdg)[0])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[0])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }
             
        }

        else if( _category == 3120 ){ // 1 tau WP Vloose, 2 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_VLoose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(abs((*_recolep_sel_pdg)[0])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[0])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(abs((*_recolep_sel_pdg)[1])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[1])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }

        }

        else if( _category == 3220 ){ // 1 tau WP VTight, 2 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byVTightDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_VTight(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(abs((*_recolep_sel_pdg)[0])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[0])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(abs((*_recolep_sel_pdg)[1])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[1])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }

        }

        else if( _category == 3320 ){ // 2 tau WP Medium, 2 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[1]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(abs((*_recolep_sel_pdg)[0])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[0])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(abs((*_recolep_sel_pdg)[1])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[1])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }

        }

        else if( _category == 4120 ){ // 1 tau WP VLoose, 3 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_VLoose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(abs((*_recolep_sel_pdg)[0])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[0])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(abs((*_recolep_sel_pdg)[1])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[1])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[2]){

                if(abs((*_recolep_sel_pdg)[2])==11){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_ele(_year, (*_recolep_sel_conept)[2], (*_recolep_sel_eta)[2]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(abs((*_recolep_sel_pdg)[2])==13){

                    std::tuple<float, float, float, float, float, float, float, float, float> lep_fakerate  = get_fakerate_muon(_year, (*_recolep_sel_conept)[2], (*_recolep_sel_eta)[2]);
                    
                    float fakerate_nominal  = std::get<0>(lep_fakerate);
                    float fakerate_up       = std::get<1>(lep_fakerate);
                    float fakerate_down     = std::get<2>(lep_fakerate);
                    float fakerate_pt1      = std::get<3>(lep_fakerate);
                    float fakerate_pt2      = std::get<4>(lep_fakerate);
                    float fakerate_be1      = std::get<5>(lep_fakerate);
                    float fakerate_be2      = std::get<6>(lep_fakerate);
                    float fakerate_QCD      = std::get<7>(lep_fakerate);
                    float fakerate_TT       = std::get<8>(lep_fakerate);

                    _event_weight_ttH_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v1  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v1 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v1 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v1 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v1 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v1 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v1 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v1 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v1 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v1 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v1 *= fakerate_be2/(1-fakerate_be2); 

                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v1 *= -1;

                _event_weight_ttH_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v1 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v1 *= -1;

                _event_weight_ttH_ele_up_v1 *= -1;
                _event_weight_ttH_ele_down_v1 *= -1;
                _event_weight_ttH_ele_pt1_v1 *= -1;
                _event_weight_ttH_ele_pt2_v1 *= -1;
                _event_weight_ttH_ele_be1_v1 *= -1;
                _event_weight_ttH_ele_be2_v1 *= -1;

                _event_weight_ttH_mu_up_v1 *= -1;
                _event_weight_ttH_mu_down_v1 *= -1;
                _event_weight_ttH_mu_pt1_v1 *= -1;
                _event_weight_ttH_mu_pt2_v1 *= -1;
                _event_weight_ttH_mu_be1_v1 *= -1;
                _event_weight_ttH_mu_be2_v1 *= -1;

            }

        }

        ////////////////////////////////////////////////////////////
        /////////////////////// FLIP WEIGHTS ///////////////////////
        ////////////////////////////////////////////////////////////

        if( _category == 2030 ){ // 1l1tau flip

            if( abs((*_recolep_sel_pdg)[0])==11 )
                _event_weight_ttH_v1 = get_fliprate(_year,(*_recolep_sel_conept)[0],(*_recolep_sel_eta)[0]);

            else
                _event_weight_ttH_v1 = 0;

        }
      
        else if( _category == 3130 ){ // 2lss1tau flip

            if( abs((*_recolep_sel_pdg)[0])==11 && ((*_recolep_sel_charge)[0]*((*_recotauh_sel_charge)[0])>0) )
                _event_weight_ttH_v1 = get_fliprate(_year,(*_recolep_sel_conept)[0],(*_recolep_sel_eta)[0]);
      
            else if( abs((*_recolep_sel_pdg)[1])==11 && ((*_recolep_sel_charge)[1]*((*_recotauh_sel_charge)[0])>0) )
                _event_weight_ttH_v1 = get_fliprate(_year,(*_recolep_sel_conept)[1],(*_recolep_sel_eta)[1]);

            else
                _event_weight_ttH_v1 = 0;

        }

      	/////////////////////////////////////////////////////////////

        tree_new->Fill();

		}

		f_new->cd();
    tree_new->Write();

	}

	f_new->Close();

  return;

}


void test(){

  	vector<TString> filein;
  	//filein.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_BDT/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWW_BDT.root");
  	//filein.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu.root");
    //filein.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu.root");
    filein.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root");
    filein.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root");
    filein.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root");

  	vector<TString> fileout;
  	//fileout.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_BDT/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWW_BDT_SFs.root");
  	//fileout.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTW_SFs_test.root");
    //fileout.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTW_SFs_test.root");
    fileout.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_datacards/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR_v1.root");
    fileout.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_datacards/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR_v1.root");
    fileout.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_datacards/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR_v1.root");

  	vector<TString> tree;
  	tree.push_back("HTauTauTree_2lss1tau_SR");
  	//tree.push_back("HTauTauTree_2lss1tau_fake");
  	//tree.push_back("HTauTauTree_2lss1tau_flip");
  	//tree.push_back("HTauTauTree_2tau_SR");
    //tree.push_back("HTauTauTree_2tau_fake");
  	//tree.push_back("HTauTauTree_1l1tau_SR");
    //tree.push_back("HTauTauTree_1l1tau_fake");
  	//tree.push_back("HTauTauTree_1l2tau_SR");
  	//tree.push_back("HTauTauTree_1l2tau_fake");
  	//tree.push_back("HTauTauTree_2los1tau_SR");
  	//tree.push_back("HTauTauTree_2los1tau_fake");
  	//tree.push_back("HTauTauTree_2l2tau_SR");
  	//tree.push_back("HTauTauTree_2l2tau_fake");
  	//tree.push_back("HTauTauTree_3l1tau_SR");
  	//tree.push_back("HTauTauTree_3l1tau_fake");

  	for (unsigned int i_file = 0; i_file<filein.size(); i_file++){
  		cout<<filein[i_file]<<endl;
    	add_SFs(filein[i_file],fileout[i_file],tree,true);  
  	}  

}