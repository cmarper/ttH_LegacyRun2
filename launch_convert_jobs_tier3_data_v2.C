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
    create_scripts("Oct19v1_Data_2018_EGamma_BlockC",26,"2018","data"); // running
    create_scripts("Oct19v1_Data_2018_EGamma_BlockD",83,"2018","data"); // repeat: 13,18,22,26,30,34,36,42,47,52,57,62,71,56,15,55,19,81,82,43,48,59,46,53,20,45,6,66,27,33,51,70,44,77,8,60,0,4,12,32,65,37,9,73,35,79,17,5,29,80,1,11,25,69,75,41,38,74

    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockA",55,"2018","data"); // repeat: 20,25,5,41,13,2,49,30,33,24,6,48,45,27,38,16,31,4,52,19,17,42,50,47,26,1,51,53
    create_scripts("Oct19v1_Data_2018_SingleMuon_BlockB",26,"2018","data"); // running
    /*create_scripts("Oct19v1_Data_2018_SingleMuon_BlockC",26,"2018","data"); 
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

launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",19,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",41,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",12,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",6,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",33,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",26,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",47,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",34,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",52,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",5,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",42,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",53,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",13,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",32,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",50,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",49,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",38,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",39,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",31,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",23,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",43,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",44,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",25,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",45,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",18,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",10,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",24,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",4,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",48,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",1,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",16,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",55,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",30,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",17,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",37,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",51,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",22,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",3,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockA",21,"2018","data");

launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",14,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",2,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",26,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",16,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",23,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",17,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",18,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",24,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",0,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",7,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",9,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",6,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",12,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",11,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",19,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",5,"2018","data");
launch_single_script("Oct19v1_Data_2018_SingleMuon_BlockB",1,"2018","data");

}