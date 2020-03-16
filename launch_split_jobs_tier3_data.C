#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <map>
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
#include <TROOT.h>
#include <TSystem.h>

using namespace std;

// BEFORE LAUNCHING:
// source tier3
// proxy
// compile tree_splitter

void create_scripts( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int maxsplit=0, TString year="2016", TString type="Data" ){

  //TString dirin = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/";
  TString dirin = "/data_CMPerez/mperez/ttH_Legacy/ntuples_converted/";
  dirin += year;
  dirin += "/nominal/";
  dirin += type;
  dirin += "/";

  //cout<<dirin<<endl;

  TString dirout = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/";
  dirout += year;
  dirout += "/nominal/";
  dirout += type;
  dirout += "/";

  //cout<<dirout<<endl;

  for(int j=0;j<maxsplit+1;j++){ 

    std::string isample = std::to_string(j);

    TString filename = "ntuple_"+sample+"_"+isample+".root";

    //cout<<filename<<endl;

    TString ScriptName = Form("script_tier3_data/"+year+"/split_"+sample+"_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/prodOct19/CMSSW_10_2_16/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_Oct19_v2.C+\n";
    myscript << "split_tree(\""+dirin+filename+"\",\""+dirout+filename+"\",0,0,false,"+year+");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

}


void launch_scripts( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int maxsplit=0, TString year="2016", TString type="Data" ){

  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3_data/"+year+"/split_"+sample+"_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
 
  }

}

void launch_single_script( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int isplit=0, TString year="2016", TString type="Data" ){

  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += Form("script_tier3_data/"+year+"/split_"+sample+"_%i.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
 
}



void create_scripts_all(){

  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockB",36,"2016","Data/SingleElectron/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockC",11,"2016","Data/SingleElectron/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockD",19,"2016","Data/SingleElectron/BlockD"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockE",25,"2016","Data/SingleElectron/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockF",12,"2016","Data/SingleElectron/BlockF"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockG",28,"2016","Data/SingleElectron/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockH",31,"2016","Data/SingleElectron/BlockH"); // DONE

  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockB",35,"2016","Data/SingleMuon/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockC",11,"2016","Data/SingleMuon/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockD",19,"2016","Data/SingleMuon/BlockD"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockE",16,"2016","Data/SingleMuon/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockF",12,"2016","Data/SingleMuon/BlockF"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockG",28,"2016","Data/SingleMuon/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockH",31,"2016","Data/SingleMuon/BlockH"); // DONE

  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17,"2016","Data/DoubleEG/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5,"2016","Data/DoubleEG/BlockC");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","Data/DoubleEG/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8,"2016","Data/DoubleEG/BlockE");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6,"2016","Data/DoubleEG/BlockF");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14,"2016","Data/DoubleEG/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15,"2016","Data/DoubleEG/BlockH"); // DONE

  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17,"2016","Data/DoubleMu/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5,"2016","Data/DoubleMu/BlockC");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10,"2016","Data/DoubleMu/BlockD"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8,"2016","Data/DoubleMu/BlockE");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6,"2016","Data/DoubleMu/BlockF");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14,"2016","Data/DoubleMu/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","Data/DoubleMu/BlockH"); // DONE

  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17,"2016","Data/MuonEG/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5,"2016","Data/MuonEG/BlockC");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9,"2016","Data/MuonEG/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8,"2016","Data/MuonEG/BlockE");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6,"2016","Data/MuonEG/BlockF");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16,"2016","Data/MuonEG/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15,"2016","Data/MuonEG/BlockH"); // DONE

  // 2017

  //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockB",8,"2017","Data/SingleElectron/BlockB");  // DONE
  //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockC",17,"2017","Data/SingleElectron/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockD",9,"2017","Data/SingleElectron/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockE",14,"2017","Data/SingleElectron/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockF",19,"2017","Data/SingleElectron/BlockF"); // DONE

  //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockB",9,"2017","Data/SingleMuon/BlockB");  // DONE
  //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockC",17,"2017","Data/SingleMuon/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockD",9,"2017","Data/SingleMuon/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockE",14,"2017","Data/SingleMuon/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockF",20,"2017","Data/SingleMuon/BlockF"); // DONE

  //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockB",8,"2017","Data/DoubleEG/BlockB");  // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockC",17,"2017","Data/DoubleEG/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockD",9,"2017","Data/DoubleEG/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockE",14,"2017","Data/DoubleEG/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockF",19,"2017","Data/DoubleEG/BlockF"); // DONE

  //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockB",8,"2017","Data/DoubleMu/BlockB");  // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockC",17,"2017","Data/DoubleMu/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockD",9,"2017","Data/DoubleMu/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockE",14,"2017","Data/DoubleMu/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockF",19,"2017","Data/DoubleMu/BlockF"); // DONE

  //create_scripts("Oct19v1_Data_2017_MuonEG_BlockB",8,"2017","Data/MuonEG/BlockB");  // DONE
  //create_scripts("Oct19v1_Data_2017_MuonEG_BlockC",18,"2017","Data/MuonEG/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2017_MuonEG_BlockD",9,"2017","Data/MuonEG/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2017_MuonEG_BlockE",14,"2017","Data/MuonEG/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2017_MuonEG_BlockF",19,"2017","Data/MuonEG/BlockF"); // DONE


  // 2018

  //create_scripts("Oct19v1_Data_2018_EGamma_BlockA",56,"2018","Data/EGamma/BlockA"); // DONE
  //create_scripts("Oct19v1_Data_2018_EGamma_BlockB",28,"2018","Data/EGamma/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2018_EGamma_BlockC",26,"2018","Data/EGamma/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2018_EGamma_BlockD",83,"2018","Data/EGamma/BlockD"); // DONE

  //create_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55,"2018","Data/SingleMuon/BlockA"); // DONE
  //create_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26,"2018","Data/SingleMuon/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26,"2018","Data/SingleMuon/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2018_SingleMuon_BlockD",83,"2018","Data/SingleMuon/BlockD"); // DONE

  //create_scripts("Oct19v1_Data_2018_DoubleMu_BlockA",56,"2018","Data/DoubleMu/BlockA"); // DONE
  //create_scripts("Oct19v1_Data_2018_DoubleMu_BlockB",26,"2018","Data/DoubleMu/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2018_DoubleMu_BlockC",26,"2018","Data/DoubleMu/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2018_DoubleMu_BlockD",83,"2018","Data/DoubleMu/BlockD"); // DONE

  //create_scripts("Oct19v1_Data_2018_MuonEG_BlockA",55,"2018","Data/MuonEG/BlockA"); // DONE
  //create_scripts("Oct19v1_Data_2018_MuonEG_BlockB",26,"2018","Data/MuonEG/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2018_MuonEG_BlockC",26,"2018","Data/MuonEG/BlockC"); // DONE
  //create_scripts("Oct19v1_Data_2018_MuonEG_BlockD",85,"2018","Data/MuonEG/BlockD"); // DONE

    
}

void launch_single_script_all(){

 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",17,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",9,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",4,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",53,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",18,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",6,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",15,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",67,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",56,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",55,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",29,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",14,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",78,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",26,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",38,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",74,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",59,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",75,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",7,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",8,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",76,"2018","Data/EGamma/BlockD"); 
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",39,"2018","Data/EGamma/BlockD"); 

}