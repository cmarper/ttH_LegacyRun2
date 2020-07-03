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


void plot_mu_comb(){

  double mu_2lss = +0.535;  
  double mu_2lss_m1s = 0.327;
  double mu_2lss_p1s = 0.360;
  cout<<"Mu 2lss = "<<mu_2lss<<" +"<<mu_2lss_p1s<<"/-"<<mu_2lss_m1s<<endl;

  double mu_2lss1tau = +0.853;  
  double mu_2lss1tau_m1s = 0.406;
  double mu_2lss1tau_p1s = 0.484;
  cout<<"Mu 2lss1tau = "<<mu_2lss1tau<<" +"<<mu_2lss1tau_p1s<<"/-"<<mu_2lss1tau_m1s<<endl;

  double mu_3l = +1.289;  
  double mu_3l_m1s = 0.392;
  double mu_3l_p1s = 0.537;
  cout<<"Mu 3l = "<<mu_3l<<" +"<<mu_3l_p1s<<"/-"<<mu_3l_m1s<<endl;

  double mu_4l = +1.513;  
  double mu_4l_m1s = 1.336;
  double mu_4l_p1s = 1.754;
  cout<<"Mu 4l = "<<mu_4l<<" +"<<mu_4l_p1s<<"/-"<<mu_4l_m1s<<endl;

  double mu_comb = +0.910;  
  double mu_comb_m1s = 0.259;
  double mu_comb_m1s_stat = 0.209;
  double mu_comb_p1s = 0.299;
  double mu_comb_p1s_stat = 0.215;
  cout<<"Mu comb = "<<mu_comb<<" +"<<mu_comb_p1s<<"/-"<<mu_comb_m1s<<endl;

  double y_2lss = 8;
  double y_3l = 4;
  double y_2lss1tau = 6;
  double y_4l = 2;

  double y_comb=4.5;

  TGraphAsymmErrors* gr_mu_2lss=new TGraphAsymmErrors();
  gr_mu_2lss->SetPoint(0,mu_2lss,y_2lss);
  gr_mu_2lss->SetPointError(0,mu_2lss_m1s,mu_2lss_p1s,0,0); 
  gr_mu_2lss->SetLineWidth(3);
  gr_mu_2lss->SetLineColor(kRed);
  gr_mu_2lss->SetMarkerStyle(21);
  gr_mu_2lss->SetMarkerSize(1.5);

  TGraphAsymmErrors* gr_mu_3l=new TGraphAsymmErrors();
  gr_mu_3l->SetPoint(0,mu_3l,y_3l);
  gr_mu_3l->SetPointError(0,mu_3l_m1s,mu_3l_p1s,0,0); 
  gr_mu_3l->SetLineWidth(3);
  gr_mu_3l->SetLineColor(kRed);
  gr_mu_3l->SetMarkerStyle(21);
  gr_mu_3l->SetMarkerSize(1.5);

  TGraphAsymmErrors* gr_mu_2lss1tau=new TGraphAsymmErrors();
  gr_mu_2lss1tau->SetPoint(0,mu_2lss1tau,y_2lss1tau);
  gr_mu_2lss1tau->SetPointError(0,mu_2lss1tau_m1s,mu_2lss1tau_p1s,0,0); 
  gr_mu_2lss1tau->SetLineWidth(3);
  gr_mu_2lss1tau->SetLineColor(kRed);
  gr_mu_2lss1tau->SetMarkerStyle(21);
  gr_mu_2lss1tau->SetMarkerSize(1.5);

  TGraphAsymmErrors* gr_mu_4l=new TGraphAsymmErrors();
  gr_mu_4l->SetPoint(0,mu_4l,y_4l);
  gr_mu_4l->SetPointError(0,mu_4l_m1s,mu_4l_p1s,0,0); 
  gr_mu_4l->SetLineWidth(3);
  gr_mu_4l->SetLineColor(kRed);
  gr_mu_4l->SetMarkerStyle(21);
  gr_mu_4l->SetMarkerSize(1.5);

  TGraphAsymmErrors* gr_mu_comb_stat=new TGraphAsymmErrors();
  gr_mu_comb_stat->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb_stat->SetPointError(0,mu_comb_m1s_stat,mu_comb_p1s_stat,y_comb,y_comb);
  gr_mu_comb_stat->SetLineWidth(2);
  gr_mu_comb_stat->SetMarkerSize(0);
  gr_mu_comb_stat->SetFillColor(kCyan);

  TGraphAsymmErrors* gr_mu_comb_syst=new TGraphAsymmErrors();
  gr_mu_comb_syst->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb_syst->SetPointError(0,mu_comb_m1s,mu_comb_p1s,y_comb,y_comb);
  gr_mu_comb_syst->SetLineWidth(2);
  gr_mu_comb_syst->SetMarkerSize(0);
  gr_mu_comb_syst->SetFillColor(kGreen);

  TGraphAsymmErrors* gr_mu_comb=new TGraphAsymmErrors();
  gr_mu_comb->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb->SetPointError(0,0,0,y_comb,y_comb);
  gr_mu_comb->SetLineWidth(3);
  gr_mu_comb->SetMarkerSize(0);

    
  TCanvas* c=new TCanvas("c","c",750,700);
  c->SetLeftMargin(0.25);
  c->SetBottomMargin(0.15);

  gStyle->SetEndErrorSize(0);
  gr_mu_comb_syst->Draw("AE2");
  gr_mu_comb_stat->Draw("E2same");
  gr_mu_comb->Draw("Psame");
  gr_mu_2lss->Draw("Psame");
  gr_mu_3l->Draw("Psame");
  gr_mu_2lss1tau->Draw("Psame");
  gr_mu_4l->Draw("Psame");
  gPad->RedrawAxis();
  
  gr_mu_comb_syst->GetXaxis()->SetLimits(-1.5,3.5);
  gr_mu_comb_syst->GetYaxis()->SetRangeUser(0,11);
  gr_mu_comb_syst->GetYaxis()->SetLabelSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickSize(0);
  gr_mu_comb_syst->GetXaxis()->SetTitle("Best fit #mu(t#bar{t}H)");
  gr_mu_comb_syst->GetXaxis()->SetTitleOffset(1.3);


  double luminosity=137000;
  TLatex tex;
  tex.SetTextSize(0.035);
  tex.DrawLatexNDC(0.26,0.91,"CMS");
  tex.DrawLatexNDC(0.68,0.91,"#bf{137 fb^{-1} (13 TeV)}");

  tex.SetTextSize(0.035);
  tex.DrawLatex(-3.10,y_2lss+0.3,"2lss + 0#tau_{h}");
  tex.DrawLatex(-3.10,y_2lss-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss,mu_2lss_p1s,mu_2lss_m1s));
  tex.DrawLatex(-3.10,y_3l+0.3,"3l + 0#tau_{h}");
  tex.DrawLatex(-3.10,y_3l-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_3l,mu_3l_p1s,mu_3l_m1s));
  tex.DrawLatex(-3.10,y_2lss1tau+0.3,"2lss + 1#tau_{h}");
  tex.DrawLatex(-3.10,y_2lss1tau-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss1tau,mu_2lss1tau_p1s,mu_2lss1tau_m1s));
  tex.DrawLatex(-3.10,y_4l+0.3,"4l + 0#tau_{h}");
  tex.DrawLatex(-3.10,y_4l-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_4l,mu_4l_p1s,mu_4l_m1s));

  double mu_comb_m1s_syst=sqrt(mu_comb_m1s*mu_comb_m1s-mu_comb_m1s_stat*mu_comb_m1s_stat);
  double mu_comb_p1s_syst=sqrt(mu_comb_p1s*mu_comb_p1s-mu_comb_p1s_stat*mu_comb_p1s_stat);

  tex.SetTextSize(0.040);
  tex.DrawLatex(-1.20,10,Form("#mu = %.2f ^{+%.2f}_{-%.2f}  #bf{#left[ {}^{+%.2f}_{-%.2f} (syst.) {}^{+%.2f}_{-%.2f} (stat.) #right]}",mu_comb,mu_comb_p1s,mu_comb_m1s,mu_comb_p1s_syst,mu_comb_m1s_syst,mu_comb_p1s_stat,mu_comb_m1s_stat));
  
  c->SaveAs("mu_ttH_obs.pdf");
  c->SaveAs("mu_ttH_obs.png");

  return;


}
