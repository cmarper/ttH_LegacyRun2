#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>

#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>

#include "headers/leptonSF.cc"
#include "headers/triggerSF.cc"
#include "headers/triggerFilter.cc"
#include "headers/metFilter.cc"

using namespace std;


bool pT_comparison_pairs(pair<int,float> pair1, pair<int,float> pair2){

    return pair1.second>pair2.second;

}


void split_tree(TString filename_in, TString filename_out,
		int i_split1=0, int i_split2=0,
		bool isMC=true){

  produce_triggerlist();

  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }

  TH1F* h=new TH1F("h_counter","h_counter",3,0,3);


  //Old branches used

  Long64_t _EventNumber;
   
  Long64_t _triggerbit; 
  int _metfilterbit;

  vector<int> *_recomu_charge;
  vector<float> *_recomu_e;
  vector<float> *_recomu_px;
  vector<float> *_recomu_py;
  vector<float> *_recomu_pz;
  vector<float> *_recomu_pt;
  vector<float> *_recomu_conept;
  vector<float> *_recomu_eta;
  vector<float> *_recomu_phi;
  vector<bool> *_recomu_ismvasel;
  vector<bool> *_recomu_isfakeable;
  vector<bool> *_recomu_isGenMatched;
  vector<int> *_recomu_genMatchInd;
  vector<float> *_recomu_rel_error_trackpt;

  vector<int> *_recoele_charge;
  vector<float> *_recoele_e;
  vector<float> *_recoele_px;
  vector<float> *_recoele_py;
  vector<float> *_recoele_pz;
  vector<float> *_recoele_pt;
  vector<float> *_recoele_conept;
  vector<float> *_recoele_eta;
  vector<float> *_recoele_phi;
  vector<bool> *_recoele_ismvasel;
  vector<bool> *_recoele_isfakeable;
  vector<bool> *_recoele_isGenMatched;
  vector<int> *_recoele_genMatchInd;
  vector<bool> *_recoele_isChargeConsistent;

  float _ETmissLD;
  int _n_recoPFJet;
  int _n_recoPFFwdJet;
  int _n_recoPFJet_btag_medium;
  int _n_recoPFJet_btag_loose;

  int _n_recotauh;
  vector<float> *_recotauh_eta;
  vector<float> *_recotauh_phi;
  vector<float> *_recotauh_pt;
  vector<int> *_recotauh_charge;
  vector<int> *_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int> *_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int> *_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int> *_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int> *_recotauh_againstMuonLoose3;
  vector<int> *_recotauh_againstMuonTight3;
  vector<int> *_recotauh_againstElectronVLooseMVA6;
  vector<int> *_recotauh_againstElectronLooseMVA6;
  vector<int> *_recotauh_againstElectronMediumMVA6;
  vector<int> *_recotauh_againstElectronTightMVA6;
  vector<int> *_recotauh_againstElectronVTightMVA6;
  vector<int> *_recotauh_decayMode;
  vector<float> *_recotauh_e;
  vector<float> *_recotauh_px;
  vector<float> *_recotauh_py;
  vector<float> *_recotauh_pz;
  vector<bool> *_recotauh_isGenMatched;
  vector<int> *_recotauh_genMatchInd;

  tree->SetBranchAddress("EventNumber",&_EventNumber);

  tree->SetBranchAddress("triggerbit",&_triggerbit);
  tree->SetBranchAddress("metfilterbit",&_metfilterbit);

  tree->SetBranchAddress("recomu_charge",&_recomu_charge);
  tree->SetBranchAddress("recomu_e",&_recomu_e);
  tree->SetBranchAddress("recomu_px",&_recomu_px);
  tree->SetBranchAddress("recomu_py",&_recomu_py);
  tree->SetBranchAddress("recomu_pz",&_recomu_pz);
  tree->SetBranchAddress("recomu_pt",&_recomu_pt);
  tree->SetBranchAddress("recomu_conept",&_recomu_conept);
  tree->SetBranchAddress("recomu_eta",&_recomu_eta);
  tree->SetBranchAddress("recomu_phi",&_recomu_phi);
  tree->SetBranchAddress("recomu_isfakeable",&_recomu_isfakeable);
  tree->SetBranchAddress("recomu_ismvasel",&_recomu_ismvasel);
  tree->SetBranchAddress("recomu_isGenMatched",&_recomu_isGenMatched);
  tree->SetBranchAddress("recomu_genMatchInd",&_recomu_genMatchInd);
  tree->SetBranchAddress("recomu_rel_error_trackpt",&_recomu_rel_error_trackpt);

  tree->SetBranchAddress("recoele_charge",&_recoele_charge);
  tree->SetBranchAddress("recoele_e",&_recoele_e);
  tree->SetBranchAddress("recoele_px",&_recoele_px);
  tree->SetBranchAddress("recoele_py",&_recoele_py);
  tree->SetBranchAddress("recoele_pz",&_recoele_pz);
  tree->SetBranchAddress("recoele_pt",&_recoele_pt);
  tree->SetBranchAddress("recoele_conept",&_recoele_conept);
  tree->SetBranchAddress("recoele_eta",&_recoele_eta);
  tree->SetBranchAddress("recoele_phi",&_recoele_phi);
  tree->SetBranchAddress("recoele_isfakeable",&_recoele_isfakeable);
  tree->SetBranchAddress("recoele_ismvasel",&_recoele_ismvasel);
  tree->SetBranchAddress("recoele_isGenMatched",&_recoele_isGenMatched);
  tree->SetBranchAddress("recoele_genMatchInd",&_recoele_genMatchInd);
  tree->SetBranchAddress("recoele_isChargeConsistent",&_recoele_isChargeConsistent);

  tree->SetBranchAddress("ETmissLD",&_ETmissLD);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("n_recoPFFwdJet",&_n_recoPFFwdJet);
  tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("n_recotauh",&_n_recotauh);
  tree->SetBranchAddress("recotauh_eta",&_recotauh_eta);
  tree->SetBranchAddress("recotauh_phi",&_recotauh_phi);
  tree->SetBranchAddress("recotauh_pt",&_recotauh_pt);
  tree->SetBranchAddress("recotauh_charge",&_recotauh_charge);
  tree->SetBranchAddress("recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_againstMuonLoose3",&_recotauh_againstMuonLoose3);
  tree->SetBranchAddress("recotauh_againstMuonTight3",&_recotauh_againstMuonTight3);
  tree->SetBranchAddress("recotauh_againstElectronVLooseMVA6",&_recotauh_againstElectronVLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronLooseMVA6",&_recotauh_againstElectronLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronMediumMVA6",&_recotauh_againstElectronMediumMVA6);
  tree->SetBranchAddress("recotauh_againstElectronTightMVA6",&_recotauh_againstElectronTightMVA6);
  tree->SetBranchAddress("recotauh_againstElectronVTightMVA6",&_recotauh_againstElectronVTightMVA6);
  tree->SetBranchAddress("recotauh_decayMode",&_recotauh_decayMode);
  tree->SetBranchAddress("recotauh_e",&_recotauh_e);
  tree->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree->SetBranchAddress("recotauh_pz",&_recotauh_pz);
  tree->SetBranchAddress("recotauh_isGenMatched",&_recotauh_isGenMatched);
  tree->SetBranchAddress("recotauh_genMatchInd",&_recotauh_genMatchInd);
  
  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(filename_out);
  
  /*if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/
  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_2tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2tau_fake=tree->GetTree()->CloneTree(0);
  TTree* tree_2tau_DY=tree->GetTree()->CloneTree(0);

  TTree* tree_1l1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_1l1tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_1l2tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_1l2tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_2lss_SR_ttH=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_SR_tH=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_fake_ttH=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_fake_tH=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_flip_ttH=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_flip_tH=tree->GetTree()->CloneTree(0);

  TTree* tree_2lss1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss1tau_fake=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss1tau_flip=tree->GetTree()->CloneTree(0);

  TTree* tree_2los1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2los1tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_2l2tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2l2tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_3l_SR_ttH=tree->GetTree()->CloneTree(0);
  TTree* tree_3l_SR_tH=tree->GetTree()->CloneTree(0);
  TTree* tree_3l_fake_ttH=tree->GetTree()->CloneTree(0);
  TTree* tree_3l_fake_tH=tree->GetTree()->CloneTree(0);

  TTree* tree_3l1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_3l1tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_4l_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_4l_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_ttW_CR_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_ttW_CR_fake=tree->GetTree()->CloneTree(0);
  TTree* tree_ttW_CR_flip=tree->GetTree()->CloneTree(0);

  TTree* tree_ttZ_CR_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_ttZ_CR_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_WZ_CR_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_WZ_CR_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_ZZ_CR_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_ZZ_CR_fake=tree->GetTree()->CloneTree(0);

  tree_2tau_SR->SetNameTitle("HTauTauTree_2tau_SR","HTauTauTree_2tau_SR");
  tree_2tau_fake->SetNameTitle("HTauTauTree_2tau_fake","HTauTauTree_2tau_fake");
  tree_2tau_DY->SetNameTitle("HTauTauTree_2tau_DY","HTauTauTree_2tau_DY");
  
  tree_1l1tau_SR->SetNameTitle("HTauTauTree_1l1tau_SR","HTauTauTree_1l1tau_SR");
  tree_1l1tau_fake->SetNameTitle("HTauTauTree_1l1tau_fake","HTauTauTree_1l1tau_fake");

  tree_1l2tau_SR->SetNameTitle("HTauTauTree_1l2tau_SR","HTauTauTree_1l2tau_SR");
  tree_1l2tau_fake->SetNameTitle("HTauTauTree_1l2tau_fake","HTauTauTree_1l2tau_fake");

  tree_2lss_SR_ttH->SetNameTitle("HTauTauTree_2lss_SR_ttH","HTauTauTree_2lss_SR_ttH");
  tree_2lss_SR_tH->SetNameTitle("HTauTauTree_2lss_SR_tH","HTauTauTree_2lss_SR_tH");
  tree_2lss_fake_ttH->SetNameTitle("HTauTauTree_2lss_fake_ttH","HTauTauTree_2lss_fake_ttH");
  tree_2lss_fake_tH->SetNameTitle("HTauTauTree_2lss_fake_tH","HTauTauTree_2lss_fake_tH");
  tree_2lss_flip_ttH->SetNameTitle("HTauTauTree_2lss_flip_ttH","HTauTauTree_2lss_flip_ttH");
  tree_2lss_flip_tH->SetNameTitle("HTauTauTree_2lss_flip_tH","HTauTauTree_2lss_flip_tH");

  tree_2lss1tau_SR->SetNameTitle("HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_SR");
  tree_2lss1tau_fake->SetNameTitle("HTauTauTree_2lss1tau_fake","HTauTauTree_2lss1tau_fake");
  tree_2lss1tau_flip->SetNameTitle("HTauTauTree_2lss1tau_flip","HTauTauTree_2lss1tau_flip");

  tree_2los1tau_SR->SetNameTitle("HTauTauTree_2los1tau_SR","HTauTauTree_2los1tau_SR");
  tree_2los1tau_fake->SetNameTitle("HTauTauTree_2los1tau_fake","HTauTauTree_2los1tau_fake");

  tree_2l2tau_SR->SetNameTitle("HTauTauTree_2l2tau_SR","HTauTauTree_2l2tau_SR");
  tree_2l2tau_fake->SetNameTitle("HTauTauTree_2l2tau_fake","HTauTauTree_2l2tau_fake");

  tree_3l_SR_ttH->SetNameTitle("HTauTauTree_3l_SR_ttH","HTauTauTree_3l_SR_ttH");
  tree_3l_SR_tH->SetNameTitle("HTauTauTree_3l_SR_tH","HTauTauTree_3l_SR_tH");
  tree_3l_fake_ttH->SetNameTitle("HTauTauTree_3l_fake_ttH","HTauTauTree_3l_fake_ttH");
  tree_3l_fake_tH->SetNameTitle("HTauTauTree_3l_fake_tH","HTauTauTree_3l_fake_tH");

  tree_3l1tau_SR->SetNameTitle("HTauTauTree_3l1tau_SR","HTauTauTree_3l1tau_SR");
  tree_3l1tau_fake->SetNameTitle("HTauTauTree_3l1tau_fake","HTauTauTree_3l1tau_fake");

  tree_4l_SR->SetNameTitle("HTauTauTree_4l_SR","HTauTauTree_4l_SR");
  tree_4l_fake->SetNameTitle("HTauTauTree_4l_fake","HTauTauTree_4l_fake");
  
  tree_ttW_CR_SR->SetNameTitle("HTauTauTree_ttW_CR_SR","HTauTauTree_ttW_CR_SR");
  tree_ttW_CR_fake->SetNameTitle("HTauTauTree_ttW_CR_fake","HTauTauTree_ttW_CR_fake");
  tree_ttW_CR_flip->SetNameTitle("HTauTauTree_ttW_CR_flip","HTauTauTree_ttW_CR_flip");

  tree_ttZ_CR_SR->SetNameTitle("HTauTauTree_ttZ_CR_SR","HTauTauTree_ttZ_CR_SR");
  tree_ttZ_CR_fake->SetNameTitle("HTauTauTree_ttZ_CR_fake","HTauTauTree_ttZ_CR_fake");

  tree_WZ_CR_SR->SetNameTitle("HTauTauTree_WZ_CR_SR","HTauTauTree_WZ_CR_SR");
  tree_WZ_CR_fake->SetNameTitle("HTauTauTree_WZ_CR_fake","HTauTauTree_WZ_CR_fake");

  tree_ZZ_CR_SR->SetNameTitle("HTauTauTree_ZZ_CR_SR","HTauTauTree_ZZ_CR_SR");
  tree_ZZ_CR_fake->SetNameTitle("HTauTauTree_ZZ_CR_fake","HTauTauTree_ZZ_CR_fake");

  vector<TTree*> tree_new;

  tree_new.push_back(tree_2tau_SR);
  tree_new.push_back(tree_2tau_fake);
  tree_new.push_back(tree_2tau_DY);

  tree_new.push_back(tree_1l1tau_SR);
  tree_new.push_back(tree_1l1tau_fake);

  tree_new.push_back(tree_1l2tau_SR);
  tree_new.push_back(tree_1l2tau_fake);

  tree_new.push_back(tree_2lss_SR_ttH);
  tree_new.push_back(tree_2lss_SR_tH);
  tree_new.push_back(tree_2lss_fake_ttH);
  tree_new.push_back(tree_2lss_fake_tH);
  tree_new.push_back(tree_2lss_flip_ttH);
  tree_new.push_back(tree_2lss_flip_tH);

  tree_new.push_back(tree_2lss1tau_SR);
  tree_new.push_back(tree_2lss1tau_fake);
  tree_new.push_back(tree_2lss1tau_flip);

  tree_new.push_back(tree_2los1tau_SR);
  tree_new.push_back(tree_2los1tau_fake);

  tree_new.push_back(tree_2l2tau_SR);
  tree_new.push_back(tree_2l2tau_fake);

  tree_new.push_back(tree_3l_SR_ttH);
  tree_new.push_back(tree_3l_SR_tH);
  tree_new.push_back(tree_3l_fake_ttH);
  tree_new.push_back(tree_3l_fake_tH);

  tree_new.push_back(tree_3l1tau_SR);
  tree_new.push_back(tree_3l1tau_fake);

  tree_new.push_back(tree_4l_SR);
  tree_new.push_back(tree_4l_fake);

  tree_new.push_back(tree_ttW_CR_SR);
  tree_new.push_back(tree_ttW_CR_fake);
  tree_new.push_back(tree_ttW_CR_flip);

  tree_new.push_back(tree_ttZ_CR_SR);
  tree_new.push_back(tree_ttZ_CR_fake);

  tree_new.push_back(tree_WZ_CR_SR);
  tree_new.push_back(tree_WZ_CR_fake);

  tree_new.push_back(tree_ZZ_CR_SR);
  tree_new.push_back(tree_ZZ_CR_fake);

  int n_2tau_SR = 0;
  int n_2tau_fake = 0;
  int n_2tau_DY = 0;

  int n_1l1tau_SR = 0;
  int n_1l1tau_fake = 0; 

  int n_1l2tau_SR = 0;  
  int n_1l2tau_fake = 0;

  int n_2lss_SR_ttH = 0;
  int n_2lss_SR_tH = 0;
  int n_2lss_fake_ttH = 0;
  int n_2lss_fake_tH = 0;
  int n_2lss_flip_ttH = 0;
  int n_2lss_flip_tH = 0;

  int n_2lss1tau_SR = 0;
  int n_2lss1tau_fake = 0;
  int n_2lss1tau_flip = 0;

  int n_2los1tau_SR = 0;
  int n_2los1tau_fake = 0;

  int n_2l2tau_SR = 0;
  int n_2l2tau_fake = 0;

  int n_3l_SR_ttH = 0;
  int n_3l_SR_tH = 0;
  int n_3l_fake_ttH = 0;
  int n_3l_fake_tH = 0;

  int n_3l1tau_SR = 0;
  int n_3l1tau_fake = 0;

  int n_4l_SR = 0;
  int n_4l_fake = 0;

  int n_ttW_CR_SR = 0;
  int n_ttW_CR_fake = 0;
  int n_ttW_CR_flip = 0;

  int n_ttZ_CR_SR = 0;
  int n_ttZ_CR_fake = 0;

  int n_WZ_CR_SR = 0;
  int n_WZ_CR_fake = 0;

  int n_ZZ_CR_SR = 0;
  int n_ZZ_CR_fake = 0;


  //New branches

  int _category;

  /*
  1010 2tau_SR
  1020 2tau_fake
  1040 2tau_DY

  2010 1l1tau_SR
  2020 1l1tau_fake

  2110 1l2tau_SR
  2120 1l2tau_fake

  3010 2lss_SR_ttH
  3011 2lss_SR_tH
  3020 2lss_fake_ttH
  3021 2lss_fake_tH
  3030 2lss_flip_ttH
  3031 2lss_flip_tH

  3110 2lss1tau_SR
  3120 2lss1tau_fake
  3130 2lss1tau_flip

  3210 2los1tau_SR
  3220 2los1tau_fake

  3310 2l2tau_SR
  3320 2l2tau_fake

  4010 3l_SR_ttH
  4011 3l_SR_tH
  4020 3l_fake_ttH
  4021 3l_fake_tH

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
  */

  vector<int>   _recolep_loose_pdg;
  vector<float> _recolep_loose_eta;
  vector<float> _recolep_loose_phi;
  vector<float> _recolep_loose_e;
  vector<float> _recolep_loose_px;
  vector<float> _recolep_loose_py;
  vector<float> _recolep_loose_pz;
  vector<float> _recolep_loose_pt;
  vector<float> _recolep_loose_conept;
  vector<int>   _recolep_loose_charge;
  vector<bool>  _recolep_loose_tightcharge;
  vector<bool>  _recolep_loose_isGenMatched;
  vector<int>   _recolep_loose_genMatchInd;
  vector<bool>  _recolep_loose_isfakeable;
  vector<bool>  _recolep_loose_istight;

  vector<int>   _recolep_fakeable_pdg;
  vector<float> _recolep_fakeable_eta;
  vector<float> _recolep_fakeable_phi;
  vector<float> _recolep_fakeable_e;
  vector<float> _recolep_fakeable_px;
  vector<float> _recolep_fakeable_py;
  vector<float> _recolep_fakeable_pz;
  vector<float> _recolep_fakeable_pt;
  vector<float> _recolep_fakeable_conept;
  vector<int>   _recolep_fakeable_charge;
  vector<bool>  _recolep_fakeable_tightcharge;
  vector<bool>  _recolep_fakeable_isGenMatched;
  vector<int>   _recolep_fakeable_genMatchInd;
  vector<bool>  _recolep_fakeable_istight;

  vector<int>   _recolep_tight_pdg;
  vector<float> _recolep_tight_eta;
  vector<float> _recolep_tight_phi;
  vector<float> _recolep_tight_e;
  vector<float> _recolep_tight_px;
  vector<float> _recolep_tight_py;
  vector<float> _recolep_tight_pz;
  vector<float> _recolep_tight_pt;
  vector<float> _recolep_tight_conept;
  vector<int>   _recolep_tight_charge;
  vector<bool>  _recolep_tight_tightcharge;
  vector<bool>  _recolep_tight_isGenMatched;
  vector<int>   _recolep_tight_genMatchInd;

  vector<float> _recotauh_VL_eta;
  vector<float> _recotauh_VL_phi;
  vector<float> _recotauh_VL_e;
  vector<float> _recotauh_VL_px;
  vector<float> _recotauh_VL_py;
  vector<float> _recotauh_VL_pz;
  vector<float> _recotauh_VL_pt;
  vector<int>   _recotauh_VL_charge;
  vector<int>   _recotauh_VL_decayMode;
  vector<bool>  _recotauh_VL_isGenMatched;
  vector<int>   _recotauh_VL_genMatchInd;
  vector<bool>  _recotauh_VL_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<bool>  _recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT;

  vector<float> _recotauh_L_eta;
  vector<float> _recotauh_L_phi;
  vector<float> _recotauh_L_e;
  vector<float> _recotauh_L_px;
  vector<float> _recotauh_L_py;
  vector<float> _recotauh_L_pz;
  vector<float> _recotauh_L_pt;
  vector<int>   _recotauh_L_charge;
  vector<int>   _recotauh_L_decayMode;
  vector<bool>  _recotauh_L_isGenMatched;
  vector<int>   _recotauh_L_genMatchInd;
  vector<bool>  _recotauh_L_byMediumIsolationMVArun2v2017v2DBoldDMwLT;

  vector<float> _recotauh_M_eta;
  vector<float> _recotauh_M_phi;
  vector<float> _recotauh_M_e;
  vector<float> _recotauh_M_px;
  vector<float> _recotauh_M_py;
  vector<float> _recotauh_M_pz;
  vector<float> _recotauh_M_pt;
  vector<int>   _recotauh_M_charge;
  vector<int>   _recotauh_M_decayMode;
  vector<bool>  _recotauh_M_isGenMatched;
  vector<int>   _recotauh_M_genMatchInd;

  int _n_loose_lep;
  int _n_fake_lep;
  int _n_tight_lep;

  int _n_VL_tau;
  int _n_L_tau;
  int _n_M_tau;


  for(unsigned int i=0; i<tree_new.size();i++){
    
    tree_new[i]->Branch("category",&_category);

    tree_new[i]->Branch("recolep_loose_pdg",&_recolep_loose_pdg);
    tree_new[i]->Branch("recolep_loose_eta",&_recolep_loose_eta);
    tree_new[i]->Branch("recolep_loose_phi",&_recolep_loose_phi);
    tree_new[i]->Branch("recolep_loose_e",&_recolep_loose_e);
    tree_new[i]->Branch("recolep_loose_px",&_recolep_loose_px);
    tree_new[i]->Branch("recolep_loose_py",&_recolep_loose_py);
    tree_new[i]->Branch("recolep_loose_pz",&_recolep_loose_pz);
    tree_new[i]->Branch("recolep_loose_pt",&_recolep_loose_pt);
    tree_new[i]->Branch("recolep_loose_conept",&_recolep_loose_conept);
    tree_new[i]->Branch("recolep_loose_charge",&_recolep_loose_charge);
    tree_new[i]->Branch("recolep_loose_tightcharge",&_recolep_loose_tightcharge);
    tree_new[i]->Branch("recolep_loose_isGenMatched",&_recolep_loose_isGenMatched);
    tree_new[i]->Branch("recolep_loose_genMatchInd",&_recolep_loose_genMatchInd);
    tree_new[i]->Branch("recolep_loose_isfakeable",&_recolep_loose_isfakeable);
    tree_new[i]->Branch("recolep_loose_istight",&_recolep_loose_istight);

    tree_new[i]->Branch("recolep_fakeable_pdg",&_recolep_fakeable_pdg);
    tree_new[i]->Branch("recolep_fakeable_eta",&_recolep_fakeable_eta);
    tree_new[i]->Branch("recolep_fakeable_phi",&_recolep_fakeable_phi);
    tree_new[i]->Branch("recolep_fakeable_e",&_recolep_fakeable_e);
    tree_new[i]->Branch("recolep_fakeable_px",&_recolep_fakeable_px);
    tree_new[i]->Branch("recolep_fakeable_py",&_recolep_fakeable_py);
    tree_new[i]->Branch("recolep_fakeable_pz",&_recolep_fakeable_pz);
    tree_new[i]->Branch("recolep_fakeable_pt",&_recolep_fakeable_pt);
    tree_new[i]->Branch("recolep_fakeable_conept",&_recolep_fakeable_conept);
    tree_new[i]->Branch("recolep_fakeable_charge",&_recolep_fakeable_charge);
    tree_new[i]->Branch("recolep_fakeable_tightcharge",&_recolep_fakeable_tightcharge);
    tree_new[i]->Branch("recolep_fakeable_isGenMatched",&_recolep_fakeable_isGenMatched);
    tree_new[i]->Branch("recolep_fakeable_genMatchInd",&_recolep_fakeable_genMatchInd);
    tree_new[i]->Branch("recolep_fakeable_istight",&_recolep_fakeable_istight);

    tree_new[i]->Branch("recolep_tight_pdg",&_recolep_tight_pdg);
    tree_new[i]->Branch("recolep_tight_eta",&_recolep_tight_eta);
    tree_new[i]->Branch("recolep_tight_phi",&_recolep_tight_phi);
    tree_new[i]->Branch("recolep_tight_e",&_recolep_tight_e);
    tree_new[i]->Branch("recolep_tight_px",&_recolep_tight_px);
    tree_new[i]->Branch("recolep_tight_py",&_recolep_tight_py);
    tree_new[i]->Branch("recolep_tight_pz",&_recolep_tight_pz);
    tree_new[i]->Branch("recolep_tight_pt",&_recolep_tight_pt);
    tree_new[i]->Branch("recolep_tight_conept",&_recolep_tight_conept);
    tree_new[i]->Branch("recolep_tight_charge",&_recolep_tight_charge);
    tree_new[i]->Branch("recolep_tight_tightcharge",&_recolep_loose_tightcharge);
    tree_new[i]->Branch("recolep_tight_isGenMatched",&_recolep_tight_isGenMatched);
    tree_new[i]->Branch("recolep_tight_genMatchInd",&_recolep_tight_genMatchInd);

    tree_new[i]->Branch("recotauh_VL_eta",&_recotauh_VL_eta);
    tree_new[i]->Branch("recotauh_VL_phi",&_recotauh_VL_phi);
    tree_new[i]->Branch("recotauh_VL_e",&_recotauh_VL_e);
    tree_new[i]->Branch("recotauh_VL_px",&_recotauh_VL_px);
    tree_new[i]->Branch("recotauh_VL_py",&_recotauh_VL_py);
    tree_new[i]->Branch("recotauh_VL_pz",&_recotauh_VL_pz);
    tree_new[i]->Branch("recotauh_VL_pt",&_recotauh_VL_pt);
    tree_new[i]->Branch("recotauh_VL_charge",&_recotauh_VL_charge);
    tree_new[i]->Branch("recotauh_VL_decayMode",&_recotauh_VL_decayMode);
    tree_new[i]->Branch("recotauh_VL_isGenMatched",&_recotauh_VL_isGenMatched);
    tree_new[i]->Branch("recotauh_VL_genMatchInd",&_recotauh_VL_genMatchInd);
    tree_new[i]->Branch("recotauh_VL_byLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_VL_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT);

    tree_new[i]->Branch("recotauh_L_eta",&_recotauh_L_eta);
    tree_new[i]->Branch("recotauh_L_phi",&_recotauh_L_phi);
    tree_new[i]->Branch("recotauh_L_e",&_recotauh_L_e);
    tree_new[i]->Branch("recotauh_L_px",&_recotauh_L_px);
    tree_new[i]->Branch("recotauh_L_py",&_recotauh_L_py);
    tree_new[i]->Branch("recotauh_L_pz",&_recotauh_L_pz);
    tree_new[i]->Branch("recotauh_L_pt",&_recotauh_L_pt);
    tree_new[i]->Branch("recotauh_L_charge",&_recotauh_L_charge);
    tree_new[i]->Branch("recotauh_L_decayMode",&_recotauh_L_decayMode);
    tree_new[i]->Branch("recotauh_L_isGenMatched",&_recotauh_L_isGenMatched);
    tree_new[i]->Branch("recotauh_L_genMatchInd",&_recotauh_L_genMatchInd);
    tree_new[i]->Branch("recotauh_L_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_L_byMediumIsolationMVArun2v2017v2DBoldDMwLT);

    tree_new[i]->Branch("recotauh_M_eta",&_recotauh_M_eta);
    tree_new[i]->Branch("recotauh_M_phi",&_recotauh_M_phi);
    tree_new[i]->Branch("recotauh_M_e",&_recotauh_M_e);
    tree_new[i]->Branch("recotauh_M_px",&_recotauh_M_px);
    tree_new[i]->Branch("recotauh_M_py",&_recotauh_M_py);
    tree_new[i]->Branch("recotauh_M_pz",&_recotauh_M_pz);
    tree_new[i]->Branch("recotauh_M_pt",&_recotauh_M_pt);
    tree_new[i]->Branch("recotauh_M_charge",&_recotauh_M_charge);
    tree_new[i]->Branch("recotauh_M_decayMode",&_recotauh_M_decayMode);
    tree_new[i]->Branch("recotauh_M_isGenMatched",&_recotauh_M_isGenMatched);
    tree_new[i]->Branch("recotauh_M_genMatchInd",&_recotauh_M_genMatchInd);

    tree_new[i]->Branch("n_loose_lep",&_n_loose_lep);
    tree_new[i]->Branch("n_fake_lep",&_n_fake_lep);
    tree_new[i]->Branch("n_tight_lep",&_n_tight_lep);

    tree_new[i]->Branch("n_VL_tau",&_n_VL_tau);
    tree_new[i]->Branch("n_L_tau",&_n_L_tau);
    tree_new[i]->Branch("n_M_tau",&_n_M_tau);
    
  }

  cout<<"nentries="<<nentries<<endl;

  int skip_entries=0;
  if(i_split1>0){
    skip_entries = nentries/i_split1 * i_split2;
    nentries = nentries/i_split1 * (i_split2+1);
  }


  for (int i=skip_entries;i<skip_entries+nentries;i++) {

    h->Fill(1);

    if(i%10000==0) 
      cout<<"i="<<i<<endl;

    //new branches

    _category = -1;

    _recolep_loose_pdg.clear();
    _recolep_loose_eta.clear();
    _recolep_loose_phi.clear();
    _recolep_loose_e.clear();
    _recolep_loose_px.clear();
    _recolep_loose_py.clear();
    _recolep_loose_pz.clear();
    _recolep_loose_pt.clear();
    _recolep_loose_conept.clear();
    _recolep_loose_charge.clear();
    _recolep_loose_tightcharge.clear();
    _recolep_loose_isGenMatched.clear();
    _recolep_loose_genMatchInd.clear();
    _recolep_loose_isfakeable.clear();
    _recolep_loose_istight.clear();

    _recolep_fakeable_pdg.clear();
    _recolep_fakeable_eta.clear();
    _recolep_fakeable_phi.clear();
    _recolep_fakeable_e.clear();
    _recolep_fakeable_px.clear();
    _recolep_fakeable_py.clear();
    _recolep_fakeable_pz.clear();
    _recolep_fakeable_pt.clear();
    _recolep_fakeable_conept.clear();
    _recolep_fakeable_charge.clear();
    _recolep_fakeable_tightcharge.clear();
    _recolep_fakeable_isGenMatched.clear();
    _recolep_fakeable_genMatchInd.clear();
    _recolep_fakeable_istight.clear();

    _recolep_tight_pdg.clear();
    _recolep_tight_eta.clear();
    _recolep_tight_phi.clear();
    _recolep_tight_e.clear();
    _recolep_tight_px.clear();
    _recolep_tight_py.clear();
    _recolep_tight_pz.clear();
    _recolep_tight_pt.clear();
    _recolep_tight_conept.clear();
    _recolep_tight_charge.clear();
    _recolep_tight_tightcharge.clear();
    _recolep_tight_isGenMatched.clear();
    _recolep_tight_genMatchInd.clear();

    _recotauh_VL_eta.clear();
    _recotauh_VL_phi.clear();
    _recotauh_VL_e.clear();
    _recotauh_VL_px.clear();
    _recotauh_VL_py.clear();
    _recotauh_VL_pz.clear();
    _recotauh_VL_pt.clear();
    _recotauh_VL_charge.clear();
    _recotauh_VL_decayMode.clear();
    _recotauh_VL_isGenMatched.clear();
    _recotauh_VL_genMatchInd.clear();
    _recotauh_VL_byLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();

    _recotauh_L_eta.clear();
    _recotauh_L_phi.clear();
    _recotauh_L_e.clear();
    _recotauh_L_px.clear();
    _recotauh_L_py.clear();
    _recotauh_L_pz.clear();
    _recotauh_L_pt.clear();
    _recotauh_L_charge.clear();
    _recotauh_L_decayMode.clear();
    _recotauh_L_isGenMatched.clear();
    _recotauh_L_genMatchInd.clear();
    _recotauh_L_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();

    _recotauh_M_eta.clear();
    _recotauh_M_phi.clear();
    _recotauh_M_e.clear();
    _recotauh_M_px.clear();
    _recotauh_M_py.clear();
    _recotauh_M_pz.clear();
    _recotauh_M_pt.clear();
    _recotauh_M_charge.clear();
    _recotauh_M_decayMode.clear();
    _recotauh_M_isGenMatched.clear();
    _recotauh_M_genMatchInd.clear();

    _n_loose_lep = 0;
    _n_fake_lep = 0;
    _n_tight_lep = 0;

    _n_VL_tau = 0;
    _n_L_tau = 0;
    _n_M_tau = 0;


    // old branches

    _recomu_charge = 0;
    _recomu_e = 0;
    _recomu_px = 0;
    _recomu_py = 0;
    _recomu_pz = 0;
    _recomu_pt = 0;
    _recomu_conept = 0;
    _recomu_eta = 0;
    _recomu_phi = 0;
    _recomu_isfakeable = 0;
    _recomu_ismvasel = 0;
    _recomu_isGenMatched = 0;
    _recomu_genMatchInd = 0;
    _recomu_rel_error_trackpt = 0;
  
    _recoele_charge = 0;
    _recoele_e = 0;
    _recoele_px = 0;
    _recoele_py = 0;
    _recoele_pz = 0;
    _recoele_pt = 0;
    _recoele_conept = 0;
    _recoele_eta = 0;
    _recoele_phi = 0;
    _recoele_isfakeable = 0;
    _recoele_ismvasel = 0;
    _recoele_isGenMatched = 0;
    _recoele_genMatchInd = 0;
    _recoele_isChargeConsistent = 0;

    _ETmissLD = 0;

    _n_recoPFJet = 0;
    _n_recoPFFwdJet = 0;
    _n_recoPFJet_btag_medium = 0;
    _n_recoPFJet_btag_loose = 0;

    _n_recotauh = 0;
    _recotauh_eta = 0;
    _recotauh_phi = 0;
    _recotauh_pt = 0;
    _recotauh_charge = 0;
    _recotauh_decayMode = 0;
    _recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT = 0;
    _recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT = 0;
    _recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT = 0;
    _recotauh_againstMuonLoose3 = 0;
    _recotauh_againstMuonTight3 = 0;
    _recotauh_againstElectronVLooseMVA6 = 0;
    _recotauh_againstElectronLooseMVA6 = 0;
    _recotauh_againstElectronMediumMVA6 = 0;
    _recotauh_againstElectronTightMVA6 = 0;
    _recotauh_againstElectronVTightMVA6 = 0;
    _recotauh_e = 0;
    _recotauh_px = 0;
    _recotauh_py = 0;
    _recotauh_pz = 0;
    _recotauh_isGenMatched = 0;
    _recotauh_genMatchInd = 0;

    tree->GetEntry(i);


    /////////////////////////////////
    //////////// Leptons ////////////
    /////////////////////////////////

    int n_loose_mu = (*_recomu_e).size();
    int n_loose_ele = (*_recoele_e).size();
    _n_loose_lep = n_loose_mu + n_loose_ele;

    //unsorted loose leptons
    vector<int>   _recolep_presel_pdg;
    vector<float> _recolep_presel_eta;
    vector<float> _recolep_presel_phi;
    vector<float> _recolep_presel_e;
    vector<float> _recolep_presel_px;
    vector<float> _recolep_presel_py;
    vector<float> _recolep_presel_pz;
    vector<float> _recolep_presel_pt;
    vector<float> _recolep_presel_conept;
    vector<int>   _recolep_presel_charge;
    vector<bool>  _recolep_presel_tightcharge;
    vector<bool>  _recolep_presel_isGenMatched;
    vector<int>   _recolep_presel_genMatchInd;
    vector<bool>  _recolep_presel_isfakeable;
    vector<bool>  _recolep_presel_istight;

    _recolep_presel_pdg.clear();
    _recolep_presel_eta.clear();
    _recolep_presel_phi.clear();
    _recolep_presel_e.clear();
    _recolep_presel_px.clear();
    _recolep_presel_py.clear();
    _recolep_presel_pz.clear();
    _recolep_presel_pt.clear();
    _recolep_presel_conept.clear();
    _recolep_presel_charge.clear();
    _recolep_presel_tightcharge.clear();
    _recolep_presel_isGenMatched.clear();
    _recolep_presel_genMatchInd.clear();
    _recolep_presel_isfakeable.clear();
    _recolep_presel_istight.clear();

    for(int i_mu=0; i_mu<n_loose_mu; i_mu++){

      _recolep_presel_pdg.push_back(-13*(*_recomu_charge)[i_mu]);
      _recolep_presel_eta.push_back((*_recomu_eta)[i_mu]);
      _recolep_presel_phi.push_back((*_recomu_phi)[i_mu]);
      _recolep_presel_e.push_back((*_recomu_e)[i_mu]);
      _recolep_presel_px.push_back((*_recomu_px)[i_mu]);
      _recolep_presel_py.push_back((*_recomu_py)[i_mu]);
      _recolep_presel_pz.push_back((*_recomu_pz)[i_mu]);
      _recolep_presel_pt.push_back((*_recomu_pt)[i_mu]);
      _recolep_presel_conept.push_back((*_recomu_conept)[i_mu]);
      _recolep_presel_charge.push_back((*_recomu_charge)[i_mu]);
      _recolep_presel_isGenMatched.push_back((*_recomu_isGenMatched)[i_mu]);
      _recolep_presel_genMatchInd.push_back((*_recomu_genMatchInd)[i_mu]);
      _recolep_presel_tightcharge.push_back( (*_recomu_rel_error_trackpt)[i_mu]<0.2 );
      _recolep_presel_isfakeable.push_back((*_recomu_isfakeable)[i_mu]);
      _recolep_presel_istight.push_back((*_recomu_ismvasel)[i_mu]);

    }

    for(int i_ele=0; i_ele<n_loose_ele; i_ele++){

      _recolep_presel_pdg.push_back(-11*(*_recoele_charge)[i_ele]);
      _recolep_presel_eta.push_back((*_recoele_eta)[i_ele]);
      _recolep_presel_phi.push_back((*_recoele_phi)[i_ele]);
      _recolep_presel_e.push_back((*_recoele_e)[i_ele]);
      _recolep_presel_px.push_back((*_recoele_px)[i_ele]);
      _recolep_presel_py.push_back((*_recoele_py)[i_ele]);
      _recolep_presel_pz.push_back((*_recoele_pz)[i_ele]);
      _recolep_presel_pt.push_back((*_recoele_pt)[i_ele]);
      _recolep_presel_conept.push_back((*_recoele_conept)[i_ele]);
      _recolep_presel_charge.push_back((*_recoele_charge)[i_ele]);
      _recolep_presel_isGenMatched.push_back((*_recoele_isGenMatched)[i_ele]);
      _recolep_presel_genMatchInd.push_back((*_recoele_genMatchInd)[i_ele]);
      _recolep_presel_tightcharge.push_back((*_recoele_isChargeConsistent)[i_ele]);
      _recolep_presel_isfakeable.push_back((*_recoele_isfakeable)[i_ele]);
      _recolep_presel_istight.push_back((*_recoele_ismvasel)[i_ele]);

    }

    //sorted leptons
    vector< pair<int,float> > ilep_pt_pairs;
    for(int i_lep=0; i_lep<_n_loose_lep; i_lep++){
      float pt = _recolep_presel_conept[i_lep];
      pair<int,float> pt_pair = make_pair(i_lep,pt);
      ilep_pt_pairs.push_back(pt_pair);
    }
    sort(ilep_pt_pairs.begin(), ilep_pt_pairs.end(), pT_comparison_pairs);

    for(int i_lep=0; i_lep<_n_loose_lep; i_lep++){

      int i_sort_lep = ilep_pt_pairs[i_lep].first;

      _recolep_loose_pdg.push_back(_recolep_presel_pdg[i_sort_lep]);
      _recolep_loose_eta.push_back(_recolep_presel_eta[i_sort_lep]);
      _recolep_loose_phi.push_back(_recolep_presel_phi[i_sort_lep]);
      _recolep_loose_e.push_back(_recolep_presel_e[i_sort_lep]);
      _recolep_loose_px.push_back(_recolep_presel_px[i_sort_lep]);
      _recolep_loose_py.push_back(_recolep_presel_py[i_sort_lep]);
      _recolep_loose_pz.push_back(_recolep_presel_pz[i_sort_lep]);
      _recolep_loose_pt.push_back(_recolep_presel_pt[i_sort_lep]);
      _recolep_loose_conept.push_back(_recolep_presel_conept[i_sort_lep]);
      _recolep_loose_charge.push_back(_recolep_presel_charge[i_sort_lep]);
      _recolep_loose_tightcharge.push_back(_recolep_presel_tightcharge[i_sort_lep]);
      _recolep_loose_isGenMatched.push_back(_recolep_presel_isGenMatched[i_sort_lep]);
      _recolep_loose_genMatchInd.push_back(_recolep_presel_genMatchInd[i_sort_lep]);
      _recolep_loose_isfakeable.push_back(_recolep_presel_isfakeable[i_sort_lep]);
      _recolep_loose_istight.push_back(_recolep_presel_istight[i_sort_lep]);

    }  

    for(int i_lep=0; i_lep<_n_loose_lep; i_lep++){

      if(_recolep_loose_isfakeable[i_lep]==1){

        _recolep_fakeable_pdg.push_back(_recolep_loose_pdg[i_lep]);
        _recolep_fakeable_eta.push_back(_recolep_loose_eta[i_lep]);
        _recolep_fakeable_phi.push_back(_recolep_loose_phi[i_lep]);
        _recolep_fakeable_e.push_back(_recolep_loose_e[i_lep]);
        _recolep_fakeable_px.push_back(_recolep_loose_px[i_lep]);
        _recolep_fakeable_py.push_back(_recolep_loose_py[i_lep]);
        _recolep_fakeable_pz.push_back(_recolep_loose_pz[i_lep]);
        _recolep_fakeable_pt.push_back(_recolep_loose_pt[i_lep]);
        _recolep_fakeable_conept.push_back(_recolep_loose_conept[i_lep]);
        _recolep_fakeable_charge.push_back(_recolep_loose_charge[i_lep]);
        _recolep_fakeable_tightcharge.push_back(_recolep_loose_tightcharge[i_lep]);
        _recolep_fakeable_isGenMatched.push_back(_recolep_loose_isGenMatched[i_lep]);
        _recolep_fakeable_genMatchInd.push_back(_recolep_loose_genMatchInd[i_lep]);
        _recolep_fakeable_istight.push_back(_recolep_loose_istight[i_lep]);

      }

      if(_recolep_loose_istight[i_lep]==1){

        _recolep_tight_pdg.push_back(_recolep_loose_pdg[i_lep]);
        _recolep_tight_eta.push_back(_recolep_loose_eta[i_lep]);
        _recolep_tight_phi.push_back(_recolep_loose_phi[i_lep]);
        _recolep_tight_e.push_back(_recolep_loose_e[i_lep]);
        _recolep_tight_px.push_back(_recolep_loose_px[i_lep]);
        _recolep_tight_py.push_back(_recolep_loose_py[i_lep]);
        _recolep_tight_pz.push_back(_recolep_loose_pz[i_lep]);
        _recolep_tight_pt.push_back(_recolep_loose_pt[i_lep]);
        _recolep_tight_conept.push_back(_recolep_loose_conept[i_lep]);
        _recolep_tight_charge.push_back(_recolep_loose_charge[i_lep]);
        _recolep_tight_tightcharge.push_back(_recolep_loose_tightcharge[i_lep]);
        _recolep_tight_isGenMatched.push_back(_recolep_loose_isGenMatched[i_lep]);
        _recolep_tight_genMatchInd.push_back(_recolep_loose_genMatchInd[i_lep]);

      }

      _n_fake_lep = _recolep_fakeable_pt.size();
      _n_tight_lep = _recolep_tight_pt.size();


    }


    ////////////////////////////////
    ///////////// Taus /////////////
    ////////////////////////////////

    for(int i_tau=0; i_tau<_n_recotauh; i_tau++){

      if((*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]>0.5){

        _recotauh_VL_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_VL_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_VL_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_VL_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_VL_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_VL_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_VL_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_VL_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_VL_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_VL_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
        _recotauh_VL_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);
        _recotauh_VL_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);

      }

      if((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]>0.5){

        _recotauh_L_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_L_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_L_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_L_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_L_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_L_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_L_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_L_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_L_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_L_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
        _recotauh_L_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);
        _recotauh_L_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);

      }

      if((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]>0.5){

        _recotauh_M_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_M_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_M_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_M_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_M_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_M_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_M_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_M_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_M_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_M_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
        _recotauh_M_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);

      }

    }

    _n_VL_tau = _recotauh_VL_pt.size();
    _n_L_tau = _recotauh_L_pt.size();
    _n_M_tau = _recotauh_M_pt.size();

    ////////////////////////////////
    ///////////// mll  /////////////
    ////////////////////////////////

    for (int i_lep1=0; i_lep1<_n_loose_lep;i_lep1++){
      cout<<_recolep_loose_pt[i_lep1]<<","<<_recolep_loose_eta[i_lep1]<<","<<_recolep_loose_phi[i_lep1]<<","<<_recolep_loose_e[i_lep1]<<endl;
    }

    bool inv_mass_lep_pairs=true;
    if(_n_loose_lep>=2){
      for(int i_lep1=0; i_lep1<_n_loose_lep; i_lep1++){ 
        TLorentzVector lep1; 
        lep1.SetPtEtaPhiE(_recolep_loose_pt[i_lep1],_recolep_loose_eta[i_lep1],_recolep_loose_phi[i_lep1],_recolep_loose_e[i_lep1]);
        cout<<"1: "<<_recolep_loose_pt[i_lep1]<<","<<_recolep_loose_eta[i_lep1]<<","<<_recolep_loose_phi[i_lep1]<<","<<_recolep_loose_e[i_lep1]<<endl;
        for(int i_lep2=i_lep1+1; i_lep2<_n_loose_lep;i_lep2++){   
          TLorentzVector lep2;      
          lep2.SetPtEtaPhiE(_recolep_loose_pt[i_lep2],_recolep_loose_eta[i_lep2],_recolep_loose_phi[i_lep2],_recolep_loose_e[i_lep2]);
          cout<<"2: "<<_recolep_loose_pt[i_lep2]<<","<<_recolep_loose_eta[i_lep2]<<","<<_recolep_loose_phi[i_lep2]<<","<<_recolep_loose_e[i_lep2]<<endl;
          //float m_ll = (lep1 + lep2).M();
          //if(m_ll<12) inv_mass_lep_pairs=false;
        }
      }
    } 

    ////////////////////////////////
    /////////// 1l2tau  ////////////
    ////////////////////////////////

    bool sig_1l2tau_base = //passTriggerMatch &&
      (_n_fake_lep>=1) &&
      ( (_recolep_loose_conept[0]>25 && abs(_recolep_loose_pdg[0])==13) || (_recolep_loose_conept[0]>30 && abs(_recolep_loose_pdg[0])==11) ) &&
      ((abs(_recolep_loose_eta[0]))<2.1) &&
      (_n_tight_lep<=1) &&
      (_n_VL_tau>=2) &&
      ( (_recotauh_VL_pt[0]>30) && (_recotauh_VL_pt[1]>20) ) &&
      inv_mass_lep_pairs;

    bool sig_1l2tau_SR = 
      sig_1l2tau_base &&
      (_recolep_loose_istight[0]==1) &&
      (_recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT[0]>0.5 && _recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT[1]>0.5) &&
      (_recotauh_VL_charge[0]*_recotauh_VL_charge[1]<0) &&
      (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) &&
      _recotauh_VL_isGenMatched[0] && _recotauh_VL_isGenMatched[1] && _recolep_loose_isGenMatched[0];

    if (sig_1l2tau_SR) n_1l2tau_SR += 1;

    bool sig_1l2tau_fake = 
        sig_1l2tau_base &&
        (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) &&
        ( !(_recolep_loose_istight[0]) || !(_recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT[0] && _recotauh_VL_byMediumIsolationMVArun2v2017v2DBoldDMwLT[1]) ) &&        
        (_recotauh_VL_charge[0]*_recotauh_VL_charge[1]<0);

    if (sig_1l2tau_fake) n_1l2tau_fake += 1;

  }

  cout<<"n_1l2tau_SR: "<<n_1l2tau_SR<<endl;  
  cout<<"n_1l2tau_fake: "<<n_1l2tau_fake<<endl;

  /*
  cout<<" "<<endl;
  cout<<"n_2tau_SR: "<<n_2tau_SR<<endl;
  cout<<"n_2tau_fake: "<<n_2tau_fake<<endl;
  cout<<"n_2tau_DY: "<<n_2tau_DY<<endl;
  cout<<" "<<endl;
  cout<<"n_1l1tau_SR: "<<n_1l1tau_SR<<endl;
  cout<<"n_1l1tau_fake<: "<<n_1l1tau_fake<<endl; 
  cout<<" "<<endl;
  cout<<"n_1l2tau_SR<<: "<<n_1l2tau_SR<<endl;  
  cout<<"n_1l2tau_fake: "<<n_1l2tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_2lss_SR_ttH: "<<n_2lss_SR_ttH<<endl;
  cout<<"n_2lss_SR_tH: "<<n_2lss_SR_tH<<endl;
  cout<<"n_2lss_fake_ttH: "<<n_2lss_fake_ttH<<endl;
  cout<<"n_2lss_fake_tH: "<<n_2lss_fake_tH<<endl;
  cout<<"n_2lss_flip_ttH: "<<n_2lss_flip_ttH<<endl;
  cout<<"n_2lss_flip_tH: "<<n_2lss_flip_tH<<endl;
  cout<<" "<<endl;
  cout<<"n_2lss1tau_SR: "<<n_2lss1tau_SR<<endl;
  cout<<"n_2lss1tau_fake: "<<n_2lss1tau_fake<<endl;
  cout<<"n_2lss1tau_flip: "<<n_2lss1tau_flip<<endl;
  cout<<" "<<endl;
  cout<<"n_2los1tau_SR: "<<n_2los1tau_SR<<endl;
  cout<<"n_2los1tau_fake: "<<n_2los1tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_2l2tau_SR: "<<n_2l2tau_SR<<endl;
  cout<<"n_2l2tau_fake: "<<n_2l2tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_3l_SR_ttH: "<<n_3l_SR_ttH<<endl;
  cout<<"n_3l_SR_tH: "<<n_3l_SR_tH<<endl;
  cout<<"n_3l_fake_ttH: "<<n_3l_fake_ttH<<endl;
  cout<<"n_3l_fake_tH: "<<n_3l_fake_tH<<endl;
  cout<<" "<<endl;
  cout<<"n_3l1tau_SR: "<<n_3l1tau_SR<<endl;
  cout<<"n_3l1tau_fake: "<<n_3l1tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_4l_SR: "<<n_4l_SR<<endl;
  cout<<"n_4l_fake: "<<n_4l_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_ttW_CR_SR: "<<n_ttW_CR_SR<<endl;
  cout<<"n_ttW_CR_fake: "<<n_ttW_CR_fake<<endl;
  cout<<"n_ttW_CR_flip: "<<n_ttW_CR_flip<<endl;
  cout<<" "<<endl;
  cout<<"n_ttZ_CR_SR: "<<n_ttZ_CR_SR<<endl;
  cout<<"n_ttZ_CR_fake: "<<n_ttZ_CR_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_WZ_CR_SR: "<<n_WZ_CR_SR<<endl;
  cout<<"n_WZ_CR_fake: "<<n_WZ_CR_fake<<endl;
  cout<<" "<<endl;
  cout<<"n_ZZ_CR_SR: "<<n_ZZ_CR_SR<<endl;
  cout<<"n_ZZ_CR_fake: "<<n_ZZ_CR_fake<<endl;
  */
  

  f_new->cd();
  
  h->Write();

  for(unsigned int i=0; i<tree_new.size();i++)
    tree_new[i]->Write();

  f_new->Close();
  return;

}


void test16(){

  TString fin = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2016/sync_ntuple_converted_ttHNonbb_2016_v10.root";
  TString fout = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/2016/sync_ntuple_splitted_ttHNonbb_2016_v1.root";

  split_tree(fin,fout,0,0,true);

}
