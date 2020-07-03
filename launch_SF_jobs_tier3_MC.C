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

    TString ScriptName = "script_tier3_SF/"+year+"/addSF_"+sample+"_JECdown.sh";
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/prodOct19/CMSSW_10_2_16/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_SFs_JEC.C+\n";
    myscript << "loadsample(\""+sample+"\","+year+",\""+type+"\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   


}


void launch_scripts( TString sample="Oct19v1_MC_2016_ttHJetToNonbb", TString year="2016", TString type="ttH" ){
          
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += "script_tier3_SF/"+year+"/addSF_"+sample+"_JECdown.sh";
    gSystem->Exec(LaunchExec.Data());        

}


void create_scripts_all(){

  create_scripts("Oct19v1_MC_2016_ttHJetToNonbb","2016","ttH");
  create_scripts("Oct19v1_MC_2016_THQ_ctcvcp","2016","ttH");
  create_scripts("Oct19v1_MC_2016_THW_ctcvcp","2016","ttH");
  create_scripts("Oct19v1_MC_2017_ttHJetToNonbb","2017","ttH");
  create_scripts("Oct19v1_MC_2017_THQ_ctcvcp","2017","ttH");
  create_scripts("Oct19v3_MC_2017_THW_ctcvcp","2017","ttH");
  create_scripts("Oct19v2_MC_2018_ttHJetToNonbb","2018","ttH");
  create_scripts("Oct19v1_MC_2018_THQ_ctcvcp","2018","ttH");
  create_scripts("Oct19v1_MC_2018_THW_ctcvcp","2018","ttH");
  create_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3","2016","ttV");
  create_scripts("Oct19v1_MC_2016_TTZToLL_M-1to10","2016","ttV");
  create_scripts("Oct19v1_MC_2016_TTWJetsToLNu","2016","ttV");
  create_scripts("Oct19v1_MC_2016_TTWW","2016","ttV");
  create_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS","2017","ttV");
  create_scripts("Oct19v1_MC_2017_TTZToLL_M-1to10","2017","ttV");
  create_scripts("Oct19v1_MC_2017_TTWJetsToLNu","2017","ttV");
  create_scripts("Oct19v1_MC_2017_TTWW","2017","ttV");
  create_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10","2018","ttV");
  create_scripts("Oct19v1_MC_2018_TTZToLL_M-1to10","2018","ttV");
  create_scripts("Oct19v1_MC_2018_TTWJetsToLNu","2018","ttV");
  create_scripts("Oct19v1_MC_2018_TTWW_ext2","2018","ttV");
  create_scripts("Oct19v1_MC_2016_WZTo3LNu","2016","EWK");
  create_scripts("Oct19v1_MC_2016_ZZTo4L","2016","EWK");
  create_scripts("Oct19v1_MC_2017_WZTo3LNu","2017","EWK");
  create_scripts("Oct19v1_MC_2017_ZZTo4L_ext1","2017","EWK");
  create_scripts("Oct19v2_MC_2018_WZTo3LNu_ext1","2018","EWK");
  create_scripts("Oct19v4_MC_2018_ZZTo4L_ext2","2018","EWK");
  create_scripts("Oct19v1_MC_2016_WWW","2016","Rares");
  create_scripts("Oct19v1_MC_2016_WWZ","2016","Rares");
  create_scripts("Oct19v1_MC_2016_WZZ","2016","Rares");
  create_scripts("Oct19v1_MC_2016_ZZZ","2016","Rares");
  create_scripts("Oct19v1_MC_2016_WZG","2016","Rares");
  create_scripts("Oct19v1_MC_2016_WGToLNuG_ext1","2016","Rares");
  create_scripts("Oct19v1_MC_2016_ZGTo2LG","2016","Rares");
  create_scripts("Oct19v1_MC_2016_TGJets_leptonDecays","2016","Rares");
  create_scripts("Oct19v1_MC_2016_TTGJets","2016","Rares");
  create_scripts("Oct19v1_MC_2016_tZq_ll_PS","2016","Rares");
  create_scripts("Oct19v1_MC_2016_WpWpJJ","2016","Rares");
  create_scripts("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering","2016","Rares");
  create_scripts("Oct19v1_MC_2016_TTTT","2016","Rares");
  create_scripts("Oct19v1_MC_2017_WWW","2017","Rares");
  create_scripts("Oct19v1_MC_2017_WWZ","2017","Rares");
  create_scripts("Oct19v2_MC_2017_WZZ","2017","Rares");
  create_scripts("Oct19v2_MC_2017_ZZZ","2017","Rares");
  create_scripts("Oct19v1_MC_2017_WZG","2017","Rares");
  create_scripts("Oct19v1_MC_2017_WGToLNuG","2017","Rares");
  create_scripts("Oct19v1_MC_2017_ZGToLLG","2017","Rares");
  create_scripts("Oct19v1_MC_2017_TGJets","2017","Rares");
  create_scripts("Oct19v1_MC_2017_TTGJets_ext1","2017","Rares");
  create_scripts("Oct19v1_MC_2017_tZq_ll","2017","Rares");
  create_scripts("Oct19v2_MC_2017_WpWpJJ","2017","Rares");
  create_scripts("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering","2017","Rares");
  create_scripts("Oct19v1_MC_2017_TTTT","2017","Rares");
  create_scripts("Oct19v2_MC_2018_WWW","2018","Rares");
  create_scripts("Oct19v2_MC_2018_WWZ","2018","Rares");
  create_scripts("Oct19v1_MC_2018_WZZ","2018","Rares");
  create_scripts("Oct19v1_MC_2018_ZZZ","2018","Rares");
  create_scripts("Oct19v1_MC_2018_WZG","2018","Rares");
  create_scripts("Oct19v1_MC_2018_WGToLNuG","2018","Rares");
  create_scripts("Oct19v2_MC_2018_ZGToLLG","2018","Rares");
  create_scripts("Oct19v1_MC_2018_TGJets","2018","Rares");
  create_scripts("Oct19v1_MC_2018_tZq_ll","2018","Rares");
  create_scripts("Oct19v1_MC_2018_WpWpJJ","2018","Rares");
  create_scripts("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering","2018","Rares");
  create_scripts("Oct19v1_MC_2017_TTJets_DiLept","2017","ttbar");
  create_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromT","2017","ttbar");
  create_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar","2017","ttbar");
  create_scripts("Oct19v1_MC_2018_TTJets_DiLept","2018","ttbar");
  create_scripts("Oct19v1_MC_2018_TTJets_SingleLeptFromT","2018","ttbar");
  create_scripts("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar","2018","ttbar");

}

void launch_scripts_all(){

  launch_scripts("Oct19v1_MC_2016_ttHJetToNonbb","2016","ttH");
  launch_scripts("Oct19v1_MC_2016_THQ_ctcvcp","2016","ttH");
  launch_scripts("Oct19v1_MC_2016_THW_ctcvcp","2016","ttH");
  launch_scripts("Oct19v1_MC_2017_ttHJetToNonbb","2017","ttH");
  launch_scripts("Oct19v1_MC_2017_THQ_ctcvcp","2017","ttH");
  launch_scripts("Oct19v3_MC_2017_THW_ctcvcp","2017","ttH");
  launch_scripts("Oct19v2_MC_2018_ttHJetToNonbb","2018","ttH");
  launch_scripts("Oct19v1_MC_2018_THQ_ctcvcp","2018","ttH");
  launch_scripts("Oct19v1_MC_2018_THW_ctcvcp","2018","ttH");
  launch_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3","2016","ttV");
  launch_scripts("Oct19v1_MC_2016_TTZToLL_M-1to10","2016","ttV");
  launch_scripts("Oct19v1_MC_2016_TTWJetsToLNu","2016","ttV");
  launch_scripts("Oct19v1_MC_2016_TTWW","2016","ttV");
  launch_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS","2017","ttV");
  launch_scripts("Oct19v1_MC_2017_TTZToLL_M-1to10","2017","ttV");
  launch_scripts("Oct19v1_MC_2017_TTWJetsToLNu","2017","ttV");
  launch_scripts("Oct19v1_MC_2017_TTWW","2017","ttV");
  launch_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10","2018","ttV");
  launch_scripts("Oct19v1_MC_2018_TTZToLL_M-1to10","2018","ttV");
  launch_scripts("Oct19v1_MC_2018_TTWJetsToLNu","2018","ttV");
  launch_scripts("Oct19v1_MC_2018_TTWW_ext2","2018","ttV");
  launch_scripts("Oct19v1_MC_2016_WZTo3LNu","2016","EWK");
  launch_scripts("Oct19v1_MC_2016_ZZTo4L","2016","EWK");
  launch_scripts("Oct19v1_MC_2017_WZTo3LNu","2017","EWK");
  launch_scripts("Oct19v1_MC_2017_ZZTo4L_ext1","2017","EWK");
  launch_scripts("Oct19v2_MC_2018_WZTo3LNu_ext1","2018","EWK");
  launch_scripts("Oct19v4_MC_2018_ZZTo4L_ext2","2018","EWK");
  launch_scripts("Oct19v1_MC_2016_WWW","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_WWZ","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_WZZ","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_ZZZ","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_WZG","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_WGToLNuG_ext1","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_ZGTo2LG","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_TGJets_leptonDecays","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_TTGJets","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_tZq_ll_PS","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_WpWpJJ","2016","Rares");
  launch_scripts("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering","2016","Rares");
  launch_scripts("Oct19v1_MC_2016_TTTT","2016","Rares");
  launch_scripts("Oct19v1_MC_2017_WWW","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_WWZ","2017","Rares");
  launch_scripts("Oct19v2_MC_2017_WZZ","2017","Rares");
  launch_scripts("Oct19v2_MC_2017_ZZZ","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_WZG","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_WGToLNuG","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_ZGToLLG","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_TGJets","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_TTGJets_ext1","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_tZq_ll","2017","Rares");
  launch_scripts("Oct19v2_MC_2017_WpWpJJ","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering","2017","Rares");
  launch_scripts("Oct19v1_MC_2017_TTTT","2017","Rares");
  launch_scripts("Oct19v2_MC_2018_WWW","2018","Rares");
  launch_scripts("Oct19v2_MC_2018_WWZ","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_WZZ","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_ZZZ","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_WZG","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_WGToLNuG","2018","Rares");
  launch_scripts("Oct19v2_MC_2018_ZGToLLG","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_TGJets","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_tZq_ll","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_WpWpJJ","2018","Rares");
  launch_scripts("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering","2018","Rares");
  launch_scripts("Oct19v1_MC_2017_TTJets_DiLept","2017","ttbar");
  launch_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromT","2017","ttbar");
  launch_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar","2017","ttbar");
  launch_scripts("Oct19v1_MC_2018_TTJets_DiLept","2018","ttbar");
  launch_scripts("Oct19v1_MC_2018_TTJets_SingleLeptFromT","2018","ttbar");
  launch_scripts("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar","2018","ttbar");

}
