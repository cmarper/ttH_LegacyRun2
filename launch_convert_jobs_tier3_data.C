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

void create_scripts( TString sample="Oct19v1_Data_2016_SingleEle_BlockB_0000", int maxsplit=0, TString year="2016", TString type="MC" ){

 for(int j=0;j<maxsplit+1;j++){ //maxsplit -> blocks of 100 files in crab

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


void launch_scripts( TString sample="Oct19v1_Data_2016_SingleEle_BlockB_0000", int maxsplit=0, TString year="2016", TString type="MC" ){
       
  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

}

void launch_single_script( TString sample="Oct19v1_Data_2016_SingleEle_BlockB_0000", int isplit=0, TString year="2016", TString type="MC" ){
       
  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
        
}



void create_scripts_all(){

    //2016

    /*
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockB_0001",0,"2016","data"); //DONE
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockD_missing1_0000",0,"2016","data"); //DONE
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockE_missing1_0000",0,"2016","data"); //DONE
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockF_missing1_0000",0,"2016","data"); //DONE
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockH_0001",0,"2016","data"); //DONE  
    */
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockB_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockC_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockD_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockE_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockF_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockG_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockG_0001",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockH_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockH_missing1_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleEle_BlockH_missing1_0001",0,"2016","data"); //repeat

    /*
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockC_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockD_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockD_missing1_0000",0,"2016","data"); //DONE
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockE_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockF_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockF_missing1_0000",0,"2016","data"); //DONE
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockG_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockG_0001",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockH_0000",0,"2016","data"); //repeat
    create_scripts("Oct19v1_Data_2016_SingleMu_BlockH_0001",0,"2016","data"); //DONE
    */
    
}

void launch_scripts_all(){

    //2016
    /*
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockB_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockB_0001",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockC_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockD_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockD_missing1_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockE_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockE_missing1_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockF_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockF_missing1_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockG_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockG_0001",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_0001",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_missing1_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_missing1_0001",0,"2016","data");
    */

    /*launch_scripts("Oct19v1_Data_2016_SingleMu_BlockC_0000",0,"2016","data"); 
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockD_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockD_missing1_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockE_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockF_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockF_missing1_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockG_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockG_0001",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockH_0000",0,"2016","data");
    launch_scripts("Oct19v1_Data_2016_SingleMu_BlockH_0001",0,"2016","data");*/

    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockB_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockC_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockD_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockE_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockF_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockG_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockG_0001",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_0000",0,"2016","data"); //could be done->check
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_missing1_0000",0,"2016","data"); //repeat
    launch_scripts("Oct19v1_Data_2016_SingleEle_BlockH_missing1_0001",0,"2016","data"); //could be done->check

}

void launch_single_script_all(){

    /*launch_single_script("Oct19v1_MC_2016_THQ_ctcvcp", 0, "2016", "MC");*/

}