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

using namespace std;

void add_SFs(TString filein, TString fileout, vector<TString> treename, bool isMC, int year){

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

      float _trigger_weight_ee_v4;
      float _trigger_weight_ee_up_v4;
      float _trigger_weight_ee_down_v4;

      float _trigger_weight_em_v4;
      float _trigger_weight_em_up_v4;
      float _trigger_weight_em_down_v4;

      float _trigger_weight_mm_v4;
      float _trigger_weight_mm_up_v4;
      float _trigger_weight_mm_down_v4;

      float _leptonID_weight_mloose_v4;
      float _leptonID_weight_mloose_up_v4;
      float _leptonID_weight_mloose_down_v4;

      float _leptonID_weight_mtight_v4;
      float _leptonID_weight_mtight_up_v4;
      float _leptonID_weight_mtight_down_v4;

      float _leptonID_weight_eloose_v4;
      float _leptonID_weight_eloose_up_v4;
      float _leptonID_weight_eloose_down_v4;

      float _leptonID_weight_etight_v4;
      float _leptonID_weight_etight_up_v4;
      float _leptonID_weight_etight_down_v4;

      tree_new->Branch("trigger_weight_ee_v4",            &_trigger_weight_ee_v4,             "trigger_weight_ee_v4/F");
      tree_new->Branch("trigger_weight_ee_up_v4",         &_trigger_weight_ee_up_v4,          "trigger_weight_ee_up_v4/F");
      tree_new->Branch("trigger_weight_ee_down_v4",       &_trigger_weight_ee_down_v4,        "trigger_weight_ee_down_v4/F");

      tree_new->Branch("trigger_weight_em_v4",            &_trigger_weight_em_v4,             "trigger_weight_em_v4/F");
      tree_new->Branch("trigger_weight_em_up_v4",         &_trigger_weight_em_up_v4,          "trigger_weight_em_up_v4/F");
      tree_new->Branch("trigger_weight_em_down_v4",       &_trigger_weight_em_down_v4,        "trigger_weight_em_down_v4/F");

      tree_new->Branch("trigger_weight_mm_v4",            &_trigger_weight_mm_v4,             "trigger_weight_mm_v4/F");
      tree_new->Branch("trigger_weight_mm_up_v4",         &_trigger_weight_mm_up_v4,          "trigger_weight_mm_up_v4/F");
      tree_new->Branch("trigger_weight_mm_down_v4",       &_trigger_weight_mm_down_v4,        "trigger_weight_mm_down_v4/F");

      tree_new->Branch("leptonID_weight_mloose_v4",       &_leptonID_weight_mloose_v4,        "leptonID_weight_mloose_v4/F");
      tree_new->Branch("leptonID_weight_mloose_up_v4",    &_leptonID_weight_mloose_up_v4,     "leptonID_weight_mloose_up_v4/F");
      tree_new->Branch("leptonID_weight_mloose_down_v4",  &_leptonID_weight_mloose_down_v4,   "leptonID_weight_mloose_down_v4/F");

      tree_new->Branch("leptonID_weight_mtight_v4",       &_leptonID_weight_mtight_v4,        "leptonID_weight_mtight_v4/F");
      tree_new->Branch("leptonID_weight_mtight_up_v4",    &_leptonID_weight_mtight_up_v4,     "leptonID_weight_mtight_up_v4/F");
      tree_new->Branch("leptonID_weight_mtight_down_v4",  &_leptonID_weight_mtight_down_v4,   "leptonID_weight_mtight_down_v4/F");

      tree_new->Branch("leptonID_weight_eloose_v4",       &_leptonID_weight_eloose_v4,        "leptonID_weight_eloose_v4/F");
      tree_new->Branch("leptonID_weight_eloose_up_v4",    &_leptonID_weight_eloose_up_v4,     "leptonID_weight_eloose_up_v4/F");
      tree_new->Branch("leptonID_weight_eloose_down_v4",  &_leptonID_weight_eloose_down_v4,   "leptonID_weight_eloose_down_v4/F");

      tree_new->Branch("leptonID_weight_etight_v4",       &_leptonID_weight_etight_v4,        "leptonID_weight_etight_v4/F");
      tree_new->Branch("leptonID_weight_etight_up_v4",    &_leptonID_weight_etight_up_v4,     "leptonID_weight_etight_up_v4/F");
      tree_new->Branch("leptonID_weight_etight_down_v4",  &_leptonID_weight_etight_down_v4,   "leptonID_weight_etight_down_v4/F");


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

        _trigger_weight_ee_v4 = 0;
        _trigger_weight_ee_up_v4 = 0;
        _trigger_weight_ee_down_v4 = 0;

        _trigger_weight_em_v4 = 0;
        _trigger_weight_em_up_v4 = 0;
        _trigger_weight_em_down_v4 = 0;

        _trigger_weight_mm_v4 = 0;
        _trigger_weight_mm_up_v4 = 0;
        _trigger_weight_mm_down_v4 = 0;

        _leptonID_weight_mloose_v4 = 0;
        _leptonID_weight_mloose_up_v4 = 0;
        _leptonID_weight_mloose_down_v4 = 0;

        _leptonID_weight_mtight_v4 = 0;
        _leptonID_weight_mtight_up_v4 = 0;
        _leptonID_weight_mtight_down_v4 = 0;

        _leptonID_weight_eloose_v4 = 0;
        _leptonID_weight_eloose_up_v4 = 0;
        _leptonID_weight_eloose_down_v4 = 0;

        _leptonID_weight_etight_v4 = 0;
        _leptonID_weight_etight_up_v4 = 0;
        _leptonID_weight_etight_down_v4 = 0;

      	tree->GetEntry(i);

        if(i==(nentries-1)) cout<<"FINISHED!!!"<<endl;

        _trigger_weight_ee_v4 = 1;
        _trigger_weight_ee_up_v4 = 1;
        _trigger_weight_ee_down_v4 = 1;

        _trigger_weight_em_v4 = 1;
        _trigger_weight_em_up_v4 = 1;
        _trigger_weight_em_down_v4 = 1;

        _trigger_weight_mm_v4 = 1;
        _trigger_weight_mm_up_v4 = 1;
        _trigger_weight_mm_down_v4 = 1;

        _leptonID_weight_mloose_v4 = 1;
        _leptonID_weight_mloose_up_v4 = 1;
        _leptonID_weight_mloose_down_v4 = 1;

        _leptonID_weight_mtight_v4 = 1;
        _leptonID_weight_mtight_up_v4 = 1;
        _leptonID_weight_mtight_down_v4 = 1;

        _leptonID_weight_eloose_v4 = 1;
        _leptonID_weight_eloose_up_v4 = 1;
        _leptonID_weight_eloose_down_v4 = 1;

        _leptonID_weight_etight_v4 = 1;
        _leptonID_weight_etight_up_v4 = 1;
        _leptonID_weight_etight_down_v4 = 1;

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


        if ( cat_2lss1tau || cat_2los1tau || cat_2l2tau ) { // 2-lepton triggers

            if(fabs((*_recolep_sel_pdg)[0])==11 && fabs((*_recolep_sel_pdg)[1])==11){

              _trigger_weight_ee_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,0,_year);
              _trigger_weight_ee_up_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,+1,_year);
              _trigger_weight_ee_down_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,-1,_year);

            }

            else if( (fabs((*_recolep_sel_pdg)[0])==13 && fabs((*_recolep_sel_pdg)[1])==11) || (fabs((*_recolep_sel_pdg)[0])==11 && fabs((*_recolep_sel_pdg)[1])==13) ) {

              _trigger_weight_em_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,0,_year);
              _trigger_weight_em_up_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,+1,_year);
              _trigger_weight_em_down_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,-1,_year);

            }

            else if(fabs((*_recolep_sel_pdg)[0])==13 && fabs((*_recolep_sel_pdg)[1])==13){

              _trigger_weight_mm_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,0,_year);
              _trigger_weight_mm_up_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,+1,_year);
              _trigger_weight_mm_down_v4 *= get_triggerSF_leptonic((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],2,-1,_year);

            }

        }


      	//////////////////////////////
      	//////// LEPTON ID SFS ///////
      	//////////////////////////////

      	if ( cat_1l1tau || cat_1l2tau ){ // 1 lepton no tight charge

      			if((*_recolep_sel_ismvasel)[0]){

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1);  

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

            }

      	}

      	else if ( cat_2lss1tau ){ // 2 leptons tight charge

      		  if((*_recolep_sel_ismvasel)[0]){

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,-1);

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2,-1);

              }

            }

      			if((*_recolep_sel_ismvasel)[1]){

              if(fabs((*_recolep_sel_pdg)[1])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[1])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[1])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[1])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

            }

        }

      	else if ( cat_2l2tau || cat_2los1tau ){ // 2 leptons not tight charge

      		  if((*_recolep_sel_ismvasel)[0]){

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

            }

      			if((*_recolep_sel_ismvasel)[1]){

              if(fabs((*_recolep_sel_pdg)[1])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1);

              }

              else if(fabs((*_recolep_sel_pdg)[1])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1);

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[1])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1);

              }

              else if(fabs((*_recolep_sel_pdg)[1])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1); 

              }

            }

        }

        else if ( cat_3l1tau ){ // 3 leptons no tight charge

      		  if((*_recolep_sel_ismvasel)[0]){

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1);

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1); 

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[0])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],3,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[0])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3,-1);

              }

            }

      			if((*_recolep_sel_ismvasel)[1]){

              if(fabs((*_recolep_sel_pdg)[1])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[1])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[1])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }

              else if(fabs((*_recolep_sel_pdg)[1])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2,-1); 

              }


            }

        		if((*_recolep_sel_ismvasel)[2]){

              if(fabs((*_recolep_sel_pdg)[2])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,-1); 

                _leptonID_weight_mtight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0); 
                _leptonID_weight_mtight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,+1); 
                _leptonID_weight_mtight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,-1);

              }

              else if(fabs((*_recolep_sel_pdg)[2])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,-1); 

                _leptonID_weight_etight_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0); 
                _leptonID_weight_etight_up_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,+1); 
                _leptonID_weight_etight_down_v4 *= get_LooseToTight_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,-1);

              }

            }

      			else{

              if(fabs((*_recolep_sel_pdg)[2])==13){

                _leptonID_weight_mloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0); 
                _leptonID_weight_mloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,+1); 
                _leptonID_weight_mloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,-1);

              }

              else if(fabs((*_recolep_sel_pdg)[2])==11){

                _leptonID_weight_eloose_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,0); 
                _leptonID_weight_eloose_up_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,+1); 
                _leptonID_weight_eloose_down_v4 *= get_RecoToLoose_leptonSF(_year,(*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],3,-1); 

              }

            }

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


void loadsample(TString sample, int year, TString type, bool ismc){

    cout<<"Processing SR sample: "<<sample;

    TString year_s = std::to_string(year);

    TString filein;
    filein = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR_SF_v3.root";

    TString fileout;
    fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR_SF_v4.root";

    vector<TString> tree;
    tree.push_back("HTauTauTree_2lss1tau_SR");

    add_SFs(filein,fileout,tree,ismc,year);


}

void test_SR_2016(){

    //loadsample("Oct19v1_MC_2016_ttHJetToNonbb",2016,"ttH",true);
    loadsample("Oct19v1_MC_2016_ttH_ctcvcp",2016,"ttH",true);
    loadsample("Oct19v1_MC_2016_THQ_ctcvcp",2016,"ttH",true);
    loadsample("Oct19v1_MC_2016_THW_ctcvcp",2016,"ttH",true);

    loadsample("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2",2016,"ttV",true);
    loadsample("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",2016,"ttV",true);
    loadsample("Oct19v1_MC_2016_TTZToLL_M-1to10",2016,"ttV",true);
    loadsample("Oct19v1_MC_2016_TTWJetsToLNu",2016,"ttV",true);
    loadsample("Oct19v1_MC_2016_TTWW",2016,"ttV",true);

    loadsample("Oct19v1_MC_2016_WWW",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WWZ",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WZZ",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_ZZZ",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WZG",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WGToLNuG_ext1",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WGToLNuG_ext2",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WGToLNuG_ext3",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_ZGTo2LG",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_TGJets_leptonDecays",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_TTGJets",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_TTGJets_ext1",2016,"Rares",true);
    loadsample("Oct19v2_MC_2016_tZq_ll",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_tZq_ll_PS",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_WpWpJJ",2016,"Rares",true);
    loadsample("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_TTTT",2016,"Rares",true);
    loadsample("Oct19v1_MC_2016_DYJetsToLL_M-10to50",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_DYJetsToLL_M-50",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_WJetsToLNu_ext2",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_WJetsToLNu",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_WWTo2L2Nu",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_WZTo3LNu",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_ZZTo4L",2016,"EWK",true);
    loadsample("Oct19v1_MC_2016_ST_s-channel",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_s-channel_PS",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_t-channel_top",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_t-channel_antitop",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_t-channel_antitop_PS",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_tW_top",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_tW_antitop",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_ST_tWll",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_TTJets_DiLept_ext1",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_TTJets_DiLept",2016,"ttbar",true);
    loadsample("Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_TTJets_SingleLeptFromT",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_TTJets_SingleLeptFromTbar",2016,"ttbar",true);
    loadsample("Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1",2016,"ttbar",true);
    loadsample("Oct19v1_MC_2016_GluGluHToTauTau",2016,"ggH",true);
    loadsample("Oct19v1_MC_2016_GluGluHToZZTo4L",2016,"ggH",true);
    loadsample("Oct19v1_MC_2016_GluGluHToWWToLNuQQ",2016,"ggH",true);
    loadsample("Oct19v1_MC_2016_GluGluHToWWTo2L2Nu",2016,"ggH",true);
    loadsample("Oct19v1_MC_2016_GluGluHToMuMu",2016,"ggH",true);
    loadsample("Oct19v1_MC_2016_GluGluHToBB",2016,"ggH",true);
    loadsample("Oct19v6_MC_2016_GluGluHToBB_ext1",2016,"ggH",true);
    loadsample("Oct19v1_MC_2016_GluGluHToGG",2016,"ggH",true);
    loadsample("Oct19v2_MC_2016_VBFHToTauTau",2016,"VBF",true);
    loadsample("Oct19v2_MC_2016_VBF_HToZZTo4L",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VBFHToWWToLNuQQ",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VBFHToWWTo2L2Nu",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VBFHToMuMu",2016,"VBF",true);
    loadsample("Oct19v3_MC_2016_VBFHToBB",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VBFHToBB_ext1",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VBFHToGG_ext1",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VBFHToGG_ext2",2016,"VBF",true);
    loadsample("Oct19v1_MC_2016_VHToNonbb",2016,"VH",true);
    loadsample("Oct19v1_MC_2016_ZH_HToBB_ZToLL",2016,"VH",true);
    loadsample("Oct19v1_MC_2016_ZHToTauTau",2016,"VH",true);
    loadsample("Oct19v1_MC_2016_TTWH",2016,"ttVH",true);
    loadsample("Oct19v2_MC_2016_TTZH",2016,"ttVH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box",2016,"HH",true);
    loadsample("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_1",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3",2016,"HH",true);
    loadsample("Oct19v4_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_4",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_5",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_7",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8",2016,"HH",true);
    loadsample("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_11",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo2B2Tau_node_9",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12",2016,"HH",true);
    loadsample("Oct19v3_MC_2016_GluGluToHHTo2B2Tau_node_13",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_8",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_10",2016,"HH",true);
    loadsample("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_11",2016,"HH",true);
    loadsample("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12",2016,"HH",true);

}

void test_SR_2017(){

    loadsample("Oct19v1_MC_2017_ttHJetToNonbb",2017,"ttH",true);
    loadsample("Oct19v1_MC_2017_THQ_ctcvcp",2017,"ttH",true);
    loadsample("Oct19v3_MC_2017_THW_ctcvcp",2017,"ttH",true);
    loadsample("Oct19v1_MC_2017_TTH_ctcvcp",2017,"ttH",true);

    loadsample("Oct19v1_MC_2017_TTZToLLNuNu_M-10",2017,"ttV",true);
    loadsample("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",2017,"ttV",true);
    loadsample("Oct19v1_MC_2017_TTZToLL_M-1to10",2017,"ttV",true);
    loadsample("Oct19v1_MC_2017_TTWJetsToLNu",2017,"ttV",true);
    loadsample("Oct19v1_MC_2017_TTWJetsToLNu_PS",2017,"ttV",true);
    loadsample("Oct19v1_MC_2017_TTWW",2017,"ttV",true);

    loadsample("Oct19v1_MC_2017_WWW",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_WWZ",2017,"Rares",true);
    loadsample("Oct19v2_MC_2017_WZZ",2017,"Rares",true);
    loadsample("Oct19v2_MC_2017_ZZZ",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_WZG",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_WGToLNuG",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_ZGToLLG",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_TGJets",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_TTGJets",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_TTGJets_ext1",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_tZq_ll",2017,"Rares",true);
    loadsample("Oct19v2_MC_2017_WpWpJJ",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering",2017,"Rares",true);
    loadsample("Oct19v1_MC_2017_TTTT",2017,"Rares",true);
    //loadsample("Oct19v1_MC_2017_TTTT_PS",2017,"Rares",true);
    
    loadsample("Oct19v1_MC_2017_DYJetsToLL_M-10to50",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_DYJetsToLL_M-50",2017,"EWK",true);
    loadsample("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",2017,"EWK",true);
    loadsample("Oct19v2_MC_2017_WJetsToLNu",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_WJetsToLNu_ext1",2017,"EWK",true);
    loadsample("Oct19v2_MC_2017_WWTo2L2Nu",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_WWTo2L2Nu_ext1",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_WZTo3LNu",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_ZZTo4L",2017,"EWK",true);
    loadsample("Oct19v1_MC_2017_ZZTo4L_ext1",2017,"EWK",true);
    loadsample("Oct19v2_MC_2017_ZZTo4L_ext2",2017,"EWK",true);

    loadsample("Oct19v1_MC_2017_ST_s-channel",2017,"ttbar",true);
    loadsample("Oct19v2_MC_2017_ST_s-channel_PS",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_ST_t-channel_top",2017,"ttbar",true);
    loadsample("Oct19v2_MC_2017_ST_t-channel_top_PS",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_ST_t-channel_antitop",2017,"ttbar",true);
    loadsample("Oct19v2_MC_2017_ST_t-channel_antitop_PS",2017,"ttbar",true);
    loadsample("Oct19v3_MC_2017_ST_tW_top",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_ST_tW_top_PS",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_ST_tW_antitop",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_ST_tW_antitop_PS",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_ST_tWll",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_TTJets_DiLept",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_TTJets_SingleLeptFromT",2017,"ttbar",true);
    loadsample("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar",2017,"ttbar",true);

    loadsample("Oct19v1_MC_2017_GluGluHToTauTau",2017,"ggH",true);
    loadsample("Oct19v3_MC_2017_GluGluHToTauTau_ext1",2017,"ggH",true);
    loadsample("Oct19v1_MC_2017_GluGluHToZZTo4L_ext1",2017,"ggH",true);
    loadsample("Oct19v2_MC_2017_GluGluHToZZTo4L_ext3",2017,"ggH",true);
    loadsample("Oct19v1_MC_2017_GluGluHToZZTo4L_ext4",2017,"ggH",true);
    loadsample("Oct19v2_MC_2017_GluGluHToZZTo2L2Q",2017,"ggH",true);
    loadsample("Oct19v1_MC_2017_GluGluHToWWToLNuQQ",2017,"ggH",true);
    loadsample("Oct19v1_MC_2017_GluGluHToWWTo2L2Nu",2017,"ggH",true);
    loadsample("Oct19v3_MC_2017_GluGluHToMuMu",2017,"ggH",true);
    loadsample("Oct19v1_MC_2017_GluGluHToMuMu_ext1",2017,"ggH",true);
    loadsample("Oct19v2_MC_2017_GluGluHToBB",2017,"ggH",true);
    loadsample("Oct19v3_MC_2017_GluGluHToGG",2017,"ggH",true);

    loadsample("Oct19v1_MC_2017_VBFHToTauTau",2017,"VBF",true);
    loadsample("Oct19v2_MC_2017_VBF_HToZZTo4L_ext2",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBF_HToZZTo4L_ext1",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBF_HToZZTo4L",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBFHToWWToLNuQQ",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBFHToWWTo2L2Nu",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBFHToMuMu",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBFHToBB",2017,"VBF",true);
    loadsample("Oct19v1_MC_2017_VBFHToGG",2017,"VBF",true);
    loadsample("Oct19v2_MC_2017_VBFHToGG_PS",2017,"VBF",true);

    loadsample("Oct19v1_MC_2017_VHToNonbb",2017,"VH",true);
    loadsample("Oct19v1_MC_2017_ZH_HToBB_ZToLL",2017,"VH",true);
    loadsample("Oct19v1_MC_2017_ZHToTauTau",2017,"VH",true);

    loadsample("Oct19v4_MC_2017_TTWH",2017,"ttVH",true);
    loadsample("Oct19v1_MC_2017_TTZH",2017,"ttVH",true);

    loadsample("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_7",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9",2017,"HH",true);
    loadsample("Oct19v4_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo4Tau_node_7",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_3",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_7",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_12",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_SM",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo4V_node_2",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_3",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_4",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_5",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_6",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_7",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_8",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_9",2017,"HH",true);
    loadsample("Oct19v1_MC_2017_GluGluToHHTo4V_node_10",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo4V_node_11",2017,"HH",true);
    loadsample("Oct19v2_MC_2017_GluGluToHHTo4V_node_12",2017,"HH",true);

}


void test_SR_2018(){

    loadsample("Oct19v2_MC_2018_ttHJetToNonbb",2018,"ttH",true);
    loadsample("Oct19v2_MC_2018_TTH_ctcvcp",2018,"ttH",true);
    loadsample("Oct19v1_MC_2018_THQ_ctcvcp",2018,"ttH",true);
    loadsample("Oct19v1_MC_2018_THW_ctcvcp",2018,"ttH",true);

    loadsample("Oct19v1_MC_2018_TTZToLLNuNu_M-10",2018,"ttV",true);
    loadsample("Oct19v1_MC_2018_TTZToLL_M-1to10",2018,"ttV",true);
    loadsample("Oct19v1_MC_2018_TTWJetsToLNu",2018,"ttV",true);
    loadsample("Oct19v1_MC_2018_TTWW_ext1",2018,"ttV",true);
    loadsample("Oct19v1_MC_2018_TTWW_ext2",2018,"ttV",true);

    loadsample("Oct19v2_MC_2018_WWW",2018,"Rares",true);
    loadsample("Oct19v2_MC_2018_WWZ",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_WZZ",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_ZZZ",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_WZG",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_WGToLNuG",2018,"Rares",true);
    loadsample("Oct19v2_MC_2018_ZGToLLG",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_TGJets",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_TTGJets",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_tZq_ll",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_WpWpJJ",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering",2018,"Rares",true);
    loadsample("Oct19v1_MC_2018_TTTT",2018,"Rares",true);
    
    loadsample("Oct19v3_MC_2018_DYJetsToLL_M-10to50",2018,"EWK",true);
    loadsample("Oct19v2_MC_2018_DYJetsToLL_M-50",2018,"EWK",true);
    loadsample("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",2018,"EWK",true);
    loadsample("Oct19v2_MC_2018_WJetsToLNu",2018,"EWK",true);
    loadsample("Oct19v3_MC_2018_WWTo2L2Nu",2018,"EWK",true);
    loadsample("Oct19v1_MC_2018_WZTo3LNu",2018,"EWK",true);
    loadsample("Oct19v2_MC_2018_WZTo3LNu_ext1",2018,"EWK",true);
    loadsample("Oct19v2_MC_2018_ZZTo4L",2018,"EWK",true);
    loadsample("Oct19v4_MC_2018_ZZTo4L_ext2",2018,"EWK",true);

    loadsample("Oct19v1_MC_2018_ST_s-channel",2018,"ttbar",true);
    loadsample("Oct19v2_MC_2018_ST_t-channel_top",2018,"ttbar",true);
    loadsample("Oct19v3_MC_2018_ST_t-channel_antitop",2018,"ttbar",true);
    loadsample("Oct19v3_MC_2018_ST_tW_top",2018,"ttbar",true);
    loadsample("Oct19v1_MC_2018_ST_tW_antitop",2018,"ttbar",true);
    loadsample("Oct19v1_MC_2018_ST_tWll",2018,"ttbar",true);
    loadsample("Oct19v1_MC_2018_TTJets_DiLept",2018,"ttbar",true);
    loadsample("Oct19v1_MC_2018_TTJets_SingleLeptFromT",2018,"ttbar",true);
    loadsample("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar",2018,"ttbar",true);

    loadsample("Oct19v2_MC_2018_GluGluHToTauTau",2018,"ggH",true);
    loadsample("Oct19v1_MC_2018_GluGluHToZZTo4L",2018,"ggH",true);
    loadsample("Oct19v2_MC_2018_GluGluHToZZTo2L2Q",2018,"ggH",true);
    loadsample("Oct19v1_MC_2018_GluGluHToWWToLNuQQ",2018,"ggH",true);
    loadsample("Oct19v2_MC_2018_GluGluHToWWTo2L2Nu",2018,"ggH",true);
    loadsample("Oct19v1_MC_2018_GluGluHToMuMu",2018,"ggH",true);
    loadsample("Oct19v2_MC_2018_GluGluHToMuMu_ext1",2018,"ggH",true);
    loadsample("Oct19v1_MC_2018_GluGluHToBB",2018,"ggH",true);
    loadsample("Oct19v1_MC_2018_GluGluHToGG",2018,"ggH",true);

    loadsample("Oct19v1_MC_2018_VBFHToTauTau",2018,"VBF",true);
    loadsample("Oct19v2_MC_2018_VBF_HToZZTo4L",2018,"VBF",true);
    loadsample("Oct19v2_MC_2018_VBFHToWWToLNuQQ",2018,"VBF",true);
    loadsample("Oct19v1_MC_2018_VBFHToWWTo2L2Nu",2018,"VBF",true);
    loadsample("Oct19v1_MC_2018_VBFHToMuMu",2018,"VBF",true);
    loadsample("Oct19v2_MC_2018_VBFHToBB",2018,"VBF",true);
    loadsample("Oct19v2_MC_2018_VBFHToGG",2018,"VBF",true);

    loadsample("Oct19v2_MC_2018_VHToNonbb",2018,"VH",true);
    loadsample("Oct19v1_MC_2018_ZH_HToBB_ZToLL",2018,"VH",true);
    loadsample("Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1",2018,"VH",true);
    loadsample("Oct19v2_MC_2018_ZHToTauTau",2018,"VH",true);

    loadsample("Oct19v1_MC_2018_TTWH",2018,"ttVH",true);
    loadsample("Oct19v2_MC_2018_TTZH",2018,"ttVH",true);

    loadsample("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM",2018,"HH",true);
    loadsample("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_2",2018,"HH",true);
    loadsample("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_3",2018,"HH",true);
    loadsample("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_4",2018,"HH",true);
    loadsample("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_5",2018,"HH",true);
    loadsample("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_6",2018,"HH",true);
    loadsample("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_7",2018,"HH",true);
    loadsample("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_8",2018,"HH",true);
    loadsample("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_9",2018,"HH",true);
    loadsample("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_10",2018,"HH",true);
    loadsample("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_11",2018,"HH",true);

}