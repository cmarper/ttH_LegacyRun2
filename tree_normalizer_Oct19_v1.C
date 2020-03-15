#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

using namespace std;

void add_pu(TString filein, TString fileout, TString year){
  
  TString treename = "Tree";

  TFile* f_new = TFile::Open(fileout);
  /*if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }*/
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain(treename);
  //for(unsigned int i=0;i<filein.size();i++)
  //  tree->Add(filein[i]);
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  TTree* tree_new=new TTree(treename,treename);

  TString pu_file_name;

  if (year=="2016") pu_file_name = "PU_weights/pu_weights_2016.root";
  else if (year=="2017") pu_file_name = "PU_weights/pu_weights_2017.root";
  else if (year=="2018") pu_file_name = "PU_weights/pu_weights_2018.root";

  TFile* pu_file = TFile::Open(pu_file_name);
  TH1F* pu_histo = (TH1F*)pu_file->Get("weights");
  
  //New branches
  unsigned long long _EventNumber = -1;
  int _RunNumber = -1, _lumi = -1;

  float _npu;
  float _MC_weight;
  float _MC_weight_originalXWGTUP;
  vector<float> *_MC_weights;
  vector<float> *_MC_weights_rwgt;
  float _MC_weights_rwgt_sum;
  float _PU_weight_v1;

  tree_new->Branch("EventNumber",&_EventNumber,"EventNumber/l");
  tree_new->Branch("RunNumber",&_RunNumber,"RunNumber/I");
  tree_new->Branch("lumi",&_lumi,"lumi/I");
  tree_new->Branch("npu",&_npu,"npu/F");
  tree_new->Branch("MC_weight",&_MC_weight,"MC_weight/F");
  tree_new->Branch("MC_weight_originalXWGTUP",&_MC_weight_originalXWGTUP,"MC_weight_originalXWGTUP/F");
  tree_new->Branch("MC_weights",&_MC_weights,"MC_weights");
  tree_new->Branch("MC_weights_rwgt",&_MC_weights_rwgt,"MC_weights_rwgt");
  tree_new->Branch("MC_weights_rwgt_sum",&_MC_weights_rwgt_sum,"MC_weights_rwgt_sum/F");
  tree_new->Branch("PU_weight_v1",&_PU_weight_v1,"PU_weight_v1/F");

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
      _MC_weights->clear();
      _MC_weights_rwgt->clear();
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


void normalize_tree(TString in = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttH_ctcvcp_0.root", 
  TString out = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttH_ctcvcp_norm_0.root",
  TString ye = "2016"){

  TString infile = in;
  TString outfile = out;
  TString yearmc = ye;

  add_pu(infile, outfile, yearmc);

}

void test(){

  normalize_tree("/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_0.root",
    "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_norm_0.root",
    "2017");

  vector<TString> samples;
  samples.clear();

  TString year;

  /*year = "2016";
  samples.push_back("ntuple_Oct19v1_MC_2016_THQ_ctcvcp_0");
  samples.push_back("ntuple_Oct19v1_MC_2016_THQ_ctcvcp_1");
  samples.push_back("ntuple_Oct19v1_MC_2016_THW_ctcvcp_0");
  samples.push_back("ntuple_Oct19v1_MC_2016_THW_ctcvcp_1");*/

  year = "2017";
  samples.push_back("ntuple_Oct19v1_MC_2017_THQ_ctcvcp_0");
  samples.push_back("ntuple_Oct19v1_MC_2017_THQ_ctcvcp_1");
  samples.push_back("ntuple_Oct19v1_MC_2017_THQ_ctcvcp_2");
  samples.push_back("ntuple_Oct19v3_MC_2017_THW_ctcvcp_0");
  samples.push_back("ntuple_Oct19v3_MC_2017_THW_ctcvcp_1");

  /*year = "2018";
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_0");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_1");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_2");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_3");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_4");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_5");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_6");
  samples.push_back("ntuple_Oct19v1_MC_2018_THQ_ctcvcp_7");
  samples.push_back("ntuple_Oct19v1_MC_2018_THW_ctcvcp_0");
  samples.push_back("ntuple_Oct19v1_MC_2018_THW_ctcvcp_1");
  samples.push_back("ntuple_Oct19v1_MC_2018_THW_ctcvcp_2");
  samples.push_back("ntuple_Oct19v1_MC_2018_THW_ctcvcp_3");
  samples.push_back("ntuple_Oct19v1_MC_2018_THW_ctcvcp_4");*/

  for(int isample=0; isample<samples.size(); isample++){

    TString samplein = samples.at(isample)+".root";
    TString dirin = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/"+year+"/nominal/ttH/"+samplein;
    TString sampleout = samples.at(isample)+"_norm.root";
    TString dirout = "/data_CMS/cms/mperez/ntuples_normalized/Oct19/ntuples_converted/"+year+"/nominal/ttH/"+sampleout;
    normalize_tree(samplein,sampleout,year);

  }

}

