using namespace std;
#include "uti.h"

int test(TString ifname0 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_0.root",
         TString ifname5 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_1.root",
         TString ifname10 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_2.root",
         TString ifname15 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_3.root",
         TString ifname30 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_4.root",
         TString ifname50 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_5.root")
{
  cout<<endl;
  TFile* infPthat0 = TFile::Open(ifname0);
  TTree* ntHiPthat0 = (TTree*)infPthat0->Get("ntHi");
  TFile* infPthat5 = TFile::Open(ifname5);
  TTree* ntHiPthat5 = (TTree*)infPthat5->Get("ntHi");

  TH1F* hPthat0 = new TH1F("hPthat0","pthat>5&&maxDgenpt>5",20,5,20);
  TH1F* hPthat5 = new TH1F("hPthat5","",20,5,20);

  ntHiPthat0->Project("hPthat0","pthat","pthat>5.&&maxDgenpt>5.");
  ntHiPthat5->Project("hPthat5","pthat","pthat>5.&&maxDgenpt>5.");

  hPthat0->Scale(126843.39);
  hPthat5->Scale(3273.1442);

  hPthat0->SetXTitle("pthat");
  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogy();
  hPthat0->Draw();
  hPthat0->SetLineColor(kRed);
  hPthat5->Sumw2();
  hPthat5->Draw("same");

  return 1;
}
