#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include "PUweight.cc"


using namespace std;



void create_PUtree(TString filein, TString fileout, TString treename, TString samplename){
  
  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain(treename);
  //for(unsigned int i=0;i<filein.size();i++)
  //  tree->Add(filein[i]);
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  TTree* tree_new=new TTree(treename,treename);

  TString pu_file_name;

  if (year==2016) pu_file_name = "PU_weights/pu_weights_2016.root";
  else if (year==2017) pu_file_name = "PU_weights/pu_weights_2017.root";
  else if (year==2018) pu_file_name = "PU_weights/pu_weights_2018.root";

  TFile* pu_file = TFile::Open(pu_file_name);
  TH1F* pu_histo = (TH1F*)pu_file->Get("weights");
  
  //New branches
  unsigned long long _EventNumber = -1;
  int _RunNumber = -1, _lumi = -1;

  float _npu;
  float _MC_weight;
  float _MC_weight_originalXWGTUP;
  vector<float> _MC_weights;
  vector<float> _MC_weights_rwgt;
  float _MC_weights_rwgt_sum;
  float _PU_weight_v1;

  tree_new->Branch("EventNumber",&_EventNumber,"EventNumber/l");
  tree_new->Branch("RunNumber",&_RunNumber,"RunNumber/I");
  tree_new->Branch("lumi",&_lumi,"lumi/I");
  tree_new->Branch("npu",&_npu,"npu/F");
  tree_new->Branch("MC_weight",&_MC_weight,"MC_weight/F");
  tree_new->Branch("MC_weight_originalXWGTUP",&_MC_weight_originalXWGTUP);
  tree_new->Branch("MC_weights",&_MC_weights);
  tree_new->Branch("MC_weights_rwgt",&_MC_weights_rwgt);
  tree_new->Branch("MC_weights_rwgt_sum",&_MC_weights_rwgt_sum);
  tree_new->Branch("PU_weight_v1",&_PU_weight_ICHEP18,"PU_weight_v1/F");

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("RunNumber",&_RunNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("npu",&_npu);
  tree->SetBranchAddress("MC_weight",&_MC_weight);
  tree->SetBranchAddress("MC_weight_originalXWGTUP",&_MC_weight_originalXWGTUP);
  tree->SetBranchAddress("MC_weights",&_MC_weights);
  tree->SetBranchAddress("MC_weights_rwgt",&_MC_weights_rwgt);
  tree->SetBranchAddress("MC_weights_rwgt_sum",&_MC_weights_rwgt_sum);

  for(int i=0;i<nentries;i++){ //nentries
  
      if(i%10000==0)
	    cout<<"i="<<i<<endl;

      _npu = 0;
      _MC_weight = 0;
      _MC_weight_originalXWGTUP = 0;
      _MC_weights.clear();
      _MC_weights_rwgt.clear();
      _MC_weights_rwgt_sum = 0;
      _PU_weight_v1 = 0;
      
      tree->GetEntry(i);

      int xbin = pu_histo->FindBin(_npu);
      _PU_weight_v1 = pu_histo->GetBinContent(xbin);
  
      tree_new->Fill();
  }

  f_new->cd();
    
  tree_new->Write();

  f_new->Close();

  return;

}