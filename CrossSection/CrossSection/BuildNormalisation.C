#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void BuildNormalisationPP(double lumiPP=25.8)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString fileMB="ROOTfiles/CrossSectionFONLLPPMBNorm.root"; 
  TString file="ROOTfiles/CrossSectionFONLLPPNorm.root";
  
  TFile* filePPMB = new TFile(fileMB.Data());  
  TH1D* hSigmaPPStatMB = (TH1D*)filePPMB->Get("hPtSigma");

  TFile* filePP = new TFile(file.Data());  
  TH1D* hSigmaPPStat = (TH1D*)filePP->Get("hPtSigma");
  
  hSigmaPPStat->Draw();
  hSigmaPPStatMB->Draw("same");

  double ratio=hSigmaPPStatMB->GetBinContent(hSigmaPPStatMB->FindBin(17.5))/hSigmaPPStat->GetBinContent(hSigmaPPStat->FindBin(17.5));
  double lumiMB=ratio*lumiPP;
  cout<<"luminosity="<<lumiMB<<endl;

  }
  
  void BuildNormalisationPbPb(int option=0,TString cut="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)")
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  double TAA=0.;
  TString selection;
  
  if (option==0){ 
    TAA=392.4/(70.*1e9);
    selection="1";
  }
  if (option==1){
    TAA=392.4/(70.*1e9);
    selection="hiBin<20";
  }


  TString inputfilePbPbMB="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
  TFile* filePbPbMBraw = new TFile(inputfilePbPbMB.Data());  
  TTree* HltTreePbPbMB= (TTree*) filePbPbMBraw->Get("ntHlt");
  TH1D*hcountsMBPbPb=new TH1D("hcountsMBPbPb","hcountsMBPbPb",2,-200,200);
  HltTreePbPbMB->Draw("1>>hcountsMBPbPb",Form("%s&&%s",cut.Data(),selection.Data()));
  double ncountsMBPbPb=hcountsMBPbPb->GetEntries();
  
  double lumiPbPbMB=ncountsMBPbPb*TAA;
  cout<<"luminosity MB="<<lumiPbPbMB<<endl;

 // cout<<"nevents MB PbPb="<<ncountsMBPbPb<<endl;
 // cout<<"1/lumiPbPb MB="<<lumiPbPbMB/(208*208)<<endl;
  
  TString fileMB="ROOTfiles/CrossSectionFONLLPbPbMBNorm.root"; 
  TString file="ROOTfiles/CrossSectionFONLLPbPbNorm.root";
  
  TFile* filePbPbMB = new TFile(fileMB.Data());  
  TH1D* hSigmaPbPbStatMB = (TH1D*)filePbPbMB->Get("hPtSigma");

  TFile* filePbPb = new TFile(file.Data());  
  TH1D* hSigmaPbPbStat = (TH1D*)filePbPb->Get("hPtSigma");
  
  double ratio=hSigmaPbPbStat->GetBinContent(hSigmaPbPbStat->FindBin(22.5))/hSigmaPbPbStatMB->GetBinContent(hSigmaPbPbStatMB->FindBin(22.5));
  cout<<"ratio="<<ratio<<endl;
  double lumiHighPt=ratio*lumiPbPbMB;
  cout<<"luminosity high pt="<<lumiHighPt<<endl;

  }