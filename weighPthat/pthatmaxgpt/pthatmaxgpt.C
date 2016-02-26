#include "uti.h"
#define MAX_GEN      6000

void pthatmaxgpt(Bool_t ifweigh=true)
{
  const int nBins=50; Float_t minBin=0,maxBin=100;  TFile* inf = new TFile("/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root");
  TTree* ntHi = (TTree*)inf->Get("ntHi");

  Int_t nentries = ntHi->GetEntries();
  TH2D* h = new TH2D("h",";Pthat;Max Gen p_{T} (GeV/c)",nBins,minBin,maxBin,nBins,minBin,maxBin);
  h->SetMarkerSize(0.5);
  Float_t pthatweight;
  if(ifweigh) ntHi->SetBranchAddress("pthatweight",&pthatweight);
  Float_t pthat;       ntHi->SetBranchAddress("pthat",&pthat);
  Float_t maxDgenpt;   ntHi->SetBranchAddress("maxDgenpt",&maxDgenpt);
  cout<<nentries<<endl;
  for(Int_t i=0;i<nentries;i++)
    {
      ntHi->GetEntry(i);
      if(ifweigh) h->Fill(pthat,maxDgenpt,pthatweight);
      else h->Fill(pthat,maxDgenpt);
    }

  cout<<endl;
  gStyle->SetPadLeftMargin(0.17);
  gStyle->SetPadRightMargin(0.15);
  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogz();
  h->Draw("colz");
  c->SaveAs("pthatmaxgpt.pdf");
}
