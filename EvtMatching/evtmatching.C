#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "evtmatching.h"

//int evtmatching(TString infdfinder="/export/d00/scratch/jwang/Dmeson/evtmatchingInput/DfinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151027.root", TString infhlt="/export/d00/scratch/jwang/Dmeson/evtmatchingInput/openHLT_HF_HLTHeavyFlavour_MVA_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_1026.root",TString outfile="/export/d00/scratch/jwang/Dmeson/DfinderMC_20151028_EvtMatching_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151027.root")
int evtmatching(TString infdfinder="/export/d00/scratch/jwang/Dmeson/evtmatchingInput/DfinderMC_Pyquen_D0tokaonpion_D0pt35p0_Pthat35_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151027.root", TString infhlt="/export/d00/scratch/jwang/Dmeson/evtmatchingInput/openHLT_HF_HLTHeavyFlavour_MVA_Pyquen_D0tokaonpion_D0pt35p0_Pthat35_1026.root",TString outfile="/export/d00/scratch/jwang/Dmeson/DfinderMC_20151028_EvtMatching_Pyquen_D0tokaonpion_D0pt35p0_Pthat35_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151027.root")
{
  TFile* fdfinder = new TFile(infdfinder);
  TFile* fhlt = new TFile(infhlt);
  TTree* root = (TTree*)fdfinder->Get("Dfinder/root");
  TTree* hiroot = (TTree*)fdfinder->Get("hiEvtAnalyzer/HiTree");
  TTree* hltroot = (TTree*)fhlt->Get("hltbitanalysis/HltTree");

  TFile* outf = new TFile(outfile,"recreate");
  TDirectory* droot = outf->mkdir("Dfinder","");
  TDirectory* dhltroot = outf->mkdir("hltbitanalysis","");
  TDirectory* dhiroot = outf->mkdir("hiEvtAnalyzer","");
  droot->cd();
  TTree* ntReco = root->CloneTree(0);
  dhltroot->cd();
  TTree* ntHlt = hltroot->CloneTree(0);
  dhiroot->cd();
  TTree* ntHi = hiroot->CloneTree(0);

  setEvtDBranch(root);
  setEvtHLTBranch(hltroot);
  setEvtHIBranch(hiroot);
  cout<<"---- Check evt no. for three trees"<<endl;
  cout<<root->GetEntries()<<", "<<hltroot->GetEntries()<<", "<<hiroot->GetEntries()<<endl;
  Long64_t nentriesReco = root->GetEntries();
  Long64_t nentriesHlt = hltroot->GetEntries();
  Long64_t nentriesHi = hiroot->GetEntries();
  Int_t aRecoRunNo[nentriesReco],aHltRun[nentriesHlt],aHiRun[nentriesHi],aRecoEvtNo[nentriesReco],aHltEvent[nentriesHlt],aHiEvt[nentriesHi],aRecoLumiNo[nentriesReco],aHltLumiBlock[nentriesHlt],aHiLumi[nentriesHi];
  cout<<"---- Event reading"<<endl;
  Long64_t nentriesMax;
  if(nentriesHi>((nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt)) nentriesMax=nentriesHi;
  else nentriesMax=((nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt);
  for(Int_t i=0;i<((nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt);i++)
    {
      if(i%1000==0) 
	{
	  cout<<setw(7)<<i<<" / "<<nentriesMax<<endl;
	}
      if(i<nentriesReco)
	{
	  root->GetEntry(i);
	  aRecoRunNo[i] = RecoRunNo;
	  aRecoEvtNo[i] = RecoEvtNo;
	  aRecoLumiNo[i] = RecoLumiNo;
	}
      if(i<nentriesHlt)
	{
	  hltroot->GetEntry(i);
	  aHltRun[i] = HltRun;
	  aHltEvent[i] = (Int_t)HltEvent;
	  aHltLumiBlock[i] = HltLumiBlock;
	}
      if(i<nentriesHi)
	{
	  hiroot->GetEntry(i);
	  aHiRun[i] = HiRun;
	  aHiEvt[i] = HiEvt;
	  aHiLumi[i] = HiLumi;
	}
    }

  Int_t hltmatching[nentriesReco],himatching[nentriesReco];
  ofstream fout("evtmatchingResult/evtmatching.dat");
  cout<<"---- Event matching"<<endl;
  for(Int_t ievt=0;ievt<nentriesReco;ievt++)
    {
      if(ievt%10000==0) cout<<setw(7)<<ievt<<" / "<<nentriesReco<<endl;
      hltmatching[ievt] = -1;
      himatching[ievt] = -1;
      for(Int_t jevt=0;jevt<nentriesHlt;jevt++)
	{
	  if(aRecoRunNo[ievt]==aHltRun[jevt]&&aRecoEvtNo[ievt]==aHltEvent[jevt]&&aRecoLumiNo[ievt]==aHltLumiBlock[jevt])
	    {
	      hltmatching[ievt] = jevt;
	      break;
	    }
	}
      for(Int_t jevt=0;jevt<nentriesHi;jevt++)
	{
	  if(aRecoRunNo[ievt]==aHiRun[jevt]&&aRecoEvtNo[ievt]==aHiEvt[jevt]&&aRecoLumiNo[ievt]==aHiLumi[jevt])
	    {
	      himatching[ievt] = jevt;
	      break;
	    }
	}
      fout<<hltmatching[ievt]<<" "<<himatching[ievt]<<endl;
    }
  cout<<"---- Event matching done"<<endl;
  cout<<"---- Writing hlt tree"<<endl;
  for(Int_t i=0;i<nentriesReco;i++)
    {
      if (i%1000==0) cout<<setw(7)<<i<<" / "<<nentriesReco<<"  HI index:"<<setiosflags(ios::left)<<setw(7)<<himatching[i]<<" HLT index:"<<hltmatching[i]<<endl;
      if(hltmatching[i]<0)
	{
	  continue;
	}
      root->GetEntry(i);
      droot->cd();
      ntReco->Fill();
      hiroot->GetEntry(himatching[i]);
      dhiroot->cd();
      ntHi->Fill();
      hltroot->GetEntry(hltmatching[i]);
      dhltroot->cd();
      ntHlt->Fill();
    }
  outf->Write();
  cout<<"---- Writing hlt tree done"<<endl;
  outf->Close();

  return 1;
}
