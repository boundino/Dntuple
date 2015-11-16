#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <TLatex.h>
#include <TMath.h>
#define MAX_XB 16384

TString prefilter = "Dgen==23333&&Dtrk1Pt>8.&&Dtrk2Pt>8.&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95";
Double_t BIN_MIN = 0;
Double_t BIN_MAX = 7;
Int_t BIN_NUM = 7;
void candidatePerEvent(TString infname="/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151012_HLTemulation_DinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010_EvtBase.root")
{
  TFile* infile = new TFile(infname);
  TTree* dnt = (TTree*)infile->Get("ntDkpi");
  Int_t      Dsize;
  Double_t   Dpt[MAX_XB];
  Double_t   Dalpha[MAX_XB];
  Double_t   DsvpvDistance[MAX_XB];
  Double_t   DsvpvDisErr[MAX_XB];
  Double_t   Dtrk1Pt[MAX_XB];
  Double_t   Dtrk2Pt[MAX_XB];
  Double_t   Dgen[MAX_XB];
  dnt->SetBranchAddress("Dsize",&Dsize);
  dnt->SetBranchAddress("Dpt",Dpt);
  dnt->SetBranchAddress("Dalpha",Dalpha);
  dnt->SetBranchAddress("DsvpvDistance",DsvpvDistance);
  dnt->SetBranchAddress("DsvpvDisErr",DsvpvDisErr);
  dnt->SetBranchAddress("Dtrk1Pt",Dtrk1Pt);
  dnt->SetBranchAddress("Dtrk2Pt",Dtrk2Pt);
  dnt->SetBranchAddress("Dgen",Dgen);

  TH1D* h = new TH1D("h",";candidate per event;after pre-filter;",BIN_NUM,BIN_MIN,BIN_MAX);
  TH1D* hMatched = new TH1D("hMatched",";candidate per event;after pre-filter+matched reco;",BIN_NUM,BIN_MIN,BIN_MAX);
  Int_t nentries = dnt->GetEntries();
  for(Int_t i=0;i<nentries;i++)
    {
      Int_t ncandpevt=0,ncandpevtMatched=0;
      dnt->GetEntry(i);
      for(Int_t j=0;j<Dsize;j++)
	{
	  if(Dtrk1Pt[j]>8.&&Dtrk2Pt[j]>8.&&(DsvpvDistance[j]/DsvpvDisErr[j])>2.5&&TMath::Cos(Dalpha[j])>0.95)
	    {
	      ncandpevt++;
	      if(Dgen[j]==23333)
		{
		  ncandpevtMatched++;
		}
	    }
	}
      h->Fill(ncandpevt);
      hMatched->Fill(ncandpevtMatched);
    }
  TCanvas* c = new TCanvas("c","",500,500);
  h->SetStats();
  h->Draw();
  TCanvas* cMatched = new TCanvas("cMatched","",500,500);
  hMatched->SetStats();
  hMatched->Draw();  
}
