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
      //h = *(TH1F*)f->Get(dir[i]+"/"+proc_name);
    	h = *(TH1F*)f->Get(proc_name);
    else
      //h.Add( (TH1F*)f->Get(dir[i]+"/"+proc_name) );
      h.Add( (TH1F*)f->Get(proc_name) );

    f->Close();
  }

  return h;

}

void plot_2lSS1tau(vector<TString> datacards, vector<TString> dirs, TString varname, TString plotname, int lumi=0, float luminosity=0.){

  /*TH1F h_flips = h_from_cards_dir(datacards,dirs,"data_flips");
  TH1F flips= h_flips;
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);*/

  //TH1F h_fakes = h_flips;
  //TH1F fakes = h_from_cards_dir(datacards,dirs,"data_fakes");

  cout<<datacards.at(0)<<endl;
  cout<<dirs.at(0)<<endl;

  TH1F h_fakes = h_from_cards_dir(datacards,dirs,"x_fakes_MC");
  TH1F fakes = h_fakes;
  h_fakes.Add( &fakes );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Convs = h_fakes;
  TH1F Convs = h_from_cards_dir(datacards,dirs,"x_Convs");
  h_Convs.Add( &Convs );
  h_Convs.SetFillColor(kOrange);
  h_Convs.SetLineColor(kBlack);

  TH1F h_Rares = h_Convs;
  TH1F Rares = h_from_cards_dir(datacards,dirs,"x_Rares");
  h_Rares.Add( &Rares );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_EWK = h_Rares;
  TH1F EWK = h_from_cards_dir(datacards,dirs,"x_WZ");
  TH1F ZZ = h_from_cards_dir(datacards,dirs,"x_ZZ");
  h_EWK.Add( &EWK );
  h_EWK.Add (&ZZ);
  h_EWK.SetFillColor(kViolet-4);
  h_EWK.SetLineColor(kBlack);

  TH1F h_ttZ = h_EWK;
  TH1F TTZ =  h_from_cards_dir(datacards,dirs,"x_TTZ");
  h_ttZ.Add( &TTZ );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  TH1F TTW = h_from_cards_dir(datacards,dirs,"x_TTW");
  h_ttW.Add( &TTW );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttWW = h_ttW;
  TH1F ttWW = h_from_cards_dir(datacards,dirs,"x_TTWW");
  h_ttWW.Add( &ttWW );
  h_ttWW.SetFillColor(kSpring-7);
  h_ttWW.SetLineColor(kBlack);

  TH1F h_tH = h_ttWW;
  TH1F tH = h_from_cards_dir(datacards,dirs,"x_THQ_hww");
  TH1F tHQhzz = h_from_cards_dir(datacards,dirs,"x_THQ_hzz");
  TH1F tHQhtt = h_from_cards_dir(datacards,dirs,"x_THQ_htt");
  TH1F tHWhww = h_from_cards_dir(datacards,dirs,"x_THW_hww");
  TH1F tHWhzz = h_from_cards_dir(datacards,dirs,"x_THW_hzz");
  TH1F tHWhtt = h_from_cards_dir(datacards,dirs,"x_THW_htt");
  tH.Add(&tHQhzz);
  tH.Add(&tHQhtt);
  tH.Add(&tHWhww);
  tH.Add(&tHWhzz);
  tH.Add(&tHWhtt);
  h_tH.Add( &tH );
  h_tH.SetFillColor(kOrange+8);
  h_tH.SetLineColor(kBlack);

  TH1F h_ttH = h_tH;
  TH1F ttH = h_from_cards_dir(datacards,dirs,"x_TTH_hww");
  TH1F ttHhzz = h_from_cards_dir(datacards,dirs,"x_TTH_hzz");
  TH1F ttHhtt = h_from_cards_dir(datacards,dirs,"x_TTH_htt");
  h_ttH.Add( &ttH );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);

  TLegend* leg=new TLegend(0.5,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_tH,"tH");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttWW,"ttWW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_EWK,"EWK");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_Convs,"Conv.");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  //leg->AddEntry(&h_flips_lines,"Flips");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  /*TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad*/
  gPad->SetTicks();

  (&h_ttH)->Draw("hist");
  (&h_ttW)->Draw("histsame");
  (&h_ttWW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_EWK)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  //(&h_Convs)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  //(&h_flips)->Draw("histsame"); 
  //(&h_flips_lines)->Draw("histsame"); 
  //(&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("esame");
  //(&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  gPad->SetTicks();

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.66,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.66,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);

  c->SaveAs("../plots/datacards/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/datacards/png/"+plotname+".png");

  return;

}

void plot_MEM_2lSS1tau_nomiss_2016(){

  float luminosity = 35900.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2016",
		luminosity);

}

void plot_MEM_2lSS1tau_miss_2016(){

  float luminosity = 35900.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2016",
		luminosity);

}

void plot_MEM_2lSS1tau_nomiss_2017(){

  float luminosity = 41400.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2017",
		luminosity);

}

void plot_MEM_2lSS1tau_miss_2017(){

  float luminosity = 41400.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2017",
		luminosity);

}

void plot_MEM_2lSS1tau_nomiss_2018(){

  float luminosity = 59700.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2018",
		luminosity);

}

void plot_MEM_2lSS1tau_miss_2018(){

  float luminosity = 59700.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2018",
		luminosity);

}

void plot_all(){

	plot_MEM_2lSS1tau_nomiss_2016();
	plot_MEM_2lSS1tau_miss_2016();

	plot_MEM_2lSS1tau_nomiss_2017();
	plot_MEM_2lSS1tau_miss_2017();

	plot_MEM_2lSS1tau_nomiss_2018();
	plot_MEM_2lSS1tau_miss_2018();

}
