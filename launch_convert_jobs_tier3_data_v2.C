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
    myscript << ".L tree_converter_Oct19_v2.C+\n";
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

    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17,"2016","data"); // CHECKED/DONE**-- / repeat: 2
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5,"2016","data");  // CHECKED/DONE**-- / missing: 4
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","data");  // ---> CHECKED/DONE!
    create_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8,"2016","data");  // CHECKED/DONE**-- / missing: 0
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15,"2016","data"); //  ---> CHECKED/DONE!

    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17,"2016","data"); // ---> CHECKED/DONE!  
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5,"2016","data");  // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10,"2016","data"); // ---> CHECKED/DONE!  
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8,"2016","data");  // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6,"2016","data");  // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","data"); // ---> CHECKED/DONE!  

    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5,"2016","data");  // ---> CHECKED/DONE! 
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9,"2016","data");  // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8,"2016","data");  // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6,"2016","data");  // ---> CHECKED/DONE!  
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16,"2016","data"); // ---> CHECKED/DONE!
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15,"2016","data"); // ---> CHECKED/DONE! 

    /*create_scripts("Oct19v1_Data_2016_Tau_BlockB",18,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockC",5,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockD",9,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockE",8,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockF",6,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockG",14,"2016","data");
    create_scripts("Oct19v1_Data_2016_Tau_BlockH",16,"2016","data");
    */

    //2017

    /*
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockC",17,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleElectron_BlockF",19,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockC",17,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockF",19,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockC",17,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleEG_BlockF",19,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockC",17,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_DoubleMu_BlockF",19,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_MuonEG_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockC",18,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_MuonEG_BlockF",19,"2017","data"); 

    create_scripts("Oct19v1_Data_2017_Tau_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockC",17,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockF",19,"2017","data"); 
    */
  
    // 2018

    /*
    create_scripts("Oct19v1_Data_2018_EGamma_BlockA",56,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockB",28,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockC",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockD",83,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockD",83,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockA",56,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockB",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockC",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_DoubleMu_BlockD",83,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_MuonEG_BlockA",55,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_MuonEG_BlockB",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_MuonEG_BlockC",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_MuonEG_BlockD",85,"2018","data"); 

    create_scripts("Oct19v1_Data_2018_Tau_BlockA",55,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_Tau_BlockB",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_Tau_BlockC",26,"2018","data"); 
    create_scripts("Oct19v1_Data_2018_Tau_BlockD",89,"2018","data"); 
    */

}

void launch_scripts_all(){

    //2016

    /*launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14,"2016","data");
    launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15,"2016","data");

    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14,"2016","data");
    launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","data");

    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16,"2016","data");
    launch_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15,"2016","data");

    launch_scripts("Oct19v1_Data_2016_Tau_BlockB",18,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockC",5,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockD",9,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockE",8,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockF",6,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_Tau_BlockG",14,"2016","data");
    launch_scripts("Oct19v1_Data_2016_Tau_BlockH",16,"2016","data");
    */

    //2017

    /*
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockB",8,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockC",17,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockD",9,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockE",14,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleElectron_BlockF",19,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockB",8,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockC",17,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockD",9,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockE",14,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_SingleMuon_BlockF",19,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockB",8,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockC",17,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockD",9,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockE",14,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleEG_BlockF",19,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockB",8,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockC",17,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockD",9,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockE",14,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_DoubleMu_BlockF",19,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockB",8,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockC",18,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockD",9,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockE",14,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_MuonEG_BlockF",19,"2017","data"); 

    launch_scripts("Oct19v1_Data_2017_Tau_BlockB",8,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockC",17,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockD",9,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockE",14,"2017","data"); 
    launch_scripts("Oct19v1_Data_2017_Tau_BlockF",19,"2017","data"); 
    */
  
    // 2018

    /*
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockA",56,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockB",28,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockC",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_EGamma_BlockD",83,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_SingleMuon_BlockD",83,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockA",56,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockB",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockC",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_DoubleMu_BlockD",83,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockA",55,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockB",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockC",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_MuonEG_BlockD",85,"2018","data"); 

    launch_scripts("Oct19v1_Data_2018_Tau_BlockA",55,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_Tau_BlockB",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_Tau_BlockC",26,"2018","data"); 
    launch_scripts("Oct19v1_Data_2018_Tau_BlockD",89,"2018","data"); 
    */

}

void launch_single_script_all(){

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",0,"2016","data"); // 1,3,5,7-8,14-17->done / 0,2,4,6,9,10,11,12,13
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",2,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",4,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",6,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",9,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",10,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",11,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",12,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockB",3,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockC",0,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockC",3,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockC",4,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockD",8,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockE",0,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockE",3,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockF",3,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockF",4,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockG",3,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockG",6,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockG",7,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockG",9,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockG",11,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockG",13,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockH",1,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleEG_BlockH",14,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockB",6,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockB",11,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockB",12,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockB",13,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockC",1,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockC",3,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockC",4,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockD",0,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockF",2,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockG",12,"2016","data");

launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockH",11,"2016","data");
launch_single_script("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","data");

launch_single_script("Oct19v1_Data_2016_MuonEG_BlockB",0,"2016","data"); // 1-9,11-17->done / 0,10
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockB",10,"2016","data");

launch_single_script("Oct19v1_Data_2016_MuonEG_BlockC",1,"2016","data");  // 0,2-5->done / 1

launch_single_script("Oct19v1_Data_2016_MuonEG_BlockF",0,"2016","data");  // DONE: 2-3,5-6 / 0,1,4
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockF",1,"2016","data");  // DONE: 2-3,5-6 / 0,1,4
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockF",4,"2016","data");  // DONE: 2-3,5-6 / 0,1,4

launch_single_script("Oct19v1_Data_2016_MuonEG_BlockG",7,"2016","data"); // DONE: 0-6,8-12,14-16 / 7,13
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockG",13,"2016","data"); 

launch_single_script("Oct19v1_Data_2016_MuonEG_BlockH",1,"2016","data"); // DONE: 0,2-5,8-10,12-15 / 1,6,7,11
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockH",6,"2016","data");
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockH",7,"2016","data");
launch_single_script("Oct19v1_Data_2016_MuonEG_BlockH",11,"2016","data");

}