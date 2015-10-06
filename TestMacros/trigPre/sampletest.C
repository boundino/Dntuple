#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TMath.h>
#include "sampletest.h"
//#include "fitD.h"

void sampletest()
{
  TFile* infmcNOCUT = new TFile("/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20150930_DinderMC_richard-HydjetMB5020_750_75X_mcRun2_centrality30_100_20150927_EvtBase.root");
  TTree* ntmcNOCUTreco = (TTree*)infmcNOCUT->Get("ntDkpi");
  TTree* ntmcNOCUTgen = (TTree*)infmcNOCUT->Get("ntGen");
  setrecoBranch(ntmcNOCUTreco);
  setgenBranch(ntmcNOCUTgen);

  Double_t minPRNE=0,maxPRNE=300,minOPNE=0,maxOPNE=20;
  TH1D* hmcNOCUTgenPT = new TH1D("hmcNOCUTgenPT","",20,0.,100.);
  TH1D* hmcNOCUTgenCT = new TH1D("hmcNOCUTgenCT","",7,30.,100.);
  TH1D* hmcNOCUTrecoPRNE = new TH1D("hmcNOCUTrecoPRNE","",20,minPRNE,maxPRNE);
  TH1D* hmcNOCUTrecoOPNE = new TH1D("hmcNOCUTrecoOPNE","",20,minOPNE,maxOPNE);
  TH1D* hmcNOCUTrecoSB = new TH1D("hmcNOCUTrecoSB","",4,0.,4.);
  TH1D* hmcNOCUTrecoSSB = new TH1D("hmcNOCUTrecoSSB","",4,0.,4.);

  Double_t nPRNE=0,nOPNE=0;
  Double_t nS=0,nB=0,nSpt=0,nBpt=0,nSffls3d=0,nBffls3d=0,nSchi2cl=0,nBchi2cl=0;
  Int_t nentries = ntmcNOCUTreco->GetEntries();
  for(Int_t i=0;i<nentries;i++)
    {
      if(i%10000==0) cout<<i<<" / "<<nentries<<endl;
      ntmcNOCUTgen->GetEntry(i);
      ntmcNOCUTreco->GetEntry(i);
      for(Int_t j=0;j<Gsize;j++)
	{
	  if(GisSignal[j]!=1&&GisSignal[j]!=2) continue;
	  hmcNOCUTgenPT->Fill(Gpt[j]);
	  hmcNOCUTgenCT->Fill(hiBin/2);
	}
      Double_t nPRsize=0,nOPsize=0;
      for(Int_t j=0;j<Dsize;j++)
	{
	  if(Dpt[j]>3.&&(DsvpvDistance[j]/DsvpvDisErr[j])>2.0&&Dchi2cl[j]>0.05)
	    {
	      nPRsize++;
	      if(Dalpha[j]<0.12&&((Dpt[j]<3.5&&(DsvpvDistance[j]/DsvpvDisErr[j])>5.90&&Dchi2cl[j]>0.248) || 
				  (Dpt[j]>3.5&&Dpt[j]<4.5&&(DsvpvDistance[j]/DsvpvDisErr[j])>5.81&&Dchi2cl[j]>0.200) || 
				  (Dpt[j]>4.5&&Dpt[j]<5.5&&(DsvpvDistance[j]/DsvpvDisErr[j])>5.10&&Dchi2cl[j]>0.191) || 
				  (Dpt[j]>5.5&&Dpt[j]<7.0&&(DsvpvDistance[j]/DsvpvDisErr[j])>4.62&&Dchi2cl[j]>0.148) || 
				  (Dpt[j]>7.0&&Dpt[j]<9.0&&(DsvpvDistance[j]/DsvpvDisErr[j])>4.46&&Dchi2cl[j]>0.102) || 
				  (Dpt[j]>9.0&&Dpt[j]<11.&&(DsvpvDistance[j]/DsvpvDisErr[j])>4.39&&Dchi2cl[j]>0.080) || 
				  (Dpt[j]>11.&&Dpt[j]<13.&&(DsvpvDistance[j]/DsvpvDisErr[j])>4.07&&Dchi2cl[j]>0.073) || 
				  (Dpt[j]>13.&&Dpt[j]<16.&&(DsvpvDistance[j]/DsvpvDisErr[j])>3.88&&Dchi2cl[j]>0.060) || 
				  (Dpt[j]>16.&&Dpt[j]<20.&&(DsvpvDistance[j]/DsvpvDisErr[j])>3.67&&Dchi2cl[j]>0.055) || 
				  (Dpt[j]>20.&&Dpt[j]<28.&&(DsvpvDistance[j]/DsvpvDisErr[j])>3.25&&Dchi2cl[j]>0.054) || 
				  (Dpt[j]>28.&&(DsvpvDistance[j]/DsvpvDisErr[j])>2.55&&Dchi2cl[j]>0.043)))
		{
		  nOPsize++;
		}
	    }
	  if(hiBin<60||hiBin>100) continue;
	  if(Dgen[j]==23333)
	    {
	      nS++;
	      if(Dpt[j]>3.) nSpt++;
	      if((DsvpvDistance[j]/DsvpvDisErr[j])>2.) nSffls3d++;
	      if(Dchi2cl[j]>0.05) nSchi2cl++;
	    }
	  else
	    {
	      nB++;
	      if(Dpt[j]>3.) nBpt++;
	      if((DsvpvDistance[j]/DsvpvDisErr[j])>2.) nBffls3d++;
	      if(Dchi2cl[j]>0.05) nBchi2cl++;
	    }
	}
      nPRNE+=nPRsize;
      nOPNE+=nOPsize;
      hmcNOCUTrecoPRNE->Fill(nPRsize);
      hmcNOCUTrecoOPNE->Fill(nOPsize);
    }
  cout<<"Average # of candidate per event:  PR:"<<(nPRNE/nentries)<<"  OP:"<<(nOPNE/nentries)<<endl;
  hmcNOCUTrecoSB->SetBinContent(1,nS/nB);
  hmcNOCUTrecoSB->SetBinContent(2,nSpt/nBpt);
  hmcNOCUTrecoSB->SetBinContent(3,nSffls3d/nBffls3d);
  hmcNOCUTrecoSB->SetBinContent(4,nSchi2cl/nBchi2cl);
  hmcNOCUTrecoSSB->SetBinContent(1,nS/TMath::Sqrt(nB+nS));
  hmcNOCUTrecoSSB->SetBinContent(2,nSpt/TMath::Sqrt(nBpt+nSpt));
  hmcNOCUTrecoSSB->SetBinContent(3,nSffls3d/TMath::Sqrt(nBffls3d+nSffls3d));
  hmcNOCUTrecoSSB->SetBinContent(4,nSchi2cl/TMath::Sqrt(nBchi2cl+nSchi2cl));

  TCanvas* chmcNOCUTgenPT = new TCanvas("chmcNOCUTgenPT","",500,500);
  chmcNOCUTgenPT->SetLogy();
  hmcNOCUTgenPT->SetStats(0);
  hmcNOCUTgenPT->SetTitle(";p_{T} (GeV/c);gen D0(kpi)");
  hmcNOCUTgenPT->Draw();
  chmcNOCUTgenPT->SaveAs("sampletestPlots/chmcNOCUTgenPT.pdf");

  TCanvas* chmcNOCUTgenCT = new TCanvas("chmcNOCUTgenCT","",500,500);
  hmcNOCUTgenCT->SetStats(0);
  hmcNOCUTgenCT->SetTitle(";Centrality;gen D0(kpi)");
  hmcNOCUTgenCT->Draw();
  chmcNOCUTgenCT->SaveAs("sampletestPlots/chmcNOCUTgenCT.pdf");

  TCanvas* chmcNOCUTrecoPRNE = new TCanvas("chmcNOCUTrecoPRNE","",500,500);
  hmcNOCUTrecoPRNE->Scale(1./hmcNOCUTrecoPRNE->Integral(minPRNE,maxPRNE));
  hmcNOCUTrecoPRNE->SetStats(0);
  hmcNOCUTrecoPRNE->SetTitle(";# of candidates per event;Probability (after pre-filter)");
  hmcNOCUTrecoPRNE->Draw();
  chmcNOCUTrecoPRNE->SaveAs("sampletestPlots/chmcNOCUTrecoPRNE.pdf");

  TCanvas* chmcNOCUTrecoOPNE = new TCanvas("chmcNOCUTrecoOPNE","",500,500);
  hmcNOCUTrecoOPNE->Scale(1./hmcNOCUTrecoOPNE->Integral(minOPNE,maxOPNE));
  hmcNOCUTrecoOPNE->SetStats(0);
  hmcNOCUTrecoOPNE->SetTitle(";# of candidates per event;Probability (after opt cuts)");
  hmcNOCUTrecoOPNE->Draw();
  chmcNOCUTrecoOPNE->SaveAs("sampletestPlots/chmcNOCUTrecoOPNE.pdf");

  TCanvas* chmcNOCUTrecoSB = new TCanvas("chmcNOCUTrecoSB","",500,500);
  hmcNOCUTrecoSB->SetStats(0);
  hmcNOCUTrecoSB->SetTitle(";Cuts;S/B");
  hmcNOCUTrecoSB->Draw();
  chmcNOCUTrecoSB->SaveAs("sampletestPlots/chmcNOCUTrecoSB.pdf");

  TCanvas* chmcNOCUTrecoSSB = new TCanvas("chmcNOCUTrecoSSB","",500,500);
  hmcNOCUTrecoSSB->SetStats(0);
  hmcNOCUTrecoSSB->SetTitle(";Cuts;S/sqrt(S+B)");
  hmcNOCUTrecoSSB->Draw();
  chmcNOCUTrecoSSB->SaveAs("sampletestPlots/chmcNOCUTrecoSSB.pdf");

}

/*
const int pt_BIN_NUM = 11;
Double_t ptbins[pt_BIN_NUM+1] = {3., 3.5, 4.5, 5.5, 7., 9., 11., 13., 16., 20., 28., 40.};
const int ct_BIN_NUM = 3;
Double_t ctbins[ct_BIN_NUM+1] = {30., 50., 70., 100.};
TH1D* hmcNOCUTgenPT = new TH1D("hmcNOCUTgenPT","",pt_BIN_NUM,ptbins);
TH1D* hmcNOCUTgenCT = new TH1D("hmcNOCUTgenCT","",ct_BIN_NUM,ctbins);
*/
