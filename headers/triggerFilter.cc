#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TH1F.h>
#include <iostream>

using namespace std;

vector<TString> triggerlist;

vector<TString> triggerlist_1e;
vector<TString> triggerlist_1m;
vector<TString> triggerlist_em;
vector<TString> triggerlist_et;
vector<TString> triggerlist_mt;
vector<TString> triggerlist_2e;
vector<TString> triggerlist_2m;
vector<TString> triggerlist_2t;
vector<TString> triggerlist_e2m;
vector<TString> triggerlist_m2e;
vector<TString> triggerlist_3e;
vector<TString> triggerlist_3m;


void produce_triggerlist(int year = 2016){

  //triggers in python config

  triggerlist.clear();

  TString filename;
  if(year==2016) 
    filename="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2016/sync_ntuple_LLRHtautau_ttHNonbb_2016_v9.root";
  else if(year==2017) 
    filename="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2017/sync_ntuple_LLRHtautau_ttHNonbb_2017_v5.root";
  else if(year==2018) 
    filename="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2018/sync_ntuple_LLRHtautau_ttHNonbb_2018_v4.root";

  TFile* f = TFile::Open(filename);
  TH1F* hCounter = (TH1F*)f->Get("HTauTauTree/Counters");

//  for(int itr=1;itr<=hCounter->GetNbinsX();itr++){
  for(int itr=0;itr<=hCounter->GetNbinsX();itr++){
    TString binlabel = hCounter->GetXaxis()->GetBinLabel(itr);
    if(binlabel.BeginsWith("HLT"))triggerlist.push_back(hCounter->GetXaxis()->GetBinLabel(itr));
    //cout<<itr<<" "<<hCounter->GetXaxis()->GetBinLabel(itr)<<endl;
  }
  
  f->Close();


  //triggers to apply

  triggerlist_1e.clear();
  triggerlist_1m.clear();
  triggerlist_em.clear();
  triggerlist_et.clear();
  triggerlist_mt.clear();
  triggerlist_2e.clear();
  triggerlist_2m.clear();
  triggerlist_2t.clear();
  triggerlist_e2m.clear();
  triggerlist_m2e.clear();
  triggerlist_3e.clear();
  triggerlist_3m.clear();

  if(year==2016){

    triggerlist_1e.push_back("HLT_Ele27_WPTight_Gsf_v");
    triggerlist_1e.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
    triggerlist_1e.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

    triggerlist_1m.push_back("HLT_IsoMu22_v");
    triggerlist_1m.push_back("HLT_IsoTkMu22_v");
    triggerlist_1m.push_back("HLT_IsoMu22_eta2p1_v");
    triggerlist_1m.push_back("HLT_IsoTkMu22_eta2p1_v");
    triggerlist_1m.push_back("HLT_IsoMu24_v");
    triggerlist_1m.push_back("HLT_IsoTkMu24_v");

    triggerlist_2e.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");
    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v");
    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

    triggerlist_em.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_em.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_em.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_em.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");

    triggerlist_et.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v");
    triggerlist_et.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v");
    triggerlist_et.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v");

    triggerlist_mt.push_back("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v");

    triggerlist_2t.push_back("HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v");

    triggerlist_3e.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    triggerlist_3m.push_back("HLT_TripleMu_12_10_5_v");

    triggerlist_m2e.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");

    triggerlist_e2m.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");    

  }

  else if(year==2017){

    triggerlist_1e.push_back("HLT_Ele35_WPTight_Gsf_v");
    triggerlist_1e.push_back("HLT_Ele32_WPTight_Gsf_v");

    triggerlist_1m.push_back("HLT_IsoMu24_v");
    triggerlist_1m.push_back("HLT_IsoMu27_v");

    triggerlist_2e.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");

    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");
    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");

    triggerlist_em.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_em.push_back("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_em.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_em.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

    triggerlist_et.push_back("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v");

    triggerlist_mt.push_back("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v");

    triggerlist_2t.push_back("HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v");

    triggerlist_3e.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    triggerlist_3m.push_back("HLT_TripleMu_12_10_5_v");

    triggerlist_m2e.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");

    triggerlist_e2m.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v");

  }

  else if(year==2018){

    triggerlist_1e.push_back("HLT_Ele32_WPTight_Gsf_v");

    triggerlist_1m.push_back("HLT_IsoMu24_v");
    triggerlist_1m.push_back("HLT_IsoMu27_v");

    triggerlist_2e.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");

    triggerlist_2m.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");

    triggerlist_em.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_em.push_back("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_em.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");

    triggerlist_et.push_back("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v");
    triggerlist_et.push_back("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_v");

    triggerlist_mt.push_back("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v");
    triggerlist_mt.push_back("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v");

    triggerlist_2t.push_back("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v");
    triggerlist_2t.push_back("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v");

    triggerlist_3e.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    triggerlist_3m.push_back("HLT_TripleMu_12_10_5_v");

    triggerlist_m2e.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");

    triggerlist_e2m.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v");

  }

}


int FindTriggerIndex(TString triggername){ 
  for(unsigned int it=0;it<triggerlist.size();it++){ 	
  	if(triggerlist.at(it).CompareTo(triggername.Data())==0){
      return it;
    }
  	else {
  	  TString newName=triggername.Data();
  	  newName.Prepend("HLT_");
  	  newName.Append("_v1");
  	  if(triggerlist.at(it).CompareTo(newName.Data())==0){
        return it;
      }
  	}
  }
  return -1;

}

bool IsTriggerFired(Long64_t triggerbit, int triggernumber){ 
  if(triggernumber>=0) { 
    return triggerbit & (long(1) << triggernumber);
  }
  else return -1;
}


bool IsTriggerFired(Long64_t triggerbit, TString triggername){
  return IsTriggerFired(triggerbit,FindTriggerIndex(triggername));
}


bool pass_trigger_list(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_1e(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_1e.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_1e[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_1m(Long64_t triggerbit){ 
  for(unsigned int i=0;i<triggerlist_1m.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_1m[i])){
    	return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_2e(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_2e.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_2e[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}


bool pass_trigger_list_2m(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_2m.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_2m[i])){
      //cout<<"dimu fired"<<endl;
      return true;
    }
    else{
        return false;
    }
  }
  return false;
}


bool pass_trigger_list_em(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_em.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_em[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_et(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_et.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_et[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}


bool pass_trigger_list_mt(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_mt.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_mt[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_2t(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_2t.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_2t[i])){
      return true;
    }
    else{
      return false;
    }
  }
  return false;
}

bool pass_trigger_list_3e(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_3e.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_3e[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_3m(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_3m.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_3m[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_e2m(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_e2m.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_e2m[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

bool pass_trigger_list_m2e(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_m2e.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_m2e[i])){
      return true;
    }
    else{
    	return false;
    }
  }
  return false;
}

