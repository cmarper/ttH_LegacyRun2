#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>

#include "headers/Helpers.C"

////////////////////////////////////////////////////////////

float XS_ttH = 0.2118;
float XS_ttH_ctcvcp = 0.5071; 
float XS_tHQ_ctcvcp = 0.07096; 
float XS_tHW_ctcvcp = 0.01561;

float XS_ttZ = 0.281;
float XS_ttZ_lowmass = 0.0822;
float XS_ttW = 0.1960;
float XS_ttWW = 0.006981;

float XS_WW = 12.2;
float XS_WZ = 4.43;
float XS_ZZ = 1.256;

float XS_DY_M10to50 = 18610;
float XS_DY_M50 = 6077.22;
float XS_WJets = 61526.7;

float XS_WWW = 0.2086;
float XS_WWZ = 0.1676;
float XS_WZZ = 0.05701;
float XS_ZZZ = 0.01473;
float XS_WZG = 0.04345;
float XS_tZq = 0.07358;
float XS_WpWp = 0.04926;
float XS_WW_DS = 0.2232;
float XS_tttt = 0.008213;

float XS_WG = 464.8;
float XS_ZG = 123.9;
float XS_tG = 1.018;
float XS_ttG = 4.215;

float XS_St_schannel = 3.364;
float XS_St_tchannel_top = 136.02;
float XS_St_tchannel_antitop = 80.95;
float XS_St_tW = 35.85;
float XS_St_tWll = 0.01096;

float XS_ttbar_DiLept = 88.40;
float XS_ttbar_SingleLep = 182.76;

float XS_ggHToTauTau = 3.0469;
float XS_ggHToZZ = 0.01297;
float XS_ggHToWWToLNuQQ = 4.5621;
float XS_ggHToWWTo2L2Nu = 1.1033;
float XS_ggHToMuMu = 0.010571;
float XS_ggHToBB = 28.293;
float XS_ggHToGG = 0.11028;

float XS_VBFHToTauTau = 0.2372;
float XS_VBFHToZZ = 0.0010099;
float XS_VBFHToWWToLNuQQ = 0.35517;
float XS_VBFHToWWTo2L2Nu = 0.085894;
float XS_VBFHToMuMu = 0.00082296;
float XS_VBFHToBB = 2.2026;
float XS_VBFHToGG = 0.0085851;

float XS_VHToNonbb = 0.9425;
float XS_ZHToTauTau = 0.05544;
float XS_ZH_HToBB_ZToLL = 0.05198;

float XS_ttWH = 0.001582;
float XS_ttZH = 0.001535;

float XS_ggHHTo2B2VTo2L2Nu = 0.00082039;
float XS_ggHHTo2B2Tau = 0.00226840;
float XS_ggHHTo4Tau = 0.00012214;

////////////////////////////////////////////////////////////

vector<float> 	MC_XS;
vector<TString> MC_filename;
vector<TString> MC_filename_norm;
vector<TString> MC_samplename;
vector<TString> MC_samplecut;
vector<TString> MC_sampletag;
vector<int>		MC_nsamples;
vector<TString> MC_convs_samplecut;

vector<float>	MC_fakeCR_XS;
vector<TString> MC_fakeCR_filename;
vector<TString> MC_fakeCR_filename_norm;

float luminosity;

////////////////////////////////////////////////////////////

TString filename_fakeCR_ttbar_DiLept;
TString filename_fakeCR_ttbar_DiLept_ext1;
TString filename_fakeCR_ttbar_SingleLeptFromt;
TString filename_fakeCR_ttbar_SingleLeptFromt_ext1;
TString filename_fakeCR_ttbar_SingleLeptFromtbar;
TString filename_fakeCR_ttbar_SingleLeptFromtbar_ext1;

TString filename_norm_ttbar_DiLept;
TString filename_norm_ttbar_DiLept_ext1;
TString filename_norm_ttbar_SingleLeptFromt;
TString filename_norm_ttbar_SingleLeptFromt_ext1;
TString filename_norm_ttbar_SingleLeptFromtbar;
TString filename_norm_ttbar_SingleLeptFromtbar_ext1;

////////////////////////////////////////////////////////////

TString chargematch = "(recolep_sel_isGenChargeMatched[0] && recolep_sel_isGenChargeMatched[1])";
TString genmatch = "(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1])";
TString conversmatch = "((recolep_matchedGenPartIdx[0]>=0 && genpart_pdg[recolep_matchedGenPartIdx[0]]==22) || (recolep_matchedGenPartIdx[1]>=0 && genpart_pdg[recolep_matchedGenPartIdx[1]]==22))";

TString hww = "(genH_decayMode[1]>5 && n_genW==4)";
TString hzz = "(genH_decayMode[1]>5 && n_genZ==2)";
TString htt = "(genH_decayMode[1]<=5)";

////////////////////////////////////////////////////////////

std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<float>, vector<TString>, vector<TString>, vector<TString>, float > initialize_2016(){

	MC_XS.clear();

	MC_filename.clear();
	MC_filename_norm.clear();
	MC_samplename.clear();
	MC_samplecut.clear();
	MC_sampletag.clear();
	MC_nsamples.clear();
	MC_convs_samplecut.clear();

	MC_fakeCR_XS.clear();
	MC_fakeCR_filename.clear();
	MC_fakeCR_filename_norm.clear();

	luminosity = 35900;

	////////////////////////////////////////////////////////////
	
	TString filename_ttH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR.root";
	//TString filename_ttH        =   "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_datacards/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR_SFsv1.root";
    TString filename_ttH_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttH_ctcvcp_MEM_SR.root";
	TString filename_tHQ_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_MEM_SR.root";
	TString filename_tHW_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THW_ctcvcp_MEM_SR.root";

	TString filename_ttZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_MEM_SR.root";
	TString filename_ttZ_ext3 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3_MEM_SR.root";
	TString filename_ttZ_lowmass = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLL_M-1to10_MEM_SR.root";
	TString filename_ttW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_MEM_SR.root";
	TString filename_ttWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWW_MEM_SR.root";

	TString filename_WW = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WWTo2L2Nu_MEM_SR.root";
	TString filename_WZ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WZTo3LNu_MEM_SR.root";
	TString filename_ZZ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_ZZTo4L_MEM_SR.root";

	TString filename_DY_M10to50 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-10to50_MEM_SR.root";
	TString filename_DY_M50 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-50_MEM_SR.root";

	TString filename_WJets = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WJetsToLNu_MEM_SR.root";
	TString filename_WJets_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WJetsToLNu_ext2_MEM_SR.root";

	TString filename_WWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWW_MEM_SR.root";
	TString filename_WWZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWZ_MEM_SR.root";
	TString filename_WZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WZZ_MEM_SR.root";
	TString filename_ZZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_ZZZ_MEM_SR.root";
	TString filename_WZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WZG_MEM_SR.root";
	TString filename_WG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext1_MEM_SR.root";
	TString filename_WG_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext2_MEM_SR.root";
	TString filename_WG_ext3 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext3_MEM_SR.root";
	TString filename_ZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_ZGTo2LG_MEM_SR.root";
	TString filename_tG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TGJets_leptonDecays_MEM_SR.root";
	TString filename_ttG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTGJets_MEM_SR.root";
	TString filename_ttG_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTGJets_ext1_MEM_SR.root";
	TString filename_tZq = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v2_MC_2016_tZq_ll_MEM_SR.root";
	TString filename_tZq_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_tZq_ll_PS_MEM_SR.root";
	TString filename_WpWp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WpWpJJ_MEM_SR.root";
	TString filename_WW_DS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering_MEM_SR.root";
	TString filename_tttt = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTTT_MEM_SR.root";

	TString filename_St_schannel = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_s-channel_MEM_SR.root";
	TString filename_St_schannel_PS = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_s-channel_PS_MEM_SR.root";
	TString filename_St_tchannel_top = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_top_MEM_SR.root";
	TString filename_St_tchannel_antitop = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_antitop_MEM_SR.root";
	TString filename_St_tchannel_antitop_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_antitop_PS_MEM_SR.root";
	TString filename_St_tW_top = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tW_top_MEM_SR.root";
	TString filename_St_tW_antitop = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tW_antitop_MEM_SR.root";
	TString filename_St_tWll = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tWll_MEM_SR.root";

	TString filename_ttbar_DiLept = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_MEM_SR.root";
	TString filename_ttbar_DiLept_ext1 = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_ext1_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromt = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromt_ext1 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromtbar = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromtbar_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_MEM_SR.root";

	TString filename_ggHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToTauTau_MEM_SR.root";
	TString filename_ggHToZZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToZZTo4L_MEM_SR.root";
	TString filename_ggHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToWWToLNuQQ_MEM_SR.root";
	TString filename_ggHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToWWTo2L2Nu_MEM_SR.root";
	TString filename_ggHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToMuMu_MEM_SR.root";
	TString filename_ggHToBB = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToBB_MEM_SR.root";
	TString filename_ggHToBB_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v6_MC_2016_GluGluHToBB_ext1_MEM_SR.root";
	TString filename_ggHToGG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToGG_MEM_SR.root";

	TString filename_VBFHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v2_MC_2016_VBFHToTauTau_MEM_SR.root";
	TString filename_VBFHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v2_MC_2016_VBF_HToZZTo4L_MEM_SR.root";
	TString filename_VBFHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToWWToLNuQQ_MEM_SR.root";
	TString filename_VBFHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToWWTo2L2Nu_MEM_SR.root";
	TString filename_VBFHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToMuMu_MEM_SR.root";
	TString filename_VBFHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v3_MC_2016_VBFHToBB_MEM_SR.root";
	TString filename_VBFHToBB_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToBB_ext1_MEM_SR.root";
	TString filename_VBFHToGG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToGG_ext1_MEM_SR.root";
	TString filename_VBFHToGG_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToGG_ext2_MEM_SR.root";

	TString filename_VHToNonbb = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VH/ntuple_Oct19v1_MC_2016_VHToNonbb_MEM_SR.root";
	TString filename_ZHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VH/ntuple_Oct19v1_MC_2016_ZHToTauTau_MEM_SR.root";
	TString filename_ZH_HToBB_ZToLL = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/VH/ntuple_Oct19v1_MC_2016_ZH_HToBB_ZToLL_MEM_SR.root";

	TString filename_ttWH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttVH/ntuple_Oct19v1_MC_2016_TTWH_MEM_SR.root";
	TString filename_ttZH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttVH/ntuple_Oct19v2_MC_2016_TTZH_MEM_SR.root";

	TString filename_ggHHTo2B2VTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/HH/ntuple_Oct19v2_MC_2016_ggHHTo2B2VTo2L2Nu_node_SM_MEM_SR.root";
	TString filename_ggHHTo2B2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/HH/ntuple_Oct19v1_MC_2016_ggHHTo2B2Tau_node_SM_MEM_SR.root";
	TString filename_ggHHTo4Tau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/HH/ntuple_Oct19v1_MC_2016_ggHHTo4Tau_node_SM_MEM_SR.root";

	////////////////////////////////////////////////////////////

	TString filename_fakeCR_ttbar_DiLept = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_MEM_fake.root";
	TString filename_fakeCR_ttbar_DiLept_ext1 = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_ext1_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromt_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromtbar = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromtbar_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2016/nominal/ttbar/ntuple_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_MEM_fake.root";

	////////////////////////////////////////////////////////////

	TString filename_norm_ttH = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_norm.root";
	TString filename_norm_ttH_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttH_ctcvcp_norm.root";
	TString filename_norm_tHQ_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_norm.root";
	TString filename_norm_tHW_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THW_ctcvcp_norm.root";

	TString filename_norm_ttZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_norm.root";
	TString filename_norm_ttZ_ext3 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3_norm.root";
	TString filename_norm_ttZ_lowmass = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLL_M-1to10_norm.root";
	TString filename_norm_ttW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_norm.root";
	TString filename_norm_ttWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWW_norm.root";

	TString filename_norm_WW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WWTo2L2Nu_norm.root";
	TString filename_norm_WZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WZTo3LNu_norm.root";
	TString filename_norm_ZZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_ZZTo4L_norm.root";

	TString filename_norm_DY_M10to50 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-10to50_norm.root";
	TString filename_norm_DY_M50 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_DYJetsToLL_M-50_norm.root";

	TString filename_norm_WJets = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WJetsToLNu_norm.root";
	TString filename_norm_WJets_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WJetsToLNu_ext2_norm.root";

	TString filename_norm_WWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWW_norm.root";
	TString filename_norm_WWZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWZ_norm.root";
	TString filename_norm_WZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WZZ_norm.root";
	TString filename_norm_ZZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_ZZZ_norm.root";
	TString filename_norm_WZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WZG_norm.root";
	TString filename_norm_WG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext1_norm.root";
	TString filename_norm_WG_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext2_norm.root";
	TString filename_norm_WG_ext3 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext3_norm.root";
	TString filename_norm_ZG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_ZGTo2LG_norm.root";
	TString filename_norm_tG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TGJets_leptonDecays_norm.root";
	TString filename_norm_ttG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTGJets_norm.root";
	TString filename_norm_ttG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTGJets_ext1_norm.root";
	TString filename_norm_tZq = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v2_MC_2016_tZq_ll_norm.root";
	TString filename_norm_tZq_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_tZq_ll_PS_norm.root";
	TString filename_norm_WpWp = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WpWpJJ_norm.root";
	TString filename_norm_WW_DS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering_norm.root";
	TString filename_norm_tttt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTTT_norm.root";

	TString filename_norm_St_schannel = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_s-channel_norm.root";
	TString filename_norm_St_schannel_PS = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_s-channel_PS_norm.root";
	TString filename_norm_St_tchannel_top = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_top_norm.root";
	TString filename_norm_St_tchannel_antitop = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_antitop_norm.root";
	TString filename_norm_St_tchannel_antitop_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_antitop_PS_norm.root";
	TString filename_norm_St_tW_top = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tW_top_norm.root";
	TString filename_norm_St_tW_antitop = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tW_antitop_norm.root";
	TString filename_norm_St_tWll = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tWll_norm.root";

	TString filename_norm_ttbar_DiLept = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_norm.root";
	TString filename_norm_ttbar_DiLept_ext1 = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_ext1_norm.root";
	TString filename_norm_ttbar_SingleLeptFromt = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_norm.root";
	TString filename_norm_ttbar_SingleLeptFromt_ext1 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1_norm.root";
	TString filename_norm_ttbar_SingleLeptFromtbar = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_norm.root";
	TString filename_norm_ttbar_SingleLeptFromtbar_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_norm.root";

	TString filename_norm_ggHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToTauTau_norm.root";
	TString filename_norm_ggHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToZZTo4L_norm.root";
	TString filename_norm_ggHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToWWToLNuQQ_norm.root";
	TString filename_norm_ggHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToWWTo2L2Nu_norm.root";
	TString filename_norm_ggHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToMuMu_norm.root";
	TString filename_norm_ggHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToBB_norm.root";
	TString filename_norm_ggHToBB_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v6_MC_2016_GluGluHToBB_ext1_norm.root";
	TString filename_norm_ggHToGG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToGG_norm.root";

	TString filename_norm_VBFHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v2_MC_2016_VBFHToTauTau_norm.root";
	TString filename_norm_VBFHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v2_MC_2016_VBF_HToZZTo4L_norm.root";
	TString filename_norm_VBFHToWWToLNuQQ = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToWWToLNuQQ_norm.root";
	TString filename_norm_VBFHToWWTo2L2Nu = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToWWTo2L2Nu_norm.root";
	TString filename_norm_VBFHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToMuMu_norm.root";
	TString filename_norm_VBFHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v3_MC_2016_VBFHToBB_norm.root";
	TString filename_norm_VBFHToBB_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToBB_ext1_norm.root";
	TString filename_norm_VBFHToGG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToGG_ext1_norm.root";
	TString filename_norm_VBFHToGG_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToGG_ext2_norm.root";

	TString filename_norm_VHToNonbb = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VH/ntuple_Oct19v1_MC_2016_VHToNonbb_norm.root";
	TString filename_norm_ZHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VH/ntuple_Oct19v1_MC_2016_ZHToTauTau_norm.root";
	TString filename_norm_ZH_HToBB_ZToLL = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/VH/ntuple_Oct19v1_MC_2016_ZH_HToBB_ZToLL_norm.root";

	TString filename_norm_ttWH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttVH/ntuple_Oct19v1_MC_2016_TTWH_norm.root";
	TString filename_norm_ttZH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttVH/ntuple_Oct19v2_MC_2016_TTZH_norm.root";

	TString filename_norm_ggHHTo2B2VTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/HH/ntuple_Oct19v2_MC_2016_ggHHTo2B2VTo2L2Nu_node_SM_norm.root";
	TString filename_norm_ggHHTo2B2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/HH/ntuple_Oct19v1_MC_2016_ggHHTo2B2Tau_node_SM_norm.root";
	TString filename_norm_ggHHTo4Tau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/HH/ntuple_Oct19v1_MC_2016_ggHHTo4Tau_node_SM_norm.root";

	///////////////////////////////////////////////////////

	TString filename_fakeCR_norm_ttbar_DiLept = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_norm.root";
	TString filename_fakeCR_norm_ttbar_DiLept_ext1 = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_ext1_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromt = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromt_ext1 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromtbar = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromtbar_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/ttbar/ntuple_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_norm.root";

	///////////////////////////////////////////////////////

	// ttH

	/*MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttH_s1");
	MC_sampletag.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	*/

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhww_s1");
	MC_sampletag.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhzz_s1");
	MC_sampletag.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhtt_s1");
	MC_sampletag.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// MISSING:
	// - ttHhzg
	// - ttHhmm

	/*MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttH_s2");
	MC_sampletag.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhww_s2");
	MC_sampletag.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhzz_s2");
	MC_sampletag.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhtt_s2");
	MC_sampletag.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);*/

	// MISSING:
	// - ttHhzg
	// - ttHhmm

	///////////////////////////////////////////////////////

	// tHQ

	/*MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQ_s1");
	MC_sampletag.push_back("tHQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhww_s1");
	MC_sampletag.push_back("tHQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhzz_s1");
	MC_sampletag.push_back("tHQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhtt_s1");
	MC_sampletag.push_back("tHQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// tHW

	/*MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHW_s1");
	MC_sampletag.push_back("tHW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhww_s1");
	MC_sampletag.push_back("tHWhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhzz_s1");
	MC_sampletag.push_back("tHWhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhtt_s1");
	MC_sampletag.push_back("tHWhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// VHToNonbb

	/*MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbb_s1");
	MC_sampletag.push_back("VHToNonbb");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhww_s1");
	MC_sampletag.push_back("VHToNonbbhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhzz_s1");
	MC_sampletag.push_back("VHToNonbbhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhtt_s1");
	MC_sampletag.push_back("VHToNonbbhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ZHToTauTau

	/*MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTau_s1");
	MC_sampletag.push_back("ZHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhww_s1");
	MC_sampletag.push_back("ZHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhzz_s1");
	MC_sampletag.push_back("ZHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhtt_s1");
	MC_sampletag.push_back("ZHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// HToBBZToLLhww

	/*MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLL_s1");
	MC_sampletag.push_back("HToBBZToLL");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhww_s1");
	MC_sampletag.push_back("HToBBZToLLhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhzz_s1");
	MC_sampletag.push_back("HToBBZToLLhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhtt_s1");
	MC_sampletag.push_back("HToBBZToLLhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ttWH

	/*MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWH_s1");
	MC_sampletag.push_back("ttWH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhww_s1");
	MC_sampletag.push_back("ttWHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhzz_s1");
	MC_sampletag.push_back("ttWHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhtt_s1");
	MC_sampletag.push_back("ttWHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ttZH

	/*MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZH_s1");
	MC_sampletag.push_back("ttZH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhww_s1");
	MC_sampletag.push_back("ttZHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhzz_s1");
	MC_sampletag.push_back("ttZHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhtt_s1");
	MC_sampletag.push_back("ttZHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ggHToTauTau

	/*MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTau_s1");
	MC_sampletag.push_back("ggHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhww_s1");
	MC_sampletag.push_back("ggHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhzz_s1");
	MC_sampletag.push_back("ggHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhtt_s1");
	MC_sampletag.push_back("ggHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToZZ

	/*MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ);
	MC_filename_norm.push_back(filename_norm_ggHToZZ);
	MC_samplename.push_back("ggHToZZ_s1");
	MC_sampletag.push_back("ggHToZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ);
	MC_filename_norm.push_back(filename_norm_ggHToZZ);
	MC_samplename.push_back("ggHToZZhww_s1");
	MC_sampletag.push_back("ggHToZZhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ);
	MC_filename_norm.push_back(filename_norm_ggHToZZ);
	MC_samplename.push_back("ggHToZZhzz_s1");
	MC_sampletag.push_back("ggHToZZhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ);
	MC_filename_norm.push_back(filename_norm_ggHToZZ);
	MC_samplename.push_back("ggHToZZhtt_s1");
	MC_sampletag.push_back("ggHToZZhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToWWToLNuQQ

	/*MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQ_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhww_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhzz_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhtt_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToWWTo2L2Nu

	/*MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhww_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhzz_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhtt_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToMuMu

	/*MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMu_s1");
	MC_sampletag.push_back("ggHToMuMu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhww_s1");
	MC_sampletag.push_back("ggHToMuMuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhzz_s1");
	MC_sampletag.push_back("ggHToMuMuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhtt_s1");
	MC_sampletag.push_back("ggHToMuMuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToBB

	/*MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBB_s1");
	MC_sampletag.push_back("ggHToBB");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhww_s1");
	MC_sampletag.push_back("ggHToBBhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhzz_s1");
	MC_sampletag.push_back("ggHToBBhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhtt_s1");
	MC_sampletag.push_back("ggHToBBhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToGG

	/*MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGG_s1");
	MC_sampletag.push_back("ggHToGG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhww_s1");
	MC_sampletag.push_back("ggHToGGhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhzz_s1");
	MC_sampletag.push_back("ggHToGGhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhtt_s1");
	MC_sampletag.push_back("ggHToGGhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// VBFHToTauTau

	/*MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTau_s1");
	MC_sampletag.push_back("VBFHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhww_s1");
	MC_sampletag.push_back("VBFHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhzz_s1");
	MC_sampletag.push_back("VBFHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhtt_s1");
	MC_sampletag.push_back("VBFHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToZZ

	/*MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZ_s1");
	MC_sampletag.push_back("VBFHToZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhww_s1");
	MC_sampletag.push_back("VBFHToZZhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhzz_s1");
	MC_sampletag.push_back("VBFHToZZhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhtt_s1");
	MC_sampletag.push_back("VBFHToZZhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToWWToLNuQQ

	/*MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQ_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhww_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhzz_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhtt_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToWWTo2L2Nu

	/*MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhww_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhzz_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhtt_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToMuMu

	/*MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMu_s1");
	MC_sampletag.push_back("VBFHToMuMu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhww_s1");
	MC_sampletag.push_back("VBFHToMuMuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhzz_s1");
	MC_sampletag.push_back("VBFHToMuMuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhtt_s1");
	MC_sampletag.push_back("VBFHToMuMuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToBB

	/*MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBB_s1");
	MC_sampletag.push_back("VBFHToBB");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhww_s1");
	MC_sampletag.push_back("VBFHToBBhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhzz_s1");
	MC_sampletag.push_back("VBFHToBBhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhtt_s1");
	MC_sampletag.push_back("VBFHToBBhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToGG

	/*MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG_ext1);
	MC_filename_norm.push_back(filename_norm_VBFHToGG_ext1);
	MC_samplename.push_back("VBFHToGG_s1");
	MC_sampletag.push_back("VBFHToGG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG_ext1);
	MC_filename_norm.push_back(filename_norm_VBFHToGG_ext1);
	MC_samplename.push_back("VBFHToGGhww_s1");
	MC_sampletag.push_back("VBFHToGGhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG_ext1);
	MC_filename_norm.push_back(filename_norm_VBFHToGG_ext1);
	MC_samplename.push_back("VBFHToGGhzz_s1");
	MC_sampletag.push_back("VBFHToGGhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG_ext1);
	MC_filename_norm.push_back(filename_norm_VBFHToGG_ext1);
	MC_samplename.push_back("VBFHToGGhtt_s1");
	MC_sampletag.push_back("VBFHToGGhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ttZ

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ_ext2); 
	MC_filename_norm.push_back(filename_norm_ttZ_ext2);
	MC_samplename.push_back("ttZ_s1");
	MC_sampletag.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ_ext3); 
	MC_filename_norm.push_back(filename_norm_ttZ_ext3);
	MC_samplename.push_back("ttZ_s2");
	MC_sampletag.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ_lowmass);
	MC_filename.push_back(filename_ttZ_lowmass);
	MC_filename_norm.push_back(filename_norm_ttZ_lowmass);
	MC_samplename.push_back("ttZm1to10_s1");
	MC_sampletag.push_back("ttZm1to10");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttW

	MC_XS.push_back(XS_ttW);
	MC_filename.push_back(filename_ttW);
	MC_filename_norm.push_back(filename_norm_ttW);
	MC_samplename.push_back("ttW_s1");
	MC_sampletag.push_back("ttW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttWW

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW);
	MC_filename_norm.push_back(filename_norm_ttWW);
	MC_samplename.push_back("ttWW_s1");
	MC_sampletag.push_back("ttWW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// WW

	/*MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW);
	MC_filename_norm.push_back(filename_norm_WW);
	MC_samplename.push_back("WW_s1");
	MC_sampletag.push_back("WW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// WZ

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ);
	MC_filename_norm.push_back(filename_norm_WZ);
	MC_samplename.push_back("WZ_s1");
	MC_sampletag.push_back("WZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ZZ

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ);
	MC_filename_norm.push_back(filename_norm_ZZ);
	MC_samplename.push_back("ZZ_s1");
	MC_sampletag.push_back("ZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// DY

	/*MC_XS.push_back(XS_DY_M10to50);
	MC_filename.push_back(filename_DY_M10to50);
	MC_filename_norm.push_back(filename_norm_DY_M10to50);
	MC_samplename.push_back("DYm10to50_s1");
	MC_sampletag.push_back("DYm10to50");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_DY_M50);
	MC_filename.push_back(filename_DY_M50);
	MC_filename_norm.push_back(filename_norm_DY_M50);
	MC_samplename.push_back("DYm50_s1");
	MC_sampletag.push_back("DYm50");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// WJets

	/*MC_XS.push_back(XS_WJets);
	MC_filename.push_back(filename_WJets);
	MC_filename_norm.push_back(filename_norm_WJets);
	MC_samplename.push_back("WJets_s1");
	MC_sampletag.push_back("WJets");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WJets);
	MC_filename.push_back(filename_WJets_ext2);
	MC_filename_norm.push_back(filename_norm_WJets_ext2);
	MC_samplename.push_back("WJets_s2");
	MC_sampletag.push_back("WJets");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// Rares

	MC_XS.push_back(XS_WWW);
	MC_filename.push_back(filename_WWW);
	MC_filename_norm.push_back(filename_norm_WWW);
	MC_samplename.push_back("WWW_s1");
	MC_sampletag.push_back("WWW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WWZ);
	MC_filename.push_back(filename_WWZ);
	MC_filename_norm.push_back(filename_norm_WWZ);
	MC_samplename.push_back("WWZ_s1");
	MC_sampletag.push_back("WWZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZZ);
	MC_filename.push_back(filename_WZZ);
	MC_filename_norm.push_back(filename_norm_WZZ);
	MC_samplename.push_back("WZZ_s1");
	MC_sampletag.push_back("WZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZZ);
	MC_filename.push_back(filename_ZZZ);
	MC_filename_norm.push_back(filename_norm_ZZZ);
	MC_samplename.push_back("ZZZ_s1");
	MC_sampletag.push_back("ZZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZG);
	MC_filename.push_back(filename_WZG);
	MC_filename_norm.push_back(filename_norm_WZG);
	MC_samplename.push_back("WZG_s1");
	MC_sampletag.push_back("WZG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG_ext1);
	MC_filename_norm.push_back(filename_norm_WG_ext1);
	MC_samplename.push_back("WG_s1");
	MC_sampletag.push_back("WG");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG_ext2);
	MC_filename_norm.push_back(filename_norm_WG_ext2);
	MC_samplename.push_back("WG_s2");
	MC_sampletag.push_back("WG");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG_ext3);
	MC_filename_norm.push_back(filename_norm_WG_ext3);
	MC_samplename.push_back("WG_s3");
	MC_sampletag.push_back("WG");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZG);
	MC_filename.push_back(filename_ZG);
	MC_filename_norm.push_back(filename_norm_ZG);
	MC_samplename.push_back("ZG_s1");
	MC_sampletag.push_back("ZG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tG);
	MC_filename.push_back(filename_tG);
	MC_filename_norm.push_back(filename_norm_tG);
	MC_samplename.push_back("tG_s1");
	MC_sampletag.push_back("tG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG);
	MC_filename_norm.push_back(filename_norm_ttG);
	MC_samplename.push_back("ttG_s1");
	MC_sampletag.push_back("ttG");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG_ext1);
	MC_filename_norm.push_back(filename_norm_ttG_ext1);
	MC_samplename.push_back("ttG_s2");
	MC_sampletag.push_back("ttG");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq); 
	MC_filename_norm.push_back(filename_norm_tZq);
	MC_samplename.push_back("tZq_s1");
	MC_sampletag.push_back("tZq");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq_PS); 
	MC_filename_norm.push_back(filename_norm_tZq_PS);
	MC_samplename.push_back("tZq_s2");
	MC_sampletag.push_back("tZq");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WpWp);
	MC_filename.push_back(filename_WpWp); 
	MC_filename_norm.push_back(filename_norm_WpWp);
	MC_samplename.push_back("WpWp_s1");
	MC_sampletag.push_back("WpWp");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW_DS);
	MC_filename.push_back(filename_WW_DS); 
	MC_filename_norm.push_back(filename_norm_WW_DS);
	MC_samplename.push_back("WWss_s1");
	MC_sampletag.push_back("WWss");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt); 
	MC_filename_norm.push_back(filename_norm_tttt);
	MC_samplename.push_back("tttt_s1");
	MC_sampletag.push_back("tttt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel); 
	MC_filename_norm.push_back(filename_norm_St_schannel);
	MC_samplename.push_back("TsCh_s1");
	MC_sampletag.push_back("TsCh");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel_PS); 
	MC_filename_norm.push_back(filename_norm_St_schannel_PS);
	MC_samplename.push_back("TsCh_s2");
	MC_sampletag.push_back("TsCh");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top);
	MC_samplename.push_back("TtChTop_s1");
	MC_sampletag.push_back("TtChTop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop);
	MC_samplename.push_back("TtChAntitop_s1");
	MC_sampletag.push_back("TtChAntitop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop_PS); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop_PS);
	MC_samplename.push_back("TtChAntitop_s2");
	MC_sampletag.push_back("TtChAntitop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top); 
	MC_filename_norm.push_back(filename_norm_St_tW_top);
	MC_samplename.push_back("TtwChTop_s1");
	MC_sampletag.push_back("TtwChTop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop);
	MC_samplename.push_back("TtwChAntitop_s1");
	MC_sampletag.push_back("TtwChAntitop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tWll);
	MC_filename.push_back(filename_St_tWll); 
	MC_filename_norm.push_back(filename_norm_St_tWll);
	MC_samplename.push_back("TtwChll_s1");
	MC_sampletag.push_back("TtwChll");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_samplename.push_back("ttbarDL_s1");
	MC_sampletag.push_back("ttbarDL");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_DiLept); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_DiLept); 
	MC_fakeCR_XS.push_back(XS_ttbar_DiLept);

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept_ext1); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept_ext1);
	MC_samplename.push_back("ttbarDL_s2");
	MC_sampletag.push_back("ttbarDL");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	//MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_DiLept_ext1); 
	//MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_DiLept_ext1); 
	//MC_fakeCR_XS.push_back(XS_ttbar_DiLept);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt);
	MC_samplename.push_back("ttbarSLfromT_s1");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromt); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt); 
	MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt_ext1); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt_ext1);
	MC_samplename.push_back("ttbarSLfromT_s2");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	//MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromt_ext1); 
	//MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt_ext1); 
	//MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar);
	MC_samplename.push_back("ttbarSLfromTbar_s1");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromtbar); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar); 
	MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar_ext1); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar_ext1);
	MC_samplename.push_back("ttbarSLfromTbar_s2");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	//MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromtbar_ext1); 
	//MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar_ext1); 
	//MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	///////////////////////////////////////////////////////

	return std::make_tuple(MC_XS, MC_filename, MC_filename_norm, MC_samplename, MC_samplecut, MC_sampletag, MC_nsamples, MC_fakeCR_XS, MC_fakeCR_filename, MC_fakeCR_filename_norm, MC_convs_samplecut, luminosity);

}

std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<float>, vector<TString>, vector<TString>, vector<TString>, float > initialize_2017(){

	MC_XS.clear();

	MC_filename.clear();
	MC_filename_norm.clear();
	MC_samplename.clear();
	MC_samplecut.clear();
	MC_sampletag.clear();
	MC_nsamples.clear();
	MC_convs_samplecut.clear();

	MC_fakeCR_XS.clear();
	MC_fakeCR_filename.clear();
	MC_fakeCR_filename_norm.clear();

	luminosity = 41400;

	////////////////////////////////////////////////////////////

	TString filename_ttH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR.root";
	//TString filename_ttH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_datacards/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR_SFsv1.root";
	TString filename_ttH_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_TTH_ctcvcp_MEM_SR.root";
	TString filename_tHQ_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_MEM_SR.root";
	TString filename_tHW_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttH/ntuple_Oct19v3_MC_2017_THW_ctcvcp_MEM_SR.root";

	TString filename_ttZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_MEM_SR.root";
	TString filename_ttZ_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS_MEM_SR.root";
	TString filename_ttZ_lowmass = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLL_M-1to10_MEM_SR.root";
	TString filename_ttW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_MEM_SR.root";
	TString filename_ttW_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_PS_MEM_SR.root";
	TString filename_ttWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWW_MEM_SR.root";

	TString filename_WW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_WWTo2L2Nu_MEM_SR.root";
	TString filename_WW_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_ext1_MEM_SR.root";
	TString filename_WZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WZTo3LNu_MEM_SR.root";
	TString filename_ZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_MEM_SR.root";
	TString filename_ZZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_ext1_MEM_SR.root";
	TString filename_ZZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_ZZTo4L_ext2_MEM_SR.root";

	TString filename_DY_M10to50 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-10to50_MEM_SR.root";
	TString filename_DY_M10to50_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1_MEM_SR.root";
	TString filename_DY_M50 = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-50_MEM_SR.root";
	TString filename_DY_M50_ext1 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v3_MC_2017_DYJetsToLL_M-50_ext1_MEM_SR.root";

	TString filename_WJets = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_WJetsToLNu_MEM_SR.root";
	TString filename_WJets_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WJetsToLNu_ext1_MEM_SR.root";

	TString filename_WWW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWW_MEM_SR.root";
	TString filename_WWZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWZ_MEM_SR.root";
	TString filename_WZZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_WZZ_MEM_SR.root";
	TString filename_ZZZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_ZZZ_MEM_SR.root";
	TString filename_WZG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WZG_MEM_SR.root";
	TString filename_WG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WGToLNuG_MEM_SR.root";
	TString filename_ZG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_ZGToLLG_MEM_SR.root";
	TString filename_tG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TGJets_MEM_SR.root";
	TString filename_ttG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTGJets_MEM_SR.root";
	TString filename_ttG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTGJets_ext1_MEM_SR.root";
	TString filename_tZq = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_tZq_ll_MEM_SR.root";
	TString filename_WpWp = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_WpWpJJ_MEM_SR.root";
	TString filename_WW_DS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering_MEM_SR.root";
	TString filename_tttt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTTT_MEM_SR.root";
	TString filename_tttt_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTTT_PS_MEM_SR.root";

	TString filename_St_schannel = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_s-channel_MEM_SR.root";
	TString filename_St_schannel_PS = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_s-channel_PS_MEM_SR.root";
	TString filename_St_tchannel_top = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_t-channel_top_MEM_SR.root";
	TString filename_St_tchannel_top_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_t-channel_top_PS_MEM_SR.root";
	TString filename_St_tchannel_antitop = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_t-channel_antitop_MEM_SR.root";
	TString filename_St_tchannel_antitop_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_t-channel_antitop_PS_MEM_SR.root";
	TString filename_St_tW_top = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v3_MC_2017_ST_tW_top_MEM_SR.root";
	TString filename_St_tW_top_PS = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_top_PS_MEM_SR.root";
	TString filename_St_tW_antitop = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_antitop_MEM_SR.root";
	TString filename_St_tW_antitop_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_antitop_PS_MEM_SR.root";
	TString filename_St_tWll = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tWll_MEM_SR.root";

	TString filename_ttbar_DiLept = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromtbar = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_MEM_SR.root";

	TString filename_ggHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToTauTau_MEM_SR.root";
	TString filename_ggHToTauTau_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToTauTau_ext1_MEM_SR.root";
	TString filename_ggHToZZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToZZTo4L_ext1_MEM_SR.root";
	TString filename_ggHToZZ_ext3 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToZZTo4L_ext3_MEM_SR.root";
	TString filename_ggHToZZ_ext4 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToZZTo4L_ext4_MEM_SR.root";
	TString filename_ggHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToWWToLNuQQ_MEM_SR.root";
	TString filename_ggHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToWWTo2L2Nu_MEM_SR.root";
	TString filename_ggHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToMuMu_MEM_SR.root";
	TString filename_ggHToMuMu_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToMuMu_ext1_MEM_SR.root";
	TString filename_ggHToBB = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToBB_MEM_SR.root";
	TString filename_ggHToGG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToGG_MEM_SR.root";

	TString filename_VBFHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToTauTau_MEM_SR.root";
	TString filename_VBFHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBF_HToZZTo4L_MEM_SR.root";
	TString filename_VBFHToZZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBF_HToZZTo4L_ext1_MEM_SR.root";
	TString filename_VBFHToZZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v2_MC_2017_VBF_HToZZTo4L_ext2_MEM_SR.root";
	TString filename_VBFHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToWWToLNuQQ_MEM_SR.root";
	TString filename_VBFHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToWWTo2L2Nu_MEM_SR.root";
	TString filename_VBFHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToMuMu_MEM_SR.root";
	TString filename_VBFHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToBB_MEM_SR.root";
	TString filename_VBFHToGG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToGG_MEM_SR.root";
	TString filename_VBFHToGG_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VBF/ntuple_Oct19v2_MC_2017_VBFHToGG_PS_MEM_SR.root";

	TString filename_VHToNonbb = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VH/ntuple_Oct19v1_MC_2017_VHToNonbb_MEM_SR.root";
	TString filename_ZHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VH/ntuple_Oct19v1_MC_2017_ZHToTauTau_MEM_SR.root";
	TString filename_ZH_HToBB_ZToLL = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/VH/ntuple_Oct19v1_MC_2017_ZH_HToBB_ZToLL_MEM_SR.root";

	TString filename_ttWH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttVH/ntuple_Oct19v4_MC_2017_TTWH_MEM_SR.root";
	TString filename_ttZH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttVH/ntuple_Oct19v1_MC_2017_TTZH_MEM_SR.root";

	TString filename_ggHHTo2B2VTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM_MEM_SR.root";
	TString filename_ggHHTo2B2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM_MEM_SR.root";
	TString filename_ggHHTo4Tau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13_MEM_SR.root";
	TString filename_ggHHTo2V2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM_MEM_SR.root";
	TString filename_ggHHTo4V = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4V_node_SM_MEM_SR.root";

	////////////////////////////////////////////////////////////

	TString filename_fakeCR_ttbar_DiLept = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromt = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromtbar = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_MEM_fake.root";

	////////////////////////////////////////////////////////////

	TString filename_norm_ttH = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_norm.root";
	TString filename_norm_ttH_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_TTH_ctcvcp_norm.root";
	TString filename_norm_tHQ_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_norm.root";
	TString filename_norm_tHW_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttH/ntuple_Oct19v3_MC_2017_THW_ctcvcp_norm.root";

	TString filename_norm_ttZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_norm.root";
	TString filename_norm_ttZ_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS_norm.root";
	TString filename_norm_ttZ_lowmass = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLL_M-1to10_norm.root";
	TString filename_norm_ttW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_norm.root";
	TString filename_norm_ttW_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_PS_norm.root";
	TString filename_norm_ttWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWW_norm.root";

	TString filename_norm_WW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_WWTo2L2Nu_norm.root";
	TString filename_norm_WW_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_ext1_norm.root";
	TString filename_norm_WZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WZTo3LNu_norm.root";
	TString filename_norm_ZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_norm.root";
	TString filename_norm_ZZ_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_ext1_norm.root";
	TString filename_norm_ZZ_ext2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_ZZTo4L_ext2_norm.root";

	TString filename_norm_DY_M10to50 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-10to50_norm.root";
	TString filename_norm_DY_M10to50_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-10to50_ext1_norm.root";
	TString filename_norm_DY_M50 = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_DYJetsToLL_M-50_norm.root";
	TString filename_norm_DY_M50_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v3_MC_2017_DYJetsToLL_M-50_ext1_norm.root";

	TString filename_norm_WJets = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_WJetsToLNu_norm.root";
	TString filename_norm_WJets_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WJetsToLNu_ext1_norm.root";

	TString filename_norm_WWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWW_norm.root";
	TString filename_norm_WWZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWZ_norm.root";
	TString filename_norm_WZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_WZZ_norm.root";
	TString filename_norm_ZZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_ZZZ_norm.root";
	TString filename_norm_WZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WZG_norm.root";
	TString filename_norm_WG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WGToLNuG_norm.root";
	TString filename_norm_ZG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_ZGToLLG_norm.root";
	TString filename_norm_tG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TGJets_norm.root";
	TString filename_norm_ttG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTGJets_norm.root";
	TString filename_norm_ttG_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTGJets_ext1_norm.root";
	TString filename_norm_tZq = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_tZq_ll_norm.root";
	TString filename_norm_WpWp = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_WpWpJJ_norm.root";
	TString filename_norm_WW_DS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering_norm.root";
	TString filename_norm_tttt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTTT_norm.root";
	TString filename_norm_tttt_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTTT_PS_norm.root";

	TString filename_norm_St_schannel = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_s-channel_norm.root";
	TString filename_norm_St_schannel_PS = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_s-channel_PS_norm.root";
	TString filename_norm_St_tchannel_top = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_t-channel_top_norm.root";
	TString filename_norm_St_tchannel_top_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_t-channel_top_PS_norm.root";
	TString filename_norm_St_tchannel_antitop = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_t-channel_antitop_norm.root";
	TString filename_norm_St_tchannel_antitop_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_t-channel_antitop_PS_norm.root";
	TString filename_norm_St_tW_top = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v3_MC_2017_ST_tW_top_norm.root";
	TString filename_norm_St_tW_top_PS = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_top_PS_norm.root";
	TString filename_norm_St_tW_antitop = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_antitop_norm.root";
	TString filename_norm_St_tW_antitop_PS = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_antitop_PS_norm.root";
	TString filename_norm_St_tWll = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tWll_norm.root";

	TString filename_norm_ttbar_DiLept = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_norm.root";
	TString filename_norm_ttbar_SingleLeptFromt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_norm.root";
	TString filename_norm_ttbar_SingleLeptFromtbar = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_norm.root";

	TString filename_norm_ggHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToTauTau_norm.root";
	TString filename_norm_ggHToTauTau_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToTauTau_ext1_norm.root";
	TString filename_norm_ggHToZZ_ext1 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToZZTo4L_ext1_norm.root";
	TString filename_norm_ggHToZZ_ext3 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToZZTo4L_ext3_norm.root";
	TString filename_norm_ggHToZZ_ext4 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToZZTo4L_ext4_norm.root";
	TString filename_norm_ggHToWWToLNuQQ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToWWToLNuQQ_norm.root";
	TString filename_norm_ggHToWWTo2L2Nu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToWWTo2L2Nu_norm.root";
	TString filename_norm_ggHToMuMu = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToMuMu_norm.root";
	TString filename_norm_ggHToMuMu_ext1 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToMuMu_ext1_norm.root";
	TString filename_norm_ggHToBB = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToBB_norm.root";
	TString filename_norm_ggHToGG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToGG_norm.root";

	TString filename_norm_VBFHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToTauTau_norm.root";
	TString filename_norm_VBFHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBF_HToZZTo4L_norm.root";
	TString filename_norm_VBFHToZZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBF_HToZZTo4L_ext1_norm.root";
	TString filename_norm_VBFHToZZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v2_MC_2017_VBF_HToZZTo4L_ext2_norm.root";
	TString filename_norm_VBFHToWWToLNuQQ = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToWWToLNuQQ_norm.root";
	TString filename_norm_VBFHToWWTo2L2Nu = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToWWTo2L2Nu_norm.root";
	TString filename_norm_VBFHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToMuMu_norm.root";
	TString filename_norm_VBFHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToBB_norm.root";
	TString filename_norm_VBFHToGG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToGG_norm.root";
	TString filename_norm_VBFHToGG_PS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VBF/ntuple_Oct19v2_MC_2017_VBFHToGG_PS_norm.root";

	TString filename_norm_VHToNonbb = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VH/ntuple_Oct19v1_MC_2017_VHToNonbb_norm.root";
	TString filename_norm_ZHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VH/ntuple_Oct19v1_MC_2017_ZHToTauTau_norm.root";
	TString filename_norm_ZH_HToBB_ZToLL = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/VH/ntuple_Oct19v1_MC_2017_ZH_HToBB_ZToLL_norm.root";
	
	TString filename_norm_ttWH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttVH/ntuple_Oct19v4_MC_2017_TTWH_norm.root";
	TString filename_norm_ttZH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttVH/ntuple_Oct19v1_MC_2017_TTZH_norm.root";

	TString filename_norm_ggHHTo2B2VTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM_norm.root";
	TString filename_norm_ggHHTo2B2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM_norm.root";
	TString filename_norm_ggHHTo4Tau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13_norm.root";
	TString filename_norm_ggHHTo2V2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM_norm.root";
	TString filename_norm_ggHHTo4V = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4V_node_SM_norm.root";

	///////////////////////////////////////////////////////

	TString filename_fakeCR_norm_ttbar_DiLept = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromtbar = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_norm.root";

	///////////////////////////////////////////////////////

	// ttH

	/*MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttH_s1");
	MC_sampletag.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhww_s1");
	MC_sampletag.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhzz_s1");
	MC_sampletag.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhtt_s1");
	MC_sampletag.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// MISSING:
	// - ttHhzg
	// - ttHhmm

	/*MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttH_s2");
	MC_sampletag.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhww_s2");
	MC_sampletag.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhzz_s2");
	MC_sampletag.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhtt_s2");
	MC_sampletag.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);*/

	// MISSING:
	// - ttHhzg
	// - ttHhmm

	///////////////////////////////////////////////////////

	// tHQ

	/*MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQ_s1");
	MC_sampletag.push_back("tHQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhww_s1");
	MC_sampletag.push_back("tHQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhzz_s1");
	MC_sampletag.push_back("tHQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhtt_s1");
	MC_sampletag.push_back("tHQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// tHW

	/*MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHW_s1");
	MC_sampletag.push_back("tHW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhww_s1");
	MC_sampletag.push_back("tHWhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhzz_s1");
	MC_sampletag.push_back("tHWhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhtt_s1");
	MC_sampletag.push_back("tHWhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// VHToNonbb

	/*MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbb_s1");
	MC_sampletag.push_back("VHToNonbb");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhww_s1");
	MC_sampletag.push_back("VHToNonbbhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhzz_s1");
	MC_sampletag.push_back("VHToNonbbhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhtt_s1");
	MC_sampletag.push_back("VHToNonbbhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ZHToTauTau

	/*MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTau_s1");
	MC_sampletag.push_back("ZHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhww_s1");
	MC_sampletag.push_back("ZHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhzz_s1");
	MC_sampletag.push_back("ZHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhtt_s1");
	MC_sampletag.push_back("ZHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ZH_HToBB_ZToLL

	/*MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLL_s1");
	MC_sampletag.push_back("HToBBZToLL");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhww_s1");
	MC_sampletag.push_back("HToBBZToLLhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhzz_s1");
	MC_sampletag.push_back("HToBBZToLLhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhtt_s1");
	MC_sampletag.push_back("HToBBZToLLhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ttWH

	/*MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWH_s1");
	MC_sampletag.push_back("ttWH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhww_s1");
	MC_sampletag.push_back("ttWHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhzz_s1");
	MC_sampletag.push_back("ttWHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhtt_s1");
	MC_sampletag.push_back("ttWHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ttZH

	/*MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZH_s1");
	MC_sampletag.push_back("ttZH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhww_s1");
	MC_sampletag.push_back("ttZHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhzz_s1");
	MC_sampletag.push_back("ttZHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhtt_s1");
	MC_sampletag.push_back("ttZHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ggHToTauTau

	/*MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTau_s1");
	MC_sampletag.push_back("ggHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhww_s1");
	MC_sampletag.push_back("ggHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhzz_s1");
	MC_sampletag.push_back("ggHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhtt_s1");
	MC_sampletag.push_back("ggHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToZZ

	/*MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ggHToZZ_ext1);
	MC_samplename.push_back("ggHToZZ_s1");
	MC_sampletag.push_back("ggHToZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ggHToZZ_ext1);
	MC_samplename.push_back("ggHToZZhww_s1");
	MC_sampletag.push_back("ggHToZZhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ggHToZZ_ext1);
	MC_samplename.push_back("ggHToZZhzz_s1");
	MC_sampletag.push_back("ggHToZZhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ggHToZZ_ext1);
	MC_samplename.push_back("ggHToZZhtt_s1");
	MC_sampletag.push_back("ggHToZZhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToWWToLNuQQ

	/*MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQ_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhww_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhzz_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhtt_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToWWTo2L2Nu

	/*MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhww_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhzz_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhtt_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToMuMu

	/*MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMu_s1");
	MC_sampletag.push_back("ggHToMuMu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhww_s1");
	MC_sampletag.push_back("ggHToMuMuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhzz_s1");
	MC_sampletag.push_back("ggHToMuMuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhtt_s1");
	MC_sampletag.push_back("ggHToMuMuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToBB

	/*MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBB_s1");
	MC_sampletag.push_back("ggHToBB");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhww_s1");
	MC_sampletag.push_back("ggHToBBhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhzz_s1");
	MC_sampletag.push_back("ggHToBBhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhtt_s1");
	MC_sampletag.push_back("ggHToBBhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToGG

	/*MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGG_s1");
	MC_sampletag.push_back("ggHToGG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhww_s1");
	MC_sampletag.push_back("ggHToGGhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhzz_s1");
	MC_sampletag.push_back("ggHToGGhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhtt_s1");
	MC_sampletag.push_back("ggHToGGhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// VBFHToTauTau

	/*MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTau_s1");
	MC_sampletag.push_back("VBFHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhww_s1");
	MC_sampletag.push_back("VBFHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhzz_s1");
	MC_sampletag.push_back("VBFHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhtt_s1");
	MC_sampletag.push_back("VBFHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToZZ

	/*MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZ_s1");
	MC_sampletag.push_back("VBFHToZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhww_s1");
	MC_sampletag.push_back("VBFHToZZhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhzz_s1");
	MC_sampletag.push_back("VBFHToZZhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhtt_s1");
	MC_sampletag.push_back("VBFHToZZhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToWWToLNuQQ

	/*MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQ_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhww_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhzz_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhtt_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToWWTo2L2Nu

	/*MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhww_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhzz_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhtt_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToMuMu

	/*MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMu_s1");
	MC_sampletag.push_back("VBFHToMuMu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhww_s1");
	MC_sampletag.push_back("VBFHToMuMuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhzz_s1");
	MC_sampletag.push_back("VBFHToMuMuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhtt_s1");
	MC_sampletag.push_back("VBFHToMuMuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToBB

	/*MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBB_s1");
	MC_sampletag.push_back("VBFHToBB");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhww_s1");
	MC_sampletag.push_back("VBFHToBBhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhzz_s1");
	MC_sampletag.push_back("VBFHToBBhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhtt_s1");
	MC_sampletag.push_back("VBFHToBBhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToGG

	/*MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGG_s1");
	MC_sampletag.push_back("VBFHToGG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGGhww_s1");
	MC_sampletag.push_back("VBFHToGGhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGGhzz_s1");
	MC_sampletag.push_back("VBFHToGGhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGGhtt_s1");
	MC_sampletag.push_back("VBFHToGGhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ttZ

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ); 
	MC_filename_norm.push_back(filename_norm_ttZ);
	MC_samplename.push_back("ttZ_s1");
	MC_sampletag.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ_PS); 
	MC_filename_norm.push_back(filename_norm_ttZ_PS);
	MC_samplename.push_back("ttZ_s2");
	MC_sampletag.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ_lowmass);
	MC_filename.push_back(filename_ttZ_lowmass);
	MC_filename_norm.push_back(filename_norm_ttZ_lowmass);
	MC_samplename.push_back("ttZm1to10_s1");
	MC_sampletag.push_back("ttZm1to10");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttW

	MC_XS.push_back(XS_ttW);
	MC_filename.push_back(filename_ttW);
	MC_filename_norm.push_back(filename_norm_ttW);
	MC_samplename.push_back("ttW_s1");
	MC_sampletag.push_back("ttW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttW);
	MC_filename.push_back(filename_ttW_PS);
	MC_filename_norm.push_back(filename_norm_ttW_PS);
	MC_samplename.push_back("ttW_s2");
	MC_sampletag.push_back("ttW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttWW

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW);
	MC_filename_norm.push_back(filename_norm_ttWW);
	MC_samplename.push_back("ttWW_s1");
	MC_sampletag.push_back("ttWW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// WW

	/*MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW);
	MC_filename_norm.push_back(filename_norm_WW);
	MC_samplename.push_back("WW_s1");
	MC_sampletag.push_back("WW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW_ext1);
	MC_filename_norm.push_back(filename_norm_WW_ext1);
	MC_samplename.push_back("WW_s2");
	MC_sampletag.push_back("WW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// WZ

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ);
	MC_filename_norm.push_back(filename_norm_WZ);
	MC_samplename.push_back("WZ_s1");
	MC_sampletag.push_back("WZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ZZ

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ);
	MC_filename_norm.push_back(filename_norm_ZZ);
	MC_samplename.push_back("ZZ_s1");
	MC_sampletag.push_back("ZZ");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ZZ_ext1);
	MC_samplename.push_back("ZZ_s2");
	MC_sampletag.push_back("ZZ");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ_ext2);
	MC_filename_norm.push_back(filename_norm_ZZ_ext2);
	MC_samplename.push_back("ZZ_s3");
	MC_sampletag.push_back("ZZ");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// DY

	/*MC_XS.push_back(XS_DY_M10to50);
	MC_filename.push_back(filename_DY_M10to50);
	MC_filename_norm.push_back(filename_norm_DY_M10to50);
	MC_samplename.push_back("DYm10to50_s1");
	MC_sampletag.push_back("DYm10to50");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_DY_M10to50);
	MC_filename.push_back(filename_DY_M10to50_ext1);
	MC_filename_norm.push_back(filename_norm_DY_M10to50_ext1);
	MC_samplename.push_back("DYm10to50_s2");
	MC_sampletag.push_back("DYm10to50");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_DY_M50);
	MC_filename.push_back(filename_DY_M50);
	MC_filename_norm.push_back(filename_norm_DY_M50);
	MC_samplename.push_back("DYm50_s1");
	MC_sampletag.push_back("DYm50");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_DY_M50);
	MC_filename.push_back(filename_DY_M50_ext1);
	MC_filename_norm.push_back(filename_norm_DY_M50_ext1);
	MC_samplename.push_back("DYm50_s2");
	MC_sampletag.push_back("DYm50");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// WJets

	/*MC_XS.push_back(XS_WJets);
	MC_filename.push_back(filename_WJets);
	MC_filename_norm.push_back(filename_norm_WJets);
	MC_samplename.push_back("WJets_s1");
	MC_sampletag.push_back("WJets");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WJets);
	MC_filename.push_back(filename_WJets_ext1);
	MC_filename_norm.push_back(filename_norm_WJets_ext1);
	MC_samplename.push_back("WJets_s2");
	MC_sampletag.push_back("WJets");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// Rares

	MC_XS.push_back(XS_WWW);
	MC_filename.push_back(filename_WWW);
	MC_filename_norm.push_back(filename_norm_WWW);
	MC_samplename.push_back("WWW_s1");
	MC_sampletag.push_back("WWW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WWZ);
	MC_filename.push_back(filename_WWZ);
	MC_filename_norm.push_back(filename_norm_WWZ);
	MC_samplename.push_back("WWZ_s1");
	MC_sampletag.push_back("WWZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZZ);
	MC_filename.push_back(filename_WZZ);
	MC_filename_norm.push_back(filename_norm_WZZ);
	MC_samplename.push_back("WZZ_s1");
	MC_sampletag.push_back("WZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZZ);
	MC_filename.push_back(filename_ZZZ);
	MC_filename_norm.push_back(filename_norm_ZZZ);
	MC_samplename.push_back("ZZZ_s1");
	MC_sampletag.push_back("ZZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZG);
	MC_filename.push_back(filename_WZG);
	MC_filename_norm.push_back(filename_norm_WZG);
	MC_samplename.push_back("WZG_s1");
	MC_sampletag.push_back("WZG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG);
	MC_filename_norm.push_back(filename_norm_WG);
	MC_samplename.push_back("WG_s1");
	MC_sampletag.push_back("WG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZG);
	MC_filename.push_back(filename_ZG);
	MC_filename_norm.push_back(filename_norm_ZG);
	MC_samplename.push_back("ZG_s1");
	MC_sampletag.push_back("ZG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tG);
	MC_filename.push_back(filename_tG);
	MC_filename_norm.push_back(filename_norm_tG);
	MC_samplename.push_back("tG_s1");
	MC_sampletag.push_back("tG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG);
	MC_filename_norm.push_back(filename_norm_ttG);
	MC_samplename.push_back("ttG_s1");
	MC_sampletag.push_back("ttG");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG_ext1);
	MC_filename_norm.push_back(filename_norm_ttG_ext1);
	MC_samplename.push_back("ttG_s2");
	MC_sampletag.push_back("ttG");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq); 
	MC_filename_norm.push_back(filename_norm_tZq);
	MC_samplename.push_back("tZq_s1");
	MC_sampletag.push_back("tZq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WpWp);
	MC_filename.push_back(filename_WpWp); 
	MC_filename_norm.push_back(filename_norm_WpWp);
	MC_samplename.push_back("WpWp_s1");
	MC_sampletag.push_back("WpWp");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW_DS);
	MC_filename.push_back(filename_WW_DS); 
	MC_filename_norm.push_back(filename_norm_WW_DS);
	MC_samplename.push_back("WWss_s1");
	MC_sampletag.push_back("WWss");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt); 
	MC_filename_norm.push_back(filename_norm_tttt);
	MC_samplename.push_back("tttt_s1");
	MC_sampletag.push_back("tttt");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt_PS); 
	MC_filename_norm.push_back(filename_norm_tttt_PS);
	MC_samplename.push_back("tttt_s2");
	MC_sampletag.push_back("tttt");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel); 
	MC_filename_norm.push_back(filename_norm_St_schannel);
	MC_samplename.push_back("TsCh_s1");
	MC_sampletag.push_back("TsCh");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel_PS); 
	MC_filename_norm.push_back(filename_norm_St_schannel_PS);
	MC_samplename.push_back("TsCh_s2");
	MC_sampletag.push_back("TsCh");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top);
	MC_samplename.push_back("TtChTop_s1");
	MC_sampletag.push_back("TtChTop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top_PS); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top_PS);
	MC_samplename.push_back("TtChTop_s2");
	MC_sampletag.push_back("TtChTop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop);
	MC_samplename.push_back("TtChAntitop_s1");
	MC_sampletag.push_back("TtChAntitop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop_PS); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop_PS);
	MC_samplename.push_back("TtChAntitop_s2");
	MC_sampletag.push_back("TtChAntitop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top); 
	MC_filename_norm.push_back(filename_norm_St_tW_top);
	MC_samplename.push_back("TtwChTop_s1");
	MC_sampletag.push_back("TtwChTop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top_PS); 
	MC_filename_norm.push_back(filename_norm_St_tW_top_PS);
	MC_samplename.push_back("TtwChTop_s2");
	MC_sampletag.push_back("TtwChTop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop);
	MC_samplename.push_back("TtwChAntitop_s1");
	MC_sampletag.push_back("TtwChAntitop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop_PS); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop_PS);
	MC_samplename.push_back("TtwChAntitop_s2");
	MC_sampletag.push_back("TtwChAntitop");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tWll);
	MC_filename.push_back(filename_St_tWll); 
	MC_filename_norm.push_back(filename_norm_St_tWll);
	MC_samplename.push_back("TtwChll_s1");
	MC_sampletag.push_back("TtwChll");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_samplename.push_back("ttbarDL_s1");
	MC_sampletag.push_back("ttbarDL");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_DiLept); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_DiLept); 
	MC_fakeCR_XS.push_back(XS_ttbar_DiLept);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt);
	MC_samplename.push_back("ttbarSLfromT_s1");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromt); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt); 
	MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar);
	MC_samplename.push_back("ttbarSLfromTbar_s1");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromtbar); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar); 
	MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	///////////////////////////////////////////////////////

	return std::make_tuple(MC_XS, MC_filename, MC_filename_norm, MC_samplename, MC_samplecut, MC_sampletag, MC_nsamples, MC_fakeCR_XS, MC_fakeCR_filename, MC_fakeCR_filename_norm, MC_convs_samplecut, luminosity);

}


std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<float>, vector<TString>, vector<TString>, vector<TString>, float > initialize_2018(){

	MC_XS.clear();

	MC_filename.clear();
	MC_filename_norm.clear();
	MC_samplename.clear();
	MC_samplecut.clear();
	MC_sampletag.clear();
	MC_nsamples.clear();
	MC_convs_samplecut.clear();

	MC_fakeCR_XS.clear();
	MC_fakeCR_filename.clear();
	MC_fakeCR_filename_norm.clear();

	luminosity = 59700;

	////////////////////////////////////////////////////////////

	TString filename_ttH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR.root";
	//TString filename_ttH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_datacards/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR_SFsv1.root";
	TString filename_ttH_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_TTH_ctcvcp_MEM_SR.root";
	TString filename_tHQ_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_MEM_SR.root";
	TString filename_tHW_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THW_ctcvcp_MEM_SR.root";

	TString filename_ttZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_MEM_SR.root";
	TString filename_ttZ_lowmass = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLL_M-1to10_MEM_SR.root";
	TString filename_ttW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_MEM_SR.root";
	TString filename_ttWW_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWW_ext1_MEM_SR.root";
	TString filename_ttWW_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWW_ext2_MEM_SR.root";

	TString filename_WW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_WWTo2L2Nu_MEM_SR.root";
	TString filename_WZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v1_MC_2018_WZTo3LNu_MEM_SR.root";
	TString filename_WZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_WZTo3LNu_ext1_MEM_SR.root";
	TString filename_ZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_ZZTo4L_MEM_SR.root";
	TString filename_ZZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v4_MC_2018_ZZTo4L_ext2_MEM_SR.root";

	TString filename_DY_M10to50 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-10to50_MEM_SR.root";
	TString filename_DY_M50 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_DYJetsToLL_M-50_MEM_SR.root";
	TString filename_DY_M50_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-50_ext2_MEM_SR.root";

	TString filename_WJets = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_WJetsToLNu_MEM_SR.root";

	TString filename_WWW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_WWW_MEM_SR.root";
	TString filename_WWZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_WWZ_MEM_SR.root";
	TString filename_WZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WZZ_MEM_SR.root";
	TString filename_ZZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_ZZZ_MEM_SR.root";
	TString filename_WZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WZG_MEM_SR.root";
	TString filename_WG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WGToLNuG_MEM_SR.root";
	TString filename_ZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_ZGToLLG_MEM_SR.root";
	TString filename_tG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TGJets_MEM_SR.root";
	TString filename_ttG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TTGJets_MEM_SR.root";
	TString filename_tZq = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_tZq_ll_MEM_SR.root";
	TString filename_WpWp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WpWpJJ_MEM_SR.root";
	TString filename_WW_DS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering_MEM_SR.root";
	TString filename_tttt = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TTTT_MEM_SR.root";

	TString filename_St_schannel = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_s-channel_MEM_SR.root";
	TString filename_St_tchannel_top = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_ST_t-channel_top_MEM_SR.root";
	TString filename_St_tchannel_antitop = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v3_MC_2018_ST_t-channel_antitop_MEM_SR.root";
	TString filename_St_tW_top = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v3_MC_2018_ST_tW_top_MEM_SR.root";
	TString filename_St_tW_antitop = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_tW_antitop_MEM_SR.root";
	TString filename_St_tWll = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_tWll_MEM_SR.root";

	TString filename_ttbar_DiLept = 					"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromt = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_MEM_SR.root";
	TString filename_ttbar_SingleLeptFromtbar = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_MEM_SR.root";

	TString filename_ggHToTauTau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToTauTau_MEM_SR.root";
	TString filename_ggHToZZ4l = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToZZTo4L_MEM_SR.root";
	TString filename_ggHToZZ2l2Q = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToZZTo2L2Q_MEM_SR.root";
	TString filename_ggHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToWWToLNuQQ_MEM_SR.root";
	TString filename_ggHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToWWTo2L2Nu_MEM_SR.root";
	TString filename_ggHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToMuMu_MEM_SR.root";
	TString filename_ggHToMuMu_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToMuMu_ext1_MEM_SR.root";
	TString filename_ggHToBB = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToBB_MEM_SR.root";
	TString filename_ggHToGG = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToGG_MEM_SR.root";

	TString filename_VBFHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToTauTau_MEM_SR.root";
	TString filename_VBFHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBF_HToZZTo4L_MEM_SR.root";
	TString filename_VBFHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToWWToLNuQQ_MEM_SR.root";
	TString filename_VBFHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToWWTo2L2Nu_MEM_SR.root";
	TString filename_VBFHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToMuMu_MEM_SR.root";
	TString filename_VBFHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToBB_MEM_SR.root";
	TString filename_VBFHToGG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToGG_MEM_SR.root";

	TString filename_VHToNonbb = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VH/ntuple_Oct19v2_MC_2018_VHToNonbb_MEM_SR.root";
	TString filename_ZHToTauTau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VH/ntuple_Oct19v2_MC_2018_ZHToTauTau_MEM_SR.root";
	TString filename_ZH_HToBB_ZToLL = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VH/ntuple_Oct19v1_MC_2018_ZH_HToBB_ZToLL_MEM_SR.root";
	TString filename_ZH_HToBB_ZToLL_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/VH/ntuple_Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1_MEM_SR.root";

	TString filename_ttWH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttVH/ntuple_Oct19v1_MC_2018_TTWH_MEM_SR.root";
	TString filename_ttZH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttVH/ntuple_Oct19v2_MC_2018_TTZH_MEM_SR.root";

	TString filename_ggHHTo2B2Tau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/HH/ntuple_Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM_MEM_SR.root";

	////////////////////////////////////////////////////////////

	TString filename_fakeCR_ttbar_DiLept = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromt = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_MEM_fake.root";
	TString filename_fakeCR_ttbar_SingleLeptFromtbar = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_splitted_MEM/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_MEM_fake.root";

	////////////////////////////////////////////////////////////

	TString filename_norm_ttH = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_norm.root";
	TString filename_norm_ttH_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_TTH_ctcvcp_norm.root";
	TString filename_norm_tHQ_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_norm.root";
	TString filename_norm_tHW_ctcvcp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THW_ctcvcp_norm.root";

	TString filename_norm_ttZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_norm.root";
	TString filename_norm_ttZ_lowmass = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLL_M-1to10_norm.root";
	TString filename_norm_ttW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_norm.root";
	TString filename_norm_ttWW_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWW_ext1_norm.root";
	TString filename_norm_ttWW_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWW_ext2_norm.root";

	TString filename_norm_WW = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_WWTo2L2Nu_norm.root";
	TString filename_norm_WZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v1_MC_2018_WZTo3LNu_norm.root";
	TString filename_norm_WZ_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_WZTo3LNu_ext1_norm.root";
	TString filename_norm_ZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_ZZTo4L_norm.root";
	TString filename_norm_ZZ_ext2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v4_MC_2018_ZZTo4L_ext2_norm.root";

	TString filename_norm_DY_M10to50 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-10to50_norm.root";
	TString filename_norm_DY_M50 = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_DYJetsToLL_M-50_norm.root";
	TString filename_norm_DY_M50_ext2 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_DYJetsToLL_M-50_ext2_norm.root";

	TString filename_norm_WJets = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_WJetsToLNu_norm.root";

	TString filename_norm_WWW = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_WWW_norm.root";
	TString filename_norm_WWZ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_WWZ_norm.root";
	TString filename_norm_WZZ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WZZ_norm.root";
	TString filename_norm_ZZZ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_ZZZ_norm.root";
	TString filename_norm_WZG = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WZG_norm.root";
	TString filename_norm_WG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WGToLNuG_norm.root";
	TString filename_norm_ZG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_ZGToLLG_norm.root";
	TString filename_norm_tG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TGJets_norm.root";
	TString filename_norm_ttG = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TTGJets_norm.root";
	TString filename_norm_tZq = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_tZq_ll_norm.root";
	TString filename_norm_WpWp = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WpWpJJ_norm.root";
	TString filename_norm_WW_DS = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering_norm.root";
	TString filename_norm_tttt = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TTTT_norm.root";

	TString filename_norm_St_schannel = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_s-channel_norm.root";
	TString filename_norm_St_tchannel_top = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_ST_t-channel_top_norm.root";
	TString filename_norm_St_tchannel_antitop = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v3_MC_2018_ST_t-channel_antitop_norm.root";
	TString filename_norm_St_tW_top = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v3_MC_2018_ST_tW_top_norm.root";
	TString filename_norm_St_tW_antitop = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_tW_antitop_norm.root";
	TString filename_norm_St_tWll = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_tWll_norm.root";

	TString filename_norm_ttbar_DiLept = 				"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_norm.root";
	TString filename_norm_ttbar_SingleLeptFromt = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_norm.root";
	TString filename_norm_ttbar_SingleLeptFromtbar = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_norm.root";

	TString filename_norm_ggHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToTauTau_norm.root";
	TString filename_norm_ggHToZZ4l = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToZZTo4L_norm.root";
	TString filename_norm_ggHToZZ2l2Q = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToZZTo2L2Q_norm.root";
	TString filename_norm_ggHToWWToLNuQQ = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToWWToLNuQQ_norm.root";
	TString filename_norm_ggHToWWTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToWWTo2L2Nu_norm.root";
	TString filename_norm_ggHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToMuMu_norm.root";
	TString filename_norm_ggHToMuMu_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToMuMu_ext1_norm.root";
	TString filename_norm_ggHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToBB_norm.root";
	TString filename_norm_ggHToGG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToGG_norm.root";

	TString filename_norm_VBFHToTauTau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToTauTau_norm.root";
	TString filename_norm_VBFHToZZ = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBF_HToZZTo4L_norm.root";
	TString filename_norm_VBFHToWWToLNuQQ = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToWWToLNuQQ_norm.root";
	TString filename_norm_VBFHToWWTo2L2Nu = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToWWTo2L2Nu_norm.root";
	TString filename_norm_VBFHToMuMu = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToMuMu_norm.root";
	TString filename_norm_VBFHToBB = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToBB_norm.root";
	TString filename_norm_VBFHToGG = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToGG_norm.root";

	TString filename_norm_VHToNonbb = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VH/ntuple_Oct19v2_MC_2018_VHToNonbb_norm.root";
	TString filename_norm_ZHToTauTau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VH/ntuple_Oct19v2_MC_2018_ZHToTauTau_norm.root";
	TString filename_norm_ZH_HToBB_ZToLL = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VH/ntuple_Oct19v1_MC_2018_ZH_HToBB_ZToLL_norm.root";
	TString filename_norm_ZH_HToBB_ZToLL_ext1 = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/VH/ntuple_Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1_norm.root";

	TString filename_norm_ttWH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttVH/ntuple_Oct19v1_MC_2018_TTWH_norm.root";
	TString filename_norm_ttZH = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttVH/ntuple_Oct19v2_MC_2018_TTZH_norm.root";

	TString filename_norm_ggHHTo2B2Tau = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/HH/ntuple_Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM_norm.root";

	///////////////////////////////////////////////////////

	TString filename_fakeCR_norm_ttbar_DiLept = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromt = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_norm.root";
	TString filename_fakeCR_norm_ttbar_SingleLeptFromtbar = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_norm.root";

	///////////////////////////////////////////////////////

	// ttH

	/*MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttH_s1");
	MC_sampletag.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhww_s1");
	MC_sampletag.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhzz_s1");
	MC_sampletag.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhtt_s1");
	MC_sampletag.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// MISSING:
	// - ttHhzg
	// - ttHhmm

	/*MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttH_s2");
	MC_sampletag.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhww_s2");
	MC_sampletag.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhzz_s2");
	MC_sampletag.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH_ctcvcp);
	MC_filename.push_back(filename_ttH_ctcvcp);
	MC_filename_norm.push_back(filename_norm_ttH_ctcvcp);
	MC_samplename.push_back("ttHhtt_s2");
	MC_sampletag.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);*/

	// MISSING:
	// - ttHhzg
	// - ttHhmm

	///////////////////////////////////////////////////////

	// tHQ

	/*MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQ_s1");
	MC_sampletag.push_back("tHQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhww_s1");
	MC_sampletag.push_back("tHQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhzz_s1");
	MC_sampletag.push_back("tHQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQhtt_s1");
	MC_sampletag.push_back("tHQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// tHW

	/*MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHW_s1");
	MC_sampletag.push_back("tHW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhww_s1");
	MC_sampletag.push_back("tHWhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhzz_s1");
	MC_sampletag.push_back("tHWhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHWhtt_s1");
	MC_sampletag.push_back("tHWhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// VHToNonbb

	/*MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbb_s1");
	MC_sampletag.push_back("VHToNonbb");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhww_s1");
	MC_sampletag.push_back("VHToNonbbhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhzz_s1");
	MC_sampletag.push_back("VHToNonbbhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbbhtt_s1");
	MC_sampletag.push_back("VHToNonbbhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ZHToTauTau

	/*MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTau_s1");
	MC_sampletag.push_back("ZHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhww_s1");
	MC_sampletag.push_back("ZHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhzz_s1");
	MC_sampletag.push_back("ZHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTauhtt_s1");
	MC_sampletag.push_back("ZHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ZH_HToBB_ZToLL

	/*MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLL_s1");
	MC_sampletag.push_back("HToBBZToLL");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhww_s1");
	MC_sampletag.push_back("HToBBZToLLhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhzz_s1");
	MC_sampletag.push_back("HToBBZToLLhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLLhtt_s1");
	MC_sampletag.push_back("HToBBZToLLhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ttWH

	/*MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWH_s1");
	MC_sampletag.push_back("ttWH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhww_s1");
	MC_sampletag.push_back("ttWHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhzz_s1");
	MC_sampletag.push_back("ttWHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWHhtt_s1");
	MC_sampletag.push_back("ttWHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ttZH

	/*MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZH_s1");
	MC_sampletag.push_back("ttZH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhww_s1");
	MC_sampletag.push_back("ttZHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhzz_s1");
	MC_sampletag.push_back("ttZHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZHhtt_s1");
	MC_sampletag.push_back("ttZHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// ggHToTauTau

	/*MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTau_s1");
	MC_sampletag.push_back("ggHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhww_s1");
	MC_sampletag.push_back("ggHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhzz_s1");
	MC_sampletag.push_back("ggHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTauhtt_s1");
	MC_sampletag.push_back("ggHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToZZ4l

	/*MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ4l);
	MC_filename_norm.push_back(filename_norm_ggHToZZ4l);
	MC_samplename.push_back("ggHToZZ4l_s1");
	MC_sampletag.push_back("ggHToZZ4l");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ4l);
	MC_filename_norm.push_back(filename_norm_ggHToZZ4l);
	MC_samplename.push_back("ggHToZZhww_s1");
	MC_sampletag.push_back("ggHToZZhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ4l);
	MC_filename_norm.push_back(filename_norm_ggHToZZ4l);
	MC_samplename.push_back("ggHToZZhzz_s1");
	MC_sampletag.push_back("ggHToZZhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ4l);
	MC_filename_norm.push_back(filename_norm_ggHToZZ4l);
	MC_samplename.push_back("ggHToZZhtt_s1");
	MC_sampletag.push_back("ggHToZZhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToWWToLNuQQ

	/*MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQ_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhww_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhzz_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQhtt_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToWWTo2L2Nu

	/*MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhww_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhzz_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nuhtt_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToMuMu

	/*MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMu_s1");
	MC_sampletag.push_back("ggHToMuMu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhww_s1");
	MC_sampletag.push_back("ggHToMuMuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhzz_s1");
	MC_sampletag.push_back("ggHToMuMuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMuhtt_s1");
	MC_sampletag.push_back("ggHToMuMuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToBB

	/*MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBB_s1");
	MC_sampletag.push_back("ggHToBB");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhww_s1");
	MC_sampletag.push_back("ggHToBBhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhzz_s1");
	MC_sampletag.push_back("ggHToBBhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBBhtt_s1");
	MC_sampletag.push_back("ggHToBBhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// ggHToGG

	/*MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGG_s1");
	MC_sampletag.push_back("ggHToGG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhww_s1");
	MC_sampletag.push_back("ggHToGGhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhzz_s1");
	MC_sampletag.push_back("ggHToGGhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGGhtt_s1");
	MC_sampletag.push_back("ggHToGGhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	///////////////////////////////////////////////////////

	// VBFHToTauTau

	/*MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTau_s1");
	MC_sampletag.push_back("VBFHToTauTau");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhww_s1");
	MC_sampletag.push_back("VBFHToTauTauhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhzz_s1");
	MC_sampletag.push_back("VBFHToTauTauhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTauhtt_s1");
	MC_sampletag.push_back("VBFHToTauTauhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToZZ

	/*MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZ_s1");
	MC_sampletag.push_back("VBFHToZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhww_s1");
	MC_sampletag.push_back("VBFHToZZhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhzz_s1");
	MC_sampletag.push_back("VBFHToZZhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZhtt_s1");
	MC_sampletag.push_back("VBFHToZZhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToWWToLNuQQ

	/*MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQ_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhww_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhzz_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQhtt_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToWWTo2L2Nu

	/*MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhww_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhzz_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nuhtt_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToMuMu

	/*MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMu_s1");
	MC_sampletag.push_back("VBFHToMuMu");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhww_s1");
	MC_sampletag.push_back("VBFHToMuMuhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhzz_s1");
	MC_sampletag.push_back("VBFHToMuMuhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMuhtt_s1");
	MC_sampletag.push_back("VBFHToMuMuhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToBB

	/*MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBB_s1");
	MC_sampletag.push_back("VBFHToBB");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhww_s1");
	MC_sampletag.push_back("VBFHToBBhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhzz_s1");
	MC_sampletag.push_back("VBFHToBBhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBBhtt_s1");
	MC_sampletag.push_back("VBFHToBBhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);

	// VBFHToGG

	/*MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGG_s1");
	MC_sampletag.push_back("VBFHToGG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGGhww_s1");
	MC_sampletag.push_back("VBFHToGGhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGGhzz_s1");
	MC_sampletag.push_back("VBFHToGGhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGGhtt_s1");
	MC_sampletag.push_back("VBFHToGGhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);


	///////////////////////////////////////////////////////

	// ttZ

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ); 
	MC_filename_norm.push_back(filename_norm_ttZ);
	MC_samplename.push_back("ttZ_s1");
	MC_sampletag.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ_lowmass);
	MC_filename.push_back(filename_ttZ_lowmass);
	MC_filename_norm.push_back(filename_norm_ttZ_lowmass);
	MC_samplename.push_back("ttZm1to10_s1");
	MC_sampletag.push_back("ttZm1to10");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttW

	MC_XS.push_back(XS_ttW);
	MC_filename.push_back(filename_ttW);
	MC_filename_norm.push_back(filename_norm_ttW);
	MC_samplename.push_back("ttW_s1");
	MC_sampletag.push_back("ttW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttWW

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW_ext1);
	MC_filename_norm.push_back(filename_norm_ttWW_ext1);
	MC_samplename.push_back("ttWW_s1");
	MC_sampletag.push_back("ttWW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW_ext2);
	MC_filename_norm.push_back(filename_norm_ttWW_ext2);
	MC_samplename.push_back("ttWW_s2");
	MC_sampletag.push_back("ttWW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// WW

	/*MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW);
	MC_filename_norm.push_back(filename_norm_WW);
	MC_samplename.push_back("WW_s1");
	MC_sampletag.push_back("WW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// WZ

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ);
	MC_filename_norm.push_back(filename_norm_WZ);
	MC_samplename.push_back("WZ_s1");
	MC_sampletag.push_back("WZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ_ext1);
	MC_filename_norm.push_back(filename_norm_WZ_ext1);
	MC_samplename.push_back("WZ_s2");
	MC_sampletag.push_back("WZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ZZ

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ);
	MC_filename_norm.push_back(filename_norm_ZZ);
	MC_samplename.push_back("ZZ_s1");
	MC_sampletag.push_back("ZZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ_ext2);
	MC_filename_norm.push_back(filename_norm_ZZ_ext2);
	MC_samplename.push_back("ZZ_s2");
	MC_sampletag.push_back("ZZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// DY

	/*MC_XS.push_back(XS_DY_M10to50);
	MC_filename.push_back(filename_DY_M10to50);
	MC_filename_norm.push_back(filename_norm_DY_M10to50);
	MC_samplename.push_back("DYm10to50_s1");
	MC_sampletag.push_back("DYm10to50");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_DY_M50);
	MC_filename.push_back(filename_DY_M50);
	MC_filename_norm.push_back(filename_norm_DY_M50);
	MC_samplename.push_back("DYm50_s1");
	MC_sampletag.push_back("DYm50");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_DY_M50);
	MC_filename.push_back(filename_DY_M50_ext2);
	MC_filename_norm.push_back(filename_norm_DY_M50_ext2);
	MC_samplename.push_back("DYm50_s2");
	MC_sampletag.push_back("DYm50");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// WJets

	/*MC_XS.push_back(XS_WJets);
	MC_filename.push_back(filename_WJets);
	MC_filename_norm.push_back(filename_norm_WJets);
	MC_samplename.push_back("WJets_s1");
	MC_sampletag.push_back("WJets");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// Rares

	MC_XS.push_back(XS_WWW);
	MC_filename.push_back(filename_WWW);
	MC_filename_norm.push_back(filename_norm_WWW);
	MC_samplename.push_back("WWW_s1");
	MC_sampletag.push_back("WWW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WWZ);
	MC_filename.push_back(filename_WWZ);
	MC_filename_norm.push_back(filename_norm_WWZ);
	MC_samplename.push_back("WWZ_s1");
	MC_sampletag.push_back("WWZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZZ);
	MC_filename.push_back(filename_WZZ);
	MC_filename_norm.push_back(filename_norm_WZZ);
	MC_samplename.push_back("WZZ_s1");
	MC_sampletag.push_back("WZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZZ);
	MC_filename.push_back(filename_ZZZ);
	MC_filename_norm.push_back(filename_norm_ZZZ);
	MC_samplename.push_back("ZZZ_s1");
	MC_sampletag.push_back("ZZZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZG);
	MC_filename.push_back(filename_WZG);
	MC_filename_norm.push_back(filename_norm_WZG);
	MC_samplename.push_back("WZG_s1");
	MC_sampletag.push_back("WZG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG);
	MC_filename_norm.push_back(filename_norm_WG);
	MC_samplename.push_back("WG_s1");
	MC_sampletag.push_back("WG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZG);
	MC_filename.push_back(filename_ZG);
	MC_filename_norm.push_back(filename_norm_ZG);
	MC_samplename.push_back("ZG_s1");
	MC_sampletag.push_back("ZG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tG);
	MC_filename.push_back(filename_tG);
	MC_filename_norm.push_back(filename_norm_tG);
	MC_samplename.push_back("tG_s1");
	MC_sampletag.push_back("tG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG);
	MC_filename_norm.push_back(filename_norm_ttG);
	MC_samplename.push_back("ttG_s1");
	MC_sampletag.push_back("ttG");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq); 
	MC_filename_norm.push_back(filename_norm_tZq);
	MC_samplename.push_back("tZq_s1");
	MC_sampletag.push_back("tZq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WpWp);
	MC_filename.push_back(filename_WpWp); 
	MC_filename_norm.push_back(filename_norm_WpWp);
	MC_samplename.push_back("WpWp_s1");
	MC_sampletag.push_back("WpWp");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW_DS);
	MC_filename.push_back(filename_WW_DS); 
	MC_filename_norm.push_back(filename_norm_WW_DS);
	MC_samplename.push_back("WWss_s1");
	MC_sampletag.push_back("WWss");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt); 
	MC_filename_norm.push_back(filename_norm_tttt);
	MC_samplename.push_back("tttt_s1");
	MC_sampletag.push_back("tttt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel); 
	MC_filename_norm.push_back(filename_norm_St_schannel);
	MC_samplename.push_back("TsCh_s1");
	MC_sampletag.push_back("TsCh");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top);
	MC_samplename.push_back("TtChTop_s1");
	MC_sampletag.push_back("TtChTop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop);
	MC_samplename.push_back("TtChAntitop_s1");
	MC_sampletag.push_back("TtChAntitop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top); 
	MC_filename_norm.push_back(filename_norm_St_tW_top);
	MC_samplename.push_back("TtwChTop_s1");
	MC_sampletag.push_back("TtwChTop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop);
	MC_samplename.push_back("TtwChAntitop_s1");
	MC_sampletag.push_back("TtwChAntitop");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tWll);
	MC_filename.push_back(filename_St_tWll); 
	MC_filename_norm.push_back(filename_norm_St_tWll);
	MC_samplename.push_back("TtwChll_s1");
	MC_sampletag.push_back("TtwChll");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_samplename.push_back("ttbarDL_s1");
	MC_sampletag.push_back("ttbarDL");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_DiLept); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_fakeCR_XS.push_back(XS_ttbar_DiLept);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt);
	MC_samplename.push_back("ttbarSLfromT_s1");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromt); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt); 
	MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar);
	MC_samplename.push_back("ttbarSLfromTbar_s1");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);
	MC_fakeCR_filename.push_back(filename_fakeCR_ttbar_SingleLeptFromtbar); 
	MC_fakeCR_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar); 
	MC_fakeCR_XS.push_back(XS_ttbar_SingleLep/2);

	///////////////////////////////////////////////////////

	return std::make_tuple(MC_XS, MC_filename, MC_filename_norm, MC_samplename, MC_samplecut, MC_sampletag, MC_nsamples, MC_fakeCR_XS, MC_fakeCR_filename, MC_fakeCR_filename_norm, MC_convs_samplecut, luminosity);

}



void datacard_maker(TString var1, int nbin, float xmin, float xmax,
					TString cut_cat, TString file, bool syst=false, int year=2016){

	cout<<"Creating datacards..."<<endl;
	cout<<" Year: "<<year<<endl;

	TString var = var1 + "*(" + var1 + Form("<=%f) + %f*(",xmax,0.999*xmax) + var1 + Form(">%f)",xmax);
  	cout<<" Variable: "<<var<<endl;

  	std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<float>, vector<TString>, vector<TString>, vector<TString>, float > loadedsamples;
  	if(year==2016) loadedsamples = initialize_2016();
  	else if(year==2017) loadedsamples = initialize_2017();
  	else if(year==2018) loadedsamples = initialize_2018();

  	vector<float> 	XS_MC = std::get<0>(loadedsamples);
  	vector<TString> filename_MC = std::get<1>(loadedsamples);
  	vector<TString> filename_norm_MC = std::get<2>(loadedsamples);
  	vector<TString> samplename_MC = std::get<3>(loadedsamples);
  	vector<TString> samplecut_MC = std::get<4>(loadedsamples);
  	vector<TString> sampletag_MC = std::get<5>(loadedsamples);
  	vector<int> 	nsamples_MC = std::get<6>(loadedsamples);
  	vector<float> 	XS_MC_fakeCR = std::get<7>(loadedsamples);
  	vector<TString> fakeCRfilename_MC = std::get<8>(loadedsamples);
  	vector<TString> fakeCRfilename_norm_MC = std::get<9>(loadedsamples);
  	vector<TString> samplecutconvs_MC = std::get<10>(loadedsamples);
  	float 			lumin = std::get<11>(loadedsamples);

  	cout<<" Lumi: "<<lumin<<endl;

  	TString cat_name = "ttH_2lss_1tau";

  	int cat_SR   = 3110;
  	int cat_fake = 3120;
  	int cat_flip = 3130;

  	TFile* f_new = TFile::Open(file,"RECREATE");

	///////////////////////////////////////////////////////

	// PROMPT REGION

	// Get normalization files

	vector<float> norm_MC;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString MC_weight = "MC_weight";
		if( samplename_MC[i_MC].Contains("tHQ") || samplename_MC[i_MC].Contains("tHW"))
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)*sign(MC_weight)";
			MC_weight = "MC_weight";

		TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
			"Tree",
			"1",
			MC_weight+"*PU_weight_v1",
			3,0,3);

		norm_MC.push_back(h_MC_norm->Integral());

	}  	


	// Normalize samples

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		if( samplename_MC[i_MC].Contains("s2") || samplename_MC[i_MC].Contains("s3") ) continue;

		TString MC_weight = "MC_weight";
		if( samplename_MC[i_MC].Contains("tHQ") || samplename_MC[i_MC].Contains("tHW"))
			MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "MC_weight";

		TH1F* h_MC = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			//MC_weight+"*PU_weight_v1*prefire_weight*triggerSF_weight_v1*leptonSF_weight_v1*bTagSF_CSVshape_weight*tauSF_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            "MC_weight*PU_weight_v1*prefire_weight*triggerSF_weight*bTagSF_CSVshape_weight*tauSF_weight*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);

		h_MC->SetNameTitle("x_"+sampletag_MC[i_MC],"x_"+sampletag_MC[i_MC]);
		makeBinContentsPositive(h_MC,true);
		//h_MC->Write();

	}

	cout<<" "<<endl;
	cout<<"Grouping samples..."<<endl;

	// Grouping samples

    TH1F* h_TTHww = (TH1F*)f_new->Get("x_ttHhww");
    h_TTHww->SetNameTitle("x_TTH_hww","x_TTH_hww");
    h_TTHww->Write();

    TH1F* h_TTHzz = (TH1F*)f_new->Get("x_ttHhzz");
    h_TTHzz->SetNameTitle("x_TTH_hzz","x_TTH_hzz");
    h_TTHzz->Write();

    TH1F* h_TTHtt = (TH1F*)f_new->Get("x_ttHhtt");
    h_TTHtt->SetNameTitle("x_TTH_htt","x_TTH_htt");
    h_TTHtt->Write();

    TH1F* h_THQww = (TH1F*)f_new->Get("x_tHQhww");
    h_THQww->SetNameTitle("x_THQ_hww","x_THQ_hww");
    h_THQww->Write();

    TH1F* h_THQzz = (TH1F*)f_new->Get("x_tHQhzz");
    h_THQzz->SetNameTitle("x_THQ_hzz","x_THQ_hzz");
    h_THQzz->Write();

    TH1F* h_THQtt = (TH1F*)f_new->Get("x_tHQhtt");
    h_THQtt->SetNameTitle("x_THQ_htt","x_THQ_htt");
    h_THQtt->Write();

    TH1F* h_THWww = (TH1F*)f_new->Get("x_tHWhww");
    h_THWww->SetNameTitle("x_THW_hww","x_THW_hww");
    h_THWww->Write();

    TH1F* h_THWzz = (TH1F*)f_new->Get("x_tHWhzz");
    h_THWzz->SetNameTitle("x_THW_hzz","x_THW_hzz");
    h_THWzz->Write();

    TH1F* h_THWtt = (TH1F*)f_new->Get("x_tHWhtt");
    h_THWtt->SetNameTitle("x_THW_htt","x_THW_htt");
    h_THWtt->Write();

    TH1F* h_TTZ = (TH1F*)f_new->Get("x_ttZ");
    h_TTZ->Add( (TH1F*)f_new->Get("x_ttZm1to10") );
    h_TTZ->Add( (TH1F*)f_new->Get("x_ttbarDL") );
    h_TTZ->Add( (TH1F*)f_new->Get("x_ttbarSLfromT") );
    h_TTZ->Add( (TH1F*)f_new->Get("x_ttbarSLfromTbar") );
    h_TTZ->SetNameTitle("x_TTZ","x_TTZ");
    h_TTZ->Write();

    TH1F* h_TTW = (TH1F*)f_new->Get("x_ttW");
    h_TTW->SetNameTitle("x_TTW","x_TTW");
    h_TTW->Write();

    TH1F* h_TTWW = (TH1F*)f_new->Get("x_ttWW");
    h_TTWW->SetNameTitle("x_TTWW","x_TTWW");
    h_TTWW->Write();

    TH1F* h_WZ = (TH1F*)f_new->Get("x_WZ");
    h_WZ->SetNameTitle("x_WZ","x_WZ");
    h_WZ->Write();

    TH1F* h_ZZ = (TH1F*)f_new->Get("x_ZZ");
    h_ZZ->SetNameTitle("x_ZZ","x_ZZ");
    h_ZZ->Write();

    /*TH1F* h_EWK = (TH1F*)f_new->Get("x_WZ");
    h_EWK->Add( (TH1F*)f_new->Get("x_ZZ") );
    h_EWK->SetNameTitle("x_EWK","x_EWK");
    h_EWK->Write();*/

 	TH1F* h_Rares = (TH1F*)f_new->Get("x_WWW");
    h_Rares->Add( (TH1F*)f_new->Get("x_WWZ") );
    h_Rares->Add( (TH1F*)f_new->Get("x_WZZ") );
    h_Rares->Add( (TH1F*)f_new->Get("x_ZZZ") );
    h_Rares->Add( (TH1F*)f_new->Get("x_WZG") );
    h_Rares->Add( (TH1F*)f_new->Get("x_WpWp") );
    h_Rares->Add( (TH1F*)f_new->Get("x_WWss") );
    h_Rares->Add( (TH1F*)f_new->Get("x_tttt") );
    h_Rares->Add( (TH1F*)f_new->Get("x_TsCh") );
    h_Rares->Add( (TH1F*)f_new->Get("x_TtChTop") );
    h_Rares->Add( (TH1F*)f_new->Get("x_TtChAntitop") );
    h_Rares->Add( (TH1F*)f_new->Get("x_TtwChTop") );
    h_Rares->Add( (TH1F*)f_new->Get("x_TtwChAntitop") );
    h_Rares->Add( (TH1F*)f_new->Get("x_TtwChll") );
    h_Rares->Add( (TH1F*)f_new->Get("x_WZG") );
    h_Rares->Add( (TH1F*)f_new->Get("x_tZq") );
    h_Rares->SetNameTitle("x_Rares","x_Rares");
    h_Rares->Write();

    TH1F* h_Convs = (TH1F*)f_new->Get("x_ttG");
    h_Convs->SetNameTitle("x_Convs","x_Convs");
    h_Convs->Write();

    // FAKE REGION

    vector<float> norm_MC_fakeCR;

	for(unsigned i_MC=0;i_MC<MC_fakeCR_filename.size();i_MC++){

		TH1F* h_MC_fakeCR_norm = single_plot(fakeCRfilename_norm_MC[i_MC],
			"Tree",
			"1",
			"MC_weight*PU_weight_v1",
			3,0,3);

		norm_MC_fakeCR.push_back(h_MC_fakeCR_norm->Integral());

	}  	


	// Normalize samples

	for(unsigned i_MC=0;i_MC<MC_fakeCR_filename.size();i_MC++){

		TH1F* h_MC_fake = single_plot(MC_fakeCR_filename[i_MC],
			"HTauTauTree_2lss1tau_fake", 
			var,
			"MC_weight*PU_weight_v1*prefire_weight*triggerSF_weight*bTagSF_CSVshape_weight*tauSF_weight*("+cut_cat+")*event_weight_ttH",
            nbin,xmin,xmax);

		h_MC_fake->Scale(lumin*XS_MC_fakeCR[i_MC]/norm_MC_fakeCR[i_MC]);

		if(i_MC==0) h_MC_fake->SetNameTitle("x_ttbar_DL_fakes","x_ttbar_DL_fakes");
		else if(i_MC==1) h_MC_fake->SetNameTitle("x_ttbar_SLfromT_fakes","x_ttbar_SLfromT_fakes");
		else if(i_MC==2) h_MC_fake->SetNameTitle("x_ttbar_SLfromTbar_fakes","x_ttbar_SLfromTbar_fakes");

		makeBinContentsPositive(h_MC_fake,true);
		//h_MC_fake->Write();

	} 
    
    TH1F* h_fakes_MC = (TH1F*)f_new->Get("x_ttbar_DL_fakes");
    h_fakes_MC->Add( (TH1F*)f_new->Get("x_ttbar_SLfromT_fakes") );
    h_fakes_MC->Add( (TH1F*)f_new->Get("x_ttbar_SLfromTbar_fakes") );
    h_fakes_MC->SetNameTitle("x_fakes_MC","x_fakes_MC");
    h_fakes_MC->Write();

}


void datacard_maker_n_recotauh(int theyear = 2016){

	std::string theyear_s = to_string(theyear);

  	TString var = "n_recotauh";
  	
  	int nbin = 5;
  	float xmin = 0.;
  	float xmax = 5.;
  	TString cut = "((recotauh_decayMode[0]!=5) && (recotauh_decayMode[0]!=6) && (recotauh_byVVVLooseDeepTau2017v2p1VSe[0]) && (recotauh_byVLooseDeepTau2017v2p1VSmu[0]) )";
  	TString file = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_nrecotauh_2lss1tau_"+theyear_s+".root";
	
  	datacard_maker(var,nbin,xmin,xmax,cut,file,false,theyear);

}

void datacard_maker_MEM_nomiss(int theyear = 2016){

	std::string theyear_s = to_string(theyear);

  	TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";
  	
  	int nbin = 10;
  	float xmin = 0.;
  	float xmax = 1.;

  	TString cut = "integration_type==0 && ((recotauh_decayMode[0]!=5) && (recotauh_decayMode[0]!=6) && (recotauh_byVVVLooseDeepTau2017v2p1VSe[0]) && (recotauh_byVLooseDeepTau2017v2p1VSmu[0]) )";
  	TString file = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_"+theyear_s+".root";
	
  	datacard_maker(var,nbin,xmin,xmax,cut,file,false,theyear);

}

void datacard_maker_MEM_miss(int theyear = 2016){

	std::string theyear_s = to_string(theyear);

  	TString var="Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)";
  
  	int nbin = 10;
  	float xmin = 0.;
  	float xmax = 1.;

  	TString cut = "integration_type==1 && ((recotauh_decayMode[0]!=5) && (recotauh_decayMode[0]!=6) && (recotauh_byVVVLooseDeepTau2017v2p1VSe[0]) && (recotauh_byVLooseDeepTau2017v2p1VSmu[0]) )";
  	TString file = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_"+theyear_s+".root";
	
  	datacard_maker(var,nbin,xmin,xmax,cut,file,false,theyear);

}

