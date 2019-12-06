// export DPM_HOST=node12.datagrid.cea.fr 
// export DPNS_HOST=node12.datagrid.cea.fr 
// rfdir /dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/
// root://node12.datagrid.cea.fr:1094//dpm/datagrid.cea.fr/home/cms/trivcat/store/user/

// rfdir /dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/<directory>/0000 > <samplename>_0000.txt
// Find replace: ^.+[_] (recursive)

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TChain.h>
#include <TMath.h>

#include <iostream>
#include <vector>
#include <tuple>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


std::tuple<TString, TString, int, TString, bool> get_parameters_data( TString sample = "Oct19v1_Data_2016_SingleEle_BlockB" ){

	TString dir_in;
	TString datafile;
	int year;
	TString type;
	bool isMC;

    ///////////////////
    //// 2016 data ////
    ///////////////////

    // SINGLE ELECTRON

  	if( sample == "Oct19v1_Data_2016_SingleEle_BlockB_0000" ) { // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockB/191011_072828/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockB_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockB_0001" ) { // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockB/191011_072828/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockB_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_SingleEle_BlockB_missing1_0000" ) {  
	    dir_in = "Data_2016_Oct19/SingleElectron/crab_Oct19v1_Data_2016_SingleEle_BlockB_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockC_0000" ) { // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockC/191011_072920/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockC_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockC_missing1_0000" ) {  
	    dir_in = "Data_2016_Oct19/SingleElectron/crab_Oct19v1_Data_2016_SingleEle_BlockC_missing1/191107_140616/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockC_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockD/191011_073008/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockD_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockD_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockD_missing1/191106_162622/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockD_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockE/191011_073103/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockE_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockE_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockE_missing1/191106_162710/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockE_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockF/191011_073157/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockF_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockF_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockF_missing1/191106_162757/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockF_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockG_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockG/191011_073243/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockG_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockG_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockG/191011_073243/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockG_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_SingleEle_BlockG_missing1_0000" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockH_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockH/191011_073334/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockH_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockH_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2016_SingleEle_BlockH/191011_073334/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockH_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockH_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/crab_Oct19v1_Data_2016_SingleEle_BlockH_missing1/191107_140709/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockH_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleEle_BlockH_missing1_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/crab_Oct19v1_Data_2016_SingleEle_BlockH_missing1/191107_140709/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleEle_BlockH_missing1_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }


    // SINGLE MUON

    /*if( sample == "Oct19v2_Data_2016_SingleMu_BlockB" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockC/191011_073519/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockC_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockD/191011_073610/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockD_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockD_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockD_missing1/191106_162927/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockD_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockE/191011_073700/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockE_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockF/191011_073751/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockF_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockF_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockF_missing1/191106_163011/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockF_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockG_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockG/191011_073838/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockG_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockG_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockG/191011_073838/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockG_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockH_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockH/191011_073926/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockH_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMu_BlockH_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2016_SingleMu_BlockH/191011_073926/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_SingleMu_BlockH_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_SingleMu_BlockH_missing1" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/


    // DOUBLE EG

    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockB/191011_074014/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockB_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockB_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockB/191011_074014/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockB_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_DoubleEG_BlockB_missing1" ) {  
	    dir_in = "Data_2016_Oct19/DoubleEG/crab_Oct19v1_Data_2016_DoubleEG_BlockB_missing1";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockC/191011_074101/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockC_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_DoubleEG_BlockC_missing1" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockD/191011_074209/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockD_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_DoubleEG_BlockD_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/DoubleEG/crab_Oct19v1_Data_2016_DoubleEG_BlockD_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockE/191011_074302/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockE_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockF/191011_074351/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockF_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockF_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockF_missing1/191106_163058/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockF_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockG_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockG/191011_074443/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockG_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockG_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockG/191011_074443/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockG_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_DoubleEG_BlockG_missing1" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockH_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockH/191011_074529/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockH_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockH_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2016_DoubleEG_BlockH/191011_074529/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleEG_BlockH_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }


    // DOUBLE MU

    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockB/191011_074619/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockB_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockB_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockB/191011_074619/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockB_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockB_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockB_missing1/191107_125944/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockB_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockC/191011_074710/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockC_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_DoubleMu_BlockC_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/DoubleMuon/crab_Oct19v1_Data_2016_DoubleMu_BlockC_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v2_Data_2016_DoubleMu_BlockD/191015_152647/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockD_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockD_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/crab_Oct19v2_Data_2016_DoubleMu_BlockD_missing1/191107_141152/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockD_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v2_Data_2016_DoubleMu_BlockE/191015_152734/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockE_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_DoubleMu_BlockE_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/DoubleMuon/crab_Oct19v2_Data_2016_DoubleMu_BlockE_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v2_Data_2016_DoubleMu_BlockF/191015_153034/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockF_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v3_Data_2016_DoubleMu_BlockF_missing1" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockG_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockG/191011_075027/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockG_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockG_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockG/191011_075027/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockG_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockG_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2016_DoubleMu_BlockG_missing1/191107_130034/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_DoubleMu_BlockG_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockH_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v2_Data_2016_DoubleMu_BlockH/191015_153213/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockH_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockH_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v2_Data_2016_DoubleMu_BlockH/191015_153213/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockH_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_DoubleMu_BlockH_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v2_Data_2016_DoubleMu_BlockH_missing1/191107_130118/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_DoubleMu_BlockH_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }


    // MUON EG

    if( sample == "Oct19v2_Data_2016_MuonEG_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockB/191015_153306/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockB_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockB_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockB/191015_153306/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockB_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_MuonEG_BlockB_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/MuonEG/crab_Oct19v2_Data_2016_MuonEG_BlockB_missing1";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockC/191015_153357/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockC_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockC_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/crab_Oct19v2_Data_2016_MuonEG_BlockC_missing1/191107_141502/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockC_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockD/191015_153443/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockD_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_MuonEG_BlockD_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/MuonEG/crab_Oct19v2_Data_2016_MuonEG_BlockD_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v4_Data_2016_MuonEG_BlockE" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v4_Data_2016_MuonEG_BlockF" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockG_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockG/191015_153717/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockG_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockG_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockG/191015_153717/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockG_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockG_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockG_missing1/191107_153542/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockG_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockH_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2016_MuonEG_BlockH/191015_153804/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockH_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockH_missing1_0000" ) {  
	    dir_in = "Data_2016_Oct19/MuonEG/crab_Oct19v2_Data_2016_MuonEG_BlockH_missing1/191107_141721/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockH_missing1_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_MuonEG_BlockH_missing1_0001" ) {  
	    dir_in = "Data_2016_Oct19/MuonEG/crab_Oct19v2_Data_2016_MuonEG_BlockH_missing1/191107_141721/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2016_MuonEG_BlockH_missing1_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }


    // TAU

    if( sample == "Oct19v2_Data_2016_Tau_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v2_Data_2016_Tau_BlockB/191015_153856/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_Tau_BlockB_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2016_Tau_BlockB_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v2_Data_2016_Tau_BlockB/191015_153856/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2016_Tau_BlockB_0001.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_Tau_BlockB_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/Tau/crab_Oct19v2_Data_2016_Tau_BlockB_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v3_Data_2016_Tau_BlockC" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2016_Tau_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v2_Data_2016_Tau_BlockD/191015_154041/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2016_Tau_BlockD_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2016_Tau_BlockD_missing1" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v4_Data_2016_Tau_BlockE" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v3_Data_2016_Tau_BlockF" ) {  
	    dir_in = "";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_Tau_BlockG_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2016_Tau_BlockG/191011_080157/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_Tau_BlockG_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_Tau_BlockG_missing1" ) {  
	    dir_in = ""Data_2016_Oct19/Tau/crab_Oct19v1_Data_2016_Tau_BlockG_missing1/";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2016_Tau_BlockH_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2016_Tau_BlockG/191011_080157/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2016_Tau_BlockH_0000.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2016_Tau_BlockH_missing1" ) {  
	    dir_in = " "Data_2016_Oct19/Tau/crab_Oct19v1_Data_2016_Tau_BlockH_missing1";
  	    datafile = ;
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }*/


    ///////////////////
    //// 2017 data ////
    ///////////////////

    // SINGLE ELECTRON

    if( sample == "Oct19v2_Data_2017_SingleEle_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockB/191015_154823/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockB_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockC/191015_154913/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockC_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockC_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockC/191015_154913/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockC_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockC_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockC_missing1/191115_082803/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockC_missing1_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockD/191015_155004/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockD_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockE/191015_155059/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockE_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockE_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockE/191015_155059/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockE_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_SingleEle_BlockE_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v2_Data_2017_SingleEle_BlockE_missing1/191112_084619/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_SingleEle_BlockE_missing1_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleEle_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2017_SingleEle_BlockF/191011_081037/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleEle_BlockF_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleEle_BlockF_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleElectron/Oct19v1_Data_2017_SingleEle_BlockF/191011_081037/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleEle_BlockF_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // SINGLE MUON
	
	if( sample == "Oct19v1_Data_2017_SingleMu_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockB/191011_081128/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockB_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMu_BlockB_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockB_missing1/191112_084704/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockB_missing1_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMu_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockC/191011_081219/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockC_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMu_BlockC_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockC/191011_081219/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockC_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMu_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockD/191011_081305/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockD_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2017_SingleMu_BlockE" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2017_SingleMu_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockF/191011_081448/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockF_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMu_BlockF_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/SingleMuon/Oct19v1_Data_2017_SingleMu_BlockF/191011_081448/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_SingleMu_BlockF_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2017_SingleMu_BlockF_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/

    // DOUBLE EG

    /*if( sample == "Oct19v2_Data_2017_DoubleEG_BlockB" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v2_Data_2017_DoubleEG_BlockC" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2017_DoubleEG_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v1_Data_2017_DoubleEG_BlockD/191011_081710/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleEG_BlockD_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v3_Data_2017_DoubleEG_BlockE" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2017_DoubleEG_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v2_Data_2017_DoubleEG_BlockF/191015_155346/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_DoubleEG_BlockF_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_DoubleEG_BlockF_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleEG/Oct19v2_Data_2017_DoubleEG_BlockF/191015_155346/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2017_DoubleEG_BlockF_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2017_DoubleEG_BlockF_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/

    // DOUBLE MUON

    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockB/191013_154745/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockB_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockB_missing_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockB_missing/191106_163803/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockB_missing_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockC/191013_154835/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockC_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockC_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockC/191013_154835/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockC_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2017_DoubleMu_BlockC_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockD/191013_154927/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockD_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2017_DoubleMu_BlockD_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockE/191013_155017/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockE_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockE_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/DoubleMuon/Oct19v1_Data_2017_DoubleMu_BlockE/191013_155017/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_DoubleMu_BlockE_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2017_DoubleMu_BlockF" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/

    // MUON EG

    if( sample == "Oct19v1_Data_2017_MuonEG_BlockB_0000" ) {  // GOOD
	    dir_in = "/Data_2016_Oct19/MuonEG/Oct19v1_Data_2017_MuonEG_BlockB/191013_155159/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_MuonEG_BlockB_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2017_MuonEG_BlockC" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2017_MuonEG_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v1_Data_2017_MuonEG_BlockD/191013_155344/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_MuonEG_BlockD_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_MuonEG_BlockD_missing1_0000" ) {  //->check overlap!!!!
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v1_Data_2017_MuonEG_BlockD_missing1/191108_112428/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_MuonEG_BlockD_missing1_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2017_MuonEG_BlockE" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v2_Data_2017_MuonEG_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2017_MuonEG_BlockF/191108_085511/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2017_MuonEG_BlockF_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2017_MuonEG_BlockF_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/MuonEG/Oct19v2_Data_2017_MuonEG_BlockF/191108_085511/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2017_MuonEG_BlockF_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // TAU

    if( sample == "Oct19v1_Data_2017_Tau_BlockB_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockB/191013_155619/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockB_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockC_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockC/191013_155707/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockC_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockC_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockC/191013_155707/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockC_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockD_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockD/191013_155800/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockD_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockD_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockD_missing1/191108_112513/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockD_missing1_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockE_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockE/191013_155846/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockE_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockE_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockE/191013_155846/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockE_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockE_missing1_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockE_missing1/191110_153201/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockE_missing1_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockF_0000" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockF/191013_155942/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockF_0000.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockF_0001" ) {  // GOOD
	    dir_in = "Data_2016_Oct19/Tau/Oct19v1_Data_2017_Tau_BlockF/191013_155942/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2017_Tau_BlockF_0001.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2017_Tau_BlockF_missing" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }*/


    ///////////////////
    //// 2018 data ////
    ///////////////////

    // SINGLE ELECTRON

    /*if( sample == "Oct19v2_Data_2018_EGamma_BlockA" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_EGamma_BlockB_0000" ) {  
	    dir_in = "Data_2018_Oct19/EGamma/Oct19v1_Data_2018_EGamma_BlockB/191014_071039/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_EGamma_BlockB_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_EGamma_BlockB_0001" ) {  
	    dir_in = "Data_2018_Oct19/EGamma/Oct19v1_Data_2018_EGamma_BlockB/191014_071039/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_EGamma_BlockB_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_EGamma_BlockB_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_EGamma_BlockC_0000" ) {  
	    dir_in = "Data_2018_Oct19/EGamma/Oct19v1_Data_2018_EGamma_BlockC/191014_071130/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_EGamma_BlockC_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_EGamma_BlockC_0001" ) {  
	    dir_in = "Data_2018_Oct19/EGamma/Oct19v1_Data_2018_EGamma_BlockC/191014_071130/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_EGamma_BlockC_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_EGamma_BlockC_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    /*if( sample == "Oct19v5_Data_2018_EGamma_BlockD" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/

    // SINGLE MUON

    if( sample == "Oct19v1_Data_2018_SingleMu_BlockA_0000" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockA/191014_071216/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockA_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockA_0001" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockA/191014_071216/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockA_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockA_0002" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockA/191014_071216/0002/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockA_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v2_Data_2018_SingleMu_BlockA_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockB_0000" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockB/191014_071303/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockB_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_SingleMu_BlockB_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockC_0000" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockC/191014_071352/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockC_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockC_0001" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockC/191014_071352/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockC_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockC_missing1_0000" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockC_missing1/191108_113021/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockC_missing1_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMu_BlockC_missing1_0001" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v1_Data_2018_SingleMu_BlockC_missing1/191108_113021/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_SingleMu_BlockC_missing1_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v3_Data_2018_SingleMu_BlockD_0000" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v3_Data_2018_SingleMu_BlockD/191016_071735/0000/";
  	    datafile = "datafiles/Oct19v3_Data_2018_SingleMu_BlockD_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v3_Data_2018_SingleMu_BlockD_0001" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v3_Data_2018_SingleMu_BlockD/191016_071735/0001/";
  	    datafile = "datafiles/Oct19v3_Data_2018_SingleMu_BlockD_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v3_Data_2018_SingleMu_BlockD_0002" ) {  
	    dir_in = "Data_2018_Oct19/SingleMuon/Oct19v3_Data_2018_SingleMu_BlockD/191016_071735/0002/";
  	    datafile = "datafiles/Oct19v3_Data_2018_SingleMu_BlockD_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v3_Data_2018_SingleMu_BlockD_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/

    // DOUBLE MUON

    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockA_0000" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockA/191014_071444/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockA_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockA_0001" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockA/191014_071444/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockA_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockA_0002" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockA/191014_071444/0002/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockA_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockA_0003" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockA/191014_071444/0003/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockA_0003.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_DoubleMu_BlockA_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockB_0000" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockB/191014_071531/0000/";
  	    datafile = "Oct19v1_Data_2018_DoubleMu_BlockB_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockB_0001" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockB/191014_071531/0001/";
  	    datafile = "Oct19v1_Data_2018_DoubleMu_BlockB_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_DoubleMu_BlockB_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockC_0000" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockC/191014_071625/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockC_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockC_0001" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockC/191014_071625/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockC_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockC_0002" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockC/191014_071625/0002/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockC_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockC_missing1_0000" ) {  
	    dir_in = "Data_2018_Oct19/DoubleMuon/Oct19v1_Data_2018_DoubleMu_BlockC_missing1/191107_130607/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_DoubleMu_BlockC_missing1_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v5_Data_2018_DoubleMu_BlockD" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/

    // MUON EG

    /*if( sample == "Oct19v2_Data_2018_MuonEG_BlockA" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockB_0000" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v1_Data_2018_MuonEG_BlockB/191014_071805/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_MuonEG_BlockB_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockB_0001" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v1_Data_2018_MuonEG_BlockB/191014_071805/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_MuonEG_BlockB_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockB_0002" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v1_Data_2018_MuonEG_BlockB/191014_071805/0002/";
  	    datafile = "datafiles/Oct19v1_Data_2018_MuonEG_BlockB_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockB_missing1_0000" ) {  // -> check overlap!!!
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v1_Data_2018_MuonEG_BlockB_missing1/191108_113250/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_MuonEG_BlockB_missing1_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2018_MuonEG_BlockC_0000" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v2_Data_2018_MuonEG_BlockC/191108_093508/0000/";
  	    datafile = "datafiles/Oct19v2_Data_2018_MuonEG_BlockC_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2018_MuonEG_BlockC_0001" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v2_Data_2018_MuonEG_BlockC/191108_093508/0001/";
  	    datafile = "datafiles/Oct19v2_Data_2018_MuonEG_BlockC_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v2_Data_2018_MuonEG_BlockC_0002" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v2_Data_2018_MuonEG_BlockC/191108_093508/0002/";
  	    datafile = "datafiles/Oct19v2_Data_2018_MuonEG_BlockC_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v3_Data_2018_MuonEG_BlockD_0000" ) {  
	    dir_in = "Data_2018_Oct19/MuonEG/Oct19v3_Data_2018_MuonEG_BlockD/191016_071913/0000/";
  	    datafile = "datafiles/Oct19v3_Data_2018_MuonEG_BlockD_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v3_Data_2018_MuonEG_BlockD_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/

    // TAU

    if( sample == "Oct19v1_Data_2018_Tau_BlockA_0000" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockA/191014_071942/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockA_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockA_0001" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockA/191014_071942/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockA_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockA_0002" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockA/191014_071942/0002/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockA_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_Tau_BlockA_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v1_Data_2018_Tau_BlockB_0000" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockB/191014_072030/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockB_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockB_0001" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockB/191014_072030/0001/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockB_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockB_0002" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockB/191014_072030/0002/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockB_0002.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockC_0000" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v1_Data_2018_Tau_BlockC/191014_072118/0000/";
  	    datafile = "datafiles/Oct19v1_Data_2018_Tau_BlockC_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v1_Data_2018_Tau_BlockC_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }*/
    if( sample == "Oct19v4_Data_2018_Tau_BlockD_0000" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v4_Data_2018_Tau_BlockD/191028_082919/0000/";
  	    datafile = "datafiles/Oct19v4_Data_2018_Tau_BlockD_0000.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v4_Data_2018_Tau_BlockD_0001" ) {  
	    dir_in = "Data_2018_Oct19/Tau/Oct19v4_Data_2018_Tau_BlockD/191028_082919/0001/";
  	    datafile = "datafiles/Oct19v4_Data_2018_Tau_BlockD_0001.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    /*if( sample == "Oct19v4_Data_2018_Tau_BlockD_missing1" ) {  
	    dir_in = 
  	    datafile = 
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    */

    /////////////////

    dir_in = "root://node12.datagrid.cea.fr:1094//dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/"+dir_in;

	cout<<" "<<endl;
    cout<<" Processing sample "<<sample<<":"<<endl;
    cout<<"  Year: "<<year<<endl;
    cout<<"  Type: "<<type<<endl;
    cout<<"  Is MC: "<<isMC<<endl;
    cout<<"  Directory in: "<<dir_in<<endl;
    cout<<"  File directory: "<<datafile<<endl;

    /////////

    return std::make_tuple(dir_in, datafile, year, type, isMC);

}


std::tuple< TString, TString, TString, vector<TString>, int, bool > load_sample_converter_data ( TString sample = "Oct19v1_Data_2016_SingleEle_BlockD_missing1_0000", int split=0, int i_split=0, int JEC=0, int TES=0){

	auto file_info = get_parameters_data(sample);

  	TString dir_in = std::get<0>(file_info);
  	TString datafile = std::get<1>(file_info);
  	int year = std::get<2>(file_info);
  	TString type = std::get<3>(file_info);
    bool isMC = std::get<4>(file_info);

	TString file = "ntuple_"+sample;

	TString dir_out="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/";
	dir_out += year;
	if(JEC>0)
    	dir_out += "/JECup/";
    if(JEC<0)
    	dir_out += "/JECdown/";
    if(TES>0)
    	dir_out += "/TESup/";
    if(TES<0)
    	dir_out += "/TESdown/";
    else
    	dir_out += "/nominal/";
  	dir_out += type;
  	dir_out += "/";

	ifstream datatxt(datafile);
	int content;

	vector<TString> list;
    while(datatxt >> content) {
        cout<<"     "<<dir_in+Form("HTauTauAnalysis_%i.root",content)<<endl;
        list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",content));
    }

    return std::make_tuple(dir_in, dir_out, file, list, year, isMC);

}