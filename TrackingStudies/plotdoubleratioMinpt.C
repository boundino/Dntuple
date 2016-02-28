#include "uti.h"

const int BIN_NUM=10;

TString outputfilename3pMC = "outputfiles/output_3p_MC_Minpt.root";
TString outputfilename3pDa = "outputfiles/output_3p_Data_Minpt.root";
TString outputfilename5pMC = "outputfiles/output_5p_MC_Minpt.root";
TString outputfilename5pDa = "outputfiles/output_5p_Data_Minpt.root";

int plotdoubleratioMinpt()
{ 
  TFile* outputfile3pMC = new TFile(outputfilename3pMC.Data());
  TFile* outputfile3pDa = new TFile(outputfilename3pDa.Data());
  TFile* outputfile5pMC = new TFile(outputfilename5pMC.Data());
  TFile* outputfile5pDa = new TFile(outputfilename5pDa.Data());

  TH1F* hPt3pMC = (TH1F*)outputfile3pMC->Get("hPt"); hPt3pMC->SetName("hPt3pMC");
  TH1F* hPt3pDa = (TH1F*)outputfile3pDa->Get("hPt"); hPt3pDa->SetName("hPt3pDa");
  TH1F* hPt5pMC = (TH1F*)outputfile5pMC->Get("hPt"); hPt5pMC->SetName("hPt5pMC");
  TH1F* hPt5pDa = (TH1F*)outputfile5pDa->Get("hPt"); hPt5pDa->SetName("hPt5pDa");

  TH1F* hGen3pMC = (TH1F*)outputfile3pMC->Get("hGen"); hGen3pMC->SetName("hGen3pMC");
  TH1F* hGen5pMC = (TH1F*)outputfile5pMC->Get("hGen"); hGen5pMC->SetName("hGen5pMC");

  TCanvas* cPt3pDa = new TCanvas("cPt3pDa","",600,600);
  hPt3pDa->Draw("pe");
  TCanvas* cPt5pDa = new TCanvas("cPt5pDa","",600,600);
  hPt5pDa->Draw("pe");

  TEfficiency* pEff3p = new TEfficiency(*hPt3pMC,*hGen3pMC); pEff3p->SetName("pEff3p");
  TEfficiency* pEff5p = new TEfficiency(*hPt5pMC,*hGen5pMC); pEff5p->SetName("pEff5p");

  TCanvas* cEff3p = new TCanvas("cEff3p","",600,600);
  pEff3p->Draw("AP");
  TCanvas* cEff5p = new TCanvas("cEff5p","",600,600);
  pEff5p->Draw("AP");

  TH1F* hEff3p = (TH1F*)hPt3pDa->Clone("hEff3p");
  TH1F* hEff5p = (TH1F*)hPt3pDa->Clone("hEff5p");
  if(hEff3p->GetNbinsX()!=BIN_NUM)
    {
      cout<<"Wrong Bin number"<<endl;
      return 0;
    }

  for(int i=0;i<BIN_NUM;i++)
    {
      hEff3p->SetBinContent(i+1,pEff3p->GetEfficiency(i+1));
      hEff3p->SetBinError(i+1,pEff3p->GetEfficiencyErrorUp(i+1));
      hEff5p->SetBinContent(i+1,pEff5p->GetEfficiency(i+1));
      hEff5p->SetBinError(i+1,pEff5p->GetEfficiencyErrorUp(i+1));
    }

  TH1F* hPtCor3pDa = (TH1F*)hPt3pDa->Clone("hPtCor3pDa");
  hPtCor3pDa->Divide(hEff3p);
  TH1F* hPtCor5pDa = (TH1F*)hPt5pDa->Clone("hPtCor5pDa");
  hPtCor5pDa->Divide(hEff5p);

  TH1F* hRatio = (TH1F*)hPtCor5pDa->Clone("hRatio");
  hRatio->Divide(hPtCor3pDa);
  Float_t aRatio[BIN_NUM],aRatioErr[BIN_NUM],aPtbin[BIN_NUM],aZero[BIN_NUM];
  for(int i=0;i<BIN_NUM;i++)
    {
      aRatio[i] = hRatio->GetBinContent(i+1);
      aRatioErr[i] = hRatio->GetBinError(i+1);
      aPtbin[i] = hRatio->GetBinCenter(i+1)-hRatio->GetBinWidth(i+1)/2.;
      aZero[i] = 0;
    }

  TGraphErrors* gRatio = new TGraphErrors(BIN_NUM,aPtbin,aRatio,aZero,aRatioErr);
  TH2F* hempty = new TH2F("hempty","",20,4.5,14.5,10.,1.,3.);  
  hempty->GetXaxis()->SetTitle("min p_{T}(D*) (GeV/c)");
  hempty->GetYaxis()->SetTitle("R");
  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(.9);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);
  TCanvas* cRatio = new TCanvas("cRatio","",600,600);
  hempty->Draw();
  gRatio->Draw("psame");

  Float_t aTrkEff[BIN_NUM],aTrkEffErr[BIN_NUM];
  for(int i=0;i<BIN_NUM;i++)
    {
      aTrkEff[i] = sqrt(aRatio[i]/2.08);
      aTrkEffErr[i] = aRatioErr[i]/(2.*2.08*aRatio[i]);
    }

  TGraphErrors* gTrkEff = new TGraphErrors(BIN_NUM,aPtbin,aTrkEff,aZero,aTrkEffErr);
  TH2F* hemptyTrkEff = new TH2F("hemptyTrkEff","",20,4.5,14.5,10.,0.7,1.3);  
  hemptyTrkEff->GetXaxis()->SetTitle("min p_{T}(D*) (GeV/c)");
  hemptyTrkEff->GetYaxis()->SetTitle("#epsilon(data)/#epsilon(MC)");
  hemptyTrkEff->GetXaxis()->SetTitleOffset(1.);
  hemptyTrkEff->GetYaxis()->SetTitleOffset(.9);
  hemptyTrkEff->GetXaxis()->SetTitleSize(0.045);
  hemptyTrkEff->GetYaxis()->SetTitleSize(0.045);
  hemptyTrkEff->GetXaxis()->SetTitleFont(42);
  hemptyTrkEff->GetYaxis()->SetTitleFont(42);
  hemptyTrkEff->GetXaxis()->SetLabelFont(42);
  hemptyTrkEff->GetYaxis()->SetLabelFont(42);
  hemptyTrkEff->GetXaxis()->SetLabelSize(0.04);
  hemptyTrkEff->GetYaxis()->SetLabelSize(0.04);
  TCanvas* cTrkEff = new TCanvas("cTrkEff","",600,600);
  hemptyTrkEff->Draw();
  gTrkEff->Draw("psame");

  return 1;
}
