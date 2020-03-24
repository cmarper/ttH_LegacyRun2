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

  TH1F h_Higgs = h_ttW;
  TH1F VH = h_from_cards_dir(datacards,dirs,"VH");
  TH1F ttVH = h_from_cards_dir(datacards,dirs,"ttVH");
  TH1F VBF = h_from_cards_dir(datacards,dirs,"VBF");
  TH1F ggH = h_from_cards_dir(datacards,dirs,"ggH");
  TH1F HH = h_from_cards_dir(datacards,dirs,"HH");
  h_Higgs.Add(&VH);
  h_Higgs.Add(&ttVH);
  h_Higgs.Add(&VBF);
  h_Higgs.Add(&ggH);
  h_Higgs.Add(&HH);
  h_Higgs.SetFillColor(kBlue);
  h_Higgs.SetLineColor(kBlack);

  TH1F h_tH = h_Higgs;
  //TH1F h_tH = h_ttW;
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

  TH1F h_ttH = h_tH;
  TH1F ttHww = h_from_cards_dir(datacards,dirs,"ttH_hww");
  TH1F ttHzz = h_from_cards_dir(datacards,dirs,"ttH_hzz");
  TH1F ttHtt = h_from_cards_dir(datacards,dirs,"ttH_htt");
  h_ttH.Add( &ttHww );
  h_ttH.Add( &ttHzz );
  h_ttH.Add( &ttHtt );
  h_ttH.SetFillColor(kOrange+10);
  h_ttH.SetLineColor(kBlack);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = h_from_cards_dir(datacards,dirs,"data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  double error=0;
  /*cout<<"Pre-fit Yields"<<endl;
  TH1F bkg = TTZ;
  bkg.Add(&TTW);
  bkg.Add(&TTZ);
  bkg.Add(&Higgs);
  bkg.Add(&tH);
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
  cout<<"tH :"<<tH.IntegralAndError(0,nbins,error);
  cout<<" +/- "<<error<<endl;
  cout<<"Other H :"<<Higgs.IntegralAndError(0,nbins,error);
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
  if(unblind) cout<<"Data obs : "<<h_data_obs.IntegralAndError(0,nbins,error)<<endl;*/

  TLegend* leg1=new TLegend(0.2,0.67,0.4,0.87);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.045);
  leg1->SetFillStyle(0); 
  leg1->AddEntry(&h_ttH,"ttH","f");
  leg1->AddEntry(&h_tH,"tH","f");
  leg1->AddEntry(&h_Higgs,"Other H proc.","f");
  if(unblind) leg1->AddEntry(&h_data_obs,"Data");

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
  (&h_tH)->Draw("histsame");
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

  (&h_ttH_error)->Draw("e2same");
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

  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");

  //h_ratio->SetLineColor(kBlack);
  h_ratio->SetLineColor(kWhite);
  h_ratio->SetMinimum(0.);
  h_ratio->SetMaximum(2.);
  if(unblind) h_ratio->SetLineColor(1);
  else h_ratio->SetLineColor(0);
  if(unblind) h_ratio->SetLineWidth(2);
  else h_ratio->SetLineWidth(0);
  if(!unblind) h_ratio->SetFillColor(0);
  if(!unblind) h_ratio->SetMarkerColor(0);

  h_ratio->Draw("ape0");

  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  if(!unblind) h_ratio_MC->SetLineColor(0);
  if(!unblind) h_ratio_MC->SetFillColor(0);
  //h_ratio_MC->SetFillStyle(3003);  
  
  //h_ratio_MC->Draw("e2same"); 

  h_ttH.GetYaxis()->SetTitleSize(22);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  h_ratio_MC->SetTitle("");
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  h_ratio_MC->GetYaxis()->SetLabelColor(0.);
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetLabelColor(0.);

  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43);
  axis2->SetLabelSize(20);
  axis2->Draw();
  
  h_ratio_MC->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(22);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  h_ratio_MC->GetXaxis()->SetTitleSize(22);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); 
  h_ratio_MC->GetXaxis()->SetLabelSize(20);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  h_ratio->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(22);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  
  h_ratio->GetXaxis()->SetTitleSize(22);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); 
  h_ratio->GetXaxis()->SetLabelSize(20);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");

  c->SaveAs("../plots/datacards/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/datacards/png/"+plotname+".png");

  return;

}

void plot_MEM_2lSS1tau_nomiss_2016(bool unblind=false){

  float luminosity = 35920.;

  vector<TString> datacards;
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2016.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2017.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_nomiss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
  datacards.push_back("/data_CMS/cms/mperez/ttH_Legacy/Oct19/datacards/2lss_1tau/datacard_MEM_miss_2lss1tau_2018.root");

  vector<TString> dirs;
  dirs.push_back("ttH_2lss_1tau");
  
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
