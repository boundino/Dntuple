#include "uti.h"

TString outputfilename3pMC = "outputfiles/output_3p_MC_MB_hPtScl.root";
TString outputfilename3pDa = "outputfiles/output_3p_Data_MB_hPtScl.root";
TString outputfilename5pMC = "outputfiles/output_5p_MC_MB_hPtScl.root";
TString outputfilename5pDa = "outputfiles/output_5p_Data_MB_hPtScl.root";

void plotdoubleratio()
{ 
  TFile* outputfile3pMC = new TFile(outputfilename3pMC.Data());
  TFile* outputfile3pDa = new TFile(outputfilename3pDa.Data());
  TFile* outputfile5pMC = new TFile(outputfilename5pMC.Data());
  TFile* outputfile5pDa = new TFile(outputfilename5pDa.Data());

  TH1D* hPtScl3pMC = (TH1D*)outputfile3pMC->Get("hPtScl"); hPtScl3pMC->SetName("hPtScl3pMC");
  TH1D* hPtScl3pDa = (TH1D*)outputfile3pDa->Get("hPtScl"); hPtScl3pDa->SetName("hPtScl3pDa");
  TH1D* hPtScl5pMC = (TH1D*)outputfile5pMC->Get("hPtScl"); hPtScl5pMC->SetName("hPtScl5pMC");
  TH1D* hPtScl5pDa = (TH1D*)outputfile5pDa->Get("hPtScl"); hPtScl5pDa->SetName("hPtScl5pDa");

  TH1D* hRatioMC = (TH1D*)hPtScl5pMC->Clone("hRatioMC");
  hRatioMC->Divide(hPtScl3pMC);
  TCanvas* cRatioMC = new TCanvas("cRatioMC","",600,600);
  hRatioMC->Draw();
  TH1D* hRatioDa = (TH1D*)hPtScl5pDa->Clone("hRatioDa");
  hRatioDa->Divide(hPtScl3pDa);
  TCanvas* cRatioDa = new TCanvas("cRatioDa","",600,600);
  hRatioDa->Draw();
  
  TH1D* hDoubleRatio = (TH1D*)hRatioDa->Clone("hDoubleRatio");
  hDoubleRatio->SetTitle(";D p_{T} (GeV/c);5/3 prong Ratio_{Data}/Ratio_{MC}");
  hDoubleRatio->Divide(hRatioMC);
  TCanvas* cDoubleRatio = new TCanvas("cDoubleRatio","",600,600);
  hDoubleRatio->Draw();

  cDoubleRatio->SaveAs("plots/pp/cDoubleRatio.pdf");
}
