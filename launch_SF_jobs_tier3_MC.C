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
// compile add_SF_v1.C+

void create_scripts( TString sample="Oct19v1_MC_2016_ttHJetToNonbb", TString year="2016", TString type="ttH" ){

    TString ScriptName = "script_tier3_SF/"+year+"/addSF_"+sample+"_v5.sh";
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/prodOct19/CMSSW_10_2_16/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_SFs_v5.C+\n";
    myscript << "loadsample(\""+sample+"\","+year+",\""+type+"\",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   


}


void launch_scripts( TString sample="Oct19v1_MC_2016_ttHJetToNonbb", TString year="2016", TString type="ttH" ){
          
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += "script_tier3_SF/"+year+"/addSF_"+sample+"_v5.sh";
    gSystem->Exec(LaunchExec.Data());        

}


void create_scripts_all(){

    //2016

    //create_scripts("Oct19v1_MC_2016_ttHJetToNonbb","2016","ttH");
    //create_scripts("Oct19v1_MC_2016_THQ_ctcvcp","2016","ttH");
    //create_scripts("Oct19v1_MC_2016_THW_ctcvcp","2016","ttH");

    //create_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2","2016","ttV");
    //create_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3","2016","ttV");
    //create_scripts("Oct19v1_MC_2016_TTWJetsToLNu","2016","ttV");

    //create_scripts("Oct19v2_MC_2016_tZq_ll","2016","Rares");
    //create_scripts("Oct19v1_MC_2016_tZq_ll_PS","2016","Rares");
    //create_scripts("Oct19v1_MC_2016_TTTT","2016","Rares");

    //2017

    //create_scripts("Oct19v1_MC_2017_ttHJetToNonbb","2017","ttH");
    //create_scripts("Oct19v1_MC_2017_THQ_ctcvcp","2017","ttH");
    //create_scripts("Oct19v3_MC_2017_THW_ctcvcp","2017","ttH");
    //create_scripts("Oct19v1_MC_2017_TTH_ctcvcp","2017","ttH");

    //create_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10","2017","ttV");
    //create_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS","2017","ttV");
    //create_scripts("Oct19v1_MC_2017_TTWJetsToLNu","2017","ttV");
    //create_scripts("Oct19v1_MC_2017_TTWJetsToLNu_PS","2017","ttV");

    //create_scripts("Oct19v1_MC_2017_tZq_ll","2017","Rares"); 
    //create_scripts("Oct19v1_MC_2017_TTTT","2017","Rares");
    //create_scripts("Oct19v1_MC_2017_TTTT_PS","2017","Rares");

    //2018

    //create_scripts("Oct19v2_MC_2018_ttHJetToNonbb","2018","ttH");
    ///create_scripts("Oct19v2_MC_2018_TTH_ctcvcp","2018","ttH");
    //create_scripts("Oct19v1_MC_2018_THQ_ctcvcp","2018","ttH");
    //create_scripts("Oct19v1_MC_2018_THW_ctcvcp","2018","ttH");

    //create_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10","2018","ttV"); 
    //create_scripts("Oct19v1_MC_2018_TTWJetsToLNu","2018","ttV");

    //create_scripts("Oct19v1_MC_2018_tZq_ll","2018","Rares");
    //create_scripts("Oct19v1_MC_2018_TTTT","2018","Rares");


}

void launch_scripts_all(){

    //2016

    //launch_scripts("Oct19v1_MC_2016_ttHJetToNonbb","2016","ttH");
    //launch_scripts("Oct19v1_MC_2016_THQ_ctcvcp","2016","ttH");
    //launch_scripts("Oct19v1_MC_2016_THW_ctcvcp","2016","ttH");

    //launch_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2","2016","ttV");
    //launch_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3","2016","ttV");
    //launch_scripts("Oct19v1_MC_2016_TTWJetsToLNu","2016","ttV");

    //launch_scripts("Oct19v2_MC_2016_tZq_ll","2016","Rares");
    //launch_scripts("Oct19v1_MC_2016_tZq_ll_PS","2016","Rares");
    //launch_scripts("Oct19v1_MC_2016_TTTT","2016","Rares");

    //2017

    launch_scripts("Oct19v1_MC_2017_ttHJetToNonbb","2017","ttH"); // running
    //launch_scripts("Oct19v1_MC_2017_THQ_ctcvcp","2017","ttH");
    //launch_scripts("Oct19v3_MC_2017_THW_ctcvcp","2017","ttH");
    //launch_scripts("Oct19v1_MC_2017_TTH_ctcvcp","2017","ttH");

    //launch_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10","2017","ttV");
    launch_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS","2017","ttV"); // running
    //launch_scripts("Oct19v1_MC_2017_TTWJetsToLNu","2017","ttV");
    //launch_scripts("Oct19v1_MC_2017_TTWJetsToLNu_PS","2017","ttV");

    launch_scripts("Oct19v1_MC_2017_tZq_ll","2017","Rares"); // running
    //launch_scripts("Oct19v1_MC_2017_TTTT","2017","Rares");
    //launch_scripts("Oct19v1_MC_2017_TTTT_PS","2017","Rares");

    //2018

    //launch_scripts("Oct19v2_MC_2018_ttHJetToNonbb","2018","ttH");
    launch_scripts("Oct19v2_MC_2018_TTH_ctcvcp","2018","ttH"); // running
    //launch_scripts("Oct19v1_MC_2018_THQ_ctcvcp","2018","ttH");
    //launch_scripts("Oct19v1_MC_2018_THW_ctcvcp","2018","ttH");

    launch_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10","2018","ttV"); // running
    //launch_scripts("Oct19v1_MC_2018_TTWJetsToLNu","2018","ttV");

    //launch_scripts("Oct19v1_MC_2018_tZq_ll","2018","Rares");
    //launch_scripts("Oct19v1_MC_2018_TTTT","2018","Rares");

}