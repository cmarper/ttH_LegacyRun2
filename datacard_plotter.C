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
    	//h = *(TH1F*)f->Get(proc_name);
    else
      h.Add( (TH1F*)f->Get(dir[i]+"/"+proc_name) );
      //h.Add( (TH1F*)f->Get(proc_name) );

    f->Close();

  }

  return h;

}

void plot_2lSS1tau(vector<TString> datacards, vector<TString> dirs, TString varname, TString plotname, int lumi=0, float luminosity=0.){

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
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_EWK = h_Rares;
  TH1F EWK = h_from_cards_dir(datacards,dirs,"EWK");
  h_EWK.Add( &EWK );
  h_EWK.SetFillColor(kViolet-4);
  h_EWK.SetLineColor(kBlack);

  TH1F h_ttZ = h_EWK;
  TH1F TTZ =  h_from_cards_dir(datacards,dirs,"TTZ");
  h_ttZ.Add( &TTZ );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  TH1F TTW = h_from_cards_dir(datacards,dirs,"TTW");
  h_ttW.Add( &TTW );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_tH = h_ttW;
  TH1F tH = h_from_cards_dir(datacards,dirs,"TH");
  h_tH.Add( &tH );
  h_tH.SetFillColor(kRed+3);
  h_tH.SetLineColor(kBlack);

  TH1F h_ttH = h_tH;
  TH1F ttH = h_from_cards_dir(datacards,dirs,"TTH");
  h_ttH.Add( &ttH );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  /*TH1F h_data_obs = h_from_cards_dir(datacards,dirs,"data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);*/

  double error=0;
  cout<<"Pre-fit Yields"<<endl;
  TH1F bkg = TTZ;
  bkg.Add(&TTW);
  bkg.Add(&TTZ);
  bkg.Add(&EWK);
  bkg.Add(&Rares);
  bkg.Add(&Convs);
  bkg.Add(&fakes);
  bkg.Add(&flips);
  TH1F SM = bkg;
  SM.Add(&ttH);
  double nbins = ttH.GetNbinsX();
  cout<<"ttH :"<<ttH.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"ttZ :"<<TTZ.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"ttW :"<<TTW.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"EWK :"<<EWK.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"Rares :"<<Rares.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"Convs :"<<Convs.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;  
  cout<<"Flips : "<<flips.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"Fakes : "<<fakes.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"Total bkg : "<<bkg.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"SM expectation : "<<SM.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  //cout<<"Data obs : "<<h_data_obs.IntegralAndError(0,nbins,error)<<endl;

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_EWK,"EWK");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_Convs,"Conv.");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  //h_ttH.SetMaximum(1.2*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_EWK)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_Convs)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));

  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  //double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  //double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  //pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");

  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);
  
  h_ratio->Draw("ape0");       // Draw the ratio plot

  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  //h_ratio_MC->Draw("e2same"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");

  c->SaveAs("../plots/datacards/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/datacards/png/"+plotname+".png");

  return;

}

void plot_MEM_2lSS1tau_nomiss_2016(){

  float luminosity = 35920.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2016",
		luminosity);

}

void plot_MEM_2lSS1tau_miss_2016(){

  float luminosity = 35920.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2016",
		luminosity);

}

void plot_MEM_2lSS1tau_nomiss_2017(){

  float luminosity = 41530.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2017",
		luminosity);

}

void plot_MEM_2lSS1tau_miss_2017(){

  float luminosity = 41530.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_miss_2017",
		luminosity);

}

void plot_MEM_2lSS1tau_nomiss_2018(){

  float luminosity = 59740.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
  plot_2lSS1tau(datacards,dirs,
		"MEM LR",
		"MEM_LR_nomiss_2018",
		luminosity);

}

void plot_MEM_2lSS1tau_miss_2018(){

  float luminosity = 59740.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
