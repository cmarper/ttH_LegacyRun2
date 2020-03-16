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

void veto_overlap_datasets(TString file_in, TString file_out, vector<TString> treename){

	TFile* f_new = TFile::Open(file_out);
  	
  /*if(f_new!=0){
    	cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    	return;
  }*/
  
	f_new = TFile::Open(file_out,"RECREATE");
	
	for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){
    
	   TChain * tree = new TChain(treename[i_tree]);
	   tree->Add(file_in);

	   Long64_t _triggerbit; 
	   int _year;

		tree->SetBranchAddress("triggerbit",&_triggerbit);
		tree->SetBranchAddress("year",&_year);
	    
	   Long64_t nentries = tree->GetEntries();
	   cout<<"nentries="<<tree->GetEntries()<<endl;
	   
		TTree* tree_new=tree->GetTree()->CloneTree(0);

    int n_in = nentries;
    int n_out = 0;

		for(int i=0;i<nentries;i++){

			if(i%10000==0)
				cout<<"i="<<i<<endl;

			_year = 0;
      _triggerbit = 0;

			tree->GetEntry(i); 

			Long64_t bitdigit = 1;

			bool pass_HLT_IsoMu22_v = _triggerbit & (bitdigit << 0);
    	bool pass_HLT_IsoTkMu22_v = _triggerbit & (bitdigit << 1);
    	bool pass_HLT_IsoMu22_eta2p1_v = _triggerbit & (bitdigit << 2);
    	bool pass_HLT_IsoTkMu22_eta2p1_v = _triggerbit & (bitdigit << 3);
    	bool pass_HLT_IsoMu24_v = _triggerbit & (bitdigit << 4);
    	bool pass_HLT_IsoTkMu24_v = _triggerbit & (bitdigit << 5);
    	bool pass_HLT_IsoMu27_v = _triggerbit & (bitdigit << 6);
    	bool pass_HLT_Ele25_eta2p1_WPTight_Gsf_v = _triggerbit & (bitdigit << 7);
    	bool pass_HLT_Ele27_WPTight_Gsf_v = _triggerbit & (bitdigit << 8);
    	bool pass_HLT_Ele27_eta2p1_WPLoose_Gsf_v = _triggerbit & (bitdigit << 9);
    	bool pass_HLT_Ele32_WPTight_Gsf_v = _triggerbit & (bitdigit << 10);
    	bool pass_HLT_Ele35_WPTight_Gsf_v = _triggerbit & (bitdigit << 11);
    	bool pass_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v = _triggerbit & (bitdigit << 12);
    	bool pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 13);
    	bool pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 14);
    	bool pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v = _triggerbit & (bitdigit << 15);
    	bool pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v = _triggerbit & (bitdigit << 16);
    	bool pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v = _triggerbit & (bitdigit << 17);
    	bool pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 18);
    	bool pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_v = _triggerbit & (bitdigit << 19);
    	bool pass_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 20);
    	bool pass_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 21);
    	bool pass_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 22);
    	bool pass_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v = _triggerbit & (bitdigit << 23);
    	bool pass_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v = _triggerbit & (bitdigit << 24);
    	bool pass_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 25);
    	bool pass_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v = _triggerbit & (bitdigit << 26);
    	bool pass_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 27);
    	bool pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 28);
    	bool pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 29);
    	bool pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 30);
    	bool pass_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 31);
    	bool pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 32);
    	bool pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 33);
    	bool pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 34);
    	bool pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 35);
    	bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v = _triggerbit & (bitdigit << 36);
    	bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v = _triggerbit & (bitdigit << 37);
    	bool pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v = _triggerbit & (bitdigit << 38);
    	bool pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v = _triggerbit & (bitdigit << 39);
    	bool pass_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v = _triggerbit & (bitdigit << 40);
    	bool pass_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v = _triggerbit & (bitdigit << 41);
    	bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v = _triggerbit & (bitdigit << 42);
    	bool pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v = _triggerbit & (bitdigit << 43);
    	bool pass_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 44);
    	bool pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v = _triggerbit & (bitdigit << 45);
    	bool pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = _triggerbit & (bitdigit << 46);
    	bool pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v = _triggerbit & (bitdigit << 47);
    	bool pass_HLT_TripleMu_12_10_5_v = _triggerbit & (bitdigit << 48);
    	bool pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v = _triggerbit & (bitdigit << 49);
    	bool pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v = _triggerbit & (bitdigit << 50);
    	bool pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v = _triggerbit & (bitdigit << 51);
    	bool pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v  = _triggerbit & (bitdigit << 52);

    	bool pass_m = false;
    	if(_year==2016) pass_m = ( pass_HLT_IsoMu22_v || pass_HLT_IsoTkMu22_v || pass_HLT_IsoMu22_eta2p1_v || pass_HLT_IsoTkMu22_eta2p1_v || pass_HLT_IsoMu24_v || pass_HLT_IsoTkMu24_v );
    	else if(_year==2017) pass_m = ( pass_HLT_IsoMu24_v || pass_HLT_IsoMu27_v );
    	else if(_year==2018) pass_m = ( pass_HLT_IsoMu24_v || pass_HLT_IsoMu27_v );

    	bool pass_e = false;
    	if(_year==2016) pass_e = ( pass_HLT_Ele27_WPTight_Gsf_v || pass_HLT_Ele25_eta2p1_WPTight_Gsf_v || pass_HLT_Ele27_eta2p1_WPLoose_Gsf_v );
    	else if(_year==2017) pass_e = ( pass_HLT_Ele35_WPTight_Gsf_v || pass_HLT_Ele32_WPTight_Gsf_v );
    	else if(_year==2018) pass_e = ( pass_HLT_Ele32_WPTight_Gsf_v );
    
    	bool pass_2e = false;
    	if(_year==2016) pass_2e = pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v;
    	else if(_year==2017) pass_2e = pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v;
    	else if(_year==2018) pass_2e = pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v;

    	bool pass_2m = false;
    	if(_year==2016) pass_2m = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v || pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v || pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v || pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v);
    	else if(_year==2017) pass_2m = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v || pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v);
    	else if(_year==2018) pass_2m = pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v;

    	bool pass_em = false;
    	if(_year==2016) pass_em = (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v || pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v || pass_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v);
    	else if(_year==2017) pass_em = (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v || pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v);
    	else if(_year==2018) pass_em = (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v || pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v);

    	/*bool pass_et = false;
    	if(_year==2016) pass_et = (pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v || pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v || pass_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v);
    	else if(_year==2017) pass_et = pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v;
    	else if(_year==2018) pass_et = (pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v || pass_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1_v);

    	bool pass_mt = false;
    	if(_year==2016) pass_mt = pass_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v;
    	else if(_year==2017) pass_mt = pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v;
    	else if(_year==2018) pass_mt = (pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v || pass_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v);

    	bool pass_2t = false;
    	if(_year==2016) pass_2t = (pass_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v || pass_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v );
    	else if(_year==2017) pass_2t = (pass_HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg_v || pass_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v);
    	else if(_year==2018) pass_2t = (pass_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v || pass_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v || pass_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v);

    	bool pass_3e = false;
    	if(_year==2016) pass_3e = pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v;
    	else if(_year==2017) pass_3e = pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v;
    	else if(_year==2018) pass_3e = pass_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v;

    	bool pass_3m = false;
    	if(_year==2016) pass_3m = pass_HLT_TripleMu_12_10_5_v;
    	else if(_year==2017) pass_3m = pass_HLT_TripleMu_12_10_5_v;
    	else if(_year==2018) pass_3m = pass_HLT_TripleMu_12_10_5_v;

    	bool pass_m2e = false;
    	if(_year==2016) pass_m2e = pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v;
    	else if(_year==2017) pass_m2e = pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v;
    	else if(_year==2018) pass_m2e = pass_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v;

    	bool pass_2me = false;
    	if(_year==2016) pass_2me = pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v;
    	else if(_year==2017) pass_2me = pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v;
    	else if(_year==2018) pass_2me = pass_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v;*/

			bool _triggerbitmask = false;

			if( _year == 2016 || _year == 2017 ){

				if(file_in.Contains("SingleElectron")){				
					//if( (pass_e || pass_et) )
          if( pass_e )
						_triggerbitmask = true;				
				}

				else if(file_in.Contains("SingleMuon")){
					//if( (pass_m || pass_mt) && !(pass_e || pass_et) )
          if( pass_m && !pass_e )
						_triggerbitmask = true;				
				}

				else if(file_in.Contains("DoubleEG")){				
					//if( (pass_2e || pass_m2e || pass_3e) && !(pass_e || pass_et) && !(pass_m || pass_mt) )
          if( pass_2e && !pass_e && !pass_m )
						_triggerbitmask = true;
				}

				else if(file_in.Contains("DoubleMu")){				
					//if( (pass_2m || pass_2me || pass_3m) && !(pass_e || pass_et) && !(pass_m || pass_mt) && !(pass_2e || pass_m2e || pass_3e) )
          if( pass_2m && !pass_e && !pass_m && !pass_2e )
						_triggerbitmask = true;
				}

				else if(file_in.Contains("MuonEG")){
					//if( (pass_em) && !(pass_e || pass_et) && !(pass_m || pass_mt) && !(pass_2e || pass_m2e || pass_3e) && !(pass_2m || pass_2me || pass_3m) ) 
          if( pass_em && !pass_e && !pass_m && !pass_2e && !pass_2m ) 
						_triggerbitmask = true;
				}

			}

			else if( _year == 2018 ){

				if(file_in.Contains("EGamma")){				
					//if( (pass_e || pass_et || pass_2e || pass_m2e || pass_3e) )
          if( pass_e || pass_2e )
						_triggerbitmask = true;				
				}

				else if(file_in.Contains("SingleMuon")){
					//if( (pass_m || pass_mt) && !(pass_e || pass_et || pass_2e || pass_m2e || pass_3e)  )
          if( pass_m && !pass_e && !pass_2e )
						_triggerbitmask = true;				
				}

				else if(file_in.Contains("DoubleMu")){				
					//if( (pass_2m || pass_2me || pass_3m) && !(pass_e || pass_et || pass_2e || pass_m2e || pass_3e) && !(pass_m || pass_mt) )
          if( pass_2m && !pass_e && !pass_2e && !pass_m )
						_triggerbitmask = true;
				}

				else if(file_in.Contains("MuonEG")){
					//if( (pass_em) && !(pass_2m || pass_2me || pass_3m) && !(pass_e || pass_et || pass_2e || pass_m2e || pass_3e) && ! (pass_m || pass_mt) ) 
          if( pass_em && !pass_e && !pass_2e && !pass_m && !pass_2m )
						_triggerbitmask = true;
				}

			}

			if (_triggerbitmask) {
        tree_new->Fill();
        n_out++;
      }
		
		}	

		f_new->cd();
		tree_new->Write();

    cout<<n_out<<"/"<<n_in<<endl;

	}

	f_new->Close();

	return;

}


void test(){

  /*TString dirin = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/";

  vector<TString> samplein;

  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockB");
  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockC");
  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockD");
  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockE");
  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockF");
  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockG");
  samplein.push_back("Oct19v1_Data_2016_SingleElectron_BlockH");

  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockB");
  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockC");
  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockD");
  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockE");
  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockF");
  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockG");
  samplein.push_back("Oct19v1_Data_2016_SingleMuon_BlockH");

  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockB");
  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockC");
  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockD");
  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockE");
  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockF");
  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockG");
  samplein.push_back("Oct19v1_Data_2016_DoubleEG_BlockH");

  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockB");
  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockC");
  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockD");
  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockE");
  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockF");
  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockG");
  samplein.push_back("Oct19v1_Data_2016_DoubleMu_BlockH");

  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockB");
  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockC");
  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockD");
  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockE");
  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockF");
  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockG");
  samplein.push_back("Oct19v1_Data_2016_MuonEG_BlockH");*/


  /*TString dirin = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/";

  vector<TString> samplein;

  samplein.push_back("Oct19v1_Data_2017_SingleElectron_BlockB");
  samplein.push_back("Oct19v1_Data_2017_SingleElectron_BlockC");
  samplein.push_back("Oct19v1_Data_2017_SingleElectron_BlockD");
  samplein.push_back("Oct19v1_Data_2017_SingleElectron_BlockE");
  samplein.push_back("Oct19v1_Data_2017_SingleElectron_BlockF");

  samplein.push_back("Oct19v1_Data_2017_SingleMuon_BlockB");
  samplein.push_back("Oct19v1_Data_2017_SingleMuon_BlockC");
  samplein.push_back("Oct19v1_Data_2017_SingleMuon_BlockD");
  samplein.push_back("Oct19v1_Data_2017_SingleMuon_BlockE");
  samplein.push_back("Oct19v1_Data_2017_SingleMuon_BlockF");

  samplein.push_back("Oct19v1_Data_2017_DoubleEG_BlockB");
  samplein.push_back("Oct19v1_Data_2017_DoubleEG_BlockC");
  samplein.push_back("Oct19v1_Data_2017_DoubleEG_BlockD");
  samplein.push_back("Oct19v1_Data_2017_DoubleEG_BlockE");
  samplein.push_back("Oct19v1_Data_2017_DoubleEG_BlockF");

  samplein.push_back("Oct19v1_Data_2017_DoubleMu_BlockB");
  samplein.push_back("Oct19v1_Data_2017_DoubleMu_BlockC");
  samplein.push_back("Oct19v1_Data_2017_DoubleMu_BlockD");
  samplein.push_back("Oct19v1_Data_2017_DoubleMu_BlockE");
  samplein.push_back("Oct19v1_Data_2017_DoubleMu_BlockF");

  samplein.push_back("Oct19v1_Data_2017_MuonEG_BlockB");
  samplein.push_back("Oct19v1_Data_2017_MuonEG_BlockC");
  samplein.push_back("Oct19v1_Data_2017_MuonEG_BlockD");
  samplein.push_back("Oct19v1_Data_2017_MuonEG_BlockE");
  samplein.push_back("Oct19v1_Data_2017_MuonEG_BlockF");*/

  TString dirin = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/";

  vector<TString> samplein;

  /*samplein.push_back("Oct19v1_Data_2018_EGamma_BlockA");
  samplein.push_back("Oct19v1_Data_2018_EGamma_BlockB");
  samplein.push_back("Oct19v1_Data_2018_EGamma_BlockC");
  samplein.push_back("Oct19v1_Data_2018_EGamma_BlockD");

  samplein.push_back("Oct19v1_Data_2018_SingleMuon_BlockA");
  samplein.push_back("Oct19v1_Data_2018_SingleMuon_BlockB");
  samplein.push_back("Oct19v1_Data_2018_SingleMuon_BlockC");
  samplein.push_back("Oct19v1_Data_2018_SingleMuon_BlockD");*/

  samplein.push_back("Oct19v1_Data_2018_DoubleMu_BlockA");
  samplein.push_back("Oct19v1_Data_2018_DoubleMu_BlockB");
  samplein.push_back("Oct19v1_Data_2018_DoubleMu_BlockC");
  samplein.push_back("Oct19v1_Data_2018_DoubleMu_BlockD");

  samplein.push_back("Oct19v1_Data_2018_MuonEG_BlockA");
  samplein.push_back("Oct19v1_Data_2018_MuonEG_BlockB");
  samplein.push_back("Oct19v1_Data_2018_MuonEG_BlockC");
  samplein.push_back("Oct19v1_Data_2018_MuonEG_BlockD");


  for (unsigned int i=0; i<samplein.size(); i++){

    cout<<"********* SR **********"<<endl;

    vector<TString> treename;
    treename.push_back("HTauTauTree_2lss1tau_SR");

    cout<<"Sample: "<<samplein.at(i)<<": ";

  	TString filein  = dirin+"ntuple_"+samplein.at(i)+"_MEM_SR_SF_v1.root";
  	TString fileout = dirin+"ntuple_"+samplein.at(i)+"_MEM_SR_SF_v1_noOverlap.root";

  	veto_overlap_datasets(filein,fileout,treename);

  }

  for (unsigned int i=0; i<samplein.size(); i++){

    cout<<"********* FAKE **********"<<endl;

    vector<TString> treename;
    treename.push_back("HTauTauTree_2lss1tau_fake");

    cout<<"Sample: "<<samplein.at(i)<<": ";

    TString filein  = dirin+"ntuple_"+samplein.at(i)+"_MEM_fake_SF_v1.root";
    TString fileout = dirin+"ntuple_"+samplein.at(i)+"_MEM_fake_SF_v1_noOverlap.root";

    veto_overlap_datasets(filein,fileout,treename);

  }

  for (unsigned int i=0; i<samplein.size(); i++){

    cout<<"********* FLIP **********"<<endl;

    vector<TString> treename;
    treename.push_back("HTauTauTree_2lss1tau_flip");

    cout<<"Sample: "<<samplein.at(i)<<": ";

    TString filein  = dirin+"ntuple_"+samplein.at(i)+"_MEM_flip_SF_v1.root";
    TString fileout = dirin+"ntuple_"+samplein.at(i)+"_MEM_flip_SF_v1_noOverlap.root";

    veto_overlap_datasets(filein,fileout,treename);

  }


}
