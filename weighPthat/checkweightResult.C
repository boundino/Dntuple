using namespace std;
#include "weighPthat.h"

void checkweightResult(TString infname = "/afs/cern.ch/work/w/wangj/public/RunII/weighPthat/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_withweight.root")
{
  TFile* inf = new TFile(infname);
  TTree* nt = (TTree*)inf->Get("ntHi");
  TH1D* hpthat = new TH1D("hpthat","After weight;pthat;Events",100,0,100);
  nt->Project("hpthat","pthat",TCut("pthatweight"));
  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogy();
  hpthat->Draw();
  for(Int_t i=0;i<nBins-1;i++)
    {
      cout<<hpthat->Integral(pthatBin[i],pthatBin[i+1])<<"  "<<crosssec[i]-crosssec[i+1]<<endl;
    }
  c->SaveAs("hpthat.pdf");
}
