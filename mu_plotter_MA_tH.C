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


void plot_mu_comb(int era){

  double mu_2lss = +3.18;  
  double mu_2lss_m1s = 4.83;
  double mu_2lss_p1s = 4.80;

  double mu_3l = +15.52;  
  double mu_3l_m1s = 7.65;
  double mu_3l_p1s = 8.12;

  double mu_2lss1tau = +8.06;  
  double mu_2lss1tau_m1s = 7.46;
  double mu_2lss1tau_p1s = 8.17;

  double mu_comb = +5.67;  
  double mu_comb_m1s = 3.98;
  double mu_comb_p1s = 4.05;
  double mu_comb_m1s_stat = 2.68;
  double mu_comb_p1s_stat = 2.75;
  double mu_comb_m1s_syst=2.95;
  double mu_comb_p1s_syst=2.98;

  if(era==0){

    mu_2lss = +3.18;  
    mu_2lss_m1s = 4.83;
    mu_2lss_p1s = 4.80;

    mu_3l = +15.52;  
    mu_3l_m1s = 7.65;
    mu_3l_p1s = 8.12;

    mu_2lss1tau = +8.06;  
    mu_2lss1tau_m1s = 7.46;
    mu_2lss1tau_p1s = 8.17;

    mu_comb = +5.67;  
    mu_comb_m1s = 3.98;
    mu_comb_p1s = 4.05;
    mu_comb_m1s_stat = 2.68;
    mu_comb_p1s_stat = 2.75;
    mu_comb_m1s_syst=2.95;
    mu_comb_p1s_syst=2.98;

  }

  else if(era==2016){

    mu_2lss = +10.21; 
    mu_2lss_m1s = 7.70; 
    mu_2lss_p1s = 8.00; 

    mu_3l = +0.46; 
    mu_3l_m1s = 11.31; 
    mu_3l_p1s = 12.66; 

    mu_2lss1tau = +5.13; 
    mu_2lss1tau_m1s = 9.47; 
    mu_2lss1tau_p1s = 11.28; 

    mu_comb = +7.26; 
    mu_comb_m1s = 6.10; 
    mu_comb_p1s = 6.47; 

  }

  else if(era==2017){

    mu_2lss = -9.21; 
    mu_2lss_m1s = 9.68; 
    mu_2lss_p1s = 10.73; 

    mu_3l = +21.63; 
    mu_3l_m1s = 14.11; 
    mu_3l_p1s = 8.37; 

    mu_2lss1tau = -9.12; 
    mu_2lss1tau_m1s = 15.05; 
    mu_2lss1tau_p1s = 15.52; 

    mu_comb = -1.09; 
    mu_comb_m1s = 8.52; 
    mu_comb_p1s = 7.57; 

  }

  else if(era==2018){

    mu_2lss = +3.88; 
    mu_2lss_m1s = 7.56; 
    mu_2lss_p1s = 7.60; 

    mu_3l = 21.68; 
    mu_3l_m1s = 12.16; 
    mu_3l_p1s = 8.32; 

    mu_2lss1tau = +12.79; 
    mu_2lss1tau_m1s = 10.49; 
    mu_2lss1tau_p1s = 11.88; 

    mu_comb = +8.25; 
    mu_comb_m1s = 6.14; 
    mu_comb_p1s = 6.32; 

  }

  double gap = 2.5;
  double y_2lss = 7;  
  double y_3l = y_2lss-1*gap;  
  double y_2lss1tau = y_2lss-2*gap;  

  double y_comb=4.5;

  TGraphAsymmErrors* gr_mu_2lss=new TGraphAsymmErrors();
  gr_mu_2lss->SetPoint(0,mu_2lss,y_2lss);
  gr_mu_2lss->SetPointError(0,mu_2lss_m1s,mu_2lss_p1s,0,0); 
  gr_mu_2lss->SetLineWidth(3);
  gr_mu_2lss->SetLineColor(kRed);
  gr_mu_2lss->SetMarkerStyle(21);
  gr_mu_2lss->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_3l=new TGraphAsymmErrors();
  gr_mu_3l->SetPoint(0,mu_3l,y_3l);
  gr_mu_3l->SetPointError(0,mu_3l_m1s,mu_3l_p1s,0,0); 
  gr_mu_3l->SetLineWidth(3);
  gr_mu_3l->SetLineColor(kRed);
  gr_mu_3l->SetMarkerStyle(21);
  gr_mu_3l->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_2lss1tau=new TGraphAsymmErrors();
  gr_mu_2lss1tau->SetPoint(0,mu_2lss1tau,y_2lss1tau);
  gr_mu_2lss1tau->SetPointError(0,mu_2lss1tau_m1s,mu_2lss1tau_p1s,0,0); 
  gr_mu_2lss1tau->SetLineWidth(3);
  gr_mu_2lss1tau->SetLineColor(kRed);
  gr_mu_2lss1tau->SetMarkerStyle(21);
  gr_mu_2lss1tau->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_comb_stat=new TGraphAsymmErrors();
  gr_mu_comb_stat->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb_stat->SetPointError(0,mu_comb_m1s_stat,mu_comb_p1s_stat,y_comb,y_comb);
  gr_mu_comb_stat->SetLineWidth(2);
  gr_mu_comb_stat->SetMarkerSize(0);
  gr_mu_comb_stat->SetFillColor(kGreen);

  TGraphAsymmErrors* gr_mu_comb_syst=new TGraphAsymmErrors();
  gr_mu_comb_syst->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb_syst->SetPointError(0,mu_comb_m1s,mu_comb_p1s,y_comb,y_comb);
  gr_mu_comb_syst->SetLineWidth(2);
  gr_mu_comb_syst->SetMarkerSize(0);
  gr_mu_comb_syst->SetFillColor(90);

  TGraphAsymmErrors* gr_mu_comb=new TGraphAsymmErrors();
  gr_mu_comb->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb->SetPointError(0,0,0,y_comb,y_comb);
  gr_mu_comb->SetLineWidth(3);
  gr_mu_comb->SetMarkerSize(0);

    
  TCanvas* c=new TCanvas("c","c",700,750);
  c->SetLeftMargin(0.25);
  c->SetBottomMargin(0.15);

  gStyle->SetEndErrorSize(0);
  gr_mu_comb_syst->Draw("AE2");
  gr_mu_comb_stat->Draw("E2same");
  gr_mu_comb->Draw("Psame");

  if(era!=0){
    gr_mu_comb_syst->SetFillColor(kGreen);
  }

  gr_mu_2lss->Draw("Psame");
  gr_mu_3l->Draw("Psame");
  gr_mu_2lss1tau->Draw("Psame");

  gr_mu_comb_syst->GetYaxis()->SetTickSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickLength(0.0);

  gPad->RedrawAxis();
  
  if(era==0)
    gr_mu_comb_syst->GetXaxis()->SetLimits(-14.9,28);
  else
    gr_mu_comb_syst->GetXaxis()->SetLimits(-49.9,34.9);

  gr_mu_comb_syst->GetYaxis()->SetRangeUser(0,11);
  gr_mu_comb_syst->GetYaxis()->SetLabelSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickLength(0.0);
  gr_mu_comb_syst->GetXaxis()->SetTitle("Best fit #mu(tH)");
  gr_mu_comb_syst->GetXaxis()->SetTitleOffset(1.3);

  gPad->RedrawAxis();

  double luminosity=137000;
  TLatex tex;
  tex.SetTextSize(0.035);
  tex.DrawLatexNDC(0.26,0.91,"CMS #bf{#it{Preliminary}}");

  if(era==0)
    tex.DrawLatexNDC(0.66,0.91,"#bf{137 fb^{-1} (13 TeV)}");
  else if(era==2016)
    tex.DrawLatexNDC(0.66,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");
  else if(era==2017)
    tex.DrawLatexNDC(0.66,0.91,"#bf{41.5 fb^{-1} (13 TeV)}");
  else if(era==2018)
    tex.DrawLatexNDC(0.66,0.91,"#bf{59.7 fb^{-1} (13 TeV)}");

  float scale = 1.0;
  if(era!=0) scale = 2.7;

  tex.SetTextSize(0.035);
  tex.DrawLatex(-27*scale,y_2lss+3,"Combined");

  tex.SetTextSize(0.035);
  tex.DrawLatex(-26*scale,y_2lss,"2lss + 0#tau_{h}");
  tex.DrawLatex(-26*scale,y_3l,"3l + 0#tau_{h}");
  tex.DrawLatex(-26*scale,y_2lss1tau,"2lss + 1#tau_{h}");

  if(era!=0) scale = 3.7;

  tex.SetTextSize(0.027);
  tex.DrawLatex(-13*scale,y_2lss,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss,mu_2lss_p1s,mu_2lss_m1s));
  tex.DrawLatex(-13*scale,y_3l,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_3l,mu_3l_p1s,mu_3l_m1s));
  tex.DrawLatex(-13*scale,y_2lss1tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss1tau,mu_2lss1tau_p1s,mu_2lss1tau_m1s));

  tex.SetTextSize(0.036);
  if(era==0)
    tex.DrawLatex(-13*scale,10,Form("#mu = %.2f ^{+%.2f}_{-%.2f} #bf{#left[ {}^{+%.2f}_{-%.2f} (stat) {}^{+%.2f}_{-%.2f} (syst) #right]}",mu_comb,mu_comb_p1s,mu_comb_m1s,mu_comb_p1s_stat,mu_comb_m1s_stat,mu_comb_p1s_syst,mu_comb_m1s_syst));
  else
    tex.DrawLatex(-13*scale,10,Form("#mu = %.2f ^{+%.2f}_{-%.2f}",mu_comb,mu_comb_p1s,mu_comb_m1s));

  TString erastring = std::to_string(era);
  c->SaveAs("test_mu_tH_"+erastring+"_2.pdf");
  c->SaveAs("test_mu_tH_"+erastring+"_2.root");

  return;


}
