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
// compile tree_converter

void create_scripts( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int maxsplit=0, TString year="2016", TString type="MC" ){

 for(int j=0;j<maxsplit+1;j++){ //maxsplit -> blocks of 50 files in crab

    TString ScriptName = Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/prodOct19/CMSSW_10_2_16/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export DPM_HOST=node12.datagrid.cea.fr\n";
    myscript << "export DPNS_HOST=node12.datagrid.cea.fr \n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_converter_Oct19_v1.C+\n";
    myscript << "convert_tree(\""+sample+"\",0,"<< j << ",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

}


void launch_scripts( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int maxsplit=0, TString year="2016", TString type="MC" ){
       
  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

}

void launch_single_script( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int isplit=0, TString year="2016", TString type="MC" ){
       
  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
        
}



void create_scripts_all(){

    //2016

    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockB",36,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockC",11,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockD",19,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockE",25,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockF",12,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockG",28,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockH",31,"2016","data"); // ---> CHECKED/DONE!

    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockB",35,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockC",11,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockD",19,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockE",16,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockF",12,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockG",28,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockH",31,"2016","data"); // ---> CHECKED/DONE!

    /*create_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14*2,"2016","data");
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15*2+1,"2016","data");

    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14*2,"2016","data");
    create_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15*2+1,"2016","data");

    create_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16*2,"2016","data");
    create_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15*2+1,"2016","data");

    create_scripts("Oct19v1_Data_2016_Tau_BlockB",18*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockC",5*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockD",9*2+1,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockE",8*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockF",6*2,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockG",14*2+1,"2016","data");
    create_scripts("Oct19v1_Data_2016_Tau_BlockH",16*2,"2016","data");
    */

    //2017

    /*
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockB",8*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockC",17*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockD",9*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockE",14*2+1,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockF",19*2+1,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockB",8*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockC",17*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockD",9*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockE",14*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockF",19*2+1,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockB",8*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockC",17*2+1,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockD",9*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockE",14*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockF",19*2+1,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockB",8*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockC",17*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockD",9*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockE",14*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockF",19*2+1,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_MuonEG_BlockB",8*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockC",18*2+1,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockD",9*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockE",14*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockF",19*2+1,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_Tau_BlockB",8*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockC",17*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockD",9*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockE",14*2,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockF",19*2,"2017","data"); 
    */
  
    // 2018

    /*
    create_scripts("Oct19v1_Data_2018_EGamma_BlockA",56*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockB",28*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockC",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockD",83*2+1,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockD",83*2+1,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockA",56*2+1,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockB",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockC",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockD",83*2+1,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_MuonEG_BlockA",55*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_MuonEG_BlockB",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_MuonEG_BlockC",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_MuonEG_BlockD",85*2,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_Tau_BlockA",55*2+1,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_Tau_BlockB",26*2,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_Tau_BlockC",26*2+1,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_Tau_BlockD",89*2,"2018","data"); 
    */

}

void launch_scripts_all(){

    //2016

    launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockB",18*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockC",5*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockD",9*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockE",12*2+1,"2016","data"); 
    //launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockF",6*2,"2016","data"); 
    //launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockG",14*2,"2016","data");
    //launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockH",15*2+1,"2016","data");  

    /*launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockB",17*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockC",5*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockD",9*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockE",8*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockF",6*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockG",14*2,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockH",15*2+1,"2016","data"); 

    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14*2,"2016","data");
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15*2+1,"2016","data");

    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14*2,"2016","data");
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15*2+1,"2016","data");

    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16*2,"2016","data");
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15*2+1,"2016","data");

    launch_scripts("Oct19v1_Data_2016_Tau_BlockB",18*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockC",5*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockD",9*2+1,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockE",8*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockF",6*2,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockG",14*2+1,"2016","data");
    launch_scripts("Oct19v1_Data_2016_Tau_BlockH",16*2,"2016","data");
    */

    //2017

    /*
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockB",8*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockC",17*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockD",9*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockE",14*2+1,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockF",19*2+1,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockB",8*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockC",17*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockD",9*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockE",14*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockF",19*2+1,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockB",8*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockC",17*2+1,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockD",9*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockE",14*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockF",19*2+1,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockB",8*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockC",17*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockD",9*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockE",14*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockF",19*2+1,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockB",8*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockC",18*2+1,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockD",9*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockE",14*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockF",19*2+1,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_Tau_BlockB",8*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockC",17*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockD",9*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockE",14*2,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockF",19*2,"2017","data"); 
    */
  
    // 2018

    /*
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockA",56*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockB",28*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockC",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockD",83*2+1,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockD",83*2+1,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockA",56*2+1,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockB",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockC",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockD",83*2+1,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockA",55*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockB",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockC",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockD",85*2,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_Tau_BlockA",55*2+1,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_Tau_BlockB",26*2,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_Tau_BlockC",26*2+1,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_Tau_BlockD",89*2,"2018","data"); 
    */

}

void launch_single_script_all(){

launch_single_script("Oct19v1_Data_2016_SingleElectron_BlockB",28,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleElectron_BlockB",30,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleElectron_BlockB",33,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleElectron_BlockC",5,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleElectron_BlockC",8,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockB",8,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockB",22,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockB",26,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockC",7,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockC",8,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockD",1,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockD",12,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockE",5,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockE",10,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockE",13,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockF",3,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockG",5,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockG",6,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockG",8,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockG",16,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockG",21,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockH",9,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockH",2,"2016","data");
launch_single_script("Oct19v1_Data_2016_SingleMuon_BlockH",28,"2016","data");


}