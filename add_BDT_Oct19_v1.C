#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <sys/stat.h>
#include <cmath>
#include <typeinfo>

using namespace std;

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

////// Global variables

float lep_conePt;
float lep1_conePt;
float lep2_conePt;
float lep3_conePt;
float lep4_conePt;

float tau_pt;
float tau1_pt;
float tau2_pt;

float mT_lep;
float mT_lep1;
float mT_lep2;

float mT_tau;
float mT_tau1;
float mT_tau2;

float mTauTau;
float mTauTauVis;
float mTauTauVis1;
float mTauTauVis2;

float costS;
float costS_tau;
float cosThetaS_hadTau;

float dr_leps;
float dr_taus;
float dr_lep_tau;
float dr_lep_tau_ss;
float dr_lep2_tau_ss;
float dr_lep_tau_os;
float dr_lep1_tau_os;

float massL;
float massL3;
float massL4;

float charge_lep_tau;
float has_SFOS;

float avg_dr_jet;

float mindr_lep1_jet;
float mindr_lep2_jet;
float mindr_tau_jet;
float mindr_tau1_jet;
float mindr_tau2_jet;
float min_dr_Lep;
float Lep_min_dr_jet;
float max_Lep_eta;

float nJet;
float nBJetLoose;
float nBJetMedium;

float mbb_loose;

float met_LD;

float res_HTT;
float res_HTT_2;

float HadTop_pt;
float HadTop_pt_2;

float btagDisc_b;
float btagDisc_Wj1;
float btagDisc_Wj2;

float qg_Wj1;
float qg_Wj2;

float m_Wj1Wj2_div_m_bWj1Wj2;

float pT_Wj1Wj2;
float dR_Wj1Wj2;
float m_bWj1Wj2;
float pT_bWj1Wj2;

float dR_bW;

float m_bWj1;
float m_bWj2;

float mass_Wj1;
float mass_Wj2;

float pT_Wj2;
float pT_b;

float mass_b;
float massW_SD;

float tau21W;

//////////////////////
////// 0l+2tau ///////
//////////////////////

/*TMVA::Reader* Book_0l2tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");
    
  reader->AddVariable("dr_taus", &dr_taus );
  reader->AddVariable("mTauTauVis", &mTauTauVis );
  reader->AddVariable("mTauTau", &mTauTau );
  reader->AddVariable("cosThetaS_hadTau", &cosThetaS_hadTau );
  reader->AddVariable("tau1_pt", &tau1_pt );
  reader->AddVariable("tau2_pt", &tau2_pt );
  reader->AddVariable("mbb_loose", &mbb_loose );
  reader->AddVariable("avg_dr_jet", &avg_dr_jet );
  reader->AddVariable("mindr_tau1_jet", &mindr_tau1_jet );
  reader->AddVariable("mindr_tau2_jet", &mindr_tau2_jet );
  reader->AddVariable("met_LD", &met_LD );
  reader->AddVariable("mT_tau1", &mT_tau1 );
  reader->AddVariable("mT_tau2", &mT_tau2 );
  reader->AddVariable("nBJetMedium", &nBJetMedium );
  reader->AddVariable("res_HTT", &res_HTT );
  reader->AddVariable("HadTop_pt", &HadTop_pt );
  reader->AddVariable("HadTop_pt_2", &HadTop_pt_2 );
  reader->AddVariable("max_Lep_eta", &max_Lep_eta);

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}*/

//////////////////////
////// 1l+1tau ///////
//////////////////////

/*TMVA::Reader* Book_1l1tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");
    
  reader->AddVariable("lep_conePt", &lep_conePt );
  reader->AddVariable("avg_dr_jet", &avg_dr_jet );
  reader->AddVariable("mT_lep", &mT_lep );
  reader->AddVariable("mT_tau", &mT_tau );
  reader->AddVariable("tau_pt", &tau_pt );
  reader->AddVariable("dr_lep_tau", &dr_lep_tau );
  reader->AddVariable("costS", &costS );
  reader->AddVariable("mTauTauVis", &mTauTauVis );
  reader->AddVariable("mTauTau", &mTauTau );
  reader->AddVariable("res_HTT", &res_HTT );
  reader->AddVariable("res_HTT_2", &res_HTT_2 );
  reader->AddVariable("mbb_loose", &mbb_loose );
  reader->AddVariable("met_LD", &met_LD );
  reader->AddVariable("nJet", &nJet );
  reader->AddVariable("nBJetLoose", &nBJetLoose );
  reader->AddVariable("charge_lep_tau", &charge_lep_tau );
  reader->AddVariable("max_Lep_eta", &max_Lep_eta );
  reader->AddVariable("Lep_min_dr_jet", &Lep_min_dr_jet);

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}*/

//////////////////////
////// 1l+2tau ///////
//////////////////////

TMVA::Reader* Book_1l2tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");
    
  reader->AddVariable("tau1_pt", &tau1_pt );
  reader->AddVariable("tau2_pt", &tau2_pt );
  reader->AddVariable("dr_taus", &dr_taus );
  reader->AddVariable("dr_lep_tau_os", &dr_lep_tau_os );
  reader->AddVariable("dr_lep_tau_ss", &dr_lep_tau_ss );
  reader->AddVariable("Lep_min_dr_jet", &Lep_min_dr_jet );
  reader->AddVariable("mTauTauVis", &mTauTauVis );
  reader->AddVariable("costS_tau", &costS_tau );
  reader->AddVariable("met_LD", &met_LD );
  reader->AddVariable("massL3", &massL3 );
  reader->AddVariable("lep1_conePt", &lep1_conePt );
  reader->AddVariable("mT_lep", &mT_lep );
  reader->AddVariable("res_HTT", &res_HTT );
  reader->AddVariable("HadTop_pt", &HadTop_pt );
  reader->AddVariable("mbb_loose", &mbb_loose );
  reader->AddVariable("avg_dr_jet", &avg_dr_jet );
  reader->AddVariable("max_Lep_eta", &max_Lep_eta );

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}

////////////////////////
////// 2los+1tau ///////
////////////////////////

TMVA::Reader* Book_2los1tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");
    
  reader->AddVariable("lep1_conePt", &lep1_conePt );
  reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
  reader->AddVariable("mT_lep1", &mT_lep1 );
  reader->AddVariable("lep2_conePt", &lep2_conePt );
  reader->AddVariable("mindr_lep2_jet", &mindr_lep2_jet );
  reader->AddVariable("mT_lep2", &mT_lep2 );
  reader->AddVariable("dr_lep2_tau_ss", &dr_lep2_tau_ss );
  reader->AddVariable("dr_lep1_tau_os", &dr_lep1_tau_os );
  reader->AddVariable("dr_leps", &dr_leps );
  reader->AddVariable("mindr_tau_jet", &mindr_tau_jet );
  reader->AddVariable("avg_dr_jet", &avg_dr_jet );
  reader->AddVariable("tau_pt", &tau_pt );
  reader->AddVariable("mTauTauVis", &mTauTauVis );
  reader->AddVariable("mbb_loose", &mbb_loose );
  reader->AddVariable("res_HTT", &res_HTT );
  reader->AddVariable("HadTop_pt", &HadTop_pt );
  reader->AddVariable("met_LD", &met_LD );
  reader->AddVariable("max_Lep_eta", &max_Lep_eta );

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}

//////////////////////
////// 2l+2tau ///////
//////////////////////

TMVA::Reader* Book_2l2tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

  reader->AddVariable("Lep_min_dr_jet", &Lep_min_dr_jet );
  reader->AddVariable("min_dr_Lep", &min_dr_Lep );
  reader->AddVariable("avg_dr_jet", &avg_dr_jet );
  reader->AddVariable("tau1_pt", &tau1_pt );
  reader->AddVariable("tau2_pt", &tau2_pt );
  reader->AddVariable("mTauTauVis", &mTauTauVis );
  reader->AddVariable("cosThetaS_hadTau", &cosThetaS_hadTau );
  reader->AddVariable("mbb_loose", &mbb_loose );
  reader->AddVariable("met_LD", &met_LD ); 

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}

//////////////////////
////// 3l+1tau ///////
//////////////////////

TMVA::Reader* Book_3l1tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

  reader->AddVariable("lep1_conePt", &lep1_conePt );
  reader->AddVariable("lep2_conePt", &lep2_conePt );
  reader->AddVariable("lep3_conePt", &lep3_conePt );
  reader->AddVariable("tau1_pt", &tau1_pt );
  reader->AddVariable("mTauTauVis1", &mTauTauVis1 );
  reader->AddVariable("mTauTauVis2", &mTauTauVis2 );
  reader->AddVariable("massL", &massL );
  reader->AddVariable("met_LD", &met_LD );
  reader->AddVariable("has_SFOS", &has_SFOS );

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}

//////////////////////
////// 4l+0tau ///////
//////////////////////

TMVA::Reader* Book_4l0tau_MVAReader(std::string basePath, std::string weightFileName){

  TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

  reader->AddVariable("lep1_conePt", &lep1_conePt );
  reader->AddVariable("lep2_conePt", &lep2_conePt );
  reader->AddVariable("lep3_conePt", &lep3_conePt );
  reader->AddVariable("lep4_conePt", &lep4_conePt );
  reader->AddVariable("massL4", &massL4 );
  reader->AddVariable("met_LD", &met_LD );
  reader->AddVariable("has_SFOS", &has_SFOS );

  reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

  return reader;

}

///////////////////////////
////// Resolved HTT ///////
///////////////////////////

TMVA::Reader* Book_HTT_Resolved_MVAReader(std::string basePath, std::string weightFileName){

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

//https://github.com/HEP-KBFI/tth-htt/blob/8bd1b484fa968390fd8765562212b197fd1b7183/bin/analyze_1l_1tau.cc#L151-L161
double comp_cosThetaS(TLorentzVector lep1, TLorentzVector lep2)
{
  TLorentzVector lep_lead;
  lep_lead.SetPtEtaPhiM(lep1.Pt(), lep1.Eta(), lep1.Phi(), lep1.M());
  TLorentzVector lep_sublead;
  lep_sublead.SetPtEtaPhiM(lep2.Pt(), lep2.Eta(), lep2.Phi(), lep2.M());
  TLorentzVector dilep = lep_lead + lep_sublead;
  TLorentzVector lep_boost = lep_lead;
  lep_boost.Boost(-dilep.BoostVector());
  return std::fabs(lep_boost.CosTheta());
}

////////////////
////////////////
////////////////

void add_BDT(TString filein, TString fileout, vector<TString> treename, int year){

  TFile* f_new = TFile::Open(fileout);

  /*if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/

  f_new = TFile::Open(fileout,"RECREATE");  

  /*TMVA::Reader* MVA_0l2tau_reader = Book_0l2tau_MVAReader("BDT_weights","0l_2tau_DeepTauLoose_7.xml");
  if(!MVA_0l2tau_reader) std::cout << "No 0l2tau xml file"<<std::endl;*/

  /*TMVA::Reader* MVA_1l1tau_reader = Book_1l1tau_MVAReader("BDT_weights","1l_1tau_DeepTauLoose_6.xml");
  if(!MVA_1l1tau_reader) std::cout << "No 1l1tau xml file"<<std::endl;*/

  TMVA::Reader* MVA_1l2tau_reader = Book_1l2tau_MVAReader("BDT_weights","1l_2tau_DeepTauTight_2.xml");
  if(!MVA_1l2tau_reader) std::cout << "No 1l2tau xml file"<<std::endl;

  TMVA::Reader* MVA_2los1tau_reader = Book_2los1tau_MVAReader("BDT_weights","2los_1tau_DeepTau_2.xml");
  if(!MVA_2los1tau_reader) std::cout << "No 2los1tau xml file"<<std::endl;

  TMVA::Reader* MVA_2l2tau_reader = Book_2l2tau_MVAReader("BDT_weights","2l_2tau.xml");
  if(!MVA_2l2tau_reader) std::cout << "No 2l12au xml file"<<std::endl;
  
  TMVA::Reader* MVA_3l1tau_reader = Book_3l1tau_MVAReader("BDT_weights","3l_1tau_DeepTau.xml");
  if(!MVA_3l1tau_reader) std::cout << "No 3l1tau xml file"<<std::endl;

  TMVA::Reader* MVA_4l0tau_reader = Book_4l0tau_MVAReader("BDT_weights","4l_0tau_3.xml");
  if(!MVA_4l0tau_reader) std::cout << "No 4l0tau xml file"<<std::endl;

  TMVA::Reader* MVA_res_HTT_reader = Book_HTT_Resolved_MVAReader("BDT_weights","HTT_HadTopTagger_2017_nomasscut_nvar17_resolved.xml");
  if(!MVA_res_HTT_reader) std::cout << "No resolved HTT xml file"<<std::endl;

  ////////////////
  ////////////////
  ////////////////

  cout<<" "<<endl;

  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filein);
    
    Long64_t nentries = tree->GetEntries();
    cout<<" "<<endl;
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

    vector<float> *_recolep_px;
    vector<float> *_recolep_py;
    vector<float> *_recolep_pz;
    vector<float> *_recolep_e;
    vector<bool>  *_recolep_isfakeable;
    vector<float> *_recolep_pdg;

    vector<float> *_recolep_sel_px;
    vector<float> *_recolep_sel_py;
    vector<float> *_recolep_sel_pz;
    vector<float> *_recolep_sel_e;
    vector<float> *_recolep_sel_conept;
    vector<float> *_recolep_sel_pt;
    vector<float> *_recolep_sel_eta;
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
    float _ETmissLD;

    tree->SetBranchAddress("EventNumber",&_EventNumber);

    tree->SetBranchAddress("category", &_category);

    tree->SetBranchAddress("n_recolep_sel",&_n_recolep_sel);
    tree->SetBranchAddress("n_recotauh_sel",&_n_recotauh_sel);
    tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
    tree->SetBranchAddress("n_recoPFak8Jet",&_n_recoPFak8Jet);
    tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);
    tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
    tree->SetBranchAddress("n_recoPFLightJet",&_n_recoPFLightJet);

    tree->SetBranchAddress("recolep_px",&_recolep_px);
    tree->SetBranchAddress("recolep_py",&_recolep_py);
    tree->SetBranchAddress("recolep_pz",&_recolep_pz);
    tree->SetBranchAddress("recolep_e",&_recolep_e);
    tree->SetBranchAddress("recolep_isfakeable",&_recolep_isfakeable);
    tree->SetBranchAddress("recolep_pdg",&_recolep_pdg);

    tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
    tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
    tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
    tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
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
    tree->SetBranchAddress("ETmissLD",&_ETmissLD);

    //new branches

    float _BDTscore_0l2tau;
    float _BDTscore_1l1tau;
    float _BDTscore_1l2tau;
    float _BDTscore_2los1tau;
    float _BDTscore_2l2tau;
    float _BDTscore_3l1tau;
    float _BDTscore_4l0tau;

    float _BDTscore_res_HTT;
    float _BDTscore_res_HTT_2;

    TTree* tree_new=tree->GetTree()->CloneTree(0);

    tree_new->Branch("BDTscore_0l2tau",  &_BDTscore_0l2tau);
    tree_new->Branch("BDTscore_1l1tau",  &_BDTscore_1l1tau);
    tree_new->Branch("BDTscore_1l2tau",  &_BDTscore_1l2tau);
    tree_new->Branch("BDTscore_2los1tau",&_BDTscore_2los1tau);
    tree_new->Branch("BDTscore_2l2tau",  &_BDTscore_2l2tau);
    tree_new->Branch("BDTscore_3l1tau",  &_BDTscore_3l1tau);
    tree_new->Branch("BDTscore_4l0tau",  &_BDTscore_4l0tau);

    tree_new->Branch("BDTscore_res_HTT",  &_BDTscore_res_HTT);
    tree_new->Branch("BDTscore_res_HTT_2",&_BDTscore_res_HTT_2);

    float _lep_conePt;
    float _lep1_conePt;
    float _lep2_conePt;
    float _lep3_conePt;
    float _lep4_conePt;

    float _tau_pt;
    float _tau1_pt;
    float _tau2_pt;

    float _mT_lep;
    float _mT_lep1;
    float _mT_lep2;

    float _mT_tau;
    float _mT_tau1;
    float _mT_tau2;

    float _mTauTau;
    float _mTauTauVis;
    float _mTauTauVis1;
    float _mTauTauVis2;

    float _costS;
    float _costS_tau;
    float _cosThetaS_hadTau;

    float _dr_leps;
    float _dr_taus;
    float _dr_lep_tau;
    float _dr_lep_tau_ss;
    float _dr_lep2_tau_ss;
    float _dr_lep_tau_os;
    float _dr_lep1_tau_os;

    float _massL;
    float _massL3;
    float _massL4;

    float _charge_lep_tau;
    float _has_SFOS;

    float _avg_dr_jet;

    float _mindr_lep1_jet;
    float _mindr_lep2_jet;
    float _mindr_tau_jet;
    float _mindr_tau1_jet;
    float _mindr_tau2_jet;
    float _min_dr_Lep;
    float _Lep_min_dr_jet;
    float _max_Lep_eta;

    float _nJet;
    float _nBJetLoose;
    float _nBJetMedium;

    float _mbb_loose;

    float _met_LD;

    float _res_HTT;
    float _res_HTT_2;

    float _res_HTT_output;
    float _res_HTT_2_output;

    float _HadTop_pt;
    float _HadTop_pt_2;

    float _btagDisc_b;
    float _btagDisc_Wj1;
    float _btagDisc_Wj2;

    float _qg_Wj1;
    float _qg_Wj2;

    float _m_Wj1Wj2_div_m_bWj1Wj2;

    float _pT_Wj1Wj2;
    float _dR_Wj1Wj2;
    float _m_bWj1Wj2;
    float _pT_bWj1Wj2;

    float _dR_bW;

    float _m_bWj1;
    float _m_bWj2;

    float _mass_Wj1;
    float _mass_Wj2;

    float _pT_Wj2;
    float _pT_b;

    float _mass_b;
    float _massW_SD;

    float _tau21W;

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0) cout<<"i="<<i<<endl;

      ////////////////

      _EventNumber = 0; 
      _category = 0;

      _n_recolep_sel = 0;
      _n_recotauh_sel = 0;
      _n_recoPFJet = 0;
      _n_recoPFak8Jet = 0;
      _n_recoPFJet_btag_loose = 0;
      _n_recoPFJet_btag_medium = 0;
      _n_recoPFLightJet = 0;

      _recolep_px = 0;
      _recolep_py = 0;
      _recolep_pz = 0;
      _recolep_e = 0;
      _recolep_isfakeable = 0;
      _recolep_pdg = 0;

      _recolep_sel_px = 0;
      _recolep_sel_py = 0;
      _recolep_sel_pz = 0;
      _recolep_sel_e = 0;
      _recolep_sel_conept = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;
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
      _ETmissLD = 0.;

      ////////////////

      _lep_conePt = -999.;
      _lep1_conePt = -999.;
      _lep2_conePt = -999.;
      _lep3_conePt = -999.;
      _lep4_conePt = -999.;

      _tau_pt = -999.;
      _tau1_pt = -999.;
      _tau2_pt = -999.;

      _mT_lep = -999.;
      _mT_lep1 = -999.;
      _mT_lep2 = -999.;

      _mT_tau = -999.;
      _mT_tau1 = -999.;
      _mT_tau2 = -999.;

      _mTauTau = -999.;
      _mTauTauVis = -999.;
      _mTauTauVis1 = -999.;
      _mTauTauVis2 = -999.;

      _costS = -999.;
      _costS_tau = -999.;
      _cosThetaS_hadTau = -999.;

      _dr_leps = -999.;
      _dr_taus = -999.;
      _dr_lep_tau = -999.;
      _dr_lep_tau_ss = -999.;
      _dr_lep2_tau_ss = -999.;
      _dr_lep_tau_os = -999.;
      _dr_lep1_tau_os = -999.;

      _massL = -999.;
      _massL3 = -999.;
      _massL4 = -999.;

      _charge_lep_tau = -999.;
      _has_SFOS = -999.;

      _avg_dr_jet = -999.;

      _mindr_lep1_jet = -999.;
      _mindr_lep2_jet = -999.;
      _mindr_tau_jet = -999.;
      _mindr_tau1_jet = -999.;
      _mindr_tau2_jet = -999.;
      _min_dr_Lep = -999.;
      _Lep_min_dr_jet = -999.;
      _max_Lep_eta = -999.;

      _nJet = -999.;
      _nBJetLoose = -999.;
      _nBJetMedium = -999.;

      _mbb_loose = -999.;

      _met_LD = -999.;

      _res_HTT = -999.;
      _res_HTT_2 = -999.;

      _HadTop_pt = 0.;
      _HadTop_pt_2 = 0.;

      _btagDisc_b = -999.;
      _btagDisc_Wj1 = -999.;
      _btagDisc_Wj2 = -999.;

      _qg_Wj1 = -999.;
      _qg_Wj2 = -999.;

      _m_Wj1Wj2_div_m_bWj1Wj2 = -999.;

      _pT_Wj1Wj2 = -999.;
      _dR_Wj1Wj2 = -999.;
      _m_bWj1Wj2 = -999.;
      _pT_bWj1Wj2 = -999.;

      _dR_bW = -999.;

      _m_bWj1 = -999.;
      _m_bWj2 = -999.;

      _mass_Wj1 = -999.;
      _mass_Wj2 = -999.;

      _pT_Wj2 = -999.;
      _pT_b = -999.;

      _mass_b = -999.;
      _massW_SD = -999.;

      _tau21W = -999.;

      _BDTscore_1l2tau = -999.;
      _BDTscore_2los1tau = -999.;
      _BDTscore_2l2tau = -999.;
      _BDTscore_3l1tau = -999.;

      _BDTscore_res_HTT = 0.;
      _BDTscore_res_HTT_2 = 0.;

      tree->GetEntry(i);

      //////////////////////////////
      //////// Resolved HTT ////////
      //////////////////////////////

      float _res_HTT_output = -1.;
      float _res_HTT_2_output = -1.;

      int i_jet1 = -999.;
      int i_jet2 = -999.;
      int i_jet3 = -999.;

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

            double bdtResult = MVA_res_HTT_reader->EvaluateMVA("BDTG method");

            if ( bdtResult > _res_HTT_output ) {

              _res_HTT_output = bdtResult;
              _res_HTT = 1. / (1. + sqrt((1. - _res_HTT_output) / (1. + _res_HTT_output))); 
              _HadTop_pt = (bjet+Wjet1+Wjet2).Pt();

              i_jet1 = i_bjet;
              i_jet2 = i_Wjet1; 
              i_jet3 = i_Wjet2;

            }
          }
        }
      }

      _BDTscore_res_HTT = _res_HTT;

      for ( int i_bjet = 0; i_bjet<_n_recoPFJet; i_bjet++) {

        if ( i_bjet == i_jet1 || i_bjet == i_jet2 || i_bjet == i_jet3 ) continue;

        TLorentzVector bjet((*_recoPFJet_px)[i_bjet],(*_recoPFJet_py)[i_bjet],(*_recoPFJet_pz)[i_bjet],(*_recoPFJet_e)[i_bjet]);

        for ( int i_Wjet1 = 0; i_Wjet1<_n_recoPFJet; i_Wjet1++) {

          TLorentzVector Wjet1((*_recoPFJet_px)[i_Wjet1],(*_recoPFJet_py)[i_Wjet1],(*_recoPFJet_pz)[i_Wjet1],(*_recoPFJet_e)[i_Wjet1]);

          if ( Wjet1==bjet ) continue;
          if ( i_Wjet1 == i_jet1 || i_Wjet1 == i_jet2 || i_Wjet1 == i_jet3 ) continue;

          for ( int i_Wjet2 = 0; i_Wjet2<_n_recoPFJet; i_Wjet2++) {

            TLorentzVector Wjet2((*_recoPFJet_px)[i_Wjet2],(*_recoPFJet_py)[i_Wjet2],(*_recoPFJet_pz)[i_Wjet2],(*_recoPFJet_e)[i_Wjet2]);

            if ( Wjet2==bjet ) continue;
            if ( Wjet2==Wjet1 ) continue;
            if ( i_Wjet2 == i_jet1 || i_Wjet2 == i_jet2 || i_Wjet2 == i_jet3 ) continue;

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

            double bdtResult_2 = MVA_res_HTT_reader->EvaluateMVA("BDTG method");

            if ( bdtResult_2 > _res_HTT_2_output ) {
              _res_HTT_2_output = bdtResult_2;
              _res_HTT_2 = 1. / (1. + sqrt((1. - _res_HTT_2_output) / (1. + _res_HTT_2_output))); 
              _HadTop_pt_2 = (bjet+Wjet1+Wjet2).Pt();
            }
          }
        }
      }

      _BDTscore_res_HTT_2 = _res_HTT_2;

      //// loose/medium btag jet collection

      vector<bool> _recoPFJet_isLooseDeepJet;
      vector<bool> _recoPFJet_isMediumDeepJet;

      _recoPFJet_isLooseDeepJet.clear();
      _recoPFJet_isMediumDeepJet.clear();

      vector<TLorentzVector> _recoPFJetLoose;
      vector<TLorentzVector> _recoPFJetMedium;

      _recoPFJetLoose.clear();
      _recoPFJetMedium.clear();

      for(int i_jet=0; i_jet<_n_recoPFJet; i_jet++){ 

        TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);

        float DeepJetscore = (*_recoPFJet_DeepJetscore)[i_jet];

        bool isloose = false;
        bool ismedium = false;

        if (year == 2016){
          if(DeepJetscore>0.0614) isloose = true;  
          if(DeepJetscore>0.3093) ismedium = true;
        }

        else if (year == 2017){
          if(DeepJetscore>0.0521) isloose = true;
          if(DeepJetscore>0.3033) ismedium = true;
        }

        else if (year == 2018){
          if(DeepJetscore>0.0494) isloose = true;
          if(DeepJetscore>0.2770) ismedium = true;
        }

        _recoPFJet_isLooseDeepJet.push_back(isloose);
        _recoPFJet_isMediumDeepJet.push_back(ismedium);

        if(isloose) _recoPFJetLoose.push_back(jet);
        if(ismedium) _recoPFJetMedium.push_back(jet);

      }

      ////////////////////////
      //////// 0l2tau ////////
      ////////////////////////
      /*
      if(_category==1010 || _category==1020){

        TLorentzVector tau1((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 
        TLorentzVector tau2((*_recotauh_sel_px)[1],(*_recotauh_sel_py)[1],(*_recotauh_sel_pz)[1],(*_recotauh_sel_e)[1]); 

        _dr_taus = tau1.DeltaR(tau2);
        _mTauTauVis = (tau1+tau2).M();
        _mTauTau = (tau1+tau2).M(); //--->>FIXME: SVFit mass!!!
        _cosThetaS_hadTau = comp_cosThetaS(tau1,tau2);
        _tau1_pt = tau1.Pt();
        _tau2_pt = tau2.Pt();

        _mbb_loose = 0;
        if(_n_recoPFJet_btag_loose>1) 
          _mbb_loose = (_recoPFJetLoose[0]+_recoPFJetLoose[1]).M();  

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

        float minDR_t1_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(tau1);
          if(i_dR < minDR_t1_j) minDR_t1_j = i_dR;
        }
        _mindr_tau1_jet = minDR_t1_j;

        float minDR_t2_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(tau2);
          if(i_dR < minDR_t2_j) minDR_t2_j = i_dR;
        }
        _mindr_tau2_jet = minDR_t2_j;

        _met_LD = _ETmissLD;

        _mT_tau1 = sqrt(2*(tau1.Pt())*_PFMET*(1-cos((tau1.Phi())-_PFMET_phi)));
        _mT_tau2 = sqrt(2*(tau2.Pt())*_PFMET*(1-cos((tau2.Phi())-_PFMET_phi)));

        _nBJetMedium = _n_recoPFJet_btag_medium;

        _max_Lep_eta = std::max(tau1.Eta(),tau2.Eta());

        //////////////////////////////////

        dr_taus = _dr_taus;
        mTauTauVis = _mTauTauVis;
        mTauTau = _mTauTau;
        cosThetaS_hadTau = _cosThetaS_hadTau;
        tau1_pt = _tau1_pt;
        tau2_pt = _tau2_pt;
        mbb_loose = _mbb_loose;
        avg_dr_jet = _avg_dr_jet;
        mindr_tau1_jet = _mindr_tau1_jet;
        mindr_tau2_jet = _mindr_tau2_jet;
        met_LD = _met_LD;
        mT_tau1 = _mT_tau1;
        mT_tau2 = _mT_tau2;
        nBJetMedium = _nBJetMedium;
        res_HTT = _res_HTT;
        HadTop_pt = _HadTop_pt;
        HadTop_pt_2 = _HadTop_pt_2;
        max_Lep_eta = _max_Lep_eta;

        float _BDToutput_0l2tau = MVA_0l2tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_0l2tau =  1. / (1. + sqrt((1. - _BDToutput_0l2tau) / (1. + _BDToutput_0l2tau)));

        cout<<"0l2tau - BDT score: "<<_BDTscore_0l2tau<<endl;

      }
      */

      ////////////////////////
      //////// 1l1tau ////////
      ////////////////////////

      /*
      if(_category==2010 || _category==2020 || _category==2030){

        TLorentzVector lep((*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]); 
        TLorentzVector tau((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 
        
        _lep_conePt = (*_recolep_sel_conept)[0];

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

        _mT_lep = sqrt(2*(lep.Pt())*_PFMET*(1-cos((lep.Phi())-_PFMET_phi)));
        _mT_tau = sqrt(2*(tau.Pt())*_PFMET*(1-cos((tau.Phi())-_PFMET_phi)));
        _tau_pt = tau.Pt();
        _dr_lep_tau = lep.DeltaR(tau);
        _costS = comp_cosThetaS(lep,tau);
        _mTauTauVis = (lep+tau).M();
        _mTauTau = (lep+tau).M(); //--->>FIXME: SVFit mass!!!

        _mbb_loose = 0;
        if(_n_recoPFJet_btag_loose>1) 
          _mbb_loose = (_recoPFJetLoose[0]+_recoPFJetLoose[1]).M();  

        _met_LD = _ETmissLD;
        _nJet = _n_recoPFJet;
        _nBJetLoose = _n_recoPFJet_btag_loose;

        _charge_lep_tau = (*_recolep_sel_charge)[0] + (*_recotauh_sel_charge)[0];

        _max_Lep_eta = std::max(lep.Eta(),tau.Eta());

        float minDR_l_j = 999.;
        float minDR_t_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR_lep = jet.DeltaR(lep);
          float i_dR_tau = jet.DeltaR(tau);
          if(i_dR_lep < minDR_l_j) minDR_l_j = i_dR_lep;
          if(i_dR_tau < minDR_t_j) minDR_t_j = i_dR_tau;
        }
        _Lep_min_dr_jet = std::min(minDR_l_j,minDR_t_j);

        //////////////////////////////////

        lep_conePt = _lep_conePt;
        avg_dr_jet = _avg_dr_jet;
        mT_lep = _mT_lep;
        mT_tau = _mT_tau;
        tau_pt = _tau_pt;
        dr_lep_tau = _dr_lep_tau;
        costS = _costS;
        mTauTauVis = _mTauTauVis;
        mTauTau = _mTauTau;
        res_HTT = _res_HTT;
        res_HTT_2 = _res_HTT_2;
        mbb_loose = _mbb_loose;
        met_LD = _met_LD;
        nJet = _nJet;
        nBJetLoose = _nBJetLoose;
        charge_lep_tau = _charge_lep_tau;
        max_Lep_eta = _max_Lep_eta;
        Lep_min_dr_jet = _Lep_min_dr_jet;

        float _BDToutput_1l1tau = MVA_1l1tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_1l1tau =  1. / (1. + sqrt((1. - _BDToutput_1l1tau) / (1. + _BDToutput_1l1tau)));

        cout<<"1l1tau - BDT score: "<<_BDTscore_1l1tau<<endl;

      }*/
      
      ////////////////////////
      //////// 1l2tau ////////
      ////////////////////////

      //SYNCHED!

      if(_category==2110 || _category==2120){

        TLorentzVector lep( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
        TLorentzVector tau1((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 
        TLorentzVector tau2((*_recotauh_sel_px)[1],(*_recotauh_sel_py)[1],(*_recotauh_sel_pz)[1],(*_recotauh_sel_e)[1]); 

        TLorentzVector lep_cone;
        lep_cone.SetPtEtaPhiE((*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0], (*_recolep_sel_phi)[0], (*_recolep_sel_e)[0]);

        _tau1_pt = tau1.Pt();
        _tau2_pt = tau2.Pt();

        _dr_taus = tau1.DeltaR(tau2);

        if( (*_recolep_sel_charge)[0] * (*_recotauh_sel_charge)[0] < 0 ){
          _dr_lep_tau_os = lep.DeltaR(tau1);
          _dr_lep_tau_ss = lep.DeltaR(tau2);

        }
        else if( (*_recolep_sel_charge)[0] * (*_recotauh_sel_charge)[0] > 0 ){
          _dr_lep_tau_os = lep.DeltaR(tau2);
          _dr_lep_tau_ss = lep.DeltaR(tau1);
        }

        float minDR_l_j = 999.;
        float minDR_t1_j = 999.;
        float minDR_t2_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR_lep = jet.DeltaR(lep);
          float i_dR_tau1 = jet.DeltaR(tau1);
          float i_dR_tau2 = jet.DeltaR(tau2);
          if(i_dR_lep < minDR_l_j)   minDR_l_j = i_dR_lep;
          if(i_dR_tau1 < minDR_t1_j) minDR_t1_j = i_dR_tau1;
          if(i_dR_tau2 < minDR_t2_j) minDR_t2_j = i_dR_tau2;
        }
        float _Lep_min_dr_jet_1 = std::min(minDR_t1_j,minDR_t2_j);
        _Lep_min_dr_jet = std::min(_Lep_min_dr_jet_1,minDR_l_j);

        _mTauTauVis = (tau1+tau2).M();

        _costS_tau = comp_cosThetaS(tau1,tau2);

        _met_LD = _ETmissLD;

        TLorentzVector lep_massless;
        lep_massless.SetPtEtaPhiM((*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0], (*_recolep_sel_phi)[0], 0.);

        TLorentzVector sumL3 = lep_massless + tau1 + tau2;
        float met_px = _PFMET*std::cos(_PFMET_phi);
        float met_py = _PFMET*std::sin(_PFMET_phi);

        _massL3 = sqrt(2*(sumL3.Pt())*_PFMET*(1-cos((sumL3.Phi())-_PFMET_phi)));
        float _massL3_v2 =  sqrt( (sumL3.Et()+_PFMET)*(sumL3.Et()+_PFMET) - ( (sumL3.Px()+met_px)*(sumL3.Px()+met_px) + (sumL3.Py()+met_py)*(sumL3.Py()+met_py) ) );

        _lep1_conePt = (*_recolep_sel_conept)[0];

        _mT_lep = sqrt(2*(lep_cone.Pt())*_PFMET*(1-cos((lep_cone.Phi())-_PFMET_phi)));
        
        _mbb_loose = 0;
        if(_n_recoPFJet_btag_loose>1) 
          _mbb_loose = (_recoPFJetLoose[0]+_recoPFJetLoose[1]).M();  

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

        float _max_Lep_eta_1 = max(abs(tau1.Eta()),abs(tau2.Eta()));
        _max_Lep_eta = (_max_Lep_eta_1<abs(lep.Eta())) ? abs(lep.Eta()):_max_Lep_eta_1;

        ///////////////////////////////////

        tau1_pt = _tau1_pt;
        tau2_pt = _tau2_pt;
        dr_taus = _dr_taus;
        dr_lep_tau_os = _dr_lep_tau_os;
        dr_lep_tau_ss = _dr_lep_tau_ss;
        Lep_min_dr_jet = _Lep_min_dr_jet;
        mTauTauVis = _mTauTauVis;
        costS_tau = _costS_tau;
        met_LD = _met_LD;
        massL3 = _massL3_v2;
        lep1_conePt = _lep1_conePt;
        mT_lep = _mT_lep;
        res_HTT = _res_HTT;
        HadTop_pt = _HadTop_pt;
        mbb_loose = _mbb_loose;
        avg_dr_jet = _avg_dr_jet;
        max_Lep_eta = _max_Lep_eta;

        float _BDToutput_1l2tau = MVA_1l2tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_1l2tau =  1. / (1. + sqrt((1. - _BDToutput_1l2tau) / (1. + _BDToutput_1l2tau)));

      }

      //////////////////////////
      //////// 2los1tau ////////
      //////////////////////////

      // SYNCHED!

      if(_category==3210 || _category==3220){

        TLorentzVector lep1( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
        TLorentzVector lep2( (*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
        TLorentzVector tau((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 

        _lep1_conePt = (*_recolep_sel_conept)[0];
        _lep2_conePt = (*_recolep_sel_conept)[1];

        float minDR_l1_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(lep1);
          if(i_dR < minDR_l1_j) minDR_l1_j = i_dR;
        }
        _mindr_lep1_jet = minDR_l1_j;

        TLorentzVector lep_cone_1;
        lep_cone_1.SetPtEtaPhiE((*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0], (*_recolep_sel_phi)[0], (*_recolep_sel_e)[0]);

        TLorentzVector lep_cone_2;
        lep_cone_2.SetPtEtaPhiE((*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1], (*_recolep_sel_phi)[1], (*_recolep_sel_e)[1]);

        _mT_lep1 = sqrt(2*(lep_cone_1.Pt())*_PFMET*(1-cos((lep_cone_1.Phi())-_PFMET_phi)));
        _mT_lep2 = sqrt(2*(lep_cone_2.Pt())*_PFMET*(1-cos((lep_cone_2.Phi())-_PFMET_phi)));
        
        float minDR_l2_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(lep2);
          if(i_dR < minDR_l2_j) minDR_l2_j = i_dR;
        }
        _mindr_lep2_jet = minDR_l2_j;

        if( (*_recolep_sel_charge)[0] * (*_recotauh_sel_charge)[0] < 0 ){
          _dr_lep1_tau_os = lep1.DeltaR(tau);
          _dr_lep2_tau_ss = lep2.DeltaR(tau);
        }
        if( (*_recolep_sel_charge)[0] * (*_recotauh_sel_charge)[0] > 0 ){
          _dr_lep1_tau_os = lep2.DeltaR(tau);
          _dr_lep2_tau_ss = lep1.DeltaR(tau);
        }

        _dr_leps = lep1.DeltaR(lep2);

        float _mindR_jettau = 999.;
        for(int i_jet=0;i_jet<_n_recoPFJet;i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet], (*_recoPFJet_py)[i_jet], (*_recoPFJet_pz)[i_jet], (*_recoPFJet_e)[i_jet]);
          float _dR_jettau = jet.DeltaR(tau);
          if(_dR_jettau < _mindR_jettau){
              _mindR_jettau = _dR_jettau;
          }
        }
        _mindr_tau_jet = _mindR_jettau;

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

        _tau_pt = tau.Pt();

        TLorentzVector lep_reco_1;
        lep_reco_1.SetPtEtaPhiE((*_recolep_sel_pt)[0], (*_recolep_sel_eta)[0], (*_recolep_sel_phi)[0], (*_recolep_sel_e)[0]);
        TLorentzVector lep_reco_2;
        lep_reco_2.SetPtEtaPhiE((*_recolep_sel_pt)[1], (*_recolep_sel_eta)[1], (*_recolep_sel_phi)[1], (*_recolep_sel_e)[1]);
        if( (*_recolep_sel_charge)[0] * (*_recotauh_sel_charge)[0] < 0 )
          _mTauTauVis = (lep_reco_1+tau).M();
        else if( (*_recolep_sel_charge)[1] * (*_recotauh_sel_charge)[0] < 0 )
          _mTauTauVis = (lep_reco_2+tau).M();

        _mbb_loose = 0;
        if(_n_recoPFJet_btag_loose>1) 
          _mbb_loose = (_recoPFJetLoose[0]+_recoPFJetLoose[1]).M(); 

        _met_LD = _ETmissLD; 

        float _max_Lep_eta_1 = max(abs(lep1.Eta()),abs(lep2.Eta()));
        _max_Lep_eta = (_max_Lep_eta_1<abs(tau.Eta())) ? abs(tau.Eta()):_max_Lep_eta_1;

        ///////////////////////////////////

        lep1_conePt = _lep1_conePt;
        mindr_lep1_jet = _mindr_lep1_jet;
        mT_lep1 = _mT_lep1; 
        lep2_conePt = _lep2_conePt;
        mindr_lep2_jet = _mindr_lep2_jet;
        mT_lep2 = _mT_lep2; 
        dr_lep2_tau_ss = _dr_lep2_tau_ss;
        dr_lep1_tau_os = _dr_lep1_tau_os;
        dr_leps = _dr_leps;
        mindr_tau_jet = _mindr_tau_jet;
        avg_dr_jet = _avg_dr_jet;
        tau_pt = _tau_pt;
        mTauTauVis = _mTauTauVis; 
        mbb_loose = _mbb_loose;
        res_HTT = _res_HTT;
        HadTop_pt = _HadTop_pt;
        met_LD = _met_LD;
        max_Lep_eta = _max_Lep_eta;

        float _BDToutput_2los1tau = MVA_2los1tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_2los1tau =  1. / (1. + sqrt((1. - _BDToutput_2los1tau) / (1. + _BDToutput_2los1tau)));

      }

      ////////////////////////
      //////// 2l2tau ////////
      ////////////////////////

      // SYNCHED!

      if(_category==3310 || _category==3320){

        TLorentzVector lep1( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
        TLorentzVector lep2( (*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
        TLorentzVector tau1((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 
        TLorentzVector tau2((*_recotauh_sel_px)[1],(*_recotauh_sel_py)[1],(*_recotauh_sel_pz)[1],(*_recotauh_sel_e)[1]); 

        float minDR_l1_j = 999.;
        float minDR_l2_j = 999.;
        float minDR_t1_j = 999.;
        float minDR_t2_j = 999.;
        for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR_lep1 = jet.DeltaR(lep1);
          float i_dR_lep2 = jet.DeltaR(lep2);
          float i_dR_tau1 = jet.DeltaR(tau1);
          float i_dR_tau2 = jet.DeltaR(tau2);
          if(i_dR_lep1 < minDR_l1_j) minDR_l1_j = i_dR_lep1;
          if(i_dR_lep2 < minDR_l2_j) minDR_l2_j = i_dR_lep2;
          if(i_dR_tau1 < minDR_t1_j) minDR_t1_j = i_dR_tau1;
          if(i_dR_tau2 < minDR_t2_j) minDR_t2_j = i_dR_tau2;
        }
        float _Lep_min_dr_jet_1 = std::min(minDR_t1_j,minDR_t2_j);
        float _Lep_min_dr_jet_2 = std::min(_Lep_min_dr_jet_1,minDR_l1_j);
        float _Lep_min_dr_jet = std::min(_Lep_min_dr_jet_2,minDR_l2_j);

        vector<TLorentzVector> Leps;
        Leps.clear();
        Leps.push_back(lep1);
        Leps.push_back(lep2);
        Leps.push_back(tau1);
        Leps.push_back(tau2);

        float minDR_leps = 999.;
        for (unsigned int i_Lep1=0; i_Lep1<Leps.size(); i_Lep1++){
          TLorentzVector Lep1 = Leps[i_Lep1];
          for (unsigned int i_Lep2=i_Lep1+1; i_Lep2<Leps.size(); i_Lep2++){
            TLorentzVector Lep2 = Leps[i_Lep2];
            float dR = Lep1.DeltaR(Lep2);
            if(dR < minDR_leps) minDR_leps = dR;
          }
        }
        _min_dr_Lep = minDR_leps;

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

        _tau1_pt = tau1.Pt();
        _tau2_pt = tau2.Pt();

        _mTauTauVis = (tau1+tau2).M();

        _cosThetaS_hadTau = comp_cosThetaS(tau1,tau2);

        _mbb_loose = 0;
        if(_n_recoPFJet_btag_loose>1) 
          _mbb_loose = (_recoPFJetLoose[0]+_recoPFJetLoose[1]).M();  

        _met_LD = _ETmissLD;

        ///////////////////////////////////

        Lep_min_dr_jet = _Lep_min_dr_jet;
        min_dr_Lep = _min_dr_Lep;
        avg_dr_jet = _avg_dr_jet;
        tau1_pt = _tau1_pt;
        tau2_pt = _tau2_pt;
        mTauTauVis = _mTauTauVis;
        cosThetaS_hadTau = _cosThetaS_hadTau;
        mbb_loose = _mbb_loose;
        met_LD = _met_LD;

        float _BDToutput_2l2tau = MVA_2l2tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_2l2tau =  1. / (1. + sqrt((1. - _BDToutput_2l2tau) / (1. + _BDToutput_2l2tau)));

        //cout<<"Lep_min_dr_jet "<<Lep_min_dr_jet<<endl;
        //cout<<"min_dr_Lep "<<min_dr_Lep<<endl;
        //cout<<"avg_dr_jet "<<avg_dr_jet<<endl;
        //cout<<"tau1_pt "<<tau1_pt<<endl;
        //cout<<"tau2_pt "<<tau2_pt<<endl;
        //cout<<"mTauTauVis "<<mTauTauVis<<endl;
        //cout<<"cosThetaS_hadTau "<<cosThetaS_hadTau<<endl;
        //cout<<"mbb_loose "<<mbb_loose<<endl;
        //cout<<"met_LD "<<met_LD<<endl;
        //cout<<"--_BDTscore_2l2tau "<<_BDTscore_2l2tau<<endl;

      } 

      ////////////////////////
      //////// 3l1tau ////////
      ////////////////////////

      // SYNCHED!

      if(_category==4110 || _category==4120){

        TLorentzVector lep1( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
        TLorentzVector lep2( (*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
        TLorentzVector lep3( (*_recolep_sel_px)[2],(*_recolep_sel_py)[2],(*_recolep_sel_pz)[2],(*_recolep_sel_e)[2]);
        TLorentzVector tau((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 

        _lep1_conePt = (*_recolep_sel_conept)[0];
        _lep2_conePt = (*_recolep_sel_conept)[1];
        _lep3_conePt = (*_recolep_sel_conept)[2];

        _tau1_pt = tau.Pt();

        vector<TLorentzVector> os_leps;
        os_leps.clear();
        for(int i_lep = 0; i_lep<3; i_lep++){
          TLorentzVector oslep( (*_recolep_sel_px)[i_lep],(*_recolep_sel_py)[i_lep],(*_recolep_sel_pz)[i_lep],(*_recolep_sel_e)[i_lep] );
          if( (*_recolep_sel_charge)[i_lep]*(*_recotauh_sel_charge)[0] > 0) continue;
          os_leps.push_back(oslep);
        }

        _mTauTauVis1 = (tau+os_leps[0]).M(); 
        _mTauTauVis2 = (tau+os_leps[1]).M(); 

        float min_mll = 999.;
        for(unsigned int i_lep1=0; i_lep1<(*_recolep_px).size(); i_lep1++){
          if((*_recolep_isfakeable)[i_lep1]==0) continue;
          TLorentzVector lep1( (*_recolep_px)[i_lep1],(*_recolep_py)[i_lep1],(*_recolep_pz)[i_lep1],(*_recolep_e)[i_lep1]);
          for(unsigned int i_lep2=i_lep1+1; i_lep2<(*_recolep_px).size(); i_lep2++){
            if((*_recolep_isfakeable)[i_lep2]==0) continue;
            TLorentzVector lep2( (*_recolep_px)[i_lep2],(*_recolep_py)[i_lep2],(*_recolep_pz)[i_lep2],(*_recolep_e)[i_lep2]);
            float m_ll = (lep1 + lep2).M();
            if(m_ll<min_mll) min_mll = m_ll;
          }

        }
        _massL = min_mll;

        _met_LD = _ETmissLD;

        bool SFOS_pair = false;
        for(unsigned int i_lep1=0; i_lep1<(*_recolep_pdg).size(); i_lep1++){
          for(unsigned int i_lep2=0; i_lep2<(*_recolep_pdg).size(); i_lep2++){
            if((*_recolep_pdg)[i_lep1]==-(*_recolep_pdg)[i_lep2] && ((*_recolep_isfakeable)[i_lep1] && (*_recolep_isfakeable)[i_lep2])) 
              SFOS_pair=true;
          }
        }
        _has_SFOS = SFOS_pair;

        ///////////////////////////////////

        lep1_conePt = _lep1_conePt;
        lep2_conePt = _lep2_conePt;
        lep3_conePt = _lep3_conePt;
        tau1_pt = _tau1_pt;
        mTauTauVis1 = _mTauTauVis1;
        mTauTauVis2 = _mTauTauVis2;
        massL = _massL;
        met_LD = _met_LD;
        has_SFOS = _has_SFOS;

        float _BDToutput_3l1tau = MVA_3l1tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_3l1tau =  1. / (1. + sqrt((1. - _BDToutput_3l1tau) / (1. + _BDToutput_3l1tau)));

        //cout<<"lep1_conePt "<<lep1_conePt<<endl;
        //cout<<"lep2_conePt "<<lep2_conePt<<endl;
        //cout<<"lep3_conePt "<<lep3_conePt<<endl;
        //cout<<"tau1_pt "<<tau1_pt<<endl;
        //cout<<"mTauTauVis1 "<<mTauTauVis1<<endl;
        //cout<<"mTauTauVis2 "<<mTauTauVis2<<endl;
        //cout<<"massL "<<massL<<endl;
        //cout<<"met_LD "<<met_LD<<endl;
        //cout<<"has_SFOS "<<has_SFOS<<endl;
        //cout<<"--score "<<_BDTscore_3l1tau<<endl;

      }

      ////////////////////////
      //////// 4l0tau ////////
      ////////////////////////

      /*
      if(_category==5010 || _category==5020){

        TLorentzVector lep1( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
        TLorentzVector lep2( (*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
        TLorentzVector lep3( (*_recolep_sel_px)[2],(*_recolep_sel_py)[2],(*_recolep_sel_pz)[2],(*_recolep_sel_e)[2]);
        TLorentzVector lep4( (*_recolep_sel_px)[3],(*_recolep_sel_py)[3],(*_recolep_sel_pz)[3],(*_recolep_sel_e)[3]);

        _lep1_conePt = (*_recolep_sel_conept)[0];
        _lep2_conePt = (*_recolep_sel_conept)[1];
        _lep3_conePt = (*_recolep_sel_conept)[2];   
        _lep4_conePt = (*_recolep_sel_conept)[3]; 

        TLorentzVector sumL4 = lep1 + lep2 + lep3 + lep4;
        _massL4 = sqrt(2*(sumL4.Pt())*_PFMET*(1-cos((sumL4.Phi())-_PFMET_phi)));   

        met_LD = _met_LD;

        bool SFOS_pair = false;
        for(unsigned int i_lep1=0; i_lep1<(*_recolep_pdg).size(); i_lep1++){
          for(unsigned int i_lep2=0; i_lep2<(*_recolep_pdg).size(); i_lep2++){
            if((*_recolep_pdg)[i_lep1]==-(*_recolep_pdg)[i_lep2] && ((*_recolep_isfakeable)[i_lep1] && (*_recolep_isfakeable)[i_lep2])) 
              SFOS_pair=true;
          }
        }
        _has_SFOS = SFOS_pair;

        ///////////////////////////////////  
        
        lep1_conePt = _lep1_conePt;
        lep2_conePt = _lep2_conePt;
        lep3_conePt = _lep3_conePt;
        lep4_conePt = _lep4_conePt;
        massL4 = _massL4;
        met_LD = _met_LD;
        has_SFOS = _has_SFOS;

        float _BDToutput_4l0tau = MVA_4l0tau_reader->EvaluateMVA("BDTG method");

        _BDTscore_4l0tau =  1. / (1. + sqrt((1. - _BDToutput_4l0tau) / (1. + _BDToutput_4l0tau)));

        cout<<"4l0tau - BDT score: "<<_BDTscore_4l0tau<<endl;

      }
      */

      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////

      tree_new->Fill();

    }

    f_new->cd();
    tree_new->Write();

  }

  f_new->Close();
  return;

}


void loadfiles(TString mysample, int myyear, TString mytype){

  TString myyearstring = std::to_string(myyear);

  TString myfilein="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/"+myyearstring+"/nominal/"+mytype+"/ntuple_"+mysample+".root";
  TString myfileout="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_BDT/"+myyearstring+"/nominal/"+mytype+"/ntuple_"+mysample+"_BDT.root";

  vector<TString> mytree;

  /*
  mytree.push_back("HTauTauTree_2tau_SR");
  mytree.push_back("HTauTauTree_2tau_fake");
  mytree.push_back("HTauTauTree_1l1tau_SR");
  mytree.push_back("HTauTauTree_1l1tau_fake");
  mytree.push_back("HTauTauTree_1l1tau_flip");*/
  mytree.push_back("HTauTauTree_1l2tau_SR");
  mytree.push_back("HTauTauTree_1l2tau_fake");
  /*mytree.push_back("HTauTauTree_2lss_SR");
  mytree.push_back("HTauTauTree_2lss_fake");
  mytree.push_back("HTauTauTree_2lss_flip");*/
  //mytree.push_back("HTauTauTree_2lss1tau_SR");
  //mytree.push_back("HTauTauTree_2lss1tau_fake");
  //mytree.push_back("HTauTauTree_2lss1tau_flip");
  mytree.push_back("HTauTauTree_2los1tau_SR");
  mytree.push_back("HTauTauTree_2los1tau_fake");
  mytree.push_back("HTauTauTree_2l2tau_SR");
  mytree.push_back("HTauTauTree_2l2tau_fake");
  /*mytree.push_back("HTauTauTree_3l_SR");
  mytree.push_back("HTauTauTree_3l_fake");*/
  mytree.push_back("HTauTauTree_3l1tau_SR");
  mytree.push_back("HTauTauTree_3l1tau_fake");
  /*mytree.push_back("HTauTauTree_4l_SR");
  mytree.push_back("HTauTauTree_4l_fake");
  mytree.push_back("HTauTauTree_ttW_CR_SR");
  mytree.push_back("HTauTauTree_ttW_CR_fake");
  mytree.push_back("HTauTauTree_ttW_CR_flip");
  mytree.push_back("HTauTauTree_ttZ_CR_SR");
  mytree.push_back("HTauTauTree_ttZ_CR_fake");
  mytree.push_back("HTauTauTree_WZ_CR_SR");
  mytree.push_back("HTauTauTree_WZ_CR_fake");
  mytree.push_back("HTauTauTree_ZZ_CR_SR");
  mytree.push_back("HTauTauTree_ZZ_CR_fake");
  mytree.push_back("HTauTauTree_3l_CR_SR");
  mytree.push_back("HTauTauTree_3l_CR_fake");
  mytree.push_back("HTauTauTree_4l_CR_SR");
  mytree.push_back("HTauTauTree_4l_CR_fake");*/

  add_BDT(myfilein,myfileout,mytree,myyear);

}

void test(){

  /*loadfiles("Oct19v1_MC_2016_ttHJetToNonbb",2016,"ttH");
  loadfiles("Oct19v1_MC_2016_ttH_ctcvcp",2016,"ttH");
  loadfiles("Oct19v1_MC_2016_THQ_ctcvcp",2016,"ttH");
  loadfiles("Oct19v1_MC_2016_THW_ctcvcp",2016,"ttH");

  loadfiles("Oct19v1_MC_2017_ttHJetToNonbb",2017,"ttH");
  loadfiles("Oct19v1_MC_2017_THQ_ctcvcp",2017,"ttH");
  loadfiles("Oct19v3_MC_2017_THW_ctcvcp",2017,"ttH");
  loadfiles("Oct19v1_MC_2017_TTH_ctcvcp",2017,"ttH");

  loadfiles("Oct19v2_MC_2018_ttHJetToNonbb",2018,"ttH");
  loadfiles("Oct19v2_MC_2018_TTH_ctcvcp",2018,"ttH");
  loadfiles("Oct19v1_MC_2018_THQ_ctcvcp",2018,"ttH");
  loadfiles("Oct19v1_MC_2018_THW_ctcvcp",2018,"ttH");

  loadfiles("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2",2016,"ttV");
  loadfiles("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",2016,"ttV");
  loadfiles("Oct19v1_MC_2016_TTZToLL_M-1to10",2016,"ttV");
  loadfiles("Oct19v1_MC_2016_TTWJetsToLNu",2016,"ttV");
  loadfiles("Oct19v1_MC_2016_TTWW",2016,"ttV");

  loadfiles("Oct19v1_MC_2017_TTZToLLNuNu_M-10",2017,"ttV");
  loadfiles("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",2017,"ttV");
  loadfiles("Oct19v1_MC_2017_TTZToLL_M-1to10",2017,"ttV");
  loadfiles("Oct19v1_MC_2017_TTWJetsToLNu",2017,"ttV");
  loadfiles("Oct19v1_MC_2017_TTWJetsToLNu_PS",2017,"ttV");
  loadfiles("Oct19v1_MC_2017_TTWW",2017,"ttV");

  loadfiles("Oct19v1_MC_2018_TTZToLLNuNu_M-10",2018,"ttV");
  loadfiles("Oct19v1_MC_2018_TTZToLL_M-1to10",2018,"ttV");
  loadfiles("Oct19v1_MC_2018_TTWJetsToLNu",2018,"ttV");
  loadfiles("Oct19v1_MC_2018_TTWW_ext1",2018,"ttV");
  loadfiles("Oct19v1_MC_2018_TTWW_ext2",2018,"ttV");

  loadfiles("Oct19v1_MC_2016_WWW",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WWZ",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WZZ",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_ZZZ",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WZG",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WGToLNuG_ext1",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WGToLNuG_ext2",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WGToLNuG_ext3",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_ZGTo2LG",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_TGJets_leptonDecays",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_TTGJets",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_TTGJets_ext1",2016,"Rares");
  loadfiles("Oct19v2_MC_2016_tZq_ll",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_tZq_ll_PS",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_WpWpJJ",2016,"Rares");
  loadfiles("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering",2016,"Rares");
  loadfiles("Oct19v1_MC_2016_TTTT",2016,"Rares");

  loadfiles("Oct19v1_MC_2017_WWW",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_WWZ",2017,"Rares");
  loadfiles("Oct19v2_MC_2017_WZZ",2017,"Rares");
  loadfiles("Oct19v2_MC_2017_ZZZ",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_WZG",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_WGToLNuG",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_ZGToLLG",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_TGJets",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_TTGJets",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_TTGJets_ext1",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_tZq_ll",2017,"Rares");
  loadfiles("Oct19v2_MC_2017_WpWpJJ",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_TTTT",2017,"Rares");
  loadfiles("Oct19v1_MC_2017_TTTT_PS",2017,"Rares");

  loadfiles("Oct19v2_MC_2018_WWW",2018,"Rares");
  loadfiles("Oct19v2_MC_2018_WWZ",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_WZZ",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_ZZZ",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_WZG",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_WGToLNuG",2018,"Rares");
  loadfiles("Oct19v2_MC_2018_ZGToLLG",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_TGJets",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_TTGJets",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_tZq_ll",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_WpWpJJ",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering",2018,"Rares");
  loadfiles("Oct19v1_MC_2018_TTTT",2018,"Rares");

  loadfiles("Oct19v1_MC_2016_DYJetsToLL_M-10to50",2016,"EWK");
  loadfiles("Oct19v1_MC_2016_DYJetsToLL_M-50",2016,"EWK");
  loadfiles("Oct19v1_MC_2016_WJetsToLNu_ext2",2016,"EWK");
  loadfiles("Oct19v1_MC_2016_WJetsToLNu",2016,"EWK");
  loadfiles("Oct19v1_MC_2016_WWTo2L2Nu",2016,"EWK");
  loadfiles("Oct19v1_MC_2016_WZTo3LNu",2016,"EWK");
  loadfiles("Oct19v1_MC_2016_ZZTo4L",2016,"EWK");
    
  loadfiles("Oct19v1_MC_2017_DYJetsToLL_M-10to50",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_DYJetsToLL_M-50",2017,"EWK");
  loadfiles("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",2017,"EWK");
  loadfiles("Oct19v2_MC_2017_WJetsToLNu",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_WJetsToLNu_ext1",2017,"EWK");
  loadfiles("Oct19v2_MC_2017_WWTo2L2Nu",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_WWTo2L2Nu_ext1",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_WZTo3LNu",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_ZZTo4L",2017,"EWK");
  loadfiles("Oct19v1_MC_2017_ZZTo4L_ext1",2017,"EWK");
  loadfiles("Oct19v2_MC_2017_ZZTo4L_ext2",2017,"EWK");
    
  loadfiles("Oct19v3_MC_2018_DYJetsToLL_M-10to50",2018,"EWK");
  loadfiles("Oct19v2_MC_2018_DYJetsToLL_M-50",2018,"EWK");
  loadfiles("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",2018,"EWK");
  loadfiles("Oct19v2_MC_2018_WJetsToLNu",2018,"EWK");
  loadfiles("Oct19v3_MC_2018_WWTo2L2Nu",2018,"EWK");
  loadfiles("Oct19v1_MC_2018_WZTo3LNu",2018,"EWK");
  loadfiles("Oct19v2_MC_2018_WZTo3LNu_ext1",2018,"EWK");
  loadfiles("Oct19v2_MC_2018_ZZTo4L",2018,"EWK");
  loadfiles("Oct19v4_MC_2018_ZZTo4L_ext2",2018,"EWK");

  loadfiles("Oct19v1_MC_2016_ST_s-channel",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_s-channel_PS",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_t-channel_top",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_t-channel_antitop",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_t-channel_antitop_PS",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_tW_top",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_tW_antitop",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_ST_tWll",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_TTJets_DiLept_ext1",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_TTJets_DiLept",2016,"ttbar");
  loadfiles("Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_TTJets_SingleLeptFromT",2016,"ttbar");
  loadfiles("Oct19v1_MC_2016_TTJets_SingleLeptFromTbar",2016,"ttbar");
  loadfiles("Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1",2016,"ttbar");

  loadfiles("Oct19v1_MC_2017_ST_s-channel",2017,"ttbar");
  loadfiles("Oct19v2_MC_2017_ST_s-channel_PS",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_ST_t-channel_top",2017,"ttbar");
  loadfiles("Oct19v2_MC_2017_ST_t-channel_top_PS",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_ST_t-channel_antitop",2017,"ttbar");
  loadfiles("Oct19v2_MC_2017_ST_t-channel_antitop_PS",2017,"ttbar");
  loadfiles("Oct19v3_MC_2017_ST_tW_top",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_ST_tW_top_PS",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_ST_tW_antitop",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_ST_tW_antitop_PS",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_ST_tWll",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_TTJets_DiLept",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_TTJets_SingleLeptFromT",2017,"ttbar");
  loadfiles("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar",2017,"ttbar");

  loadfiles("Oct19v1_MC_2018_ST_s-channel",2018,"ttbar");
  loadfiles("Oct19v2_MC_2018_ST_t-channel_top",2018,"ttbar");
  loadfiles("Oct19v3_MC_2018_ST_t-channel_antitop",2018,"ttbar");
  loadfiles("Oct19v3_MC_2018_ST_tW_top",2018,"ttbar");
  loadfiles("Oct19v1_MC_2018_ST_tW_antitop",2018,"ttbar");
  loadfiles("Oct19v1_MC_2018_ST_tWll",2018,"ttbar");
  loadfiles("Oct19v1_MC_2018_TTJets_DiLept",2018,"ttbar");
  loadfiles("Oct19v1_MC_2018_TTJets_SingleLeptFromT",2018,"ttbar");
  loadfiles("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar",2018,"ttbar");

  loadfiles("Oct19v1_MC_2016_GluGluHToTauTau",2016,"ggH");
  loadfiles("Oct19v1_MC_2016_GluGluHToZZTo4L",2016,"ggH");
  loadfiles("Oct19v1_MC_2016_GluGluHToWWToLNuQQ",2016,"ggH");
  loadfiles("Oct19v1_MC_2016_GluGluHToWWTo2L2Nu",2016,"ggH");
  loadfiles("Oct19v1_MC_2016_GluGluHToMuMu",2016,"ggH");
  loadfiles("Oct19v1_MC_2016_GluGluHToBB",2016,"ggH");
  loadfiles("Oct19v6_MC_2016_GluGluHToBB_ext1",2016,"ggH");
  loadfiles("Oct19v1_MC_2016_GluGluHToGG",2016,"ggH");

  loadfiles("Oct19v1_MC_2017_GluGluHToTauTau",2017,"ggH");
  loadfiles("Oct19v3_MC_2017_GluGluHToTauTau_ext1",2017,"ggH");
  loadfiles("Oct19v1_MC_2017_GluGluHToZZTo4L_ext1",2017,"ggH");
  loadfiles("Oct19v2_MC_2017_GluGluHToZZTo4L_ext3",2017,"ggH");
  loadfiles("Oct19v1_MC_2017_GluGluHToZZTo4L_ext4",2017,"ggH");
  loadfiles("Oct19v2_MC_2017_GluGluHToZZTo2L2Q",2017,"ggH");
  loadfiles("Oct19v1_MC_2017_GluGluHToWWToLNuQQ",2017,"ggH");
  loadfiles("Oct19v1_MC_2017_GluGluHToWWTo2L2Nu",2017,"ggH");
  loadfiles("Oct19v3_MC_2017_GluGluHToMuMu",2017,"ggH");
  loadfiles("Oct19v1_MC_2017_GluGluHToMuMu_ext1",2017,"ggH");
  loadfiles("Oct19v2_MC_2017_GluGluHToBB",2017,"ggH");
  loadfiles("Oct19v3_MC_2017_GluGluHToGG",2017,"ggH");

  loadfiles("Oct19v2_MC_2018_GluGluHToTauTau",2018,"ggH");
  loadfiles("Oct19v1_MC_2018_GluGluHToZZTo4L",2018,"ggH");
  loadfiles("Oct19v2_MC_2018_GluGluHToZZTo2L2Q",2018,"ggH");
  loadfiles("Oct19v1_MC_2018_GluGluHToWWToLNuQQ",2018,"ggH");
  loadfiles("Oct19v2_MC_2018_GluGluHToWWTo2L2Nu",2018,"ggH");
  loadfiles("Oct19v1_MC_2018_GluGluHToMuMu",2018,"ggH");
  loadfiles("Oct19v2_MC_2018_GluGluHToMuMu_ext1",2018,"ggH");
  loadfiles("Oct19v1_MC_2018_GluGluHToBB",2018,"ggH");
  loadfiles("Oct19v1_MC_2018_GluGluHToGG",2018,"ggH");

  loadfiles("Oct19v2_MC_2016_VBFHToTauTau",2016,"VBF");
  loadfiles("Oct19v2_MC_2016_VBF_HToZZTo4L",2016,"VBF");
  loadfiles("Oct19v1_MC_2016_VBFHToWWToLNuQQ",2016,"VBF");
  loadfiles("Oct19v1_MC_2016_VBFHToWWTo2L2Nu",2016,"VBF");
  loadfiles("Oct19v1_MC_2016_VBFHToMuMu",2016,"VBF");
  loadfiles("Oct19v3_MC_2016_VBFHToBB",2016,"VBF");
  loadfiles("Oct19v1_MC_2016_VBFHToBB_ext1",2016,"VBF");
  loadfiles("Oct19v1_MC_2016_VBFHToGG_ext1",2016,"VBF");
  loadfiles("Oct19v1_MC_2016_VBFHToGG_ext2",2016,"VBF");

  loadfiles("Oct19v1_MC_2017_VBFHToTauTau",2017,"VBF");
  loadfiles("Oct19v2_MC_2017_VBF_HToZZTo4L_ext2",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBF_HToZZTo4L_ext1",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBF_HToZZTo4L",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBFHToWWToLNuQQ",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBFHToWWTo2L2Nu",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBFHToMuMu",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBFHToBB",2017,"VBF");
  loadfiles("Oct19v1_MC_2017_VBFHToGG",2017,"VBF");
  loadfiles("Oct19v2_MC_2017_VBFHToGG_PS",2017,"VBF");

  loadfiles("Oct19v1_MC_2018_VBFHToTauTau",2018,"VBF");
  loadfiles("Oct19v2_MC_2018_VBF_HToZZTo4L",2018,"VBF");
  loadfiles("Oct19v2_MC_2018_VBFHToWWToLNuQQ",2018,"VBF");
  loadfiles("Oct19v1_MC_2018_VBFHToWWTo2L2Nu",2018,"VBF");
  loadfiles("Oct19v1_MC_2018_VBFHToMuMu",2018,"VBF");
  loadfiles("Oct19v2_MC_2018_VBFHToBB",2018,"VBF");
  loadfiles("Oct19v2_MC_2018_VBFHToGG",2018,"VBF");

  loadfiles("Oct19v1_MC_2016_VHToNonbb",2016,"VH");
  loadfiles("Oct19v1_MC_2016_ZH_HToBB_ZToLL",2016,"VH");
  loadfiles("Oct19v1_MC_2016_ZHToTauTau",2016,"VH");

  loadfiles("Oct19v1_MC_2017_VHToNonbb",2017,"VH");
  loadfiles("Oct19v1_MC_2017_ZH_HToBB_ZToLL",2017,"VH");
  loadfiles("Oct19v1_MC_2017_ZHToTauTau",2017,"VH");

  loadfiles("Oct19v2_MC_2018_VHToNonbb",2018,"VH");
  loadfiles("Oct19v1_MC_2018_ZH_HToBB_ZToLL",2018,"VH");
  loadfiles("Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1",2018,"VH");
  loadfiles("Oct19v2_MC_2018_ZHToTauTau",2018,"VH");

  loadfiles("Oct19v1_MC_2016_TTWH",2016,"ttVH");
  loadfiles("Oct19v2_MC_2016_TTZH",2016,"ttVH");

  loadfiles("Oct19v4_MC_2017_TTWH",2017,"ttVH");
  loadfiles("Oct19v1_MC_2017_TTZH",2017,"ttVH");

  loadfiles("Oct19v1_MC_2018_TTWH",2018,"ttVH");
  loadfiles("Oct19v2_MC_2018_TTZH",2018,"ttVH");

  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box",2016,"HH");
  loadfiles("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_1",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3",2016,"HH");
  loadfiles("Oct19v4_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_4",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_5",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_7",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8",2016,"HH");
  loadfiles("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_11",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo2B2Tau_node_9",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12",2016,"HH");
  loadfiles("Oct19v3_MC_2016_GluGluToHHTo2B2Tau_node_13",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_8",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_10",2016,"HH");
  loadfiles("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_11",2016,"HH");
  loadfiles("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12",2016,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_7",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9",2017,"HH");
  loadfiles("Oct19v4_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo4Tau_node_7",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM",2017,"HH");*/
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_3",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_7",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_12",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_SM",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo4V_node_2",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_3",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_4",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_5",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_6",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_7",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_8",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_9",2017,"HH");
  loadfiles("Oct19v1_MC_2017_GluGluToHHTo4V_node_10",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo4V_node_11",2017,"HH");
  loadfiles("Oct19v2_MC_2017_GluGluToHHTo4V_node_12",2017,"HH");
  loadfiles("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM",2018,"HH");
  loadfiles("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_2",2018,"HH");
  loadfiles("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_3",2018,"HH");
  loadfiles("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_4",2018,"HH");
  loadfiles("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_5",2018,"HH");
  loadfiles("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_6",2018,"HH");
  loadfiles("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_7",2018,"HH");
  loadfiles("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_8",2018,"HH");
  loadfiles("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_9",2018,"HH");
  loadfiles("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_10",2018,"HH");
  loadfiles("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_11",2018,"HH");
  loadfiles("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_12",2018,"HH");

}

