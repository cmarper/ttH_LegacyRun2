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

float mindrLep1Jet;


///////////////////////////
////// Resolved HTT ///////
///////////////////////////

/*TMVA::Reader* Book_HTT_Resolved_MVAReader(std::string basePath, std::string weightFileName){

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

}*/

//https://github.com/HEP-KBFI/tth-htt/blob/8bd1b484fa968390fd8765562212b197fd1b7183/bin/analyze_1l_1tau.cc#L151-L161
/*double comp_cosThetaS(TLorentzVector lep1, TLorentzVector lep2)
{
  TLorentzVector lep_lead;
  lep_lead.SetPtEtaPhiM(lep1.Pt(), lep1.Eta(), lep1.Phi(), lep1.M());
  TLorentzVector lep_sublead;
  lep_sublead.SetPtEtaPhiM(lep2.Pt(), lep2.Eta(), lep2.Phi(), lep2.M());
  TLorentzVector dilep = lep_lead + lep_sublead;
  TLorentzVector lep_boost = lep_lead;
  lep_boost.Boost(-dilep.BoostVector());
  return std::fabs(lep_boost.CosTheta());
}*/

////////////////
////////////////
////////////////

void add_BDT(TString filein, TString fileout, vector<TString> treename){

  TFile* f_new = TFile::Open(fileout);

  /*if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/

  f_new = TFile::Open(fileout,"RECREATE");  

  //TMVA::Reader* MVA_res_HTT_reader = Book_HTT_Resolved_MVAReader("BDT_weights","HTT_HadTopTagger_2017_nomasscut_nvar17_resolved.xml");
  //if(!MVA_res_HTT_reader) std::cout << "No resolved HTT xml file"<<std::endl;

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

    float _BDTscore_res_HTT;
    float _BDTscore_res_HTT_2;

    TTree* tree_new=tree->GetTree()->CloneTree(0);

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

    float _mindrLep1Jet;

    tree_new->Branch("avg_dr_jet",&_avg_dr_jet);
    tree_new->Branch("massL3",&_massL3);
    tree_new->Branch("mindrLep1Jet",&_mindrLep1Jet);
    //tree_new->Branch("mTauTauVis",&_mTauTauVis);
    //tree_new->Branch("mT_lep2",&_mT_lep2);

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0) cout<<"i="<<i<<endl;

      ////////////////

      _mindrLep1Jet = 0;

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

      tree->GetEntry(i);


      //////////////////////////
      //////// 2lss1tau ////////
      //////////////////////////

      /*TLorentzVector lep1( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
      TLorentzVector lep2( (*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
      TLorentzVector tau((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]); 

      TLorentzVector lep_cone_1;
      lep_cone_1.SetPtEtaPhiE((*_recolep_sel_conept)[0], (*_recolep_sel_eta)[0], (*_recolep_sel_phi)[0], (*_recolep_sel_e)[0]);

      TLorentzVector lep_cone_2;
      lep_cone_2.SetPtEtaPhiE((*_recolep_sel_conept)[1], (*_recolep_sel_eta)[1], (*_recolep_sel_phi)[1], (*_recolep_sel_e)[1]);

      _lep1_conePt = (*_recolep_sel_conept)[0];
      _lep2_conePt = (*_recolep_sel_conept)[1];

      _mT_lep1 = sqrt(2*(lep_cone_1.Pt())*_PFMET*(1-cos((lep_cone_1.Phi())-_PFMET_phi)));
      _mT_lep2 = sqrt(2*(lep_cone_2.Pt())*_PFMET*(1-cos((lep_cone_2.Phi())-_PFMET_phi)));

      _mTauTauVis = (lep1+tau).M();

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

      ///////////////////////////////////

      mT_lep2 = _mT_lep2; 
      avg_dr_jet = _avg_dr_jet;
      mTauTauVis = _mTauTauVis; */

      ////////////////////////
      //////// 3l0tau ////////
      ////////////////////////  

      TLorentzVector lep1( (*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
      TLorentzVector lep2( (*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
      TLorentzVector lep3( (*_recolep_sel_px)[2],(*_recolep_sel_py)[2],(*_recolep_sel_pz)[2],(*_recolep_sel_e)[2]);

      TLorentzVector lepsyst = lep1+lep2+lep3;

      _massL3 = sqrt(2*(lepsyst.Pt())*_PFMET*(1-cos((lepsyst.Phi())-_PFMET_phi)));

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

      float minDR_l1_j = 999.;
      for(int i_jet = 0; i_jet<_n_recoPFJet; i_jet++){
          TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
          float i_dR = jet.DeltaR(lep1);
          if(i_dR < minDR_l1_j) minDR_l1_j = i_dR;
      }
      _mindrLep1Jet = minDR_l1_j;

      ///////////////////////////////////

      tree_new->Fill();

    }

    f_new->cd();
    tree_new->Write();

  }

  f_new->Close();
  return;

}


void loadfiles(TString mysample, TString mytype){

  TString myfilein="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/"+mytype+"/ntuple_"+mysample+".root";
  TString myfileout="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/2018/nominal/"+mytype+"/ntuple_"+mysample+"_DNN_vbles_3l.root";

  vector<TString> mytree;

  //mytree.push_back("HTauTauTree_2lss1tau_SR");
  mytree.push_back("HTauTauTree_3l_SR");

  add_BDT(myfilein,myfileout,mytree);

}

void test(){

  //loadfiles("Oct19v1_MC_2016_ttHJetToNonbb","ttH");
  //loadfiles("Oct19v1_MC_2016_THQ_ctcvcp","ttH");
  //loadfiles("Oct19v1_MC_2016_TTWJetsToLNu","ttV");
  //loadfiles("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2","ttV");
  //loadfiles("Oct19v1_MC_2016_TTJets_DiLept","ttbar");

  //loadfiles("Oct19v1_MC_2017_ttHJetToNonbb","ttH");
  //loadfiles("Oct19v1_MC_2017_THQ_ctcvcp","ttH");
  //loadfiles("Oct19v1_MC_2017_TTWJetsToLNu","ttV");
  //loadfiles("Oct19v1_MC_2017_TTZToLLNuNu_M-10","ttV");
  //loadfiles("Oct19v1_MC_2017_TTJets_DiLept","ttbar");

  loadfiles("Oct19v2_MC_2018_ttHJetToNonbb","ttH");
  loadfiles("Oct19v1_MC_2018_THQ_ctcvcp","ttH");
  loadfiles("Oct19v1_MC_2018_TTWJetsToLNu","ttV");
  loadfiles("Oct19v1_MC_2018_TTZToLLNuNu_M-10","ttV");
  loadfiles("Oct19v1_MC_2018_TTJets_DiLept","ttbar");

}

