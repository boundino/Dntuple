using namespace std;
#include "uti.h"

TString infname = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
void checkweightResult()
{
  TFile* inf = new TFile(infname);
  TTree* nt = (TTree*)inf->Get("ntHi");
  TH1D* hpthat = new TH1D("hpthat","After weight;pthat;Events",100,0,100);
  nt->Project("hpthat","pthat",TCut("pthatweight"));
  TCanvas* chpthat = new TCanvas("chpthat","",600,600);
  chpthat->SetLogy();
  hpthat->Draw();
  chpthat->SaveAs("chpthat.pdf");

  TH1D* hmaxDgenpt = new TH1D("hmaxDgenpt","After weight;max D gen p_{T} (GeV/c);Events",100,0,100);
  nt->Project("hmaxDgenpt","maxDgenpt",TCut("pthatweight"));
  TCanvas* chmaxDgenpt = new TCanvas("chmaxDgenpt","",600,600);
  chmaxDgenpt->SetLogy();
  hmaxDgenpt->Draw();
  chmaxDgenpt->SaveAs("chmaxDgenpt.pdf");
}
