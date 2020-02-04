#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

using namespace std;


void merge_MEM(TString sample, TString year, TString type, TString region){

    ////////////////////////////////////////////////////////////////////////////////

    TString filein1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted/"+year+"/nominal/"+type+"/ntuple_"+sample+".root";
    cout<<"Split file: "<<filein1<<endl;

    TString treename1;
    if(region=="SR") treename1 = "HTauTauTree_2lss1tau_SR";
    else if(region=="fake") treename1 = "HTauTauTree_2lss1tau_fake";
    else if(region=="flip") treename1 = "HTauTauTree_2lss1tau_flip";
    else cout<<"No region specified!"<<endl;

    TChain * tree1 = new TChain(treename1);
    tree1->Add(filein1);

    int nentries1 = tree1->GetEntries();

    ////////////////////////////////////////////////////////////////////////////////

    TString fileout;
    if(region=="SR") fileout = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/"+year+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR.root";
    else if(region=="fake") fileout = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/"+year+"/nominal/"+type+"/ntuple_"+sample+"_MEM_fake.root";
    else if(region=="flip") fileout = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/"+year+"/nominal/"+type+"/ntuple_"+sample+"_MEM_flip.root";
    cout<<"Output file: "<<fileout<<endl;

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
    if(region=="SR") filein2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/"+year+"/nominal/"+type+"/ntuple_"+sample+"_MEM_SR.root";
    else if(region=="fake") filein2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/"+year+"/nominal/"+type+"/ntuple_"+sample+"_MEM_fake.root";
    else if(region=="flip") filein2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_MEM/"+year+"/nominal/"+type+"/ntuple_"+sample+"_MEM_flip.root";

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

    //TString myregion = "SR";
    //TString myregion = "fake";
    TString myregion = "flip";

    /*merge_MEM("Oct19v1_MC_2016_ttHJetToNonbb","2016","ttH",myregion);
    merge_MEM("Oct19v1_MC_2016_ttH_ctcvcp","2016","ttH",myregion);
    merge_MEM("Oct19v1_MC_2016_THQ_ctcvcp","2016","ttH",myregion);
    merge_MEM("Oct19v1_MC_2016_THW_ctcvcp","2016","ttH",myregion);

    merge_MEM("Oct19v1_MC_2017_ttHJetToNonbb","2017","ttH",myregion);
    merge_MEM("Oct19v1_MC_2017_THQ_ctcvcp","2017","ttH",myregion);
    merge_MEM("Oct19v3_MC_2017_THW_ctcvcp","2017","ttH",myregion);
    merge_MEM("Oct19v1_MC_2017_TTH_ctcvcp","2017","ttH",myregion);

    merge_MEM("Oct19v2_MC_2018_ttHJetToNonbb","2018","ttH",myregion);
    merge_MEM("Oct19v2_MC_2018_TTH_ctcvcp","2018","ttH",myregion);
    merge_MEM("Oct19v1_MC_2018_THQ_ctcvcp","2018","ttH",myregion);
    merge_MEM("Oct19v1_MC_2018_THW_ctcvcp","2018","ttH",myregion);

    merge_MEM("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2","2016","ttV",myregion);
    merge_MEM("Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3","2016","ttV",myregion);
    merge_MEM("Oct19v1_MC_2016_TTZToLL_M-1to10","2016","ttV",myregion);
    merge_MEM("Oct19v1_MC_2016_TTWJetsToLNu","2016","ttV",myregion);
    merge_MEM("Oct19v1_MC_2016_TTWW","2016","ttV",myregion);

    merge_MEM("Oct19v1_MC_2017_TTZToLLNuNu_M-10","2017","ttV",myregion);
    merge_MEM("Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS","2017","ttV",myregion);
    merge_MEM("Oct19v1_MC_2017_TTZToLL_M-1to10","2017","ttV",myregion);
    merge_MEM("Oct19v1_MC_2017_TTWJetsToLNu","2017","ttV",myregion);
    merge_MEM("Oct19v1_MC_2017_TTWJetsToLNu_PS","2017","ttV",myregion);
    merge_MEM("Oct19v1_MC_2017_TTWW","2017","ttV",myregion);

    merge_MEM("Oct19v1_MC_2018_TTZToLLNuNu_M-10","2018","ttV",myregion);
    merge_MEM("Oct19v1_MC_2018_TTZToLL_M-1to10","2018","ttV",myregion);
    merge_MEM("Oct19v1_MC_2018_TTWJetsToLNu","2018","ttV",myregion);
    merge_MEM("Oct19v1_MC_2018_TTWW_ext1","2018","ttV",myregion);
    merge_MEM("Oct19v1_MC_2018_TTWW_ext2","2018","ttV",myregion);

    merge_MEM("Oct19v1_MC_2016_WWW","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WWZ","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WZZ","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_ZZZ","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WZG","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WGToLNuG_ext1","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WGToLNuG_ext2","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WGToLNuG_ext3","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_ZGTo2LG","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_TGJets_leptonDecays","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_TTGJets","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_TTGJets_ext1","2016","Rares",myregion);
    merge_MEM("Oct19v2_MC_2016_tZq_ll","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_tZq_ll_PS","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_WpWpJJ","2016","Rares",myregion);
    merge_MEM("Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering","2016","Rares",myregion);
    merge_MEM("Oct19v1_MC_2016_TTTT","2016","Rares",myregion);

    merge_MEM("Oct19v1_MC_2017_WWW","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_WWZ","2017","Rares",myregion);
    merge_MEM("Oct19v2_MC_2017_WZZ","2017","Rares",myregion);
    merge_MEM("Oct19v2_MC_2017_ZZZ","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_WZG","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_WGToLNuG","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_ZGToLLG","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_TGJets","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_TTGJets","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_TTGJets_ext1","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_tZq_ll","2017","Rares",myregion);
    merge_MEM("Oct19v2_MC_2017_WpWpJJ","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_TTTT","2017","Rares",myregion);
    merge_MEM("Oct19v1_MC_2017_TTTT_PS","2017","Rares",myregion);

    merge_MEM("Oct19v2_MC_2018_WWW","2018","Rares",myregion);
    merge_MEM("Oct19v2_MC_2018_WWZ","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_WZZ","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_ZZZ","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_WZG","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_WGToLNuG","2018","Rares",myregion);
    merge_MEM("Oct19v2_MC_2018_ZGToLLG","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_TGJets","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_TTGJets","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_tZq_ll","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_WpWpJJ","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering","2018","Rares",myregion);
    merge_MEM("Oct19v1_MC_2018_TTTT","2018","Rares",myregion);

    merge_MEM("Oct19v1_MC_2016_DYJetsToLL_M-10to50","2016","EWK",myregion);
    merge_MEM("Oct19v1_MC_2016_DYJetsToLL_M-50","2016","EWK",myregion);
    merge_MEM("Oct19v1_MC_2016_WJetsToLNu_ext2","2016","EWK",myregion);
    merge_MEM("Oct19v1_MC_2016_WJetsToLNu","2016","EWK",myregion);
    merge_MEM("Oct19v1_MC_2016_WWTo2L2Nu","2016","EWK",myregion);
    merge_MEM("Oct19v1_MC_2016_WZTo3LNu","2016","EWK",myregion);
    merge_MEM("Oct19v1_MC_2016_ZZTo4L","2016","EWK",myregion);
    
    merge_MEM("Oct19v1_MC_2017_DYJetsToLL_M-10to50","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_DYJetsToLL_M-50","2017","EWK",myregion);
    merge_MEM("Oct19v3_MC_2017_DYJetsToLL_M-50_ext1","2017","EWK",myregion);
    merge_MEM("Oct19v2_MC_2017_WJetsToLNu","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_WJetsToLNu_ext1","2017","EWK",myregion);
    merge_MEM("Oct19v2_MC_2017_WWTo2L2Nu","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_WWTo2L2Nu_ext1","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_WZTo3LNu","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_ZZTo4L","2017","EWK",myregion);
    merge_MEM("Oct19v1_MC_2017_ZZTo4L_ext1","2017","EWK",myregion);
    merge_MEM("Oct19v2_MC_2017_ZZTo4L_ext2","2017","EWK",myregion);
    
    merge_MEM("Oct19v3_MC_2018_DYJetsToLL_M-10to50","2018","EWK",myregion);
    merge_MEM("Oct19v2_MC_2018_DYJetsToLL_M-50","2018","EWK",myregion);
    merge_MEM("Oct19v3_MC_2018_DYJetsToLL_M-50_ext2","2018","EWK",myregion);
    merge_MEM("Oct19v2_MC_2018_WJetsToLNu","2018","EWK",myregion);
    merge_MEM("Oct19v3_MC_2018_WWTo2L2Nu","2018","EWK",myregion);
    merge_MEM("Oct19v1_MC_2018_WZTo3LNu","2018","EWK",myregion);
    merge_MEM("Oct19v2_MC_2018_WZTo3LNu_ext1","2018","EWK",myregion);
    merge_MEM("Oct19v2_MC_2018_ZZTo4L","2018","EWK",myregion);
    merge_MEM("Oct19v4_MC_2018_ZZTo4L_ext2","2018","EWK",myregion);

    merge_MEM("Oct19v1_MC_2016_ST_s-channel","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_s-channel_PS","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_t-channel_top","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_t-channel_antitop","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_t-channel_antitop_PS","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_tW_top","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_tW_antitop","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_ST_tWll","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_TTJets_DiLept_ext1","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_TTJets_DiLept","2016","ttbar",myregion);
    merge_MEM("Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_TTJets_SingleLeptFromT","2016","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2016_TTJets_SingleLeptFromTbar","2016","ttbar",myregion);
    merge_MEM("Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1","2016","ttbar",myregion);

    merge_MEM("Oct19v1_MC_2017_ST_s-channel","2017","ttbar",myregion);
    merge_MEM("Oct19v2_MC_2017_ST_s-channel_PS","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_ST_t-channel_top","2017","ttbar",myregion);
    merge_MEM("Oct19v2_MC_2017_ST_t-channel_top_PS","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_ST_t-channel_antitop","2017","ttbar",myregion);
    merge_MEM("Oct19v2_MC_2017_ST_t-channel_antitop_PS","2017","ttbar",myregion);
    merge_MEM("Oct19v3_MC_2017_ST_tW_top","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_ST_tW_top_PS","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_ST_tW_antitop","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_ST_tW_antitop_PS","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_ST_tWll","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_TTJets_DiLept","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_TTJets_SingleLeptFromT","2017","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2017_TTJets_SingleLeptFromTbar","2017","ttbar",myregion);

    merge_MEM("Oct19v1_MC_2018_ST_s-channel","2018","ttbar",myregion);
    merge_MEM("Oct19v2_MC_2018_ST_t-channel_top","2018","ttbar",myregion);
    merge_MEM("Oct19v3_MC_2018_ST_t-channel_antitop","2018","ttbar",myregion);
    merge_MEM("Oct19v3_MC_2018_ST_tW_top","2018","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2018_ST_tW_antitop","2018","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2018_ST_tWll","2018","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2018_TTJets_DiLept","2018","ttbar",myregion);
    merge_MEM("Oct19v1_MC_2018_TTJets_SingleLeptFromT","2018","ttbar",myregion);
    merge_MEM("Oct19v2_MC_2018_TTJets_SingleLeptFromTbar","2018","ttbar",myregion);

    merge_MEM("Oct19v1_MC_2016_GluGluHToTauTau","2016","ggH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluHToZZTo4L","2016","ggH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluHToWWToLNuQQ","2016","ggH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluHToWWTo2L2Nu","2016","ggH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluHToMuMu","2016","ggH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluHToBB","2016","ggH",myregion);
    merge_MEM("Oct19v6_MC_2016_GluGluHToBB_ext1","2016","ggH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluHToGG","2016","ggH",myregion);

    merge_MEM("Oct19v1_MC_2017_GluGluHToTauTau","2017","ggH",myregion);
    merge_MEM("Oct19v3_MC_2017_GluGluHToTauTau_ext1","2017","ggH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluHToZZTo4L_ext1","2017","ggH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluHToZZTo4L_ext3","2017","ggH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluHToZZTo4L_ext4","2017","ggH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluHToZZTo2L2Q","2017","ggH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluHToWWToLNuQQ","2017","ggH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluHToWWTo2L2Nu","2017","ggH",myregion);
    merge_MEM("Oct19v3_MC_2017_GluGluHToMuMu","2017","ggH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluHToMuMu_ext1","2017","ggH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluHToBB","2017","ggH",myregion);
    merge_MEM("Oct19v3_MC_2017_GluGluHToGG","2017","ggH",myregion);

    merge_MEM("Oct19v2_MC_2018_GluGluHToTauTau","2018","ggH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluHToZZTo4L","2018","ggH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluHToZZTo2L2Q","2018","ggH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluHToWWToLNuQQ","2018","ggH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluHToWWTo2L2Nu","2018","ggH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluHToMuMu","2018","ggH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluHToMuMu_ext1","2018","ggH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluHToBB","2018","ggH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluHToGG","2018","ggH",myregion);

    merge_MEM("Oct19v2_MC_2016_VBFHToTauTau","2016","VBF",myregion);
    merge_MEM("Oct19v2_MC_2016_VBF_HToZZTo4L","2016","VBF",myregion);
    merge_MEM("Oct19v1_MC_2016_VBFHToWWToLNuQQ","2016","VBF",myregion);
    merge_MEM("Oct19v1_MC_2016_VBFHToWWTo2L2Nu","2016","VBF",myregion);
    merge_MEM("Oct19v1_MC_2016_VBFHToMuMu","2016","VBF",myregion);
    merge_MEM("Oct19v3_MC_2016_VBFHToBB","2016","VBF",myregion);
    merge_MEM("Oct19v1_MC_2016_VBFHToBB_ext1","2016","VBF",myregion);
    merge_MEM("Oct19v1_MC_2016_VBFHToGG_ext1","2016","VBF",myregion);
    merge_MEM("Oct19v1_MC_2016_VBFHToGG_ext2","2016","VBF",myregion);

    merge_MEM("Oct19v1_MC_2017_VBFHToTauTau","2017","VBF",myregion);
    merge_MEM("Oct19v2_MC_2017_VBF_HToZZTo4L_ext2","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBF_HToZZTo4L_ext1","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBF_HToZZTo4L","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBFHToWWToLNuQQ","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBFHToWWTo2L2Nu","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBFHToMuMu","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBFHToBB","2017","VBF",myregion);
    merge_MEM("Oct19v1_MC_2017_VBFHToGG","2017","VBF",myregion);
    merge_MEM("Oct19v2_MC_2017_VBFHToGG_PS","2017","VBF",myregion);

    merge_MEM("Oct19v1_MC_2018_VBFHToTauTau","2018","VBF",myregion);
    merge_MEM("Oct19v2_MC_2018_VBF_HToZZTo4L","2018","VBF",myregion);
    merge_MEM("Oct19v2_MC_2018_VBFHToWWToLNuQQ","2018","VBF",myregion);
    merge_MEM("Oct19v1_MC_2018_VBFHToWWTo2L2Nu","2018","VBF",myregion);
    merge_MEM("Oct19v1_MC_2018_VBFHToMuMu","2018","VBF",myregion);
    merge_MEM("Oct19v2_MC_2018_VBFHToBB","2018","VBF",myregion);
    merge_MEM("Oct19v2_MC_2018_VBFHToGG","2018","VBF",myregion);

    merge_MEM("Oct19v1_MC_2016_VHToNonbb","2016","VH",myregion);
    merge_MEM("Oct19v1_MC_2016_ZH_HToBB_ZToLL","2016","VH",myregion);
    merge_MEM("Oct19v1_MC_2016_ZHToTauTau","2016","VH",myregion);

    merge_MEM("Oct19v1_MC_2017_VHToNonbb","2017","VH",myregion);
    merge_MEM("Oct19v1_MC_2017_ZH_HToBB_ZToLL","2017","VH",myregion);
    merge_MEM("Oct19v1_MC_2017_ZHToTauTau","2017","VH",myregion);

    merge_MEM("Oct19v2_MC_2018_VHToNonbb","2018","VH",myregion);
    merge_MEM("Oct19v1_MC_2018_ZH_HToBB_ZToLL","2018","VH",myregion);
    merge_MEM("Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1","2018","VH",myregion);
    merge_MEM("Oct19v2_MC_2018_ZHToTauTau","2018","VH",myregion);

    merge_MEM("Oct19v1_MC_2016_TTWH","2016","ttVH",myregion);
    merge_MEM("Oct19v2_MC_2016_TTZH","2016","ttVH",myregion);

    merge_MEM("Oct19v4_MC_2017_TTWH","2017","ttVH",myregion);
    merge_MEM("Oct19v1_MC_2017_TTZH","2017","ttVH",myregion);

    merge_MEM("Oct19v1_MC_2018_TTWH","2018","ttVH",myregion);
    merge_MEM("Oct19v2_MC_2018_TTZH","2018","ttVH",myregion);

    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_box","2016","HH",myregion);
    merge_MEM("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_1","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_2","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_3","2016","HH",myregion);
    merge_MEM("Oct19v4_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_4","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_5","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_6","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_7","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_8","2016","HH",myregion);
    merge_MEM("Oct19v3_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_9","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_10","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_11","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_12","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_box","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_2","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo2B2Tau_node_9","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_10","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_11","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_12","2016","HH",myregion);
    merge_MEM("Oct19v3_MC_2016_GluGluToHHTo2B2Tau_node_13","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_box","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_2","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_3","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_4","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_5","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_6","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_7","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_8","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_9","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_10","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2016_GluGluToHHTo4Tau_node_11","2016","HH",myregion);
    merge_MEM("Oct19v1_MC_2016_GluGluToHHTo4Tau_node_12","2016","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_2","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_3","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_7","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_9","2017","HH",myregion);
    merge_MEM("Oct19v4_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_12","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_2","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_3","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_4","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_7","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_9","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_12","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_2","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_3","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo4Tau_node_7","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_9","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4Tau_node_12","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_2","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_3","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_4","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_5","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_6","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_7","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_8","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_9","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_10","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo2V2Tau_node_11","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_12","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_SM","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo4V_node_2","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_3","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_4","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_5","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_6","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_7","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_8","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_9","2017","HH",myregion);
    merge_MEM("Oct19v1_MC_2017_GluGluToHHTo4V_node_10","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo4V_node_11","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2017_GluGluToHHTo4V_node_12","2017","HH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM","2018","HH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_2","2018","HH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_3","2018","HH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_4","2018","HH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_5","2018","HH",myregion);
    merge_MEM("Oct19v1_MC_2018_GluGluToHHTo2B2Tau_node_6","2018","HH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_7","2018","HH",myregion);
    merge_MEM("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_8","2018","HH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_9","2018","HH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_10","2018","HH",myregion);
    merge_MEM("Oct19v3_MC_2018_GluGluToHHTo2B2Tau_node_11","2018","HH",myregion);
    merge_MEM("Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_12","2018","HH",myregion);*/

    /*merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockB","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockC","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockD","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockE","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockF","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockG","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleElectron_BlockH","2016","Data",myregion);

    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockB","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockC","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockD","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockE","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockF","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockG","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_SingleMuon_BlockH","2016","Data",myregion);

    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockB","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockC","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockD","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockE","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockF","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockG","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleEG_BlockH","2016","Data",myregion);

    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockB","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockC","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockD","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockE","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockF","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockG","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_DoubleMu_BlockH","2016","Data",myregion);

    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockB","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockC","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockD","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockE","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockF","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockG","2016","Data",myregion);
    merge_MEM("Oct19v1_Data_2016_MuonEG_BlockH","2016","Data",myregion);*/

    merge_MEM("Oct19v1_Data_2017_SingleElectron_BlockB","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleElectron_BlockC","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleElectron_BlockD","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleElectron_BlockE","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleElectron_BlockF","2017","Data",myregion);

    /*merge_MEM("Oct19v1_Data_2017_SingleMuon_BlockB","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleMuon_BlockC","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleMuon_BlockD","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleMuon_BlockE","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_SingleMuon_BlockF","2017","Data",myregion);*/

    merge_MEM("Oct19v1_Data_2017_DoubleEG_BlockB","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleEG_BlockC","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleEG_BlockD","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleEG_BlockE","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleEG_BlockF","2017","Data",myregion);

    merge_MEM("Oct19v1_Data_2017_DoubleMu_BlockB","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleMu_BlockC","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleMu_BlockD","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleMu_BlockE","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_DoubleMu_BlockF","2017","Data",myregion);

    merge_MEM("Oct19v1_Data_2017_MuonEG_BlockB","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_MuonEG_BlockC","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_MuonEG_BlockD","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_MuonEG_BlockE","2017","Data",myregion);
    merge_MEM("Oct19v1_Data_2017_MuonEG_BlockF","2017","Data",myregion);

}

