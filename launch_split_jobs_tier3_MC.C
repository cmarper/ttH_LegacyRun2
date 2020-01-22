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
// compile tree_splitter

void create_scripts( TString sample="Oct19v1_MC_2016_ttHJetToNonbb", int maxsplit=0, TString year="2016", TString type="ttH" ){

  TString dirin = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/";
  dirin += year;
  dirin += "/nominal/";
  dirin += type;
  dirin += "/";

  //cout<<dirin<<endl;

  TString dirout = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/";
  dirout += year;
  dirout += "/nominal/";
  dirout += type;
  dirout += "/";

  //cout<<dirout<<endl;

  for(int j=0;j<maxsplit+1;j++){ 

    std::string isample = std::to_string(j);

    TString filename = "ntuple_"+sample+"_"+isample+".root";

    //cout<<filename<<endl;

    TString ScriptName = Form("script_tier3_MC/"+year+"/split_"+sample+"_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/prodOct19/CMSSW_10_2_16/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_Oct19_v1.C+\n";
    myscript << "split_tree(\""+dirin+filename+"\",\""+dirout+filename+"\",0,0,true,"+year+");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

}


void launch_scripts( TString sample="Oct19v1_MC_2016_ttHJetToNonbb", int maxsplit=0, TString year="2016", TString type="ttH" ){

  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3_MC/"+year+"/split_"+sample+"_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
 
  }

}

void launch_single_script( TString sample="Oct19v1_MC_2016_THQ_ctcvcp", int isplit=0, TString year="2016", TString type="MC" ){

  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += Form("script_tier3_MC/"+year+"/split_"+sample+"_%i.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
 
}



void create_scripts_all(){

    //ttH  ---> RUNNING

    /*
    create_scripts("Oct19v1_MC_2016_ttHJetToNonbb", 0,"2016","ttH"); // DONE
    create_scripts("Oct19v1_MC_2016_ttH_ctcvcp", 1, "2016","ttH");   // DONE
    create_scripts("Oct19v1_MC_2016_THQ_ctcvcp", 1, "2016", "ttH");  // DONE
    create_scripts("Oct19v1_MC_2016_THW_ctcvcp", 1, "2016", "ttH");  // DONE
    */

    /*
    create_scripts("Oct19v1_MC_2017_ttHJetToNonbb", 2, "2017", "ttH"); // DONE
    create_scripts("Oct19v1_MC_2017_THQ_ctcvcp", 2, "2017", "ttH");    // DONE
    create_scripts("Oct19v3_MC_2017_THW_ctcvcp", 1, "2017","ttH");     // DONE
    create_scripts("Oct19v1_MC_2017_TTH_ctcvcp", 2, "2017", "ttH");    // DONE
    */

    /*
    create_scripts("Oct19v2_MC_2018_ttHJetToNonbb",2,"2018","ttH");     // DONE
    create_scripts("Oct19v2_MC_2018_TTH_ctcvcp", 7, "2018","ttH");      // DONE
    create_scripts("Oct19v1_MC_2018_THQ_ctcvcp", 7, "2018", "ttH");     // DONE
    create_scripts("Oct19v1_MC_2018_THW_ctcvcp", 4, "2018", "ttH");     // DONE
    */

    //ttV  ---> DONE

    /*
    create_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2",0,"2016","ttV"); // DONE
    create_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",0,"2016","ttV"); // DONE
    create_scripts("Oct19v1_MC_2016_TTZToLL_M-1to10", 0, "2016", "ttV" );   // DONE 
    create_scripts("Oct19v1_MC_2016_TTWJetsToLNu",0,"2016","ttV");          // DONE
    create_scripts("Oct19v1_MC_2016_TTWW", 0, "2016", "ttV" );              // DONE

    create_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10", 1, "2017", "ttV" );  // DONE
    create_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",3,"2017","ttV");   // DONE
    create_scripts("Oct19v1_MC_2017_TTZToLL_M-1to10", 0, "2017", "ttV" );   // DONE    
    create_scripts("Oct19v1_MC_2017_TTWJetsToLNu", 0, "2017", "ttV" );      // DONE
    create_scripts("Oct19v1_MC_2017_TTWJetsToLNu_PS",1,"2017","ttV");       // DONE
    create_scripts("Oct19v1_MC_2017_TTWW", 0,"2017", "ttV" );               // DONE

    create_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10", 3, "2018", "ttV" );  // DONE
    create_scripts("Oct19v1_MC_2018_TTZToLL_M-1to10", 0, "2018", "ttV" );   // DONE 
    create_scripts("Oct19v1_MC_2018_TTWJetsToLNu", 1, "2018", "ttV" );      // DONE
    create_scripts("Oct19v1_MC_2018_TTWW_ext1", 0, "2018", "ttV" );         // DONE
    create_scripts("Oct19v1_MC_2018_TTWW_ext2", 0, "2018", "ttV" );         // DONE
    */

    // Rares  ---> DONE

    /*
    create_scripts("Oct19v1_MC_2016_WWW",0,"2016", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2016_WWZ",0,"2016", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2016_WZZ",0,"2016", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2016_ZZZ",0,"2016", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2016_WZG",0,"2016", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2016_WGToLNuG_ext1",0,"2016", "Rares");              // DONE
    create_scripts("Oct19v1_MC_2016_WGToLNuG_ext2",0,"2016", "Rares");              // DONE
    create_scripts("Oct19v1_MC_2016_WGToLNuG_ext3",0,"2016","Rares");               // DONE
    create_scripts("Oct19v1_MC_2016_ZGTo2LG",1,"2016", "Rares");                    // DONE
    create_scripts("Oct19v1_MC_2016_TGJets_leptonDecays",0,"2016", "Rares");        // DONE
    create_scripts("Oct19v1_MC_2016_TTGJets",0,"2016", "Rares");                    // DONE
    create_scripts("Oct19v1_MC_2016_TTGJets_ext1",0,"2016", "Rares");               // DONE
    create_scripts("Oct19v2_MC_2016_tZq_ll",1,"2016", "Rares");                     // DONE
    create_scripts("Oct19v1_MC_2016_tZq_ll_PS",2,"2016","Rares");                   // DONE
    create_scripts("Oct19v1_MC_2016_WpWpJJ",0,"2016", "Rares");                     // DONE
    create_scripts("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering",0,"2016","Rares");  // DONE
    create_scripts("Oct19v1_MC_2016_TTTT",0,"2016", "Rares");                       // DONE
    */

    /*
    create_scripts("Oct19v1_MC_2017_WWW",0,"2017", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2017_WWZ",0,"2017","Rares");                         // DONE
    create_scripts("Oct19v2_MC_2017_WZZ",0,"2017","Rares");                         // DONE
    create_scripts("Oct19v2_MC_2017_ZZZ",0,"2017","Rares");                         // DONE
    create_scripts("Oct19v1_MC_2017_WZG",0,"2017", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2017_WGToLNuG",1,"2017","Rares");                    // DONE
    create_scripts("Oct19v1_MC_2017_ZGToLLG",3,"2017","Rares");                     // DONE
    create_scripts("Oct19v1_MC_2017_TGJets",1,"2017", "Rares");                     // DONE
    create_scripts("Oct19v1_MC_2017_TTGJets",1,"2017", "Rares");                    // DONE
    create_scripts("Oct19v1_MC_2017_TTGJets_ext1",2,"2017", "Rares");               // DONE
    create_scripts("Oct19v1_MC_2017_tZq_ll",2,"2017", "Rares");                     // DONE
    create_scripts("Oct19v2_MC_2017_WpWpJJ",0,"2017","Rares");                      // DONE
    create_scripts("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering",0,"2017","Rares");  // DONE  
    create_scripts("Oct19v1_MC_2017_TTTT",0,"2017", "Rares");                       // DONE
    create_scripts("Oct19v1_MC_2017_TTTT_PS",0,"2017", "Rares");                    // DONE
    */

    /*
    create_scripts("Oct19v2_MC_2018_WWW",0,"2018","Rares");                         // DONE
    create_scripts("Oct19v2_MC_2018_WWZ",0,"2018","Rares");                         // DONE
    create_scripts("Oct19v1_MC_2018_WZZ",0,"2018", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2018_ZZZ",0,"2018", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2018_WZG",0,"2018", "Rares");                        // DONE
    create_scripts("Oct19v1_MC_2018_WGToLNuG",1,"2018","Rares");                    // DONE
    create_scripts("Oct19v2_MC_2018_ZGToLLG",4,"2018","Rares");                     // DONE
    create_scripts("Oct19v1_MC_2018_TGJets",1,"2018","Rares");                      // DONE
    create_scripts("Oct19v1_MC_2018_TTGJets",1,"2018","Rares");                     // DONE
    create_scripts("Oct19v1_MC_2018_tZq_ll",3,"2018", "Rares");                     // DONE
    create_scripts("Oct19v1_MC_2018_WpWpJJ",0,"2018", "Rares");                     // DONE 
    create_scripts("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering",0,"2018", "Rares"); // DONE
    create_scripts("Oct19v1_MC_2018_TTTT",0,"2018", "Rares");                       // DONE  
    */

    // EWK ---> DONE
    /*
    create_scripts("Oct19v1_MC_2016_DYJetsToLL_M-10to50",2,"2016","EWK");       // DONE
    create_scripts("Oct19v1_MC_2016_DYJetsToLL_M-50", 7, "2016", "EWK");        // DONE
    create_scripts("Oct19v1_MC_2016_WJetsToLNu_ext2",2,"2016","EWK");           // DONE
    create_scripts("Oct19v1_MC_2016_WJetsToLNu", 2, "2016", "EWK");             // DONE
    create_scripts("Oct19v1_MC_2016_WWTo2L2Nu", 0, "2016", "EWK");              // DONE
    create_scripts("Oct19v1_MC_2016_WZTo3LNu", 0, "2016", "EWK");               // DONE
    create_scripts("Oct19v1_MC_2016_ZZTo4L", 0, "2016", "EWK");                 // DONE

    create_scripts("Oct19v1_MC_2017_DYJetsToLL_M-10to50", 4, "2017", "EWK");    // DONE
    create_scripts("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",4,"2017","EWK");  // DONE
    create_scripts("Oct19v1_MC_2017_DYJetsToLL_M-50",3,"2017","EWK");           // DONE
    create_scripts("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",7,"2017","EWK");      // DONE
    create_scripts("Oct19v2_MC_2017_WJetsToLNu",4,"2017","EWK");                // DONE
    create_scripts("Oct19v1_MC_2017_WJetsToLNu_ext1", 7 , "2017", "EWK");       // DONE
    create_scripts("Oct19v2_MC_2017_WWTo2L2Nu",0,"2017","EWK");                 // DONE 
    create_scripts("Oct19v1_MC_2017_WWTo2L2Nu_ext1", 0, "2017", "EWK");         // DONE
    create_scripts("Oct19v1_MC_2017_WZTo3LNu", 1, "2017", "EWK");               // DONE
    create_scripts("Oct19v1_MC_2017_ZZTo4L", 0, "2017", "EWK");                 // DONE
    create_scripts("Oct19v1_MC_2017_ZZTo4L_ext1", 11, "2017", "EWK");           // DONE
    create_scripts("Oct19v2_MC_2017_ZZTo4L_ext2",0,"2017","EWK");               // DONE

    create_scripts("Oct19v3_MC_2018_DYJetsToLL_M-10to50",5,"2018","EWK");       // DONE
    create_scripts("Oct19v2_MC_2018_DYJetsToLL_M-50", 0, "2018", "EWK");        // DONE
    create_scripts("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",6,"2018","EWK");      // DONE
    create_scripts("Oct19v2_MC_2018_WJetsToLNu",9,"2018","EWK");                // DONE
    create_scripts("Oct19v3_MC_2018_WWTo2L2Nu",1, "2018","EWK");                // DONE
    create_scripts("Oct19v1_MC_2018_WZTo3LNu", 2, "2018", "EWK");               // DONE
    create_scripts("Oct19v2_MC_2018_WZTo3LNu_ext1",2,"2018","EWK");             // DONE
    create_scripts("Oct19v2_MC_2018_ZZTo4L", 1, "2018", "EWK");                 // DONE
    create_scripts("Oct19v4_MC_2018_ZZTo4L_ext2",7,"2018","EWK");               // DONE
    */

    // ggH  ---> DONE
    /*
    create_scripts("Oct19v1_MC_2016_GluGluHToTauTau",0,"2016", "ggH");      // DONE
    create_scripts("Oct19v1_MC_2016_GluGluHToZZTo4L",0,"2016", "ggH");      // DONE
    create_scripts("Oct19v1_MC_2016_GluGluHToWWToLNuQQ",0,"2016", "ggH");   // DONE
    create_scripts("Oct19v1_MC_2016_GluGluHToWWTo2L2Nu",0,"2016", "ggH");   // DONE
    create_scripts("Oct19v1_MC_2016_GluGluHToMuMu",0,"2016", "ggH");        // DONE
    create_scripts("Oct19v1_MC_2016_GluGluHToBB",0,"2016", "ggH");          // DONE
    create_scripts("Oct19v6_MC_2016_GluGluHToBB_ext1",0,"2016","ggH");      // DONE
    create_scripts("Oct19v1_MC_2016_GluGluHToGG",0,"2016", "ggH");          // DONE

    create_scripts("Oct19v1_MC_2017_GluGluHToTauTau",0,"2017", "ggH");      // DONE
    create_scripts("Oct19v3_MC_2017_GluGluHToTauTau_ext1",1,"2017","ggH");  // DONE
    create_scripts("Oct19v1_MC_2017_GluGluHToZZTo4L_ext1",0,"2017", "ggH"); // DONE  
    create_scripts("Oct19v2_MC_2017_GluGluHToZZTo4L_ext3",0,"2017","ggH");  // DONE 
    create_scripts("Oct19v1_MC_2017_GluGluHToZZTo4L_ext4",0,"2017","ggH");  // DONE 
    create_scripts("Oct19v2_MC_2017_GluGluHToZZTo2L2Q", 0, "2017","ggH");   // DONE
    create_scripts("Oct19v1_MC_2017_GluGluHToWWToLNuQQ",0,"2017", "ggH");   // DONE
    create_scripts("Oct19v1_MC_2017_GluGluHToWWTo2L2Nu",0,"2017", "ggH");   // DONE
    create_scripts("Oct19v3_MC_2017_GluGluHToMuMu",0,"2017","ggH");         // DONE
    create_scripts("Oct19v1_MC_2017_GluGluHToMuMu_ext1",0,"2017", "ggH");   // DONE
    create_scripts("Oct19v2_MC_2017_GluGluHToBB",2,"2017","ggH");           // DONE
    create_scripts("Oct19v3_MC_2017_GluGluHToGG",0, "2017","ggH");          // DONE

    create_scripts("Oct19v2_MC_2018_GluGluHToTauTau", 1, "2018","ggH");     // DONE
    create_scripts("Oct19v1_MC_2018_GluGluHToZZTo4L",0,"2018","ggH");       // DONE
    create_scripts("Oct19v2_MC_2018_GluGluHToZZTo2L2Q",0,"2018","ggH");     // DONE
    create_scripts("Oct19v1_MC_2018_GluGluHToWWToLNuQQ",0,"2018","ggH");    // DONE
    create_scripts("Oct19v2_MC_2018_GluGluHToWWTo2L2Nu",0,"2018","ggH");    // DONE
    create_scripts("Oct19v1_MC_2018_GluGluHToMuMu",0,"2018", "ggH");        // DONE
    create_scripts("Oct19v2_MC_2018_GluGluHToMuMu_ext1",0,"2018","ggH");    // DONE
    create_scripts("Oct19v1_MC_2018_GluGluHToBB",3,"2018", "ggH");          // DONE
    create_scripts("Oct19v1_MC_2018_GluGluHToGG",0,"2018", "ggH");          // DONE
    */

    // VBF  ---> DONE
    /*
    create_scripts("Oct19v2_MC_2016_VBFHToTauTau",0,"2016","VBF");          // DONE
    create_scripts("Oct19v2_MC_2016_VBF_HToZZTo4L",0,"2016","VBF");         // DONE
    create_scripts("Oct19v1_MC_2016_VBFHToWWToLNuQQ", 0, "2016", "VBF");    // DONE
    create_scripts("Oct19v1_MC_2016_VBFHToWWTo2L2Nu", 0, "2016", "VBF");    // DONE
    create_scripts("Oct19v1_MC_2016_VBFHToMuMu", 0, "2016", "VBF");         // DONE
    create_scripts("Oct19v3_MC_2016_VBFHToBB",0,"2016","VBF");              // DONE
    create_scripts("Oct19v1_MC_2016_VBFHToBB_ext1", 0, "2016", "VBF");      // DONE
    create_scripts("Oct19v1_MC_2016_VBFHToGG_ext1", 0, "2016", "VBF");      // DONE
    create_scripts("Oct19v1_MC_2016_VBFHToGG_ext2", 0, "2016", "VBF");      // DONE

    create_scripts("Oct19v1_MC_2017_VBFHToTauTau", 0, "2017", "VBF");       // DONE
    create_scripts("Oct19v2_MC_2017_VBF_HToZZTo4L_ext2",0,"2017","VBF");    // DONE
    create_scripts("Oct19v1_MC_2017_VBF_HToZZTo4L_ext1", 0, "2017", "VBF"); // DONE
    create_scripts("Oct19v1_MC_2017_VBF_HToZZTo4L", 0, "2017", "VBF");      // DONE
    create_scripts("Oct19v1_MC_2017_VBFHToWWToLNuQQ",0,"2017","VBF");       // DONE
    create_scripts("Oct19v1_MC_2017_VBFHToWWTo2L2Nu", 0,"2017", "VBF");     // DONE
    create_scripts("Oct19v1_MC_2017_VBFHToMuMu",0,"2017","VBF");            // DONE
    create_scripts("Oct19v1_MC_2017_VBFHToBB", 0, "2017", "VBF");           // DONE
    create_scripts("Oct19v1_MC_2017_VBFHToGG",0,"2017","VBF");              // DONE
    create_scripts("Oct19v2_MC_2017_VBFHToGG_PS",0,"2017","VBF");           // DONE

    create_scripts("Oct19v1_MC_2018_VBFHToTauTau",0,"2018","VBF");          // DONE
    create_scripts("Oct19v2_MC_2018_VBF_HToZZTo4L",0,"2018","VBF");         // DONE  
    create_scripts("Oct19v2_MC_2018_VBFHToWWToLNuQQ",0,"2018","VBF");       // DONE
    create_scripts("Oct19v1_MC_2018_VBFHToWWTo2L2Nu", 0, "2018", "VBF");    // DONE
    create_scripts("Oct19v1_MC_2018_VBFHToMuMu",0,"2018","VBF");            // DONE
    create_scripts("Oct19v2_MC_2018_VBFHToBB",1,"2018","VBF");              // DONE
    create_scripts("Oct19v2_MC_2018_VBFHToGG",0,"2018","VBF");              // DONE
    */

    // VH   ---> DONE
    /*
    create_scripts("Oct19v1_MC_2016_VHToNonbb", 0, "2016", "VH");           // DONE
    create_scripts("Oct19v1_MC_2016_ZH_HToBB_ZToLL", 0, "2016", "VH");      // DONE
    create_scripts("Oct19v1_MC_2016_ZHToTauTau", 0, "2016", "VH");          // DONE

    create_scripts("Oct19v1_MC_2017_VHToNonbb", 0, "2017", "VH");           // DONE
    create_scripts("Oct19v1_MC_2017_ZH_HToBB_ZToLL", 0, "2017", "VH");      // DONE  
    create_scripts("Oct19v1_MC_2017_ZHToTauTau",0,"2017","VH");             // DONE

    create_scripts("Oct19v2_MC_2018_VHToNonbb",0,"2018","VH");              // DONE
    create_scripts("Oct19v1_MC_2018_ZH_HToBB_ZToLL", 1, "2018", "VH");      // DONE
    create_scripts("Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1",1, "2018","VH");   // DONE
    create_scripts("Oct19v2_MC_2018_ZHToTauTau", 1, "2018", "VH");          // DONE
    */

    // TTVH   ---> DONE
    /*
    create_scripts("Oct19v1_MC_2016_TTWH", 0, "2016", "ttVH");  // DONE 
    create_scripts("Oct19v2_MC_2016_TTZH", 0, "2016", "ttVH");  // DONE

    create_scripts("Oct19v4_MC_2017_TTWH",0,"2017","ttVH");     // DONE
    create_scripts("Oct19v1_MC_2017_TTZH", 0, "2017", "ttVH");  // DONE

    create_scripts("Oct19v1_MC_2018_TTWH", 0, "2018", "ttVH");  // DONE   
    create_scripts("Oct19v2_MC_2018_TTZH", 0, "2018", "ttVH");  // DONE
    */

    // HH  ---> DONE
    /*
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM",0,"2016","HH");    // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box",0,"2016", "HH");  // DONE
    create_scripts("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_1",0,"2016", "HH");    // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2",0,"2016", "HH");    // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3",0,"2016", "HH");    // DONE
    create_scripts("Oct19v4_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_4",0,"2016","HH");     // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_5",0,"2016", "HH");    // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6",0,"2016", "HH");    // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_7",0,"2016","HH");     // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8",0,"2016", "HH");    // DONE
    create_scripts("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9",0,"2016","HH");     // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10",0,"2016","HH");    // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_11",0,"2016","HH");    // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12",0,"2016", "HH");   // DONE
    
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM",0,"2016", "HH");    // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box",0,"2016", "HH");   // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2",0,"2016", "HH");     // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2Tau_node_9",0,"2016","HH");      // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10",0,"2016", "HH");    // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11",0,"2016", "HH");    // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12",0,"2016", "HH");    // DONE
    create_scripts("Oct19v3_MC_2016_GluGluToHHTo2B2Tau_node_13",0,"2016","HH");     // DONE

    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM",0,"2016", "HH");      // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box",0,"2016", "HH");     // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2",0,"2016", "HH");       // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3",0,"2016", "HH");       // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4",0,"2016", "HH");       // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5",0,"2016", "HH");       // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6",0,"2016", "HH");       // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7",0,"2016", "HH");       // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_8",0,"2016","HH");        // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9",0,"2016", "HH");       // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_10",0,"2016","HH");       // DONE
    create_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_11",0,"2016","HH");       // DONE
    create_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12",0,"2016", "HH");      // DONE


    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM",0,"2017","HH");    // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2", 0, "2017","HH");   // ODNE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3",0,"2017","HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_7",0,"2017","HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9",0,"2017","HH");     // DONE
    create_scripts("Oct19v4_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12",0,"2017","HH");    // DONE

    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM",0,"2017", "HH");    // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12",0,"2017", "HH");    // DONE

    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13",0,"2017", "HH");   // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2",0,"2017", "HH");       // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3",0,"2017", "HH");       // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo4Tau_node_7",0,"2017","HH");        // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9",0,"2017", "HH");       // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12",0,"2017", "HH");      // DONE

    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM",0,"2017","HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2",0,"2017", "HH");     // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_3", 0, "2017","HH");    // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6",0,"2017", "HH");     // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_7",0,"2017","HH");      // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10",0,"2017","HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11",0,"2017", "HH");    // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_12",0,"2017","HH");     // DONE

    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_SM",0,"2017", "HH");    // DONE 
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo4V_node_2",0,"2017","HH");      // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_3",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_4",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_5",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_6",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_7",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_8",0,"2017", "HH");     // DONE
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_9",0,"2017", "HH");     // DONE  
    create_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_10",0,"2017", "HH");    // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo4V_node_11",0,"2017", "HH");    // DONE
    create_scripts("Oct19v2_MC_2017_GluGluToHHTo4V_node_12",0,"2017","HH");     // DONE

    
    create_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM",0,"2018", "HH");    // DONE
    create_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_2",0,"2018", "HH");     // DONE
    create_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_3",0,"2018", "HH");     // DONE
    create_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_4",0,"2018", "HH");     // DONE
    create_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_5",0,"2018", "HH");     // DONE
    create_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_6",0,"2018", "HH");     // DONE
    create_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_7",0,"2018", "HH");     // DONE
    create_scripts("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_8",0,"2018", "HH");     // DONE
    create_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_9",0,"2018", "HH");     // DONE
    create_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_10",0,"2018","HH");     // DONE
    create_scripts("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_11",0,"2018","HH");     // DONE
    create_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_12",0,"2018", "HH");    // DONE
    */

    // TT ---> DONE
    /*
    create_scripts("Oct19v1_MC_2016_ST_s-channel",0,"2016", "ttbar");                   // DONE
    create_scripts("Oct19v1_MC_2016_ST_s-channel_PS",2,"2016", "ttbar");                // DONE
    create_scripts("Oct19v1_MC_2016_ST_t-channel_top",4,"2016", "ttbar");               // DONE
    create_scripts("Oct19v1_MC_2016_ST_t-channel_antitop",2,"2016","ttbar");            // DONE
    create_scripts("Oct19v1_MC_2016_ST_t-channel_antitop_PS",4,"2016","ttbar");         // DONE
    create_scripts("Oct19v1_MC_2016_ST_tW_top",0,"2016","ttbar");                       // DONE
    create_scripts("Oct19v1_MC_2016_ST_tW_antitop",0,"2016","ttbar");                   // DONE
    create_scripts("Oct19v1_MC_2016_ST_tWll",0,"2016","ttbar");                         // DONE
    create_scripts("Oct19v1_MC_2016_TTJets_DiLept_ext1",2,"2016", "ttbar");             // DONE
    create_scripts("Oct19v1_MC_2016_TTJets_DiLept",0,"2016", "ttbar");                  // DONE
    create_scripts("Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1",3,"2016","ttbar");     // DONE
    create_scripts("Oct19v1_MC_2016_TTJets_SingleLeptFromT",0,"2016", "ttbar");         // DONE
    create_scripts("Oct19v1_MC_2016_TTJets_SingleLeptFromTbar",1,"2016", "ttbar");      // DONE
    create_scripts("Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1",2,"2016","ttbar");  // DONE

    create_scripts("Oct19v1_MC_2017_ST_s-channel",1,"2017","ttbar");                // DONE
    create_scripts("Oct19v2_MC_2017_ST_s-channel_PS",1,"2017","ttbar");             // DONE
    create_scripts("Oct19v1_MC_2017_ST_t-channel_top",0,"2017", "ttbar");           // DONE
    create_scripts("Oct19v2_MC_2017_ST_t-channel_top_PS",8,"2017","ttbar");         // DONE
    create_scripts("Oct19v1_MC_2017_ST_t-channel_antitop",0,"2017", "ttbar");       // DONE
    create_scripts("Oct19v2_MC_2017_ST_t-channel_antitop_PS",12,"2017","ttbar");    // DONE
    create_scripts("Oct19v3_MC_2017_ST_tW_top",1,"2017","ttbar");                   // DONE
    create_scripts("Oct19v1_MC_2017_ST_tW_top_PS",1,"2017","ttbar");                // DONE
    create_scripts("Oct19v1_MC_2017_ST_tW_antitop",1,"2017","ttbar");               // DONE
    create_scripts("Oct19v1_MC_2017_ST_tW_antitop_PS",1,"2017","ttbar");            // DONE
    create_scripts("Oct19v1_MC_2017_ST_tWll",0,"2017", "ttbar");                    // DONE
    create_scripts("Oct19v1_MC_2017_TTJets_DiLept",6,"2017", "ttbar");              // DONE
    create_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromT",9,"2017", "ttbar");     // DONE
    create_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar",13,"2017","ttbar");  // DONE

    create_scripts("Oct19v1_MC_2018_ST_s-channel",3,"2018", "ttbar");               // DONE
    create_scripts("Oct19v2_MC_2018_ST_t-channel_top",5,"2018","ttbar");            // DONE
    create_scripts("Oct19v3_MC_2018_ST_t-channel_antitop",10,"2018","ttbar");       // DONE
    create_scripts("Oct19v3_MC_2018_ST_tW_top",1,"2018","ttbar");                   // DONE
    create_scripts("Oct19v1_MC_2018_ST_tW_antitop",1,"2018","ttbar");               // DONE
    create_scripts("Oct19v1_MC_2018_ST_tWll",0,"2018", "ttbar");                    // DONE
    create_scripts("Oct19v1_MC_2018_TTJets_DiLept",8,"2018","ttbar");               // DONE
    create_scripts("Oct19v1_MC_2018_TTJets_SingleLeptFromT",15,"2018","ttbar");     // DONE
    create_scripts("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar",9,"2018","ttbar");   // DONE
    */

    /*create_scripts("Oct19v1_MC_2016_WZTo2L2Q",1,"2016","EWK"); // DONE
    create_scripts("Oct19v1_MC_2016_ZZTo2L2Q",1,"2016","EWK"); // DONE
    create_scripts("Oct19v2_MC_2017_WZTo2L2Q",4,"2017","EWK"); // DONE
    create_scripts("Oct19v1_MC_2017_ZZTo2L2Q",4,"2017","EWK"); // DONE
    create_scripts("Oct19v1_MC_2018_WZTo2L2Q",5,"2018","EWK"); // DONE
    create_scripts("Oct19v1_MC_2018_ZZTo2L2Q",4,"2018","EWK"); // DONE

    create_scripts("Oct19v1_MC_2017_MadGraph_TTTo2L2Nu",1,"2017","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2017_MadGraph_TTTo2L2Nu_PS",10,"2017","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2017_MadGraph_TTToSemiLeptonic",8,"2017","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2017_MadGraph_TTToSemiLeptonic_PS",10,"2017","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2017_MadGraph_TTToHadronic",6,"2017","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2017_MadGraph_TTToHadronic_PS",10,"2017","ttbar"); // DONE

    create_scripts("Oct19v1_MC_2018_MadGraph_TTTo2L2Nu",9,"2018","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2018_MadGraph_TTToSemiLeptonic",10,"2018","ttbar"); // DONE
    create_scripts("Oct19v1_MC_2018_MadGraph_TTToHadronic",10,"2018","ttbar"); // DONE*/

    create_scripts("Oct19v4_MC_2016_MadGraph_TTTo2L2Nu",1,"2016","ttbar"); // DONE
    create_scripts("Oct19v4_MC_2016_MadGraph_TTTo2L2Nu_PS",7,"2016","ttbar"); // 6->repeat
    create_scripts("Oct19v4_MC_2016_MadGraph_TTToSemiLeptonic",6,"2016","ttbar"); // DONE
    create_scripts("Oct19v4_MC_2016_MadGraph_TTToSemiLeptonic_PS",8,"2016","ttbar"); // DONE (7 doesnt exist) 
    create_scripts("Oct19v4_MC_2016_MadGraph_TTToHadronic",4,"2016","ttbar"); // DONE
    create_scripts("Oct19v4_MC_2016_MadGraph_TTToHadronic_PS",4,"2016","ttbar"); // DONE
    
}

void launch_scripts_all(){

    //ttH --> CHECKED

    /*launch_scripts("Oct19v1_MC_2016_ttHJetToNonbb", 0,"2016","ttH");    
    launch_scripts("Oct19v1_MC_2016_ttH_ctcvcp", 1,"2016","ttH");
    launch_scripts("Oct19v1_MC_2016_THQ_ctcvcp", 1, "2016", "ttH");
    launch_scripts("Oct19v1_MC_2016_THW_ctcvcp", 1, "2016", "ttH");*/

    /*launch_scripts("Oct19v1_MC_2017_ttHJetToNonbb", 2, "2017", "ttH");  
    launch_scripts("Oct19v1_MC_2017_THQ_ctcvcp", 2, "2017", "ttH");
    launch_scripts("Oct19v3_MC_2017_THW_ctcvcp",1,"2017","ttH"); 
    launch_scripts("Oct19v1_MC_2017_TTH_ctcvcp", 2, "2017", "ttH");

    launch_scripts("Oct19v2_MC_2018_ttHJetToNonbb",2,"2018","ttH");
    launch_scripts("Oct19v2_MC_2018_TTH_ctcvcp", 7, "2018","ttH");
    launch_scripts("Oct19v1_MC_2018_THQ_ctcvcp", 7, "2018", "ttH");
    launch_scripts("Oct19v1_MC_2018_THW_ctcvcp", 4, "2018", "ttH");*/

    //ttV

    /*launch_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2",0,"2016","ttV");  
    launch_scripts("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",0,"2016","ttV");  
    launch_scripts("Oct19v1_MC_2016_TTZToLL_M-1to10", 0, "2016", "ttV" );    
    launch_scripts("Oct19v1_MC_2016_TTWJetsToLNu",0,"2016","ttV"); 
    launch_scripts("Oct19v1_MC_2016_TTWW", 0, "2016", "ttV" );

    launch_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10", 1, "2017", "ttV" );   
    launch_scripts("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",3,"2017","ttV");    
    launch_scripts("Oct19v1_MC_2017_TTZToLL_M-1to10", 0, "2017", "ttV" );    
    launch_scripts("Oct19v1_MC_2017_TTWJetsToLNu", 0, "2017", "ttV" );
    launch_scripts("Oct19v1_MC_2017_TTWJetsToLNu_PS",1,"2017","ttV"); 
    launch_scripts("Oct19v1_MC_2017_TTWW", 0,"2017", "ttV" ); 

    launch_scripts("Oct19v1_MC_2018_TTZToLLNuNu_M-10", 3, "2018", "ttV" );   
    launch_scripts("Oct19v1_MC_2018_TTZToLL_M-1to10", 0, "2018", "ttV" );    
    launch_scripts("Oct19v1_MC_2018_TTWJetsToLNu", 1, "2018", "ttV" );
    launch_scripts("Oct19v1_MC_2018_TTWW_ext1", 0, "2018", "ttV" );   
    launch_scripts("Oct19v1_MC_2018_TTWW_ext2", 0, "2018", "ttV" );   */

    // Rares 

    /*launch_scripts("Oct19v1_MC_2016_WWW",0,"2016", "Rares");
    launch_scripts("Oct19v1_MC_2016_WWZ",0,"2016", "Rares");
    launch_scripts("Oct19v1_MC_2016_WZZ",0,"2016", "Rares");
    launch_scripts("Oct19v1_MC_2016_ZZZ",0,"2016", "Rares");
    launch_scripts("Oct19v1_MC_2016_WZG",0,"2016", "Rares");
    launch_scripts("Oct19v1_MC_2016_WGToLNuG_ext1",0,"2016", "Rares");  
    launch_scripts("Oct19v1_MC_2016_WGToLNuG_ext2",0,"2016", "Rares");  
    launch_scripts("Oct19v1_MC_2016_WGToLNuG_ext3",0,"2016","Rares");   
    launch_scripts("Oct19v1_MC_2016_ZGTo2LG",1,"2016", "Rares"); 
    launch_scripts("Oct19v1_MC_2016_TGJets_leptonDecays",0,"2016", "Rares");   
    launch_scripts("Oct19v1_MC_2016_TTGJets",0,"2016", "Rares"); 
    launch_scripts("Oct19v1_MC_2016_TTGJets_ext1",0,"2016", "Rares");   
    launch_scripts("Oct19v2_MC_2016_tZq_ll",1,"2016", "Rares");  
    launch_scripts("Oct19v1_MC_2016_tZq_ll_PS",2,"2016","Rares");
    launch_scripts("Oct19v1_MC_2016_WpWpJJ",0,"2016", "Rares");  
    launch_scripts("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering",0,"2016","Rares");    
    launch_scripts("Oct19v1_MC_2016_TTTT",0,"2016", "Rares");  

    launch_scripts("Oct19v1_MC_2017_WWW",0,"2017", "Rares");
    launch_scripts("Oct19v1_MC_2017_WWZ",0,"2017","Rares");
    launch_scripts("Oct19v2_MC_2017_WZZ",0,"2017","Rares");
    launch_scripts("Oct19v2_MC_2017_ZZZ",0,"2017","Rares");
    launch_scripts("Oct19v1_MC_2017_WZG",0,"2017", "Rares");
    launch_scripts("Oct19v1_MC_2017_WGToLNuG",1,"2017","Rares"); 
    launch_scripts("Oct19v1_MC_2017_ZGToLLG",3,"2017","Rares");  
    launch_scripts("Oct19v1_MC_2017_TGJets",1,"2017", "Rares");  
    launch_scripts("Oct19v1_MC_2017_TTGJets",1,"2017", "Rares"); 
    launch_scripts("Oct19v1_MC_2017_TTGJets_ext1",2,"2017", "Rares");   
    launch_scripts("Oct19v1_MC_2017_tZq_ll",2,"2017", "Rares");  
    launch_scripts("Oct19v2_MC_2017_WpWpJJ",0,"2017","Rares");   
    launch_scripts("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering",0,"2017","Rares");    
    launch_scripts("Oct19v1_MC_2017_TTTT",0,"2017", "Rares");    
    launch_scripts("Oct19v1_MC_2017_TTTT_PS",0,"2017", "Rares");

    launch_scripts("Oct19v2_MC_2018_WWW",0,"2018","Rares");
    launch_scripts("Oct19v2_MC_2018_WWZ",0,"2018","Rares");
    launch_scripts("Oct19v1_MC_2018_WZZ",0,"2018", "Rares");
    launch_scripts("Oct19v1_MC_2018_ZZZ",0,"2018", "Rares");
    launch_scripts("Oct19v1_MC_2018_WZG",0,"2018", "Rares");
    launch_scripts("Oct19v1_MC_2018_WGToLNuG",1,"2018","Rares"); 
    launch_scripts("Oct19v2_MC_2018_ZGToLLG",4,"2018","Rares");  
    launch_scripts("Oct19v1_MC_2018_TGJets",1,"2018","Rares");   
    launch_scripts("Oct19v1_MC_2018_TTGJets",1,"2018","Rares");  
    launch_scripts("Oct19v1_MC_2018_tZq_ll",3,"2018", "Rares");  
    launch_scripts("Oct19v1_MC_2018_WpWpJJ",0,"2018", "Rares");  
    launch_scripts("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering",0,"2018", "Rares");   
    launch_scripts("Oct19v1_MC_2018_TTTT",0,"2018", "Rares"); */

    // EWK 

    /*launch_scripts("Oct19v1_MC_2016_DYJetsToLL_M-10to50",2,"2016","EWK"); 
    launch_scripts("Oct19v1_MC_2016_DYJetsToLL_M-50", 7, "2016", "EWK");  
    launch_scripts("Oct19v1_MC_2016_WJetsToLNu_ext2",3,"2016","EWK");
    launch_scripts("Oct19v1_MC_2016_WJetsToLNu", 2, "2016", "EWK"); 
    launch_scripts("Oct19v1_MC_2016_WWTo2L2Nu", 0, "2016", "EWK"); 
    launch_scripts("Oct19v1_MC_2016_WZTo3LNu", 0, "2016", "EWK");  
    launch_scripts("Oct19v1_MC_2016_ZZTo4L", 0, "2016", "EWK");    

    launch_scripts("Oct19v1_MC_2017_DYJetsToLL_M-10to50", 4, "2017", "EWK");
    launch_scripts("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",4,"2017","EWK");   
    launch_scripts("Oct19v1_MC_2017_DYJetsToLL_M-50",3,"2017","EWK");
    launch_scripts("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",7,"2017","EWK");
    launch_scripts("Oct19v2_MC_2017_WJetsToLNu",4,"2017","EWK");   
    launch_scripts("Oct19v1_MC_2017_WJetsToLNu_ext1", 7 , "2017", "EWK"); 
    launch_scripts("Oct19v2_MC_2017_WWTo2L2Nu",0,"2017","EWK");    
    launch_scripts("Oct19v1_MC_2017_WWTo2L2Nu_ext1", 0, "2017", "EWK");   
    launch_scripts("Oct19v1_MC_2017_WZTo3LNu", 1, "2017", "EWK");  
    launch_scripts("Oct19v1_MC_2017_ZZTo4L", 0, "2017", "EWK");    
    launch_scripts("Oct19v1_MC_2017_ZZTo4L_ext1", 11, "2017", "EWK");
    launch_scripts("Oct19v2_MC_2017_ZZTo4L_ext2",0,"2017","EWK");

    launch_scripts("Oct19v3_MC_2018_DYJetsToLL_M-10to50",5,"2018","EWK"); 
    launch_scripts("Oct19v2_MC_2018_DYJetsToLL_M-50", 0, "2018", "EWK");  
    launch_scripts("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",7,"2018","EWK");
    launch_scripts("Oct19v2_MC_2018_WJetsToLNu",9,"2018","EWK");   
    launch_scripts("Oct19v3_MC_2018_WWTo2L2Nu",1, "2018","EWK");   
    launch_scripts("Oct19v1_MC_2018_WZTo3LNu", 2, "2018", "EWK");  
    launch_scripts("Oct19v2_MC_2018_WZTo3LNu_ext1",2,"2018","EWK");
    launch_scripts("Oct19v2_MC_2018_ZZTo4L", 1, "2018", "EWK");    
    launch_scripts("Oct19v4_MC_2018_ZZTo4L_ext2",7,"2018","EWK");*/

    // ggH 
    /*
    launch_scripts("Oct19v1_MC_2016_GluGluHToTauTau",0,"2016", "ggH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluHToZZTo4L",0,"2016", "ggH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluHToWWToLNuQQ",0,"2016", "ggH");
    launch_scripts("Oct19v1_MC_2016_GluGluHToWWTo2L2Nu",0,"2016", "ggH");
    launch_scripts("Oct19v1_MC_2016_GluGluHToMuMu",0,"2016", "ggH");   
    launch_scripts("Oct19v1_MC_2016_GluGluHToBB",0,"2016", "ggH");
    launch_scripts("Oct19v6_MC_2016_GluGluHToBB_ext1",0,"2016","ggH");
    launch_scripts("Oct19v1_MC_2016_GluGluHToGG",0,"2016", "ggH");

    launch_scripts("Oct19v1_MC_2017_GluGluHToTauTau",0,"2017", "ggH"); 
    launch_scripts("Oct19v3_MC_2017_GluGluHToTauTau_ext1",1,"2017","ggH");
    launch_scripts("Oct19v1_MC_2017_GluGluHToZZTo4L_ext1",0,"2017", "ggH");   
    launch_scripts("Oct19v2_MC_2017_GluGluHToZZTo4L_ext3",0,"2017","ggH");    
    launch_scripts("Oct19v1_MC_2017_GluGluHToZZTo4L_ext4",0,"2017", "ggH");   
    launch_scripts("Oct19v2_MC_2017_GluGluHToZZTo2L2Q", 0, "2017","ggH");
    launch_scripts("Oct19v1_MC_2017_GluGluHToWWToLNuQQ",0,"2017", "ggH");
    launch_scripts("Oct19v1_MC_2017_GluGluHToWWTo2L2Nu",0,"2017", "ggH");
    launch_scripts("Oct19v3_MC_2017_GluGluHToMuMu",0,"2017","ggH");    
    launch_scripts("Oct19v1_MC_2017_GluGluHToMuMu_ext1",0,"2017", "ggH");
    launch_scripts("Oct19v2_MC_2017_GluGluHToBB",2,"2017","ggH");
    launch_scripts("Oct19v3_MC_2017_GluGluHToGG",0, "2017","ggH");

    launch_scripts("Oct19v2_MC_2018_GluGluHToTauTau", 1, "2018","ggH");
    launch_scripts("Oct19v1_MC_2018_GluGluHToZZTo4L",0,"2018","ggH");   
    launch_scripts("Oct19v2_MC_2018_GluGluHToZZTo2L2Q",0,"2018","ggH");
    launch_scripts("Oct19v1_MC_2018_GluGluHToWWToLNuQQ",0,"2018","ggH");
    launch_scripts("Oct19v2_MC_2018_GluGluHToWWTo2L2Nu",0,"2018","ggH");
    launch_scripts("Oct19v1_MC_2018_GluGluHToMuMu",0,"2018", "ggH");   
    launch_scripts("Oct19v2_MC_2018_GluGluHToMuMu_ext1",0,"2018","ggH");
    launch_scripts("Oct19v1_MC_2018_GluGluHToBB",3,"2018", "ggH");
    launch_scripts("Oct19v1_MC_2018_GluGluHToGG",0,"2018", "ggH");
    */

    // VBF 
    /*
    launch_scripts("Oct19v2_MC_2016_VBFHToTauTau",0,"2016","VBF");    
    launch_scripts("Oct19v2_MC_2016_VBF_HToZZTo4L",0,"2016","VBF");   
    launch_scripts("Oct19v1_MC_2016_VBFHToWWToLNuQQ", 0, "2016", "VBF");
    launch_scripts("Oct19v1_MC_2016_VBFHToWWTo2L2Nu", 0, "2016", "VBF");
    launch_scripts("Oct19v1_MC_2016_VBFHToMuMu", 0, "2016", "VBF");   
    launch_scripts("Oct19v3_MC_2016_VBFHToBB",0,"2016","VBF");
    launch_scripts("Oct19v1_MC_2016_VBFHToBB_ext1", 0, "2016", "VBF");
    launch_scripts("Oct19v1_MC_2016_VBFHToGG_ext1", 0, "2016", "VBF");
    launch_scripts("Oct19v1_MC_2016_VBFHToGG_ext2", 0, "2016", "VBF");

    launch_scripts("Oct19v1_MC_2017_VBFHToTauTau", 0, "2017", "VBF"); 
    launch_scripts("Oct19v2_MC_2017_VBF_HToZZTo4L_ext2",0,"2017","VBF");
    launch_scripts("Oct19v1_MC_2017_VBF_HToZZTo4L_ext1", 0, "2017", "VBF");  
    launch_scripts("Oct19v1_MC_2017_VBF_HToZZTo4L", 0, "2017", "VBF");
    launch_scripts("Oct19v1_MC_2017_VBFHToWWToLNuQQ",0,"2017","VBF"); 
    launch_scripts("Oct19v1_MC_2017_VBFHToWWTo2L2Nu", 0,"2017", "VBF");
    launch_scripts("Oct19v1_MC_2017_VBFHToMuMu",0,"2017","VBF");
    launch_scripts("Oct19v1_MC_2017_VBFHToBB", 0, "2017", "VBF");
    launch_scripts("Oct19v1_MC_2017_VBFHToGG",0,"2017","VBF"); 
    launch_scripts("Oct19v2_MC_2017_VBFHToGG_PS",0,"2017","VBF");

    launch_scripts("Oct19v1_MC_2018_VBFHToTauTau",0,"2018","VBF");    
    launch_scripts("Oct19v2_MC_2018_VBF_HToZZTo4L",0,"2018","VBF");   
    launch_scripts("Oct19v2_MC_2018_VBFHToWWToLNuQQ",0,"2018","VBF"); 
    launch_scripts("Oct19v1_MC_2018_VBFHToWWTo2L2Nu", 0, "2018", "VBF");
    launch_scripts("Oct19v1_MC_2018_VBFHToMuMu",0,"2018","VBF");
    launch_scripts("Oct19v2_MC_2018_VBFHToBB",1,"2018","VBF"); 
    launch_scripts("Oct19v2_MC_2018_VBFHToGG",0,"2018","VBF"); 
    */

    // VH 
    /*
    launch_scripts("Oct19v1_MC_2016_VHToNonbb", 0, "2016", "VH");  
    launch_scripts("Oct19v1_MC_2016_ZH_HToBB_ZToLL", 0, "2016", "VH");    
    launch_scripts("Oct19v1_MC_2016_ZHToTauTau", 0, "2016", "VH"); 

    launch_scripts("Oct19v1_MC_2017_VHToNonbb", 0, "2017", "VH");  
    launch_scripts("Oct19v1_MC_2017_ZH_HToBB_ZToLL", 0, "2017", "VH");    
    launch_scripts("Oct19v1_MC_2017_ZHToTauTau",0,"2017","VH"); 

    launch_scripts("Oct19v2_MC_2018_VHToNonbb",0,"2018","VH");
    launch_scripts("Oct19v1_MC_2018_ZH_HToBB_ZToLL", 1, "2018", "VH");    
    launch_scripts("Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1",1, "2018","VH"); 
    launch_scripts("Oct19v2_MC_2018_ZHToTauTau", 1, "2018", "VH"); 
    */

    // TTVH
    /*
    launch_scripts("Oct19v1_MC_2016_TTWH", 0, "2016", "ttVH");    
    launch_scripts("Oct19v2_MC_2016_TTZH", 0, "2016", "ttVH"); 

    launch_scripts("Oct19v4_MC_2017_TTWH",0,"2017","ttVH");
    launch_scripts("Oct19v1_MC_2017_TTZH", 0, "2017", "ttVH");  

    launch_scripts("Oct19v1_MC_2018_TTWH", 0, "2018", "ttVH");
    launch_scripts("Oct19v2_MC_2018_TTZH", 0, "2018", "ttVH");
    */

    // HH
    /*
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM",0,"2016","HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box",0,"2016", "HH");
    launch_scripts("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_1",0,"2016", "HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2",0,"2016", "HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3",0,"2016", "HH"); 
    launch_scripts("Oct19v4_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_4",0,"2016","HH");
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_5",0,"2016", "HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6",0,"2016", "HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_7",0,"2016","HH");  
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8",0,"2016", "HH"); 
    launch_scripts("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9",0,"2016","HH");  
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10",0,"2016","HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_11",0,"2016","HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12",0,"2016", "HH");
    
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM",0,"2016", "HH");
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box",0,"2016", "HH");    
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2",0,"2016", "HH");
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo2B2Tau_node_9",0,"2016","HH");
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10",0,"2016", "HH");
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11",0,"2016", "HH");
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12",0,"2016", "HH");
    launch_scripts("Oct19v3_MC_2016_GluGluToHHTo2B2Tau_node_13",0,"2016","HH");

    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM",0,"2016", "HH");
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box",0,"2016", "HH");
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2",0,"2016", "HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3",0,"2016", "HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4",0,"2016", "HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5",0,"2016", "HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6",0,"2016", "HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7",0,"2016", "HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_8",0,"2016","HH");  
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9",0,"2016", "HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_10",0,"2016","HH"); 
    launch_scripts("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_11",0,"2016","HH"); 
    launch_scripts("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12",0,"2016", "HH");


    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM",0,"2017","HH"); 
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2", 0, "2017","HH");
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3",0,"2017","HH");  
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_7",0,"2017","HH");  
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9",0,"2017","HH");  
    launch_scripts("Oct19v4_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12",0,"2017","HH");

    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12",0,"2017", "HH");

    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13",0,"2017", "HH");    
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2",0,"2017", "HH"); 
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3",0,"2017", "HH"); 
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo4Tau_node_7",0,"2017","HH");  
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9",0,"2017", "HH"); 
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12",0,"2017", "HH");

    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM",0,"2017","HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2",0,"2017", "HH");
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_3", 0, "2017","HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6",0,"2017", "HH");
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_7",0,"2017","HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9",0,"2017", "HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10",0,"2017","HH");
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11",0,"2017", "HH");
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_12",0,"2017","HH");

    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_SM",0,"2017", "HH");  
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo4V_node_2",0,"2017","HH");    
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_3",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_4",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_5",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_6",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_7",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_8",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_9",0,"2017", "HH");   
    launch_scripts("Oct19v1_MC_2017_GluGluToHHTo4V_node_10",0,"2017", "HH");  
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo4V_node_11",0,"2017", "HH");  
    launch_scripts("Oct19v2_MC_2017_GluGluToHHTo4V_node_12",0,"2017","HH");

    
    launch_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM",0,"2018", "HH");
    launch_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_2",0,"2018", "HH");
    launch_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_3",0,"2018", "HH");
    launch_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_4",0,"2018", "HH");
    launch_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_5",0,"2018", "HH");
    launch_scripts("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_6",0,"2018", "HH");
    launch_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_7",0,"2018", "HH");
    launch_scripts("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_8",0,"2018", "HH");
    launch_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_9",0,"2018", "HH");
    launch_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_10",0,"2018","HH"); 
    launch_scripts("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_11",0,"2018","HH");
    launch_scripts("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_12",0,"2018", "HH");
    */

    // TT
    /*
    launch_scripts("Oct19v1_MC_2016_ST_s-channel",0,"2016", "ttbar"); 
    launch_scripts("Oct19v1_MC_2016_ST_s-channel_PS",2,"2016", "ttbar");
    launch_scripts("Oct19v1_MC_2016_ST_t-channel_top",4,"2016", "ttbar");    
    launch_scripts("Oct19v1_MC_2016_ST_t-channel_antitop",2,"2016", "ttbar");
    launch_scripts("Oct19v1_MC_2016_ST_t-channel_antitop_PS",5,"2016","ttbar");
    launch_scripts("Oct19v1_MC_2016_ST_tW_top",0,"2016","ttbar");
    launch_scripts("Oct19v1_MC_2016_ST_tW_antitop",0,"2016","ttbar"); 
    launch_scripts("Oct19v1_MC_2016_ST_tWll",0,"2016", "ttbar");
    launch_scripts("Oct19v1_MC_2016_TTJets_DiLept_ext1",2,"2016", "ttbar");  
    launch_scripts("Oct19v1_MC_2016_TTJets_DiLept",0,"2016", "ttbar");
    launch_scripts("Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1",3,"2016","ttbar");  
    launch_scripts("Oct19v1_MC_2016_TTJets_SingleLeptFromT",0,"2016", "ttbar"); 
    launch_scripts("Oct19v1_MC_2016_TTJets_SingleLeptFromTbar",1,"2016", "ttbar");  
    launch_scripts("Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1",2,"2016","ttbar");

    launch_scripts("Oct19v1_MC_2017_ST_s-channel",1,"2017","ttbar");  
    launch_scripts("Oct19v2_MC_2017_ST_s-channel_PS",1,"2017","ttbar");
    launch_scripts("Oct19v1_MC_2017_ST_t-channel_top",0,"2017", "ttbar");    
    launch_scripts("Oct19v2_MC_2017_ST_t-channel_top_PS",9,"2017","ttbar");
    launch_scripts("Oct19v1_MC_2017_ST_t-channel_antitop",0,"2017", "ttbar"); 
    launch_scripts("Oct19v2_MC_2017_ST_t-channel_antitop_PS",12,"2017","ttbar");    
    launch_scripts("Oct19v3_MC_2017_ST_tW_top",1,"2017","ttbar");
    launch_scripts("Oct19v1_MC_2017_ST_tW_top_PS",1,"2017","ttbar");   
    launch_scripts("Oct19v1_MC_2017_ST_tW_antitop",1,"2017","ttbar"); 
    launch_scripts("Oct19v1_MC_2017_ST_tW_antitop_PS",1,"2017","ttbar");
    launch_scripts("Oct19v1_MC_2017_ST_tWll",0,"2017", "ttbar");
    launch_scripts("Oct19v1_MC_2017_TTJets_DiLept",6,"2017", "ttbar");
    launch_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromT",9,"2017", "ttbar");    
    launch_scripts("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar",13,"2017","ttbar");  

    launch_scripts("Oct19v1_MC_2018_ST_s-channel",3,"2018", "ttbar"); 
    launch_scripts("Oct19v2_MC_2018_ST_t-channel_top",5,"2018","ttbar");
    launch_scripts("Oct19v3_MC_2018_ST_t-channel_antitop",10,"2018","ttbar");
    launch_scripts("Oct19v3_MC_2018_ST_tW_top",1,"2018","ttbar");
    launch_scripts("Oct19v1_MC_2018_ST_tW_antitop",1,"2018", "ttbar");
    launch_scripts("Oct19v1_MC_2018_ST_tWll",0,"2018", "ttbar");
    launch_scripts("Oct19v1_MC_2018_TTJets_DiLept",8,"2018","ttbar"); 
    launch_scripts("Oct19v1_MC_2018_TTJets_SingleLeptFromT",15,"2018","ttbar");
    launch_scripts("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar",9,"2018","ttbar");
    */ 

    /*launch_scripts("Oct19v1_MC_2016_WZTo2L2Q",1,"2016","EWK"); // DONE
    launch_scripts("Oct19v1_MC_2016_ZZTo2L2Q",1,"2016","EWK"); // DONE
    launch_scripts("Oct19v2_MC_2017_WZTo2L2Q",4,"2017","EWK"); // DONE
    launch_scripts("Oct19v1_MC_2017_ZZTo2L2Q",4,"2017","EWK"); // DONE
    launch_scripts("Oct19v1_MC_2018_WZTo2L2Q",5,"2018","EWK"); // DONE
    launch_scripts("Oct19v1_MC_2018_ZZTo2L2Q",4,"2018","EWK"); // DONE

    launch_scripts("Oct19v1_MC_2017_MadGraph_TTTo2L2Nu",1,"2017","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2017_MadGraph_TTTo2L2Nu_PS",10,"2017","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2017_MadGraph_TTToSemiLeptonic",8,"2017","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2017_MadGraph_TTToSemiLeptonic_PS",10,"2017","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2017_MadGraph_TTToHadronic",6,"2017","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2017_MadGraph_TTToHadronic_PS",10,"2017","ttbar"); // DONE

    launch_scripts("Oct19v1_MC_2018_MadGraph_TTTo2L2Nu",9,"2018","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2018_MadGraph_TTToSemiLeptonic",10,"2018","ttbar"); // DONE
    launch_scripts("Oct19v1_MC_2018_MadGraph_TTToHadronic",10,"2018","ttbar"); // DONE*/

    launch_scripts("Oct19v4_MC_2016_MadGraph_TTTo2L2Nu",1,"2016","ttbar"); // DONE
    launch_scripts("Oct19v4_MC_2016_MadGraph_TTTo2L2Nu_PS",7,"2016","ttbar"); // DONE
    launch_scripts("Oct19v4_MC_2016_MadGraph_TTToSemiLeptonic",6,"2016","ttbar"); // DONE
    launch_scripts("Oct19v4_MC_2016_MadGraph_TTToSemiLeptonic_PS",8,"2016","ttbar");// DONE
    launch_scripts("Oct19v4_MC_2016_MadGraph_TTToHadronic",4,"2016","ttbar"); //DONE
    launch_scripts("Oct19v4_MC_2016_MadGraph_TTToHadronic_PS",4,"2016","ttbar");//DONE

}

void launch_single_script_all(){

launch_single_script("Oct19v1_MC_2016_DYJetsToLL_M-50",3,"2016","EWK");
launch_single_script("Oct19v1_MC_2016_DYJetsToLL_M-50",6,"2016","EWK");
launch_single_script("Oct19v1_MC_2016_WJetsToLNu_ext2",2,"2016","EWK");
launch_single_script("Oct19v1_MC_2016_WJetsToLNu_ext2",3,"2016","EWK");
launch_single_script("Oct19v1_MC_2016_WJetsToLNu",1,"2016","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-10to50",3,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",0,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",1,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",3,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1",4,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-50",1,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_DYJetsToLL_M-50",2,"2017","EWK");
launch_single_script("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",0,"2017","EWK");
launch_single_script("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",1,"2017","EWK");
launch_single_script("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",2,"2017","EWK");
launch_single_script("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",4,"2017","EWK");
launch_single_script("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",6,"2017","EWK");
launch_single_script("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1",7,"2017","EWK");
launch_single_script("Oct19v2_MC_2017_WJetsToLNu",0,"2017","EWK");
launch_single_script("Oct19v2_MC_2017_WJetsToLNu",2,"2017","EWK");
launch_single_script("Oct19v2_MC_2017_WJetsToLNu",3,"2017","EWK");
launch_single_script("Oct19v2_MC_2017_WJetsToLNu",4,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",0,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",1,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",2,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",3,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",4,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",5,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",6,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WJetsToLNu_ext1",7,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WWTo2L2Nu_ext1",0,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WZTo3LNu",0,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_WZTo3LNu",1,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L",0,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",0,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",1,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",2,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",3,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",4,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",5,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",6,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",7,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",8,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",9,"2017","EWK");
launch_single_script("Oct19v1_MC_2017_ZZTo4L_ext1",10,"2017","EWK");
launch_single_script("Oct19v2_MC_2017_ZZTo4L_ext2",0,"2017","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-10to50",0,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-10to50",2,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-10to50",3,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-10to50",4,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_DYJetsToLL_M-50",0,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",0,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",1,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",2,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",3,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",4,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",5,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",7,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",8,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WJetsToLNu",9,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_WWTo2L2Nu",0,"2018","EWK");
launch_single_script("Oct19v1_MC_2018_WZTo3LNu",0,"2018","EWK");
launch_single_script("Oct19v1_MC_2018_WZTo3LNu",1,"2018","EWK");
launch_single_script("Oct19v1_MC_2018_WZTo3LNu",2,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WZTo3LNu_ext1",0,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_WZTo3LNu_ext1",1,"2018","EWK");
launch_single_script("Oct19v2_MC_2018_ZZTo4L",0,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",0,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",1,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",2,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",3,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",4,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",5,"2018","EWK");
launch_single_script("Oct19v4_MC_2018_ZZTo4L_ext2",6,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",1,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",2,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",3,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",4,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",5,"2018","EWK");
launch_single_script("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2",7,"2018","EWK");
launch_single_script("Oct19v1_MC_2016_GluGluHToMuMu",0,"2016","ggH");
launch_single_script("Oct19v1_MC_2017_GluGluHToTauTau",0,"2017","ggH");
launch_single_script("Oct19v3_MC_2017_GluGluHToTauTau_ext1",0,"2017","ggH");
launch_single_script("Oct19v3_MC_2017_GluGluHToTauTau_ext1",1,"2017","ggH");
launch_single_script("Oct19v1_MC_2017_GluGluHToZZTo4L_ext1",0,"2017","ggH");
launch_single_script("Oct19v1_MC_2017_GluGluHToMuMu_ext1",0,"2017","ggH");
launch_single_script("Oct19v2_MC_2017_GluGluHToBB",0,"2017","ggH");
launch_single_script("Oct19v2_MC_2017_GluGluHToBB",1,"2017","ggH");
launch_single_script("Oct19v2_MC_2018_GluGluHToTauTau",0,"2018","ggH");
launch_single_script("Oct19v2_MC_2018_GluGluHToTauTau",1,"2018","ggH");
launch_single_script("Oct19v2_MC_2018_GluGluHToMuMu_ext1",0,"2018","ggH");
launch_single_script("Oct19v1_MC_2018_GluGluHToBB",0,"2018","ggH");
launch_single_script("Oct19v1_MC_2018_GluGluHToBB",1,"2018","ggH");
launch_single_script("Oct19v1_MC_2018_GluGluHToBB",2,"2018","ggH");
launch_single_script("Oct19v1_MC_2018_GluGluHToGG",0,"2018","ggH");

}