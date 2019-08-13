#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TChain.h>
#include <TMath.h>

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


std::tuple< TString, TString, TString, vector<TString> > setup_files(TString sample, int split, int i_split, int JEC, int TES){

  TString dir_in;
  TString dir_out;
  TString file;    
  vector<TString> list;

  ///////////////
  //// SYNC /////
  ///////////////

  if(sample=="sync16"){

    file="sync_ntuple_converted_ttHNonbb_2016_v24";
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2016/";
    list.push_back("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2016/sync_ntuple_LLRHtautau_ttHNonbb_2016_v13.root");

  }

  else if(sample=="sync17"){

    file="sync_ntuple_converted_ttHNonbb_2017_v19";
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2017/";
    list.push_back("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2017/sync_ntuple_LLRHtautau_ttHNonbb_2017_v9.root");

  }

  else if(sample=="sync18"){

    file="sync_ntuple_converted_ttHNonbb_2018_v18";
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2018/";
    list.push_back("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2018/sync_ntuple_LLRHtautau_ttHNonbb_2018_v8.root");

  }


  //////////////////////
  //// Signal 2016 /////
  //////////////////////

  // Datacard production 

  if(sample=="MC_2016_v2_ttHnobb"){ // in process
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/MC_2016_v2_ttHnobb/190812_095310/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=90+1; 
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_THQ_Tune8M1_ctcvcp"){ // completed 97%
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/MC_2016_v1_THQ_Tune8M1_ctcvcp/190703_074930/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=1+1; //95+1
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_THW_Tune8M1_ctcvcp"){ // completed 98%
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/THW_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/MC_2016_v1_THW_Tune8M1_ctcvcp/190703_075115/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=46+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  /*if(sample=="MC_2016_v1_ttH_ctcvcp"){ //running
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
        dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=149+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }*/

  // Training

  if(sample=="MC_2016_v1_TTHnobb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/MC_2016_v1_TTHnobb/190703_073009/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=35+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  /*if(sample=="MC_2016_v2_THQ"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in=""; // FIXME
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=25+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }*/

  if(sample=="MC_2016_v2_THW"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/MC_2016_v2_THW/190812_095453/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=11+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_THQ_TuneCP5_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/THQ_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/MC_2016_v1_THQ_TuneCP5_ctcvcp/190703_074854/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=191+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_THW_TuneCP5_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/MC_2016_v1_THW_TuneCP5_ctcvcp/190703_075040/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=17+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }


  //////////////////////
  //// Signal 2017 /////
  //////////////////////

  // Datacard production 

  if(sample=="MC_2017_v1_ttHJetToNonbb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2017/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2017_v1/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/MC_2017_v1_ttHJetToNonbb/190704_091334/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=208+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2017_v1_THQ_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2017/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2017_v1/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/MC_2017_v1_THQ_ctcvcp/190704_091558/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=258+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2017_v1_THW_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2017/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2017_v1/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/MC_2017_v1_THW_ctcvcp/190704_091632/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=172+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2017_v1_TTH_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2017/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2017_v1/TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/MC_2017_v1_TTH_ctcvcp/190704_091409/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=258+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  // Training

  if(sample=="MC_2017_v1_ttHToNonbb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2017/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2017_v1/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/MC_2017_v1_ttHToNonbb/190704_091446/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=164+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2017_v1_ttHToNonbb_ext1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2017/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2017_v1/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/MC_2017_v1_ttHToNonbb_ext1/190704_091521/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=267+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }


  //////////////////////
  //// Signal 2018 /////
  //////////////////////

  // Datacard production

  if(sample=="MC_2018_v2_ttHJetToNonbb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2018/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2018_v1/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/MC_2018_v2_ttHJetToNonbb/190802_071438/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=261+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  // Datacard production + training (split by odd/even)

  if(sample=="MC_2018_v1_ttHToNonbb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2018/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2018_v1/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/MC_2018_v1_ttHToNonbb/190704_131143/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=224+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2018_v2_THQ_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2018/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2018_v1/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/MC_2018_v2_THQ_ctcvcp/190812_101256/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==7) i_max=793+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2018_v2_THW_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2018/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2018_v1/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/MC_2018_v2_THW_ctcvcp/190812_101330/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==4) i_max=463+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2018_v2_TTH_ctcvcp"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2018/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2018_v1/TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/MC_2018_v2_TTH_ctcvcp/190812_101220/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==7) i_max=720+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }



  //////////////////////////
  //// Background 2016 /////
  //////////////////////////

  //ttV datacards

  if(sample=="MC_2016_v1_TTZ_M10_ext1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_TTZ_M10_ext1/190703_075303/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=49+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTZ_M10_ext2"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_TTZ_M10_ext2/190703_075337/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=48+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTZ_M1to10"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_TTZ_M1to10/190703_075226/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=60+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTWJets"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/MC_2016_v1_TTWJets/190703_075414/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=31+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTWW"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/MC_2016_v1_TTWW/190703_075450/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=22+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  //ttV training

  if(sample=="MC_2016_v1_ttZ"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ttZJets_13TeV_madgraphMLM-pythia8/MC_2016_v1_ttZ/190703_082425/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=80+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ttW"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ttV/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ttWJets_13TeV_madgraphMLM/MC_2016_v1_ttW/190703_082500/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=60+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  //TT

  if(sample=="MC_2016_v1_ST_sCh_lepDecay"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/MC_2016_v1_ST_sCh_lepDecay/190703_075529/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=8+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v2_ST_sCh_lepDecay_PS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_s-channel_4f_leptonDecays_13TeV_PSweights-amcatnlo-pythia8/MC_2016_v2_ST_sCh_lepDecay_PS/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=228+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ST_tCh_top"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/MC_2016_v1_ST_tCh_top/190703_075641/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==4) i_max=449+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ST_tCh_antitop"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/MC_2016_v1_ST_tCh_antitop/190703_075717/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=298+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v2_ST_tCh_antitop_PS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_t-channel_antitop_4f_inclusiveDecays_13TeV_PSweights-powhegV2-madspin/MC_2016_v2_ST_tCh_antitop_PS/190727_150507/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==5) i_max=532+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ST_tW_top"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/MC_2016_v1_ST_tW_top/190703_075839/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=60+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ST_tW_antitop"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/MC_2016_v1_ST_tW_antitop/190703_075918/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=58+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_tWll"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/MC_2016_v1_tWll/190703_075953/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=1+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTTo2L_PS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/MC_2016_v1_TTTo2L_PS/190703_080030/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==7) i_max=778+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTToSemiLep_PS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/MC_2016_v1_TTToSemiLep_PS/190703_080109/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==11) i_max=1105+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTToHad_PS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/MC_2016_v1_TTToHad_PS/190703_080148/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==7) i_max=772+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTJets_DiLep_v1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_TTJets_DiLep_v1/190703_080223/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=48+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTJets_DiLep_ext"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_TTJets_DiLep_ext/190703_080304/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=208+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTJets_TToSingleLep_v1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_TTJets_TToSingleLep_v1/190703_080343/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=97+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  /*if(sample=="MC_2016_v2_TTJets_TToSingleLep_ext"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==4) i_max=407+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }*/

  if(sample=="MC_2016_v1_TTJets_TbarToSingleLep_v1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_TTJets_TbarToSingleLep_v1/190703_080500/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=112+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTJets_TbarToSingleLep_ext"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="TT/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_TTJets_TbarToSingleLep_ext/190703_080539/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==3) i_max=366+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  //ggH

  if(sample=="MC_2016_v3_GGHToTauTau"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="ggH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/GluGluHToTauTau_M125_13TeV_powheg_pythia8/MC_2016_v3_GGHToTauTau/190812_094713/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=11+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  // MISSING
  //GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM
  //GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM
  //GluGluHToWWTo2L2Nu_M125_W10_13TeV_powheg_JHUgen_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM
  //GluGlu_HToMuMu_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM
  //GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM
  //GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM

  //qqH

  if(sample=="MC_2016_v1_VBFHToTauTau"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="qqH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/VBFHToTauTau_M125_13TeV_powheg_pythia8/MC_2016_v1_VBFHToTauTau/190703_081412/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=15+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  // MISSING
  //VBF_HToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM
  //VBFHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM
  //VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM
  //VBF_HToMuMu_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM
  //VBFHToBB_M125_13TeV_amcatnlo_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM
  //VBFHToGG_M125_13TeV_amcatnlo_pythia8_v2/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM

  // Rares

  if(sample=="MC_2016_v1_WWW"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_WWW/190703_080614/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=2+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WWZ"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_WWZ/190703_080651/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=2+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WZZ"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_WZZ/190703_080729/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=3+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ZZZ"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_ZZZ/190703_080805/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=4+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WZG"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_WZG/190703_080840/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=8+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WGToLNuG_ext1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MC_2016_v1_WGToLNuG_ext1/190703_080916/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=45+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WGToLNuG_ext2"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MC_2016_v1_WGToLNuG_ext2/190703_080951/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=73+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WGToLNuG_ext3"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MC_2016_v1_WGToLNuG_ext3/190703_081029/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=90+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ZGToLLG"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MC_2016_v1_ZGToLLG/190703_081106/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=106+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TGJetsLep"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TGJets_leptonDecays_13TeV_amcatnlo_madspin_pythia8/MC_2016_v1_TGJetsLep/190703_081148/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=62+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTGJets_v1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/MC_2016_v1_TTGJets_v1/190703_081223/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=42+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTGJets_ext"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/MC_2016_v1_TTGJets_ext/190703_081301/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=42+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_tZq_ext"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/MC_2016_v1/tZq_ll_4f_13TeV-amcatnlo-pythia8/MC_2016_v1_tZq_ext/190703_081448/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=117+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v2_tZq_PS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/tZq_ll_4f_PSweights_13TeV-amcatnlo-pythia8/MC_2016_v2_tZq_PS/190727_150645/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=268+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WpWpJJ"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/MC_2016_v1_WpWpJJ/190703_081607/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=2+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WW_DS"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/MC_2016_v1_WW_DS/190703_081644/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=8+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_TTTT"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="Rares/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MC_2016_v1_TTTT/190703_081719/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=6+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  //VH

  if(sample=="MC_2016_v1_VHToNonbb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="VH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MC_2016_v1_VHToNonbb/190703_081756/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=10+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ZHTobb"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="VH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/MC_2016_v1_ZHTobb/190703_081832/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=28+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v2_ZHToTauTau"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="VH/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/ZHToTauTau_M125_13TeV_powheg_pythia8/MC_2016_v2_ZHToTauTau/190812_095813/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=7+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  //EWK
  if(sample=="MC_2016_v1_DYJets_M10to50"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_DYJets_M10to50/190703_081951/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=264+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_DYJets_M50"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MC_2016_v1_DYJets_M50/190703_082035/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==8) i_max=871+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WJets_v1"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_WJets_v1/190703_082111/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==2) i_max=215+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WJets_ext"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_2016_v1_WJets_ext/190703_082150/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==4) i_max=410+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WWTo2LNu"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/WWTo2L2Nu_13TeV-powheg/MC_2016_v1_WWTo2LNu/190703_082227/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=16+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_WZTo3LNu"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/MC_2016_v1_WZTo3LNu/190703_082305/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=130+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  if(sample=="MC_2016_v1_ZZTo4L"){ 
    file="ntuple_"+sample;
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/ntuples_converted/";
    dir_out+="2016/";
    if(JEC>0)
      dir_out+="JECup/";
    else if(JEC<0)
      dir_out+="JECdown/";
    else if(TES>0)
      dir_out+="TESup/";
    else if(TES<0)
      dir_out+="TESdown/";
    else
      dir_out+="nominal/";
    dir_out+="EWK/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH_Legacy/ttH_Legacy/MC_2016_v1/ZZTo4L_13TeV_powheg_pythia8/MC_2016_v1_ZZTo4L/190703_082347/";
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=50+1;
    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }
  }

  return std::make_tuple(dir_in, dir_out, file, list);

}
