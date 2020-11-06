#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>
#include <TGaxis.h>
#include <TGraphAsymmErrors.h>

TH1F h_from_cards_dir(vector<TString> datacards, vector<TString> dir, TString proc_name){

  TH1F h;
  
  for(unsigned int i=0;i<datacards.size();i++){

    TFile* f = TFile::Open(datacards[i]);
    if(i==0)
      h = *(TH1F*)f->Get(dir[i]+"/"+proc_name);
    else
      h.Add( (TH1F*)f->Get(dir[i]+"/"+proc_name) );

    f->Close();

  }

  return h;

}

void plot_2lSS1tau(vector<TString> datacards, vector<TString> dirs, TString varname, TString plotname, float luminosity=0., bool ismiss=true, bool unblind=false){

  TH1F h_flips = h_from_cards_dir(datacards,dirs,"data_flips");
  TH1F flips= h_flips;
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  TH1F fakes = h_from_cards_dir(datacards,dirs,"data_fakes");
  h_fakes.Add( &fakes );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Convs = h_fakes;
  TH1F Convs = h_from_cards_dir(datacards,dirs,"Convs");
  h_Convs.Add( &Convs );
  h_Convs.SetFillColor(kOrange);
  h_Convs.SetLineColor(kBlack);

  TH1F h_Rares = h_Convs;
  TH1F Rares = h_from_cards_dir(datacards,dirs,"Rares");
  h_Rares.Add( &Rares );
  h_Rares.SetFillColor(kAzure-9);
  h_Rares.SetLineColor(kBlack);

  TH1F h_EWK = h_Rares;
  TH1F WZ = h_from_cards_dir(datacards,dirs,"WZ");
  TH1F ZZ = h_from_cards_dir(datacards,dirs,"ZZ");
  h_EWK.Add( &WZ );
  h_EWK.Add( &ZZ );
  h_EWK.SetFillColor(kViolet-4);
  h_EWK.SetLineColor(kBlack);

  TH1F h_ttZ = h_EWK;
  TH1F TTZ =  h_from_cards_dir(datacards,dirs,"TTZ");
  h_ttZ.Add( &TTZ );
  h_ttZ.SetFillColor(kSpring+2);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  TH1F TTW = h_from_cards_dir(datacards,dirs,"TTW");
  TH1F TTWW = h_from_cards_dir(datacards,dirs,"TTWW");
  h_ttW.Add( &TTW );
  h_ttW.Add( &TTWW );
  h_ttW.SetFillColor(kGreen-5);
  h_ttW.SetLineColor(kBlack);

  TH1F h_tH = h_ttW;
  TH1F tHQww = h_from_cards_dir(datacards,dirs,"tHq_hww");
  TH1F tHQzz = h_from_cards_dir(datacards,dirs,"tHq_hzz");
  TH1F tHQtt = h_from_cards_dir(datacards,dirs,"tHq_htt");
  TH1F tHWww = h_from_cards_dir(datacards,dirs,"tHW_hww");
  TH1F tHWzz = h_from_cards_dir(datacards,dirs,"tHW_hzz");
  TH1F tHWtt = h_from_cards_dir(datacards,dirs,"tHW_htt");
  h_tH.Add( &tHQww );
  h_tH.Add( &tHQzz );
  h_tH.Add( &tHQtt );
  h_tH.Add( &tHWww );
  h_tH.Add( &tHWzz );
  h_tH.Add( &tHWtt );
  h_tH.SetFillColor(kRed-3);
  h_tH.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_from_cards_dir(datacards,dirs,"ttH_hww");
  TH1F ttHzz = h_from_cards_dir(datacards,dirs,"ttH_hzz");
  h_ttH_boson.Add( &ttHzz );
  h_ttH_boson.SetFillColor(kWhite);
  h_ttH_boson.SetLineColor(kOrange);

  TH1F h_ttH_tautau = h_from_cards_dir(datacards,dirs,"ttH_htt");
  h_ttH_tautau.SetFillColor(kWhite);
  h_ttH_tautau.SetLineColor(kOrange);

  /*TLegend* leg1=new TLegend(0.2,0.67,0.4,0.87);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.045);
  leg1->SetFillStyle(0); 
  leg1->AddEntry(&h_ttH,"ttH","f");
  leg1->AddEntry(&h_tH,"tH","f");
  leg1->AddEntry(&h_Higgs,"Other H proc.","f");
  //if(unblind) leg1->AddEntry(&h_data_obs,"Data");

  TLegend* leg2=new TLegend(0.48,0.67,0.68,0.87);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.045);
  leg2->SetFillStyle(0); 
  leg2->AddEntry(&h_ttW,"ttW(W)","f");
  leg2->AddEntry(&h_ttZ,"ttZ","f");
  leg2->AddEntry(&h_EWK,"EWK","f");
  leg2->AddEntry(&h_Rares,"Rares","f");

  TLegend* leg3=new TLegend(0.7,0.67,0.9,0.87);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.045);
  leg3->SetFillStyle(0); 
  leg3->AddEntry(&h_Convs,"Conv.","f");
  leg3->AddEntry(&h_fakes_lines,"Fakes","f");
  leg3->AddEntry(&h_flips_lines,"Flips","f");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  TCanvas* c=new TCanvas("c","c",610,650);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0);
  pad1->Draw();
  pad1->cd();
  gPad->SetTicks();

  h_ttH.SetMaximum(1.2*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_tH)->Draw("hist");
  (&h_Higgs)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_EWK)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_Convs)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  //(&h_ttH_error)->Draw("e2same");
  if(unblind) (&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg1->Draw("same");
  leg2->Draw("same");
  leg3->Draw("same");

  //h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  if (!ismiss) h_ttH.GetYaxis()->SetRangeUser(0,5.5);
  else if (ismiss) h_ttH.GetYaxis()->SetRangeUser(0,21);

  TLatex tex;
  tex.SetTextSize(0.05);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.65,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  TLatex tex2;
  tex2.SetTextSize(0.045);
  tex2.DrawLatexNDC(0.61,0.60,"#bf{2lss + 1#tau_{h}}");

  TLatex tex3;
  tex3.SetTextSize(0.045);
  if(!ismiss) tex3.DrawLatexNDC(0.58,0.54,"#bf{no-missing-jet}");
  else if(ismiss) tex3.DrawLatexNDC(0.60,0.54,"#bf{missing-jet}");

  h_ttH.GetYaxis()->SetLabelSize(0.);
  h_ttH.GetYaxis()->SetLabelColor(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(20);
  axis->Draw();

  c->cd(); 
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd(); 
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  c->SaveAs("../plots/datacards/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/datacards/png/"+plotname+".png");*/

  return;

}

void plot_MEM_2lSS1tau_nomiss_2016(bool unblind=false){

  float luminosity = 35920.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacards_MEM_syst_4Apr/datacard_MEM_nomiss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau_nomiss");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2016",
		luminosity,
    false,
    unblind);

}

void plot_MEM_2lSS1tau_miss_2016(bool unblind=false){

  float luminosity = 35920.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacards_MEM_syst_4Apr/datacard_MEM_miss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau_miss");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2016",
		luminosity,
    true,
    unblind);

}

void plot_MEM_2lSS1tau_nomiss_2017(bool unblind=false){

  float luminosity = 41530.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacards_MEM_syst_4Apr/datacard_MEM_nomiss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau_nomiss");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2017",
		luminosity,
    false,
    unblind);

}

void plot_MEM_2lSS1tau_miss_2017(bool unblind=false){

  float luminosity = 41530.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacards_MEM_syst_4Apr/datacard_MEM_miss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau_miss");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2017",
		luminosity,
    true,
    unblind);

}

void plot_MEM_2lSS1tau_nomiss_2018(bool unblind=false){

  float luminosity = 59740.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacards_MEM_syst_4Apr/datacard_MEM_nomiss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau_nomiss");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2018",
		luminosity,
    false,
    unblind);

}

void plot_MEM_2lSS1tau_miss_2018(bool unblind=false){

  float luminosity = 59740.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacards_MEM_syst_4Apr/datacard_MEM_miss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau_miss");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2018",
		luminosity,
    true,
    unblind);

}

void plot_all(bool unblind=false){

	plot_MEM_2lSS1tau_nomiss_2016(unblind);
	plot_MEM_2lSS1tau_miss_2016(unblind);

	plot_MEM_2lSS1tau_nomiss_2017(unblind);
	plot_MEM_2lSS1tau_miss_2017(unblind);

	plot_MEM_2lSS1tau_nomiss_2018(unblind);
	plot_MEM_2lSS1tau_miss_2018(unblind);

}
