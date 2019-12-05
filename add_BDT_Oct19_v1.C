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
#include <TLorentzVector.h>

#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


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
float dr_lep1_tau;
float dr_lep2_tau;
float dr_leps;
float lep2_conePt;
float mT_lep1;
float mT_lep2;
float mTauTauVis2;
float mbb_loose;
float max_lep_eta;
float mbb;
float mindr_lep1_jet;
float mindr_lep2_jet;
float mindr_tau_jet;
float nJet;
float tau_pt;
float cosThetaS_hadTau;
float avr_dr_lep_tau;
float is_OS; 
float lep1_conePt;
float mTauTauVis1;


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

float btagDisc_b;
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
  reader->AddVariable("m_Wj1Wj2_div_m_bWj1Wj2",&m_Wj1Wj2_div_m_bWj1Wj2);
  reader->AddVariable("pT_Wj1Wj2",&pT_Wj1Wj2);
  reader->AddVariable("dR_Wj1Wj2",&dR_Wj1Wj2);
  reader->AddVariable("m_bWj1Wj2",&m_bWj1Wj2);
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

}

//////////////////////////////
////// HTT SemiBoosted ///////
//////////////////////////////


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
  reader->AddVariable("m_Wj1Wj2_div_m_bWj1Wj2",&m_Wj1Wj2_div_m_bWj1Wj2);
  reader->AddVariable("dR_Wj1Wj2",&dR_Wj1Wj2);
  reader->AddVariable("m_bWj1Wj2",&m_bWj1Wj2);
  reader->AddVariable("pT_bWj1Wj2",&pT_bWj1Wj2);
  reader->AddVariable("mass_Wj1",&mass_Wj1);
  reader->AddVariable("pT_Wj2",&pT_Wj2);
  reader->AddVariable("mass_Wj2",&mass_Wj2);
  reader->AddVariable("pT_b",&pT_b);
  reader->AddVariable("mass_b",&mass_b);

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}

void add_BDT(TString filein, TString fileout, vector<TString> treename){

  TFile* f_new = TFile::Open(fileout);
  /*if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/

  f_new = TFile::Open(fileout,"RECREATE");  


  TMVA::Reader* MVA_HTT_reader = Book_HTT_MVAReader("TauCats_weights/HTT","HTT_HadTopTagger_2017_nomasscut_nvar17_resolved.xml");
  if(!MVA_HTT_reader) std::cout << "No HTT xml file"<<std::endl;

  TMVA::Reader* MVA_HTT_SemiBoosted_reader = Book_HTT_SemiBoosted_MVAReader("TauCats_weights/HTT","HTT_HadTopTagger_2017_nomasscut_nvar12_semi_boosted_AK8.xml");
  if(!MVA_HTT_SemiBoosted_reader) std::cout << "No HTT semiboosted xml file"<<std::endl;

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
    cout<<treename[i_tree]<<", nentries="<<tree->GetEntries()<<endl;

    //old branches used

    ULong64_t _EventNumber;

    int _category;

    int _n_recolep_sel;
    int _n_recotauh_sel;
    int _n_recoPFJet;
    int _n_recoPFak8Jet;
    int _n_recoPFJet_btag_loose;
    int _n_recoPFJet_btag_medium;
    int _n_recoPFLightJet;

    vector<float> *_recolep_sel_px;
    vector<float> *_recolep_sel_py;
    vector<float> *_recolep_sel_pz;
    vector<float> *_recolep_sel_e;
    vector<float> *_recolep_sel_conept;
    vector<float> *_recolep_sel_pt;
    vector<float> *_recolep_sel_phi;
    vector<float> *_recolep_sel_charge;

    vector<float> *_recotauh_sel_px;
    vector<float> *_recotauh_sel_py;
    vector<float> *_recotauh_sel_pz;
    vector<float> *_recotauh_sel_e;
    vector<float> *_recotauh_sel_charge;

    vector<float> *_recoPFJet_px;
    vector<float> *_recoPFJet_py;
    vector<float> *_recoPFJet_pz;
    vector<float> *_recoPFJet_e;
    vector<float> *_recoPFJet_DeepJetscore;
    vector<float> *_recoPFJet_DeepCSVscore;
    vector<float> *_recoPFJet_QGdiscr;

    vector<float> *_recoPFak8Jet_px;
    vector<float> *_recoPFak8Jet_py;
    vector<float> *_recoPFak8Jet_pz;
    vector<float> *_recoPFak8Jet_e;
    vector<float> *_recoPFak8Jet_SoftDropMass;
    vector<float> *_recoPFak8Jet_tau1;
    vector<float> *_recoPFak8Jet_tau2;
    vector<float> *_recoPFak8Jet_subjet1_px;
    vector<float> *_recoPFak8Jet_subjet1_py;
    vector<float> *_recoPFak8Jet_subjet1_pz;
    vector<float> *_recoPFak8Jet_subjet1_e;
    vector<float> *_recoPFak8Jet_subjet2_px;
    vector<float> *_recoPFak8Jet_subjet2_py;
    vector<float> *_recoPFak8Jet_subjet2_pz;
    vector<float> *_recoPFak8Jet_subjet2_e;

    float _PFMET;
    float _PFMET_phi;

    tree->SetBranchAddress("EventNumber",&_EventNumber);

    tree->SetBranchAddress("category", &_category);

    tree->SetBranchAddress("n_recolep_sel",&_n_recolep_sel);
    tree->SetBranchAddress("n_recotauh_sel",&_n_recotauh_sel);
    tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
    tree->SetBranchAddress("n_recoPFak8Jet",&_n_recoPFak8Jet);
    tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);
    tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
    tree->SetBranchAddress("n_recoPFLightJet",&_n_recoPFLightJet);

    tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
    tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
    tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
    tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_phi",&_recolep_sel_phi);
    tree->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);

    tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
    tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
    tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
    tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
    tree->SetBranchAddress("recotauh_sel_charge",&_recotauh_sel_charge);

    tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
    tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
    tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
    tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
    tree->SetBranchAddress("recoPFJet_DeepJetscore",&_recoPFJet_DeepJetscore);
    tree->SetBranchAddress("recoPFJet_DeepCSVscore",&_recoPFJet_DeepCSVscore);
    tree->SetBranchAddress("recoPFJet_QGdiscr",&_recoPFJet_QGdiscr);

    tree->SetBranchAddress("recoPFak8Jet_px",&_recoPFak8Jet_px);
    tree->SetBranchAddress("recoPFak8Jet_py",&_recoPFak8Jet_py);
    tree->SetBranchAddress("recoPFak8Jet_pz",&_recoPFak8Jet_pz);
    tree->SetBranchAddress("recoPFak8Jet_e",&_recoPFak8Jet_e);
    tree->SetBranchAddress("recoPFak8Jet_SoftDropMass",&_recoPFak8Jet_SoftDropMass);
    tree->SetBranchAddress("recoPFak8Jet_tau1",&_recoPFak8Jet_tau1);
    tree->SetBranchAddress("recoPFak8Jet_tau2",&_recoPFak8Jet_tau2);
    tree->SetBranchAddress("recoPFak8Jet_subjet1_px",&_recoPFak8Jet_subjet1_px);
    tree->SetBranchAddress("recoPFak8Jet_subjet1_py",&_recoPFak8Jet_subjet1_py);
    tree->SetBranchAddress("recoPFak8Jet_subjet1_pz",&_recoPFak8Jet_subjet1_pz);
    tree->SetBranchAddress("recoPFak8Jet_subjet1_e",&_recoPFak8Jet_subjet1_e);
    tree->SetBranchAddress("recoPFak8Jet_subjet2_px",&_recoPFak8Jet_subjet2_px);
    tree->SetBranchAddress("recoPFak8Jet_subjet2_py",&_recoPFak8Jet_subjet2_py);
    tree->SetBranchAddress("recoPFak8Jet_subjet2_pz",&_recoPFak8Jet_subjet2_pz);
    tree->SetBranchAddress("recoPFak8Jet_subjet2_e",&_recoPFak8Jet_subjet2_e);

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

    float _btagDisc_b;
    float _btagDisc_Wj1;
    float _btagDisc_Wj2;
    float _qg_Wj1;
    float _qg_Wj2;
    float _m_bWj1Wj2;
    float _m_Wj1Wj2_div_m_bWj1Wj2;
    float _pT_Wj1Wj2;
    float _dR_Wj1Wj2;
    float _dR_bW;
    float _m_bWj1;
    float _m_bWj2;
    float _mass_Wj1;
    float _pT_Wj2;
    float _mass_Wj2;
    float _pT_b;
    float _mass_b;

    float _HTToutput;
    float _HTT;
    float _HadTop_pt;

    float _massW_SD;
    float _tau21W;
    float _pT_bWj1Wj2;

    float _HTTsemiboostedoutput;
    float _HTTsemiboosted;

    float _avg_dr_jet;
    float _dr_taus;
    float _ptmiss;
    float _lep_conePt;
    float _mT_lep;
    float _mTauTauVis;
    float _mindr_lep_jet;
    float _mindr_tau1_jet;
    float _mindr_tau2_jet;
    float _dr_lep_tau_lead;
    float _dr_lep_tau_sublead;
    float _nBJetLoose;
    float _tau1_pt;
    float _tau2_pt;
    float _dr_lep_tau_ss;
    float _costS_tau;

    float _dr_lep1_tau;
    float _dr_lep2_tau;
    float _dr_leps;
    float _lep2_conePt;
    float _mT_lep1;
    float _mT_lep2;
    float _mTauTauVis2;
    float _mbb_loose;
    float _max_lep_eta;
    float _mbb;
    float _mindr_lep1_jet;
    float _mindr_lep2_jet;
    float _mindr_tau_jet;
    float _nJet;
    float _tau_pt;
    float _cosThetaS_hadTau;
    float _avr_dr_lep_tau;
    float _is_OS; 
    float _lep1_conePt;
    float _mTauTauVis1;

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
        cout<<"i="<<i<<endl;

      _EventNumber = 0; 
      _category = 0;

      _n_recolep_sel = 0;
      _n_recotauh_sel = 0;
      _n_recoPFJet = 0;
      _n_recoPFak8Jet = 0;
      _n_recoPFJet_btag_loose = 0;
      _n_recoPFJet_btag_medium = 0;
      _n_recoPFLightJet = 0;

      _recolep_sel_px = 0;
      _recolep_sel_py = 0;
      _recolep_sel_pz = 0;
      _recolep_sel_e = 0;
      _recolep_sel_conept = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_phi = 0;
      _recolep_sel_charge = 0;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      _recotauh_sel_charge = 0;

      _recoPFJet_px = 0;
      _recoPFJet_py = 0;
      _recoPFJet_pz = 0;
      _recoPFJet_e = 0;
      _recoPFJet_DeepJetscore = 0;
      _recoPFJet_DeepCSVscore = 0;
      _recoPFJet_QGdiscr = 0;

      _recoPFak8Jet_px = 0;
      _recoPFak8Jet_py = 0;
      _recoPFak8Jet_pz = 0;
      _recoPFak8Jet_e = 0;
      _recoPFak8Jet_SoftDropMass = 0;
      _recoPFak8Jet_tau1 = 0;
      _recoPFak8Jet_tau2 = 0;
      _recoPFak8Jet_subjet1_px = 0;
      _recoPFak8Jet_subjet1_py = 0;
      _recoPFak8Jet_subjet1_pz = 0;
      _recoPFak8Jet_subjet1_e = 0;
      _recoPFak8Jet_subjet2_px = 0;
      _recoPFak8Jet_subjet2_py = 0;
      _recoPFak8Jet_subjet2_pz = 0;
      _recoPFak8Jet_subjet2_e = 0;

      _PFMET = 0;
      _PFMET_phi = 0;

      _btagDisc_b = 0;
      _btagDisc_Wj1 = 0;
      _btagDisc_Wj2 = 0;
      _qg_Wj1 = 0;
      _qg_Wj2 = 0;
      _m_bWj1Wj2 = 0;
      _m_Wj1Wj2_div_m_bWj1Wj2 = 0;
      _pT_Wj1Wj2 = 0;
      _dR_Wj1Wj2 = 0;
      _dR_bW = 0;
      _m_bWj1 = 0;
      _m_bWj2 = 0;
      _mass_Wj1 = 0;
      _pT_Wj2 = 0;
      _mass_Wj2 = 0;
      _pT_b = 0;
      _mass_b = 0;

      _HTToutput = -1;
      _HTT = -1;
      _HadTop_pt = 0;

      _massW_SD = 0;
      _tau21W = 0;
      _pT_bWj1Wj2 = 0;

      _HTTsemiboostedoutput = -1;
      _HTTsemiboosted = -1;

      _avg_dr_jet = 0;
      _dr_taus = 0;
      _ptmiss = 0;
      _lep_conePt = 0;
      _mT_lep = 0;
      _mTauTauVis = 0;
      _mindr_lep_jet = 0;
      _mindr_tau1_jet = 0;
      _mindr_tau2_jet = 0;
      _dr_lep_tau_lead = 0;
      _dr_lep_tau_sublead = 0;
      _nBJetLoose = 0;
      _tau1_pt = 0;
      _tau2_pt = 0;
      _dr_lep_tau_ss = 0;
      _costS_tau = 0;

      _dr_lep1_tau = 0;
      _dr_lep2_tau = 0;
      _dr_leps = 0;
      _lep2_conePt = 0;
      _mT_lep1 = 0;
      _mT_lep2 = 0;
      _mTauTauVis2 = 0;
      _max_lep_eta = 0;
      _mbb = 0;
      _mindr_lep1_jet = 0;
      _mindr_lep2_jet = 0;
      _mindr_tau_jet = 0;
      _nJet = 0;
      _tau_pt = 0;
      _cosThetaS_hadTau = 0;
      _avr_dr_lep_tau = 0;
      _is_OS = 0;
      _dr_lep_tau_ss = 0;
      _lep1_conePt = 0;
      _mTauTauVis1 = 0;

      _BDTscore_1l2tau = -999.;
      _BDTscore_2lss1tau = -999.;
      _BDTscore_2l2tau = -999.;
      _BDTscore_3l1tau = -999.;

      _BDTscore_HTT = -999.;
      _BDTscore_HTTsemiboosted = -999.;

      tree->GetEntry(i);

      /////////////////////
      //////// HTT ////////
      /////////////////////

      // used in 0l2tau (1010,1020), 1l1tau (2010,2020,2030), 1l2tau (2110,2120), 2lss (3010,3020,3030), 2lss1tau (3110,3120,3130), 2los1tau (3210,3220)

      /*if( 
        _category==1010 || _category==1020 ||
        _category==2010 || _category==2020 || _category==2030 ||
        _category==2110 || _category==2120 || 
        _category==3010 || _category==3020 || _category==3030 ||
        _category==3110 || _category==3120 || _category==3130 ||
        _category==3210 || _category==3220 
        ){*/

        for ( int i_bjet = 0; i_bjet<_n_recoPFJet; i_bjet++) {

          TLorentzVector bjet((*_recoPFJet_px)[i_bjet],(*_recoPFJet_py)[i_bjet],(*_recoPFJet_pz)[i_bjet],(*_recoPFJet_e)[i_bjet]);

          for ( int i_Wjet1 = 0; i_Wjet1<_n_recoPFJet; i_Wjet1++) {

            TLorentzVector Wjet1((*_recoPFJet_px)[i_Wjet1],(*_recoPFJet_py)[i_Wjet1],(*_recoPFJet_pz)[i_Wjet1],(*_recoPFJet_e)[i_Wjet1]);

            if ( Wjet1==bjet ) continue;

            for ( int i_Wjet2 = 0; i_Wjet2<_n_recoPFJet; i_Wjet2++) {

              TLorentzVector Wjet2((*_recoPFJet_px)[i_Wjet2],(*_recoPFJet_py)[i_Wjet2],(*_recoPFJet_pz)[i_Wjet2],(*_recoPFJet_e)[i_Wjet2]);

              if ( Wjet2==bjet ) continue;
              if ( Wjet2==Wjet1 ) continue;

              _btagDisc_b = (*_recoPFJet_DeepCSVscore)[i_bjet];
              _btagDisc_Wj1 = (*_recoPFJet_DeepCSVscore)[i_Wjet1];
              _btagDisc_Wj2 = (*_recoPFJet_DeepCSVscore)[i_Wjet2];
              _qg_Wj1 = (*_recoPFJet_QGdiscr)[i_Wjet1];
              _qg_Wj2 = (*_recoPFJet_QGdiscr)[i_Wjet2];
              _m_bWj1Wj2 = (bjet+Wjet1+Wjet2).M();
              _m_Wj1Wj2_div_m_bWj1Wj2 = (Wjet1+Wjet2).M()/_m_bWj1Wj2;
              _pT_Wj1Wj2 = (Wjet1+Wjet2).Pt();
              _dR_Wj1Wj2 = Wjet1.DeltaR(Wjet2);
              _dR_bW = bjet.DeltaR(Wjet1+Wjet2);
              _m_bWj1 = (bjet+Wjet1).M();
              _m_bWj2 = (bjet+Wjet2).M();
              _mass_Wj1 = Wjet1.M();
              _pT_Wj2 = Wjet2.Pt();
              _mass_Wj2 = Wjet2.M();
              _pT_b = bjet.Pt();
              _mass_b = bjet.M();

              btagDisc_b = _btagDisc_b;
              btagDisc_Wj1 = _btagDisc_Wj1;
              btagDisc_Wj2 = _btagDisc_Wj2;
              qg_Wj1 = _qg_Wj1;
              qg_Wj2 = _qg_Wj2;
              m_bWj1Wj2 = _m_bWj1Wj2;
              m_Wj1Wj2_div_m_bWj1Wj2 = _m_Wj1Wj2_div_m_bWj1Wj2;
              pT_Wj1Wj2 = _pT_Wj1Wj2;
              dR_Wj1Wj2 = _dR_Wj1Wj2;
              dR_bW = _dR_bW;
              m_bWj1 = _m_bWj1;
              m_bWj2 = _m_bWj2;
              mass_Wj1 = _mass_Wj1;
              pT_Wj2 = _pT_Wj2;
              mass_Wj2 = _mass_Wj2;
              pT_b = _pT_b;
              mass_b = _mass_b;

              double bdtResult = MVA_HTT_reader->EvaluateMVA("BDTG method");

              if ( bdtResult > _HTToutput ) {
                 _HTToutput = bdtResult;
                 _HTT = 1. / (1. + sqrt((1. - _HTToutput) / (1. + _HTToutput))); 
                 _HadTop_pt = (bjet+Wjet1+Wjet2).Pt();
              }

            }
          }
        }
      /*}*/

      _BDTscore_HTT = _HTT;

      cout<<"_EventNumber "<<_EventNumber<<", HTT "<<_BDTscore_HTT<<endl;

      /////////////////////////////
      //////// Boosted HTT ////////
      /////////////////////////////

      /*if(_category==3210 || _category==3220 || _category==1010 || _category==1020 ){


        //cleaned jets from ak8 jets

        vector<TLorentzVector> cleaned_jets;
        vector<float> DeepCSV_cleaned_jets;

        for ( int i_jet = 0; i_jet<_n_recoPFJet; i_jet++) {

          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);

          //cleaning from ak8 jets
          bool dR_veto = false;
          for (int i_ak8jet = 0; i_ak8jet<_n_recoPFak8Jet; i_ak8jet++) {
            TLorentzVector ak8jet((*_recoPFak8Jet_px)[i_ak8jet],(*_recoPFak8Jet_py)[i_ak8jet],(*_recoPFak8Jet_pz)[i_ak8jet],(*_recoPFak8Jet_e)[i_ak8jet]);
            float dR=ak8jet.DeltaR(jet);
            if(dR<0.8) {
              dR_veto=true;
              break; 
            }
          }

          if(dR_veto) 
            continue;

          cleaned_jets.push_back(jet);
          DeepCSV_cleaned_jets.push_back((*_recoPFJet_DeepCSVscore)[i_jet]);

        }

        int n_cleaned_jets = cleaned_jets.size();

        for ( int i_bjet = 0; i_bjet<n_cleaned_jets; i_bjet++) {

          TLorentzVector bjet = cleaned_jets.at(i_bjet);

          for ( int i_ak8jet = 0; i_ak8jet<_n_recoPFak8Jet; i_ak8jet++) {

            TLorentzVector ak8jet((*_recoPFak8Jet_px)[i_ak8jet],(*_recoPFak8Jet_py)[i_ak8jet],(*_recoPFak8Jet_pz)[i_ak8jet],(*_recoPFak8Jet_e)[i_ak8jet]);

            TLorentzVector Wjet1((*_recoPFak8Jet_subjet1_px)[i_ak8jet],(*_recoPFak8Jet_subjet1_py)[i_ak8jet],(*_recoPFak8Jet_subjet1_pz)[i_ak8jet],(*_recoPFak8Jet_subjet1_e)[i_ak8jet]);
            TLorentzVector Wjet2((*_recoPFak8Jet_subjet2_px)[i_ak8jet],(*_recoPFak8Jet_subjet2_py)[i_ak8jet],(*_recoPFak8Jet_subjet2_pz)[i_ak8jet],(*_recoPFak8Jet_subjet2_e)[i_ak8jet]);

            _massW_SD = (*_recoPFak8Jet_SoftDropMass)[i_ak8jet];
            _tau21W = (*_recoPFak8Jet_tau2)[i_ak8jet] / (*_recoPFak8Jet_tau1)[i_ak8jet];
            _btagDisc_b = DeepCSV_cleaned_jets.at(i_bjet);
            _pT_bWj1Wj2 = (bjet+Wjet1+Wjet2).Pt();
            _m_bWj1Wj2 = (bjet+Wjet1+Wjet2).M();
            _m_Wj1Wj2_div_m_bWj1Wj2 = (Wjet1+Wjet2).M()/_m_bWj1Wj2;
            _dR_Wj1Wj2 = Wjet1.DeltaR(Wjet2);
            _mass_Wj1 = Wjet1.M();
            _pT_Wj2 = Wjet2.Pt();
            _mass_Wj2 = Wjet2.M();
            _pT_b = bjet.Pt();
            _mass_b = bjet.M();

            btagDisc_b = _btagDisc_b;
            btagDisc_Wj1 = _btagDisc_Wj1;
            btagDisc_Wj2 = _btagDisc_Wj2;
            qg_Wj1 = _qg_Wj1;
            qg_Wj2 = _qg_Wj2;
            m_bWj1Wj2 = _m_bWj1Wj2;
            m_Wj1Wj2_div_m_bWj1Wj2 = _m_Wj1Wj2_div_m_bWj1Wj2;
            pT_Wj1Wj2 = _pT_Wj1Wj2;
            dR_Wj1Wj2 = _dR_Wj1Wj2;
            dR_bW = _dR_bW;
            m_bWj1 = _m_bWj1;
            m_bWj2 = _m_bWj2;
            mass_Wj1 = _mass_Wj1;
            pT_Wj2 = _pT_Wj2;
            mass_Wj2 = _mass_Wj2;
            pT_b = _pT_b;
            mass_b = _mass_b;

            double bdtResult = MVA_HTT_SemiBoosted_reader->EvaluateMVA("BDTG method");
            //cout<<"bdtResult"<<bdtResult<<endl;

            if ( bdtResult > _HTToutput ) {
              _HTTsemiboostedoutput = bdtResult;
              _HTTsemiboosted = 1. / (1. + sqrt((1. - _HTTsemiboostedoutput) / (1. + _HTTsemiboostedoutput))); 
              _HadTop_pt = (bjet+ak8jet).Pt();
            }
          }
        }
      }

      _BDTscore_HTTsemiboosted = _HTTsemiboosted;
      */

      ////////////////////////
      //////// 1l2tau ////////
      ////////////////////////

      if(_category==2110 || _category==2120){

        TLorentzVector lep( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
        TLorentzVector tau1((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 
        TLorentzVector tau2((*_recotauh_sel_px)[1],(*_recotauh_sel_py)[1],(*_recotauh_sel_pz)[1],(*_recotauh_sel_e)[1]); 

        _avg_dr_jet = 0;
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

        float minDR_l_j = 9999;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(lep);
          if(i_dR < minDR_l_j) minDR_l_j = i_dR;
        }
        _mindr_lep_jet = minDR_l_j;

        float minDR_t1_j = 9999;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(tau1);
          if(i_dR < minDR_t1_j) minDR_t1_j = i_dR;
        }
        _mindr_tau1_jet = minDR_t1_j;

        float minDR_t2_j = 9999;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(tau2);
          if(i_dR < minDR_t2_j) minDR_t2_j = i_dR;
        }
        _mindr_tau2_jet = minDR_t2_j;

        _dr_taus = tau1.DeltaR(tau2);
        _ptmiss = _PFMET;
        _mTauTauVis = (tau1+tau2).M();
        _lep_conePt = (*_recolep_sel_conept)[0];
        _mT_lep = sqrt(2*((*_recolep_sel_pt)[0])*_PFMET*(1-cos(((*_recolep_sel_phi)[0])-_PFMET_phi)));
        _dr_lep_tau_lead = lep.DeltaR(tau1);
        _dr_lep_tau_sublead = lep.DeltaR(tau2);
        _nBJetLoose = _n_recoPFJet_btag_loose;
        _tau1_pt = tau1.Pt();
        _tau2_pt = tau2.Pt();

        if( ((*_recolep_sel_charge)[0]*(*_recotauh_sel_charge)[0])>0 ) 
          _dr_lep_tau_ss = lep.DeltaR(tau1);
        else if( ((*_recolep_sel_charge)[0]*(*_recotauh_sel_charge)[1])>0 )
          _dr_lep_tau_ss = lep.DeltaR(tau2);

        _costS_tau = abs(tau1.CosTheta());

        avg_dr_jet = _avg_dr_jet;
        dr_taus = _dr_taus;
        ptmiss = _ptmiss;
        lep_conePt = _lep_conePt;
        mT_lep = _mT_lep;
        mTauTauVis = _mTauTauVis;
        mindr_lep_jet = _mindr_lep_jet;
        mindr_tau1_jet = _mindr_tau1_jet;
        mindr_tau2_jet = _mindr_tau2_jet;
        dr_lep_tau_lead = _dr_lep_tau_lead;
        dr_lep_tau_sublead = _dr_lep_tau_sublead;
        nBJetLoose = _nBJetLoose;
        tau1_pt = _tau1_pt;
        tau2_pt = _tau2_pt;
        dr_lep_tau_ss = _dr_lep_tau_ss;
        costS_tau = _costS_tau;
        
        HTT = _HTT;
        HadTop_pt = _HadTop_pt;

        float _BDToutput_1l2tau = MVA_1l2tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_1l2tau =  1. / (1. + sqrt((1. - _BDToutput_1l2tau) / (1. + _BDToutput_1l2tau)));

      }      

      tree_new->Fill();

    }

    f_new->cd();
    tree_new->Write();

  }

  f_new->Close();
  return;

}


void test16(){

  TString filein="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/2016/sync_ntuple_splitted_ttHNonbb_2016_Oct19_v1.root";
  TString fileout="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted_BDT/2016/sync_ntuple_splitted_BDT_ttHNonbb_2016_Oct19_v1.root";

  vector<TString> tree;
  tree.push_back("HTauTauTree_2tau_SR");
  tree.push_back("HTauTauTree_2tau_fake");
  tree.push_back("HTauTauTree_1l1tau_SR");
  tree.push_back("HTauTauTree_1l1tau_fake");
  tree.push_back("HTauTauTree_1l2tau_SR");
  tree.push_back("HTauTauTree_1l2tau_fake");
  tree.push_back("HTauTauTree_2lss1tau_SR");
  tree.push_back("HTauTauTree_2lss1tau_fake");
  tree.push_back("HTauTauTree_2lss1tau_flip");
  tree.push_back("HTauTauTree_2los1tau_SR");
  tree.push_back("HTauTauTree_2los1tau_fake");
  tree.push_back("HTauTauTree_2l2tau_SR");
  tree.push_back("HTauTauTree_2l2tau_fake");
  tree.push_back("HTauTauTree_3l1tau_SR");
  tree.push_back("HTauTauTree_3l1tau_fake");

  add_BDT(filein,fileout,tree);

}

