#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include "evtmatching.h"

//int evtmatching(TString infdfinder="openHLT_HF_100_1_OYu.root", TString infhlt="openHLT_HF_100_1_OYu.root",TString outfile="comp1.root")
int evtmatching(TString infdfinder="/export/d00/scratch/jwang/Dmeson/DinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010.root", TString infhlt="/export/d00/scratch/jwang/Dmeson/openHLT_HF_Pyquen_D0pt15p0_Pthat15_50k_tketa2p0_newGT.root",TString outfile="/export/d00/scratch/jwang/Dmeson/DinderMC_20151015_EvtMatching_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010.root")
{
  TFile* fdfinder = new TFile(infdfinder);
  TFile* fhlt = new TFile(infhlt);
  TTree* root = (TTree*)fdfinder->Get("Dfinder/root");
  TTree* hltroot = (TTree*)fhlt->Get("hltbitanalysis/HltTree");
  TFile* outf = new TFile(outfile,"recreate");
  TDirectory* droot = outf->mkdir("Dfinder","");
  TDirectory* dhltroot = outf->mkdir("hltbitanalysis","");
  droot->cd();
  TTree* ntReco = root->CloneTree();
  ntReco->Write();
  dhltroot->cd();
  TTree* ntHlt = hltroot->CloneTree(0);
  setEvtDBranch(root);
  setEvtHLTBranch(hltroot);
  Long64_t nentries = root->GetEntries();
  Int_t hltmatching[nentries];

  for(Int_t ievt=0;ievt<nentries;ievt++)
    {
      hltmatching[ievt] = -1;
      root->GetEntry(ievt);
      for(Int_t jevt=0;jevt<nentries;jevt++)
	{
	  hltroot->GetEntry(jevt);
	  hltmatching[ievt] = jevt;
	  if(RecoRunNo==HltRun&&RecoEvtNo==(Int_t)HltEvent&&RecoLumiNo==HltLumiBlock) break;
	}
      if(hltmatching[ievt]==-1) cout<<"ERROR"<<endl;
    }

  for(Int_t i=0;i<nentries;i++)
    {
      hltroot->GetEntry(hltmatching[i]);
      if (i%10000==0) cout<<i<<" / "<<nentries<<"   HLT index:"<<hltmatching[i]<<endl;
      ntHlt->Fill();
    }
  ntHlt->Write();
  outf->Close();
  return 1;
}
