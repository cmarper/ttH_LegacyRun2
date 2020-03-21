#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

using namespace std;


void merge_MEM(TString sample, TString year, TString type){

    ////////////////////////////////////////////////////////////////////////////////

    TString filein1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/"+year+"/JECdown/"+type+"/ntuple_"+sample+"_JECdown.root";
    //cout<<"Split file: "<<filein1<<endl;

    TString treename1;
    treename1 = "HTauTauTree_2lss1tau_SR";

    TChain * tree1 = new TChain(treename1);
    tree1->Add(filein1);

    int nentries1 = tree1->GetEntries();

    ////////////////////////////////////////////////////////////////////////////////

    TString fileout;
    fileout = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/"+year+"/JECdown/"+type+"/ntuple_"+sample+"_MEM_SR_JECdown.root";
    cout<<fileout<<endl;
    //cout<<"....."<<endl;

    TFile* out_file = TFile::Open(fileout,"RECREATE");

    TTree* treeout = tree1->GetTree()->CloneTree();

    int nentriesout = treeout->GetEntries();

    ULong64_t   _EventNumber_out;
    float       _Integral_ttH_out;
    float       _Integral_ttbar_DL_fakelep_tlep_out;
    float       _Integral_ttbar_DL_fakelep_ttau_out;
    float       _Integral_ttZ_out;
    float       _Integral_ttZ_Zll_out;
    int         _integration_type_out;
    
    treeout->SetBranchAddress("EventNumber",&_EventNumber_out);

    TBranch* b_Integral_ttH = treeout->Branch("Integral_ttH",&_Integral_ttH_out,"Integral_ttH/F");
    TBranch* b_Integral_ttbar_DL_fakelep_tlep = treeout->Branch("Integral_ttbar_DL_fakelep_tlep",&_Integral_ttbar_DL_fakelep_tlep_out,"Integral_ttbar_DL_fakelep_tlep/F");
    TBranch* b_Integral_ttbar_DL_fakelep_ttau = treeout->Branch("Integral_ttbar_DL_fakelep_ttau",&_Integral_ttbar_DL_fakelep_ttau_out,"Integral_ttbar_DL_fakelep_ttau/F");
    TBranch* b_Integral_ttZ = treeout->Branch("Integral_ttZ",&_Integral_ttZ_out,"Integral_ttZ/F");
    TBranch* b_Integral_ttZ_Zll = treeout->Branch("Integral_ttZ_Zll",&_Integral_ttZ_Zll_out,"Integral_ttZ_Zll/F");
    TBranch* b_integration_type = treeout->Branch("integration_type",&_integration_type_out,"integration_type/I");

    ////////////////////////////////////////////////////////////////////////////////

    TString filein2;
    filein2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/"+year+"/JECdown/"+type+"/ntuple_"+sample+"_MEM_SR_JECdown.root";

	TChain * tree2 = new TChain("T");
	tree2->Add(filein2);

	Long64_t nentries2 = tree2->GetEntries();

    ULong64_t _EventNumber_2;
    float _Integral_ttH_2;
    float _Integral_ttbar_DL_fakelep_tlep_2;
    float _Integral_ttbar_DL_fakelep_ttau_2;
    float _Integral_ttZ_2;
    float _Integral_ttZ_Zll_2;
    int _integration_type_2;

    tree2->SetBranchAddress("EventNumber",&_EventNumber_2);
    tree2->SetBranchAddress("Integral_ttH",&_Integral_ttH_2);
    tree2->SetBranchAddress("Integral_ttbar_DL_fakelep_tlep",&_Integral_ttbar_DL_fakelep_tlep_2);
    tree2->SetBranchAddress("Integral_ttbar_DL_fakelep_ttau",&_Integral_ttbar_DL_fakelep_ttau_2);
    tree2->SetBranchAddress("Integral_ttZ",&_Integral_ttZ_2);
    tree2->SetBranchAddress("Integral_ttZ_Zll",&_Integral_ttZ_Zll_2);
    tree2->SetBranchAddress("integration_type",&_integration_type_2);

    ////////////////////////////////////////////////////////////////////////////////

    if( nentries1 != nentries2 )
        cout<<" **** ERROR ****: different number of events in input trees! "<<endl;

    ////////////////////////////////////////////////////////////////////////////////
 
    vector<std::pair<ULong64_t, float> > Integral_ttH_vector;
    vector<std::pair<ULong64_t, float> > Integral_ttbar_DL_fakelep_tlep_vector;
    vector<std::pair<ULong64_t, float> > Integral_ttbar_DL_fakelep_ttau_vector;
    vector<std::pair<ULong64_t, float> > Integral_ttZ_vector;
    vector<std::pair<ULong64_t, float> > Integral_ttZ_Zll_vector;
    vector<std::pair<ULong64_t, int> >   integration_type_vector;

    Integral_ttH_vector.clear();    
    Integral_ttbar_DL_fakelep_tlep_vector.clear();  
    Integral_ttbar_DL_fakelep_ttau_vector.clear();  
    Integral_ttZ_vector.clear();  
    Integral_ttZ_Zll_vector.clear();  
    integration_type_vector.clear();

    for(int ientry=0;ientry<nentries2;ientry++){

        _EventNumber_2 = -999;
        _Integral_ttH_2 = -999;
        _Integral_ttbar_DL_fakelep_tlep_2 = -999;
        _Integral_ttbar_DL_fakelep_ttau_2 = -999;
        _Integral_ttZ_2 = -999;
        _Integral_ttZ_Zll_2 = -999;
        _integration_type_2 = -999;

        tree2->GetEntry(ientry);

        Integral_ttH_vector.push_back( std::make_pair(_EventNumber_2, _Integral_ttH_2) );
        Integral_ttbar_DL_fakelep_tlep_vector.push_back( std::make_pair(_EventNumber_2, _Integral_ttbar_DL_fakelep_tlep_2) );
        Integral_ttbar_DL_fakelep_ttau_vector.push_back( std::make_pair(_EventNumber_2, _Integral_ttbar_DL_fakelep_ttau_2) );
        Integral_ttZ_vector.push_back( std::make_pair(_EventNumber_2, _Integral_ttZ_2) );
        Integral_ttZ_Zll_vector.push_back( std::make_pair(_EventNumber_2, _Integral_ttZ_Zll_2) );
        integration_type_vector.push_back( std::make_pair(_EventNumber_2, _integration_type_2) );

    }

    ////////////////////////////////////////////////////////////////////////////////

    int vectorsize = Integral_ttH_vector.size();

    if( nentries1 != vectorsize )
        cout<<" **** ERROR ****: different number of events in tree and vector!"<<endl;

    ////////////////////////////////////////////////////////////////////////////////

    for(int ientry=0;ientry<nentries2;ientry++){ 

        _EventNumber_out = -999;
        _Integral_ttH_out = -999;
        _Integral_ttbar_DL_fakelep_tlep_out = -999;
        _Integral_ttbar_DL_fakelep_ttau_out = -999;
        _Integral_ttZ_out = -999;
        _Integral_ttZ_Zll_out = -999;
        _integration_type_out = -999;

        treeout->GetEntry(ientry);

        for(unsigned int i=0; i<Integral_ttH_vector.size();i++){

            if (_EventNumber_out == Integral_ttH_vector.at(i).first){

                _Integral_ttH_out = Integral_ttH_vector.at(i).second;
                _Integral_ttbar_DL_fakelep_tlep_out = Integral_ttbar_DL_fakelep_tlep_vector.at(i).second;
                _Integral_ttbar_DL_fakelep_ttau_out = Integral_ttbar_DL_fakelep_ttau_vector.at(i).second;
                _Integral_ttZ_out = Integral_ttZ_vector.at(i).second;
                _Integral_ttZ_Zll_out = Integral_ttZ_Zll_vector.at(i).second;
                _integration_type_out = integration_type_vector.at(i).second;

                break;
            }  
        }

        b_Integral_ttH->Fill();
        b_Integral_ttbar_DL_fakelep_tlep->Fill();
        b_Integral_ttbar_DL_fakelep_ttau->Fill();
        b_Integral_ttZ->Fill();
        b_Integral_ttZ_Zll->Fill();
        b_integration_type->Fill();

    }

    ////////////////////////////////////////////////////////////////////////////////

    if( nentries1 != treeout->GetEntries() )
        cout<<" **** ERROR ****: different number of events in input and output trees!"<<endl;

    ////////////////////////////////////////////////////////////////////////////////
  
    treeout->SetDirectory(out_file);
    treeout->Write();
    out_file->Close();


}


void test(){

merge_MEM("Oct19v1_MC_2016_ttHJetToNonbb","2016","ttH");
merge_MEM("Oct19v1_MC_2016_THQ_ctcvcp","2016","ttH");
merge_MEM("Oct19v1_MC_2016_THW_ctcvcp","2016","ttH");
merge_MEM("Oct19v1_MC_2017_ttHJetToNonbb","2017","ttH");
merge_MEM("Oct19v1_MC_2017_THQ_ctcvcp","2017","ttH");
merge_MEM("Oct19v3_MC_2017_THW_ctcvcp","2017","ttH");
merge_MEM("Oct19v2_MC_2018_ttHJetToNonbb","2018","ttH");
merge_MEM("Oct19v1_MC_2018_THQ_ctcvcp","2018","ttH");
merge_MEM("Oct19v1_MC_2018_THW_ctcvcp","2018","ttH");

merge_MEM("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3","2016","ttV");
merge_MEM("Oct19v1_MC_2016_TTZToLL_M-1to10","2016","ttV");
merge_MEM("Oct19v1_MC_2016_TTWJetsToLNu","2016","ttV");
merge_MEM("Oct19v1_MC_2016_TTWW","2016","ttV");
merge_MEM("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS","2017","ttV");
merge_MEM("Oct19v1_MC_2017_TTZToLL_M-1to10","2017","ttV");
merge_MEM("Oct19v1_MC_2017_TTWJetsToLNu","2017","ttV");
merge_MEM("Oct19v1_MC_2017_TTWW","2017","ttV");
merge_MEM("Oct19v1_MC_2018_TTZToLLNuNu_M-10","2018","ttV");
merge_MEM("Oct19v1_MC_2018_TTZToLL_M-1to10","2018","ttV");
merge_MEM("Oct19v1_MC_2018_TTWJetsToLNu","2018","ttV");
merge_MEM("Oct19v1_MC_2018_TTWW_ext2","2018","ttV");

merge_MEM("Oct19v1_MC_2016_WZTo3LNu","2016","EWK");
merge_MEM("Oct19v1_MC_2016_ZZTo4L","2016","EWK");
merge_MEM("Oct19v1_MC_2017_WZTo3LNu","2017","EWK");
merge_MEM("Oct19v1_MC_2017_ZZTo4L_ext1","2017","EWK");
merge_MEM("Oct19v2_MC_2018_WZTo3LNu_ext1","2018","EWK");
merge_MEM("Oct19v4_MC_2018_ZZTo4L_ext2","2018","EWK");

merge_MEM("Oct19v1_MC_2016_WWW","2016","Rares");
merge_MEM("Oct19v1_MC_2016_WWZ","2016","Rares");
merge_MEM("Oct19v1_MC_2016_WZZ","2016","Rares");
merge_MEM("Oct19v1_MC_2016_ZZZ","2016","Rares");
merge_MEM("Oct19v1_MC_2016_WZG","2016","Rares");
merge_MEM("Oct19v1_MC_2016_WGToLNuG_ext1","2016","Rares");
merge_MEM("Oct19v1_MC_2016_ZGTo2LG","2016","Rares");
merge_MEM("Oct19v1_MC_2016_TGJets_leptonDecays","2016","Rares");
merge_MEM("Oct19v1_MC_2016_TTGJets","2016","Rares");
merge_MEM("Oct19v1_MC_2016_tZq_ll_PS","2016","Rares");
merge_MEM("Oct19v1_MC_2016_WpWpJJ","2016","Rares");
merge_MEM("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering","2016","Rares");
merge_MEM("Oct19v1_MC_2016_TTTT","2016","Rares");
merge_MEM("Oct19v1_MC_2017_WWW","2017","Rares");
merge_MEM("Oct19v1_MC_2017_WWZ","2017","Rares");
merge_MEM("Oct19v2_MC_2017_WZZ","2017","Rares");
merge_MEM("Oct19v2_MC_2017_ZZZ","2017","Rares");
merge_MEM("Oct19v1_MC_2017_WZG","2017","Rares");
merge_MEM("Oct19v1_MC_2017_WGToLNuG","2017","Rares");
merge_MEM("Oct19v1_MC_2017_ZGToLLG","2017","Rares");
merge_MEM("Oct19v1_MC_2017_TGJets","2017","Rares");
merge_MEM("Oct19v1_MC_2017_TTGJets_ext1","2017","Rares");
merge_MEM("Oct19v1_MC_2017_tZq_ll","2017","Rares");
merge_MEM("Oct19v2_MC_2017_WpWpJJ","2017","Rares");
merge_MEM("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering","2017","Rares");
merge_MEM("Oct19v1_MC_2017_TTTT","2017","Rares");
merge_MEM("Oct19v2_MC_2018_WWW","2018","Rares");
merge_MEM("Oct19v2_MC_2018_WWZ","2018","Rares");
merge_MEM("Oct19v1_MC_2018_WZZ","2018","Rares");
merge_MEM("Oct19v1_MC_2018_ZZZ","2018","Rares");
merge_MEM("Oct19v1_MC_2018_WZG","2018","Rares");
merge_MEM("Oct19v1_MC_2018_WGToLNuG","2018","Rares");
merge_MEM("Oct19v2_MC_2018_ZGToLLG","2018","Rares");
merge_MEM("Oct19v1_MC_2018_TGJets","2018","Rares");
merge_MEM("Oct19v1_MC_2018_tZq_ll","2018","Rares");
merge_MEM("Oct19v1_MC_2018_WpWpJJ","2018","Rares");
merge_MEM("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering","2018","Rares");

//MISSING TTBAR 2016
merge_MEM("Oct19v1_MC_2017_TTJets_DiLept","2017","ttbar");
merge_MEM("Oct19v1_MC_2017_TTJets_SingleLeptFromT","2017","ttbar");
merge_MEM("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar","2017","ttbar");
merge_MEM("Oct19v1_MC_2018_TTJets_DiLept","2018","ttbar");
merge_MEM("Oct19v1_MC_2018_TTJets_SingleLeptFromT","2018","ttbar");
merge_MEM("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar","2018","ttbar");

}

