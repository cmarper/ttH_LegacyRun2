// export DPM_HOST=node12.datagrid.cea.fr 
// export DPNS_HOST=node12.datagrid.cea.fr 
// rfdir /dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/
// root://node12.datagrid.cea.fr:1094//dpm/datagrid.cea.fr/home/cms/trivcat/store/user/

// rfdir /dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/<directory>/0000 > <samplename>_0000.txt
// Find: ^.+[_] (recursive)
// Replace: <dir>/HTauTauAnalysis_

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


std::tuple<TString, TString, int, TString, bool> get_parameters_data( TString sample = "Oct19v1_Data_2016_SingleElectron_BlockB" ){

	TString dir_in;
	TString datafile;
	int year;
	TString type;
	bool isMC;

    ///////////////////
    //// 2016 data ////
    ///////////////////

    // Single Electron

  	if( sample == "Oct19v1_Data_2016_SingleElectron_BlockB" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockB.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleElectron_BlockC" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockC.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleElectron_BlockD" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockD.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleElectron_BlockE" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockE.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleElectron_BlockF" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockF.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleElectron_BlockG" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockG.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleElectron_BlockH" ) { 
  	  datafile = "datafiles/2016/2016_SingleElectron_BlockH.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }

    // Single Muon

    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockB" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockB.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockC" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockC.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockD" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockD.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockE" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockE.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockF" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockF.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockG" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockG.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_SingleMuon_BlockH" ) { 
  	  datafile = "datafiles/2016/2016_SingleMuon_BlockH.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }

    // Double EG

    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockB" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockB.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockC" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockC.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockD" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockD.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockE" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockE.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockF" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockF.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockG" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockG.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleEG_BlockH" ) { 
  	  datafile = "datafiles/2016/2016_DoubleEG_BlockH.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }

    // Double Mu

    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockB" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockB.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockC" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockC.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockD" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockD.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockE" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockE.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockF" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockF.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockG" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockG.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_DoubleMu_BlockH" ) { 
  	  datafile = "datafiles/2016/2016_DoubleMu_BlockH.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }

    // Muon EG

    if( sample == "Oct19v1_Data_2016_MuonEG_BlockB" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockB.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_MuonEG_BlockC" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockC.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_MuonEG_BlockD" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockD.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_MuonEG_BlockE" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockE.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_MuonEG_BlockF" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockF.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_MuonEG_BlockG" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockG.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_MuonEG_BlockH" ) { 
  	  datafile = "datafiles/2016/2016_MuonEG_BlockH.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }

    // Tau

    if( sample == "Oct19v1_Data_2016_Tau_BlockB" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockB.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_Tau_BlockC" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockC.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_Tau_BlockD" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockD.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_Tau_BlockE" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockE.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_Tau_BlockF" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockF.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_Tau_BlockG" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockG.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2016_Tau_BlockH" ) { 
  	  datafile = "datafiles/2016/2016_Tau_BlockH.txt";
	    year = 2016;
	    type = "Data";
	    isMC = false;
    }


    ///////////////////
    //// 2017 data ////
    ///////////////////

    // Single Electron

  	if( sample == "Oct19v1_Data_2017_SingleElectron_BlockB" ) { 
  	  datafile = "datafiles/2017/2017_SingleElectron_BlockB.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleElectron_BlockC" ) { 
  	  datafile = "datafiles/2017/2017_SingleElectron_BlockC.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleElectron_BlockD" ) { 
  	  datafile = "datafiles/2017/2017_SingleElectron_BlockD.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleElectron_BlockE" ) { 
  	  datafile = "datafiles/2017/2017_SingleElectron_BlockE.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleElectron_BlockF" ) { 
  	  datafile = "datafiles/2017/2017_SingleElectron_BlockF.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // Single Muon

    if( sample == "Oct19v1_Data_2017_SingleMuon_BlockB" ) { 
  	  datafile = "datafiles/2017/2017_SingleMuon_BlockB.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMuon_BlockC" ) { 
  	  datafile = "datafiles/2017/2017_SingleMuon_BlockC.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMuon_BlockD" ) { 
  	  datafile = "datafiles/2017/2017_SingleMuon_BlockD.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMuon_BlockE" ) { 
  	  datafile = "datafiles/2017/2017_SingleMuon_BlockE.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_SingleMuon_BlockF" ) { 
  	  datafile = "datafiles/2017/2017_SingleMuon_BlockF.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // Double EG

    if( sample == "Oct19v1_Data_2017_DoubleEG_BlockB" ) { 
  	  datafile = "datafiles/2017/2017_DoubleEG_BlockB.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleEG_BlockC" ) { 
  	  datafile = "datafiles/2017/2017_DoubleEG_BlockC.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleEG_BlockD" ) { 
  	  datafile = "datafiles/2017/2017_DoubleEG_BlockD.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleEG_BlockE" ) { 
  	  datafile = "datafiles/2017/2017_DoubleEG_BlockE.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleEG_BlockF" ) { 
  	  datafile = "datafiles/2017/2017_DoubleEG_BlockF.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // Double Mu

    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockB" ) { 
  	  datafile = "datafiles/2017/2017_DoubleMu_BlockB.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockC" ) { 
  	  datafile = "datafiles/2017/2017_DoubleMu_BlockC.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockD" ) { 
  	  datafile = "datafiles/2017/2017_DoubleMu_BlockD.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockE" ) { 
  	  datafile = "datafiles/2017/2017_DoubleMu_BlockE.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_DoubleMu_BlockF" ) { 
  	  datafile = "datafiles/2017/2017_DoubleMu_BlockF.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // Muon EG

    if( sample == "Oct19v1_Data_2017_MuonEG_BlockB" ) { 
  	  datafile = "datafiles/2017/2017_MuonEG_BlockB.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_MuonEG_BlockC" ) { 
  	  datafile = "datafiles/2017/2017_MuonEG_BlockC.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_MuonEG_BlockD" ) { 
  	  datafile = "datafiles/2017/2017_MuonEG_BlockD.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_MuonEG_BlockE" ) { 
  	  datafile = "datafiles/2017/2017_MuonEG_BlockE.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_MuonEG_BlockF" ) { 
  	  datafile = "datafiles/2017/2017_MuonEG_BlockF.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }

    // Tau

    if( sample == "Oct19v1_Data_2017_Tau_BlockB" ) { 
  	  datafile = "datafiles/2017/2017_Tau_BlockB.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockC" ) { 
  	  datafile = "datafiles/2017/2017_Tau_BlockC.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockD" ) { 
  	  datafile = "datafiles/2017/2017_Tau_BlockD.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockE" ) { 
  	  datafile = "datafiles/2017/2017_Tau_BlockE.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2017_Tau_BlockF" ) { 
  	  datafile = "datafiles/2017/2017_Tau_BlockF.txt";
	    year = 2017;
	    type = "Data";
	    isMC = false;
    }


    ///////////////////
    //// 2018 data ////
    ///////////////////

    // EGamma

	if( sample == "Oct19v1_Data_2018_EGamma_BlockA" ) { 
  	  datafile = "datafiles/2018/2018_EGamma_BlockA.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
  	if( sample == "Oct19v1_Data_2018_EGamma_BlockB" ) { 
  	  datafile = "datafiles/2018/2018_EGamma_BlockB.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_EGamma_BlockC" ) { 
  	  datafile = "datafiles/2018/2018_EGamma_BlockC.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_EGamma_BlockD" ) { 
  	  datafile = "datafiles/2018/2018_EGamma_BlockD.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }

    // Single Muon

    if( sample == "Oct19v1_Data_2018_SingleMuon_BlockA" ) { 
  	  datafile = "datafiles/2018/2018_SingleMuon_BlockA.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMuon_BlockB" ) { 
  	  datafile = "datafiles/2018/2018_SingleMuon_BlockB.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMuon_BlockC" ) { 
  	  datafile = "datafiles/2018/2018_SingleMuon_BlockC.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_SingleMuon_BlockD" ) { 
  	  datafile = "datafiles/2018/2018_SingleMuon_BlockD.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }

    // Double Mu

    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockA" ) { 
  	  datafile = "datafiles/2018/2018_DoubleMu_BlockA.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockB" ) { 
  	  datafile = "datafiles/2018/2018_DoubleMu_BlockB.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockC" ) { 
  	  datafile = "datafiles/2018/2018_DoubleMu_BlockC.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_DoubleMu_BlockD" ) { 
  	  datafile = "datafiles/2018/2018_DoubleMu_BlockD.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }

    // Muon EG

    if( sample == "Oct19v1_Data_2018_MuonEG_BlockA" ) { 
  	  datafile = "datafiles/2018/2018_MuonEG_BlockA.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockB" ) { 
  	  datafile = "datafiles/2018/2018_MuonEG_BlockB.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockC" ) { 
  	  datafile = "datafiles/2018/2018_MuonEG_BlockC.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_MuonEG_BlockD" ) { 
  	  datafile = "datafiles/2018/2018_MuonEG_BlockD.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }

    // Tau

    if( sample == "Oct19v1_Data_2018_Tau_BlockA" ) { 
  	  datafile = "datafiles/2018/2018_Tau_BlockA.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockB" ) { 
  	  datafile = "datafiles/2018/2018_Tau_BlockB.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockC" ) { 
  	  datafile = "datafiles/2018/2018_Tau_BlockC.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    if( sample == "Oct19v1_Data_2018_Tau_BlockD" ) { 
  	  datafile = "datafiles/2018/2018_Tau_BlockD.txt";
	    year = 2018;
	    type = "Data";
	    isMC = false;
    }
    

    /////////////////

    dir_in = "root://node12.datagrid.cea.fr:1094//dpm/datagrid.cea.fr/home/cms/trivcat/store/user/cmartinp/ttH_Legacy/"+dir_in;

	  cout<<" "<<endl;
    cout<<" Processing sample "<<sample<<":"<<endl;
    cout<<"  Year: "<<year<<endl;
    cout<<"  Type: "<<type<<endl;
    cout<<"  Is MC: "<<isMC<<endl;
    //cout<<"  Directory in: "<<dir_in<<endl;
    cout<<"  File list: "<<datafile<<endl;
    cout<<"  Files to process: "<<endl;

    /////////

    return std::make_tuple(dir_in, datafile, year, type, isMC);

}


std::tuple< TString, TString, TString, vector<TString>, int, bool > load_sample_converter_data ( TString sample = "Oct19v1_Data_2016_SingleElectron_BlockB", int split=0, int i_split=0, int JEC=0, int TES=0){

	auto file_info = get_parameters_data(sample);

  	TString dir_in = std::get<0>(file_info);
  	TString datafile = std::get<1>(file_info);
  	int year = std::get<2>(file_info);
  	TString type = std::get<3>(file_info);
    bool isMC = std::get<4>(file_info);

	TString file = "ntuple_"+sample;

	//TString dir_out="/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/";
  TString dir_out="/data_CMPerez/mperez/ttH_Legacy/ntuples_converted/";
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

	int nfiles = 0;
	ifstream infile(datafile);
	std::string ifile;
	vector<TString> filelist;
	while ( std::getline(infile, ifile) ){
   		++nfiles;
   		TString fullfile = dir_in + ifile;
   		filelist.push_back(fullfile);
	}
 	 	
	int i_split_max = i_split_max = nfiles/100;
  //int i_split_max = i_split_max = nfiles/50;

  int i_min = i_split*100;
  //int i_min = i_split*50;
  if(i_split == 0) i_min++;
  int i_max = (i_split+1)*100;
  //int i_max = (i_split+1)*50;
  if(i_split == i_split_max) i_max = nfiles+1;

  vector<TString> list;
  for(int i = i_min; i < i_max; i++){ 
    	list.push_back(filelist.at(i-1));
      cout<<"   "<<filelist.at(i-1)<<endl;
  }

  return std::make_tuple(dir_in, dir_out, file, list, year, isMC);

}