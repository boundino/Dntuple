#include "uti.h"
#include "TLegendEntry.h"
#include "parameters.h"

TString sample1, sample2, sample3;
TString sample4="ss";

void compareMCPthat(bool isPbPb=1,int effselector=3){

  if(!isPbPb){
    sample1="ROOTfiles/pthatallPP.root";
    sample2="ROOTfiles/pthatallPPpthatreweighted.root";
    sample3="ROOTfiles/pthatallPPptreweighted.root";
    
  }
  else{
    sample1="ROOTfiles/pthatallPbPb.root";
    sample2="ROOTfiles/pthatallPbPbpthatreweighted.root";
    sample3="ROOTfiles/pthatallPbPbptreweighted.root";
    sample4="ROOTfiles/pthatallPbPbptreweightedPPMC.root";
  }

  TString effhisto, titlename;
  if(effselector==0) {effhisto="hEffAcc"; titlename="Acceptance";}
  if(effselector==1) {effhisto="hEffReco"; titlename="Reco efficiency";}
  if(effselector==2) {effhisto="hEffSelection"; titlename="Selection efficiency";}
  if(effselector==3) {effhisto="hEff"; titlename="Total effiiciency";}

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  TFile *f1=new TFile(sample1.Data());
  TFile *f2=new TFile(sample2.Data());
  TFile *f3=new TFile(sample3.Data());

  TH1D *h1=(TH1D*)f1->Get(effhisto.Data());
  TH1D *h2=(TH1D*)f2->Get(effhisto.Data());
  TH1D *h3=(TH1D*)f3->Get(effhisto.Data());  
  
  TH2F* hemptyPthat=new TH2F("hemptyPthat","",50,0,100.,10,0.01,10.);  
  hemptyPthat->GetXaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->SetTitle("Efficiencies");
  hemptyPthat->GetXaxis()->SetTitle("p_{T}");
  hemptyPthat->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthat->GetYaxis()->SetTitleOffset(1.0);
  hemptyPthat->GetXaxis()->SetTitleSize(0.05);
  hemptyPthat->GetYaxis()->SetTitleSize(0.05);
  hemptyPthat->GetXaxis()->SetTitleFont(42);
  hemptyPthat->GetYaxis()->SetTitleFont(42);
  hemptyPthat->GetXaxis()->SetLabelFont(42);
  hemptyPthat->GetYaxis()->SetLabelFont(42);
  hemptyPthat->GetXaxis()->SetLabelSize(0.035);
  hemptyPthat->GetYaxis()->SetLabelSize(0.035);  

  TH2F* hemptyPthatRatio=new TH2F("hemptyPthatRatio","",50,0,100.,10,0.0,3.);  
  hemptyPthatRatio->GetXaxis()->CenterTitle();
  hemptyPthatRatio->GetYaxis()->CenterTitle();
  hemptyPthatRatio->GetYaxis()->SetTitle("Ratio efficiency weighted / unweighted");
  hemptyPthatRatio->GetXaxis()->SetTitle("p_{T}");
  hemptyPthatRatio->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthatRatio->GetYaxis()->SetTitleOffset(1.0);
  hemptyPthatRatio->GetXaxis()->SetTitleSize(0.05);
  hemptyPthatRatio->GetYaxis()->SetTitleSize(0.05);
  hemptyPthatRatio->GetXaxis()->SetTitleFont(42);
  hemptyPthatRatio->GetYaxis()->SetTitleFont(42);
  hemptyPthatRatio->GetXaxis()->SetLabelFont(42);
  hemptyPthatRatio->GetYaxis()->SetLabelFont(42);
  hemptyPthatRatio->GetXaxis()->SetLabelSize(0.035);
  hemptyPthatRatio->GetYaxis()->SetLabelSize(0.035);  


  TH1D *hRatio2=(TH1D*)h2->Clone("hRatio2");
  TH1D *hRatio3=(TH1D*)h3->Clone("hRatio3"); 
  hRatio2->Divide(h1);
  hRatio3->Divide(h1);
  
  TCanvas*c=new TCanvas("c","c",800,500);
  c->cd();
  gPad->SetLogx();
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(4);
  h1->SetMarkerColor(1);
  h2->SetMarkerColor(2);
  h3->SetMarkerColor(4);
  gPad->SetLogx();
  hemptyPthatRatio->Draw();
  hRatio2->SetLineColor(2);
  hRatio3->SetLineColor(4);
  hRatio2->SetMarkerColor(2);
  hRatio3->SetMarkerColor(4);
  hemptyPthatRatio->Draw();
  hRatio2->Draw("same");
  hRatio3->Draw("same");
  
  TLegend *legend=new TLegend(0.2100806,0.7068644,0.5084677,0.8605932,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.045);
  TLegendEntry *ent_pthat1=legend->AddEntry(hRatio2,"pthat weighted / unweighted","pf");
  ent_pthat1->SetTextFont(42);
  ent_pthat1->SetLineColor(1);
  ent_pthat1->SetMarkerColor(1);
  TLegendEntry *ent_pthat2=legend->AddEntry(hRatio3,"pt weighted / unweighted","pf");
  ent_pthat2->SetTextFont(42);
  ent_pthat2->SetLineColor(2);
  ent_pthat2->SetMarkerColor(2);
  legend->Draw();
  
   if(0){

  
  TFile *f4=new TFile(sample4.Data());
  TH1D *h4=(TH1D*)f4->Get(effhisto.Data());  
  TH1D *hRatio4=(TH1D*)h4->Clone("hRatio3"); 
  hRatio4->Divide(h1);
  hRatio4->SetLineColor(1);
  hRatio4->SetMarkerColor(1);
  hRatio4->Draw("same");
  TLegendEntry *ent_pthat3=legend->AddEntry(hRatio4,"pp efficiency unweighted / PbPb efficiency unweighted","pf");
  ent_pthat3->SetTextFont(42);
  ent_pthat3->SetLineColor(4);
  ent_pthat3->SetMarkerColor(4);
  legend->Draw();


  }
  
  if(effselector==0) c->SaveAs(Form("canvasAccEfficiencyPtHatWeight_isPbPb%d.pdf",isPbPb));
  if(effselector==1) c->SaveAs(Form("canvasRecoEfficiencyPtHatWeight_isPbPb%d.pdf",isPbPb));
  if(effselector==2) c->SaveAs(Form("canvasSelEfficiencyPtHatWeight_isPbPb%d.pdf",isPbPb));
  if(effselector==3) c->SaveAs(Form("canvasTotAccEfficiencyPtHatWeight_isPbPb%d.pdf",isPbPb));

}