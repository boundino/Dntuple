#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TMath.h>
#include "sampletest.h"
//#include "fitD.h"

const int pt_BIN_NUM = 6;
Double_t ptbins[pt_BIN_NUM+1] = {3.,5.,7.,9.,11.,15.,20.};
const int ct_BIN_NUM = 3;
Double_t ctbins[ct_BIN_NUM+1] = {30., 50., 70., 100.};

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
  TH1D* hmcNOCUTgenPTkpi = new TH1D("hmcNOCUTgenPTkpi","",20,0.,100.);
  TH1D* hmcNOCUTgenCTkpi = new TH1D("hmcNOCUTgenCTkpi","",7,30.,100.);
  TH1D* hmcNOCUTrecoSB = new TH1D("hmcNOCUTrecoSB","",4,0.,4.);
  TH1D* hmcNOCUTrecoSSB = new TH1D("hmcNOCUTrecoSSB","",4,0.,4.);

  Double_t nPRNE[pt_BIN_NUM][ct_BIN_NUM],nOPNE[pt_BIN_NUM][ct_BIN_NUM];
  Double_t nS=0,nB=0,nSpt=0,nBpt=0,nSffls3d=0,nBffls3d=0,nSchi2cl=0,nBchi2cl=0;
  Int_t nentries = ntmcNOCUTreco->GetEntries();
  for(Int_t i=0;i<nentries;i++)
    {
      if(i%10000==0) cout<<i<<" / "<<nentries<<endl;
      ntmcNOCUTgen->GetEntry(i);
      ntmcNOCUTreco->GetEntry(i);
      for(Int_t j=0;j<Gsize;j++)
	{
	  hmcNOCUTgenPT->Fill(Gpt[j]);
	  hmcNOCUTgenCT->Fill(hiBin/2);
	  if(GisSignal[j]!=1&&GisSignal[j]!=2) continue;
	  hmcNOCUTgenPTkpi->Fill(Gpt[j]);
	  hmcNOCUTgenCTkpi->Fill(hiBin/2);
	}
      Double_t nPRsize[pt_BIN_NUM][ct_BIN_NUM],nOPsize[pt_BIN_NUM][ct_BIN_NUM];
      for(Int_t ipt=0;ipt<pt_BIN_NUM;ipt++)
	{
	  for(Int_t ict=0;ict<ct_BIN_NUM;ict++)
	    {
	      nPRsize[ipt][ict]=0;
	      nOPsize[ipt][ict]=0;
	    }
	}
      for(Int_t j=0;j<Dsize;j++)
	{
	  for(Int_t ipt=0;ipt<pt_BIN_NUM;ipt++)
	    {
	      for(Int_t ict=0;ict<ct_BIN_NUM;ict++)
		{
		  if(Dpt[j]>ptbins[ipt]&&Dpt[j]<ptbins[ipt+1]&&(hiBin/2.)>ctbins[ict]&&(hiBin/2.)<ctbins[ict+1])
		    {
		      if(Dpt[j]>3.&&(DsvpvDistance[j]/DsvpvDisErr[j])>2.0&&Dchi2cl[j]>0.05)
			{
			  nPRsize[ipt][ict]++;
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
			      nOPsize[ipt][ict]++;
			    }
			}
		    }
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
      for(Int_t ipt=0;ipt<pt_BIN_NUM;ipt++)
	{
	  for(Int_t ict=0;ict<ct_BIN_NUM;ict++)
	    {
	      nPRNE[ipt][ict]+=nPRsize[ipt][ict];
	      nOPNE[ipt][ict]+=nOPsize[ipt][ict];
	    }
	}
    }
  TH2D* hmcNOCUTrecoPRNE = new TH2D("hmcNOCUTrecoPRNE","",pt_BIN_NUM,ptbins,ct_BIN_NUM,ctbins);
  TH2D* hmcNOCUTrecoOPNE = new TH2D("hmcNOCUTrecoOPNE","",pt_BIN_NUM,ptbins,ct_BIN_NUM,ctbins);
  for(Int_t ipt=0;ipt<pt_BIN_NUM;ipt++)
    {
      for(Int_t ict=0;ict<ct_BIN_NUM;ict++)
	{
	  cout<<"("<<ptbins[ipt]<<", "<<ptbins[ipt+1]<<"), "<<"("<<ctbins[ict]<<", "<<ctbins[ict+1]<<"): "<<nPRNE[ipt][ict]/nentries<<", "<<nOPNE[ipt][ict]/nentries<<endl;
	  hmcNOCUTrecoPRNE->SetBinContent(ipt+1,ict+1,nPRNE[ipt][ict]/nentries);
	  hmcNOCUTrecoOPNE->SetBinContent(ipt+1,ict+1,nOPNE[ipt][ict]/nentries);
	}
    }

  //cout<<"Average # of candidate per event:  PR:"<<(nPRNE/nentries)<<"  OP:"<<(nOPNE/nentries)<<endl;
  hmcNOCUTrecoSB->SetBinContent(1,nS/nB);
  hmcNOCUTrecoSB->SetBinContent(2,nSpt/nBpt);
  hmcNOCUTrecoSB->SetBinContent(3,nSffls3d/nBffls3d);
  hmcNOCUTrecoSB->SetBinContent(4,nSchi2cl/nBchi2cl);
  hmcNOCUTrecoSSB->SetBinContent(1,nS/TMath::Sqrt(nB+nS));
  hmcNOCUTrecoSSB->SetBinContent(2,nSpt/TMath::Sqrt(nBpt+nSpt));
  hmcNOCUTrecoSSB->SetBinContent(3,nSffls3d/TMath::Sqrt(nBffls3d+nSffls3d));
  hmcNOCUTrecoSSB->SetBinContent(4,nSchi2cl/TMath::Sqrt(nBchi2cl+nSchi2cl));

  TCanvas* chmcNOCUTgenPT = new TCanvas("chmcNOCUTgenPT","",500,500);
  hmcNOCUTgenPT->Scale(1./nentries);
  chmcNOCUTgenPT->SetLogy();
  hmcNOCUTgenPT->SetStats(0);
  hmcNOCUTgenPT->SetTitle(";p_{T} (GeV/c);gen D0");
  hmcNOCUTgenPT->Draw();
  chmcNOCUTgenPT->SaveAs("sampletestPlots/chmcNOCUTgenPT.pdf");

  TCanvas* chmcNOCUTgenCT = new TCanvas("chmcNOCUTgenCT","",500,500);
  hmcNOCUTgenCT->Scale(1./nentries);
  hmcNOCUTgenCT->SetStats(0);
  hmcNOCUTgenCT->SetTitle(";Centrality;gen D0");
  hmcNOCUTgenCT->Draw();
  chmcNOCUTgenCT->SaveAs("sampletestPlots/chmcNOCUTgenCT.pdf");

  TCanvas* chmcNOCUTgenPTkpi = new TCanvas("chmcNOCUTgenPTkpi","",500,500);
  hmcNOCUTgenPTkpi->Scale(1./nentries);
  chmcNOCUTgenPTkpi->SetLogy();
  hmcNOCUTgenPTkpi->SetStats(0);
  hmcNOCUTgenPTkpi->SetTitle(";p_{T} (GeV/c);gen D0(k#pi)");
  hmcNOCUTgenPTkpi->Draw();
  chmcNOCUTgenPTkpi->SaveAs("sampletestPlots/chmcNOCUTgenPTkpi.pdf");

  TCanvas* chmcNOCUTgenCTkpi = new TCanvas("chmcNOCUTgenCTkpi","",500,500);
  hmcNOCUTgenCTkpi->Scale(1./nentries);
  hmcNOCUTgenCTkpi->SetStats(0);
  hmcNOCUTgenCTkpi->SetTitle(";Centrality;gen D0(k#pi)");
  hmcNOCUTgenCTkpi->Draw();
  chmcNOCUTgenCTkpi->SaveAs("sampletestPlots/chmcNOCUTgenCTkpi.pdf");

  TCanvas* chmcNOCUTrecoPRNE = new TCanvas("chmcNOCUTrecoPRNE","",500,500);
  chmcNOCUTrecoPRNE->SetRightMargin(3.);
  //hmcNOCUTrecoPRNE->GetZaxis()->SetDecimals(2);
  hmcNOCUTrecoPRNE->SetStats(0);
  hmcNOCUTrecoPRNE->SetTitle(";p_{T} (GeV/c);Centrality");
  hmcNOCUTrecoPRNE->Draw("colz");
  chmcNOCUTrecoPRNE->SaveAs("sampletestPlots/chmcNOCUTrecoPRNE.pdf");

  TCanvas* chmcNOCUTrecoOPNE = new TCanvas("chmcNOCUTrecoOPNE","",500,500);
  chmcNOCUTrecoOPNE->SetRightMargin(7.);
  //hmcNOCUTrecoOPNE->GetZaxis()->SetDecimals(1);
  hmcNOCUTrecoOPNE->SetStats(0);
  hmcNOCUTrecoOPNE->SetTitle(";p_{T} (GeV/c);Centrality");
  hmcNOCUTrecoOPNE->Draw("colz");
  chmcNOCUTrecoOPNE->SaveAs("sampletestPlots/chmcNOCUTrecoOPNE.pdf");

  /*
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
  */

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
TH1D* hmcNOCUTrecoPRNE = new TH1D("hmcNOCUTrecoPRNE","",20,minPRNE,maxPRNE);
TH1D* hmcNOCUTrecoOPNE = new TH1D("hmcNOCUTrecoOPNE","",20,minOPNE,maxOPNE);
TH1D* hmcNOCUTgenPT = new TH1D("hmcNOCUTgenPT","",pt_BIN_NUM,ptbins);
TH1D* hmcNOCUTgenCT = new TH1D("hmcNOCUTgenCT","",ct_BIN_NUM,ctbins);
*/
