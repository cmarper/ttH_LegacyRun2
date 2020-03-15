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

void create_scripts( TString sample="Oct19v1_MC_2016_THQ_ctcvcp", int maxsplit=0, TString year="2016", TString type="MC" ){

 for(int j=0;j<maxsplit+1;j++){

    TString ScriptName = Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i_newConePt.sh",j);
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
    myscript << ".L tree_converter_Oct19_v2_newConePt.C+\n";
    myscript << "convert_tree(\""+sample+"\",0,"<< j << ",0,0,true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

}


void launch_scripts( TString sample="Oct19v1_MC_2016_THQ_ctcvcp", int maxsplit=0, TString year="2016", TString type="MC" ){
       
  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i_newConePt.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

}

void launch_single_script( TString sample="Oct19v1_MC_2016_THQ_ctcvcp", int isplit=0, TString year="2016", TString type="MC" ){
       
  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
  LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i_newConePt.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
        
}



void create_scripts_all(){

    create_scripts("Oct19v1_MC_2016_ttHJetToNonbb",0,"2016","MC");
    create_scripts("Oct19v1_MC_2017_ttHJetToNonbb",2,"2017","MC");
    create_scripts("Oct19v2_MC_2018_ttHJetToNonbb",2,"2018","MC");

    create_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",0,"2016","MC");
    create_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",3,"2017","MC");
    create_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10",3,"2018","MC");

    create_scripts("Oct19v1_MC_2016_TTWJetsToLNu",0,"2016","MC");
    create_scripts("Oct19v1_MC_2017_TTWJetsToLNu",0,"2017","MC");
    create_scripts("Oct19v1_MC_2018_TTWJetsToLNu",1,"2018","MC");
    
}

void launch_scripts_all(){

    launch_scripts("Oct19v1_MC_2016_ttHJetToNonbb",0,"2016","MC");
    launch_scripts("Oct19v1_MC_2017_ttHJetToNonbb",2,"2017","MC");
    launch_scripts("Oct19v2_MC_2018_ttHJetToNonbb",2,"2018","MC");

    launch_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",0,"2016","MC");
    launch_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",3,"2017","MC");
    launch_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10",3,"2018","MC");

    launch_scripts("Oct19v1_MC_2016_TTWJetsToLNu",0,"2016","MC");
    launch_scripts("Oct19v1_MC_2017_TTWJetsToLNu",0,"2017","MC");
    launch_scripts("Oct19v1_MC_2018_TTWJetsToLNu",1,"2018","MC");

}

void launch_single_script_all(){

}