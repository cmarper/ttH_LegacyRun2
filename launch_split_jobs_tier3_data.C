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

void create_scripts( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int maxsplit=0, TString year="2016", TString type="Data" ){

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

    TString ScriptName = Form("script_tier3_data/"+year+"/split_"+sample+"_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/prodOct19/CMSSW_10_2_16/src\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/mperez/ttH/Legacy/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/mperez/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_Oct19_v2.C+\n";
    myscript << "split_tree(\""+dirin+filename+"\",\""+dirout+filename+"\",0,0,false,"+year+");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

}


void launch_scripts( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int maxsplit=0, TString year="2016", TString type="Data" ){

  for(int j=0;j<maxsplit+1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3_data/"+year+"/split_"+sample+"_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
 
  }

}

void launch_single_script( TString sample="Oct19v1_Data_2016_SingleElectron_BlockB", int isplit=0, TString year="2016", TString type="Data" ){

  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += Form("script_tier3_data/"+year+"/split_"+sample+"_%i.sh",isplit);
  gSystem->Exec(LaunchExec.Data());
 
}



void create_scripts_all(){

  //-NOTREADY- create_scripts("Oct19v1_Data_2016_SingleElectron_BlockB",36,"2016","Data/SingleElectron/BlockB");
  create_scripts("Oct19v1_Data_2016_SingleElectron_BlockC",11,"2016","Data/SingleElectron/BlockC"); // missing: 2,5,9,10
  create_scripts("Oct19v1_Data_2016_SingleElectron_BlockD",19,"2016","Data/SingleElectron/BlockD"); // missing: 3
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockE",25,"2016","Data/SingleElectron/BlockE"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockF",12,"2016","Data/SingleElectron/BlockF"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockG",28,"2016","Data/SingleElectron/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_SingleElectron_BlockH",31,"2016","Data/SingleElectron/BlockH"); // DONE

  create_scripts("Oct19v1_Data_2016_SingleMuon_BlockB",35,"2016","Data/SingleMuon/BlockB"); // missing: 1,4,5,6,10,14,15,19,24,27,31,32,35
  //create_scripts("Oct19v1_Data_2016_SingleMuon_BlockC",11,"2016","Data/SingleMuon/BlockC"); // DONE
  create_scripts("Oct19v1_Data_2016_SingleMuon_BlockD",19,"2016","Data/SingleMuon/BlockD"); // missing: 2,3,4,10,11,12,16,17,18,19
  create_scripts("Oct19v1_Data_2016_SingleMuon_BlockE",16,"2016","Data/SingleMuon/BlockE"); // missing: 0,2,3,4,6,7,8,9,10,11,12,13,16
  //-NOTREADY- create_scripts("Oct19v1_Data_2016_SingleMuon_BlockF",12,"2016","Data/SingleMuon/BlockF"); 
  create_scripts("Oct19v1_Data_2016_SingleMuon_BlockG",28,"2016","Data/SingleMuon/BlockG"); // missing: 2,12,14,17,28
  //-NOTREADY- create_scripts("Oct19v1_Data_2016_SingleMuon_BlockH",31,"2016","Data/SingleMuon/BlockH"); 

  //-NOTREADY- create_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17,"2016","Data/DoubleEG/BlockB"); 
  //-NOTREADY- create_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5,"2016","Data/DoubleEG/BlockC");  
  create_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","Data/DoubleEG/BlockD"); // missing: 3
  //-NOTREADY- create_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8,"2016","Data/DoubleEG/BlockE"); 
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6,"2016","Data/DoubleEG/BlockF");  // DONE
  create_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14,"2016","Data/DoubleEG/BlockG");   // missing: 0,1,2,3,4,5,6,7,8,9,10,11,12,13
  //create_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15,"2016","Data/DoubleEG/BlockH"); // DONE

  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17,"2016","Data/DoubleMu/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5,"2016","Data/DoubleMu/BlockC");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10,"2016","Data/DoubleMu/BlockD"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8,"2016","Data/DoubleMu/BlockE");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6,"2016","Data/DoubleMu/BlockF");  // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14,"2016","Data/DoubleMu/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","Data/DoubleMu/BlockH"); // DONE

  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17,"2016","Data/MuonEG/BlockB"); // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5,"2016","Data/MuonEG/BlockC");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9,"2016","Data/MuonEG/BlockD");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8,"2016","Data/MuonEG/BlockE");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6,"2016","Data/MuonEG/BlockF");  // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16,"2016","Data/MuonEG/BlockG"); // DONE
  //create_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15,"2016","Data/MuonEG/BlockH"); // DONE

    
}

void launch_scripts_all(){

  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockB",36,"2016","Data/SingleElectron/BlockB");
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockC",11,"2016","Data/SingleElectron/BlockC");
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockD",19,"2016","Data/SingleElectron/BlockD");
  launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockE",25,"2016","Data/SingleElectron/BlockE"); // 
  launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockF",12,"2016","Data/SingleElectron/BlockF"); // 
  //launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockG",28,"2016","Data/SingleElectron/BlockG");
  launch_scripts("Oct19v1_Data_2016_SingleElectron_BlockH",31,"2016","Data/SingleElectron/BlockH"); // 

  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockB",35,"2016","Data/SingleMuon/BlockB");
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockC",11,"2016","Data/SingleMuon/BlockC"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockD",19,"2016","Data/SingleMuon/BlockD");
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockE",16,"2016","Data/SingleMuon/BlockE"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockF",12,"2016","Data/SingleMuon/BlockF"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockG",28,"2016","Data/SingleMuon/BlockG"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_SingleMuon_BlockH",31,"2016","Data/SingleMuon/BlockH"); 

  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockB",17,"2016","Data/DoubleEG/BlockB"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockC",5,"2016","Data/DoubleEG/BlockC");  
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockD",9,"2016","Data/DoubleEG/BlockD");  
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockE",8,"2016","Data/DoubleEG/BlockE"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockF",6,"2016","Data/DoubleEG/BlockF");  
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockG",14,"2016","Data/DoubleEG/BlockG"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleEG_BlockH",15,"2016","Data/DoubleEG/BlockH"); 

  launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockB",17,"2016","Data/DoubleMu/BlockB"); // 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockC",5,"2016","Data/DoubleMu/BlockC");  
  launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockD",10,"2016","Data/DoubleMu/BlockD"); // 
  launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockE",8,"2016","Data/DoubleMu/BlockE");  // 
  launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockF",6,"2016","Data/DoubleMu/BlockF");  
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockG",14,"2016","Data/DoubleMu/BlockG"); 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_DoubleMu_BlockH",15,"2016","Data/DoubleMu/BlockH"); 

  launch_scripts("Oct19v1_Data_2016_MuonEG_BlockB",17,"2016","Data/MuonEG/BlockB"); // 
  launch_scripts("Oct19v1_Data_2016_MuonEG_BlockC",5,"2016","Data/MuonEG/BlockC");  //  
  launch_scripts("Oct19v1_Data_2016_MuonEG_BlockD",9,"2016","Data/MuonEG/BlockD");  // 
  launch_scripts("Oct19v1_Data_2016_MuonEG_BlockE",8,"2016","Data/MuonEG/BlockE");  // 
  //-NOTREADY- launch_scripts("Oct19v1_Data_2016_MuonEG_BlockF",6,"2016","Data/MuonEG/BlockF");  
  launch_scripts("Oct19v1_Data_2016_MuonEG_BlockG",16,"2016","Data/MuonEG/BlockG"); 
  launch_scripts("Oct19v1_Data_2016_MuonEG_BlockH",15,"2016","Data/MuonEG/BlockH"); //  

}