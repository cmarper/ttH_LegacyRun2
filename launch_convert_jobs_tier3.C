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



void create_scripts( TString sample="MC_2016_v2_ttHnobb", int maxsplit=0, TString year="2016", TString type="MC" ){

 for(int j=0;j<maxsplit+1;j++){

    TString ScriptName = Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/dataprod_legacyRun2/CMSSW_10_2_14/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_converter_v15.C+\n";
    myscript << "convert_tree(\"MC_2016_v2_ttHnobb\",0,"<< j << ",true,0,0,"+year+");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

}


void launch_scripts( TString sample="MC_2016_v2_ttHnobb", int maxsplit=0, TString year="2016", TString type="MC" ){
       
  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

}


void create_scripts_all(){

    //// signal 2016
    create_scripts( "MC_2016_v2_ttHnobb", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_THQ_Tune8M1_ctcvcp", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_THW_Tune8M1_ctcvcp", 0, "2016", "MC");
    create_scripts( "MC_2016_v1_ttH_ctcvcp", 1, "2016", "MC" );

    //// signal 2017
    /*create_scripts( "MC_2017_v1_ttHJetToNonbb", 2, "2017", "MC" );
    create_scripts( "MC_2017_v1_THQ_ctcvcp", 2, "2017", "MC" );
    create_scripts( "MC_2017_v1_THW_ctcvcp", 1, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTH_ctcvcp", 2, "2017", "MC" );*/

    //// signal 2018
    /*create_scripts( "MC_2018_v2_ttHJetToNonbb", 2, "2018", "MC" );
    create_scripts( "MC_2018_v1_ttHToNonbb", 2, "2018", "MC");
    create_scripts( "MC_2018_v2_THQ_ctcvcp", 7, "2018", "MC" );
    create_scripts( "MC_2018_v2_THW_ctcvcp", 4, "2018", "MC");
    create_scripts( "MC_2018_v2_TTH_ctcvcp", 7, "2018", "MC");*/

}

void launch_scripts_all(){

    //// signal 2016
    launch_scripts( "MC_2016_v2_ttHnobb", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_THQ_Tune8M1_ctcvcp", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_THW_Tune8M1_ctcvcp", 0, "2016", "MC");
    launch_scripts( "MC_2016_v1_ttH_ctcvcp", 1, "2016", "MC" );

    //// signal 2017
    /*launch_scripts( "MC_2017_v1_ttHJetToNonbb", 2, "2017", "MC" );
    launch_scripts( "MC_2017_v1_THQ_ctcvcp", 2, "2017", "MC" );
    launch_scripts( "MC_2017_v1_THW_ctcvcp", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTH_ctcvcp", 2, "2017", "MC" );*/

    //// signal 2018
    /*launch_scripts( "MC_2018_v2_ttHJetToNonbb", 2, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ttHToNonbb", 2, "2018", "MC");
    launch_scripts( "MC_2018_v2_THQ_ctcvcp", 7, "2018", "MC" );
    launch_scripts( "MC_2018_v2_THW_ctcvcp", 4, "2018", "MC");
    launch_scripts( "MC_2018_v2_TTH_ctcvcp", 7, "2018", "MC");*/

}
