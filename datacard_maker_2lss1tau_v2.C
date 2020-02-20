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
float XS_ggHToZZTo2L2Q = 0.17963;
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
float XS_ggHHTo2V2Tau = 0.00093435;
float XS_ggHHTo4V = 0.00178684;

////////////////////////////////////////////////////////////

vector<float> 	MC_XS;
vector<TString> MC_filename;
vector<TString> MC_filename_norm;
vector<TString> MC_samplename;
vector<TString> MC_samplecut;
vector<TString> MC_sampletag;
vector<TString> MC_samplegroup;
vector<int>		MC_nsamples;
vector<TString> MC_convs_samplecut;

vector<TString>	Data_SR_filename;
vector<TString> Data_fake_filename;
vector<TString> Data_flip_filename;

float luminosity;

////////////////////////////////////////////////////////////

TString chargematch = "(recolep_sel_isGenChargeMatched[0] && recolep_sel_isGenChargeMatched[1])";
TString genmatch = "(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1])";
TString conversmatch = "((recolep_matchedGenPartIdx[0]>=0 && genpart_pdg[recolep_matchedGenPartIdx[0]]==22) || (recolep_matchedGenPartIdx[1]>=0 && genpart_pdg[recolep_matchedGenPartIdx[1]]==22))";

TString hww = "(genH_decayMode[1]>5 && n_genW==4)";
TString hzz = "(genH_decayMode[1]>5 && n_genZ==2)";
TString htt = "(genH_decayMode[1]<=5)";

////////////////////////////////////////////////////////////

std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, float > initialize_2016(){

	MC_XS.clear();

	MC_filename.clear();
	MC_filename_norm.clear();
	MC_samplename.clear();
	MC_samplecut.clear();
	MC_sampletag.clear();
	MC_samplegroup.clear();
	MC_nsamples.clear();
	MC_convs_samplecut.clear();

	Data_SR_filename.clear();
	Data_fake_filename.clear();
	Data_flip_filename.clear();

	luminosity = 35920;

	////////////////////////////////////////////////////////////
	
	TString filename_ttH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttHJetToNonbb_MEM_SR_SF_v1.root";
    TString filename_ttH_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_ttH_ctcvcp_MEM_SR_SF_v1.root";
	TString filename_tHQ_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THQ_ctcvcp_MEM_SR_SF_v1.root";
	TString filename_tHW_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttH/ntuple_Oct19v1_MC_2016_THW_ctcvcp_MEM_SR_SF_v1.root";

	TString filename_ttZ_ext2 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext2_MEM_SR_SF_v1.root";
	TString filename_ttZ_ext3 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLLNuNu_M-10_ext3_MEM_SR_SF_v1.root";
	TString filename_ttZ_lowmass = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTZToLL_M-1to10_MEM_SR_SF_v1.root";
	TString filename_ttW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWJetsToLNu_MEM_SR_SF_v1.root";
	TString filename_ttWW = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttV/ntuple_Oct19v1_MC_2016_TTWW_MEM_SR_SF_v1.root";

	TString filename_WW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_WZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_WZTo3LNu_MEM_SR_SF_v1.root";
	TString filename_ZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/EWK/ntuple_Oct19v1_MC_2016_ZZTo4L_MEM_SR_SF_v1.root";

	TString filename_WWW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWW_MEM_SR_SF_v1.root";
	TString filename_WWZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WWZ_MEM_SR_SF_v1.root";
	TString filename_WZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WZZ_MEM_SR_SF_v1.root";
	TString filename_ZZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_ZZZ_MEM_SR_SF_v1.root";
	TString filename_WZG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WZG_MEM_SR_SF_v1.root";
	TString filename_WG_ext1 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext1_MEM_SR_SF_v1.root";
	TString filename_WG_ext2 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext2_MEM_SR_SF_v1.root";
	TString filename_WG_ext3 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WGToLNuG_ext3_MEM_SR_SF_v1.root";
	TString filename_ZG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_ZGTo2LG_MEM_SR_SF_v1.root";
	TString filename_tG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TGJets_leptonDecays_MEM_SR_SF_v1.root";
	TString filename_ttG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTGJets_MEM_SR_SF_v1.root";
	TString filename_ttG_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTGJets_ext1_MEM_SR_SF_v1.root";
	TString filename_tZq = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v2_MC_2016_tZq_ll_MEM_SR_SF_v1.root";
	TString filename_tZq_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_tZq_ll_PS_MEM_SR_SF_v1.root";
	TString filename_WpWp = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_WpWpJJ_MEM_SR_SF_v1.root";
	TString filename_WW_DS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v2_MC_2016_WWTo2L2Nu_DoubleScattering_MEM_SR_SF_v1.root";
	TString filename_tttt = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Rares/ntuple_Oct19v1_MC_2016_TTTT_MEM_SR_SF_v1.root";

	TString filename_St_schannel = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_s-channel_MEM_SR_SF_v1.root";
	TString filename_St_schannel_PS = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_s-channel_PS_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_top = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_top_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_antitop = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_antitop_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_antitop_PS = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_t-channel_antitop_PS_MEM_SR_SF_v1.root";
	TString filename_St_tW_top = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tW_top_MEM_SR_SF_v1.root";
	TString filename_St_tW_antitop = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tW_antitop_MEM_SR_SF_v1.root";
	TString filename_St_tWll = 					"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_ST_tWll_MEM_SR_SF_v1.root";

	TString filename_ttbar_DiLept = 					"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_MEM_SR_SF_v1.root";
	TString filename_ttbar_DiLept_ext1 = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_DiLept_ext1_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromt = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromT_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromt_ext1 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v2_MC_2016_TTJets_SingleLeptFromT_ext1_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromtbar = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v1_MC_2016_TTJets_SingleLeptFromTbar_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromtbar_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttbar/ntuple_Oct19v3_MC_2016_TTJets_SingleLeptFromTbar_ext1_MEM_SR_SF_v1.root";

	TString filename_ggHToTauTau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToTauTau_MEM_SR_SF_v1.root";
	TString filename_ggHToZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToZZTo4L_MEM_SR_SF_v1.root";
	TString filename_ggHToWWToLNuQQ = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToWWToLNuQQ_MEM_SR_SF_v1.root";
	TString filename_ggHToWWTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToWWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_ggHToMuMu = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToMuMu_MEM_SR_SF_v1.root";
	TString filename_ggHToBB = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToBB_MEM_SR_SF_v1.root";
	TString filename_ggHToBB_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v6_MC_2016_GluGluHToBB_ext1_MEM_SR_SF_v1.root";
	TString filename_ggHToGG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ggH/ntuple_Oct19v1_MC_2016_GluGluHToGG_MEM_SR_SF_v1.root";

	TString filename_VBFHToTauTau = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v2_MC_2016_VBFHToTauTau_MEM_SR_SF_v1.root";
	TString filename_VBFHToZZ = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v2_MC_2016_VBF_HToZZTo4L_MEM_SR_SF_v1.root";
	TString filename_VBFHToWWToLNuQQ = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToWWToLNuQQ_MEM_SR_SF_v1.root";
	TString filename_VBFHToWWTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToWWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_VBFHToMuMu = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToMuMu_MEM_SR_SF_v1.root";
	TString filename_VBFHToBB = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v3_MC_2016_VBFHToBB_MEM_SR_SF_v1.root";
	TString filename_VBFHToBB_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToBB_ext1_MEM_SR_SF_v1.root";
	TString filename_VBFHToGG_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToGG_ext1_MEM_SR_SF_v1.root";
	TString filename_VBFHToGG_ext2 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VBF/ntuple_Oct19v1_MC_2016_VBFHToGG_ext2_MEM_SR_SF_v1.root";

	TString filename_VHToNonbb = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VH/ntuple_Oct19v1_MC_2016_VHToNonbb_MEM_SR_SF_v1.root";
	TString filename_ZHToTauTau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VH/ntuple_Oct19v1_MC_2016_ZHToTauTau_MEM_SR_SF_v1.root";
	TString filename_ZH_HToBB_ZToLL = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/VH/ntuple_Oct19v1_MC_2016_ZH_HToBB_ZToLL_MEM_SR_SF_v1.root";

	TString filename_ttWH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttVH/ntuple_Oct19v1_MC_2016_TTWH_MEM_SR_SF_v1.root";
	TString filename_ttZH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/ttVH/ntuple_Oct19v2_MC_2016_TTZH_MEM_SR_SF_v1.root";

	TString filename_ggHHTo2B2VTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/HH/ntuple_Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM_MEM_SR_SF_v1.root";
	TString filename_ggHHTo2B2Tau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/HH/ntuple_Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM_MEM_SR_SF_v1.root";
	TString filename_ggHHTo4Tau = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/HH/ntuple_Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM_MEM_SR_SF_v1.root";

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

	TString filename_norm_ggHHTo2B2VTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/HH/ntuple_Oct19v2_MC_2016_GluGluToHHTo2B2VTo2L2Nu_node_SM_norm.root";
	TString filename_norm_ggHHTo2B2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/HH/ntuple_Oct19v1_MC_2016_GluGluToHHTo2B2Tau_node_SM_norm.root";
	TString filename_norm_ggHHTo4Tau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2016/nominal/HH/ntuple_Oct19v1_MC_2016_GluGluToHHTo4Tau_node_SM_norm.root";

	///////////////////////////////////////////////////////

	TString filename_SingleElectron_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockF_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockG_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockG_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockH_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleElectron_BlockH_MEM_SR_SF_v1_noOverlap.root";

	TString filename_SingleMuon_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockF_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockG_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockG_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockH_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_SingleMuon_BlockH_MEM_SR_SF_v1_noOverlap.root";

	TString filename_DoubleEG_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockG_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockH_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_SR_SF_v1_noOverlap.root";

	TString filename_DoubleMu_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockG_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockH_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_SR_SF_v1_noOverlap.root";

	TString filename_MuonEG_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockG_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockH_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/SR/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_SR_SF_v1_noOverlap.root";

	///////////////////////////////////////////////////////

	TString filename_SingleElectron_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockF_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockG_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockG_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockH_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleElectron_BlockH_MEM_fake_SF_v2_noOverlap.root";

	TString filename_SingleMuon_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockF_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockG_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockG_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockH_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_SingleMuon_BlockH_MEM_fake_SF_v2_noOverlap.root";

	TString filename_DoubleEG_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockG_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockH_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_fake_SF_v2_noOverlap.root";

	TString filename_DoubleMu_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockG_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockH_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_fake_SF_v2_noOverlap.root";

	TString filename_MuonEG_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockG_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockH_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/fake/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_fake_SF_v2_noOverlap.root";

	///////////////////////////////////////////////////////

	TString filename_SingleElectron_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockF_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockG_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockG_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockH_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleElectron_BlockH_MEM_flip_SF_v2_noOverlap.root";

	TString filename_SingleMuon_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockF_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockG_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockG_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockH_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_SingleMuon_BlockH_MEM_flip_SF_v2_noOverlap.root";

	TString filename_DoubleEG_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockG_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockH_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_flip_SF_v2_noOverlap.root";

	TString filename_DoubleMu_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockG_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockH_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_flip_SF_v2_noOverlap.root";

	TString filename_MuonEG_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockF_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockG_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockG_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockH_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2016/nominal/Data/flip/ntuple_Oct19v1_Data_2016_DoubleEG_BlockH_MEM_flip_SF_v2_noOverlap.root";

	///////////////////////////////////////////////////////

	// ttH

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttH_s1");
	MC_sampletag.push_back("ttH");
	MC_samplegroup.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhww_s1");
	MC_sampletag.push_back("ttHhww");
	MC_samplegroup.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhzz_s1");
	MC_sampletag.push_back("ttHhzz");
	MC_samplegroup.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhtt_s1");
	MC_sampletag.push_back("ttHhtt");
	MC_samplegroup.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);*/

	///////////////////////////////////////////////////////

	// tHQ

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQ_s1");
	MC_sampletag.push_back("tHQ");
	MC_samplegroup.push_back("tHq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// tHW

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHW_s1");
	MC_sampletag.push_back("tHW");
	MC_samplegroup.push_back("tHq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// VH

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbb_s1");
	MC_sampletag.push_back("VHToNonbb");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTau_s1");
	MC_sampletag.push_back("ZHToTauTau");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLL_s1");
	MC_sampletag.push_back("ZHToBBZToLL");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttVH

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWH_s1");
	MC_sampletag.push_back("ttWH");
	MC_samplegroup.push_back("ttVH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZH_s1");
	MC_sampletag.push_back("ttZH");
	MC_samplegroup.push_back("ttVH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ggH

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTau_s1");
	MC_sampletag.push_back("ggHToTauTau");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ);
	MC_filename_norm.push_back(filename_norm_ggHToZZ);
	MC_samplename.push_back("ggHToZZ_s1");
	MC_sampletag.push_back("ggHToZZ");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQ_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQ");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nu");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMu_s1");
	MC_sampletag.push_back("ggHToMuMu");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBB_s1");
	MC_sampletag.push_back("ggHToBB");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGG_s1");
	MC_sampletag.push_back("ggHToGG");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// qqH

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTau_s1");
	MC_sampletag.push_back("VBFHToTauTau");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZ_s1");
	MC_sampletag.push_back("VBFHToZZ");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQ_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQ");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nu");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMu_s1");
	MC_sampletag.push_back("VBFHToMuMu");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBB_s1");
	MC_sampletag.push_back("VBFHToBB");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG_ext1);
	MC_filename_norm.push_back(filename_norm_VBFHToGG_ext1);
	MC_samplename.push_back("VBFHToGG_s1");
	MC_sampletag.push_back("VBFHToGG");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// HH

	MC_XS.push_back(XS_ggHHTo2B2VTo2L2Nu);
	MC_filename.push_back(filename_ggHHTo2B2VTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHHTo2B2VTo2L2Nu);
	MC_samplename.push_back("ggHHTo2B2VTo2L2Nu_s1");
	MC_sampletag.push_back("ggHHTo2B2VTo2L2Nu");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHHTo2B2Tau);
	MC_filename.push_back(filename_ggHHTo2B2Tau);
	MC_filename_norm.push_back(filename_norm_ggHHTo2B2Tau);
	MC_samplename.push_back("ggHHTo2B2Tau_s1");
	MC_sampletag.push_back("ggHHTo2B2Tau");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHHTo4Tau);
	MC_filename.push_back(filename_ggHHTo4Tau);
	MC_filename_norm.push_back(filename_norm_ggHHTo4Tau);
	MC_samplename.push_back("ggHHTo4Tau_s1");
	MC_sampletag.push_back("ggHHTo4Tau");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttZ

	/*MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ_ext2); 
	MC_filename_norm.push_back(filename_norm_ttZ_ext2);
	MC_samplename.push_back("ttZ_s2");
	MC_sampletag.push_back("ttZ");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ_ext3); 
	MC_filename_norm.push_back(filename_norm_ttZ_ext3);
	MC_samplename.push_back("ttZ_s1");
	MC_sampletag.push_back("ttZ");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ_lowmass);
	MC_filename.push_back(filename_ttZ_lowmass);
	MC_filename_norm.push_back(filename_norm_ttZ_lowmass);
	MC_samplename.push_back("ttZm1to10_s1");
	MC_sampletag.push_back("ttZm1to10");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_samplename.push_back("ttbarDL_s2");
	MC_sampletag.push_back("ttbarDL");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept_ext1); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept_ext1);
	MC_samplename.push_back("ttbarDL_s1");
	MC_sampletag.push_back("ttbarDL");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt);
	MC_samplename.push_back("ttbarSLfromT_s2");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt_ext1); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt_ext1);
	MC_samplename.push_back("ttbarSLfromT_s1");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar);
	MC_samplename.push_back("ttbarSLfromTbar_s2");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar_ext1); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar_ext1);
	MC_samplename.push_back("ttbarSLfromTbar_s1");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttW

	MC_XS.push_back(XS_ttW);
	MC_filename.push_back(filename_ttW);
	MC_filename_norm.push_back(filename_norm_ttW);
	MC_samplename.push_back("ttW_s1");
	MC_sampletag.push_back("ttW");
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// ttWW

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW);
	MC_filename_norm.push_back(filename_norm_ttWW);
	MC_samplename.push_back("ttWW_s1");
	MC_sampletag.push_back("ttWW");
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// WW

	MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW);
	MC_filename_norm.push_back(filename_norm_WW);
	MC_samplename.push_back("WW_s1");
	MC_sampletag.push_back("WW");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// WZ

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ);
	MC_filename_norm.push_back(filename_norm_WZ);
	MC_samplename.push_back("WZ_s1");
	MC_sampletag.push_back("WZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// ZZ

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ);
	MC_filename_norm.push_back(filename_norm_ZZ);
	MC_samplename.push_back("ZZ_s1");
	MC_sampletag.push_back("ZZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// Rares

	MC_XS.push_back(XS_WWW);
	MC_filename.push_back(filename_WWW);
	MC_filename_norm.push_back(filename_norm_WWW);
	MC_samplename.push_back("WWW_s1");
	MC_sampletag.push_back("WWW");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WWZ);
	MC_filename.push_back(filename_WWZ);
	MC_filename_norm.push_back(filename_norm_WWZ);
	MC_samplename.push_back("WWZ_s1");
	MC_sampletag.push_back("WWZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZZ);
	MC_filename.push_back(filename_WZZ);
	MC_filename_norm.push_back(filename_norm_WZZ);
	MC_samplename.push_back("WZZ_s1");
	MC_sampletag.push_back("WZZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZZ);
	MC_filename.push_back(filename_ZZZ);
	MC_filename_norm.push_back(filename_norm_ZZZ);
	MC_samplename.push_back("ZZZ_s1");
	MC_sampletag.push_back("ZZZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZG);
	MC_filename.push_back(filename_WZG);
	MC_filename_norm.push_back(filename_norm_WZG);
	MC_samplename.push_back("WZG_s1");
	MC_sampletag.push_back("WZG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG_ext1);
	MC_filename_norm.push_back(filename_norm_WG_ext1);
	MC_samplename.push_back("WG_s1");
	MC_sampletag.push_back("WG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG_ext2);
	MC_filename_norm.push_back(filename_norm_WG_ext2);
	MC_samplename.push_back("WG_s2");
	MC_sampletag.push_back("WG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	/*MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG_ext3);
	MC_filename_norm.push_back(filename_norm_WG_ext3);
	MC_samplename.push_back("WG_s3");
	MC_sampletag.push_back("WG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZG);
	MC_filename.push_back(filename_ZG);
	MC_filename_norm.push_back(filename_norm_ZG);
	MC_samplename.push_back("ZG_s1");
	MC_sampletag.push_back("ZG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tG);
	MC_filename.push_back(filename_tG);
	MC_filename_norm.push_back(filename_norm_tG);
	MC_samplename.push_back("tG_s1");
	MC_sampletag.push_back("tG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG);
	MC_filename_norm.push_back(filename_norm_ttG);
	MC_samplename.push_back("ttG_s1");
	MC_sampletag.push_back("ttG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG_ext1);
	MC_filename_norm.push_back(filename_norm_ttG_ext1);
	MC_samplename.push_back("ttG_s2");
	MC_sampletag.push_back("ttG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	/*MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq); 
	MC_filename_norm.push_back(filename_norm_tZq);
	MC_samplename.push_back("tZq_s2");
	MC_sampletag.push_back("tZq");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq_PS); 
	MC_filename_norm.push_back(filename_norm_tZq_PS);
	MC_samplename.push_back("tZq_s1");
	MC_sampletag.push_back("tZq");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WpWp);
	MC_filename.push_back(filename_WpWp); 
	MC_filename_norm.push_back(filename_norm_WpWp);
	MC_samplename.push_back("WpWp_s1");
	MC_sampletag.push_back("WpWp");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW_DS);
	MC_filename.push_back(filename_WW_DS); 
	MC_filename_norm.push_back(filename_norm_WW_DS);
	MC_samplename.push_back("WWss_s1");
	MC_sampletag.push_back("WWss");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt); 
	MC_filename_norm.push_back(filename_norm_tttt);
	MC_samplename.push_back("tttt_s1");
	MC_sampletag.push_back("tttt");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel); 
	MC_filename_norm.push_back(filename_norm_St_schannel);
	MC_samplename.push_back("TsCh_s1");
	MC_sampletag.push_back("TsCh");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel_PS); 
	MC_filename_norm.push_back(filename_norm_St_schannel_PS);
	MC_samplename.push_back("TsCh_s2");
	MC_sampletag.push_back("TsCh");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top);
	MC_samplename.push_back("TtChTop_s1");
	MC_sampletag.push_back("TtChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop);
	MC_samplename.push_back("TtChAntitop_s1");
	MC_sampletag.push_back("TtChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop_PS); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop_PS);
	MC_samplename.push_back("TtChAntitop_s2");
	MC_sampletag.push_back("TtChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top); 
	MC_filename_norm.push_back(filename_norm_St_tW_top);
	MC_samplename.push_back("TtwChTop_s1");
	MC_sampletag.push_back("TtwChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop);
	MC_samplename.push_back("TtwChAntitop_s1");
	MC_sampletag.push_back("TtwChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tWll);
	MC_filename.push_back(filename_St_tWll); 
	MC_filename_norm.push_back(filename_norm_St_tWll);
	MC_samplename.push_back("TtwChll_s1");
	MC_sampletag.push_back("TtwChll");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	Data_SR_filename.push_back(filename_SingleElectron_BlockB_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockC_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockD_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockE_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockF_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockG_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockH_SR);

	Data_SR_filename.push_back(filename_SingleMuon_BlockB_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockC_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockD_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockE_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockF_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockG_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockH_SR);

	Data_SR_filename.push_back(filename_DoubleEG_BlockB_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockC_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockD_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockE_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockF_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockG_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockH_SR);

	Data_SR_filename.push_back(filename_DoubleMu_BlockB_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockC_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockD_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockE_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockF_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockG_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockH_SR);

	Data_SR_filename.push_back(filename_MuonEG_BlockB_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockC_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockD_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockE_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockF_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockG_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockH_SR);

	///////////////////////////////////////////////////////

	Data_fake_filename.push_back(filename_SingleElectron_BlockB_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockC_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockD_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockE_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockF_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockG_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockH_fake);

	Data_fake_filename.push_back(filename_SingleMuon_BlockB_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockC_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockD_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockE_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockF_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockG_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockH_fake);

	Data_fake_filename.push_back(filename_DoubleEG_BlockB_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockC_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockD_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockE_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockF_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockG_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockH_fake);

	Data_fake_filename.push_back(filename_DoubleMu_BlockB_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockC_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockD_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockE_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockF_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockG_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockH_fake);

	Data_fake_filename.push_back(filename_MuonEG_BlockB_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockC_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockD_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockE_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockF_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockG_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockH_fake);

	///////////////////////////////////////////////////////

	Data_flip_filename.push_back(filename_SingleElectron_BlockB_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockC_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockD_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockE_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockF_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockG_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockH_flip);

	Data_flip_filename.push_back(filename_SingleMuon_BlockB_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockC_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockD_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockE_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockF_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockG_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockH_flip);

	Data_flip_filename.push_back(filename_DoubleEG_BlockB_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockC_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockD_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockE_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockF_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockG_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockH_flip);

	Data_flip_filename.push_back(filename_DoubleMu_BlockB_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockC_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockD_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockE_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockF_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockG_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockH_flip);

	Data_flip_filename.push_back(filename_MuonEG_BlockB_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockC_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockD_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockE_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockF_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockG_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockH_flip);

	///////////////////////////////////////////////////////

	return std::make_tuple(MC_XS, MC_filename, MC_filename_norm, MC_samplename, MC_samplecut, MC_sampletag, MC_samplegroup, MC_nsamples, MC_convs_samplecut, Data_SR_filename, Data_fake_filename, Data_flip_filename, luminosity);

}

std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, float > initialize_2017(){

	MC_XS.clear();

	MC_filename.clear();
	MC_filename_norm.clear();
	MC_samplename.clear();
	MC_samplecut.clear();
	MC_sampletag.clear();
	MC_samplegroup.clear();
	MC_nsamples.clear();
	MC_convs_samplecut.clear();

	Data_SR_filename.clear();
	Data_fake_filename.clear();
	Data_flip_filename.clear();

	luminosity = 41530;

	////////////////////////////////////////////////////////////

	TString filename_ttH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_ttHJetToNonbb_MEM_SR_SF_v1.root";
	TString filename_ttH_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_TTH_ctcvcp_MEM_SR_SF_v1.root";
	TString filename_tHQ_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttH/ntuple_Oct19v1_MC_2017_THQ_ctcvcp_MEM_SR_SF_v1.root";
	TString filename_tHW_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttH/ntuple_Oct19v3_MC_2017_THW_ctcvcp_MEM_SR_SF_v1.root";

	TString filename_ttZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_MEM_SR_SF_v1.root";
	TString filename_ttZ_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLLNuNu_M-10_PS_MEM_SR_SF_v1.root";
	TString filename_ttZ_lowmass = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTZToLL_M-1to10_MEM_SR_SF_v1.root";
	TString filename_ttW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_MEM_SR_SF_v1.root";
	TString filename_ttW_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWJetsToLNu_PS_MEM_SR_SF_v1.root";
	TString filename_ttWW = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttV/ntuple_Oct19v1_MC_2017_TTWW_MEM_SR_SF_v1.root";

	TString filename_WW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_WWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_WW_ext1 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_ext1_MEM_SR_SF_v1.root";
	TString filename_WZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WZTo3LNu_MEM_SR_SF_v1.root";
	TString filename_ZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_MEM_SR_SF_v1.root";
	TString filename_ZZ_ext1 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_ext1_MEM_SR_SF_v1.root";
	TString filename_ZZ_ext2 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_ZZTo4L_ext2_MEM_SR_SF_v1.root";

	TString filename_WWW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWW_MEM_SR_SF_v1.root";
	TString filename_WWZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWZ_MEM_SR_SF_v1.root";
	TString filename_WZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_WZZ_MEM_SR_SF_v1.root";
	TString filename_ZZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_ZZZ_MEM_SR_SF_v1.root";
	TString filename_WZG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WZG_MEM_SR_SF_v1.root";
	TString filename_WG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WGToLNuG_MEM_SR_SF_v1.root";
	TString filename_ZG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_ZGToLLG_MEM_SR_SF_v1.root";
	TString filename_tG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TGJets_MEM_SR_SF_v1.root";
	TString filename_ttG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTGJets_MEM_SR_SF_v1.root";
	TString filename_ttG_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTGJets_ext1_MEM_SR_SF_v1.root";
	TString filename_tZq = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_tZq_ll_MEM_SR_SF_v1.root";
	TString filename_WpWp = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v2_MC_2017_WpWpJJ_MEM_SR_SF_v1.root";
	TString filename_WW_DS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_DoubleScattering_MEM_SR_SF_v1.root";
	TString filename_tttt = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTTT_MEM_SR_SF_v1.root";
	TString filename_tttt_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Rares/ntuple_Oct19v1_MC_2017_TTTT_PS_MEM_SR_SF_v1.root";

	TString filename_St_schannel = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_s-channel_MEM_SR_SF_v1.root";
	TString filename_St_schannel_PS = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_s-channel_PS_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_top = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_t-channel_top_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_top_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_t-channel_top_PS_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_antitop = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_t-channel_antitop_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_antitop_PS = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v2_MC_2017_ST_t-channel_antitop_PS_MEM_SR_SF_v1.root";
	TString filename_St_tW_top = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v3_MC_2017_ST_tW_top_MEM_SR_SF_v1.root";
	TString filename_St_tW_top_PS = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_top_PS_MEM_SR_SF_v1.root";
	TString filename_St_tW_antitop = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_antitop_MEM_SR_SF_v1.root";
	TString filename_St_tW_antitop_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tW_antitop_PS_MEM_SR_SF_v1.root";
	TString filename_St_tWll = 					"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_ST_tWll_MEM_SR_SF_v1.root";

	TString filename_ttbar_DiLept = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_DiLept_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromt = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromT_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromtbar = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttbar/ntuple_Oct19v1_MC_2017_TTJets_SingleLeptFromTbar_MEM_SR_SF_v1.root";

	TString filename_ggHToTauTau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToTauTau_MEM_SR_SF_v1.root";
	TString filename_ggHToTauTau_ext1 = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToTauTau_ext1_MEM_SR_SF_v1.root";
	TString filename_ggHToZZ_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToZZTo4L_ext1_MEM_SR_SF_v1.root";
	TString filename_ggHToZZ_ext3 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToZZTo4L_ext3_MEM_SR_SF_v1.root";
	TString filename_ggHToZZ_ext4 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToZZTo4L_ext4_MEM_SR_SF_v1.root";
	TString filename_ggHToZZTo2L2Q = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToZZTo2L2Q_MEM_SR_SF_v1.root";
	TString filename_ggHToWWToLNuQQ = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToWWToLNuQQ_MEM_SR_SF_v1.root";
	TString filename_ggHToWWTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToWWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_ggHToMuMu = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToMuMu_MEM_SR_SF_v1.root";
	TString filename_ggHToMuMu_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v1_MC_2017_GluGluHToMuMu_ext1_MEM_SR_SF_v1.root";
	TString filename_ggHToBB = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToBB_MEM_SR_SF_v1.root";
	TString filename_ggHToGG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ggH/ntuple_Oct19v3_MC_2017_GluGluHToGG_MEM_SR_SF_v1.root";

	TString filename_VBFHToTauTau = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToTauTau_MEM_SR_SF_v1.root";
	TString filename_VBFHToZZ = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBF_HToZZTo4L_MEM_SR_SF_v1.root";
	TString filename_VBFHToZZ_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBF_HToZZTo4L_ext1_MEM_SR_SF_v1.root";
	TString filename_VBFHToZZ_ext2 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v2_MC_2017_VBF_HToZZTo4L_ext2_MEM_SR_SF_v1.root";
	TString filename_VBFHToWWToLNuQQ = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToWWToLNuQQ_MEM_SR_SF_v1.root";
	TString filename_VBFHToWWTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToWWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_VBFHToMuMu = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToMuMu_MEM_SR_SF_v1.root";
	TString filename_VBFHToBB = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToBB_MEM_SR_SF_v1.root";
	TString filename_VBFHToGG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v1_MC_2017_VBFHToGG_MEM_SR_SF_v1.root";
	TString filename_VBFHToGG_PS = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VBF/ntuple_Oct19v2_MC_2017_VBFHToGG_PS_MEM_SR_SF_v1.root";

	TString filename_VHToNonbb = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VH/ntuple_Oct19v1_MC_2017_VHToNonbb_MEM_SR_SF_v1.root";
	TString filename_ZHToTauTau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VH/ntuple_Oct19v1_MC_2017_ZHToTauTau_MEM_SR_SF_v1.root";
	TString filename_ZH_HToBB_ZToLL = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/VH/ntuple_Oct19v1_MC_2017_ZH_HToBB_ZToLL_MEM_SR_SF_v1.root";

	TString filename_ttWH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttVH/ntuple_Oct19v4_MC_2017_TTWH_MEM_SR_SF_v1.root";
	TString filename_ttZH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/ttVH/ntuple_Oct19v1_MC_2017_TTZH_MEM_SR_SF_v1.root";

	TString filename_ggHHTo2B2VTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM_MEM_SR_SF_v1.root";
	TString filename_ggHHTo2B2Tau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM_MEM_SR_SF_v1.root";
	TString filename_ggHHTo4Tau = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13_MEM_SR_SF_v1.root";
	TString filename_ggHHTo2V2Tau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM_MEM_SR_SF_v1.root";
	TString filename_ggHHTo4V = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4V_node_SM_MEM_SR_SF_v1.root";

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

	TString filename_norm_WW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_WWTo2L2Nu_norm.root";
	TString filename_norm_WW_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WWTo2L2Nu_ext1_norm.root";
	TString filename_norm_WZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_WZTo3LNu_norm.root";
	TString filename_norm_ZZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_norm.root";
	TString filename_norm_ZZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v1_MC_2017_ZZTo4L_ext1_norm.root";
	TString filename_norm_ZZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/EWK/ntuple_Oct19v2_MC_2017_ZZTo4L_ext2_norm.root";

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
	TString filename_norm_ggHToZZTo2L2Q = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ggH/ntuple_Oct19v2_MC_2017_GluGluHToZZTo2L2Q_norm.root";
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
	
	TString filename_norm_ttWH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttVH/ntuple_Oct19v4_MC_2017_TTWH_norm.root";
	TString filename_norm_ttZH = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/ttVH/ntuple_Oct19v1_MC_2017_TTZH_norm.root";

	TString filename_norm_ggHHTo2B2VTo2L2Nu = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2B2VTo2L2Nu_node_SM_norm.root";
	TString filename_norm_ggHHTo2B2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo2B2Tau_node_SM_norm.root";
	TString filename_norm_ggHHTo4Tau = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4Tau_node_SM_13_norm.root";
	TString filename_norm_ggHHTo2V2Tau = 		"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v2_MC_2017_GluGluToHHTo2V2Tau_node_SM_norm.root";
	TString filename_norm_ggHHTo4V = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2017/nominal/HH/ntuple_Oct19v1_MC_2017_GluGluToHHTo4V_node_SM_norm.root";

	////////////////////////////////////////////////////////////

	TString filename_SingleElectron_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleElectron_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleElectron_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleElectron_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleElectron_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleElectron_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleElectron_BlockF_MEM_SR_SF_v1_noOverlap.root";

	TString filename_SingleMuon_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleMuon_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleMuon_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleMuon_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleMuon_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_SingleMuon_BlockF_MEM_SR_SF_v1_noOverlap.root";

	TString filename_DoubleEG_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleEG_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_SR_SF_v1_noOverlap.root";

	TString filename_DoubleMu_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_SR_SF_v1_noOverlap.root";

	TString filename_MuonEG_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockE_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockF_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/SR/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_SR_SF_v1_noOverlap.root";

	////////////////////////////////////////////////////////////

	TString filename_SingleElectron_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleElectron_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleElectron_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleElectron_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleElectron_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleElectron_BlockF_MEM_fake_SF_v2_noOverlap.root";

	TString filename_SingleMuon_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleMuon_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleMuon_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleMuon_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleMuon_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_SingleMuon_BlockF_MEM_fake_SF_v2_noOverlap.root";

	TString filename_DoubleEG_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_fake_SF_v2_noOverlap.root";

	TString filename_DoubleMu_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_fake_SF_v2_noOverlap.root";

	TString filename_MuonEG_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockE_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockF_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/fake/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_fake_SF_v2_noOverlap.root";

	////////////////////////////////////////////////////////////

	TString filename_SingleElectron_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleElectron_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleElectron_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleElectron_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleElectron_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleElectron_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleElectron_BlockF_MEM_flip_SF_v2_noOverlap.root";

	TString filename_SingleMuon_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleMuon_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleMuon_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleMuon_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleMuon_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_SingleMuon_BlockF_MEM_flip_SF_v2_noOverlap.root";

	TString filename_DoubleEG_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleEG_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_flip_SF_v2_noOverlap.root";

	TString filename_DoubleMu_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_flip_SF_v2_noOverlap.root";

	TString filename_MuonEG_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockD_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockE_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockE_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockF_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2017/nominal/Data/flip/ntuple_Oct19v1_Data_2017_DoubleEG_BlockF_MEM_flip_SF_v2_noOverlap.root";

	////////////////////////////////////////////////////////////

	// ttH

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttH_s1");
	MC_sampletag.push_back("ttH");
	MC_samplegroup.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhww_s1");
	MC_sampletag.push_back("ttHhww");
	MC_samplegroup.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhzz_s1");
	MC_sampletag.push_back("ttHhzz");
	MC_samplegroup.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhtt_s1");
	MC_sampletag.push_back("ttHhtt");
	MC_samplegroup.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);*/

	///////////////////////////////////////////////////////

	// tHQ

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQ_s1");
	MC_sampletag.push_back("tHQ");
	MC_samplegroup.push_back("tHq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// tHW

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHW_s1");
	MC_sampletag.push_back("tHW");
	MC_samplegroup.push_back("tHq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// VH

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbb_s1");
	MC_sampletag.push_back("VHToNonbb");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTau_s1");
	MC_sampletag.push_back("ZHToTauTau");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("HToBBZToLL_s1");
	MC_sampletag.push_back("ZHToBBZToLL");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttVH

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWH_s1");
	MC_sampletag.push_back("ttWH");
	MC_samplegroup.push_back("ttVH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZH_s1");
	MC_sampletag.push_back("ttZH");
	MC_samplegroup.push_back("ttVH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ggH

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTau_s1");
	MC_sampletag.push_back("ggHToTauTau");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ggHToZZ_ext1);
	MC_samplename.push_back("ggHToZZ_s1");
	MC_sampletag.push_back("ggHToZZ");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToZZTo2L2Q);
	MC_filename.push_back(filename_ggHToZZTo2L2Q);
	MC_filename_norm.push_back(filename_norm_ggHToZZTo2L2Q);
	MC_samplename.push_back("ggHToZZTo2L2Q_s1");
	MC_sampletag.push_back("ggHToZZTo2L2Q");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQ_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQ");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nu");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMu_s1");
	MC_sampletag.push_back("ggHToMuMu");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBB_s1");
	MC_sampletag.push_back("ggHToBB");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGG_s1");
	MC_sampletag.push_back("ggHToGG");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// qqH

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTau_s1");
	MC_sampletag.push_back("VBFHToTauTau");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZ_s1");
	MC_sampletag.push_back("VBFHToZZ");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQ_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQ");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nu");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMu_s1");
	MC_sampletag.push_back("VBFHToMuMu");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBB_s1");
	MC_sampletag.push_back("VBFHToBB");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGG_s1");
	MC_sampletag.push_back("VBFHToGG");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// HH

	MC_XS.push_back(XS_ggHHTo2B2VTo2L2Nu);
	MC_filename.push_back(filename_ggHHTo2B2VTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHHTo2B2VTo2L2Nu);
	MC_samplename.push_back("ggHHTo2B2VTo2L2Nu_s1");
	MC_sampletag.push_back("ggHHTo2B2VTo2L2Nu");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHHTo2B2Tau);
	MC_filename.push_back(filename_ggHHTo2B2Tau);
	MC_filename_norm.push_back(filename_norm_ggHHTo2B2Tau);
	MC_samplename.push_back("ggHHTo2B2Tau_s1");
	MC_sampletag.push_back("ggHHTo2B2Tau");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHHTo4Tau);
	MC_filename.push_back(filename_ggHHTo4Tau);
	MC_filename_norm.push_back(filename_norm_ggHHTo4Tau);
	MC_samplename.push_back("ggHHTo4Tau_s1");
	MC_sampletag.push_back("ggHHTo4Tau");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHHTo2V2Tau);
	MC_filename.push_back(filename_ggHHTo2V2Tau);
	MC_filename_norm.push_back(filename_norm_ggHHTo2V2Tau);
	MC_samplename.push_back("ggHHTo2V2Tau_s1");
	MC_sampletag.push_back("ggHHTo2V2Tau");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHHTo4V);
	MC_filename.push_back(filename_ggHHTo4V);
	MC_filename_norm.push_back(filename_norm_ggHHTo4V);
	MC_samplename.push_back("ggHHTo4V_s1");
	MC_sampletag.push_back("ggHHTo4V");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttZ

	/*MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ); 
	MC_filename_norm.push_back(filename_norm_ttZ);
	MC_samplename.push_back("ttZ_s2");
	MC_sampletag.push_back("ttZ");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ_PS); 
	MC_filename_norm.push_back(filename_norm_ttZ_PS);
	MC_samplename.push_back("ttZ_s1");
	MC_sampletag.push_back("ttZ");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ_lowmass);
	MC_filename.push_back(filename_ttZ_lowmass);
	MC_filename_norm.push_back(filename_norm_ttZ_lowmass);
	MC_samplename.push_back("ttZm1to10_s1");
	MC_sampletag.push_back("ttZm1to10");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_samplename.push_back("ttbarDL_s1");
	MC_sampletag.push_back("ttbarDL");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt);
	MC_samplename.push_back("ttbarSLfromT_s1");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar);
	MC_samplename.push_back("ttbarSLfromTbar_s1");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_samplegroup.push_back("ttZ");
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
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttW);
	MC_filename.push_back(filename_ttW_PS);
	MC_filename_norm.push_back(filename_norm_ttW_PS);
	MC_samplename.push_back("ttW_s2");
	MC_sampletag.push_back("ttW");
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	// ttWW

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW);
	MC_filename_norm.push_back(filename_norm_ttWW);
	MC_samplename.push_back("ttWW_s1");
	MC_sampletag.push_back("ttWW");
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// WW

	MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW);
	MC_filename_norm.push_back(filename_norm_WW);
	MC_samplename.push_back("WW_s1");
	MC_sampletag.push_back("WW");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW_ext1);
	MC_filename_norm.push_back(filename_norm_WW_ext1);
	MC_samplename.push_back("WW_s2");
	MC_sampletag.push_back("WW");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	// WZ

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ);
	MC_filename_norm.push_back(filename_norm_WZ);
	MC_samplename.push_back("WZ_s1");
	MC_sampletag.push_back("WZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// ZZ

	/*MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ);
	MC_filename_norm.push_back(filename_norm_ZZ);
	MC_samplename.push_back("ZZ_s2");
	MC_sampletag.push_back("ZZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ_ext1);
	MC_filename_norm.push_back(filename_norm_ZZ_ext1);
	MC_samplename.push_back("ZZ_s1");
	MC_sampletag.push_back("ZZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ_ext2);
	MC_filename_norm.push_back(filename_norm_ZZ_ext2);
	MC_samplename.push_back("ZZ_s3");
	MC_sampletag.push_back("ZZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(3);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	///////////////////////////////////////////////////////

	// Rares

	MC_XS.push_back(XS_WWW);
	MC_filename.push_back(filename_WWW);
	MC_filename_norm.push_back(filename_norm_WWW);
	MC_samplename.push_back("WWW_s1");
	MC_sampletag.push_back("WWW");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WWZ);
	MC_filename.push_back(filename_WWZ);
	MC_filename_norm.push_back(filename_norm_WWZ);
	MC_samplename.push_back("WWZ_s1");
	MC_sampletag.push_back("WWZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZZ);
	MC_filename.push_back(filename_WZZ);
	MC_filename_norm.push_back(filename_norm_WZZ);
	MC_samplename.push_back("WZZ_s1");
	MC_sampletag.push_back("WZZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZZ);
	MC_filename.push_back(filename_ZZZ);
	MC_filename_norm.push_back(filename_norm_ZZZ);
	MC_samplename.push_back("ZZZ_s1");
	MC_sampletag.push_back("ZZZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZG);
	MC_filename.push_back(filename_WZG);
	MC_filename_norm.push_back(filename_norm_WZG);
	MC_samplename.push_back("WZG_s1");
	MC_sampletag.push_back("WZG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG);
	MC_filename_norm.push_back(filename_norm_WG);
	MC_samplename.push_back("WG_s1");
	MC_sampletag.push_back("WG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZG);
	MC_filename.push_back(filename_ZG);
	MC_filename_norm.push_back(filename_norm_ZG);
	MC_samplename.push_back("ZG_s1");
	MC_sampletag.push_back("ZG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tG);
	MC_filename.push_back(filename_tG);
	MC_filename_norm.push_back(filename_norm_tG);
	MC_samplename.push_back("tG_s1");
	MC_sampletag.push_back("tG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG);
	MC_filename_norm.push_back(filename_norm_ttG);
	MC_samplename.push_back("ttG_s2");
	MC_sampletag.push_back("ttG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG_ext1);
	MC_filename_norm.push_back(filename_norm_ttG_ext1);
	MC_samplename.push_back("ttG_s1");
	MC_sampletag.push_back("ttG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq); 
	MC_filename_norm.push_back(filename_norm_tZq);
	MC_samplename.push_back("tZq_s1");
	MC_sampletag.push_back("tZq");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WpWp);
	MC_filename.push_back(filename_WpWp); 
	MC_filename_norm.push_back(filename_norm_WpWp);
	MC_samplename.push_back("WpWp_s1");
	MC_sampletag.push_back("WpWp");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW_DS);
	MC_filename.push_back(filename_WW_DS); 
	MC_filename_norm.push_back(filename_norm_WW_DS);
	MC_samplename.push_back("WWss_s1");
	MC_sampletag.push_back("WWss");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt); 
	MC_filename_norm.push_back(filename_norm_tttt);
	MC_samplename.push_back("tttt_s1");
	MC_sampletag.push_back("tttt");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt_PS); 
	MC_filename_norm.push_back(filename_norm_tttt_PS);
	MC_samplename.push_back("tttt_s2");
	MC_sampletag.push_back("tttt");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel); 
	MC_filename_norm.push_back(filename_norm_St_schannel);
	MC_samplename.push_back("TsCh_s1");
	MC_sampletag.push_back("TsCh");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel_PS); 
	MC_filename_norm.push_back(filename_norm_St_schannel_PS);
	MC_samplename.push_back("TsCh_s2");
	MC_sampletag.push_back("TsCh");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top);
	MC_samplename.push_back("TtChTop_s1");
	MC_sampletag.push_back("TtChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top_PS); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top_PS);
	MC_samplename.push_back("TtChTop_s2");
	MC_sampletag.push_back("TtChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop);
	MC_samplename.push_back("TtChAntitop_s1");
	MC_sampletag.push_back("TtChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop_PS); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop_PS);
	MC_samplename.push_back("TtChAntitop_s2");
	MC_sampletag.push_back("TtChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top); 
	MC_filename_norm.push_back(filename_norm_St_tW_top);
	MC_samplename.push_back("TtwChTop_s1");
	MC_sampletag.push_back("TtwChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top_PS); 
	MC_filename_norm.push_back(filename_norm_St_tW_top_PS);
	MC_samplename.push_back("TtwChTop_s2");
	MC_sampletag.push_back("TtwChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop);
	MC_samplename.push_back("TtwChAntitop_s1");
	MC_sampletag.push_back("TtwChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop_PS); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop_PS);
	MC_samplename.push_back("TtwChAntitop_s2");
	MC_sampletag.push_back("TtwChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_St_tWll);
	MC_filename.push_back(filename_St_tWll); 
	MC_filename_norm.push_back(filename_norm_St_tWll);
	MC_samplename.push_back("TtwChll_s1");
	MC_sampletag.push_back("TtwChll");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	Data_SR_filename.push_back(filename_SingleElectron_BlockB_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockC_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockD_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockE_SR);
	Data_SR_filename.push_back(filename_SingleElectron_BlockF_SR);

	Data_SR_filename.push_back(filename_SingleMuon_BlockB_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockC_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockD_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockE_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockF_SR);

	Data_SR_filename.push_back(filename_DoubleEG_BlockB_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockC_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockD_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockE_SR);
	Data_SR_filename.push_back(filename_DoubleEG_BlockF_SR);

	Data_SR_filename.push_back(filename_DoubleMu_BlockB_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockC_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockD_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockE_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockF_SR);

	Data_SR_filename.push_back(filename_MuonEG_BlockB_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockC_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockD_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockE_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockF_SR);

	///////////////////////////////////////////////////////

	Data_fake_filename.push_back(filename_SingleElectron_BlockB_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockC_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockD_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockE_fake);
	Data_fake_filename.push_back(filename_SingleElectron_BlockF_fake);

	Data_fake_filename.push_back(filename_SingleMuon_BlockB_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockC_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockD_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockE_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockF_fake);

	Data_fake_filename.push_back(filename_DoubleEG_BlockB_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockC_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockD_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockE_fake);
	Data_fake_filename.push_back(filename_DoubleEG_BlockF_fake);

	Data_fake_filename.push_back(filename_DoubleMu_BlockB_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockC_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockD_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockE_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockF_fake);

	Data_fake_filename.push_back(filename_MuonEG_BlockB_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockC_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockD_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockE_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockF_fake);

	///////////////////////////////////////////////////////

	Data_flip_filename.push_back(filename_SingleElectron_BlockB_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockC_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockD_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockE_flip);
	Data_flip_filename.push_back(filename_SingleElectron_BlockF_flip);

	Data_flip_filename.push_back(filename_SingleMuon_BlockB_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockC_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockD_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockE_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockF_flip);

	Data_flip_filename.push_back(filename_DoubleEG_BlockB_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockC_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockD_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockE_flip);
	Data_flip_filename.push_back(filename_DoubleEG_BlockF_flip);

	Data_flip_filename.push_back(filename_DoubleMu_BlockB_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockC_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockD_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockE_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockF_flip);

	Data_flip_filename.push_back(filename_MuonEG_BlockB_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockC_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockD_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockE_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockF_flip);

	///////////////////////////////////////////////////////

	return std::make_tuple(MC_XS, MC_filename, MC_filename_norm, MC_samplename, MC_samplecut, MC_sampletag, MC_samplegroup, MC_nsamples, MC_convs_samplecut, Data_SR_filename, Data_fake_filename, Data_flip_filename, luminosity);

}


std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, float > initialize_2018(){

	MC_XS.clear();

	MC_filename.clear();
	MC_filename_norm.clear();
	MC_samplename.clear();
	MC_samplecut.clear();
	MC_sampletag.clear();
	MC_samplegroup.clear();
	MC_nsamples.clear();
	MC_convs_samplecut.clear();

	Data_SR_filename.clear();
	Data_fake_filename.clear();
	Data_flip_filename.clear();

	luminosity = 59740;

	////////////////////////////////////////////////////////////

	TString filename_ttH = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_ttHJetToNonbb_MEM_SR_SF_v1.root";
	TString filename_ttH_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttH/ntuple_Oct19v2_MC_2018_TTH_ctcvcp_MEM_SR_SF_v1.root";
	TString filename_tHQ_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THQ_ctcvcp_MEM_SR_SF_v1.root";
	TString filename_tHW_ctcvcp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttH/ntuple_Oct19v1_MC_2018_THW_ctcvcp_MEM_SR_SF_v1.root";

	TString filename_ttZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLLNuNu_M-10_MEM_SR_SF_v1.root";
	TString filename_ttZ_lowmass = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTZToLL_M-1to10_MEM_SR_SF_v1.root";
	TString filename_ttW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWJetsToLNu_MEM_SR_SF_v1.root";
	TString filename_ttWW_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWW_ext1_MEM_SR_SF_v1.root";
	TString filename_ttWW_ext2 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttV/ntuple_Oct19v1_MC_2018_TTWW_ext2_MEM_SR_SF_v1.root";

	TString filename_WW = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_WWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_WZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/EWK/ntuple_Oct19v1_MC_2018_WZTo3LNu_MEM_SR_SF_v1.root";
	TString filename_WZ_ext1 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_WZTo3LNu_ext1_MEM_SR_SF_v1.root";
	TString filename_ZZ = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_ZZTo4L_MEM_SR_SF_v1.root";
	TString filename_ZZ_ext2 = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/EWK/ntuple_Oct19v4_MC_2018_ZZTo4L_ext2_MEM_SR_SF_v1.root";

	TString filename_WWW = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_WWW_MEM_SR_SF_v1.root";
	TString filename_WWZ = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_WWZ_MEM_SR_SF_v1.root";
	TString filename_WZZ = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WZZ_MEM_SR_SF_v1.root";
	TString filename_ZZZ = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_ZZZ_MEM_SR_SF_v1.root";
	TString filename_WZG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WZG_MEM_SR_SF_v1.root";
	TString filename_WG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WGToLNuG_MEM_SR_SF_v1.root";
	TString filename_ZG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v2_MC_2018_ZGToLLG_MEM_SR_SF_v1.root";
	TString filename_tG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TGJets_MEM_SR_SF_v1.root";
	TString filename_ttG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TTGJets_MEM_SR_SF_v1.root";
	TString filename_tZq = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_tZq_ll_MEM_SR_SF_v1.root";
	TString filename_WpWp = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WpWpJJ_MEM_SR_SF_v1.root";
	TString filename_WW_DS = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_WWTo2L2Nu_DoubleScattering_MEM_SR_SF_v1.root";
	TString filename_tttt = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Rares/ntuple_Oct19v1_MC_2018_TTTT_MEM_SR_SF_v1.root";

	TString filename_St_schannel = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_s-channel_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_top = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_ST_t-channel_top_MEM_SR_SF_v1.root";
	TString filename_St_tchannel_antitop = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v3_MC_2018_ST_t-channel_antitop_MEM_SR_SF_v1.root";
	TString filename_St_tW_top = 				"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v3_MC_2018_ST_tW_top_MEM_SR_SF_v1.root";
	TString filename_St_tW_antitop = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_tW_antitop_MEM_SR_SF_v1.root";
	TString filename_St_tWll = 					"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_ST_tWll_MEM_SR_SF_v1.root";

	TString filename_ttbar_DiLept = 					"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_DiLept_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromt = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v1_MC_2018_TTJets_SingleLeptFromT_MEM_SR_SF_v1.root";
	TString filename_ttbar_SingleLeptFromtbar = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttbar/ntuple_Oct19v2_MC_2018_TTJets_SingleLeptFromTbar_MEM_SR_SF_v1.root";

	TString filename_ggHToTauTau = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToTauTau_MEM_SR_SF_v1.root";
	TString filename_ggHToZZ4l = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToZZTo4L_MEM_SR_SF_v1.root";
	TString filename_ggHToZZ2l2Q = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToZZTo2L2Q_MEM_SR_SF_v1.root";
	TString filename_ggHToWWToLNuQQ = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToWWToLNuQQ_MEM_SR_SF_v1.root";
	TString filename_ggHToZZTo2L2Q = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToZZTo2L2Q_MEM_SR_SF_v1.root";
	TString filename_ggHToWWTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToWWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_ggHToMuMu = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToMuMu_MEM_SR_SF_v1.root";
	TString filename_ggHToMuMu_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToMuMu_ext1_MEM_SR_SF_v1.root";
	TString filename_ggHToBB = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToBB_MEM_SR_SF_v1.root";
	TString filename_ggHToGG = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ggH/ntuple_Oct19v1_MC_2018_GluGluHToGG_MEM_SR_SF_v1.root";

	TString filename_VBFHToTauTau = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToTauTau_MEM_SR_SF_v1.root";
	TString filename_VBFHToZZ = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBF_HToZZTo4L_MEM_SR_SF_v1.root";
	TString filename_VBFHToWWToLNuQQ = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToWWToLNuQQ_MEM_SR_SF_v1.root";
	TString filename_VBFHToWWTo2L2Nu = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToWWTo2L2Nu_MEM_SR_SF_v1.root";
	TString filename_VBFHToMuMu = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v1_MC_2018_VBFHToMuMu_MEM_SR_SF_v1.root";
	TString filename_VBFHToBB = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToBB_MEM_SR_SF_v1.root";
	TString filename_VBFHToGG = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VBF/ntuple_Oct19v2_MC_2018_VBFHToGG_MEM_SR_SF_v1.root";

	TString filename_VHToNonbb = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VH/ntuple_Oct19v2_MC_2018_VHToNonbb_MEM_SR_SF_v1.root";
	TString filename_ZHToTauTau = 			"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VH/ntuple_Oct19v2_MC_2018_ZHToTauTau_MEM_SR_SF_v1.root";
	TString filename_ZH_HToBB_ZToLL = 		"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VH/ntuple_Oct19v1_MC_2018_ZH_HToBB_ZToLL_MEM_SR_SF_v1.root";
	TString filename_ZH_HToBB_ZToLL_ext1 = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/VH/ntuple_Oct19v3_MC_2018_ZH_HToBB_ZToLL_ext1_MEM_SR_SF_v1.root";

	TString filename_ttWH = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttVH/ntuple_Oct19v1_MC_2018_TTWH_MEM_SR_SF_v1.root";
	TString filename_ttZH = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/ttVH/ntuple_Oct19v2_MC_2018_TTZH_MEM_SR_SF_v1.root";

	TString filename_ggHHTo2B2Tau = 	"/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/HH/ntuple_Oct19v2_MC_2018_GluGluToHHTo2B2Tau_node_SM_MEM_SR_SF_v1.root";

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

	TString filename_norm_WW = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v3_MC_2018_WWTo2L2Nu_norm.root";
	TString filename_norm_WZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v1_MC_2018_WZTo3LNu_norm.root";
	TString filename_norm_WZ_ext1 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_WZTo3LNu_ext1_norm.root";
	TString filename_norm_ZZ = 			"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v2_MC_2018_ZZTo4L_norm.root";
	TString filename_norm_ZZ_ext2 = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/EWK/ntuple_Oct19v4_MC_2018_ZZTo4L_ext2_norm.root";

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
	TString filename_norm_ggHToZZTo2L2Q = 	"/data_CMS/cms/mperez/ttH_Legacy/Oct19/ntuples_normalized/2018/nominal/ggH/ntuple_Oct19v2_MC_2018_GluGluHToZZTo2L2Q_norm.root";
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

	TString filename_EGamma_BlockA_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_EGamma_BlockA_MEM_SR_SF_v1_noOverlap.root";
	TString filename_EGamma_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_EGamma_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_EGamma_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_EGamma_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_EGamma_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_EGamma_BlockD_MEM_SR_SF_v1_noOverlap.root";

	TString filename_SingleMuon_BlockA_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_SingleMuon_BlockA_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_SingleMuon_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_SingleMuon_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_SingleMuon_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_SingleMuon_BlockD_MEM_SR_SF_v1_noOverlap.root";
	
	TString filename_DoubleMu_BlockA_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_DoubleMu_BlockA_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_DoubleMu_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_DoubleMu_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_DoubleMu_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_DoubleMu_BlockD_MEM_SR_SF_v1_noOverlap.root";

	TString filename_MuonEG_BlockA_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_MuonEG_BlockA_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockB_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_MuonEG_BlockB_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockC_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_MuonEG_BlockC_MEM_SR_SF_v1_noOverlap.root";
	TString filename_MuonEG_BlockD_SR = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/SR/ntuple_Oct19v1_Data_2018_MuonEG_BlockD_MEM_SR_SF_v1_noOverlap.root";

	///////////////////////////////////////////////////////

	TString filename_EGamma_BlockA_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_EGamma_BlockA_MEM_fake_SF_v2_noOverlap.root";
	TString filename_EGamma_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_EGamma_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_EGamma_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_EGamma_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_EGamma_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_EGamma_BlockD_MEM_fake_SF_v2_noOverlap.root";

	TString filename_SingleMuon_BlockA_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_SingleMuon_BlockA_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_SingleMuon_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_SingleMuon_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_SingleMuon_BlockD_MEM_fake_SF_v2_noOverlap.root";
	
	TString filename_DoubleMu_BlockA_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_DoubleMu_BlockA_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_DoubleMu_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_DoubleMu_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_DoubleMu_BlockD_MEM_fake_SF_v2_noOverlap.root";

	TString filename_MuonEG_BlockA_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_MuonEG_BlockA_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockB_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_MuonEG_BlockB_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockC_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_MuonEG_BlockC_MEM_fake_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockD_fake = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/fake/ntuple_Oct19v1_Data_2018_MuonEG_BlockD_MEM_fake_SF_v2_noOverlap.root";

	///////////////////////////////////////////////////////

	TString filename_EGamma_BlockA_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_EGamma_BlockA_MEM_flip_SF_v2_noOverlap.root";
	TString filename_EGamma_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_EGamma_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_EGamma_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_EGamma_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_EGamma_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_EGamma_BlockD_MEM_flip_SF_v2_noOverlap.root";

	TString filename_SingleMuon_BlockA_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_SingleMuon_BlockA_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_SingleMuon_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_SingleMuon_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_SingleMuon_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_SingleMuon_BlockD_MEM_flip_SF_v2_noOverlap.root";
	
	TString filename_DoubleMu_BlockA_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_DoubleMu_BlockA_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_DoubleMu_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_DoubleMu_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_DoubleMu_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_DoubleMu_BlockD_MEM_flip_SF_v2_noOverlap.root";

	TString filename_MuonEG_BlockA_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_MuonEG_BlockA_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockB_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_MuonEG_BlockB_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockC_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_MuonEG_BlockC_MEM_flip_SF_v2_noOverlap.root";
	TString filename_MuonEG_BlockD_flip = "/data_CMPerez/mperez/ttH_Legacy/ntuples_datacards/2018/nominal/Data/flip/ntuple_Oct19v1_Data_2018_MuonEG_BlockD_MEM_flip_SF_v2_noOverlap.root";

	///////////////////////////////////////////////////////

	// ttH

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttH_s1");
	MC_sampletag.push_back("ttH");
	MC_samplegroup.push_back("ttH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	/*MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhww_s1");
	MC_sampletag.push_back("ttHhww");
	MC_samplegroup.push_back("ttHhww");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hww);
	MC_convs_samplecut.push_back(conversmatch+" && "+hww);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhzz_s1");
	MC_sampletag.push_back("ttHhzz");
	MC_samplegroup.push_back("ttHhzz");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+hzz);
	MC_convs_samplecut.push_back(conversmatch+" && "+hzz);

	MC_XS.push_back(XS_ttH);
	MC_filename.push_back(filename_ttH);
	MC_filename_norm.push_back(filename_norm_ttH);
	MC_samplename.push_back("ttHhtt_s1");
	MC_sampletag.push_back("ttHhtt");
	MC_samplegroup.push_back("ttHhtt");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch+" && "+htt);
	MC_convs_samplecut.push_back(conversmatch+" && "+htt);*/

	///////////////////////////////////////////////////////

	// tHQ

	MC_XS.push_back(XS_tHQ_ctcvcp);
	MC_filename.push_back(filename_tHQ_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHQ_ctcvcp);
	MC_samplename.push_back("tHQ_s1");
	MC_sampletag.push_back("tHQ");
	MC_samplegroup.push_back("tHq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// tHW

	MC_XS.push_back(XS_tHW_ctcvcp);
	MC_filename.push_back(filename_tHW_ctcvcp);
	MC_filename_norm.push_back(filename_norm_tHW_ctcvcp);
	MC_samplename.push_back("tHW_s1");
	MC_sampletag.push_back("tHW");
	MC_samplegroup.push_back("tHq");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// VH

	MC_XS.push_back(XS_VHToNonbb);
	MC_filename.push_back(filename_VHToNonbb);
	MC_filename_norm.push_back(filename_norm_VHToNonbb);
	MC_samplename.push_back("VHToNonbb_s1");
	MC_sampletag.push_back("VHToNonbb");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZHToTauTau);
	MC_filename.push_back(filename_ZHToTauTau);
	MC_filename_norm.push_back(filename_norm_ZHToTauTau);
	MC_samplename.push_back("ZHToTauTau_s1");
	MC_sampletag.push_back("ZHToTauTau");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZH_HToBB_ZToLL);
	MC_filename.push_back(filename_ZH_HToBB_ZToLL);
	MC_filename_norm.push_back(filename_norm_ZH_HToBB_ZToLL);
	MC_samplename.push_back("ZHToBBZToLL_s1");
	MC_sampletag.push_back("ZHToBBZToLL");
	MC_samplegroup.push_back("VH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttVH

	MC_XS.push_back(XS_ttWH);
	MC_filename.push_back(filename_ttWH);
	MC_filename_norm.push_back(filename_norm_ttWH);
	MC_samplename.push_back("ttWH_s1");
	MC_sampletag.push_back("ttWH");
	MC_samplegroup.push_back("ttVH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZH);
	MC_filename.push_back(filename_ttZH);
	MC_filename_norm.push_back(filename_norm_ttZH);
	MC_samplename.push_back("ttZH_s1");
	MC_sampletag.push_back("ttZH");
	MC_samplegroup.push_back("ttVH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ggH

	MC_XS.push_back(XS_ggHToTauTau);
	MC_filename.push_back(filename_ggHToTauTau);
	MC_filename_norm.push_back(filename_norm_ggHToTauTau);
	MC_samplename.push_back("ggHToTauTau_s1");
	MC_sampletag.push_back("ggHToTauTau");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToZZ);
	MC_filename.push_back(filename_ggHToZZ4l);
	MC_filename_norm.push_back(filename_norm_ggHToZZ4l);
	MC_samplename.push_back("ggHToZZ4l_s1");
	MC_sampletag.push_back("ggHToZZ4l");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToZZTo2L2Q);
	MC_filename.push_back(filename_ggHToZZTo2L2Q);
	MC_filename_norm.push_back(filename_norm_ggHToZZTo2L2Q);
	MC_samplename.push_back("ggHToZZTo2L2Q_s1");
	MC_sampletag.push_back("ggHToZZTo2L2Q");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToWWToLNuQQ);
	MC_filename.push_back(filename_ggHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_ggHToWWToLNuQQ);
	MC_samplename.push_back("ggHToWWToLNuQQ_s1");
	MC_sampletag.push_back("ggHToWWToLNuQQ");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToWWTo2L2Nu);
	MC_filename.push_back(filename_ggHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_ggHToWWTo2L2Nu);
	MC_samplename.push_back("ggHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("ggHToWWTo2L2Nu");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToMuMu);
	MC_filename.push_back(filename_ggHToMuMu);
	MC_filename_norm.push_back(filename_norm_ggHToMuMu);
	MC_samplename.push_back("ggHToMuMu_s1");
	MC_sampletag.push_back("ggHToMuMu");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToBB);
	MC_filename.push_back(filename_ggHToBB);
	MC_filename_norm.push_back(filename_norm_ggHToBB);
	MC_samplename.push_back("ggHToBB_s1");
	MC_sampletag.push_back("ggHToBB");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ggHToGG);
	MC_filename.push_back(filename_ggHToGG);
	MC_filename_norm.push_back(filename_norm_ggHToGG);
	MC_samplename.push_back("ggHToGG_s1");
	MC_sampletag.push_back("ggHToGG");
	MC_samplegroup.push_back("ggH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// qqH

	MC_XS.push_back(XS_VBFHToTauTau);
	MC_filename.push_back(filename_VBFHToTauTau);
	MC_filename_norm.push_back(filename_norm_VBFHToTauTau);
	MC_samplename.push_back("VBFHToTauTau_s1");
	MC_sampletag.push_back("VBFHToTauTau");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToZZ);
	MC_filename.push_back(filename_VBFHToZZ);
	MC_filename_norm.push_back(filename_norm_VBFHToZZ);
	MC_samplename.push_back("VBFHToZZ_s1");
	MC_sampletag.push_back("VBFHToZZ");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToWWToLNuQQ);
	MC_filename.push_back(filename_VBFHToWWToLNuQQ);
	MC_filename_norm.push_back(filename_norm_VBFHToWWToLNuQQ);
	MC_samplename.push_back("VBFHToWWToLNuQQ_s1");
	MC_sampletag.push_back("VBFHToWWToLNuQQ");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToWWTo2L2Nu);
	MC_filename.push_back(filename_VBFHToWWTo2L2Nu);
	MC_filename_norm.push_back(filename_norm_VBFHToWWTo2L2Nu);
	MC_samplename.push_back("VBFHToWWTo2L2Nu_s1");
	MC_sampletag.push_back("VBFHToWWTo2L2Nu");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToMuMu);
	MC_filename.push_back(filename_VBFHToMuMu);
	MC_filename_norm.push_back(filename_norm_VBFHToMuMu);
	MC_samplename.push_back("VBFHToMuMu_s1");
	MC_sampletag.push_back("VBFHToMuMu");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToBB);
	MC_filename.push_back(filename_VBFHToBB);
	MC_filename_norm.push_back(filename_norm_VBFHToBB);
	MC_samplename.push_back("VBFHToBB_s1");
	MC_sampletag.push_back("VBFHToBB");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_VBFHToGG);
	MC_filename.push_back(filename_VBFHToGG);
	MC_filename_norm.push_back(filename_norm_VBFHToGG);
	MC_samplename.push_back("VBFHToGG_s1");
	MC_sampletag.push_back("VBFHToGG");
	MC_samplegroup.push_back("VBF");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// HH

	MC_XS.push_back(XS_ggHHTo2B2Tau);
	MC_filename.push_back(filename_ggHHTo2B2Tau);
	MC_filename_norm.push_back(filename_norm_ggHHTo2B2Tau);
	MC_samplename.push_back("ggHHTo2B2Tau_s1");
	MC_sampletag.push_back("ggHHTo2B2Tau");
	MC_samplegroup.push_back("HH");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// ttZ

	MC_XS.push_back(XS_ttZ);
	MC_filename.push_back(filename_ttZ); 
	MC_filename_norm.push_back(filename_norm_ttZ);
	MC_samplename.push_back("ttZ_s1");
	MC_sampletag.push_back("ttZ");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttZ_lowmass);
	MC_filename.push_back(filename_ttZ_lowmass);
	MC_filename_norm.push_back(filename_norm_ttZ_lowmass);
	MC_samplename.push_back("ttZm1to10_s1");
	MC_sampletag.push_back("ttZm1to10");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttbar_DiLept);
	MC_filename.push_back(filename_ttbar_DiLept); 
	MC_filename_norm.push_back(filename_norm_ttbar_DiLept);
	MC_samplename.push_back("ttbarDL_s1");
	MC_sampletag.push_back("ttbarDL");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromt); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromt);
	MC_samplename.push_back("ttbarSLfromT_s1");
	MC_sampletag.push_back("ttbarSLfromT");
	MC_samplegroup.push_back("ttZ");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttbar_SingleLep);
	MC_filename.push_back(filename_ttbar_SingleLeptFromtbar); 
	MC_filename_norm.push_back(filename_norm_ttbar_SingleLeptFromtbar);
	MC_samplename.push_back("ttbarSLfromTbar_s1");
	MC_sampletag.push_back("ttbarSLfromTbar");
	MC_samplegroup.push_back("ttZ");
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
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// ttWW

	/*MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW_ext1);
	MC_filename_norm.push_back(filename_norm_ttWW_ext1);
	MC_samplename.push_back("ttWW_s2");
	MC_sampletag.push_back("ttWW");
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ttWW);
	MC_filename.push_back(filename_ttWW_ext2);
	MC_filename_norm.push_back(filename_norm_ttWW_ext2);
	MC_samplename.push_back("ttWW_s1");
	MC_sampletag.push_back("ttWW");
	MC_samplegroup.push_back("ttW");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// WW

	MC_XS.push_back(XS_WW);
	MC_filename.push_back(filename_WW);
	MC_filename_norm.push_back(filename_norm_WW);
	MC_samplename.push_back("WW_s1");
	MC_sampletag.push_back("WW");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// WZ

	/*MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ);
	MC_filename_norm.push_back(filename_norm_WZ);
	MC_samplename.push_back("WZ_s2");
	MC_sampletag.push_back("WZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_WZ);
	MC_filename.push_back(filename_WZ_ext1);
	MC_filename_norm.push_back(filename_norm_WZ_ext1);
	MC_samplename.push_back("WZ_s1");
	MC_sampletag.push_back("WZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	// ZZ

	/*MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ);
	MC_filename_norm.push_back(filename_norm_ZZ);
	MC_samplename.push_back("ZZ_s2");
	MC_sampletag.push_back("ZZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);*/

	MC_XS.push_back(XS_ZZ);
	MC_filename.push_back(filename_ZZ_ext2);
	MC_filename_norm.push_back(filename_norm_ZZ_ext2);
	MC_samplename.push_back("ZZ_s1");
	MC_sampletag.push_back("ZZ");
	MC_samplegroup.push_back("EWK");
	MC_nsamples.push_back(2);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	// Rares

	MC_XS.push_back(XS_WWW);
	MC_filename.push_back(filename_WWW);
	MC_filename_norm.push_back(filename_norm_WWW);
	MC_samplename.push_back("WWW_s1");
	MC_sampletag.push_back("WWW");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WWZ);
	MC_filename.push_back(filename_WWZ);
	MC_filename_norm.push_back(filename_norm_WWZ);
	MC_samplename.push_back("WWZ_s1");
	MC_sampletag.push_back("WWZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZZ);
	MC_filename.push_back(filename_WZZ);
	MC_filename_norm.push_back(filename_norm_WZZ);
	MC_samplename.push_back("WZZ_s1");
	MC_sampletag.push_back("WZZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZZZ);
	MC_filename.push_back(filename_ZZZ);
	MC_filename_norm.push_back(filename_norm_ZZZ);
	MC_samplename.push_back("ZZZ_s1");
	MC_sampletag.push_back("ZZZ");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WZG);
	MC_filename.push_back(filename_WZG);
	MC_filename_norm.push_back(filename_norm_WZG);
	MC_samplename.push_back("WZG_s1");
	MC_sampletag.push_back("WZG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WG);
	MC_filename.push_back(filename_WG);
	MC_filename_norm.push_back(filename_norm_WG);
	MC_samplename.push_back("WG_s1");
	MC_sampletag.push_back("WG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ZG);
	MC_filename.push_back(filename_ZG);
	MC_filename_norm.push_back(filename_norm_ZG);
	MC_samplename.push_back("ZG_s1");
	MC_sampletag.push_back("ZG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tG);
	MC_filename.push_back(filename_tG);
	MC_filename_norm.push_back(filename_norm_tG);
	MC_samplename.push_back("tG_s1");
	MC_sampletag.push_back("tG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_ttG);
	MC_filename.push_back(filename_ttG);
	MC_filename_norm.push_back(filename_norm_ttG);
	MC_samplename.push_back("ttG_s1");
	MC_sampletag.push_back("ttG");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tZq);
	MC_filename.push_back(filename_tZq); 
	MC_filename_norm.push_back(filename_norm_tZq);
	MC_samplename.push_back("tZq_s1");
	MC_sampletag.push_back("tZq");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WpWp);
	MC_filename.push_back(filename_WpWp); 
	MC_filename_norm.push_back(filename_norm_WpWp);
	MC_samplename.push_back("WpWp_s1");
	MC_sampletag.push_back("WpWp");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_WW_DS);
	MC_filename.push_back(filename_WW_DS); 
	MC_filename_norm.push_back(filename_norm_WW_DS);
	MC_samplename.push_back("WWss_s1");
	MC_sampletag.push_back("WWss");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_tttt);
	MC_filename.push_back(filename_tttt); 
	MC_filename_norm.push_back(filename_norm_tttt);
	MC_samplename.push_back("tttt_s1");
	MC_sampletag.push_back("tttt");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_schannel);
	MC_filename.push_back(filename_St_schannel); 
	MC_filename_norm.push_back(filename_norm_St_schannel);
	MC_samplename.push_back("TsCh_s1");
	MC_sampletag.push_back("TsCh");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_top);
	MC_filename.push_back(filename_St_tchannel_top); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_top);
	MC_samplename.push_back("TtChTop_s1");
	MC_sampletag.push_back("TtChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tchannel_antitop);
	MC_filename.push_back(filename_St_tchannel_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tchannel_antitop);
	MC_samplename.push_back("TtChAntitop_s1");
	MC_sampletag.push_back("TtChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_top); 
	MC_filename_norm.push_back(filename_norm_St_tW_top);
	MC_samplename.push_back("TtwChTop_s1");
	MC_sampletag.push_back("TtwChTop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tW);
	MC_filename.push_back(filename_St_tW_antitop); 
	MC_filename_norm.push_back(filename_norm_St_tW_antitop);
	MC_samplename.push_back("TtwChAntitop_s1");
	MC_sampletag.push_back("TtwChAntitop");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	MC_XS.push_back(XS_St_tWll);
	MC_filename.push_back(filename_St_tWll); 
	MC_filename_norm.push_back(filename_norm_St_tWll);
	MC_samplename.push_back("TtwChll_s1");
	MC_sampletag.push_back("TtwChll");
	MC_samplegroup.push_back("Rares");
	MC_nsamples.push_back(1);
	MC_samplecut.push_back(genmatch+" && "+chargematch);
	MC_convs_samplecut.push_back(conversmatch);

	///////////////////////////////////////////////////////

	Data_SR_filename.push_back(filename_EGamma_BlockA_SR);
	Data_SR_filename.push_back(filename_EGamma_BlockB_SR);
	Data_SR_filename.push_back(filename_EGamma_BlockC_SR);
	Data_SR_filename.push_back(filename_EGamma_BlockD_SR);

	Data_SR_filename.push_back(filename_SingleMuon_BlockA_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockB_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockC_SR);
	Data_SR_filename.push_back(filename_SingleMuon_BlockD_SR);

	Data_SR_filename.push_back(filename_DoubleMu_BlockA_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockB_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockC_SR);
	Data_SR_filename.push_back(filename_DoubleMu_BlockD_SR);

	Data_SR_filename.push_back(filename_MuonEG_BlockA_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockB_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockC_SR);
	Data_SR_filename.push_back(filename_MuonEG_BlockD_SR);

	///////////////////////////////////////////////////////

	Data_fake_filename.push_back(filename_EGamma_BlockA_fake);
	Data_fake_filename.push_back(filename_EGamma_BlockB_fake);
	Data_fake_filename.push_back(filename_EGamma_BlockC_fake);
	Data_fake_filename.push_back(filename_EGamma_BlockD_fake);

	Data_fake_filename.push_back(filename_SingleMuon_BlockA_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockB_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockC_fake);
	Data_fake_filename.push_back(filename_SingleMuon_BlockD_fake);

	Data_fake_filename.push_back(filename_DoubleMu_BlockA_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockB_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockC_fake);
	Data_fake_filename.push_back(filename_DoubleMu_BlockD_fake);

	Data_fake_filename.push_back(filename_MuonEG_BlockA_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockB_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockC_fake);
	Data_fake_filename.push_back(filename_MuonEG_BlockD_fake);

	///////////////////////////////////////////////////////

	Data_flip_filename.push_back(filename_EGamma_BlockA_flip);
	Data_flip_filename.push_back(filename_EGamma_BlockB_flip);
	Data_flip_filename.push_back(filename_EGamma_BlockC_flip);
	Data_flip_filename.push_back(filename_EGamma_BlockD_flip);

	Data_flip_filename.push_back(filename_SingleMuon_BlockA_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockB_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockC_flip);
	Data_flip_filename.push_back(filename_SingleMuon_BlockD_flip);

	Data_flip_filename.push_back(filename_DoubleMu_BlockA_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockB_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockC_flip);
	Data_flip_filename.push_back(filename_DoubleMu_BlockD_flip);

	Data_flip_filename.push_back(filename_MuonEG_BlockA_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockB_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockC_flip);
	Data_flip_filename.push_back(filename_MuonEG_BlockD_flip);

	///////////////////////////////////////////////////////

	return std::make_tuple(MC_XS, MC_filename, MC_filename_norm, MC_samplename, MC_samplecut, MC_sampletag, MC_samplegroup, MC_nsamples, MC_convs_samplecut, Data_SR_filename, Data_fake_filename, Data_flip_filename, luminosity);

}



void datacard_maker(TString var1, int nbin, float xmin, float xmax,
					TString cut_cat, TString file, bool syst=false, int year=2016){

	cout<<" "<<endl;
	cout<<" ************************************************ "<<endl;
	cout<<" Creating datacards..."<<endl;
	cout<<"   Year: "<<year<<endl;
	cout<<"   Systematics: "<<syst<<endl;

	TString var = var1 + "*(" + var1 + Form("<=%f) + %f*(",xmax,0.999*xmax) + var1 + Form(">%f)",xmax);
  	cout<<"   Variable: "<<var<<endl;

  	std::tuple< vector<float>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, vector<int>, vector<TString>, vector<TString>, vector<TString>, vector<TString>, float > loadedsamples;
  	
  	if(year==2016) loadedsamples = initialize_2016();
  	else if(year==2017) loadedsamples = initialize_2017();
  	else if(year==2018) loadedsamples = initialize_2018();

  	vector<float> 	XS_MC 				= std::get<0>(loadedsamples);
  	vector<TString> filename_MC 		= std::get<1>(loadedsamples);
  	vector<TString> filename_norm_MC 	= std::get<2>(loadedsamples);
  	vector<TString> samplename_MC 		= std::get<3>(loadedsamples);
  	vector<TString> samplecut_MC 		= std::get<4>(loadedsamples);
  	vector<TString> sampletag_MC 		= std::get<5>(loadedsamples);
  	vector<TString> samplegroup_MC 		= std::get<6>(loadedsamples);
  	vector<int> 	nsamples_MC 		= std::get<7>(loadedsamples);
  	vector<TString> samplecutconvs_MC 	= std::get<8>(loadedsamples);
  	vector<TString> filename_data_SR 	= std::get<9>(loadedsamples);
  	vector<TString> filename_data_fake 	= std::get<10>(loadedsamples);
  	vector<TString> filename_data_flip 	= std::get<11>(loadedsamples);
  	float 			lumin 				= std::get<12>(loadedsamples);

  	cout<<"   Lumi: "<<lumin<<endl;

  	cout<<" ************************************************ "<<endl;
  	cout<<" "<<endl;

  	TString cat_name = "ttH_2lss_1tau";

  	TFile* f_new = TFile::Open(file,"RECREATE");
  	TDirectory* dir = f_new->mkdir(cat_name);
    dir->cd();

    /////////////////////////////
    ////       NOMINAL       ////
    /////////////////////////////

	cout<<"------ NOMINAL ------"<<endl;

	// MC normalization files

	vector<float> norm_MC;
	norm_MC.clear();

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString MC_weight = "MC_weight";

		if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)*sign(MC_weight)";
			MC_weight = "MC_weight";

		TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
			"Tree",
			"1",
			MC_weight+"*PU_weight_v1",
			3,0,3);

		norm_MC.push_back(h_MC_norm->Integral());

	}  	

	///////////////////////////////////////////////////////

	// MC SR prompt and conversion files

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString MC_weight = "MC_weight";

		//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
		h_MC->SetNameTitle("x_"+sampletag_MC[i_MC],"x_"+sampletag_MC[i_MC]);
		makeBinContentsPositive(h_MC,false);
		//h_MC->Write();

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
		h_MC_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC],"x_"+sampletag_MC[i_MC]);
		makeBinContentsPositive(h_MC_Convs,false);
		//h_MC_Convs->Write();

		////////////////////////////////////////////////////////////////////////////

	}

	///////////////////////////////////////////////////////

	vector<TString> group_names;

	group_names.clear();

	group_names.push_back("ttH");
	group_names.push_back("tHq");
	group_names.push_back("VH");
	group_names.push_back("ttVH");
	group_names.push_back("ggH");
	group_names.push_back("VBF");
	group_names.push_back("HH");
	group_names.push_back("ttZ");
	group_names.push_back("ttW");
	group_names.push_back("EWK");
	group_names.push_back("Rares");

	for (unsigned i_group=0;i_group<group_names.size();i_group++){
		
		TH1F* histo;
		int counts = 0;

		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			if( samplegroup_MC[i_MC] == group_names[i_group] ){

				if (counts==0) histo = (TH1F*)f_new->Get(cat_name+"/x_"+sampletag_MC[i_MC]);
				else histo->Add( (TH1F*)f_new->Get(cat_name+"/x_"+sampletag_MC[i_MC]) );
				counts++;

			}

		}

		TString histoname = group_names[i_group];
		histo->SetNameTitle(histoname,histoname);
		histo->Write();

	}

	TH1F* histo_convs;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		if (i_MC==0) histo_convs = (TH1F*)f_new->Get(cat_name+"/x_Convs_"+sampletag_MC[i_MC]);
		else histo_convs->Add( (TH1F*)f_new->Get(cat_name+"/x_Convs_"+sampletag_MC[i_MC]) );

	}

	histo_convs->SetNameTitle("Convs","Convs");
	histo_convs->Write();

    ///////////////////////////////////////////////////////

	// Fakes from data

    TH1F* h_fakes =single_plot(filename_data_fake,
			"HTauTauTree_2lss1tau_fake",
			var,
			"event_weight_ttH_v2*("+cut_cat+")",
			nbin,xmin,xmax);
    
    h_fakes->SetNameTitle("data_fakes","data_fakes");
    makeBinContentsPositive(h_fakes,false);
    h_fakes->Write();

	///////////////////////////////////////////////////////

	// Flips from data

    TH1F* h_flips =single_plot(filename_data_flip,
			"HTauTauTree_2lss1tau_flip",
			var,
			"event_weight_ttH_v2*("+cut_cat+")",
			nbin,xmin,xmax);
    
    h_flips->SetNameTitle("data_flips","data_flips");
    makeBinContentsPositive(h_flips,false);
    h_flips->Write();

	///////////////////////////////////////////////////////

	// Data

    /*TH1F* h_data_obs =single_plot(filename_data_SR,
		    "HTauTauTree_2lss1tau_SR",
		    var,
            cut_cat,
            nbin,xmin,xmax);
      
    h_data_obs->SetNameTitle("data_obs","data_obs");
    makeBinContentsPositive(h_data_obs,false);
    h_data_obs->Write();*/

    ///////////////////////////////////////////////////////

    cout<<"OK nominal"<<endl;

    if(!syst){
      f_new->Close();
      return;
    }


    ////////////////////////////////
    ////       SYSTEMATICS       ///
    ////////////////////////////////


    ////////////////
    //// THEORY ////
    ////////////////

    cout<<" "<<endl;
    cout<<"------ THEORY SYST ------"<<endl;

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	if( !(samplegroup_MC[i_MC]=="ttH" || samplegroup_MC[i_MC]=="tHq" || samplegroup_MC[i_MC]=="ttZ"  || samplegroup_MC[i_MC]=="ttW" || samplegroup_MC[i_MC]=="EWK" ) ) continue;

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_x1_up = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				"MC_weight_scale_muR2*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            	nbin,xmin,xmax);

		h_MC_x1_up->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
      	h_MC_x1_up->SetNameTitle("x_"+sampletag_MC[i_MC]+"_theory_shape_x1Up","x_"+sampletag_MC[i_MC]+"_theory_shape_x1Up");
      	makeBinContentsPositive(h_MC_x1_up);
      	//h_MC_x1_up->Write();

      	TH1F* h_MC_x1_down = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				"MC_weight_scale_muR0p5*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            	nbin,xmin,xmax);

		h_MC_x1_down->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
      	h_MC_x1_down->SetNameTitle("x_"+sampletag_MC[i_MC]+"_theory_shape_x1Down","x_"+sampletag_MC[i_MC]+"_theory_shape_x1Down");
      	makeBinContentsPositive(h_MC_x1_down);
      	//h_MC_x1_down->Write();

      	TH1F* h_MC_y1_up = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				"MC_weight_scale_muF2*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            	nbin,xmin,xmax);

		h_MC_y1_up->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
      	h_MC_y1_up->SetNameTitle("x_"+sampletag_MC[i_MC]+"_theory_shape_y1Up","x_"+sampletag_MC[i_MC]+"_theory_shape_y1Up");
      	makeBinContentsPositive(h_MC_y1_up);
      	//h_MC_y1_up->Write();

      	TH1F* h_MC_y1_down = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				"MC_weight_scale_muF0p5*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            	nbin,xmin,xmax);

		h_MC_y1_down->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
      	h_MC_y1_down->SetNameTitle("x_"+sampletag_MC[i_MC]+"_theory_shape_y1Down","x_"+sampletag_MC[i_MC]+"_theory_shape_y1Down");
      	makeBinContentsPositive(h_MC_y1_down);
      	//h_MC_y1_down->Write();

      	////////////////////////////////////////////////////////////////////////////

      	TH1F* h_nomin = (TH1F*)f_new->Get(cat_name+"/x_"+sampletag_MC[i_MC]);

      	TH1F* ratio_x1_up = (TH1F*)h_MC_x1_up->Clone();
      	ratio_x1_up->Divide(h_nomin);
      	TF1* f_x1_up = new TF1("f_x1_up","pol1");
      	ratio_x1_up->Fit(f_x1_up);
      	double slope_x1_up = f_x1_up->GetParameter(1);

      	TH1F* ratio_x1_down = (TH1F*)h_MC_x1_down->Clone();
      	ratio_x1_down->Divide(h_nomin);
      	TF1* f_x1_down = new TF1("f_x1_down","pol1");
      	ratio_x1_down->Fit(f_x1_down);
      	double slope_x1_down = f_x1_down->GetParameter(1);

      	TH1F* ratio_y1_up = (TH1F*)h_MC_y1_up->Clone();
      	ratio_y1_up->Divide(h_nomin);
      	TF1* f_y1_up = new TF1("f_y1_up","pol1");
      	ratio_y1_up->Fit(f_y1_up);
      	double slope_y1_up = f_y1_up->GetParameter(1);

      	TH1F* ratio_y1_down = (TH1F*)h_MC_y1_down->Clone();
      	ratio_y1_down->Divide(h_nomin);
      	TF1* f_y1_down = new TF1("f_y1_down","pol1");
      	ratio_y1_down->Fit(f_y1_down);
      	double slope_y1_down = f_y1_down->GetParameter(1);

      	vector<double> slopes={slope_x1_up, slope_x1_down, slope_y1_up, slope_y1_down};
      	int max_slope = distance(slopes.begin(), max_element(slopes.begin(),slopes.end()));
      	int min_slope = distance(slopes.begin(), min_element(slopes.begin(),slopes.end()));

      	TH1F* h_MC_thu_shapeUp; 
      	if(max_slope==0)
			h_MC_thu_shapeUp = (TH1F*)h_MC_x1_up->Clone(); 
      	else if(max_slope==1)
			h_MC_thu_shapeUp = (TH1F*)h_MC_x1_down->Clone(); 
      	else if(max_slope==2)
			h_MC_thu_shapeUp = (TH1F*)h_MC_y1_up->Clone();
      	else if(max_slope==3)
			h_MC_thu_shapeUp = (TH1F*)h_MC_y1_down->Clone();      
      	h_MC_thu_shapeUp->SetNameTitle("x_"+sampletag_MC[i_MC]+"_theory_shape_Up","x_"+sampletag_MC[i_MC]+"_theory_shape_Up");
      	//h_MC_thu_shapeUp->Write();

      	TH1F* h_MC_thu_shapeDown; 
      	if(min_slope==0)
			h_MC_thu_shapeDown = (TH1F*)h_MC_x1_up->Clone();
      	else if(min_slope==1)
			h_MC_thu_shapeDown = (TH1F*)h_MC_x1_down->Clone();
      	else if(min_slope==2)
			h_MC_thu_shapeDown = (TH1F*)h_MC_y1_up->Clone();
      	else if(min_slope==3)
			h_MC_thu_shapeDown = (TH1F*)h_MC_y1_down->Clone();      
      	h_MC_thu_shapeDown->SetNameTitle("x_"+sampletag_MC[i_MC]+"_theory_shape_Down","x_"+sampletag_MC[i_MC]+"_theory_shape_Down");
      	//h_MC_thu_shapeDown->Write();   

      	////////////////////////////////////////////////////////////////////////////

    }

    vector<TString> thu_uncert;

    thu_uncert.clear();

    thu_uncert.push_back("x1Up");
    thu_uncert.push_back("x1Down");
    thu_uncert.push_back("y1Up");
    thu_uncert.push_back("y1Down");
    thu_uncert.push_back("Up");
    thu_uncert.push_back("Down");

    for(unsigned int i_th=0;i_th<thu_uncert.size();i_th++){

    	TH1F* h_TTH = (TH1F*)f_new->Get(cat_name+"/x_ttH_theory_shape_"+thu_uncert[i_th])->Clone();
    	h_TTH->SetNameTitle("ttH_theory_shape_"+thu_uncert[i_th],"ttH_theory_shape_"+thu_uncert[i_th]);
	    h_TTH->Write();

	    TH1F* h_TH = (TH1F*)f_new->Get(cat_name+"/x_tHQ_theory_shape_"+thu_uncert[i_th])->Clone();
	    h_TH->Add( (TH1F*)f_new->Get(cat_name+"/x_tHW_theory_shape_"+thu_uncert[i_th]) );
    	h_TH->SetNameTitle("tHq_theory_shape_"+thu_uncert[i_th],"tHq_theory_shape_"+thu_uncert[i_th]);
	    h_TH->Write();

	    TH1F* h_TTZ = (TH1F*)f_new->Get(cat_name+"/x_ttZ_theory_shape_"+thu_uncert[i_th])->Clone();
	    h_TTZ->Add( (TH1F*)f_new->Get(cat_name+"/x_ttbarDL_theory_shape_"+thu_uncert[i_th]) );
	    h_TTZ->Add( (TH1F*)f_new->Get(cat_name+"/x_ttbarSLfromT_theory_shape_"+thu_uncert[i_th]) );
	    h_TTZ->Add( (TH1F*)f_new->Get(cat_name+"/x_ttbarSLfromTbar_theory_shape_"+thu_uncert[i_th]) );
    	h_TTZ->SetNameTitle("ttZ_theory_shape_"+thu_uncert[i_th],"ttZ_theory_shape_"+thu_uncert[i_th]);
	    h_TTZ->Write();

	    TH1F* h_TTW = (TH1F*)f_new->Get(cat_name+"/x_ttW_theory_shape_"+thu_uncert[i_th])->Clone();
	    h_TTW->Add( (TH1F*)f_new->Get(cat_name+"/x_ttWW_theory_shape_"+thu_uncert[i_th]) );
    	h_TTW->SetNameTitle("ttW_theory_shape_"+thu_uncert[i_th],"ttW_theory_shape_"+thu_uncert[i_th]);
	    h_TTW->Write();

	    TH1F* h_EWK = (TH1F*)f_new->Get(cat_name+"/x_WZ_theory_shape_"+thu_uncert[i_th])->Clone();
	    h_EWK->Add( (TH1F*)f_new->Get(cat_name+"/x_ZZ_theory_shape_"+thu_uncert[i_th]) );
	    h_EWK->Add( (TH1F*)f_new->Get(cat_name+"/x_WW_theory_shape_"+thu_uncert[i_th]) );
    	h_EWK->SetNameTitle("EWK_theory_shape_"+thu_uncert[i_th],"EWK_theory_shape_"+thu_uncert[i_th]);
	    h_EWK->Write();

    }

    cout<<" "<<endl;
    cout<<"OK theory syst"<<endl;

    ///////////////
    //// B-TAG ////
    ///////////////

    cout<<" "<<endl;
    cout<<"------ B-TAG SYST ------"<<endl;

    vector<TString> bTag_syst_names;

    bTag_syst_names.clear();

  	bTag_syst_names.push_back("LFUp");
  	bTag_syst_names.push_back("LFDown");
  	bTag_syst_names.push_back("HFUp");
  	bTag_syst_names.push_back("HFDown");
  	bTag_syst_names.push_back("HFStats1Up");
  	bTag_syst_names.push_back("HFStats1Down");
  	bTag_syst_names.push_back("HFStats2Up");
  	bTag_syst_names.push_back("HFStats2Down");
  	bTag_syst_names.push_back("LFStats1Up");
  	bTag_syst_names.push_back("LFStats1Down");
  	bTag_syst_names.push_back("LFStats2Up");
  	bTag_syst_names.push_back("LFStats2Down");
  	bTag_syst_names.push_back("CFErr1Up");
  	bTag_syst_names.push_back("CFErr1Down");
  	bTag_syst_names.push_back("CFErr2Up");
  	bTag_syst_names.push_back("CFErr2Down");


    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){ 

    		TString MC_weight = "MC_weight";

			//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
				//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
				//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

			////////////////////////////////////////////////////////////////////////////

			TH1F* h_MC_btag_syst = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")*bTagSF_CSVshape_weight_"+bTag_syst_names[i_b],
            	nbin,xmin,xmax);

			h_MC_btag_syst->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);

			TString h_name = "x_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];

    		if(bTag_syst_names[i_b].Contains("Stats"))
    	   		h_name = "x_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];
    		if(bTag_syst_names[i_b]=="CFErr1Up")
    	   		h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr1Up";
    		else if(bTag_syst_names[i_b]=="CFErr1Down")
    	   		h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr1Down";
    		else if(bTag_syst_names[i_b]=="CFErr2Up")
    	   		h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr2Up";
    		else if(bTag_syst_names[i_b]=="CFErr2Down")
    	   		h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr2Down";
    
    		h_MC_btag_syst->SetNameTitle(h_name,h_name);
            makeBinContentsPositive(h_MC_btag_syst,false);

            ////////////////////////////////////////////////////////////////////////////

			TH1F* h_MC_btag_syst_Convs = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")*bTagSF_CSVshape_weight_"+bTag_syst_names[i_b],
            	nbin,xmin,xmax);

			h_MC_btag_syst_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);

			TString h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];

    		if(bTag_syst_names[i_b].Contains("Stats"))
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];
    		if(bTag_syst_names[i_b]=="CFErr1Up")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr1Up";
    		else if(bTag_syst_names[i_b]=="CFErr1Down")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr1Down";
    		else if(bTag_syst_names[i_b]=="CFErr2Up")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr2Up";
    		else if(bTag_syst_names[i_b]=="CFErr2Down")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr2Down";

			h_MC_btag_syst_Convs->SetNameTitle(h_name_convs,h_name_convs);
            makeBinContentsPositive(h_MC_btag_syst_Convs,false);

            ////////////////////////////////////////////////////////////////////////////

    	}

    }

    for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){ 

		for (unsigned i_group=0;i_group<group_names.size();i_group++){

			TH1F* histo;

			int counts = 0;
		
			for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

				TString h_name = "x_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];

				if(bTag_syst_names[i_b].Contains("Stats"))
    	   			h_name = "x_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];
    			if(bTag_syst_names[i_b]=="CFErr1Up")
    	   			h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr1Up";
    			else if(bTag_syst_names[i_b]=="CFErr1Down")
    	   			h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr1Down";
    			else if(bTag_syst_names[i_b]=="CFErr2Up")
    	   			h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr2Up";
    			else if(bTag_syst_names[i_b]=="CFErr2Down")
    	   			h_name = "x_"+sampletag_MC[i_MC]+"_btag_cErr2Down";

				if( samplegroup_MC[i_MC] == group_names[i_group] ){

					if (counts==0) histo = (TH1F*)f_new->Get(cat_name+"/"+h_name);
					else histo->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name) );
					counts++;

				}

			}

			TString h_name_group = group_names[i_group]+"_btag_"+bTag_syst_names[i_b];

			if(bTag_syst_names[i_b].Contains("Stats"))
    			h_name_group = group_names[i_group]+"_btag_"+bTag_syst_names[i_b];
    		if(bTag_syst_names[i_b]=="CFErr1Up")
    			h_name_group = group_names[i_group]+"_btag_cErr1Up";
    		else if(bTag_syst_names[i_b]=="CFErr1Down")
    			h_name_group = group_names[i_group]+"_btag_cErr1Down";
    		else if(bTag_syst_names[i_b]=="CFErr2Up")
    			h_name_group = group_names[i_group]+"_btag_cErr2Up";
    		else if(bTag_syst_names[i_b]=="CFErr2Down")
    			h_name_group = group_names[i_group]+"_btag_cErr2Down";

			histo->SetNameTitle(h_name_group,h_name_group);

			histo->Write();

		}

		TH1F* histo_convs;

		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];

			if(bTag_syst_names[i_b].Contains("Stats"))
    	   			h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_"+bTag_syst_names[i_b];
    		if(bTag_syst_names[i_b]=="CFErr1Up")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr1Up";
    		else if(bTag_syst_names[i_b]=="CFErr1Down")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr1Down";
    		else if(bTag_syst_names[i_b]=="CFErr2Up")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr2Up";
    		else if(bTag_syst_names[i_b]=="CFErr2Down")
    	   		h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_btag_cErr2Down";

			if (i_MC==0) histo_convs = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs);
			else histo_convs->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs) );

		}

		TString h_name_convs_group = "Convs_btag_"+bTag_syst_names[i_b];

		if(bTag_syst_names[i_b].Contains("Stats"))
    	   	h_name_convs_group = "Convs_btag_"+bTag_syst_names[i_b];
    	if(bTag_syst_names[i_b]=="CFErr1Up")
    	   	h_name_convs_group = "Convs_btag_cErr1Up";
    	else if(bTag_syst_names[i_b]=="CFErr1Down")
    	   	h_name_convs_group = "Convs_btag_cErr1Down";
    	else if(bTag_syst_names[i_b]=="CFErr2Up")
    	   	h_name_convs_group = "Convs_btag_cErr2Up";
    	else if(bTag_syst_names[i_b]=="CFErr2Down")
    	   	h_name_convs_group = "Convs_btag_cErr2Down";

    	histo_convs->SetNameTitle(h_name_convs_group,h_name_convs_group);

		histo_convs->Write();

	}

	cout<<" "<<endl;
    cout<<"OK b-tag syst"<<endl;

    ////////////////////
    ////// TRIGGER /////
    ////////////////////

    cout<<" "<<endl;
    cout<<"------ TRIGGER SYST ------"<<endl;

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	TString MC_weight = "MC_weight";

		//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_triggerUp = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_up_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_triggerUp->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_triggerUp->SetNameTitle("x_"+sampletag_MC[i_MC]+"_trigger_Up","x_"+sampletag_MC[i_MC]+"_trigger_Up");
        makeBinContentsPositive(h_MC_triggerUp,false);

        TH1F* h_MC_triggerDown = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_down_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_triggerDown->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_triggerDown->SetNameTitle("x_"+sampletag_MC[i_MC]+"_trigger_Down","x_"+sampletag_MC[i_MC]+"_trigger_Down");
        makeBinContentsPositive(h_MC_triggerDown,false);

        ////////////////////////////////////////////////////////////////////////////

        TH1F* h_MC_triggerUp_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_up_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_triggerUp_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_triggerUp_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_trigger_Up","x_Convs_"+sampletag_MC[i_MC]+"_trigger_Up");
        makeBinContentsPositive(h_MC_triggerUp_Convs,false);

        TH1F* h_MC_triggerDown_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_down_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_triggerDown_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_triggerDown_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_trigger_Down","x_Convs_"+sampletag_MC[i_MC]+"_trigger_Down");
        makeBinContentsPositive(h_MC_triggerDown_Convs,false);

        ////////////////////////////////////////////////////////////////////////////

    }


	for (unsigned i_group=0;i_group<group_names.size();i_group++){

		TH1F* histo_up;
		TH1F* histo_down;

		int counts = 0;
		
		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_up = "x_"+sampletag_MC[i_MC]+"_trigger_Up";
			TString h_name_down = "x_"+sampletag_MC[i_MC]+"_trigger_Down";

			if( samplegroup_MC[i_MC] == group_names[i_group] ){

				if (counts==0) {

					histo_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_up);
					histo_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_down);

				}

				else {

					histo_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_up) );
					histo_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_down) );

				}

				counts++;

			}

		}

		TString h_name_group_up = group_names[i_group]+"_trigger_Up";
		TString h_name_group_down = group_names[i_group]+"_trigger_Down";

		histo_up->SetNameTitle(h_name_group_up,h_name_group_up);
		histo_down->SetNameTitle(h_name_group_down,h_name_group_down);

		histo_up->Write();
		histo_down->Write();

	}


	TH1F* histo_convs_trig_up;
	TH1F* histo_convs_trig_down;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString h_name_convs_up = "x_Convs_"+sampletag_MC[i_MC]+"_trigger_Up";
		TString h_name_convs_down = "x_Convs_"+sampletag_MC[i_MC]+"_trigger_Down";

		if (i_MC==0) {

			histo_convs_trig_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up);
			histo_convs_trig_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down);

		}

		else {

			histo_convs_trig_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up) );
			histo_convs_trig_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down) );

		}

	}

	TString h_name_convs_trig_up = "Convs_trigger_Up";
	TString h_name_convs_trig_down = "Convs_trigger_Down";

	histo_convs_trig_up->SetNameTitle(h_name_convs_trig_up,h_name_convs_trig_up);
	histo_convs_trig_down->SetNameTitle(h_name_convs_trig_down,h_name_convs_trig_down);

	histo_convs_trig_up->Write();
	histo_convs_trig_down->Write();

	cout<<" "<<endl;
    cout<<"OK trigger"<<endl;


    ////////////////////
    ////// PREFIRE /////
    ////////////////////

    cout<<" "<<endl;
    cout<<"------ PREFIRING SYST ------"<<endl;

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	TString MC_weight = "MC_weight";

		//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_prefireUp = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight_up*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_prefireUp->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_prefireUp->SetNameTitle("x_"+sampletag_MC[i_MC]+"_prefire_Up","x_"+sampletag_MC[i_MC]+"_prefire_Up");
        makeBinContentsPositive(h_MC_prefireUp,false);

        TH1F* h_MC_prefireDown = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight_down*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_prefireDown->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_prefireDown->SetNameTitle("x_"+sampletag_MC[i_MC]+"_prefire_Down","x_"+sampletag_MC[i_MC]+"_prefire_Down");
        makeBinContentsPositive(h_MC_prefireDown,false);

        ////////////////////////////////////////////////////////////////////////////

        TH1F* h_MC_prefireUp_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight_up*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_prefireUp_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_prefireUp_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_prefire_Up","x_Convs_"+sampletag_MC[i_MC]+"_prefire_Up");
        makeBinContentsPositive(h_MC_prefireUp_Convs,false);

        TH1F* h_MC_prefireDown_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight_down*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_prefireDown_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_prefireDown_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_prefire_Down","x_Convs_"+sampletag_MC[i_MC]+"_prefire_Down");
        makeBinContentsPositive(h_MC_prefireDown_Convs,false);

        ////////////////////////////////////////////////////////////////////////////

    }


	for (unsigned i_group=0;i_group<group_names.size();i_group++){

		TH1F* histo_up;
		TH1F* histo_down;

		int counts = 0;
		
		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_up = "x_"+sampletag_MC[i_MC]+"_prefire_Up";
			TString h_name_down = "x_"+sampletag_MC[i_MC]+"_prefire_Down";

			if( samplegroup_MC[i_MC] == group_names[i_group] ){

				if (counts==0) {

					histo_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_up);
					histo_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_down);

				}

				else {

					histo_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_up) );
					histo_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_down) );

				}

				counts++;

			}

		}

		TString h_name_group_up = group_names[i_group]+"_prefire_Up";
		TString h_name_group_down = group_names[i_group]+"_prefire_Down";

		histo_up->SetNameTitle(h_name_group_up,h_name_group_up);
		histo_down->SetNameTitle(h_name_group_down,h_name_group_down);

		histo_up->Write();
		histo_down->Write();

	}


	TH1F* histo_convs_prefire_up;
	TH1F* histo_convs_prefire_down;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString h_name_convs_up = "x_Convs_"+sampletag_MC[i_MC]+"_prefire_Up";
		TString h_name_convs_down = "x_Convs_"+sampletag_MC[i_MC]+"_prefire_Down";

		if (i_MC==0) {

			histo_convs_prefire_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up);
			histo_convs_prefire_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down);

		}

		else {

			histo_convs_prefire_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up) );
			histo_convs_prefire_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down) );

		}

	}

	TString h_name_convs_prefire_up = "Convs_prefire_Up";
	TString h_name_convs_prefire_down = "Convs_prefire_Down";

	histo_convs_prefire_up->SetNameTitle(h_name_convs_prefire_up,h_name_convs_prefire_up);
	histo_convs_prefire_down->SetNameTitle(h_name_convs_prefire_down,h_name_convs_prefire_down);

	histo_convs_prefire_up->Write();
	histo_convs_prefire_down->Write();

	cout<<" "<<endl;
    cout<<"OK prefiring"<<endl;
    

    //////////////////////
    ////// LEPTON ID /////
    //////////////////////

    cout<<" "<<endl;
    cout<<"------ LEPTON ID SYST ------"<<endl;

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	TString MC_weight = "MC_weight";

		//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_lepEffUp = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_up_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_lepEffUp->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_lepEffUp->SetNameTitle("x_"+sampletag_MC[i_MC]+"_leptonID_Up","x_"+sampletag_MC[i_MC]+"_leptonID_Up");
        makeBinContentsPositive(h_MC_lepEffUp,false);

        TH1F* h_MC_lepEffDown = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_down_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_lepEffDown->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_lepEffDown->SetNameTitle("x_"+sampletag_MC[i_MC]+"_leptonID_Down","x_"+sampletag_MC[i_MC]+"_leptonID_Down");
        makeBinContentsPositive(h_MC_lepEffDown,false);

        ////////////////////////////////////////////////////////////////////////////

        TH1F* h_MC_lepEffUp_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_up_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_lepEffUp_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_lepEffUp_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_leptonID_Up","x_Convs_"+sampletag_MC[i_MC]+"_leptonID_Up");
        makeBinContentsPositive(h_MC_lepEffUp_Convs,false);

        TH1F* h_MC_lepEffDown_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_down_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_lepEffDown_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_lepEffDown_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_leptonID_Down","x_Convs_"+sampletag_MC[i_MC]+"_leptonID_Down");
        makeBinContentsPositive(h_MC_lepEffDown_Convs,false);

        ////////////////////////////////////////////////////////////////////////////

    }


	for (unsigned i_group=0;i_group<group_names.size();i_group++){

		TH1F* histo_up;
		TH1F* histo_down;

		int counts = 0;
		
		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_up = "x_"+sampletag_MC[i_MC]+"_leptonID_Up";
			TString h_name_down = "x_"+sampletag_MC[i_MC]+"_leptonID_Down";

			if( samplegroup_MC[i_MC] == group_names[i_group] ){

				if (counts==0) {

					histo_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_up);
					histo_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_down);

				}

				else {

					histo_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_up) );
					histo_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_down) );

				}

				counts++;

			}

		}

		TString h_name_group_up = group_names[i_group]+"_leptonID_Up";
		TString h_name_group_down = group_names[i_group]+"_leptonID_Down";

		histo_up->SetNameTitle(h_name_group_up,h_name_group_up);
		histo_down->SetNameTitle(h_name_group_down,h_name_group_down);

		histo_up->Write();
		histo_down->Write();

	}


	TH1F* histo_convs_lepeff_up;
	TH1F* histo_convs_lepeff_down;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString h_name_convs_up = "x_Convs_"+sampletag_MC[i_MC]+"_leptonID_Up";
		TString h_name_convs_down = "x_Convs_"+sampletag_MC[i_MC]+"_leptonID_Down";

		if (i_MC==0) {

			histo_convs_lepeff_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up);
			histo_convs_lepeff_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down);

		}

		else {

			histo_convs_lepeff_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up) );
			histo_convs_lepeff_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down) );

		}

	}

	TString h_name_convs_lepeff_up = "Convs_leptonID_Up";
	TString h_name_convs_lepeff_down = "Convs_leptonID_Down";

	histo_convs_lepeff_up->SetNameTitle(h_name_convs_lepeff_up,h_name_convs_lepeff_up);
	histo_convs_lepeff_down->SetNameTitle(h_name_convs_lepeff_down,h_name_convs_lepeff_down);

	histo_convs_lepeff_up->Write();
	histo_convs_lepeff_down->Write();

	cout<<" "<<endl;
    cout<<"OK lepton ID"<<endl;

    ////////////////////
    ////// TAU ID //////
    ////////////////////

    cout<<" "<<endl;
    cout<<"------ TAU ID SYST ------"<<endl;

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	TString MC_weight = "MC_weight";

		//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_tauIDUp = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_up_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauIDUp->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauIDUp->SetNameTitle("x_"+sampletag_MC[i_MC]+"_tauID_Up","x_"+sampletag_MC[i_MC]+"_tauID_Up");
        makeBinContentsPositive(h_MC_tauIDUp,false);

        TH1F* h_MC_tauIDDown = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_down_v1*tauES_weight_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauIDDown->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauIDDown->SetNameTitle("x_"+sampletag_MC[i_MC]+"_tauID_Down","x_"+sampletag_MC[i_MC]+"_tauID_Down");
        makeBinContentsPositive(h_MC_tauIDDown,false);

        ////////////////////////////////////////////////////////////////////////////

        TH1F* h_MC_tauIDUp_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_up_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauIDUp_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauIDUp_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_tauID_Up","x_Convs_"+sampletag_MC[i_MC]+"_tauID_Up");
        makeBinContentsPositive(h_MC_tauIDUp_Convs,false);

        TH1F* h_MC_tauIDDown_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_down_v1*tauES_weight_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauIDDown_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauIDDown_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_tauID_Down","x_Convs_"+sampletag_MC[i_MC]+"_tauID_Down");
        makeBinContentsPositive(h_MC_tauIDDown_Convs,false);

        ////////////////////////////////////////////////////////////////////////////

    }


	for (unsigned i_group=0;i_group<group_names.size();i_group++){

		TH1F* histo_up;
		TH1F* histo_down;

		int counts = 0;
		
		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_up = "x_"+sampletag_MC[i_MC]+"_tauID_Up";
			TString h_name_down = "x_"+sampletag_MC[i_MC]+"_tauID_Down";

			if( samplegroup_MC[i_MC] == group_names[i_group] ){

				if (counts==0) {

					histo_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_up);
					histo_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_down);

				}

				else {

					histo_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_up) );
					histo_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_down) );

				}

				counts++;

			}

		}

		TString h_name_group_up = group_names[i_group]+"_tauID_Up";
		TString h_name_group_down = group_names[i_group]+"_tauID_Down";

		histo_up->SetNameTitle(h_name_group_up,h_name_group_up);
		histo_down->SetNameTitle(h_name_group_down,h_name_group_down);

		histo_up->Write();
		histo_down->Write();

	}


	TH1F* histo_convs_tauid_up;
	TH1F* histo_convs_tauid_down;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString h_name_convs_up = "x_Convs_"+sampletag_MC[i_MC]+"_tauID_Up";
		TString h_name_convs_down = "x_Convs_"+sampletag_MC[i_MC]+"_tauID_Down";

		if (i_MC==0) {

			histo_convs_tauid_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up);
			histo_convs_tauid_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down);

		}

		else {

			histo_convs_tauid_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up) );
			histo_convs_tauid_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down) );

		}

	}

	TString h_name_convs_tauid_up = "Convs_tauID_Up";
	TString h_name_convs_tauid_down = "Convs_tauID_Down";

	histo_convs_tauid_up->SetNameTitle(h_name_convs_tauid_up,h_name_convs_tauid_up);
	histo_convs_tauid_down->SetNameTitle(h_name_convs_tauid_down,h_name_convs_tauid_down);

	histo_convs_tauid_up->Write();
	histo_convs_tauid_down->Write();

	cout<<" "<<endl;
    cout<<"OK tau ID"<<endl;
    

    ////////////////////
    ////// TAU ES //////
    ////////////////////

    cout<<" "<<endl;
    cout<<"------ TAU ES SYST ------"<<endl;

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	TString MC_weight = "MC_weight";

		//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
			//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
			//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

		////////////////////////////////////////////////////////////////////////////

		TH1F* h_MC_tauESUp = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_up_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauESUp->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauESUp->SetNameTitle("x_"+sampletag_MC[i_MC]+"_tauES_Up","x_"+sampletag_MC[i_MC]+"_tauES_Up");
        makeBinContentsPositive(h_MC_tauESUp,false);

        TH1F* h_MC_tauESDown = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_down_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauESDown->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauESDown->SetNameTitle("x_"+sampletag_MC[i_MC]+"_tauES_Down","x_"+sampletag_MC[i_MC]+"_tauES_Down");
        makeBinContentsPositive(h_MC_tauESDown,false);

        ////////////////////////////////////////////////////////////////////////////

        TH1F* h_MC_tauESUp_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_up_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauESUp_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauESUp_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_tauES_Up","x_Convs_"+sampletag_MC[i_MC]+"_tauES_Up");
        makeBinContentsPositive(h_MC_tauESUp_Convs,false);

        TH1F* h_MC_tauESDown_Convs = single_plot(filename_MC[i_MC],
			"HTauTauTree_2lss1tau_SR", 
			var,
			MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_down_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            nbin,xmin,xmax);

		h_MC_tauESDown_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);
    	h_MC_tauESDown_Convs->SetNameTitle("x_Convs_"+sampletag_MC[i_MC]+"_tauES_Down","x_Convs_"+sampletag_MC[i_MC]+"_tauES_Down");
        makeBinContentsPositive(h_MC_tauESDown_Convs,false);

        ////////////////////////////////////////////////////////////////////////////

    }


	for (unsigned i_group=0;i_group<group_names.size();i_group++){

		TH1F* histo_up;
		TH1F* histo_down;

		int counts = 0;
		
		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_up = "x_"+sampletag_MC[i_MC]+"_tauES_Up";
			TString h_name_down = "x_"+sampletag_MC[i_MC]+"_tauES_Down";

			if( samplegroup_MC[i_MC] == group_names[i_group] ){

				if (counts==0) {

					histo_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_up);
					histo_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_down);

				}

				else {

					histo_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_up) );
					histo_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_down) );

				}

				counts++;

			}

		}

		TString h_name_group_up = group_names[i_group]+"_tauES_Up";
		TString h_name_group_down = group_names[i_group]+"_tauES_Down";

		histo_up->SetNameTitle(h_name_group_up,h_name_group_up);
		histo_down->SetNameTitle(h_name_group_down,h_name_group_down);

		histo_up->Write();
		histo_down->Write();

	}


	TH1F* histo_convs_taues_up;
	TH1F* histo_convs_taues_down;

	for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

		TString h_name_convs_up = "x_Convs_"+sampletag_MC[i_MC]+"_tauES_Up";
		TString h_name_convs_down = "x_Convs_"+sampletag_MC[i_MC]+"_tauES_Down";

		if (i_MC==0) {

			histo_convs_taues_up = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up);
			histo_convs_taues_down = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down);

		}

		else {

			histo_convs_taues_up->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_up) );
			histo_convs_taues_down->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs_down) );

		}

	}

	TString h_name_convs_taues_up = "Convs_tauES_Up";
	TString h_name_convs_taues_down = "Convs_tauES_Down";

	histo_convs_taues_up->SetNameTitle(h_name_convs_taues_up,h_name_convs_taues_up);
	histo_convs_taues_down->SetNameTitle(h_name_convs_taues_down,h_name_convs_taues_down);

	histo_convs_taues_up->Write();
	histo_convs_taues_down->Write();

	cout<<" "<<endl;
    cout<<"OK tau ES"<<endl;


    ///////////////////////
    //// JET-TO-TAU FR ////
    ///////////////////////

    // Only for fake taus

    /*

    vector<TString> jetToTau_FR_syst_names;

    jetToTau_FR_syst_names.clear();

    jetToTau_FR_syst_names.push_back("tauNormUp");
  	jetToTau_FR_syst_names.push_back("tauNormDown");
  	jetToTau_FR_syst_names.push_back("tauShapeUp");
  	jetToTau_FR_syst_names.push_back("tauShapeDown");

    for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

    	for(unsigned int i_jt=0;i_jt<jetToTau_FR_syst_names.size();i_jt++){ 

    		TString MC_weight = "MC_weight";

			//if( sampletag_MC[i_MC] == "tHQ" || sampletag_MC[i_MC] == "tHW") //FIXME
				//MC_weight = "10*(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";
				//MC_weight = "(MC_weights_rwgt[11]/MC_weight_originalXWGTUP)";

			////////////////////////////////////////////////////////////////////////////

			TH1F* h_MC_FRjt_syst = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*bTagSF_CSVshape_weight*leptonID_weight_v1*tauES_weight_v1*tauID_weight_"+jetToTau_FR_syst_names[i_jt]+"_v1*("+samplecut_MC[i_MC]+" && "+cut_cat+")",
            	nbin,xmin,xmax);

			h_MC_FRjt_syst->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);

	    	TString h_name = "x_"+sampletag_MC[i_MC]+"_CMS_ttHl_FRjt_";

	    	if(jetToTau_FR_syst_names[i_jt]=="tauNormUp")
	      		h_name+="normUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauNormDown")
	      		h_name+="normDown";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeUp")
	      		h_name+="shapeUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeDown")
	      		h_name+="shapeDown";

	    	h_MC_FRjt_syst->SetNameTitle(h_name,h_name);
	    	makeBinContentsPositive(h_MC_FRjt_syst);
	    	//h_MC_FRjt_syst->Write();

            ////////////////////////////////////////////////////////////////////////////

			TH1F* h_MC_FRjt_syst_Convs = single_plot(filename_MC[i_MC],
				"HTauTauTree_2lss1tau_SR", 
				var,
				MC_weight+"*PU_weight_v1*prefire_weight*trigger_weight_v1*bTagSF_CSVshape_weight*leptonID_weight_v1*tauES_weight_v1*tauID_weight_"+jetToTau_FR_syst_names[i_jt]+"_v1*("+samplecutconvs_MC[i_MC]+" && "+cut_cat+")",
            	nbin,xmin,xmax);

			h_MC_FRjt_syst_Convs->Scale(lumin*XS_MC[i_MC]/norm_MC[i_MC]);

			TString h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_CMS_ttHl_FRjt_";

	    	if(jetToTau_FR_syst_names[i_jt]=="tauNormUp")
	      		h_name_convs+="normUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauNormDown")
	      		h_name_convs+="normDown";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeUp")
	      		h_name_convs+="shapeUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeDown")
	      		h_name_convs+="shapeDown";

	    	h_MC_FRjt_syst_Convs->SetNameTitle(h_name_convs,h_name_convs);
	    	makeBinContentsPositive(h_MC_FRjt_syst_Convs);
	    	//h_MC_FRjt_syst_Convs->Write();

            ////////////////////////////////////////////////////////////////////////////

    	}

    }

    for(unsigned int i_jt=0;i_jt<jetToTau_FR_syst_names.size();i_jt++){ 

		for (unsigned i_group=0;i_group<group_names.size();i_group++){

			TH1F* histo;

			int counts = 0;
		
			for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

				TString h_name = "x_"+sampletag_MC[i_MC]+"_CMS_ttHl_FRjt_";

	    		if(jetToTau_FR_syst_names[i_jt]=="tauNormUp")
	      			h_name+="normUp";
	    		else if(jetToTau_FR_syst_names[i_jt]=="tauNormDown")
	      			h_name+="normDown";
	    		else if(jetToTau_FR_syst_names[i_jt]=="tauShapeUp")
	      			h_name+="shapeUp";
	    		else if(jetToTau_FR_syst_names[i_jt]=="tauShapeDown")
	      			h_name+="shapeDown";

				if( samplegroup_MC[i_MC] == group_names[i_group] ){

					if (counts==0) histo = (TH1F*)f_new->Get(cat_name+"/"+h_name);
					else histo->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name) );
					counts++;

				}

			}

			TString h_name_group = group_names[i_group]+"_CMS_ttHl_FRjt_";

			if(jetToTau_FR_syst_names[i_jt]=="tauNormUp")
	      		h_name_group+="normUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauNormDown")
	      		h_name_group+="normDown";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeUp")
	      		h_name_group+="shapeUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeDown")
	      		h_name_group+="shapeDown";

			histo->SetNameTitle(h_name_group,h_name_group);

			histo->Write();

		}


		TH1F* histo_convs;

		for(unsigned i_MC=0;i_MC<samplename_MC.size();i_MC++){

			TString h_name_convs = "x_Convs_"+sampletag_MC[i_MC]+"_CMS_ttHl_FRjt_";

	    	if(jetToTau_FR_syst_names[i_jt]=="tauNormUp")
	      		h_name_convs+="normUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauNormDown")
	      		h_name_convs+="normDown";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeUp")
	      		h_name_convs+="shapeUp";
	    	else if(jetToTau_FR_syst_names[i_jt]=="tauShapeDown")
	      		h_name_convs+="shapeDown";

			if (i_MC==0) histo_convs = (TH1F*)f_new->Get(cat_name+"/"+h_name_convs);
			else histo_convs->Add( (TH1F*)f_new->Get(cat_name+"/"+h_name_convs) );

		}

		TString h_name_convs_group = "Convs_CMS_ttHl_FRjt_";

		if(jetToTau_FR_syst_names[i_jt]=="tauNormUp")
	      	h_name_convs_group+="normUp";
	    else if(jetToTau_FR_syst_names[i_jt]=="tauNormDown")
	      	h_name_convs_group+="normDown";
	    else if(jetToTau_FR_syst_names[i_jt]=="tauShapeUp")
	      	h_name_convs_group+="shapeUp";
	    else if(jetToTau_FR_syst_names[i_jt]=="tauShapeDown")
	      	h_name_convs_group+="shapeDown";

    	histo_convs->SetNameTitle(h_name_convs_group,h_name_convs_group);

		histo_convs->Write();

	}

	cout<<" "<<endl;
    cout<<"OK jet->tau FR syst"<<endl;
    */

    ///////////////////////////////////////////////////////

    f_new->Close();
    return;

}


void datacard_maker_n_recotauh(int year = 2016){

	std::string year_s = to_string(year);

  	TString var = "n_recotauh";
  	
  	int nbin = 5;
  	float xmin = 0.;
  	float xmax = 5.;
  	TString cut = "((recotauh_decayMode[0]!=5) && (recotauh_decayMode[0]!=6) && (recotauh_byVVVLooseDeepTau2017v2p1VSe[0]) && (recotauh_byVLooseDeepTau2017v2p1VSmu[0]) )";
  	TString file = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_nrecotauh_2lss1tau_"+year_s+".root";
	
  	datacard_maker(var,nbin,xmin,xmax,cut,file,true,year);

}

void datacard_maker_MEM_nomiss(int year = 2016){

	std::string year_s = to_string(year);

  	TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";
  	
  	int nbin = 10;
  	float xmin = 0.;
  	float xmax = 1.;

  	TString cut = "integration_type==0 && ((recotauh_decayMode[0]!=5) && (recotauh_decayMode[0]!=6) && (recotauh_byVVVLooseDeepTau2017v2p1VSe[0]) && (recotauh_byVLooseDeepTau2017v2p1VSmu[0]) )";
  	TString file = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_"+year_s+".root";
	
  	datacard_maker(var,nbin,xmin,xmax,cut,file,true,year);

}

void datacard_maker_MEM_miss(int year = 2016){

	std::string year_s = to_string(year);

  	TString var="Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)";
  
  	int nbin = 10;
  	float xmin = 0.;
  	float xmax = 1.;

  	TString cut = "integration_type==1 && ((recotauh_decayMode[0]!=5) && (recotauh_decayMode[0]!=6) && (recotauh_byVVVLooseDeepTau2017v2p1VSe[0]) && (recotauh_byVLooseDeepTau2017v2p1VSmu[0]) )";
  	TString file = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_"+year_s+".root";
	
  	datacard_maker(var,nbin,xmin,xmax,cut,file,true,year);

}

