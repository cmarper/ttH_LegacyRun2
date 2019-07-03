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

#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif

using namespace std;



void create_syncNtuple_objectbased(int year=2016){

  TString dir_in="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/";
  TString dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_syncformat/";
 
  if(year==2016) dir_in+="2016/";
  else if(year==2017) dir_in+="2017/";
  else if(year==2018) dir_in+="2018/";

  if(year==2016) dir_out+="objects/2016/";
  else if(year==2017) dir_out+="objects/2017/";
  else if(year==2018) dir_out+="objects/2018/";

  TString file;
  if(year==2016) file="sync_ntuple_objects_syncformat_ttHNonbb_2016_v17.root";
  else if(year==2017) file="sync_ntuple_objects_syncformat_ttHNonbb_2017_v10.root";
  else if(year==2018) file="sync_ntuple_objects_syncformat_ttHNonbb_2018_v9.root";

  vector<TString> list;
  if(year==2016) list.push_back(dir_in+"sync_ntuple_converted_ttHNonbb_2016_v23.root");
  else if(year==2017) list.push_back(dir_in+"sync_ntuple_converted_ttHNonbb_2017_v16.root");
  else if(year==2018) list.push_back(dir_in+"sync_ntuple_converted_ttHNonbb_2018_v15.root");

  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  Long64_t nentries = tree->GetEntries();
  cout<<"nentries "<<nentries<<endl;

  TFile* f_new = TFile::Open(dir_out+file);
  /*if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/
  
  f_new = TFile::Open(dir_out+file,"RECREATE");

  TTree* tree_new=new TTree("syncTree","syncTree");
  

  //New branches
  ULong64_t _nEvent;
  int _ls;
  int _run;

  int _n_presel_mu;
  int _n_fakeablesel_mu;
  int _n_mvasel_mu;

  int _n_presel_ele;
  int _n_fakeablesel_ele;
  int _n_mvasel_ele;

  int _n_presel_tau;

  int _n_presel_jet;
  int _n_presel_jetFwd;
  int _n_presel_jetAK8;

  float _mu1_pt;
  float _mu1_conept;
  float _mu1_eta;
  float _mu1_phi;
  float _mu1_E;
  int   _mu1_charge;
  float _mu1_miniRelIso;
  float _mu1_miniIsoCharged;
  float _mu1_miniIsoNeutral;
  float _mu1_PFRelIso04; 
  int   _mu1_jetNDauChargedMVASel;
  float _mu1_jetPtRel;
  float _mu1_jetPtRatio;
  float _mu1_jetCSV;
  float _mu1_jetDeepCSV; //NEW
  float _mu1_jetDeepJet; //NEW
  float _mu1_sip3D;
  float _mu1_dxy;
  float _mu1_dxyAbs;
  float _mu1_dz;
  float _mu1_segmentCompatibility;
  float _mu1_leptonMVA;
  bool  _mu1_mediumID;
  float _mu1_dpt_div_pt;
  bool  _mu1_isfakeablesel;
  bool  _mu1_ismvasel;
  int   _mu1_isGenMatched;

  float _mu2_pt;
  float _mu2_conept;
  float _mu2_eta;
  float _mu2_phi;
  float _mu2_E;
  int   _mu2_charge;
  float _mu2_miniRelIso;
  float _mu2_miniIsoCharged;
  float _mu2_miniIsoNeutral;
  float _mu2_PFRelIso04; 
  int   _mu2_jetNDauChargedMVASel;
  float _mu2_jetPtRel;
  float _mu2_jetPtRatio;
  float _mu2_jetCSV;
  float _mu2_jetDeepCSV; //NEW
  float _mu2_jetDeepJet; //NEW
  float _mu2_sip3D;
  float _mu2_dxy;
  float _mu2_dxyAbs;
  float _mu2_dz;
  float _mu2_segmentCompatibility;
  float _mu2_leptonMVA;
  bool  _mu2_mediumID;
  float _mu2_dpt_div_pt;
  bool  _mu2_isfakeablesel;
  bool  _mu2_ismvasel;
  int _mu2_isGenMatched;

  float _ele1_pt;
  float _ele1_conept;
  float _ele1_eta;
  float _ele1_phi;
  float _ele1_E;
  int   _ele1_charge;
  float _ele1_miniRelIso;
  float _ele1_miniIsoCharged;
  float _ele1_miniIsoNeutral;
  float _ele1_PFRelIso04; 
  int   _ele1_jetNDauChargedMVASel;
  float _ele1_jetPtRel;
  float _ele1_jetPtRatio;
  float _ele1_jetCSV;
  float _ele1_jetDeepCSV;
  float _ele1_jetDeepJet;
  float _ele1_sip3D;
  float _ele1_dxy; 
  float _ele1_dxyAbs;
  float _ele1_dz;
  float _ele1_ntMVAeleID;
  float _ele1_leptonMVA;
  bool  _ele1_isChargeConsistent;
  bool  _ele1_passesConversionVeto;
  int   _ele1_nMissingHits;
  float _ele1_sigmaEtaEta; 
  float _ele1_HoE; 
  float _ele1_deltaEta; 
  float _ele1_deltaPhi; 
  float _ele1_OoEminusOoP; 
  bool  _ele1_isfakeablesel;
  bool  _ele1_ismvasel;
  int _ele1_isGenMatched;
 
  float _ele2_pt;
  float _ele2_conept;
  float _ele2_eta;
  float _ele2_phi;
  float _ele2_E;
  int   _ele2_charge;
  float _ele2_miniRelIso;
  float _ele2_miniIsoCharged;
  float _ele2_miniIsoNeutral;
  float _ele2_PFRelIso04; 
  int   _ele2_jetNDauChargedMVASel;
  float _ele2_jetPtRel;
  float _ele2_jetPtRatio;
  float _ele2_jetCSV;
  float _ele2_jetDeepCSV;
  float _ele2_jetDeepJet;
  float _ele2_sip3D;
  float _ele2_dxy; 
  float _ele2_dxyAbs;
  float _ele2_dz;
  float _ele2_ntMVAeleID;
  float _ele2_leptonMVA;
  bool  _ele2_isChargeConsistent;
  bool  _ele2_passesConversionVeto;
  int   _ele2_nMissingHits;
  float _ele2_sigmaEtaEta; 
  float _ele2_HoE; 
  float _ele2_deltaEta; 
  float _ele2_deltaPhi; 
  float _ele2_OoEminusOoP; 
  bool  _ele2_isfakeablesel;
  bool  _ele2_ismvasel;
  int _ele2_isGenMatched;

  float _tau1_pt;
  float _tau1_eta;
  float _tau1_phi;
  float _tau1_E;
  int   _tau1_charge;
  float _tau1_dxy;
  float _tau1_dz;
  int   _tau1_decayModeFindingOldDMs;
  int   _tau1_decayModeFindingNewDMs;
  float _tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  float _tau1_rawMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byVVVLooseDeepTau2017v2VSjet;
  int   _tau1_byVVLooseDeepTau2017v2VSjet;
  int   _tau1_byVLooseDeepTau2017v2VSjet;
  int   _tau1_byLooseDeepTau2017v2VSjet;
  int   _tau1_byMediumDeepTau2017v2VSjet;
  int   _tau1_byTightDeepTau2017v2VSjet;
  int   _tau1_byVTightDeepTau2017v2VSjet;
  int   _tau1_byVVTightDeepTau2017v2VSjet;
  float _tau1_byDeepTau2017v2VSjetraw;
  int   _tau1_againstMuonLoose3;
  int   _tau1_againstMuonTight3;
  int   _tau1_againstElectronVLooseMVA6;
  int   _tau1_againstElectronLooseMVA6;
  int   _tau1_againstElectronMediumMVA6;
  int   _tau1_againstElectronTightMVA6;
  int   _tau1_againstElectronVTightMVA6;
  int   _tau1_isGenMatched;

  float _tau2_pt;
  float _tau2_eta;
  float _tau2_phi;
  float _tau2_E;
  int   _tau2_charge;
  float _tau2_dxy;
  float _tau2_dz;
  int   _tau2_decayModeFindingOldDMs;
  int   _tau2_decayModeFindingNewDMs;
  float _tau2_byCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  float _tau2_rawMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byVVVLooseDeepTau2017v2VSjet;
  int   _tau2_byVVLooseDeepTau2017v2VSjet;
  int   _tau2_byVLooseDeepTau2017v2VSjet;
  int   _tau2_byLooseDeepTau2017v2VSjet;
  int   _tau2_byMediumDeepTau2017v2VSjet;
  int   _tau2_byTightDeepTau2017v2VSjet;
  int   _tau2_byVTightDeepTau2017v2VSjet;
  int   _tau2_byVVTightDeepTau2017v2VSjet;
  float _tau2_byDeepTau2017v2VSjetraw;
  int   _tau2_againstMuonLoose3;
  int   _tau2_againstMuonTight3;
  int   _tau2_againstElectronVLooseMVA6;
  int   _tau2_againstElectronLooseMVA6;
  int   _tau2_againstElectronMediumMVA6;
  int   _tau2_againstElectronTightMVA6;
  int   _tau2_againstElectronVTightMVA6;
  int   _tau2_isGenMatched;

  float _jet1_pt;
  float _jet1_eta;
  float _jet1_phi;
  float _jet1_E;
  float _jet1_CSV;
  float _jet1_DeepCSV;
  float _jet1_DeepJet;
  float _jet1_QGdiscr;
	
  float _jet2_pt;
  float _jet2_eta;
  float _jet2_phi;
  float _jet2_E;
  float _jet2_CSV;
  float _jet2_DeepCSV;
  float _jet2_DeepJet;
  float _jet2_QGdiscr;
	
  float _jet3_pt;
  float _jet3_eta;
  float _jet3_phi;
  float _jet3_E;
  float _jet3_CSV;
  float _jet3_DeepCSV;
  float _jet3_DeepJet;
  float _jet3_QGdiscr;

  float _jet4_pt;
  float _jet4_eta;
  float _jet4_phi;
  float _jet4_E;
  float _jet4_CSV;
  float _jet4_DeepCSV;
  float _jet4_DeepJet;
  float _jet4_QGdiscr;

  float _jetFwd1_pt;
  float _jetFwd1_eta;
  float _jetFwd1_phi;
  float _jetFwd1_E;
  
  float _jetFwd2_pt;
  float _jetFwd2_eta;
  float _jetFwd2_phi;
  float _jetFwd2_E;
  
  float _jetFwd3_pt;
  float _jetFwd3_eta;
  float _jetFwd3_phi;
  float _jetFwd3_E;

  float _jetFwd4_pt;
  float _jetFwd4_eta;
  float _jetFwd4_phi;
  float _jetFwd4_E;

  float _jetAK8_1_pt;
  float _jetAK8_1_eta;
  float _jetAK8_1_phi;
  float _jetAK8_1_E;
  float _jetAK8_1_subjet_1_pt;
  float _jetAK8_1_subjet_1_eta;
  float _jetAK8_1_subjet_1_phi;
  float _jetAK8_1_subjet_1_E;
  float _jetAK8_1_subjet_2_pt;
  float _jetAK8_1_subjet_2_eta;
  float _jetAK8_1_subjet_2_phi;
  float _jetAK8_1_subjet_2_E;
  float _jetAK8_1_SDmass;
  float _jetAK8_1_tau1;
  float _jetAK8_1_tau2;

  float _jetAK8_2_pt;
  float _jetAK8_2_eta;
  float _jetAK8_2_phi;
  float _jetAK8_2_E;
  float _jetAK8_2_subjet_1_pt;
  float _jetAK8_2_subjet_1_eta;
  float _jetAK8_2_subjet_1_phi;
  float _jetAK8_2_subjet_1_E;
  float _jetAK8_2_subjet_2_pt;
  float _jetAK8_2_subjet_2_eta;
  float _jetAK8_2_subjet_2_phi;
  float _jetAK8_2_subjet_2_E;
  float _jetAK8_2_SDmass;
  float _jetAK8_2_tau1;
  float _jetAK8_2_tau2;

  float _PFMET;
  float _PFMETphi;
  float _MHT;
  float _metLD;

  
  tree_new->Branch("nEvent",        &_nEvent,         "nEvent/L");
  tree_new->Branch("ls",            &_ls,             "ls/I");
  tree_new->Branch("run",           &_run,            "run/I");

  tree_new->Branch("n_presel_mu",      &_n_presel_mu,      "n_presel_mu/I");
  tree_new->Branch("n_fakeablesel_mu", &_n_fakeablesel_mu, "n_fakeablesel_mu/I");
  tree_new->Branch("n_mvasel_mu",      &_n_mvasel_mu,      "n_mvasel_mu/I");

  tree_new->Branch("n_presel_ele",      &_n_presel_ele,      "n_presel_ele/I");
  tree_new->Branch("n_fakeablesel_ele", &_n_fakeablesel_ele, "n_fakeablesel_ele/I");
  tree_new->Branch("n_mvasel_ele",      &_n_mvasel_ele,      "n_mvasel_ele/I");

  tree_new->Branch("n_presel_tau",  &_n_presel_tau,   "n_presel_tau/I");
  tree_new->Branch("n_presel_jet",  &_n_presel_jet,   "n_presel_jet/I");
  tree_new->Branch("n_presel_jetFwd",  &_n_presel_jetFwd,   "n_presel_jetFwd/I");
  tree_new->Branch("n_presel_jetAK8",  &_n_presel_jetAK8,   "n_presel_jetAK8/I");

  tree_new->Branch("mu1_pt",        &_mu1_pt,         "mu1_pt/F");
  tree_new->Branch("mu1_conept",    &_mu1_conept,     "mu1_conept/F");
  tree_new->Branch("mu1_eta",       &_mu1_eta,        "mu1_eta/F");
  tree_new->Branch("mu1_phi",       &_mu1_phi,        "mu1_phi/F");
  tree_new->Branch("mu1_E",         &_mu1_E,          "mu1_E/F");
  tree_new->Branch("mu1_charge",    &_mu1_charge,     "mu1_charge/I");
  tree_new->Branch("mu1_miniRelIso",          &_mu1_miniRelIso,          "mu1_miniRelIso/F");
  tree_new->Branch("mu1_miniIsoCharged",      &_mu1_miniIsoCharged,      "mu1_miniIsoCharged/F");
  tree_new->Branch("mu1_miniIsoNeutral",      &_mu1_miniIsoNeutral,      "mu1_miniIsoNeutral/F");
  tree_new->Branch("mu1_PFRelIso04",    &_mu1_PFRelIso04,    "mu1_PFRelIso04/F");
  tree_new->Branch("mu1_jetNDauChargedMVASel",&_mu1_jetNDauChargedMVASel,"mu1_jetNDauChargedMVASel/I");
  tree_new->Branch("mu1_jetPtRel",  &_mu1_jetPtRel,   "mu1_jetPtRel/F");
  tree_new->Branch("mu1_jetPtRatio",&_mu1_jetPtRatio, "mu1_jetPtRatio/F");
  tree_new->Branch("mu1_jetCSV",    &_mu1_jetCSV,     "mu1_jetCSV/F");
  tree_new->Branch("mu1_jetDeepCSV",    &_mu1_jetDeepCSV,     "mu1_jetDeepCSV/F");
  tree_new->Branch("mu1_jetDeepJet",    &_mu1_jetDeepJet,     "mu1_jetDeepJet/F");
  tree_new->Branch("mu1_sip3D",     &_mu1_sip3D,      "mu1_sip3D/F");
  tree_new->Branch("mu1_dxy",       &_mu1_dxy,        "mu1_dxy/F");
  tree_new->Branch("mu1_dxyAbs",       &_mu1_dxyAbs,        "mu1_dxyAbs/F");
  tree_new->Branch("mu1_dz",        &_mu1_dz,         "mu1_dz/F");
  tree_new->Branch("mu1_segmentCompatibility",&_mu1_segmentCompatibility,"mu1_segmentCompatibility/F");
  tree_new->Branch("mu1_leptonMVA",     &_mu1_leptonMVA,     "mu1_leptonMVA/F");
  tree_new->Branch("mu1_mediumID",      &_mu1_mediumID,      "mu1_mediumID/O");
  tree_new->Branch("mu1_dpt_div_pt",    &_mu1_dpt_div_pt,    "mu1_dpt_div_pt/F");
  tree_new->Branch("mu1_isfakeablesel", &_mu1_isfakeablesel, "mu1_isfakeablesel/O");
  tree_new->Branch("mu1_ismvasel",      &_mu1_ismvasel,      "mu1_ismvasel/O");
  tree_new->Branch("mu1_isGenMatched",      &_mu1_isGenMatched,      "mu1_isGenMatched/I");

  tree_new->Branch("mu2_pt",        &_mu2_pt,         "mu2_pt/F");
  tree_new->Branch("mu2_conept",    &_mu2_conept,     "mu2_conept/F");
  tree_new->Branch("mu2_eta",       &_mu2_eta,        "mu2_eta/F");
  tree_new->Branch("mu2_phi",       &_mu2_phi,        "mu2_phi/F");
  tree_new->Branch("mu2_E",         &_mu2_E,          "mu2_E/F");
  tree_new->Branch("mu2_charge",    &_mu2_charge,     "mu2_charge/I");
  tree_new->Branch("mu2_miniRelIso",          &_mu2_miniRelIso,          "mu2_miniRelIso/F");
  tree_new->Branch("mu2_miniIsoCharged",      &_mu2_miniIsoCharged,      "mu2_miniIsoCharged/F");
  tree_new->Branch("mu2_miniIsoNeutral",      &_mu2_miniIsoNeutral,      "mu2_miniIsoNeutral/F");
  tree_new->Branch("mu2_PFRelIso04",    &_mu2_PFRelIso04,    "mu2_PFRelIso04/F");
  tree_new->Branch("mu2_jetNDauChargedMVASel",&_mu2_jetNDauChargedMVASel,"mu2_jetNDauChargedMVASel/I");
  tree_new->Branch("mu2_jetPtRel",  &_mu2_jetPtRel,   "mu2_jetPtRel/F");
  tree_new->Branch("mu2_jetPtRatio",&_mu2_jetPtRatio, "mu2_jetPtRatio/F");
  tree_new->Branch("mu2_jetCSV",    &_mu2_jetCSV,     "mu2_jetCSV/F");
  tree_new->Branch("mu2_jetDeepCSV",    &_mu2_jetDeepCSV,     "mu2_jetDeepCSV/F");
  tree_new->Branch("mu2_jetDeepJet",    &_mu2_jetDeepJet,     "mu2_jetDeepJet/F");
  tree_new->Branch("mu2_sip3D",     &_mu2_sip3D,      "mu2_sip3D/F");
  tree_new->Branch("mu2_dxy",       &_mu2_dxy,        "mu2_dxy/F");
  tree_new->Branch("mu2_dxyAbs",       &_mu2_dxyAbs,        "mu2_dxyAbs/F");
  tree_new->Branch("mu2_dz",        &_mu2_dz,         "mu2_dz/F");
  tree_new->Branch("mu2_segmentCompatibility",&_mu2_segmentCompatibility,"mu2_segmentCompatibility/F");
  tree_new->Branch("mu2_leptonMVA",     &_mu2_leptonMVA,     "mu2_leptonMVA/F");
  tree_new->Branch("mu2_mediumID",      &_mu2_mediumID,      "mu2_mediumID/O");
  tree_new->Branch("mu2_dpt_div_pt",    &_mu2_dpt_div_pt,    "mu2_dpt_div_pt/F");
  tree_new->Branch("mu2_isfakeablesel", &_mu2_isfakeablesel, "mu2_isfakeablesel/O");
  tree_new->Branch("mu2_ismvasel",      &_mu2_ismvasel,      "mu2_ismvasel/O");
  tree_new->Branch("mu2_isGenMatched",      &_mu2_isGenMatched,      "mu2_isGenMatched/I");

  tree_new->Branch("ele1_pt",        &_ele1_pt,         "ele1_pt/F");
  tree_new->Branch("ele1_conept",    &_ele1_conept,     "ele1_conept/F");
  tree_new->Branch("ele1_eta",       &_ele1_eta,        "ele1_eta/F");
  tree_new->Branch("ele1_phi",       &_ele1_phi,        "ele1_phi/F");
  tree_new->Branch("ele1_E",         &_ele1_E,          "ele1_E/F");
  tree_new->Branch("ele1_charge",    &_ele1_charge,     "ele1_charge/I");
  tree_new->Branch("ele1_miniRelIso",          &_ele1_miniRelIso,          "ele1_miniRelIso/F");
  tree_new->Branch("ele1_miniIsoCharged",      &_ele1_miniIsoCharged,      "ele1_miniIsoCharged/F");
  tree_new->Branch("ele1_miniIsoNeutral",      &_ele1_miniIsoNeutral,      "ele1_miniIsoNeutral/F");
  tree_new->Branch("ele1_PFRelIso04",    &_ele1_PFRelIso04,    "ele1_PFRelIso04/F");
  tree_new->Branch("ele1_jetNDauChargedMVASel",&_ele1_jetNDauChargedMVASel,"ele1_jetNDauChargedMVASel/I");
  tree_new->Branch("ele1_jetPtRel",  &_ele1_jetPtRel,   "ele1_jetPtRel/F");
  tree_new->Branch("ele1_jetPtRatio",&_ele1_jetPtRatio, "ele1_jetPtRatio/F");
  tree_new->Branch("ele1_jetCSV",    &_ele1_jetCSV,     "ele1_jetCSV/F");
  tree_new->Branch("ele1_jetDeepCSV",    &_ele1_jetDeepCSV,     "ele1_jetDeepCSV/F");
  tree_new->Branch("ele1_jetDeepJet",    &_ele1_jetDeepJet,     "ele1_jetDeepJet/F");
  tree_new->Branch("ele1_sip3D",     &_ele1_sip3D,      "ele1_sip3D/F");
  tree_new->Branch("ele1_dxyAbs",       &_ele1_dxyAbs,        "ele1_dxyAbs/F");
  tree_new->Branch("ele1_dxy",       &_ele1_dxy,        "ele1_dxy/F");
  tree_new->Branch("ele1_dz",        &_ele1_dz,         "ele1_dz/F");
  tree_new->Branch("ele1_ntMVAeleID",&_ele1_ntMVAeleID, "ele1_ntMVAeleID/F");
  tree_new->Branch("ele1_leptonMVA", &_ele1_leptonMVA,  "ele1_leptonMVA/F");
  tree_new->Branch("ele1_isChargeConsistent",   &_ele1_isChargeConsistent,    "ele1_isChargeConsistent/O");
  tree_new->Branch("ele1_passesConversionVeto", &_ele1_passesConversionVeto,  "ele1_passesConversionVeto/O");
  tree_new->Branch("ele1_nMissingHits",  &_ele1_nMissingHits,  "ele1_nMissingHits/I");
  tree_new->Branch("ele1_sigmaEtaEta", &_ele1_sigmaEtaEta, "ele1_sigmaEtaEta/F");
  tree_new->Branch("ele1_HoE", &_ele1_HoE, "ele1_HoE/F");
  tree_new->Branch("ele1_deltaEta", &_ele1_deltaEta, "ele1_deltaEta");
  tree_new->Branch("ele1_deltaPhi", &_ele1_deltaPhi, "ele1_deltaPhi");
  tree_new->Branch("ele1_OoEminusOoP", &_ele1_OoEminusOoP, "ele1_OoEminusOoP");
  tree_new->Branch("ele1_isfakeablesel", &_ele1_isfakeablesel, "ele1_isfakeablesel/O");
  tree_new->Branch("ele1_ismvasel",      &_ele1_ismvasel,      "ele1_ismvasel/O");
  tree_new->Branch("ele1_isGenMatched",  &_ele1_isGenMatched,  "ele1_isGenMatched/I");

  
  tree_new->Branch("ele2_pt",        &_ele2_pt,         "ele2_pt/F");
  tree_new->Branch("ele2_conept",    &_ele2_conept,     "ele2_conept/F");
  tree_new->Branch("ele2_eta",       &_ele2_eta,        "ele2_eta/F");
  tree_new->Branch("ele2_phi",       &_ele2_phi,        "ele2_phi/F");
  tree_new->Branch("ele2_E",         &_ele2_E,          "ele2_E/F");
  tree_new->Branch("ele2_charge",    &_ele2_charge,     "ele2_charge/I");
  tree_new->Branch("ele2_miniRelIso",          &_ele2_miniRelIso,          "ele2_miniRelIso/F");
  tree_new->Branch("ele2_miniIsoCharged",      &_ele2_miniIsoCharged,      "ele2_miniIsoCharged/F");
  tree_new->Branch("ele2_miniIsoNeutral",      &_ele2_miniIsoNeutral,      "ele2_miniIsoNeutral/F");
  tree_new->Branch("ele2_PFRelIso04",    &_ele2_PFRelIso04,    "ele2_PFRelIso04/F");
  tree_new->Branch("ele2_jetNDauChargedMVASel",&_ele2_jetNDauChargedMVASel,"ele2_jetNDauChargedMVASel/I");
  tree_new->Branch("ele2_jetPtRel",  &_ele2_jetPtRel,   "ele2_jetPtRel/F");
  tree_new->Branch("ele2_jetPtRatio",&_ele2_jetPtRatio, "ele2_jetPtRatio/F");
  tree_new->Branch("ele2_jetCSV",    &_ele2_jetCSV,     "ele2_jetCSV/F");
  tree_new->Branch("ele2_jetDeepCSV",    &_ele2_jetDeepCSV,     "ele2_jetDeepCSV/F");
  tree_new->Branch("ele2_jetDeepJet",    &_ele2_jetDeepJet,     "ele2_jetDeepJet/F");
  tree_new->Branch("ele2_sip3D",     &_ele2_sip3D,      "ele2_sip3D/F");
  tree_new->Branch("ele2_dxyAbs",       &_ele2_dxyAbs,        "ele2_dxyAbs/F");
  tree_new->Branch("ele2_dxy",       &_ele2_dxy,        "ele2_dxy/F");
  tree_new->Branch("ele2_dz",        &_ele2_dz,         "ele2_dz/F");
  tree_new->Branch("ele2_ntMVAeleID",&_ele2_ntMVAeleID, "ele2_ntMVAeleID/F");
  tree_new->Branch("ele2_leptonMVA", &_ele2_leptonMVA,  "ele2_leptonMVA/F");
  tree_new->Branch("ele2_isChargeConsistent",   &_ele2_isChargeConsistent,    "ele2_isChargeConsistent/O");
  tree_new->Branch("ele2_passesConversionVeto", &_ele2_passesConversionVeto,  "ele2_passesConversionVeto/O");
  tree_new->Branch("ele2_nMissingHits",  &_ele2_nMissingHits,  "ele2_nMissingHits/I");
  tree_new->Branch("ele2_sigmaEtaEta", &_ele2_sigmaEtaEta, "ele2_sigmaEtaEta/F");
  tree_new->Branch("ele2_HoE", &_ele2_HoE, "ele2_HoE/F");
  tree_new->Branch("ele2_deltaEta", &_ele2_deltaEta, "ele2_deltaEta");
  tree_new->Branch("ele2_deltaPhi", &_ele2_deltaPhi, "ele2_deltaPhi");
  tree_new->Branch("ele2_OoEminusOoP", &_ele2_OoEminusOoP, "ele2_OoEminusOoP");
  tree_new->Branch("ele2_isfakeablesel", &_ele2_isfakeablesel, "ele2_isfakeablesel/O");
  tree_new->Branch("ele2_ismvasel",      &_ele2_ismvasel,      "ele2_ismvasel/O");
  tree_new->Branch("ele2_isGenMatched",  &_ele2_isGenMatched,  "ele2_isGenMatched/I");

  tree_new->Branch("tau1_pt",        &_tau1_pt,         "tau1_pt/F");
  tree_new->Branch("tau1_eta",       &_tau1_eta,        "tau1_eta/F");
  tree_new->Branch("tau1_phi",       &_tau1_phi,        "tau1_phi/F");
  tree_new->Branch("tau1_E",         &_tau1_E,          "tau1_E/F");
  tree_new->Branch("tau1_charge",    &_tau1_charge,     "tau1_charge/I");
  tree_new->Branch("tau1_dxy",       &_tau1_dxy,        "tau1_dxy/F");
  tree_new->Branch("tau1_dz",        &_tau1_dz,         "tau1_dz/F");
  tree_new->Branch("tau1_decayModeFindingOldDMs",                       &_tau1_decayModeFindingOldDMs,                       "tau1_decayModeFindingOldDMs/I");
  tree_new->Branch("tau1_decayModeFindingNewDMs",                       &_tau1_decayModeFindingNewDMs,                       "tau1_decayModeFindingNewDMs/I");
  tree_new->Branch("tau1_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau1_byCombinedIsolationDeltaBetaCorr3Hits,        "tau1_byCombinedIsolationDeltaBetaCorr3Hits/F");
  tree_new->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_rawMVArun2v1DBdR03oldDMwLT",     &_tau1_rawMVArun2v1DBdR03oldDMwLT,     "tau1_rawMVArun2v1DBdR03oldDMwLT/F");
  tree_new->Branch("tau1_byVVVLooseDeepTau2017v2VSjet" ,&_tau1_byVVVLooseDeepTau2017v2VSjet, "tau1_byVVVLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byVVLooseDeepTau2017v2VSjet" ,&_tau1_byVVLooseDeepTau2017v2VSjet, "tau1_byVVLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byVLooseDeepTau2017v2VSjet" ,&_tau1_byVLooseDeepTau2017v2VSjet, "tau1_byVLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byLooseDeepTau2017v2VSjet" ,&_tau1_byLooseDeepTau2017v2VSjet, "tau1_byLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byMediumDeepTau2017v2VSjet" ,&_tau1_byMediumDeepTau2017v2VSjet, "tau1_byMediumDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byTightDeepTau2017v2VSjet" ,&_tau1_byTightDeepTau2017v2VSjet, "tau1_byTightDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byVTightDeepTau2017v2VSjet" ,&_tau1_byVTightDeepTau2017v2VSjet, "tau1_byVTightDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byVVTightDeepTau2017v2VSjet" ,&_tau1_byVVTightDeepTau2017v2VSjet, "tau1_byVVTightDeepTau2017v2VSjet/I");
  tree_new->Branch("tau1_byDeepTau2017v2VSjetraw" ,&_tau1_byDeepTau2017v2VSjetraw, "tau1_byDeepTau2017v2VSjetraw/F");
  tree_new->Branch("tau1_againstMuonLoose3",         &_tau1_againstMuonLoose3,         "tau1_againstMuonLoose3/I");                         
  tree_new->Branch("tau1_againstMuonTight3",         &_tau1_againstMuonTight3,         "tau1_againstMuonTight3/I");                         
  tree_new->Branch("tau1_againstElectronVLooseMVA6", &_tau1_againstElectronVLooseMVA6, "tau1_againstElectronVLooseMVA6/I");                         
  tree_new->Branch("tau1_againstElectronLooseMVA6",  &_tau1_againstElectronLooseMVA6,  "tau1_againstElectronLooseMVA6/I");                         
  tree_new->Branch("tau1_againstElectronMediumMVA6", &_tau1_againstElectronMediumMVA6, "tau1_againstElectronMediumMVA6/I");                         
  tree_new->Branch("tau1_againstElectronTightMVA6",  &_tau1_againstElectronTightMVA6,  "tau1_againstElectronTightMVA6/I");   
  tree_new->Branch("tau1_againstElectronVTightMVA6", &_tau1_againstElectronVTightMVA6, "tau1_againstElectronVTightMVA6/I");
  tree_new->Branch("tau1_isGenMatched", &_tau1_isGenMatched, "tau1_isGenMatched/I");

  tree_new->Branch("tau2_pt",        &_tau2_pt,         "tau2_pt/F");
  tree_new->Branch("tau2_eta",       &_tau2_eta,        "tau2_eta/F");
  tree_new->Branch("tau2_phi",       &_tau2_phi,        "tau2_phi/F");
  tree_new->Branch("tau2_E",         &_tau2_E,          "tau2_E/F");
  tree_new->Branch("tau2_charge",    &_tau2_charge,     "tau2_charge/I");
  tree_new->Branch("tau2_dxy",       &_tau2_dxy,        "tau2_dxy/F");
  tree_new->Branch("tau2_dz",        &_tau2_dz,         "tau2_dz/F");
  tree_new->Branch("tau2_decayModeFindingOldDMs",                       &_tau2_decayModeFindingOldDMs,                       "tau2_decayModeFindingOldDMs/I");
  tree_new->Branch("tau2_decayModeFindingNewDMs",                       &_tau2_decayModeFindingNewDMs,                       "tau2_decayModeFindingNewDMs/I");
  tree_new->Branch("tau2_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau2_byCombinedIsolationDeltaBetaCorr3Hits,        "tau2_byCombinedIsolationDeltaBetaCorr3Hits/F");
  tree_new->Branch("tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau2_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau2_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau2_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau2_rawMVArun2v1DBdR03oldDMwLT",     &_tau2_rawMVArun2v1DBdR03oldDMwLT,     "tau2_rawMVArun2v1DBdR03oldDMwLT/F");
  tree_new->Branch("tau2_byVVVLooseDeepTau2017v2VSjet" ,&_tau2_byVVVLooseDeepTau2017v2VSjet, "tau2_byVVVLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byVVLooseDeepTau2017v2VSjet" ,&_tau2_byVVLooseDeepTau2017v2VSjet, "tau2_byVVLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byVLooseDeepTau2017v2VSjet" ,&_tau2_byVLooseDeepTau2017v2VSjet, "tau2_byVLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byLooseDeepTau2017v2VSjet" ,&_tau2_byLooseDeepTau2017v2VSjet, "tau2_byLooseDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byMediumDeepTau2017v2VSjet" ,&_tau2_byMediumDeepTau2017v2VSjet, "tau2_byMediumDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byTightDeepTau2017v2VSjet" ,&_tau2_byTightDeepTau2017v2VSjet, "tau2_byTightDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byVTightDeepTau2017v2VSjet" ,&_tau2_byVTightDeepTau2017v2VSjet, "tau2_byVTightDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byVVTightDeepTau2017v2VSjet" ,&_tau2_byVVTightDeepTau2017v2VSjet, "tau2_byVVTightDeepTau2017v2VSjet/I");
  tree_new->Branch("tau2_byDeepTau2017v2VSjetraw" ,&_tau2_byDeepTau2017v2VSjetraw, "tau2_byDeepTau2017v2VSjetraw/F");
  tree_new->Branch("tau2_againstMuonLoose3",         &_tau2_againstMuonLoose3,         "tau2_againstMuonLoose3/I");                         
  tree_new->Branch("tau2_againstMuonTight3",         &_tau2_againstMuonTight3,         "tau2_againstMuonTight3/I");                         
  tree_new->Branch("tau2_againstElectronVLooseMVA6", &_tau2_againstElectronVLooseMVA6, "tau2_againstElectronVLooseMVA6/I");                         
  tree_new->Branch("tau2_againstElectronLooseMVA6",  &_tau2_againstElectronLooseMVA6,  "tau2_againstElectronLooseMVA6/I");                         
  tree_new->Branch("tau2_againstElectronMediumMVA6", &_tau2_againstElectronMediumMVA6, "tau2_againstElectronMediumMVA6/I");                         
  tree_new->Branch("tau2_againstElectronTightMVA6",  &_tau2_againstElectronTightMVA6,  "tau2_againstElectronTightMVA6/I");   
  tree_new->Branch("tau2_againstElectronVTightMVA6", &_tau2_againstElectronVTightMVA6,  "tau2_againstElectronVTightMVA6/I"); 
  tree_new->Branch("tau2_isGenMatched", &_tau2_isGenMatched, "tau2_isGenMatched/I");
                      
  tree_new->Branch("jet1_pt",  &_jet1_pt,  "jet1_pt/F");
  tree_new->Branch("jet1_eta", &_jet1_eta, "jet1_eta/F");
  tree_new->Branch("jet1_phi", &_jet1_phi, "jet1_phi/F");
  tree_new->Branch("jet1_E",   &_jet1_E,   "jet1_E/F");
  tree_new->Branch("jet1_CSV", &_jet1_CSV, "jet1_CSV/F");
  tree_new->Branch("jet1_DeepCSV", &_jet1_DeepCSV, "jet1_DeepCSV/F");
  tree_new->Branch("jet1_DeepJet", &_jet1_DeepJet, "jet1_DeepJet/F");
  tree_new->Branch("jet1_QGdiscr", &_jet1_QGdiscr, "jet1_QGdiscr/F");
			       
  tree_new->Branch("jet2_pt",  &_jet2_pt,  "jet2_pt/F");
  tree_new->Branch("jet2_eta", &_jet2_eta, "jet2_eta/F");
  tree_new->Branch("jet2_phi", &_jet2_phi, "jet2_phi/F");
  tree_new->Branch("jet2_E",   &_jet2_E,   "jet2_E/F");
  tree_new->Branch("jet2_CSV", &_jet2_CSV, "jet2_CSV/F");
  tree_new->Branch("jet2_DeepCSV", &_jet2_DeepCSV, "jet2_DeepCSV/F");
  tree_new->Branch("jet2_DeepJet", &_jet2_DeepJet, "jet2_DeepJet/F");
  tree_new->Branch("jet2_QGdiscr", &_jet2_QGdiscr, "jet2_QGdiscr/F");

  tree_new->Branch("jet3_pt",  &_jet3_pt,  "jet3_pt/F");
  tree_new->Branch("jet3_eta", &_jet3_eta, "jet3_eta/F");
  tree_new->Branch("jet3_phi", &_jet3_phi, "jet3_phi/F");
  tree_new->Branch("jet3_E",   &_jet3_E,   "jet3_E/F");
  tree_new->Branch("jet3_CSV", &_jet3_CSV, "jet3_CSV/F");
  tree_new->Branch("jet3_DeepCSV", &_jet3_DeepCSV, "jet3_DeepCSV/F");
  tree_new->Branch("jet3_DeepJet", &_jet3_DeepJet, "jet3_DeepJet/F");
  tree_new->Branch("jet3_QGdiscr", &_jet3_QGdiscr, "jet3_QGdiscr/F");
			       
  tree_new->Branch("jet4_pt",  &_jet4_pt,  "jet4_pt/F");
  tree_new->Branch("jet4_eta", &_jet4_eta, "jet4_eta/F");
  tree_new->Branch("jet4_phi", &_jet4_phi, "jet4_phi/F");
  tree_new->Branch("jet4_E",   &_jet4_E,   "jet4_E/F");
  tree_new->Branch("jet4_CSV", &_jet4_CSV, "jet4_CSV/F");
  tree_new->Branch("jet4_DeepCSV", &_jet4_DeepCSV, "jet4_DeepCSV/F");
  tree_new->Branch("jet4_DeepJet", &_jet4_DeepJet, "jet4_DeepJet/F");
  tree_new->Branch("jet4_QGdiscr", &_jet4_QGdiscr, "jet4_QGdiscr/F");

  tree_new->Branch("jetFwd1_pt",  &_jetFwd1_pt,  "jetFwd1_pt/F");
  tree_new->Branch("jetFwd1_eta", &_jetFwd1_eta, "jetFwd1_eta/F");
  tree_new->Branch("jetFwd1_phi", &_jetFwd1_phi, "jetFwd1_phi/F");
  tree_new->Branch("jetFwd1_E",   &_jetFwd1_E,   "jetFwd1_E/F");

  tree_new->Branch("jetFwd2_pt",  &_jetFwd2_pt,  "jetFwd2_pt/F");
  tree_new->Branch("jetFwd2_eta", &_jetFwd2_eta, "jetFwd2_eta/F");
  tree_new->Branch("jetFwd2_phi", &_jetFwd2_phi, "jetFwd2_phi/F");
  tree_new->Branch("jetFwd2_E",   &_jetFwd2_E,   "jetFwd2_E/F");

  tree_new->Branch("jetFwd3_pt",  &_jetFwd3_pt,  "jetFwd3_pt/F");
  tree_new->Branch("jetFwd3_eta", &_jetFwd3_eta, "jetFwd3_eta/F");
  tree_new->Branch("jetFwd3_phi", &_jetFwd3_phi, "jetFwd3_phi/F");
  tree_new->Branch("jetFwd3_E",   &_jetFwd3_E,   "jetFwd3_E/F");

  tree_new->Branch("jetFwd4_pt",  &_jetFwd4_pt,  "jetFwd4_pt/F");
  tree_new->Branch("jetFwd4_eta", &_jetFwd4_eta, "jetFwd4_eta/F");
  tree_new->Branch("jetFwd4_phi", &_jetFwd4_phi, "jetFwd4_phi/F");
  tree_new->Branch("jetFwd4_E",   &_jetFwd4_E,   "jetFwd4_E/F");

  tree_new->Branch("jetAK8_1_pt", &_jetAK8_1_pt, "jetAK8_1_pt/F");
  tree_new->Branch("jetAK8_1_eta", &_jetAK8_1_eta, "jetAK8_1_eta/F");
  tree_new->Branch("jetAK8_1_phi", &_jetAK8_1_phi, "jetAK8_1_phi/F");
  tree_new->Branch("jetAK8_1_E", &_jetAK8_1_E, "jetAK8_1_E/F");
  tree_new->Branch("jetAK8_1_subjet_1_pt", &_jetAK8_1_subjet_1_pt, "jetAK8_1_subjet_1_pt/F");
  tree_new->Branch("jetAK8_1_subjet_1_eta", &_jetAK8_1_subjet_1_eta, "jetAK8_1_subjet_1_eta/F");
  tree_new->Branch("jetAK8_1_subjet_1_phi", &_jetAK8_1_subjet_1_phi, "jetAK8_1_subjet_1_phi/F");
  tree_new->Branch("jetAK8_1_subjet_1_E", &_jetAK8_1_subjet_1_E, "jetAK8_1_subjet_1_E/F");
  tree_new->Branch("jetAK8_1_subjet_2_pt", &_jetAK8_1_subjet_2_pt, "jetAK8_1_subjet_2_pt/F");
  tree_new->Branch("jetAK8_1_subjet_2_eta", &_jetAK8_1_subjet_2_eta, "jetAK8_1_subjet_2_eta/F");
  tree_new->Branch("jetAK8_1_subjet_2_phi", &_jetAK8_1_subjet_2_phi, "jetAK8_1_subjet_2_phi/F");
  tree_new->Branch("jetAK8_1_subjet_2_E", &_jetAK8_1_subjet_2_E, "jetAK8_1_subjet_2_E/F");
  tree_new->Branch("jetAK8_1_SDmass", &_jetAK8_1_SDmass, "jetAK8_1_SDmass/F");
  tree_new->Branch("jetAK8_1_tau1", &_jetAK8_1_tau1, "jetAK8_1_tau1/F");
  tree_new->Branch("jetAK8_1_tau2", &_jetAK8_1_tau2, "jetAK8_1_tau2/F");
 
  tree_new->Branch("jetAK8_2_pt", &_jetAK8_2_pt, "jetAK8_2_pt/F");
  tree_new->Branch("jetAK8_2_eta", &_jetAK8_2_eta, "jetAK8_2_eta/F");
  tree_new->Branch("jetAK8_2_phi", &_jetAK8_2_phi, "jetAK8_2_phi/F");
  tree_new->Branch("jetAK8_2_E", &_jetAK8_2_E, "jetAK8_2_E/F");
  tree_new->Branch("jetAK8_2_subjet_1_pt", &_jetAK8_2_subjet_1_pt, "jetAK8_2_subjet_1_pt/F");
  tree_new->Branch("jetAK8_2_subjet_1_eta", &_jetAK8_2_subjet_1_eta, "jetAK8_2_subjet_1_eta/F");
  tree_new->Branch("jetAK8_2_subjet_1_phi", &_jetAK8_2_subjet_1_phi, "jetAK8_2_subjet_1_phi/F");
  tree_new->Branch("jetAK8_2_subjet_1_E", &_jetAK8_2_subjet_1_E, "jetAK8_2_subjet_1_E/F");
  tree_new->Branch("jetAK8_2_subjet_2_pt", &_jetAK8_2_subjet_2_pt, "jetAK8_2_subjet_2_pt/F");
  tree_new->Branch("jetAK8_2_subjet_2_eta", &_jetAK8_2_subjet_2_eta, "jetAK8_2_subjet_2_eta/F");
  tree_new->Branch("jetAK8_2_subjet_2_phi", &_jetAK8_2_subjet_2_phi, "jetAK8_2_subjet_2_phi/F");
  tree_new->Branch("jetAK8_2_subjet_2_E", &_jetAK8_2_subjet_2_E, "jetAK8_2_subjet_2_E/F");
  tree_new->Branch("jetAK8_2_SDmass", &_jetAK8_2_SDmass, "jetAK8_2_SDmass/F");
  tree_new->Branch("jetAK8_2_tau1", &_jetAK8_2_tau1, "jetAK8_2_tau1/F");
  tree_new->Branch("jetAK8_2_tau2", &_jetAK8_2_tau2, "jetAK8_2_tau2/F");
  			       
  tree_new->Branch("PFMET",    &_PFMET,    "PFMET/F");
  tree_new->Branch("PFMETphi", &_PFMETphi, "PFMETphi/F");
  tree_new->Branch("MHT",      &_MHT,      "MHT/F");
  tree_new->Branch("metLD",    &_metLD,    "metLD/F");
 

  //Old branches used
  tree->SetBranchAddress("EventNumber",&_nEvent);
  tree->SetBranchAddress("lumi",&_ls);
  tree->SetBranchAddress("RunNumber",&_run);

  tree->SetBranchAddress("n_recomu_presel",&_n_presel_mu);
  tree->SetBranchAddress("n_recomu_fakeable",&_n_fakeablesel_mu);
  tree->SetBranchAddress("n_recomu_mvasel",&_n_mvasel_mu);

  tree->SetBranchAddress("n_recoele_presel",&_n_presel_ele);
  tree->SetBranchAddress("n_recoele_fakeable",&_n_fakeablesel_ele);
  tree->SetBranchAddress("n_recoele_mvasel",&_n_mvasel_ele);

  tree->SetBranchAddress("n_recotauh",&_n_presel_tau);
  tree->SetBranchAddress("n_recoPFJet",&_n_presel_jet);
  tree->SetBranchAddress("n_recoPFFwdJet",&_n_presel_jetFwd);
  tree->SetBranchAddress("n_recoPFak8Jet",&_n_presel_jetAK8);

  vector<float> *_recomu_pt;
  vector<float> *_recomu_conept;
  vector<float> *_recomu_eta;
  vector<float> *_recomu_phi;
  vector<float> *_recomu_e;
  vector<int>   *_recomu_charge;
  vector<int>   *_recomu_jetNDauChargedMVASel;
  vector<int>   *_recomu_jetNDauChargedMVASel_nanoAOD;
  vector<float> *_recomu_miniRelIso;
  vector<float> *_recomu_miniRelIso_nanoAOD;
  vector<float> *_recomu_miniIsoCharged;
  vector<float> *_recomu_miniIsoCharged_nanoAOD;
  vector<float> *_recomu_miniIsoNeutral;
  vector<float> *_recomu_miniIsoNeutral_nanoAOD;
  vector<float> *_recomu_combreliso04;
  vector<float> *_recomu_jetPtRel;
  vector<float> *_recomu_jetPtRel_nanoAOD;
  vector<float> *_recomu_jetPtRatio;
  vector<float> *_recomu_jetPtRatio_nanoAOD;
  vector<float> *_recomu_jetCSV;
  vector<float> *_recomu_jetDeepCSV;
  vector<float> *_recomu_jetDeepJet;
  vector<float> *_recomu_sip3D;
  vector<float> *_recomu_dxy;
  vector<float> *_recomu_dz;
  vector<float> *_recomu_lepMVA_Id;
  vector<float> *_recomu_leptonMVA;
  vector<bool>  *_recomu_mediumID;
  vector<float> *_recomu_rel_error_trackpt;
  vector<bool>  *_recomu_isfakeable;
  vector<bool>  *_recomu_ismvasel;
  vector<bool>  *_recomu_isGenMatched;

  vector<float> *_recoele_pt;
  vector<float> *_recoele_corr_pt;
  vector<float> *_recoele_conept;
  vector<float> *_recoele_eta;
  vector<float> *_recoele_phi;
  vector<float> *_recoele_e;
  vector<float> *_recoele_corr_e;
  vector<int>   *_recoele_charge;
  vector<int>   *_recoele_jetNDauChargedMVASel;
  vector<int>   *_recoele_jetNDauChargedMVASel_nanoAOD;
  vector<float> *_recoele_miniRelIso;
  vector<float> *_recoele_miniRelIso_nanoAOD;
  vector<float> *_recoele_miniIsoCharged;
  vector<float> *_recoele_miniIsoCharged_nanoAOD;
  vector<float> *_recoele_miniIsoNeutral;
  vector<float> *_recoele_miniIsoNeutral_nanoAOD;
  vector<float> *_recoele_PFRelIsoAll04_nanoAOD;
  vector<float> *_recoele_jetPtRel;
  vector<float> *_recoele_jetPtRel_nanoAOD;
  vector<float> *_recoele_jetPtRatio;
  vector<float> *_recoele_jetPtRatio_nanoAOD;
  vector<float> *_recoele_jetCSV;
  vector<float> *_recoele_jetDeepCSV;
  vector<float> *_recoele_jetDeepJet;
  vector<float> *_recoele_sip3D;
  vector<float> *_recoele_dxy;
  vector<float> *_recoele_dz;
  vector<float> *_recoele_lepMVA_Id;
  vector<float> *_recoele_leptonMVA;
  vector<bool>  *_recoele_isChargeConsistent;
  vector<bool>  *_recoele_passConversionVeto;
  vector<int>   *_recoele_nMissingHits;
  vector<float> *_recoele_sigmaEtaEta;
  vector<float> *_recoele_HoE;
  vector<float> *_recoele_deltaEta;
  vector<float> *_recoele_deltaPhi;
  vector<float> *_recoele_OoEminusOoP;
  vector<bool>  *_recoele_isfakeable;
  vector<bool>  *_recoele_ismvasel;
  vector<bool>  *_recoele_isGenMatched;

  vector<float> *_recotauh_pt;
  vector<float> *_recotauh_eta;
  vector<float> *_recotauh_phi;
  vector<float> *_recotauh_e;
  vector<int>   *_recotauh_charge;
  vector<float> *_recotauh_dxy;
  vector<float> *_recotauh_dz;
  vector<float> *_recotauh_iso;
  vector<int>   *_recotauh_decayModeFindingOldDMs;
  vector<int>   *_recotauh_decayModeFindingNewDMs;
  vector<int>   *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   *_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   *_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   *_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<float> *_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw;
  vector<int>   *_recotauh_byVVVLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVVLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byMediumDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byTightDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVTightDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVVTightDeepTau2017v2VSjet;
  vector<float> *_recotauh_byDeepTau2017v2VSjetraw;

  vector<int>   *_recotauh_againstMuonLoose3;
  vector<int>   *_recotauh_againstMuonTight3;
  vector<int>   *_recotauh_againstElectronVLooseMVA6;
  vector<int>   *_recotauh_againstElectronLooseMVA6;
  vector<int>   *_recotauh_againstElectronMediumMVA6;
  vector<int>   *_recotauh_againstElectronTightMVA6;
  vector<int>   *_recotauh_againstElectronVTightMVA6;
  vector<bool>  *_recotauh_isGenMatched;

  vector<float> *_recoPFJet_pt;
  vector<float> *_recoPFJet_eta;
  vector<float> *_recoPFJet_phi;
  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_CSVscore;
  vector<float> *_recoPFJet_DeepCSVscore;
  vector<float> *_recoPFJet_DeepJetscore;
  vector<float> *_recoPFJet_QGdiscr;

  vector<float> *_recoPFFwdJet_pt;
  vector<float> *_recoPFFwdJet_eta;
  vector<float> *_recoPFFwdJet_phi;
  vector<float> *_recoPFFwdJet_e;

  vector<float> *_recoPFak8Jet_e;
  vector<float> *_recoPFak8Jet_pt;
  vector<float> *_recoPFak8Jet_eta;
  vector<float> *_recoPFak8Jet_phi;
  vector<float> *_recoPFak8Jet_SoftDropMass;
  vector<float> *_recoPFak8Jet_tau1;
  vector<float> *_recoPFak8Jet_tau2;
  vector<int>   *_recoPFak8Jet_nsubjets;

  vector<float> *_recoPFak8Jet_subjet1_e;
  vector<float> *_recoPFak8Jet_subjet1_pt;
  vector<float> *_recoPFak8Jet_subjet1_eta;
  vector<float> *_recoPFak8Jet_subjet1_phi;

  vector<float> *_recoPFak8Jet_subjet2_e;
  vector<float> *_recoPFak8Jet_subjet2_pt;
  vector<float> *_recoPFak8Jet_subjet2_eta;
  vector<float> *_recoPFak8Jet_subjet2_phi;

  tree->SetBranchAddress("recomu_pt",                   &_recomu_pt);
  tree->SetBranchAddress("recomu_conept",               &_recomu_conept);
  tree->SetBranchAddress("recomu_eta",                  &_recomu_eta);
  tree->SetBranchAddress("recomu_phi",                  &_recomu_phi);
  tree->SetBranchAddress("recomu_e",                    &_recomu_e);
  tree->SetBranchAddress("recomu_charge",               &_recomu_charge);
  tree->SetBranchAddress("recomu_jetNDauChargedMVASel", &_recomu_jetNDauChargedMVASel);
  tree->SetBranchAddress("recomu_jetNDauChargedMVASel_nanoAOD", &_recomu_jetNDauChargedMVASel_nanoAOD);
  tree->SetBranchAddress("recomu_miniRelIso",           &_recomu_miniRelIso);
  tree->SetBranchAddress("recomu_miniRelIso_nanoAOD",      &_recomu_miniRelIso_nanoAOD);
  tree->SetBranchAddress("recomu_miniIsoCharged",       &_recomu_miniIsoCharged);
  tree->SetBranchAddress("recomu_miniIsoCharged_nanoAOD",         &_recomu_miniIsoCharged_nanoAOD);
  tree->SetBranchAddress("recomu_miniIsoNeutral",       &_recomu_miniIsoNeutral);
  tree->SetBranchAddress("recomu_miniIsoNeutral_nanoAOD",       &_recomu_miniIsoNeutral_nanoAOD);
  tree->SetBranchAddress("recomu_jetPtRel",             &_recomu_jetPtRel);
  tree->SetBranchAddress("recomu_jetPtRel_nanoAOD",     &_recomu_jetPtRel_nanoAOD);
  tree->SetBranchAddress("recomu_jetPtRatio",           &_recomu_jetPtRatio);
  tree->SetBranchAddress("recomu_jetPtRatio_nanoAOD",   &_recomu_jetPtRatio_nanoAOD);
  tree->SetBranchAddress("recomu_combreliso04",         &_recomu_combreliso04);
  tree->SetBranchAddress("recomu_jetCSV",               &_recomu_jetCSV);
  tree->SetBranchAddress("recomu_jetDeepCSV",           &_recomu_jetDeepCSV);
  tree->SetBranchAddress("recomu_jetDeepJet",           &_recomu_jetDeepJet);
  tree->SetBranchAddress("recomu_sip3D",                &_recomu_sip3D);
  tree->SetBranchAddress("recomu_dxy",                  &_recomu_dxy);
  tree->SetBranchAddress("recomu_dz",                   &_recomu_dz);
  tree->SetBranchAddress("recomu_lepMVA_Id",            &_recomu_lepMVA_Id);
  tree->SetBranchAddress("recomu_leptonMVA",            &_recomu_leptonMVA);
  tree->SetBranchAddress("recomu_mediumID",             &_recomu_mediumID);
  tree->SetBranchAddress("recomu_rel_error_trackpt",    &_recomu_rel_error_trackpt);
  tree->SetBranchAddress("recomu_isfakeable",           &_recomu_isfakeable);
  tree->SetBranchAddress("recomu_ismvasel",             &_recomu_ismvasel);
  tree->SetBranchAddress("recomu_isGenMatched",         &_recomu_isGenMatched);

  tree->SetBranchAddress("recoele_pt",                  &_recoele_pt);
  tree->SetBranchAddress("recoele_corr_pt",             &_recoele_corr_pt);
  tree->SetBranchAddress("recoele_conept",              &_recoele_conept);
  tree->SetBranchAddress("recoele_eta",                 &_recoele_eta);
  tree->SetBranchAddress("recoele_phi",                 &_recoele_phi);
  tree->SetBranchAddress("recoele_e",                   &_recoele_e);
  tree->SetBranchAddress("recoele_corr_e",              &_recoele_corr_e);
  tree->SetBranchAddress("recoele_charge",              &_recoele_charge);
  tree->SetBranchAddress("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
  tree->SetBranchAddress("recoele_jetNDauChargedMVASel_nanoAOD",&_recoele_jetNDauChargedMVASel_nanoAOD);
  tree->SetBranchAddress("recoele_miniRelIso",          &_recoele_miniRelIso);
  tree->SetBranchAddress("recoele_miniRelIso_nanoAOD",     &_recoele_miniRelIso_nanoAOD);
  tree->SetBranchAddress("recoele_miniIsoCharged",      &_recoele_miniIsoCharged);
  tree->SetBranchAddress("recoele_miniIsoCharged_nanoAOD",        &_recoele_miniIsoCharged_nanoAOD);
  tree->SetBranchAddress("recoele_miniIsoNeutral",      &_recoele_miniIsoNeutral);
  tree->SetBranchAddress("recoele_miniIsoNeutral_nanoAOD",      &_recoele_miniIsoNeutral_nanoAOD);
  tree->SetBranchAddress("recoele_PFRelIsoAll04_nanoAOD",    	&_recoele_PFRelIsoAll04_nanoAOD);
  tree->SetBranchAddress("recoele_jetPtRel",            &_recoele_jetPtRel);
  tree->SetBranchAddress("recoele_jetPtRel_nanoAOD",          &_recoele_jetPtRel_nanoAOD);
  tree->SetBranchAddress("recoele_jetPtRatio",          &_recoele_jetPtRatio);
  tree->SetBranchAddress("recoele_jetPtRatio_nanoAOD",        &_recoele_jetPtRatio_nanoAOD);
  tree->SetBranchAddress("recoele_jetCSV",              &_recoele_jetCSV);
  tree->SetBranchAddress("recoele_jetDeepCSV",          &_recoele_jetDeepCSV);
  tree->SetBranchAddress("recoele_jetDeepJet",          &_recoele_jetDeepJet);
  tree->SetBranchAddress("recoele_sip3D",               &_recoele_sip3D);
  tree->SetBranchAddress("recoele_dxy",                 &_recoele_dxy);
  tree->SetBranchAddress("recoele_dz",                  &_recoele_dz);
  tree->SetBranchAddress("recoele_lepMVA_Id",           &_recoele_lepMVA_Id);
  tree->SetBranchAddress("recoele_leptonMVA",           &_recoele_leptonMVA);
  tree->SetBranchAddress("recoele_isChargeConsistent",  &_recoele_isChargeConsistent);
  tree->SetBranchAddress("recoele_passConversionVeto",  &_recoele_passConversionVeto);
  tree->SetBranchAddress("recoele_nMissingHits",        &_recoele_nMissingHits);
  tree->SetBranchAddress("recoele_isfakeable",          &_recoele_isfakeable);
  tree->SetBranchAddress("recoele_ismvasel",            &_recoele_ismvasel);
  tree->SetBranchAddress("recoele_HoE",                 &_recoele_HoE);
  tree->SetBranchAddress("recoele_sigmaEtaEta",         &_recoele_sigmaEtaEta);
  tree->SetBranchAddress("recoele_deltaEta",		&_recoele_deltaEta);
  tree->SetBranchAddress("recoele_deltaPhi",		&_recoele_deltaPhi);
  tree->SetBranchAddress("recoele_OoEminusOoP",		&_recoele_OoEminusOoP);
  tree->SetBranchAddress("recoele_isGenMatched",	&_recoele_isGenMatched);

  tree->SetBranchAddress("recotauh_pt",                 &_recotauh_pt);
  tree->SetBranchAddress("recotauh_eta",                &_recotauh_eta);
  tree->SetBranchAddress("recotauh_phi",                &_recotauh_phi);
  tree->SetBranchAddress("recotauh_e",                  &_recotauh_e);
  tree->SetBranchAddress("recotauh_charge",             &_recotauh_charge);
  tree->SetBranchAddress("recotauh_dxy",                &_recotauh_dxy);
  tree->SetBranchAddress("recotauh_dz",                 &_recotauh_dz);
  tree->SetBranchAddress("recotauh_iso",                &_recotauh_iso);
  tree->SetBranchAddress("recotauh_decayModeFindingOldDMs", &_recotauh_decayModeFindingOldDMs);
  tree->SetBranchAddress("recotauh_decayModeFindingNewDMs", &_recotauh_decayModeFindingNewDMs);
  tree->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  tree->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",     &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  tree->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
  tree->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree->SetBranchAddress("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT);
  tree->SetBranchAddress("recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw", &_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw); 
  tree->SetBranchAddress("recotauh_byVVVLooseDeepTau2017v2VSjet", &_recotauh_byVVVLooseDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byVVLooseDeepTau2017v2VSjet", &_recotauh_byVVLooseDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byVLooseDeepTau2017v2VSjet", &_recotauh_byVLooseDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byLooseDeepTau2017v2VSjet", &_recotauh_byLooseDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byMediumDeepTau2017v2VSjet", &_recotauh_byMediumDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byTightDeepTau2017v2VSjet", &_recotauh_byTightDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byVTightDeepTau2017v2VSjet", &_recotauh_byVTightDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byVVTightDeepTau2017v2VSjet", &_recotauh_byVVTightDeepTau2017v2VSjet);
  tree->SetBranchAddress("recotauh_byDeepTau2017v2VSjetraw", &_recotauh_byDeepTau2017v2VSjetraw);
  tree->SetBranchAddress("recotauh_againstMuonLoose3",           &_recotauh_againstMuonLoose3);
  tree->SetBranchAddress("recotauh_againstMuonTight3",           &_recotauh_againstMuonTight3);
  tree->SetBranchAddress("recotauh_againstElectronVLooseMVA6",   &_recotauh_againstElectronVLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronLooseMVA6",    &_recotauh_againstElectronLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronMediumMVA6",   &_recotauh_againstElectronMediumMVA6);
  tree->SetBranchAddress("recotauh_againstElectronTightMVA6",    &_recotauh_againstElectronTightMVA6);
  tree->SetBranchAddress("recotauh_againstElectronVTightMVA6",   &_recotauh_againstElectronVTightMVA6);
  tree->SetBranchAddress("recotauh_isGenMatched", &_recotauh_isGenMatched);

  tree->SetBranchAddress("recoPFJet_pt",       &_recoPFJet_pt);
  tree->SetBranchAddress("recoPFJet_eta",      &_recoPFJet_eta);
  tree->SetBranchAddress("recoPFJet_phi",      &_recoPFJet_phi);
  tree->SetBranchAddress("recoPFJet_e",        &_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_CSVscore", &_recoPFJet_CSVscore);
  tree->SetBranchAddress("recoPFJet_DeepCSVscore", &_recoPFJet_DeepCSVscore);
  tree->SetBranchAddress("recoPFJet_DeepJetscore", &_recoPFJet_DeepJetscore);
  tree->SetBranchAddress("recoPFJet_QGdiscr",  &_recoPFJet_QGdiscr);

  tree->SetBranchAddress("recoPFFwdJet_pt",       &_recoPFFwdJet_pt);
  tree->SetBranchAddress("recoPFFwdJet_eta",      &_recoPFFwdJet_eta);
  tree->SetBranchAddress("recoPFFwdJet_phi",      &_recoPFFwdJet_phi);
  tree->SetBranchAddress("recoPFFwdJet_e",        &_recoPFFwdJet_e);

  tree->SetBranchAddress("recoPFak8Jet_e", &_recoPFak8Jet_e);
  tree->SetBranchAddress("recoPFak8Jet_pt", &_recoPFak8Jet_pt);
  tree->SetBranchAddress("recoPFak8Jet_eta", &_recoPFak8Jet_eta);
  tree->SetBranchAddress("recoPFak8Jet_phi", &_recoPFak8Jet_phi);
  tree->SetBranchAddress("recoPFak8Jet_SoftDropMass", &_recoPFak8Jet_SoftDropMass);
  tree->SetBranchAddress("recoPFak8Jet_tau1", &_recoPFak8Jet_tau1);
  tree->SetBranchAddress("recoPFak8Jet_tau2", &_recoPFak8Jet_tau2);
  tree->SetBranchAddress("recoPFak8Jet_nsubjets", &_recoPFak8Jet_nsubjets);

  tree->SetBranchAddress("recoPFak8Jet_subjet1_e", &_recoPFak8Jet_subjet1_e);
  tree->SetBranchAddress("recoPFak8Jet_subjet1_pt", &_recoPFak8Jet_subjet1_pt);
  tree->SetBranchAddress("recoPFak8Jet_subjet1_eta", &_recoPFak8Jet_subjet1_eta);
  tree->SetBranchAddress("recoPFak8Jet_subjet1_phi", &_recoPFak8Jet_subjet1_phi);
  tree->SetBranchAddress("recoPFak8Jet_subjet2_e", &_recoPFak8Jet_subjet2_e);
  tree->SetBranchAddress("recoPFak8Jet_subjet2_pt", &_recoPFak8Jet_subjet2_pt);
  tree->SetBranchAddress("recoPFak8Jet_subjet2_eta", &_recoPFak8Jet_subjet2_eta);
  tree->SetBranchAddress("recoPFak8Jet_subjet2_phi", &_recoPFak8Jet_subjet2_phi);

  tree->SetBranchAddress("PFMET",&_PFMET);
  tree->SetBranchAddress("PFMET_phi",&_PFMETphi);
  tree->SetBranchAddress("HTmiss",&_MHT);
  tree->SetBranchAddress("ETmissLD",&_metLD);
  
  //nentries = 100;
  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _nEvent       = -9999;
    _ls           = -9999;
    _run          = -9999;

    _n_presel_mu  = -9999;
    _n_fakeablesel_mu  = -9999;
    _n_mvasel_mu  = -9999;

    _n_presel_ele = -9999;
    _n_fakeablesel_ele  = -9999;
    _n_mvasel_ele  = -9999;

    _n_presel_tau = -9999;
    _n_presel_jet = -9999;
    _n_presel_jetFwd = -9999;
    _n_presel_jetAK8 = -9999;

    _mu1_pt       = -9999;
    _mu1_conept   = -9999;
    _mu1_eta      = -9999;
    _mu1_phi      = -9999;
    _mu1_E        = -9999;
    _mu1_charge   = -9999;
    _mu1_jetNDauChargedMVASel = -9999;
    _mu1_miniRelIso           = -9999;
    _mu1_miniIsoCharged       = -9999;
    _mu1_miniIsoNeutral       = -9999;
    _mu1_PFRelIso04           = -9999;
    _mu1_jetPtRel             = -9999;
    _mu1_jetPtRatio           = -9999;
    _mu1_jetCSV               = -9999;
    _mu1_jetDeepCSV           = -9999;
    _mu1_jetDeepJet           = -9999;
    _mu1_sip3D                = -9999;
    _mu1_dxy                  = -9999;
    _mu1_dxyAbs               = -9999;
    _mu1_dz                   = -9999;
    _mu1_segmentCompatibility = -9999;
    _mu1_leptonMVA            = -9999;
    _mu1_mediumID = 0;
    _mu1_dpt_div_pt = -9999;
    _mu1_isfakeablesel = 0;
    _mu1_ismvasel = 0;
    _mu1_isGenMatched = -9999;

    _mu2_pt       = -9999;
    _mu2_conept   = -9999;
    _mu2_eta      = -9999;
    _mu2_phi      = -9999;
    _mu2_E        = -9999;
    _mu2_charge   = -9999;
    _mu2_jetNDauChargedMVASel = -9999;
    _mu2_miniRelIso           = -9999;
    _mu2_miniIsoCharged       = -9999;
    _mu2_miniIsoNeutral       = -9999;
    _mu2_PFRelIso04 = -9999;
    _mu2_jetPtRel             = -9999;
    _mu2_jetPtRatio           = -9999;
    _mu2_jetCSV               = -9999;
    _mu2_jetDeepCSV           = -9999;
    _mu2_jetDeepJet           = -9999;
    _mu2_sip3D                = -9999;
    _mu2_dxy                  = -9999;
    _mu2_dxyAbs               = -9999;
    _mu2_dz                   = -9999;
    _mu2_segmentCompatibility = -9999;
    _mu2_leptonMVA            = -9999;
    _mu2_mediumID = 0;
    _mu2_dpt_div_pt = -9999;
    _mu2_isfakeablesel = 0;
    _mu2_ismvasel = 0;
    _mu2_isGenMatched = -9999;


    _ele1_pt       = -9999;
    _ele1_conept   = -9999;
    _ele1_eta      = -9999;
    _ele1_phi      = -9999;
    _ele1_E        = -9999;
    _ele1_charge   = -9999;
    _ele1_jetNDauChargedMVASel = -9999;
    _ele1_miniRelIso           = -9999;
    _ele1_miniIsoCharged       = -9999;
    _ele1_miniIsoNeutral       = -9999;
    _ele1_PFRelIso04           = -9999;
    _ele1_jetPtRel             = -9999;
    _ele1_jetPtRatio           = -9999;
    _ele1_jetCSV               = -9999;
    _ele1_jetDeepCSV           = -9999;
    _ele1_jetDeepJet           = -9999;
    _ele1_sip3D                = -9999;
    _ele1_dxy                  = -9999;
    _ele1_dxyAbs               = -9999;
    _ele1_dz                   = -9999;
    _ele1_ntMVAeleID           = -9999;
    _ele1_leptonMVA            = -9999;
    _ele1_isChargeConsistent   = 0;
    _ele1_passesConversionVeto = 0;
    _ele1_nMissingHits         = -9999;
    _ele1_sigmaEtaEta          = -9999;
    _ele1_HoE         	       = -9999;
    _ele1_deltaEta             = -9999;
    _ele1_deltaPhi             = -9999;
    _ele1_OoEminusOoP          = -9999;
    _ele1_isfakeablesel        = 0;
    _ele1_ismvasel             = 0;
    _ele1_isGenMatched         = -9999;

    _ele2_pt       = -9999;
    _ele2_conept   = -9999;
    _ele2_eta      = -9999;
    _ele2_phi      = -9999;
    _ele2_E        = -9999;
    _ele2_charge   = -9999;
    _ele2_jetNDauChargedMVASel = -9999;
    _ele2_miniRelIso           = -9999;
    _ele2_miniIsoCharged       = -9999;
    _ele2_miniIsoNeutral       = -9999;
    _ele2_PFRelIso04           = -9999;
    _ele2_jetPtRel             = -9999;
    _ele2_jetPtRatio           = -9999;
    _ele2_jetCSV               = -9999;
    _ele2_jetDeepCSV           = -9999;
    _ele2_jetDeepJet           = -9999;
    _ele2_sip3D                = -9999;
    _ele2_dxy                  = -9999;
    _ele2_dxyAbs               = -9999;
    _ele2_dz                   = -9999;
    _ele2_ntMVAeleID           = -9999;
    _ele2_leptonMVA            = -9999;
    _ele2_isChargeConsistent   = 0;
    _ele2_passesConversionVeto = 0;
    _ele2_nMissingHits         = -9999;
    _ele2_sigmaEtaEta          = -9999;
    _ele2_HoE                  = -9999;
    _ele2_deltaEta             = -9999;
    _ele2_deltaPhi             = -9999;
    _ele2_OoEminusOoP          = -9999;
    _ele2_isfakeablesel        = 0;
    _ele2_ismvasel             = 0;
    _ele2_isGenMatched         = -9999;

    _tau1_pt       = -9999;
    _tau1_eta      = -9999;
    _tau1_phi      = -9999;
    _tau1_E        = -9999;
    _tau1_charge   = -9999;    
    _tau1_dxy      = -9999;
    _tau1_dz       = -9999;
    _tau1_decayModeFindingOldDMs                           = -9999;
    _tau1_decayModeFindingNewDMs                           = -9999;
    _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_rawMVArun2v1DBdR03oldDMwLT                       = -9999;
    _tau1_byVVVLooseDeepTau2017v2VSjet = -9999;
    _tau1_byVVLooseDeepTau2017v2VSjet = -9999;
    _tau1_byVLooseDeepTau2017v2VSjet = -9999;
    _tau1_byLooseDeepTau2017v2VSjet = -9999;
    _tau1_byMediumDeepTau2017v2VSjet = -9999;
    _tau1_byTightDeepTau2017v2VSjet = -9999;
    _tau1_byVTightDeepTau2017v2VSjet = -9999;
    _tau1_byVVTightDeepTau2017v2VSjet = -9999;
    _tau1_byDeepTau2017v2VSjetraw = -9999;    
    _tau1_againstMuonLoose3          = -9999;
    _tau1_againstMuonTight3          = -9999;
    _tau1_againstElectronVLooseMVA6  = -9999;
    _tau1_againstElectronLooseMVA6   = -9999;
    _tau1_againstElectronMediumMVA6  = -9999;
    _tau1_againstElectronTightMVA6   = -9999;
    _tau1_againstElectronVTightMVA6  = -9999;
    _tau1_isGenMatched = -9999;

    _tau2_pt       = -9999;
    _tau2_eta      = -9999;
    _tau2_phi      = -9999;
    _tau2_E        = -9999;
    _tau2_charge   = -9999;    
    _tau2_dxy      = -9999;
    _tau2_dz       = -9999;
    _tau2_decayModeFindingOldDMs                           = -9999;
    _tau2_decayModeFindingNewDMs                           = -9999;
    _tau2_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau2_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau2_rawMVArun2v1DBdR03oldDMwLT                       = -9999;
    _tau2_byVVVLooseDeepTau2017v2VSjet = -9999;
    _tau2_byVVLooseDeepTau2017v2VSjet = -9999;
    _tau2_byVLooseDeepTau2017v2VSjet = -9999;
    _tau2_byLooseDeepTau2017v2VSjet = -9999;
    _tau2_byMediumDeepTau2017v2VSjet = -9999;
    _tau2_byTightDeepTau2017v2VSjet = -9999;
    _tau2_byVTightDeepTau2017v2VSjet = -9999;
    _tau2_byVVTightDeepTau2017v2VSjet = -9999;
    _tau2_byDeepTau2017v2VSjetraw = -9999;
    _tau2_againstMuonLoose3          = -9999;
    _tau2_againstMuonTight3          = -9999;
    _tau2_againstElectronVLooseMVA6  = -9999;
    _tau2_againstElectronLooseMVA6   = -9999;
    _tau2_againstElectronMediumMVA6  = -9999;
    _tau2_againstElectronTightMVA6   = -9999;
    _tau2_againstElectronVTightMVA6  = -9999;
    _tau2_isGenMatched = -9999;       
 
    _jet1_pt   = -9999;
    _jet1_eta  = -9999;
    _jet1_phi  = -9999;
    _jet1_E    = -9999;
    _jet1_CSV  = -9999;
    _jet1_DeepCSV  = -9999;
    _jet1_DeepJet = -9999;
    _jet1_QGdiscr  = -9999;

    _jet2_pt   = -9999;
    _jet2_eta  = -9999;
    _jet2_phi  = -9999;
    _jet2_E    = -9999;
    _jet2_CSV  = -9999;
    _jet2_DeepCSV  = -9999;
    _jet2_DeepJet = -9999;
    _jet2_QGdiscr  = -9999;

    _jet3_pt   = -9999;
    _jet3_eta  = -9999;
    _jet3_phi  = -9999;
    _jet3_E    = -9999;
    _jet3_CSV  = -9999;
    _jet3_DeepCSV  = -9999;
    _jet3_DeepJet = -9999;
    _jet3_QGdiscr  = -9999;
	
    _jet4_pt   = -9999;
    _jet4_eta  = -9999;
    _jet4_phi  = -9999;
    _jet4_E    = -9999;
    _jet4_CSV  = -9999;
    _jet4_DeepCSV  = -9999;
    _jet4_DeepJet = -9999;
    _jet4_QGdiscr  = -9999;

    _jetFwd1_pt   = -9999;
    _jetFwd1_eta  = -9999;
    _jetFwd1_phi  = -9999;
    _jetFwd1_E    = -9999;

    _jetFwd2_pt   = -9999;
    _jetFwd2_eta  = -9999;
    _jetFwd2_phi  = -9999;
    _jetFwd2_E    = -9999;

    _jetFwd3_pt   = -9999;
    _jetFwd3_eta  = -9999;
    _jetFwd3_phi  = -9999;
    _jetFwd3_E    = -9999;

    _jetFwd4_pt   = -9999;
    _jetFwd4_eta  = -9999;
    _jetFwd4_phi  = -9999;
    _jetFwd4_E    = -9999;

    _jetAK8_1_pt = -9999;
    _jetAK8_1_eta = -9999;
    _jetAK8_1_phi = -9999;
    _jetAK8_1_E = -9999;
    _jetAK8_1_subjet_1_pt = -9999;
    _jetAK8_1_subjet_1_eta = -9999;
    _jetAK8_1_subjet_1_phi = -9999;
    _jetAK8_1_subjet_1_E = -9999;
    _jetAK8_1_subjet_2_pt = -9999;
    _jetAK8_1_subjet_2_eta = -9999;
    _jetAK8_1_subjet_2_phi = -9999;
    _jetAK8_1_subjet_2_E = -9999;
    _jetAK8_1_SDmass = -9999;
    _jetAK8_1_tau1 = -9999;
    _jetAK8_1_tau2 = -9999;

    _jetAK8_2_pt = -9999;
    _jetAK8_2_eta = -9999;
    _jetAK8_2_phi = -9999;
    _jetAK8_2_E = -9999;
    _jetAK8_2_subjet_1_pt = -9999;
    _jetAK8_2_subjet_1_eta = -9999;
    _jetAK8_2_subjet_1_phi = -9999;
    _jetAK8_2_subjet_1_E = -9999;
    _jetAK8_2_subjet_2_pt = -9999;
    _jetAK8_2_subjet_2_eta = -9999;
    _jetAK8_2_subjet_2_phi = -9999;
    _jetAK8_2_subjet_2_E = -9999;
    _jetAK8_2_SDmass = -9999;
    _jetAK8_2_tau1 = -9999;
    _jetAK8_2_tau2 = -9999;

    _PFMET     = -9999;
    _PFMETphi  = -9999;    
    _MHT       = -9999;
    _metLD     = -9999;    

    ////
    
    _recomu_pt      = 0;
    _recomu_conept  = 0;
    _recomu_eta     = 0;
    _recomu_phi     = 0;
    _recomu_e       = 0;
    _recomu_charge  = 0;
    _recomu_jetNDauChargedMVASel = 0;
    _recomu_jetNDauChargedMVASel_nanoAOD = 0;
    _recomu_miniRelIso           = 0;
    _recomu_miniRelIso_nanoAOD      = 0;
    _recomu_miniIsoCharged       = 0;
    _recomu_miniIsoCharged_nanoAOD         = 0;
    _recomu_miniIsoNeutral       = 0;
    _recomu_miniIsoNeutral_nanoAOD       = 0;
    _recomu_combreliso04         = 0;
    _recomu_jetPtRel             = 0;
    _recomu_jetPtRatio           = 0;
    _recomu_jetPtRel_nanoAOD             = 0;
    _recomu_jetPtRatio_nanoAOD           = 0;
    _recomu_jetCSV               = 0;
    _recomu_jetDeepCSV           = 0;
    _recomu_jetDeepJet           = 0;
    _recomu_sip3D                = 0;
    _recomu_dxy                  = 0;
    _recomu_dz                   = 0;
    _recomu_lepMVA_Id         = 0;
    _recomu_leptonMVA            = 0;
    _recomu_mediumID             = 0;
    _recomu_rel_error_trackpt    = 0;
    _recomu_isfakeable           = 0;
    _recomu_ismvasel             = 0;
    _recomu_isGenMatched         = 0;

    _recoele_pt      = 0;
    _recoele_corr_pt = 0;
    _recoele_conept  = 0;
    _recoele_eta     = 0;
    _recoele_phi     = 0;
    _recoele_e       = 0;
    _recoele_corr_e  = 0;
    _recoele_charge  = 0;
    _recoele_jetNDauChargedMVASel = 0;
    _recoele_jetNDauChargedMVASel_nanoAOD = 0;
    _recoele_miniRelIso            = 0;
    _recoele_miniRelIso_nanoAOD      = 0;
    _recoele_miniIsoCharged       = 0;
    _recoele_miniIsoCharged_nanoAOD         = 0;
    _recoele_miniIsoNeutral       = 0;
    _recoele_miniIsoNeutral_nanoAOD       = 0;
    _recoele_PFRelIsoAll04_nanoAOD         = 0;
    _recoele_jetPtRel             = 0;
    _recoele_jetPtRatio           = 0;
    _recoele_jetPtRel_nanoAOD             = 0;
    _recoele_jetPtRatio_nanoAOD           = 0;
    _recoele_jetCSV               = 0;
    _recoele_jetDeepCSV           = 0;
    _recoele_jetDeepJet           = 0;
    _recoele_sip3D                = 0;
    _recoele_dxy                  = 0;
    _recoele_dz                   = 0;
    _recoele_lepMVA_Id         = 0;
    _recoele_leptonMVA            = 0;    
    _recoele_isChargeConsistent   = 0;
    _recoele_passConversionVeto   = 0;
    _recoele_nMissingHits         = 0;
    _recoele_sigmaEtaEta	  = 0;
    _recoele_HoE 		  = 0;
    _recoele_deltaEta  		  = 0;
    _recoele_deltaPhi		  = 0;
    _recoele_OoEminusOoP	  = 0;
    _recoele_isfakeable           = 0;
    _recoele_ismvasel             = 0;    
    _recoele_isGenMatched         = 0;

    _recotauh_pt     = 0;
    _recotauh_eta    = 0;
    _recotauh_phi    = 0;
    _recotauh_e      = 0;
    _recotauh_charge = 0;
    _recotauh_dxy    = 0;
    _recotauh_dz     = 0;
    _recotauh_iso    = 0;
    _recotauh_decayModeFindingOldDMs                             = 0;
    _recotauh_decayModeFindingNewDMs                             = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits        = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03    = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT   = 0;
    _recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT    = 0;
    _recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT   = 0;
    _recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT    = 0;
    _recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT   = 0;
    _recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw      = 0;
    _recotauh_byVVVLooseDeepTau2017v2VSjet = 0;
    _recotauh_byVVLooseDeepTau2017v2VSjet = 0;
    _recotauh_byVLooseDeepTau2017v2VSjet = 0;
    _recotauh_byLooseDeepTau2017v2VSjet = 0;
    _recotauh_byMediumDeepTau2017v2VSjet = 0;
    _recotauh_byTightDeepTau2017v2VSjet = 0;
    _recotauh_byVTightDeepTau2017v2VSjet = 0;
    _recotauh_byVVTightDeepTau2017v2VSjet = 0;
    _recotauh_byDeepTau2017v2VSjetraw = 0;
    _recotauh_againstMuonLoose3           = 0;
    _recotauh_againstMuonTight3           = 0;
    _recotauh_againstElectronVLooseMVA6   = 0;
    _recotauh_againstElectronLooseMVA6    = 0;
    _recotauh_againstElectronMediumMVA6   = 0;
    _recotauh_againstElectronTightMVA6    = 0;
    _recotauh_againstElectronVTightMVA6   = 0;
    _recotauh_isGenMatched = 0;

    _recoPFJet_pt           = 0;
    _recoPFJet_eta          = 0;
    _recoPFJet_phi          = 0;
    _recoPFJet_e            = 0;
    _recoPFJet_CSVscore     = 0;
    _recoPFJet_DeepCSVscore = 0; 
    _recoPFJet_DeepJetscore = 0; 
    _recoPFJet_QGdiscr = 0; 

    _recoPFFwdJet_pt           = 0;
    _recoPFFwdJet_eta          = 0;
    _recoPFFwdJet_phi          = 0;
    _recoPFFwdJet_e            = 0;

    _recoPFak8Jet_e = 0;
    _recoPFak8Jet_pt = 0;
    _recoPFak8Jet_eta = 0;
    _recoPFak8Jet_phi = 0;
    _recoPFak8Jet_SoftDropMass = 0;
    _recoPFak8Jet_tau1 = 0;
    _recoPFak8Jet_tau2 = 0;
    _recoPFak8Jet_nsubjets = 0;
    _recoPFak8Jet_subjet1_e = 0;
    _recoPFak8Jet_subjet1_pt = 0;
    _recoPFak8Jet_subjet1_eta = 0;
    _recoPFak8Jet_subjet1_phi = 0;
    _recoPFak8Jet_subjet2_e = 0;
    _recoPFak8Jet_subjet2_pt = 0;
    _recoPFak8Jet_subjet2_eta = 0;
    _recoPFak8Jet_subjet2_phi = 0;

    tree->GetEntry(i);
 
    if(_n_presel_mu>0){

      _mu1_pt     = (*_recomu_pt)[0];
      _mu1_conept = (*_recomu_conept)[0];
      _mu1_eta    = (*_recomu_eta)[0];
      _mu1_phi    = (*_recomu_phi)[0];
      _mu1_E      = (*_recomu_e)[0];
      _mu1_charge = (*_recomu_charge)[0];
      _mu1_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel_nanoAOD)[0];
      _mu1_miniRelIso           = (*_recomu_miniRelIso_nanoAOD)[0];
      _mu1_miniIsoCharged       = (*_recomu_miniIsoCharged_nanoAOD)[0]/_mu1_pt;
      _mu1_miniIsoNeutral       = (*_recomu_miniIsoNeutral_nanoAOD)[0]/_mu1_pt;
      _mu1_PFRelIso04           = (*_recomu_combreliso04)[0];
      _mu1_jetPtRel             = (*_recomu_jetPtRel_nanoAOD)[0];
      _mu1_jetPtRatio           = (*_recomu_jetPtRatio_nanoAOD)[0];
      _mu1_jetCSV               = (*_recomu_jetCSV)[0] ;
      _mu1_jetDeepCSV           = (*_recomu_jetDeepCSV)[0] ;
      _mu1_jetDeepJet           = (*_recomu_jetDeepJet)[0] ;
      _mu1_sip3D                = (*_recomu_sip3D)[0];
      _mu1_dxy                  = (*_recomu_dxy)[0];
      _mu1_dxyAbs               = abs((*_recomu_dxy)[0]);
      _mu1_dz                   = (*_recomu_dz)[0];
      _mu1_segmentCompatibility = (*_recomu_lepMVA_Id)[0];
      _mu1_leptonMVA            = (*_recomu_leptonMVA)[0];
      _mu1_mediumID             = (*_recomu_mediumID)[0];
      _mu1_dpt_div_pt           = (*_recomu_rel_error_trackpt)[0];
      _mu1_isfakeablesel        = (*_recomu_isfakeable)[0];      
      _mu1_ismvasel             = (*_recomu_ismvasel)[0];
      _mu1_isGenMatched         = (*_recomu_isGenMatched)[0];

    }
    
   if(_n_presel_mu>1){

      _mu2_pt     = (*_recomu_pt)[1];
      _mu2_conept = (*_recomu_conept)[1];
      _mu2_eta    = (*_recomu_eta)[1];
      _mu2_phi    = (*_recomu_phi)[1];
      _mu2_E      = (*_recomu_e)[1];
      _mu2_charge = (*_recomu_charge)[1];
      _mu2_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel_nanoAOD)[1];
      _mu2_miniRelIso           = (*_recomu_miniRelIso_nanoAOD)[1];
      _mu2_miniIsoCharged       = (*_recomu_miniIsoCharged_nanoAOD)[1]/_mu2_pt;
      _mu2_miniIsoNeutral       = (*_recomu_miniIsoNeutral_nanoAOD)[1]/_mu2_pt;
      _mu2_PFRelIso04           = (*_recomu_combreliso04)[1];
      _mu2_jetPtRel             = (*_recomu_jetPtRel_nanoAOD)[1];
      _mu2_jetPtRatio           = (*_recomu_jetPtRatio_nanoAOD)[1];
      _mu2_jetCSV               = (*_recomu_jetCSV)[1];
      _mu2_jetDeepCSV           = (*_recomu_jetDeepCSV)[1];
      _mu2_jetDeepJet           = (*_recomu_jetDeepJet)[1];
      _mu2_sip3D                = (*_recomu_sip3D)[1];
      _mu2_dxy                  = (*_recomu_dxy)[1];
      _mu2_dxyAbs               = abs((*_recomu_dxy)[1]);
      _mu2_dz                   = (*_recomu_dz)[1];
      _mu2_segmentCompatibility = (*_recomu_lepMVA_Id)[1];
      _mu2_leptonMVA            = (*_recomu_leptonMVA)[1];
      _mu2_mediumID             = (*_recomu_mediumID)[1];
      _mu2_dpt_div_pt           = (*_recomu_rel_error_trackpt)[1];
      _mu2_isfakeablesel        = (*_recomu_isfakeable)[1];  
      _mu2_ismvasel             = (*_recomu_ismvasel)[1];
      _mu2_isGenMatched         = (*_recomu_isGenMatched)[1];
      
    }
    
    if(_n_presel_ele>0){

      _ele1_pt = (*_recoele_corr_pt)[0];
      _ele1_conept = (*_recoele_conept)[0];
      _ele1_eta    = (*_recoele_eta)[0];
      _ele1_phi    = (*_recoele_phi)[0];
      _ele1_E = (*_recoele_corr_e)[0];
      _ele1_charge = (*_recoele_charge)[0];
      _ele1_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel_nanoAOD)[0];
      _ele1_miniRelIso           = (*_recoele_miniRelIso_nanoAOD)[0];
      _ele1_miniIsoCharged       = (*_recoele_miniIsoCharged_nanoAOD)[0]/(*_recoele_pt)[0];
      _ele1_miniIsoNeutral       = (*_recoele_miniIsoNeutral_nanoAOD)[0]/(*_recoele_pt)[0];
      _ele1_PFRelIso04           = (*_recoele_PFRelIsoAll04_nanoAOD)[0];
      _ele1_jetPtRel             = (*_recoele_jetPtRel_nanoAOD)[0];
      _ele1_jetPtRatio           = (*_recoele_jetPtRatio_nanoAOD)[0];
      _ele1_jetCSV               = (*_recoele_jetCSV)[0] ;
      _ele1_jetDeepCSV           = (*_recoele_jetDeepCSV)[0] ;
      _ele1_jetDeepJet           = (*_recoele_jetDeepJet)[0] ;
      _ele1_sip3D                = (*_recoele_sip3D)[0];
      _ele1_dxy                  = (*_recoele_dxy)[0];
      _ele1_dxyAbs               = abs((*_recoele_dxy)[0]);
      _ele1_dz                   = (*_recoele_dz)[0];
      _ele1_ntMVAeleID           = (*_recoele_lepMVA_Id)[0];
      _ele1_leptonMVA            = (*_recoele_leptonMVA)[0];
      _ele1_isChargeConsistent   = (*_recoele_isChargeConsistent)[0];      
      _ele1_passesConversionVeto = (*_recoele_passConversionVeto)[0];
      _ele1_nMissingHits         = (*_recoele_nMissingHits)[0];
      _ele1_sigmaEtaEta		 = (*_recoele_sigmaEtaEta)[0];
      _ele1_HoE			 = (*_recoele_HoE)[0];
      _ele1_deltaEta		 = (*_recoele_deltaEta)[0];
      _ele1_deltaPhi		 = (*_recoele_deltaPhi)[0];
      _ele1_OoEminusOoP		 = (*_recoele_OoEminusOoP)[0];
      _ele1_isfakeablesel        = (*_recoele_isfakeable)[0];
      _ele1_ismvasel             = (*_recoele_ismvasel)[0];
      _ele1_isGenMatched         = (*_recoele_isGenMatched)[0];

    }

    if(_n_presel_ele>1){

      _ele2_pt = (*_recoele_corr_pt)[1];
      _ele2_conept = (*_recoele_conept)[1];
      _ele2_eta    = (*_recoele_eta)[1];
      _ele2_phi    = (*_recoele_phi)[1];
      _ele2_E = (*_recoele_corr_e)[1];
      _ele2_charge = (*_recoele_charge)[1];
      _ele2_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel_nanoAOD)[1];
      _ele2_miniRelIso           = (*_recoele_miniRelIso_nanoAOD)[1];
      _ele2_miniIsoCharged       = (*_recoele_miniIsoCharged_nanoAOD)[1]/(*_recoele_pt)[1];
      _ele2_miniIsoNeutral       = (*_recoele_miniIsoNeutral_nanoAOD)[1]/(*_recoele_pt)[1];
      _ele2_PFRelIso04           = (*_recoele_PFRelIsoAll04_nanoAOD)[1];
      _ele2_jetPtRel             = (*_recoele_jetPtRel_nanoAOD)[1];
      _ele2_jetPtRatio           = (*_recoele_jetPtRatio_nanoAOD)[1];
      _ele2_jetCSV               = (*_recoele_jetCSV)[1] ;
      _ele2_jetDeepCSV           = (*_recoele_jetDeepCSV)[1] ;
      _ele2_jetDeepJet           = (*_recoele_jetDeepJet)[1] ;
      _ele2_sip3D                = (*_recoele_sip3D)[1];
      _ele2_dxy                  = (*_recoele_dxy)[1];
      _ele2_dxyAbs               = abs((*_recoele_dxy)[1]);
      _ele2_dz                   = (*_recoele_dz)[1];
      _ele2_ntMVAeleID           = (*_recoele_lepMVA_Id)[1];
      _ele2_leptonMVA            = (*_recoele_leptonMVA)[1];
      _ele2_isChargeConsistent   = (*_recoele_isChargeConsistent)[1];
      _ele2_passesConversionVeto = (*_recoele_passConversionVeto)[1];
      _ele2_nMissingHits         = (*_recoele_nMissingHits)[1];
      _ele2_sigmaEtaEta          = (*_recoele_sigmaEtaEta)[1];
      _ele2_HoE                  = (*_recoele_HoE)[1];
      _ele2_deltaEta             = (*_recoele_deltaEta)[1];
      _ele2_deltaPhi             = (*_recoele_deltaPhi)[1];
      _ele2_OoEminusOoP          = (*_recoele_OoEminusOoP)[1];
      _ele2_isfakeablesel        = (*_recoele_isfakeable)[1];
      _ele2_ismvasel             = (*_recoele_ismvasel)[1];
      _ele2_isGenMatched             = (*_recoele_isGenMatched)[1];

    }

    if(_n_presel_tau>0){

      _tau1_pt     = (*_recotauh_pt)[0];
      _tau1_eta    = (*_recotauh_eta)[0];
      _tau1_phi    = (*_recotauh_phi)[0];
      _tau1_E      = (*_recotauh_e)[0];
      _tau1_charge = (*_recotauh_charge)[0]; 
      _tau1_dxy    = (*_recotauh_dxy)[0]; 
      _tau1_dz     = (*_recotauh_dz)[0]; 
      _tau1_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[0];
      _tau1_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[0];
      _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[0];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_rawMVArun2v1DBdR03oldDMwLT                       = (*_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw)[0];
      _tau1_byVVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVVLooseDeepTau2017v2VSjet)[0];
      _tau1_byVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVLooseDeepTau2017v2VSjet)[0];
      _tau1_byVLooseDeepTau2017v2VSjet = (*_recotauh_byVLooseDeepTau2017v2VSjet)[0];
      _tau1_byLooseDeepTau2017v2VSjet = (*_recotauh_byLooseDeepTau2017v2VSjet)[0];
      _tau1_byMediumDeepTau2017v2VSjet = (*_recotauh_byMediumDeepTau2017v2VSjet)[0];
      _tau1_byTightDeepTau2017v2VSjet = (*_recotauh_byTightDeepTau2017v2VSjet)[0];
      _tau1_byVTightDeepTau2017v2VSjet = (*_recotauh_byVTightDeepTau2017v2VSjet)[0];
      _tau1_byVVTightDeepTau2017v2VSjet = (*_recotauh_byVVTightDeepTau2017v2VSjet)[0];
      _tau1_byDeepTau2017v2VSjetraw = (*_recotauh_byDeepTau2017v2VSjetraw)[0];    
      _tau1_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[0];
      _tau1_againstMuonTight3          = (*_recotauh_againstMuonTight3)[0];
      _tau1_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[0];
      _tau1_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[0];
      _tau1_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[0];
      _tau1_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[0];
      _tau1_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[0];
      _tau1_isGenMatched = (*_recotauh_isGenMatched)[0];

    }

    if(_n_presel_tau>1){

      _tau2_pt     = (*_recotauh_pt)[1];
      _tau2_eta    = (*_recotauh_eta)[1];
      _tau2_phi    = (*_recotauh_phi)[1];
      _tau2_E      = (*_recotauh_e)[1];
      _tau2_charge = (*_recotauh_charge)[1];
      _tau2_dxy    = (*_recotauh_dxy)[1]; 
      _tau2_dz     = (*_recotauh_dz)[1];     
      _tau2_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[1];
      _tau2_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[1];
      _tau2_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[1];
      _tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau2_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_rawMVArun2v1DBdR03oldDMwLT                       = (*_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw)[1];
      _tau2_byVVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVVLooseDeepTau2017v2VSjet)[1];
      _tau2_byVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVLooseDeepTau2017v2VSjet)[1];
      _tau2_byVLooseDeepTau2017v2VSjet = (*_recotauh_byVLooseDeepTau2017v2VSjet)[1];
      _tau2_byLooseDeepTau2017v2VSjet = (*_recotauh_byLooseDeepTau2017v2VSjet)[1];
      _tau2_byMediumDeepTau2017v2VSjet = (*_recotauh_byMediumDeepTau2017v2VSjet)[1];
      _tau2_byTightDeepTau2017v2VSjet = (*_recotauh_byTightDeepTau2017v2VSjet)[1];
      _tau2_byVTightDeepTau2017v2VSjet = (*_recotauh_byVTightDeepTau2017v2VSjet)[1];
      _tau2_byVVTightDeepTau2017v2VSjet = (*_recotauh_byVVTightDeepTau2017v2VSjet)[1];
      _tau2_byDeepTau2017v2VSjetraw = (*_recotauh_byDeepTau2017v2VSjetraw)[1];
      _tau2_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[1];
      _tau2_againstMuonTight3          = (*_recotauh_againstMuonTight3)[1];
      _tau2_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[1];
      _tau2_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[1];
      _tau2_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[1];
      _tau2_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[1];
      _tau2_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[1];
      _tau2_isGenMatched  = (*_recotauh_isGenMatched)[1];

    }
    
    if(_n_presel_jet>0){

      _jet1_pt   = (*_recoPFJet_pt)[0];
      _jet1_eta  = (*_recoPFJet_eta)[0];
      _jet1_phi  = (*_recoPFJet_phi)[0];
      _jet1_E    = (*_recoPFJet_e)[0];
      _jet1_CSV  = (*_recoPFJet_CSVscore)[0];
      _jet1_DeepCSV  = (*_recoPFJet_DeepCSVscore)[0];
      _jet1_DeepJet  = (*_recoPFJet_DeepJetscore)[0];
      _jet1_QGdiscr  = (*_recoPFJet_QGdiscr)[0];

    }

    if(_n_presel_jet>1){

      _jet2_pt   = (*_recoPFJet_pt)[1];
      _jet2_eta  = (*_recoPFJet_eta)[1];
      _jet2_phi  = (*_recoPFJet_phi)[1];
      _jet2_E    = (*_recoPFJet_e)[1];
      _jet2_CSV  = (*_recoPFJet_CSVscore)[1];
      _jet2_DeepCSV  = (*_recoPFJet_DeepCSVscore)[1];
      _jet2_DeepJet  = (*_recoPFJet_DeepJetscore)[1];
      _jet2_QGdiscr  = (*_recoPFJet_QGdiscr)[1];

    }
    
    if(_n_presel_jet>2){

      _jet3_pt   = (*_recoPFJet_pt)[2];
      _jet3_eta  = (*_recoPFJet_eta)[2];
      _jet3_phi  = (*_recoPFJet_phi)[2];
      _jet3_E    = (*_recoPFJet_e)[2];
      _jet3_CSV  = (*_recoPFJet_CSVscore)[2];
      _jet3_DeepCSV  = (*_recoPFJet_DeepCSVscore)[2];
      _jet3_DeepJet  = (*_recoPFJet_DeepJetscore)[2];
      _jet3_QGdiscr  = (*_recoPFJet_QGdiscr)[2];

    }
  
    if(_n_presel_jet>3){

      _jet4_pt   = (*_recoPFJet_pt)[3];
      _jet4_eta  = (*_recoPFJet_eta)[3];
      _jet4_phi  = (*_recoPFJet_phi)[3];
      _jet4_E    = (*_recoPFJet_e)[3];
      _jet4_CSV  = (*_recoPFJet_CSVscore)[3];
      _jet4_DeepCSV  = (*_recoPFJet_DeepCSVscore)[3];
      _jet4_DeepJet  = (*_recoPFJet_DeepJetscore)[3];
      _jet4_QGdiscr  = (*_recoPFJet_QGdiscr)[3];

    }

    if(_n_presel_jetFwd>0){

      _jetFwd1_pt   = (*_recoPFFwdJet_pt)[0];
      _jetFwd1_eta  = (*_recoPFFwdJet_eta)[0];
      _jetFwd1_phi  = (*_recoPFFwdJet_phi)[0];
      _jetFwd1_E    = (*_recoPFFwdJet_e)[0];

    }

    if(_n_presel_jetFwd>1){

      _jetFwd2_pt   = (*_recoPFFwdJet_pt)[1];
      _jetFwd2_eta  = (*_recoPFFwdJet_eta)[1];
      _jetFwd2_phi  = (*_recoPFFwdJet_phi)[1];
      _jetFwd2_E    = (*_recoPFFwdJet_e)[1];

    }
    
    if(_n_presel_jetFwd>2){

      _jetFwd3_pt   = (*_recoPFFwdJet_pt)[2];
      _jetFwd3_eta  = (*_recoPFFwdJet_eta)[2];
      _jetFwd3_phi  = (*_recoPFFwdJet_phi)[2];
      _jetFwd3_E    = (*_recoPFFwdJet_e)[2];

    }
  
    if(_n_presel_jetFwd>3){

      _jetFwd4_pt   = (*_recoPFFwdJet_pt)[3];
      _jetFwd4_eta  = (*_recoPFFwdJet_eta)[3];
      _jetFwd4_phi  = (*_recoPFFwdJet_phi)[3];
      _jetFwd4_E    = (*_recoPFFwdJet_e)[3];

    }

    if(_n_presel_jetAK8>0){

      _jetAK8_1_pt = (*_recoPFak8Jet_pt)[0];
      _jetAK8_1_eta = (*_recoPFak8Jet_eta)[0];
      _jetAK8_1_phi = (*_recoPFak8Jet_phi)[0];
      _jetAK8_1_E = (*_recoPFak8Jet_e)[0];
      _jetAK8_1_SDmass = (*_recoPFak8Jet_SoftDropMass)[0];
      _jetAK8_1_tau1 = (*_recoPFak8Jet_tau1)[0];
      _jetAK8_1_tau2 = (*_recoPFak8Jet_tau2)[0];

      if((*_recoPFak8Jet_nsubjets)[0]==2){

        _jetAK8_1_subjet_1_pt = (*_recoPFak8Jet_subjet1_pt)[0];
        _jetAK8_1_subjet_1_eta = (*_recoPFak8Jet_subjet1_eta)[0];
        _jetAK8_1_subjet_1_phi = (*_recoPFak8Jet_subjet1_phi)[0];
        _jetAK8_1_subjet_1_E = (*_recoPFak8Jet_subjet1_e)[0];

        _jetAK8_1_subjet_2_pt = (*_recoPFak8Jet_subjet2_pt)[0];
        _jetAK8_1_subjet_2_eta = (*_recoPFak8Jet_subjet2_pt)[0];
        _jetAK8_1_subjet_2_phi = (*_recoPFak8Jet_subjet2_pt)[0];
        _jetAK8_1_subjet_2_E = (*_recoPFak8Jet_subjet2_pt)[0];
        
      }

      else{

        _jetAK8_1_subjet_1_pt = -9999;
        _jetAK8_1_subjet_1_eta = -9999;
        _jetAK8_1_subjet_1_phi = -9999;
        _jetAK8_1_subjet_1_E = -9999;

        _jetAK8_1_subjet_2_pt = -9999;
        _jetAK8_1_subjet_2_eta = -9999;
        _jetAK8_1_subjet_2_phi = -9999;
        _jetAK8_1_subjet_2_E = -9999;
        
      }

    }

    if(_n_presel_jetAK8>1){

      _jetAK8_2_pt = (*_recoPFak8Jet_pt)[1];
      _jetAK8_2_eta = (*_recoPFak8Jet_eta)[1];
      _jetAK8_2_phi = (*_recoPFak8Jet_phi)[1];
      _jetAK8_2_E = (*_recoPFak8Jet_e)[1];
      _jetAK8_2_SDmass = (*_recoPFak8Jet_SoftDropMass)[1];
      _jetAK8_2_tau1 = (*_recoPFak8Jet_tau1)[1];
      _jetAK8_2_tau2 = (*_recoPFak8Jet_tau2)[1];

      /*if((*_recoPFak8Jet_nsubjets)[1]==2){

        _jetAK8_2_subjet_1_pt = (*_recoPFak8Jet_subjet1_pt)[1];
        _jetAK8_2_subjet_1_eta = (*_recoPFak8Jet_subjet1_eta)[1];
        _jetAK8_2_subjet_1_phi = (*_recoPFak8Jet_subjet1_phi)[1];
        _jetAK8_2_subjet_1_E = (*_recoPFak8Jet_subjet1_e)[1];

        _jetAK8_2_subjet_2_pt = (*_recoPFak8Jet_subjet2_pt)[1];
        _jetAK8_2_subjet_2_eta = (*_recoPFak8Jet_subjet2_pt)[1];
        _jetAK8_2_subjet_2_phi = (*_recoPFak8Jet_subjet2_pt)[1];
        _jetAK8_2_subjet_2_E = (*_recoPFak8Jet_subjet2_pt)[1];

      }

      else{

        _jetAK8_2_subjet_1_pt = -9999;
        _jetAK8_2_subjet_1_eta = -9999;
        _jetAK8_2_subjet_1_phi = -9999;
        _jetAK8_2_subjet_1_E = -9999;

        _jetAK8_2_subjet_2_pt = -9999;
        _jetAK8_2_subjet_2_eta = -9999;
        _jetAK8_2_subjet_2_phi = -9999;
        _jetAK8_2_subjet_2_E = -9999;
        
      }*/
      
    }
    

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}





void create_syncNtuple_eventbased(int year=2016){

  TString dir_in="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_splitted/";
  TString dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_syncformat/";
 
  if(year==2016) dir_in+="2016/";
  else if(year==2017) dir_in+="2017/";
  else if(year==2018) dir_in+="2018/";

  if(year==2016) dir_out+="events/2016/";
  else if(year==2017) dir_out+="events/2017/";
  else if(year==2018) dir_out+="events/2018/";

  TString file;
  if(year==2016) file="sync_ntuple_events_syncformat_ttHNonbb_2016_v15.root";
  else if(year==2017) file="sync_ntuple_events_syncformat_ttHNonbb_2017_v14.root";
  else if(year==2018) file="sync_ntuple_events_syncformat_ttHNonbb_2018_v14.root";

  vector<TString> list;
  if(year==2016) list.push_back(dir_in+"sync_ntuple_splitted_ttHNonbb_2016_v15.root");
  else if(year==2017) list.push_back(dir_in+"sync_ntuple_splitted_ttHNonbb_2017_v14.root");
  else if(year==2018) list.push_back(dir_in+"sync_ntuple_splitted_ttHNonbb_2018_v14.root");

  TChain * tree_2tau_SR = new TChain ("HTauTauTree_2tau_SR");
  TChain * tree_2tau_fake = new TChain ("HTauTauTree_2tau_fake");
  TChain * tree_1l1tau_SR = new TChain ("HTauTauTree_1l1tau_SR");
  TChain * tree_1l1tau_fake = new TChain ("HTauTauTree_1l1tau_fake");
  TChain * tree_1l1tau_flip = new TChain ("HTauTauTree_1l1tau_flip");
  TChain * tree_1l2tau_SR = new TChain ("HTauTauTree_1l2tau_SR");
  TChain * tree_1l2tau_fake = new TChain ("HTauTauTree_1l2tau_fake");
  TChain * tree_2lss_SR = new TChain ("HTauTauTree_2lss_SR");
  TChain * tree_2lss_fake = new TChain ("HTauTauTree_2lss_fake");
  TChain * tree_2lss_flip = new TChain ("HTauTauTree_2lss_flip");
  TChain * tree_2lss1tau_SR = new TChain ("HTauTauTree_2lss1tau_SR");
  TChain * tree_2lss1tau_fake = new TChain ("HTauTauTree_2lss1tau_fake");
  TChain * tree_2lss1tau_flip = new TChain ("HTauTauTree_2lss1tau_flip");
  TChain * tree_2los1tau_SR = new TChain ("HTauTauTree_2los1tau_SR");
  TChain * tree_2los1tau_fake = new TChain ("HTauTauTree_2los1tau_fake");
  TChain * tree_2l2tau_SR = new TChain ("HTauTauTree_2l2tau_SR");
  TChain * tree_2l2tau_fake = new TChain ("HTauTauTree_2l2tau_fake");
  TChain * tree_3l_SR = new TChain ("HTauTauTree_3l_SR");
  TChain * tree_3l_fake = new TChain ("HTauTauTree_3l_fake");
  TChain * tree_3l1tau_SR = new TChain ("HTauTauTree_3l1tau_SR");
  TChain * tree_3l1tau_fake = new TChain ("HTauTauTree_3l1tau_fake");
  TChain * tree_4l_SR = new TChain ("HTauTauTree_4l_SR");
  TChain * tree_4l_fake = new TChain ("HTauTauTree_4l_fake");
  TChain * tree_ttW_CR_SR = new TChain ("HTauTauTree_ttW_CR_SR");
  TChain * tree_ttW_CR_fake = new TChain ("HTauTauTree_ttW_CR_fake");
  TChain * tree_ttW_CR_flip = new TChain ("HTauTauTree_ttW_CR_flip");
  TChain * tree_ttZ_CR_SR = new TChain ("HTauTauTree_ttZ_CR_SR");
  TChain * tree_ttZ_CR_fake = new TChain ("HTauTauTree_ttZ_CR_fake");
  TChain * tree_WZ_CR_SR = new TChain ("HTauTauTree_WZ_CR_SR");
  TChain * tree_WZ_CR_fake = new TChain ("HTauTauTree_WZ_CR_fake");
  TChain * tree_ZZ_CR_SR = new TChain ("HTauTauTree_ZZ_CR_SR");
  TChain * tree_ZZ_CR_fake = new TChain ("HTauTauTree_ZZ_CR_fake");

  vector<TChain*> tree;
  tree.push_back(tree_2tau_SR);
  tree.push_back(tree_2tau_fake);
  tree.push_back(tree_1l1tau_SR);
  tree.push_back(tree_1l1tau_fake);
  tree.push_back(tree_1l1tau_flip);
  tree.push_back(tree_1l2tau_SR);
  tree.push_back(tree_1l2tau_fake);
  tree.push_back(tree_2lss_SR);
  tree.push_back(tree_2lss_fake);
  tree.push_back(tree_2lss_flip);
  tree.push_back(tree_2lss1tau_SR);
  tree.push_back(tree_2lss1tau_fake);
  tree.push_back(tree_2lss1tau_flip);
  tree.push_back(tree_2los1tau_SR);
  tree.push_back(tree_2los1tau_fake);
  tree.push_back(tree_2l2tau_SR);
  tree.push_back(tree_2l2tau_fake);
  tree.push_back(tree_3l_SR);
  tree.push_back(tree_3l_fake);
  tree.push_back(tree_3l1tau_SR);
  tree.push_back(tree_3l1tau_fake);
  tree.push_back(tree_4l_SR);
  tree.push_back(tree_4l_fake);
  tree.push_back(tree_ttW_CR_SR);
  tree.push_back(tree_ttW_CR_fake);
  tree.push_back(tree_ttW_CR_flip);
  tree.push_back(tree_ttZ_CR_SR);
  tree.push_back(tree_ttZ_CR_fake);
  tree.push_back(tree_WZ_CR_SR);
  tree.push_back(tree_WZ_CR_fake);
  tree.push_back(tree_ZZ_CR_SR);
  tree.push_back(tree_ZZ_CR_fake);


  int nFiles = list.size();

  for(int i=0;i<nFiles;i++){
    tree_2tau_SR->Add(list[i]);
    tree_2tau_fake->Add(list[i]);
    tree_1l1tau_SR->Add(list[i]);
    tree_1l1tau_fake->Add(list[i]);
    tree_1l1tau_flip->Add(list[i]);
    tree_1l2tau_SR->Add(list[i]);
    tree_1l2tau_fake->Add(list[i]);
    tree_2lss_SR->Add(list[i]);
    tree_2lss_fake->Add(list[i]);
    tree_2lss_flip->Add(list[i]);
    tree_2lss1tau_SR->Add(list[i]);
    tree_2lss1tau_fake->Add(list[i]);
    tree_2lss1tau_flip->Add(list[i]);
    tree_2los1tau_SR->Add(list[i]);
    tree_2los1tau_fake->Add(list[i]);
    tree_2l2tau_SR->Add(list[i]);
    tree_2l2tau_fake->Add(list[i]);
    tree_3l_SR->Add(list[i]);
    tree_3l_fake->Add(list[i]);
    tree_3l1tau_SR->Add(list[i]);
    tree_3l1tau_fake->Add(list[i]);
    tree_4l_SR->Add(list[i]);
    tree_4l_fake->Add(list[i]);
    tree_ttW_CR_SR->Add(list[i]);
    tree_ttW_CR_fake->Add(list[i]);
    tree_ttW_CR_flip->Add(list[i]);
    tree_ttZ_CR_SR->Add(list[i]);
    tree_ttZ_CR_fake->Add(list[i]);
    tree_WZ_CR_SR->Add(list[i]);
    tree_WZ_CR_fake->Add(list[i]);
    tree_ZZ_CR_SR->Add(list[i]);
    tree_ZZ_CR_fake->Add(list[i]);
  }

  TFile* f_new = TFile::Open(dir_out+file);
  /*if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/

  f_new = TFile::Open(dir_out+file,"RECREATE");

  TTree* tree_new_2tau_SR = new TTree("syncTree_0l2tau_SR","syncTree_0l2tau_SR");
  TTree* tree_new_2tau_fake = new TTree("syncTree_0l2tau_Fake","syncTree_0l2tau_Fake");
  TTree* tree_new_1l1tau_SR = new TTree("syncTree_1l1tau_SR","syncTree_1l1tau_SR");
  TTree* tree_new_1l1tau_fake = new TTree("syncTree_1l1tau_Fake","syncTree_1l1tau_Fake");
  TTree* tree_new_1l1tau_flip = new TTree("syncTree_1l1tau_Flip","syncTree_1l1tau_Flip");
  TTree* tree_new_1l2tau_SR = new TTree("syncTree_1l2tau_SR","syncTree_1l2tau_SR");
  TTree* tree_new_1l2tau_fake = new TTree("syncTree_1l2tau_Fake","syncTree_1l2tau_Fake");
  TTree* tree_new_2lss_SR = new TTree("syncTree_2lSS_SR","syncTree_2lSS_SR");
  TTree* tree_new_2lss_fake = new TTree("syncTree_2lSS_Fake","syncTree_2lSS_Fake");
  TTree* tree_new_2lss_flip = new TTree("syncTree_2lSS_Flip","syncTree_2lSS_Flip");
  TTree* tree_new_2lss1tau_SR = new TTree("syncTree_2lSS1tau_SR","syncTree_2lSS1tau_SR");
  TTree* tree_new_2lss1tau_fake = new TTree("syncTree_2lSS1tau_Fake","syncTree_2lSS1tau_Fake");
  TTree* tree_new_2lss1tau_flip = new TTree("syncTree_2lSS1tau_Flip","syncTree_2lSS1tau_Flip");
  TTree* tree_new_2los1tau_SR = new TTree("syncTree_2lOS1tau_SR","syncTree_2lOS1tau_SR");
  TTree* tree_new_2los1tau_fake = new TTree("syncTree_2lOS1tau_Fake","syncTree_2lOS1tau_Fake");
  TTree* tree_new_2l2tau_SR = new TTree("syncTree_2l2tau_SR","syncTree_2l2tau_SR");
  TTree* tree_new_2l2tau_fake = new TTree("syncTree_2l2tau_Fake","syncTree_2l2tau_Fake");
  TTree* tree_new_3l_SR = new TTree("syncTree_3l_SR","syncTree_3l_SR");
  TTree* tree_new_3l_fake = new TTree("syncTree_3l_Fake","syncTree_3l_Fake");
  TTree* tree_new_3l1tau_SR = new TTree("syncTree_3l1tau_SR","syncTree_3l1tau_SR");
  TTree* tree_new_3l1tau_fake = new TTree("syncTree_3l1tau_Fake","syncTree_3l1tau_Fake");
  TTree* tree_new_4l_SR = new TTree("syncTree_4l_SR","syncTree_4l_SR");
  TTree* tree_new_4l_fake = new TTree("syncTree_4l_Fake","syncTree_4l_Fake");
  TTree* tree_new_ttW_CR_SR = new TTree("syncTree_ttWctrl_SR","syncTree_ttWctrl_SR");
  TTree* tree_new_ttW_CR_fake = new TTree("syncTree_ttWctrl_Fake","syncTree_ttWctrl_Fake");
  TTree* tree_new_ttW_CR_flip = new TTree("syncTree_ttWctrl_Flip","syncTree_ttWctrl_Flip");
  TTree* tree_new_ttZ_CR_SR = new TTree("syncTree_ttZctrl_SR","syncTree_ttZctrl_SR");
  TTree* tree_new_ttZ_CR_fake = new TTree("syncTree_ttZctrl_Fake","syncTree_ttZctrl_Fake");
  TTree* tree_new_WZ_CR_SR = new TTree("syncTree_WZctrl_SR","syncTree_WZctrl_SR");
  TTree* tree_new_WZ_CR_fake = new TTree("syncTree_WZctrl_Fake","syncTree_WZctrl_Fake");
  TTree* tree_new_ZZ_CR_SR = new TTree("syncTree_ZZctrl_SR","syncTree_ZZctrl_SR");
  TTree* tree_new_ZZ_CR_fake = new TTree("syncTree_ZZctrl_Fake","syncTree_ZZctrl_Fake");

  vector<TTree*> tree_new;
  tree_new.push_back(tree_new_2tau_SR);
  tree_new.push_back(tree_new_2tau_fake);
  tree_new.push_back(tree_new_1l1tau_SR);
  tree_new.push_back(tree_new_1l1tau_fake);
  tree_new.push_back(tree_new_1l1tau_flip);
  tree_new.push_back(tree_new_1l2tau_SR);
  tree_new.push_back(tree_new_1l2tau_fake);
  tree_new.push_back(tree_new_2lss_SR);
  tree_new.push_back(tree_new_2lss_fake);
  tree_new.push_back(tree_new_2lss_flip);
  tree_new.push_back(tree_new_2lss1tau_SR);
  tree_new.push_back(tree_new_2lss1tau_fake);
  tree_new.push_back(tree_new_2lss1tau_flip);
  tree_new.push_back(tree_new_2los1tau_SR);
  tree_new.push_back(tree_new_2los1tau_fake);
  tree_new.push_back(tree_new_2l2tau_SR);
  tree_new.push_back(tree_new_2l2tau_fake);
  tree_new.push_back(tree_new_3l_SR);
  tree_new.push_back(tree_new_3l_fake);
  tree_new.push_back(tree_new_3l1tau_SR);
  tree_new.push_back(tree_new_3l1tau_fake);
  tree_new.push_back(tree_new_4l_SR);
  tree_new.push_back(tree_new_4l_fake);
  tree_new.push_back(tree_new_ttW_CR_SR);
  tree_new.push_back(tree_new_ttW_CR_fake);
  tree_new.push_back(tree_new_ttW_CR_flip);
  tree_new.push_back(tree_new_ttZ_CR_SR);
  tree_new.push_back(tree_new_ttZ_CR_fake);
  tree_new.push_back(tree_new_WZ_CR_SR);
  tree_new.push_back(tree_new_WZ_CR_fake);
  tree_new.push_back(tree_new_ZZ_CR_SR);
  tree_new.push_back(tree_new_ZZ_CR_fake);

  //New branches
  ULong64_t _nEvent;
  int _ls;
  int _run;

  bool _is_ttH_like;
  bool _is_tH_like_and_not_ttH_like;

  int _n_presel_mu;
  int _n_fakeablesel_mu;
  int _n_mvasel_mu;

  int _n_presel_ele;
  int _n_fakeablesel_ele;
  int _n_mvasel_ele;

  int _n_presel_tau;

  int _n_presel_jet;
  int _n_presel_jetFwd;
  int _n_presel_jetAK8;

  float _mu1_pt;
  float _mu1_conept;
  float _mu1_eta;
  float _mu1_phi;
  float _mu1_E;
  int   _mu1_charge;
  float _mu1_miniRelIso;
  float _mu1_miniIsoCharged;
  float _mu1_miniIsoNeutral;
  float _mu1_PFRelIso04; 
  int   _mu1_jetNDauChargedMVASel;
  float _mu1_jetPtRel;
  float _mu1_jetPtRatio;
  float _mu1_jetCSV;
  float _mu1_jetDeepCSV; 
  float _mu1_jetDeepJet; 
  float _mu1_sip3D;
  float _mu1_dxy;
  float _mu1_dxyAbs;
  float _mu1_dz;
  float _mu1_segmentCompatibility;
  float _mu1_leptonMVA;
  bool  _mu1_mediumID;
  float _mu1_dpt_div_pt;
  bool  _mu1_isfakeablesel;
  bool  _mu1_ismvasel;
  int   _mu1_isGenMatched;

  float _mu2_pt;
  float _mu2_conept;
  float _mu2_eta;
  float _mu2_phi;
  float _mu2_E;
  int   _mu2_charge;
  float _mu2_miniRelIso;
  float _mu2_miniIsoCharged;
  float _mu2_miniIsoNeutral;
  float _mu2_PFRelIso04; 
  int   _mu2_jetNDauChargedMVASel;
  float _mu2_jetPtRel;
  float _mu2_jetPtRatio;
  float _mu2_jetCSV;
  float _mu2_jetDeepCSV; 
  float _mu2_jetDeepJet; 
  float _mu2_sip3D;
  float _mu2_dxy;
  float _mu2_dxyAbs;
  float _mu2_dz;
  float _mu2_segmentCompatibility;
  float _mu2_leptonMVA;
  bool  _mu2_mediumID;
  float _mu2_dpt_div_pt;
  bool  _mu2_isfakeablesel;
  bool  _mu2_ismvasel;
  int _mu2_isGenMatched;

  float _ele1_pt;
  float _ele1_conept;
  float _ele1_eta;
  float _ele1_phi;
  float _ele1_E;
  int   _ele1_charge;
  float _ele1_miniRelIso;
  float _ele1_miniIsoCharged;
  float _ele1_miniIsoNeutral;
  float _ele1_PFRelIso04; 
  int   _ele1_jetNDauChargedMVASel;
  float _ele1_jetPtRel;
  float _ele1_jetPtRatio;
  float _ele1_jetCSV;
  float _ele1_jetDeepCSV;
  float _ele1_jetDeepJet;
  float _ele1_sip3D;
  float _ele1_dxy; 
  float _ele1_dxyAbs;
  float _ele1_dz;
  float _ele1_ntMVAeleID;
  float _ele1_leptonMVA;
  bool  _ele1_isChargeConsistent;
  bool  _ele1_passesConversionVeto;
  int   _ele1_nMissingHits;
  float _ele1_sigmaEtaEta; 
  float _ele1_HoE; 
  float _ele1_deltaEta; 
  float _ele1_deltaPhi; 
  float _ele1_OoEminusOoP; 
  bool  _ele1_isfakeablesel;
  bool  _ele1_ismvasel;
  int _ele1_isGenMatched;
 
  float _ele2_pt;
  float _ele2_conept;
  float _ele2_eta;
  float _ele2_phi;
  float _ele2_E;
  int   _ele2_charge;
  float _ele2_miniRelIso;
  float _ele2_miniIsoCharged;
  float _ele2_miniIsoNeutral;
  float _ele2_PFRelIso04; 
  int   _ele2_jetNDauChargedMVASel;
  float _ele2_jetPtRel;
  float _ele2_jetPtRatio;
  float _ele2_jetCSV;
  float _ele2_jetDeepCSV;
  float _ele2_jetDeepJet;
  float _ele2_sip3D;
  float _ele2_dxy; 
  float _ele2_dxyAbs;
  float _ele2_dz;
  float _ele2_ntMVAeleID;
  float _ele2_leptonMVA;
  bool  _ele2_isChargeConsistent;
  bool  _ele2_passesConversionVeto;
  int   _ele2_nMissingHits;
  float _ele2_sigmaEtaEta; 
  float _ele2_HoE; 
  float _ele2_deltaEta; 
  float _ele2_deltaPhi; 
  float _ele2_OoEminusOoP; 
  bool  _ele2_isfakeablesel;
  bool  _ele2_ismvasel;
  int _ele2_isGenMatched;

  float _tau1_pt;
  float _tau1_eta;
  float _tau1_phi;
  float _tau1_E;
  int   _tau1_charge;
  float _tau1_dxy;
  float _tau1_dz;
  int   _tau1_decayModeFindingOldDMs;
  int   _tau1_decayModeFindingNewDMs;
  float _tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  float _tau1_rawMVArun2v1DBdR03oldDMwLT;
  int   _tau1_byVVVLooseDeepTau2017v2VSjet;
  int   _tau1_byVVLooseDeepTau2017v2VSjet;
  int   _tau1_byVLooseDeepTau2017v2VSjet;
  int   _tau1_byLooseDeepTau2017v2VSjet;
  int   _tau1_byMediumDeepTau2017v2VSjet;
  int   _tau1_byTightDeepTau2017v2VSjet;
  int   _tau1_byVTightDeepTau2017v2VSjet;
  int   _tau1_byVVTightDeepTau2017v2VSjet;
  float _tau1_byDeepTau2017v2VSjetraw;
  int   _tau1_againstMuonLoose3;
  int   _tau1_againstMuonTight3;
  int   _tau1_againstElectronVLooseMVA6;
  int   _tau1_againstElectronLooseMVA6;
  int   _tau1_againstElectronMediumMVA6;
  int   _tau1_againstElectronTightMVA6;
  int   _tau1_againstElectronVTightMVA6;
  int   _tau1_isGenMatched;

  float _tau2_pt;
  float _tau2_eta;
  float _tau2_phi;
  float _tau2_E;
  int   _tau2_charge;
  float _tau2_dxy;
  float _tau2_dz;
  int   _tau2_decayModeFindingOldDMs;
  int   _tau2_decayModeFindingNewDMs;
  float _tau2_byCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int   _tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int   _tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  float _tau2_rawMVArun2v1DBdR03oldDMwLT;
  int   _tau2_byVVVLooseDeepTau2017v2VSjet;
  int   _tau2_byVVLooseDeepTau2017v2VSjet;
  int   _tau2_byVLooseDeepTau2017v2VSjet;
  int   _tau2_byLooseDeepTau2017v2VSjet;
  int   _tau2_byMediumDeepTau2017v2VSjet;
  int   _tau2_byTightDeepTau2017v2VSjet;
  int   _tau2_byVTightDeepTau2017v2VSjet;
  int   _tau2_byVVTightDeepTau2017v2VSjet;
  float _tau2_byDeepTau2017v2VSjetraw;
  int   _tau2_againstMuonLoose3;
  int   _tau2_againstMuonTight3;
  int   _tau2_againstElectronVLooseMVA6;
  int   _tau2_againstElectronLooseMVA6;
  int   _tau2_againstElectronMediumMVA6;
  int   _tau2_againstElectronTightMVA6;
  int   _tau2_againstElectronVTightMVA6;
  int   _tau2_isGenMatched;

  float _jet1_pt;
  float _jet1_eta;
  float _jet1_phi;
  float _jet1_E;
  float _jet1_CSV;
  float _jet1_DeepCSV;
  float _jet1_DeepJet;
  float _jet1_QGdiscr;
  
  float _jet2_pt;
  float _jet2_eta;
  float _jet2_phi;
  float _jet2_E;
  float _jet2_CSV;
  float _jet2_DeepCSV;
  float _jet2_DeepJet;
  float _jet2_QGdiscr;
  
  float _jet3_pt;
  float _jet3_eta;
  float _jet3_phi;
  float _jet3_E;
  float _jet3_CSV;
  float _jet3_DeepCSV;
  float _jet3_DeepJet;
  float _jet3_QGdiscr;

  float _jet4_pt;
  float _jet4_eta;
  float _jet4_phi;
  float _jet4_E;
  float _jet4_CSV;
  float _jet4_DeepCSV;
  float _jet4_DeepJet;
  float _jet4_QGdiscr;

  float _jetFwd1_pt;
  float _jetFwd1_eta;
  float _jetFwd1_phi;
  float _jetFwd1_E;
  
  float _jetFwd2_pt;
  float _jetFwd2_eta;
  float _jetFwd2_phi;
  float _jetFwd2_E;
  
  float _jetFwd3_pt;
  float _jetFwd3_eta;
  float _jetFwd3_phi;
  float _jetFwd3_E;

  float _jetFwd4_pt;
  float _jetFwd4_eta;
  float _jetFwd4_phi;
  float _jetFwd4_E;

  float _jetAK8_1_pt;
  float _jetAK8_1_eta;
  float _jetAK8_1_phi;
  float _jetAK8_1_E;
  float _jetAK8_1_subjet_1_pt;
  float _jetAK8_1_subjet_1_eta;
  float _jetAK8_1_subjet_1_phi;
  float _jetAK8_1_subjet_1_E;
  float _jetAK8_1_subjet_2_pt;
  float _jetAK8_1_subjet_2_eta;
  float _jetAK8_1_subjet_2_phi;
  float _jetAK8_1_subjet_2_E;
  float _jetAK8_1_SDmass;
  float _jetAK8_1_tau1;
  float _jetAK8_1_tau2;

  float _jetAK8_2_pt;
  float _jetAK8_2_eta;
  float _jetAK8_2_phi;
  float _jetAK8_2_E;
  float _jetAK8_2_subjet_1_pt;
  float _jetAK8_2_subjet_1_eta;
  float _jetAK8_2_subjet_1_phi;
  float _jetAK8_2_subjet_1_E;
  float _jetAK8_2_subjet_2_pt;
  float _jetAK8_2_subjet_2_eta;
  float _jetAK8_2_subjet_2_phi;
  float _jetAK8_2_subjet_2_E;
  float _jetAK8_2_SDmass;
  float _jetAK8_2_tau1;
  float _jetAK8_2_tau2;

  float _PFMET;
  float _PFMETphi;
  float _MHT;
  float _metLD;

  for(unsigned int i=0;i<tree_new.size();i++){

     tree_new[i]->Branch("nEvent",   &_nEvent,    "nEvent/L");
     tree_new[i]->Branch("ls",       &_ls,        "ls/I");
     tree_new[i]->Branch("run",      &_run,       "run/I");
 
     tree_new[i]->Branch("is_ttH_like",  &_is_ttH_like,  "is_ttH_like/O");
     tree_new[i]->Branch("is_tH_like_and_not_ttH_like",  &_is_tH_like_and_not_ttH_like,  "is_tH_like_and_not_ttH_like/O");

     tree_new[i]->Branch("n_presel_mu",      &_n_presel_mu,      "n_presel_mu/I");
     tree_new[i]->Branch("n_fakeablesel_mu", &_n_fakeablesel_mu, "n_fakeablesel_mu/I");
     tree_new[i]->Branch("n_mvasel_mu",      &_n_mvasel_mu,      "n_mvasel_mu/I");

     tree_new[i]->Branch("n_presel_ele",      &_n_presel_ele,      "n_presel_ele/I");
     tree_new[i]->Branch("n_fakeablesel_ele", &_n_fakeablesel_ele, "n_fakeablesel_ele/I");
     tree_new[i]->Branch("n_mvasel_ele",      &_n_mvasel_ele,      "n_mvasel_ele/I");

     tree_new[i]->Branch("n_presel_tau",  &_n_presel_tau,   "n_presel_tau/I");
     tree_new[i]->Branch("n_presel_jet",  &_n_presel_jet,   "n_presel_jet/I");
     tree_new[i]->Branch("n_presel_jetFwd",  &_n_presel_jetFwd,   "n_presel_jetFwd/I");
     tree_new[i]->Branch("n_presel_jetAK8",  &_n_presel_jetAK8,   "n_presel_jetAK8/I");

     tree_new[i]->Branch("mu1_pt",        &_mu1_pt,         "mu1_pt/F");
     tree_new[i]->Branch("mu1_conept",    &_mu1_conept,     "mu1_conept/F");
     tree_new[i]->Branch("mu1_eta",       &_mu1_eta,        "mu1_eta/F");
     tree_new[i]->Branch("mu1_phi",       &_mu1_phi,        "mu1_phi/F");
     tree_new[i]->Branch("mu1_E",         &_mu1_E,          "mu1_E/F");
     tree_new[i]->Branch("mu1_charge",    &_mu1_charge,     "mu1_charge/I");
     tree_new[i]->Branch("mu1_miniRelIso",          &_mu1_miniRelIso,          "mu1_miniRelIso/F");
     tree_new[i]->Branch("mu1_miniIsoCharged",      &_mu1_miniIsoCharged,      "mu1_miniIsoCharged/F");
     tree_new[i]->Branch("mu1_miniIsoNeutral",      &_mu1_miniIsoNeutral,      "mu1_miniIsoNeutral/F");
     tree_new[i]->Branch("mu1_PFRelIso04",    &_mu1_PFRelIso04,    "mu1_PFRelIso04/F");
     tree_new[i]->Branch("mu1_jetNDauChargedMVASel",&_mu1_jetNDauChargedMVASel,"mu1_jetNDauChargedMVASel/I");
     tree_new[i]->Branch("mu1_jetPtRel",  &_mu1_jetPtRel,   "mu1_jetPtRel/F");
     tree_new[i]->Branch("mu1_jetPtRatio",&_mu1_jetPtRatio, "mu1_jetPtRatio/F");
     tree_new[i]->Branch("mu1_jetCSV",    &_mu1_jetCSV,     "mu1_jetCSV/F");
     tree_new[i]->Branch("mu1_jetDeepCSV",    &_mu1_jetDeepCSV,     "mu1_jetDeepCSV/F");
     tree_new[i]->Branch("mu1_jetDeepJet",    &_mu1_jetDeepJet,     "mu1_jetDeepJet/F");
     tree_new[i]->Branch("mu1_sip3D",     &_mu1_sip3D,      "mu1_sip3D/F");
     tree_new[i]->Branch("mu1_dxy",       &_mu1_dxy,        "mu1_dxy/F");
     tree_new[i]->Branch("mu1_dxyAbs",       &_mu1_dxyAbs,        "mu1_dxyAbs/F");
     tree_new[i]->Branch("mu1_dz",        &_mu1_dz,         "mu1_dz/F");
     tree_new[i]->Branch("mu1_segmentCompatibility",&_mu1_segmentCompatibility,"mu1_segmentCompatibility/F");
     tree_new[i]->Branch("mu1_leptonMVA",     &_mu1_leptonMVA,     "mu1_leptonMVA/F");
     tree_new[i]->Branch("mu1_mediumID",      &_mu1_mediumID,      "mu1_mediumID/O");
     tree_new[i]->Branch("mu1_dpt_div_pt",    &_mu1_dpt_div_pt,    "mu1_dpt_div_pt/F");
     tree_new[i]->Branch("mu1_isfakeablesel", &_mu1_isfakeablesel, "mu1_isfakeablesel/O");
     tree_new[i]->Branch("mu1_ismvasel",      &_mu1_ismvasel,      "mu1_ismvasel/O");
     tree_new[i]->Branch("mu1_isGenMatched",      &_mu1_isGenMatched,      "mu1_isGenMatched/I");

     tree_new[i]->Branch("mu2_pt",        &_mu2_pt,         "mu2_pt/F");
     tree_new[i]->Branch("mu2_conept",    &_mu2_conept,     "mu2_conept/F");
     tree_new[i]->Branch("mu2_eta",       &_mu2_eta,        "mu2_eta/F");
     tree_new[i]->Branch("mu2_phi",       &_mu2_phi,        "mu2_phi/F");
     tree_new[i]->Branch("mu2_E",         &_mu2_E,          "mu2_E/F");
     tree_new[i]->Branch("mu2_charge",    &_mu2_charge,     "mu2_charge/I");
     tree_new[i]->Branch("mu2_miniRelIso",          &_mu2_miniRelIso,          "mu2_miniRelIso/F");
     tree_new[i]->Branch("mu2_miniIsoCharged",      &_mu2_miniIsoCharged,      "mu2_miniIsoCharged/F");
     tree_new[i]->Branch("mu2_miniIsoNeutral",      &_mu2_miniIsoNeutral,      "mu2_miniIsoNeutral/F");
     tree_new[i]->Branch("mu2_PFRelIso04",    &_mu2_PFRelIso04,    "mu2_PFRelIso04/F");
     tree_new[i]->Branch("mu2_jetNDauChargedMVASel",&_mu2_jetNDauChargedMVASel,"mu2_jetNDauChargedMVASel/I");
     tree_new[i]->Branch("mu2_jetPtRel",  &_mu2_jetPtRel,   "mu2_jetPtRel/F");
     tree_new[i]->Branch("mu2_jetPtRatio",&_mu2_jetPtRatio, "mu2_jetPtRatio/F");
     tree_new[i]->Branch("mu2_jetCSV",    &_mu2_jetCSV,     "mu2_jetCSV/F");
     tree_new[i]->Branch("mu2_jetDeepCSV",    &_mu2_jetDeepCSV,     "mu2_jetDeepCSV/F");
     tree_new[i]->Branch("mu2_jetDeepJet",    &_mu2_jetDeepJet,     "mu2_jetDeepJet/F");
     tree_new[i]->Branch("mu2_sip3D",     &_mu2_sip3D,      "mu2_sip3D/F");
     tree_new[i]->Branch("mu2_dxy",       &_mu2_dxy,        "mu2_dxy/F");
     tree_new[i]->Branch("mu2_dxyAbs",       &_mu2_dxyAbs,        "mu2_dxyAbs/F");
     tree_new[i]->Branch("mu2_dz",        &_mu2_dz,         "mu2_dz/F");
     tree_new[i]->Branch("mu2_segmentCompatibility",&_mu2_segmentCompatibility,"mu2_segmentCompatibility/F");
     tree_new[i]->Branch("mu2_leptonMVA",     &_mu2_leptonMVA,     "mu2_leptonMVA/F");
     tree_new[i]->Branch("mu2_mediumID",      &_mu2_mediumID,      "mu2_mediumID/O");
     tree_new[i]->Branch("mu2_dpt_div_pt",    &_mu2_dpt_div_pt,    "mu2_dpt_div_pt/F");
     tree_new[i]->Branch("mu2_isfakeablesel", &_mu2_isfakeablesel, "mu2_isfakeablesel/O");
     tree_new[i]->Branch("mu2_ismvasel",      &_mu2_ismvasel,      "mu2_ismvasel/O");
     tree_new[i]->Branch("mu2_isGenMatched",      &_mu2_isGenMatched,      "mu2_isGenMatched/I");

     tree_new[i]->Branch("ele1_pt",        &_ele1_pt,         "ele1_pt/F");
     tree_new[i]->Branch("ele1_conept",    &_ele1_conept,     "ele1_conept/F");
     tree_new[i]->Branch("ele1_eta",       &_ele1_eta,        "ele1_eta/F");
     tree_new[i]->Branch("ele1_phi",       &_ele1_phi,        "ele1_phi/F");
     tree_new[i]->Branch("ele1_E",         &_ele1_E,          "ele1_E/F");
     tree_new[i]->Branch("ele1_charge",    &_ele1_charge,     "ele1_charge/I");
     tree_new[i]->Branch("ele1_miniRelIso",          &_ele1_miniRelIso,          "ele1_miniRelIso/F");
     tree_new[i]->Branch("ele1_miniIsoCharged",      &_ele1_miniIsoCharged,      "ele1_miniIsoCharged/F");
     tree_new[i]->Branch("ele1_miniIsoNeutral",      &_ele1_miniIsoNeutral,      "ele1_miniIsoNeutral/F");
     tree_new[i]->Branch("ele1_PFRelIso04",    &_ele1_PFRelIso04,    "ele1_PFRelIso04/F");
     tree_new[i]->Branch("ele1_jetNDauChargedMVASel",&_ele1_jetNDauChargedMVASel,"ele1_jetNDauChargedMVASel/I");
     tree_new[i]->Branch("ele1_jetPtRel",  &_ele1_jetPtRel,   "ele1_jetPtRel/F");
     tree_new[i]->Branch("ele1_jetPtRatio",&_ele1_jetPtRatio, "ele1_jetPtRatio/F");
     tree_new[i]->Branch("ele1_jetCSV",    &_ele1_jetCSV,     "ele1_jetCSV/F");
     tree_new[i]->Branch("ele1_jetDeepCSV",    &_ele1_jetDeepCSV,     "ele1_jetDeepCSV/F");
     tree_new[i]->Branch("ele1_jetDeepJet",    &_ele1_jetDeepJet,     "ele1_jetDeepJet/F");
     tree_new[i]->Branch("ele1_sip3D",     &_ele1_sip3D,      "ele1_sip3D/F");
     tree_new[i]->Branch("ele1_dxyAbs",       &_ele1_dxyAbs,        "ele1_dxyAbs/F");
     tree_new[i]->Branch("ele1_dxy",       &_ele1_dxy,        "ele1_dxy/F");
     tree_new[i]->Branch("ele1_dz",        &_ele1_dz,         "ele1_dz/F");
     tree_new[i]->Branch("ele1_ntMVAeleID",&_ele1_ntMVAeleID, "ele1_ntMVAeleID/F");
     tree_new[i]->Branch("ele1_leptonMVA", &_ele1_leptonMVA,  "ele1_leptonMVA/F");
     tree_new[i]->Branch("ele1_isChargeConsistent",   &_ele1_isChargeConsistent,    "ele1_isChargeConsistent/O");
     tree_new[i]->Branch("ele1_passesConversionVeto", &_ele1_passesConversionVeto,  "ele1_passesConversionVeto/O");
     tree_new[i]->Branch("ele1_nMissingHits",  &_ele1_nMissingHits,  "ele1_nMissingHits/I");
     tree_new[i]->Branch("ele1_sigmaEtaEta", &_ele1_sigmaEtaEta, "ele1_sigmaEtaEta/F");
     tree_new[i]->Branch("ele1_HoE", &_ele1_HoE, "ele1_HoE/F");
     tree_new[i]->Branch("ele1_deltaEta", &_ele1_deltaEta, "ele1_deltaEta");
     tree_new[i]->Branch("ele1_deltaPhi", &_ele1_deltaPhi, "ele1_deltaPhi");
     tree_new[i]->Branch("ele1_OoEminusOoP", &_ele1_OoEminusOoP, "ele1_OoEminusOoP");
     tree_new[i]->Branch("ele1_isfakeablesel", &_ele1_isfakeablesel, "ele1_isfakeablesel/O");
     tree_new[i]->Branch("ele1_ismvasel",      &_ele1_ismvasel,      "ele1_ismvasel/O");
     tree_new[i]->Branch("ele1_isGenMatched",  &_ele1_isGenMatched,  "ele1_isGenMatched/I");
  
     tree_new[i]->Branch("ele2_pt",        &_ele2_pt,         "ele2_pt/F");
     tree_new[i]->Branch("ele2_conept",    &_ele2_conept,     "ele2_conept/F");
     tree_new[i]->Branch("ele2_eta",       &_ele2_eta,        "ele2_eta/F");
     tree_new[i]->Branch("ele2_phi",       &_ele2_phi,        "ele2_phi/F");
     tree_new[i]->Branch("ele2_E",         &_ele2_E,          "ele2_E/F");
     tree_new[i]->Branch("ele2_charge",    &_ele2_charge,     "ele2_charge/I");
     tree_new[i]->Branch("ele2_miniRelIso",          &_ele2_miniRelIso,          "ele2_miniRelIso/F");
     tree_new[i]->Branch("ele2_miniIsoCharged",      &_ele2_miniIsoCharged,      "ele2_miniIsoCharged/F");
     tree_new[i]->Branch("ele2_miniIsoNeutral",      &_ele2_miniIsoNeutral,      "ele2_miniIsoNeutral/F");
     tree_new[i]->Branch("ele2_PFRelIso04",    &_ele2_PFRelIso04,    "ele2_PFRelIso04/F");
     tree_new[i]->Branch("ele2_jetNDauChargedMVASel",&_ele2_jetNDauChargedMVASel,"ele2_jetNDauChargedMVASel/I");
     tree_new[i]->Branch("ele2_jetPtRel",  &_ele2_jetPtRel,   "ele2_jetPtRel/F");
     tree_new[i]->Branch("ele2_jetPtRatio",&_ele2_jetPtRatio, "ele2_jetPtRatio/F");
     tree_new[i]->Branch("ele2_jetCSV",    &_ele2_jetCSV,     "ele2_jetCSV/F");
     tree_new[i]->Branch("ele2_jetDeepCSV",    &_ele2_jetDeepCSV,     "ele2_jetDeepCSV/F");
     tree_new[i]->Branch("ele2_jetDeepJet",    &_ele2_jetDeepJet,     "ele2_jetDeepJet/F");
     tree_new[i]->Branch("ele2_sip3D",     &_ele2_sip3D,      "ele2_sip3D/F");
     tree_new[i]->Branch("ele2_dxyAbs",       &_ele2_dxyAbs,        "ele2_dxyAbs/F");
     tree_new[i]->Branch("ele2_dxy",       &_ele2_dxy,        "ele2_dxy/F");
     tree_new[i]->Branch("ele2_dz",        &_ele2_dz,         "ele2_dz/F");
     tree_new[i]->Branch("ele2_ntMVAeleID",&_ele2_ntMVAeleID, "ele2_ntMVAeleID/F");
     tree_new[i]->Branch("ele2_leptonMVA", &_ele2_leptonMVA,  "ele2_leptonMVA/F");
     tree_new[i]->Branch("ele2_isChargeConsistent",   &_ele2_isChargeConsistent,    "ele2_isChargeConsistent/O");
     tree_new[i]->Branch("ele2_passesConversionVeto", &_ele2_passesConversionVeto,  "ele2_passesConversionVeto/O");
     tree_new[i]->Branch("ele2_nMissingHits",  &_ele2_nMissingHits,  "ele2_nMissingHits/I");
     tree_new[i]->Branch("ele2_sigmaEtaEta", &_ele2_sigmaEtaEta, "ele2_sigmaEtaEta/F");
     tree_new[i]->Branch("ele2_HoE", &_ele2_HoE, "ele2_HoE/F");
     tree_new[i]->Branch("ele2_deltaEta", &_ele2_deltaEta, "ele2_deltaEta");
     tree_new[i]->Branch("ele2_deltaPhi", &_ele2_deltaPhi, "ele2_deltaPhi");
     tree_new[i]->Branch("ele2_OoEminusOoP", &_ele2_OoEminusOoP, "ele2_OoEminusOoP");
     tree_new[i]->Branch("ele2_isfakeablesel", &_ele2_isfakeablesel, "ele2_isfakeablesel/O");
     tree_new[i]->Branch("ele2_ismvasel",      &_ele2_ismvasel,      "ele2_ismvasel/O");
     tree_new[i]->Branch("ele2_isGenMatched",  &_ele2_isGenMatched,  "ele2_isGenMatched/I");

     tree_new[i]->Branch("tau1_pt",        &_tau1_pt,         "tau1_pt/F");
     tree_new[i]->Branch("tau1_eta",       &_tau1_eta,        "tau1_eta/F");
     tree_new[i]->Branch("tau1_phi",       &_tau1_phi,        "tau1_phi/F");
     tree_new[i]->Branch("tau1_E",         &_tau1_E,          "tau1_E/F");
     tree_new[i]->Branch("tau1_charge",    &_tau1_charge,     "tau1_charge/I");
     tree_new[i]->Branch("tau1_dxy",       &_tau1_dxy,        "tau1_dxy/F");
     tree_new[i]->Branch("tau1_dz",        &_tau1_dz,         "tau1_dz/F");
     tree_new[i]->Branch("tau1_decayModeFindingOldDMs",                       &_tau1_decayModeFindingOldDMs,                       "tau1_decayModeFindingOldDMs/I");
     tree_new[i]->Branch("tau1_decayModeFindingNewDMs",                       &_tau1_decayModeFindingNewDMs,                       "tau1_decayModeFindingNewDMs/I");
     tree_new[i]->Branch("tau1_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau1_byCombinedIsolationDeltaBetaCorr3Hits,        "tau1_byCombinedIsolationDeltaBetaCorr3Hits/F");
     tree_new[i]->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
     tree_new[i]->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
     tree_new[i]->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
     tree_new[i]->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
     tree_new[i]->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
     tree_new[i]->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
     tree_new[i]->Branch("tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau1_rawMVArun2v1DBdR03oldDMwLT",     &_tau1_rawMVArun2v1DBdR03oldDMwLT,     "tau1_rawMVArun2v1DBdR03oldDMwLT/F");
     tree_new[i]->Branch("tau1_byVVVLooseDeepTau2017v2VSjet" ,&_tau1_byVVVLooseDeepTau2017v2VSjet, "tau1_byVVVLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byVVLooseDeepTau2017v2VSjet" ,&_tau1_byVVLooseDeepTau2017v2VSjet, "tau1_byVVLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byVLooseDeepTau2017v2VSjet" ,&_tau1_byVLooseDeepTau2017v2VSjet, "tau1_byVLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byLooseDeepTau2017v2VSjet" ,&_tau1_byLooseDeepTau2017v2VSjet, "tau1_byLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byMediumDeepTau2017v2VSjet" ,&_tau1_byMediumDeepTau2017v2VSjet, "tau1_byMediumDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byTightDeepTau2017v2VSjet" ,&_tau1_byTightDeepTau2017v2VSjet, "tau1_byTightDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byVTightDeepTau2017v2VSjet" ,&_tau1_byVTightDeepTau2017v2VSjet, "tau1_byVTightDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byVVTightDeepTau2017v2VSjet" ,&_tau1_byVVTightDeepTau2017v2VSjet, "tau1_byVVTightDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau1_byDeepTau2017v2VSjetraw" ,&_tau1_byDeepTau2017v2VSjetraw, "tau1_byDeepTau2017v2VSjetraw/F");
     tree_new[i]->Branch("tau1_againstMuonLoose3",         &_tau1_againstMuonLoose3,         "tau1_againstMuonLoose3/I");                         
     tree_new[i]->Branch("tau1_againstMuonTight3",         &_tau1_againstMuonTight3,         "tau1_againstMuonTight3/I");                         
     tree_new[i]->Branch("tau1_againstElectronVLooseMVA6", &_tau1_againstElectronVLooseMVA6, "tau1_againstElectronVLooseMVA6/I");                         
     tree_new[i]->Branch("tau1_againstElectronLooseMVA6",  &_tau1_againstElectronLooseMVA6,  "tau1_againstElectronLooseMVA6/I");                         
     tree_new[i]->Branch("tau1_againstElectronMediumMVA6", &_tau1_againstElectronMediumMVA6, "tau1_againstElectronMediumMVA6/I");                         
     tree_new[i]->Branch("tau1_againstElectronTightMVA6",  &_tau1_againstElectronTightMVA6,  "tau1_againstElectronTightMVA6/I");   
     tree_new[i]->Branch("tau1_againstElectronVTightMVA6", &_tau1_againstElectronVTightMVA6, "tau1_againstElectronVTightMVA6/I");
     tree_new[i]->Branch("tau1_isGenMatched", &_tau1_isGenMatched, "tau1_isGenMatched/I");

     tree_new[i]->Branch("tau2_pt",        &_tau2_pt,         "tau2_pt/F");
     tree_new[i]->Branch("tau2_eta",       &_tau2_eta,        "tau2_eta/F");
     tree_new[i]->Branch("tau2_phi",       &_tau2_phi,        "tau2_phi/F");
     tree_new[i]->Branch("tau2_E",         &_tau2_E,          "tau2_E/F");
     tree_new[i]->Branch("tau2_charge",    &_tau2_charge,     "tau2_charge/I");
     tree_new[i]->Branch("tau2_dxy",       &_tau2_dxy,        "tau2_dxy/F");
     tree_new[i]->Branch("tau2_dz",        &_tau2_dz,         "tau2_dz/F");
     tree_new[i]->Branch("tau2_decayModeFindingOldDMs",                       &_tau2_decayModeFindingOldDMs,                       "tau2_decayModeFindingOldDMs/I");
     tree_new[i]->Branch("tau2_decayModeFindingNewDMs",                       &_tau2_decayModeFindingNewDMs,                       "tau2_decayModeFindingNewDMs/I");
     tree_new[i]->Branch("tau2_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau2_byCombinedIsolationDeltaBetaCorr3Hits,        "tau2_byCombinedIsolationDeltaBetaCorr3Hits/F");
     tree_new[i]->Branch("tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
     tree_new[i]->Branch("tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
     tree_new[i]->Branch("tau2_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau2_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau2_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
     tree_new[i]->Branch("tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
     tree_new[i]->Branch("tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
     tree_new[i]->Branch("tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
     tree_new[i]->Branch("tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
     tree_new[i]->Branch("tau2_rawMVArun2v1DBdR03oldDMwLT",     &_tau2_rawMVArun2v1DBdR03oldDMwLT,     "tau2_rawMVArun2v1DBdR03oldDMwLT/F");
     tree_new[i]->Branch("tau2_byVVVLooseDeepTau2017v2VSjet" ,&_tau2_byVVVLooseDeepTau2017v2VSjet, "tau2_byVVVLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byVVLooseDeepTau2017v2VSjet" ,&_tau2_byVVLooseDeepTau2017v2VSjet, "tau2_byVVLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byVLooseDeepTau2017v2VSjet" ,&_tau2_byVLooseDeepTau2017v2VSjet, "tau2_byVLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byLooseDeepTau2017v2VSjet" ,&_tau2_byLooseDeepTau2017v2VSjet, "tau2_byLooseDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byMediumDeepTau2017v2VSjet" ,&_tau2_byMediumDeepTau2017v2VSjet, "tau2_byMediumDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byTightDeepTau2017v2VSjet" ,&_tau2_byTightDeepTau2017v2VSjet, "tau2_byTightDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byVTightDeepTau2017v2VSjet" ,&_tau2_byVTightDeepTau2017v2VSjet, "tau2_byVTightDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byVVTightDeepTau2017v2VSjet" ,&_tau2_byVVTightDeepTau2017v2VSjet, "tau2_byVVTightDeepTau2017v2VSjet/I");
     tree_new[i]->Branch("tau2_byDeepTau2017v2VSjetraw" ,&_tau2_byDeepTau2017v2VSjetraw, "tau2_byDeepTau2017v2VSjetraw/F");
     tree_new[i]->Branch("tau2_againstMuonLoose3",         &_tau2_againstMuonLoose3,         "tau2_againstMuonLoose3/I");                         
     tree_new[i]->Branch("tau2_againstMuonTight3",         &_tau2_againstMuonTight3,         "tau2_againstMuonTight3/I");                         
     tree_new[i]->Branch("tau2_againstElectronVLooseMVA6", &_tau2_againstElectronVLooseMVA6, "tau2_againstElectronVLooseMVA6/I");                         
     tree_new[i]->Branch("tau2_againstElectronLooseMVA6",  &_tau2_againstElectronLooseMVA6,  "tau2_againstElectronLooseMVA6/I");                         
     tree_new[i]->Branch("tau2_againstElectronMediumMVA6", &_tau2_againstElectronMediumMVA6, "tau2_againstElectronMediumMVA6/I");                         
     tree_new[i]->Branch("tau2_againstElectronTightMVA6",  &_tau2_againstElectronTightMVA6,  "tau2_againstElectronTightMVA6/I");   
     tree_new[i]->Branch("tau2_againstElectronVTightMVA6", &_tau2_againstElectronVTightMVA6,  "tau2_againstElectronVTightMVA6/I"); 
     tree_new[i]->Branch("tau2_isGenMatched", &_tau2_isGenMatched, "tau2_isGenMatched/I");
                      
     tree_new[i]->Branch("jet1_pt",  &_jet1_pt,  "jet1_pt/F");
     tree_new[i]->Branch("jet1_eta", &_jet1_eta, "jet1_eta/F");
     tree_new[i]->Branch("jet1_phi", &_jet1_phi, "jet1_phi/F");
     tree_new[i]->Branch("jet1_E",   &_jet1_E,   "jet1_E/F");
     tree_new[i]->Branch("jet1_CSV", &_jet1_CSV, "jet1_CSV/F");
     tree_new[i]->Branch("jet1_DeepCSV", &_jet1_DeepCSV, "jet1_DeepCSV/F");
     tree_new[i]->Branch("jet1_DeepJet", &_jet1_DeepJet, "jet1_DeepJet/F");
     tree_new[i]->Branch("jet1_QGdiscr", &_jet1_QGdiscr, "jet1_QGdiscr/F");
             
     tree_new[i]->Branch("jet2_pt",  &_jet2_pt,  "jet2_pt/F");
     tree_new[i]->Branch("jet2_eta", &_jet2_eta, "jet2_eta/F");
     tree_new[i]->Branch("jet2_phi", &_jet2_phi, "jet2_phi/F");
     tree_new[i]->Branch("jet2_E",   &_jet2_E,   "jet2_E/F");
     tree_new[i]->Branch("jet2_CSV", &_jet2_CSV, "jet2_CSV/F");
     tree_new[i]->Branch("jet2_DeepCSV", &_jet2_DeepCSV, "jet2_DeepCSV/F");
     tree_new[i]->Branch("jet2_DeepJet", &_jet2_DeepJet, "jet2_DeepJet/F");
     tree_new[i]->Branch("jet2_QGdiscr", &_jet2_QGdiscr, "jet2_QGdiscr/F");

     tree_new[i]->Branch("jet3_pt",  &_jet3_pt,  "jet3_pt/F");
     tree_new[i]->Branch("jet3_eta", &_jet3_eta, "jet3_eta/F");
     tree_new[i]->Branch("jet3_phi", &_jet3_phi, "jet3_phi/F");
     tree_new[i]->Branch("jet3_E",   &_jet3_E,   "jet3_E/F");
     tree_new[i]->Branch("jet3_CSV", &_jet3_CSV, "jet3_CSV/F");
     tree_new[i]->Branch("jet3_DeepCSV", &_jet3_DeepCSV, "jet3_DeepCSV/F");
     tree_new[i]->Branch("jet3_DeepJet", &_jet3_DeepJet, "jet3_DeepJet/F");
     tree_new[i]->Branch("jet3_QGdiscr", &_jet3_QGdiscr, "jet3_QGdiscr/F");
             
     tree_new[i]->Branch("jet4_pt",  &_jet4_pt,  "jet4_pt/F");
     tree_new[i]->Branch("jet4_eta", &_jet4_eta, "jet4_eta/F");
     tree_new[i]->Branch("jet4_phi", &_jet4_phi, "jet4_phi/F");
     tree_new[i]->Branch("jet4_E",   &_jet4_E,   "jet4_E/F");
     tree_new[i]->Branch("jet4_CSV", &_jet4_CSV, "jet4_CSV/F");
     tree_new[i]->Branch("jet4_DeepCSV", &_jet4_DeepCSV, "jet4_DeepCSV/F");
     tree_new[i]->Branch("jet4_DeepJet", &_jet4_DeepJet, "jet4_DeepJet/F");
     tree_new[i]->Branch("jet4_QGdiscr", &_jet4_QGdiscr, "jet4_QGdiscr/F");

     tree_new[i]->Branch("jetFwd1_pt",  &_jetFwd1_pt,  "jetFwd1_pt/F");
     tree_new[i]->Branch("jetFwd1_eta", &_jetFwd1_eta, "jetFwd1_eta/F");
     tree_new[i]->Branch("jetFwd1_phi", &_jetFwd1_phi, "jetFwd1_phi/F");
     tree_new[i]->Branch("jetFwd1_E",   &_jetFwd1_E,   "jetFwd1_E/F");

     tree_new[i]->Branch("jetFwd2_pt",  &_jetFwd2_pt,  "jetFwd2_pt/F");
     tree_new[i]->Branch("jetFwd2_eta", &_jetFwd2_eta, "jetFwd2_eta/F");
     tree_new[i]->Branch("jetFwd2_phi", &_jetFwd2_phi, "jetFwd2_phi/F");
     tree_new[i]->Branch("jetFwd2_E",   &_jetFwd2_E,   "jetFwd2_E/F");

     tree_new[i]->Branch("jetFwd3_pt",  &_jetFwd3_pt,  "jetFwd3_pt/F");
     tree_new[i]->Branch("jetFwd3_eta", &_jetFwd3_eta, "jetFwd3_eta/F");
     tree_new[i]->Branch("jetFwd3_phi", &_jetFwd3_phi, "jetFwd3_phi/F");
     tree_new[i]->Branch("jetFwd3_E",   &_jetFwd3_E,   "jetFwd3_E/F");

     tree_new[i]->Branch("jetFwd4_pt",  &_jetFwd4_pt,  "jetFwd4_pt/F");
     tree_new[i]->Branch("jetFwd4_eta", &_jetFwd4_eta, "jetFwd4_eta/F");
     tree_new[i]->Branch("jetFwd4_phi", &_jetFwd4_phi, "jetFwd4_phi/F");
     tree_new[i]->Branch("jetFwd4_E",   &_jetFwd4_E,   "jetFwd4_E/F");

     tree_new[i]->Branch("jetAK8_1_pt", &_jetAK8_1_pt, "jetAK8_1_pt/F");
     tree_new[i]->Branch("jetAK8_1_eta", &_jetAK8_1_eta, "jetAK8_1_eta/F");
     tree_new[i]->Branch("jetAK8_1_phi", &_jetAK8_1_phi, "jetAK8_1_phi/F");
     tree_new[i]->Branch("jetAK8_1_E", &_jetAK8_1_E, "jetAK8_1_E/F");
     tree_new[i]->Branch("jetAK8_1_subjet_1_pt", &_jetAK8_1_subjet_1_pt, "jetAK8_1_subjet_1_pt/F");
     tree_new[i]->Branch("jetAK8_1_subjet_1_eta", &_jetAK8_1_subjet_1_eta, "jetAK8_1_subjet_1_eta/F");
     tree_new[i]->Branch("jetAK8_1_subjet_1_phi", &_jetAK8_1_subjet_1_phi, "jetAK8_1_subjet_1_phi/F");
     tree_new[i]->Branch("jetAK8_1_subjet_1_E", &_jetAK8_1_subjet_1_E, "jetAK8_1_subjet_1_E/F");
     tree_new[i]->Branch("jetAK8_1_subjet_2_pt", &_jetAK8_1_subjet_2_pt, "jetAK8_1_subjet_2_pt/F");
     tree_new[i]->Branch("jetAK8_1_subjet_2_eta", &_jetAK8_1_subjet_2_eta, "jetAK8_1_subjet_2_eta/F");
     tree_new[i]->Branch("jetAK8_1_subjet_2_phi", &_jetAK8_1_subjet_2_phi, "jetAK8_1_subjet_2_phi/F");
     tree_new[i]->Branch("jetAK8_1_subjet_2_E", &_jetAK8_1_subjet_2_E, "jetAK8_1_subjet_2_E/F");
     tree_new[i]->Branch("jetAK8_1_SDmass", &_jetAK8_1_SDmass, "jetAK8_1_SDmass/F");
     tree_new[i]->Branch("jetAK8_1_tau1", &_jetAK8_1_tau1, "jetAK8_1_tau1/F");
     tree_new[i]->Branch("jetAK8_1_tau2", &_jetAK8_1_tau2, "jetAK8_1_tau2/F");
 
     tree_new[i]->Branch("jetAK8_2_pt", &_jetAK8_2_pt, "jetAK8_2_pt/F");
     tree_new[i]->Branch("jetAK8_2_eta", &_jetAK8_2_eta, "jetAK8_2_eta/F");
     tree_new[i]->Branch("jetAK8_2_phi", &_jetAK8_2_phi, "jetAK8_2_phi/F");
     tree_new[i]->Branch("jetAK8_2_E", &_jetAK8_2_E, "jetAK8_2_E/F");
     tree_new[i]->Branch("jetAK8_2_subjet_1_pt", &_jetAK8_2_subjet_1_pt, "jetAK8_2_subjet_1_pt/F");
     tree_new[i]->Branch("jetAK8_2_subjet_1_eta", &_jetAK8_2_subjet_1_eta, "jetAK8_2_subjet_1_eta/F");
     tree_new[i]->Branch("jetAK8_2_subjet_1_phi", &_jetAK8_2_subjet_1_phi, "jetAK8_2_subjet_1_phi/F");
     tree_new[i]->Branch("jetAK8_2_subjet_1_E", &_jetAK8_2_subjet_1_E, "jetAK8_2_subjet_1_E/F");
     tree_new[i]->Branch("jetAK8_2_subjet_2_pt", &_jetAK8_2_subjet_2_pt, "jetAK8_2_subjet_2_pt/F");
     tree_new[i]->Branch("jetAK8_2_subjet_2_eta", &_jetAK8_2_subjet_2_eta, "jetAK8_2_subjet_2_eta/F");
     tree_new[i]->Branch("jetAK8_2_subjet_2_phi", &_jetAK8_2_subjet_2_phi, "jetAK8_2_subjet_2_phi/F");
     tree_new[i]->Branch("jetAK8_2_subjet_2_E", &_jetAK8_2_subjet_2_E, "jetAK8_2_subjet_2_E/F");
     tree_new[i]->Branch("jetAK8_2_SDmass", &_jetAK8_2_SDmass, "jetAK8_2_SDmass/F");
     tree_new[i]->Branch("jetAK8_2_tau1", &_jetAK8_2_tau1, "jetAK8_2_tau1/F");
     tree_new[i]->Branch("jetAK8_2_tau2", &_jetAK8_2_tau2, "jetAK8_2_tau2/F");
               
     tree_new[i]->Branch("PFMET",    &_PFMET,    "PFMET/F");
     tree_new[i]->Branch("PFMETphi", &_PFMETphi, "PFMETphi/F");
     tree_new[i]->Branch("MHT",      &_MHT,      "MHT/F");
     tree_new[i]->Branch("metLD",    &_metLD,    "metLD/F");

  }


  int _category;
  int _n_recotauh_sel;

  vector<float> *_recomu_pt;
  vector<float> *_recomu_conept;
  vector<float> *_recomu_eta;
  vector<float> *_recomu_phi;
  vector<float> *_recomu_e;
  vector<int>   *_recomu_charge;
  vector<int>   *_recomu_jetNDauChargedMVASel;
  vector<int>   *_recomu_jetNDauChargedMVASel_nanoAOD;
  vector<float> *_recomu_miniRelIso;
  vector<float> *_recomu_miniRelIso_nanoAOD;
  vector<float> *_recomu_miniIsoCharged;
  vector<float> *_recomu_miniIsoCharged_nanoAOD;
  vector<float> *_recomu_miniIsoNeutral;
  vector<float> *_recomu_miniIsoNeutral_nanoAOD;
  vector<float> *_recomu_combreliso04;
  vector<float> *_recomu_jetPtRel;
  vector<float> *_recomu_jetPtRel_nanoAOD;
  vector<float> *_recomu_jetPtRatio;
  vector<float> *_recomu_jetPtRatio_nanoAOD;
  vector<float> *_recomu_jetCSV;
  vector<float> *_recomu_jetDeepCSV;
  vector<float> *_recomu_jetDeepJet;
  vector<float> *_recomu_sip3D;
  vector<float> *_recomu_dxy;
  vector<float> *_recomu_dz;
  vector<float> *_recomu_lepMVA_Id;
  vector<float> *_recomu_leptonMVA;
  vector<bool>  *_recomu_mediumID;
  vector<float> *_recomu_rel_error_trackpt;
  vector<bool>  *_recomu_isfakeable;
  vector<bool>  *_recomu_ismvasel;
  vector<bool>  *_recomu_isGenMatched;

  vector<float> *_recoele_pt;
  vector<float> *_recoele_corr_pt;
  vector<float> *_recoele_conept;
  vector<float> *_recoele_eta;
  vector<float> *_recoele_phi;
  vector<float> *_recoele_e;
  vector<float> *_recoele_corr_e;
  vector<int>   *_recoele_charge;
  vector<int>   *_recoele_jetNDauChargedMVASel;
  vector<int>   *_recoele_jetNDauChargedMVASel_nanoAOD;
  vector<float> *_recoele_miniRelIso;
  vector<float> *_recoele_miniRelIso_nanoAOD;
  vector<float> *_recoele_miniIsoCharged;
  vector<float> *_recoele_miniIsoCharged_nanoAOD;
  vector<float> *_recoele_miniIsoNeutral;
  vector<float> *_recoele_miniIsoNeutral_nanoAOD;
  vector<float> *_recoele_PFRelIsoAll04_nanoAOD;
  vector<float> *_recoele_jetPtRel;
  vector<float> *_recoele_jetPtRel_nanoAOD;
  vector<float> *_recoele_jetPtRatio;
  vector<float> *_recoele_jetPtRatio_nanoAOD;
  vector<float> *_recoele_jetCSV;
  vector<float> *_recoele_jetDeepCSV;
  vector<float> *_recoele_jetDeepJet;
  vector<float> *_recoele_sip3D;
  vector<float> *_recoele_dxy;
  vector<float> *_recoele_dz;
  vector<float> *_recoele_lepMVA_Id;
  vector<float> *_recoele_leptonMVA;
  vector<bool>  *_recoele_isChargeConsistent;
  vector<bool>  *_recoele_passConversionVeto;
  vector<int>   *_recoele_nMissingHits;
  vector<float> *_recoele_sigmaEtaEta;
  vector<float> *_recoele_HoE;
  vector<float> *_recoele_deltaEta;
  vector<float> *_recoele_deltaPhi;
  vector<float> *_recoele_OoEminusOoP;
  vector<bool>  *_recoele_isfakeable;
  vector<bool>  *_recoele_ismvasel;
  vector<bool>  *_recoele_isGenMatched;

  vector<float> *_recotauh_pt;
  vector<float> *_recotauh_eta;
  vector<float> *_recotauh_phi;
  vector<float> *_recotauh_e;
  vector<int>   *_recotauh_charge;
  vector<float> *_recotauh_dxy;
  vector<float> *_recotauh_dz;
  vector<float> *_recotauh_iso;
  vector<int>   *_recotauh_decayModeFindingOldDMs;
  vector<int>   *_recotauh_decayModeFindingNewDMs;
  vector<int>   *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   *_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   *_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   *_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   *_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   *_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<float> *_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw;
  vector<int>   *_recotauh_byVVVLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVVLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byLooseDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byMediumDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byTightDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVTightDeepTau2017v2VSjet;
  vector<int>   *_recotauh_byVVTightDeepTau2017v2VSjet;
  vector<float> *_recotauh_byDeepTau2017v2VSjetraw;
  vector<int>   *_recotauh_againstMuonLoose3;
  vector<int>   *_recotauh_againstMuonTight3;
  vector<int>   *_recotauh_againstElectronVLooseMVA6;
  vector<int>   *_recotauh_againstElectronLooseMVA6;
  vector<int>   *_recotauh_againstElectronMediumMVA6;
  vector<int>   *_recotauh_againstElectronTightMVA6;
  vector<int>   *_recotauh_againstElectronVTightMVA6;
  vector<bool>  *_recotauh_isGenMatched;

  vector<float> *_recoPFJet_pt;
  vector<float> *_recoPFJet_eta;
  vector<float> *_recoPFJet_phi;
  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_CSVscore;
  vector<float> *_recoPFJet_DeepCSVscore;
  vector<float> *_recoPFJet_DeepJetscore;
  vector<float> *_recoPFJet_QGdiscr;

  vector<float> *_recoPFFwdJet_pt;
  vector<float> *_recoPFFwdJet_eta;
  vector<float> *_recoPFFwdJet_phi;
  vector<float> *_recoPFFwdJet_e;

  vector<float> *_recoPFak8Jet_e;
  vector<float> *_recoPFak8Jet_pt;
  vector<float> *_recoPFak8Jet_eta;
  vector<float> *_recoPFak8Jet_phi;
  vector<float> *_recoPFak8Jet_SoftDropMass;
  vector<float> *_recoPFak8Jet_tau1;
  vector<float> *_recoPFak8Jet_tau2;
  vector<int>   *_recoPFak8Jet_nsubjets;

  vector<float> *_recoPFak8Jet_subjet1_e;
  vector<float> *_recoPFak8Jet_subjet1_pt;
  vector<float> *_recoPFak8Jet_subjet1_eta;
  vector<float> *_recoPFak8Jet_subjet1_phi;

  vector<float> *_recoPFak8Jet_subjet2_e;
  vector<float> *_recoPFak8Jet_subjet2_pt;
  vector<float> *_recoPFak8Jet_subjet2_eta;
  vector<float> *_recoPFak8Jet_subjet2_phi;


  for(unsigned int i=0;i<tree.size();i++){

    tree[i]->SetBranchAddress("category",&_category);
    tree[i]->SetBranchAddress("is_ttH_like",&_is_ttH_like);
    tree[i]->SetBranchAddress("is_tH_like_and_not_ttH_like",&_is_tH_like_and_not_ttH_like);

    tree[i]->SetBranchAddress("n_recotauh_sel",&_n_recotauh_sel);

    tree[i]->SetBranchAddress("EventNumber",&_nEvent);
    tree[i]->SetBranchAddress("lumi",&_ls);
    tree[i]->SetBranchAddress("RunNumber",&_run);

    tree[i]->SetBranchAddress("n_recomu_presel",&_n_presel_mu);
    tree[i]->SetBranchAddress("n_recomu_fakeable",&_n_fakeablesel_mu);
    tree[i]->SetBranchAddress("n_recomu_mvasel",&_n_mvasel_mu);

    tree[i]->SetBranchAddress("n_recoele_presel",&_n_presel_ele);
    tree[i]->SetBranchAddress("n_recoele_fakeable",&_n_fakeablesel_ele);
    tree[i]->SetBranchAddress("n_recoele_mvasel",&_n_mvasel_ele);

    tree[i]->SetBranchAddress("n_recotauh",&_n_presel_tau);
    tree[i]->SetBranchAddress("n_recoPFJet",&_n_presel_jet);
    tree[i]->SetBranchAddress("n_recoPFFwdJet",&_n_presel_jetFwd);
    tree[i]->SetBranchAddress("n_recoPFak8Jet",&_n_presel_jetAK8);

    tree[i]->SetBranchAddress("recomu_pt",                   &_recomu_pt);
    tree[i]->SetBranchAddress("recomu_conept",               &_recomu_conept);
    tree[i]->SetBranchAddress("recomu_eta",                  &_recomu_eta);
    tree[i]->SetBranchAddress("recomu_phi",                  &_recomu_phi);
    tree[i]->SetBranchAddress("recomu_e",                    &_recomu_e);
    tree[i]->SetBranchAddress("recomu_charge",               &_recomu_charge);
    tree[i]->SetBranchAddress("recomu_jetNDauChargedMVASel", &_recomu_jetNDauChargedMVASel);
    tree[i]->SetBranchAddress("recomu_jetNDauChargedMVASel_nanoAOD", &_recomu_jetNDauChargedMVASel_nanoAOD);
    tree[i]->SetBranchAddress("recomu_miniRelIso",           &_recomu_miniRelIso);
    tree[i]->SetBranchAddress("recomu_miniRelIso_nanoAOD",      &_recomu_miniRelIso_nanoAOD);
    tree[i]->SetBranchAddress("recomu_miniIsoCharged",       &_recomu_miniIsoCharged);
    tree[i]->SetBranchAddress("recomu_miniIsoCharged_nanoAOD",         &_recomu_miniIsoCharged_nanoAOD);
    tree[i]->SetBranchAddress("recomu_miniIsoNeutral",       &_recomu_miniIsoNeutral);
    tree[i]->SetBranchAddress("recomu_miniIsoNeutral_nanoAOD",       &_recomu_miniIsoNeutral_nanoAOD);
    tree[i]->SetBranchAddress("recomu_jetPtRel",             &_recomu_jetPtRel);
    tree[i]->SetBranchAddress("recomu_jetPtRel_nanoAOD",     &_recomu_jetPtRel_nanoAOD);
    tree[i]->SetBranchAddress("recomu_jetPtRatio",           &_recomu_jetPtRatio);
    tree[i]->SetBranchAddress("recomu_jetPtRatio_nanoAOD",   &_recomu_jetPtRatio_nanoAOD);
    tree[i]->SetBranchAddress("recomu_combreliso04",         &_recomu_combreliso04);
    tree[i]->SetBranchAddress("recomu_jetCSV",               &_recomu_jetCSV);
    tree[i]->SetBranchAddress("recomu_jetDeepCSV",           &_recomu_jetDeepCSV);
    tree[i]->SetBranchAddress("recomu_jetDeepJet",           &_recomu_jetDeepJet);
    tree[i]->SetBranchAddress("recomu_sip3D",                &_recomu_sip3D);
    tree[i]->SetBranchAddress("recomu_dxy",                  &_recomu_dxy);
    tree[i]->SetBranchAddress("recomu_dz",                   &_recomu_dz);
    tree[i]->SetBranchAddress("recomu_lepMVA_Id",            &_recomu_lepMVA_Id);
    tree[i]->SetBranchAddress("recomu_leptonMVA",            &_recomu_leptonMVA);
    tree[i]->SetBranchAddress("recomu_mediumID",             &_recomu_mediumID);
    tree[i]->SetBranchAddress("recomu_rel_error_trackpt",    &_recomu_rel_error_trackpt);
    tree[i]->SetBranchAddress("recomu_isfakeable",           &_recomu_isfakeable);
    tree[i]->SetBranchAddress("recomu_ismvasel",             &_recomu_ismvasel);
    tree[i]->SetBranchAddress("recomu_isGenMatched",         &_recomu_isGenMatched);

    tree[i]->SetBranchAddress("recoele_pt",                  &_recoele_pt);
    tree[i]->SetBranchAddress("recoele_corr_pt",             &_recoele_corr_pt);
    tree[i]->SetBranchAddress("recoele_conept",              &_recoele_conept);
    tree[i]->SetBranchAddress("recoele_eta",                 &_recoele_eta);
    tree[i]->SetBranchAddress("recoele_phi",                 &_recoele_phi);
    tree[i]->SetBranchAddress("recoele_e",                   &_recoele_e);
    tree[i]->SetBranchAddress("recoele_corr_e",              &_recoele_corr_e);
    tree[i]->SetBranchAddress("recoele_charge",              &_recoele_charge);
    tree[i]->SetBranchAddress("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
    tree[i]->SetBranchAddress("recoele_jetNDauChargedMVASel_nanoAOD",&_recoele_jetNDauChargedMVASel_nanoAOD);
    tree[i]->SetBranchAddress("recoele_miniRelIso",          &_recoele_miniRelIso);
    tree[i]->SetBranchAddress("recoele_miniRelIso_nanoAOD",     &_recoele_miniRelIso_nanoAOD);
    tree[i]->SetBranchAddress("recoele_miniIsoCharged",      &_recoele_miniIsoCharged);
    tree[i]->SetBranchAddress("recoele_miniIsoCharged_nanoAOD",        &_recoele_miniIsoCharged_nanoAOD);
    tree[i]->SetBranchAddress("recoele_miniIsoNeutral",      &_recoele_miniIsoNeutral);
    tree[i]->SetBranchAddress("recoele_miniIsoNeutral_nanoAOD",      &_recoele_miniIsoNeutral_nanoAOD);
    tree[i]->SetBranchAddress("recoele_PFRelIsoAll04_nanoAOD",     &_recoele_PFRelIsoAll04_nanoAOD);
    tree[i]->SetBranchAddress("recoele_jetPtRel",            &_recoele_jetPtRel);
    tree[i]->SetBranchAddress("recoele_jetPtRel_nanoAOD",          &_recoele_jetPtRel_nanoAOD);
    tree[i]->SetBranchAddress("recoele_jetPtRatio",          &_recoele_jetPtRatio);
    tree[i]->SetBranchAddress("recoele_jetPtRatio_nanoAOD",        &_recoele_jetPtRatio_nanoAOD);
    tree[i]->SetBranchAddress("recoele_jetCSV",              &_recoele_jetCSV);
    tree[i]->SetBranchAddress("recoele_jetDeepCSV",          &_recoele_jetDeepCSV);
    tree[i]->SetBranchAddress("recoele_jetDeepJet",          &_recoele_jetDeepJet);
    tree[i]->SetBranchAddress("recoele_sip3D",               &_recoele_sip3D);
    tree[i]->SetBranchAddress("recoele_dxy",                 &_recoele_dxy);
    tree[i]->SetBranchAddress("recoele_dz",                  &_recoele_dz);
    tree[i]->SetBranchAddress("recoele_lepMVA_Id",           &_recoele_lepMVA_Id);
    tree[i]->SetBranchAddress("recoele_leptonMVA",           &_recoele_leptonMVA);
    tree[i]->SetBranchAddress("recoele_isChargeConsistent",  &_recoele_isChargeConsistent);
    tree[i]->SetBranchAddress("recoele_passConversionVeto",  &_recoele_passConversionVeto);
    tree[i]->SetBranchAddress("recoele_nMissingHits",        &_recoele_nMissingHits);
    tree[i]->SetBranchAddress("recoele_isfakeable",          &_recoele_isfakeable);
    tree[i]->SetBranchAddress("recoele_ismvasel",            &_recoele_ismvasel);
    tree[i]->SetBranchAddress("recoele_HoE",                 &_recoele_HoE);
    tree[i]->SetBranchAddress("recoele_sigmaEtaEta",         &_recoele_sigmaEtaEta);
    tree[i]->SetBranchAddress("recoele_deltaEta",    &_recoele_deltaEta);
    tree[i]->SetBranchAddress("recoele_deltaPhi",    &_recoele_deltaPhi);
    tree[i]->SetBranchAddress("recoele_OoEminusOoP",   &_recoele_OoEminusOoP);
    tree[i]->SetBranchAddress("recoele_isGenMatched",  &_recoele_isGenMatched);

    tree[i]->SetBranchAddress("recotauh_pt",                 &_recotauh_pt);
    tree[i]->SetBranchAddress("recotauh_eta",                &_recotauh_eta);
    tree[i]->SetBranchAddress("recotauh_phi",                &_recotauh_phi);
    tree[i]->SetBranchAddress("recotauh_e",                  &_recotauh_e);
    tree[i]->SetBranchAddress("recotauh_charge",             &_recotauh_charge);
    tree[i]->SetBranchAddress("recotauh_dxy",                &_recotauh_dxy);
    tree[i]->SetBranchAddress("recotauh_dz",                 &_recotauh_dz);
    tree[i]->SetBranchAddress("recotauh_iso",                &_recotauh_iso);
    tree[i]->SetBranchAddress("recotauh_decayModeFindingOldDMs", &_recotauh_decayModeFindingOldDMs);
    tree[i]->SetBranchAddress("recotauh_decayModeFindingNewDMs", &_recotauh_decayModeFindingNewDMs);
    tree[i]->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",     &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT", &_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw", &_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw); 
    tree[i]->SetBranchAddress("recotauh_byVVVLooseDeepTau2017v2VSjet", &_recotauh_byVVVLooseDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byVVLooseDeepTau2017v2VSjet", &_recotauh_byVVLooseDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byVLooseDeepTau2017v2VSjet", &_recotauh_byVLooseDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byLooseDeepTau2017v2VSjet", &_recotauh_byLooseDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byMediumDeepTau2017v2VSjet", &_recotauh_byMediumDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byTightDeepTau2017v2VSjet", &_recotauh_byTightDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byVTightDeepTau2017v2VSjet", &_recotauh_byVTightDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byVVTightDeepTau2017v2VSjet", &_recotauh_byVVTightDeepTau2017v2VSjet);
    tree[i]->SetBranchAddress("recotauh_byDeepTau2017v2VSjetraw", &_recotauh_byDeepTau2017v2VSjetraw);
    tree[i]->SetBranchAddress("recotauh_againstMuonLoose3",           &_recotauh_againstMuonLoose3);
    tree[i]->SetBranchAddress("recotauh_againstMuonTight3",           &_recotauh_againstMuonTight3);
    tree[i]->SetBranchAddress("recotauh_againstElectronVLooseMVA6",   &_recotauh_againstElectronVLooseMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronLooseMVA6",    &_recotauh_againstElectronLooseMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronMediumMVA6",   &_recotauh_againstElectronMediumMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronTightMVA6",    &_recotauh_againstElectronTightMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronVTightMVA6",   &_recotauh_againstElectronVTightMVA6);
    tree[i]->SetBranchAddress("recotauh_isGenMatched", &_recotauh_isGenMatched);

    tree[i]->SetBranchAddress("recoPFJet_pt",       &_recoPFJet_pt);
    tree[i]->SetBranchAddress("recoPFJet_eta",      &_recoPFJet_eta);
    tree[i]->SetBranchAddress("recoPFJet_phi",      &_recoPFJet_phi);
    tree[i]->SetBranchAddress("recoPFJet_e",        &_recoPFJet_e);
    tree[i]->SetBranchAddress("recoPFJet_CSVscore", &_recoPFJet_CSVscore);
    tree[i]->SetBranchAddress("recoPFJet_DeepCSVscore", &_recoPFJet_DeepCSVscore);
    tree[i]->SetBranchAddress("recoPFJet_DeepJetscore", &_recoPFJet_DeepJetscore);
    tree[i]->SetBranchAddress("recoPFJet_QGdiscr",  &_recoPFJet_QGdiscr);

    tree[i]->SetBranchAddress("recoPFFwdJet_pt",       &_recoPFFwdJet_pt);
    tree[i]->SetBranchAddress("recoPFFwdJet_eta",      &_recoPFFwdJet_eta);
    tree[i]->SetBranchAddress("recoPFFwdJet_phi",      &_recoPFFwdJet_phi);
    tree[i]->SetBranchAddress("recoPFFwdJet_e",        &_recoPFFwdJet_e);

    tree[i]->SetBranchAddress("recoPFak8Jet_e", &_recoPFak8Jet_e);
    tree[i]->SetBranchAddress("recoPFak8Jet_pt", &_recoPFak8Jet_pt);
    tree[i]->SetBranchAddress("recoPFak8Jet_eta", &_recoPFak8Jet_eta);
    tree[i]->SetBranchAddress("recoPFak8Jet_phi", &_recoPFak8Jet_phi);
    tree[i]->SetBranchAddress("recoPFak8Jet_SoftDropMass", &_recoPFak8Jet_SoftDropMass);
    tree[i]->SetBranchAddress("recoPFak8Jet_tau1", &_recoPFak8Jet_tau1);
    tree[i]->SetBranchAddress("recoPFak8Jet_tau2", &_recoPFak8Jet_tau2);
    tree[i]->SetBranchAddress("recoPFak8Jet_nsubjets", &_recoPFak8Jet_nsubjets);

    tree[i]->SetBranchAddress("recoPFak8Jet_subjet1_e", &_recoPFak8Jet_subjet1_e);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet1_pt", &_recoPFak8Jet_subjet1_pt);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet1_eta", &_recoPFak8Jet_subjet1_eta);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet1_phi", &_recoPFak8Jet_subjet1_phi);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet2_e", &_recoPFak8Jet_subjet2_e);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet2_pt", &_recoPFak8Jet_subjet2_pt);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet2_eta", &_recoPFak8Jet_subjet2_eta);
    tree[i]->SetBranchAddress("recoPFak8Jet_subjet2_phi", &_recoPFak8Jet_subjet2_phi);

    tree[i]->SetBranchAddress("PFMET",&_PFMET);
    tree[i]->SetBranchAddress("PFMET_phi",&_PFMETphi);
    tree[i]->SetBranchAddress("HTmiss",&_MHT);
    tree[i]->SetBranchAddress("ETmissLD",&_metLD);

  }

  for(unsigned int i_tree=0; i_tree<tree.size(); i_tree++){

  Long64_t nentries = tree[i_tree]->GetEntries();

  //nentries = 100;
  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _nEvent       = -9999;
    _ls           = -9999;
    _run          = -9999;

    _n_presel_mu  = -9999;
    _n_fakeablesel_mu  = -9999;
    _n_mvasel_mu  = -9999;

    _n_presel_ele = -9999;
    _n_fakeablesel_ele  = -9999;
    _n_mvasel_ele  = -9999;

    _n_presel_tau = -9999;
    _n_presel_jet = -9999;
    _n_presel_jetFwd = -9999;
    _n_presel_jetAK8 = -9999;

    _mu1_pt       = -9999;
    _mu1_conept   = -9999;
    _mu1_eta      = -9999;
    _mu1_phi      = -9999;
    _mu1_E        = -9999;
    _mu1_charge   = -9999;
    _mu1_jetNDauChargedMVASel = -9999;
    _mu1_miniRelIso           = -9999;
    _mu1_miniIsoCharged       = -9999;
    _mu1_miniIsoNeutral       = -9999;
    _mu1_PFRelIso04           = -9999;
    _mu1_jetPtRel             = -9999;
    _mu1_jetPtRatio           = -9999;
    _mu1_jetCSV               = -9999;
    _mu1_jetDeepCSV           = -9999;
    _mu1_jetDeepJet           = -9999;
    _mu1_sip3D                = -9999;
    _mu1_dxy                  = -9999;
    _mu1_dxyAbs               = -9999;
    _mu1_dz                   = -9999;
    _mu1_segmentCompatibility = -9999;
    _mu1_leptonMVA            = -9999;
    _mu1_mediumID = 0;
    _mu1_dpt_div_pt = -9999;
    _mu1_isfakeablesel = 0;
    _mu1_ismvasel = 0;
    _mu1_isGenMatched = -9999;

    _mu2_pt       = -9999;
    _mu2_conept   = -9999;
    _mu2_eta      = -9999;
    _mu2_phi      = -9999;
    _mu2_E        = -9999;
    _mu2_charge   = -9999;
    _mu2_jetNDauChargedMVASel = -9999;
    _mu2_miniRelIso           = -9999;
    _mu2_miniIsoCharged       = -9999;
    _mu2_miniIsoNeutral       = -9999;
    _mu2_PFRelIso04 = -9999;
    _mu2_jetPtRel             = -9999;
    _mu2_jetPtRatio           = -9999;
    _mu2_jetCSV               = -9999;
    _mu2_jetDeepCSV           = -9999;
    _mu2_jetDeepJet           = -9999;
    _mu2_sip3D                = -9999;
    _mu2_dxy                  = -9999;
    _mu2_dxyAbs               = -9999;
    _mu2_dz                   = -9999;
    _mu2_segmentCompatibility = -9999;
    _mu2_leptonMVA            = -9999;
    _mu2_mediumID = 0;
    _mu2_dpt_div_pt = -9999;
    _mu2_isfakeablesel = 0;
    _mu2_ismvasel = 0;
    _mu2_isGenMatched = -9999;


    _ele1_pt       = -9999;
    _ele1_conept   = -9999;
    _ele1_eta      = -9999;
    _ele1_phi      = -9999;
    _ele1_E        = -9999;
    _ele1_charge   = -9999;
    _ele1_jetNDauChargedMVASel = -9999;
    _ele1_miniRelIso           = -9999;
    _ele1_miniIsoCharged       = -9999;
    _ele1_miniIsoNeutral       = -9999;
    _ele1_PFRelIso04           = -9999;
    _ele1_jetPtRel             = -9999;
    _ele1_jetPtRatio           = -9999;
    _ele1_jetCSV               = -9999;
    _ele1_jetDeepCSV           = -9999;
    _ele1_jetDeepJet           = -9999;
    _ele1_sip3D                = -9999;
    _ele1_dxy                  = -9999;
    _ele1_dxyAbs               = -9999;
    _ele1_dz                   = -9999;
    _ele1_ntMVAeleID           = -9999;
    _ele1_leptonMVA            = -9999;
    _ele1_isChargeConsistent   = 0;
    _ele1_passesConversionVeto = 0;
    _ele1_nMissingHits         = -9999;
    _ele1_sigmaEtaEta          = -9999;
    _ele1_HoE                  = -9999;
    _ele1_deltaEta             = -9999;
    _ele1_deltaPhi             = -9999;
    _ele1_OoEminusOoP          = -9999;
    _ele1_isfakeablesel        = 0;
    _ele1_ismvasel             = 0;
    _ele1_isGenMatched         = -9999;

    _ele2_pt       = -9999;
    _ele2_conept   = -9999;
    _ele2_eta      = -9999;
    _ele2_phi      = -9999;
    _ele2_E        = -9999;
    _ele2_charge   = -9999;
    _ele2_jetNDauChargedMVASel = -9999;
    _ele2_miniRelIso           = -9999;
    _ele2_miniIsoCharged       = -9999;
    _ele2_miniIsoNeutral       = -9999;
    _ele2_PFRelIso04           = -9999;
    _ele2_jetPtRel             = -9999;
    _ele2_jetPtRatio           = -9999;
    _ele2_jetCSV               = -9999;
    _ele2_jetDeepCSV           = -9999;
    _ele2_jetDeepJet           = -9999;
    _ele2_sip3D                = -9999;
    _ele2_dxy                  = -9999;
    _ele2_dxyAbs               = -9999;
    _ele2_dz                   = -9999;
    _ele2_ntMVAeleID           = -9999;
    _ele2_leptonMVA            = -9999;
    _ele2_isChargeConsistent   = 0;
    _ele2_passesConversionVeto = 0;
    _ele2_nMissingHits         = -9999;
    _ele2_sigmaEtaEta          = -9999;
    _ele2_HoE                  = -9999;
    _ele2_deltaEta             = -9999;
    _ele2_deltaPhi             = -9999;
    _ele2_OoEminusOoP          = -9999;
    _ele2_isfakeablesel        = 0;
    _ele2_ismvasel             = 0;
    _ele2_isGenMatched         = -9999;

    _tau1_pt       = -9999;
    _tau1_eta      = -9999;
    _tau1_phi      = -9999;
    _tau1_E        = -9999;
    _tau1_charge   = -9999;    
    _tau1_dxy      = -9999;
    _tau1_dz       = -9999;
    _tau1_decayModeFindingOldDMs                           = -9999;
    _tau1_decayModeFindingNewDMs                           = -9999;
    _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_rawMVArun2v1DBdR03oldDMwLT                       = -9999;
    _tau1_byVVVLooseDeepTau2017v2VSjet = -9999;
    _tau1_byVVLooseDeepTau2017v2VSjet = -9999;
    _tau1_byVLooseDeepTau2017v2VSjet = -9999;
    _tau1_byLooseDeepTau2017v2VSjet = -9999;
    _tau1_byMediumDeepTau2017v2VSjet = -9999;
    _tau1_byTightDeepTau2017v2VSjet = -9999;
    _tau1_byVTightDeepTau2017v2VSjet = -9999;
    _tau1_byVVTightDeepTau2017v2VSjet = -9999;
    _tau1_byDeepTau2017v2VSjetraw = -9999;    
    _tau1_againstMuonLoose3          = -9999;
    _tau1_againstMuonTight3          = -9999;
    _tau1_againstElectronVLooseMVA6  = -9999;
    _tau1_againstElectronLooseMVA6   = -9999;
    _tau1_againstElectronMediumMVA6  = -9999;
    _tau1_againstElectronTightMVA6   = -9999;
    _tau1_againstElectronVTightMVA6  = -9999;
    _tau1_isGenMatched = -9999;  

    _tau2_pt       = -9999;
    _tau2_eta      = -9999;
    _tau2_phi      = -9999;
    _tau2_E        = -9999;
    _tau2_charge   = -9999;    
    _tau2_dxy      = -9999;
    _tau2_dz       = -9999;
    _tau2_decayModeFindingOldDMs                           = -9999;
    _tau2_decayModeFindingNewDMs                           = -9999;
    _tau2_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau2_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau2_rawMVArun2v1DBdR03oldDMwLT                       = -9999;
    _tau2_byVVVLooseDeepTau2017v2VSjet = -9999;
    _tau2_byVVLooseDeepTau2017v2VSjet = -9999;
    _tau2_byVLooseDeepTau2017v2VSjet = -9999;
    _tau2_byLooseDeepTau2017v2VSjet = -9999;
    _tau2_byMediumDeepTau2017v2VSjet = -9999;
    _tau2_byTightDeepTau2017v2VSjet = -9999;
    _tau2_byVTightDeepTau2017v2VSjet = -9999;
    _tau2_byVVTightDeepTau2017v2VSjet = -9999;
    _tau2_byDeepTau2017v2VSjetraw = -9999;    
    _tau2_againstMuonLoose3          = -9999;
    _tau2_againstMuonTight3          = -9999;
    _tau2_againstElectronVLooseMVA6  = -9999;
    _tau2_againstElectronLooseMVA6   = -9999;
    _tau2_againstElectronMediumMVA6  = -9999;
    _tau2_againstElectronTightMVA6   = -9999;
    _tau2_againstElectronVTightMVA6  = -9999;
    _tau2_isGenMatched = -9999;   
 
    _jet1_pt   = -9999;
    _jet1_eta  = -9999;
    _jet1_phi  = -9999;
    _jet1_E    = -9999;
    _jet1_CSV  = -9999;
    _jet1_DeepCSV  = -9999;
    _jet1_DeepJet = -9999;
    _jet1_QGdiscr  = -9999;

    _jet2_pt   = -9999;
    _jet2_eta  = -9999;
    _jet2_phi  = -9999;
    _jet2_E    = -9999;
    _jet2_CSV  = -9999;
    _jet2_DeepCSV  = -9999;
    _jet2_DeepJet = -9999;
    _jet2_QGdiscr  = -9999;

    _jet3_pt   = -9999;
    _jet3_eta  = -9999;
    _jet3_phi  = -9999;
    _jet3_E    = -9999;
    _jet3_CSV  = -9999;
    _jet3_DeepCSV  = -9999;
    _jet3_DeepJet = -9999;
    _jet3_QGdiscr  = -9999;
  
    _jet4_pt   = -9999;
    _jet4_eta  = -9999;
    _jet4_phi  = -9999;
    _jet4_E    = -9999;
    _jet4_CSV  = -9999;
    _jet4_DeepCSV  = -9999;
    _jet4_DeepJet = -9999;
    _jet4_QGdiscr  = -9999;

    _jetFwd1_pt   = -9999;
    _jetFwd1_eta  = -9999;
    _jetFwd1_phi  = -9999;
    _jetFwd1_E    = -9999;

    _jetFwd2_pt   = -9999;
    _jetFwd2_eta  = -9999;
    _jetFwd2_phi  = -9999;
    _jetFwd2_E    = -9999;

    _jetFwd3_pt   = -9999;
    _jetFwd3_eta  = -9999;
    _jetFwd3_phi  = -9999;
    _jetFwd3_E    = -9999;

    _jetFwd4_pt   = -9999;
    _jetFwd4_eta  = -9999;
    _jetFwd4_phi  = -9999;
    _jetFwd4_E    = -9999;

    _jetAK8_1_pt = -9999;
    _jetAK8_1_eta = -9999;
    _jetAK8_1_phi = -9999;
    _jetAK8_1_E = -9999;
    _jetAK8_1_subjet_1_pt = -9999;
    _jetAK8_1_subjet_1_eta = -9999;
    _jetAK8_1_subjet_1_phi = -9999;
    _jetAK8_1_subjet_1_E = -9999;
    _jetAK8_1_subjet_2_pt = -9999;
    _jetAK8_1_subjet_2_eta = -9999;
    _jetAK8_1_subjet_2_phi = -9999;
    _jetAK8_1_subjet_2_E = -9999;
    _jetAK8_1_SDmass = -9999;
    _jetAK8_1_tau1 = -9999;
    _jetAK8_1_tau2 = -9999;

    _jetAK8_2_pt = -9999;
    _jetAK8_2_eta = -9999;
    _jetAK8_2_phi = -9999;
    _jetAK8_2_E = -9999;
    _jetAK8_2_subjet_1_pt = -9999;
    _jetAK8_2_subjet_1_eta = -9999;
    _jetAK8_2_subjet_1_phi = -9999;
    _jetAK8_2_subjet_1_E = -9999;
    _jetAK8_2_subjet_2_pt = -9999;
    _jetAK8_2_subjet_2_eta = -9999;
    _jetAK8_2_subjet_2_phi = -9999;
    _jetAK8_2_subjet_2_E = -9999;
    _jetAK8_2_SDmass = -9999;
    _jetAK8_2_tau1 = -9999;
    _jetAK8_2_tau2 = -9999;

    _PFMET     = -9999;
    _PFMETphi  = -9999;    
    _MHT       = -9999;
    _metLD     = -9999;    

    
    ////

    _category = 0;
    _n_recotauh_sel = 0;
    _is_ttH_like = 0;
    _is_tH_like_and_not_ttH_like = 0;
    
    _recomu_pt      = 0;
    _recomu_conept  = 0;
    _recomu_eta     = 0;
    _recomu_phi     = 0;
    _recomu_e       = 0;
    _recomu_charge  = 0;
    _recomu_jetNDauChargedMVASel = 0;
    _recomu_jetNDauChargedMVASel_nanoAOD = 0;
    _recomu_miniRelIso           = 0;
    _recomu_miniRelIso_nanoAOD      = 0;
    _recomu_miniIsoCharged       = 0;
    _recomu_miniIsoCharged_nanoAOD         = 0;
    _recomu_miniIsoNeutral       = 0;
    _recomu_miniIsoNeutral_nanoAOD       = 0;
    _recomu_combreliso04         = 0;
    _recomu_jetPtRel             = 0;
    _recomu_jetPtRatio           = 0;
    _recomu_jetPtRel_nanoAOD             = 0;
    _recomu_jetPtRatio_nanoAOD           = 0;
    _recomu_jetCSV               = 0;
    _recomu_jetDeepCSV           = 0;
    _recomu_jetDeepJet           = 0;
    _recomu_sip3D                = 0;
    _recomu_dxy                  = 0;
    _recomu_dz                   = 0;
    _recomu_lepMVA_Id         = 0;
    _recomu_leptonMVA            = 0;
    _recomu_mediumID             = 0;
    _recomu_rel_error_trackpt    = 0;
    _recomu_isfakeable           = 0;
    _recomu_ismvasel             = 0;
    _recomu_isGenMatched         = 0;

    _recoele_pt      = 0;
    _recoele_corr_pt = 0;
    _recoele_conept  = 0;
    _recoele_eta     = 0;
    _recoele_phi     = 0;
    _recoele_e       = 0;
    _recoele_corr_e  = 0;
    _recoele_charge  = 0;
    _recoele_jetNDauChargedMVASel = 0;
    _recoele_jetNDauChargedMVASel_nanoAOD = 0;
    _recoele_miniRelIso            = 0;
    _recoele_miniRelIso_nanoAOD      = 0;
    _recoele_miniIsoCharged       = 0;
    _recoele_miniIsoCharged_nanoAOD         = 0;
    _recoele_miniIsoNeutral       = 0;
    _recoele_miniIsoNeutral_nanoAOD       = 0;
    _recoele_PFRelIsoAll04_nanoAOD         = 0;
    _recoele_jetPtRel             = 0;
    _recoele_jetPtRatio           = 0;
    _recoele_jetPtRel_nanoAOD             = 0;
    _recoele_jetPtRatio_nanoAOD           = 0;
    _recoele_jetCSV               = 0;
    _recoele_jetDeepCSV           = 0;
    _recoele_jetDeepJet           = 0;
    _recoele_sip3D                = 0;
    _recoele_dxy                  = 0;
    _recoele_dz                   = 0;
    _recoele_lepMVA_Id         = 0;
    _recoele_leptonMVA            = 0;    
    _recoele_isChargeConsistent   = 0;
    _recoele_passConversionVeto   = 0;
    _recoele_nMissingHits         = 0;
    _recoele_sigmaEtaEta    = 0;
    _recoele_HoE      = 0;
    _recoele_deltaEta       = 0;
    _recoele_deltaPhi     = 0;
    _recoele_OoEminusOoP    = 0;
    _recoele_isfakeable           = 0;
    _recoele_ismvasel             = 0;    
    _recoele_isGenMatched         = 0;

    _recotauh_pt     = 0;
    _recotauh_eta    = 0;
    _recotauh_phi    = 0;
    _recotauh_e      = 0;
    _recotauh_charge = 0;
    _recotauh_dxy    = 0;
    _recotauh_dz     = 0;
    _recotauh_iso    = 0;
    _recotauh_decayModeFindingOldDMs                             = 0;
    _recotauh_decayModeFindingNewDMs                             = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits        = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03    = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT   = 0;
    _recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT    = 0;
    _recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT   = 0;
    _recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT    = 0;
    _recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT   = 0;
    _recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw      = 0;
    _recotauh_byVVVLooseDeepTau2017v2VSjet = 0;
    _recotauh_byVVLooseDeepTau2017v2VSjet = 0;
    _recotauh_byVLooseDeepTau2017v2VSjet = 0;
    _recotauh_byLooseDeepTau2017v2VSjet = 0;
    _recotauh_byMediumDeepTau2017v2VSjet = 0;
    _recotauh_byTightDeepTau2017v2VSjet = 0;
    _recotauh_byVTightDeepTau2017v2VSjet = 0;
    _recotauh_byVVTightDeepTau2017v2VSjet = 0;
    _recotauh_byDeepTau2017v2VSjetraw = 0;
    _recotauh_againstMuonLoose3           = 0;
    _recotauh_againstMuonTight3           = 0;
    _recotauh_againstElectronVLooseMVA6   = 0;
    _recotauh_againstElectronLooseMVA6    = 0;
    _recotauh_againstElectronMediumMVA6   = 0;
    _recotauh_againstElectronTightMVA6    = 0;
    _recotauh_againstElectronVTightMVA6   = 0;
    _recotauh_isGenMatched = 0;

    _recoPFJet_pt           = 0;
    _recoPFJet_eta          = 0;
    _recoPFJet_phi          = 0;
    _recoPFJet_e            = 0;
    _recoPFJet_CSVscore     = 0;
    _recoPFJet_DeepCSVscore = 0; 
    _recoPFJet_DeepJetscore = 0; 
    _recoPFJet_QGdiscr = 0; 

    _recoPFFwdJet_pt           = 0;
    _recoPFFwdJet_eta          = 0;
    _recoPFFwdJet_phi          = 0;
    _recoPFFwdJet_e            = 0;

    _recoPFak8Jet_e = 0;
    _recoPFak8Jet_pt = 0;
    _recoPFak8Jet_eta = 0;
    _recoPFak8Jet_phi = 0;
    _recoPFak8Jet_SoftDropMass = 0;
    _recoPFak8Jet_tau1 = 0;
    _recoPFak8Jet_tau2 = 0;
    _recoPFak8Jet_nsubjets = 0;
    _recoPFak8Jet_subjet1_e = 0;
    _recoPFak8Jet_subjet1_pt = 0;
    _recoPFak8Jet_subjet1_eta = 0;
    _recoPFak8Jet_subjet1_phi = 0;
    _recoPFak8Jet_subjet2_e = 0;
    _recoPFak8Jet_subjet2_pt = 0;
    _recoPFak8Jet_subjet2_eta = 0;
    _recoPFak8Jet_subjet2_phi = 0;

    tree[i_tree]->GetEntry(i);
 
    if(_n_presel_mu>0){

      _mu1_pt     = (*_recomu_pt)[0];
      _mu1_conept = (*_recomu_conept)[0];
      _mu1_eta    = (*_recomu_eta)[0];
      _mu1_phi    = (*_recomu_phi)[0];
      _mu1_E      = (*_recomu_e)[0];
      _mu1_charge = (*_recomu_charge)[0];
      _mu1_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel_nanoAOD)[0];
      _mu1_miniRelIso           = (*_recomu_miniRelIso_nanoAOD)[0];
      _mu1_miniIsoCharged       = (*_recomu_miniIsoCharged_nanoAOD)[0]/_mu1_pt;
      _mu1_miniIsoNeutral       = (*_recomu_miniIsoNeutral_nanoAOD)[0]/_mu1_pt;
      _mu1_PFRelIso04           = (*_recomu_combreliso04)[0];
      _mu1_jetPtRel             = (*_recomu_jetPtRel_nanoAOD)[0];
      _mu1_jetPtRatio           = (*_recomu_jetPtRatio_nanoAOD)[0];
      _mu1_jetCSV               = (*_recomu_jetCSV)[0] ;
      _mu1_jetDeepCSV           = (*_recomu_jetDeepCSV)[0] ;
      _mu1_jetDeepJet           = (*_recomu_jetDeepJet)[0] ;
      _mu1_sip3D                = (*_recomu_sip3D)[0];
      _mu1_dxy                  = (*_recomu_dxy)[0];
      _mu1_dxyAbs               = abs((*_recomu_dxy)[0]);
      _mu1_dz                   = (*_recomu_dz)[0];
      _mu1_segmentCompatibility = (*_recomu_lepMVA_Id)[0];
      _mu1_leptonMVA            = (*_recomu_leptonMVA)[0];
      _mu1_mediumID             = (*_recomu_mediumID)[0];
      _mu1_dpt_div_pt           = (*_recomu_rel_error_trackpt)[0];
      _mu1_isfakeablesel        = (*_recomu_isfakeable)[0];      
      _mu1_ismvasel             = (*_recomu_ismvasel)[0];
      _mu1_isGenMatched         = (*_recomu_isGenMatched)[0];

    }
    
   if(_n_presel_mu>1){

      _mu2_pt     = (*_recomu_pt)[1];
      _mu2_conept = (*_recomu_conept)[1];
      _mu2_eta    = (*_recomu_eta)[1];
      _mu2_phi    = (*_recomu_phi)[1];
      _mu2_E      = (*_recomu_e)[1];
      _mu2_charge = (*_recomu_charge)[1];
      _mu2_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel_nanoAOD)[1];
      _mu2_miniRelIso           = (*_recomu_miniRelIso_nanoAOD)[1];
      _mu2_miniIsoCharged       = (*_recomu_miniIsoCharged_nanoAOD)[1]/_mu2_pt;
      _mu2_miniIsoNeutral       = (*_recomu_miniIsoNeutral_nanoAOD)[1]/_mu2_pt;
      _mu2_PFRelIso04           = (*_recomu_combreliso04)[1];
      _mu2_jetPtRel             = (*_recomu_jetPtRel_nanoAOD)[1];
      _mu2_jetPtRatio           = (*_recomu_jetPtRatio_nanoAOD)[1];
      _mu2_jetCSV               = (*_recomu_jetCSV)[1];
      _mu2_jetDeepCSV           = (*_recomu_jetDeepCSV)[1];
      _mu2_jetDeepJet           = (*_recomu_jetDeepJet)[1];
      _mu2_sip3D                = (*_recomu_sip3D)[1];
      _mu2_dxy                  = (*_recomu_dxy)[1];
      _mu2_dxyAbs               = abs((*_recomu_dxy)[1]);
      _mu2_dz                   = (*_recomu_dz)[1];
      _mu2_segmentCompatibility = (*_recomu_lepMVA_Id)[1];
      _mu2_leptonMVA            = (*_recomu_leptonMVA)[1];
      _mu2_mediumID             = (*_recomu_mediumID)[1];
      _mu2_dpt_div_pt           = (*_recomu_rel_error_trackpt)[1];
      _mu2_isfakeablesel        = (*_recomu_isfakeable)[1];  
      _mu2_ismvasel             = (*_recomu_ismvasel)[1];
      _mu2_isGenMatched         = (*_recomu_isGenMatched)[1];
      
    }
    
    if(_n_presel_ele>0){

      _ele1_pt = (*_recoele_corr_pt)[0];
      _ele1_conept = (*_recoele_conept)[0];
      _ele1_eta    = (*_recoele_eta)[0];
      _ele1_phi    = (*_recoele_phi)[0];
      _ele1_E = (*_recoele_corr_e)[0];
      _ele1_charge = (*_recoele_charge)[0];
      _ele1_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel_nanoAOD)[0];
      _ele1_miniRelIso           = (*_recoele_miniRelIso_nanoAOD)[0];
      _ele1_miniIsoCharged       = (*_recoele_miniIsoCharged_nanoAOD)[0]/(*_recoele_pt)[0];
      _ele1_miniIsoNeutral       = (*_recoele_miniIsoNeutral_nanoAOD)[0]/(*_recoele_pt)[0];
      _ele1_PFRelIso04           = (*_recoele_PFRelIsoAll04_nanoAOD)[0];
      _ele1_jetPtRel             = (*_recoele_jetPtRel_nanoAOD)[0];
      _ele1_jetPtRatio           = (*_recoele_jetPtRatio_nanoAOD)[0];
      _ele1_jetCSV               = (*_recoele_jetCSV)[0] ;
      _ele1_jetDeepCSV           = (*_recoele_jetDeepCSV)[0] ;
      _ele1_jetDeepJet           = (*_recoele_jetDeepJet)[0] ;
      _ele1_sip3D                = (*_recoele_sip3D)[0];
      _ele1_dxy                  = (*_recoele_dxy)[0];
      _ele1_dxyAbs               = abs((*_recoele_dxy)[0]);
      _ele1_dz                   = (*_recoele_dz)[0];
      _ele1_ntMVAeleID           = (*_recoele_lepMVA_Id)[0];
      _ele1_leptonMVA            = (*_recoele_leptonMVA)[0];
      _ele1_isChargeConsistent   = (*_recoele_isChargeConsistent)[0];      
      _ele1_passesConversionVeto = (*_recoele_passConversionVeto)[0];
      _ele1_nMissingHits         = (*_recoele_nMissingHits)[0];
      _ele1_sigmaEtaEta    = (*_recoele_sigmaEtaEta)[0];
      _ele1_HoE      = (*_recoele_HoE)[0];
      _ele1_deltaEta     = (*_recoele_deltaEta)[0];
      _ele1_deltaPhi     = (*_recoele_deltaPhi)[0];
      _ele1_OoEminusOoP    = (*_recoele_OoEminusOoP)[0];
      _ele1_isfakeablesel        = (*_recoele_isfakeable)[0];
      _ele1_ismvasel             = (*_recoele_ismvasel)[0];
      _ele1_isGenMatched         = (*_recoele_isGenMatched)[0];

    }

    if(_n_presel_ele>1){

      _ele2_pt = (*_recoele_corr_pt)[1];
      _ele2_conept = (*_recoele_conept)[1];
      _ele2_eta    = (*_recoele_eta)[1];
      _ele2_phi    = (*_recoele_phi)[1];
      _ele2_E = (*_recoele_corr_e)[1];
      _ele2_charge = (*_recoele_charge)[1];
      _ele2_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel_nanoAOD)[1];
      _ele2_miniRelIso           = (*_recoele_miniRelIso_nanoAOD)[1];
      _ele2_miniIsoCharged       = (*_recoele_miniIsoCharged_nanoAOD)[1]/(*_recoele_pt)[1];
      _ele2_miniIsoNeutral       = (*_recoele_miniIsoNeutral_nanoAOD)[1]/(*_recoele_pt)[1];
      _ele2_PFRelIso04           = (*_recoele_PFRelIsoAll04_nanoAOD)[1];
      _ele2_jetPtRel             = (*_recoele_jetPtRel_nanoAOD)[1];
      _ele2_jetPtRatio           = (*_recoele_jetPtRatio_nanoAOD)[1];
      _ele2_jetCSV               = (*_recoele_jetCSV)[1] ;
      _ele2_jetDeepCSV           = (*_recoele_jetDeepCSV)[1] ;
      _ele2_jetDeepJet           = (*_recoele_jetDeepJet)[1] ;
      _ele2_sip3D                = (*_recoele_sip3D)[1];
      _ele2_dxy                  = (*_recoele_dxy)[1];
      _ele2_dxyAbs               = abs((*_recoele_dxy)[1]);
      _ele2_dz                   = (*_recoele_dz)[1];
      _ele2_ntMVAeleID           = (*_recoele_lepMVA_Id)[1];
      _ele2_leptonMVA            = (*_recoele_leptonMVA)[1];
      _ele2_isChargeConsistent   = (*_recoele_isChargeConsistent)[1];
      _ele2_passesConversionVeto = (*_recoele_passConversionVeto)[1];
      _ele2_nMissingHits         = (*_recoele_nMissingHits)[1];
      _ele2_sigmaEtaEta          = (*_recoele_sigmaEtaEta)[1];
      _ele2_HoE                  = (*_recoele_HoE)[1];
      _ele2_deltaEta             = (*_recoele_deltaEta)[1];
      _ele2_deltaPhi             = (*_recoele_deltaPhi)[1];
      _ele2_OoEminusOoP          = (*_recoele_OoEminusOoP)[1];
      _ele2_isfakeablesel        = (*_recoele_isfakeable)[1];
      _ele2_ismvasel             = (*_recoele_ismvasel)[1];
      _ele2_isGenMatched             = (*_recoele_isGenMatched)[1];

    }

    if(_n_presel_tau>0){

      _tau1_pt     = (*_recotauh_pt)[0];
      _tau1_eta    = (*_recotauh_eta)[0];
      _tau1_phi    = (*_recotauh_phi)[0];
      _tau1_E      = (*_recotauh_e)[0];
      _tau1_charge = (*_recotauh_charge)[0]; 
      _tau1_dxy    = (*_recotauh_dxy)[0]; 
      _tau1_dz     = (*_recotauh_dz)[0]; 
      _tau1_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[0];
      _tau1_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[0];
      _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[0];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT)[0];
      _tau1_rawMVArun2v1DBdR03oldDMwLT                       = (*_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw)[0];
      _tau1_byVVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVVLooseDeepTau2017v2VSjet)[0];
      _tau1_byVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVLooseDeepTau2017v2VSjet)[0];
      _tau1_byVLooseDeepTau2017v2VSjet = (*_recotauh_byVLooseDeepTau2017v2VSjet)[0];
      _tau1_byLooseDeepTau2017v2VSjet = (*_recotauh_byLooseDeepTau2017v2VSjet)[0];
      _tau1_byMediumDeepTau2017v2VSjet = (*_recotauh_byMediumDeepTau2017v2VSjet)[0];
      _tau1_byTightDeepTau2017v2VSjet = (*_recotauh_byTightDeepTau2017v2VSjet)[0];
      _tau1_byVTightDeepTau2017v2VSjet = (*_recotauh_byVTightDeepTau2017v2VSjet)[0];
      _tau1_byVVTightDeepTau2017v2VSjet = (*_recotauh_byVVTightDeepTau2017v2VSjet)[0];
      _tau1_byDeepTau2017v2VSjetraw = (*_recotauh_byDeepTau2017v2VSjetraw)[0];    
      _tau1_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[0];
      _tau1_againstMuonTight3          = (*_recotauh_againstMuonTight3)[0];
      _tau1_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[0];
      _tau1_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[0];
      _tau1_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[0];
      _tau1_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[0];
      _tau1_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[0];
      _tau1_isGenMatched = (*_recotauh_isGenMatched)[0];

    }

    if(_n_presel_tau>1){

      _tau2_pt     = (*_recotauh_pt)[1];
      _tau2_eta    = (*_recotauh_eta)[1];
      _tau2_phi    = (*_recotauh_phi)[1];
      _tau2_E      = (*_recotauh_e)[1];
      _tau2_charge = (*_recotauh_charge)[1];
      _tau2_dxy    = (*_recotauh_dxy)[1]; 
      _tau2_dz     = (*_recotauh_dz)[1];     
      _tau2_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[1];
      _tau2_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[1];
      _tau2_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[1];
      _tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau2_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT)[1];
      _tau2_rawMVArun2v1DBdR03oldDMwLT                       = (*_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw)[1];
      _tau2_byVVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVVLooseDeepTau2017v2VSjet)[1];
      _tau2_byVVLooseDeepTau2017v2VSjet = (*_recotauh_byVVLooseDeepTau2017v2VSjet)[1];
      _tau2_byVLooseDeepTau2017v2VSjet = (*_recotauh_byVLooseDeepTau2017v2VSjet)[1];
      _tau2_byLooseDeepTau2017v2VSjet = (*_recotauh_byLooseDeepTau2017v2VSjet)[1];
      _tau2_byMediumDeepTau2017v2VSjet = (*_recotauh_byMediumDeepTau2017v2VSjet)[1];
      _tau2_byTightDeepTau2017v2VSjet = (*_recotauh_byTightDeepTau2017v2VSjet)[1];
      _tau2_byVTightDeepTau2017v2VSjet = (*_recotauh_byVTightDeepTau2017v2VSjet)[1];
      _tau2_byVVTightDeepTau2017v2VSjet = (*_recotauh_byVVTightDeepTau2017v2VSjet)[1];
      _tau2_byDeepTau2017v2VSjetraw = (*_recotauh_byDeepTau2017v2VSjetraw)[1];
      _tau2_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[1];
      _tau2_againstMuonTight3          = (*_recotauh_againstMuonTight3)[1];
      _tau2_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[1];
      _tau2_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[1];
      _tau2_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[1];
      _tau2_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[1];
      _tau2_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[1];
      _tau2_isGenMatched  = (*_recotauh_isGenMatched)[1];

    }
    
    if(_n_presel_jet>0){

      _jet1_pt   = (*_recoPFJet_pt)[0];
      _jet1_eta  = (*_recoPFJet_eta)[0];
      _jet1_phi  = (*_recoPFJet_phi)[0];
      _jet1_E    = (*_recoPFJet_e)[0];
      _jet1_CSV  = (*_recoPFJet_CSVscore)[0];
      _jet1_DeepCSV  = (*_recoPFJet_DeepCSVscore)[0];
      _jet1_DeepJet  = (*_recoPFJet_DeepJetscore)[0];
      _jet1_QGdiscr  = (*_recoPFJet_QGdiscr)[0];

    }

    if(_n_presel_jet>1){

      _jet2_pt   = (*_recoPFJet_pt)[1];
      _jet2_eta  = (*_recoPFJet_eta)[1];
      _jet2_phi  = (*_recoPFJet_phi)[1];
      _jet2_E    = (*_recoPFJet_e)[1];
      _jet2_CSV  = (*_recoPFJet_CSVscore)[1];
      _jet2_DeepCSV  = (*_recoPFJet_DeepCSVscore)[1];
      _jet2_DeepJet  = (*_recoPFJet_DeepJetscore)[1];
      _jet2_QGdiscr  = (*_recoPFJet_QGdiscr)[1];

    }
    
    if(_n_presel_jet>2){

      _jet3_pt   = (*_recoPFJet_pt)[2];
      _jet3_eta  = (*_recoPFJet_eta)[2];
      _jet3_phi  = (*_recoPFJet_phi)[2];
      _jet3_E    = (*_recoPFJet_e)[2];
      _jet3_CSV  = (*_recoPFJet_CSVscore)[2];
      _jet3_DeepCSV  = (*_recoPFJet_DeepCSVscore)[2];
      _jet3_DeepJet  = (*_recoPFJet_DeepJetscore)[2];
      _jet3_QGdiscr  = (*_recoPFJet_QGdiscr)[2];

    }
  
    if(_n_presel_jet>3){

      _jet4_pt   = (*_recoPFJet_pt)[3];
      _jet4_eta  = (*_recoPFJet_eta)[3];
      _jet4_phi  = (*_recoPFJet_phi)[3];
      _jet4_E    = (*_recoPFJet_e)[3];
      _jet4_CSV  = (*_recoPFJet_CSVscore)[3];
      _jet4_DeepCSV  = (*_recoPFJet_DeepCSVscore)[3];
      _jet4_DeepJet  = (*_recoPFJet_DeepJetscore)[3];
      _jet4_QGdiscr  = (*_recoPFJet_QGdiscr)[3];

    }

    if(_n_presel_jetFwd>0){

      _jetFwd1_pt   = (*_recoPFFwdJet_pt)[0];
      _jetFwd1_eta  = (*_recoPFFwdJet_eta)[0];
      _jetFwd1_phi  = (*_recoPFFwdJet_phi)[0];
      _jetFwd1_E    = (*_recoPFFwdJet_e)[0];

    }

    if(_n_presel_jetFwd>1){

      _jetFwd2_pt   = (*_recoPFFwdJet_pt)[1];
      _jetFwd2_eta  = (*_recoPFFwdJet_eta)[1];
      _jetFwd2_phi  = (*_recoPFFwdJet_phi)[1];
      _jetFwd2_E    = (*_recoPFFwdJet_e)[1];

    }
    
    if(_n_presel_jetFwd>2){

      _jetFwd3_pt   = (*_recoPFFwdJet_pt)[2];
      _jetFwd3_eta  = (*_recoPFFwdJet_eta)[2];
      _jetFwd3_phi  = (*_recoPFFwdJet_phi)[2];
      _jetFwd3_E    = (*_recoPFFwdJet_e)[2];

    }
  
    if(_n_presel_jetFwd>3){

      _jetFwd4_pt   = (*_recoPFFwdJet_pt)[3];
      _jetFwd4_eta  = (*_recoPFFwdJet_eta)[3];
      _jetFwd4_phi  = (*_recoPFFwdJet_phi)[3];
      _jetFwd4_E    = (*_recoPFFwdJet_e)[3];

    }

    if(_n_presel_jetAK8>0){

      _jetAK8_1_pt = (*_recoPFak8Jet_pt)[0];
      _jetAK8_1_eta = (*_recoPFak8Jet_eta)[0];
      _jetAK8_1_phi = (*_recoPFak8Jet_phi)[0];
      _jetAK8_1_E = (*_recoPFak8Jet_e)[0];
      _jetAK8_1_SDmass = (*_recoPFak8Jet_SoftDropMass)[0];
      _jetAK8_1_tau1 = (*_recoPFak8Jet_tau1)[0];
      _jetAK8_1_tau2 = (*_recoPFak8Jet_tau2)[0];

      if((*_recoPFak8Jet_nsubjets)[0]==2){

        _jetAK8_1_subjet_1_pt = (*_recoPFak8Jet_subjet1_pt)[0];
        _jetAK8_1_subjet_1_eta = (*_recoPFak8Jet_subjet1_eta)[0];
        _jetAK8_1_subjet_1_phi = (*_recoPFak8Jet_subjet1_phi)[0];
        _jetAK8_1_subjet_1_E = (*_recoPFak8Jet_subjet1_e)[0];

        _jetAK8_1_subjet_2_pt = (*_recoPFak8Jet_subjet2_pt)[0];
        _jetAK8_1_subjet_2_eta = (*_recoPFak8Jet_subjet2_pt)[0];
        _jetAK8_1_subjet_2_phi = (*_recoPFak8Jet_subjet2_pt)[0];
        _jetAK8_1_subjet_2_E = (*_recoPFak8Jet_subjet2_pt)[0];

      }

      else{

        _jetAK8_1_subjet_1_pt = -9999;
        _jetAK8_1_subjet_1_eta = -9999;
        _jetAK8_1_subjet_1_phi = -9999;
        _jetAK8_1_subjet_1_E = -9999;

        _jetAK8_1_subjet_2_pt = -9999;
        _jetAK8_1_subjet_2_eta = -9999;
        _jetAK8_1_subjet_2_phi = -9999;
        _jetAK8_1_subjet_2_E = -9999;
        
      }

    }

    if(_n_presel_jetAK8>1){

      _jetAK8_2_pt = (*_recoPFak8Jet_pt)[1];
      _jetAK8_2_eta = (*_recoPFak8Jet_eta)[1];
      _jetAK8_2_phi = (*_recoPFak8Jet_phi)[1];
      _jetAK8_2_E = (*_recoPFak8Jet_e)[1];
      _jetAK8_2_SDmass = (*_recoPFak8Jet_SoftDropMass)[1];
      _jetAK8_2_tau1 = (*_recoPFak8Jet_tau1)[1];
      _jetAK8_2_tau2 = (*_recoPFak8Jet_tau2)[1];

      if((*_recoPFak8Jet_nsubjets)[1]==2){

        _jetAK8_2_subjet_1_pt = (*_recoPFak8Jet_subjet1_pt)[1];
        _jetAK8_2_subjet_1_eta = (*_recoPFak8Jet_subjet1_eta)[1];
        _jetAK8_2_subjet_1_phi = (*_recoPFak8Jet_subjet1_phi)[1];
        _jetAK8_2_subjet_1_E = (*_recoPFak8Jet_subjet1_e)[1];

        _jetAK8_2_subjet_2_pt = (*_recoPFak8Jet_subjet2_pt)[1];
        _jetAK8_2_subjet_2_eta = (*_recoPFak8Jet_subjet2_pt)[1];
        _jetAK8_2_subjet_2_phi = (*_recoPFak8Jet_subjet2_pt)[1];
        _jetAK8_2_subjet_2_E = (*_recoPFak8Jet_subjet2_pt)[1];

      }

      else{

        _jetAK8_2_subjet_1_pt = -9999;
        _jetAK8_2_subjet_1_eta = -9999;
        _jetAK8_2_subjet_1_phi = -9999;
        _jetAK8_2_subjet_1_E = -9999;

        _jetAK8_2_subjet_2_pt = -9999;
        _jetAK8_2_subjet_2_eta = -9999;
        _jetAK8_2_subjet_2_phi = -9999;
        _jetAK8_2_subjet_2_E = -9999;
        
      }
      
    }


    if(_category==1010) tree_new_2tau_SR->Fill();
    if(_category==1020) tree_new_2tau_fake->Fill();

    if(_category==2010) tree_new_1l1tau_SR->Fill();
    if(_category==2020) tree_new_1l1tau_fake->Fill();
    if(_category==2030) tree_new_1l1tau_flip->Fill();

    if(_category==2110) tree_new_1l2tau_SR->Fill();
    if(_category==2120) tree_new_1l2tau_fake->Fill();

    if(_category==3010) tree_new_2lss_SR->Fill();
    if(_category==3020) tree_new_2lss_fake->Fill();
    if(_category==3030) tree_new_2lss_flip->Fill();

    if(_category==3110) tree_new_2lss1tau_SR->Fill();
    if(_category==3120) tree_new_2lss1tau_fake->Fill();
    if(_category==3130) tree_new_2lss1tau_flip->Fill();

    if(_category==3210) tree_new_2los1tau_SR->Fill();
    if(_category==3220) tree_new_2los1tau_fake->Fill();

    if(_category==3310) tree_new_2l2tau_SR->Fill();
    if(_category==3320) tree_new_2l2tau_fake->Fill();

    if(_category==4010) tree_new_3l_SR->Fill();
    if(_category==4020) tree_new_3l_fake->Fill();

    if(_category==4110) tree_new_3l1tau_SR->Fill();
    if(_category==4120) tree_new_3l1tau_fake->Fill();

    if(_category==5010) tree_new_4l_SR->Fill();
    if(_category==5020) tree_new_4l_fake->Fill();

    if(_category==6010) tree_new_ttW_CR_SR->Fill();
    if(_category==6020) tree_new_ttW_CR_fake->Fill();
    if(_category==6030) tree_new_ttW_CR_flip->Fill();

    if(_category==7010) tree_new_ttZ_CR_SR->Fill();
    if(_category==7020) tree_new_ttZ_CR_fake->Fill();

    if(_category==8010) tree_new_WZ_CR_SR->Fill();
    if(_category==8020) tree_new_WZ_CR_fake->Fill();
    
    if(_category==9010) tree_new_ZZ_CR_SR->Fill();
    if(_category==9020) tree_new_ZZ_CR_fake->Fill();


  }
  
  }
  
  for(unsigned int i=0;i<tree_new.size();i++)
    tree_new[i]->Write();

  f_new->Close();


  return;

}
