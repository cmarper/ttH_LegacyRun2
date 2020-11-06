#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TStyle.h>
#include <TROOT.h>
#include <sstream>
#include <TBranchElement.h>
#include <fstream>
#include <TGraphAsymmErrors.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <TGaxis.h>

using namespace std;

void EvaluateAcceptance(TString process = "VBF", double Threshold_XX = 40, double Threshold_YY = 30, bool is0jet = true, bool is1jet = false, bool is2jet = false ){

  TString InputFileName = "/data_CMS/cms/mperez/TauTrigger_data/TauTauJet/Ntuple_MC_MiniAOD_GluGluHToTauTau_181210_10_3_X_multipletaus.root";
  if (process=="ggH") InputFileName = "/data_CMS/cms/mperez/TauTrigger_data/TauTauJet/Ntuple_MC_MiniAOD_GluGluHToTauTau_181210_10_3_X_multipletaus.root";
  else if (process=="VBF") InputFileName = "/data_CMS/cms/mperez/TauTrigger_data/TauTauJet/Ntuple_MC_MiniAOD_VBFHToTauTau_261210_10_3_X_multipletaus.root";
  else if (process=="ttH") InputFileName = "/data_CMS/cms/mperez/TauTrigger_data/2018/MC/NTuple_MC_ttHnonbb_MiniAOD_RunIIAutumn18_2Apr19_multipletaus.root";

  //TChain * tree = new TChain("Ntuplizer_noTagAndProbe_multipleTaus/TagAndProbe");
  TChain * tree = new TChain("TagAndProbe"); //for ttH file
  tree->Add(InputFileName);

  Int_t       RunNumber = 0;
  ULong64_t   EventNumber = 0;
  Int_t       lumi = 0;

  //offl
  vector<float>   *tauPt = 0;
  vector<float>   *tauEta = 0;
  vector<float>   *tauPhi = 0;

  vector<float>   *jets_px = 0;
  vector<float>   *jets_py = 0;
  vector<float>   *jets_pz = 0;
  vector<float>   *jets_e = 0;

  //online
  vector<float>   *l1tPt = 0;
  vector<float>   *l1tEta = 0;
  vector<float>   *l1tPhi = 0;
  vector<int>     *l1tIso = 0;

  vector<float>   *l1tPtJet = 0;
  vector<float>   *l1tEtaJet = 0;
  vector<float>   *l1tPhiJet = 0;

  TBranch   *b_RunNumber ;
  TBranch   *b_EventNumber ;
  TBranch   *b_lumi ;

  TBranch   *b_tauPt ;
  TBranch   *b_tauEta ;
  TBranch   *b_tauPhi ;

  TBranch   *b_jets_px ;
  TBranch   *b_jets_py ;
  TBranch   *b_jets_pz ;
  TBranch   *b_jets_e ;

  TBranch   *b_l1tPt ;
  TBranch   *b_l1tEta ;
  TBranch   *b_l1tPhi ;
  TBranch   *b_l1tIso ;

  TBranch   *b_l1tPtJet ;
  TBranch   *b_l1tEtaJet ;
  TBranch   *b_l1tPhiJet ;

  TBranch   *b_isMatched ;
  
  tree->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
  tree->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
  tree->SetBranchAddress("lumi", &lumi, &b_lumi);

  tree->SetBranchAddress("tauPt", &tauPt, &b_tauPt);
  tree->SetBranchAddress("tauEta", &tauEta, &b_tauEta);
  tree->SetBranchAddress("tauPhi", &tauPhi, &b_tauPhi);

  tree->SetBranchAddress("jets_px", &jets_px, &b_jets_px);
  tree->SetBranchAddress("jets_py", &jets_py, &b_jets_py);
  tree->SetBranchAddress("jets_pz", &jets_pz, &b_jets_pz);
  tree->SetBranchAddress("jets_e", &jets_e, &b_jets_e);

  tree->SetBranchAddress("l1tPt", &l1tPt, &b_l1tPt);
  tree->SetBranchAddress("l1tEta", &l1tEta, &b_l1tEta);
  tree->SetBranchAddress("l1tPhi", &l1tPhi, &b_l1tPhi);
  tree->SetBranchAddress("l1tIso", &l1tIso, &b_l1tIso);
 
  tree->SetBranchAddress("l1tPtJet", &l1tPtJet, &b_l1tPtJet);
  tree->SetBranchAddress("l1tEtaJet", &l1tEtaJet, &b_l1tEtaJet);
  tree->SetBranchAddress("l1tPhiJet", &l1tPhiJet, &b_l1tPhiJet);

 
  double n_Pass_Offl_DiTau32_0jet = 0.;
  double n_Pass_Offl_DiTau32_1jet = 0.;
  double n_Pass_Offl_DiTau32_2jet = 0.;

  double n_Pass_Offl_DiTauXY_0jet = 0.;
  double n_Pass_Offl_DiTauXY_1jet = 0.;
  double n_Pass_Offl_DiTauXY_2jet = 0.;

  double n_Pass_L1_DiTau32 = 0.;
  double n_Pass_L1_DiTauXY = 0.;

  double numerator_0jet = 0;
  double numerator_1jet = 0;
  double numerator_2jet = 0;

  double denominator_0jet = 0.;
  double denominator_1jet = 0.;
  double denominator_2jet = 0.;

  double accept_gain_0jet = 0;
  double accept_gain_1jet = 0.;
  double accept_gain_2jet = 0.;

  // loop events
  for(UInt_t i = 0 ; i < tree->GetEntries() ; ++i){

    tree->GetEntry(i);
    //if(i%100000==0) 
    //  cout<<"Entry #"<<i<<endl;

    ///////////////////////////////////////////////
    ////////////////  OFFLINE  ////////////////////
    ///////////////////////////////////////////////

    double Pass_Offl_DiTau32_0jet = false;
    double Pass_Offl_DiTau32_1jet = false;
    double Pass_Offl_DiTau32_2jet = false;

    double Pass_Offl_DiTauXY_0jet = false;
    double Pass_Offl_DiTauXY_1jet = false;
    double Pass_Offl_DiTauXY_2jet = false;

    double Cuts_Offl_DiTau32_0jet = false;
    double Cuts_Offl_DiTau32_1jet = false;
    double Cuts_Offl_DiTau32_2jet = false;

    double Cuts_Offl_DiTauXY_0jet = false;
    double Cuts_Offl_DiTauXY_1jet = false;
    double Cuts_Offl_DiTauXY_2jet = false;

    vector<TLorentzVector> offl_tau_vector;
    offl_tau_vector.clear();
    TLorentzVector OfflTau;
    Int_t n_offl_taus = tauPt->size();
 
    for(Int_t iTau = 0 ; iTau < n_offl_taus ; ++iTau){
      OfflTau.SetPtEtaPhiM(tauPt->at(iTau),tauEta->at(iTau),tauPhi->at(iTau),0.);
      offl_tau_vector.push_back(OfflTau);
    }

    vector<TLorentzVector> offl_jet_vector;
    offl_jet_vector.clear();
    TLorentzVector OfflJet;
    Int_t n_offl_jets = jets_px->size();

    for(Int_t iJet = 0 ; iJet < n_offl_jets ; ++iJet){
      OfflJet.SetPxPyPzE(jets_px->at(iJet),jets_py->at(iJet),jets_pz->at(iJet),jets_e->at(iJet));
      offl_jet_vector.push_back(OfflJet);
    }
    
    vector<TLorentzVector> offl_jet_vector_dR;
    offl_jet_vector_dR.clear();

    //look for jets that are dR>0.5 from tau1 and tau2   
    vector<int> index_offl_jet_tau1;
    vector<int> index_offl_jet_tau2;

    if (n_offl_taus>1 && n_offl_jets>0){
      for(Int_t iJet = 0 ; iJet < n_offl_jets ; ++iJet){
        if(offl_tau_vector.at(0).DeltaR(offl_jet_vector.at(iJet))>0.5) {
          index_offl_jet_tau1.push_back(iJet);
        }
        if(offl_tau_vector.at(1).DeltaR(offl_jet_vector.at(iJet))>0.5) {
          index_offl_jet_tau2.push_back(iJet);
        }
      }
    }

    //look for jets that are dR>0.5 from both taus simultaneously
    int index_offl_jet_taus = -999;  

    if (index_offl_jet_tau1.size()>0 && index_offl_jet_tau2.size()>0) {
      for (UInt_t i = 0; i<index_offl_jet_tau1.size(); ++i){
        for (UInt_t j = 0; j<index_offl_jet_tau2.size(); ++j){    
          if (index_offl_jet_tau1.at(i) == index_offl_jet_tau2.at(j)){
            index_offl_jet_taus = index_offl_jet_tau1.at(i);
            offl_jet_vector_dR.push_back(offl_jet_vector.at(index_offl_jet_tau1.at(i))); 
          } 
        }
      }      
    }

    //Cuts DiTau32
    Cuts_Offl_DiTau32_0jet = n_offl_taus>=2
          && offl_tau_vector.at(0).Pt()>=50 && offl_tau_vector.at(1).Pt()>=40
          && offl_tau_vector.at(0).Eta()<=2.1 && offl_tau_vector.at(1).Eta()<=2.1;

    Cuts_Offl_DiTau32_1jet = n_offl_taus>=2 && offl_jet_vector_dR.size()>=1
          && offl_tau_vector.at(0).Pt()>=50 && offl_tau_vector.at(1).Pt()>=40
          && offl_jet_vector_dR.at(0).Pt()>=30
          && offl_tau_vector.at(0).Eta()<=2.1 && offl_tau_vector.at(1).Eta()<=2.1;

    Cuts_Offl_DiTau32_2jet = n_offl_taus>=2 && offl_jet_vector_dR.size()>=2
          && offl_tau_vector.at(0).Pt()>=50 && offl_tau_vector.at(1).Pt()>=40
          && offl_jet_vector_dR.at(0).Pt()>=30 && offl_jet_vector_dR.at(1).Pt()>=30
          && offl_tau_vector.at(0).Eta()<=2.1 && offl_tau_vector.at(1).Eta()<=2.1;

    //Cuts DiTauXY
    Cuts_Offl_DiTauXY_0jet = n_offl_taus>=2
           && offl_tau_vector.at(0).Pt()>=Threshold_XX+18 && offl_tau_vector.at(1).Pt()>=Threshold_YY+8
           && offl_tau_vector.at(0).Eta()<=2.1 && offl_tau_vector.at(1).Eta()<=2.1;
    //Cuts_Offl_DiTauXY_0jet = Cuts_Offl_DiTau32_0jet;

    Cuts_Offl_DiTauXY_1jet = n_offl_taus>=2 && offl_jet_vector_dR.size()>=1
           && offl_tau_vector.at(0).Pt()>=Threshold_XX+18 && offl_tau_vector.at(1).Pt()>=Threshold_YY+8
           && offl_jet_vector_dR.at(0).Pt()>=30
           && offl_tau_vector.at(0).Eta()<=2.1 && offl_tau_vector.at(1).Eta()<=2.1;
    //Cuts_Offl_DiTauXY_1jet = Cuts_Offl_DiTau32_1jet;

    Cuts_Offl_DiTauXY_2jet = n_offl_taus>=2 && offl_jet_vector_dR.size()>=2
           && offl_tau_vector.at(0).Pt()>=Threshold_XX+18 && offl_tau_vector.at(1).Pt()>=Threshold_YY+8
           && offl_jet_vector_dR.at(0).Pt()>=30 && offl_jet_vector_dR.at(1).Pt()>=30
           && offl_tau_vector.at(0).Eta()<=2.1 && offl_tau_vector.at(1).Eta()<=2.1;
    //Cuts_Offl_DiTauXY_2jet = Cuts_Offl_DiTau32_2jet;
    
    if (Cuts_Offl_DiTau32_0jet) 
      Pass_Offl_DiTau32_0jet = true;

    if (Cuts_Offl_DiTau32_1jet)
      Pass_Offl_DiTau32_1jet = true;

    if (Cuts_Offl_DiTau32_2jet)
      Pass_Offl_DiTau32_2jet = true;

    if (Cuts_Offl_DiTauXY_0jet)
      Pass_Offl_DiTauXY_0jet = true;

    if (Cuts_Offl_DiTauXY_1jet)
      Pass_Offl_DiTauXY_1jet = true;

    if (Cuts_Offl_DiTauXY_2jet)
      Pass_Offl_DiTauXY_2jet = true;


    ///////////////////////////////////////////////
    ////////////////  ONLINE  /////////////////////
    ///////////////////////////////////////////////

    bool Pass_L1_DiTauXY = false;
    bool Pass_L1_DiTau32 = false;

    bool Cuts_L1_DiTauXY = false;
    bool Cuts_L1_DiTau32 = false;

    vector<TLorentzVector> L1_tau_vector;
    L1_tau_vector.clear();
    TLorentzVector L1Tau;

    vector<TLorentzVector> good_L1_tau_vector;
    good_L1_tau_vector.clear();
    TLorentzVector GoodL1Tau;

    Int_t n_L1_taus = l1tPt->size();
    Int_t n_good_L1_taus = 0;
   
    // all L1 taus
    for(Int_t iTau = 0 ; iTau < n_L1_taus ; ++iTau){
      L1Tau.SetPtEtaPhiM(l1tPt->at(iTau),l1tEta->at(iTau),l1tPhi->at(iTau),0.);
      L1_tau_vector.push_back(L1Tau);
      
      // good L1 taus
      for(Int_t iOffTau = 0 ; iOffTau < n_offl_taus ; ++iOffTau){
        if (l1tPt->at(iTau)>0.5 && (offl_tau_vector.at(iOffTau)).DeltaR(L1Tau)<0.5 && l1tIso->at(iTau)){
          n_good_L1_taus++;
          GoodL1Tau = L1Tau;
          good_L1_tau_vector.push_back(GoodL1Tau);
        }
      }
    }

    Cuts_L1_DiTau32 = n_good_L1_taus>=2
          && good_L1_tau_vector.at(0).Pt()>=32 && good_L1_tau_vector.at(1).Pt()>=32
          && good_L1_tau_vector.at(0).Eta()<=2.1 && good_L1_tau_vector.at(1).Eta()<=2.1;

    Cuts_L1_DiTauXY = n_good_L1_taus>=2
          && good_L1_tau_vector.at(0).Pt()>=Threshold_XX && good_L1_tau_vector.at(1).Pt()>=Threshold_YY
          && good_L1_tau_vector.at(0).Eta()<=2.1 && good_L1_tau_vector.at(1).Eta()<=2.1;

    if (Cuts_L1_DiTau32)
      Pass_L1_DiTau32 = true;

    if (Cuts_L1_DiTauXY)
      Pass_L1_DiTauXY = true;


    //////////////////////////////////////////////////
    ////////////////  ACCEPTANCE  ////////////////////
    //////////////////////////////////////////////////

    // numerator
    if ( Cuts_L1_DiTauXY && Pass_Offl_DiTauXY_0jet )
      numerator_0jet++;

    if ( Cuts_L1_DiTauXY && Pass_Offl_DiTauXY_1jet )
      numerator_1jet++;

    if ( Cuts_L1_DiTauXY && Pass_Offl_DiTauXY_2jet )
      numerator_2jet++;

    // denominator

    if ( Cuts_L1_DiTau32 && Cuts_Offl_DiTau32_0jet )
      denominator_0jet++;

    if ( Cuts_L1_DiTau32 && Cuts_Offl_DiTau32_1jet )
      denominator_1jet++;

    if ( Cuts_L1_DiTau32 && Cuts_Offl_DiTau32_2jet )
      denominator_2jet++;
    
  }

  accept_gain_0jet = numerator_0jet/denominator_0jet;
  accept_gain_1jet = numerator_1jet/denominator_1jet;
  accept_gain_2jet = numerator_2jet/denominator_2jet;

  if (is0jet) cout<<process<<", 0-jet, ("<<Threshold_XX<<","<<Threshold_YY<<"): "<<100*(accept_gain_0jet-1)<<"."<<endl;
  else if (is1jet) cout<<process<<", 1-jet, ("<<Threshold_XX<<","<<Threshold_YY<<"): "<<100*(accept_gain_1jet-1)<<"."<<endl;
  else if (is2jet) cout<<process<<", 2-jet, ("<<Threshold_XX<<","<<Threshold_YY<<"): "<<100*(accept_gain_2jet-1)<<"."<<endl;

}

void GetAcceptancePerThr(double thrx = 40, double thry = 30){

	//EvaluateAcceptance("ggH", thrx, thry, true, false, false);
	//EvaluateAcceptance("ggH", thrx, thry, false, true, false);
	//EvaluateAcceptance("ggH", thrx, thry, false, false, true);

	//EvaluateAcceptance("VBF", thrx, thry, true, false, false);
	//EvaluateAcceptance("VBF", thrx, thry, false, true, false);
	//EvaluateAcceptance("VBF", thrx, thry, false, false, true);

	EvaluateAcceptance("ttH", thrx, thry, true, false, false);
	EvaluateAcceptance("ttH", thrx, thry, false, true, false);
	EvaluateAcceptance("ttH", thrx, thry, false, false, true);

}

void test(){

	GetAcceptancePerThr(40,30);
	GetAcceptancePerThr(42,28);
	GetAcceptancePerThr(44,27);
	GetAcceptancePerThr(46,26);
	GetAcceptancePerThr(48,24);

}
