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
#include <TGraphAsymmErrors.h>
#include <TF1.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "headers/bTagSF.cc"
#include "headers/bTagSF_CSVshape.cc"
//#include "PUReweight.cc"

#include <vector>
#include <map>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif

using namespace std;


bool pT_comparison_pairs(pair<int,TLorentzVector> pair1, pair<int,TLorentzVector> pair2){

  return (pair1.second).Pt()>(pair2.second).Pt();

}

bool pT_comparison_pairs_pdg(pair<pair<int,int>, TLorentzVector> pair1, pair<pair<int,int>, TLorentzVector> pair2){

  return (pair1.second).Pt()>(pair2.second).Pt();

}


bool CSV_comparison_pairs(pair<int,float> pair1, pair<int,float> pair2){

  return pair1.second>pair2.second;

}


pair<int,float> find_i_dRmin_closest(TLorentzVector obj1_tlv,
				     vector<float> obj2_px, vector<float> obj2_py, vector<float> obj2_pz, vector<float> obj2_e){

  int imin = -1;
  float dRmin = 100000;
   
  for(unsigned int i_obj2=0; i_obj2<obj2_e.size(); i_obj2++){

    TLorentzVector obj2_tlv( obj2_px[i_obj2], obj2_py[i_obj2], obj2_pz[i_obj2], obj2_e[i_obj2]);	
    float dR = obj1_tlv.DeltaR(obj2_tlv);
    if(dR<dRmin){
      dRmin=dR;
      imin=i_obj2;
    } 
	
  }

  pair<int,float> p=make_pair(imin,dRmin);

  return p;

}

// PU-reweighting 

TString get_PU_file(TString _sample){
     
  TString _inputFile;

  if (_sample == "GluGluH_2018") _inputFile = "PU_weights_2017/ggHZZ4l.txt";
  else if (_sample == "ttG_2018") _inputFile = "PU_weights_2017/TTGJets.txt";
  else if (_sample == "ttHJet_Hnonbb_2018" || "test") _inputFile = "PU_weights_2017/ttHJetToNonbb.txt";
  else if (_sample == "ntuple_tHQ_local_2018") _inputFile = "PU_weights_2017/THQ.txt";
  else if (_sample == "ntuple_tHW_local_2018") _inputFile = "PU_weights_2017/THW.txt";
  else if (_sample == "TTLeptons_2018") _inputFile = "PU_weights_2017/TTToDiLep.txt";
  else if (_sample == "TTSemileptonic_2018") _inputFile = "PU_weights_2017/TTToSemiLep.txt";
  else if (_sample == "TTTT_2018") _inputFile = "PU_weights_2017/TTTT.txt";
  else if (_sample == "ttW_2018") _inputFile = "PU_weights_2017/TTW.txt";
  else if (_sample == "ttWW_ICHEP2018") _inputFile = "PU_weights_2017/TTWW.txt";
  else if (_sample == "ttZ_2018") _inputFile = "PU_weights_2017/TTZ.txt";
  else if (_sample == "ttZ_lowmass_2018") _inputFile = "PU_weights_2017/TTZ_M1to10.txt";
  else if (_sample == "tZq_2018") _inputFile = "PU_weights_2017/tZq.txt";
  else if (_sample == "WW_2018") _inputFile = "PU_weights_2017/WW.txt";
  else if (_sample == "WW_DoubleScat_2018") _inputFile = "PU_weights_2017/WWds.txt";
  else if (_sample == "WWW_2018") _inputFile = "PU_weights_2017/WWW.txt";
  else if (_sample == "WWZ_2018") _inputFile = "PU_weights_2017/WWZ.txt";
  else if (_sample == "WZ_2018") _inputFile = "PU_weights_2017/WZ.txt";
  else if (_sample == "WZTo3LNu_2018") _inputFile = "PU_weights_2017/WZTo3LNu.txt";
  else if (_sample == "WZZ_2018") _inputFile = "PU_weights_2017/WZZ.txt";
  else if (_sample == "ZZ_2018") _inputFile = "PU_weights_2017/ZZ.txt";
  else if (_sample == "ZZZ_2018") _inputFile = "PU_weights_2017/ZZZ.txt";
  else if (_sample == "WpWp_2018") _inputFile = "PU_weights_2017/WpWp.txt";
  else cout<<"Problem: No PU reweight file!"<<endl;

  return _inputFile;

}

float get_pu_weight(int nPU, bool isMC, TString samplename)
{
    int   nInt_file;
    float PU_file;
    float PU_weight = 0;

    ifstream inputFile(get_PU_file(samplename));

    while (inputFile >> nInt_file >> PU_file){
        if( nPU == nInt_file ) PU_weight = PU_file;
    }
    return PU_weight;
}


// Lepton MVA

float lepMVA_pt;
float lepMVA_eta;
float lepMVA_jetNDauChargedMVASel;
float lepMVA_miniRelIsoCharged;
float lepMVA_miniRelIsoNeutral;
float lepMVA_jetPtRel;
float lepMVA_jetDF;
float lepMVA_jetPtRatio;
float lepMVA_dxy;
float lepMVA_sip3d;
float lepMVA_dz;
float lepMVA_Id;


TMVA::Reader* BookLeptonMVAReader(std::string basePath, std::string weightFileName, std::string type)
{
   TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

   reader->AddVariable("LepGood_pt",                                     &lepMVA_pt);
   reader->AddVariable("LepGood_eta",                                    &lepMVA_eta);
   reader->AddVariable("LepGood_jetNDauChargedMVASel",                   &lepMVA_jetNDauChargedMVASel);
   reader->AddVariable("LepGood_miniRelIsoCharged",                      &lepMVA_miniRelIsoCharged);
   reader->AddVariable("LepGood_miniRelIsoNeutral",                      &lepMVA_miniRelIsoNeutral);
   reader->AddVariable("LepGood_jetPtRelv2",                             &lepMVA_jetPtRel);
   reader->AddVariable("LepGood_jetDF",                                  &lepMVA_jetDF);
   reader->AddVariable("LepGood_jetPtRatio",                             &lepMVA_jetPtRatio);
   reader->AddVariable("LepGood_dxy",                                    &lepMVA_dxy);
   reader->AddVariable("LepGood_sip3d",                                  &lepMVA_sip3d);
   reader->AddVariable("LepGood_dz",                                     &lepMVA_dz);
   if( type == "ele" ) reader->AddVariable("LepGood_mvaFall17V2noIso",   &lepMVA_Id);
   else reader->AddVariable("LepGood_segmentComp",                       &lepMVA_Id);

   reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

   return reader;
}



// variables for BDT multilepton categories

float max_Lep_eta;
float mindr_lep1_jet;
float mindr_lep2_jet;
float met;
float avg_dr_jet;
float MT_met_lep1;
float LepGood_conePt1;
float LepGood_conePt2;
float LepGood_conePt3;
float nJet25_Recl;
float mhtJet25_Recl;

float iF_Recl0;
float iF_Recl1;
float iF_Recl2;


// 2lss MVA ttH vs ttV

TMVA::Reader* Book_2LSS_TTV_MVAReader(std::string basePath, std::string weightFileName)
{
    // weight/2lss_ttV_BDTG.weights.xml
    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", &max_Lep_eta      );
    reader->AddVariable("MT_met_lep1",                                                    &MT_met_lep1      );
    reader->AddVariable("nJet25_Recl",                                                    &nJet25_Recl      );
    reader->AddVariable("mindr_lep1_jet",                                                 &mindr_lep1_jet   );
    reader->AddVariable("mindr_lep2_jet",                                                 &mindr_lep2_jet   );
    reader->AddVariable("LepGood_conePt[iF_Recl[0]]",                                     &LepGood_conePt1  );
    reader->AddVariable("LepGood_conePt[iF_Recl[1]]",                                     &LepGood_conePt2  );

    reader->AddSpectator("iF_Recl[0]",                                                    &iF_Recl0         );
    reader->AddSpectator("iF_Recl[1]",                                                    &iF_Recl1         );
    reader->AddSpectator("iF_Recl[2]",                                                    &iF_Recl2         );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


// 2lss MVA ttH vs ttbar

TMVA::Reader* Book_2LSS_TT_MVAReader(std::string basePath, std::string weightFileName)
{

    // weight/2lss_ttbar_BDTG.weights.xml
    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))",  &max_Lep_eta      );
    reader->AddVariable("nJet25_Recl",                                                     &nJet25_Recl      );
    reader->AddVariable("mindr_lep1_jet",                                                  &mindr_lep1_jet   );
    reader->AddVariable("mindr_lep2_jet",                                                  &mindr_lep2_jet   );
    reader->AddVariable("min(met_pt,400)",                                                 &met              );
    reader->AddVariable("avg_dr_jet",                                                      &avg_dr_jet       );
    reader->AddVariable("MT_met_lep1",                                                     &MT_met_lep1      );

    reader->AddSpectator("iF_Recl[0]",                                                     &iF_Recl0         );
    reader->AddSpectator("iF_Recl[1]",                                                     &iF_Recl1         );
    reader->AddSpectator("iF_Recl[2]",                                                     &iF_Recl2         );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


// 3l MVA ttH vs ttV

TMVA::Reader* Book_3l_TTV_MVAReader(std::string basePath, std::string weightFileName)
{

    // weight/3l_ttV_BDTG.weights.xml
    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", &max_Lep_eta      );
    reader->AddVariable("MT_met_lep1",                                                    &MT_met_lep1      );
    reader->AddVariable("nJet25_Recl",                                                    &nJet25_Recl      );
    reader->AddVariable("mindr_lep1_jet",                                                 &mindr_lep1_jet   );
    reader->AddVariable("mindr_lep2_jet",                                                 &mindr_lep2_jet   );
    reader->AddVariable("LepGood_conePt[iF_Recl[0]]",                                     &LepGood_conePt1  );
    reader->AddVariable("LepGood_conePt[iF_Recl[2]]",                                     &LepGood_conePt3  );

    reader->AddSpectator("iF_Recl[0]",                                                    &iF_Recl0         );
    reader->AddSpectator("iF_Recl[1]",                                                    &iF_Recl1         );
    reader->AddSpectator("iF_Recl[2]",                                                    &iF_Recl2         );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}

// 3l MVA ttH vs ttbar

TMVA::Reader* Book_3l_TT_MVAReader(std::string basePath, std::string weightFileName)
{

    // weight/3l_ttbar_BDTG.weights.xml
    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))",  &max_Lep_eta      );
    reader->AddVariable("MT_met_lep1",                                                     &MT_met_lep1      );
    reader->AddVariable("nJet25_Recl",                                                     &nJet25_Recl      );
    reader->AddVariable("mhtJet25_Recl",                                                   &mhtJet25_Recl    );
    reader->AddVariable("avg_dr_jet",                                                      &avg_dr_jet       );
    reader->AddVariable("mindr_lep1_jet",                                                  &mindr_lep1_jet   );
    reader->AddVariable("mindr_lep2_jet",                                                  &mindr_lep2_jet   );


    reader->AddSpectator("iF_Recl[0]",                                                     &iF_Recl0         );
    reader->AddSpectator("iF_Recl[1]",                                                     &iF_Recl1         );
    reader->AddSpectator("iF_Recl[2]",                                                     &iF_Recl2         );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}


// get fake rates

float fakerate_from_TGraph(TGraphAsymmErrors* graph, float pt){

  int n = graph->GetN();

  double x, y;
  graph->GetPoint(0,x,y);
  if(pt<x)
    return y;

  graph->GetPoint(n-1,x,y);
  if(pt>x)
    return y;
  
  for(int i=0; i<n;i++){

    graph->GetPoint(i,x,y);
    double err_low_x = graph->GetErrorXlow(i);
    double err_high_x = graph->GetErrorXhigh(i);

    if( (x-err_low_x) < pt && pt < (x+err_high_x) )
      return y;

  }

  return -1.;

}


void convert_tree(
      TString sample, 
      int iso_tau=0,
      TString iso_type="byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT", 
      bool conept_sorting=true,
      int split=0, int i_split=0,
      bool isMC=true,
      int JEC=0, int TES=0,
      TString tau_cleaning="presel",
      float year=2016){

  TString dir_in;
  TString dir_out;
  TString file;    

  vector<TString> list;

  // SYNC NTUPLE

  if(sample=="sync16"){

    file="sync_ntuple_converted_ttHNonbb_2016_v15";
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2016/";
    list.push_back("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2016/sync_ntuple_LLRHtautau_ttHNonbb_2016_v9.root");

  }

  else if(sample=="sync17"){

    file="sync_ntuple_converted_ttHNonbb_2017_v10";
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2017/";
    list.push_back("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2017/sync_ntuple_LLRHtautau_ttHNonbb_2017_v5.root");

  }

  else if(sample=="sync18"){

    file="sync_ntuple_converted_ttHNonbb_2018_v9";
    dir_out="/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_converted/2018/";
    list.push_back("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_LLRHtautau/2018/sync_ntuple_LLRHtautau_ttHNonbb_2018_v4.root");

  }

  //MC
 
  /*
  // privately produced samples 

  if(sample=="ntuple_tHW_local_2018"){

    file="ntuple_THW001_v2";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    list.push_back("/data_CMS/cms/mperez/ttH_2017/THW/HTauTauAnalysis_THW001_v2.root");

  }
 
  if(sample=="ntuple_tHQ_local_2018"){

    file="ntuple_THQ001_v2";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    list.push_back("/data_CMS/cms/mperez/ttH_2017/THQ/HTauTauAnalysis_THQ001_v2.root");

  }

  //centrally produced samples

  if(sample=="ttHJet_Hnonbb_2018"){

    file="ntuple_ttH_Hnonbb";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/ttHJetToNonbb_25Jun18/180625_151728/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==10) i_max=1005;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="tHq_2018"){

    file="ntuple_tHq";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/THQ_4f_Hincl_13TeV_madgraph_pythia8/THQ_25Jun18/180625_152339/";
    
    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==3) i_max=350;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }*/


 /*else if(sample=="tHW_2018"){

    file="ntuple_tHW";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    //FIXME file_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/THQ_4f_Hincl_13TeV_madgraph_pythia8/THQ_25Jun18/180625_152339";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==3) i_max=350;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }



  else if(sample=="GluGluH_2018"){

    file="ntuple_GluGluH";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/GluGluHToZZTo4L_25Jun18/180625_152523/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=95;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

	
  else if(sample=="ttZ_2018"){

    file="ntuple_ttZ";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/TTZToLLNuNu_M-10_25Jun18/180625_152751/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==7) i_max=784;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  else if(sample=="ttZ_lowmass_2018"){

    file="ntuple_ttZ_lowmass";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/TTZToLL_M-1to10_25Jun18/180625_152908/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=28;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }



  else if(sample=="ttW_2018"){

    file="ntuple_ttW";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/TTWJetsToLNu_25Jun18/180625_153018/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==5) i_max=511;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  else if(sample=="ttWW_ICHEP2018"){

    file="ntuple_ttWW";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTWW_TuneCP5_13TeV-madgraph-pythia8/TTWW_25Jun18/180625_153202/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=22;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="ttG_2018"){

    file="ntuple_ttG";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/TTGJets_25Jun18/180625_153902/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==4) i_max=472;

    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="ZZZ_2018"){
    
    file="ntuple_ZZZ";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/ZZZ_25Jun18/180625_154614/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=27;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }
  

  else if(sample=="WWW_2018"){
    
    file="ntuple_WWW";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/WWW_25Jun18/180625_154337/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=26;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="WZZ_2018"){
    
    file="ntuple_WZZ";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/WZZ_25Jun18/180625_154522/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=27;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="WWZ_2018"){
    
    file="ntuple_WWZ";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/WWZ_25Jun18/180625_154430/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=26;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }
	
  else if(sample=="WW_DoubleScat_2018"){
    
    file="ntuple_WW_DoubleScat";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WW_DoubleScattering_13TeV-pythia8_TuneCP5/WW_DoubleScattering_25Jun18/180625_154130/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=107;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

	
  else if(sample=="WZ_2018"){

    file="ntuple_WZ";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/WZTo3LNu_25Jun18/180625_153405/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==11) i_max=1157;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="WW_2018"){

    file="ntuple_WW";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/WWTo2L2Nu_25Jun18/180625_153302/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=193;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }



  else if(sample=="ZZ_2018"){

    file="ntuple_ZZ";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/ZZTo4L_13TeV_powheg_pythia8/ZZTo4L_25Jun18/180625_153552/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==7) i_max=738;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="WpWp_2018"){  //take from Marco

    file="ntuple_WpWp";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/WpWpJJ_25Jun18/180625_152651/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==0) i_max=16;

    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  
  else if(sample=="tZq_2018"){

    file="ntuple_tZq";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8//tZq_25Jun18/180625_154000/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==13) i_max=1360;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 
  else if(sample=="TTTT_2018"){

    file="ntuple_TTTT";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/TTTT_25Jun18/180625_154718/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==1) i_max=105;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  
  else if(sample=="TTLeptons_2018"){

    file="ntuple_TTLeptons";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/TTTo2L2Nu_25Jun18/180625_153653/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==9) i_max=900;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  else if(sample=="TTSemileptonic_2018"){

    file="ntuple_TTSemileptonic";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/";

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

    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/MC2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/TTToSemiLeptonic_25Jun18/180625_153801/";

    int i_dir=i_split/10;
    dir_in+=Form("000%i/",i_dir);

    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==42) i_max=4252;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }



 //DATA 

 else if(sample=="DoubleEG_2017B_2018"){

    file="ntuple_DoubleEG_2017B";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleEG/2017B/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleEG/DoubleEG_2017B_25Jun18/180625_204557/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==28) i_max=2845;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleEG_2017C_2018"){

    file="ntuple_DoubleEG_2017C";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleEG/2017C/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleEG/DoubleEG_2017C_8Oct18/181008_083817/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==62) i_max=6289;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleEG_2017D_2018"){

    file="ntuple_DoubleEG_2017D";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleEG/2017D/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleEG/DoubleEG_2017D_25Jun18/180625_204707/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==12) i_max=1290;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleEG_2017E_2018"){

    file="ntuple_DoubleEG_2017E";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleEG/2017E/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleEG/DoubleEG_2017E_8Oct18/181008_083928/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==57) i_max=5786;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleEG_2017F_2018"){

    file="ntuple_DoubleEG_2017F";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleEG/2017F/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleEG/DoubleEG_2017F_25Jun18/180625_204818/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==37) i_max=3722;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleMu_2017B_2018"){

    file="ntuple_DoubleMu_2017B";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleMu/2017B/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleMuon/DoubleMuon_2017B_25Jun18/180625_204232/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==47) i_max=4738;

    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleMu_2017C_2018"){

    file="ntuple_DoubleMu_2017C";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleMu/2017C/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleMuon/DoubleMuon_2017C_25Jun18/180625_204132/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==13) i_max=1358;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleMu_2017D_2018"){

    file="ntuple_DoubleMu_2017D";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleMu/2017D/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleMuon/DoubleMuon_2017D_25Jun18/180625_204313/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==23) i_max=2329;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleMu_2017E_2018"){

    file="ntuple_DoubleMu_2017E";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleMu/2017E/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleMuon/DoubleMuon_2017E_25Jun18/180625_204355/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==52) i_max=5284;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="DoubleMu_2017F_2018"){

    file="ntuple_DoubleMu_2017F";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/DoubleMu/2017F/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/DoubleMuon/DoubleMuon_2017F_25Jun18/180625_204434/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==82) i_max=8260;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="MuonEG_2017B_2018"){

    file="ntuple_MuonEG_2017B";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/MuonEG/2017B/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/MuonEG/MuonEG_2017B_25Jun18/180625_205025/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==4) i_max=411;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="MuonEG_2017C_2018"){

    file="ntuple_MuonEG_2017C";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/MuonEG/2017C/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/MuonEG/MuonEG_2017C_25Jun18/180625_205106/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==14) i_max=1439;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="MuonEG_2017D_2018"){

    file="ntuple_MuonEG_2017D";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/MuonEG/2017D/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/MuonEG/MuonEG_2017D_25Jun18/180625_205144/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==9) i_max=901;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="MuonEG_2017E_2018"){

    file="ntuple_MuonEG_2017E";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/MuonEG/2017E/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/MuonEG/MuonEG_2017E_25Jun18/180625_205218/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==18) i_max=1872;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="MuonEG_2017F_2018"){

    file="ntuple_MuonEG_2017F";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/MuonEG/2017F/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/MuonEG/MuonEG_2017F_25Jun18/180625_205253/";
    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==25) i_max=2547;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

 else if(sample=="SingleMu_2017B_2018"){

    file="ntuple_SingleMu_2017B";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleMu/2017B/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleMuon/SingleMuon_2017B_25Jun18_v4/180626_081815/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==73) i_max=7386;

    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  
 else if(sample=="SingleMu_2017C_2018"){

    file="ntuple_SingleMu_2017C";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleMu/2017C/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleMuon/SingleMuon_2017C_8Oct18/181008_083238/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==59) i_max=5955;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

 else if(sample=="SingleMu_2017D_2018"){

    file="ntuple_SingleMu_2017D";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleMu/2017D/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleMuon/SingleMuon_2017D_25Jun18_v2/180625_202407/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==78) i_max=7879;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="SingleMu_2017E_2018"){

    file="ntuple_SingleMu_2017E";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleMu/2017E/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleMuon/SingleMuon_2017E_25Jun18_v3/180626_082001/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==82) i_max=8216;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="SingleMu_2017F_2018"){

    file="ntuple_SingleMu_2017F";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleMu/2017F/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleMuon/SingleMuon_2017F_25Jun18_v5/180626_082831/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==94) i_max=9441;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  
 else if(sample=="SingleEle_2017B_2018"){

    file="ntuple_SingleEle_2017B";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleEle/2017B/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleElectron/SingleEle_2017B_25Jun18/180625_203715/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==33) i_max=3331;



    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

 
 else if(sample=="SingleEle_2017C_2018"){

    file="ntuple_SingleEle_2017C";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleEle/2017C/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleElectron/SingleEle_2017C_25Jun18/180625_203800/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==74) i_max=7483;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }

  
 else if(sample=="SingleEle_2017D_2018"){

    file="ntuple_SingleEle_2017D";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleEle/2017D/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleElectron/SingleEle_2017D_25Jun18/180625_203844/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==29) i_max=2941;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="SingleEle_2017E_2018"){

    file="ntuple_SingleEle_2017E";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleEle/2017E/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleElectron/SingleEle_2017E_25Jun18/180625_203922/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==58) i_max=5861;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


 else if(sample=="SingleEle_2017F_2018"){

    file="ntuple_SingleEle_2017F";
    dir_out="/data_CMS/cms/mperez/ttH_2017/ntuples_converted/nominal/Data/SingleEle/2017F/";
    dir_in="root://polgrid4.in2p3.fr//store/user/cmartinp/ttH/data2017/SingleElectron/SingleEle_2017F_25Jun18/180625_204001/";

    int i_dir=i_split/10;

    dir_in+=Form("000%i/",i_dir);
    
    int i_min=i_split*100;
    if(i_split==0) i_min++;
    int i_max=(i_split+1)*100;
    if(i_split==74) i_max=7400;


    for(int i=i_min;i<i_max;i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

  }


  else if(sample=="sync_ttH_94X"){
   file="syncNtuple_converted";
   dir_in="/data_CMS/cms/mperez/ttH_2017/sync_ntuples/";
   dir_out="/data_CMS/cms/mperez/ttH_2017/sync_ntuples/";

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
   list.push_back(dir_in+"HTauTauAnalysis.root");
  }

  */

	
  file+=Form("_%i",i_split);

  /*if(iso_type=="")
    file+=Form("_iso%i",iso_tau);
  else
    file+="_"+iso_type;*/

  /*if(tau_cleaning!="presel")
    file+="_"+tau_cleaning+"_tau_cleaning";*/


  if(JEC>0)
    file+="_JECup";
  else if(JEC<0)
    file+="_JECdown";

  if(TES>0)
    file+="_TESup";
  else if(TES<0)
    file+="_TESdown";
  
  file+=".root";

  

  TChain * tree = new TChain("HTauTauTree/HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++){
      tree->Add(list[i]);
  }

  Long64_t nentries = tree->GetEntries();
  //Long64_t nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
 
  f_new = TFile::Open(dir_out+file,"RECREATE");

  //Old branches used
  unsigned long long _EventNumber = -1;
  int _RunNumber = -1, _lumi = -1;
  int _year = -1;

  float _npu = -1.;

  vector<float> *_jets_e;
  vector<float> *_jets_px;
  vector<float> *_jets_py;
  vector<float> *_jets_pz;
  vector<float> *_jets_jecUnc;  
  vector<int>   *_jets_Flavour;
  vector<int>   *_jets_HadronFlavour;

  vector<float> *_jets_PUJetID;
  vector<int>   *_PFjetID;
  vector<float> *_bCSVscore;
  vector<float> *_bDeepCSV_probb;
  vector<float> *_bDeepCSV_probbb;
  vector<float> *_bDeepFlavor_probb;
  vector<float> *_bDeepFlavor_probbb;
  vector<float> *_bDeepFlavor_problepb;
  vector<float> *_jets_QGdiscr;

  vector<float> *_ak8jets_px;
  vector<float> *_ak8jets_py;
  vector<float> *_ak8jets_pz;
  vector<float> *_ak8jets_e;
  vector<float> *_ak8jets_SoftDropMass;
  vector<float> *_ak8jets_PrunedMass;
  vector<float> *_ak8jets_TrimmedMass;
  vector<float> *_ak8jets_FilteredMass;
  vector<float> *_ak8jets_tau1; // subjettiness
  vector<float> *_ak8jets_tau2; // subjettiness
  vector<float> *_ak8jets_tau3; // subjettiness
  vector<float> *_ak8jets_CSV; // CSV score
  vector<int>   *_ak8jets_nsubjets;

  vector<float> *_subjets_px;
  vector<float> *_subjets_py;
  vector<float> *_subjets_pz;
  vector<float> *_subjets_e;
  vector<float> *_subjets_CSV;
  vector<int>   *_subjets_ak8MotherIdx;

  vector<float> *_dxy;
  vector<float> *_dz;
  vector<float> *_dxy_innerTrack;
  vector<float> *_dz_innerTrack;
  vector<float> *_SIP;
  vector<float> *_daughters_rel_error_trackpt;
  vector<int>   *_daughters_muonID;
  vector<int>   *_daughters_eleMissingHits;
  vector<int>   *_daughters_eleMissingLostHits;
  vector<bool>  *_daughters_passConversionVeto;
  vector<float> *_daughters_SCeta;
  vector<float> *_daughters_IetaIeta;
  vector<float> *_daughters_full5x5_IetaIeta;
  vector<float> *_daughters_hOverE;
  vector<float> *_daughters_deltaEtaSuperClusterTrackAtVtx;
  vector<float> *_daughters_deltaPhiSuperClusterTrackAtVtx;
  vector<float> *_daughters_IoEmIoP_ttH;
  vector<float> *_daughters_eleMVAnt;
  vector<float> *_daughters_eleMVAntNoIso;
  vector<float> *_daughters_eleMVA_HZZ;
  vector<bool> *_daughters_iseleWPLoose;
  vector<bool> *_daughters_iseleNoIsoWPLoose;

  vector<float> *_daughters_e;
  vector<float> *_daughters_px;
  vector<float> *_daughters_py;
  vector<float> *_daughters_pz;
  vector<int>   *_daughters_matchedJetIndex;

  vector<float> *_daughters_ecalTrkEnergyPostCorr;
  vector<float> *_daughters_ecalTrkEnergyPreCorr;
  vector<float> *_daughters_corr_ele;//correction SF
  vector<float> *_daughters_pt_corr;//corrected pt
  vector<float> *_daughters_energy_corr;//corrected energy

  vector<int>   *_daughters_TauUpExists;
  vector<float> *_daughters_e_TauUp;
  vector<float> *_daughters_px_TauUp;
  vector<float> *_daughters_py_TauUp;
  vector<float> *_daughters_pz_TauUp;
  vector<int>   *_daughters_TauDownExists;
  vector<float> *_daughters_e_TauDown;
  vector<float> *_daughters_px_TauDown;
  vector<float> *_daughters_py_TauDown;
  vector<float> *_daughters_pz_TauDown;

  vector<int>   *_PDGIdDaughters;
  vector<int>   *_decayMode;
  vector<float> *_combreliso;
  vector<float> *_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits;
  vector<int>   *_daughters_decayModeFindingOldDMs;
  vector<int>   *_daughters_decayModeFindingNewDMs;
  vector<float> *_daughters_byIsolationMVArun2017v2DBoldDMwLTraw2017;
  vector<Long64_t> *_tauID;

  Long64_t _triggerbit;
  Int_t _metfilterbit;
  bool _passecalBadCalibFilterUpdate;

  vector<int>   *_daughters_jetNDauChargedMVASel;
  vector<float> *_daughters_miniRelIsoCharged;
  vector<float> *_daughters_miniRelIsoNeutral;
  vector<float> *_daughters_jetPtRel;
  vector<float> *_daughters_jetPtRatio;
  vector<float> *_daughters_jetBTagCSV;
  vector<float> *_daughters_jetBTagDeepCSV;
  vector<float> *_daughters_jetBTagDeepJet;
  vector<float> *_daughters_lepMVA_mvaId;
  vector<bool>  *_daughters_iseleChargeConsistent;

  vector<float> *_daughters_miniRelIsoCharged_nanoAOD;
  vector<float> *_daughters_miniRelIso_nanoAOD;
  vector<float> *_daughters_PFRelIsoCharged_nanoAOD;
  vector<float> *_daughters_PFRelIsoAll_nanoAOD;
  vector<float> *_daughters_PFRelIsoAll04_nanoAOD;
  vector<float> *_daughters_jetPtRatio_nanoAOD;
  vector<float> *_daughters_jetPtRel_nanoAOD;
  vector<float> *_daughters_jetNDauChargedMVASel_nanoAOD;

  float _met;
  float _metphi;

  vector<float> *_genpart_px;
  vector<float> *_genpart_py;
  vector<float> *_genpart_pz;
  vector<float> *_genpart_e;
  vector<int> *_genpart_pdg;
  vector<int> *_genpart_HMothInd;
  vector<int> *_genpart_ZMothInd;
  vector<int> *_genpart_TopMothInd;
  vector<int> *_genpart_WMothInd;
  vector<int> *_genpart_bMothInd;
  vector<int> *_genpart_TauMothInd;
  vector<int> *_genpart_TopDecayMode;
  vector<int> *_genpart_WDecayMode;
  vector<int> *_genpart_HZDecayMode;
  vector<int> *_genpart_TauGenDecayMode;
  vector<int> *_genpart_flags;
  vector<int> *_genpart_status;

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("RunNumber",&_RunNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("year",&_year);

  tree->SetBranchAddress("jets_px",&_jets_px);
  tree->SetBranchAddress("jets_py",&_jets_py);
  tree->SetBranchAddress("jets_pz",&_jets_pz);
  tree->SetBranchAddress("jets_e",&_jets_e);
  tree->SetBranchAddress("jets_jecUnc",&_jets_jecUnc);
  tree->SetBranchAddress("jets_Flavour",&_jets_Flavour);
  tree->SetBranchAddress("jets_HadronFlavour",&_jets_HadronFlavour);
  tree->SetBranchAddress("jets_PUJetID",&_jets_PUJetID);
  tree->SetBranchAddress("PFjetID",&_PFjetID);
  tree->SetBranchAddress("bCSVscore",&_bCSVscore);
  tree->SetBranchAddress("bDeepCSV_probb",&_bDeepCSV_probb); 
  tree->SetBranchAddress("bDeepCSV_probbb",&_bDeepCSV_probbb); 
  tree->SetBranchAddress("bDeepFlavor_probb",&_bDeepFlavor_probb); 
  tree->SetBranchAddress("bDeepFlavor_probbb",&_bDeepFlavor_probbb); 
  tree->SetBranchAddress("bDeepFlavor_problepb",&_bDeepFlavor_problepb);   
  tree->SetBranchAddress("jets_QGdiscr",&_jets_QGdiscr);

  tree->SetBranchAddress("ak8jets_px", &_ak8jets_px);
  tree->SetBranchAddress("ak8jets_py", &_ak8jets_py);
  tree->SetBranchAddress("ak8jets_pz", &_ak8jets_pz);
  tree->SetBranchAddress("ak8jets_e", &_ak8jets_e);
  tree->SetBranchAddress("ak8jets_SoftDropMass", &_ak8jets_SoftDropMass);
  tree->SetBranchAddress("ak8jets_PrunedMass", &_ak8jets_PrunedMass);
  tree->SetBranchAddress("ak8jets_TrimmedMass", &_ak8jets_TrimmedMass);
  tree->SetBranchAddress("ak8jets_FilteredMass", &_ak8jets_FilteredMass);
  tree->SetBranchAddress("ak8jets_tau1", &_ak8jets_tau1);
  tree->SetBranchAddress("ak8jets_tau2", &_ak8jets_tau2);
  tree->SetBranchAddress("ak8jets_tau3", &_ak8jets_tau3);
  tree->SetBranchAddress("ak8jets_CSV", &_ak8jets_CSV);
  tree->SetBranchAddress("ak8jets_nsubjets", &_ak8jets_nsubjets);

  tree->SetBranchAddress("subjets_px", &_subjets_px);
  tree->SetBranchAddress("subjets_py", &_subjets_py);
  tree->SetBranchAddress("subjets_pz", &_subjets_pz);
  tree->SetBranchAddress("subjets_e", &_subjets_e);
  tree->SetBranchAddress("subjets_CSV", &_subjets_CSV);
  tree->SetBranchAddress("subjets_ak8MotherIdx", &_subjets_ak8MotherIdx);

  tree->SetBranchAddress("dxy",&_dxy);
  tree->SetBranchAddress("dz",&_dz);
  tree->SetBranchAddress("dxy_innerTrack",&_dxy_innerTrack);
  tree->SetBranchAddress("dz_innerTrack",&_dz_innerTrack);
  tree->SetBranchAddress("SIP",&_SIP);
  tree->SetBranchAddress("daughters_rel_error_trackpt",&_daughters_rel_error_trackpt);
  tree->SetBranchAddress("daughters_muonID",&_daughters_muonID);
  tree->SetBranchAddress("daughters_eleMissingHits",&_daughters_eleMissingHits);
  tree->SetBranchAddress("daughters_eleMissingLostHits",&_daughters_eleMissingLostHits);
  tree->SetBranchAddress("daughters_passConversionVeto",&_daughters_passConversionVeto);
  tree->SetBranchAddress("daughters_SCeta",&_daughters_SCeta);
  tree->SetBranchAddress("daughters_IetaIeta",&_daughters_IetaIeta);
  tree->SetBranchAddress("daughters_full5x5_IetaIeta",&_daughters_full5x5_IetaIeta);
  tree->SetBranchAddress("daughters_hOverE",&_daughters_hOverE);
  tree->SetBranchAddress("daughters_deltaEtaSuperClusterTrackAtVtx",&_daughters_deltaEtaSuperClusterTrackAtVtx);
  tree->SetBranchAddress("daughters_deltaPhiSuperClusterTrackAtVtx",&_daughters_deltaPhiSuperClusterTrackAtVtx);
  tree->SetBranchAddress("daughters_IoEmIoP_ttH",&_daughters_IoEmIoP_ttH);
  tree->SetBranchAddress("daughters_eleMVAnt",&_daughters_eleMVAnt);
  tree->SetBranchAddress("daughters_eleMVAntNoIso",&_daughters_eleMVAntNoIso);
  tree->SetBranchAddress("daughters_eleMVA_HZZ",&_daughters_eleMVA_HZZ);
  tree->SetBranchAddress("daughters_iseleWPLoose",&_daughters_iseleWPLoose);
  tree->SetBranchAddress("daughters_iseleNoIsoWPLoose",&_daughters_iseleNoIsoWPLoose);

  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("daughters_matchedJetIndex",&_daughters_matchedJetIndex);

  tree->SetBranchAddress("daughters_ecalTrkEnergyPostCorr",&_daughters_ecalTrkEnergyPostCorr);
  tree->SetBranchAddress("daughters_ecalTrkEnergyPreCorr",&_daughters_ecalTrkEnergyPreCorr);
  tree->SetBranchAddress("daughters_corr_ele",&_daughters_corr_ele);
  tree->SetBranchAddress("daughters_pt_corr",&_daughters_pt_corr);
  tree->SetBranchAddress("daughters_energy_corr",&_daughters_energy_corr);
  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree->SetBranchAddress("decayMode",&_decayMode);
  tree->SetBranchAddress("combreliso",&_combreliso);
  tree->SetBranchAddress("daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits",&_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits);
  tree->SetBranchAddress("daughters_decayModeFindingOldDMs",&_daughters_decayModeFindingOldDMs);
  tree->SetBranchAddress("daughters_decayModeFindingNewDMs",&_daughters_decayModeFindingNewDMs);
  tree->SetBranchAddress("tauID",&_tauID);
  tree->SetBranchAddress("triggerbit",&_triggerbit);
  tree->SetBranchAddress("metfilterbit",&_metfilterbit);
  tree->SetBranchAddress("passecalBadCalibFilterUpdate",&_passecalBadCalibFilterUpdate);

  tree->SetBranchAddress("daughters_byIsolationMVArun2017v2DBoldDMwLTraw2017",&_daughters_byIsolationMVArun2017v2DBoldDMwLTraw2017);

  tree->SetBranchAddress("daughters_jetNDauChargedMVASel",&_daughters_jetNDauChargedMVASel);
  tree->SetBranchAddress("daughters_miniRelIsoCharged",&_daughters_miniRelIsoCharged);
  tree->SetBranchAddress("daughters_miniRelIsoNeutral",&_daughters_miniRelIsoNeutral);
  tree->SetBranchAddress("daughters_jetPtRel",&_daughters_jetPtRel);
  tree->SetBranchAddress("daughters_jetPtRatio",&_daughters_jetPtRatio);
  tree->SetBranchAddress("daughters_jetBTagCSV",&_daughters_jetBTagCSV);
  tree->SetBranchAddress("daughters_jetBTagDeepCSV",&_daughters_jetBTagDeepCSV);
  tree->SetBranchAddress("daughters_jetBTagDeepJet",&_daughters_jetBTagDeepJet);
  tree->SetBranchAddress("daughters_lepMVA_mvaId",&_daughters_lepMVA_mvaId);
  tree->SetBranchAddress("daughters_iseleChargeConsistent",&_daughters_iseleChargeConsistent);

  tree->SetBranchAddress("daughters_miniRelIsoCharged_nanoAOD",&_daughters_miniRelIsoCharged_nanoAOD);
  tree->SetBranchAddress("daughters_miniRelIso_nanoAOD",&_daughters_miniRelIso_nanoAOD);
  tree->SetBranchAddress("daughters_PFRelIsoCharged_nanoAOD",&_daughters_PFRelIsoCharged_nanoAOD);
  tree->SetBranchAddress("daughters_PFRelIsoAll_nanoAOD",&_daughters_PFRelIsoAll_nanoAOD);
  tree->SetBranchAddress("daughters_PFRelIsoAll04_nanoAOD",&_daughters_PFRelIsoAll04_nanoAOD);

  tree->SetBranchAddress("daughters_jetPtRatio_nanoAOD",&_daughters_jetPtRatio_nanoAOD);
  tree->SetBranchAddress("daughters_jetPtRel_nanoAOD",&_daughters_jetPtRel_nanoAOD);
  tree->SetBranchAddress("daughters_jetNDauChargedMVASel_nanoAOD",&_daughters_jetNDauChargedMVASel_nanoAOD);

  tree->SetBranchAddress("met",&_met);
  tree->SetBranchAddress("metphi",&_metphi);  

  if(isMC){

    tree->SetBranchAddress("npu",&_npu);

    tree->SetBranchAddress("daughters_TauUpExists",&_daughters_TauUpExists);
    tree->SetBranchAddress("daughters_px_TauUp",&_daughters_px_TauUp);
    tree->SetBranchAddress("daughters_py_TauUp",&_daughters_py_TauUp);
    tree->SetBranchAddress("daughters_pz_TauUp",&_daughters_pz_TauUp);
    tree->SetBranchAddress("daughters_e_TauUp",&_daughters_e_TauUp);
    
    tree->SetBranchAddress("daughters_TauDownExists",&_daughters_TauDownExists);
    tree->SetBranchAddress("daughters_px_TauDown",&_daughters_px_TauDown);
    tree->SetBranchAddress("daughters_py_TauDown",&_daughters_py_TauDown);
    tree->SetBranchAddress("daughters_pz_TauDown",&_daughters_pz_TauDown);
    tree->SetBranchAddress("daughters_e_TauDown",&_daughters_e_TauDown);

    tree->SetBranchAddress("genpart_px",&_genpart_px);
    tree->SetBranchAddress("genpart_py",&_genpart_py);
    tree->SetBranchAddress("genpart_pz",&_genpart_pz);
    tree->SetBranchAddress("genpart_e",&_genpart_e);
    tree->SetBranchAddress("genpart_pdg",&_genpart_pdg);
    tree->SetBranchAddress("genpart_HMothInd",&_genpart_HMothInd);
    tree->SetBranchAddress("genpart_ZMothInd",&_genpart_ZMothInd);
    tree->SetBranchAddress("genpart_TopMothInd",&_genpart_TopMothInd);
    tree->SetBranchAddress("genpart_WMothInd",&_genpart_WMothInd);  
    tree->SetBranchAddress("genpart_bMothInd",&_genpart_bMothInd);    
    tree->SetBranchAddress("genpart_TauMothInd",&_genpart_TauMothInd);
    tree->SetBranchAddress("genpart_TopDecayMode",&_genpart_TopDecayMode);
    tree->SetBranchAddress("genpart_WDecayMode",&_genpart_WDecayMode);
    tree->SetBranchAddress("genpart_HZDecayMode",&_genpart_HZDecayMode);
    tree->SetBranchAddress("genpart_TauGenDecayMode",&_genpart_TauGenDecayMode);
    tree->SetBranchAddress("genpart_flags",&_genpart_flags);
    tree->SetBranchAddress("genpart_status",&_genpart_status); 
 
  }


  TTree* tree_new=tree->GetTree()->CloneTree(0);
  if(JEC!=0 || TES!=0)
    tree_new=new TTree("HTauTauTree","HTauTauTree");

  //New branches

  vector<float> _daughters_pt;
  vector<float> _daughters_eta;
  vector<float> _daughters_phi;
  vector<float> _daughters_dR_closest_jet;

  vector<float> _jets_pt;
  vector<float> _jets_eta;
  vector<float> _jets_phi;

  int _n_recomu_presel;
  int _n_recomu_fakeable;
  int _n_recomu_cutsel;
  int _n_recomu_mvasel;

  vector<int>   _recomu_charge;
  vector<float> _recomu_e;
  vector<float> _recomu_px;
  vector<float> _recomu_py;
  vector<float> _recomu_pz;
  vector<float> _recomu_pt;
  vector<float> _recomu_conept;
  vector<float> _recomu_eta;
  vector<float> _recomu_phi;
  vector<float> _recomu_dxy;
  vector<float> _recomu_dz;
  vector<float> _recomu_dxy_innerTrack;
  vector<float> _recomu_dz_innerTrack;
  vector<int>   _recomu_jetNDauChargedMVASel;
  vector<int>   _recomu_jetNDauChargedMVASel_nanoAOD;
  vector<float> _recomu_miniRelIso;
  vector<float> _recomu_miniRelIso_nanoAOD;
  vector<float> _recomu_miniIsoCharged;
  vector<float> _recomu_miniIsoCharged_nanoAOD;
  vector<float> _recomu_miniIsoNeutral;
  vector<float> _recomu_miniIsoNeutral_nanoAOD;
  vector<float> _recomu_combreliso04;
  vector<float> _recomu_sip3D;
  vector<float> _recomu_jetPtRel;
  vector<float> _recomu_jetPtRel_nanoAOD;
  vector<float> _recomu_jetCSV;
  vector<float> _recomu_jetDeepCSV;
  vector<float> _recomu_jetDeepJet;
  vector<float> _recomu_jetPtRatio;
  vector<float> _recomu_jetPtRatio_nanoAOD;
  vector<float> _recomu_lepMVA_Id;
  vector<float> _recomu_leptonMVA;
  vector<float> _recomu_rel_error_trackpt;
  vector<bool>  _recomu_mediumID;
  vector<bool>  _recomu_isfakeable;
  vector<bool>  _recomu_iscutsel;
  vector<bool>  _recomu_ismvasel;
  vector<int>   _recomu_TopMothInd;
  vector<int>   _recomu_HMothInd;
  vector<int>   _recomu_goodsign;
  vector<float> _recomu_fakerate;
  vector<float> _recomu_fakerate_up;
  vector<float> _recomu_fakerate_down;
  vector<float> _recomu_fakerate_pt1;
  vector<float> _recomu_fakerate_pt2;
  vector<float> _recomu_fakerate_be1;
  vector<float> _recomu_fakerate_be2;
  vector<float> _recomu_fakerate_QCD_MC;
  vector<float> _recomu_fakerate_ttbar_MC;
  vector<bool>  _recomu_isGenMatched;
  vector<int>   _recomu_genMatchInd;
  vector<bool>  _recomu_isGenChargeMatched;
  vector<int>   _recomu_matchedJetIndex;

  int _n_recoele_presel;
  int _n_recoele_fakeable;
  int _n_recoele_cutsel;
  int _n_recoele_mvasel;

  vector<int>   _recoele_charge;
  vector<float> _recoele_e;
  vector<float> _recoele_px;
  vector<float> _recoele_py;
  vector<float> _recoele_pz;
  vector<float> _recoele_pt;
  vector<float> _recoele_corr_e;
  vector<float> _recoele_corr_pt;
  vector<float> _recoele_conept;
  vector<float> _recoele_eta;
  vector<float> _recoele_phi;
  vector<float> _recoele_dxy;
  vector<float> _recoele_dz;
  vector<int>   _recoele_jetNDauChargedMVASel;
  vector<int>   _recoele_jetNDauChargedMVASel_nanoAOD;
  vector<float> _recoele_miniRelIso;
  vector<float> _recoele_miniRelIso_nanoAOD;
  vector<float> _recoele_PFRelIsoAll_nanoAOD;
  vector<float> _recoele_PFRelIsoAll04_nanoAOD;
  vector<float> _recoele_miniIsoCharged;
  vector<float> _recoele_miniIsoCharged_nanoAOD;
  vector<float> _recoele_PFIsoCharged_nanoAOD;
  vector<float> _recoele_miniIsoNeutral;
  vector<float> _recoele_miniIsoNeutral_nanoAOD;
  vector<float> _recoele_PFIsoNeutral_nanoAOD;
  vector<float> _recoele_sip3D;
  vector<float> _recoele_jetPtRel;
  vector<float> _recoele_jetPtRel_nanoAOD;
  vector<float> _recoele_jetCSV;
  vector<float> _recoele_jetDeepCSV;
  vector<float> _recoele_jetDeepJet;
  vector<float> _recoele_jetPtRatio;
  vector<float> _recoele_jetPtRatio_nanoAOD;
  vector<float> _recoele_lepMVA_Id;
  vector<float> _recoele_leptonMVA;
  vector<bool>  _recoele_isChargeConsistent;
  vector<bool>  _recoele_passConversionVeto;
  vector<int>   _recoele_nMissingHits;
  vector<float> _recoele_sigmaEtaEta; 
  vector<float> _recoele_HoE;
  vector<float> _recoele_deltaEta;
  vector<float> _recoele_deltaPhi; 
  vector<float> _recoele_OoEminusOoP;
  vector<bool>  _recoele_isfakeable;
  vector<bool>  _recoele_iscutsel;
  vector<bool>  _recoele_ismvasel;
  vector<int>   _recoele_TopMothInd;
  vector<int>   _recoele_HMothInd;
  vector<int>   _recoele_goodsign;
  vector<float> _recoele_fakerate;
  vector<float> _recoele_fakerate_up;
  vector<float> _recoele_fakerate_down;
  vector<float> _recoele_fakerate_pt1;
  vector<float> _recoele_fakerate_pt2;
  vector<float> _recoele_fakerate_be1;
  vector<float> _recoele_fakerate_be2;
  vector<float> _recoele_fakerate_QCD_MC;
  vector<float> _recoele_fakerate_ttbar_MC;
  vector<float> _recoele_QFrate; 
  vector<bool>  _recoele_isGenMatched;
  vector<int>   _recoele_genMatchInd;
  vector<bool>  _recoele_isGenChargeMatched;
  vector<int>   _recoele_matchedJetIndex;

  int _n_recolep_presel;
  int _n_recolep_fakeable;
  int _n_recolep_cutsel;
  int _n_recolep_mvasel;

  vector<int>   _recolep_charge;
  vector<int>   _recolep_pdg;
  vector<float> _recolep_e;
  vector<float> _recolep_px;
  vector<float> _recolep_py;
  vector<float> _recolep_pz;
  vector<float> _recolep_pt;
  vector<float> _recolep_conept;
  vector<float> _recolep_eta;
  vector<float> _recolep_phi;
  vector<float> _recolep_leptonMVA;
  vector<float> _recolep_fakerate;
  vector<float> _recolep_fakerate_up;
  vector<float> _recolep_fakerate_down;
  vector<float> _recolep_fakerate_pt1;
  vector<float> _recolep_fakerate_pt2;
  vector<float> _recolep_fakerate_be1;
  vector<float> _recolep_fakerate_be2;
  vector<float> _recolep_fakerate_QCD_MC;
  vector<float> _recolep_fakerate_ttbar_MC;
  vector<float> _recolep_QFrate; 
  vector<bool>  _recolep_isfakeable;
  vector<bool>  _recolep_iscutsel;
  vector<bool>  _recolep_ismvasel;
  vector<bool>  _recolep_tightcharge;
  vector<bool>  _recolep_eleconv_misshits;
  vector<bool>  _recolep_isGenMatched;
  vector<bool>  _recolep_isGenChargeMatched;
  vector<int>   _recolep_genMatchInd;


  int _n_recotauh;

  vector<int>   _recotauh_charge;
  vector<int>   _recotauh_decayMode;
  vector<float> _recotauh_e;
  vector<float> _recotauh_px;
  vector<float> _recotauh_py;
  vector<float> _recotauh_pz;
  vector<float> _recotauh_pt;
  vector<float> _recotauh_eta;
  vector<float> _recotauh_phi;
  vector<float> _recotauh_dxy;
  vector<float> _recotauh_dz;
  vector<float> _recotauh_iso;
  vector<bool>  _recotauh_isGenMatched;
  vector<int>   _recotauh_genMatchInd;
  vector<int>   _recotauh_matchedJetIndex;

  vector<int>   _recotauh_decayModeFindingOldDMs;
  vector<int>   _recotauh_decayModeFindingNewDMs;
  vector<int>   _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>   _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>   _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>   _recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<int>   _recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT;
  vector<float> _recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw;
  vector<int>   _recotauh_againstMuonLoose3;
  vector<int>   _recotauh_againstMuonTight3;
  vector<int>   _recotauh_againstElectronVLooseMVA6;
  vector<int>   _recotauh_againstElectronLooseMVA6;
  vector<int>   _recotauh_againstElectronMediumMVA6;
  vector<int>   _recotauh_againstElectronTightMVA6;
  vector<int>   _recotauh_againstElectronVTightMVA6;

  vector<float> _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT;
  vector<float> _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT;
  vector<float> _recotauh_fakerate_byTightIsolationMVArun2v2017v2DBdR03oldDMwLT;
  vector<float> _recotauh_fakerate_byVTightIsolationMVArun2v2017v2DBdR03oldDMwLT;

  vector<float> _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Up;
  vector<float> _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Down;
  vector<float> _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Up;
  vector<float> _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Down;

  vector<float> _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Up;
  vector<float> _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Down;
  vector<float> _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Up;
  vector<float> _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Down;


  vector<int> _recotauh_i_closest_genpart;
  vector<float> _recotauh_dR_closest_genpart;

  int _n_recoPFJet;

  vector<float> _recoPFJet_e;
  vector<float> _recoPFJet_pt;
  vector<float> _recoPFJet_px;
  vector<float> _recoPFJet_py;
  vector<float> _recoPFJet_pz;
  vector<float> _recoPFJet_eta;
  vector<float> _recoPFJet_phi;
  vector<float> _recoPFJet_CSVscore;
  vector<float> _recoPFJet_DeepCSVscore;
  vector<float> _recoPFJet_DeepJetscore;
  vector<float> _recoPFJet_jecUnc;
  vector<int>   _recoPFJet_Flavour; 
  vector<int>   _recoPFJet_hadronFlavour; 
  vector<float> _recoPFJet_QGdiscr;

  int _n_recoPFFwdJet;

  vector<float> _recoPFFwdJet_e;
  vector<float> _recoPFFwdJet_pt;
  vector<float> _recoPFFwdJet_px;
  vector<float> _recoPFFwdJet_py;
  vector<float> _recoPFFwdJet_pz;
  vector<float> _recoPFFwdJet_eta;
  vector<float> _recoPFFwdJet_phi;
  vector<float> _recoPFFwdJet_CSVscore;
  vector<float> _recoPFFwdJet_DeepCSVscore;
  vector<float> _recoPFFwdJet_DeepJetscore;
  vector<float> _recoPFFwdJet_jecUnc;
  vector<int>   _recoPFFwdJet_Flavour; 
  vector<int>   _recoPFFwdJet_hadronFlavour; 
  vector<float> _recoPFFwdJet_QGdiscr;

  int _n_recoPFak8Jet;
 
  vector<float> _recoPFak8Jet_e;
  vector<float> _recoPFak8Jet_pt;
  vector<float> _recoPFak8Jet_px;
  vector<float> _recoPFak8Jet_py;
  vector<float> _recoPFak8Jet_pz;
  vector<float> _recoPFak8Jet_eta;
  vector<float> _recoPFak8Jet_phi;
  vector<float> _recoPFak8Jet_SoftDropMass;
  vector<float> _recoPFak8Jet_tau1; 
  vector<float> _recoPFak8Jet_tau2;
  vector<float> _recoPFak8Jet_tau3;
  vector<int>   _recoPFak8Jet_nsubjets;

  vector<vector<float>> _recoPFak8Jet_subjets_e;
  vector<vector<float>> _recoPFak8Jet_subjets_pt;
  vector<vector<float>> _recoPFak8Jet_subjets_px;
  vector<vector<float>> _recoPFak8Jet_subjets_py;
  vector<vector<float>> _recoPFak8Jet_subjets_pz;
  vector<vector<float>> _recoPFak8Jet_subjets_eta;
  vector<vector<float>> _recoPFak8Jet_subjets_phi;
  vector<vector<int>>   _recoPFak8Jet_subjets_ak8MotherIdx;

  vector<int>   _recoPFJet_i_closest_genpart;
  vector<float> _recoPFJet_dR_closest_genpart;
  vector<int>   _recoPFJet_i_2nd_closest_genpart;
  vector<float> _recoPFJet_dR_2nd_closest_genpart;
  vector<int>   _recoPFJet_i_closest_tau;
  vector<float> _recoPFJet_dR_closest_tau;

  vector<float> _recoPFJet_CSVsort_e;
  vector<float> _recoPFJet_CSVsort_pt;
  vector<float> _recoPFJet_CSVsort_px;
  vector<float> _recoPFJet_CSVsort_py;
  vector<float> _recoPFJet_CSVsort_pz;
  vector<float> _recoPFJet_CSVsort_eta;
  vector<float> _recoPFJet_CSVsort_phi;
  vector<float> _recoPFJet_CSVsort_CSVscore;
  vector<float> _recoPFJet_CSVsort_DeepCSVscore;
  vector<float> _recoPFJet_CSVsort_DeepJetscore;
  vector<float> _recoPFJet_CSVsort_jecUnc;
  vector<int>   _recoPFJet_CSVsort_Flavour; 
  vector<int>   _recoPFJet_CSVsort_hadronFlavour; 
  vector<float> _recoPFJet_CSVsort_QGdiscr;
  
  vector<float> _recoPFJet_DeepCSVsort_e;
  vector<float> _recoPFJet_DeepCSVsort_pt;
  vector<float> _recoPFJet_DeepCSVsort_px;
  vector<float> _recoPFJet_DeepCSVsort_py;
  vector<float> _recoPFJet_DeepCSVsort_pz;
  vector<float> _recoPFJet_DeepCSVsort_eta;
  vector<float> _recoPFJet_DeepCSVsort_phi;
  vector<float> _recoPFJet_DeepCSVsort_CSVscore;
  vector<float> _recoPFJet_DeepCSVsort_DeepCSVscore;
  vector<float> _recoPFJet_DeepCSVsort_DeepJetscore;
  vector<float> _recoPFJet_DeepCSVsort_jecUnc;
  vector<int>   _recoPFJet_DeepCSVsort_Flavour; 
  vector<int>   _recoPFJet_DeepCSVsort_hadronFlavour; 
  vector<float> _recoPFJet_DeepCSVsort_QGdiscr;

  vector<float> _recoPFJet_DeepJetsort_e;
  vector<float> _recoPFJet_DeepJetsort_pt;
  vector<float> _recoPFJet_DeepJetsort_px;
  vector<float> _recoPFJet_DeepJetsort_py;
  vector<float> _recoPFJet_DeepJetsort_pz;
  vector<float> _recoPFJet_DeepJetsort_eta;
  vector<float> _recoPFJet_DeepJetsort_phi;
  vector<float> _recoPFJet_DeepJetsort_CSVscore;
  vector<float> _recoPFJet_DeepJetsort_DeepCSVscore;
  vector<float> _recoPFJet_DeepJetsort_DeepJetscore;
  vector<float> _recoPFJet_DeepJetsort_jecUnc;
  vector<int>   _recoPFJet_DeepJetsort_Flavour; 
  vector<int>   _recoPFJet_DeepJetsort_hadronFlavour; 
  vector<float> _recoPFJet_DeepJetsort_QGdiscr;

  vector<int>   _recoPFJet_CSVsort_i_closest_genb;
  vector<float> _recoPFJet_CSVsort_dR_closest_genb;
  vector<int>   _recoPFJet_CSVsort_i_closest_gentauh;
  vector<float> _recoPFJet_CSVsort_dR_closest_gentauh;

  vector<int>   _recoPFJet_DeepCSVsort_i_closest_genb;
  vector<float> _recoPFJet_DeepCSVsort_dR_closest_genb;
  vector<int>   _recoPFJet_DeepCSVsort_i_closest_gentauh;
  vector<float> _recoPFJet_DeepCSVsort_dR_closest_gentauh;

  vector<int>   _recoPFJet_DeepJetsort_i_closest_genb;
  vector<float> _recoPFJet_DeepJetsort_dR_closest_genb;
  vector<int>   _recoPFJet_DeepJetsort_i_closest_gentauh;
  vector<float> _recoPFJet_DeepJetsort_dR_closest_gentauh;

  int _n_recoPFJet_btag_loose; //# jets passing DeepCSVL
  int _n_recoPFJet_btag_medium;  //# jets passing DeepCSVM
 
  //2 jets with highest DeepCSV score
  vector<float> _recoPFJet_btag_e;
  vector<float> _recoPFJet_btag_pt;
  vector<float> _recoPFJet_btag_px;
  vector<float> _recoPFJet_btag_py;
  vector<float> _recoPFJet_btag_pz;
  vector<float> _recoPFJet_btag_eta;
  vector<float> _recoPFJet_btag_phi;
  vector<float> _recoPFJet_btag_CSVscore;
  vector<float> _recoPFJet_btag_DeepCSVscore;
  vector<float> _recoPFJet_btag_DeepJetscore;
  vector<float> _recoPFJet_btag_jecUnc;  
  vector<int>   _recoPFJet_btag_Flavour; 
  vector<int>   _recoPFJet_btag_hadronFlavour; 
  vector<float> _recoPFJet_btag_QGdiscr;

  //Other jets
  int _n_recoPFJet_untag;

  vector<float> _recoPFJet_untag_e;
  vector<float> _recoPFJet_untag_pt;
  vector<float> _recoPFJet_untag_px;
  vector<float> _recoPFJet_untag_py;
  vector<float> _recoPFJet_untag_pz;
  vector<float> _recoPFJet_untag_eta;
  vector<float> _recoPFJet_untag_phi;
  vector<float> _recoPFJet_untag_CSVscore;
  vector<float> _recoPFJet_untag_DeepCSVscore;
  vector<float> _recoPFJet_untag_DeepJetscore;
  vector<float> _recoPFJet_untag_jecUnc;
  vector<int>   _recoPFJet_untag_Flavour;
  vector<int>   _recoPFJet_untag_hadronFlavour;
  vector<float> _recoPFJet_untag_QGdiscr;

  int _n_pair_Wtag_recoPFJet_untag;  
  float _recoPFJet_untag_best_mW; 

  vector<float> _recoPFJet_untag_Wtag_e;
  vector<float> _recoPFJet_untag_Wtag_pt;
  vector<float> _recoPFJet_untag_Wtag_px;
  vector<float> _recoPFJet_untag_Wtag_py;
  vector<float> _recoPFJet_untag_Wtag_pz;
  vector<float> _recoPFJet_untag_Wtag_eta;
  vector<float> _recoPFJet_untag_Wtag_phi;
  vector<float> _recoPFJet_untag_Wtag_CSVscore;
  vector<float> _recoPFJet_untag_Wtag_DeepCSVscore;
  vector<float> _recoPFJet_untag_Wtag_DeepJetscore;
  vector<float> _recoPFJet_untag_Wtag_jecUnc;
  vector<int>   _recoPFJet_untag_Wtag_Flavour; 
  vector<int>   _recoPFJet_untag_Wtag_hadronFlavour; 
  vector<float> _recoPFJet_untag_Wtag_QGdiscr;

  vector<float> _mtop_had_perm;
  vector<float> _mblep_perm;
  vector<float> _mleptauh_perm;

  float _PFMET;
  float _PFMET_phi;
  float _PFMETx;
  float _PFMETy;

  //Multilepton variables
  float _HTmiss;
  float _ETmissLD;
  float _MT_lep1;
  float _mindR_lep1_recoPFjet;
  float _mindR_lep2_recoPFjet;
  float _lep1_conept;
  float _lep2_conept;
  float _lep3_conept;
  float _avg_dr_jet;

  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;
  float _MVA_3l_ttV;
  float _MVA_3l_ttbar;

  // scale factors

  float _PU_weight;

  float _bTagSF_CSVshape_weight;
  float _bTagSF_CSVshape_weight_JESUp;
  float _bTagSF_CSVshape_weight_JESDown;
  float _bTagSF_CSVshape_weight_LFUp;
  float _bTagSF_CSVshape_weight_LFDown;
  float _bTagSF_CSVshape_weight_HFUp;
  float _bTagSF_CSVshape_weight_HFDown;
  float _bTagSF_CSVshape_weight_HFStats1Up;
  float _bTagSF_CSVshape_weight_HFStats1Down;
  float _bTagSF_CSVshape_weight_HFStats2Up;
  float _bTagSF_CSVshape_weight_HFStats2Down;
  float _bTagSF_CSVshape_weight_LFStats1Up;
  float _bTagSF_CSVshape_weight_LFStats1Down;
  float _bTagSF_CSVshape_weight_LFStats2Up;
  float _bTagSF_CSVshape_weight_LFStats2Down;
  float _bTagSF_CSVshape_weight_CFErr1Up;
  float _bTagSF_CSVshape_weight_CFErr1Down;
  float _bTagSF_CSVshape_weight_CFErr2Up;
  float _bTagSF_CSVshape_weight_CFErr2Down;

  float _tauSF_weight;
  float _tauSF_weight_tauNormUp;
  float _tauSF_weight_tauNormDown;
  float _tauSF_weight_tauShapeUp;
  float _tauSF_weight_tauShapeDown;
 
  //Gen information
  vector<float> _genpart_pt;
  vector<float> _genpart_eta;
  vector<float> _genpart_phi;
  vector<int>   _genpart_i_closest_daughter;
  vector<float> _genpart_dR_closest_daughter;

  int _n_genlep;
  int _n_genlep10;
  int _n_genlep20;
  int _n_genlep20_eta21;
  int _n_genlep_fromTop;
  int _n_genlep_fromTau;

  vector<int>   _genlep_pdg;
  vector<int>   _genlep_charge;
  vector<float> _genlep_e;
  vector<float> _genlep_px;
  vector<float> _genlep_py;
  vector<float> _genlep_pz;
  vector<float> _genlep_pt;
  vector<float> _genlep_eta;
  vector<float> _genlep_phi;
  vector<int>   _genlep_flags;  
  vector<int>   _genlep_TauMothInd; //-1 if not from tau
  vector<int>   _genlep_TopMothInd; //-1 if not from top
  vector<int>   _genlep_WMothInd; //-1 if not from top
  vector<int>   _genlep_ZMothInd;

  int _n_gentauh;
  int _n_gentauh10;
  int _n_gentauh30;
  int _n_gentauh30_eta21;
  int _n_gentauh_fromTop;
  int _n_gentauh_fromTau;

  vector<int>   _gentauh_charge;
  vector<float> _gentauh_e;
  vector<float> _gentauh_px;
  vector<float> _gentauh_py;
  vector<float> _gentauh_pz;
  vector<float> _gentauh_pt;
  vector<float> _gentauh_eta;
  vector<float> _gentauh_phi;
  vector<int>   _gentauh_flags;  
  vector<int>   _gentauh_TauMothInd;
  vector<int>   _gentauh_TopMothInd;
  vector<int>   _gentauh_WMothInd;

  int _n_gentau;
  int _n_gentau_fromTop;
  int _n_gentau_fromH;

  vector<int>   _gentau_decayMode; //0 muon, 1 electron, 2 had
  vector<int>   _gentau_charge;
  vector<float> _gentau_e;
  vector<float> _gentau_px;
  vector<float> _gentau_py;
  vector<float> _gentau_pz;
  vector<float> _gentau_pt;
  vector<float> _gentau_eta;
  vector<float> _gentau_phi;
  vector<int>   _gentau_flags;  
  vector<int>   _gentau_TopMothInd;
  vector<int>   _gentau_WMothInd;
  vector<int>   _gentau_HMothInd;
  vector<int>   _gentau_ZMothInd;

  int _n_genH;

  vector<int>   _genH_decayMode; //0 mu+tauh, 1 e+tauh, 2 tauh+tauh, 3 mu+mu, 4 e+e, 5 e+mu
  vector<float> _genH_e;
  vector<float> _genH_px;
  vector<float> _genH_py;
  vector<float> _genH_pz;
  vector<float> _genH_pt;
  vector<float> _genH_eta;
  vector<float> _genH_phi;
  vector<int>   _genH_flags;  

  int _n_genZ;

  vector<int>   _genZ_decayMode; //0 mu+tauh, 1 e+tauh, 2 tauh+tauh, 3 mu+mu, 4 e+e, 5 e+mu
  vector<float> _genZ_e;
  vector<float> _genZ_px;
  vector<float> _genZ_py;
  vector<float> _genZ_pz;
  vector<float> _genZ_pt;
  vector<float> _genZ_eta;
  vector<float> _genZ_phi;
  vector<int>   _genZ_flags;  

  int _n_gentop;

  vector<int>   _gentop_pdg;
  vector<int>   _gentop_decayMode;
  vector<float> _gentop_e;
  vector<float> _gentop_px;
  vector<float> _gentop_py;
  vector<float> _gentop_pz;
  vector<float> _gentop_pt;
  vector<float> _gentop_eta;
  vector<float> _gentop_phi;
  vector<int>   _gentop_flags;  
  vector<bool>  _gentop_isRecoMatched;
  vector<int>   _gentop_i_recoPFJet_btag;
  vector<int>   _gentop_i_recoPFJet_untag1;
  vector<int>   _gentop_i_recoPFJet_untag2;
  vector<int>   _gentop_i_recolep;

  int _n_genW;
  int _n_genW_fromTop;

  vector<int>   _genW_pdg;
  vector<int>   _genW_decayMode;
  vector<float> _genW_e;
  vector<float> _genW_px;
  vector<float> _genW_py;
  vector<float> _genW_pz;
  vector<float> _genW_pt;
  vector<float> _genW_eta;
  vector<float> _genW_phi;
  vector<int>   _genW_flags;  
  vector<int>   _genW_TopMothInd;

  int _n_genb;
  int _n_genb10;
  int _n_genb_fromTop;

  vector<int>   _genb_pdg;
  vector<float> _genb_e;
  vector<float> _genb_px;
  vector<float> _genb_py;
  vector<float> _genb_pz;
  vector<float> _genb_pt;
  vector<float> _genb_eta;
  vector<float> _genb_phi;
  vector<int>   _genb_flags;  
  vector<int>   _genb_TopMothInd;
  vector<int>   _genb_WMothInd;
  vector<int>   _genb_i_closest_recolep;
  vector<float> _genb_dR_closest_recolep;


  int _n_genq;
  int _n_genq10;
  int _n_genq_fromTop;

  vector<int>   _genq_pdg;
  vector<float> _genq_e;
  vector<float> _genq_px;
  vector<float> _genq_py;
  vector<float> _genq_pz;
  vector<float> _genq_pt;
  vector<float> _genq_eta;
  vector<float> _genq_phi;
  vector<int>   _genq_flags;  
  vector<int>   _genq_TopMothInd;
  vector<int>   _genq_WMothInd;

  int _n_gennu;
  int _n_gennu_fromTop;
  int _n_gennu_fromTau;

  vector<int>   _gennu_pdg;
  vector<float> _gennu_e;
  vector<float> _gennu_px;
  vector<float> _gennu_py;
  vector<float> _gennu_pz;
  vector<float> _gennu_pt;
  vector<float> _gennu_eta;
  vector<float> _gennu_phi;
  vector<int>   _gennu_flags;  
  vector<int>   _gennu_TauMothInd; //-1 if not from tau
  vector<int>   _gennu_TopMothInd; //-1 if not from top
  vector<int>   _gennu_WMothInd; //-1 if not from W


  tree_new->Branch("daughters_pt",&_daughters_pt);
  tree_new->Branch("daughters_eta",&_daughters_eta);
  tree_new->Branch("daughters_phi",&_daughters_phi);
  tree_new->Branch("daughters_dR_closest_jet",&_daughters_dR_closest_jet);
  
  tree_new->Branch("jets_pt",&_jets_pt);
  tree_new->Branch("jets_eta",&_jets_eta);
  tree_new->Branch("jets_phi",&_jets_phi);   

  tree_new->Branch("n_recomu_presel",&_n_recomu_presel,"n_recomu_presel/I");
  tree_new->Branch("n_recomu_fakeable",&_n_recomu_fakeable,"n_recomu_fakeable/I");
  tree_new->Branch("n_recomu_cutsel",&_n_recomu_cutsel,"n_recomu_cutsel/I");
  tree_new->Branch("n_recomu_mvasel",&_n_recomu_mvasel,"n_recomu_mvasel/I");
  tree_new->Branch("recomu_charge",&_recomu_charge);
  tree_new->Branch("recomu_e",&_recomu_e);
  tree_new->Branch("recomu_px",&_recomu_px);
  tree_new->Branch("recomu_py",&_recomu_py);
  tree_new->Branch("recomu_pz",&_recomu_pz);
  tree_new->Branch("recomu_pt",&_recomu_pt);
  tree_new->Branch("recomu_conept",&_recomu_conept);
  tree_new->Branch("recomu_eta",&_recomu_eta);
  tree_new->Branch("recomu_phi",&_recomu_phi);
  tree_new->Branch("recomu_dxy",&_recomu_dxy);
  tree_new->Branch("recomu_dz",&_recomu_dz);
  tree_new->Branch("recomu_dxy_innerTrack",&_recomu_dxy_innerTrack);
  tree_new->Branch("recomu_dz_innerTrack",&_recomu_dz_innerTrack);
  tree_new->Branch("recomu_jetNDauChargedMVASel",&_recomu_jetNDauChargedMVASel); //as taken for 2016 analysis
  tree_new->Branch("recomu_jetNDauChargedMVASel_nanoAOD",&_recomu_jetNDauChargedMVASel_nanoAOD); //taken from nanoAOD plugin
  tree_new->Branch("recomu_miniRelIso",&_recomu_miniRelIso);
  tree_new->Branch("recomu_miniRelIso_nanoAOD",&_recomu_miniRelIso_nanoAOD);
  tree_new->Branch("recomu_miniIsoCharged",&_recomu_miniIsoCharged);
  tree_new->Branch("recomu_miniIsoCharged_nanoAOD",&_recomu_miniIsoCharged_nanoAOD); 
  tree_new->Branch("recomu_miniIsoNeutral",&_recomu_miniIsoNeutral);
  tree_new->Branch("recomu_miniIsoNeutral_nanoAOD",&_recomu_miniIsoNeutral_nanoAOD);  
  tree_new->Branch("recomu_sip3D",&_recomu_sip3D);
  tree_new->Branch("recomu_jetPtRel",&_recomu_jetPtRel);
  tree_new->Branch("recomu_jetPtRel_nanoAOD",&_recomu_jetPtRel_nanoAOD);
  tree_new->Branch("recomu_jetCSV",&_recomu_jetCSV);
  tree_new->Branch("recomu_jetDeepCSV",&_recomu_jetDeepCSV);
  tree_new->Branch("recomu_jetDeepJet",&_recomu_jetDeepJet);
  tree_new->Branch("recomu_jetPtRatio",&_recomu_jetPtRatio);
  tree_new->Branch("recomu_jetPtRatio_nanoAOD",&_recomu_jetPtRatio_nanoAOD);
  tree_new->Branch("recomu_combreliso04",&_recomu_combreliso04);
  tree_new->Branch("recomu_lepMVA_Id",&_recomu_lepMVA_Id);
  tree_new->Branch("recomu_leptonMVA",&_recomu_leptonMVA);
  tree_new->Branch("recomu_rel_error_trackpt",&_recomu_rel_error_trackpt);
  tree_new->Branch("recomu_mediumID",&_recomu_mediumID);
  tree_new->Branch("recomu_isfakeable",&_recomu_isfakeable);
  tree_new->Branch("recomu_iscutsel",&_recomu_iscutsel);
  tree_new->Branch("recomu_ismvasel",&_recomu_ismvasel);
  tree_new->Branch("recomu_TopMothInd",&_recomu_TopMothInd);
  tree_new->Branch("recomu_HMothInd",&_recomu_HMothInd);
  tree_new->Branch("recomu_goodsign",&_recomu_goodsign);
  tree_new->Branch("recomu_fakerate",&_recomu_fakerate);
  tree_new->Branch("recomu_fakerate_up",&_recomu_fakerate_up);
  tree_new->Branch("recomu_fakerate_down",&_recomu_fakerate_down);
  tree_new->Branch("recomu_fakerate_pt1",&_recomu_fakerate_pt1);
  tree_new->Branch("recomu_fakerate_pt2",&_recomu_fakerate_pt2);
  tree_new->Branch("recomu_fakerate_be1",&_recomu_fakerate_be1);
  tree_new->Branch("recomu_fakerate_be2",&_recomu_fakerate_be2);
  tree_new->Branch("recomu_fakerate_QCD_MC",&_recomu_fakerate_QCD_MC);
  tree_new->Branch("recomu_fakerate_ttbar_MC",&_recomu_fakerate_ttbar_MC);
  tree_new->Branch("recomu_isGenMatched",&_recomu_isGenMatched);
  tree_new->Branch("recomu_genMatchInd",&_recomu_genMatchInd);
  tree_new->Branch("recomu_isGenChargeMatched",&_recomu_isGenChargeMatched);
  tree_new->Branch("recomu_matchedJetIndex",&_recomu_matchedJetIndex);

  tree_new->Branch("n_recoele_presel",&_n_recoele_presel,"n_recoele_presel/I");
  tree_new->Branch("n_recoele_fakeable",&_n_recoele_fakeable,"n_recoele_fakeable/I");
  tree_new->Branch("n_recoele_cutsel",&_n_recoele_cutsel,"n_recoele_cutsel/I");
  tree_new->Branch("n_recoele_mvasel",&_n_recoele_mvasel,"n_recoele_mvasel/I");
  tree_new->Branch("recoele_charge",&_recoele_charge);
  tree_new->Branch("recoele_e",&_recoele_e);
  tree_new->Branch("recoele_px",&_recoele_px);
  tree_new->Branch("recoele_py",&_recoele_py);
  tree_new->Branch("recoele_pz",&_recoele_pz);
  tree_new->Branch("recoele_pt",&_recoele_pt);
  tree_new->Branch("recoele_corr_e",&_recoele_corr_e); 
  tree_new->Branch("recoele_corr_pt",&_recoele_corr_pt);
  tree_new->Branch("recoele_conept",&_recoele_conept);
  tree_new->Branch("recoele_eta",&_recoele_eta);
  tree_new->Branch("recoele_phi",&_recoele_phi);
  tree_new->Branch("recoele_dxy",&_recoele_dxy);
  tree_new->Branch("recoele_dz",&_recoele_dz);
  tree_new->Branch("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
  tree_new->Branch("recoele_jetNDauChargedMVASel_nanoAOD",&_recoele_jetNDauChargedMVASel_nanoAOD);
  tree_new->Branch("recoele_miniRelIso",&_recoele_miniRelIso);
  tree_new->Branch("recoele_miniRelIso_nanoAOD",&_recoele_miniRelIso_nanoAOD);
  tree_new->Branch("recoele_PFRelIsoAll_nanoAOD",&_recoele_PFRelIsoAll_nanoAOD);
  tree_new->Branch("recoele_PFRelIsoAll04_nanoAOD",&_recoele_PFRelIsoAll04_nanoAOD);
  tree_new->Branch("recoele_miniIsoCharged",&_recoele_miniIsoCharged);
  tree_new->Branch("recoele_miniIsoCharged_nanoAOD",&_recoele_miniIsoCharged_nanoAOD);
  tree_new->Branch("recoele_PFIsoCharged_nanoAOD",&_recoele_PFIsoCharged_nanoAOD);
  tree_new->Branch("recoele_miniIsoNeutral",&_recoele_miniIsoNeutral);
  tree_new->Branch("recoele_miniIsoNeutral_nanoAOD",&_recoele_miniIsoNeutral_nanoAOD);
  tree_new->Branch("recoele_PFIsoNeutral_nanoAOD",&_recoele_PFIsoNeutral_nanoAOD);
  tree_new->Branch("recoele_sip3D",&_recoele_sip3D);
  tree_new->Branch("recoele_jetPtRel",&_recoele_jetPtRel);
  tree_new->Branch("recoele_jetPtRel_nanoAOD",&_recoele_jetPtRel_nanoAOD);
  tree_new->Branch("recoele_jetCSV",&_recoele_jetCSV);
  tree_new->Branch("recoele_jetDeepCSV",&_recoele_jetDeepCSV);
  tree_new->Branch("recoele_jetDeepJet",&_recoele_jetDeepJet);
  tree_new->Branch("recoele_jetPtRatio",&_recoele_jetPtRatio);
  tree_new->Branch("recoele_jetPtRatio_nanoAOD",&_recoele_jetPtRatio_nanoAOD);
  tree_new->Branch("recoele_lepMVA_Id",&_recoele_lepMVA_Id);
  tree_new->Branch("recoele_leptonMVA",&_recoele_leptonMVA);
  tree_new->Branch("recoele_isChargeConsistent",&_recoele_isChargeConsistent);
  tree_new->Branch("recoele_passConversionVeto",&_recoele_passConversionVeto);
  tree_new->Branch("recoele_nMissingHits",&_recoele_nMissingHits);
  tree_new->Branch("recoele_sigmaEtaEta",&_recoele_sigmaEtaEta);
  tree_new->Branch("recoele_HoE",&_recoele_HoE);
  tree_new->Branch("recoele_deltaEta",&_recoele_deltaEta);
  tree_new->Branch("recoele_deltaPhi",&_recoele_deltaPhi);
  tree_new->Branch("recoele_OoEminusOoP",&_recoele_OoEminusOoP);
  tree_new->Branch("recoele_isfakeable",&_recoele_isfakeable);
  tree_new->Branch("recoele_iscutsel",&_recoele_iscutsel);
  tree_new->Branch("recoele_ismvasel",&_recoele_ismvasel);
  tree_new->Branch("recoele_TopMothInd",&_recoele_TopMothInd);
  tree_new->Branch("recoele_HMothInd",&_recoele_HMothInd);
  tree_new->Branch("recoele_goodsign",&_recoele_goodsign);
  tree_new->Branch("recoele_fakerate",&_recoele_fakerate);
  tree_new->Branch("recoele_fakerate_up",&_recoele_fakerate_up);
  tree_new->Branch("recoele_fakerate_down",&_recoele_fakerate_down);
  tree_new->Branch("recoele_fakerate_pt1",&_recoele_fakerate_pt1);
  tree_new->Branch("recoele_fakerate_pt2",&_recoele_fakerate_pt2);
  tree_new->Branch("recoele_fakerate_be1",&_recoele_fakerate_be1);
  tree_new->Branch("recoele_fakerate_be2",&_recoele_fakerate_be2);
  tree_new->Branch("recoele_fakerate_QCD_MC",&_recoele_fakerate_QCD_MC);
  tree_new->Branch("recoele_fakerate_ttbar_MC",&_recoele_fakerate_ttbar_MC);
  tree_new->Branch("recoele_QFrate",&_recoele_QFrate);
  tree_new->Branch("recoele_isGenMatched",&_recoele_isGenMatched);
  tree_new->Branch("recoele_isGenChargeMatched",&_recoele_isGenChargeMatched);
  tree_new->Branch("recoele_genMatchInd",&_recoele_genMatchInd);
  tree_new->Branch("recoele_matchedJetIndex",&_recoele_matchedJetIndex);
  
  tree_new->Branch("n_recolep_presel",&_n_recolep_presel,"n_recolep_presel/I");
  tree_new->Branch("n_recolep_fakeable",&_n_recolep_fakeable,"n_recolep_fakeable/I");
  tree_new->Branch("n_recolep_cutsel",&_n_recolep_cutsel,"n_recolep_cutsel/I");
  tree_new->Branch("n_recolep_mvasel",&_n_recolep_mvasel,"n_recolep_mvasel/I");
  tree_new->Branch("recolep_charge",&_recolep_charge);
  tree_new->Branch("recolep_pdg",&_recolep_pdg);
  tree_new->Branch("recolep_e",&_recolep_e);
  tree_new->Branch("recolep_px",&_recolep_px);
  tree_new->Branch("recolep_py",&_recolep_py);
  tree_new->Branch("recolep_pz",&_recolep_pz);
  tree_new->Branch("recolep_pt",&_recolep_pt);
  tree_new->Branch("recolep_conept",&_recolep_conept);
  tree_new->Branch("recolep_eta",&_recolep_eta);
  tree_new->Branch("recolep_phi",&_recolep_phi);
  tree_new->Branch("recolep_leptonMVA",&_recolep_leptonMVA);
  tree_new->Branch("recolep_fakerate",&_recolep_fakerate);
  tree_new->Branch("recolep_fakerate_up",&_recolep_fakerate_up);
  tree_new->Branch("recolep_fakerate_down",&_recolep_fakerate_down);
  tree_new->Branch("recolep_fakerate_pt1",&_recolep_fakerate_pt1);
  tree_new->Branch("recolep_fakerate_pt2",&_recolep_fakerate_pt2);
  tree_new->Branch("recolep_fakerate_be1",&_recolep_fakerate_be1);
  tree_new->Branch("recolep_fakerate_be2",&_recolep_fakerate_be2);
  tree_new->Branch("recolep_fakerate_QCD_MC",&_recolep_fakerate_QCD_MC);
  tree_new->Branch("recolep_fakerate_ttbar_MC",&_recolep_fakerate_ttbar_MC);
  tree_new->Branch("recolep_QFrate",&_recolep_QFrate);
  tree_new->Branch("recolep_isfakeable",&_recolep_isfakeable);
  tree_new->Branch("recolep_iscutsel",&_recolep_iscutsel);
  tree_new->Branch("recolep_ismvasel",&_recolep_ismvasel);
  tree_new->Branch("recolep_tightcharge",&_recolep_tightcharge);
  tree_new->Branch("recolep_eleconv_misshits",&_recolep_eleconv_misshits);
  tree_new->Branch("recolep_isGenMatched",&_recolep_isGenMatched);
  tree_new->Branch("recolep_isGenChargeMatched",&_recolep_isGenChargeMatched);
  tree_new->Branch("recolep_genMatchInd",&_recolep_genMatchInd);

  tree_new->Branch("n_recotauh",&_n_recotauh,"n_recotauh/I");
  tree_new->Branch("recotauh_decayMode",&_recotauh_decayMode);
  tree_new->Branch("recotauh_charge",&_recotauh_charge);
  tree_new->Branch("recotauh_e",&_recotauh_e);
  tree_new->Branch("recotauh_px",&_recotauh_px);
  tree_new->Branch("recotauh_py",&_recotauh_py);
  tree_new->Branch("recotauh_pz",&_recotauh_pz);
  tree_new->Branch("recotauh_pt",&_recotauh_pt);
  tree_new->Branch("recotauh_eta",&_recotauh_eta);
  tree_new->Branch("recotauh_phi",&_recotauh_phi);
  tree_new->Branch("recotauh_dxy",&_recotauh_dxy);
  tree_new->Branch("recotauh_dz",&_recotauh_dz);
  tree_new->Branch("recotauh_iso",&_recotauh_iso);
  tree_new->Branch("recotauh_isGenMatched",&_recotauh_isGenMatched);
  tree_new->Branch("recotauh_genMatchInd",&_recotauh_genMatchInd);
  tree_new->Branch("recotauh_matchedJetIndex",&_recotauh_matchedJetIndex);  

  tree_new->Branch("recotauh_decayModeFindingOldDMs",&_recotauh_decayModeFindingOldDMs);
  tree_new->Branch("recotauh_decayModeFindingNewDMs",&_recotauh_decayModeFindingNewDMs);
  tree_new->Branch("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",&_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  tree_new->Branch("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",&_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  tree_new->Branch("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",&_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
  tree_new->Branch("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",&_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree_new->Branch("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",&_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree_new->Branch("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",&_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree_new->Branch("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT);
  tree_new->Branch("recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT);
  tree_new->Branch("recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT);
  tree_new->Branch("recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT);
  tree_new->Branch("recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT",&_recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT);
  tree_new->Branch("recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw",&_recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw);
  tree_new->Branch("recotauh_againstMuonLoose3",&_recotauh_againstMuonLoose3);
  tree_new->Branch("recotauh_againstMuonTight3",&_recotauh_againstMuonTight3);
  tree_new->Branch("recotauh_againstElectronVLooseMVA6",&_recotauh_againstElectronVLooseMVA6);
  tree_new->Branch("recotauh_againstElectronLooseMVA6",&_recotauh_againstElectronLooseMVA6);
  tree_new->Branch("recotauh_againstElectronMediumMVA6",&_recotauh_againstElectronMediumMVA6);
  tree_new->Branch("recotauh_againstElectronTightMVA6",&_recotauh_againstElectronTightMVA6);
  tree_new->Branch("recotauh_againstElectronVTightMVA6",&_recotauh_againstElectronVTightMVA6);

  tree_new->Branch("recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT",&_recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT);
  tree_new->Branch("recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT",&_recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT);
  tree_new->Branch("recotauh_fakerate_byTightIsolationMVArun2v2017v2DBdR03oldDMwLT",&_recotauh_fakerate_byTightIsolationMVArun2v2017v2DBdR03oldDMwLT);
  tree_new->Branch("recotauh_fakerate_byVTightIsolationMVArun2v2017v2DBdR03oldDMwLT",&_recotauh_fakerate_byVTightIsolationMVArun2v2017v2DBdR03oldDMwLT);

  tree_new->Branch("recotauh_i_closest_genpart",&_recotauh_i_closest_genpart);
  tree_new->Branch("recotauh_dR_closest_genpart",&_recotauh_dR_closest_genpart);
  
  tree_new->Branch("n_recoPFJet",&_n_recoPFJet,"n_recoPFJet/I");
  tree_new->Branch("recoPFJet_e",&_recoPFJet_e);
  tree_new->Branch("recoPFJet_pt",&_recoPFJet_pt);
  tree_new->Branch("recoPFJet_px",&_recoPFJet_px);
  tree_new->Branch("recoPFJet_py",&_recoPFJet_py);
  tree_new->Branch("recoPFJet_pz",&_recoPFJet_pz);
  tree_new->Branch("recoPFJet_eta",&_recoPFJet_eta);
  tree_new->Branch("recoPFJet_phi",&_recoPFJet_phi);
  tree_new->Branch("recoPFJet_CSVscore",&_recoPFJet_CSVscore);
  tree_new->Branch("recoPFJet_DeepCSVscore",&_recoPFJet_DeepCSVscore);
  tree_new->Branch("recoPFJet_DeepJetscore",&_recoPFJet_DeepJetscore);
  tree_new->Branch("recoPFJet_jecUnc",&_recoPFJet_jecUnc);
  tree_new->Branch("recoPFJet_Flavour",&_recoPFJet_Flavour);
  tree_new->Branch("recoPFJet_hadronFlavour",&_recoPFJet_hadronFlavour);
  tree_new->Branch("recoPFJet_QGdiscr",&_recoPFJet_QGdiscr);

  tree_new->Branch("n_recoPFFwdJet",&_n_recoPFFwdJet,"n_recoPFFwdJet/I");
  tree_new->Branch("recoPFFwdJet_e",&_recoPFFwdJet_e);
  tree_new->Branch("recoPFFwdJet_pt",&_recoPFFwdJet_pt);
  tree_new->Branch("recoPFFwdJet_px",&_recoPFFwdJet_px);
  tree_new->Branch("recoPFFwdJet_py",&_recoPFFwdJet_py);
  tree_new->Branch("recoPFFwdJet_pz",&_recoPFFwdJet_pz);
  tree_new->Branch("recoPFFwdJet_eta",&_recoPFFwdJet_eta);
  tree_new->Branch("recoPFFwdJet_phi",&_recoPFFwdJet_phi);
  tree_new->Branch("recoPFFwdJet_CSVscore",&_recoPFFwdJet_CSVscore);
  tree_new->Branch("recoPFFwdJet_DeepCSVscore",&_recoPFFwdJet_DeepCSVscore);
  tree_new->Branch("recoPFFwdJet_DeepJetscore",&_recoPFFwdJet_DeepJetscore);
  tree_new->Branch("recoPFFwdJet_jecUnc",&_recoPFFwdJet_jecUnc);
  tree_new->Branch("recoPFFwdJet_Flavour",&_recoPFFwdJet_Flavour);
  tree_new->Branch("recoPFFwdJet_hadronFlavour",&_recoPFFwdJet_hadronFlavour);
  tree_new->Branch("recoPFFwdJet_QGdiscr",&_recoPFFwdJet_QGdiscr);

  tree_new->Branch("n_recoPFak8Jet",&_n_recoPFak8Jet,"n_recoPFJet/I");
  tree_new->Branch("recoPFak8Jet_e",&_recoPFak8Jet_e);
  tree_new->Branch("recoPFak8Jet_pt",&_recoPFak8Jet_pt);
  tree_new->Branch("recoPFak8Jet_px",&_recoPFak8Jet_px);
  tree_new->Branch("recoPFak8Jet_py",&_recoPFak8Jet_py);
  tree_new->Branch("recoPFak8Jet_pz",&_recoPFak8Jet_pz);
  tree_new->Branch("recoPFak8Jet_eta",&_recoPFak8Jet_eta);
  tree_new->Branch("recoPFak8Jet_phi",&_recoPFak8Jet_phi);
  tree_new->Branch("recoPFak8Jet_SoftDropMass",&_recoPFak8Jet_SoftDropMass);
  tree_new->Branch("recoPFak8Jet_tau1",&_recoPFak8Jet_tau1); 
  tree_new->Branch("recoPFak8Jet_tau2",&_recoPFak8Jet_tau2); 
  tree_new->Branch("recoPFak8Jet_tau3",&_recoPFak8Jet_tau3); 
  tree_new->Branch("recoPFak8Jet_nsubjets",&_recoPFak8Jet_nsubjets);

  tree_new->Branch("recoPFak8Jet_subjets_e",&_recoPFak8Jet_subjets_e);
  tree_new->Branch("recoPFak8Jet_subjets_pt",&_recoPFak8Jet_subjets_pt);
  tree_new->Branch("recoPFak8Jet_subjets_px",&_recoPFak8Jet_subjets_px);
  tree_new->Branch("recoPFak8Jet_subjets_py",&_recoPFak8Jet_subjets_py);
  tree_new->Branch("recoPFak8Jet_subjets_pz",&_recoPFak8Jet_subjets_pz);
  tree_new->Branch("recoPFak8Jet_subjets_eta",&_recoPFak8Jet_subjets_eta);
  tree_new->Branch("recoPFak8Jet_subjets_phi",&_recoPFak8Jet_subjets_phi);
  tree_new->Branch("recoPFak8Jet_subjets_ak8MotherIdx",&_recoPFak8Jet_subjets_ak8MotherIdx);

  tree_new->Branch("recoPFJet_i_closest_genpart",&_recoPFJet_i_closest_genpart);
  tree_new->Branch("recoPFJet_dR_closest_genpart",&_recoPFJet_dR_closest_genpart);
  tree_new->Branch("recoPFJet_i_2nd_closest_genpart",&_recoPFJet_i_2nd_closest_genpart);
  tree_new->Branch("recoPFJet_dR_2nd_closest_genpart",&_recoPFJet_dR_2nd_closest_genpart);
  tree_new->Branch("recoPFJet_i_closest_tau",&_recoPFJet_i_closest_tau);
  tree_new->Branch("recoPFJet_dR_closest_tau",&_recoPFJet_dR_closest_tau);
  
  tree_new->Branch("recoPFJet_CSVsort_e",&_recoPFJet_CSVsort_e);
  tree_new->Branch("recoPFJet_CSVsort_pt",&_recoPFJet_CSVsort_pt);
  tree_new->Branch("recoPFJet_CSVsort_px",&_recoPFJet_CSVsort_px);
  tree_new->Branch("recoPFJet_CSVsort_py",&_recoPFJet_CSVsort_py);
  tree_new->Branch("recoPFJet_CSVsort_pz",&_recoPFJet_CSVsort_pz);
  tree_new->Branch("recoPFJet_CSVsort_eta",&_recoPFJet_CSVsort_eta);
  tree_new->Branch("recoPFJet_CSVsort_phi",&_recoPFJet_CSVsort_phi);
  tree_new->Branch("recoPFJet_CSVsort_CSVscore",&_recoPFJet_CSVsort_CSVscore);
  tree_new->Branch("recoPFJet_CSVsort_DeepCSVscore",&_recoPFJet_CSVsort_DeepCSVscore);
  tree_new->Branch("recoPFJet_CSVsort_DeepJetscore",&_recoPFJet_CSVsort_DeepJetscore);
  tree_new->Branch("recoPFJet_CSVsort_jecUnc",&_recoPFJet_CSVsort_jecUnc);
  tree_new->Branch("recoPFJet_CSVsort_Flavour",&_recoPFJet_CSVsort_Flavour);
  tree_new->Branch("recoPFJet_CSVsort_hadronFlavour",&_recoPFJet_CSVsort_hadronFlavour);
  tree_new->Branch("recoPFJet_CSVsort_QGdiscr",&_recoPFJet_CSVsort_QGdiscr);
  
  tree_new->Branch("recoPFJet_DeepCSVsort_e",&_recoPFJet_DeepCSVsort_e);
  tree_new->Branch("recoPFJet_DeepCSVsort_pt",&_recoPFJet_DeepCSVsort_pt);
  tree_new->Branch("recoPFJet_DeepCSVsort_px",&_recoPFJet_DeepCSVsort_px);
  tree_new->Branch("recoPFJet_DeepCSVsort_py",&_recoPFJet_DeepCSVsort_py);
  tree_new->Branch("recoPFJet_DeepCSVsort_pz",&_recoPFJet_DeepCSVsort_pz);
  tree_new->Branch("recoPFJet_DeepCSVsort_eta",&_recoPFJet_DeepCSVsort_eta);
  tree_new->Branch("recoPFJet_DeepCSVsort_phi",&_recoPFJet_DeepCSVsort_phi);
  tree_new->Branch("recoPFJet_DeepCSVsort_DeepCSVscore",&_recoPFJet_DeepCSVsort_DeepCSVscore);
  tree_new->Branch("recoPFJet_DeepCSVsort_DeepJetscore",&_recoPFJet_DeepCSVsort_DeepJetscore);
  tree_new->Branch("recoPFJet_DeepCSVsort_jecUnc",&_recoPFJet_DeepCSVsort_jecUnc);
  tree_new->Branch("recoPFJet_DeepCSVsort_Flavour",&_recoPFJet_DeepCSVsort_Flavour);
  tree_new->Branch("recoPFJet_DeepCSVsort_hadronFlavour",&_recoPFJet_DeepCSVsort_hadronFlavour);
  tree_new->Branch("recoPFJet_DeepCSVsort_QGdiscr",&_recoPFJet_DeepCSVsort_QGdiscr);

  tree_new->Branch("recoPFJet_DeepJetsort_e",&_recoPFJet_DeepJetsort_e);
  tree_new->Branch("recoPFJet_DeepJetsort_pt",&_recoPFJet_DeepJetsort_pt);
  tree_new->Branch("recoPFJet_DeepJetsort_px",&_recoPFJet_DeepJetsort_px);
  tree_new->Branch("recoPFJet_DeepJetsort_py",&_recoPFJet_DeepJetsort_py);
  tree_new->Branch("recoPFJet_DeepJetsort_pz",&_recoPFJet_DeepJetsort_pz);
  tree_new->Branch("recoPFJet_DeepJetsort_eta",&_recoPFJet_DeepJetsort_eta);
  tree_new->Branch("recoPFJet_DeepJetsort_phi",&_recoPFJet_DeepJetsort_phi);
  tree_new->Branch("recoPFJet_DeepJetsort_DeepCSVscore",&_recoPFJet_DeepJetsort_DeepCSVscore);
  tree_new->Branch("recoPFJet_DeepJetsort_DeepJetscore",&_recoPFJet_DeepJetsort_DeepJetscore);
  tree_new->Branch("recoPFJet_DeepJetsort_jecUnc",&_recoPFJet_DeepJetsort_jecUnc);
  tree_new->Branch("recoPFJet_DeepJetsort_Flavour",&_recoPFJet_DeepCSVsort_Flavour);
  tree_new->Branch("recoPFJet_DeepJetsort_hadronFlavour",&_recoPFJet_DeepCSVsort_hadronFlavour);
  tree_new->Branch("recoPFJet_DeepJetsort_QGdiscr",&_recoPFJet_DeepCSVsort_QGdiscr);

  tree_new->Branch("recoPFJet_CSVsort_i_closest_genb",&_recoPFJet_CSVsort_i_closest_genb);
  tree_new->Branch("recoPFJet_CSVsort_dR_closest_genb",&_recoPFJet_CSVsort_dR_closest_genb);
  tree_new->Branch("recoPFJet_CSVsort_i_closest_gentauh",&_recoPFJet_CSVsort_i_closest_gentauh);
  tree_new->Branch("recoPFJet_CSVsort_dR_closest_gentauh",&_recoPFJet_CSVsort_dR_closest_gentauh);
  
  tree_new->Branch("recoPFJet_DeepCSVsort_i_closest_genb",&_recoPFJet_DeepCSVsort_i_closest_genb);
  tree_new->Branch("recoPFJet_DeepCSVsort_dR_closest_genb",&_recoPFJet_DeepCSVsort_dR_closest_genb);
  tree_new->Branch("recoPFJet_DeepCSVsort_i_closest_gentauh",&_recoPFJet_DeepCSVsort_i_closest_gentauh);
  tree_new->Branch("recoPFJet_DeepCSVsort_dR_closest_gentauh",&_recoPFJet_DeepCSVsort_dR_closest_gentauh);

  tree_new->Branch("recoPFJet_DeepJetsort_i_closest_genb",&_recoPFJet_DeepJetsort_i_closest_genb);
  tree_new->Branch("recoPFJet_DeepJetsort_dR_closest_genb",&_recoPFJet_DeepJetsort_dR_closest_genb);
  tree_new->Branch("recoPFJet_DeepJetsort_i_closest_gentauh",&_recoPFJet_DeepJetsort_i_closest_gentauh);
  tree_new->Branch("recoPFJet_DeepJetsort_dR_closest_gentauh",&_recoPFJet_DeepJetsort_dR_closest_gentauh);

  tree_new->Branch("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium,"n_recoPFJet_btag_medium/I");
  tree_new->Branch("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose,"n_recoPFJet_btag_loose/I");
  tree_new->Branch("recoPFJet_btag_e",&_recoPFJet_btag_e);
  tree_new->Branch("recoPFJet_btag_pt",&_recoPFJet_btag_pt);
  tree_new->Branch("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree_new->Branch("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree_new->Branch("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree_new->Branch("recoPFJet_btag_eta",&_recoPFJet_btag_eta);
  tree_new->Branch("recoPFJet_btag_phi",&_recoPFJet_btag_phi);
  tree_new->Branch("recoPFJet_btag_CSVscore",&_recoPFJet_btag_CSVscore);
  tree_new->Branch("recoPFJet_btag_DeepCSVscore",&_recoPFJet_btag_DeepCSVscore);
  tree_new->Branch("recoPFJet_btag_DeepJetscore",&_recoPFJet_btag_DeepJetscore);
  tree_new->Branch("recoPFJet_btag_jecUnc",&_recoPFJet_btag_jecUnc);
  tree_new->Branch("recoPFJet_btag_Flavour",&_recoPFJet_btag_Flavour);
  tree_new->Branch("recoPFJet_btag_hadronFlavour",&_recoPFJet_btag_hadronFlavour);
  tree_new->Branch("recoPFJet_btag_QGdiscr",&_recoPFJet_btag_QGdiscr); 
 
  tree_new->Branch("n_recoPFJet_untag",&_n_recoPFJet_untag,"n_recoPFJet_untag/I");
  tree_new->Branch("recoPFJet_untag_e",&_recoPFJet_untag_e);
  tree_new->Branch("recoPFJet_untag_pt",&_recoPFJet_untag_pt);
  tree_new->Branch("recoPFJet_untag_px",&_recoPFJet_untag_px);
  tree_new->Branch("recoPFJet_untag_py",&_recoPFJet_untag_py);
  tree_new->Branch("recoPFJet_untag_pz",&_recoPFJet_untag_pz);
  tree_new->Branch("recoPFJet_untag_eta",&_recoPFJet_untag_eta);
  tree_new->Branch("recoPFJet_untag_phi",&_recoPFJet_untag_phi);
  tree_new->Branch("recoPFJet_untag_CSVscore",&_recoPFJet_untag_CSVscore);
  tree_new->Branch("recoPFJet_untag_DeepCSVscore",&_recoPFJet_untag_DeepCSVscore);
  tree_new->Branch("recoPFJet_untag_DeepJetscore",&_recoPFJet_untag_DeepJetscore);
  tree_new->Branch("recoPFJet_untag_jecUnc",&_recoPFJet_untag_jecUnc);
  tree_new->Branch("recoPFJet_untag_Flavour",&_recoPFJet_untag_Flavour);
  tree_new->Branch("recoPFJet_untag_hadronFlavour",&_recoPFJet_untag_hadronFlavour);
  tree_new->Branch("recoPFJet_untag_QGdiscr",&_recoPFJet_untag_QGdiscr);  

  tree_new->Branch("n_pair_Wtag_recoPFJet_untag",&_n_pair_Wtag_recoPFJet_untag,"n_pair_Wtag_recoPFJet_untag/I");  
  tree_new->Branch("recoPFJet_untag_best_mW",&_recoPFJet_untag_best_mW,"recoPFJet_untag_best_mW/F");  
  tree_new->Branch("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);
  tree_new->Branch("recoPFJet_untag_Wtag_pt",&_recoPFJet_untag_Wtag_pt);
  tree_new->Branch("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree_new->Branch("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree_new->Branch("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree_new->Branch("recoPFJet_untag_Wtag_eta",&_recoPFJet_untag_Wtag_eta);
  tree_new->Branch("recoPFJet_untag_Wtag_phi",&_recoPFJet_untag_Wtag_phi);
  tree_new->Branch("recoPFJet_untag_Wtag_CSVscore",&_recoPFJet_untag_Wtag_CSVscore);
  tree_new->Branch("recoPFJet_untag_Wtag_DeepCSVscore",&_recoPFJet_untag_Wtag_DeepCSVscore);
  tree_new->Branch("recoPFJet_untag_Wtag_DeepJetscore",&_recoPFJet_untag_Wtag_DeepJetscore);
  tree_new->Branch("recoPFJet_untag_Wtag_jecUnc",&_recoPFJet_untag_Wtag_jecUnc);
  tree_new->Branch("recoPFJet_untag_Wtag_Flavour",&_recoPFJet_untag_Wtag_Flavour);
  tree_new->Branch("recoPFJet_untag_Wtag_hadronFlavour",&_recoPFJet_untag_Wtag_hadronFlavour);
  tree_new->Branch("recoPFJet_untag_Wtag_QGdiscr",&_recoPFJet_untag_Wtag_QGdiscr);
    
  tree_new->Branch("mtop_had_perm",&_mtop_had_perm);
  tree_new->Branch("mblep_perm",&_mblep_perm);
  tree_new->Branch("mleptauh_perm",&_mleptauh_perm);
  
  tree_new->Branch("PFMETx",&_PFMETx,"PFMETx/F");
  tree_new->Branch("PFMETy",&_PFMETy,"PFMETy/F");
  tree_new->Branch("PFMET",&_PFMET,"PFMET/F");
  tree_new->Branch("PFMET_phi",&_PFMET_phi,"PFMET_phi/F");
  
  tree_new->Branch("HTmiss",&_HTmiss,"HTmiss/F");
  tree_new->Branch("ETmissLD",&_ETmissLD,"ETmissLD/F");
  tree_new->Branch("MT_lep1",&_MT_lep1,"MT_lep1/F");
  tree_new->Branch("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet,"mindR_lep1_recoPFjet/F");
  tree_new->Branch("mindR_lep2_recoPFjet",&_mindR_lep2_recoPFjet,"mindR_lep2_recoPFjet/F");
  tree_new->Branch("lep1_conept",&_lep1_conept,"lep1_conept/F");
  tree_new->Branch("lep2_conept",&_lep2_conept,"lep2_conept/F");
  tree_new->Branch("lep3_conept",&_lep3_conept,"lep3_conept/F");
  tree_new->Branch("avg_dr_jet",&_avg_dr_jet,"avg_dr_jet/F");

  tree_new->Branch("MVA_2lSS_ttV",&_MVA_2lSS_ttV,"MVA_2lSS_ttV/F");
  tree_new->Branch("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar,"MVA_2lSS_ttbar/F");
  tree_new->Branch("MVA_3l_ttV",&_MVA_3l_ttV,"MVA_3l_ttV/F");
  tree_new->Branch("MVA_3l_ttbar",&_MVA_3l_ttbar,"MVA_3l_ttbar/F");
  
  tree_new->Branch("PU_weight",&_PU_weight,"PU_weight/F");

  tree_new->Branch("tauSF_weight",&_tauSF_weight_tauNormUp,"tauSF_weight/F");
  tree_new->Branch("tauSF_weight_tauNormUp",&_tauSF_weight_tauNormUp,"tauSF_weight_tauNormUp/F");
  tree_new->Branch("tauSF_weight_tauNormDown",&_tauSF_weight_tauNormDown,"tauSF_weight_tauNormDown/F");
  tree_new->Branch("tauSF_weight_tauShapeUp",&_tauSF_weight_tauShapeUp,"tauSF_weight_tauShapeUp/F");
  tree_new->Branch("tauSF_weight_tauShapeDown",&_tauSF_weight_tauShapeDown,"tauSF_weight_tauShapeDown/F"); 

  tree_new->Branch("bTagSF_CSVshape_weight",&_bTagSF_CSVshape_weight);
  tree_new->Branch("bTagSF_CSVshape_weight_JESUp",&_bTagSF_CSVshape_weight_JESUp);
  tree_new->Branch("bTagSF_CSVshape_weight_JESDown",&_bTagSF_CSVshape_weight_JESDown);
  tree_new->Branch("bTagSF_CSVshape_weight_LFUp",&_bTagSF_CSVshape_weight_LFUp);
  tree_new->Branch("bTagSF_CSVshape_weight_LFDown",&_bTagSF_CSVshape_weight_LFDown);
  tree_new->Branch("bTagSF_CSVshape_weight_HFUp",&_bTagSF_CSVshape_weight_HFUp);
  tree_new->Branch("bTagSF_CSVshape_weight_HFDown",&_bTagSF_CSVshape_weight_HFDown);
  tree_new->Branch("bTagSF_CSVshape_weight_HFStats1Up",&_bTagSF_CSVshape_weight_HFStats1Up);
  tree_new->Branch("bTagSF_CSVshape_weight_HFStats1Down",&_bTagSF_CSVshape_weight_HFStats1Down);
  tree_new->Branch("bTagSF_CSVshape_weight_HFStats2Up",&_bTagSF_CSVshape_weight_HFStats2Up);
  tree_new->Branch("bTagSF_CSVshape_weight_HFStats2Down",&_bTagSF_CSVshape_weight_HFStats2Down);
  tree_new->Branch("bTagSF_CSVshape_weight_LFStats1Up",&_bTagSF_CSVshape_weight_LFStats1Up);
  tree_new->Branch("bTagSF_CSVshape_weight_LFStats1Down",&_bTagSF_CSVshape_weight_LFStats1Down);
  tree_new->Branch("bTagSF_CSVshape_weight_LFStats2Up",&_bTagSF_CSVshape_weight_LFStats2Up);
  tree_new->Branch("bTagSF_CSVshape_weight_LFStats2Down",&_bTagSF_CSVshape_weight_LFStats2Down);
  tree_new->Branch("bTagSF_CSVshape_weight_CFErr1Up",&_bTagSF_CSVshape_weight_CFErr1Up);
  tree_new->Branch("bTagSF_CSVshape_weight_CFErr1Down",&_bTagSF_CSVshape_weight_CFErr1Down);
  tree_new->Branch("bTagSF_CSVshape_weight_CFErr2Up",&_bTagSF_CSVshape_weight_CFErr2Up);
  tree_new->Branch("bTagSF_CSVshape_weight_CFErr2Down",&_bTagSF_CSVshape_weight_CFErr2Down);

  tree_new->Branch("genH_decayMode",&_genH_decayMode);
  tree_new->Branch("n_genW",&_n_genW,"n_genW/I");
  tree_new->Branch("n_genZ",&_n_genZ,"n_genZ/I");


  if(JEC==0 && TES==0){

    tree_new->Branch("genpart_pt",&_genpart_pt);
    tree_new->Branch("genpart_eta",&_genpart_eta);
    tree_new->Branch("genpart_phi",&_genpart_phi);
    tree_new->Branch("genpart_i_closest_daughter",&_genpart_i_closest_daughter);
    tree_new->Branch("genpart_dR_closest_daughter",&_genpart_dR_closest_daughter);
    
    tree_new->Branch("n_genlep",&_n_genlep,"n_genlep/I");
    tree_new->Branch("n_genlep10",&_n_genlep10,"n_genlep10/I");
    tree_new->Branch("n_genlep20",&_n_genlep20,"n_genlep20/I");
    tree_new->Branch("n_genlep20_eta21",&_n_genlep20_eta21,"n_genlep20_eta21/I");
    tree_new->Branch("n_genlep_fromTop",&_n_genlep_fromTop,"n_genlep_fromTop/I");
    tree_new->Branch("n_genlep_fromTau",&_n_genlep_fromTau,"n_genlep_fromTau/I");
    tree_new->Branch("genlep_pdg",&_genlep_pdg);
    tree_new->Branch("genlep_charge",&_genlep_charge);
    tree_new->Branch("genlep_e",&_genlep_e);
    tree_new->Branch("genlep_px",&_genlep_px);
    tree_new->Branch("genlep_py",&_genlep_py);
    tree_new->Branch("genlep_pz",&_genlep_pz);
    tree_new->Branch("genlep_pt",&_genlep_pt);
    tree_new->Branch("genlep_eta",&_genlep_eta);
    tree_new->Branch("genlep_phi",&_genlep_phi);
    tree_new->Branch("genlep_flags",&_genlep_flags);
    tree_new->Branch("genlep_TauMothInd",&_genlep_TauMothInd);
    tree_new->Branch("genlep_TopMothInd",&_genlep_TopMothInd);
    tree_new->Branch("genlep_WMothInd",&_genlep_WMothInd);
    tree_new->Branch("genlep_ZMothInd",&_genlep_ZMothInd);
    
    tree_new->Branch("n_gentauh",&_n_gentauh,"n_gentauh/I");
    tree_new->Branch("n_gentauh10",&_n_gentauh10,"n_gentauh10/I");
    tree_new->Branch("n_gentauh30",&_n_gentauh30,"n_gentauh30/I");
    tree_new->Branch("n_gentauh30_eta21",&_n_gentauh30_eta21,"n_gentauh30_eta21/I");
    tree_new->Branch("n_gentauh_fromTop",&_n_gentauh_fromTop,"n_gentauh_fromTop/I");
    tree_new->Branch("n_gentauh_fromTau",&_n_gentauh_fromTau,"n_gentauh_fromTau/I");
    tree_new->Branch("gentauh_charge",&_gentauh_charge);
    tree_new->Branch("gentauh_e",&_gentauh_e);
    tree_new->Branch("gentauh_px",&_gentauh_px);
    tree_new->Branch("gentauh_py",&_gentauh_py);
    tree_new->Branch("gentauh_pz",&_gentauh_pz);
    tree_new->Branch("gentauh_pt",&_gentauh_pt);
    tree_new->Branch("gentauh_eta",&_gentauh_eta);
    tree_new->Branch("gentauh_phi",&_gentauh_phi);
    tree_new->Branch("gentauh_flags",&_gentauh_flags);
    tree_new->Branch("gentauh_TauMothInd",&_gentauh_TauMothInd);
    tree_new->Branch("gentauh_TopMothInd",&_gentauh_TopMothInd);
    tree_new->Branch("gentauh_WMothInd",&_gentauh_WMothInd);
    
    tree_new->Branch("n_gentau",&_n_gentau,"n_gentau/I");
    tree_new->Branch("n_gentau_fromTop",&_n_gentau_fromTop,"n_gentau_fromTop/I");
    tree_new->Branch("n_gentau_fromH",&_n_gentau_fromH,"n_gentau_fromH/I");
    tree_new->Branch("gentau_decayMode",&_gentau_decayMode);
    tree_new->Branch("gentau_charge",&_gentau_charge);
    tree_new->Branch("gentau_e",&_gentau_e);
    tree_new->Branch("gentau_px",&_gentau_px);
    tree_new->Branch("gentau_py",&_gentau_py);
    tree_new->Branch("gentau_pz",&_gentau_pz);
    tree_new->Branch("gentau_pt",&_gentau_pt);
    tree_new->Branch("gentau_eta",&_gentau_eta);
    tree_new->Branch("gentau_phi",&_gentau_phi);
    tree_new->Branch("gentau_flags",&_gentau_flags);
    tree_new->Branch("gentau_TopMothInd",&_gentau_TopMothInd);
    tree_new->Branch("gentau_WMothInd",&_gentau_WMothInd);
    tree_new->Branch("gentau_HMothInd",&_gentau_HMothInd);
    tree_new->Branch("gentau_ZMothInd",&_gentau_ZMothInd);
    
    tree_new->Branch("n_genH",&_n_genH,"n_genH/I");
    tree_new->Branch("genH_e",&_genH_e);
    tree_new->Branch("genH_px",&_genH_px);
    tree_new->Branch("genH_py",&_genH_py);
    tree_new->Branch("genH_pz",&_genH_pz);
    tree_new->Branch("genH_pt",&_genH_pt);
    tree_new->Branch("genH_eta",&_genH_eta);
    tree_new->Branch("genH_phi",&_genH_phi);
    tree_new->Branch("genH_flags",&_genH_flags);

    tree_new->Branch("n_genZ",&_n_genZ,"n_genZ/I");
    tree_new->Branch("genZ_decayMode",&_genZ_decayMode);
    tree_new->Branch("genZ_e",&_genZ_e);
    tree_new->Branch("genZ_px",&_genZ_px);
    tree_new->Branch("genZ_py",&_genZ_py);
    tree_new->Branch("genZ_pz",&_genZ_pz);
    tree_new->Branch("genZ_pt",&_genZ_pt);
    tree_new->Branch("genZ_eta",&_genZ_eta);
    tree_new->Branch("genZ_phi",&_genZ_phi);
    tree_new->Branch("genZ_flags",&_genZ_flags);
    
    tree_new->Branch("n_gentop",&_n_gentop,"n_gentop/I");
    tree_new->Branch("gentop_pdg",&_gentop_pdg);
    tree_new->Branch("gentop_decayMode",&_gentop_decayMode);
    tree_new->Branch("gentop_e",&_gentop_e);
    tree_new->Branch("gentop_px",&_gentop_px);
    tree_new->Branch("gentop_py",&_gentop_py);
    tree_new->Branch("gentop_pz",&_gentop_pz);
    tree_new->Branch("gentop_pt",&_gentop_pt);
    tree_new->Branch("gentop_eta",&_gentop_eta);
    tree_new->Branch("gentop_phi",&_gentop_phi);
    tree_new->Branch("gentop_flags",&_gentop_flags);
    tree_new->Branch("gentop_isRecoMatched",&_gentop_isRecoMatched);
    tree_new->Branch("gentop_i_recoPFJet_btag",&_gentop_i_recoPFJet_btag);
    tree_new->Branch("gentop_i_recoPFJet_untag1",&_gentop_i_recoPFJet_untag1);
    tree_new->Branch("gentop_i_recoPFJet_untag2",&_gentop_i_recoPFJet_untag2);
    tree_new->Branch("gentop_i_recolep",&_gentop_i_recolep);
    
    tree_new->Branch("n_genW_fromTop",&_n_genW_fromTop,"n_genW_fromTop/I");
    tree_new->Branch("genW_pdg",&_genW_pdg);
    tree_new->Branch("genW_decayMode",&_genW_decayMode);
    tree_new->Branch("genW_e",&_genW_e);
    tree_new->Branch("genW_px",&_genW_px);
    tree_new->Branch("genW_py",&_genW_py);
    tree_new->Branch("genW_pz",&_genW_pz);
    tree_new->Branch("genW_pt",&_genW_pt);
    tree_new->Branch("genW_eta",&_genW_eta);
    tree_new->Branch("genW_phi",&_genW_phi);
    tree_new->Branch("genW_flags",&_genW_flags);
    tree_new->Branch("genW_TopMothInd",&_genW_TopMothInd);
    
    tree_new->Branch("n_genb",&_n_genb,"n_genb/I");
    tree_new->Branch("n_genb10",&_n_genb10,"n_genb10/I");
    tree_new->Branch("n_genb_fromTop",&_n_genb_fromTop,"n_genb_fromTop/I");
    tree_new->Branch("genb_pdg",&_genb_pdg);
    tree_new->Branch("genb_e",&_genb_e);
    tree_new->Branch("genb_px",&_genb_px);
    tree_new->Branch("genb_py",&_genb_py);
    tree_new->Branch("genb_pz",&_genb_pz);
    tree_new->Branch("genb_pt",&_genb_pt);
    tree_new->Branch("genb_eta",&_genb_eta);
    tree_new->Branch("genb_phi",&_genb_phi);
    tree_new->Branch("genb_flags",&_genb_flags);
    tree_new->Branch("genb_TopMothInd",&_genb_TopMothInd);
    tree_new->Branch("genb_WMothInd",&_genb_WMothInd);
    tree_new->Branch("genb_i_closest_recolep",&_genb_i_closest_recolep);
    tree_new->Branch("genb_dR_closest_recolep",&_genb_dR_closest_recolep);
    
    
    tree_new->Branch("n_genq",&_n_genq,"n_genq/I");
    tree_new->Branch("n_genq10",&_n_genq10,"n_genq10/I");
    tree_new->Branch("n_genq_fromTop",&_n_genq_fromTop,"n_genq_fromTop/I");
    tree_new->Branch("genq_pdg",&_genq_pdg);
    tree_new->Branch("genq_e",&_genq_e);
    tree_new->Branch("genq_px",&_genq_px);
    tree_new->Branch("genq_py",&_genq_py);
    tree_new->Branch("genq_pz",&_genq_pz);
    tree_new->Branch("genq_pt",&_genq_pt);
    tree_new->Branch("genq_eta",&_genq_eta);
    tree_new->Branch("genq_phi",&_genq_phi);
    tree_new->Branch("genq_flags",&_genq_flags);
    tree_new->Branch("genq_TopMothInd",&_genq_TopMothInd);
    tree_new->Branch("genq_WMothInd",&_genq_WMothInd);
    
    tree_new->Branch("n_gennu",&_n_gennu,"n_gennu/I");
    tree_new->Branch("n_gennu_fromTop",&_n_gennu_fromTop,"n_gennu_fromTop/I");
    tree_new->Branch("n_gennu_fromTau",&_n_gennu_fromTau,"n_gennu_fromTau/I");
    tree_new->Branch("gennu_pdg",&_gennu_pdg);
    tree_new->Branch("gennu_e",&_gennu_e);
    tree_new->Branch("gennu_px",&_gennu_px);
    tree_new->Branch("gennu_py",&_gennu_py);
    tree_new->Branch("gennu_pz",&_gennu_pz);
    tree_new->Branch("gennu_pt",&_gennu_pt);
    tree_new->Branch("gennu_eta",&_gennu_eta);
    tree_new->Branch("gennu_phi",&_gennu_phi);
    tree_new->Branch("gennu_flags",&_gennu_flags);
    tree_new->Branch("gennu_TauMothInd",&_gennu_TauMothInd);
    tree_new->Branch("gennu_TopMothInd",&_gennu_TopMothInd);
    tree_new->Branch("gennu_WMothInd",&_gennu_WMothInd);
    
  }

  //Old branches only there in MC
  //Dummy created in data as well
  
  int _PUNumInteractions = -1;
  vector<int> _daughters_genindex;
  float _MC_weight = -1., _MC_weight_scale_muF0p5 = -1., _MC_weight_scale_muF2 = -1., _MC_weight_scale_muR0p5 = -1., _MC_weight_scale_muR2 = -1.;
  float _MC_weight_tHq = -1, _MC_weight_tHW = -1;
  float _lheHt = -1.;
  int _lheNOutPartons = -1;
  int _lheNOutB = -1;
  int _lheNOutC = -1;
  float _aMCatNLOweight = -1.;
  vector<float> _genpart_px_dummy, _genpart_py_dummy, _genpart_pz_dummy, _genpart_e_dummy;
  vector<int> _genpart_pdg_dummy, _genpart_status_dummy, _genpart_HMothInd_dummy, _genpart_MSSMHMothInd_dummy, _genpart_TopMothInd_dummy, _genpart_TauMothInd_dummy, _genpart_ZMothInd_dummy, _genpart_WMothInd_dummy, _genpart_bMothInd_dummy, _genpart_HZDecayMode_dummy, _genpart_TopDecayMode_dummy, _genpart_WDecayMode_dummy, _genpart_TauGenDecayMode_dummy, _genpart_TauGenDetailedDecayMode_dummy, _genpart_flags_dummy;
  vector<float> _genjet_px_dummy, _genjet_py_dummy, _genjet_pz_dummy, _genjet_e_dummy;
  vector<int> _genjet_partonFlavour_dummy, _genjet_hadronFlavour_dummy;
  int _NUP = -1;

  vector<int> _daughters_TauUpExists_dummy;
  vector<float> _daughters_e_TauUp_dummy, _daughters_px_TauUp_dummy, _daughters_py_TauUp_dummy, _daughters_pz_TauUp_dummy;
  vector<int> _daughters_TauDownExists_dummy;
  vector<float> _daughters_e_TauDown_dummy, _daughters_px_TauDown_dummy, _daughters_py_TauDown_dummy, _daughters_pz_TauDown_dummy;
  vector<float> _SVfit_fitMETPhiTauUp_dummy, _SVfit_fitMETRhoTauUp_dummy, _SVfit_phiUncTauUp_dummy, _SVfit_phiTauUp_dummy, _SVfit_etaUncTauUp_dummy, _SVfit_etaTauUp_dummy, _SVfit_ptUncTauUp_dummy, _SVfit_ptTauUp_dummy, _SVfitTransverseMassTauUp_dummy, _SVfitMassTauUp_dummy;
  vector<float> _SVfit_fitMETPhiTauDown_dummy, _SVfit_fitMETRhoTauDown_dummy, _SVfit_phiUncTauDown_dummy, _SVfit_phiTauDown_dummy, _SVfit_etaUncTauDown_dummy, _SVfit_etaTauDown_dummy, _SVfit_ptUncTauDown_dummy, _SVfit_ptTauDown_dummy, _SVfitTransverseMassTauDown_dummy, _SVfitMassTauDown_dummy;

  if(!isMC && JEC==0 && TES==0){
    
    tree_new->Branch("npu",&_npu,"npu/F");
    tree_new->Branch("PUNumInteractions",&_PUNumInteractions,"PUNumInteractions/I");
    tree_new->Branch("daughters_genindex",&_daughters_genindex);
    tree_new->Branch("MC_weight",&_MC_weight,"MC_weight/F");
    tree_new->Branch("MC_weight_tHq",&_MC_weight_tHq,"MC_weight_tHq/F");
    tree_new->Branch("MC_weight_tHW",&_MC_weight_tHW,"MC_weight_tHW/F");
    tree_new->Branch("MC_weight_scale_muF0p5",&_MC_weight_scale_muF0p5,"MC_weight_scale_muF0p5/F");
    tree_new->Branch("MC_weight_scale_muF2",&_MC_weight_scale_muF2,"MC_weight_scale_muF2/F");
    tree_new->Branch("MC_weight_scale_muR0p5",&_MC_weight_scale_muR0p5,"MC_weight_scale_muR0p5/F");
    tree_new->Branch("MC_weight_scale_muR2",&_MC_weight_scale_muR2,"MC_weight_scale_muR2/F");
    tree_new->Branch("PU_weight",&_PU_weight,"PU_weight/F");

    tree_new->Branch("lheHt",&_lheHt,"lheHt/F");
    tree_new->Branch("lheNOutPartons",&_lheNOutPartons,"lheNOutPartons/I");
    tree_new->Branch("lheNOutB",&_lheNOutB,"lheNOutB/I");
    tree_new->Branch("lheNOutC",&_lheNOutC,"lheNOutC/I");
    tree_new->Branch("aMCatNLOweight",&_aMCatNLOweight,"aMCatNLOweight/F");

    tree_new->Branch("genpart_px",&_genpart_px_dummy);
    tree_new->Branch("genpart_py",&_genpart_py_dummy);
    tree_new->Branch("genpart_pz",&_genpart_pz_dummy);
    tree_new->Branch("genpart_e",&_genpart_e_dummy);
    tree_new->Branch("genpart_pdg",&_genpart_pdg_dummy);
    tree_new->Branch("genpart_status",&_genpart_status_dummy);
    tree_new->Branch("genpart_HMothInd",&_genpart_HMothInd_dummy);
    tree_new->Branch("genpart_MSSMHMothInd",&_genpart_MSSMHMothInd_dummy);
    tree_new->Branch("genpart_TopMothInd",&_genpart_TopMothInd_dummy);
    tree_new->Branch("genpart_TauMothInd",&_genpart_TauMothInd_dummy);
    tree_new->Branch("genpart_ZMothInd",&_genpart_ZMothInd_dummy);
    tree_new->Branch("genpart_WMothInd",&_genpart_WMothInd_dummy);
    tree_new->Branch("genpart_bMothInd",&_genpart_bMothInd_dummy);
    tree_new->Branch("genpart_HZDecayMode",&_genpart_HZDecayMode_dummy);
    tree_new->Branch("genpart_TopDecayMode",&_genpart_TopDecayMode_dummy);
    tree_new->Branch("genpart_WDecayMode",&_genpart_WDecayMode_dummy);
    tree_new->Branch("genpart_TauGenDecayMode",&_genpart_TauGenDecayMode_dummy);
    tree_new->Branch("genpart_TauGenDetailedDecayMode",&_genpart_TauGenDetailedDecayMode_dummy);
    tree_new->Branch("genpart_flags",&_genpart_flags_dummy);
    tree_new->Branch("genpart_status",&_genpart_status_dummy);    
 
    tree_new->Branch("genjet_px",&_genjet_px_dummy);
    tree_new->Branch("genjet_py",&_genjet_py_dummy);
    tree_new->Branch("genjet_pz",&_genjet_pz_dummy);
    tree_new->Branch("genjet_e",&_genjet_e_dummy);
    tree_new->Branch("genjet_partonFlavour",&_genjet_partonFlavour_dummy);
    tree_new->Branch("genjet_hadronFlavour",&_genjet_hadronFlavour_dummy);
 
    tree_new->Branch("NUP",&_NUP,"NUP/I");

    tree_new->Branch("daughters_TauUpExists",&_daughters_TauUpExists_dummy);
    tree_new->Branch("daughters_px_TauUp",&_daughters_px_TauUp_dummy);
    tree_new->Branch("daughters_py_TauUp",&_daughters_py_TauUp_dummy);
    tree_new->Branch("daughters_pz_TauUp",&_daughters_pz_TauUp_dummy);
    tree_new->Branch("daughters_e_TauUp",&_daughters_e_TauUp_dummy);
    tree_new->Branch("daughters_TauDownExists",&_daughters_TauDownExists_dummy);
    tree_new->Branch("daughters_px_TauDown",&_daughters_px_TauDown_dummy);
    tree_new->Branch("daughters_py_TauDown",&_daughters_py_TauDown_dummy);
    tree_new->Branch("daughters_pz_TauDown",&_daughters_pz_TauDown_dummy);
    tree_new->Branch("daughters_e_TauDown",&_daughters_e_TauDown_dummy);

    tree_new->Branch("SVfit_fitMETPhiTauUp",&_SVfit_fitMETPhiTauUp_dummy);
    tree_new->Branch("SVfit_fitMETRhoTauUp",&_SVfit_fitMETRhoTauUp_dummy);
    tree_new->Branch("SVfit_phiUncTauUp",&_SVfit_phiUncTauUp_dummy);
    tree_new->Branch("SVfit_phiTauUp",&_SVfit_phiTauUp_dummy);
    tree_new->Branch("SVfit_etaUncTauUp",&_SVfit_etaUncTauUp_dummy);
    tree_new->Branch("SVfit_etaTauUp",&_SVfit_etaTauUp_dummy);
    tree_new->Branch("SVfit_ptUncTauUp",&_SVfit_ptUncTauUp_dummy);
    tree_new->Branch("SVfit_ptTauUp",&_SVfit_ptTauUp_dummy);
    tree_new->Branch("SVfitTransverseMassTauUp",&_SVfitTransverseMassTauUp_dummy);
    tree_new->Branch("SVfitMassTauUp",&_SVfitMassTauUp_dummy);

    tree_new->Branch("SVfit_fitMETPhiTauDown",&_SVfit_fitMETPhiTauDown_dummy);
    tree_new->Branch("SVfit_fitMETRhoTauDown",&_SVfit_fitMETRhoTauDown_dummy);
    tree_new->Branch("SVfit_phiUncTauDown",&_SVfit_phiUncTauDown_dummy);
    tree_new->Branch("SVfit_phiTauDown",&_SVfit_phiTauDown_dummy);
    tree_new->Branch("SVfit_etaUncTauDown",&_SVfit_etaUncTauDown_dummy);
    tree_new->Branch("SVfit_etaTauDown",&_SVfit_etaTauDown_dummy);
    tree_new->Branch("SVfit_ptUncTauDown",&_SVfit_ptUncTauDown_dummy);
    tree_new->Branch("SVfit_ptTauDown",&_SVfit_ptTauDown_dummy);
    tree_new->Branch("SVfitTransverseMassTauDown",&_SVfitTransverseMassTauDown_dummy);
    tree_new->Branch("SVfitMassTauDown",&_SVfitMassTauDown_dummy);

  }


  //Branches need even with JEC/TES Up/Down

  //unsigned long long _EventNumber = -1;
  //int _RunNumber = -1, _lumi = -1;

  float _PFMETCov00=-1., _PFMETCov01=-1., _PFMETCov10=-1., _PFMETCov11=-1.;

  if(JEC!=0 || TES!=0){

    tree->SetBranchAddress("triggerbit",&_triggerbit);
    tree->SetBranchAddress("metfilterbit",&_metfilterbit);
    tree->SetBranchAddress("passecalBadCalibFilterUpdate",&_passecalBadCalibFilterUpdate);

    tree->SetBranchAddress("PFMETCov00",&_PFMETCov00);
    tree->SetBranchAddress("PFMETCov01",&_PFMETCov01);
    tree->SetBranchAddress("PFMETCov10",&_PFMETCov10);
    tree->SetBranchAddress("PFMETCov11",&_PFMETCov11);

    tree->SetBranchAddress("npu",&_npu);

    tree->SetBranchAddress("MC_weight",&_MC_weight);
    tree->SetBranchAddress("MC_weight_tHq",&_MC_weight_tHq);
    tree->SetBranchAddress("MC_weight_tHW",&_MC_weight_tHW);   

    tree->SetBranchAddress("PU_weight",&_PU_weight);
 
    tree_new->Branch("EventNumber",&_EventNumber,"EventNumber/l");
    tree_new->Branch("RunNumber",&_RunNumber,"RunNumber/I");
    tree_new->Branch("lumi",&_lumi,"lumi/I");
    tree_new->Branch("year",&_year,"year/I");

    tree_new->Branch("triggerbit",&_triggerbit,"triggerbit/L");
    tree_new->Branch("metfilterbit",&_metfilterbit,"metfilterbit/L");
    tree_new->Branch("passecalBadCalibFilterUpdate",&_passecalBadCalibFilterUpdate,"passecalBadCalibFilterUpdate/O");
    tree_new->Branch("PFMETCov00",&_PFMETCov00,"PFMETCov00/F");
    tree_new->Branch("PFMETCov01",&_PFMETCov01,"PFMETCov01/F");
    tree_new->Branch("PFMETCov10",&_PFMETCov10,"PFMETCov10/F");
    tree_new->Branch("PFMETCov11",&_PFMETCov11,"PFMETCov11/F");

    tree_new->Branch("npu",&_npu,"npu/F");

    tree_new->Branch("MC_weight",&_MC_weight,"MC_weight/F");
    tree_new->Branch("MC_weight_tHq",&_MC_weight_tHq,"MC_weight_tHq/F");
    tree_new->Branch("MC_weight_tHW",&_MC_weight_tHW,"MC_weight_tHW/F");

    tree_new->Branch("PU_weight",&_PU_weight,"PU_weight/F");

  }


  //TauID WPs + trigger counters
  TFile* f_tauID = TFile::Open(list[0]);
  TH1F* h_tauID = (TH1F*)f_tauID->Get("HTauTauTree/TauIDs");
  TH1F* h_Counter = (TH1F*) f_tauID->Get("HTauTauTree/Counters");
  h_tauID->SetDirectory(0);
  h_Counter->SetDirectory(0);
  f_tauID->Close();

  std::map<std::string,int> map_tauID;

  cout<<endl;
  //cout<<"TauID"<<endl;
  for(int i=1; i<=h_tauID->GetNbinsX();i++){
    const char* bin_label=h_tauID->GetXaxis()->GetBinLabel(i);
    std::string str(bin_label);
    //cout<<"i="<<i<<" bin_label="<<bin_label<<endl;
    map_tauID[str]=i-1;
}


  //Lepton MVA
  cout<<"Getting BDT lepton MVA"<<endl;
  TMVA::Reader* mu_reader_2016  = BookLeptonMVAReader("lepMVA_weights", "mu_BDTG_2016.weights.xml", "mu");
  TMVA::Reader* ele_reader_2016 = BookLeptonMVAReader("lepMVA_weights", "el_BDTG_2016.weights.xml", "ele");
  TMVA::Reader* mu_reader_2017  = BookLeptonMVAReader("lepMVA_weights", "mu_BDTG_2017.weights.xml", "mu");
  TMVA::Reader* ele_reader_2017 = BookLeptonMVAReader("lepMVA_weights", "el_BDTG_2017.weights.xml", "ele");

  //BDTs multileptons
  cout<<"Getting BDT multileptons signal extraction"<<endl;
  TMVA::Reader* MVA_2lSS_TTV_reader = Book_2LSS_TTV_MVAReader("2lSSMVA_weights","2lss_ttV_BDTG.weights.xml");
  TMVA::Reader* MVA_2lSS_TT_reader  = Book_2LSS_TT_MVAReader("2lSSMVA_weights","2lss_ttbar_BDTG.weights.xml");
  TMVA::Reader* MVA_3l_TTV_reader   = Book_3l_TTV_MVAReader("3lMVA_weights","3l_ttV_BDTG.weights.xml");
  TMVA::Reader* MVA_3l_TT_reader    = Book_3l_TT_MVAReader("3lMVA_weights","3l_ttbar_BDTG.weights.xml");

  //fake rate leptons
  cout<<"Getting lepton fake rates"<<endl;
  TFile* f_fakerate = TFile::Open("fake_rate_weights/FR_lep_ttH_mva090_2017_CERN_2018May29.root");

  TH2F* h_fakerate_mu = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb");
  h_fakerate_mu->SetDirectory(0);
  TH2F* h_fakerate_el = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC");
  h_fakerate_el->SetDirectory(0);

  TH2F* h_fakerate_mu_data_up = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb_up");
  h_fakerate_mu_data_up->SetDirectory(0);
  TH2F* h_fakerate_el_data_up = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC_up");
  h_fakerate_el_data_up->SetDirectory(0);

  TH2F* h_fakerate_mu_data_down = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb_down");
  h_fakerate_mu_data_down->SetDirectory(0);
  TH2F* h_fakerate_el_data_down = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC_down");
  h_fakerate_el_data_down->SetDirectory(0);

  TH2F* h_fakerate_mu_data_pt1 = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb_pt1");
  h_fakerate_mu_data_pt1->SetDirectory(0);
  TH2F* h_fakerate_el_data_pt1 = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC_pt1");
  h_fakerate_el_data_pt1->SetDirectory(0);

  TH2F* h_fakerate_mu_data_pt2 = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb_pt2");
  h_fakerate_mu_data_pt2->SetDirectory(0);
  TH2F* h_fakerate_el_data_pt2 = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC_pt2");
  h_fakerate_el_data_pt2->SetDirectory(0);

  TH2F* h_fakerate_mu_data_be1 = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb_be1");
  h_fakerate_mu_data_be1->SetDirectory(0);
  TH2F* h_fakerate_el_data_be1 = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC_be1");
  h_fakerate_el_data_be1->SetDirectory(0);

  TH2F* h_fakerate_mu_data_be2 = (TH2F*)f_fakerate->Get("FR_mva090_mu_data_comb_be2");
  h_fakerate_mu_data_be2->SetDirectory(0);
  TH2F* h_fakerate_el_data_be2 = (TH2F*)f_fakerate->Get("FR_mva090_el_data_comb_NC_be2");
  h_fakerate_el_data_be2->SetDirectory(0);

  TH2F* h_fakerate_mu_QCD = (TH2F*)f_fakerate->Get("FR_mva090_mu_QCD");
  h_fakerate_mu_QCD->SetDirectory(0);
  TH2F* h_fakerate_el_QCD = (TH2F*)f_fakerate->Get("FR_mva090_el_QCD_NC");
  h_fakerate_el_QCD->SetDirectory(0);

  TH2F* h_fakerate_mu_TT = (TH2F*)f_fakerate->Get("FR_mva090_mu_TT");
  h_fakerate_mu_TT->SetDirectory(0);
  TH2F* h_fakerate_el_TT = (TH2F*)f_fakerate->Get("FR_mva090_el_TT");
  h_fakerate_el_TT->SetDirectory(0);

  f_fakerate->Close();

  //fake rate taus
  cout<<"Getting tau fake rates"<<endl;

  TFile* f_fakerate_tau = TFile::Open("fake_rate_weights/FR_tau_2017_v2.root");

  TGraphAsymmErrors* gr_fakerate_tau_loose_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_loose_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_medium_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_medium_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_tight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_tight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_Vtight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_Vtight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_VVtight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVVTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_VVtight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVVTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
	
  TF1* f_dataMC_fakerate_tau_loose_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_loose_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_medium_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_medium_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_tight_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_tight_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");  
  TF1* f_dataMC_fakerate_tau_Vtight_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_Vtight_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");  
  TF1* f_dataMC_fakerate_tau_VVtight_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_VVtight_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");  

  TF1* f_dataMC_fakerate_tau_loose_barrel_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  TF1* f_dataMC_fakerate_tau_loose_barrel_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  TF1* f_dataMC_fakerate_tau_loose_barrel_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Up");
  TF1* f_dataMC_fakerate_tau_loose_barrel_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Down");

  TF1* f_dataMC_fakerate_tau_loose_endcaps_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  TF1* f_dataMC_fakerate_tau_loose_endcaps_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  TF1* f_dataMC_fakerate_tau_loose_endcaps_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Up");
  TF1* f_dataMC_fakerate_tau_loose_endcaps_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaLoose/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Down");

  TF1* f_dataMC_fakerate_tau_medium_barrel_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  TF1* f_dataMC_fakerate_tau_medium_barrel_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  TF1* f_dataMC_fakerate_tau_medium_barrel_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Up");
  TF1* f_dataMC_fakerate_tau_medium_barrel_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt_par2Down");

  TF1* f_dataMC_fakerate_tau_medium_endcaps_par1Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Up");
  TF1* f_dataMC_fakerate_tau_medium_endcaps_par1Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par1Down");
  TF1* f_dataMC_fakerate_tau_medium_endcaps_par2Up = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Up");
  TF1* f_dataMC_fakerate_tau_medium_endcaps_par2Down = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt_par2Down");
  
  // charge flip leptons
  cout<<"Getting charge flip rates"<<endl;
  TFile* f_QFrate = TFile::Open("charge_flip_weights/ElectronChargeMisIdRates_2017_2018Jun22.root");
  TH2F* h_QFrate_el = (TH2F*)f_QFrate->Get("eChargeMisIdRates");
  h_QFrate_el->SetDirectory(0);
  f_QFrate->Close();

  //BTag SF
  cout<<"Getting btag SFs"<<endl;

  bTagSF_CSVshape* bTagSF_CSVshape_DeepJet;
  bTagSF_CSVshape_DeepJet = new bTagSF_CSVshape("bTagSF_weights/DeepJet_2016LegacySF_V1.csv");
  /*if (year==2016) bTagSF_CSVshape_DeepJet = new bTagSF_CSVshape("bTagSF_weights/DeepJet_2016LegacySF_V1.csv");    
  else if (year==2017) bTagSF_CSVshape_DeepJet = new bTagSF_CSVshape("bTagSF_weights/DeepFlavour_94XSF_V2_B_F.csv"); 
  else if (year==2018) bTagSF_CSVshape_DeepJet = new bTagSF_CSVshape("bTagSF_weights/DeepJet_102XSF_V1.csv");*/ 

  /*bTagSF_CSVshape* bTagSF_CSVshape_DeepCSV;
  if (year==2016) bTagSF_CSVshape_DeepCSV = new bTagSF_CSVshape("bTagSF_weights/DeepCSV_2016LegacySF_V1.csv"); 
  else if (year==2017) bTagSF_CSVshape_DeepCSV = new bTagSF_CSVshape("bTagSF_weights/DeepCSV_94XSF_V4_B_F.csv"); 
  else if (year==2018) bTagSF_CSVshape_DeepCSV = new bTagSF_CSVshape("bTagSF_weights/DeepCSV_102XSF_V1.csv");*/
  

  int skip_entries = 0;

  if(split>0){
    nentries/=split;
    skip_entries=(i_split-1)*nentries;    
  }

  cout<<"nentries="<<nentries<<endl;

  for (int i=skip_entries;i<skip_entries+nentries;i++) {

    if(i%10000==0) cout<<"i="<<i<<endl;

    _daughters_pt.clear();
    _daughters_eta.clear();
    _daughters_phi.clear();
    _daughters_dR_closest_jet.clear();

    _jets_pt.clear();
    _jets_eta.clear();
    _jets_phi.clear();

    _n_recomu_presel = 0;
    _n_recomu_fakeable = 0;
    _n_recomu_cutsel = 0;
    _n_recomu_mvasel = 0;
    _recomu_charge.clear();
    _recomu_e.clear();
    _recomu_px.clear();
    _recomu_py.clear();
    _recomu_pz.clear();
    _recomu_pt.clear();
    _recomu_conept.clear();
    _recomu_eta.clear();
    _recomu_phi.clear();
    _recomu_dxy.clear();
    _recomu_dz.clear();
    _recomu_dxy_innerTrack.clear();
    _recomu_dz_innerTrack.clear();
    _recomu_jetNDauChargedMVASel.clear();
    _recomu_jetNDauChargedMVASel_nanoAOD.clear();
    _recomu_miniRelIso.clear();
    _recomu_miniRelIso_nanoAOD.clear();
    _recomu_miniIsoCharged.clear();
    _recomu_miniIsoCharged_nanoAOD.clear();
    _recomu_miniIsoNeutral.clear();
    _recomu_miniIsoNeutral_nanoAOD.clear();
    _recomu_sip3D.clear();
    _recomu_jetPtRel.clear();
    _recomu_jetPtRel_nanoAOD.clear();
    _recomu_jetCSV.clear();
    _recomu_jetDeepCSV.clear();
    _recomu_jetDeepJet.clear();
    _recomu_jetPtRatio.clear();
    _recomu_jetPtRatio_nanoAOD.clear();
    _recomu_combreliso04.clear();
    _recomu_lepMVA_Id.clear();
    _recomu_leptonMVA.clear();
    _recomu_rel_error_trackpt.clear();
    _recomu_mediumID.clear();
    _recomu_isfakeable.clear();
    _recomu_iscutsel.clear();
    _recomu_ismvasel.clear();
    _recomu_TopMothInd.clear();
    _recomu_HMothInd.clear();
    _recomu_goodsign.clear();
    _recomu_fakerate.clear();
    _recomu_fakerate_up.clear();
    _recomu_fakerate_down.clear();
    _recomu_fakerate_pt1.clear();
    _recomu_fakerate_pt2.clear();
    _recomu_fakerate_be1.clear();
    _recomu_fakerate_be2.clear();
    _recomu_fakerate_QCD_MC.clear();
    _recomu_fakerate_ttbar_MC.clear();
    _recomu_isGenMatched.clear();
    _recomu_isGenChargeMatched.clear();
    _recomu_genMatchInd.clear();
    _recomu_matchedJetIndex.clear();

    _n_recoele_presel = 0;
    _n_recoele_fakeable = 0;
    _n_recoele_cutsel = 0;
    _n_recoele_mvasel = 0;
    _recoele_charge.clear();
    _recoele_e.clear();
    _recoele_px.clear();
    _recoele_py.clear();
    _recoele_pz.clear();
    _recoele_pt.clear();
    _recoele_corr_e.clear();
    _recoele_corr_pt.clear();
    _recoele_conept.clear();
    _recoele_eta.clear();
    _recoele_phi.clear();
    _recoele_dxy.clear();
    _recoele_dz.clear();
    _recoele_jetNDauChargedMVASel.clear();
    _recoele_jetNDauChargedMVASel_nanoAOD.clear();
    _recoele_miniRelIso.clear();
    _recoele_miniRelIso_nanoAOD.clear();
    _recoele_PFRelIsoAll_nanoAOD.clear();
    _recoele_PFRelIsoAll04_nanoAOD.clear();
    _recoele_miniIsoCharged.clear();
    _recoele_miniIsoCharged_nanoAOD.clear();
    _recoele_PFIsoCharged_nanoAOD.clear();
    _recoele_PFIsoCharged_nanoAOD.clear();
    _recoele_miniIsoNeutral.clear();
    _recoele_miniIsoNeutral_nanoAOD.clear();
    _recoele_PFIsoNeutral_nanoAOD.clear();
    _recoele_sip3D.clear();
    _recoele_jetPtRel.clear();
    _recoele_jetPtRel_nanoAOD.clear();
    _recoele_jetCSV.clear();
    _recoele_jetDeepCSV.clear();
    _recoele_jetDeepJet.clear();
    _recoele_jetPtRatio.clear();
    _recoele_jetPtRatio_nanoAOD.clear();
    _recoele_lepMVA_Id.clear();
    _recoele_leptonMVA.clear();
    _recoele_isChargeConsistent.clear();
    _recoele_passConversionVeto.clear();
    _recoele_nMissingHits.clear();
    _recoele_sigmaEtaEta.clear();
    _recoele_HoE.clear();
    _recoele_deltaEta.clear();      
    _recoele_deltaPhi.clear();
    _recoele_OoEminusOoP.clear();
    _recoele_isfakeable.clear();
    _recoele_iscutsel.clear();
    _recoele_ismvasel.clear();
    _recoele_TopMothInd.clear();
    _recoele_HMothInd.clear();
    _recoele_goodsign.clear();
    _recoele_fakerate.clear();
    _recoele_fakerate_up.clear();
    _recoele_fakerate_down.clear();
    _recoele_fakerate_pt1.clear();
    _recoele_fakerate_pt2.clear();
    _recoele_fakerate_be1.clear();
    _recoele_fakerate_be2.clear();
    _recoele_fakerate_QCD_MC.clear();
    _recoele_fakerate_ttbar_MC.clear();
    _recoele_QFrate.clear();
    _recoele_isGenMatched.clear();
    _recoele_isGenChargeMatched.clear();
    _recoele_genMatchInd.clear();
    _recoele_matchedJetIndex.clear();

    _n_recolep_presel = 0;
    _n_recolep_fakeable = 0;
    _n_recolep_cutsel = 0;
    _n_recolep_mvasel = 0;
    _recolep_charge.clear();
    _recolep_pdg.clear();
    _recolep_e.clear();
    _recolep_px.clear();
    _recolep_py.clear();
    _recolep_pz.clear();
    _recolep_pt.clear();
    _recolep_conept.clear();
    _recolep_eta.clear();
    _recolep_phi.clear();
    _recolep_leptonMVA.clear();
    _recolep_fakerate.clear();
    _recolep_fakerate_up.clear();
    _recolep_fakerate_down.clear();
    _recolep_fakerate_pt1.clear();
    _recolep_fakerate_pt2.clear();
    _recolep_fakerate_be1.clear();
    _recolep_fakerate_be2.clear();
    _recolep_fakerate_QCD_MC.clear();
    _recolep_fakerate_ttbar_MC.clear();
    _recolep_QFrate.clear(); 
    _recolep_isfakeable.clear();
    _recolep_iscutsel.clear();
    _recolep_ismvasel.clear();
    _recolep_tightcharge.clear();
    _recolep_eleconv_misshits.clear();
    _recolep_isGenMatched.clear();
    _recolep_isGenChargeMatched.clear();
    _recolep_genMatchInd.clear();

    _n_recotauh = 0;
    _recotauh_charge.clear();
    _recotauh_decayMode.clear();
    _recotauh_e.clear();
    _recotauh_px.clear();
    _recotauh_py.clear();
    _recotauh_pz.clear();
    _recotauh_pt.clear();
    _recotauh_eta.clear();
    _recotauh_phi.clear();
    _recotauh_dxy.clear();
    _recotauh_dz.clear();
    _recotauh_iso.clear();
    _recotauh_isGenMatched.clear();
    _recotauh_genMatchInd.clear();
    _recotauh_matchedJetIndex.clear();

    _recotauh_decayModeFindingOldDMs.clear();
    _recotauh_decayModeFindingNewDMs.clear();
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits.clear();
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits.clear();
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits.clear();
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03.clear();
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03.clear();
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03.clear();
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT.clear();
    _recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw.clear();
    _recotauh_againstMuonLoose3.clear();
    _recotauh_againstMuonTight3.clear();
    _recotauh_againstElectronVLooseMVA6.clear();
    _recotauh_againstElectronLooseMVA6.clear();
    _recotauh_againstElectronMediumMVA6.clear();
    _recotauh_againstElectronTightMVA6.clear();
    _recotauh_againstElectronVTightMVA6.clear();

    _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT.clear();
    _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT.clear();
    _recotauh_fakerate_byTightIsolationMVArun2v2017v2DBdR03oldDMwLT.clear();
    _recotauh_fakerate_byVTightIsolationMVArun2v2017v2DBdR03oldDMwLT.clear();

    _recotauh_i_closest_genpart.clear();
    _recotauh_dR_closest_genpart.clear();

    _n_recoPFJet = 0;
    _recoPFJet_e.clear();
    _recoPFJet_pt.clear();
    _recoPFJet_px.clear();
    _recoPFJet_py.clear();
    _recoPFJet_pz.clear();
    _recoPFJet_eta.clear();
    _recoPFJet_phi.clear();
    _recoPFJet_CSVscore.clear(); 
    _recoPFJet_DeepCSVscore.clear();
    _recoPFJet_DeepJetscore.clear();
    _recoPFJet_jecUnc.clear();   
    _recoPFJet_Flavour.clear(); 
    _recoPFJet_hadronFlavour.clear(); 
    _recoPFJet_QGdiscr.clear();

    _n_recoPFFwdJet = 0;
    _recoPFFwdJet_e.clear();
    _recoPFFwdJet_pt.clear();
    _recoPFFwdJet_px.clear();
    _recoPFFwdJet_py.clear();
    _recoPFFwdJet_pz.clear();
    _recoPFFwdJet_eta.clear();
    _recoPFFwdJet_phi.clear();
    _recoPFFwdJet_CSVscore.clear(); 
    _recoPFFwdJet_DeepCSVscore.clear();
    _recoPFFwdJet_DeepJetscore.clear();
    _recoPFFwdJet_jecUnc.clear();   
    _recoPFFwdJet_Flavour.clear(); 
    _recoPFFwdJet_hadronFlavour.clear(); 
    _recoPFFwdJet_QGdiscr.clear();

    _n_recoPFak8Jet = 0;
    _recoPFak8Jet_e.clear();
    _recoPFak8Jet_pt.clear();
    _recoPFak8Jet_px.clear();
    _recoPFak8Jet_py.clear();
    _recoPFak8Jet_pz.clear();
    _recoPFak8Jet_eta.clear();
    _recoPFak8Jet_phi.clear();
    _recoPFak8Jet_SoftDropMass.clear();
    _recoPFak8Jet_tau1.clear();
    _recoPFak8Jet_tau2.clear();
    _recoPFak8Jet_tau3.clear();
    _recoPFak8Jet_nsubjets.clear();

    _recoPFak8Jet_subjets_e.clear();
    _recoPFak8Jet_subjets_pt.clear();
    _recoPFak8Jet_subjets_px.clear();
    _recoPFak8Jet_subjets_py.clear();
    _recoPFak8Jet_subjets_pz.clear();
    _recoPFak8Jet_subjets_eta.clear();
    _recoPFak8Jet_subjets_phi.clear();

    _recoPFJet_i_closest_genpart.clear();
    _recoPFJet_dR_closest_genpart.clear();
    _recoPFJet_i_2nd_closest_genpart.clear();
    _recoPFJet_dR_2nd_closest_genpart.clear();
    _recoPFJet_i_closest_tau.clear();
    _recoPFJet_dR_closest_tau.clear();

    _recoPFJet_CSVsort_e.clear();
    _recoPFJet_CSVsort_pt.clear();
    _recoPFJet_CSVsort_px.clear();
    _recoPFJet_CSVsort_py.clear();
    _recoPFJet_CSVsort_pz.clear();
    _recoPFJet_CSVsort_eta.clear();
    _recoPFJet_CSVsort_phi.clear();
    _recoPFJet_CSVsort_CSVscore.clear();  
    _recoPFJet_CSVsort_DeepCSVscore.clear();
    _recoPFJet_CSVsort_DeepJetscore.clear();
    _recoPFJet_CSVsort_jecUnc.clear(); 
    _recoPFJet_CSVsort_Flavour.clear(); 
    _recoPFJet_CSVsort_hadronFlavour.clear(); 
    _recoPFJet_CSVsort_QGdiscr.clear();   

    _recoPFJet_DeepCSVsort_e.clear();
    _recoPFJet_DeepCSVsort_pt.clear();
    _recoPFJet_DeepCSVsort_px.clear();
    _recoPFJet_DeepCSVsort_py.clear();
    _recoPFJet_DeepCSVsort_pz.clear();
    _recoPFJet_DeepCSVsort_eta.clear();
    _recoPFJet_DeepCSVsort_phi.clear();
    _recoPFJet_DeepCSVsort_CSVscore.clear();
    _recoPFJet_DeepCSVsort_DeepCSVscore.clear();
    _recoPFJet_DeepCSVsort_DeepJetscore.clear();
    _recoPFJet_DeepCSVsort_jecUnc.clear(); 
    _recoPFJet_DeepCSVsort_Flavour.clear(); 
    _recoPFJet_DeepCSVsort_hadronFlavour.clear(); 
    _recoPFJet_DeepCSVsort_QGdiscr.clear(); 

    _recoPFJet_DeepJetsort_e.clear();
    _recoPFJet_DeepJetsort_pt.clear();
    _recoPFJet_DeepJetsort_px.clear();
    _recoPFJet_DeepJetsort_py.clear();
    _recoPFJet_DeepJetsort_pz.clear();
    _recoPFJet_DeepJetsort_eta.clear();
    _recoPFJet_DeepJetsort_phi.clear();
    _recoPFJet_DeepJetsort_CSVscore.clear();
    _recoPFJet_DeepJetsort_DeepCSVscore.clear();
    _recoPFJet_DeepJetsort_DeepJetscore.clear();
    _recoPFJet_DeepJetsort_jecUnc.clear(); 
    _recoPFJet_DeepJetsort_Flavour.clear(); 
    _recoPFJet_DeepJetsort_hadronFlavour.clear(); 
    _recoPFJet_DeepJetsort_QGdiscr.clear();   
   
    _recoPFJet_CSVsort_i_closest_genb.clear();
    _recoPFJet_CSVsort_dR_closest_genb.clear(); 
    _recoPFJet_CSVsort_i_closest_gentauh.clear();
    _recoPFJet_CSVsort_dR_closest_gentauh.clear(); 

    _recoPFJet_DeepCSVsort_i_closest_genb.clear();
    _recoPFJet_DeepCSVsort_dR_closest_genb.clear();
    _recoPFJet_DeepCSVsort_i_closest_gentauh.clear();
    _recoPFJet_DeepCSVsort_dR_closest_gentauh.clear();

    _recoPFJet_DeepJetsort_i_closest_genb.clear();
    _recoPFJet_DeepJetsort_dR_closest_genb.clear();
    _recoPFJet_DeepJetsort_i_closest_gentauh.clear();
    _recoPFJet_DeepJetsort_dR_closest_gentauh.clear();

    _n_recoPFJet_btag_medium = 0;
    _n_recoPFJet_btag_loose = 0;
    _recoPFJet_btag_e.clear();
    _recoPFJet_btag_pt.clear();
    _recoPFJet_btag_px.clear();
    _recoPFJet_btag_py.clear();
    _recoPFJet_btag_pz.clear();
    _recoPFJet_btag_eta.clear();
    _recoPFJet_btag_phi.clear();
    _recoPFJet_btag_CSVscore.clear();   
    _recoPFJet_btag_DeepCSVscore.clear();
    _recoPFJet_btag_DeepJetscore.clear();
    _recoPFJet_btag_jecUnc.clear();    
    _recoPFJet_btag_Flavour.clear();    
    _recoPFJet_btag_hadronFlavour.clear(); 
    _recoPFJet_btag_QGdiscr.clear();    

    _n_recoPFJet_untag = 0;
    _recoPFJet_untag_e.clear();
    _recoPFJet_untag_pt.clear();
    _recoPFJet_untag_px.clear();
    _recoPFJet_untag_py.clear();
    _recoPFJet_untag_pz.clear();
    _recoPFJet_untag_eta.clear();
    _recoPFJet_untag_phi.clear();
    _recoPFJet_untag_CSVscore.clear(); 
    _recoPFJet_untag_DeepCSVscore.clear(); 
    _recoPFJet_untag_DeepJetscore.clear();
    _recoPFJet_untag_jecUnc.clear();    
    _recoPFJet_untag_Flavour.clear();
    _recoPFJet_untag_hadronFlavour.clear();
    _recoPFJet_untag_QGdiscr.clear();

    _n_pair_Wtag_recoPFJet_untag = 0;
    _recoPFJet_untag_best_mW = -1;
    _recoPFJet_untag_Wtag_e.clear();
    _recoPFJet_untag_Wtag_pt.clear();
    _recoPFJet_untag_Wtag_px.clear();
    _recoPFJet_untag_Wtag_py.clear();
    _recoPFJet_untag_Wtag_pz.clear();
    _recoPFJet_untag_Wtag_eta.clear();
    _recoPFJet_untag_Wtag_phi.clear();
    _recoPFJet_untag_Wtag_CSVscore.clear();    
    _recoPFJet_untag_Wtag_DeepCSVscore.clear();
    _recoPFJet_untag_Wtag_DeepJetscore.clear();
    _recoPFJet_untag_Wtag_jecUnc.clear();    
    _recoPFJet_untag_Wtag_Flavour.clear();    
    _recoPFJet_untag_Wtag_hadronFlavour.clear();
    _recoPFJet_untag_Wtag_QGdiscr.clear();         
 
    _mtop_had_perm.clear();
    _mblep_perm.clear();
    _mleptauh_perm.clear();

    _PFMETx = 0;
    _PFMETy = 0;
    _PFMET = 0;
    _PFMET_phi = 0;

    _HTmiss = 0;
    _ETmissLD = 0;
    _MT_lep1 = 0;
    _mindR_lep1_recoPFjet = 0;
    _mindR_lep2_recoPFjet = 0;
    _lep1_conept = 0;
    _lep2_conept = 0;
    _lep3_conept = 0;
    _avg_dr_jet = 0;

    _MVA_2lSS_ttV = 0;
    _MVA_2lSS_ttbar = 0;
    _MVA_3l_ttV = 0;
    _MVA_3l_ttbar = 0;

    //scale factors and systematics

    _PU_weight = 0;

    _tauSF_weight = 0;
    _tauSF_weight_tauNormUp = 0;
    _tauSF_weight_tauNormDown = 0;
    _tauSF_weight_tauShapeUp = 0;
    _tauSF_weight_tauShapeDown = 0;

    _bTagSF_CSVshape_weight = 0;
    _bTagSF_CSVshape_weight_JESUp = 0;
    _bTagSF_CSVshape_weight_JESDown = 0;
    _bTagSF_CSVshape_weight_LFUp = 0;
    _bTagSF_CSVshape_weight_LFDown = 0;
    _bTagSF_CSVshape_weight_HFUp = 0;
    _bTagSF_CSVshape_weight_HFDown = 0;
    _bTagSF_CSVshape_weight_HFStats1Up = 0;
    _bTagSF_CSVshape_weight_HFStats1Down = 0;
    _bTagSF_CSVshape_weight_HFStats2Up = 0;
    _bTagSF_CSVshape_weight_HFStats2Down = 0;
    _bTagSF_CSVshape_weight_LFStats1Up = 0;
    _bTagSF_CSVshape_weight_LFStats1Down = 0;
    _bTagSF_CSVshape_weight_LFStats2Up = 0;
    _bTagSF_CSVshape_weight_LFStats2Down = 0;
    _bTagSF_CSVshape_weight_CFErr1Up = 0;
    _bTagSF_CSVshape_weight_CFErr1Down = 0;
    _bTagSF_CSVshape_weight_CFErr2Up = 0;
    _bTagSF_CSVshape_weight_CFErr2Down = 0;

    _genpart_pt.clear();
    _genpart_eta.clear();
    _genpart_phi.clear();
    _genpart_i_closest_daughter.clear();
    _genpart_dR_closest_daughter.clear();

    _n_genlep = 0;
    _n_genlep10 = 0;
    _n_genlep20 = 0;
    _n_genlep20_eta21 = 0;
    _n_genlep_fromTop = 0;
    _n_genlep_fromTau = 0;
    _genlep_pdg.clear();
    _genlep_charge.clear();
    _genlep_e.clear();
    _genlep_px.clear();
    _genlep_py.clear();
    _genlep_pz.clear();
    _genlep_pt.clear();
    _genlep_eta.clear();
    _genlep_phi.clear();
    _genlep_flags.clear();
    _genlep_TauMothInd.clear();
    _genlep_TopMothInd.clear();
    _genlep_WMothInd.clear();
    _genlep_ZMothInd.clear();

    _n_gentauh = 0;
    _n_gentauh10 = 0;
    _n_gentauh30 = 0;
    _n_gentauh30_eta21 = 0;
    _n_gentauh_fromTop = 0;
    _n_gentauh_fromTau = 0;
    _gentauh_charge.clear();
    _gentauh_e.clear();
    _gentauh_px.clear();
    _gentauh_py.clear();
    _gentauh_pz.clear();
    _gentauh_pt.clear();
    _gentauh_eta.clear();
    _gentauh_phi.clear();
    _gentauh_flags.clear();
    _gentauh_TauMothInd.clear();
    _gentauh_TopMothInd.clear();
    _gentauh_WMothInd.clear();

    _n_gentau = 0;
    _n_gentau_fromTop = 0;
    _n_gentau_fromH = 0;
    _gentau_decayMode.clear();
    _gentau_charge.clear();
    _gentau_e.clear();
    _gentau_px.clear();
    _gentau_py.clear();
    _gentau_pz.clear();
    _gentau_pt.clear();
    _gentau_eta.clear();
    _gentau_phi.clear();
    _gentau_flags.clear();
    _gentau_TopMothInd.clear();
    _gentau_WMothInd.clear();
    _gentau_HMothInd.clear();
    _gentau_ZMothInd.clear();

    _n_genH = 0;
    _genH_decayMode.clear();
    _genH_e.clear();
    _genH_px.clear();
    _genH_py.clear();
    _genH_pz.clear();
    _genH_pt.clear();
    _genH_eta.clear();
    _genH_phi.clear();
    _genH_flags.clear();

    _n_genZ = 0;
    _genZ_decayMode.clear();
    _genZ_e.clear();
    _genZ_px.clear();
    _genZ_py.clear();
    _genZ_pz.clear();
    _genZ_pt.clear();
    _genZ_eta.clear();
    _genZ_phi.clear();
    _genZ_flags.clear();

    _n_gentop = 0;
    _gentop_pdg.clear();
    _gentop_decayMode.clear();
    _gentop_e.clear();
    _gentop_px.clear();
    _gentop_py.clear();
    _gentop_pz.clear();
    _gentop_pt.clear();
    _gentop_eta.clear();
    _gentop_phi.clear();
    _gentop_flags.clear();
    _gentop_isRecoMatched.clear();
    _gentop_i_recoPFJet_btag.clear();
    _gentop_i_recoPFJet_untag1.clear();
    _gentop_i_recoPFJet_untag2.clear();
    _gentop_i_recolep.clear();

    _n_genW = 0;
    _n_genW_fromTop = 0;
    _genW_pdg.clear();
    _genW_decayMode.clear();
    _genW_e.clear();
    _genW_px.clear();
    _genW_py.clear();
    _genW_pz.clear();
    _genW_pt.clear();
    _genW_eta.clear();
    _genW_phi.clear();
    _genW_flags.clear();
    _genW_TopMothInd.clear();

    _n_genb = 0;
    _n_genb10 = 0;
    _n_genb_fromTop = 0;
    _genb_pdg.clear();
    _genb_e.clear();
    _genb_px.clear();
    _genb_py.clear();
    _genb_pz.clear();
    _genb_pt.clear();
    _genb_eta.clear();
    _genb_phi.clear();
    _genb_flags.clear();
    _genb_TopMothInd.clear();
    _genb_WMothInd.clear();
    _genb_i_closest_recolep.clear();
    _genb_dR_closest_recolep.clear();

    _n_genq = 0;
    _n_genq10 = 0;
    _n_genq_fromTop = 0;
    _genq_pdg.clear();
    _genq_e.clear();
    _genq_px.clear();
    _genq_py.clear();
    _genq_pz.clear();
    _genq_pt.clear();
    _genq_eta.clear();
    _genq_phi.clear();
    _genq_flags.clear();
    _genq_TopMothInd.clear();
    _genq_WMothInd.clear();

    _n_gennu = 0;
    _n_gennu_fromTop = 0;
    _n_gennu_fromTau = 0;
    _gennu_pdg.clear();
    _gennu_e.clear();
    _gennu_px.clear();
    _gennu_py.clear();
    _gennu_pz.clear();
    _gennu_pt.clear();
    _gennu_eta.clear();
    _gennu_phi.clear();
    _gennu_flags.clear();
    _gennu_TauMothInd.clear();
    _gennu_TopMothInd.clear();
    _gennu_WMothInd.clear();

    _npu = 0;

    _jets_e = 0;
    _jets_px = 0;
    _jets_py = 0;
    _jets_pz = 0;
    _jets_jecUnc = 0;
    _jets_Flavour = 0;
    _jets_HadronFlavour = 0;

    _jets_PUJetID = 0;
    _PFjetID = 0;
    _bCSVscore = 0;
    _bDeepCSV_probb = 0;
    _bDeepCSV_probbb = 0;
    _bDeepFlavor_probb = 0;
    _bDeepFlavor_probbb = 0;
    _bDeepFlavor_problepb = 0;
    _jets_QGdiscr = 0;

    _ak8jets_px = 0;
    _ak8jets_py = 0;
    _ak8jets_pz = 0;
    _ak8jets_e = 0;
    _ak8jets_SoftDropMass = 0;
    _ak8jets_PrunedMass = 0;
    _ak8jets_TrimmedMass = 0;
    _ak8jets_FilteredMass = 0;
    _ak8jets_tau1 = 0;
    _ak8jets_tau2 = 0;
    _ak8jets_tau3 = 0;
    _ak8jets_CSV = 0;
    _ak8jets_nsubjets = 0;

    _subjets_px = 0;
    _subjets_py = 0;
    _subjets_pz = 0;
    _subjets_e = 0;
    _subjets_CSV = 0;
    _subjets_ak8MotherIdx = 0;

    _dxy = 0;
    _dz = 0;
    _dxy_innerTrack = 0;
    _dz_innerTrack = 0;
    _SIP = 0;
    _daughters_rel_error_trackpt = 0;
    _daughters_muonID = 0;
    _daughters_eleMissingHits = 0;
    _daughters_eleMissingLostHits = 0;
    _daughters_passConversionVeto = 0;
    _daughters_SCeta = 0;
    _daughters_IetaIeta = 0;
    _daughters_full5x5_IetaIeta = 0;
    _daughters_hOverE = 0;
    _daughters_deltaEtaSuperClusterTrackAtVtx = 0;
    _daughters_deltaPhiSuperClusterTrackAtVtx = 0;
    _daughters_IoEmIoP_ttH = 0;
    _daughters_eleMVAnt = 0;
    _daughters_eleMVAntNoIso = 0;
    _daughters_eleMVA_HZZ = 0;
    _daughters_iseleWPLoose = 0;
    _daughters_iseleNoIsoWPLoose = 0;
 
    _daughters_e = 0;
    _daughters_px = 0;
    _daughters_py = 0;
    _daughters_pz = 0;
    _daughters_matchedJetIndex = 0;

    _daughters_ecalTrkEnergyPostCorr = 0;
    _daughters_ecalTrkEnergyPreCorr = 0;
    _daughters_corr_ele = 0;
    _daughters_pt_corr = 0;
    _daughters_energy_corr = 0;

    _daughters_TauUpExists = 0;
    _daughters_e_TauUp = 0;
    _daughters_px_TauUp = 0;
    _daughters_py_TauUp = 0;
    _daughters_pz_TauUp = 0;
    _daughters_TauDownExists = 0;
    _daughters_e_TauDown = 0;
    _daughters_px_TauDown = 0;
    _daughters_py_TauDown = 0;
    _daughters_pz_TauDown = 0;

    _PDGIdDaughters = 0;
    _decayMode = 0;
    _combreliso = 0;
    _daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
    _daughters_decayModeFindingOldDMs = 0;
    _daughters_decayModeFindingNewDMs = 0;
    _daughters_byIsolationMVArun2017v2DBoldDMwLTraw2017 = 0;
    _tauID = 0;
    _triggerbit = 0;
    _metfilterbit = 0;
    _passecalBadCalibFilterUpdate = 0;

    _daughters_jetNDauChargedMVASel = 0;
    _daughters_jetNDauChargedMVASel_nanoAOD = 0;
    _daughters_miniRelIsoCharged = 0;
    _daughters_miniRelIsoNeutral = 0;
    _daughters_miniRelIsoCharged_nanoAOD = 0;
    _daughters_miniRelIso_nanoAOD = 0;
    _daughters_PFRelIsoCharged_nanoAOD = 0;
    _daughters_PFRelIsoAll_nanoAOD = 0;
    _daughters_PFRelIsoAll04_nanoAOD = 0;
    _daughters_jetPtRel = 0;
    _daughters_jetPtRel_nanoAOD = 0;
    _daughters_jetPtRatio = 0;
    _daughters_jetPtRatio_nanoAOD = 0;
    _daughters_jetBTagCSV = 0;
    _daughters_jetBTagDeepCSV = 0;
    _daughters_jetBTagDeepJet = 0;
    _daughters_lepMVA_mvaId = 0;
    _daughters_iseleChargeConsistent = 0;
 
    _met = 0;
    _metphi = 0;

    _genpart_px = 0;
    _genpart_py = 0;
    _genpart_pz = 0;
    _genpart_e = 0;
    _genpart_pdg = 0;
    _genpart_HMothInd = 0;
    _genpart_ZMothInd = 0;
    _genpart_TopMothInd = 0;
    _genpart_WMothInd = 0;
    _genpart_bMothInd = 0;
    _genpart_TauMothInd = 0;
    _genpart_HZDecayMode = 0;
    _genpart_TopDecayMode = 0;
    _genpart_WDecayMode = 0;
    _genpart_TauGenDecayMode = 0;
    _genpart_flags = 0;
    _genpart_status = 0;

    _EventNumber = -1;
    _RunNumber = -1;
    _lumi = -1;
    _year = -1;   
 
    _PFMETCov00 = -1.;
    _PFMETCov01 = -1.;
    _PFMETCov10 = -1.;
    _PFMETCov11 = -1.;
    
    _MC_weight = 0;
    _MC_weight_tHq = 0;
    _MC_weight_tHW = 0;
    
    int entry_ok = tree->GetEntry(i);
    if(entry_ok<0) continue;

    _PU_weight = get_pu_weight(_npu,isMC,sample);
    //cout << "_PU_weight " << _PU_weight << endl;
    

    //////////////////////////////////////////////
    ///                 Muons                  ///
    //////////////////////////////////////////////
   

    vector< pair<int,TLorentzVector> > reco_mus;
   	
    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){

      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );
           
      _daughters_pt.push_back(daughter.Pt());
      _daughters_eta.push_back(daughter.Eta());
      _daughters_phi.push_back(daughter.Phi());      


      float dR_min=-1;
      for(unsigned int i_jet=0; i_jet<(*_jets_e).size(); i_jet++){
	      TLorentzVector jet( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );
	      float dR = jet.DeltaR(daughter);
	      if(dR_min<0 || dR<dR_min)
	        dR_min = dR;
      }

      _daughters_dR_closest_jet.push_back(dR_min);

      if( fabs(PDGId)==13 ){
	
        //float dxy = (*_dxy_innerTrack)[i_daughter];
	      //float dz = (*_dz_innerTrack)[i_daughter];
	      float dxy = (*_dxy)[i_daughter];
	      float dz = (*_dz)[i_daughter];
	      float miniRelIsoCharged = (*_daughters_miniRelIsoCharged)[i_daughter];
        float miniRelIsoNeutral = (*_daughters_miniRelIsoNeutral)[i_daughter];
        float miniRelIsoAll = miniRelIsoCharged + miniRelIsoNeutral;
        float miniRelIsoCharged_nanoAOD = (*_daughters_miniRelIsoCharged_nanoAOD)[i_daughter]; //rel
        float miniRelIso_nanoAOD = (*_daughters_miniRelIso_nanoAOD)[i_daughter]; //rel
	      float miniRelIsoNeutral_nanoAOD = miniRelIso_nanoAOD - miniRelIsoCharged_nanoAOD; // rel
        float sip = (*_SIP)[i_daughter];
	      bool  looseID = (*_daughters_muonID)[i_daughter] & 1;
        bool  mediumID = ((*_daughters_muonID)[i_daughter]>>2) & 1; 

 
        if(daughter.Pt()>5 && fabs(daughter.Eta())<2.4 && fabs(dxy)<=0.05 && fabs(dz)<0.1 && miniRelIso_nanoAOD<0.4 && sip < 8 && looseID){

          ////////////////
          // Lepton MVA //
          ////////////////

          float leptonMVA = -999;

          lepMVA_pt = daughter.Pt();
          lepMVA_eta = daughter.Eta();
          lepMVA_jetNDauChargedMVASel = (*_daughters_jetNDauChargedMVASel_nanoAOD)[i_daughter]; 
          lepMVA_miniRelIsoCharged = miniRelIsoCharged_nanoAOD; 
          lepMVA_miniRelIsoNeutral = miniRelIsoNeutral_nanoAOD; 

          lepMVA_jetPtRel = 0.; 
	  lepMVA_jetPtRatio = 1.;      
          if(_daughters_dR_closest_jet[i_daughter]<0.4){
            lepMVA_jetPtRel   = (*_daughters_jetPtRel_nanoAOD)[i_daughter]; 
            lepMVA_jetPtRatio = std::min((*_daughters_jetPtRatio_nanoAOD)[i_daughter],float(1.5));
          }
          else{
            lepMVA_jetPtRel = 0.;
            lepMVA_jetPtRatio = 1 / ( 1+(*_combreliso)[i_daughter] ); 
          } 

          lepMVA_jetDF = std::max((*_daughters_jetBTagDeepJet)[i_daughter],float(0.));
          lepMVA_sip3d = (*_SIP)[i_daughter];
	  lepMVA_dxy = log(fabs((*_dxy)[i_daughter]));
	  lepMVA_dz = log(fabs((*_dz)[i_daughter]));
          lepMVA_Id = (*_daughters_lepMVA_mvaId)[i_daughter]; //segment compatibility

          
          if(year==2016) 
            leptonMVA = mu_reader_2016->EvaluateMVA("BDTG method");
          else if(year==2017 || year==2018) 
            leptonMVA = mu_reader_2017->EvaluateMVA("BDTG method");


          float conept;
          if (leptonMVA > 0.9 && mediumID) { conept = daughter.Pt(); }
          else { conept = 0.90*daughter.Pt()/lepMVA_jetPtRatio; }	

          if(conept_sorting)
	          daughter.SetPtEtaPhiM(conept,daughter.Eta(),daughter.Phi(),daughter.M());	  	    
           
	        pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
	        reco_mus.push_back(daughter_pair);
	      }
      }
      
    }


    sort(reco_mus.begin(), reco_mus.end(), pT_comparison_pairs); //sorting muons by pT

    _n_recomu_presel = reco_mus.size();

    for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){
      
      int i_daughter=reco_mus[i_mu].first;
      TLorentzVector muon=reco_mus[i_mu].second;  //reco_mus may have cone pt
      muon.SetPtEtaPhiM(_daughters_pt[i_daughter],muon.Eta(),muon.Phi(),muon.M());

      _recomu_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recomu_e.push_back( muon.E() );
      _recomu_px.push_back( muon.Px() );
      _recomu_py.push_back( muon.Py() );
      _recomu_pz.push_back( muon.Pz() );
      _recomu_pt.push_back( muon.Pt() );
      _recomu_eta.push_back( muon.Eta() );
      _recomu_phi.push_back( muon.Phi() );
      _recomu_dxy_innerTrack.push_back( (*_dxy_innerTrack)[i_daughter] );
      _recomu_dz_innerTrack.push_back( (*_dz_innerTrack)[i_daughter] );
      _recomu_dxy.push_back( (*_dxy)[i_daughter] );
      _recomu_dz.push_back( (*_dz)[i_daughter] );
      _recomu_jetNDauChargedMVASel.push_back( (*_daughters_jetNDauChargedMVASel)[i_daughter] );
      _recomu_jetNDauChargedMVASel_nanoAOD.push_back( (*_daughters_jetNDauChargedMVASel_nanoAOD)[i_daughter] );     
      _recomu_miniRelIso.push_back( (*_daughters_miniRelIsoCharged)[i_daughter] + (*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recomu_miniRelIso_nanoAOD.push_back( (*_daughters_miniRelIso_nanoAOD)[i_daughter] ); 
      _recomu_miniIsoCharged.push_back( muon.Pt()*(*_daughters_miniRelIsoCharged)[i_daughter] );
      _recomu_miniIsoCharged_nanoAOD.push_back( muon.Pt()*(*_daughters_miniRelIsoCharged_nanoAOD)[i_daughter] ); //not the relative one
      _recomu_miniIsoNeutral.push_back( muon.Pt()*(*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recomu_miniIsoNeutral_nanoAOD.push_back( muon.Pt()*(((*_daughters_miniRelIso_nanoAOD)[i_daughter]) - (*_daughters_miniRelIsoCharged_nanoAOD)[i_daughter]));
      _recomu_sip3D.push_back( (*_SIP)[i_daughter] );
      _recomu_jetCSV.push_back( std::max((*_daughters_jetBTagCSV)[i_daughter],float(0.)) );   
      _recomu_jetDeepCSV.push_back( std::max((*_daughters_jetBTagDeepCSV)[i_daughter],float(0.)) );
      _recomu_jetDeepJet.push_back( std::max((*_daughters_jetBTagDeepJet)[i_daughter],float(0.)) );
      _recomu_combreliso04.push_back( (*_combreliso)[i_daughter] );  
	    _recomu_jetPtRel.push_back( (*_daughters_jetPtRel)[i_daughter] );
	    _recomu_jetPtRel_nanoAOD.push_back( (*_daughters_jetPtRel_nanoAOD)[i_daughter] );
      _recomu_jetPtRatio.push_back( std::min((*_daughters_jetPtRatio)[i_daughter],float(1.5)) );
      _recomu_jetPtRatio_nanoAOD.push_back( std::min((*_daughters_jetPtRatio_nanoAOD)[i_daughter],float(1.5)) );   
      _recomu_lepMVA_Id.push_back( (*_daughters_lepMVA_mvaId)[i_daughter] );
      _recomu_matchedJetIndex.push_back( (*_daughters_matchedJetIndex)[i_daughter] );

      ////////////////
      // Lepton MVA //
      ////////////////
      
      float leptonMVA_ = -999;

      lepMVA_pt = _recomu_pt[i_mu];
      lepMVA_eta = _recomu_eta[i_mu];
      lepMVA_jetNDauChargedMVASel = _recomu_jetNDauChargedMVASel_nanoAOD[i_mu];
      lepMVA_miniRelIsoCharged =_recomu_miniIsoCharged_nanoAOD[i_mu] / lepMVA_pt; 
      lepMVA_miniRelIsoNeutral = _recomu_miniIsoNeutral_nanoAOD[i_mu] / lepMVA_pt;

      lepMVA_jetPtRel = 0.;
      lepMVA_jetPtRatio = 1.;
      if(_daughters_dR_closest_jet[i_daughter]<0.4){
        lepMVA_jetPtRel   = _recomu_jetPtRel_nanoAOD[i_mu];
        lepMVA_jetPtRatio = _recomu_jetPtRatio_nanoAOD[i_mu];    
      }
      else{
        lepMVA_jetPtRel = 0.;
        lepMVA_jetPtRatio = 1 / ( 1 + _recomu_combreliso04[i_mu] ); 
      } 

      lepMVA_jetDF = std::max(_recomu_jetDeepJet[i_mu],float(0.));  
      lepMVA_sip3d = _recomu_sip3D[i_mu];
      lepMVA_dxy = log(fabs(_recomu_dxy[i_mu]));
      lepMVA_dz = log(fabs(_recomu_dz[i_mu]));
      lepMVA_Id = _recomu_lepMVA_Id[i_mu];
   
      if(year==2016) 
        leptonMVA_ = mu_reader_2016->EvaluateMVA("BDTG method");
      else if(year==2017 || year==2018) 
        leptonMVA_ = mu_reader_2017->EvaluateMVA("BDTG method");

      /*if(_EventNumber == 46612 || _EventNumber == 46622 || _EventNumber == 46671 || _EventNumber == 46743 || _EventNumber == 46814 || _EventNumber == 46812 || _EventNumber == 46805){

         cout<<"----"<<endl;
         cout<<"nEvent "<<_EventNumber<<endl;
         cout<<"pt "<<lepMVA_pt<<endl;
         cout<<"eta "<<lepMVA_eta<<endl;
         cout<<"jetNDauChargedMVASel "<<lepMVA_jetNDauChargedMVASel<<endl;
         cout<<"miniRelIsoCharged "<<lepMVA_miniRelIsoCharged<<endl;
         cout<<"miniRelIsoNeutral "<<lepMVA_miniRelIsoNeutral<<endl;
         cout<<"jetPtRel "<<lepMVA_jetPtRel<<endl;
         cout<<"jetDF "<<lepMVA_jetDF<<endl;
         cout<<"jetPtRatio "<<lepMVA_jetPtRatio<<endl;
         cout<<"sip3d "<<lepMVA_sip3d<<endl;
         cout<<"abs(dxy) "<<lepMVA_dxy<<endl;
         cout<<"abs(dz) "<<lepMVA_dz<<endl;
         cout<<"seg comp "<<lepMVA_Id<<endl;
         cout<<"lep mva "<<leptonMVA_<<endl;
      }*/

      _recomu_leptonMVA.push_back( leptonMVA_ );

      bool  mediumID = ((*_daughters_muonID)[i_daughter]>>2) & 1; //mediumID
      float conept;

      if (leptonMVA_ > 0.9 && mediumID) 
        conept = muon.Pt();
      else 
        conept = 0.90*muon.Pt()/lepMVA_jetPtRatio;

      _recomu_conept.push_back( conept );

      float segm_comp = (*_daughters_lepMVA_mvaId)[i_daughter];
      
      //Fakeable
      bool isfakeable=false;

      if(conept>10 && _recomu_leptonMVA[i_mu]>=0.90 && _recomu_jetDeepCSV[i_mu]<0.4941) 
	  isfakeable=true;	
      else if(conept>10 && _recomu_leptonMVA[i_mu]<0.90 && _recomu_jetDeepCSV[i_mu]<0.07 && lepMVA_jetPtRatio>0.6 && segm_comp>0.3)
	  isfakeable=true;	

      _recomu_isfakeable.push_back(isfakeable);

      if(isfakeable){
	      _n_recomu_fakeable++;
        _n_recolep_fakeable++;
      }

      float miniIso = lepMVA_miniRelIsoCharged + lepMVA_miniRelIsoNeutral;
      float rel_error_trackpt = (*_daughters_rel_error_trackpt)[i_daughter];

      _recomu_rel_error_trackpt.push_back(rel_error_trackpt);
      _recomu_mediumID.push_back(mediumID);

      //Cut-based selection - to be updated for 2017 (?)
      bool iscutsel=false;
      if(muon.Pt()>10 && miniIso<0.2 && lepMVA_sip3d<4 && mediumID && rel_error_trackpt<0.2)
	      iscutsel=true;
	
      _recomu_iscutsel.push_back(iscutsel);
      _recolep_iscutsel.push_back(iscutsel);

      if(iscutsel){
	      _n_recomu_cutsel++;
        _n_recolep_cutsel++;
      }

      //MVA-based selection 
      bool ismvasel=false;

      if(conept>10 && _recomu_leptonMVA[i_mu]>=0.9 && _recomu_jetDeepCSV[i_mu]<0.4941 && mediumID) 
	      ismvasel=true;
	
      _recomu_ismvasel.push_back(ismvasel);
      
      if(ismvasel){
	      _n_recomu_mvasel++;	
        _n_recolep_mvasel++; 
      }
   
      //Fake rate
      int bin_FR = h_fakerate_mu->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      float FR = h_fakerate_mu->GetBinContent(bin_FR);
      _recomu_fakerate.push_back(FR);

      bin_FR = h_fakerate_mu_data_up->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_data_up->GetBinContent(bin_FR);
      _recomu_fakerate_up.push_back(FR);

      bin_FR = h_fakerate_mu_data_down->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_data_down->GetBinContent(bin_FR);
      _recomu_fakerate_down.push_back(FR);

      bin_FR = h_fakerate_mu_data_pt1->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_data_pt1->GetBinContent(bin_FR);
      _recomu_fakerate_pt1.push_back(FR);

      bin_FR = h_fakerate_mu_data_pt2->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_data_pt2->GetBinContent(bin_FR);
      _recomu_fakerate_pt2.push_back(FR);

      bin_FR = h_fakerate_mu_data_be1->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_data_be1->GetBinContent(bin_FR);
      _recomu_fakerate_be1.push_back(FR);

      bin_FR = h_fakerate_mu_data_be2->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_data_be2->GetBinContent(bin_FR);
      _recomu_fakerate_be2.push_back(FR);

      bin_FR = h_fakerate_mu_QCD->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_QCD->GetBinContent(bin_FR);
      _recomu_fakerate_QCD_MC.push_back(FR);

      bin_FR = h_fakerate_mu_TT->FindBin(min(conept,float(99.)), abs(muon.Eta()));
      FR = h_fakerate_mu_TT->GetBinContent(bin_FR);
      _recomu_fakerate_ttbar_MC.push_back(FR);


    }

    //////////////////////////////////////////////
    ///              Electrons                 ///
    //////////////////////////////////////////////
	  
    vector< pair<int,TLorentzVector> > reco_eles;
    vector< pair<int,TLorentzVector> > reco_eles_corr;

    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){

      int PDGId=(*_PDGIdDaughters)[i_daughter];

      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );

      TLorentzVector daughter_corr;
      daughter_corr.SetPtEtaPhiM((*_daughters_pt_corr)[i_daughter], daughter.Eta(), daughter.Phi(), daughter.M());

      if( fabs(PDGId)==11 ){
	
        float dxy = (*_dxy)[i_daughter];
	      float dz = (*_dz)[i_daughter];
	      float miniRelIsoCharged = (*_daughters_miniRelIsoCharged)[i_daughter];
        float miniRelIsoNeutral = (*_daughters_miniRelIsoNeutral)[i_daughter];
        float miniRelIsoAll = miniRelIsoCharged + miniRelIsoNeutral;
        float miniRelIsoCharged_nanoAOD = (*_daughters_miniRelIsoCharged_nanoAOD)[i_daughter]; 
        float miniRelIso_nanoAOD = (*_daughters_miniRelIso_nanoAOD)[i_daughter]; 
        float miniRelIsoNeutral_nanoAOD = miniRelIso_nanoAOD - miniRelIsoCharged_nanoAOD; 
        float PFRelIsoAll04_nanoAOD = (*_daughters_PFRelIsoAll04_nanoAOD)[i_daughter]; 
        float PFRelIsoAll_nanoAOD = (*_daughters_PFRelIsoAll_nanoAOD)[i_daughter]; 
        float sip = (*_SIP)[i_daughter];
	      float eleMVA = (*_daughters_eleMVAntNoIso)[i_daughter];
        bool LooseIdWP = (*_daughters_iseleNoIsoWPLoose)[i_daughter]; 
	      int eleMissingHits = (*_daughters_eleMissingHits)[i_daughter];
        int eleMissingLostHits = (*_daughters_eleMissingLostHits)[i_daughter];

        //scale and smear corrections
        float e_corr = (*_daughters_energy_corr)[i_daughter];
        float pt_corr = (*_daughters_pt_corr)[i_daughter];

        //if (_EventNumber == 46577 || _EventNumber == 46577 || _EventNumber == 46581 || _EventNumber == 46583 || _EventNumber == 46588){
        //if (_EventNumber == 46585 || _EventNumber == 46610 || _EventNumber == 46621 || _EventNumber == 46655 || _EventNumber == 46688){
           //cout<<"eta "<<daughter.Eta()<<",pt_corr "<<pt_corr<<",e_corr "<<e_corr<<endl;
           //cout<<"raw pT "<<daughter.Pt()<<",eta "<<daughter.Eta()<<",phi "<<daughter.Phi()<<",corr "<<corr<<",event "<<_EventNumber<<endl;
        //}

        float ptforcut = pt_corr;
        //float ptforcut = daughter.Pt();
	
	      if(ptforcut>7 && fabs(daughter.Eta())<2.5 && fabs(dxy)<=0.05 && fabs(dz)<0.1 && miniRelIso_nanoAOD<0.4 && sip < 8 && LooseIdWP && eleMissingLostHits<=1){
	  
          //muon-electron cleaning
          bool dR_veto=false;
	  
          for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){
	          TLorentzVector mu=reco_mus[i_mu].second;
	          float dR_ele_mu=mu.DeltaR(daughter);
	          if(dR_ele_mu<0.3){ //0.05 in 2017
	            dR_veto=true;
	           break;
	          }
	        }

	        if(dR_veto)
	          continue;

          ////////////////
          // Lepton MVA //
          ////////////////

          float leptonMVA = -999;

          lepMVA_pt = daughter.Pt(); //uncorrected pt
          lepMVA_eta = daughter.Eta();
          lepMVA_jetNDauChargedMVASel = (*_daughters_jetNDauChargedMVASel_nanoAOD)[i_daughter]; 
          lepMVA_miniRelIsoCharged = miniRelIsoCharged_nanoAOD; 
          lepMVA_miniRelIsoNeutral = miniRelIsoNeutral_nanoAOD;

          lepMVA_jetPtRel = 0.;
          lepMVA_jetPtRatio = 1.;
          if(_daughters_dR_closest_jet[i_daughter]<0.4){
            lepMVA_jetPtRel   = (*_daughters_jetPtRel_nanoAOD)[i_daughter]; 
            lepMVA_jetPtRatio = std::min((*_daughters_jetPtRatio_nanoAOD)[i_daughter],float(1.5)); 
          }
          else{
            lepMVA_jetPtRel = 0.;
            lepMVA_jetPtRatio = 1 / ( 1 + PFRelIsoAll04_nanoAOD ); 
          } 

          lepMVA_jetDF = std::max((*_daughters_jetBTagDeepJet)[i_daughter],float(0.));
          lepMVA_sip3d = (*_SIP)[i_daughter];
          lepMVA_dxy = log(fabs((*_dxy)[i_daughter]));
          lepMVA_dz = log(fabs((*_dz)[i_daughter]));
          lepMVA_Id = (*_daughters_lepMVA_mvaId)[i_daughter]; //eleID

          if(year==2016) 
            leptonMVA = ele_reader_2016->EvaluateMVA("BDTG method");
          else if(year==2017 || year==2018) 
            leptonMVA = ele_reader_2017->EvaluateMVA("BDTG method");

                float pt_forcone = (*_daughters_pt_corr)[i_daughter];
	        float conept = pt_forcone;
	        if(leptonMVA<0.90)
	          conept = 0.90*pt_forcone/lepMVA_jetPtRatio;
          
	        if(conept_sorting)
	          daughter.SetPtEtaPhiM(conept,daughter.Eta(),daughter.Phi(),daughter.M());	  

          pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
	        reco_eles.push_back(daughter_pair);

          pair<int,TLorentzVector> daughter_corr_pair = make_pair(i_daughter,daughter_corr);
          reco_eles_corr.push_back(daughter_corr_pair);
	      }

      }

    }

    sort(reco_eles.begin(), reco_eles.end(), pT_comparison_pairs);
    _n_recoele_presel = reco_eles.size();

    for(unsigned int i_ele=0; i_ele<reco_eles.size(); i_ele++){
      
      int i_daughter=reco_eles[i_ele].first;

      TLorentzVector elec=reco_eles[i_ele].second;  //reco_eles may have cone pt
      elec.SetPtEtaPhiM(_daughters_pt[i_daughter],elec.Eta(),elec.Phi(),elec.M());

      TLorentzVector elec_corr; //scale+smear
      elec_corr.SetPtEtaPhiM((*_daughters_pt_corr)[i_daughter],elec.Eta(),elec.Phi(),elec.M());

      _recoele_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recoele_e.push_back( elec.E() );
      _recoele_px.push_back( elec.Px() );
      _recoele_py.push_back( elec.Py() );
      _recoele_pz.push_back( elec.Pz() );
      _recoele_pt.push_back( elec.Pt() );
      _recoele_corr_e.push_back( (*_daughters_energy_corr)[i_daughter] );
      _recoele_corr_pt.push_back( (*_daughters_pt_corr)[i_daughter] );
      _recoele_eta.push_back( elec.Eta() );
      _recoele_phi.push_back( elec.Phi() );	  
      _recoele_dxy.push_back( (*_dxy)[i_daughter] );
      _recoele_dz.push_back( (*_dz)[i_daughter] );
      _recoele_jetNDauChargedMVASel.push_back( (*_daughters_jetNDauChargedMVASel)[i_daughter] );
      _recoele_jetNDauChargedMVASel_nanoAOD.push_back( (*_daughters_jetNDauChargedMVASel_nanoAOD)[i_daughter] );
      _recoele_PFRelIsoAll_nanoAOD.push_back( (*_daughters_PFRelIsoAll_nanoAOD)[i_daughter] );
      _recoele_PFRelIsoAll04_nanoAOD.push_back( (*_daughters_PFRelIsoAll04_nanoAOD)[i_daughter] );
      _recoele_miniIsoCharged.push_back( elec.Pt()*(*_daughters_miniRelIsoCharged)[i_daughter] );
      _recoele_miniRelIso.push_back( (*_daughters_miniRelIsoCharged)[i_daughter] + (*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recoele_miniRelIso_nanoAOD.push_back( (*_daughters_miniRelIso_nanoAOD)[i_daughter] );
      _recoele_miniIsoCharged_nanoAOD.push_back( elec.Pt()*(*_daughters_miniRelIsoCharged_nanoAOD)[i_daughter] );      
      _recoele_PFIsoCharged_nanoAOD.push_back( elec.Pt()*(*_daughters_PFRelIsoCharged_nanoAOD)[i_daughter] );
      _recoele_miniIsoNeutral.push_back( elec.Pt()*(*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recoele_miniIsoNeutral_nanoAOD.push_back( elec.Pt()*(((*_daughters_miniRelIso_nanoAOD)[i_daughter]) - (*_daughters_miniRelIsoCharged_nanoAOD)[i_daughter]));
      _recoele_PFIsoNeutral_nanoAOD.push_back( elec.Pt()*(((*_daughters_PFRelIsoAll_nanoAOD)[i_daughter]) - (*_daughters_PFRelIsoCharged_nanoAOD)[i_daughter]));
      _recoele_sip3D.push_back( (*_SIP)[i_daughter] );
      _recoele_jetCSV.push_back( std::max((*_daughters_jetBTagCSV)[i_daughter],float(0.)) );
      _recoele_jetDeepCSV.push_back( std::max((*_daughters_jetBTagDeepCSV)[i_daughter],float(0.)) );
      _recoele_jetDeepJet.push_back( std::max((*_daughters_jetBTagDeepJet)[i_daughter],float(0.)) );
	    _recoele_jetPtRel.push_back( (*_daughters_jetPtRel)[i_daughter] );
	    _recoele_jetPtRel_nanoAOD.push_back( (*_daughters_jetPtRel_nanoAOD)[i_daughter] );
	    _recoele_jetPtRatio.push_back( std::min((*_daughters_jetPtRatio)[i_daughter],float(1.5)) );
      _recoele_jetPtRatio_nanoAOD.push_back( std::min((*_daughters_jetPtRatio_nanoAOD)[i_daughter],float(1.5)) );
      _recoele_lepMVA_Id.push_back( (*_daughters_lepMVA_mvaId)[i_daughter] );
      _recoele_isChargeConsistent.push_back( (*_daughters_iseleChargeConsistent)[i_daughter] );
      _recoele_matchedJetIndex.push_back( (*_daughters_matchedJetIndex)[i_daughter] );

      ////////////////
      // Lepton MVA //
      ////////////////
      
      float leptonMVA_ = -999;

      lepMVA_pt = _recoele_pt[i_ele]; //uncorrected one
      lepMVA_eta = _recoele_eta[i_ele];
      lepMVA_jetNDauChargedMVASel = _recoele_jetNDauChargedMVASel_nanoAOD[i_ele];
      lepMVA_miniRelIsoCharged = _recoele_miniIsoCharged_nanoAOD[i_ele] / lepMVA_pt;
      lepMVA_miniRelIsoNeutral = _recoele_miniIsoNeutral_nanoAOD[i_ele] / lepMVA_pt;

      lepMVA_jetPtRel = 0.;
      lepMVA_jetPtRatio = 1.;
      if(_daughters_dR_closest_jet[i_daughter]<0.4){
        lepMVA_jetPtRel   = _recoele_jetPtRel_nanoAOD[i_ele];
        lepMVA_jetPtRatio = _recoele_jetPtRatio_nanoAOD[i_ele];    
      }
      else{
        lepMVA_jetPtRel = 0.;
        lepMVA_jetPtRatio = 1 / 1 + _recoele_PFRelIsoAll04_nanoAOD[i_ele];
      } 

      lepMVA_jetDF = std::max(_recoele_jetDeepJet[i_ele],float(0.));  
      lepMVA_sip3d = _recoele_sip3D[i_ele];
      lepMVA_dxy = log(fabs(_recoele_dxy[i_ele]));
      lepMVA_dz = log(fabs(_recoele_dz[i_ele]));
      lepMVA_Id = _recoele_lepMVA_Id[i_ele];
    
      if(year==2016) 
        leptonMVA_ = ele_reader_2016->EvaluateMVA("BDTG method");
      else if(year==2017 || year==2018) 
        leptonMVA_ = ele_reader_2017->EvaluateMVA("BDTG method");

      /*if(_EventNumber == 62084 || _EventNumber == 1694425 || _EventNumber == 1665111 || _EventNumber == 1665121 || _EventNumber == 2334303){

         cout<<"----"<<endl;
         cout<<"nEvent "<<_EventNumber<<endl;
         cout<<"pt "<<lepMVA_pt<<endl;
         cout<<"eta "<<lepMVA_eta<<endl;
         cout<<"jetNDauChargedMVASel "<<lepMVA_jetNDauChargedMVASel<<endl;
         cout<<"miniRelIsoCharged "<<lepMVA_miniRelIsoCharged<<endl;
         cout<<"miniRelIsoNeutral "<<lepMVA_miniRelIsoNeutral<<endl;
         cout<<"jetPtRel "<<lepMVA_jetPtRel<<endl;
         cout<<"jetDF "<<lepMVA_jetDF<<endl;
         cout<<"jetPtRatio "<<lepMVA_jetPtRatio<<endl;
         cout<<"sip3d "<<lepMVA_sip3d<<endl;
         cout<<"abs(dxy) "<<lepMVA_dxy<<endl;
         cout<<"abs(dz) "<<lepMVA_dz<<endl;
         cout<<"seg comp "<<lepMVA_Id<<endl;
         cout<<"lep mva "<<leptonMVA_<<endl;
      }*/

      _recoele_leptonMVA.push_back( leptonMVA_ );

      bool eleIDcut=false;
      float SCeta = (*_daughters_SCeta)[i_daughter];
      float sigma_IetaIeta = (*_daughters_full5x5_IetaIeta)[i_daughter]; 
      float hOverE = (*_daughters_hOverE)[i_daughter];
      float deltaEta_in = (*_daughters_deltaEtaSuperClusterTrackAtVtx)[i_daughter]; 
      float deltaPhi_in = (*_daughters_deltaPhiSuperClusterTrackAtVtx)[i_daughter];
      float IoEmIoP = (*_daughters_IoEmIoP_ttH)[i_daughter];

      _recoele_sigmaEtaEta.push_back(sigma_IetaIeta);
      _recoele_HoE.push_back(hOverE);
      _recoele_deltaEta.push_back(deltaEta_in);
      _recoele_deltaPhi.push_back(deltaPhi_in);
      _recoele_OoEminusOoP.push_back(IoEmIoP);
	
      if(fabs(SCeta)<1.479){
	    if(sigma_IetaIeta<0.011 && hOverE<0.1 && -0.04<IoEmIoP)
	      eleIDcut=true;
      }
      else{
	    if(sigma_IetaIeta<0.03 && hOverE<0.1 && -0.04<IoEmIoP)
	      eleIDcut=true; 
      }
	
      int eleMissingHits = (*_daughters_eleMissingHits)[i_daughter];
      int eleMissingLostHits = (*_daughters_eleMissingLostHits)[i_daughter];
      bool passConversionVeto = (*_daughters_passConversionVeto)[i_daughter];
	    
      _recoele_nMissingHits.push_back(eleMissingLostHits);
      _recoele_passConversionVeto.push_back(passConversionVeto);

      float conept;
      if (leptonMVA_ > 0.9 ) 
        conept = elec_corr.Pt();
      else 
        conept = 0.90*elec_corr.Pt()/lepMVA_jetPtRatio;

      _recoele_conept.push_back( conept );

      // fakeable selection
      bool isfakeable=false;
      if(conept>10 && eleIDcut && eleMissingLostHits==0 && passConversionVeto){
        if(_recoele_leptonMVA[i_ele]>0.9 && _recoele_jetDeepCSV[i_ele]<0.4941)
	    isfakeable=true;	
	else if(_recoele_leptonMVA[i_ele]<=0.9 && _recoele_jetDeepCSV[i_ele]<0.07 && lepMVA_jetPtRatio>0.6 && lepMVA_Id>0.5)
	    isfakeable=true;
      }	

      _recoele_isfakeable.push_back(isfakeable);

      if(isfakeable){
	      _n_recoele_fakeable++;
        _n_recolep_fakeable++;
      }

      //Cut-based selection - not used
      float miniIso = lepMVA_miniRelIsoCharged + lepMVA_miniRelIsoNeutral;

      float eleMVA = (*_daughters_lepMVA_mvaId)[i_daughter];
      bool TightIdEmuWP = false;
      if(fabs(elec.Eta())<0.8)
	      TightIdEmuWP = (eleMVA>0.87);
      else if(fabs(elec.Eta())<1.479)
	      TightIdEmuWP = (eleMVA>0.6);
      else
	      TightIdEmuWP = (eleMVA>0.17);

      bool iscutsel=false;
      if(elec.Pt()>15 && miniIso<0.1 && lepMVA_sip3d<4 && TightIdEmuWP && eleMissingLostHits==0 && passConversionVeto && _recoele_isChargeConsistent[i_ele])
	   iscutsel=true;
      
      _recoele_iscutsel.push_back(iscutsel);
      _recolep_iscutsel.push_back(iscutsel);

      if(iscutsel){
	      _n_recoele_cutsel++;
        _n_recolep_cutsel++;
      }
      	
      //MVA-based selection
      bool ismvasel=false;
      if(conept>10 && eleIDcut && eleMissingLostHits==0 && _recoele_leptonMVA[i_ele]>0.9 && _recoele_jetDeepCSV[i_ele]<0.4941 && passConversionVeto) 
	   ismvasel=true;
     
      _recoele_ismvasel.push_back(ismvasel);

      if(ismvasel){
	      _n_recoele_mvasel++;
        _n_recolep_mvasel++;
      }

      //Fake rate
      int bin_FR = h_fakerate_el->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      float FR = h_fakerate_el->GetBinContent(bin_FR);
      _recoele_fakerate.push_back(FR);

      bin_FR = h_fakerate_el_data_up->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_data_up->GetBinContent(bin_FR);
      _recoele_fakerate_up.push_back(FR);

      bin_FR = h_fakerate_el_data_down->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_data_down->GetBinContent(bin_FR);
      _recoele_fakerate_down.push_back(FR);

      bin_FR = h_fakerate_el_data_pt1->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_data_pt1->GetBinContent(bin_FR);
      _recoele_fakerate_pt1.push_back(FR);

      bin_FR = h_fakerate_el_data_pt2->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_data_pt2->GetBinContent(bin_FR);
      _recoele_fakerate_pt2.push_back(FR);

      bin_FR = h_fakerate_el_data_be1->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_data_be1->GetBinContent(bin_FR);
      _recoele_fakerate_be1.push_back(FR);

      bin_FR = h_fakerate_el_data_be2->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_data_be2->GetBinContent(bin_FR);
      _recoele_fakerate_be2.push_back(FR);

      bin_FR = h_fakerate_el_QCD->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_QCD->GetBinContent(bin_FR);
      _recoele_fakerate_QCD_MC.push_back(FR);

      bin_FR = h_fakerate_el_TT->FindBin(min(conept,float(99.)), abs(elec.Eta()));
      FR = h_fakerate_el_TT->GetBinContent(bin_FR);
      _recoele_fakerate_ttbar_MC.push_back(FR);

      int bin_QF = h_QFrate_el->FindBin(min(elec.Pt(),999.), abs(elec.Eta()));
      float QF = h_QFrate_el->GetBinContent(bin_QF);
      _recoele_QFrate.push_back(QF);     
      
    }
    

    vector< pair<pair<int,int>, TLorentzVector> > reco_leptons;
    
    for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){

      //if(_recomu_isfakeable[i_mu]==0) continue; 

      pair<int,int> p_ind_pdg = make_pair(13,i_mu);
      TLorentzVector mu = reco_mus[i_mu].second;
      mu.SetPtEtaPhiM(_recomu_conept[i_mu],mu.Eta(),mu.Phi(),mu.M());
      pair<pair<int,int>, TLorentzVector> pair=make_pair(p_ind_pdg, mu);
      reco_leptons.push_back(pair);

    }


    for(unsigned int i_ele=0; i_ele<reco_eles.size(); i_ele++){

      //if(_recoele_isfakeable[i_ele]==0) continue;

      pair<int,int> p_ind_pdg = make_pair(11,i_ele);
      TLorentzVector ele = reco_eles[i_ele].second;
      ele.SetPtEtaPhiM(_recoele_conept[i_ele],ele.Eta(),ele.Phi(),ele.M());
      pair<pair<int,int>, TLorentzVector> pair=make_pair(p_ind_pdg, ele);
      reco_leptons.push_back(pair);

    }


    sort(reco_leptons.begin(), reco_leptons.end(), pT_comparison_pairs_pdg);

    for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){

      int pdg = reco_leptons[i_lep].first.first;

      if(pdg==13){

	      int i_mu = reco_leptons[i_lep].first.second;     
	      _recolep_charge.push_back(_recomu_charge[i_mu]);
	      _recolep_pdg.push_back(-13*_recomu_charge[i_mu]);
	      TLorentzVector mu = reco_mus[i_mu].second;
	      _recolep_e.push_back(_recomu_e[i_mu]);
	      _recolep_px.push_back(_recomu_px[i_mu]);
	      _recolep_py.push_back(_recomu_py[i_mu]);
	      _recolep_pz.push_back(_recomu_pz[i_mu]);
	      _recolep_pt.push_back(_recomu_pt[i_mu]);
	      _recolep_conept.push_back(_recomu_conept[i_mu]);
	      _recolep_eta.push_back(_recomu_eta[i_mu]);
	      _recolep_phi.push_back(_recomu_phi[i_mu]);
	      _recolep_leptonMVA.push_back(_recomu_leptonMVA[i_mu]);
        _recolep_isfakeable.push_back(_recomu_isfakeable[i_mu]);
        _recolep_ismvasel.push_back(_recomu_ismvasel[i_mu]);
	      _recolep_fakerate.push_back(_recomu_fakerate[i_mu]);
        _recolep_fakerate_up.push_back(_recomu_fakerate_up[i_mu]);
        _recolep_fakerate_down.push_back(_recomu_fakerate_down[i_mu]);
        _recolep_fakerate_pt1.push_back(_recomu_fakerate_pt1[i_mu]);
        _recolep_fakerate_pt2.push_back(_recomu_fakerate_pt2[i_mu]);
        _recolep_fakerate_be1.push_back(_recomu_fakerate_be1[i_mu]);
        _recolep_fakerate_be2.push_back(_recomu_fakerate_be2[i_mu]);
	      _recolep_fakerate_QCD_MC.push_back(_recomu_fakerate_QCD_MC[i_mu]);	
	      _recolep_fakerate_ttbar_MC.push_back(_recomu_fakerate_ttbar_MC[i_mu]);
	      _recolep_QFrate.push_back(0);
	
	      float rel_error_trackpt = _recomu_rel_error_trackpt[i_mu];
	      bool tightcharge = rel_error_trackpt<0.2;

	      _recolep_tightcharge.push_back(tightcharge);
	      _recolep_eleconv_misshits.push_back(true);	
	
      }

      else if(pdg==11){

	      int i_ele = reco_leptons[i_lep].first.second;

	      _recolep_charge.push_back(_recoele_charge[i_ele]);
	      _recolep_pdg.push_back(-11*_recoele_charge[i_ele]);

	      TLorentzVector ele = reco_eles[i_ele].second;

	      _recolep_e.push_back(_recoele_corr_e[i_ele]);
	      _recolep_px.push_back(_recoele_px[i_ele]);
	      _recolep_py.push_back(_recoele_py[i_ele]);
	      _recolep_pz.push_back(_recoele_pz[i_ele]);
	      _recolep_pt.push_back(_recoele_corr_pt[i_ele]);
	      _recolep_conept.push_back(_recoele_conept[i_ele]);
	      _recolep_eta.push_back(_recoele_eta[i_ele]);
	      _recolep_phi.push_back(_recoele_phi[i_ele]);
	      _recolep_leptonMVA.push_back(_recoele_leptonMVA[i_ele]);
        _recolep_isfakeable.push_back(_recoele_isfakeable[i_ele]);
        _recolep_ismvasel.push_back(_recoele_ismvasel[i_ele]);
	      _recolep_fakerate.push_back(_recoele_fakerate[i_ele]);	
        _recolep_fakerate_up.push_back(_recoele_fakerate_up[i_ele]);
        _recolep_fakerate_down.push_back(_recoele_fakerate_down[i_ele]);
        _recolep_fakerate_pt1.push_back(_recoele_fakerate_pt1[i_ele]);
        _recolep_fakerate_pt2.push_back(_recoele_fakerate_pt2[i_ele]);
        _recolep_fakerate_be1.push_back(_recoele_fakerate_be1[i_ele]);
        _recolep_fakerate_be2.push_back(_recoele_fakerate_be2[i_ele]);
	      _recolep_fakerate_QCD_MC.push_back(_recoele_fakerate_QCD_MC[i_ele]);	
	      _recolep_fakerate_ttbar_MC.push_back(_recoele_fakerate_ttbar_MC[i_ele]);	
	      _recolep_QFrate.push_back(_recoele_QFrate[i_ele]);

	      bool tightcharge = _recoele_isChargeConsistent[i_ele];
	      bool eleconv_misshits = _recoele_passConversionVeto[i_ele]&&(_recoele_nMissingHits[i_ele]==0);

	      _recolep_tightcharge.push_back(tightcharge);
	      _recolep_eleconv_misshits.push_back(eleconv_misshits);	
      
      }

    }
 
    

    //////////////////////////////////////////////
    ///                Taus                    ///
    //////////////////////////////////////////////
   
    vector< pair<int,TLorentzVector> > reco_taus;
    
    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){

      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );

      if(TES>0 && (*_daughters_TauUpExists)[i_daughter])
	      daughter.SetPxPyPzE( (*_daughters_px_TauUp)[i_daughter] , (*_daughters_py_TauUp)[i_daughter] , (*_daughters_pz_TauUp)[i_daughter] , (*_daughters_e_TauUp)[i_daughter] );
      else if(TES<0 && (*_daughters_TauDownExists)[i_daughter])
	      daughter.SetPxPyPzE( (*_daughters_px_TauDown)[i_daughter] , (*_daughters_py_TauDown)[i_daughter] , (*_daughters_pz_TauDown)[i_daughter] , (*_daughters_e_TauDown)[i_daughter] );
      
      pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
     
      float iso=(*_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits)[i_daughter];   
      int byLooseCombinedIsolationDeltaBetaCorr3Hits = ((*_tauID)[i_daughter]>>map_tauID["byLooseCombinedIsolationDeltaBetaCorr3Hits"])&1;
      int byLooseCombinedIsolationDeltaBetaCorr3HitsdR03 = ((*_tauID)[i_daughter]>>map_tauID["byLooseCombinedIsolationDeltaBetaCorr3HitsdR03"])&1;

      int byLooseIsolationMVArun2v1DBdR03oldDMwLT = ((*_tauID)[i_daughter]>>map_tauID["byLooseIsolationMVArun2v1DBdR03oldDMwLT"])&1;
      int byMediumIsolationMVArun2v1DBdR03oldDMwLT = ((*_tauID)[i_daughter]>>map_tauID["byMediumIsolationMVArun2v1DBdR03oldDMwLT"])&1;

      int byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT = ((*_tauID)[i_daughter]>>map_tauID["byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1; 
      int byLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT = ((*_tauID)[i_daughter]>>map_tauID["byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1;
      int byMediumIsolationMVArun2v2017v2DBoldDMdR0p3wLT = ((*_tauID)[i_daughter]>>map_tauID["byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1;
      int byTightIsolationMVArun2v2017v2DBoldDMdR0p3wLT = ((*_tauID)[i_daughter]>>map_tauID["byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1;
      int byVTightIsolationMVArun2v2017v2DBoldDMdR0p3wLT = ((*_tauID)[i_daughter]>>map_tauID["byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1;

      int decayModeFinding=(*_daughters_decayModeFindingOldDMs)[i_daughter];

      float dxy = (*_dxy)[i_daughter];
      float dz = (*_dz)[i_daughter];
      
      bool iso_cut = iso<(0.1*iso_tau);

      if(iso_type=="byLooseCombinedIsolationDeltaBetaCorr3Hits")
	      iso_cut = byLooseCombinedIsolationDeltaBetaCorr3Hits;
      else if(iso_type=="byLooseCombinedIsolationDeltaBetaCorr3HitsdR03")
	      iso_cut = byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
      else if(iso_type=="byLooseIsolationMVArun2v1DBdR03oldDMwLT")
	      iso_cut = byLooseIsolationMVArun2v1DBdR03oldDMwLT;
      else if(iso_type=="byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT")
        iso_cut = byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT;
      else if(iso_type=="byLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT")
        iso_cut = byLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT;
 
      bool nomin_cut = fabs(PDGId)==15 && daughter.Pt()>20 && fabs(daughter.Eta())<2.3 && iso_cut && decayModeFinding>0.5 && abs(dxy)<=1000 && abs(dz)<=0.2;     
      
      if( nomin_cut ){	
	      bool dR_veto=false;

	    for(unsigned int i_lep=0; i_lep<reco_mus.size(); i_lep++){	  
	      TLorentzVector lep=reco_mus[i_lep].second;
	      if(tau_cleaning=="fakeable" && !_recomu_isfakeable[i_lep]) continue;		      
        float dR_lep_tau=lep.DeltaR(daughter);
	      if(dR_lep_tau<0.3){ //Change wrt v3
	        dR_veto=true;
	        break;
	      }
	    }

	    for(unsigned int i_lep=0; i_lep<reco_eles.size(); i_lep++){	  
	      TLorentzVector lep=reco_eles[i_lep].second;
	      if(tau_cleaning=="fakeable" && !_recoele_isfakeable[i_lep]) continue;
	      float dR_lep_tau=lep.DeltaR(daughter);
	      if(dR_lep_tau<0.3){ //Change wrt v3
	        dR_veto=true;
	        break;
	      }
	    }

	    if(dR_veto)
	      continue;

	    reco_taus.push_back(daughter_pair);
	
      }

    }


    sort(reco_taus.begin(), reco_taus.end(), pT_comparison_pairs);

    _n_recotauh = reco_taus.size();

    for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){
      
      int i_daughter=reco_taus[i_tauh].first;
      TLorentzVector tauh=reco_taus[i_tauh].second;

      _recotauh_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recotauh_decayMode.push_back( (*_decayMode)[i_daughter] );
      _recotauh_e.push_back( tauh.E() );
      _recotauh_px.push_back( tauh.Px() );
      _recotauh_py.push_back( tauh.Py() );
      _recotauh_pz.push_back( tauh.Pz() );
      _recotauh_pt.push_back( tauh.Pt() );
      _recotauh_eta.push_back( tauh.Eta() );
      _recotauh_phi.push_back( tauh.Phi() );
      _recotauh_dxy.push_back( (*_dxy)[i_daughter] );
      _recotauh_dz.push_back( (*_dz)[i_daughter] );
      _recotauh_iso.push_back( (*_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits)[i_daughter] );

      _recotauh_matchedJetIndex.push_back( (*_daughters_matchedJetIndex)[i_daughter] );

      _recotauh_decayModeFindingOldDMs.push_back( (*_daughters_decayModeFindingOldDMs)[i_daughter] );
      _recotauh_decayModeFindingNewDMs.push_back( (*_daughters_decayModeFindingNewDMs)[i_daughter] );
      _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits.push_back( ((*_tauID)[i_daughter]>>map_tauID["byLooseCombinedIsolationDeltaBetaCorr3Hits"])&1 );
      _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits.push_back( ((*_tauID)[i_daughter]>>map_tauID["byMediumCombinedIsolationDeltaBetaCorr3Hits"])&1 );
      _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits.push_back( ((*_tauID)[i_daughter]>>map_tauID["byTightCombinedIsolationDeltaBetaCorr3Hits"])&1 );
      _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03.push_back( ((*_tauID)[i_daughter]>>map_tauID["byLooseCombinedIsolationDeltaBetaCorr3HitsdR03"])&1 );
      _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03.push_back( ((*_tauID)[i_daughter]>>map_tauID["byMediumCombinedIsolationDeltaBetaCorr3HitsdR03"])&1 );
      _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03.push_back( ((*_tauID)[i_daughter]>>map_tauID["byTightCombinedIsolationDeltaBetaCorr3HitsdR03"])&1 );

      _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byLooseIsolationMVArun2v1DBdR03oldDMwLT"])&1 );
      _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byMediumIsolationMVArun2v1DBdR03oldDMwLT"])&1 );
      _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byTightIsolationMVArun2v1DBdR03oldDMwLT"])&1 );
      _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byVTightIsolationMVArun2v1DBdR03oldDMwLT"])&1 );

      _recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1 );
      _recotauh_byLooseIsolationMVArun2v2017v2DBoldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1 );
      _recotauh_byMediumIsolationMVArun2v2017v2DBoldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1 );
      _recotauh_byTightIsolationMVArun2v2017v2DBoldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1 );
      _recotauh_byVTightIsolationMVArun2v2017v2DBoldDMwLT.push_back( ((*_tauID)[i_daughter]>>map_tauID["byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"])&1 );
      _recotauh_byIsolationMVArun2v2017v2DBoldDMdR0p3wLTraw.push_back ( (*_daughters_byIsolationMVArun2017v2DBoldDMwLTraw2017)[i_daughter] );

      _recotauh_againstMuonLoose3.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstMuonLoose3"])&1 );
      _recotauh_againstMuonTight3.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstMuonTight3"])&1 );
      _recotauh_againstElectronVLooseMVA6.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstElectronVLooseMVA6"])&1 );
      _recotauh_againstElectronLooseMVA6.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstElectronLooseMVA6"])&1 );
      _recotauh_againstElectronMediumMVA6.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstElectronMediumMVA6"])&1 );
      _recotauh_againstElectronTightMVA6.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstElectronTightMVA6"])&1 );
      _recotauh_againstElectronVTightMVA6.push_back( ((*_tauID)[i_daughter]>>map_tauID["againstElectronVTightMVA6"])&1 );

      float fakerate_loose = 0;
      float fakerate_medium = 0;
      float fakerate_tight = 0;
      float fakerate_Vtight = 0;
      float fakerate_loose_par1Up = 0;
      float fakerate_loose_par1Down = 0;
      float fakerate_loose_par2Up = 0;
      float fakerate_loose_par2Down = 0;
      float fakerate_medium_par1Up = 0;
      float fakerate_medium_par1Down = 0;
      float fakerate_medium_par2Up = 0;
      float fakerate_medium_par2Down = 0;

      if(fabs(tauh.Eta())<1.479){

        fakerate_loose = fakerate_from_TGraph(gr_fakerate_tau_loose_barrel,tauh.Pt());
        fakerate_loose *= f_dataMC_fakerate_tau_loose_barrel->Eval(tauh.Pt());

	      fakerate_medium = fakerate_from_TGraph(gr_fakerate_tau_medium_barrel,tauh.Pt());
	      fakerate_medium *= f_dataMC_fakerate_tau_medium_barrel->Eval(tauh.Pt());

	      fakerate_tight = fakerate_from_TGraph(gr_fakerate_tau_tight_barrel,tauh.Pt());
	      fakerate_tight *= f_dataMC_fakerate_tau_tight_barrel->Eval(tauh.Pt());

	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_barrel,tauh.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_barrel->Eval(tauh.Pt());

        fakerate_loose_par1Up = fakerate_from_TGraph(gr_fakerate_tau_loose_barrel,tauh.Pt());
        fakerate_loose_par1Up *= f_dataMC_fakerate_tau_loose_barrel_par1Up->Eval(tauh.Pt());

        fakerate_loose_par1Down = fakerate_from_TGraph(gr_fakerate_tau_loose_barrel,tauh.Pt());
        fakerate_loose_par1Down *= f_dataMC_fakerate_tau_loose_barrel_par1Down->Eval(tauh.Pt());

        fakerate_loose_par2Up = fakerate_from_TGraph(gr_fakerate_tau_loose_barrel,tauh.Pt());
        fakerate_loose_par2Up *= f_dataMC_fakerate_tau_loose_barrel_par2Up->Eval(tauh.Pt());

        fakerate_loose_par2Down = fakerate_from_TGraph(gr_fakerate_tau_loose_barrel,tauh.Pt());
        fakerate_loose_par2Down *= f_dataMC_fakerate_tau_loose_barrel_par2Down->Eval(tauh.Pt());

        fakerate_medium_par1Up = fakerate_from_TGraph(gr_fakerate_tau_medium_barrel,tauh.Pt());
        fakerate_medium_par1Up *= f_dataMC_fakerate_tau_medium_barrel_par1Up->Eval(tauh.Pt());

        fakerate_medium_par1Down = fakerate_from_TGraph(gr_fakerate_tau_medium_barrel,tauh.Pt());
        fakerate_medium_par1Down *= f_dataMC_fakerate_tau_medium_barrel_par1Down->Eval(tauh.Pt());

        fakerate_medium_par2Up = fakerate_from_TGraph(gr_fakerate_tau_medium_barrel,tauh.Pt());
        fakerate_medium_par2Up *= f_dataMC_fakerate_tau_medium_barrel_par2Up->Eval(tauh.Pt());

        fakerate_medium_par2Down = fakerate_from_TGraph(gr_fakerate_tau_medium_barrel,tauh.Pt());
        fakerate_medium_par2Down *= f_dataMC_fakerate_tau_medium_barrel_par2Down->Eval(tauh.Pt());

      }

      else{

        fakerate_loose = fakerate_from_TGraph(gr_fakerate_tau_loose_endcaps,tauh.Pt());
        fakerate_loose *= f_dataMC_fakerate_tau_loose_endcaps->Eval(tauh.Pt());

	      fakerate_medium = fakerate_from_TGraph(gr_fakerate_tau_medium_endcaps,tauh.Pt());
	      fakerate_medium *= f_dataMC_fakerate_tau_medium_endcaps->Eval(tauh.Pt());	

	      fakerate_tight = fakerate_from_TGraph(gr_fakerate_tau_tight_endcaps,tauh.Pt());
	      fakerate_tight *= f_dataMC_fakerate_tau_tight_endcaps->Eval(tauh.Pt());

	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_endcaps,tauh.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_endcaps->Eval(tauh.Pt());

        fakerate_loose_par1Up = fakerate_from_TGraph(gr_fakerate_tau_loose_endcaps,tauh.Pt());
        fakerate_loose_par1Up *= f_dataMC_fakerate_tau_loose_endcaps_par1Up->Eval(tauh.Pt());

        fakerate_loose_par1Down = fakerate_from_TGraph(gr_fakerate_tau_loose_endcaps,tauh.Pt());
        fakerate_loose_par1Down *= f_dataMC_fakerate_tau_loose_endcaps_par1Down->Eval(tauh.Pt());

        fakerate_loose_par2Up = fakerate_from_TGraph(gr_fakerate_tau_loose_endcaps,tauh.Pt());
        fakerate_loose_par2Up *= f_dataMC_fakerate_tau_loose_endcaps_par2Up->Eval(tauh.Pt());

        fakerate_loose_par2Down = fakerate_from_TGraph(gr_fakerate_tau_loose_endcaps,tauh.Pt());
        fakerate_loose_par2Down *= f_dataMC_fakerate_tau_loose_endcaps_par2Down->Eval(tauh.Pt());

        fakerate_medium_par1Up = fakerate_from_TGraph(gr_fakerate_tau_medium_endcaps,tauh.Pt());
        fakerate_medium_par1Up *= f_dataMC_fakerate_tau_medium_endcaps_par1Up->Eval(tauh.Pt());

        fakerate_medium_par1Down = fakerate_from_TGraph(gr_fakerate_tau_medium_endcaps,tauh.Pt());
        fakerate_medium_par1Down *= f_dataMC_fakerate_tau_medium_endcaps_par1Down->Eval(tauh.Pt());

        fakerate_medium_par2Up = fakerate_from_TGraph(gr_fakerate_tau_medium_endcaps,tauh.Pt());
        fakerate_medium_par2Up *= f_dataMC_fakerate_tau_medium_endcaps_par2Up->Eval(tauh.Pt());

        fakerate_medium_par2Down = fakerate_from_TGraph(gr_fakerate_tau_medium_endcaps,tauh.Pt());
        fakerate_medium_par2Down *= f_dataMC_fakerate_tau_medium_endcaps_par2Down->Eval(tauh.Pt());

      }

      _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT.push_back(fakerate_loose);
      _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT.push_back(fakerate_medium);
      _recotauh_fakerate_byTightIsolationMVArun2v2017v2DBdR03oldDMwLT.push_back(fakerate_tight);
      _recotauh_fakerate_byVTightIsolationMVArun2v2017v2DBdR03oldDMwLT.push_back(fakerate_Vtight);

      _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Up.push_back(fakerate_loose_par1Up);
      _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Down.push_back(fakerate_loose_par1Down);
      _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Up.push_back(fakerate_loose_par2Up);
      _recotauh_fakerate_byLooseIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Down.push_back(fakerate_loose_par2Down);

      _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Up.push_back(fakerate_medium_par1Up);
      _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par1Down.push_back(fakerate_medium_par1Down);
      _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Up.push_back(fakerate_medium_par2Up);
      _recotauh_fakerate_byMediumIsolationMVArun2v2017v2DBdR03oldDMwLT_par2Down.push_back(fakerate_medium_par2Down);


      if(isMC){

	      pair<int,float> pair = find_i_dRmin_closest( tauh, (*_genpart_px), (*_genpart_py), (*_genpart_pz), (*_genpart_e) );	
	      _recotauh_i_closest_genpart.push_back(pair.first);
	      _recotauh_dR_closest_genpart.push_back(pair.second);

      }

      else{

	      _recotauh_i_closest_genpart.push_back(-1);
	      _recotauh_dR_closest_genpart.push_back(-1);

      }

    }   
    


    //////////////////////////////////////////////
    ///                Jets                    ///
    //////////////////////////////////////////////
    
    vector< pair<int,TLorentzVector> > reco_jets;
    vector< pair<int,TLorentzVector> > reco_jets_fwd;

    vector< pair<int,float> > i_jet_CSV_pairs;
    vector< pair<int,float> > i_jet_DeepCSV_pairs;
    vector< pair<int,float> > i_jet_DeepJet_pairs;

    for(unsigned int i_jet=0; i_jet<(*_jets_e).size(); i_jet++){

      TLorentzVector jet ( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );
      
      _jets_pt.push_back(jet.Pt());
      _jets_eta.push_back(jet.Eta());
      _jets_phi.push_back(jet.Phi());      

      //JEC
      jet.SetPtEtaPhiE( jet.Pt() * (1+JEC*(*_jets_jecUnc)[i_jet]), jet.Eta(), jet.Phi(), jet.E() * (1+JEC*(*_jets_jecUnc)[i_jet]) );

      pair<int,TLorentzVector> jet_pair = make_pair(i_jet,jet);

      float CSVscore = (*_bCSVscore)[i_jet];
      float DeepCSVscore = ( (*_bDeepCSV_probb)[i_jet] + (*_bDeepCSV_probbb)[i_jet] );
      float DeepJetscore = ( (*_bDeepFlavor_probb)[i_jet] + (*_bDeepFlavor_probbb)[i_jet] + (*_bDeepFlavor_problepb)[i_jet]);

      pair<int,float> CSV_pair = make_pair(i_jet,CSVscore);
      pair<int,float> DeepCSV_pair = make_pair(i_jet,DeepCSVscore);
      pair<int,float> DeepJet_pair = make_pair(i_jet,DeepJetscore);
      
      float PFJetID = (*_PFjetID)[i_jet];
      bool passPFjetID = false;
      if(year == 2016) 
        passPFjetID = (PFJetID >= 1);
      if(year == 2017 || year == 2018) 
        passPFjetID = (PFJetID >= 2);

      float jets_QGdiscr = (*_jets_QGdiscr)[i_jet];

      if(jet.Pt()>25 && fabs(jet.Eta())<2.4 && passPFjetID){  

	      bool dR_veto=false;

	      /*for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){
	  
	        TLorentzVector lep=reco_leptons[i_lep].second;
	        float dR_lep_jet=lep.DeltaR(jet);
	        if(dR_lep_jet<0.4){
	          dR_veto=true;
	          break;
	        }
	      }


	      for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){

	        TLorentzVector tauh=reco_taus[i_tauh].second;
	        float dR_tauh_jet=tauh.DeltaR(jet);
	        if(dR_tauh_jet<0.4){
	          dR_veto=true;
	          break;
	        }
	
	      }*/

              int jet_index = i_jet;

              for(unsigned int i_ele=0; i_ele<_recoele_matchedJetIndex.size(); i_ele++){
                if(_recoele_matchedJetIndex[i_ele]==jet_index && _recoele_isfakeable[i_ele]){
	           dR_veto=true;
                   break;
                }
              }

              for(unsigned int i_mu=0; i_mu<_recomu_matchedJetIndex.size(); i_mu++){
                if(_recomu_matchedJetIndex[i_mu]==jet_index && _recomu_isfakeable[i_mu]){
                   dR_veto=true;
                   break;
                }
              }

              for(unsigned int i_tau=0; i_tau<_recotauh_matchedJetIndex.size(); i_tau++){
                if(_recotauh_matchedJetIndex.at(i_tau)==jet_index){ 
                   dR_veto=true;
                   break;
                }
              }

	      if(dR_veto)
	        continue;

	      reco_jets.push_back(jet_pair);
	      i_jet_CSV_pairs.push_back(CSV_pair);
        i_jet_DeepCSV_pairs.push_back(DeepCSV_pair);
        i_jet_DeepJet_pairs.push_back(DeepJet_pair);

        // DeepJet

        if (year == 2016){

          if(DeepJetscore>0.0614)
          _n_recoPFJet_btag_loose++;
          if(DeepJetscore>0.3093)
          _n_recoPFJet_btag_medium++;

        }

        else if (year == 2017){

          if(DeepJetscore>0.0521)
          _n_recoPFJet_btag_loose++;
          if(DeepJetscore>0.3033)
          _n_recoPFJet_btag_medium++;

        }

        else if (year == 2018){

          if(DeepJetscore>0.0494)
          _n_recoPFJet_btag_loose++;
          if(DeepJetscore>0.2770)
          _n_recoPFJet_btag_medium++;

        }
      

      }

      //forward jets

      if(jet.Pt()>25 && fabs(jet.Eta())>2.4 && fabs(jet.Eta())<5 && passPFjetID){  

        bool pass_noise = true;
        if(fabs(jet.Eta())>2.7 && fabs(jet.Eta())<3) 
          pass_noise = jet.Pt()>60;
 
        if(!pass_noise) continue;

        bool dR_veto=false;

        /*for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){
    
          TLorentzVector lep=reco_leptons[i_lep].second;
          float dR_lep_jet=lep.DeltaR(jet);
          if(dR_lep_jet<0.4){
            dR_veto=true;
            break;
          }
        }


        for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){

          TLorentzVector tauh=reco_taus[i_tauh].second;
          float dR_tauh_jet=tauh.DeltaR(jet);
          if(dR_tauh_jet<0.4){
            dR_veto=true;
            break;
          }
  
        }*/


        int jet_index = i_jet;

        for(unsigned int i_ele=0; i_ele<_recoele_matchedJetIndex.size(); i_ele++){
           if(_recoele_matchedJetIndex[i_ele]==jet_index && _recoele_isfakeable[i_ele]){ 
              dR_veto=true;
              break;
           }
        }

        for(unsigned int i_mu=0; i_mu<_recomu_matchedJetIndex.size(); i_mu++){
           if(_recomu_matchedJetIndex[i_mu]==jet_index && _recomu_isfakeable[i_mu]){ 
               dR_veto=true;
               break;
            }
        }

        for(unsigned int i_tau=0; i_tau<_recotauh_matchedJetIndex.size(); i_tau++){
            if(_recotauh_matchedJetIndex.at(i_tau)==jet_index){
               dR_veto=true;
               break;
            }
        }


        if(dR_veto)
          continue;

        reco_jets_fwd.push_back(jet_pair);      

      }

    }


    sort(reco_jets.begin(), reco_jets.end(), pT_comparison_pairs);
    sort(reco_jets_fwd.begin(), reco_jets_fwd.end(), pT_comparison_pairs);

    sort(i_jet_CSV_pairs.begin(), i_jet_CSV_pairs.end(), CSV_comparison_pairs);
    sort(i_jet_DeepCSV_pairs.begin(), i_jet_DeepCSV_pairs.end(), CSV_comparison_pairs);
    sort(i_jet_DeepJet_pairs.begin(), i_jet_DeepJet_pairs.end(), CSV_comparison_pairs);

    _n_recoPFJet = reco_jets.size();
    _n_recoPFFwdJet = reco_jets_fwd.size();
    

    vector<TLorentzVector> recoPFJets;

    for(unsigned int i_PFJet=0; i_PFJet<reco_jets.size(); i_PFJet++){

      int i_jet = reco_jets[i_PFJet].first;
      TLorentzVector jet =  reco_jets[i_PFJet].second;
      
      recoPFJets.push_back(jet);

      _recoPFJet_e.push_back( jet.E() );
      _recoPFJet_pt.push_back( jet.Pt() );
      _recoPFJet_px.push_back( jet.Px() );
      _recoPFJet_py.push_back( jet.Py() );
      _recoPFJet_pz.push_back( jet.Pz() );
      _recoPFJet_eta.push_back( jet.Eta() );
      _recoPFJet_phi.push_back( jet.Phi() );
      _recoPFJet_CSVscore.push_back(  (*_bCSVscore)[i_jet] );
      _recoPFJet_DeepCSVscore.push_back(  (*_bDeepCSV_probb)[i_jet] + (*_bDeepCSV_probbb)[i_jet] );
      _recoPFJet_DeepJetscore.push_back(  (*_bDeepFlavor_probb)[i_jet] + (*_bDeepFlavor_probbb)[i_jet] + (*_bDeepFlavor_problepb)[i_jet]);
      _recoPFJet_jecUnc.push_back(  (*_jets_jecUnc)[i_jet] );
      _recoPFJet_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
      _recoPFJet_hadronFlavour.push_back(  (*_jets_HadronFlavour)[i_jet] );
      _recoPFJet_QGdiscr.push_back ( (*_jets_QGdiscr)[i_jet] );
  
      int imin = -1;
      float dRmin = 100000;
      int imin_2nd = -1;
      float dRmin_2nd = 100000;
      
      if(isMC){
	
	      for(unsigned int i_gen=0; i_gen<(*_genpart_e).size(); i_gen++){
	  
	        TLorentzVector genpart_tlv( (*_genpart_px)[i_gen], (*_genpart_py)[i_gen], (*_genpart_pz)[i_gen], (*_genpart_e)[i_gen]);	
	        float dR = jet.DeltaR(genpart_tlv);
	  
	        if(dR<dRmin_2nd){

	          if(dR<dRmin){
	            imin_2nd=imin;
	            dRmin_2nd=dRmin;
	            dRmin=dR;
	            imin=i_gen;
	          } 

	          else{
	            imin_2nd=i_gen;
	            dRmin_2nd=dR;
	          }
	        }
	  
	      }
	
      }

      _recoPFJet_i_closest_genpart.push_back(imin);
      _recoPFJet_dR_closest_genpart.push_back(dRmin);
      _recoPFJet_i_2nd_closest_genpart.push_back(imin_2nd);
      _recoPFJet_dR_2nd_closest_genpart.push_back(dRmin_2nd);     


      pair<int,float> pair_tauh = find_i_dRmin_closest( jet, _recotauh_px, _recotauh_py, _recotauh_pz, _recotauh_e );

      _recoPFJet_i_closest_tau.push_back(pair_tauh.first);
      _recoPFJet_dR_closest_tau.push_back(pair_tauh.second);  

    }

    vector<TLorentzVector> recoPFFwdJets;

    for(unsigned int i_PFFwdJet=0; i_PFFwdJet<reco_jets_fwd.size(); i_PFFwdJet++){

      int i_jet = reco_jets_fwd[i_PFFwdJet].first;
      TLorentzVector jet_fwd =  reco_jets_fwd[i_PFFwdJet].second;
      
      recoPFFwdJets.push_back(jet_fwd);

      _recoPFFwdJet_e.push_back( jet_fwd.E() );
      _recoPFFwdJet_pt.push_back( jet_fwd.Pt() );
      _recoPFFwdJet_px.push_back( jet_fwd.Px() );
      _recoPFFwdJet_py.push_back( jet_fwd.Py() );
      _recoPFFwdJet_pz.push_back( jet_fwd.Pz() );
      _recoPFFwdJet_eta.push_back( jet_fwd.Eta() );
      _recoPFFwdJet_phi.push_back( jet_fwd.Phi() );
      _recoPFFwdJet_CSVscore.push_back(  (*_bCSVscore)[i_jet] );
      _recoPFFwdJet_DeepCSVscore.push_back(  (*_bDeepCSV_probb)[i_jet] + (*_bDeepCSV_probbb)[i_jet] );
      _recoPFFwdJet_DeepJetscore.push_back(  (*_bDeepFlavor_probb)[i_jet] + (*_bDeepFlavor_probbb)[i_jet] + (*_bDeepFlavor_problepb)[i_jet]);
      _recoPFFwdJet_jecUnc.push_back(  (*_jets_jecUnc)[i_jet] );
      _recoPFFwdJet_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
      _recoPFFwdJet_hadronFlavour.push_back(  (*_jets_HadronFlavour)[i_jet] );
      _recoPFFwdJet_QGdiscr.push_back ( (*_jets_QGdiscr)[i_jet] );

    }

    //with DeepCSV
    
    _bTagSF_CSVshape_weight = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::central);
    _bTagSF_CSVshape_weight_JESUp = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::JESUp);
    _bTagSF_CSVshape_weight_JESDown = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::JESDown);
    _bTagSF_CSVshape_weight_LFUp = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::LFUp);
    _bTagSF_CSVshape_weight_LFDown = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::LFDown);
    _bTagSF_CSVshape_weight_HFUp = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::HFUp);
    _bTagSF_CSVshape_weight_HFDown = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::HFDown);
    _bTagSF_CSVshape_weight_HFStats1Up = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::HFStats1Up);
    _bTagSF_CSVshape_weight_HFStats1Down = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::HFStats1Down);
    _bTagSF_CSVshape_weight_HFStats2Up = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::HFStats2Up);
    _bTagSF_CSVshape_weight_HFStats2Down = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::HFStats2Down);
    _bTagSF_CSVshape_weight_LFStats1Up = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::LFStats1Up);
    _bTagSF_CSVshape_weight_LFStats1Down = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::LFStats1Down);
    _bTagSF_CSVshape_weight_LFStats2Up = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::LFStats2Up);
    _bTagSF_CSVshape_weight_LFStats2Down = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::LFStats2Down);
    _bTagSF_CSVshape_weight_CFErr1Up = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::CFErr1Up);
    _bTagSF_CSVshape_weight_CFErr1Down = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::CFErr1Down);
    _bTagSF_CSVshape_weight_CFErr2Up = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::CFErr2Up);
    _bTagSF_CSVshape_weight_CFErr2Down = bTagSF_CSVshape_DeepJet->getEvtWeight(_recoPFJet_DeepJetscore, recoPFJets, _recoPFJet_hadronFlavour, bTagSF_CSVshape::CFErr2Down);


    //using DeepJet sorting for now
    for(unsigned int i_PFJet=0; i_PFJet<i_jet_DeepJet_pairs.size(); i_PFJet++){

      int i_jet = i_jet_DeepJet_pairs[i_PFJet].first;
      float DeepCSVscore= i_jet_DeepCSV_pairs[i_PFJet].second;
      float DeepJetscore= i_jet_DeepJet_pairs[i_PFJet].second;
      
      TLorentzVector jet  ( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );
      
      _recoPFJet_DeepJetsort_e.push_back( jet.E() );
      _recoPFJet_DeepJetsort_pt.push_back( jet.Pt() );
      _recoPFJet_DeepJetsort_px.push_back( jet.Px() );
      _recoPFJet_DeepJetsort_py.push_back( jet.Py() );
      _recoPFJet_DeepJetsort_pz.push_back( jet.Pz() );
      _recoPFJet_DeepJetsort_eta.push_back( jet.Eta() );
      _recoPFJet_DeepJetsort_phi.push_back( jet.Phi() );
      _recoPFJet_DeepJetsort_CSVscore.push_back( (*_bCSVscore)[i_jet] );
      _recoPFJet_DeepJetsort_DeepCSVscore.push_back( DeepCSVscore );
      _recoPFJet_DeepJetsort_DeepJetscore.push_back( DeepJetscore );
      _recoPFJet_DeepJetsort_jecUnc.push_back(  (*_jets_jecUnc)[i_jet] );
      _recoPFJet_DeepJetsort_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
      _recoPFJet_DeepJetsort_hadronFlavour.push_back(  (*_jets_HadronFlavour)[i_jet] );
      _recoPFJet_DeepJetsort_QGdiscr.push_back(  (*_jets_QGdiscr)[i_jet] );

      if(i_PFJet<2){
        _recoPFJet_btag_e.push_back( jet.E() );
	      _recoPFJet_btag_pt.push_back( jet.Pt() );
	      _recoPFJet_btag_px.push_back( jet.Px() );
	      _recoPFJet_btag_py.push_back( jet.Py() );
	      _recoPFJet_btag_pz.push_back( jet.Pz() );
	      _recoPFJet_btag_eta.push_back( jet.Eta() );
	      _recoPFJet_btag_phi.push_back( jet.Phi() );
	      _recoPFJet_btag_CSVscore.push_back( (*_bCSVscore)[i_jet] );
        _recoPFJet_btag_DeepCSVscore.push_back( DeepCSVscore );
        _recoPFJet_btag_DeepJetscore.push_back( DeepJetscore );
	      _recoPFJet_btag_jecUnc.push_back(  (*_jets_jecUnc)[i_jet] );
	      _recoPFJet_btag_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
	      _recoPFJet_btag_hadronFlavour.push_back(  (*_jets_HadronFlavour)[i_jet] );
        _recoPFJet_btag_QGdiscr.push_back(  (*_jets_QGdiscr)[i_jet] );

      }

    }


    if(_n_recoPFJet>=2){

      for(unsigned int i_PFJet=0; i_PFJet<reco_jets.size(); i_PFJet++){

	      int i_jet = reco_jets[i_PFJet].first;
	      TLorentzVector jet =  reco_jets[i_PFJet].second;
    
	      if(i_jet==i_jet_DeepJet_pairs[0].first || i_jet==i_jet_DeepJet_pairs[1].first) continue;

	      _recoPFJet_untag_e.push_back( jet.E() );
	      _recoPFJet_untag_pt.push_back( jet.Pt() );
	      _recoPFJet_untag_px.push_back( jet.Px() );
	      _recoPFJet_untag_py.push_back( jet.Py() );
	      _recoPFJet_untag_pz.push_back( jet.Pz() );
	      _recoPFJet_untag_eta.push_back( jet.Eta() );
	      _recoPFJet_untag_phi.push_back( jet.Phi() );
	      _recoPFJet_untag_CSVscore.push_back( (*_bCSVscore)[i_jet] );
        _recoPFJet_untag_DeepCSVscore.push_back( (*_bDeepCSV_probb)[i_jet] + (*_bDeepCSV_probbb)[i_jet] );
        _recoPFJet_untag_DeepJetscore.push_back( (*_bDeepFlavor_probb)[i_jet] + (*_bDeepFlavor_probbb)[i_jet] + (*_bDeepFlavor_problepb)[i_jet]);
	      _recoPFJet_untag_jecUnc.push_back( (*_jets_jecUnc)[i_jet] );
	      _recoPFJet_untag_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
	      _recoPFJet_untag_hadronFlavour.push_back(  (*_jets_HadronFlavour)[i_jet] );
        _recoPFJet_untag_QGdiscr.push_back(  (*_jets_QGdiscr)[i_jet] );

      }

    }

    _n_recoPFJet_untag=_recoPFJet_untag_e.size();

    //W-tag
    double mW=80.4;

    if(_recoPFJet_untag_e.size()>1){

      vector<int> index_Wtag;
      index_Wtag.push_back(0);
      index_Wtag.push_back(0);
	    
      for(unsigned int i_jet1=0; i_jet1<_recoPFJet_untag_e.size()-1; i_jet1++){
        
        TLorentzVector jet1 ( _recoPFJet_untag_px[i_jet1], _recoPFJet_untag_py[i_jet1], _recoPFJet_untag_pz[i_jet1], _recoPFJet_untag_e[i_jet1] );
	
	      for(unsigned int i_jet2=i_jet1+1; i_jet2<_recoPFJet_untag_e.size(); i_jet2++){

	        TLorentzVector jet2 ( _recoPFJet_untag_px[i_jet2], _recoPFJet_untag_py[i_jet2], _recoPFJet_untag_pz[i_jet2], _recoPFJet_untag_e[i_jet2] );
	  
	        double mjj = (jet1+jet2).M();
	        if(mjj>60 && mjj<100)
	          _n_pair_Wtag_recoPFJet_untag++;

	        if( _recoPFJet_untag_best_mW<0 || (abs( mjj - mW ) < abs( _recoPFJet_untag_best_mW - mW )) ){
	    
	          _recoPFJet_untag_best_mW = mjj;
	    
	          if(jet1.Pt()>jet2.Pt()){
	            index_Wtag[0]=i_jet1;
	            index_Wtag[1]=i_jet2;
	          }
	          else{
	            index_Wtag[0]=i_jet2;
	            index_Wtag[1]=i_jet1;
	          }

	        }
	  
	      }
	
      }

      for(int k=0;k<2;k++){

	      int i_jet=index_Wtag[k];

	      _recoPFJet_untag_Wtag_e.push_back( _recoPFJet_untag_e[i_jet] );
	      _recoPFJet_untag_Wtag_pt.push_back( _recoPFJet_untag_pt[i_jet] );
	      _recoPFJet_untag_Wtag_px.push_back( _recoPFJet_untag_px[i_jet] );
	      _recoPFJet_untag_Wtag_py.push_back( _recoPFJet_untag_py[i_jet] );
	      _recoPFJet_untag_Wtag_pz.push_back( _recoPFJet_untag_pz[i_jet] );
	      _recoPFJet_untag_Wtag_eta.push_back( _recoPFJet_untag_eta[i_jet] );
	      _recoPFJet_untag_Wtag_phi.push_back( _recoPFJet_untag_phi[i_jet] );
	      _recoPFJet_untag_Wtag_CSVscore.push_back( _recoPFJet_untag_CSVscore[i_jet] );
	      _recoPFJet_untag_Wtag_DeepCSVscore.push_back( _recoPFJet_untag_DeepCSVscore[i_jet] );
        _recoPFJet_untag_Wtag_DeepJetscore.push_back( _recoPFJet_untag_DeepJetscore[i_jet] );
        _recoPFJet_untag_Wtag_jecUnc.push_back( _recoPFJet_untag_jecUnc[i_jet] );
	      _recoPFJet_untag_Wtag_Flavour.push_back( _recoPFJet_untag_Flavour[i_jet] );
	      _recoPFJet_untag_Wtag_hadronFlavour.push_back( _recoPFJet_untag_hadronFlavour[i_jet] );
        _recoPFJet_untag_Wtag_QGdiscr.push_back( _recoPFJet_untag_QGdiscr[i_jet] );

      }

    }


    //////////////////////////////////////////////
    ///             ak8   Jets                 ///
    //////////////////////////////////////////////


    vector< pair<int,TLorentzVector> > reco_ak8jets;

    for(unsigned int i_jet=0; i_jet<(*_ak8jets_e).size(); i_jet++){

      TLorentzVector ak8jet ( (*_ak8jets_px)[i_jet] , (*_ak8jets_py)[i_jet] , (*_ak8jets_pz)[i_jet] , (*_ak8jets_e)[i_jet] );

      if(ak8jet.Pt()>170) cout<<"here"<<endl;

      float msoftdrop = (*_ak8jets_SoftDropMass)[i_jet];

      pair<int,TLorentzVector> ak8jet_pair = make_pair(i_jet,ak8jet);

      int nsubjets = _recoPFak8Jet_nsubjets[i_jet];

      vector< pair<int,TLorentzVector> > reco_subjets;
      for(int i_subjet=0; i_subjet<nsubjets; i_subjet++){
        //TLorentzVector subjet ( (*_subjets_px)[i_jet] , (*_subjets_py)[i_jet] , (*_subjets_pz)[i_jet] , (*_subjets_e)[i_jet] );
        //unsigned int motherindex = (*_subjets_ak8MotherIdx)[i_subjet];
        //if(motherindex!=i_jet) continue;
        //pair<int,TLorentzVector> subjet_pair = make_pair(i_subjet,subjet);
        //reco_subjets.push_back(subjet_pair);
      }
      //sort(reco_subjets.begin(), reco_subjets.end(), pT_comparison_pairs);

      /*for(unsigned int i = 0; i<reco_subjets.size(); i++) {
        TLorentzVector mysubjet = reco_subjets[i].second;
        cout<<"i "<<mysubjet.Pt()<<endl;
      }*/

      if(ak8jet.Pt()>100 && fabs(ak8jet.Eta())<2.4 && msoftdrop>50){

        bool dR_veto=false;

        //cleaning here

        /*for(unsigned int i_lep=0; i_lep<_recolep_pt.size(); i_lep++){

          TLorentzVector lep;
          lep.SetPtEtaPhiE( recolep_pt[i_lep] , _recolep_eta[i_lep] , _recolep_phi[i_lep] , _recolep_e[i_lep] );
          float dR_lep_jet=lep.DeltaR(ak8jet);
          if(dR_lep_jet<0.4 && _recolep_ismvasel[i_lep]){
            dR_veto=true;
            break;
          }
        }

        for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){
          TLorentzVector tauh=reco_taus[i_tauh].second;
          float dR_tauh_jet=tauh.DeltaR(ak8jet);
          if(dR_tauh_jet<0.4){
            dR_veto=true;
            break;
          }
        }

        if(dR_veto)
          continue;*/

        reco_ak8jets.push_back(ak8jet_pair);

      }

    }

    sort(reco_ak8jets.begin(), reco_ak8jets.end(), pT_comparison_pairs);

    _n_recoPFak8Jet = reco_ak8jets.size();



    //////////////////////////////////////////////
    ///                MET                     ///
    //////////////////////////////////////////////
    
    TVector3 PFMET_tv3;
    PFMET_tv3.SetPtEtaPhi(_met,0,_metphi);
    _PFMETx = PFMET_tv3.Px();
    _PFMETy = PFMET_tv3.Py();    
    _PFMET = PFMET_tv3.Pt();    
    _PFMET_phi = PFMET_tv3.Phi();


    TLorentzVector HTmiss_tlv;
    
    for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){
      TLorentzVector muon=reco_mus[i_mu].second;
      if(_recomu_isfakeable[i_mu]){ HTmiss_tlv-=muon; }
    }
    /*
    for(unsigned int i_ele=0; i_ele<reco_eles.size(); i_ele++){
      TLorentzVector elec=reco_eles[i_ele].second;
      if(_recoele_isfakeable[i_ele]){ HTmiss_tlv-=elec; }
    }*/
    //Take smearing/scale pT
    for(unsigned int i_ele=0; i_ele<reco_eles_corr.size(); i_ele++){
      TLorentzVector elec=reco_eles_corr[i_ele].second;
      if(_recoele_isfakeable[i_ele]){ HTmiss_tlv-=elec; }
    }
    for(unsigned int i_tau=0; i_tau<reco_taus.size(); i_tau++){
      TLorentzVector tau=reco_taus[i_tau].second;
      if (_recotauh_byVLooseIsolationMVArun2v2017v2DBoldDMwLT[i_tau]){ HTmiss_tlv-=tau; }
    }
    for(unsigned int i_jet=0; i_jet<reco_jets.size(); i_jet++){
      TLorentzVector jet=reco_jets[i_jet].second;
      HTmiss_tlv-=jet;
    }

    _HTmiss = HTmiss_tlv.Pt();    
    _ETmissLD = _PFMET*0.6 + _HTmiss*0.4;


    //////////////////////////////////////////
    ///           MVAs multilep            ///
    //////////////////////////////////////////

    _MT_lep1= -999.;
    _mindR_lep1_recoPFjet = -999.;
    _mindR_lep2_recoPFjet = -999.;
    _lep1_conept = -999.;
    _lep2_conept = -999.;
    _lep3_conept = -999.;
    _avg_dr_jet = 0.;
    _MVA_2lSS_ttV = -999.;
    _MVA_2lSS_ttbar = -999.;
    _MVA_3l_ttV = -999.;
    _MVA_3l_ttbar = -999.;


    TLorentzVector leading_lep(0.,0.,0.,0.);
    TLorentzVector subleading_lep(0.,0.,0.,0.);
    TLorentzVector trailing_lep(0.,0.,0.,0.);

    if(reco_leptons.size()>0){

      leading_lep=reco_leptons[0].second;
      _lep1_conept = _recolep_conept[0];
      _MT_lep1=sqrt( 2*_lep1_conept*_PFMET*(1-cos(leading_lep.Phi()-_PFMET_phi)) );

      for(unsigned int i_jet=0; i_jet<reco_jets.size(); i_jet++){  

	      TLorentzVector jet=reco_jets[i_jet].second;
	      float dR=leading_lep.DeltaR(jet);

	      if(_mindR_lep1_recoPFjet<0 || dR<_mindR_lep1_recoPFjet)
	        _mindR_lep1_recoPFjet = dR;
      }

    }

    if(reco_leptons.size()>1){

      subleading_lep=reco_leptons[1].second;

      for(unsigned int i_jet=0; i_jet<reco_jets.size(); i_jet++){ 

	      TLorentzVector jet=reco_jets[i_jet].second;
	      float dR=subleading_lep.DeltaR(jet);

	      if(_mindR_lep2_recoPFjet<0 || dR<_mindR_lep2_recoPFjet)
	        _mindR_lep2_recoPFjet = dR;

      }

      _lep2_conept = _recolep_conept[1];

    }
      
    if(reco_leptons.size()>2){
      _lep3_conept = _recolep_conept[2];
    }

    
    if(_n_recoPFJet>1){
      int n_pair_jets = 0;
    
      for(unsigned int i_jet1=0; i_jet1<reco_jets.size(); i_jet1++){      
	      TLorentzVector jet1=reco_jets[i_jet1].second;

	      for(unsigned int i_jet2=i_jet1+1; i_jet2<reco_jets.size(); i_jet2++){     
	        TLorentzVector jet2=reco_jets[i_jet2].second;
	        _avg_dr_jet+=jet1.DeltaR(jet2);
	        n_pair_jets++;
	      }

      }    
      
      _avg_dr_jet/=n_pair_jets;

    }      

    if( (_n_recomu_presel+_n_recoele_presel)>=2){
    
      max_Lep_eta = max(fabs(leading_lep.Eta()),fabs(subleading_lep.Eta()));
      MT_met_lep1 = _MT_lep1;
      nJet25_Recl = _n_recoPFJet;
      mindr_lep1_jet = _mindR_lep1_recoPFjet;
      mindr_lep2_jet = _mindR_lep2_recoPFjet;
      LepGood_conePt1 = _lep1_conept;
      LepGood_conePt2 = _lep2_conept;
      met = min(_PFMET,float(400.));
      avg_dr_jet = _avg_dr_jet;
      
      _MVA_2lSS_ttV = MVA_2lSS_TTV_reader->EvaluateMVA("BDTG method");
      _MVA_2lSS_ttbar = MVA_2lSS_TT_reader->EvaluateMVA("BDTG method");
      
    }

    if( (_n_recomu_presel+_n_recoele_presel)>=3){
    
      max_Lep_eta = max(fabs(leading_lep.Eta()),fabs(subleading_lep.Eta()));
      MT_met_lep1 = _MT_lep1;
      nJet25_Recl = _n_recoPFJet;
      mhtJet25_Recl = _HTmiss;
      mindr_lep1_jet = _mindR_lep1_recoPFjet;
      mindr_lep2_jet = _mindR_lep2_recoPFjet;
      LepGood_conePt1 = _lep1_conept;
      LepGood_conePt2 = _lep2_conept;
      LepGood_conePt3 = _lep3_conept;
      met = min(_PFMET,float(400.));
      avg_dr_jet = _avg_dr_jet;
      
      _MVA_2lSS_ttV = MVA_2lSS_TTV_reader->EvaluateMVA("BDTG method");
      _MVA_2lSS_ttbar = MVA_2lSS_TT_reader->EvaluateMVA("BDTG method");
      _MVA_3l_ttV = MVA_3l_TTV_reader->EvaluateMVA("BDTG method");
      _MVA_3l_ttbar = MVA_3l_TT_reader->EvaluateMVA("BDTG method");
      
    }

    

    
    if(isMC){

      //////////////////////////////////////////////
      ///              Gen info                  ///
      //////////////////////////////////////////////
      
      vector<int> genlep_index;
      vector<int> gentauh_index;
      vector<int> gentau_index;
      vector<int> gentop_index;
      vector<int> genW_index;
      vector<int> genH_index;
      vector<int> genZ_index;
      vector<int> genb_index;
      vector<int> genq_index;
      vector<int> gennu_index;
            
      for(unsigned int i_gen=0; i_gen<(*_genpart_e).size(); i_gen++){
        
        TLorentzVector genpart_tlv( (*_genpart_px)[i_gen], (*_genpart_py)[i_gen], (*_genpart_pz)[i_gen], (*_genpart_e)[i_gen]);
  
        _genpart_pt.push_back(genpart_tlv.Pt());
        _genpart_eta.push_back(genpart_tlv.Eta());
        _genpart_phi.push_back(genpart_tlv.Phi());
  
        pair<int,float> pair = find_i_dRmin_closest( genpart_tlv,
                 (*_daughters_px), (*_daughters_py), (*_daughters_pz), (*_daughters_e) );
        _genpart_i_closest_daughter.push_back(pair.first);
        _genpart_dR_closest_daughter.push_back(pair.second);  

        int TauMothInd = (*_genpart_TauMothInd)[i_gen];
        int HMothInd = (*_genpart_HMothInd)[i_gen];
        int TopMothInd = (*_genpart_TopMothInd)[i_gen];
        int WMothInd = (*_genpart_WMothInd)[i_gen];
        int ZMothInd = (*_genpart_ZMothInd)[i_gen];
  
        int flags = (*_genpart_flags)[i_gen];
        bool isFromHardProcess = (flags >> 8) & 1;
        bool isDirectTauDecayProduct = (flags >> 4) & 1;
        bool isHardProcessTauDecayProduct = (flags >> 9) & 1;
        bool isLastCopy = (flags >>13) & 1;
        
        if( isLastCopy && (abs( (*_genpart_pdg)[i_gen] )==11 || abs( (*_genpart_pdg)[i_gen] )==13) ){
    
          _genlep_pdg.push_back( (*_genpart_pdg)[i_gen] );
          _genlep_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
    
          _genlep_e.push_back( genpart_tlv.E() );
          _genlep_px.push_back( genpart_tlv.Px() );
          _genlep_py.push_back( genpart_tlv.Py() );
          _genlep_pz.push_back( genpart_tlv.Pz() );
          _genlep_pt.push_back( genpart_tlv.Pt() );
          _genlep_eta.push_back( genpart_tlv.Eta() );
          _genlep_phi.push_back( genpart_tlv.Phi() );
          _genlep_flags.push_back(flags);
    
          if( TauMothInd>-1 && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
            _n_genlep_fromTau++;
          if( TopMothInd>-1 && WMothInd>-1 && isFromHardProcess)
            _n_genlep_fromTop++;
          if( genpart_tlv.Pt()>10)
            _n_genlep10++;
          if( genpart_tlv.Pt()>20)
            _n_genlep20++;
          if( genpart_tlv.Pt()>20 && abs(genpart_tlv.Eta())<2.1)
            _n_genlep20_eta21++;
    
          genlep_index.push_back(i_gen);
    
        }
  
        else if( abs( (*_genpart_pdg)[i_gen] )==66615){
    
          _gentauh_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
    
          _gentauh_e.push_back( genpart_tlv.E() );
          _gentauh_px.push_back( genpart_tlv.Px() );
          _gentauh_py.push_back( genpart_tlv.Py() );
          _gentauh_pz.push_back( genpart_tlv.Pz() );
          _gentauh_pt.push_back( genpart_tlv.Pt() );
          _gentauh_eta.push_back( genpart_tlv.Eta() );
          _gentauh_phi.push_back( genpart_tlv.Phi() );
          _gentauh_flags.push_back(flags);
    
          int flag_Mother = (*_genpart_flags)[(*_genpart_TauMothInd)[i_gen]];
          bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
    
          if( TauMothInd>-1 && isMotherFromHardProcess )
            _n_gentauh_fromTau++;
          if( TopMothInd>-1 && WMothInd>-1 && TauMothInd>-1 && isMotherFromHardProcess )
            _n_gentauh_fromTop++;
          if( genpart_tlv.Pt()>10)
            _n_gentauh10++;
          if( genpart_tlv.Pt()>30)
            _n_gentauh30++;
          if( genpart_tlv.Pt()>30 && abs(genpart_tlv.Eta())<2.1 )
            _n_gentauh30_eta21++;
    
          gentauh_index.push_back(i_gen);
    
        }
  
        else if( abs( (*_genpart_pdg)[i_gen] )==15){
    
          _gentau_decayMode.push_back( (*_genpart_TauGenDecayMode)[i_gen] );
          _gentau_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
    
          _gentau_e.push_back( genpart_tlv.E() );
          _gentau_px.push_back( genpart_tlv.Px() );
          _gentau_py.push_back( genpart_tlv.Py() );
          _gentau_pz.push_back( genpart_tlv.Pz() );
          _gentau_pt.push_back( genpart_tlv.Pt() );
          _gentau_eta.push_back( genpart_tlv.Eta() );
          _gentau_phi.push_back( genpart_tlv.Phi() );
          _gentau_flags.push_back(flags);
    
          if( HMothInd>-1 && isFromHardProcess)
            _n_gentau_fromH++;
          if( TopMothInd>-1 && WMothInd>-1 && isFromHardProcess )
            _n_gentau_fromTop++;
    
          gentau_index.push_back(i_gen);
    
         }
  
        else if( abs( (*_genpart_pdg)[i_gen] )==25 ){
    
          _genH_decayMode.push_back( (*_genpart_HZDecayMode)[i_gen] );
    
          _genH_e.push_back( genpart_tlv.E() );
          _genH_px.push_back( genpart_tlv.Px() );
          _genH_py.push_back( genpart_tlv.Py() );
          _genH_pz.push_back( genpart_tlv.Pz() );
          _genH_pt.push_back( genpart_tlv.Pt() );
          _genH_eta.push_back( genpart_tlv.Eta() );
          _genH_phi.push_back( genpart_tlv.Phi() );
          _genH_flags.push_back(flags);
    
          genH_index.push_back(i_gen);
    
        }

        else if( abs( (*_genpart_pdg)[i_gen] )==23){
    
          _genZ_decayMode.push_back( (*_genpart_HZDecayMode)[i_gen] );
    
          _genZ_e.push_back( genpart_tlv.E() );
          _genZ_px.push_back( genpart_tlv.Px() );
          _genZ_py.push_back( genpart_tlv.Py() );
          _genZ_pz.push_back( genpart_tlv.Pz() );
          _genZ_pt.push_back( genpart_tlv.Pt() );
          _genZ_eta.push_back( genpart_tlv.Eta() );
          _genZ_phi.push_back( genpart_tlv.Phi() );
          _genZ_flags.push_back(flags);
    
          genZ_index.push_back(i_gen);
    
        }
  
        //Check if top is last copy
        else if( abs( (*_genpart_pdg)[i_gen] )==6 && (flags>>13)&1){
    
          _gentop_pdg.push_back( (*_genpart_pdg)[i_gen] );
    
          _gentop_decayMode.push_back(  (*_genpart_TopDecayMode)[i_gen] );
          _gentop_e.push_back( genpart_tlv.E() );
          _gentop_px.push_back( genpart_tlv.Px() );
          _gentop_py.push_back( genpart_tlv.Py() );
          _gentop_pz.push_back( genpart_tlv.Pz() );
          _gentop_pt.push_back( genpart_tlv.Pt() );
          _gentop_eta.push_back( genpart_tlv.Eta() );
          _gentop_phi.push_back( genpart_tlv.Phi() );
          _gentop_flags.push_back(flags);
    
          gentop_index.push_back(i_gen);
    
        }
  
        else if( abs( (*_genpart_pdg)[i_gen] )==24){
    
          _genW_pdg.push_back( (*_genpart_pdg)[i_gen] );
    
          _genW_decayMode.push_back(  (*_genpart_WDecayMode)[i_gen] );
          _genW_e.push_back( genpart_tlv.E() );
          _genW_px.push_back( genpart_tlv.Px() );
          _genW_py.push_back( genpart_tlv.Py() );
          _genW_pz.push_back( genpart_tlv.Pz() );
          _genW_pt.push_back( genpart_tlv.Pt() );
          _genW_eta.push_back( genpart_tlv.Eta() );
          _genW_phi.push_back( genpart_tlv.Phi() );
          _genW_flags.push_back(flags);
    
          if( TopMothInd>-1 )
           _n_genW_fromTop++;
    
          genW_index.push_back(i_gen);
    
        }
  
        else if( abs( (*_genpart_pdg)[i_gen] )==5){
    
          _genb_pdg.push_back( (*_genpart_pdg)[i_gen] );
    
          _genb_e.push_back( genpart_tlv.E() );
          _genb_px.push_back( genpart_tlv.Px() );
          _genb_py.push_back( genpart_tlv.Py() );
          _genb_pz.push_back( genpart_tlv.Pz() );
          _genb_pt.push_back( genpart_tlv.Pt() );
          _genb_eta.push_back( genpart_tlv.Eta() );
          _genb_phi.push_back( genpart_tlv.Phi() );
          _genb_flags.push_back(flags);
    
          if( TopMothInd>-1 && WMothInd==-1 && isFromHardProcess )
            _n_genb_fromTop++;
          if( genpart_tlv.Pt()>10)
            _n_genb10++;
    
          genb_index.push_back(i_gen);
    
          std::pair<int,float> pair_genb = find_i_dRmin_closest( genpart_tlv, _recolep_px, _recolep_py, _recolep_pz, _recolep_e );
          _genb_i_closest_recolep.push_back(pair_genb.first);
          _genb_dR_closest_recolep.push_back(pair_genb.second);
    
    
        }
  
        else if( abs( (*_genpart_pdg)[i_gen] )<5){
    
          _genq_pdg.push_back( (*_genpart_pdg)[i_gen] );
    
          _genq_e.push_back( genpart_tlv.E() );
          _genq_px.push_back( genpart_tlv.Px() );
          _genq_py.push_back( genpart_tlv.Py() );
          _genq_pz.push_back( genpart_tlv.Pz() );
          _genq_pt.push_back( genpart_tlv.Pt() );
          _genq_eta.push_back( genpart_tlv.Eta() );
          _genq_phi.push_back( genpart_tlv.Phi() );
          _genq_flags.push_back(flags);
    
          if( TopMothInd>-1 && WMothInd>-1 && isFromHardProcess )
            _n_genq_fromTop++;
          if( genpart_tlv.Pt()>10)
            _n_genq10++;
    
          genq_index.push_back(i_gen);
    
        }
  
        else if( abs( (*_genpart_pdg)[i_gen] )==12 || abs( (*_genpart_pdg)[i_gen] )==14 || abs( (*_genpart_pdg)[i_gen] )==16){
    
          _gennu_pdg.push_back( (*_genpart_pdg)[i_gen] );
    
          _gennu_e.push_back( genpart_tlv.E() );
          _gennu_px.push_back( genpart_tlv.Px() );
          _gennu_py.push_back( genpart_tlv.Py() );
          _gennu_pz.push_back( genpart_tlv.Pz() );
          _gennu_pt.push_back( genpart_tlv.Pt() );
          _gennu_eta.push_back( genpart_tlv.Eta() );
          _gennu_phi.push_back( genpart_tlv.Phi() );
          _gennu_flags.push_back(flags);
    
          //Only count lep from tau from Higgs or top
          if( TauMothInd>-1 && ( HMothInd>-1  || (TopMothInd>-1 && WMothInd>-1 && isFromHardProcess) ) )
            _n_gennu_fromTau++;
          if( (TopMothInd>-1 && WMothInd>-1 && isFromHardProcess) )
            _n_gennu_fromTop++;
    
          gennu_index.push_back(i_gen);
    
    
        }
  

      }
      
      _n_genlep = _genlep_e.size();
      _n_gentauh = _gentauh_e.size();
      _n_gentau = _gentau_e.size();
      _n_genH = _genH_e.size();
      _n_genZ = _genZ_e.size();
      _n_gentop = _gentop_e.size();
      _n_genW = _genW_e.size();
      _n_genb = _genb_e.size();
      _n_genq = _genq_e.size();
      _n_gennu = _gennu_e.size();


      for(int i_lep=0; i_lep<_n_genlep; i_lep++){

        int i_gen = genlep_index[i_lep];
      
        int i_tau_Moth = -1;
        int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
        if( i_gen_TauMoth > -1 ){
          for(int i_tau=0; i_tau<_n_gentau; i_tau++){
            if( gentau_index[i_tau]==i_gen_TauMoth){
              i_tau_Moth = i_tau;
              break;
            }
          } 
        }
        _genlep_TauMothInd.push_back(i_tau_Moth);

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }   
        }      
        _genlep_TopMothInd.push_back(i_top_Moth);

        int i_W_Moth = -1;
        int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
        if( i_gen_WMoth > -1 ){
          for(int i_W=0; i_W<_n_genW; i_W++){
            if( genW_index[i_W]==i_gen_WMoth){
              i_W_Moth = i_W;
              break;
            }
          }
        }      
        _genlep_WMothInd.push_back(i_W_Moth);

        int i_Z_Moth = -1;
        int i_gen_ZMoth = (*_genpart_ZMothInd)[i_gen];
        if( i_gen_ZMoth > -1 && i_gen_TauMoth==-1){
          for(int i_Z=0; i_Z<_n_genZ; i_Z++){
            if( genZ_index[i_Z]==i_gen_ZMoth){
              i_Z_Moth = i_Z;
              break;
            }
          }
        }      
        _genlep_ZMothInd.push_back(i_Z_Moth);

      }


      for(int i_tauh=0; i_tauh<_n_gentauh; i_tauh++){

        int i_gen = gentauh_index[i_tauh];
      
        int i_tau_Moth = -1;
        int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
        if( i_gen_TauMoth > -1 ){
          for(int i_tau=0; i_tau<_n_gentau; i_tau++){
            if( gentau_index[i_tau]==i_gen_TauMoth){
              i_tau_Moth = i_tau;
              break;
            }
          }
        }
        _gentauh_TauMothInd.push_back(i_tau_Moth);

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }
        }      
        _gentauh_TopMothInd.push_back(i_top_Moth);

        int i_W_Moth = -1;
        int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
        if( i_gen_WMoth > -1 ){
          for(int i_W=0; i_W<_n_genW; i_W++){
            if( genW_index[i_W]==i_gen_WMoth){
              i_W_Moth = i_W;
              break;
            }
          }
        }      
        _gentauh_WMothInd.push_back(i_W_Moth);

      }

    
      for(int i_tau=0; i_tau<_n_gentau; i_tau++){

        int i_gen = gentau_index[i_tau];     

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }
        }      
        _gentau_TopMothInd.push_back(i_top_Moth);

        int i_W_Moth = -1;
        int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
        if( i_gen_WMoth > -1 ){
          for(int i_W=0; i_W<_n_genW; i_W++){
            if( genW_index[i_W]==i_gen_WMoth){
              i_W_Moth = i_W;
              break;
            }
          }
        }      
        _gentau_WMothInd.push_back(i_W_Moth);

        int i_H_Moth = -1;
        int i_gen_HMoth = (*_genpart_HMothInd)[i_gen];
        if( i_gen_HMoth > -1 ){
          for(int i_H=0; i_H<_n_genH; i_H++){
            if( genH_index[i_H]==i_gen_HMoth){
              i_H_Moth = i_H;
              break;
            }
          }
        }      
        _gentau_HMothInd.push_back(i_H_Moth);

        int i_Z_Moth = -1;
        int i_gen_ZMoth = (*_genpart_ZMothInd)[i_gen];
        if( i_gen_ZMoth > -1 ){
          for(int i_Z=0; i_Z<_n_genZ; i_Z++){
            if( genZ_index[i_Z]==i_gen_ZMoth){
              i_Z_Moth = i_Z;
              break;
            }
          }
        }      
        _gentau_ZMothInd.push_back(i_Z_Moth);


      }


      for(int i_W=0; i_W<_n_genW; i_W++){

        int i_gen = genW_index[i_W];     

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }
        }      
        _genW_TopMothInd.push_back(i_top_Moth);


      }


      for(int i_b=0; i_b<_n_genb; i_b++){

        int i_gen = genb_index[i_b];     

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }
        }      
        _genb_TopMothInd.push_back(i_top_Moth);

        int i_W_Moth = -1;
        int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
        if( i_gen_WMoth > -1 ){
          for(int i_W=0; i_W<_n_genW; i_W++){
            if( genW_index[i_W]==i_gen_WMoth){
              i_W_Moth = i_W;
              break;
            }
          }
        }      
        _genb_WMothInd.push_back(i_W_Moth);


      }


      for(int i_q=0; i_q<_n_genq; i_q++){

        int i_gen = genq_index[i_q];     

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }
        }      
        _genq_TopMothInd.push_back(i_top_Moth);

        int i_W_Moth = -1;
        int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
        if( i_gen_WMoth > -1 ){
          for(int i_W=0; i_W<_n_genW; i_W++){
            if( genW_index[i_W]==i_gen_WMoth){
              i_W_Moth = i_W;
              break;
            }
          }
        }      
        _genq_WMothInd.push_back(i_W_Moth);


      }


      for(int i_nu=0; i_nu<_n_gennu; i_nu++){

        int i_gen = gennu_index[i_nu];
      
        int i_tau_Moth = -1;
        int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
        if( i_gen_TauMoth > -1 ){
          for(int i_tau=0; i_tau<_n_gentau; i_tau++){
            if( gentau_index[i_tau]==i_gen_TauMoth){
              i_tau_Moth = i_tau;
              break;
            }
          }
        }
        _gennu_TauMothInd.push_back(i_tau_Moth);

        int i_top_Moth = -1;
        int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
        if( i_gen_TopMoth > -1 ){
          for(int i_top=0; i_top<_n_gentop; i_top++){
            if( gentop_index[i_top]==i_gen_TopMoth){
              i_top_Moth = i_top;
              break;
            }
          }
        }      
        _gennu_TopMothInd.push_back(i_top_Moth);


        int i_W_Moth = -1;
        int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
        if( i_gen_WMoth > -1 ){
          for(int i_W=0; i_W<_n_genW; i_W++){
            if( genW_index[i_W]==i_gen_WMoth){
              i_W_Moth = i_W;
              break;
            }
          }
        }      
        _gennu_WMothInd.push_back(i_W_Moth);


      }


      
      for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){

        TLorentzVector mu = reco_mus[i_mu].second;
        float pt = (_recomu_pt)[i_mu];
	float conept = (_recomu_conept)[i_mu];
        int charge = (_recomu_charge)[i_mu];

        float dRmin = 1.0;
        int genMatchInd = -1;
        bool genchargematch = false;

        for(unsigned int i_gen=0; i_gen<(*_genpart_pdg).size();i_gen++){

	  if(!( abs((*_genpart_pdg)[i_gen])==13)) continue;
          
	  TLorentzVector gen((*_genpart_px)[i_gen],(*_genpart_py)[i_gen],(*_genpart_pz)[i_gen],(*_genpart_e)[i_gen]);        
          // check generator flags
          int flags = (*_genpart_flags)[i_gen];
          bool isprompt = flags&1;
          bool isdirectprompttau = (flags>>5)&1;
          if( !(isprompt || isdirectprompttau) ) continue;

	  // check if particle is stable
	  bool isstable = (*_genpart_status)[i_gen]==1;
          if( !isstable) continue;
 	
	  // check if particle has mother H/W/Z
          bool hasHmother = (*_genpart_HMothInd)[i_gen]>0;
          bool hasWmother = (*_genpart_WMothInd)[i_gen]>0;
          bool hasZmother = (*_genpart_ZMothInd)[i_gen]>0;
          if( !(hasHmother || hasWmother || hasZmother) ) continue;
    
          // check delta_pT
          float delta_pt = (fabs(pt - gen.Pt()) / gen.Pt());
          if(delta_pt > 0.5) continue;

          // check charge match
          int chargematch = false;
          if ( abs((*_genpart_pdg)[i_gen])==13 ){
            int charge_gen = (*_genpart_pdg)[i_gen] > 0 ? -1 : 1;
            if (charge_gen == charge) chargematch = true;
          }

	  // check dR
          float dR = mu.DeltaR(gen);    
          if(dR<dRmin){
            dRmin = dR;
            if(isprompt) genMatchInd = 2;
            else if(isdirectprompttau) genMatchInd = 4;
            genchargematch = chargematch;
          }

        }

        _recomu_isGenMatched.push_back(dRmin<0.3);
        _recomu_isGenChargeMatched.push_back(genchargematch);
        _recomu_genMatchInd.push_back(genMatchInd);

      }


      for(unsigned int i_ele=0; i_ele<reco_eles.size(); i_ele++){

        TLorentzVector ele = reco_eles[i_ele].second;
        float pt = (_recoele_pt)[i_ele];
        float conept = (_recoele_conept)[i_ele];
        int charge = (_recoele_charge)[i_ele];

        float dRmin = 1.0;
        int genMatchInd = -1;
        bool genchargematch = false;

        for(unsigned int i_gen=0; i_gen<(*_genpart_pdg).size();i_gen++){
          
          //for ele, also try to match to photons (for conversion bkg)
	  if( !( abs((*_genpart_pdg)[i_gen])==11 || abs((*_genpart_pdg)[i_gen])==22 )) continue;

	  TLorentzVector gen((*_genpart_px)[i_gen],(*_genpart_py)[i_gen],(*_genpart_pz)[i_gen],(*_genpart_e)[i_gen]);

	  //check the generator flags
          int flags = (*_genpart_flags)[i_gen];
          bool isprompt = flags&1;
          bool isdirectprompttau = (flags>>5)&1;
          if( !(isprompt || isdirectprompttau) ) continue;

	  //check if particle is stable
	  bool isstable = (*_genpart_status)[i_gen]==1;
          if( !isstable) continue;

	  //check if particle has mother H/W/Z
	  bool hasHmother = (*_genpart_HMothInd)[i_gen]>0;
          bool hasWmother = (*_genpart_WMothInd)[i_gen]>0;
          bool hasZmother = (*_genpart_ZMothInd)[i_gen]>0;
          if( !(hasHmother || hasWmother || hasZmother) ) continue;

	  //check delta_pT
	  float delta_pt = (fabs(pt - gen.Pt()) / gen.Pt());
          if(delta_pt > 0.5) continue;

          //check charge match
          bool chargematch = false;
          if ( abs((*_genpart_pdg)[i_gen])==11 ){
            int charge_gen = (*_genpart_pdg)[i_gen] > 0 ? -1 : 1;
            if (charge_gen == charge) chargematch = true;
          }

	  //check dR
	  float dR = ele.DeltaR(gen);
          if(dR<dRmin){
            dRmin = dR;
            if(isprompt) genMatchInd = 2;
            else if(isdirectprompttau) genMatchInd = 4;
            genchargematch = chargematch;
          }

        }

        _recoele_isGenMatched.push_back(dRmin<0.3);
        _recoele_isGenChargeMatched.push_back(genchargematch);
        _recoele_genMatchInd.push_back(genMatchInd);

      }


      for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){

        TLorentzVector lep = reco_leptons[i_lep].second;
	float pt = (_recolep_pt)[i_lep];
        float conept = (_recolep_conept)[i_lep];
        int charge = (_recolep_charge)[i_lep];

        float dRmin = 1.0;
        int genMatchInd = -1;
        bool genchargematch = false;

        for(unsigned int i_gen=0; i_gen<(*_genpart_pdg).size();i_gen++){

	  if( !( abs((*_genpart_pdg)[i_gen])==abs(_recolep_pdg[i_lep]) || abs((*_genpart_pdg)[i_gen])==22 )) continue;
    
          //check charge
          if ( abs((*_genpart_pdg)[i_gen])==11 || abs((*_genpart_pdg)[i_gen])==13 ){
            int charge_gen = (*_genpart_pdg)[i_gen] > 0 ? -1 : 1;
            if (charge_gen != charge) continue;
          }          

          TLorentzVector gen((*_genpart_px)[i_gen],(*_genpart_py)[i_gen],(*_genpart_pz)[i_gen],(*_genpart_e)[i_gen]);

	  //check the generator flags
	  int flags = (*_genpart_flags)[i_gen];
          bool isprompt = flags&1;
          bool isdirectprompttau = (flags>>5)&1;
          if( !(isprompt || isdirectprompttau) ) continue;
          
	  //check if particle is stable
	  bool isstable = (*_genpart_status)[i_gen]==1;
          if( !isstable) continue;

          //check if particle has mother H/W/Z
          bool hasHmother = (*_genpart_HMothInd)[i_gen]>0;
          bool hasWmother = (*_genpart_WMothInd)[i_gen]>0;
          bool hasZmother = (*_genpart_ZMothInd)[i_gen]>0;
          if( !(hasHmother || hasWmother || hasZmother) ) continue;

	  //check delta_pT
          float delta_pt = (fabs(pt - gen.Pt()) / gen.Pt());
          if(delta_pt > 0.5) continue;
          
	  //check charge match
          bool chargematch = false;
	  if ( abs((*_genpart_pdg)[i_gen])==11 || abs((*_genpart_pdg)[i_gen])==13 ){
            int charge_gen = (*_genpart_pdg)[i_gen] > 0 ? -1 : 1;
            if (charge_gen == charge) chargematch = true;
          }

	  //check dR
	  float dR = lep.DeltaR(gen);
          if(dR<dRmin){
            dRmin = dR;
            if(isprompt) genMatchInd = 2;
            else if(isdirectprompttau) genMatchInd = 4;
            genchargematch = chargematch;
          }	

        }   

        _recolep_isGenMatched.push_back(dRmin<0.3);
        _recolep_isGenChargeMatched.push_back(genchargematch);
        _recolep_genMatchInd.push_back(genMatchInd);

      }


      for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){

        TLorentzVector tauh = reco_taus[i_tauh].second;
  
        float dRmin = 1.0;
        int genMatchInd = -1;

        for(unsigned int i_gen=0; i_gen<(*_genpart_pdg).size();i_gen++){

          // require tau matched to electron, muon or tauh
	  int apdg = abs((*_genpart_pdg)[i_gen]);
          if( !( apdg==11 || apdg==13 || apdg==66615) ) continue;
	
          // require isPrompt
          int flags = (*_genpart_flags)[i_gen];
          if( apdg==11 || apdg==13){
             if( !( flags&1 || (flags>>5)&1) ) continue;
          }
          else if(apdg==66615){
	    int flags_tau = (*_genpart_flags)[(*_genpart_TauMothInd)[i_gen]];
	    if( !(flags_tau&1) ) continue; //!isprompt
          }

          // require mother is H,W or Z
          if( apdg==11 || apdg==13){
            bool hasHmother = ((*_genpart_HMothInd)[i_gen]>0);
            bool hasWmother = ((*_genpart_WMothInd)[i_gen]>0);
            bool hasZmother = ((*_genpart_ZMothInd)[i_gen]>0);
            if( !(hasHmother || hasWmother || hasZmother) ) continue;
          }
          else if(apdg==66615){
            bool hasHmother = ((*_genpart_HMothInd)[(*_genpart_TauMothInd)[i_gen]]>0);
            bool hasWmother = ((*_genpart_WMothInd)[(*_genpart_TauMothInd)[i_gen]]>0);
            bool hasZmother = ((*_genpart_ZMothInd)[(*_genpart_TauMothInd)[i_gen]]>0);
            if( !(hasHmother || hasWmother || hasZmother) ) continue;
          }

          TLorentzVector gen((*_genpart_px)[i_gen],(*_genpart_py)[i_gen],(*_genpart_pz)[i_gen],(*_genpart_e)[i_gen]);

          // require delta_pt<0.5/1.0
          float delta_pt = (fabs(tauh.Pt() - gen.Pt()) / gen.Pt());
          if( apdg==11 || apdg==13 ) {
	     if (delta_pt>0.5) continue;
          }
          else if(apdg==66615){
	     if (delta_pt>1.0) continue;
          }

	  // require dR<0.3
          float dR = tauh.DeltaR(gen);
          if(dR<dRmin){
            dRmin = dR;
            if(apdg==11){
              if(flags&1) genMatchInd = 1;
              else if((flags>>5)&1) genMatchInd = 3;
            }
            else if(apdg==13){
              if(flags&1) genMatchInd = 2;
              else if((flags>>5)&1) genMatchInd = 4;
            }
            else if(apdg==66615)
              genMatchInd = 5;
          }

        }

        _recotauh_isGenMatched.push_back(dRmin<0.3);
        _recotauh_genMatchInd.push_back(genMatchInd);

      }


      //Check lepton top/Higgs decay product

      for(unsigned int i_lepton=0; i_lepton<reco_mus.size(); i_lepton++){

        int reco_TopMothInd = -1;
        int reco_HMothInd = -1;
      
        TLorentzVector lep=reco_mus[i_lepton].second;
        int i_daughter = reco_mus[i_lepton].first;
        pair<int,float> pair = find_i_dRmin_closest( lep,
                       _genlep_px, _genlep_py, _genlep_pz, _genlep_e );

        int i_genlep = pair.first;
        float dR = pair.second;
      

        //Check matching reco/gen lepton
        if(fabs((*_PDGIdDaughters)[i_daughter]) == fabs(_genlep_pdg[i_genlep]) && dR<0.1){

          bool isFromHardProcess = ( (_genlep_flags)[i_genlep] >> 8 ) & 1;
          bool isDirectTauDecayProduct = ( (_genlep_flags)[i_genlep] >> 4) & 1;
          bool isHardProcessTauDecayProduct = ( (_genlep_flags)[i_genlep] >> 9) & 1;
          int TauMothInd = (_genlep_TauMothInd)[i_genlep];
          int TopMothInd = (_genlep_TopMothInd)[i_genlep];
          int HMothInd = -1;
          bool isTauFromHardProcess = false;
          if(TauMothInd>=0){
            HMothInd = (_gentau_HMothInd)[TauMothInd];
            isTauFromHardProcess = ( (_gentau_flags)[TauMothInd] >> 8 ) & 1;
          }

          //Top
          if(TopMothInd>=0){

            if( (_gentop_decayMode[TopMothInd]==1 || _gentop_decayMode[TopMothInd]==2) && isFromHardProcess)
              reco_TopMothInd = TopMothInd;

            else if( (_gentop_decayMode[TopMothInd]==3 || _gentop_decayMode[TopMothInd]==4) && isTauFromHardProcess && isDirectTauDecayProduct && isHardProcessTauDecayProduct)
              reco_TopMothInd = TopMothInd;


          }

          //Higgs
          if(HMothInd>=0){
    
            if( (_genH_decayMode[HMothInd]==0 || _genH_decayMode[HMothInd]==1 || _genH_decayMode[HMothInd]==3 || _genH_decayMode[HMothInd]==4 || _genH_decayMode[HMothInd]==5) && isTauFromHardProcess && isDirectTauDecayProduct && isHardProcessTauDecayProduct)
              reco_HMothInd = HMothInd;

          }
    
        }

        _recomu_TopMothInd.push_back(reco_TopMothInd);
        _recomu_HMothInd.push_back(reco_HMothInd);
      

      }
 

      for(unsigned int i_lepton=0; i_lepton<reco_eles.size(); i_lepton++){

        int reco_TopMothInd = -1;
        int reco_HMothInd = -1;
      
        TLorentzVector lep=reco_eles[i_lepton].second;
        int i_daughter = reco_eles[i_lepton].first;
        pair<int,float> pair = find_i_dRmin_closest( lep,
                       _genlep_px, _genlep_py, _genlep_pz, _genlep_e );

        int i_genlep = pair.first;
        float dR = pair.second;
      

        //Check matching reco/gen lepton
        if(fabs((*_PDGIdDaughters)[i_daughter]) == fabs(_genlep_pdg[i_genlep]) && dR<0.1){

          bool isFromHardProcess = ( (_genlep_flags)[i_genlep] >> 8 ) & 1;
          bool isDirectTauDecayProduct = ( (_genlep_flags)[i_genlep] >> 4) & 1;
          bool isHardProcessTauDecayProduct = ( (_genlep_flags)[i_genlep] >> 9) & 1;
          int TauMothInd = (_genlep_TauMothInd)[i_genlep];
          int TopMothInd = (_genlep_TopMothInd)[i_genlep];
          int HMothInd = -1;
          bool isTauFromHardProcess = false;
          if(TauMothInd>=0){
            HMothInd = (_gentau_HMothInd)[TauMothInd];
            isTauFromHardProcess = ( (_gentau_flags)[TauMothInd] >> 8 ) & 1;
          }

          //Top
          if(TopMothInd>=0){

            if( (_gentop_decayMode[TopMothInd]==1 || _gentop_decayMode[TopMothInd]==2) && isFromHardProcess)
              reco_TopMothInd = TopMothInd;

            else if( (_gentop_decayMode[TopMothInd]==3 || _gentop_decayMode[TopMothInd]==4) && isTauFromHardProcess && isDirectTauDecayProduct && isHardProcessTauDecayProduct)
              reco_TopMothInd = TopMothInd;


          }

          //Higgs
          if(HMothInd>=0){
    
            if( (_genH_decayMode[HMothInd]==0 || _genH_decayMode[HMothInd]==1 || _genH_decayMode[HMothInd]==3 || _genH_decayMode[HMothInd]==4 || _genH_decayMode[HMothInd]==5) && isTauFromHardProcess && isDirectTauDecayProduct && isHardProcessTauDecayProduct)
              reco_HMothInd = HMothInd;

          }
    
        }

        _recoele_TopMothInd.push_back(reco_TopMothInd);
        _recoele_HMothInd.push_back(reco_HMothInd);
      

      }
    
       
      //Check lepton charge assignement
      for(unsigned int i_recolep=0; i_recolep<reco_mus.size(); i_recolep++){

        TLorentzVector recolep=reco_mus[i_recolep].second;
        float dRmin = -1;
        int i_closest_genlep = -1;

        for(unsigned int i_genlep=0; i_genlep<genlep_index.size(); i_genlep++){

          if(abs(_genlep_pdg[i_genlep])!=13)
            continue;

          TLorentzVector genlep(_genlep_px[i_genlep], _genlep_py[i_genlep], _genlep_pz[i_genlep], _genlep_e[i_genlep]);
          float dR = genlep.DeltaR(recolep);

          if(dRmin<0 || dR<dRmin){
            dRmin = dR;
            i_closest_genlep = i_genlep;
          }

        }

        int goodsign = 0;

        if(i_closest_genlep>=0 && dRmin<0.1){
          if( _genlep_pdg[i_closest_genlep]*_recomu_charge[i_recolep]<0)
            goodsign = 1;
          else
            goodsign = -1;
        }

        _recomu_goodsign.push_back(goodsign);

      }


      for(unsigned int i_recolep=0; i_recolep<reco_eles.size(); i_recolep++){

        TLorentzVector recolep=reco_eles[i_recolep].second;
        float dRmin = -1;
        int i_closest_genlep = -1;

        for(unsigned int i_genlep=0; i_genlep<genlep_index.size(); i_genlep++){

          if(abs(_genlep_pdg[i_genlep])!=11)
            continue;

          TLorentzVector genlep(_genlep_px[i_genlep], _genlep_py[i_genlep], _genlep_pz[i_genlep], _genlep_e[i_genlep]);
          float dR = genlep.DeltaR(recolep);

          if(dRmin<0 || dR<dRmin){
            dRmin = dR;
            i_closest_genlep = i_genlep;
          }

        }

        int goodsign = 0;

        if(i_closest_genlep>=0 && dRmin<0.1){
          if( _genlep_pdg[i_closest_genlep]*_recoele_charge[i_recolep]<0)
            goodsign = 1;
         else
            goodsign = -1;
        }

        _recoele_goodsign.push_back(goodsign);

      }

    

      for(int i_top=0; i_top<_n_gentop; i_top++){
      

        bool isRecoMatched = false;
        int i_recoPFJet_btag = -1;
        float dR_recoPFJet_btag = 9999.;
        int i_recoPFJet_untag1 = -1;
        float dR_recoPFJet_untag1 = 9999.;
        int i_recoPFJet_untag2 = -1;
        float dR_recoPFJet_untag2 = 9999.;
        int i_recolep = -1;
        float dR_recolep = 9999.;      
      
        if(_gentop_decayMode[i_top]==0){  // Hadronic top

          int i_bh = -1;
          int i_q1 = -1;
          int i_q2 = -1;

          for(int i_b=0; i_b<_n_genb; i_b++){

            bool isFromHardProcess = ( (_genb_flags)[i_b] >> 8 ) & 1;
            int TopMothInd = (_genb_TopMothInd)[i_b];
            int WMothInd = (_genb_WMothInd)[i_b];

            if( !( TopMothInd==i_top && WMothInd==-1 && isFromHardProcess ) )
              continue;

            i_bh = i_b;

          }

          for(int i_q=0; i_q<_n_genq; i_q++){

            bool isFromHardProcess = ( (_genq_flags)[i_q] >> 8 ) & 1;
            int TopMothInd = (_genq_TopMothInd)[i_q];
            int WMothInd = (_genq_WMothInd)[i_q];

            if( !( TopMothInd==i_top && WMothInd>=0 && isFromHardProcess ) )
              continue;

            if(i_q1==-1)
              i_q1=i_q;
            else
              i_q2=i_q;
    
          }

          if( (_genq_pt)[i_q1] < (_genq_pt)[i_q2] ){
            int iq_temp = i_q2;
            i_q2 = i_q1;
            i_q1 = iq_temp;
          }

  
          TLorentzVector genbh(_genb_px[i_bh],_genb_py[i_bh],_genb_pz[i_bh],_genb_e[i_bh]);
          TLorentzVector genq1(_genq_px[i_q1],_genq_py[i_q1],_genq_pz[i_q1],_genq_e[i_q1]);
          TLorentzVector genq2(_genq_px[i_q2],_genq_py[i_q2],_genq_pz[i_q2],_genq_e[i_q2]);


          for(unsigned int i_bjet=0; i_bjet<_recoPFJet_btag_e.size(); i_bjet++){

            TLorentzVector bjet(_recoPFJet_btag_px[i_bjet],_recoPFJet_btag_py[i_bjet],_recoPFJet_btag_pz[i_bjet],_recoPFJet_btag_e[i_bjet]);
            float dR = bjet.DeltaR(genbh);
            if(dR<min(float(0.5),dR_recoPFJet_btag)){
              dR_recoPFJet_btag = dR;
              i_recoPFJet_btag = i_bjet;
            }

          }

          for(unsigned int i_jet=0; i_jet<_recoPFJet_untag_e.size(); i_jet++){

            TLorentzVector jet(_recoPFJet_untag_px[i_jet],_recoPFJet_untag_py[i_jet],_recoPFJet_untag_pz[i_jet],_recoPFJet_untag_e[i_jet]);

            float dR1 = jet.DeltaR(genq1);
            if(dR1<min(float(0.5),dR_recoPFJet_untag1)){
              dR_recoPFJet_untag1 = dR1;
              i_recoPFJet_untag1 = i_jet;
            }

            float dR2 = jet.DeltaR(genq2);
            if(dR2<min(float(0.5),dR_recoPFJet_untag2)){
              dR_recoPFJet_untag2 = dR2;
              i_recoPFJet_untag2 = i_jet;
            }

          }

  
          isRecoMatched = (i_recoPFJet_btag>=0) && (i_recoPFJet_untag1>=0) && (i_recoPFJet_untag2>=0);

        }     

        else if(_gentop_decayMode[i_top]<4){ // Leptonic top

          int i_bl = -1;
          int i_lt = -1;

          for(int i_b=0; i_b<_n_genb; i_b++){

            bool isFromHardProcess = ( (_genb_flags)[i_b] >> 8 ) & 1;
            int TopMothInd = (_genb_TopMothInd)[i_b];
            int WMothInd = (_genb_WMothInd)[i_b];

            if( !( TopMothInd==i_top && WMothInd==-1 && isFromHardProcess ) )
              continue;

            i_bl = i_b;

          }


          for(int i_lep=0; i_lep<_n_genlep; i_lep++){

            bool isFromHardProcess = ( (_genlep_flags)[i_lep] >> 8 ) & 1;
            int TopMothInd = (_genlep_TopMothInd)[i_lep];
     
            if( !(TopMothInd == i_top && isFromHardProcess)) continue;

              i_lt = i_lep;

          }

          TLorentzVector genbl(_genb_px[i_bl],_genb_py[i_bl],_genb_pz[i_bl],_genb_e[i_bl]);
          TLorentzVector genlt(_genlep_px[i_lt],_genlep_py[i_lt],_genlep_pz[i_lt],_genlep_e[i_lt]);
  

          for(unsigned int i_bjet=0; i_bjet<_recoPFJet_btag_e.size(); i_bjet++){

            TLorentzVector bjet(_recoPFJet_btag_px[i_bjet],_recoPFJet_btag_py[i_bjet],_recoPFJet_btag_pz[i_bjet],_recoPFJet_btag_e[i_bjet]);
            float dR = bjet.DeltaR(genbl);
            if(dR<min(float(0.5),dR_recoPFJet_btag)){
              dR_recoPFJet_btag = dR;
              i_recoPFJet_btag = i_bjet;
            }

          }


          for(unsigned int i_lep=0; i_lep<_recolep_e.size(); i_lep++){

            TLorentzVector lep(_recolep_px[i_lep],_recolep_py[i_lep],_recolep_pz[i_lep],_recolep_e[i_lep]);
            float dR = lep.DeltaR(genlt);
            if(dR<min(float(0.5),dR_recolep)){
              dR_recolep = dR;
              i_recolep = i_lep;
            }
    
          }
  
          isRecoMatched = (i_recoPFJet_btag>=0) && (i_recolep>=0);


        }

      
        _gentop_isRecoMatched.push_back(isRecoMatched);
        _gentop_i_recoPFJet_btag.push_back(i_recoPFJet_btag);
        _gentop_i_recoPFJet_untag1.push_back(i_recoPFJet_untag1);
        _gentop_i_recoPFJet_untag2.push_back(i_recoPFJet_untag2);
        _gentop_i_recolep.push_back(i_recolep);

      }



    }


    tree_new->Fill();
    
  }
  
  f_new->cd();
  tree_new->Write();
  f_new->Close();

  return;

}


void test16(){

  convert_tree("sync16",0,"byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT",true,0,0,true,0,0,"presel",2016);

}

void test17(){

  convert_tree("sync17",0,"byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT",true,0,0,true,0,0,"presel",2017);

}

void test18(){

  convert_tree("sync18",0,"byVLooseIsolationMVArun2v2017v2DBoldDMdR0p3wLT",true,0,0,true,0,0,"presel",2018);

}
