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

#include "headers/triggerFilter.cc"

using namespace std;


bool pT_comparison_pairs(pair<int,float> pair1, pair<int,float> pair2){
  return pair1.second>pair2.second;
}


void split_tree(TString filename_in, TString filename_out,
		int i_split1=0, int i_split2=0,
		bool isMC=true, int year=2016){

  produce_triggerlist();

  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++){
    tree->Add(list[i]);
  }

  TH1F* h=new TH1F("h_counter","h_counter",3,0,3);


  //Old branches used

  Long64_t _EventNumber;
  int _year;  
 
  Long64_t _triggerbit; 
  Int_t _metfilterbit;
  bool _passecalBadCalibFilterUpdate;

  vector<int> *_recolep_charge;
  vector<int> *_recolep_pdg;
  vector<float> *_recolep_e;
  vector<float> *_recolep_px;
  vector<float> *_recolep_py;
  vector<float> *_recolep_pz;
  vector<float> *_recolep_pt;
  vector<float> *_recolep_conept;
  vector<float> *_recolep_eta;
  vector<float> *_recolep_phi;
  vector<bool> *_recolep_isfakeable;
  vector<bool> *_recolep_ismvasel;
  vector<bool> *_recolep_tightcharge;
  vector<bool> *_recolep_isGenMatched;
  vector<int> *_recolep_genMatchInd;

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

  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_px;
  vector<float> *_recoPFJet_py;
  vector<float> *_recoPFJet_pz;

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("year",&_year);

  tree->SetBranchAddress("triggerbit",&_triggerbit);
  tree->SetBranchAddress("metfilterbit",&_metfilterbit);
  tree->SetBranchAddress("passecalBadCalibFilterUpdate",&_passecalBadCalibFilterUpdate);

  tree->SetBranchAddress("recolep_charge",&_recolep_charge);
  tree->SetBranchAddress("recolep_pdg",&_recolep_pdg);
  tree->SetBranchAddress("recolep_e",&_recolep_e);
  tree->SetBranchAddress("recolep_px",&_recolep_px);
  tree->SetBranchAddress("recolep_py",&_recolep_py);
  tree->SetBranchAddress("recolep_pz",&_recolep_pz);
  tree->SetBranchAddress("recolep_pt",&_recolep_pt);
  tree->SetBranchAddress("recolep_conept",&_recolep_conept);
  tree->SetBranchAddress("recolep_eta",&_recolep_eta);
  tree->SetBranchAddress("recolep_phi",&_recolep_phi);
  tree->SetBranchAddress("recolep_isfakeable",&_recolep_isfakeable);
  tree->SetBranchAddress("recolep_ismvasel",&_recolep_ismvasel);
  tree->SetBranchAddress("recolep_tightcharge",&_recolep_tightcharge);
  tree->SetBranchAddress("recolep_isGenMatched",&_recolep_isGenMatched);
  tree->SetBranchAddress("recolep_genMatchInd",&_recolep_genMatchInd);

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

  tree->SetBranchAddress("recoPFJet_e", &_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  
  //Long64_t nentries=100;
  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(filename_out);
  
  /*if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/
  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_2tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_1l1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_1l1tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_1l2tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_1l2tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_2lss_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_fake=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss_flip=tree->GetTree()->CloneTree(0);

  TTree* tree_2lss1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss1tau_fake=tree->GetTree()->CloneTree(0);
  TTree* tree_2lss1tau_flip=tree->GetTree()->CloneTree(0);

  TTree* tree_2los1tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2los1tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_2l2tau_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_2l2tau_fake=tree->GetTree()->CloneTree(0);

  TTree* tree_3l_SR=tree->GetTree()->CloneTree(0);
  TTree* tree_3l_fake=tree->GetTree()->CloneTree(0);

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
  
  tree_1l1tau_SR->SetNameTitle("HTauTauTree_1l1tau_SR","HTauTauTree_1l1tau_SR");
  tree_1l1tau_fake->SetNameTitle("HTauTauTree_1l1tau_fake","HTauTauTree_1l1tau_fake");

  tree_1l2tau_SR->SetNameTitle("HTauTauTree_1l2tau_SR","HTauTauTree_1l2tau_SR");
  tree_1l2tau_fake->SetNameTitle("HTauTauTree_1l2tau_fake","HTauTauTree_1l2tau_fake");

  tree_2lss_SR->SetNameTitle("HTauTauTree_2lss_SR","HTauTauTree_2lss_SR");
  tree_2lss_fake->SetNameTitle("HTauTauTree_2lss_fake","HTauTauTree_2lss_fake");
  tree_2lss_flip->SetNameTitle("HTauTauTree_2lss_flip","HTauTauTree_2lss_flip");

  tree_2lss1tau_SR->SetNameTitle("HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_SR");
  tree_2lss1tau_fake->SetNameTitle("HTauTauTree_2lss1tau_fake","HTauTauTree_2lss1tau_fake");
  tree_2lss1tau_flip->SetNameTitle("HTauTauTree_2lss1tau_flip","HTauTauTree_2lss1tau_flip");

  tree_2los1tau_SR->SetNameTitle("HTauTauTree_2los1tau_SR","HTauTauTree_2los1tau_SR");
  tree_2los1tau_fake->SetNameTitle("HTauTauTree_2los1tau_fake","HTauTauTree_2los1tau_fake");

  tree_2l2tau_SR->SetNameTitle("HTauTauTree_2l2tau_SR","HTauTauTree_2l2tau_SR");
  tree_2l2tau_fake->SetNameTitle("HTauTauTree_2l2tau_fake","HTauTauTree_2l2tau_fake");

  tree_3l_SR->SetNameTitle("HTauTauTree_3l_SR","HTauTauTree_3l_SR");
  tree_3l_fake->SetNameTitle("HTauTauTree_3l_fake","HTauTauTree_3l_fake");

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

  tree_new.push_back(tree_1l1tau_SR);
  tree_new.push_back(tree_1l1tau_fake);

  tree_new.push_back(tree_1l2tau_SR);
  tree_new.push_back(tree_1l2tau_fake);

  tree_new.push_back(tree_2lss_SR);
  tree_new.push_back(tree_2lss_fake);
  tree_new.push_back(tree_2lss_flip);

  tree_new.push_back(tree_2lss1tau_SR);
  tree_new.push_back(tree_2lss1tau_fake);
  tree_new.push_back(tree_2lss1tau_flip);

  tree_new.push_back(tree_2los1tau_SR);
  tree_new.push_back(tree_2los1tau_fake);

  tree_new.push_back(tree_2l2tau_SR);
  tree_new.push_back(tree_2l2tau_fake);

  tree_new.push_back(tree_3l_SR);
  tree_new.push_back(tree_3l_fake);

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

  int n_1l1tau_SR = 0;
  int n_1l1tau_fake = 0; 

  int n_1l2tau_SR = 0;  
  int n_1l2tau_fake = 0;

  int n_2lss_SR = 0;
  int n_2lss_fake = 0;
  int n_2lss_flip = 0;
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

  int n_3l_SR = 0;
  int n_3l_fake = 0;
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

  2010 1l1tau_SR
  2020 1l1tau_fake

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
  */

  int _n_loose_lep;
  int _n_fakeable_lep;
  int _n_tight_lep;

  int _n_recolep_sel;
  int _n_recotauh_sel;

  vector<int>   _recolep_fakeable_charge;
  vector<int>   _recolep_fakeable_pdg;
  vector<float> _recolep_fakeable_e;
  vector<float> _recolep_fakeable_px;
  vector<float> _recolep_fakeable_py;
  vector<float> _recolep_fakeable_pz;
  vector<float> _recolep_fakeable_pt;
  vector<float> _recolep_fakeable_conept;
  vector<float> _recolep_fakeable_eta;
  vector<float> _recolep_fakeable_phi;
  vector<bool>  _recolep_fakeable_isfakeable;
  vector<bool>  _recolep_fakeable_ismvasel;
  vector<bool>  _recolep_fakeable_tightcharge;
  vector<bool>  _recolep_fakeable_isGenMatched;
  vector<int>   _recolep_fakeable_genMatchInd;

  vector<int>   _recolep_tight_charge;
  vector<int>   _recolep_tight_pdg;
  vector<float> _recolep_tight_e;
  vector<float> _recolep_tight_px;
  vector<float> _recolep_tight_py;
  vector<float> _recolep_tight_pz;
  vector<float> _recolep_tight_pt;
  vector<float> _recolep_tight_conept;
  vector<float> _recolep_tight_eta;
  vector<float> _recolep_tight_phi;
  vector<bool>  _recolep_tight_isfakeable;
  vector<bool>  _recolep_tight_ismvasel;
  vector<bool>  _recolep_tight_tightcharge;
  vector<bool>  _recolep_tight_isGenMatched;
  vector<int>   _recolep_tight_genMatchInd;

  vector<int>   _recolep_sel_charge;
  vector<int>   _recolep_sel_pdg;
  vector<float> _recolep_sel_e;
  vector<float> _recolep_sel_px;
  vector<float> _recolep_sel_py;
  vector<float> _recolep_sel_pz;
  vector<float> _recolep_sel_pt;
  vector<float> _recolep_sel_conept;
  vector<float> _recolep_sel_eta;
  vector<float> _recolep_sel_phi;
  vector<bool>  _recolep_sel_isfakeable;
  vector<bool>  _recolep_sel_ismvasel;
  vector<bool>  _recolep_sel_tightcharge;
  vector<bool>  _recolep_sel_isGenMatched;
  vector<int>   _recolep_sel_genMatchInd;

  int _n_fakeable_tau;
  int _n_tight_WPL_tau;
  int _n_tight_WPM_tau;

  vector<float> _recotauh_tight_WPL_eta;
  vector<float> _recotauh_tight_WPL_phi;
  vector<float> _recotauh_tight_WPL_pt;
  vector<int>   _recotauh_tight_WPL_charge;
  vector<int>   _recotauh_tight_WPL_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPL_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPL_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPL_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPL_decayMode;
  vector<float> _recotauh_tight_WPL_e;
  vector<float> _recotauh_tight_WPL_px;
  vector<float> _recotauh_tight_WPL_py;
  vector<float> _recotauh_tight_WPL_pz;
  vector<bool>  _recotauh_tight_WPL_isGenMatched;
  vector<int>   _recotauh_tight_WPL_genMatchInd;

  vector<float> _recotauh_tight_WPM_eta;
  vector<float> _recotauh_tight_WPM_phi;
  vector<float> _recotauh_tight_WPM_pt;
  vector<int>   _recotauh_tight_WPM_charge;
  vector<int>   _recotauh_tight_WPM_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPM_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPM_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPM_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_tight_WPM_decayMode;
  vector<float> _recotauh_tight_WPM_e;
  vector<float> _recotauh_tight_WPM_px;
  vector<float> _recotauh_tight_WPM_py;
  vector<float> _recotauh_tight_WPM_pz;
  vector<bool>  _recotauh_tight_WPM_isGenMatched;
  vector<int>   _recotauh_tight_WPM_genMatchInd;

  vector<float> _recotauh_sel_eta;
  vector<float> _recotauh_sel_phi;
  vector<float> _recotauh_sel_pt;
  vector<int>   _recotauh_sel_charge;
  vector<int>   _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_sel_decayMode;
  vector<float> _recotauh_sel_e;
  vector<float> _recotauh_sel_px;
  vector<float> _recotauh_sel_py;
  vector<float> _recotauh_sel_pz;
  vector<bool>  _recotauh_sel_isGenMatched;
  vector<int>   _recotauh_sel_genMatchInd;

  int _n_light_jet;

  bool _isGenMatched;

  bool _is_ttH_like;
  bool _is_tH_like_and_not_ttH_like;


  /*float _lep1_conePt;
  float _lep2_conePt;
  float _lep3_conePt;
  float _lep1_charge;
  float _mindr_lep1_jet;
  float _mindr_lep2_jet;
  float _mindr_lep3_jet;
  float _mindr_tau1_jet;
  float _mindr_tau2_jet;
  float _avg_dr_jet;
  float _avg_dr_lep_tau;
  float _max_dr_lep_tau;
  float _mindr_tau_jet;
  float _min_dr_lep_tau;
  float _min_dr_lep_jet;
  float _dr_leps;
  float _dr_taus;
  float _dR_lep_tau_ss;
  float _dr_lep1_tau;
  float _dr_lep2_tau;
  float _max_lep_eta;
  float _mT_lep1;
  float _mT_lep2;
  float _mTauTauVis;
  float _mTauTauVis1;
  float _mTauTauVis2;
  float _mbb;
  float _mbb_loose;
  float _cosThetaS_hadTau;
  float _HTT;
  float _HadTop_pt;
  float _Hj_tagger;
  int _nBJetLoose;
  int _nLightJet;
  int _nBJetMedium;
  float _massL;*/


  for(unsigned int i=0; i<tree_new.size();i++){
    
    tree_new[i]->Branch("category",&_category);

    tree_new[i]->Branch("n_loose_lep",&_n_loose_lep);
    tree_new[i]->Branch("n_fakeable_lep",&_n_fakeable_lep);
    tree_new[i]->Branch("n_tight_lep",&_n_tight_lep);

    tree_new[i]->Branch("n_recolep_sel",&_n_recolep_sel);
    tree_new[i]->Branch("n_recotauh_sel",&_n_recotauh_sel);

    tree_new[i]->Branch("recolep_fakeable_charge",&_recolep_fakeable_charge);
    tree_new[i]->Branch("recolep_fakeable_pdg",&_recolep_fakeable_pdg);
    tree_new[i]->Branch("recolep_fakeable_e",&_recolep_fakeable_e);
    tree_new[i]->Branch("recolep_fakeable_px",&_recolep_fakeable_px);
    tree_new[i]->Branch("recolep_fakeable_py",&_recolep_fakeable_py);
    tree_new[i]->Branch("recolep_fakeable_pz",&_recolep_fakeable_pz);
    tree_new[i]->Branch("recolep_fakeable_pt",&_recolep_fakeable_pt);
    tree_new[i]->Branch("recolep_fakeable_conept",&_recolep_fakeable_conept);
    tree_new[i]->Branch("recolep_fakeable_eta",&_recolep_fakeable_eta);
    tree_new[i]->Branch("recolep_fakeable_phi",&_recolep_fakeable_phi);
    tree_new[i]->Branch("recolep_fakeable_isfakeable",&_recolep_fakeable_isfakeable);
    tree_new[i]->Branch("recolep_fakeable_ismvasel",&_recolep_fakeable_ismvasel);
    tree_new[i]->Branch("recolep_fakeable_tightcharge",&_recolep_fakeable_tightcharge);
    tree_new[i]->Branch("recolep_fakeable_isGenMatched",&_recolep_fakeable_isGenMatched);
    tree_new[i]->Branch("recolep_fakeable_genMatchInd",&_recolep_fakeable_genMatchInd);

    tree_new[i]->Branch("recolep_tight_charge",&_recolep_tight_charge);
    tree_new[i]->Branch("recolep_tight_pdg",&_recolep_tight_pdg);
    tree_new[i]->Branch("recolep_tight_e",&_recolep_tight_e);
    tree_new[i]->Branch("recolep_tight_px",&_recolep_tight_px);
    tree_new[i]->Branch("recolep_tight_py",&_recolep_tight_py);
    tree_new[i]->Branch("recolep_tight_pz",&_recolep_tight_pz);
    tree_new[i]->Branch("recolep_tight_pt",&_recolep_tight_pt);
    tree_new[i]->Branch("recolep_tight_conept",&_recolep_tight_conept);
    tree_new[i]->Branch("recolep_tight_eta",&_recolep_tight_eta);
    tree_new[i]->Branch("recolep_tight_phi",&_recolep_tight_phi);
    tree_new[i]->Branch("recolep_tight_isfakeable",&_recolep_tight_isfakeable);
    tree_new[i]->Branch("recolep_tight_ismvasel",&_recolep_tight_ismvasel);
    tree_new[i]->Branch("recolep_tight_tightcharge",&_recolep_tight_tightcharge);
    tree_new[i]->Branch("recolep_tight_isGenMatched",&_recolep_tight_isGenMatched);
    tree_new[i]->Branch("recolep_tight_genMatchInd",&_recolep_tight_genMatchInd);

    tree_new[i]->Branch("recolep_sel_charge",&_recolep_sel_charge);
    tree_new[i]->Branch("recolep_sel_pdg",&_recolep_sel_pdg);
    tree_new[i]->Branch("recolep_sel_e",&_recolep_sel_e);
    tree_new[i]->Branch("recolep_sel_px",&_recolep_sel_px);
    tree_new[i]->Branch("recolep_sel_py",&_recolep_sel_py);
    tree_new[i]->Branch("recolep_sel_pz",&_recolep_sel_pz);
    tree_new[i]->Branch("recolep_sel_pt",&_recolep_sel_pt);
    tree_new[i]->Branch("recolep_sel_conept",&_recolep_sel_conept);
    tree_new[i]->Branch("recolep_sel_eta",&_recolep_sel_eta);
    tree_new[i]->Branch("recolep_sel_phi",&_recolep_sel_phi);
    tree_new[i]->Branch("recolep_sel_isfakeable",&_recolep_sel_isfakeable);
    tree_new[i]->Branch("recolep_sel_ismvasel",&_recolep_sel_ismvasel);
    tree_new[i]->Branch("recolep_sel_tightcharge",&_recolep_sel_tightcharge);
    tree_new[i]->Branch("recolep_sel_isGenMatched",&_recolep_sel_isGenMatched);
    tree_new[i]->Branch("recolep_sel_genMatchInd",&_recolep_sel_genMatchInd);

    tree_new[i]->Branch("n_fakeable_tau",&_n_fakeable_tau);
    tree_new[i]->Branch("n_tight_WPL_tau",&_n_tight_WPL_tau);
    tree_new[i]->Branch("n_tight_WPM_tau",&_n_tight_WPM_tau);

    tree_new[i]->Branch("recotauh_tight_WPL_eta",&_recotauh_tight_WPL_eta);
    tree_new[i]->Branch("recotauh_tight_WPL_phi",&_recotauh_tight_WPL_phi);
    tree_new[i]->Branch("recotauh_tight_WPL_pt",&_recotauh_tight_WPL_pt);
    tree_new[i]->Branch("recotauh_tight_WPL_charge",&_recotauh_tight_WPL_charge);
    tree_new[i]->Branch("recotauh_tight_WPL_byVLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPL_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPL_byLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPL_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPL_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPL_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPL_byTightIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPL_byTightIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPL_decayMode",&_recotauh_tight_WPL_decayMode);
    tree_new[i]->Branch("recotauh_tight_WPL_e",&_recotauh_tight_WPL_e);
    tree_new[i]->Branch("recotauh_tight_WPL_px",&_recotauh_tight_WPL_px);
    tree_new[i]->Branch("recotauh_tight_WPL_py",&_recotauh_tight_WPL_py);
    tree_new[i]->Branch("recotauh_tight_WPL_pz",&_recotauh_tight_WPL_pz);
    tree_new[i]->Branch("recotauh_tight_WPL_isGenMatched",&_recotauh_tight_WPL_isGenMatched);
    tree_new[i]->Branch("recotauh_tight_WPL_genMatchInd",&_recotauh_tight_WPL_genMatchInd);

    tree_new[i]->Branch("recotauh_tight_WPM_eta",&_recotauh_tight_WPM_eta);
    tree_new[i]->Branch("recotauh_tight_WPM_phi",&_recotauh_tight_WPM_phi);
    tree_new[i]->Branch("recotauh_tight_WPM_pt",&_recotauh_tight_WPM_pt);
    tree_new[i]->Branch("recotauh_tight_WPM_charge",&_recotauh_tight_WPM_charge);
    tree_new[i]->Branch("recotauh_tight_WPM_byVLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPM_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPM_byLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPM_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPM_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPM_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPM_byTightIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_tight_WPM_byTightIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_tight_WPM_decayMode",&_recotauh_tight_WPM_decayMode);
    tree_new[i]->Branch("recotauh_tight_WPM_e",&_recotauh_tight_WPM_e);
    tree_new[i]->Branch("recotauh_tight_WPM_px",&_recotauh_tight_WPM_px);
    tree_new[i]->Branch("recotauh_tight_WPM_py",&_recotauh_tight_WPM_py);
    tree_new[i]->Branch("recotauh_tight_WPM_pz",&_recotauh_tight_WPM_pz);
    tree_new[i]->Branch("recotauh_tight_WPM_isGenMatched",&_recotauh_tight_WPM_isGenMatched);
    tree_new[i]->Branch("recotauh_tight_WPM_genMatchInd",&_recotauh_tight_WPM_genMatchInd);

    tree_new[i]->Branch("recotauh_sel_eta",&_recotauh_sel_eta);
    tree_new[i]->Branch("recotauh_sel_phi",&_recotauh_sel_phi);
    tree_new[i]->Branch("recotauh_sel_pt",&_recotauh_sel_pt);
    tree_new[i]->Branch("recotauh_sel_charge",&_recotauh_sel_charge);
    tree_new[i]->Branch("recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT);
    tree_new[i]->Branch("recotauh_sel_decayMode",&_recotauh_sel_decayMode);
    tree_new[i]->Branch("recotauh_sel_e",&_recotauh_sel_e);
    tree_new[i]->Branch("recotauh_sel_px",&_recotauh_sel_px);
    tree_new[i]->Branch("recotauh_sel_py",&_recotauh_sel_py);
    tree_new[i]->Branch("recotauh_sel_pz",&_recotauh_sel_pz);
    tree_new[i]->Branch("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);
    tree_new[i]->Branch("recotauh_sel_genMatchInd",&_recotauh_sel_genMatchInd);

    tree_new[i]->Branch("n_light_jet",&_n_light_jet);

    tree_new[i]->Branch("isGenMatched",&_isGenMatched);

    tree_new[i]->Branch("is_ttH_like",&_is_ttH_like);
    tree_new[i]->Branch("is_tH_like_and_not_ttH_like",&_is_tH_like_and_not_ttH_like);

    /*tree_new[i]->Branch("lep1_conePt",&_lep1_conePt);
    tree_new[i]->Branch("lep2_conePt",&_lep2_conePt);
    tree_new[i]->Branch("lep3_conePt",&_lep3_conePt);
    tree_new[i]->Branch("lep1_charge",&_lep1_charge);
    tree_new[i]->Branch("mindr_lep1_jet",&_mindr_lep1_jet);
    tree_new[i]->Branch("mindr_lep2_jet",&_mindr_lep2_jet);
    tree_new[i]->Branch("mindr_lep3_jet",&_mindr_lep3_jet);
    tree_new[i]->Branch("mindr_tau1_jet",&_mindr_tau1_jet);
    tree_new[i]->Branch("mindr_tau2_jet",&_mindr_tau2_jet);
    tree_new[i]->Branch("avg_dr_jet",&_avg_dr_jet);
    tree_new[i]->Branch("avg_dr_lep_tau",&_avg_dr_lep_tau);
    tree_new[i]->Branch("max_dr_lep_tau",&_max_dr_lep_tau);
    tree_new[i]->Branch("mindr_tau_jet",&_mindr_tau_jet);
    tree_new[i]->Branch("min_dr_lep_tau",&_min_dr_lep_tau);
    tree_new[i]->Branch("min_dr_lep_jet",&_min_dr_lep_jet);
    tree_new[i]->Branch("dr_leps",&_dr_leps);
    tree_new[i]->Branch("dr_taus",&_dr_taus);
    tree_new[i]->Branch("dR_lep_tau_ss",&_dR_lep_tau_ss);
    tree_new[i]->Branch("dr_lep1_tau",&_dr_lep1_tau);
    tree_new[i]->Branch("dr_lep2_tau",&_dr_lep2_tau);
    tree_new[i]->Branch("max_lep_eta",&_max_lep_eta);
    tree_new[i]->Branch("mT_lep1",&_mT_lep1);
    tree_new[i]->Branch("mT_lep2",&_mT_lep2);
    tree_new[i]->Branch("mTauTauVis",&_mTauTauVis);
    tree_new[i]->Branch("mTauTauVis1",&_mTauTauVis1);
    tree_new[i]->Branch("mTauTauVis2",&_mTauTauVis2);
    tree_new[i]->Branch("mbb",&_mbb);
    tree_new[i]->Branch("mbb_loose",&_mbb_loose);
    tree_new[i]->Branch("cosThetaS_hadTau",&_cosThetaS_hadTau);
    tree_new[i]->Branch("HTT",&_HTT);
    tree_new[i]->Branch("HadTop_pt",&_HadTop_pt);
    tree_new[i]->Branch("Hj_tagger",&_Hj_tagger);
    tree_new[i]->Branch("nBJetLoose",&_nBJetLoose);
    tree_new[i]->Branch("nLightJet",&_nLightJet);
    tree_new[i]->Branch("nBJetMedium",&_nBJetMedium);
    tree_new[i]->Branch("massL",&_massL);*/
   
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

    _n_loose_lep = 0;
    _n_fakeable_lep = 0;
    _n_tight_lep = 0;

    _n_recolep_sel = 0;
    _n_recotauh_sel = 0;

    _recolep_fakeable_charge.clear();
    _recolep_fakeable_pdg.clear();
    _recolep_fakeable_e.clear();
    _recolep_fakeable_px.clear();
    _recolep_fakeable_py.clear();
    _recolep_fakeable_pz.clear();
    _recolep_fakeable_pt.clear();
    _recolep_fakeable_conept.clear();
    _recolep_fakeable_eta.clear();
    _recolep_fakeable_phi.clear();
    _recolep_fakeable_isfakeable.clear();
    _recolep_fakeable_ismvasel.clear();
    _recolep_fakeable_tightcharge.clear();
    _recolep_fakeable_isGenMatched.clear();
    _recolep_fakeable_genMatchInd.clear();

    _recolep_tight_charge.clear();
    _recolep_tight_pdg.clear();
    _recolep_tight_e.clear();
    _recolep_tight_px.clear();
    _recolep_tight_py.clear();
    _recolep_tight_pz.clear();
    _recolep_tight_pt.clear();
    _recolep_tight_conept.clear();
    _recolep_tight_eta.clear();
    _recolep_tight_phi.clear();
    _recolep_tight_isfakeable.clear();
    _recolep_tight_ismvasel.clear();
    _recolep_tight_tightcharge.clear();
    _recolep_tight_isGenMatched.clear();
    _recolep_tight_genMatchInd.clear();

    _recolep_sel_charge.clear();
    _recolep_sel_pdg.clear();
    _recolep_sel_e.clear();
    _recolep_sel_px.clear();
    _recolep_sel_py.clear();
    _recolep_sel_pz.clear();
    _recolep_sel_pt.clear();
    _recolep_sel_conept.clear();
    _recolep_sel_eta.clear();
    _recolep_sel_phi.clear();
    _recolep_sel_isfakeable.clear();
    _recolep_sel_ismvasel.clear();
    _recolep_sel_tightcharge.clear();
    _recolep_sel_isGenMatched.clear();
    _recolep_sel_genMatchInd.clear();

    _n_fakeable_tau = 0;
    _n_tight_WPL_tau = 0;
    _n_tight_WPM_tau = 0;

    _recotauh_tight_WPL_eta.clear();
    _recotauh_tight_WPL_phi.clear();
    _recotauh_tight_WPL_pt.clear();
    _recotauh_tight_WPL_charge.clear();
    _recotauh_tight_WPL_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPL_byLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPL_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPL_byTightIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPL_decayMode.clear();
    _recotauh_tight_WPL_e.clear();
    _recotauh_tight_WPL_px.clear();
    _recotauh_tight_WPL_py.clear();
    _recotauh_tight_WPL_pz.clear();
    _recotauh_tight_WPL_isGenMatched.clear();
    _recotauh_tight_WPL_genMatchInd.clear();

    _recotauh_tight_WPM_eta.clear();
    _recotauh_tight_WPM_phi.clear();
    _recotauh_tight_WPM_pt.clear();
    _recotauh_tight_WPM_charge.clear();
    _recotauh_tight_WPM_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPM_byLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPM_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPM_byTightIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_tight_WPM_decayMode.clear();
    _recotauh_tight_WPM_e.clear();
    _recotauh_tight_WPM_px.clear();
    _recotauh_tight_WPM_py.clear();
    _recotauh_tight_WPM_pz.clear();
    _recotauh_tight_WPM_isGenMatched.clear();
    _recotauh_tight_WPM_genMatchInd.clear();

    _recotauh_sel_eta.clear();
    _recotauh_sel_phi.clear();
    _recotauh_sel_pt.clear();
    _recotauh_sel_charge.clear();
    _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_decayMode.clear();
    _recotauh_sel_e.clear();
    _recotauh_sel_px.clear();
    _recotauh_sel_py.clear();
    _recotauh_sel_pz.clear();
    _recotauh_sel_isGenMatched.clear();
    _recotauh_sel_genMatchInd.clear();

    _n_light_jet = 0;

    _isGenMatched = 0;

    _is_ttH_like = 0;
    _is_tH_like_and_not_ttH_like = 0;

    //MVA variables

    /*_lep1_conePt = -999.;
    _lep2_conePt = -999.;
    _lep3_conePt = -999.;
    _lep1_charge = -999.;
    _mindr_lep1_jet = -999.;
    _mindr_lep2_jet = -999.;
    _mindr_lep3_jet = -999.;
    _mindr_tau1_jet = -999.;
    _mindr_tau2_jet = -999.;
    _avg_dr_jet = -999.;
    _avg_dr_lep_tau = -999.;
    _max_dr_lep_tau = -999.;
    _mindr_tau_jet = -999.;
    _min_dr_lep_tau = -999.;
    _min_dr_lep_jet = -999.;
    _dr_leps = -999.;
    _dr_taus = -999.;
    _dR_lep_tau_ss = -999.;
    _dr_lep1_tau = -999.;
    _dr_lep2_tau = -999.;
    _max_lep_eta = -999.;
    _mT_lep1 = -999.;
    _mT_lep2 = -999.;
    _mTauTauVis = -999.;
    _mTauTauVis1 = -999.;
    _mTauTauVis2 = -999.;
    _mbb = -999.;
    _mbb_loose = -999.;
    _cosThetaS_hadTau = -999.;
    _HTT = -999.;
    _HadTop_pt = -999.;
    _Hj_tagger = -999.;
    _nBJetLoose = -999.;
    _nLightJet = -999.;
    _nBJetMedium = -999.;
    _massL = -999.;*/


    // old branches

    _EventNumber = 0;  
    _year = 0;
 
    _triggerbit = 0;  
    _metfilterbit = 0;  
    _passecalBadCalibFilterUpdate = 0;

    _recolep_charge = 0;
    _recolep_pdg = 0;
    _recolep_e = 0;
    _recolep_px = 0;
    _recolep_py = 0;
    _recolep_pz = 0;
    _recolep_pt = 0;
    _recolep_conept = 0;
    _recolep_eta = 0;
    _recolep_phi = 0;
    _recolep_isfakeable = 0;
    _recolep_ismvasel = 0;
    _recolep_tightcharge = 0;
    _recolep_isGenMatched = 0;
    _recolep_genMatchInd = 0;

    _recomu_charge = 0;
    _recomu_e = 0;
    _recomu_px = 0;
    _recomu_py = 0;
    _recomu_pz = 0;
    _recomu_pt = 0;
    _recomu_conept = 0;
    _recomu_eta = 0;
    _recomu_phi = 0;
    _recomu_ismvasel = 0;
    _recomu_isfakeable = 0;
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
    _recoele_ismvasel = 0;
    _recoele_isfakeable = 0;
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
    _recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT = 0;
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
    _recotauh_decayMode = 0;
    _recotauh_e = 0;
    _recotauh_px = 0;
    _recotauh_py = 0;
    _recotauh_pz = 0;
    _recotauh_isGenMatched = 0;
    _recotauh_genMatchInd = 0;

    _recoPFJet_e = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;

    tree->GetEntry(i);


    /////////////////////////////////
    ////////// MET filters //////////
    /////////////////////////////////

    bool Flag_goodVertices = (_metfilterbit>>0)&1;
    bool Flag_HBHENoiseFilter = (_metfilterbit>>1)&1;
    bool Flag_HBHENoiseIsoFilter = (_metfilterbit>>2)&1;
    bool Flag_EcalDeadCellTriggerPrimitiveFilter = (_metfilterbit>>3)&1;
    bool Flag_globalSuperTightHalo2016Filter = (_metfilterbit>>4)&1;
    bool Flag_BadPFMuonFilter = (_metfilterbit>>5)&1;
    bool Flag_BadChargedCandidateFilter = (_metfilterbit>>6)&1;
    bool Flag_eeBadScFilter = (_metfilterbit>>7)&1;
    bool Flag_ecalBadCalibReducedMINIAODFilter = _passecalBadCalibFilterUpdate;

    bool metcut_base = Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter;
    
    if (_year == 2017 || _year == 2018) metcut_base = metcut_base && Flag_ecalBadCalibReducedMINIAODFilter;
    if (!isMC) metcut_base = metcut_base && Flag_eeBadScFilter;

    ////////////////////////////////////////
    ////////// Trigger selections //////////
    ////////////////////////////////////////

    bool pass_e   = pass_trigger_list_1e(_triggerbit);
    bool pass_m   = pass_trigger_list_1m(_triggerbit);
    bool pass_2e  = pass_trigger_list_2e(_triggerbit); 
    bool pass_2m  = pass_trigger_list_2m(_triggerbit);
    bool pass_em  = pass_trigger_list_em(_triggerbit);
    bool pass_et  = pass_trigger_list_et(_triggerbit);
    bool pass_mt  = pass_trigger_list_mt(_triggerbit);
    bool pass_2t  = pass_trigger_list_2t(_triggerbit);
    bool pass_3e  = pass_trigger_list_3e(_triggerbit);
    bool pass_m2e = pass_trigger_list_m2e(_triggerbit);
    bool pass_2me = pass_trigger_list_e2m(_triggerbit);
    bool pass_3m  = pass_trigger_list_3m(_triggerbit);
    

    /////////////////////////////////
    //////////// Leptons ////////////
    /////////////////////////////////

    _n_loose_lep = (*_recolep_pt).size();

    for(int i_lep=0; i_lep<_n_loose_lep; i_lep++){

      
      if((*_recolep_isfakeable)[i_lep]==1){

        _recolep_fakeable_charge.push_back((*_recolep_charge)[i_lep]);
        _recolep_fakeable_pdg.push_back((*_recolep_pdg)[i_lep]);
        _recolep_fakeable_e.push_back((*_recolep_e)[i_lep]);
        _recolep_fakeable_px.push_back((*_recolep_px)[i_lep]);
        _recolep_fakeable_py.push_back((*_recolep_py)[i_lep]);
        _recolep_fakeable_pz.push_back((*_recolep_pz)[i_lep]);
        _recolep_fakeable_pt.push_back((*_recolep_pt)[i_lep]);
        _recolep_fakeable_conept.push_back((*_recolep_conept)[i_lep]);       
        _recolep_fakeable_eta.push_back((*_recolep_eta)[i_lep]);
        _recolep_fakeable_phi.push_back((*_recolep_phi)[i_lep]);
        _recolep_fakeable_isfakeable.push_back((*_recolep_isfakeable)[i_lep]);
        _recolep_fakeable_ismvasel.push_back((*_recolep_ismvasel)[i_lep]);
        _recolep_fakeable_tightcharge.push_back((*_recolep_tightcharge)[i_lep]);
        _recolep_fakeable_isGenMatched.push_back((*_recolep_isGenMatched)[i_lep]);
        _recolep_fakeable_genMatchInd.push_back((*_recolep_genMatchInd)[i_lep]);

      }

      if((*_recolep_ismvasel)[i_lep]==1){

        _recolep_tight_charge.push_back((*_recolep_charge)[i_lep]);
        _recolep_tight_pdg.push_back((*_recolep_pdg)[i_lep]);
        _recolep_tight_e.push_back((*_recolep_e)[i_lep]);
        _recolep_tight_px.push_back((*_recolep_px)[i_lep]);
        _recolep_tight_py.push_back((*_recolep_py)[i_lep]);
        _recolep_tight_pz.push_back((*_recolep_pz)[i_lep]);
        _recolep_tight_pt.push_back((*_recolep_pt)[i_lep]);
        _recolep_tight_conept.push_back((*_recolep_conept)[i_lep]);       
        _recolep_tight_eta.push_back((*_recolep_eta)[i_lep]);
        _recolep_tight_phi.push_back((*_recolep_phi)[i_lep]);
        _recolep_tight_isfakeable.push_back((*_recolep_isfakeable)[i_lep]);
        _recolep_tight_ismvasel.push_back((*_recolep_ismvasel)[i_lep]);
        _recolep_tight_tightcharge.push_back((*_recolep_tightcharge)[i_lep]);
        _recolep_tight_isGenMatched.push_back((*_recolep_isGenMatched)[i_lep]);
        _recolep_tight_genMatchInd.push_back((*_recolep_genMatchInd)[i_lep]);

      }

    }

    _n_fakeable_lep = _recolep_fakeable_pt.size();
    _n_tight_lep = _recolep_tight_pt.size();


    ////////////////////////////////
    ///////////// Taus /////////////
    ////////////////////////////////

    _n_fakeable_tau = (*_recotauh_pt).size();

    for(int i_tau=0; i_tau<_n_fakeable_tau; i_tau++){

      if((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]>0.5){

        _recotauh_tight_WPL_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_tight_WPL_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_tight_WPL_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_tight_WPL_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_tight_WPL_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPL_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPL_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPL_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPL_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_tight_WPL_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_tight_WPL_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_tight_WPL_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_tight_WPL_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_tight_WPL_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
        _recotauh_tight_WPL_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);

      }

      if((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]>0.5){

        _recotauh_tight_WPM_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_tight_WPM_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_tight_WPM_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_tight_WPM_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_tight_WPM_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPM_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPM_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPM_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_tight_WPM_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_tight_WPM_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_tight_WPM_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_tight_WPM_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_tight_WPM_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_tight_WPM_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
        _recotauh_tight_WPM_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);

      }

    }
    
    _n_tight_WPL_tau = _recotauh_tight_WPL_pt.size();
    _n_tight_WPM_tau = _recotauh_tight_WPM_pt.size();

    _n_light_jet = (_n_recoPFJet - _n_recoPFJet_btag_loose) + _n_recoPFFwdJet;


    /////////////////////////////////////
    ////////// MVA input vbles  /////////
    /////////////////////////////////////

    /*if(_n_loose_lep>0) {
      _lep1_conePt = (*_recolep_conept)[0];
      _lep1_charge = (*_recolep_charge)[0];
      TLorentzVector lep1((*_recolep_px)[0],(*_recolep_py)[0],(*_recolep_pz)[0],(*_recolep_e)[0]);
      float minDR_l1_j = 9999;
      for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
        TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
        float mydR = jet.DeltaR(lep1);
        if(mydR < minDR_l1_j) minDR_l1_j = mydR;
      }
      _mindr_lep1_jet = minDR_l1_j;
    }

    if(_n_loose_lep>1) {
      _lep2_conePt = (*_recolep_conept)[1];
      TLorentzVector lep2((*_recolep_px)[1],(*_recolep_py)[1],(*_recolep_pz)[1],(*_recolep_e)[1]);
      float minDR_l2_j = 9999;
      for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
        TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
        float mydR = jet.DeltaR(lep2);
        if(mydR < minDR_l2_j) minDR_l2_j = mydR;
      }
      _mindr_lep2_jet = minDR_l2_j;
    }

    if(_n_loose_lep>2) {
      _lep3_conePt = (*_recolep_conept)[2];
      TLorentzVector lep3((*_recolep_px)[2],(*_recolep_py)[2],(*_recolep_pz)[2],(*_recolep_e)[2]);
      float minDR_l3_j = 9999;
      for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
        TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
        float mydR = jet.DeltaR(lep3);
        if(mydR < minDR_l3_j) minDR_l3_j = mydR;
      }
      _mindr_lep3_jet = minDR_l3_j;
    }


    if(_n_recotauh>0) {
      TLorentzVector tau1((*_recotauh_px)[0],(*_recotauh_py)[0],(*_recotauh_pz)[0],(*_recotauh_e)[0]);
      float minDR_t1_j = 9999;
      for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
        TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
        float mydR = jet.DeltaR(tau1);
        if(mydR < minDR_t1_j) minDR_t1_j = mydR;
      }
      _mindr_tau1_jet = minDR_t1_j;
    }

    if(_n_recotauh>1) {
      TLorentzVector tau2((*_recotauh_px)[1],(*_recotauh_py)[1],(*_recotauh_pz)[1],(*_recotauh_e)[1]);
      float minDR_t2_j = 9999;
      for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
        TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
        float mydR = jet.DeltaR(tau2);
        if(mydR < minDR_t2_j) minDR_t2_j = mydR;
      }
      _mindr_tau2_jet = minDR_t2_j;
    }

    if(_n_recoPFJet>1){
      int n_pair_jets = 0;
      for(int i_jet1=0; i_jet1<_n_recoPFJet; i_jet1++){  
        TLorentzVector jet1((*_recoPFJet_px)[i_jet1],(*_recoPFJet_py)[i_jet1],(*_recoPFJet_pz)[i_jet1],(*_recoPFJet_e)[i_jet1]);
        for(int i_jet2=i_jet1+1; i_jet2<_n_recoPFJet; i_jet2++){  
          TLorentzVector jet2((*_recoPFJet_px)[i_jet2],(*_recoPFJet_py)[i_jet2],(*_recoPFJet_pz)[i_jet2],(*_recoPFJet_e)[i_jet2]);
          _avg_dr_jet+=jet1.DeltaR(jet2);
          n_pair_jets++;
        }
      }
      _avg_dr_jet/=n_pair_jets;
    }

    if(_n_loose_lep>0 && _n_recotauh>0){
      int n_pair_lep_tau = 0;
      float maxDR_l_t = 0;
      for(int i_lep=0; i_lep<_n_loose_lep; i_lep++){  
        TLorentzVector lep((*_recolep_px)[i_lep],(*_recolep_py)[i_lep],(*_recolep_pz)[i_lep],(*_recolep_e)[i_lep]);
        for(int i_tau=0; i_tau<_n_recotauh; i_tau++){  
          TLorentzVector tau((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
          float mydR = lep.DeltaR(tau);
          _avg_dr_lep_tau+=mydR;
          n_pair_lep_tau++;
          if(mydR > maxDR_l_t) maxDR_l_t = mydR ;
        }
      }
      _avg_dr_lep_tau/=n_pair_lep_tau;
      _max_dr_lep_tau = maxDR_l_t;
    }

    if(_n_recotauh>0 && _n_recoPFJet>0) {
      float minDR_t_j = 9999;
      for(int i_tau = 0; i_tau<_n_recotauh; i_tau++){
        TLorentzVector tau((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);    
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float mydR = jet.DeltaR(tau);
          if(mydR < minDR_t_j) minDR_t_j = mydR;
        }
      }
      _mindr_tau_jet = minDR_t_j;
    }

    if(_n_loose_lep>0 && _n_recotauh>0) {
      float minDR_l_t = 9999;
      for(int i_lep = 0; i_lep<_n_loose_lep; i_lep++){
        TLorentzVector lep((*_recolep_px)[i_lep],(*_recolep_py)[i_lep],(*_recolep_pz)[i_lep],(*_recolep_e)[i_lep]);    
        for(int i_tau = 0; i_tau<_n_recotauh; i_tau++){
          TLorentzVector tau((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);    
          float mydR = tau.DeltaR(lep);
          if(mydR < minDR_l_t) minDR_l_t = mydR;
        }
      }
      _mindr_lep_tau = minDR_l_t;
    }


    if(_n_loose_lep>0 && _n_recoPFJet>0) {
      float minDR_l_j = 9999;
      for(int i_lep = 0; i_lep<_n_loose_lep; i_lep++){
        TLorentzVector lep((*_recolep_px)[i_lep],(*_recolep_py)[i_lep],(*_recolep_pz)[i_lep],(*_recolep_e)[i_lep]);    
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float mydR = jet.DeltaR(lep);
          if(mydR < minDR_l_j) minDR_l_j = mydR;
        }
      }
      _mindr_lep_jet = minDR_l_j;
    }

    if(_n_loose_lep>1) {
      TLorentzVector lep1((*_recolep_px)[0],(*_recolep_py)[0],(*_recolep_pz)[0],(*_recolep_e)[0]); 
      TLorentzVector lep2((*_recolep_px)[1],(*_recolep_py)[1],(*_recolep_pz)[1],(*_recolep_e)[1]); 
      _dr_leps = lep1.DeltaR(lep2);
    } 

    if(_n_recotauh>1) {
      TLorentzVector tau1((*_recotauh_px)[0],(*_recotauh_py)[0],(*_recotauh_pz)[0],(*_recotauh_e)[0]); 
      TLorentzVector tau2((*_recotauh_px)[1],(*_recotauh_py)[1],(*_recotauh_pz)[1],(*_recotauh_e)[1]); 
      _dr_taus = tau1.DeltaR(tau2);
    } 


    _dR_lep_tau_ss = 0;
    _dr_lep1_tau = 0;
    _dr_lep2_tau = 0;
    _max_lep_eta = 0;
    _mT_lep1 = 0;
    _mT_lep2 = 0;
    _mTauTauVis = 0;
    _mTauTauVis1 = 0;
    _mTauTauVis2 = 0;
    _mbb = 0;
    _mbb_loose = 0;
    _cosThetaS_hadTau = 0;
    _HTT = 0;
    _HadTop_pt = 0;
    _Hj_tagger = 0;
    _nBJetLoose = 0;
    _nLightJet = 0;
    _nBJetMedium = 0;
    _massL = 0;*/


    ////////////////////////////////
    ///////////// mll  /////////////
    ////////////////////////////////


    bool inv_mass_lep_pairs=true;

    bool SFOS_loose_pair=false;
    bool SFOS_fakeable_pair=false;

    bool inv_mass_Z=true;
    bool inv_mass_Zee=true;

    for(int i_lep1=0; i_lep1<_n_loose_lep; i_lep1++){
      TLorentzVector lep1; //use standard pt here (smeared for electrons)
      lep1.SetPtEtaPhiE((*_recolep_pt)[i_lep1],(*_recolep_eta)[i_lep1],(*_recolep_phi)[i_lep1],(*_recolep_e)[i_lep1]);

      for(int i_lep2=i_lep1+1; i_lep2<_n_loose_lep; i_lep2++){
        TLorentzVector lep2;
        lep2.SetPtEtaPhiE((*_recolep_pt)[i_lep2],(*_recolep_eta)[i_lep2],(*_recolep_phi)[i_lep2],(*_recolep_e)[i_lep2]);
        float m_ll = (lep1 + lep2).M();

        if((*_recolep_pdg)[i_lep1]==-(*_recolep_pdg)[i_lep2] && ((*_recolep_isfakeable)[i_lep1] && (*_recolep_isfakeable)[i_lep2])) 
          SFOS_fakeable_pair=true;

        if(m_ll<12) 
          inv_mass_lep_pairs=false;

        if((*_recolep_pdg)[i_lep1]==-(*_recolep_pdg)[i_lep2]){
          SFOS_loose_pair=true;
          if(fabs(m_ll-91.2)<10) {
            inv_mass_Z=false;
          }
        }

        if( (fabs(m_ll-91.2)<10) && abs((*_recolep_pdg)[i_lep1]) == 11 && abs((*_recolep_pdg)[i_lep2]) == 11 && (*_recolep_isfakeable)[i_lep1] && (*_recolep_isfakeable)[i_lep2] ){
          inv_mass_Zee=false;
        }

      }
    }


    bool inv_mass_4l=true;
    bool SFOS_doublepair=false;
    float m_4l = 0;   

    if (_n_loose_lep>=4){
      for(int i_lep=0; i_lep<_n_loose_lep; i_lep++){
      TLorentzVector lep1;
      lep1.SetPtEtaPhiE((*_recolep_pt)[i_lep],(*_recolep_eta)[i_lep],(*_recolep_phi)[i_lep],(*_recolep_e)[i_lep]);
        for(int i_lep2=i_lep+1; i_lep2<_n_loose_lep; i_lep2++){
          TLorentzVector lep2;
          lep2.SetPtEtaPhiE((*_recolep_pt)[i_lep2],(*_recolep_eta)[i_lep2],(*_recolep_phi)[i_lep2],(*_recolep_e)[i_lep2]);
          for(int i_lep3=i_lep+2; i_lep3<_n_loose_lep; i_lep3++){
            TLorentzVector lep3;
            lep3.SetPtEtaPhiE((*_recolep_pt)[i_lep3],(*_recolep_eta)[i_lep3],(*_recolep_phi)[i_lep3],(*_recolep_e)[i_lep3]);
            for(int i_lep4=i_lep+3; i_lep4<_n_loose_lep; i_lep4++){
              TLorentzVector lep4;
              lep4.SetPtEtaPhiE((*_recolep_pt)[i_lep4],(*_recolep_eta)[i_lep4],(*_recolep_phi)[i_lep4],(*_recolep_e)[i_lep4]);
              if( (i_lep != i_lep2) && (i_lep != i_lep3) && (i_lep != i_lep4) && (i_lep2 != i_lep3) && (i_lep2 != i_lep4) && (i_lep3 != i_lep4)){ 
                if( ((*_recolep_pdg)[i_lep]==-(*_recolep_pdg)[i_lep2] && (*_recolep_pdg)[i_lep3]==-(*_recolep_pdg)[i_lep4])
                  || ((*_recolep_pdg)[i_lep]==-(*_recolep_pdg)[i_lep3] && (*_recolep_pdg)[i_lep2]==-(*_recolep_pdg)[i_lep4]) 
                  || ((*_recolep_pdg)[i_lep]==-(*_recolep_pdg)[i_lep4] && (*_recolep_pdg)[i_lep2]==-(*_recolep_pdg)[i_lep3])) {
                  m_4l = (lep1 + lep2 + lep3 + lep4).M();
                  SFOS_doublepair=true;
                  if(m_4l<140) {
                    inv_mass_4l=false;
                    break;                  
                  }
                }
              }  
            }
          }
        }
      }
    }
    

    //////////////////////////////
    /////////// 2tau  ////////////
    //////////////////////////////

    bool passTriggers_0lep2tau = pass_2t;

    bool sig_2tau_base = passTriggers_0lep2tau &&
      (_n_recotauh>=2) &&
      (((*_recotauh_charge)[0]*(*_recotauh_charge)[1])<0) &&
      (*_recotauh_pt)[0]>40 && (*_recotauh_pt)[1]>40 &&
      (abs((*_recotauh_eta)[0])<2.1) && (abs((*_recotauh_eta)[1])<2.1) &&
      inv_mass_lep_pairs &&
      (_n_tight_lep==0) &&
      (_n_recoPFJet>=4 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) );

    bool sig_2tau_SR = 
      sig_2tau_base &&
      ((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5 && (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1]>0.5) &&
      (*_recotauh_isGenMatched)[0] && (*_recotauh_isGenMatched)[1];

    bool sig_2tau_fake = 
      sig_2tau_base &&
      !((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5 && (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1]>0.5);


    ////////////////////////////////
    /////////// 1l1tau  ////////////
    ////////////////////////////////

    bool passTriggers_1lep1tau = (pass_e || pass_m || pass_et || pass_mt);

    bool sig_1l1tau_base = passTriggers_1lep1tau &&
      (_n_fakeable_lep>=1) &&
      ( (_recolep_fakeable_conept[0]>25 && abs(_recolep_fakeable_pdg[0])==13) || (_recolep_fakeable_conept[0]>30 && abs(_recolep_fakeable_pdg[0])==11) ) &&
      ((abs(_recolep_fakeable_eta[0]))<2.1) &&
      (_n_recotauh>=1) &&
      ((*_recotauh_pt)[0]>30) &&
      inv_mass_lep_pairs &&
      (_n_recoPFJet>=4 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2));

    bool sig_1l1tau_SR = 
      sig_1l1tau_base &&
      (_n_tight_lep==1) && (_recolep_fakeable_ismvasel[0]) &&
      (_n_tight_WPM_tau==1) && ((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5) &&
      ((*_recotauh_isGenMatched)[0] && _recolep_fakeable_isGenMatched[0]); 

    bool sig_1l1tau_fake = 
      sig_1l1tau_base &&
      (!(_recolep_fakeable_ismvasel[0]) || !((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5));

  
    ////////////////////////////////
    /////////// 1l2tau  ////////////
    ////////////////////////////////

    bool passTriggers_1lep2tau = (pass_e || pass_m || pass_et || pass_mt || pass_2t);

    bool sig_1l2tau_base = passTriggers_1lep2tau &&
      (_n_fakeable_lep>=1) &&
      ( (_recolep_fakeable_conept[0]>25 && abs(_recolep_fakeable_pdg[0])==13) || (_recolep_fakeable_conept[0]>30 && abs(_recolep_fakeable_pdg[0])==11) ) &&
      ((abs(_recolep_fakeable_eta[0]))<2.1) &&
      (_n_tight_lep<=1) &&
      (_n_fakeable_tau>=2) &&
      ( (*_recotauh_pt)[0]>30 && (*_recotauh_pt)[1]>20 )  &&
      inv_mass_lep_pairs;

    bool sig_1l2tau_SR = 
      sig_1l2tau_base &&
      (_recolep_fakeable_ismvasel[0]==1) &&
      ((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5 && (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1]>0.5) &&
      (((*_recotauh_charge)[0]*(*_recotauh_charge)[1])<0) &&
      (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) &&
      (*_recotauh_isGenMatched)[0] && (*_recotauh_isGenMatched)[1] && _recolep_fakeable_isGenMatched[0];

    bool sig_1l2tau_fake = 
        sig_1l2tau_base &&
        (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) &&
        ( !(_recolep_fakeable_ismvasel[0]==1) || !((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5 && (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1]>0.5) ) &&        
        ( ((*_recotauh_charge)[0]*(*_recotauh_charge)[1])<0 );


    ////////////////////////////////
    //////////// 2lss  /////////////
    ////////////////////////////////

    bool passTriggers_2lep0tau = (pass_e || pass_m || pass_2e || pass_2m || pass_em);

    bool metLD_e = true;
    if(abs(_recolep_fakeable_pdg[0])==11 && abs(_recolep_fakeable_pdg[1])==11) 
      metLD_e = (_ETmissLD>30); 

    bool sig_2lss_base = passTriggers_2lep0tau &&
      (_n_fakeable_lep>=2) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15) &&
      inv_mass_lep_pairs &&
      (_n_tight_lep<=2) &&
      (_recolep_fakeable_tightcharge[0]==1 && _recolep_fakeable_tightcharge[1]==1) &&
      (_n_tight_WPL_tau==0) &&
      inv_mass_Zee && 
      metLD_e;

    bool sig_2lss_SR =
      sig_2lss_base &&
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])>0) &&
      _recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1];

    bool pass_njet_2l_ttH = (_n_recoPFJet>=4 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) );
    bool pass_njet_2l_tH = (_n_recoPFJet_btag_medium>=1 &&  _n_light_jet>=1);

    bool is_2l_ttH_like = pass_njet_2l_ttH;
    bool is_2l_tH_like = pass_njet_2l_tH;
    bool is_2l_ttH_like_and_not_tH_like = pass_njet_2l_ttH && !pass_njet_2l_tH;
    bool is_2l_tH_like_and_not_ttH_like = pass_njet_2l_tH && !pass_njet_2l_ttH;

    bool sig_2lss_SR_ttH =
      sig_2lss_SR &&
      pass_njet_2l_ttH;

    bool sig_2lss_SR_tH =
      sig_2lss_SR &&
      pass_njet_2l_tH && !pass_njet_2l_ttH;

    bool sig_2lss_fake =
      sig_2lss_base &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])>0) &&
      !((_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]));

    bool sig_2lss_fake_ttH =
      sig_2lss_fake &&
      pass_njet_2l_ttH;

    bool sig_2lss_fake_tH =
      sig_2lss_fake &&
      pass_njet_2l_tH && !pass_njet_2l_ttH;

    bool sig_2lss_flip =
      sig_2lss_base &&
      ((_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1])) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])<0) &&
      (abs(_recolep_fakeable_pdg[0])==11 || abs(_recolep_fakeable_pdg[1])==11) &&
      _recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1];

    bool sig_2lss_flip_ttH =
      sig_2lss_flip &&
      pass_njet_2l_ttH;

    bool sig_2lss_flip_tH =
      sig_2lss_flip &&
      pass_njet_2l_tH && !pass_njet_2l_ttH;


    ////////////////////////////////
    ////////// 2lss1tau  ///////////
    ////////////////////////////////

    bool passTriggers_2lep1tau = (pass_e || pass_m || pass_2e || pass_2m || pass_em || pass_et || pass_mt);

    bool sig_2lss1tau_base =  passTriggers_2lep1tau &&
      (_n_fakeable_lep>=2) &&
      (_recolep_fakeable_conept[0]>25) && ( (_recolep_fakeable_conept[1]>10 && abs(_recolep_fakeable_pdg[1])==11) || (_recolep_fakeable_conept[1]>15 && abs(_recolep_fakeable_pdg[1])==13) ) &&
      inv_mass_lep_pairs &&
      (_n_tight_lep<=2) &&
      (_recolep_fakeable_tightcharge[0]==1 && _recolep_fakeable_tightcharge[1]==1) &&
      (_n_recotauh>=1) &&
      (_n_tight_WPM_tau<=1) &&
      inv_mass_Zee && 
      metLD_e;

    bool sig_2lss1tau_SR =
      sig_2lss1tau_base &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])>0) &&
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) &&
      (_n_tight_WPL_tau>=1) &&
      ((_recolep_fakeable_charge[0]*_recotauh_tight_WPL_charge[0])<0) &&
      (_recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1]) &&
      (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) );

    bool sig_2lss1tau_fake =
      sig_2lss1tau_base &&
      (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) &&
      ( (_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])>0 ) &&
      (_n_tight_WPL_tau>=1) &&
      ( (_recolep_fakeable_charge[0]*_recotauh_tight_WPL_charge[0])<0 ) &&
      !(_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]);

    bool sig_2lss1tau_flip =
      sig_2lss1tau_base &&
      ( abs(_recolep_fakeable_pdg[0])==11 || abs(_recolep_fakeable_pdg[1])==11) &&
      (_n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])<0) &&
      ((abs((_recolep_fakeable_pdg)[0])==11 && (_recolep_fakeable_charge)[0]*(_recotauh_tight_WPL_charge)[0]>0) || (abs((_recolep_fakeable_pdg)[1])==11 && (_recolep_fakeable_charge)[1]*(_recotauh_tight_WPL_charge)[0]>0)) && //needed?
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) &&
      (_n_tight_WPL_tau>=1) &&
      ( (_recolep_fakeable_charge[0]*_recotauh_tight_WPL_charge[0])>0 || (_recolep_fakeable_charge[1]*_recotauh_tight_WPL_charge[0])>0) &&
      _recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1];


    ////////////////////////////////
    ////////// 2los1tau  ///////////
    ////////////////////////////////

    bool sig_2los1tau_base = passTriggers_2lep1tau &&
      (_n_fakeable_lep>=2) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])<0) &&
      (_recolep_fakeable_conept[0]>25) && ( (_recolep_fakeable_conept[1]>10 && abs(_recolep_fakeable_pdg[1])==11) || (_recolep_fakeable_conept[1]>15 && abs(_recolep_fakeable_pdg[1])==13) ) &&
      (_n_recotauh>=1) &&
      (_n_tight_WPM_tau<=1) &&
      ((*_recotauh_pt)[0]>40) &&
      inv_mass_lep_pairs &&
      inv_mass_Z &&
      (_ETmissLD>30);

    bool sig_2los1tau_SR =
      sig_2los1tau_base &&
      (_n_tight_lep==2) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])<0) &&
      ( _recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) &&
      (_n_tight_WPL_tau==1) &&
      ((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5) &&
      (_recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] && (*_recotauh_isGenMatched)[0]);

    bool sig_2los1tau_fake =
      sig_2los1tau_base &&
      ( (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) || !((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[0]>0.5) );


    ////////////////////////////////
    /////////// 2l2tau  ////////////
    ////////////////////////////////

    bool passTriggers_2lep2tau = (pass_e || pass_m || pass_2e || pass_2m || pass_em || pass_et || pass_mt || pass_2t);

    bool metLD_f = true;
    if (_n_recoPFJet<=3){
      if(SFOS_fakeable_pair) metLD_f = _ETmissLD>45;
      else if (!SFOS_fakeable_pair) metLD_f = _ETmissLD>30;
    }

    bool sig_2l2tau_base = passTriggers_2lep2tau &&
      (_n_fakeable_lep>=2) &&
      (_recolep_fakeable_conept[0]>25) &&
      ( (_recolep_fakeable_conept[1]>15 && abs(_recolep_fakeable_pdg[1])==11) || (_recolep_fakeable_conept[1]>10 && abs(_recolep_fakeable_pdg[1])==13) ) &&
      inv_mass_lep_pairs &&
      inv_mass_Z &&
      (_n_fakeable_tau>=2) &&
      metLD_f &&
      ( ((*_recotauh_charge)[0]+(*_recotauh_charge)[1]+_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]) == 0) &&
      (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) );

    bool sig_2l2tau_SR =
      sig_2l2tau_base &&
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) &&
      ((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0] && (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1] )&&
      (_recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] && (*_recotauh_isGenMatched)[0] && (*_recotauh_isGenMatched)[1]);

    bool sig_2l2tau_fake =
      sig_2l2tau_base &&
      (!(_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) || !((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0] && (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1] ));


    //////////////////////////////
    //////////// 3l  /////////////
    //////////////////////////////

    bool passTriggers_3lep0tau = (pass_e || pass_m || pass_2e || pass_2m || pass_em || pass_3e || pass_3m || pass_2me || pass_m2e);

    bool sig_3l_base = passTriggers_3lep0tau &&
      (_n_fakeable_lep>=3) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15 && _recolep_fakeable_conept[2]>10) &&
      inv_mass_lep_pairs &&
      inv_mass_Z &&
      (_n_tight_WPL_tau==0) &&
      ( abs(_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]+_recolep_fakeable_charge[2]) == 1 ) &&
      inv_mass_4l &&
      (_n_tight_lep<=3);

    bool sig_3l_SR =
      sig_3l_base &&
      (_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1) &&
      (_recolep_fakeable_isGenMatched[0]==1 && _recolep_fakeable_isGenMatched[1]==1 && _recolep_fakeable_isGenMatched[2]==1);

    bool pass_njet_3l_ttH = (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) && metLD_f;
    bool pass_njet_3l_tH = (_n_recoPFJet_btag_medium>=1 && _n_light_jet>=1);

    bool is_3l_ttH_like = pass_njet_3l_ttH;
    bool is_3l_tH_like = pass_njet_3l_tH;
    bool is_3l_ttH_like_and_not_tH_like = pass_njet_3l_ttH && !pass_njet_3l_tH;
    bool is_3l_tH_like_and_not_ttH_like = pass_njet_3l_tH && !pass_njet_3l_ttH;

    bool sig_3l_SR_ttH =
      sig_3l_SR &&
      pass_njet_3l_ttH;

    bool sig_3l_SR_tH =
      sig_3l_SR &&
      pass_njet_3l_tH && !pass_njet_3l_ttH;

    bool sig_3l_fake =
      sig_3l_base &&
      !(_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1);

    bool sig_3l_fake_ttH =
      sig_3l_fake &&
      pass_njet_3l_ttH;

    bool sig_3l_fake_tH =
      sig_3l_fake &&
      pass_njet_3l_tH && !pass_njet_3l_ttH;


    ////////////////////////////////
    ////////// 3l1tau  /////////////
    ////////////////////////////////

    bool passTriggers_3lep1tau = (pass_e || pass_m || pass_2e || pass_2m || pass_em || pass_et || pass_mt || pass_3e || pass_3m || pass_2me || pass_m2e);

    bool sig_3l1tau_base = passTriggers_3lep1tau &&
      (_n_fakeable_lep>=3) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15 && _recolep_fakeable_conept[2]>10) &&
      inv_mass_lep_pairs &&
      inv_mass_Z &&
      (_n_recotauh>=1) &&
      metLD_f &&
      ( ((*_recotauh_charge)[0]+_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]+_recolep_fakeable_charge[2]) == 0) &&
      ( _n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) );

    bool sig_3l1tau_SR =
      sig_3l1tau_base &&
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1] && _recolep_fakeable_ismvasel[2]) &&
      (_n_tight_WPL_tau>=1) &&
      (_recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] && _recolep_fakeable_isGenMatched[2]);

    bool sig_3l1tau_fake =
      sig_3l1tau_base &&
      !(_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1] && _recolep_fakeable_ismvasel[2]) &&
      (_n_tight_WPL_tau>=1);


    //////////////////////////////
    //////////// 4l  /////////////
    //////////////////////////////

    bool sig_4l_base = passTriggers_3lep0tau &&
      (_n_fakeable_lep>=4) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15 && _recolep_fakeable_conept[2]>15 && _recolep_fakeable_conept[3]>10) &&
      inv_mass_lep_pairs &&
      inv_mass_Z &&
      metLD_f &&
      ( (_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]+_recolep_fakeable_charge[2]+_recolep_fakeable_charge[3]) == 0) &&
      ( _n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) && 
      inv_mass_4l;

    bool sig_4l_SR =
      sig_4l_base && 
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1] && _recolep_fakeable_ismvasel[2] && _recolep_fakeable_ismvasel[3]) &&
      (_recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] && _recolep_fakeable_isGenMatched[2] && _recolep_fakeable_isGenMatched[3]);

    bool sig_4l_fake =
      sig_4l_base &&
      !(_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1 && _recolep_fakeable_ismvasel[3]==1);  

 
    //////////////////////////////
    //////////// ttW /////////////
    //////////////////////////////

    // Same as the ttH 2lss selection (SR, fake, flip) except that (_n_recoPFJet==3) instead of (_n_recoPFJet>=4)

    bool sig_ttW_CR_base = passTriggers_2lep0tau &&
      (_n_fakeable_lep>=2) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15) &&
      inv_mass_lep_pairs &&
      (_n_tight_lep<=2) &&
      (_recolep_fakeable_tightcharge[0]==1 && _recolep_fakeable_tightcharge[1]==1) &&
      (_n_tight_WPL_tau==0) &&
      inv_mass_Zee && 
      metLD_e;

    bool sig_ttW_CR_SR =
      sig_ttW_CR_base &&
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1]) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])>0) &&
      _recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] &&
      (_n_recoPFJet==3) && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ;

    bool sig_ttW_CR_fake =
      sig_ttW_CR_base &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])>0) &&
      !((_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1])) &&
      (_n_recoPFJet==3) && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ;

    bool sig_ttW_CR_flip =
      sig_ttW_CR_base &&
      ((_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1])) &&
      ((_recolep_fakeable_charge[0]*_recolep_fakeable_charge[1])<0) &&
      (abs(_recolep_fakeable_pdg[0])==11 || abs(_recolep_fakeable_pdg[1])==11) &&
      _recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] &&
      (_n_recoPFJet==3) && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ;


    ////////////////////////////////
    ///////////// ttZ //////////////
    ////////////////////////////////

    // Same as the ttH 3l selection (SR, fake) except that inv_mass_Z is inverted

    bool sig_ttZ_CR_base = passTriggers_3lep0tau &&
      (_n_fakeable_lep>=3) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15 && _recolep_fakeable_conept[2]>10) &&
      inv_mass_lep_pairs &&
      !inv_mass_Z &&
      (_n_tight_WPL_tau==0) &&
      ( abs(_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]+_recolep_fakeable_charge[2]) == 1 ) &&
      inv_mass_4l &&
      (_n_tight_lep<=3);

    bool sig_ttZ_CR_SR =
      sig_ttZ_CR_base &&
      (_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1) &&
      (_recolep_fakeable_isGenMatched[0]==1 && _recolep_fakeable_isGenMatched[1]==1 && _recolep_fakeable_isGenMatched[2]==1) &&
      (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) && metLD_f;

    bool sig_ttZ_CR_fake =
      sig_ttZ_CR_base &&
      !(_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1) &&
      (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) ) && metLD_f;


    ////////////////////////////////
    //////////// WZ_CR  ////////////
    ////////////////////////////////

    // Same as the ttH 3l selection (SR, fake) except that inv_mass_Z is inverted and we require 
    // (_n_recoPFJet_btag_medium==0 && _n_recoPFJet_btag_loose<2) instead of (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) 

    bool sig_WZ_CR_base = passTriggers_3lep0tau &&
      (_n_fakeable_lep>=3) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15 && _recolep_fakeable_conept[2]>10) &&
      inv_mass_lep_pairs &&
      !inv_mass_Z &&
      (_n_tight_WPL_tau==0) &&
      ( abs(_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]+_recolep_fakeable_charge[2]) == 1 ) &&
      inv_mass_4l &&
      (_n_tight_lep<=3);

    bool sig_WZ_CR_SR =
      sig_WZ_CR_base &&
      (_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1) &&
      (_recolep_fakeable_isGenMatched[0]==1 && _recolep_fakeable_isGenMatched[1]==1 && _recolep_fakeable_isGenMatched[2]==1) &&
      (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium==0 && _n_recoPFJet_btag_loose<2) ) && metLD_f;

    bool sig_WZ_CR_fake =
      sig_WZ_CR_base &&
      !(_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1) &&
      (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium==0 && _n_recoPFJet_btag_loose<2) ) && metLD_f;


    //////////////////////////////
    //////////// ZZ_CR  //////////
    //////////////////////////////

    // Same as the 4l selection (SR, fake) except that inv_mass_Z is inverted and we require 
    // (_n_recoPFJet_btag_medium==0 && _n_recoPFJet_btag_loose<2) instead of (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2) 

    bool sig_ZZ_CR_base = passTriggers_3lep0tau &&
      (_n_fakeable_lep>=4) &&
      (_recolep_fakeable_conept[0]>25 && _recolep_fakeable_conept[1]>15 && _recolep_fakeable_conept[2]>15 && _recolep_fakeable_conept[3]>10) &&
      inv_mass_lep_pairs &&
      !inv_mass_Z &&
      metLD_f &&
      ( (_recolep_fakeable_charge[0]+_recolep_fakeable_charge[1]+_recolep_fakeable_charge[2]+_recolep_fakeable_charge[3]) == 0) &&
      (_n_recoPFJet>=2 && (_n_recoPFJet_btag_medium==0 && _n_recoPFJet_btag_loose<2)) && 
      inv_mass_4l;

    bool sig_ZZ_CR_SR =
      sig_ZZ_CR_base && 
      (_recolep_fakeable_ismvasel[0] && _recolep_fakeable_ismvasel[1] && _recolep_fakeable_ismvasel[2] && _recolep_fakeable_ismvasel[3]) &&
      (_recolep_fakeable_isGenMatched[0] && _recolep_fakeable_isGenMatched[1] && _recolep_fakeable_isGenMatched[2] && _recolep_fakeable_isGenMatched[3]);

    bool sig_ZZ_CR_fake =
      sig_ZZ_CR_base &&
      !(_recolep_fakeable_ismvasel[0]==1 && _recolep_fakeable_ismvasel[1]==1 && _recolep_fakeable_ismvasel[2]==1 && _recolep_fakeable_ismvasel[3]==1); 
   

    /////////////////////////////////////
    /////// Fill lepton branches ////////
    /////////////////////////////////////

    _recolep_sel_charge.clear();
    _recolep_sel_pdg.clear();
    _recolep_sel_e.clear();
    _recolep_sel_px.clear();
    _recolep_sel_py.clear();
    _recolep_sel_pz.clear();
    _recolep_sel_pt.clear();
    _recolep_sel_conept.clear();
    _recolep_sel_eta.clear();
    _recolep_sel_phi.clear();
    _recolep_sel_isfakeable.clear();
    _recolep_sel_ismvasel.clear();
    _recolep_sel_tightcharge.clear();
    _recolep_sel_isGenMatched.clear();
    _recolep_sel_genMatchInd.clear();

    bool has1lep = 
      sig_1l1tau_SR || sig_1l1tau_fake ||
      sig_1l2tau_SR || sig_1l2tau_fake;

    bool has2lep = 
      sig_2lss_SR_ttH || sig_2lss_SR_tH || sig_2lss_fake_ttH || sig_2lss_fake_tH || sig_2lss_flip_ttH || sig_2lss_flip_tH || 
      sig_2lss1tau_SR || sig_2lss1tau_fake || sig_2lss1tau_flip || 
      sig_2los1tau_SR || sig_2los1tau_fake ||
      sig_2l2tau_SR || sig_2l2tau_fake ||
      sig_ttW_CR_SR || sig_ttW_CR_fake; 
      
    bool has3lep = 
      sig_3l_SR_ttH || sig_3l_SR_tH || sig_3l_fake_ttH  || sig_3l_fake_tH ||
      sig_3l1tau_SR || sig_3l1tau_fake ||
      sig_ttZ_CR_SR || sig_ttZ_CR_fake ||
      sig_WZ_CR_SR || sig_WZ_CR_fake;

    bool has4lep =
      sig_4l_SR || sig_4l_fake ||
      sig_ZZ_CR_SR || sig_ZZ_CR_fake;

    int nlep = 0;
    if(has1lep) nlep = 1;
    if(has2lep) nlep = 2;
    if(has3lep) nlep = 3;
    if(has4lep) nlep = 4;

    for(int i_lep = 0; i_lep<nlep; i_lep++){

      _recolep_sel_charge.push_back(_recolep_fakeable_charge[i_lep]);
      _recolep_sel_pdg.push_back(_recolep_fakeable_pdg[i_lep]);
      _recolep_sel_e.push_back(_recolep_fakeable_e[i_lep]);
      _recolep_sel_px.push_back(_recolep_fakeable_px[i_lep]);
      _recolep_sel_py.push_back(_recolep_fakeable_py[i_lep]);
      _recolep_sel_pz.push_back(_recolep_fakeable_pz[i_lep]);
      _recolep_sel_pt.push_back(_recolep_fakeable_pt[i_lep]);
      _recolep_sel_conept.push_back(_recolep_fakeable_conept[i_lep]);
      _recolep_sel_eta.push_back(_recolep_fakeable_eta[i_lep]);
      _recolep_sel_phi.push_back(_recolep_fakeable_phi[i_lep]);
      _recolep_sel_isfakeable.push_back(_recolep_fakeable_isfakeable[i_lep]);
      _recolep_sel_ismvasel.push_back(_recolep_fakeable_ismvasel[i_lep]);
      _recolep_sel_tightcharge.push_back(_recolep_fakeable_tightcharge[i_lep]);
      _recolep_sel_isGenMatched.push_back(_recolep_fakeable_isGenMatched[i_lep]);
      _recolep_sel_genMatchInd.push_back(_recolep_fakeable_genMatchInd[i_lep]);

    }

    _n_recolep_sel = _recolep_sel_charge.size();


    /////////////////////////////////////
    ///////// Fill tau branches /////////
    /////////////////////////////////////

    _recotauh_sel_eta.clear();
    _recotauh_sel_phi.clear();
    _recotauh_sel_pt.clear();
    _recotauh_sel_charge.clear();
    _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_sel_decayMode.clear();
    _recotauh_sel_e.clear();
    _recotauh_sel_px.clear();
    _recotauh_sel_py.clear();
    _recotauh_sel_pz.clear();
    _recotauh_sel_isGenMatched.clear();
    _recotauh_sel_genMatchInd.clear();


    bool has1tau = 
      sig_1l1tau_SR || sig_1l1tau_fake ||
      sig_2lss1tau_SR || sig_2lss1tau_fake || sig_2lss1tau_flip || 
      sig_2los1tau_SR || sig_2los1tau_fake ||
      sig_3l1tau_SR || sig_3l1tau_fake;

    bool has2tau = 
      sig_2tau_SR || sig_2tau_fake ||
      sig_1l2tau_SR || sig_1l2tau_fake || 
      sig_2l2tau_SR || sig_2l2tau_fake;
      
    int ntau = 0;
    if(has1tau) ntau = 1;
    if(has2tau) ntau = 2;

    /*bool hasfaketau =
      sig_1l2tau_fake ||
      sig_2l2tau_fake ||
      sig_2lss1tau_SR || sig_2lss1tau_fake || sig_2lss1tau_flip || 
      sig_2los1tau_SR || sig_2los1tau_fake ||
      sig_3l1tau_SR || sig_3l1tau_fake ||
      sig_2tau_SR || sig_2tau_fake ||
      sig_1l1tau_SR || sig_1l1tau_fake ||
      sig_1l2tau_SR ||
      sig_2l2tau_SR;

    bool hasfaketau =
      sig_1l2tau_fake ||
      sig_2l2tau_fake;

    bool hasWPLtau =
      sig_2lss1tau_SR || sig_2lss1tau_fake || sig_2lss1tau_flip || 
      sig_2los1tau_SR || sig_2los1tau_fake ||
      sig_3l1tau_SR || sig_3l1tau_fake;

    bool hasWPMtau =
      sig_2tau_SR || sig_2tau_fake ||
      sig_1l1tau_SR || sig_1l1tau_fake ||
      sig_1l2tau_SR ||
      sig_2l2tau_SR;

    bool leptonic =
      sig_2lss_SR_ttH || sig_2lss_SR_tH || sig_2lss_fake_ttH || sig_2lss_fake_tH || sig_2lss_flip_ttH || sig_2lss_flip_tH || 
      sig_3l_SR_ttH || sig_3l_SR_tH || sig_3l_fake_ttH  || sig_3l_fake_tH ||
      sig_4l_SR || sig_4l_fake ||
      sig_ttW_CR_SR || sig_ttW_CR_fake ||
      sig_ttZ_CR_SR || sig_ttZ_CR_fake ||
      sig_WZ_CR_SR || sig_WZ_CR_fake ||
      sig_ZZ_CR_SR || sig_ZZ_CR_fake;


    for(int i_tau = 0; i_tau<ntau; i_tau++){

      if(hasfaketau){

        _recotauh_sel_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_sel_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_sel_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_sel_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_sel_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_sel_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_sel_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);

      }

      else if(hasWPLtau){

        _recotauh_sel_eta.push_back(_recotauh_tight_WPL_eta[i_tau]);
        _recotauh_sel_phi.push_back(_recotauh_tight_WPL_phi[i_tau]);
        _recotauh_sel_pt.push_back(_recotauh_tight_WPL_pt[i_tau]);
        _recotauh_sel_charge.push_back(_recotauh_tight_WPL_charge[i_tau]);
        _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPL_byVLooseIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPL_byLooseIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPL_byMediumIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPL_byTightIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_decayMode.push_back(_recotauh_tight_WPL_decayMode[i_tau]);
        _recotauh_sel_e.push_back(_recotauh_tight_WPL_e[i_tau]);
        _recotauh_sel_px.push_back(_recotauh_tight_WPL_px[i_tau]);
        _recotauh_sel_py.push_back(_recotauh_tight_WPL_py[i_tau]);
        _recotauh_sel_pz.push_back(_recotauh_tight_WPL_pz[i_tau]);
        _recotauh_sel_isGenMatched.push_back(_recotauh_tight_WPL_isGenMatched[i_tau]);

      }

      else if(hasWPMtau){

        _recotauh_sel_eta.push_back(_recotauh_tight_WPM_eta[i_tau]);
        _recotauh_sel_phi.push_back(_recotauh_tight_WPM_phi[i_tau]);
        _recotauh_sel_pt.push_back(_recotauh_tight_WPM_pt[i_tau]);
        _recotauh_sel_charge.push_back(_recotauh_tight_WPM_charge[i_tau]);
        _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPM_byVLooseIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPM_byLooseIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPM_byMediumIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back(_recotauh_tight_WPM_byTightIsolationMVArun2v2017v2DBoldDMwLT[i_tau]);
        _recotauh_sel_decayMode.push_back(_recotauh_tight_WPM_decayMode[i_tau]);
        _recotauh_sel_e.push_back(_recotauh_tight_WPM_e[i_tau]);
        _recotauh_sel_px.push_back(_recotauh_tight_WPM_px[i_tau]);
        _recotauh_sel_py.push_back(_recotauh_tight_WPM_py[i_tau]);
        _recotauh_sel_pz.push_back(_recotauh_tight_WPM_pz[i_tau]);
        _recotauh_sel_isGenMatched.push_back(_recotauh_tight_WPM_isGenMatched[i_tau]);

      }

    }


    if(leptonic){

      for(int i_tau = 0; i_tau<_n_recotauh; i_tau++){

        _recotauh_sel_eta.push_back((*_recotauh_eta)[i_tau]);
        _recotauh_sel_phi.push_back((*_recotauh_phi)[i_tau]);
        _recotauh_sel_pt.push_back((*_recotauh_pt)[i_tau]);
        _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
        _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
        _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
        _recotauh_sel_e.push_back((*_recotauh_e)[i_tau]);
        _recotauh_sel_px.push_back((*_recotauh_px)[i_tau]);
        _recotauh_sel_py.push_back((*_recotauh_py)[i_tau]);
        _recotauh_sel_pz.push_back((*_recotauh_pz)[i_tau]);
        _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);

      }

    }*/

    for(int i_tau = 0; i_tau<ntau; i_tau++){

      _recotauh_sel_eta.push_back((*_recotauh_eta)[i_tau]);
      _recotauh_sel_phi.push_back((*_recotauh_phi)[i_tau]);
      _recotauh_sel_pt.push_back((*_recotauh_pt)[i_tau]);
      _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
      _recotauh_sel_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
      _recotauh_sel_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
      _recotauh_sel_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
      _recotauh_sel_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[i_tau]);
      _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
      _recotauh_sel_e.push_back((*_recotauh_e)[i_tau]);
      _recotauh_sel_px.push_back((*_recotauh_px)[i_tau]);
      _recotauh_sel_py.push_back((*_recotauh_py)[i_tau]);
      _recotauh_sel_pz.push_back((*_recotauh_pz)[i_tau]);
      _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);

    }

    _n_recotauh_sel = _recotauh_sel_pt.size();


    //////////////////////////
    /////// Fill tree ////////
    //////////////////////////


    if (sig_2tau_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2tau_SR += 1;
      _category = 1010;
      tree_2tau_SR->Fill();

    }

    if (sig_2tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2tau_fake += 1;
      _category = 1020;
      tree_2tau_fake->Fill();

    }

    if(sig_1l1tau_SR){

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_1l1tau_SR += 1;
      _category = 2010;
      tree_1l1tau_SR->Fill();

    }

    if (sig_1l1tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_1l1tau_fake += 1;
      _category = 2020;
      tree_1l1tau_fake->Fill();

    }

    if (sig_1l2tau_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_1l2tau_SR += 1;
      _category = 2110;
      tree_1l2tau_SR->Fill();

    }

    if (sig_1l2tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_1l2tau_fake += 1;
      _category = 2120;
      tree_1l2tau_fake->Fill();

    }

    if (sig_2lss_SR_ttH || sig_2lss_SR_tH) {

      if (sig_2lss_SR_ttH) n_2lss_SR_ttH += 1;
      if (sig_2lss_SR_tH)  n_2lss_SR_tH += 1;

      _is_ttH_like = sig_2lss_SR_ttH;
      _is_tH_like_and_not_ttH_like = sig_2lss_SR_tH;

      tree_2lss_SR->Fill();
      _category = 3010;

    }


    if (sig_2lss_fake_ttH || sig_2lss_fake_tH) {

      if (sig_2lss_fake_ttH) n_2lss_fake_ttH += 1;
      if (sig_2lss_fake_tH)  n_2lss_fake_tH += 1;

      _is_ttH_like = sig_2lss_fake_ttH;
      _is_tH_like_and_not_ttH_like = sig_2lss_fake_tH;

      tree_2lss_fake->Fill();
      _category = 3020;
    }


    if (sig_2lss_flip_ttH || sig_2lss_flip_tH) {

      if (sig_2lss_flip_ttH) n_2lss_flip_ttH += 1;
      if (sig_2lss_flip_tH)  n_2lss_flip_tH += 1;

      _is_ttH_like = sig_2lss_flip_ttH;
      _is_tH_like_and_not_ttH_like = sig_2lss_flip_tH;

      tree_2lss_flip->Fill();
      _category = 3030;

    }

    if (sig_2lss1tau_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2lss1tau_SR += 1;
      _category = 3110;
      tree_2lss1tau_SR->Fill();

    }

    if (sig_2lss1tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2lss1tau_fake += 1;
      _category = 3120;
      tree_2lss1tau_fake->Fill();

    }

    if (sig_2lss1tau_flip) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2lss1tau_flip += 1;
      _category = 3130;
      tree_2lss1tau_flip->Fill();

    }

    if (sig_2los1tau_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2los1tau_SR += 1;
      _category = 3210;
      tree_2los1tau_SR->Fill();

    }

    if (sig_2los1tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2los1tau_fake += 1;
      _category = 3220;
      tree_2los1tau_fake->Fill();

    }

    if (sig_2l2tau_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2l2tau_SR += 1;
      _category = 3310;
      tree_2l2tau_SR->Fill();

    }

    if (sig_2l2tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_2l2tau_fake += 1;
      _category = 3320;
      tree_2l2tau_fake->Fill();

    }

    if (sig_3l_SR_ttH || sig_3l_SR_tH) {

      if (sig_3l_SR_ttH) n_3l_SR_ttH += 1;
      if (sig_3l_SR_tH)  n_3l_SR_tH += 1;

      _is_ttH_like = sig_3l_SR_ttH;
      _is_tH_like_and_not_ttH_like = sig_3l_SR_tH;
      
      tree_3l_SR->Fill();
      _category = 4010;

    }

    if (sig_3l_fake_ttH || sig_3l_fake_tH) {

      if (sig_3l_fake_ttH) n_3l_fake_ttH += 1;
      if (sig_3l_fake_tH)  n_3l_fake_tH += 1;

      _is_ttH_like = sig_3l_fake_ttH;
      _is_tH_like_and_not_ttH_like = sig_3l_fake_tH;

      tree_3l_fake->Fill();
      _category = 4020;
    }

    
    if (sig_3l1tau_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_3l1tau_SR += 1;
      _category = 4110;
      tree_3l1tau_SR->Fill();

    }
    
    if (sig_3l1tau_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_3l1tau_fake += 1;
      _category = 4120;
      tree_3l1tau_fake->Fill();

    }

    if (sig_4l_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_4l_SR += 1;
      _category = 5010;
      tree_4l_SR->Fill();

    }

    if (sig_4l_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_4l_fake += 1;
      _category = 5020;
      tree_4l_fake->Fill();

    }

    if (sig_ttW_CR_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ttW_CR_SR += 1;
      _category = 6010;
      tree_ttW_CR_SR->Fill();

    }

    if (sig_ttW_CR_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ttW_CR_fake += 1;
      _category = 6020;
      tree_ttW_CR_fake->Fill();

    }

    if (sig_ttW_CR_flip) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ttW_CR_flip += 1;
      _category = 6030;
      tree_ttW_CR_flip->Fill();

    }

    if (sig_ttZ_CR_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ttZ_CR_SR += 1;
      _category = 7010;
      tree_ttZ_CR_SR->Fill();

    }

    if (sig_ttZ_CR_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ttZ_CR_fake += 1;
      _category = 7020;
      tree_ttZ_CR_fake->Fill();

    }

    if (sig_WZ_CR_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_WZ_CR_SR += 1;
      _category = 8010;
      tree_WZ_CR_SR->Fill();

    }

    if (sig_WZ_CR_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_WZ_CR_fake += 1;
      _category = 8020;
      tree_WZ_CR_fake->Fill();

    }

    if (sig_ZZ_CR_SR) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ZZ_CR_SR += 1;
      _category = 9010;
      tree_ZZ_CR_SR->Fill();

    }
    
    if (sig_ZZ_CR_fake) {

      _is_ttH_like = true;
      _is_tH_like_and_not_ttH_like = false;

      n_ZZ_CR_fake += 1;
      _category = 9020;
      tree_ZZ_CR_fake->Fill();

    }


  }

  
  cout<<" "<<endl;
  cout<<"2lss SR: "<<n_2lss_SR_ttH<<"/"<<n_2lss_SR_tH<<endl;
  cout<<"2lss fake: "<<n_2lss_fake_ttH<<"/"<<n_2lss_fake_tH<<endl;
  cout<<"2lss flip: "<<n_2lss_flip_ttH<<"/"<<n_2lss_flip_tH<<endl;
  cout<<" "<<endl;
  cout<<"3l SR: "<<n_3l_SR_ttH<<"/"<<n_3l_SR_tH<<endl;
  cout<<"3l fake: "<<n_3l_fake_ttH<<"/"<<n_3l_fake_tH<<endl;
  cout<<" "<<endl;
  cout<<"4l SR: "<<n_4l_SR<<endl;
  cout<<"4l fake: "<<n_4l_fake<<endl;
  cout<<" "<<endl;
  cout<<"2tau SR: "<<n_2tau_SR<<endl;
  cout<<"2tau fake: "<<n_2tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"1l1tau SR: "<<n_1l1tau_SR<<endl;
  cout<<"1l1tau fake: "<<n_1l1tau_fake<<endl; 
  cout<<" "<<endl;
  cout<<"1l2tau SR: "<<n_1l2tau_SR<<endl;  
  cout<<"1l2tau fake: "<<n_1l2tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"2lss1tau SR: "<<n_2lss1tau_SR<<endl;
  cout<<"2lss1tau fake: "<<n_2lss1tau_fake<<endl;
  cout<<"2lss1tau flip: "<<n_2lss1tau_flip<<endl;
  cout<<" "<<endl;
  cout<<"2los1tau SR: "<<n_2los1tau_SR<<endl;
  cout<<"2los1tau fake: "<<n_2los1tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"2l2tau SR: "<<n_2l2tau_SR<<endl;
  cout<<"2l2tau fake: "<<n_2l2tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"3l1tau SR: "<<n_3l1tau_SR<<endl;
  cout<<"3l1tau fake: "<<n_3l1tau_fake<<endl;
  cout<<" "<<endl;
  cout<<"ttW SR: "<<n_ttW_CR_SR<<endl;
  cout<<"ttW fake: "<<n_ttW_CR_fake<<endl;
  cout<<"ttW flip: "<<n_ttW_CR_flip<<endl;
  cout<<" "<<endl;
  cout<<"ttZ SR: "<<n_ttZ_CR_SR<<endl;
  cout<<"ttZ fake: "<<n_ttZ_CR_fake<<endl;
  cout<<" "<<endl;
  cout<<"WZ SR: "<<n_WZ_CR_SR<<endl;
  cout<<"WZ fake: "<<n_WZ_CR_fake<<endl;
  cout<<" "<<endl;
  cout<<"ZZ SR: "<<n_ZZ_CR_SR<<endl;
  cout<<"ZZ fake: "<<n_ZZ_CR_fake<<endl;
  cout<<" "<<endl;

  f_new->cd();
  
  h->Write();

  for(unsigned int i=0; i<tree_new.size();i++)
    tree_new[i]->Write();

  f_new->Close();

  return;

}


void test16(){

  TString fin = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2016/sync_ntuple_converted_ttHNonbb_2016_v13.root";
  TString fout = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/2016/sync_ntuple_splitted_ttHNonbb_2016_v3.root";

  split_tree(fin,fout,0,0,true,2016);

}

void test17(){

  TString fin = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2017/sync_ntuple_converted_ttHNonbb_2017_v8.root";
  TString fout = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/2017/sync_ntuple_splitted_ttHNonbb_2017_v3.root";

  split_tree(fin,fout,0,0,true,2017);

}

void test18(){

  TString fin = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2018/sync_ntuple_converted_ttHNonbb_2018_v7.root";
  TString fout = "/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/2018/sync_ntuple_splitted_ttHNonbb_2018_v3.root";

  split_tree(fin,fout,0,0,true,2018);

}
