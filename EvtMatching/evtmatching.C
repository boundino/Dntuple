#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <fstream>
#include "evtmatching.h"

//int evtmatching(TString infdfinder="openHLT_HF_100_1_OYu.root", TString infhlt="openHLT_HF_100_1_OYu.root",TString outfile="comp1.root")
int evtmatchingFaster(TString infdfinder="/export/d00/scratch/jwang/Dmeson/DfinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root", TString infhlt="/export/d00/scratch/jwang/Dmeson/openHLT_HF_HLTHeavyFlavour_MVA_V13_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_1016_MBseed_fix.root",TString outfile="/export/d00/scratch/jwang/Dmeson/DfinderMC_20151023_EvtMatching_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root")
{
  TFile* fdfinder = new TFile(infdfinder);
  TFile* fhlt = new TFile(infhlt);
  TTree* root = (TTree*)fdfinder->Get("Dfinder/root");
  TTree* hltroot = (TTree*)fhlt->Get("hltbitanalysis/HltTree");

  TFile* outf = new TFile(outfile,"recreate");
  TDirectory* droot = outf->mkdir("Dfinder","");
  TDirectory* dhltroot = outf->mkdir("hltbitanalysis","");
  droot->cd();
  TTree* ntReco = root->CloneTree(0);
  dhltroot->cd();
  TTree* ntHlt = hltroot->CloneTree(0);

  setEvtDBranch(root);
  setEvtHLTBranch(hltroot);
  cout<<"---- Check evt no. for two trees"<<endl;
  cout<<"     "<<root->GetEntries()<<", "<<hltroot->GetEntries()<<endl;
  Long64_t nentriesReco = root->GetEntries();
  Long64_t nentriesHlt = hltroot->GetEntries();
  Int_t aRecoRunNo[nentriesReco],aHltRun[nentriesHlt],aRecoEvtNo[nentriesReco],aHltEvent[nentriesHlt],aRecoLumiNo[nentriesReco],aHltLumiBlock[nentriesHlt];
  cout<<"---- Event reading"<<endl;
  for(Int_t i=0;i<((nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt);i++)
    {
      if(i%10000==0) 
	{
	  cout<<i<<" / ";
	  if(i<nentriesReco) cout<<"Reco:"<<nentriesReco<<"  "<<endl;
	  if(i<nentriesHlt) cout<<"Hlt:"<<nentriesHlt<<endl;
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
    }
  Int_t hltmatching[nentriesReco];
  ofstream fout("evtmatchingResult/evtmatching.dat");
  cout<<"---- Event matching"<<endl;
  for(Int_t ievt=0;ievt<nentriesReco;ievt++)
    {
      if(ievt%1000==0) cout<<ievt<<" / "<<nentriesReco<<endl;
      hltmatching[ievt] = -1;
      for(Int_t jevt=0;jevt<nentriesHlt;jevt++)
	{
	  if(aRecoRunNo[ievt]==aHltRun[jevt]&&aRecoEvtNo[ievt]==aHltEvent[jevt]&&aRecoLumiNo[ievt]==aHltLumiBlock[jevt])
	    {
	      hltmatching[ievt] = jevt;
	      break;
	    }
	}
      fout<<hltmatching[ievt]<<endl;
    }
  cout<<"---- Event matching done"<<endl;
  cout<<"---- Writing hlt tree"<<endl;
  for(Int_t i=0;i<nentriesReco;i++)
    {
      if (i%10000==0) cout<<i<<" / "<<nentriesReco<<"   HLT index:"<<hltmatching[i]<<endl;
      if(hltmatching[i]<0)
	{
	  cout<<"test "<<i<<endl;
	  continue;
	}
      root->GetEntry(i);
      hltroot->GetEntry(hltmatching[i]);
      ntReco->Fill();
      ntHlt->Fill();
    }
  outf->Write();
  cout<<"---- Writing hlt tree done"<<endl;
  outf->Close();

  return 1;
}
