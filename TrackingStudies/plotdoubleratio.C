#include "uti.h"

TString outputfilenameDa = "outputfiles/outputfileData.root";
TString outputfilenameMC = "outputfiles/outputfileMC.root";

void plotdoubleratio()
{ 
  TFile* outputfileDa = new TFile(outputfilenameDa.Data());
  TFile* outputfileMC = new TFile(outputfilenameMC.Data());
  /*
  TH1D* hPt3prongDa = (TH1D*)outputfileDa->Get("hPt3prong");
  TH1D* hPt3prongMC = (TH1D*)outputfileMC->Get("hPt3prong");
  TH1D* hPt5prongDa = (TH1D*)outputfileDa->Get("hPt5prong");
  TH1D* hPt5prongMC = (TH1D*)outputfileMC->Get("hPt5prong");
  */
  TH1D* hRatioDa = (TH1D*)outputfileDa->Get("hRatio");
  TH1D* hRatioMC = (TH1D*)outputfileMC->Get("hRatio");
  
  TH1D* hDoubleRatio = (TH1D*)hRatioDa->Clone("hDoubleRatio");
  hDoubleRatio->SetTitle(";D p_{T} (GeV/c);Uncorrected 5/3 prong Ratio_{Data}/Ratio_{MC}");
  hDoubleRatio->Divide(hRatioMC);

  TCanvas* cDoubleRatio = new TCanvas("cDoubleRatio","",600,600);
  hDoubleRatio->Draw();

  cDoubleRatio->SaveAs("plots/pp/cDoubleRatio.pdf");
}
