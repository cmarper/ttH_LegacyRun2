#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

using namespace std;

void compare_events(std::pair<TString, TString> filepair){

	TString filein1 = filepair.first;
	TString filein2 = filepair.second;
	cout<<filein1<<endl;
	cout<<filein2<<endl;

	TChain * tree1 = new TChain("Tree");
	tree1->Add(filein1);
	Long64_t nentries1 = tree1->GetEntries();

	TChain * tree2 = new TChain("Tree");
	tree2->Add(filein2);
	Long64_t nentries2 = tree2->GetEntries();

	if(nentries1 == nentries2) cout << " -> good! " << endl;
	if(nentries1 != nentries2) cout << " -> *** ERROR! *** " << endl;
	cout<<" "<<endl;

}


std::pair<TString, TString> create_file_pair(TString sample, int isample, TString year, TString type){

  TString dirin1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_converted/";
  TString dirin2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/";

  dirin1 += year;
  dirin1 += "/nominal/";
  dirin1 += type;
  dirin1 += "/";

  dirin2 += year;
  dirin2 += "/nominal/";
  dirin2 += type;
  dirin2 += "/";

  string isamplestr= to_string(isample);

  TString file1 = dirin1+"ntuple_"+sample+"_"+isamplestr+".root";
  TString file2 = dirin2+"ntuple_"+sample+"_norm_"+isamplestr+".root";

  return std::make_pair(file1, file2);

}

void test(){

	vector<std::pair<TString, TString>> filepairs;

	/*filepairs.push_back(create_file_pair("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2",0,"2016","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2",0,"2016","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3",0,"2016","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2016_TTZToLL_M-1to10", 0, "2016", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2016_TTWJetsToLNu",0,"2016","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2016_TTWW", 0, "2016", "ttV"));  
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLLNuNu_M-10", 0, "2017", "ttV")); 
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLLNuNu_M-10", 1, "2017", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",0,"2017","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",1,"2017","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",2,"2017","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS",3,"2017","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTZToLL_M-1to10", 0, "2017", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTWJetsToLNu", 0, "2017", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTWJetsToLNu_PS",0,"2017","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTWJetsToLNu_PS",1,"2017","ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2017_TTWW", 0,"2017", "ttV")); 
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTZToLLNuNu_M-10", 0, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTZToLLNuNu_M-10", 1, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTZToLLNuNu_M-10", 2, "2018", "ttV"));  
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTZToLLNuNu_M-10", 3, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTZToLL_M-1to10", 0, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTWJetsToLNu", 0, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTWJetsToLNu", 1, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTWW_ext1", 0, "2018", "ttV"));
    filepairs.push_back(create_file_pair("Oct19v1_MC_2018_TTWW_ext2", 0, "2018", "ttV"));*/

	for (unsigned int i=0; i<filepairs.size(); i++)
		compare_events(filepairs[i]);

}

