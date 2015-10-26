#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <fstream>
#include "evtmatching.h"

//int evtmatching(TString infdfinder="openHLT_HF_100_1_OYu.root", TString infhlt="openHLT_HF_100_1_OYu.root",TString outfile="comp1.root")
int evtmatching(TString infdfinder="/export/d00/scratch/jwang/Dmeson/DfinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root", TString infhlt="/export/d00/scratch/jwang/Dmeson/openHLT_HF_HLTHeavyFlavour_MVA_V13_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_1016_MBseed_fix.root",TString outfile="/export/d00/scratch/jwang/Dmeson/DfinderMC_20151017_EvtMatching_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root")
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
  Long64_t nentries = root->GetEntries();
  Int_t hltmatching[nentries];

  ofstream fout("evtmatchingResult/evtmatching.dat");
  cout<<"---- Event matching"<<endl;
  for(Int_t ievt=0;ievt<nentries;ievt++)
    {
      if(ievt%1000==0) cout<<ievt<<" / "<<nentries<<endl;
      hltmatching[ievt] = -1;
      root->GetEntry(ievt);
      for(Int_t jevt=0;jevt<nentries;jevt++)
	{
	  hltroot->GetEntry(jevt);
	  if(RecoRunNo==HltRun&&RecoEvtNo==(Int_t)HltEvent&&RecoLumiNo==HltLumiBlock)
	    {
	      hltmatching[ievt] = jevt;
	      break;
	    }
	}
      fout<<hltmatching[ievt]<<endl;
    }
  
  cout<<"---- Event matching done"<<endl;
  cout<<"---- Writing hlt tree"<<endl;
  for(Int_t i=0;i<nentries;i++)
    {
      if (i%1000==0) cout<<i<<" / "<<nentries<<"   HLT index:"<<hltmatching[i]<<endl;
      if(hltmatching[i]<0) continue;
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
