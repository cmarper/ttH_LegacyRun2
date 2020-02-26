#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>
#include <TH2F.h>

#include "headers/fakerateSF_v3.cc"
#include "headers/tauIDSF_v1.cc"

using namespace std;

void add_SFs(TString filein, TString fileout, vector<TString> treename, bool isMC, int year){

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

      float _tauID_weight_v3;
      float _tauID_weight_up_v3;
      float _tauID_weight_down_v3;

      float _tauID_weight_tauNormUp_v3;
      float _tauID_weight_tauNormDown_v3;
      float _tauID_weight_tauShapeUp_v3;
      float _tauID_weight_tauShapeDown_v3;

      tree_new->Branch("tauID_weight_v3",&_tauID_weight_v3,"tauID_weight_v3/F");
      tree_new->Branch("tauID_weight_up_v3",&_tauID_weight_up_v3,"tauID_weight_up_v3/F");
      tree_new->Branch("tauID_weight_down_v3",&_tauID_weight_down_v3,"tauID_weight_down_v3/F");

      tree_new->Branch("tauID_weight_tauNormUp_v3",&_tauID_weight_tauNormUp_v3,"tauID_weight_tauNormUp_v3/F");
      tree_new->Branch("tauID_weight_tauNormDown_v3",&_tauID_weight_tauNormDown_v3,"tauID_weight_tauNormDown_v3/F");
      tree_new->Branch("tauID_weight_tauShapeUp_v3",&_tauID_weight_tauShapeUp_v3,"tauID_weight_tauShapeUp_v3/F");
      tree_new->Branch("tauID_weight_tauShapeDown_v3",&_tauID_weight_tauShapeDown_v3,"tauID_weight_tauShapeDown_v3/F");

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

        _tauID_weight_v3 = 0;
        _tauID_weight_up_v3 = 0;
        _tauID_weight_down_v3 = 0;

        _tauID_weight_tauNormUp_v3 = 0;
        _tauID_weight_tauNormDown_v3 = 0;
        _tauID_weight_tauShapeUp_v3 = 0;
        _tauID_weight_tauShapeDown_v3 = 0;

      	tree->GetEntry(i);

        if(i==(nentries-1)) cout<<"FINISHED!!!"<<endl;

        _tauID_weight_v3 = 1.;
        _tauID_weight_up_v3 = 1.;
        _tauID_weight_down_v3 = 1.;

        _tauID_weight_tauNormUp_v3 = 1.;
        _tauID_weight_tauNormDown_v3 = 1.;
        _tauID_weight_tauShapeUp_v3 = 1.;
        _tauID_weight_tauShapeDown_v3 = 1.;

        // New variables

      	bool cat_2tau = 	  (_category == 1010 || _category==1020);
      	bool cat_1l1tau = 	(_category == 2010 || _category==2020 || _category==2030);
      	bool cat_1l2tau = 	(_category == 2110 || _category==2120);
      	bool cat_2lss1tau = (_category == 3110 || _category==3120 || _category==3130);
      	bool cat_2los1tau = (_category == 3210 || _category==3220);
      	bool cat_2l2tau = 	(_category == 3310 || _category==3320);
      	bool cat_3l1tau = 	(_category == 4110 || _category==4120);

        if (!isMC) continue;

        if ( cat_2lss1tau || cat_3l1tau ){

            TString wp;
            if((*_recotauh_sel_byVLooseDeepTau2017v2p1VSjet)[0]==1) wp = "VLoose";
            else wp = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

            if((*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate);

            }     

        }

        else if ( cat_1l1tau ){ // 1-tau Medium WP

            TString wp;
            if((*_recotauh_sel_byMediumDeepTau2017v2p1VSjet)[0]==1) wp = "Medium";
            else wp = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

            if((*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate);

            } 

        }

        else if ( cat_2los1tau ){ // 1-tau VTight WP

            TString wp;
            if((*_recotauh_sel_byVTightDeepTau2017v2p1VSjet)[0]==1) wp = "VTight";
            else wp = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);

            if((*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate);

            } 

        }

        else if ( cat_2tau ){ // 2-tau Loose WP

            TString wp1;
            if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[0]==1) wp1 = "Loose";
            else wp1 = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate1 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
            
            if((*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp1,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp1,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp1,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate1);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate1);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate1);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate1);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate1);

            } 

            TString wp2;
            if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[1]==1) wp2 = "Loose";
            else wp2 = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate2 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

            if((*_recotauh_sel_isGenMatched)[1]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp2,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp2,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp2,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[1]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate2);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate2);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate2);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate2);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate2);

            } 


        }

        else if ( cat_1l2tau || cat_2l2tau ){ // 2-tau Medium WP

            TString wp1;
            if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[0]==1) wp1 = "Medium";
            else wp1 = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate1 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[0],(*_recotauh_sel_eta)[0]);
            
            if((*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp1,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp1,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[0], (*_recotauh_sel_eta)[0], (*_recotauh_sel_decayMode)[0], wp1,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[0]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate1);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate1);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate1);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate1);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate1);

            } 

            TString wp2;
            if((*_recotauh_sel_byLooseDeepTau2017v2p1VSjet)[1]==1) wp2 = "Medium";
            else wp2 = "VVLoose";

            std::tuple<float, float, float, float, float> tau_fakerate2 = get_fakerate_tau_Loose(_year,(*_recotauh_sel_pt)[1],(*_recotauh_sel_eta)[1]);

            if((*_recotauh_sel_isGenMatched)[1]){

              _tauID_weight_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp2,0);

              _tauID_weight_up_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp2,+1);
              _tauID_weight_down_v3 *= get_tauIDSF(_year, (*_recotauh_sel_pt)[1], (*_recotauh_sel_eta)[1], (*_recotauh_sel_decayMode)[1], wp2,-1);

              _tauID_weight_tauNormUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauNormDown_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeUp_v3 *= _tauID_weight_v3;
              _tauID_weight_tauShapeDown_v3 *= _tauID_weight_v3;

            }

            else if(!(*_recotauh_sel_isGenMatched)[1]){

              _tauID_weight_v3 *= std::get<0>(tau_fakerate2);

              _tauID_weight_up_v3 *= _tauID_weight_v3;
              _tauID_weight_down_v3 *= _tauID_weight_v3;

              _tauID_weight_tauNormUp_v3 *= std::get<1>(tau_fakerate2);
              _tauID_weight_tauNormDown_v3 *= std::get<2>(tau_fakerate2);
              _tauID_weight_tauShapeUp_v3 *= std::get<3>(tau_fakerate2);
              _tauID_weight_tauShapeDown_v3 *= std::get<4>(tau_fakerate2);

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
    filein = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR_SF_v1.root";

    TString fileout;
    fileout = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/"+year_s+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR_SF_v3.root";

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