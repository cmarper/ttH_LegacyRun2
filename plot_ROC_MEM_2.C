#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TLatex.h>

#include "headers/Helpers_ROCcurve.C"



void plot_ROC(vector<TGraphErrors*> ROC, vector<TString> leg_entry, bool save=false, TString filename="", TString leg_title="", TString leg_title2=""){

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.12);
  c->SetGridx();
  c->SetGridy();

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  ROC[0]->GetYaxis()->SetTitle("Background efficiency");
  ROC[0]->GetXaxis()->SetTitleSize(0.04);
  ROC[0]->GetYaxis()->SetTitleSize(0.04);
  ROC[0]->GetXaxis()->SetRangeUser(0,1);
  ROC[0]->GetYaxis()->SetRangeUser(0,1);
  ROC[0]->GetYaxis()->SetTitleOffset(1.5);
  ROC[0]->GetXaxis()->SetTitleOffset(1.2);

  //TLegend* leg=new TLegend(0.15,0.6,0.4,0.87);
  TLegend* leg=new TLegend(0.15,0.55,0.30,0.72);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<ROC.size(); i++){
    ROC[i]->SetLineWidth(3);
    ROC[i]->SetFillColor(0);
    //ROC[i]->SetLineColor(i+2);
    //if(i>2)
    //if(i>1)
      //ROC[i]->SetLineColor(i+3);
    //if(i>6)
      //ROC[i]->SetLineColor(i+4);

    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i],"l");
  }

  ROC[0]->SetLineColor(2);
  ROC[1]->SetLineColor(4);
  ROC[2]->SetLineColor(8);

  ROC[0]->SetLineStyle(7);
  ROC[1]->SetLineStyle(7);
  ROC[2]->SetLineStyle(7);

  ROC[0]->Draw("AL");

  for(unsigned int i=1; i<ROC.size(); i++)
  ROC[i]->Draw("sameL");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.05,0.85,leg_title);
  texl->SetTextSize(0.037);
  texl->Draw("same");

  TLatex *texl2 = new TLatex(0.05,0.94,leg_title2);
  texl2->SetTextSize(0.037);
  texl2->Draw("same");

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.13,0.91,"CMS #bf{#it{Simulation Preliminary}}");

  TLatex tex2;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.78,0.91,"#bf{(13 TeV)}");

  if(save){
    c->SaveAs("../plots/ROCs/pdf/"+filename+".pdf");
    c->SaveAs("../plots/ROCs/png/"+filename+".png");
  }

  return;

}



void plot_ROC_MEM_LR_ttZZtautau_nomiss(){
	
	vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_ttHJetToNonbb.root");

	vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_TTZToLLNuNu_M-10.root");

	vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==0)");
	vector<TString> cut_denom_sig = cut_num_sig;

	vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(genZ_decayMode[0]<=5 && integration_type==0)");
	vector<TString> cut_denom_bkg=cut_num_bkg;

	vector<TGraphErrors*> ROCs;
	ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));
	ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));
	ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));
	ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

	vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  TString leg_title="#bf{#splitline{Signal: ttH H#rightarrow#tau#tau/WW/ZZ}{Background: ttZ Z#rightarrow#tau#tau}}";
  
  TString leg_title2;
  leg_title2="#bf{2lss+1#tau_{h}, no-missing-jet}";

  TString filename;
  filename="ROC_MEM_ttH_ttZtautau_nomiss_fullRun2";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title,leg_title2);

}



void plot_ROC_MEM_LR_ttZZtautau_miss(){
  
  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_ttHJetToNonbb.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_TTZToLLNuNu_M-10.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(genZ_decayMode[0]<=5 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  TString leg_title="#bf{#splitline{Signal: ttH H#rightarrow#tau#tau/WW/ZZ}{Background: ttZ Z#rightarrow#tau#tau}}";
  
  TString leg_title2;
  leg_title2="#bf{2lss+1#tau_{h}, missing-jet}";

  TString filename;
  filename="ROC_MEM_ttH_ttZtautau_miss_fullRun2";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title,leg_title2);

}


void plot_ROC_MEM_LR_ttZZll_nomiss(){
  
  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_ttHJetToNonbb.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_TTZToLLNuNu_M-10.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*((genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  TString leg_title="#bf{#splitline{Signal: ttH H#rightarrow#tau#tau/WW/ZZ}{Background: ttZ Z#rightarrowll}}";
  
  TString leg_title2;
  leg_title2="#bf{2lss+1#tau_{h}, no-missing-jet}";

  TString filename;
  filename="ROC_MEM_ttH_ttZll_nomiss_fullRun2";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title,leg_title2);

}



void plot_ROC_MEM_LR_ttZZll_miss(){
  
  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_ttHJetToNonbb.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_TTZToLLNuNu_M-10.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*((genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  TString leg_title="#bf{#splitline{Signal: ttH H#rightarrow#tau#tau/WW/ZZ}{Background: ttZ Z#rightarrowll}}";
  
  TString leg_title2;
  leg_title2="#bf{2lss+1#tau_{h}, missing-jet}";

  TString filename;
  filename="ROC_MEM_ttH_ttZll_miss_fullRun2";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title,leg_title2);

}



void plot_ROC_MEM_LR_ttbarDL_nomiss(){
  
  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_ttHJetToNonbb.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_TTJets_DiLep.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH_v1*MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  TString leg_title="#bf{#splitline{Signal: ttH H#rightarrow#tau#tau/WW/ZZ}{Background: t#bar{t} dilepton}}";

  TString leg_title2;
  leg_title2="#bf{2lss+1#tau_{h}, no-missing-jet}";

  TString filename;
  filename="ROC_MEM_ttH_ttbarDL_nomiss_fullRun2";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title,leg_title2);

}



void plot_ROC_MEM_LR_ttbarDL_miss(){
  
  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_ttHJetToNonbb.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mperez/ttH/Legacy/macros/test/ntuple_TTJets_DiLep.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH_v1*MC_weight*PU_weight_v1*trigger_weight_v1*leptonID_weight_v1*bTagSF_CSVshape_weight*tauID_weight_v1*tauES_weight_v1*(integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2(file_sig,file_bkg,"HTauTauTree_2lss1tau_SR","HTauTauTree_2lss1tau_fake",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  TString leg_title="#bf{#splitline{Signal: ttH H#rightarrow#tau#tau/WW/ZZ}{Background: t#bar{t} dilepton}}";

  TString leg_title2;
  leg_title2="#bf{2lss+1#tau_{h}, missing-jet}";

  TString filename;
  filename="ROC_MEM_ttH_ttbarDL_miss_fullRun2";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title,leg_title2);

}

void plot_all(){

  plot_ROC_MEM_LR_ttZZll_miss();
  plot_ROC_MEM_LR_ttZZll_nomiss();
  plot_ROC_MEM_LR_ttZZtautau_miss();
  plot_ROC_MEM_LR_ttZZtautau_nomiss();
  plot_ROC_MEM_LR_ttbarDL_miss();
  plot_ROC_MEM_LR_ttbarDL_nomiss();

}
