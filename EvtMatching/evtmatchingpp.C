#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "evtmatching.h"

Float_t pthat = 5;
int evtmatchingpp(TString infdfinder=Form("/export/d00/scratch/jwang/Dmeson/evtmatchingInput/DfinderMC_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151027.root",pthat,pthat), TString infhlt=Form("/export/d00/scratch/jwang/Dmeson/evtmatchingInput/openHLT_HF_HLTHeavyFlavour_MVA_Pythia_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_1026.root",pthat,pthat),TString outfile=Form("/export/d00/scratch/jwang/Dmeson/DfinderMC_20151029_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151027.root",pthat,pthat))
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
  cout<<"---- Check evt no. for three trees"<<endl;
  cout<<root->GetEntries()<<", "<<hltroot->GetEntries()<<endl;
  Long64_t nentriesReco = root->GetEntries();
  Long64_t nentriesHlt = hltroot->GetEntries();
  Int_t aRecoRunNo[nentriesReco],aRecoEvtNo[nentriesReco],aRecoLumiNo[nentriesReco];
  Int_t aHltRun[nentriesHlt],aHltEvent[nentriesHlt],aHltLumiBlock[nentriesHlt];

  cout<<"---- Event reading"<<endl;
  for(Int_t i=0;i<((nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt);i++)
    {
      if(i%10000==0)
	{
	  cout<<setw(7)<<i<<" / "<<((nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt)<<endl;
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
      if(ievt%10000==0) cout<<setw(7)<<ievt<<" / "<<nentriesReco<<endl;
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
      if (i%1000==0) cout<<setw(7)<<i<<" / "<<nentriesReco<<" HLT index:"<<setiosflags(ios::left)<<hltmatching[i]<<endl;
      if(hltmatching[i]<0)
	{
	  continue;
	}
      root->GetEntry(i);
      droot->cd();
      ntReco->Fill();
      hltroot->GetEntry(hltmatching[i]);
      dhltroot->cd();
      ntHlt->Fill();
    }
  outf->Write();
  cout<<"---- Writing hlt tree done"<<endl;
  outf->Close();

  return 1;
}
