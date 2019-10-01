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
    myscript << "convert_tree(\""+sample+"\",0,"<< j << ",true,0,0,"+year+");\n";
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

void launch_one_script( TString sample="MC_2016_v2_ttHnobb", int isplit=0, TString year="2016", TString type="MC" ){
       
  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += Form("script_tier3_"+type+"/"+year+"/convert_"+sample+"_%i.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
        

}



void create_scripts_all(){

    /*
    //// signal 2016
    create_scripts( "MC_2016_v2_ttHnobb", 0, "2016", "MC" ); //0 -> done
    create_scripts( "MC_2016_v1_THQ_Tune8M1_ctcvcp", 0, "2016", "MC" ); // 0 -> done
    create_scripts( "MC_2016_v1_THW_Tune8M1_ctcvcp", 0, "2016", "MC"); // 0 -> done
    create_scripts( "MC_2016_v1_ttH_ctcvcp", 1, "2016", "MC" ); // 0, 1 -> done

    //// signal 2017
    create_scripts( "MC_2017_v1_ttHJetToNonbb", 2, "2017", "MC" ); //0, 2 -> done, 1 -> RUNNING
    create_scripts( "MC_2017_v1_THQ_ctcvcp", 2, "2017", "MC" ); // 0,1,2 -> done
    create_scripts( "MC_2017_v1_THW_ctcvcp", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_TTH_ctcvcp", 2, "2017", "MC" ); // 0,1,2 -> done

    //// signal 2018
    create_scripts( "MC_2018_v2_ttHJetToNonbb", 2, "2018", "MC" ); //0,1,2 -> done
    create_scripts( "MC_2018_v1_ttHToNonbb", 2, "2018", "MC"); // 0,2 -> done, 1 -> RUNNING
    create_scripts( "MC_2018_v2_THQ_ctcvcp", 7, "2018", "MC" ); // 0-7 -> done
    create_scripts( "MC_2018_v2_THW_ctcvcp", 4, "2018", "MC"); // 0,1,2,3,4 -> done
    create_scripts( "MC_2018_v2_TTH_ctcvcp", 7, "2018", "MC"); // 0-7 -> done
    */

    /////////////
    /////////////

    /*
    //// ttV 2016
    create_scripts( "MC_2016_v1_TTZ_M10_ext1", 0, "2016", "MC" ); // 0 -> RUNNING
    create_scripts( "MC_2016_v1_TTZ_M10_ext2", 0, "2016", "MC" ); // 0 -> done
    create_scripts( "MC_2016_v2_TTZ_M1to10", 0, "2016", "MC" ); // 0 -> done
    create_scripts( "MC_2016_v1_TTWJets", 0, "2016", "MC" ); // 0 -> done
    create_scripts( "MC_2016_v1_TTWW", 0, "2016", "MC" ); //0 -> done 

    //// ttV 2017
    create_scripts( "MC_2017_v1_TTZ_M10", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_TTZ_M10_PS", 3, "2017", "MC" ); // 0,1,2 -> done
    create_scripts( "MC_2017_v1_TTZ_M1to10", 0, "2017", "MC" ); // 0 -> done
    create_scripts( "MC_2017_v1_TTWJets", 0, "2017", "MC" ); // 0 -> RUNNING
    create_scripts( "MC_2017_v3_TTWJets_PS", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_TTWW", 0, "2017", "MC" ); // 0 -> done 

    //// ttV 2018
    create_scripts( "MC_2018_v1_TTZ_M10", 3, "2018", "MC" ); // 0,1,2,3 -> done
    create_scripts( "MC_2018_v1_TTZ_M1to10", 0, "2018", "MC" ); // 0 -> done
    create_scripts( "MC_2018_v1_TTWJets", 1, "2018", "MC" ); // 0,1 -> done
    create_scripts( "MC_2018_v1_TTWW", 0, "2018", "MC" ); // 0 -> done 
    */

    /////////////
    /////////////

    /*
    //// Single top 2016
    create_scripts( "MC_2016_v1_ST_sCh_lepDecay", 0, "2016", "MC" ); // 0 -> done
    create_scripts( "MC_2016_v2_ST_sCh_lepDecay_PS", 2, "2016", "MC" ); // 0,1,2 -> RUNNING
    create_scripts( "MC_2016_v1_ST_tCh_top", 4, "2016", "MC" ); // 0,1,2,3,4 -> done
    create_scripts( "MC_2016_v1_ST_tCh_antitop", 2, "2016", "MC" ); // 0,1,2 -> done
    create_scripts( "MC_2016_v2_ST_tCh_antitop_PS", 5, "2016", "MC" ); // 0,1,2,3,5 -> done, 4 -> RUNNING
    create_scripts( "MC_2016_v1_ST_tW_top", 0, "2016", "MC" ); // 0 -> done
    create_scripts( "MC_2016_v1_ST_tW_antitop", 0, "2016", "MC" ); // 0 -> RUNNING
    create_scripts( "MC_2016_v1_tWll", 0, "2016", "MC" ); // 0 -> done

    //// Single top 2017
    create_scripts( "MC_2017_v1_ST_sCh_lepDecay", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_ST_sCh_lepDecay_PS", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_ST_tCh_top", 0, "2017", "MC" ); // 0 -> done
    create_scripts( "MC_2017_v1_ST_tCh_top_PS", 23, "2017", "MC" ); // 0,9,18,19,20 -> RUNNING, rest -> done
    create_scripts( "MC_2017_v1_ST_tCh_antitop", 0, "2017", "MC" ); // 0 -> done
    create_scripts( "MC_2017_v1_ST_tCh_antitop_PS", 12, "2017", "MC" ); // 0,2,3,4,10 -> RUNNING, rest -> done
    create_scripts( "MC_2017_v1_ST_tW_top", 1, "2017", "MC" ); // 0 -> RUNNING, 1 -> done
    create_scripts( "MC_2017_v1_ST_tW_top_PS", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_ST_tW_antitop", 1, "2017", "MC" ); // 0,1 -> done
    create_scripts( "MC_2017_v1_ST_tW_antitop_PS", 1, "2017", "MC" ); // 0 -> RUNNING, 1 -> done
    create_scripts( "MC_2017_v1_tWll", 0, "2017", "MC" ); // 0 -> done

    //// Single top 2018
    create_scripts( "MC_2018_v1_ST_sCh_lepDecay", 3, "2018", "MC" ); // 0 -> RUNNING, 1,2,3 -> done
    create_scripts( "MC_2018_v1_ST_tCh_top", 23, "2018", "MC" ); // 2,15,22 -> RUNNING, rest -> done
    create_scripts( "MC_2018_v1_ST_tCh_antitop", 13, "2018", "MC" ); // 4,5,6,7,9,13 -> RUNNING, rest -> done
    create_scripts( "MC_2018_v1_ST_tW_top", 1, "2018", "MC" ); // 0,1 -> RUNNING
    create_scripts( "MC_2018_v1_ST_tW_antitop", 1, "2018", "MC" ); // 0,1 -> done
    create_scripts( "MC_2018_v1_tWll", 0, "2018", "MC" ); // 0 -> done
    */

    /////////////
    /////////////
    
    /*
    //// Double top 2016
    create_scripts( "MC_2016_v1_TTTo2L_PS", 7 , "2016", "MC" );
    create_scripts( "MC_2016_v1_TTToSemiLep_PS", 11 , "2016", "MC" );
    create_scripts( "MC_2016_v1_TTToHad_PS", 7, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTJets_DiLep_v1", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTJets_DiLep_ext", 2, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTJets_TToSingleLep_v1", 0, "2016", "MC" );
    create_scripts( "MC_2016_v2_TTJets_TToSingleLep_ext", 4, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTJets_TbarToSingleLep_v1", 1, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTJets_TbarToSingleLep_ext", 3, "2016", "MC" );

    //// Double top 2017
    create_scripts( "MC_2017_v1_TTJets_DiLep", 6, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTJets_TToSingleLep", 10, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTJets_TbarToSingleLep", 13, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTTo2L", 1, "2017", "MC" );
    create_scripts( "MC_2017_v2_TTTo2L_PS", 10, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTToSemiLep", 8, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTToSemiLep_PS", 21, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTToHad", 6, "2017", "MC" );
    create_scripts( "MC_2017_v2_TTToHad_PS", 20, "2017", "MC" );

    //// Double top 2018
    create_scripts( "MC_2018_v1_TTTo2L", 9, "2018", "MC" );
    create_scripts( "MC_2018_v2_TTToSemiLep", 15, "2018", "MC" );
    create_scripts( "MC_2018_v2_TTToHad", 33, "2018", "MC" );
    create_scripts( "MC_2018_v1_TTJets_DiLep", 8, "2018", "MC" );
    create_scripts( "MC_2018_v1_TTJets_TToSingleLep", 15, "2018", "MC" );
    create_scripts( "MC_2018_v1_TTJets_TbarToSingleLep", 15, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Triboson 2016
    create_scripts( "MC_2016_v1_WWW", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WWZ", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WZZ", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_ZZZ", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WZG", 0, "2016", "MC" );

    //// Triboson 2017
    create_scripts( "MC_2017_v1_WWW", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_WWZ", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_WZZ", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_ZZZ", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_WZG", 0, "2017", "MC" );

    //// Triboson 2018
    create_scripts( "MC_2018_v1_WWW", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_WWZ", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_WZZ", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_ZZZ", 0, "2018", "MC" );
    create_scripts( "MC_2018_v2_WZG", 0, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// EWK 2016
    create_scripts( "MC_2016_v1_WGToLNuG_ext1", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WGToLNuG_ext2", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WGToLNuG_ext3", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_ZGToLLG", 1, "2016", "MC" );
    create_scripts( "MC_2016_v1_TGJetsLep", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTGJets_v1", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTGJets_ext", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WJets_v1", 2, "2016", "MC" );
    create_scripts( "MC_2016_v1_WJets_ext", 4, "2016", "MC" );
    create_scripts( "MC_2016_v1_WWTo2LNu", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WZTo3LNu", 1, "2016", "MC" );
    create_scripts( "MC_2016_v1_ZZTo4L", 0, "2016", "MC" );

    //// EWK 2017
    create_scripts( "MC_2017_v1_WGToLNuG", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_ZGToLLG", 5, "2017", "MC" );
    create_scripts( "MC_2017_v1_TGJetsLep", 1, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTGJets", 1, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTGJets_ext", 2, "2017", "MC" );
    create_scripts( "MC_2017_v2_WJets", 4, "2017", "MC" );
    create_scripts( "MC_2017_v1_WJets_ext", 7, "2017", "MC" );
    create_scripts( "MC_2017_v1_WWTo2LNu", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_WWTo2LNu_PS", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_WZTo3LNu", 1, "2017", "MC" );
    create_scripts( "MC_2017_v1_ZZTo4L", 0, "2017", "MC" );
    create_scripts( "MC_2017_v2_ZZTo4L_ext1", 11, "2017", "MC" );
    create_scripts( "MC_2017_v2_ZZTo4L_ext2", 16, "2017", "MC" );

    //// EWK 2018
    create_scripts( "MC_2018_v1_WGToLNuG", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_ZGToLLG", 2, "2018", "MC" );
    create_scripts( "MC_2018_v1_TGJetsLep", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_TTGJets", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_WJets", 9, "2018", "MC" );
    create_scripts( "MC_2018_v1_WWTo2LNu", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_WZTo3LNu_ext", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_ZZTo4L_ext1", 1, "2018", "MC" );
    create_scripts( "MC_2018_v2_ZZTo4L_ext2", 14, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Higgs 2016
    create_scripts( "MC_2016_v3_GGHToTauTau", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_VBFHToTauTau", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_VHToNonbb", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_ZHTobb", 0, "2016", "MC" );
    create_scripts( "MC_2016_v2_ZHToTauTau", 0, "2016", "MC" );

    //// Higgs 2017
    create_scripts( "MC_2017_v1_GGHToTauTau", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_GGHToTauTau_ext", 1, "2017", "MC" );
    create_scripts( "MC_2017_v1_VBFHToTauTau", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_VHToNonbb", 0, "2017", "MC" );
    create_scripts( "MC_2017_v2_ZHTobb", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_ZHToTauTau", 0, "2017", "MC" );

    //// Higgs 2018
    create_scripts( "MC_2018_v1_GGHToTauTau", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_VBFHToTauTau", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_VHToNonbb", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_ZHTobb", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_ZHTobb_ext", 1, "2018", "MC" );
    create_scripts( "MC_2018_v1_ZHToTauTau", 1, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Rares 2016
    create_scripts( "MC_2016_v1_tZq_ext", 1, "2016", "MC" );
    create_scripts( "MC_2016_v2_tZq_PS", 2, "2016", "MC" );
    create_scripts( "MC_2016_v1_WpWpJJ", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_WW_DS", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_TTTT", 0, "2016", "MC" );
    create_scripts( "MC_2016_v1_DYJets_M10to50", 2, "2016", "MC" );
    create_scripts( "MC_2016_v1_DYJets_M50", 8, "2016", "MC" );

    //// Rares 2017
    create_scripts( "MC_2017_v1_tZq", 2, "2017", "MC" );
    create_scripts( "MC_2017_v1_WpWpJJ", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_WW_DS", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTTT", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_TTTT_PS", 0, "2017", "MC" );
    create_scripts( "MC_2017_v1_DYJets_M10to50", 4, "2017", "MC" );
    create_scripts( "MC_2017_v1_DYJets_M10to50_ext", 4, "2017", "MC" );
    create_scripts( "MC_2017_v1_DYJets_M50", 3, "2017", "MC" );
    create_scripts( "MC_2017_v1_DYJets_M50_ext", 19, "2017", "MC" );

    //// Rares 2018
    create_scripts( "MC_2018_v1_tZq", 3, "2018", "MC" );
    create_scripts( "MC_2018_v1_WpWpJJ", 0, "2018", "MC" );
    create_scripts( "MC_2018_v2_WW_DS", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_TTTT", 0, "2018", "MC" );
    create_scripts( "MC_2018_v1_DYJets_M10to50", 5, "2018", "MC" );
    create_scripts( "MC_2018_v1_DYJets_M50", 0, "2018", "MC" );
    create_scripts( "MC_2018_v2_DYJets_M50_ext", 28, "2018", "MC" );
    */
}

void launch_scripts_all(){

    /*
    //// signal 2016
    launch_scripts( "MC_2016_v2_ttHnobb", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_THQ_Tune8M1_ctcvcp", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_THW_Tune8M1_ctcvcp", 0, "2016", "MC");
    launch_scripts( "MC_2016_v1_ttH_ctcvcp", 1, "2016", "MC" );

    //// signal 2017
    launch_scripts( "MC_2017_v1_ttHJetToNonbb", 2, "2017", "MC" );
    launch_scripts( "MC_2017_v1_THQ_ctcvcp", 2, "2017", "MC" );
    launch_scripts( "MC_2017_v1_THW_ctcvcp", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTH_ctcvcp", 2, "2017", "MC" );

    //// signal 2018
    launch_scripts( "MC_2018_v2_ttHJetToNonbb", 2, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ttHToNonbb", 2, "2018", "MC");
    launch_scripts( "MC_2018_v2_THQ_ctcvcp", 7, "2018", "MC" );
    launch_scripts( "MC_2018_v2_THW_ctcvcp", 4, "2018", "MC");
    launch_scripts( "MC_2018_v2_TTH_ctcvcp", 7, "2018", "MC");
    */

    /////////////
    /////////////

    /*
    ////ttV 2016
    launch_scripts( "MC_2016_v1_TTZ_M10_ext1", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTZ_M10_ext2", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v2_TTZ_M1to10", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTWJets", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTWW", 0, "2016", "MC" );

    ////ttV 2017
    launch_scripts( "MC_2017_v1_TTZ_M10", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTZ_M10_PS", 3, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTZ_M1to10", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTWJets", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v3_TTWJets_PS", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTWW", 0, "2017", "MC" );

    ////ttV 2018
    launch_scripts( "MC_2018_v1_TTZ_M10", 3, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTZ_M1to10", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTWJets", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTWW", 0, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Single top 2016
    launch_scripts( "MC_2016_v1_ST_sCh_lepDecay", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v2_ST_sCh_lepDecay_PS", 2, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ST_tCh_top", 4, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ST_tCh_antitop", 2, "2016", "MC" );
    launch_scripts( "MC_2016_v2_ST_tCh_antitop_PS", 5, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ST_tW_top", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ST_tW_antitop", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_tWll", 0, "2016", "MC" );

    //// Single top 2017
    launch_scripts( "MC_2017_v1_ST_sCh_lepDecay", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_sCh_lepDecay_PS", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tCh_top", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tCh_top_PS", 23, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tCh_antitop", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tCh_antitop_PS", 12, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tW_top", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tW_top_PS", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tW_antitop", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ST_tW_antitop_PS", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_tWll", 0, "2017", "MC" );

    //// Single top 2018
    launch_scripts( "MC_2018_v1_ST_sCh_lepDecay", 3, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ST_tCh_top", 23, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ST_tCh_antitop", 13, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ST_tW_top", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ST_tW_antitop", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_tWll", 0, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Double top 2016
    launch_scripts( "MC_2016_v1_TTTo2L_PS", 7 , "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTToSemiLep_PS", 11 , "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTToHad_PS", 7, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTJets_DiLep_v1", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTJets_DiLep_ext", 2, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTJets_TToSingleLep_v1", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v2_TTJets_TToSingleLep_ext", 4, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTJets_TbarToSingleLep_v1", 1, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTJets_TbarToSingleLep_ext", 3, "2016", "MC" );

    //// Double top 2017
    launch_scripts( "MC_2017_v1_TTJets_DiLep", 6, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTJets_TToSingleLep", 10, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTJets_TbarToSingleLep", 13, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTTo2L", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v2_TTTo2L_PS", 10, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTToSemiLep", 8, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTToSemiLep_PS", 21, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTToHad", 6, "2017", "MC" );
    launch_scripts( "MC_2017_v2_TTToHad_PS", 20, "2017", "MC" );

    //// Double top 2018
    launch_scripts( "MC_2018_v1_TTTo2L", 9, "2018", "MC" );
    launch_scripts( "MC_2018_v2_TTToSemiLep", 15, "2018", "MC" );
    launch_scripts( "MC_2018_v2_TTToHad", 33, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTJets_DiLep", 8, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTJets_TToSingleLep", 15, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTJets_TbarToSingleLep", 15, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Triboson 2016
    launch_scripts( "MC_2016_v1_WWW", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WWZ", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WZZ", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ZZZ", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WZG", 0, "2016", "MC" );

    //// Triboson 2017
    launch_scripts( "MC_2017_v1_WWW", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WWZ", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WZZ", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ZZZ", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WZG", 0, "2017", "MC" );

    //// Triboson 2018
    launch_scripts( "MC_2018_v1_WWW", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_WWZ", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_WZZ", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ZZZ", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v2_WZG", 0, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// EWK 2016
    launch_scripts( "MC_2016_v1_WGToLNuG_ext1", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WGToLNuG_ext2", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WGToLNuG_ext3", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ZGToLLG", 1, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TGJetsLep", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTGJets_v1", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTGJets_ext", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WJets_v1", 2, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WJets_ext", 4, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WWTo2LNu", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WZTo3LNu", 1, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ZZTo4L", 0, "2016", "MC" );

    //// EWK 2017
    launch_scripts( "MC_2017_v1_WGToLNuG", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ZGToLLG", 5, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TGJetsLep", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTGJets", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTGJets_ext", 2, "2017", "MC" );
    launch_scripts( "MC_2017_v2_WJets", 4, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WJets_ext", 7, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WWTo2LNu", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WWTo2LNu_PS", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WZTo3LNu", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ZZTo4L", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v2_ZZTo4L_ext1", 11, "2017", "MC" );
    launch_scripts( "MC_2017_v2_ZZTo4L_ext2", 16, "2017", "MC" );

    //// EWK 2018
    launch_scripts( "MC_2018_v1_WGToLNuG", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ZGToLLG", 2, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TGJetsLep", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTGJets", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_WJets", 9, "2018", "MC" );
    launch_scripts( "MC_2018_v1_WWTo2LNu", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_WZTo3LNu_ext", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ZZTo4L_ext1", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v2_ZZTo4L_ext2", 14, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Higgs 2016
    launch_scripts( "MC_2016_v3_GGHToTauTau", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_VBFHToTauTau", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_VHToNonbb", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_ZHTobb", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v2_ZHToTauTau", 0, "2016", "MC" );

    //// Higgs 2017
    launch_scripts( "MC_2017_v1_GGHToTauTau", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_GGHToTauTau_ext", 1, "2017", "MC" );
    launch_scripts( "MC_2017_v1_VBFHToTauTau", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_VHToNonbb", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v2_ZHTobb", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_ZHToTauTau", 0, "2017", "MC" );

    //// Higgs 2018
    launch_scripts( "MC_2018_v1_GGHToTauTau", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_VBFHToTauTau", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_VHToNonbb", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ZHTobb", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ZHTobb_ext", 1, "2018", "MC" );
    launch_scripts( "MC_2018_v1_ZHToTauTau", 1, "2018", "MC" );
    */

    /////////////
    /////////////

    /*
    //// Rares 2016
    launch_scripts( "MC_2016_v1_tZq_ext", 1, "2016", "MC" );
    launch_scripts( "MC_2016_v2_tZq_PS", 2, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WpWpJJ", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_WW_DS", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_TTTT", 0, "2016", "MC" );
    launch_scripts( "MC_2016_v1_DYJets_M10to50", 2, "2016", "MC" );
    launch_scripts( "MC_2016_v1_DYJets_M50", 8, "2016", "MC" );

    //// Rares 2017
    launch_scripts( "MC_2017_v1_tZq", 2, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WpWpJJ", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_WW_DS", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTTT", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_TTTT_PS", 0, "2017", "MC" );
    launch_scripts( "MC_2017_v1_DYJets_M10to50", 4, "2017", "MC" );
    launch_scripts( "MC_2017_v1_DYJets_M10to50_ext", 4, "2017", "MC" );
    launch_scripts( "MC_2017_v1_DYJets_M50", 3, "2017", "MC" );
    launch_scripts( "MC_2017_v1_DYJets_M50_ext", 19, "2017", "MC" );

    //// Rares 2018
    launch_scripts( "MC_2018_v1_tZq", 3, "2018", "MC" );
    launch_scripts( "MC_2018_v1_WpWpJJ", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v2_WW_DS", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_TTTT", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v1_DYJets_M10to50", 5, "2018", "MC" );
    launch_scripts( "MC_2018_v1_DYJets_M50", 0, "2018", "MC" );
    launch_scripts( "MC_2018_v2_DYJets_M50_ext", 28, "2018", "MC" );
    */

}

void launch_scripts_single(){

    launch_one_script( "MC_2017_v1_TTWJets", 0, "2017", "MC" );
    launch_one_script( "MC_2016_v2_ST_sCh_lepDecay_PS", 0, "2016", "MC" );
    launch_one_script( "MC_2016_v2_ST_sCh_lepDecay_PS", 1, "2016", "MC" );
    launch_one_script( "MC_2016_v2_ST_sCh_lepDecay_PS", 2, "2016", "MC" );
    launch_one_script( "MC_2016_v2_ST_tCh_antitop_PS", 4, "2016", "MC" );
    launch_one_script( "MC_2016_v1_ST_tW_antitop", 0, "2016", "MC" );
    launch_one_script( "MC_2017_v1_ST_tCh_top_PS", 19, "2017", "MC" );
    launch_one_script( "MC_2017_v1_ST_tCh_antitop_PS", 0, "2017", "MC" );
    launch_one_script( "MC_2017_v1_ST_tCh_antitop_PS", 3, "2017", "MC" );
    launch_one_script( "MC_2018_v1_ST_tCh_top", 15, "2018", "MC" );
    launch_one_script( "MC_2018_v1_ST_tCh_antitop", 4, "2018", "MC" );

}