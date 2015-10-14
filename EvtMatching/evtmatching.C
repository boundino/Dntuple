#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TString.h>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <iostream>
#include <cmath>
#include "evtmatching.h"

int evtmatching(TString infile="openHLT_HF_100_1_OYu.root", TString outfile="comp1.root")
{
  TFile *f = new TFile(infile);
  TTree *root = (TTree*)f->Get("Dfinder/root");
  TTree *hltroot = (TTree*)f->Get("hltbitanalysis/HltTree");
  TFile *outf = new TFile(outfile,"recreate");
  TTree* ntReco = root->CloneTree();
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
    }

  for(Int_t i=startEntries;i<nentries;i++)
    {
      hltroot->GetEntry(hltmatching[i]);
      if (i%10000==0) cout<<i<<" / "<<nentries<<"   HLT index:"<<hltmatching[i]<<endl;
      ntHlt->Fill();
    }
  outf->Write();
  outf->Close();
  return 1;
}
