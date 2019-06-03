/////////////////////////////////////////////////////////
///// HGCal L1 taus, C. Martin Perez, LLR, May 2019 /////
/////////////////////////////////////////////////////////

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>

using namespace std;


void dump_variables(TString region="2lSS_SR"){
	
	ofstream out_file_LLR;
	ofstream out_file_Tallinn;
	ofstream out_file_IHEP;
	ofstream out_file_VUB;

	out_file_LLR.open("/home/llr/cms/mperez/ttH/Legacy/macros/sync/sync_events_LLR_"+region+".txt");
	out_file_Tallinn.open("/home/llr/cms/mperez/ttH/Legacy/macros/sync/sync_events_Tallinn_"+region+".txt");
	out_file_IHEP.open("/home/llr/cms/mperez/ttH/Legacy/macros/sync/sync_events_IHEP_"+region+".txt");
	out_file_VUB.open("/home/llr/cms/mperez/ttH/Legacy/macros/sync/sync_events_VUB_"+region+".txt");

	TChain * in_tree_LLR = new TChain("syncTree_"+region);	
	TChain * in_tree_Tallinn = new TChain("syncTree_"+region);	
	TChain * in_tree_IHEP = new TChain("syncTree_"+region);	
	TChain * in_tree_VUB = new TChain("syncTree_"+region);	

	in_tree_LLR->Add("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_syncformat/events/2016/sync_ntuple_events_syncformat_ttHNonbb_2016_v5.root");
	in_tree_Tallinn->Add("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_groups/events/2016/sync_Tallinn_2016_v19.root");
	in_tree_IHEP->Add("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_groups/events/2016/IHEP_EventSync_2016_V5.root");
	in_tree_VUB->Add("/data_CMS/cms/mperez/ttH_Legacy/sync_ntuples/ntuples_groups/events/2016/2016_event_v8.root");

	Long64_t nentries_LLR = in_tree_LLR->GetEntries();
	Long64_t nentries_Tallinn = in_tree_Tallinn->GetEntries();
	Long64_t nentries_IHEP = in_tree_IHEP->GetEntries();
	Long64_t nentries_VUB = in_tree_VUB->GetEntries();

	Long64_t _nEvent_LLR;
	Long64_t _nEvent_Tallinn;
	Int_t _nEvent_IHEP;
	Int_t _nEvent_VUB;

	in_tree_LLR->SetBranchAddress("nEvent",	&_nEvent_LLR);
	in_tree_Tallinn->SetBranchAddress("nEvent",	&_nEvent_Tallinn);
	in_tree_IHEP->SetBranchAddress("nEvent",	&_nEvent_IHEP);
	in_tree_VUB->SetBranchAddress("nEvent",	&_nEvent_VUB);

	for (int i=0;i<nentries_LLR;i++) {
	    _nEvent_LLR = 0;
	    int entry_ok = in_tree_LLR->GetEntry(i);	
		if(entry_ok<0) 
			continue;
		TString s_nEvent = Form("%.0i", _nEvent_LLR);
		out_file_LLR<<s_nEvent<<'\n';
	}

	for (int i=0;i<nentries_Tallinn;i++) {
	    _nEvent_Tallinn = 0;
	    int entry_ok = in_tree_Tallinn->GetEntry(i);	
		if(entry_ok<0) 
			continue;
		TString s_nEvent = Form("%.0i", _nEvent_Tallinn);
		out_file_Tallinn<<s_nEvent<<'\n';
	}

	for (int i=0;i<nentries_IHEP;i++) {
	    _nEvent_IHEP = 0;
	    int entry_ok = in_tree_IHEP->GetEntry(i);	
		if(entry_ok<0) 
			continue;
		TString s_nEvent = Form("%.0i", _nEvent_IHEP);
		out_file_IHEP<<s_nEvent<<'\n';
	}


	for (int i=0;i<nentries_VUB;i++) {
	    _nEvent_VUB = 0;
	    int entry_ok = in_tree_VUB->GetEntry(i);	
		if(entry_ok<0) 
			continue;
		TString s_nEvent = Form("%.0i", _nEvent_VUB);
		out_file_VUB<<s_nEvent<<'\n';
	}


	out_file_LLR.close();
	out_file_Tallinn.close();
	out_file_IHEP.close();
	out_file_VUB.close();

	return;
}

