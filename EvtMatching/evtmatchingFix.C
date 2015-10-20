#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <fstream>
#include "evtmatching.h"

Float_t pthat = 15;
//int evtmatching(TString infdfinder="openHLT_HF_100_1_OYu.root", TString infhlt="openHLT_HF_100_1_OYu.root",TString outfile="comp1.root")
int evtmatchingFix(TString infdfinder=Form("/export/d00/scratch/jwang/Dmeson/DfinderMC_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root",pthat,pthat), TString infhlt=Form("/export/d00/scratch/jwang/Dmeson/openHLT_HF_HLTHeavyFlavour_MVA_V13_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_1016_MBseed_fix.root",pthat,pthat),TString outfile=Form("/export/d00/scratch/jwang/Dmeson/DfinderMC_20151020_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root",pthat,pthat))
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

  ifstream fin(Form("evtmatchingResult/evtmatching_pthat%.0f.dat",pthat));
  cout<<"---- Event matching"<<endl;
  for(Int_t ievt=0;ievt<nentries;ievt++)
    {
      fin>>hltmatching[ievt];
    }  
  cout<<"---- Event matching done"<<endl;
  cout<<"---- Writing hlt tree"<<endl;
  for(Int_t i=0;i<nentries;i++)
    {
      if(hltmatching[i]<0) continue;
      root->GetEntry(i);
      hltroot->GetEntry(hltmatching[i]);
      if (i%10000==0) cout<<i<<" / "<<nentries<<"   HLT index:"<<hltmatching[i]<<endl;
      ntReco->Fill();
      ntHlt->Fill();
    }
  outf->Write();
  /*
  droot->cd();
  ntReco->Write();
  dhltroot->cd();
  ntHlt->Write();
  */
  cout<<"---- Writing hlt tree done"<<endl;
  outf->Close();

  return 1;
}
