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

    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17,"2016","data"); // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14,"2016","data"); // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15,"2016","data"); // DONE

    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17,"2016","data"); // DONE  
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10,"2016","data"); // DONE  
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14,"2016","data"); // DONE
    //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","data"); // DONE  

    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17,"2016","data"); // DONE
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5,"2016","data");  // DONE 
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8,"2016","data");  // DONE
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6,"2016","data");  // DONE  
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16,"2016","data"); // DONE
    //create_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15,"2016","data"); // DONE 

    /*create_scripts("Oct19v1_Data_2016_Tau_BlockB",18,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockC",5,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockD",9,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockE",8,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockF",6,"2016","data"); 
    create_scripts("Oct19v1_Data_2016_Tau_BlockG",14,"2016","data");
    create_scripts("Oct19v1_Data_2016_Tau_BlockH",16,"2016","data");
    */

    //2017

    //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockB",8,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockC",17,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockD",9,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockE",14,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_SingleElectron_BlockF",19,"2017","data"); // DONE

    //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockB",8,"2017","data");  // DONE
    create_scripts("Oct19v1_Data_2017_SingleMuon_BlockC",17,"2017","data"); // repeat: 4 with data_CMS!!!
    //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockD",9,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockE",14,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_SingleMuon_BlockF",19,"2017","data"); // DONE

    //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockB",8,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockC",17,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockD",9,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockE",14,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleEG_BlockF",19,"2017","data"); // DONE

    //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockB",8,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockC",17,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockD",9,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockE",14,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_DoubleMu_BlockF",19,"2017","data"); // DONE

    //create_scripts("Oct19v1_Data_2017_MuonEG_BlockB",8,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_MuonEG_BlockC",18,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_MuonEG_BlockD",9,"2017","data");  // DONE
    //create_scripts("Oct19v1_Data_2017_MuonEG_BlockE",14,"2017","data"); // DONE
    //create_scripts("Oct19v1_Data_2017_MuonEG_BlockF",19,"2017","data"); // DONE

    /*create_scripts("Oct19v1_Data_2017_Tau_BlockB",8,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockC",17,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockD",9,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockE",14,"2017","data"); 
    create_scripts("Oct19v1_Data_2017_Tau_BlockF",19,"2017","data"); 
    */
  
    // 2018

    create_scripts("Oct19v1_Data_2018_EGamma_BlockA",56,"2018","data"); // running 
    create_scripts("Oct19v1_Data_2018_EGamma_BlockB",28,"2018","data"); // running 
    //create_scripts("Oct19v1_Data_2018_EGamma_BlockC",26,"2018","data"); // DONE
    create_scripts("Oct19v1_Data_2018_EGamma_BlockD",83,"2018","data"); // running

    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55,"2018","data"); // running
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26,"2018","data"); // running
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26,"2018","data"); // running
    /*create_scripts("Oct19v1_Data_2018_SingleMuon_BlockD",83,"2018","data"); 

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
    
    /*launch_scripts("Oct19v1_Data_2018_EGamma_BlockA",56,"2018","data"); 
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

launch_single_script("Oct19v1_Data_2018_EGamma_BlockA",21,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockA",23,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockA",30,"2018","data");

launch_single_script("Oct19v1_Data_2018_EGamma_BlockB",27,"2018","data");

launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",77,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",17,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",1,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",5,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",70,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",69,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",75,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",71,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",26,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",11,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",43,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",65,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",66,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",19,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",74,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",82,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",6,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",73,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",52,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",46,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",32,"2018","data");
launch_single_script("Oct19v1_Data_2018_EGamma_BlockD",33,"2018","data");

launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",42,"2018","data");

}