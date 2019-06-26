#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <sys/stat.h>
#include <cmath>
#include <typeinfo>

using namespace std;

//ROOT libraries
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TBranch.h>
#include <TBranchElement.h>
#include <TCanvas.h>
#include <vector>
#include <TLorentzVector.h>
#include <TH2F.h>

#include <Math/Functor.h> // ROOT::Math::Functo
#include <Math/Factory.h> // ROOT::Math::Factory
#include <Math/Minimizer.h> // ROOT::Math::Minimizer
#include <TFile.h> // TFile
#include <TF1.h> // TF1

#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


//////////////////////
////// 1l+2tau ///////
//////////////////////

float avg_dr_jet;
float dr_taus;
float ptmiss;
float lep_conePt;
float mT_lep;
float mTauTauVis;
float mindr_lep_jet;
float mindr_tau1_jet;
float mindr_tau2_jet;
float dr_lep_tau_lead;
float dr_lep_tau_sublead;
float nBJetLoose;
float tau1_pt;
float tau2_pt;
float dr_lep_tau_ss;
float costS_tau;
float HTT;
float HadTop_pt;

TMVA::Reader* Book_1l2tau_MVAReader(std::string basePath, std::string weightFileName){

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");
    
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("dr_taus", &dr_taus );
    reader->AddVariable("ptmiss", &ptmiss );
    reader->AddVariable("lep_conePt", &lep_conePt );
    reader->AddVariable("mT_lep", &mT_lep );
    reader->AddVariable("mTauTauVis", &mTauTauVis );
    reader->AddVariable("mindr_lep_jet", &mindr_lep_jet );
    reader->AddVariable("mindr_tau1_jet", &mindr_tau1_jet );
    reader->AddVariable("mindr_tau2_jet", &mindr_tau2_jet );
    reader->AddVariable("dr_lep_tau_ss", &dr_lep_tau_ss );
    reader->AddVariable("dr_lep_tau_lead", &dr_lep_tau_lead );
    reader->AddVariable("costS_tau", &costS_tau );
    reader->AddVariable("nBJetLoose", &nBJetLoose );
    reader->AddVariable("tau1_pt", &tau1_pt );
    reader->AddVariable("tau2_pt", &tau2_pt );
    reader->AddVariable("HTT", &HTT );
    reader->AddVariable("HadTop_pt", &HadTop_pt );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


////////////////////////
////// 2lss+1tau ///////
////////////////////////

//float avg_dr_jet;
float dr_lep1_tau;
float dr_lep2_tau;
float dr_leps;
float lep2_conePt;
float mT_lep1;
float mT_lep2;
float mTauTauVis2;
float max_lep_eta;
float mbb;
float mindr_lep1_jet;
float mindr_lep2_jet;
float mindr_tau_jet;
float nJet;
//float ptmiss;
float tau_pt;
//float HTT;
//float HadTop_pt;

TMVA::Reader* Book_2lss1tau_MVAReader(std::string basePath, std::string weightFileName){

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");
    
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("dr_lep1_tau", &dr_lep1_tau );
    reader->AddVariable("dr_lep2_tau", &dr_lep2_tau );
    reader->AddVariable("dr_leps", &dr_leps );
    reader->AddVariable("lep2_conePt", &lep2_conePt );
    reader->AddVariable("mT_lep1", &mT_lep1 );
    reader->AddVariable("mT_lep2", &mT_lep2 );
    reader->AddVariable("mTauTauVis2", &mTauTauVis2 );
    reader->AddVariable("max_lep_eta", &max_lep_eta );
    reader->AddVariable("mbb", &mbb );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("mindr_lep2_jet", &mindr_lep2_jet );
    reader->AddVariable("mindr_tau_jet", &mindr_tau_jet );
    reader->AddVariable("nJet", &nJet );
    reader->AddVariable("ptmiss", &ptmiss );
    reader->AddVariable("tau_pt", &tau_pt );
    reader->AddVariable("HTT", &HTT );
    reader->AddVariable("HadTop_pt", &HadTop_pt );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


//////////////////////
////// 2l+2tau ///////
//////////////////////

//float mTauTauVis;
float cosThetaS_hadTau;
//float tau1_pt;
//float tau2_pt;
//float lep2_conePt;
//float mindr_lep1_jet;
//float mT_lep1;
//float mindr_tau_jet;
//float avg_dr_jet;
float avr_dr_lep_tau;
//float dr_taus;
float is_OS; 
//float nBJetLoose;

TMVA::Reader* Book_2l2tau_MVAReader(std::string basePath, std::string weightFileName){

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("mTauTauVis", &mTauTauVis );
    reader->AddVariable("cosThetaS_hadTau", &cosThetaS_hadTau );
    reader->AddVariable("tau1_pt", &tau1_pt );
    reader->AddVariable("tau2_pt", &tau2_pt );
    reader->AddVariable("lep2_conePt", &lep2_conePt );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("mT_lep1", &mT_lep1 );
    reader->AddVariable("mindr_tau_jet", &mindr_tau_jet );
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("avr_dr_lep_tau", &avr_dr_lep_tau );  
    reader->AddVariable("dr_taus", &dr_taus ); 
    reader->AddVariable("is_OS", &is_OS );
    reader->AddVariable("nBJetLoose", &nBJetLoose );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


//////////////////////
////// 3l+1tau ///////
//////////////////////

float lep1_conePt;
//float lep2_conePt;
//float mindr_lep1_jet;
//float max_lep_eta;
//float mindr_tau_jet;
//float ptmiss;
//float tau_pt;
//float dr_leps;
float mTauTauVis1;
//float mTauTauVis2;
float mbb_loose;
//float nJet;

TMVA::Reader* Book_3l1tau_MVAReader(std::string basePath, std::string weightFileName){

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("lep1_conePt", &lep1_conePt );
    reader->AddVariable("lep2_conePt", &lep2_conePt );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("max_lep_eta", &max_lep_eta );
    reader->AddVariable("mindr_tau_jet", &mindr_tau_jet );
    reader->AddVariable("ptmiss", &ptmiss );
    reader->AddVariable("tau_pt", &tau_pt );
    reader->AddVariable("dr_leps", &dr_leps );
    reader->AddVariable("mTauTauVis1", &mTauTauVis1 );
    reader->AddVariable("mTauTauVis2", &mTauTauVis2 );  
    reader->AddVariable("mbb_loose", &mbb_loose ); 
    reader->AddVariable("nJet", &nJet );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


//////////////////
////// HTT ///////
//////////////////

/*float btagDisc_b;
float btagDisc_Wj1;
float btagDisc_Wj2;
float qg_Wj1;
float qg_Wj2;
float m_bWj1Wj2;
float m_Wj1Wj2_div_m_bWj1Wj2;
float pT_Wj1Wj2;
float dR_Wj1Wj2;
float dR_bW;
float m_bWj1;
float m_bWj2;
float mass_Wj1;
float pT_Wj2;
float mass_Wj2;
float pT_b;
float mass_b;

TMVA::Reader* Book_HTT_MVAReader(std::string basePath, std::string weightFileName){

   TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

   reader->AddVariable("btagDisc_b",&btagDisc_b);
   reader->AddVariable("btagDisc_Wj1",&btagDisc_Wj1);
   reader->AddVariable("btagDisc_Wj2",&btagDisc_Wj2);
   reader->AddVariable("qg_Wj1",&qg_Wj1);
   reader->AddVariable("qg_Wj2",&qg_Wj2);
   reader->AddVariable("m_bWj1Wj2",&m_bWj1Wj2);
   reader->AddVariable("m_Wj1Wj2_div_m_bWj1Wj2",&m_Wj1Wj2_div_m_bWj1Wj2);
   reader->AddVariable("pT_Wj1Wj2",&pT_Wj1Wj2);
   reader->AddVariable("dR_Wj1Wj2",&dR_Wj1Wj2);;
   reader->AddVariable("dR_bW",&dR_bW);
   reader->AddVariable("m_bWj1",&m_bWj1);
   reader->AddVariable("m_bWj2",&m_bWj2);
   reader->AddVariable("mass_Wj1",&mass_Wj1);
   reader->AddVariable("pT_Wj2",&pT_Wj2);
   reader->AddVariable("mass_Wj2",&mass_Wj2);
   reader->AddVariable("pT_b",&pT_b);
   reader->AddVariable("mass_b",&mass_b);

   reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

   return reader;

}*/

//////////////////////////////
////// HTT SemiBoosted ///////
//////////////////////////////

/*
float massW_SD;
float tau21W;
//float btagDisc_b;
float pT_bWj1Wj2;
//float m_bWj1Wj2;
//float m_Wj1Wj2_div_m_bWj1Wj2;
//float dR_Wj1Wj2;
//float mass_Wj1;
//float pT_Wj2;
//float mass_Wj2;
//float pT_b;
//float mass_b;

TMVA::Reader* Book_HTT_SemiBoosted_MVAReader(std::string basePath, std::string weightFileName){

   TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

   reader->AddVariable("massW_SD",&massW_SD);
   reader->AddVariable("tau21W",&tau21W);
   reader->AddVariable("btagDisc_b",&btagDisc_b);
   reader->AddVariable("pT_bWj1Wj2",&pT_bWj1Wj2);
   reader->AddVariable("m_bWj1Wj2",&m_bWj1Wj2);
   reader->AddVariable("m_Wj1Wj2_div_m_bWj1Wj2",&m_Wj1Wj2_div_m_bWj1Wj2);
   reader->AddVariable("dR_Wj1Wj2",&dR_Wj1Wj2);
   reader->AddVariable("mass_Wj1",&mass_Wj1);
   reader->AddVariable("pT_Wj2",&pT_Wj2);
   reader->AddVariable("mass_Wj2",&mass_Wj2);
   reader->AddVariable("pT_b",&pT_b);
   reader->AddVariable("mass_b",&mass_b);

   reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

   return reader;

}*/

void add_BDT(TString filein, TString fileout, vector<TString> treename){

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  f_new = TFile::Open(fileout,"RECREATE");  


  /*TMVA::Reader* MVA_HTT_reader = Book_HTT_MVAReader("TauCats_weights/HTT","HTT_HadTopTagger_2017_nomasscut_nvar17_resolved.xml");
  if(!MVA_HTT_reader) std::cout << "No HTT xml file"<<std::endl;*/

  /*TMVA::Reader* MVA_HTT_SemiBoosted_reader = Book_HTT_SemiBoosted_MVAReader("TauCats_weights/HTT","HTT_HadTopTagger_2017_nomasscut_nvar12_semi_boosted_AK8.xml");
  if(!MVA_HTT_SemiBoosted_reader) std::cout << "No HTT semiboosted xml file"<<std::endl;*/

  TMVA::Reader* MVA_1l2tau_reader = Book_1l2tau_MVAReader("TauCats_weights/1l2tau","1l_2tau_XGB_HTT_evtLevelSUM_TTH_VT_17Var.xml");
  if(!MVA_1l2tau_reader) std::cout << "No 1l2tau xml file"<<std::endl;

  TMVA::Reader* MVA_2lss1tau_reader = Book_2lss1tau_MVAReader("TauCats_weights/2lss1tau","2lss_1tau_XGB_HTT_evtLevelSUM_TTH_M_18Var.xml");
  if(!MVA_2lss1tau_reader) std::cout << "No 2lss1tau xml file"<<std::endl;

  TMVA::Reader* MVA_2l2tau_reader = Book_2l2tau_MVAReader("TauCats_weights/2l2tau","2l_2tau_XGB_plainKin_evtLevelSUM_TTH_VT_13Var.xml");
  if(!MVA_2l2tau_reader) std::cout << "No 2l12au xml file"<<std::endl;
  
  TMVA::Reader* MVA_3l1tau_reader = Book_3l1tau_MVAReader("TauCats_weights/3l1tau","3l_1tau_XGB_plainKin_evtLevelSUM_TTH_M_12Var.xml");
  if(!MVA_3l1tau_reader) std::cout << "No 3l1tau xml file"<<std::endl;
	
  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filein);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;

    //old branches used

    int _category;

    int _n_recolep_sel;
    int _n_recotauh_sel;
    int _n_recoPFJet_btag_loose;
    int _n_recoPFJet_btag_medium;
    int _n_recoPFLightJet;

    vector<float> *_recolep_sel_px;
    vector<float> *_recolep_sel_py;
    vector<float> *_recolep_sel_pz;
    vector<float> *_recolep_sel_e;

    vector<float> *_recotauh_sel_px;
    vector<float> *_recotauh_sel_py;
    vector<float> *_recotauh_sel_pz;
    vector<float> *_recotauh_sel_e;

    vector<float> *_recoPFJet_px;
    vector<float> *_recoPFJet_py;
    vector<float> *_recoPFJet_pz;
    vector<float> *_recoPFJet_e;
    vector<float> *_recoPFJet_DeepJetscore;

    vector<float> *_recoPFAk8Jet_px;
    vector<float> *_recoPFAk8Jet_py;
    vector<float> *_recoPFAk8Jet_pz;
    vector<float> *_recoPFAk8Jet_e;

    float _PFMET;
    float _PFMET_phi;

    tree->SetBranchAddress("category", &_category);

    tree->SetBranchAddress("n_recolep_sel",&_n_recolep_sel);
    tree->SetBranchAddress("n_recotauh_sel",&_n_recotauh_sel);
    tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);
    tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
    tree->SetBranchAddress("n_recoPFLightJet",&_n_recoPFLightJet);

    tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
    tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
    tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
    tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);

    tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
    tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
    tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
    tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);

    tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
    tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
    tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
    tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
    tree->SetBranchAddress("recoPFJet_DeepJetscore",&_recoPFJet_DeepJetscore);

    tree->SetBranchAddress("recoPFAk8Jet_px",&_recoPFAk8Jet_px);
    tree->SetBranchAddress("recoPFAk8Jet_py",&_recoPFAk8Jet_py);
    tree->SetBranchAddress("recoPFAk8Jet_pz",&_recoPFAk8Jet_pz);
    tree->SetBranchAddress("recoPFAk8Jet_e",&_recoPFAk8Jet_e);

    tree->SetBranchAddress("PFMET",&_PFMET);
    tree->SetBranchAddress("PFMET_phi",&_PFMET_phi);

    //new branches

    float _BDTscore_1l2tau;
    float _BDTscore_2lss1tau;
    float _BDTscore_2l2tau;
    float _BDTscore_3l1tau;

    float _BDTscore_HTT;
    float _BDTscore_HTTsemiboosted;

    TTree* tree_new=tree->GetTree()->CloneTree(0);

    tree_new->Branch("BDTscore_1l2tau",&_BDTscore_1l2tau);
    tree_new->Branch("BDTscore_2lss1tau",&_BDTscore_2lss1tau);
    tree_new->Branch("BDTscore_2l2tau",&_BDTscore_2l2tau);
    tree_new->Branch("BDTscore_3l1tau",&_BDTscore_3l1tau);

    tree_new->Branch("BDTscore_HTT",&_BDTscore_HTT);
    tree_new->Branch("BDTscore_HTTsemiboosted",&_BDTscore_HTTsemiboosted);

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
        cout<<"i="<<i<<endl;

      _BDTscore_1l2tau = 0;
      _BDTscore_2lss1tau = 0;
      _BDTscore_2l2tau = 0;
      _BDTscore_3l1tau = 0;

      _BDTscore_HTT = 0;
      _BDTscore_HTTsemiboosted = 0;

      _recolep_sel_px = 0;
      _recolep_sel_py = 0;
      _recolep_sel_pz = 0;
      _recolep_sel_e = 0;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;

      _recoPFJet_px = 0;
      _recoPFJet_py = 0;
      _recoPFJet_pz = 0;
      _recoPFJet_e = 0;
      _recoPFJet_DeepJetscore = 0;

      _recoPFAk8Jet_px = 0;
      _recoPFAk8Jet_py = 0;
      _recoPFAk8Jet_pz = 0;
      _recoPFAk8Jet_e = 0;

      _PFMET = 0;
      _PFMET_phi = 0;

      tree->GetEntry(i);

      //code here

      tree_new->Fill();

    }

    f_new->cd();
    tree_new->Write();

  }

  f_new->Close();
  return;

}


void test16(){

  TString filein="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/2016/sync_ntuple_splitted_ttHNonbb_2016_v12.root";
  TString fileout="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted_BDT/2016/sync_ntuple_splitted_BDT_ttHNonbb_2016_v1.root";

  vector<TString> tree;
  tree.push_back("HTauTauTree_1l2tau_SR");
  tree.push_back("HTauTauTree_1l12tau_fake");
  tree.push_back("HTauTauTree_2lss1tau_SR");
  tree.push_back("HTauTauTree_2lss1tau_fake");
  tree.push_back("HTauTauTree_2lss1tau_flip");
  tree.push_back("HTauTauTree_2l2tau_SR");
  tree.push_back("HTauTauTree_2l2tau_fake");
  tree.push_back("HTauTauTree_3l1tau_SR");
  tree.push_back("HTauTauTree_3l1tau_fake");

  add_BDT(filein,fileout,tree);

}



