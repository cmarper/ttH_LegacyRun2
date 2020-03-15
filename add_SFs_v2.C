#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>
#include <TH2F.h>

#include "headers/fakerateSF_v3.cc"
#include "headers/fliprateSF_v2.cc"

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

      float _event_weight_ttH_v2;

      float _event_weight_ttH_ele_up_v2;
      float _event_weight_ttH_ele_down_v2;
      float _event_weight_ttH_ele_pt1_v2;
      float _event_weight_ttH_ele_pt2_v2;
      float _event_weight_ttH_ele_be1_v2;
      float _event_weight_ttH_ele_be2_v2;

      float _event_weight_ttH_mu_up_v2;
      float _event_weight_ttH_mu_down_v2;
      float _event_weight_ttH_mu_pt1_v2;
      float _event_weight_ttH_mu_pt2_v2;
      float _event_weight_ttH_mu_be1_v2;
      float _event_weight_ttH_mu_be2_v2;

      float _event_weight_ttH_FR_QCD_MC_v2;
      float _event_weight_ttH_FR_TT_MC_v2;
      float _event_weight_ttH_ele_FR_QCD_MC_v2;
      float _event_weight_ttH_ele_FR_TT_MC_v2;
      float _event_weight_ttH_mu_FR_QCD_MC_v2;
      float _event_weight_ttH_mu_FR_TT_MC_v2;

      tree_new->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");

      tree_new->Branch("event_weight_ttH_ele_up_v2",&_event_weight_ttH_ele_up_v2,"event_weight_ttH_ele_up_v2/F");
      tree_new->Branch("event_weight_ttH_ele_down_v2",&_event_weight_ttH_ele_down_v2,"event_weight_ttH_ele_down_v2/F");
      tree_new->Branch("event_weight_ttH_ele_pt1_v2",&_event_weight_ttH_ele_pt1_v2,"event_weight_ttH_ele_pt1_v2/F");
      tree_new->Branch("event_weight_ttH_ele_pt2_v2",&_event_weight_ttH_ele_pt2_v2,"event_weight_ttH_ele_pt2_v2/F");
      tree_new->Branch("event_weight_ttH_ele_be1_v2",&_event_weight_ttH_ele_be1_v2,"event_weight_ttH_ele_be1_v2/F");
      tree_new->Branch("event_weight_ttH_ele_be2_v2",&_event_weight_ttH_ele_be2_v2,"event_weight_ttH_ele_be2_v2/F");

      tree_new->Branch("event_weight_ttH_mu_up_v2",&_event_weight_ttH_mu_up_v2,"event_weight_ttH_mu_up_v2/F");
      tree_new->Branch("event_weight_ttH_mu_down_v2",&_event_weight_ttH_mu_down_v2,"event_weight_ttH_mu_down_v2/F");
      tree_new->Branch("event_weight_ttH_mu_pt1_v2",&_event_weight_ttH_mu_pt1_v2,"event_weight_ttH_mu_pt1_v2/F");
      tree_new->Branch("event_weight_ttH_mu_pt2_v2",&_event_weight_ttH_mu_pt2_v2,"event_weight_ttH_mu_pt2_v2/F");
      tree_new->Branch("event_weight_ttH_mu_be1_v2",&_event_weight_ttH_mu_be1_v2,"event_weight_ttH_mu_be1_v2/F");
      tree_new->Branch("event_weight_ttH_mu_be2_v2",&_event_weight_ttH_mu_be2_v2,"event_weight_ttH_mu_be2_v2/F");

      tree_new->Branch("event_weight_ttH_FR_QCD_MC_v2",&_event_weight_ttH_FR_QCD_MC_v2,"event_weight_ttH_FR_QCD_MC_v2/F");
      tree_new->Branch("event_weight_ttH_FR_TT_MC_v2",&_event_weight_ttH_FR_TT_MC_v2,"event_weight_ttH_FR_TT_MC_v2/F");
      tree_new->Branch("event_weight_ttH_ele_FR_QCD_MC_v2",&_event_weight_ttH_ele_FR_QCD_MC_v2,"event_weight_ttH_ele_FR_QCD_MC_v2/F");
      tree_new->Branch("event_weight_ttH_ele_FR_TT_MC_v2",&_event_weight_ttH_ele_FR_TT_MC_v2,"event_weight_ttH_ele_FR_TT_MC_v2/F");
      tree_new->Branch("event_weight_ttH_mu_FR_QCD_MC_v2",&_event_weight_ttH_mu_FR_QCD_MC_v2,"event_weight_ttH_mu_FR_QCD_MC_v2/F");
      tree_new->Branch("event_weight_ttH_mu_FR_TT_MC_v2",&_event_weight_ttH_mu_FR_TT_MC_v2,"event_weight_ttH_mu_FR_TT_MC_v2/F");

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

        _event_weight_ttH_v2 = 0;

        _event_weight_ttH_ele_up_v2 = 0;
        _event_weight_ttH_ele_down_v2 = 0;
        _event_weight_ttH_ele_pt1_v2 = 0;
        _event_weight_ttH_ele_pt2_v2 = 0;
        _event_weight_ttH_ele_be1_v2 = 0;
        _event_weight_ttH_ele_be2_v2 = 0;

        _event_weight_ttH_mu_up_v2 = 0;
        _event_weight_ttH_mu_down_v2 = 0;
        _event_weight_ttH_mu_pt1_v2 = 0;
        _event_weight_ttH_mu_pt2_v2 = 0;
        _event_weight_ttH_mu_be1_v2 = 0;
        _event_weight_ttH_mu_be2_v2 = 0;

        _event_weight_ttH_FR_QCD_MC_v2 = 0;
        _event_weight_ttH_FR_TT_MC_v2 = 0;
        _event_weight_ttH_ele_FR_QCD_MC_v2 = 0;
        _event_weight_ttH_ele_FR_TT_MC_v2 = 0;
        _event_weight_ttH_mu_FR_QCD_MC_v2 = 0;
        _event_weight_ttH_mu_FR_TT_MC_v2 = 0;

      	tree->GetEntry(i);

        if(i==(nentries-1)) cout<<"FINISHED!!!"<<endl;

        _event_weight_ttH_v2 = 1.;

        _event_weight_ttH_ele_up_v2 = 1.;
        _event_weight_ttH_ele_down_v2 = 1.;
        _event_weight_ttH_ele_pt1_v2 = 1.;
        _event_weight_ttH_ele_pt2_v2 = 1.;
        _event_weight_ttH_ele_be1_v2 = 1.;
        _event_weight_ttH_ele_be2_v2 = 1.;

        _event_weight_ttH_mu_up_v2 = 1.;
        _event_weight_ttH_mu_down_v2 = 1.;
        _event_weight_ttH_mu_pt1_v2 = 1.;
        _event_weight_ttH_mu_pt2_v2 = 1.;
        _event_weight_ttH_mu_be1_v2 = 1.;
        _event_weight_ttH_mu_be2_v2 = 1.;

        _event_weight_ttH_FR_QCD_MC_v2 = 1.;
        _event_weight_ttH_FR_TT_MC_v2 = 1.;
        _event_weight_ttH_ele_FR_QCD_MC_v2 = 1.;
        _event_weight_ttH_ele_FR_TT_MC_v2 = 1.;
        _event_weight_ttH_mu_FR_QCD_MC_v2 = 1.;
        _event_weight_ttH_mu_FR_TT_MC_v2 = 1.;

        // New variables

      	bool cat_2tau = 	  (_category == 1010 || _category==1020);
      	bool cat_1l1tau = 	(_category == 2010 || _category==2020 || _category==2030);
      	bool cat_1l2tau = 	(_category == 2110 || _category==2120);
      	bool cat_2lss1tau = (_category == 3110 || _category==3120 || _category==3130);
      	bool cat_2los1tau = (_category == 3210 || _category==3220);
      	bool cat_2l2tau = 	(_category == 3310 || _category==3320);
      	bool cat_3l1tau = 	(_category == 4110 || _category==4120);


        ///////////////////////////////
        ///////// FAKE WEIGHTS ////////
        ///////////////////////////////

        if( _category == 1020 ){ // 2 tau WP Loose, 0 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[1]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

                float fakerate_nominal = std::get<0>(tau_fakerate);

                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                if(isMC){

                  float tauNormUp = std::get<1>(tau_fakerate);
                  float tauNormDown = std::get<2>(tau_fakerate);
                  float tauShapeUp = std::get<3>(tau_fakerate);
                  float tauShapeDown = std::get<4>(tau_fakerate);

                }

                n_fake++;

            }


            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }
             
        }

        else if( _category == 2020 ){ // 1 tau WP Medium, 1 lepton

            int n_fake = 0;

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(fabs((*_recolep_sel_pdg)[0])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[0])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

                

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }

        }

        else if( _category == 2120 ){ // 2 tau WP Medium, 1 lepton

            int n_fake = 0;

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[1]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(fabs((*_recolep_sel_pdg)[0])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[0])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }
             
        }

        else if( _category == 3120 ){ // 1 tau WP Vloose, 2 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_VLoose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(fabs((*_recolep_sel_pdg)[0])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[0])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 

                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(fabs((*_recolep_sel_pdg)[1])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[1])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 

                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }

        }

        else if( _category == 3220 ){ // 1 tau WP VTight, 2 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byVTightDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_VTight(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(fabs((*_recolep_sel_pdg)[0])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[0])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(fabs((*_recolep_sel_pdg)[1])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[1])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }

        }

        else if( _category == 3320 ){ // 2 tau WP Medium, 2 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[1]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Medium(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(fabs((*_recolep_sel_pdg)[0])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[0])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(fabs((*_recolep_sel_pdg)[1])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[1])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }

        }

        else if( _category == 4120 ){ // 1 tau WP VLoose, 3 leptons

            int n_fake = 0;

            if(!(*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]){

                std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_VLoose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
                
                float fakerate_nominal = std::get<0>(tau_fakerate);
                
                _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                n_fake++;

            }

            if(!(*_recolep_sel_ismvasel)[0]){

                if(fabs((*_recolep_sel_pdg)[0])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[0])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[1]){

                if(fabs((*_recolep_sel_pdg)[1])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[1])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 


                    n_fake++;

                }

            }

            if(!(*_recolep_sel_ismvasel)[2]){

                if(fabs((*_recolep_sel_pdg)[2])==11){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_ele_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_ele_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_be2/(1-fakerate_be2);

                    _event_weight_ttH_mu_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    n_fake++;

                }

                else if(fabs((*_recolep_sel_pdg)[2])==13){

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

                    _event_weight_ttH_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);
                    _event_weight_ttH_ele_FR_QCD_MC_v2  *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_FR_TT_MC_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_mu_FR_QCD_MC_v2 *= fakerate_QCD/(1-fakerate_QCD);
                    _event_weight_ttH_mu_FR_TT_MC_v2 *= fakerate_TT/(1-fakerate_TT);

                    _event_weight_ttH_ele_up_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_down_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_pt2_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be1_v2 *= fakerate_nominal/(1-fakerate_nominal);
                    _event_weight_ttH_ele_be2_v2 *= fakerate_nominal/(1-fakerate_nominal);

                    _event_weight_ttH_mu_up_v2 *= fakerate_up/(1-fakerate_up);
                    _event_weight_ttH_mu_down_v2 *= fakerate_down/(1-fakerate_down);
                    _event_weight_ttH_mu_pt1_v2 *= fakerate_pt1/(1-fakerate_pt1);
                    _event_weight_ttH_mu_pt2_v2 *= fakerate_pt2/(1-fakerate_pt2);
                    _event_weight_ttH_mu_be1_v2 *= fakerate_be1/(1-fakerate_be1);
                    _event_weight_ttH_mu_be2_v2 *= fakerate_be2/(1-fakerate_be2); 

                    n_fake++;

                }

            }

            if(n_fake>0 && n_fake%2==0){

                _event_weight_ttH_v2 *= -1;

                _event_weight_ttH_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_QCD_MC_v2 *= -1;
                _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

                _event_weight_ttH_ele_up_v2 *= -1;
                _event_weight_ttH_ele_down_v2 *= -1;
                _event_weight_ttH_ele_pt1_v2 *= -1;
                _event_weight_ttH_ele_pt2_v2 *= -1;
                _event_weight_ttH_ele_be1_v2 *= -1;
                _event_weight_ttH_ele_be2_v2 *= -1;

                _event_weight_ttH_mu_up_v2 *= -1;
                _event_weight_ttH_mu_down_v2 *= -1;
                _event_weight_ttH_mu_pt1_v2 *= -1;
                _event_weight_ttH_mu_pt2_v2 *= -1;
                _event_weight_ttH_mu_be1_v2 *= -1;
                _event_weight_ttH_mu_be2_v2 *= -1;

            }

        }

        ////////////////////////////
        //////// FLIP WEIGHTS //////
        ////////////////////////////

        if( _category == 2030 ){ // 1l1tau flip

            if( abs((*_recolep_sel_pdg)[0])==11 )
                _event_weight_ttH_v2 = get_fliprate(_year,(*_recolep_sel_conept)[0],(*_recolep_sel_eta)[0]);

            else
                _event_weight_ttH_v2 = 0;

        }
      
        else if( _category == 3130 ){ // 2lss1tau flip

            if( abs((*_recolep_sel_pdg)[0])==11 && ((*_recolep_sel_charge)[0]*((*_recotauh_sel_charge)[0])>0) )
                _event_weight_ttH_v2 = get_fliprate(_year,(*_recolep_sel_conept)[0],(*_recolep_sel_eta)[0]);
      
            else if( abs((*_recolep_sel_pdg)[1])==11 && ((*_recolep_sel_charge)[1]*((*_recotauh_sel_charge)[0])>0) )
                _event_weight_ttH_v2 = get_fliprate(_year,(*_recolep_sel_conept)[1],(*_recolep_sel_eta)[1]);

            else
                _event_weight_ttH_v2 = 0;

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


void loadsample(TString region, TString sample, int year, TString type, bool ismc){

    if(region=="SR") cout<<"Processing SR sample: "<<sample;
    else if(region=="fake") cout<<"Processing fake sample: "<<sample;
    else if(region=="flip") cout<<"Processing flip sample: "<<sample;

    TString year_s = std::to_string(year);

    TString filein;
    if(region=="SR") filein = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/SR/ntuple_"+sample+"_MEM_SR_SF_v1_noOverlap.root";
    else if(region=="fake") filein = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/fake/ntuple_"+sample+"_MEM_fake_SF_v1_noOverlap.root";
    else if(region=="flip") filein = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/flip/ntuple_"+sample+"_MEM_flip_SF_v1_noOverlap.root";

    TString fileout;
    if(region=="SR") fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/SR/ntuple_"+sample+"_MEM_SR_SF_v2_noOverlap.root";
    else if(region=="fake") fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/fake/ntuple_"+sample+"_MEM_fake_SF_v2_noOverlap.root";
    else if(region=="flip") fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/flip/ntuple_"+sample+"_MEM_flip_SF_v2_noOverlap.root";

  	vector<TString> tree;
    if(region=="SR") tree.push_back("HTauTauTree_2lss1tau_SR");
    else if(region=="fake") tree.push_back("HTauTauTree_2lss1tau_fake");
    else if(region=="flip") tree.push_back("HTauTauTree_2lss1tau_flip");

    add_SFs(filein,fileout,tree,ismc,year);


}

void test_2016(TString region = "SR"){

    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockB",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockC",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockD",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockE",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockF",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockG",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleElectron_BlockH",2016,"Data",false);

    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockB",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockC",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockD",2016,"Data",false); 
    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockE",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockF",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockG",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_SingleMuon_BlockH",2016,"Data",false);

    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockB",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockC",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockD",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockE",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockF",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockG",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleEG_BlockH",2016,"Data",false);

    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockB",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockC",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockD",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockE",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockF",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockG",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_DoubleMu_BlockH",2016,"Data",false);

    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockB",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockC",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockD",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockE",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockF",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockG",2016,"Data",false);
    loadsample(region,"Oct19v1_Data_2016_MuonEG_BlockH",2016,"Data",false);

}

void test_2017(TString region = "SR"){

    loadsample(region,"Oct19v1_Data_2017_SingleElectron_BlockB",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleElectron_BlockC",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleElectron_BlockD",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleElectron_BlockE",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleElectron_BlockF",2017,"Data",false);

    loadsample(region,"Oct19v1_Data_2017_SingleMuon_BlockB",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleMuon_BlockC",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleMuon_BlockD",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleMuon_BlockE",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_SingleMuon_BlockF",2017,"Data",false);

    loadsample(region,"Oct19v1_Data_2017_DoubleEG_BlockB",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleEG_BlockC",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleEG_BlockD",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleEG_BlockE",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleEG_BlockF",2017,"Data",false);

    loadsample(region,"Oct19v1_Data_2017_DoubleMu_BlockB",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleMu_BlockC",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleMu_BlockD",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleMu_BlockE",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_DoubleMu_BlockF",2017,"Data",false);

    loadsample(region,"Oct19v1_Data_2017_MuonEG_BlockB",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_MuonEG_BlockC",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_MuonEG_BlockD",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_MuonEG_BlockE",2017,"Data",false);
    loadsample(region,"Oct19v1_Data_2017_MuonEG_BlockF",2017,"Data",false);

}


void test_2018(TString region = "SR"){

    loadsample(region,"Oct19v1_Data_2018_EGamma_BlockA",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_EGamma_BlockB",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_EGamma_BlockC",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_EGamma_BlockD",2018,"Data",false);

    loadsample(region,"Oct19v1_Data_2018_SingleMuon_BlockA",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_SingleMuon_BlockB",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_SingleMuon_BlockC",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_SingleMuon_BlockD",2018,"Data",false);

    loadsample(region,"Oct19v1_Data_2018_DoubleMu_BlockA",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_DoubleMu_BlockB",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_DoubleMu_BlockC",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_DoubleMu_BlockD",2018,"Data",false);

    loadsample(region,"Oct19v1_Data_2018_MuonEG_BlockA",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_MuonEG_BlockB",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_MuonEG_BlockC",2018,"Data",false);
    loadsample(region,"Oct19v1_Data_2018_MuonEG_BlockD",2018,"Data",false);

}