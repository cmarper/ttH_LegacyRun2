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


  double mu_2lss;  
  double mu_2lss_m1s;  
  double mu_2lss_p1s;  

  double mu_3l;  
  double mu_3l_m1s;  
  double mu_3l_p1s;  

  double mu_2lss1tau;  
  double mu_2lss1tau_m1s;  
  double mu_2lss1tau_p1s;  

  double mu_1l2tau;  
  double mu_1l2tau_m1s;  
  double mu_1l2tau_p1s;  

  double mu_2los1tau;  
  double mu_2los1tau_m1s;
  double mu_2los1tau_p1s;

  double mu_3l1tau;  
  double mu_3l1tau_m1s;
  double mu_3l1tau_p1s;

  double mu_2l2tau;  
  double mu_2l2tau_m1s;
  double mu_2l2tau_p1s;

  double mu_4l;  
  double mu_4l_m1s;
  double mu_4l_p1s;

  double mu_2tau;  
  double mu_2tau_m1s;
  double mu_2tau_p1s;

  double mu_1l1tau;  
  double mu_1l1tau_m1s;
  double mu_1l1tau_p1s;

  double mu_comb;  
  double mu_comb_m1s;
  double mu_comb_m1s_stat;
  double mu_comb_p1s;
  double mu_comb_p1s_stat;
  double mu_comb_m1s_syst;
  double mu_comb_p1s_syst;


  if(era==0){

    mu_2lss = +1.01;  
    mu_2lss_m1s = 0.29;
    mu_2lss_p1s = 0.32;

    mu_3l = +1.53;  
    mu_3l_m1s = 0.38;
    mu_3l_p1s = 0.43;

    mu_2lss1tau = +0.62;  
    mu_2lss1tau_m1s = 0.62;
    mu_2lss1tau_p1s = 0.54;

    mu_1l2tau = +0.36;  
    mu_1l2tau_m1s = 0.44;
    mu_1l2tau_p1s = 0.51;

    mu_2los1tau = +0.49;  
    mu_2los1tau_m1s = 0.77;
    mu_2los1tau_p1s = 0.85;

    mu_3l1tau = +1.52;  
    mu_3l1tau_m1s = 0.94;
    mu_3l1tau_p1s = 1.11;

    mu_2l2tau = +0.00;  
    mu_2l2tau_m1s = 0.00;
    mu_2l2tau_p1s = 0.31;

    mu_4l = +1.28;  
    mu_4l_m1s = 1.25;
    mu_4l_p1s = 1.62;

    mu_2tau = +2.22;  
    mu_2tau_m1s = 2.10;
    mu_2tau_p1s = 2.18;

    mu_1l1tau = +1.80;  
    mu_1l1tau_m1s = 2.22;
    mu_1l1tau_p1s = 2.20;

    mu_comb = +0.92;  
    mu_comb_m1s = 0.23;
    mu_comb_m1s_stat = 0.19;
    mu_comb_p1s = 0.26;
    mu_comb_p1s_stat = 0.19;
    mu_comb_m1s_syst=0.13;
    mu_comb_p1s_syst=0.17;

  }

  else if(era==2016){

    mu_2lss = +1.44;  
    mu_2lss_m1s = 0.57;
    mu_2lss_p1s = 0.63;

    mu_3l = +1.76;  
    mu_3l_m1s = 0.73;
    mu_3l_p1s = 0.82;

    mu_2lss1tau = +1.67;  
    mu_2lss1tau_m1s = 0.89;
    mu_2lss1tau_p1s = 1.05;

    mu_1l2tau = +1.53;  
    mu_1l2tau_m1s = 1.32;
    mu_1l2tau_p1s = 1.66;

    mu_2los1tau = -0.76; 
    mu_2los1tau_m1s = 1.46; 
    mu_2los1tau_p1s = 1.71; 

    mu_3l1tau = +4.49; 
    mu_3l1tau_m1s = 2.06; 
    mu_3l1tau_p1s = 2.79; 

    mu_2l2tau = +0.00; 
    mu_2l2tau_m1s = 0.00; 
    mu_2l2tau_p1s = 1.33; 

    mu_4l = +2.71; 
    mu_4l_m1s = 2.30; 
    mu_4l_p1s = 3.47; 

    mu_2tau = -0.19; 
    mu_2tau_m1s = 4.28; 
    mu_2tau_p1s = 4.07; 

    mu_1l1tau = +3.34; 
    mu_1l1tau_m1s = 5.07; 
    mu_1l1tau_p1s = 4.84; 

    mu_comb = +1.57; 
    mu_comb_m1s = 0.45; 
    mu_comb_p1s = 0.50; 

  }

  else if(era==2017){

    mu_2lss = +1.00;  
    mu_2lss_m1s = 0.55;
    mu_2lss_p1s = 0.59;

    mu_3l = +1.57;  
    mu_3l_m1s = 0.68;
    mu_3l_p1s = 0.76;

    mu_2lss1tau = +0.62;  
    mu_2lss1tau_m1s = 0.82;
    mu_2lss1tau_p1s = 0.91;

    mu_1l2tau = -0.01;  
    mu_1l2tau_m1s = 0.62;
    mu_1l2tau_p1s = 0.87;

    mu_2los1tau = +0.96; 
    mu_2los1tau_m1s = 1.21; 
    mu_2los1tau_p1s = 1.42; 

    mu_3l1tau = +1.49; 
    mu_3l1tau_m1s = 1.46; 
    mu_3l1tau_p1s = 2.00; 

    mu_2l2tau = +0.00; 
    mu_2l2tau_m1s = 0.00; 
    mu_2l2tau_p1s = 1.47; 

    mu_4l = +0.28; 
    mu_4l_m1s = 1.84; 
    mu_4l_p1s = 3.01; 

    mu_2tau = +3.27; 
    mu_2tau_m1s = 3.58; 
    mu_2tau_p1s = 3.99; 

    mu_1l1tau = +6.49; 
    mu_1l1tau_m1s = 4.86; 
    mu_1l1tau_p1s = 3.51; 

    mu_comb = +0.90; 
    mu_comb_m1s = 0.40; 
    mu_comb_p1s = 0.44; 

  }

  else if(era==2018){

    mu_2lss = +0.87;  
    mu_2lss_m1s = 0.44;
    mu_2lss_p1s = 0.47;

    mu_3l = +1.64;  
    mu_3l_m1s = 0.59;
    mu_3l_p1s = 0.66;

    mu_2lss1tau = -0.34;  
    mu_2lss1tau_m1s = 0.57;
    mu_2lss1tau_p1s = 0.66;

    mu_1l2tau = +0.11;  
    mu_1l2tau_m1s = 0.57;
    mu_1l2tau_p1s = 0.69;

    mu_2los1tau = +0.74; 
    mu_2los1tau_m1s = 1.26; 
    mu_2los1tau_p1s = 1.42; 

    mu_3l1tau = -0.67; 
    mu_3l1tau_m1s = 0.95; 
    mu_3l1tau_p1s = 1.15; 

    mu_2l2tau = +0.00; 
    mu_2l2tau_m1s = 0.00; 
    mu_2l2tau_p1s = 0.52; 

    mu_4l = +0.29; 
    mu_4l_m1s = 1.82; 
    mu_4l_p1s = 2.73; 

    mu_2tau = +4.20; 
    mu_2tau_m1s = 3.33; 
    mu_2tau_p1s = 3.61; 

    mu_1l1tau = -1.15; 
    mu_1l1tau_m1s = 3.56; 
    mu_1l1tau_p1s = 3.25; 

    mu_comb = +0.58; 
    mu_comb_m1s = 0.33; 
    mu_comb_p1s = 0.36; 

  }

  double gap = 0.85;
  double y_2lss = 8.5;  
  double y_3l = y_2lss-1*gap;  
  double y_2lss1tau = y_2lss-2*gap;  
  double y_1l2tau = y_2lss-3*gap;  
  double y_2los1tau = y_2lss-4*gap;  
  double y_3l1tau = y_2lss-5*gap;  
  double y_2l2tau = y_2lss-6*gap;  
  double y_4l = y_2lss-7*gap;  
  double y_2tau = y_2lss-8*gap;  
  double y_1l1tau = y_2lss-9*gap;  

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

  TGraphAsymmErrors* gr_mu_1l2tau=new TGraphAsymmErrors();
  gr_mu_1l2tau->SetPoint(0,mu_1l2tau,y_1l2tau);
  gr_mu_1l2tau->SetPointError(0,mu_1l2tau_m1s,mu_1l2tau_p1s,0,0); 
  gr_mu_1l2tau->SetLineWidth(3);
  gr_mu_1l2tau->SetLineColor(kRed);
  gr_mu_1l2tau->SetMarkerStyle(21);
  gr_mu_1l2tau->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_2los1tau=new TGraphAsymmErrors();
  gr_mu_2los1tau->SetPoint(0,mu_2los1tau,y_2los1tau);
  gr_mu_2los1tau->SetPointError(0,mu_2los1tau_m1s,mu_2los1tau_p1s,0,0); 
  gr_mu_2los1tau->SetLineWidth(3);
  gr_mu_2los1tau->SetLineColor(kRed);
  gr_mu_2los1tau->SetMarkerStyle(21);
  gr_mu_2los1tau->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_3l1tau=new TGraphAsymmErrors();
  gr_mu_3l1tau->SetPoint(0,mu_3l1tau,y_3l1tau);
  gr_mu_3l1tau->SetPointError(0,mu_3l1tau_m1s,mu_3l1tau_p1s,0,0); 
  gr_mu_3l1tau->SetLineWidth(3);
  gr_mu_3l1tau->SetLineColor(kRed);
  gr_mu_3l1tau->SetMarkerStyle(21);
  gr_mu_3l1tau->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_2l2tau=new TGraphAsymmErrors();
  gr_mu_2l2tau->SetPoint(0,mu_2l2tau,y_2l2tau);
  gr_mu_2l2tau->SetPointError(0,mu_2l2tau_m1s,mu_2l2tau_p1s,0,0); 
  gr_mu_2l2tau->SetLineWidth(3);
  gr_mu_2l2tau->SetLineColor(kRed);
  gr_mu_2l2tau->SetMarkerStyle(21);
  gr_mu_2l2tau->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_4l=new TGraphAsymmErrors();
  gr_mu_4l->SetPoint(0,mu_4l,y_4l);
  gr_mu_4l->SetPointError(0,mu_4l_m1s,mu_4l_p1s,0,0); 
  gr_mu_4l->SetLineWidth(3);
  gr_mu_4l->SetLineColor(kRed);
  gr_mu_4l->SetMarkerStyle(21);
  gr_mu_4l->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_2tau=new TGraphAsymmErrors();
  gr_mu_2tau->SetPoint(0,mu_2tau,y_2tau);
  gr_mu_2tau->SetPointError(0,mu_2tau_m1s,mu_2tau_p1s,0,0); 
  gr_mu_2tau->SetLineWidth(3);
  gr_mu_2tau->SetLineColor(kRed);
  gr_mu_2tau->SetMarkerStyle(21);
  gr_mu_2tau->SetMarkerSize(1.1);

  TGraphAsymmErrors* gr_mu_1l1tau=new TGraphAsymmErrors();
  gr_mu_1l1tau->SetPoint(0,mu_1l1tau,y_1l1tau);
  gr_mu_1l1tau->SetPointError(0,mu_1l1tau_m1s,mu_1l1tau_p1s,0,0); 
  gr_mu_1l1tau->SetLineWidth(3);
  gr_mu_1l1tau->SetLineColor(kRed);
  gr_mu_1l1tau->SetMarkerStyle(21);
  gr_mu_1l1tau->SetMarkerSize(1.1);

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
  gr_mu_1l2tau->Draw("Psame");
  gr_mu_2los1tau->Draw("Psame");
  gr_mu_3l1tau->Draw("Psame");
  gr_mu_2l2tau->Draw("Psame");
  gr_mu_4l->Draw("Psame");
  gr_mu_2tau->Draw("Psame");
  gr_mu_1l1tau->Draw("Psame");

  gr_mu_comb_syst->GetYaxis()->SetTickSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickLength(0.0);

  gPad->RedrawAxis();
  
  if(era==0) 
    gr_mu_comb_syst->GetXaxis()->SetLimits(-3.1,5.1);
  else
    gr_mu_comb_syst->GetXaxis()->SetLimits(-10.1,10.1);
  gr_mu_comb_syst->GetYaxis()->SetRangeUser(0,11);
  gr_mu_comb_syst->GetYaxis()->SetLabelSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickLength(0.0);
  gr_mu_comb_syst->GetXaxis()->SetTitle("Best fit #mu(t#bar{t}H)");
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
  if(era!=0) scale = 3.0;

  tex.SetTextSize(0.035);
  tex.DrawLatex(-5.3*scale,y_2lss+1.45,"Combined");

  tex.SetTextSize(0.035);
  tex.DrawLatex(-5.1*scale,y_2lss,"2lss + 0#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_3l,"3l + 0#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_2lss1tau,"2lss + 1#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_1l2tau,"1l + 2#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_2los1tau,"2los + 1#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_3l1tau,"3l + 1#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_2l2tau,"2l + 2#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_4l,"4l + 0#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_2tau,"0l + 2#tau_{h}");
  tex.DrawLatex(-5.1*scale,y_1l1tau,"1l + 1#tau_{h}");

  if(era!=0) scale = 3.6;

  tex.SetTextSize(0.027);
  tex.DrawLatex(-2.65*scale,y_2lss,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss,mu_2lss_p1s,mu_2lss_m1s));
  tex.DrawLatex(-2.65*scale,y_3l,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_3l,mu_3l_p1s,mu_3l_m1s));
  tex.DrawLatex(-2.65*scale,y_2lss1tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss1tau,mu_2lss1tau_p1s,mu_2lss1tau_m1s));
  tex.DrawLatex(-2.65*scale,y_1l2tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_1l2tau,mu_1l2tau_p1s,mu_1l2tau_m1s));
  tex.DrawLatex(-2.65*scale,y_2los1tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2los1tau,mu_2los1tau_p1s,mu_2los1tau_m1s));
  tex.DrawLatex(-2.65*scale,y_3l1tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_3l1tau,mu_3l1tau_p1s,mu_3l1tau_m1s));
  tex.DrawLatex(-2.65*scale,y_2l2tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2l2tau,mu_2l2tau_p1s,mu_2l2tau_m1s));
  tex.DrawLatex(-2.65*scale,y_4l,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_4l,mu_4l_p1s,mu_4l_m1s));
  tex.DrawLatex(-2.65*scale,y_2tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2tau,mu_2tau_p1s,mu_2tau_m1s));
  tex.DrawLatex(-2.65*scale,y_1l1tau,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_1l1tau,mu_1l1tau_p1s,mu_1l1tau_m1s));

  tex.SetTextSize(0.036);
  if(era==0)
    tex.DrawLatex(-2.65*scale,10,Form("#mu = %.2f ^{+%.2f}_{-%.2f} #bf{#left[ {}^{+%.2f}_{-%.2f} (stat) {}^{+%.2f}_{-%.2f} (syst) #right]}",mu_comb,mu_comb_p1s,mu_comb_m1s,mu_comb_p1s_stat,mu_comb_m1s_stat,mu_comb_p1s_syst,mu_comb_m1s_syst));
  else
    tex.DrawLatex(-2.65*scale,10,Form("#mu = %.2f ^{+%.2f}_{-%.2f}",mu_comb,mu_comb_p1s,mu_comb_m1s));

  TString erastring = std::to_string(era);
  c->SaveAs("test_mu_ttH_"+erastring+"_2.pdf");
  c->SaveAs("test_mu_ttH_"+erastring+"_2.root");

  return;


}
