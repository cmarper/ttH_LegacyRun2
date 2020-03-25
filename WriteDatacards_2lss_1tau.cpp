#include <string>
#include <map>
#include <set>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include "boost/program_options.hpp"
#include <TString.h>
#include "CombineHarvester/CombineTools/interface/CombineHarvester.h"
#include "CombineHarvester/CombineTools/interface/Observation.h"
#include "CombineHarvester/CombineTools/interface/Process.h"
#include "CombineHarvester/CombineTools/interface/Utilities.h"
#include "CombineHarvester/CombineTools/interface/Systematics.h"
#include "CombineHarvester/CombineTools/interface/BinByBin.h"

using namespace std;
using boost::starts_with;
namespace po = boost::program_options;

int main(int argc, char** argv) {

  // input_file -i, output_file -o, bin_name -b
  std::string input_file, output_file, bin_name;
  double lumi = -1.;
  bool add_shape_sys = true;
  int year = 2016;
  po::variables_map vm;
  po::options_description config("configuration");
  config.add_options()
    ("input_file,i", po::value<string>(&input_file)->default_value("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2016.root"))
    ("output_file,o", po::value<string>(&output_file)->default_value("ttH_2lss_1tau.root"))
    ("lumi,l", po::value<double>(&lumi)->default_value(lumi))
    ("add_shape_sys,s", po::value<bool>(&add_shape_sys)->default_value(true))
    ("bin_name,b", po::value<string>(&bin_name)->default_value("ttH_2lss_1tau"))
    ("year,y", po::value<int>(&year)->default_value(2016));
  po::store(po::command_line_parser(argc, argv).options(config).run(), vm);
  po::notify(vm);

  std::string year_s;
  if(year==2016) year_s = "16";
  else if(year==2017) year_s = "17";
  else if(year==2018) year_s = "18";

  //! [part1]
  // Location of the "auxiliaries" directory where we can source the input files containing the datacard shapes
  string aux_shapes = "/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/";
  if ( input_file.find_first_of("/") == 0 ) aux_shapes = ""; // set aux_shapes directory to zero in case full path to input file is given on command line
 
  // Create an empty CombineHarvester instance that will hold all of the datacard configuration and histograms etc.
  ch::CombineHarvester cb;
  // Uncomment this next line to see a *lot* of debug information
  // cb.SetVerbosity(3);

  // Define the categories. Each entry in the vector below specifies a bin name and corresponding bin_id.
  ch::Categories cats = {
    {1, bin_name} //{1, "ttH_2lss_1tau"}
  };
  //! [part1]

  //! [part2]
  vector<string> masses = {"*"};
  //! [part2]

  // Add observations for unblinding
  //! [part3] 
  //cb.AddObservations({"*"}, {"ttHl"}, {"13TeV"}, {"*"}, cats);
  //! [part3]

  // Add observations for unblinding
  //! [part4]
  vector<string> bkg_procs = {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs","data_fakes","data_flips"};
  cb.AddProcesses({"*"}, {"*"}, {"13TeV"}, {"*"}, bkg_procs, cats, false);

  vector<string> sig_procs = {"ttH_hww","ttH_hzz","ttH_htt","tHq_hww","tHq_hzz","tHq_htt","tHW_hww","tHW_hzz","tHW_htt"};
  cb.AddProcesses(masses, {"*"}, {"13TeV"}, {"*"}, sig_procs, cats, true);
  //! [part4]

  using ch::syst::SystMap;
  using ch::syst::SystMapAsymm;
  using ch::syst::era;
  using ch::syst::bin_id;
  using ch::syst::process;

  //! [part5]

  // Luminosity https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM#LumiComb
  if(year==2016){
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_2016", "lnN", SystMap<>::init(1.022));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_XY", "lnN", SystMap<>::init(1.009));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_BBD", "lnN", SystMap<>::init(1.004));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_DB", "lnN", SystMap<>::init(1.005));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_GS", "lnN", SystMap<>::init(1.004));
  }
  else if (year==2017){
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_2017", "lnN", SystMap<>::init(1.020));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_XY", "lnN", SystMap<>::init(1.008));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_LS", "lnN", SystMap<>::init(1.003));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_BBD", "lnN", SystMap<>::init(1.004));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_DB", "lnN", SystMap<>::init(1.005));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_BCC", "lnN", SystMap<>::init(1.003));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_GS", "lnN", SystMap<>::init(1.001));
  }
  else if (year==2018){
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_2018", "lnN", SystMap<>::init(1.015));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_XY", "lnN", SystMap<>::init(1.020));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_LS", "lnN", SystMap<>::init(1.002));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "lumi_13TeV_BCC", "lnN", SystMap<>::init(1.002));
  }

  // Prefiring
  if(year==2016 || year==2017){
    if ( add_shape_sys ) {
      cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
          .AddSyst(cb, "CMS_ttHl"+year_s+"_L1PreFiring", "shape", SystMap<>::init(1.0));
    }
  }

  // Pileup
  if ( add_shape_sys ) {
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
        .AddSyst(cb, "CMS_ttHl_pileup", "shape", SystMap<>::init(1.0));
  }

  // Theoretical ttH
  cb.cp().process({"ttH_hww","ttH_hzz","ttH_htt"})
    .AddSyst(cb, "pdf_Higgs_ttH", "lnN", SystMap<>::init(1.036));
  cb.cp().process({"ttH_hww","ttH_hzz","ttH_htt"})
    .AddSyst(cb, "QCDscale_ttH", "lnN", SystMapAsymm<>::init(0.907, 1.058));
  if ( add_shape_sys ) {
    cb.cp().process({"ttH_hww","ttH_hzz","ttH_htt"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_ttH", "shape", SystMap<>::init(1.0));
  }

  // Theoretical tHq
  cb.cp().process({"tHq_hww","tHq_hzz","tHq_htt"})
    .AddSyst(cb, "pdf_qg", "lnN", SystMap<>::init(1.01));
  cb.cp().process({"tHq_hww","tHq_hzz","tHq_htt"})
    .AddSyst(cb, "QCDscale_tHq", "lnN", SystMapAsymm<>::init(0.933, 1.041));
  if ( add_shape_sys ) {
    cb.cp().process({"tHq_hww","tHq_hzz","tHq_htt"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_tHq", "shape", SystMap<>::init(1.0));
  }

  // Theoretical tHW
  cb.cp().process({"tHW_hww","tHW_hzz","tHW_htt"})
    .AddSyst(cb, "pdf_qg", "lnN", SystMap<>::init(1.027));
  cb.cp().process({"tHW_hww","tHW_hzz","tHW_htt"})
    .AddSyst(cb, "QCDscale_tHW", "lnN", SystMapAsymm<>::init(0.939, 1.046));
  if ( add_shape_sys ) {
    cb.cp().process({"tHW_hww","tHW_hzz","tHW_htt"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_tHW", "shape", SystMap<>::init(1.0));
  }

  // Theoretical Higgs BR
  cb.cp().process({"ttH_hww","tHq_hww","tHW_hww"})
    .AddSyst(cb, "BR_hww", "lnN", SystMap<>::init(1.0154));
  cb.cp().process({"ttH_hzz","tHq_hzz","tHW_hzz"})
    .AddSyst(cb, "BR_hzz", "lnN", SystMap<>::init(1.0154));
  cb.cp().process({"ttH_htt","tHq_htt","tHW_htt"})
    .AddSyst(cb, "BR_htt", "lnN", SystMap<>::init(1.0165));

  // Theoretical ttW
  cb.cp().process({"TTW"})
    .AddSyst(cb, "pdf_qqbar", "lnN", SystMap<>::init(1.04));
  cb.cp().process({"TTW"})
    .AddSyst(cb, "QCDscale_ttW", "lnN", SystMapAsymm<>::init(0.885, 1.129));
  if ( add_shape_sys ) {
    cb.cp().process({"TTW"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_ttW", "shape", SystMap<>::init(1.0));
  }

  // Theoretical ttWW
  cb.cp().process({"TTWW"})
    .AddSyst(cb, "pdf_TTWW", "lnN", SystMap<>::init(1.03));
  cb.cp().process({"TTWW"})
    .AddSyst(cb, "QCDscale_ttWW", "lnN", SystMapAsymm<>::init(0.891, 1.081));
  /*if ( add_shape_sys ) {
    cb.cp().process({"TTWW"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_ttWW", "shape", SystMap<>::init(1.0));
  }*/

  // Theoretical ttZ
  cb.cp().process({"TTZ"})
    .AddSyst(cb, "pdf_gg", "lnN", SystMap<>::init(0.966));
  cb.cp().process({"TTW"})
    .AddSyst(cb, "QCDscale_ttZ", "lnN", SystMapAsymm<>::init(0.904, 1.112));
  if ( add_shape_sys ) {
    cb.cp().process({"TTZ"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_ttZ", "shape", SystMap<>::init(1.0));
  }

  // Theoretical WZ
  if ( add_shape_sys ) {
    cb.cp().process({"WZ"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_WZ", "shape", SystMap<>::init(1.0));
  }

  // Theoretical ZZ
  if ( add_shape_sys ) {
    cb.cp().process({"ZZ"})
      .AddSyst(cb, "CMS_ttHl_thu_shape_ZZ", "shape", SystMap<>::init(1.0));
  }

  // Normalization EWK
  cb.cp().process({"WZ"})
    .AddSyst(cb, "CMS_ttHl_WZ_lnU", "lnU", SystMap<>::init(1.3));
  cb.cp().process({"ZZ"})
    .AddSyst(cb, "CMS_ttHl_ZZ_lnU", "lnU", SystMap<>::init(3.0));
  if ( add_shape_sys ) {
    cb.cp().process({"WZ","ZZ"})
      .AddSyst(cb, "CMS_ttHl_EWK_jet", "shape", SystMap<>::init(1.0));
  }

  // Normalization Rares
  cb.cp().process({"Rares"})
    .AddSyst(cb, "CMS_ttHl_Rares", "lnN", SystMap<>::init(1.5));

  // Normalization Convs
  cb.cp().process({"Convs"})
    .AddSyst(cb, "CMS_ttHl_Convs", "lnN", SystMap<>::init(1.3));

  // Normalization fake leptons
  if ( add_shape_sys ) {

    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_FRe_be", "shape", SystMap<>::init(1.0));
    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_FRe_norm", "shape", SystMap<>::init(1.0));    
    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_FRe_pt", "shape", SystMap<>::init(1.0));

    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_FRm_be", "shape", SystMap<>::init(1.0));
    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_FRm_norm", "shape", SystMap<>::init(1.0));     
    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_FRm_pt", "shape", SystMap<>::init(1.0));

  }

  // Closure fake leptons
  cb.cp().process({"data_fakes"})
    .AddSyst(cb, "CMS_ttHl_Clos_e_norm", "lnN", SystMap<>::init(0.9)); //.AddSyst(cb, "CMS_ttHl_Clos_e_norm", "shape", SystMap<>::init(1.0)); //
  cb.cp().process({"data_fakes"})
    .AddSyst(cb, "CMS_ttHl_Clos_m_norm", "lnN", SystMap<>::init(1.2));  //.AddSyst(cb, "CMS_ttHl_Clos_m_norm", "shape", SystMap<>::init(1.0));

  if ( add_shape_sys ) {

    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_Clos_e_shape", "shape", SystMap<>::init(1.0));
    cb.cp().process({"data_fakes"})
      .AddSyst(cb, "CMS_ttHl_Clos_m_shape", "shape", SystMap<>::init(1.0)); 

  }

  // Normalization fake taus MC
  if ( add_shape_sys ) {

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_ttHl"+year_s"+_FRjt_norm", "shape", SystMap<>::init(1.0));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_ttHl"+year_s"+_FRjt_shape", "shape", SystMap<>::init(1.0));

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_ttHl_FRjtMC_shape", "shape", SystMap<>::init(1.0));

  }

  // Normalization flips
  cb.cp().process({"data_flips"})
    .AddSyst(cb, "CMS_ttHl_QF", "lnN", SystMap<>::init(1.3));

  // Trigger
  if ( add_shape_sys ) {

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_ttHl"+year_s"+_trigger_ee", "shape", SystMap<>::init(1.0));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_ttHl"+year_s"+_trigger_em", "shape", SystMap<>::init(1.0));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_ttHl"+year_s"+_trigger_mm", "shape", SystMap<>::init(1.0));

  }

  // Lepton ID
  if ( add_shape_sys ) {

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_eff_ttHl_eloose", "shape", SystMap<>::init(1.0));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_eff_ttHl_mloose", "shape", SystMap<>::init(1.0));

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_eff_ttHl_mtight", "shape", SystMap<>::init(1.0));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_eff_ttHl_etight", "shape", SystMap<>::init(1.0));

  }

  // Tau ID
  if ( add_shape_sys ) {

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_eff_t", "shape", SystMap<>::init(1.0));

  }

  // TES and JEC
  if ( add_shape_sys ) {

    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_scale_j", "shape", SystMap<>::init(1.0));
    cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
      .AddSyst(cb, "CMS_scale_t", "shape", SystMap<>::init(1.0));

  }

  // b-tagging
  if ( add_shape_sys ) {
   for ( auto s : {"HF", "LF", "cErr1", "cErr2"} ) {
      cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
          .AddSyst(cb, Form("CMS_ttHl_btag_%s", s), "shape", SystMap<>::init(1.0));
    }
    for ( auto s : {"HFStats1", "HFStats2", "LFStats1", "LFStats2"} ) {
      cb.cp().process(ch::JoinStr({sig_procs, {"TTZ","TTW","TTWW","WZ","ZZ","Rares","Convs"}}))
          .AddSyst(cb, Form("CMS_ttHl"+year_s"+_btag_%s", s), "shape", SystMap<>::init(1.0));
    } 
  }

  // Unclustered energy
  cb.cp().process({"tHq_hww"})
    .AddSyst(cb, "CMS_ttHl_UnclusteredEn", "lnN", SystMapAsymm<>::init(0.999,1.001));
  cb.cp().process({"tHW_hww"})
    .AddSyst(cb, "CMS_ttHl_UnclusteredEn", "lnN", SystMapAsymm<>::init(1.000,1.001));
  cb.cp().process({"tHW_htt"})
    .AddSyst(cb, "CMS_ttHl_UnclusteredEn", "lnN", SystMapAsymm<>::init(0.999,1.001));

  //! [part6]

  //! [part7]
  cb.cp().backgrounds().ExtractShapes(
      aux_shapes + input_file,
      "ttH_2lss_1tau/$PROCESS",
      "ttH_2lss_1tau/$PROCESS_$SYSTEMATIC");
  cb.cp().signals().ExtractShapes(
      aux_shapes + input_file,
      "ttH_2lss_1tau/$PROCESS",
      "ttH_2lss_1tau/$PROCESS_$SYSTEMATIC");
  //! [part7]

  // Scale yield of all signal and background processes by lumi/2.3, with 2.3 corresponding to integrated luminosity of 2015 dataset
  if ( lumi > 0. ) {  
    std::cout << "scaling signal and background yields to L=" << lumi << "fb^-1 @ 13 TeV." << std::endl;
    cb.cp().process(ch::JoinStr({sig_procs, {"TTW", "TTZ", "WZ", "Rares", "fakes_data", "flips_data"}})).ForEachProc([&](ch::Process* proc) {
      proc->set_rate(proc->rate()*lumi/2.3);
    });
  }

  //! [part8]
  auto bbb = ch::BinByBinFactory()
    .SetAddThreshold(0.1)
    .SetFixNorm(true);
  bbb.SetPattern("CMS_$BIN_$PROCESS_bin_$#");
  bbb.AddBinByBin(cb.cp().backgrounds(), cb);

  // This function modifies every entry to have a standardised bin name of the form: {analysis}_{channel}_{bin_id}_{era} which is commonly used in the htt analyses
  //ch::SetStandardBinNames(cb);
  //! [part8]

  //! [part9]
  // First we generate a set of bin names:
  set<string> bins = cb.bin_set();
  // This method will produce a set of unique bin names by considering all Observation, Process and Systematic entries in the CombineHarvester instance.

  // We create the output root file that will contain all the shapes.
  TFile output(output_file.data(), "RECREATE");

  // Finally we iterate through bins and write a datacard.
  for (auto b : bins) {
    cout << ">> Writing datacard for bin: " << b << "\n";
    // We need to filter on both the mass and the mass hypothesis, where we must remember to include the "*" mass entry to get all the data and backgrounds.
    //cb.cp().bin({b}).mass({"*"}).WriteDatacard(b + ".txt", output);
    cb.cp().bin({b}).mass({"*"}).WriteDatacard(
        TString(output_file.data()).ReplaceAll(".root", ".txt").Data(), output);				       
  }
  //! [part9]

}

