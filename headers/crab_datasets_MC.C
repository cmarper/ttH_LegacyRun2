// export DPM_HOST=node12.datagrid.cea.fr 
// export DPNS_HOST=node12.datagrid.cea.fr 
// rfdir /dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/
// root://node12.datagrid.cea.fr:1094//dpm/datagrid.cea.fr/home/cms/trivcat/store/user/


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


std::tuple<TString, int, int, TString, bool> get_parameters( TString sample = "Oct19v1_MC_2016_ttHJetToNonbb" ){

  TString dir_in;
  int nfiles;
  int year;
  TString type;
  bool isMC;

    /////////////////
    //// 2016 MC ////
    /////////////////

    // t(t)H 
  /*if( sample = "Oct19v1_MC_2016_ttHJetToNonbb" ) {  //0
	    dir_in = "MC_2016_Oct19/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/Oct19v1_MC_2016_ttHJetToNonbb/191009_140820/";
  	    nfiles = 90;
	    year = 2016;
	    type = "ttH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_THQ_ctcvcp" ) {  //1 - GOOD
	    dir_in = "MC_2016_Oct19/THQ_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2016_THQ_ctcvcp/191009_140908/";
	  i_split = 191;
	    year = 2016;
	    type = "ttH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_THW_ctcvcp" ) {  //2 - GOOD
	    dir_in = "MC_2016_Oct19/THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2016_THW_ctcvcp/191009_140956/";
  	    nfiles = 127;
	    year = 2016;
	    type = "ttH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_ttH_ctcvcp" ) {  //3
	    dir_in = "MC_2016_Oct19/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/Oct19v1_MC_2016_ttH_ctcvcp/191009_141043/";
  	    nfiles = 149;
	    year = 2016;
	    type = "ttH";
	    isMC = true;
    }*/

    // TTV
    /*else if( sample = "Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2" ) {  //4
	    dir_in = "MC_2016_Oct19/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2/191009_141131/";
  	    nfiles = 49;
	    year = 2016;
	    type = "ttV";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3" ) {  //5
	    dir_in = "MC_2016_Oct19/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3/191009_141221/";
  	    nfiles = 48;
	    year = 2016; 
	    type = "ttV";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_TTZToLL_M-1to10" ) {  //6 - GOOD
	    dir_in = "MC_2016_Oct19/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTZToLL_M-1to10/191009_141309/";
  	    nfiles = 5;
	    year = 2016; 
	    type = "ttV";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_TTWJetsToLNu" ) {  //7
	    dir_in = "MC_2016_Oct19/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2016_TTWJetsToLNu/191009_141358/";
  	    nfiles = 31;
	    year = 2016; 
	    type = "ttV";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_TTWW" ) {  //8 - GOOD
	    dir_in = "MC_2016_Oct19/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/Oct19v1_MC_2016_TTWW/191009_141444/";
  	    nfiles = 22;
	    year = 2016; 
	    type = "ttV";
	    isMC = true;
    }

    // TT 
    else if( sample = "Oct19v1_MC_2016_ST_s-channel" ) {  //9 - GOOD
	    dir_in = "MC_2016_Oct19/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/Oct19v1_MC_2016_ST_s-channel/191009_141535/";
  	    nfiles = 8;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ST_s-channel_PS" ) {  //10 - GOOD
	    dir_in = "MC_2016_Oct19/ST_s-channel_4f_leptonDecays_13TeV_PSweights-amcatnlo-pythia8/Oct19v1_MC_2016_ST_s-channel_PS/191009_141622/";
  	    nfiles = 228;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ST_t-channel_top" ) {  //11 - GOOD
	    dir_in = "MC_2016_Oct19/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/Oct19v1_MC_2016_ST_t-channel_top/191009_141712/";
  	    nfiles = 499;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ST_t-channel_antitop" ) {  //12 - GOOD
	    dir_in = "MC_2016_Oct19/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/Oct19v1_MC_2016_ST_t-channel_antitop/191009_141806/";
  	    nfiles = 298;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_ST_t-channel_antitop_PS" ) {  //13
	    dir_in = "MC_2016_Oct19/ST_t-channel_antitop_4f_inclusiveDecays_13TeV_PSweights-powhegV2-madspin/Oct19v1_MC_2016_ST_t-channel_antitop_PS/191009_141852/";
  	    nfiles = 532;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_ST_tW_top" ) {  //14
	    dir_in = "MC_2016_Oct19/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/Oct19v1_MC_2016_ST_tW_top/191009_141940/";
  	    nfiles = 60;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_ST_tW_antitop" ) {  //15
	    dir_in = "MC_2016_Oct19/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/Oct19v1_MC_2016_ST_tW_top/191009_141940/";
  	    nfiles = 58;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_ST_tWll" ) {  //16 ---> GOOD (CHECK)
	    dir_in = "MC_2016_Oct19/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/Oct19v1_MC_2016_ST_tWll/191009_142117/";
  	    nfiles = 1;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_TTJets_DiLept_ext1" ) {  //17 ---> GOOD (CHECK)
	    dir_in = "MC_2016_Oct19/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTJets_DiLept_ext1/191009_142203/";
  	    nfiles = 208;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_TTJets_DiLept" ) {  //18 - GOOD
	    dir_in = "MC_2016_Oct19/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTJets_DiLept/191009_142254/";
  	    nfiles = 48;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_TTJets_SingleLeptFromT_ext1" ) {  //19
	    dir_in = "MC_2016_Oct19/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTJets_SingleLeptFromT_ext1/191009_142341/";
  	    nfiles = 407;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_TTJets_SingleLeptFromT" ) {  //20 - GOOD
	    dir_in = "MC_2016_Oct19/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTJets_SingleLeptFromT/191009_142430/";
  	    nfiles = 97;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_TTJets_SingleLeptFromTbar" ) {  //21 - GOOD
	    dir_in = "MC_2016_Oct19/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTJets_SingleLeptFromTbar/191009_142516/";
  	    nfiles = 112;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_ext1" ) {  //22
	    dir_in = "MC_2016_Oct19/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_ext1/191009_142605/";
  	    nfiles = 366;
	    year = 2016; 
	    type = "ttbar";
	    isMC = true;
    }*/

    // ggH
    else if( sample = "Oct19v1_MC_2016_GluGluHToTauTau" ) {  //23 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2016_GluGluHToTauTau/191009_142656/";
  	    nfiles = 78;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluHToZZTo4L" ) {  //24 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/Oct19v1_MC_2016_GluGluHToZZTo4L/191009_142743/";
  	    nfiles = 9;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluHToWWToLNuQQ" ) {  //25 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8/Oct19v1_MC_2016_GluGluHToWWToLNuQQ/191009_142829/";
  	    nfiles = 22;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluHToWWTo2L2Nu" ) {  //26 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/Oct19v1_MC_2016_GluGluHToWWTo2L2Nu/191009_142916/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluHToMuMu" ) {  //27 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/Oct19v1_MC_2016_GluGluHToMuMu/191009_143004/";
  	    nfiles = 34;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluHToBB" ) {  //28 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/Oct19v1_MC_2016_GluGluHToBB/191009_143054/";
  	    nfiles = 7;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_GluGluHToBB_ext1" ) {  //29
	    dir_in = "MC_2016_Oct19/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/Oct19v1_MC_2016_GluGluHToBB_ext1/191009_143141/";
  	    nfiles = 31;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluHToGG" ) {  //30 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/Oct19v1_MC_2016_GluGluHToGG/191009_143232/";
  	    nfiles = 7;
	    year = 2016; 
	    type = "ggH";
	    isMC = true;
    }

    // qqH 
    /*else if( sample = "Oct19v1_MC_2016_VBFHToTauTau" ) {  //31
	    dir_in = // ---> CHECK???
  	    nfiles = 15;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_VBF_HToZZTo4L" ) {  //32
	    dir_in = "MC_2016_Oct19/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/Oct19v1_MC_2016_VBF_HToZZTo4L/191009_143423/";
  	    nfiles = 6;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_VBFHToWWToLNuQQ" ) {  //33 - GOOD
	    dir_in = "MC_2016_Oct19/VBFHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8/Oct19v1_MC_2016_VBFHToWWToLNuQQ/191009_143512/";
  	    nfiles = 31;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_VBFHToWWTo2L2Nu" ) {  //34 - GOOD
	    dir_in = "MC_2016_Oct19/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8/Oct19v1_MC_2016_VBFHToWWTo2L2Nu/191009_143602/";
  	    nfiles = 1;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_VBFHToMuMu" ) {  //35 - GOOD
	    dir_in = "MC_2016_Oct19/VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/Oct19v1_MC_2016_VBFHToMuMu/191009_143653/";
  	    nfiles = 25;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2016_VBFHToBB" ) {  //36 
	    dir_in = // ---> CHECK???
  	    nfiles = // ---> CHECK???
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_VBFHToBB_ext1" ) {  //37 - GOOD
	    dir_in = "MC_2016_Oct19/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/Oct19v1_MC_2016_VBFHToBB_ext1/191009_152510/";
  	    nfiles = 36;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_VBFHToGG_ext1" ) {  //38 - GOOD
	    dir_in = "MC_2016_Oct19/VBFHToGG_M125_13TeV_amcatnlo_pythia8/Oct19v1_MC_2016_VBFHToGG_ext1/191009_152604/";
  	    nfiles = 14;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_VBFHToGG_ext2" ) {  //39 - GOOD
	    dir_in = "MC_2016_Oct19/VBFHToGG_M125_13TeV_amcatnlo_pythia8/Oct19v1_MC_2016_VBFHToGG_ext2/191009_152719/";
  	    nfiles = 12;
	    year = 2016; 
	    type = "qqH";
	    isMC = true;
    }

    // Rares
    else if( sample = "Oct19v1_MC_2016_WWW" ) {  //40 - GOOD
	    dir_in = "MC_2016_Oct19/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_WWW/191009_152840/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WWZ" ) {  //41 - GOOD
	    dir_in = "MC_2016_Oct19/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_WWZ/191009_153008/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WZZ" ) {  //42 - GOOD
	    dir_in = "MC_2016_Oct19/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_WZZ/191009_153115/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ZZZ" ) {  //43 - GOOD
	    dir_in = "MC_2016_Oct19/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_ZZZ/191009_153210/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WZG" ) {  //44 - GOOD
	    dir_in = "MC_2016_Oct19/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_WZG/191009_153259/";
  	    nfiles = 8;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WGToLNuG_ext1" ) {  //45 - GOOD
	    dir_in = "MC_2016_Oct19/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2016_WGToLNuG_ext1/191009_153400/";
  	    nfiles = 45;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WGToLNuG_ext2" ) {  //46 - GOOD
	    dir_in = "MC_2016_Oct19/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2016_WGToLNuG_ext2/191009_153515/";
  	    nfiles = 73;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_WGToLNuG_ext3" ) {  //47
	    dir_in = "MC_2016_Oct19/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2016_WGToLNuG_ext3/191009_153616/";
  	    nfiles = 90;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_ZGTo2LG" ) {  //48 - GOOD
	    dir_in = "MC_2016_Oct19/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2016_ZGTo2LG/191009_153707/";
  	    nfiles = 106;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_TGJets_leptonDecays" ) {  //49 - GOOD
	    dir_in = "MC_2016_Oct19/TGJets_leptonDecays_13TeV_amcatnlo_madspin_pythia8/Oct19v1_MC_2016_TGJets_leptonDecays/191009_153757/";
  	    nfiles = 62;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_TTGJets" ) {  //50 - GOOD
	    dir_in = "MC_2016_Oct19/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2016_TTGJets/191009_153847/";
  	    nfiles = 42;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_TTGJets_ext1" ) {  //51 - GOOD
	    dir_in = "MC_2016_Oct19/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2016_TTGJets_ext1/191009_153947/";
  	    nfiles = 83;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_tZq_ll" ) {  //52
	    dir_in = "MC_2016_Oct19/tZq_ll_4f_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_tZq_ll/191009_154042/";
  	    nfiles = 117;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_tZq_ll_PS" ) {  //53
	    dir_in = "MC_2016_Oct19/tZq_ll_4f_PSweights_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_tZq_ll_PS/191009_154129/";
  	    nfiles = 268;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_WpWpJJ" ) {  //54 - GOOD
	    dir_in = "MC_2016_Oct19/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/Oct19v1_MC_2016_WpWpJJ/191009_154223/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_WWTo2L2Nu_DoubleScattering" ) {  //55 
	    dir_in = "MC_2016_Oct19/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/Oct19v1_MC_2016_WWTo2L2Nu_DoubleScattering/191009_154318/";
  	    nfiles = 8;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_TTTT" ) {  //56 - GOOD
	    dir_in = "MC_2016_Oct19/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/Oct19v1_MC_2016_TTTT/191009_154408/";
  	    nfiles = 6;
	    year = 2016; 
	    type = "Rares";
	    isMC = true;
    }

    // VH
    else if( sample = "Oct19v1_MC_2016_VHToNonbb" ) {  //57 - GOOD
	    dir_in = "MC_2016_Oct19/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/Oct19v1_MC_2016_VHToNonbb/191009_154457/";
  	    nfiles = 10;
	    year = 2016; 
	    type = "VH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ZH_HToBB_ZToLL" ) {  //58 - GOOD
	    dir_in = "MC_2016_Oct19/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/Oct19v1_MC_2016_ZH_HToBB_ZToLL/191009_154550/";
  	    nfiles = 28;
	    year = 2016; 
	    type = "VH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ZHToTauTau" ) {  //59 - GOOD
	    dir_in = "MC_2016_Oct19/ZHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2016_ZHToTauTau/191009_154642/";
  	    nfiles = 7;
	    year = 2016; 
	    type = "VH";
	    isMC = true;
    }

    // EWK
    /*else if( sample = "Oct19v1_MC_2016_DYJetsToLL_M-10to50" ) {  //60
	    dir_in = "MC_2016_Oct19/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_DYJetsToLL_M-10to50/191009_154739/";
  	    nfiles = 264;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_DYJetsToLL_M-50" ) {  //61 - GOOD
	    dir_in = "MC_2016_Oct19/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2016_DYJetsToLL_M-50/191009_154833/";
  	    nfiles = 871;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_WJetsToLNu_ext2" ) {  //62
	    dir_in = "MC_2016_Oct19/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_WJetsToLNu_ext2/191009_154925/";
  	    nfiles = 410;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_WJetsToLNu" ) {  //63 - GOOD
	    dir_in = "MC_2016_Oct19/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2016_WJetsToLNu/191009_155019/";
  	    nfiles = 215;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WWTo2L2Nu" ) {  //64 - GOOD
	    dir_in = "MC_2016_Oct19/WWTo2L2Nu_13TeV-powheg/Oct19v1_MC_2016_WWTo2L2Nu/191009_155118/";
  	    nfiles = 16;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_WZTo3LNu" ) {  //65 - GOOD
	    dir_in = "MC_2016_Oct19/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2016_WZTo3LNu/191009_155209/";
  	    nfiles = 91;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_ZZTo4L" ) {  //66 - GOOD
	    dir_in = "MC_2016_Oct19/ZZTo4L_13TeV_powheg_pythia8/Oct19v1_MC_2016_ZZTo4L/191009_155257/";
  	    nfiles = 50;
	    year = 2016; 
	    type = "EWK";
	    isMC = true;
    }

    // TTVH
    else if( sample = "Oct19v1_MC_2016_TTWH" ) {  //67 - GOOD
	    dir_in = "MC_2016_Oct19/TTWH_TuneCUETP8M2T4_13TeV-madgraph-pythia8/Oct19v1_MC_2016_TTWH/191009_155349/";
  	    nfiles = 19;
	    year = 2016; 
	    type = "ttVH";
	    isMC = true;
    }
    else if( sample = "Oct19v2_MC_2016_TTZH" ) {  //68 - GOOD
	    dir_in = "MC_2016_Oct19/TTZH_TuneCUETP8M2T4_13TeV-madgraph-pythia8/Oct19v2_MC_2016_TTZH/191015_122154/";
  	    nfiles = 25;
	    year = 2016; 
	    type = "ttVH";
	    isMC = true;
    }

    // HH
    /*else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM" ) {  //69
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_SM_13TeV-madgraph-v2/Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM/191015_122240/";
  	    nfiles = 5;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box" ) {  //70 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_box_13TeV-madgraph-v2/Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box/191015_122330/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_1" ) {  //71
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_10_13TeV-madgraph-v2/Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10/191009_160433/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2" ) {  //72 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_2_13TeV-madgraph-v2/Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2/191009_155803/";
  	    nfiles = 1;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3" ) {  //73 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_3_13TeV-madgraph-v2/Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3/191009_155853/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_4" ) {  //74
	    dir_in = // ---> CHECK!
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_5" ) {  //75
	    dir_in = // ---> CHECK!
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6" ) {  //76 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_6_13TeV-madgraph-v2/Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6/191015_122604/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_7" ) {  //77
	    dir_in = // ---> CHECK!
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8" ) {  //78
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_8_13TeV-madgraph-v2/Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8/191015_122742/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9" ) {  //79
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_9_13TeV-madgraph-v2/Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9/191015_122828/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10" ) {  //80
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_10_13TeV-madgraph-v2/Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10/191009_160433/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_11" ) {  //81
	    dir_in = // ---> CHECK!
  	    nfiles = 5;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12" ) {  //82 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_12_13TeV-madgraph-v2/Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12/191009_160618/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM" ) {  //83 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_SM_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM/191009_160705/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box" ) {  //84 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_box_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box/191009_160754/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2" ) {  //85 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_2_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2/191009_160840/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2016_GluGluToHHTo2B2Tau_node_9" ) {  //86
	    dir_in = // ---> CHECK!
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10" ) {  //87 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_10_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10/191009_161018/";
  	    nfiles = 4;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11" ) {  //88 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_11_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11/191009_161109/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12" ) {  //89 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_12_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12/191009_161205/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_13" ) {  //90
	    dir_in = "MC_2016_Oct19/GluGluToHHTo2B2Tau_node_13_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_13/191009_161253/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM" ) {  //91 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_SM_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM/191009_161344/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box" ) {  //92 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_box_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box/191009_161432/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2" ) {  //93 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_2_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2/191009_161519/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3" ) {  //94 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_3_13TeV-madgraph/Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3/191015_123150/";
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4" ) {  //95 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_4_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4/191009_161700/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5" ) {  //96 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_5_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5/191009_161751/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6" ) {  //97 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_6_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6/191009_161845/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7" ) {  //98 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_7_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7/191009_161934/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_8" ) {  //99
	    dir_in = // --> CHECK!
  	    nfiles = 3;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9" ) {  //100 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_9_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9/191009_162115/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_10" ) {  //101
	    dir_in = // --> CHECK!
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_11" ) {  //102
	    dir_in = // --> CHECK!
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12" ) {  //103 - GOOD
	    dir_in = "MC_2016_Oct19/GluGluToHHTo4Tau_node_12_13TeV-madgraph/Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12/191009_162351/";
  	    nfiles = 2;
	    year = 2016; 
	    type = "HH";
	    isMC = true;
    }

  
    /////////////////
    //// 2017 MC ////
    /////////////////

    // t(t)H
    else if( sample = "Oct19v1_MC_2017_ttHJetToNonbb" ) {  //0 - GOOD
	    dir_in = "MC_2017_Oct19/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/Oct19v1_MC_2017_ttHJetToNonbb/191009_172456/";
  	    nfiles = 208;
	    year = 2017; 
	    type = "ttH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_THQ_ctcvcp" ) {  //1 - GOOD
	    dir_in = "MC_2017_Oct19/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/Oct19v1_MC_2017_THQ_ctcvcp/191009_172547/";
  	    nfiles = 258;
	    year = 2017; 
	    type = "ttH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_THW_ctcvcp" ) {  //2
	    dir_in = "MC_2017_Oct19/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/Oct19v1_MC_2017_THW_ctcvcp/191009_172635/";
  	    nfiles = 172;
	    year = 2017; 
	    type = "ttH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_TTH_ctcvcp" ) {  //3 - GOOD
	    dir_in = "MC_2017_Oct19/TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/Oct19v1_MC_2017_TTH_ctcvcp/191009_172723/";
  	    nfiles = 257;
	    year = 2017; 
	    type = "ttH";
	    isMC = true;
    }

    // TTV
    else if( sample = "Oct19v1_MC_2017_TTZToLLNuNu_M-10" ) {  //4 - GOOD
	    dir_in = "MC_2017_Oct19/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_TTZToLLNuNu_M-10/191009_172812/";
  	    nfiles = 150;
	    year = 2017; 
	    type = "ttV";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS" ) {  //5
	    dir_in = "MC_2017_Oct19/TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS/191009_172858/";
  	    nfiles = 300;
	    year = 2017; 
	    type = "ttV";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_TTZToLL_M-1to10" ) {  //6 - GOOD
	    dir_in = "MC_2017_Oct19/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_TTZToLL_M-1to10/191009_172945/";
  	    nfiles = 6;
	    year = 2017; 
	    type = "ttV";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_TTWJetsToLNu" ) {  //7 - GOOD
	    dir_in = "MC_2017_Oct19/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2017_TTWJetsToLNu/191009_173041/";
  	    nfiles = 95;
	    year = 2017; 
	    type = "ttV";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_TTWJetsToLNu_PS" ) {  //8
	    dir_in = "MC_2017_Oct19/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2017_TTWJetsToLNu_PS/191009_173130/";
  	    nfiles = 122;
	    year = 2017; 
	    type = "ttV";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_TTWW" ) {  //9 - GOOD
	    dir_in = "MC_2017_Oct19/TTWW_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2017_TTWW/191009_173216/";
  	    nfiles = 5;
	    year = 2017; 
	    type = "ttV";
	    isMC = true;
    }

    // TT
    /*else if( sample = "Oct19v1_MC_2017_ST_s-channel" ) {  //10
	    dir_in = "MC_2017_Oct19/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_ST_s-channel/";
  	    nfiles = 143;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2017_ST_s-channel_PS" ) {  //11
	    dir_in = // --> CHECK!
  	    nfiles = // --> CHECK!
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_ST_t-channel_top" ) {  //12 - GOOD
	    dir_in = "MC_2017_Oct19/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/Oct19v1_MC_2017_ST_t-channel_top/191009_183430/";
  	    nfiles = 93;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_ST_t-channel_top_PS" ) {  //13
	    dir_in = "MC_2017_Oct19/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/Oct19v1_MC_2017_ST_t-channel_top_PS/191009_183519/";
  	    nfiles = 2354;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_ST_t-channel_antitop" ) {  //14 - GOOD
	    dir_in = "MC_2017_Oct19/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/Oct19v1_MC_2017_ST_t-channel_antitop/191009_183608/";
  	    nfiles = 69;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_ST_t-channel_antitop_PS" ) {  //15
	    dir_in = "MC_2017_Oct19/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/Oct19v1_MC_2017_ST_t-channel_top_PS/191009_183519/";
  	    nfiles = 1288;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2017_ST_tW_top" ) {  //16 
	    dir_in = // --> CHECK!
  	    nfiles = // --> CHECK!
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_ST_tW_top_PS" ) {  //17
	    dir_in = "MC_2017_Oct19/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/Oct19v1_MC_2017_ST_tW_top_PS/191009_183833/";
  	    nfiles = 114;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_ST_tW_antitop" ) {  //18
	    dir_in = "MC_2017_Oct19/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Oct19v1_MC_2017_ST_tW_antitop/191009_183927/";
  	    nfiles = 134;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_ST_tW_antitop_PS" ) {  //19
	    dir_in = "MC_2017_Oct19/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/Oct19v1_MC_2017_ST_tW_antitop_PS/191009_184013/";
  	    nfiles = 150;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_ST_tWll" ) {  //20 - GOOD
	    dir_in = "MC_2017_Oct19/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/Oct19v1_MC_2017_ST_tWll/191009_184100/";
  	    nfiles = 42;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_TTJets_DiLept" ) {  //21 - GOOD
	    dir_in = "MC_2017_Oct19/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_TTJets_DiLept/191009_184146/";
  	    nfiles = 602;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_TTJets_SingleLeptFromT" ) {  //22
	    dir_in = "MC_2017_Oct19/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_TTJets_SingleLeptFromT/191009_184234/";
  	    nfiles = 1052;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_TTJets_SingleLeptFromTbar" ) {  //23
	    dir_in = "MC_2017_Oct19/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_TTJets_SingleLeptFromTbar/191009_184319/";
  	    nfiles = 1306;
	    year = 2017; 
	    type = "ttbar";
	    isMC = true;
    }*/

    // ggH
    else if( sample = "Oct19v1_MC_2017_GluGluHToTauTau" ) {  //24 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2017_GluGluHToTauTau/191009_184407/";
  	    nfiles = 35;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluHToTauTau_ext1" ) {  //25
	    dir_in = // --> CHECK!
  	    nfiles = 169;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluHToZZTo4L_ext1" ) {  //26 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/Oct19v1_MC_2017_GluGluHToZZTo4L_ext1/191009_184540/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluHToZZTo4L_ext3" ) {  //27
	    dir_in = // --> CHECK!
  	    nfiles = 50;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluHToZZTo4L_ext4" ) {  //28 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/Oct19v1_MC_2017_GluGluHToZZTo4L_ext4/191009_184724/";
  	    nfiles = 45;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluHToZZTo2L2Q" ) {  //29
	    dir_in = // --> CHECK!
  	    nfiles = 48;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluHToWWToLNuQQ" ) {  //30 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluHToWWToLNuQQ_M125_NNPDF31_TuneCP5_PSweights_13TeV_powheg_JHUGen710_pythia8/Oct19v1_MC_2017_GluGluHToWWToLNuQQ/191009_184905/";
  	    nfiles = 19;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluHToWWTo2L2Nu" ) {  //31 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/Oct19v1_MC_2017_GluGluHToWWTo2L2Nu/191009_184953/";
  	    nfiles = 58;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluHToMuMu" ) {  //32
	    dir_in = // --> CHECK!
  	    nfiles = // --> CHECK!
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluHToMuMu_ext1" ) {  //33 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/Oct19v1_MC_2017_GluGluHToMuMu_ext1/191009_185129/";
  	    nfiles = 53;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluHToBB" ) {  //34
	    dir_in = "MC_2017_Oct19/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/Oct19v1_MC_2017_GluGluHToBB/191009_185226/";
  	    nfiles = 200;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2017_GluGluHToGG" ) {  //35
	    dir_in = "MC_2017_Oct19/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/Oct19v1_MC_2017_GluGluHToGG/191009_185316/";
  	    nfiles = 61;
	    year = 2017; 
	    type = "ggH";
	    isMC = true;
    }*/

    // qqH
    else if( sample = "Oct19v1_MC_2017_VBFHToTauTau" ) {  //36 - GOOD
	    dir_in = "MC_2017_Oct19/VBFHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2017_VBFHToTauTau/191009_185405/";
  	    nfiles = 39;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_VBF_HToZZTo4L_ext2" ) {  //37
	    dir_in = // --> CHECK!
  	    nfiles = 29;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_VBF_HToZZTo4L_ext1" ) {  //38 - GOOD
	    dir_in = "MC_2017_Oct19/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/Oct19v1_MC_2017_VBF_HToZZTo4L_ext1/191009_185540/";
  	    nfiles = 19;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_VBF_HToZZTo4L" ) {  //39 - GOOD
	    dir_in = "MC_2017_Oct19/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/Oct19v1_MC_2017_VBF_HToZZTo4L/191009_185630/";
  	    nfiles = 36;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_VBFHToWWToLNuQQ" ) {  //40
	    dir_in = "MC_2017_Oct19/VBFHToWWToLNuQQ_M125_NNPDF31_TuneCP5_PSweights_13TeV_powheg_JHUGen710_pythia8/Oct19v1_MC_2017_VBFHToWWToLNuQQ/191009_185718/";
  	    nfiles = 30;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_VBFHToWWTo2L2Nu" ) {  //41 - GOOD
	    dir_in = "MC_2017_Oct19/VBFHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/Oct19v1_MC_2017_VBFHToWWTo2L2Nu/191009_185807/";
  	    nfiles = 32;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_VBFHToMuMu" ) {  //42
	    dir_in = "MC_2017_Oct19/VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/Oct19v1_MC_2017_VBFHToMuMu/191009_185901/";
  	    nfiles = 69;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_VBFHToBB" ) {  //43 - GOOD
	    dir_in = "MC_2017_Oct19/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/Oct19v1_MC_2017_VBFHToBB/191009_185947/";
  	    nfiles = 69;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_VBFHToGG" ) {  //44
	    dir_in = "MC_2017_Oct19/VBFHToGG_M125_13TeV_amcatnlo_pythia8/Oct19v1_MC_2017_VBFHToGG/191009_190037/";
  	    nfiles = 28;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_VBFHToGG_PS" ) {  //45 ---> no info from crab???
	    dir_in = "MC_2017_Oct19/VBFHToGG_M125_13TeV_amcatnlo_pythia8_PSWeights/Oct19v1_MC_2017_VBFHToGG_PS/191009_190130/";
  	    nfiles = 16;
	    year = 2017; 
	    type = "qqH";
	    isMC = true;
    }*/

    // Rares
    else if( sample = "Oct19v1_MC_2017_WWW" ) {  //46 - GOOD
	    dir_in = "MC_2017_Oct19/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8//Oct19v1_MC_2017_WWW/191009_190226/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_WWZ" ) {  //47
	    dir_in = "MC_2017_Oct19/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_WWZ/191009_190324/";
  	    nfiles = 24;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_WZZ" ) {  //48
	    dir_in = // --> CHECK!
  	    nfiles = 5;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_ZZZ" ) {  //49 ---> CHECK
	    dir_in = "MC_2017_Oct19/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_ZZZ/191009_190507/";
  	    nfiles = 22;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_WZG" ) {  //50 - GOOD
	    dir_in = "MC_2017_Oct19/WZG_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_WZG/191009_190558/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_WGToLNuG" ) {  //51
	    dir_in = // --> CHECK!
  	    nfiles = 134;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_ZGToLLG" ) {  //52
	    dir_in = "MC_2017_Oct19/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2017_ZGToLLG/191009_190740/";
  	    nfiles = 526;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_TGJets" ) {  //53 - GOOD
	    dir_in = "MC_2017_Oct19/TGJets_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_TGJets/191009_190834/";
  	    nfiles = 110;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_TTGJets" ) {  //54 - GOOD
	    dir_in = "MC_2017_Oct19/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2017_TTGJets/191009_190931/";
  	    nfiles = 193;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_TTGJets_ext1" ) {  //55 - GOOD
	    dir_in = "MC_2017_Oct19/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2017_TTGJets_ext1/191009_191020/";
  	    nfiles = 239;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_tZq_ll" ) {  //56 - GOOD
	    dir_in = "MC_2017_Oct19/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_tZq_ll/191009_191110/";
  	    nfiles = 211;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_WpWpJJ" ) {  //57 ---> CHECK
	    dir_in = "MC_2017_Oct19/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2017_WpWpJJ/191009_191200/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering" ) {  //58
	    dir_in = "MC_2017_Oct19/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering/191009_191250/";
  	    nfiles = 31;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_TTTT" ) {  //59 - GOOD
	    dir_in = "/MC_2017_Oct19/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_TTTT/191009_191337/";
  	    nfiles = 31;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_TTTT_PS" ) {  //60 - GOOD
	    dir_in = "MC_2017_Oct19/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/Oct19v1_MC_2017_TTTT_PS/191009_191425/";
  	    nfiles = 71;
	    year = 2017; 
	    type = "Rares";
	    isMC = true;
    }

    // VH
    else if( sample = "Oct19v1_MC_2017_VHToNonbb" ) {  //61 - GOOD
	    dir_in = "MC_2017_Oct19/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/Oct19v1_MC_2017_VHToNonbb/191009_191523/";
  	    nfiles = 35;
	    year = 2017; 
	    type = "VH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_ZH_HToBB_ZToLL" ) {  //62
	    dir_in = "MC_2017_Oct19/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/Oct19v1_MC_2017_ZH_HToBB_ZToLL/191009_191614/";
  	    nfiles = 75;
	    year = 2017; 
	    type = "VH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_ZHToTauTau" ) {  //63
	    dir_in = "MC_2017_Oct19/ZHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2017_ZHToTauTau/191009_191702/";
  	    nfiles = 75;
	    year = 2017; 
	    type = "VH";
	    isMC = true;
    }*/

    // EWK
    else if( sample = "Oct19v1_MC_2017_DYJetsToLL_M-10to50" ) {  //64 - GOOD
	    dir_in = "MC_2017_Oct19/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_DYJetsToLL_M-10to50/191009_191758/";
  	    nfiles = 477;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1" ) {  //65
	    dir_in = "MC_2017_Oct19/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1/191009_191851/";
  	    nfiles = 480;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_DYJetsToLL_M-50" ) {  //66
	    dir_in = "MC_2017_Oct19/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2017_DYJetsToLL_M-50/191009_191943/";
  	    nfiles = 324;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_DYJetsToLL_M-50_ext1" ) {  //67
	    dir_in = "MC_2017_Oct19/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2017_DYJetsToLL_M-50_ext1/191009_192043/";
  	    nfiles = 2005;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_WJetsToLNu" ) {  //68
	    dir_in = "MC_2017_Oct19/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_WJetsToLNu/191009_192134/";
  	    nfiles = 490;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_WJetsToLNu_ext1" ) {  //69 - GOOD
	    dir_in = "MC_2017_Oct19/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2017_WJetsToLNu_ext1/191009_192226/";
  	    nfiles = 738;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_WWTo2L2Nu" ) {  //70
	    dir_in = "MC_2017_Oct19/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/Oct19v1_MC_2017_WWTo2L2Nu/191009_192320/";
  	    nfiles = 25;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_WWTo2L2Nu_ext1" ) {  //71 - GOOD
	    dir_in = "MC_2017_Oct19/WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/Oct19v1_MC_2017_WWTo2L2Nu_ext1/191009_192409/";
  	    nfiles = 25;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_WZTo3LNu" ) {  //72 - GOOD
	    dir_in = "MC_2017_Oct19/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2017_WZTo3LNu/191009_192503/";
  	    nfiles = 131;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_ZZTo4L" ) {  //73 - GOOD
	    dir_in = "MC_2017_Oct19/ZZTo4L_13TeV_powheg_pythia8/Oct19v1_MC_2017_ZZTo4L/191009_192553/";
  	    nfiles = 80;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_ZZTo4L_ext1" ) {  //74 - GOOD
	    dir_in = "MC_2017_Oct19/ZZTo4L_13TeV_powheg_pythia8/Oct19v1_MC_2017_ZZTo4L_ext1/191009_192648/";
  	    nfiles = 1128;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_ZZTo4L_ext2" ) {  //75
	    dir_in = "MC_2017_Oct19/ZZTo4L_13TeV_powheg_pythia8/Oct19v1_MC_2017_ZZTo4L_ext2/191009_192736/";
  	    nfiles = 1623;
	    year = 2017; 
	    type = "EWK";
	    isMC = true;
    }*/

    // TTVH
    /*else if( sample = "Oct19v1_MC_2017_TTWH" ) {  //76
	    dir_in = // --> CHECK!
  	    nfiles = 5;
	    year = 2017; 
	    type = "ttVH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_TTZH" ) {  //77 - GOOD
	    dir_in = "MC_2017_Oct19/TTZH_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2017_TTZH/191009_192924/";
  	    nfiles = 7;
	    year = 2017; 
	    type = "ttVH";
	    isMC = true;
    }

    // HH
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM" ) {  //78
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_SM_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM/191009_193014/";
  	    nfiles = 17;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2" ) {  //79
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_2_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2/191009_193107/";
  	    nfiles = 17;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3" ) {  //80
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_3_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3/191009_193156/";
  	    nfiles = 17;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_7" ) {  //81
	    dir_in = // --> CHECK!
  	    nfiles = 19;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9" ) {  //82
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_9_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9/191009_193341/";
  	    nfiles = 19;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12" ) {  //83
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2VTo2L2Nu_node_12_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12/191009_193429/";
  	    nfiles = 23;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM" ) {  //84 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_SM_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM/191009_193521/";
  	    nfiles = 18;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2" ) {  //85 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_2_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2/191009_193613/";
  	    nfiles = 14;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3" ) {  //86 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_3_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3/191009_193707/";
  	    nfiles = 22;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4" ) {  //87 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_4_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4/191009_193754/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7" ) {  //88 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_7_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7/191009_193843/";
  	    nfiles = 16;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9" ) {  //89 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_9_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9/191010_073118/";
  	    nfiles = 18;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12" ) {  //90 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2B2Tau_node_12_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12/191009_194021/";
  	    nfiles = 10;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13" ) {  //91 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4Tau_node_SM_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13/191009_194113/";
  	    nfiles = 15;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2" ) {  //92 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4Tau_node_2_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2/191009_194210/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3" ) {  //93 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4Tau_node_3_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3/191009_194305/";
  	    nfiles = 23;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4Tau_node_7" ) {  //94
	    dir_in = // --> CHECK!
  	    nfiles = 16;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9" ) {  //95 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4Tau_node_9_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9/191009_194453/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12" ) {  //96
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4Tau_node_12_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12/191009_194544/";
  	    nfiles = 16;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_SM" ) {  //97
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_SM_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_SM/191009_194633/";
  	    nfiles = 15;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2" ) {  //98 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_2_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2/191009_194726/";
  	    nfiles = 19;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_3" ) {  //99
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_3_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_3/191009_194823/";
  	    nfiles = 14;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4" ) {  //100 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_4_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4/191009_194913/";
  	    nfiles = 13;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5" ) {  //101 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_5_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5/191009_195001/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6" ) {  //102 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_6_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6/191009_195057/";
  	    nfiles = 18;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_7" ) {  //103
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_7_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_7/191009_195144/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8" ) {  //104 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_8_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8/191009_195240/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9" ) {  //105 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_9_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9/191009_195329/";
  	    nfiles = 12;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10" ) {  //106
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_10_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10/191009_195422/";
  	    nfiles = 18;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11" ) {  //107 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_11_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11/191009_195518/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_12" ) {  //108
	    dir_in = "MC_2017_Oct19/GluGluToHHTo2V2Tau_node_12_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_12/191009_195610/";
  	    nfiles = 20;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_SM" ) {  //109 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_SM_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_SM/191009_195700/";
  	    nfiles = 17;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_2" ) {  //110
	    dir_in = // --> CHECK!
  	    nfiles = 15;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_3" ) {  //111
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_3_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_3/191009_195842/";
  	    nfiles = 22;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_4" ) {  //112 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_4_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_4/191009_195934/";
  	    nfiles = 22;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_5" ) {  //113 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_5_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_5/191009_200029/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_6" ) {  //114 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_6_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_6/191009_200125/";
  	    nfiles = 16;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_7" ) {  //115 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_7_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_7/191009_200214/";
  	    nfiles = 21;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_8" ) {  //116 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_8_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_8/191009_200307/";
  	    nfiles = 17;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_9" ) {  //117 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_9_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_9/191009_200416/";
  	    nfiles = 23;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_10" ) {  //118 - GOOD
	    dir_in = "MC_2017_Oct19/GluGluToHHTo4V_node_10_13TeV-madgraph_correctedcfg/Oct19v1_MC_2017_GluGluToHHTo4V_node_10/191009_200519/";
  	    nfiles = 18;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_11" ) {  //119
	    dir_in = // --> CHECK!
  	    nfiles = 17;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2017_GluGluToHHTo4V_node_12" ) {  //120
	    dir_in = // --> CHECK!
  	    nfiles = 13;
	    year = 2017; 
	    type = "HH";
	    isMC = true;
    }*/

  
    /////////////////
    //// 2018 MC ////
    /////////////////

    // t(t)H
    /*else if( sample = "Oct19v1_MC_2018_ttHJetToNonbb" ) {  //0
	    dir_in = "MC_2018_Oct19/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/Oct19v1_MC_2018_ttHJetToNonbb/191009_201155/";
  	    nfiles = 261;
	    year = 2018; 
	    type = "ttH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_THQ_ctcvcp" ) {  //1 - GOOD
	    dir_in = "MC_2018_Oct19/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/Oct19v1_MC_2018_THQ_ctcvcp/191009_201243/";
  	    nfiles = 793;
	    year = 2018; 
	    type = "ttH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_THW_ctcvcp" ) {  //2 - GOOD
	    dir_in = "MC_2018_Oct19/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/Oct19v1_MC_2018_THW_ctcvcp/191009_201335/";
  	    nfiles = 436;
	    year = 2018; 
	    type = "ttH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2018_TTH_ctcvcp" ) {  //3
	    dir_in = "MC_2018_Oct19/TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/Oct19v1_MC_2018_TTH_ctcvcp/191009_201420/";
  	    nfiles = 720;
	    year = 2018; 
	    type = "ttH";
	    isMC = true;
    }*/

    // TTV
    else if( sample = "Oct19v1_MC_2018_TTZToLLNuNu_M-10" ) {  //4 - GOOD
	    dir_in = "MC_2018_Oct19/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_TTZToLLNuNu_M-10/191009_201508/";
  	    nfiles = 340;
	    year = 2018; 
	    type = "ttV";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_TTZToLL_M-1to10" ) {  //5 - GOOD
	    dir_in = "MC_2018_Oct19/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_TTZToLL_M-1to10/191009_201559/";
  	    nfiles = 19;
	    year = 2018; 
	    type = "ttV";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_TTWJetsToLNu" ) {  //6 - GOOD
	    dir_in = "MC_2018_Oct19/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2018_TTWJetsToLNu/191009_201652/";
  	    nfiles = 149;
	    year = 2018; 
	    type = "ttV";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_TTWW_ext1" ) {  //7 - GOOD
	    dir_in = "MC_2018_Oct19/TTWW_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_TTWW_ext1/191009_201741/";
  	    nfiles = 13;
	    year = 2018; 
	    type = "ttV";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_TTWW_ext2" ) {  //8 - GOOD
	    dir_in = "MC_2018_Oct19/TTWW_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_TTWW_ext2/191009_201835/";
  	    nfiles = 27;
	    year = 2018; 
	    type = "ttV";
	    isMC = true;
    }

    // TT
    else if( sample = "Oct19v1_MC_2018_ST_s-channel" ) {  //9 - GOOD
	    dir_in = "MC_2018_Oct19/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_ST_s-channel/191009_201925/";
  	    nfiles = 353;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2018_ST_t-channel_top" ) {  //10
	    dir_in = // --> CHECK!
  	    nfiles = 2395;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2018_ST_t-channel_antitop" ) {  //11
	    dir_in = "MC_2018_Oct19/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/Oct19v2_MC_2018_ST_t-channel_antitop/191015_124135/";
  	    nfiles = 1319;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_ST_tW_top" ) {  //12
	    dir_in = "MC_2018_Oct19/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Oct19v1_MC_2018_ST_tW_top/191009_202211/";
  	    nfiles = 173;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_ST_tW_antitop" ) {  //13 - GOOD
	    dir_in = "MC_2018_Oct19/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Oct19v1_MC_2018_ST_tW_antitop/191009_202314/";
  	    nfiles = 160;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_ST_tWll" ) {  //14 - GOOD
	    dir_in = "MC_2018_Oct19/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/Oct19v1_MC_2018_ST_tWll/191009_202404/";
  	    nfiles = 21;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2018_TTJets_DiLept" ) {  //15
	    dir_in = "MC_2018_Oct19/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2018_TTJets_DiLept/191009_202501/";
  	    nfiles = 841;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_TTJets_SingleLeptFromT" ) {  //16
	    dir_in = "MC_2018_Oct19/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2018_TTJets_SingleLeptFromT/191009_202559/";
  	    nfiles = 1505;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_TTJets_SingleLeptFromTbar" ) {  //17
	    dir_in = "MC_2018_Oct19/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2018_TTJets_SingleLeptFromTbar/191009_202704/";
  	    nfiles = 1540;
	    year = 2018; 
	    type = "ttbar";
	    isMC = true;
    }*/

    // ggH
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToTauTau" ) {  //18
	    dir_in = "MC_2018_Oct19/GluGluHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2018_GluGluHToTauTau/191009_202757/";
  	    nfiles = 188;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToZZTo4L" ) {  //19
	    dir_in = "MC_2018_Oct19/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/Oct19v1_MC_2018_GluGluHToZZTo4L/191009_202853/";
  	    nfiles = 30;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToZZTo2L2Q" ) {  //20
	    dir_in = // --> CHECK!
  	    nfiles = 30;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToWWToLNuQQ" ) {  //21
	    dir_in = "MC_2018_Oct19/GluGluHToWWToLNuQQ_M125_13TeV_powheg2_JHUGenV714_pythia8/Oct19v1_MC_2018_GluGluHToWWToLNuQQ/191009_203103/";
  	    nfiles = 26;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToWWTo2L2Nu" ) {  //22
	    dir_in = // --> CHECK!
  	    nfiles = 33;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_GluGluHToMuMu" ) {  //23 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/Oct19v1_MC_2018_GluGluHToMuMu/191009_203245/";
  	    nfiles = 16;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToMuMu_ext1" ) {  //24
	    dir_in = // --> CHECK!
  	    nfiles = 37;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_GluGluHToBB" ) {  //25
	    dir_in = "MC_2018_Oct19/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/Oct19v1_MC_2018_GluGluHToBB/191009_203505/";
  	    nfiles = 320;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_GluGluHToGG" ) {  //26 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluHToGG_M125_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2018_GluGluHToGG/191009_203559/";
  	    nfiles = 63;
	    year = 2018; 
	    type = "ggH";
	    isMC = true;
    }

    // qqH
    /*else if( sample = "Oct19v1_MC_2018_VBFHToTauTau" ) {  //27
	    dir_in = "MC_2018_Oct19/VBFHToTauTau_M125_13TeV_powheg_pythia8/Oct19v1_MC_2018_VBFHToTauTau/191009_203646/";
  	    nfiles = 72;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_VBF_HToZZTo4L" ) {  //28
	    dir_in = // --> CHECK!
  	    nfiles = 29;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_VBFHToWWToLNuQQ" ) {  //29
	    dir_in = // --> CHECK!
  	    nfiles = 24;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_VBFHToWWTo2L2Nu" ) {  //30 - GOOD
	    dir_in = "MC_2018_Oct19/VBFHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/Oct19v1_MC_2018_VBFHToWWTo2L2Nu/191009_203952/";
  	    nfiles = 34;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2018_VBFHToMuMu" ) {  //31
	    dir_in = // --> CHECK!
  	    nfiles = 38;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_VBFHToBB" ) {  //32
	    dir_in = // --> CHECK!
  	    nfiles = 207;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_VBFHToGG" ) {  //33
	    dir_in = // --> CHECK!
  	    nfiles = 44;
	    year = 2018; 
	    type = "qqH";
	    isMC = true;
    }*/

    // Rares
    /*else if( sample = "Oct19v1_MC_2018_WWW" ) {  //34
	    dir_in = "MC_2018_Oct19/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_WWW/191009_204407/";
  	    nfiles = 12;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_WWZ" ) {  //35
	    dir_in = // --> CHECK!
  	    nfiles = 15;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_WZZ" ) {  //36 - GOOD
	    dir_in = "MC_2018_Oct19/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_WZZ/191009_204546/";
  	    nfiles = 14;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_ZZZ" ) {  //37 - GOOD
	    dir_in = "MC_2018_Oct19/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_ZZZ/191009_204650/";
  	    nfiles = 14;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_WZG" ) {  //38 - GOOD
	    dir_in = "MC_2018_Oct19/WZG_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_WZG/191009_204743/";
  	    nfiles = 47;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_WGToLNuG" ) {  //39 - GOOD
	    dir_in = "MC_2018_Oct19/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v1_MC_2018_WGToLNuG/191009_204834/";
  	    nfiles = 117;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_MC_2018_ZGToLLG" ) {  //40
	    dir_in = "MC_2018_Oct19/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2018_ZGToLLG/191009_204926/";
  	    nfiles = 266;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_TGJets" ) {  //41
	    dir_in = "MC_2018_Oct19/TGJets_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_TGJets/191009_205015/";
  	    nfiles = 146;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_MC_2018_TTGJets" ) {  //42
	    dir_in = "MC_2018_Oct19/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Oct19v1_MC_2018_TTGJets/191009_205109/";
  	    nfiles = 133;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_tZq_ll" ) {  //43 - GOOD
	    dir_in = "MC_2018_Oct19/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_tZq_ll/191009_205158/";
  	    nfiles = 382;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_WpWpJJ" ) {  //44 - GOOD
	    dir_in = "MC_2018_Oct19/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_WpWpJJ/191009_205249/";
  	    nfiles = 10;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering" ) {  //45 - GOOD
	    dir_in = "MC_2018_Oct19/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering/191009_205339/";
  	    nfiles = 49;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }
    else if( sample = "Oct19v1_MC_2018_TTTT" ) {  //46 - GOOD
	    dir_in = "MC_2018_Oct19/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/Oct19v1_MC_2018_TTTT/191009_205431/";
  	    nfiles = 98;
	    year = 2018; 
	    type = "Rares";
	    isMC = true;
    }

    // VH
    /*else if( sample = "Oct19v1_MC_2018_VHToNonbb" ) {  //47
	    dir_in = // --> CHECK!
  	    nfiles = 30;
	    year = 2018; 
	    type = "VH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_ZH_HToBB_ZToLL" ) {  //48 - DONE
	    dir_in = "MC_2018_Oct19/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/Oct19v1_MC_2018_ZH_HToBB_ZToLL/191009_205611/";
  	    nfiles = 171;
	    year = 2018; 
	    type = "VH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2018_ZH_HToBB_ZToLL_ext1" ) {  //49
	    dir_in = // --> CHECK!
  	    nfiles = 108;
	    year = 2018; 
	    type = "VH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2018_ZHToTauTau" ) {  //50
	    dir_in = "MC_2018_Oct19/ZHToTauTau_M125_13TeV_powheg_pythia8/Oct19v2_MC_2018_ZHToTauTau/191015_124337/";
  	    nfiles = 163;
	    year = 2018; 
	    type = "VH";
	    isMC = true;
    }*/

    // EWK
    /*else if( sample = "Oct19v2_MC_2018_DYJetsToLL_M-10to50" ) {  //51
	    dir_in = // --> CHECK!
  	    nfiles = 569;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2018_DYJetsToLL_M-50" ) {  //52
	    dir_in = // --> CHECK!
  	    nfiles = 15;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2018_DYJetsToLL_M-50_ext2" ) {  //53
	    dir_in = // --> CHECK!
  	    nfiles = 2802;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2018_WJetsToLNu" ) {  //54
	    dir_in = "MC_2018_Oct19/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/Oct19v2_MC_2018_WJetsToLNu/191015_124701/";
  	    nfiles = 990;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_MC_2018_WWTo2L2Nu" ) {  //55
	    dir_in = // --> CHECK!
  	    nfiles = 176;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_MC_2018_WZTo3LNu" ) {  //56 - GOOD
	    dir_in = "MC_2018_Oct19/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v1_MC_2018_WZTo3LNu/191009_210318/";
  	    nfiles = 280;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2018_WZTo3LNu_ext1" ) {  //57
	    dir_in = "MC_2018_Oct19/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/Oct19v2_MC_2018_WZTo3LNu_ext1/191015_125023/";
  	    nfiles = 206;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/
    else if( sample = "Oct19v2_MC_2018_ZZTo4L" ) {  //58 - GOOD
	    dir_in = "MC_2018_Oct19/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/Oct19v2_MC_2018_ZZTo4L/191015_125112/";
  	    nfiles = 138;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_MC_2018_ZZTo4L_ext2" ) {  //59
	    dir_in = // --> CHECK!
  	    nfiles = 1473;
	    year = 2018; 
	    type = "EWK";
	    isMC = true;
    }*/

    // TTVH
    else if( sample = "Oct19v1_MC_2018_TTWH" ) {  //60 - GOOD
	    dir_in = "MC_2018_Oct19/TTWH_TuneCP5_13TeV-madgraph-pythia8/Oct19v1_MC_2018_TTWH/191009_210700/";
  	    nfiles = 13;
	    year = 2018; 
	    type = "ttVH";
	    isMC = true;
    }
    else if( sample = "Oct19v2_MC_2018_TTZH" ) {  //61 - GOOD
	    dir_in = "MC_2018_Oct19/TTZH_TuneCP5_13TeV-madgraph-pythia8/Oct19v2_MC_2018_TTZH/191015_125405/";
  	    nfiles = 15;
	    year = 2018; 
	    type = "ttVH";
	    isMC = true;
    }

    // HH
    else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_SM" ) {  //62 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/Oct19v2_GluGluToHHTo2B2Tau_node_SM/191015_125450/";
  	    nfiles = 22;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v1_GluGluToHHTo2B2Tau_node_2" ) {  //63
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_2_TuneCP5_PSWeights_13TeV-madgraph-pythia8/GluGluToHHTo2B2Tau_node_2/191009_210953/";
  	    nfiles = 25;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v1_GluGluToHHTo2B2Tau_node_3" ) {  //64
	    dir_in = // --> CHECK!
  	    nfiles = 16;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v1_GluGluToHHTo2B2Tau_node_4" ) {  //65 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_4_TuneCP5_PSWeights_13TeV-madgraph-pythia8/GluGluToHHTo2B2Tau_node_4/191009_211134/";
  	    nfiles = 21;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_GluGluToHHTo2B2Tau_node_5" ) {  //66 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_5_TuneCP5_PSWeights_13TeV-madgraph-pythia8/GluGluToHHTo2B2Tau_node_5/191009_211234/";
  	    nfiles = 17;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }
    else if( sample = "Oct19v1_GluGluToHHTo2B2Tau_node_6" ) {  //67 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_6_TuneCP5_PSWeights_13TeV-madgraph-pythia8/GluGluToHHTo2B2Tau_node_6/191009_211337/";
  	    nfiles = 25;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_7" ) {  //68
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_7_TuneCP5_PSWeights_13TeV-madgraph-pythia8/Oct19v2_GluGluToHHTo2B2Tau_node_7/191015_125603/";
  	    nfiles = 20;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_8" ) {  //69
	    dir_in = // --> CHECK!
  	    nfiles = 15;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_9" ) {  //70 - GOOD
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_9_TuneCP5_PSWeights_13TeV-madgraph-pythia8/Oct19v2_GluGluToHHTo2B2Tau_node_9/191015_125739/";
  	    nfiles = 19;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }
    /*else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_10" ) {  //71
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_10_TuneCP5_PSWeights_13TeV-madgraph-pythia8/Oct19v2_GluGluToHHTo2B2Tau_node_10/191015_125824/";
  	    nfiles = 23;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }*/
    /*else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_11" ) {  //72
	    dir_in = // --> CHECK!
  	    nfiles = 12;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }*/
    else if( sample = "Oct19v2_GluGluToHHTo2B2Tau_node_12" ) {  //73 - DONE
	    dir_in = "MC_2018_Oct19/GluGluToHHTo2B2Tau_node_12_TuneCP5_PSWeights_13TeV-madgraph-pythia8/Oct19v2_GluGluToHHTo2B2Tau_node_12/191015_130003/";
  	    nfiles = 23;
	    year = 2018; 
	    type = "HH";
	    isMC = true;
    }

    else cout<<"ERROR: No sample found!"<<endl;

    dir_in = dir_in+"root://node12.datagrid.cea.fr:1094//dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/";
    int i_split_max = nfiles/i_split_max;

    cout<<"Processing sample "<<sample<<endl;
    cout<<" Year: "<<year<<endl;
    cout<<" Type: "<<type<<endl;
    cout<<" Is MC: "<<isMC<<endl;
    cout<<" Dir_in: "<<dir_in<<endl;
    cout<<" nFiles: "<<nfiles<<endl;

    /////////

    return std::make_tuple(dir_in, nfiles, i_split_max, year, type, isMC);

}


std::tuple< TString, TString, TString, vector<TString> > load_sample_converter( TString sample = "Oct19v1_MC_2016_ttHJetToNonbb", int split, int i_split, int JEC, int TES){

	auto file_info = get_parameters(sample);

  	TString dir_in = std::get<0>(file_info);
  	int nfiles = std::get<1>(file_info);
  	int i_split_max = std::get<2>(file_info);
  	//int year = std::get<3>(file_info);
  	TString type = std::get<4>(file_info);
  	//bool isMC = std::get<5>(file_info);

	TString file = "ntuple_"+sample;
	cout<<"File: "<<file<<endl;

	TString dir_out="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/";
	dir_out += year;
	if(JEC>0)
      dir_out += "/JECup/";
    else if(JEC<0)
      dir_out += "/JECdown/";
    else if(TES>0)
      dir_out += "/TESup/";
    else if(TES<0)
      dir_out += "/TESdown/";
    else
      dir_out += "/nominal/";
  	dir_out += type;
  	dir_out += "/";
  	cout<<"Dir_out: "<<dir_out<<endl;

  	int i_dir = i_split/10;
    dir_in += Form("000%i/",i_dir);
    int i_min = i_split*100;
    if(i_split == 0) i_min++;
    int i_max = (i_split+1)*100;
    if(i_split == i_split_max) i_max = nfiles+1;

    vector<TString> list;
    for(int i = i_min; i < i_max; i++){
      cout<<dir_in+Form("HTauTauAnalysis_%i.root",i)<<endl;
      list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
    }

    return std::make_tuple(dir_in, dir_out, file, list);

}