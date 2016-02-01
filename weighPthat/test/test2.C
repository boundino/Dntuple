using namespace std;
#include "uti.h"

int test2(TString ifname0 = "/data/wangj/debug/weighPthat/addmaxGenptBranch/Dzero/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0_addmaxgenpt_0.root",
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
  TFile* infPthat10 = TFile::Open(ifname10);
  TTree* ntHiPthat10 = (TTree*)infPthat10->Get("ntHi");
  TFile* infPthat15 = TFile::Open(ifname15);
  TTree* ntHiPthat15 = (TTree*)infPthat15->Get("ntHi");
  TFile* infPthat30 = TFile::Open(ifname30);
  TTree* ntHiPthat30 = (TTree*)infPthat30->Get("ntHi");
  TFile* infPthat50 = TFile::Open(ifname50);
  TTree* ntHiPthat50 = (TTree*)infPthat50->Get("ntHi");

  TH1F* hPthat0_pthat30_50_maxDgenpt0_5 = new TH1F("hPthat0_pthat30_50_maxDgenpt0_5","",20,30,50);
  hPthat0_pthat30_50_maxDgenpt0_5->SetLineColor(2);
  TH1F* hPthat0_pthat30_50_maxDgenpt5_10 = new TH1F("hPthat0_pthat30_50_maxDgenpt5_10","",20,30,50);
  TH1F* hPthat5_pthat30_50_maxDgenpt5_10 = new TH1F("hPthat5_pthat30_50_maxDgenpt5_10","",20,30,50);
  hPthat5_pthat30_50_maxDgenpt5_10->SetLineColor(3);
  TH1F* hPthat0_pthat30_50_maxDgenpt10_15 = new TH1F("hPthat0_pthat30_50_maxDgenpt10_15","",20,30,50);
  TH1F* hPthat5_pthat30_50_maxDgenpt10_15 = new TH1F("hPthat5_pthat30_50_maxDgenpt10_15","",20,30,50);
  TH1F* hPthat10_pthat30_50_maxDgenpt10_15 = new TH1F("hPthat10_pthat30_50_maxDgenpt10_15","",20,30,50);
  hPthat10_pthat30_50_maxDgenpt10_15->SetLineColor(4);
  TH1F* hPthat0_pthat30_50_maxDgenpt15_30 = new TH1F("hPthat0_pthat30_50_maxDgenpt15_30","",20,30,50);
  TH1F* hPthat5_pthat30_50_maxDgenpt15_30 = new TH1F("hPthat5_pthat30_50_maxDgenpt15_30","",20,30,50);
  TH1F* hPthat10_pthat30_50_maxDgenpt15_30 = new TH1F("hPthat10_pthat30_50_maxDgenpt15_30","",20,30,50);
  TH1F* hPthat15_pthat30_50_maxDgenpt15_30 = new TH1F("hPthat15_pthat30_50_maxDgenpt15_30","",20,30,50);
  hPthat15_pthat30_50_maxDgenpt15_30->SetLineColor(5);
  TH1F* hPthat0_pthat30_50_maxDgenpt30_inf = new TH1F("hPthat0_pthat30_50_maxDgenpt30_inf","",20,30,50);
  TH1F* hPthat5_pthat30_50_maxDgenpt30_inf = new TH1F("hPthat5_pthat30_50_maxDgenpt30_inf","",20,30,50);
  TH1F* hPthat10_pthat30_50_maxDgenpt30_inf = new TH1F("hPthat10_pthat30_50_maxDgenpt30_inf","",20,30,50);
  TH1F* hPthat15_pthat30_50_maxDgenpt30_inf = new TH1F("hPthat15_pthat30_50_maxDgenpt30_inf","",20,30,50);
  TH1F* hPthat30_pthat30_50_maxDgenpt30_inf = new TH1F("hPthat30_pthat30_50_maxDgenpt30_inf","",20,30,50);
  hPthat30_pthat30_50_maxDgenpt30_inf->SetLineColor(6);

  ntHiPthat0->Project("hPthat0_pthat30_50_maxDgenpt0_5","pthat","pthat>15&&pthat<30&&maxDgenpt>0&&maxDgenpt<5");
  divideBinWidthWithoutError(hPthat0_pthat30_50_maxDgenpt0_5);
  hPthat0_pthat30_50_maxDgenpt0_5->Scale(163481);

  ntHiPthat0->Project("hPthat0_pthat30_50_maxDgenpt5_10","pthat","pthat>15&&pthat<30&&maxDgenpt>5&&maxDgenpt<10");
  divideBinWidthWithoutError(hPthat0_pthat30_50_maxDgenpt5_10);
  ntHiPthat5->Project("hPthat5_pthat30_50_maxDgenpt5_10","pthat","pthat>15&&pthat<30&&maxDgenpt>5&&maxDgenpt>10");
  divideBinWidthWithoutError(hPthat5_pthat30_50_maxDgenpt5_10);
  hPthat5_pthat30_50_maxDgenpt5_10->Add(hPthat0_pthat30_50_maxDgenpt5_10);
  hPthat5_pthat30_50_maxDgenpt5_10->Scale(4110.11);

  ntHiPthat0->Project("hPthat0_pthat30_50_maxDgenpt10_15","pthat","pthat>15&&pthat<30&&maxDgenpt>10&&maxDgenpt<15");
  divideBinWidthWithoutError(hPthat0_pthat30_50_maxDgenpt10_15);
  ntHiPthat5->Project("hPthat5_pthat30_50_maxDgenpt10_15","pthat","pthat>15&&pthat<30&&maxDgenpt>10&&maxDgenpt<15");
  divideBinWidthWithoutError(hPthat5_pthat30_50_maxDgenpt10_15);
  ntHiPthat10->Project("hPthat10_pthat30_50_maxDgenpt10_15","pthat","pthat>15&&pthat<30&&maxDgenpt>10&&maxDgenpt<15");
  divideBinWidthWithoutError(hPthat10_pthat30_50_maxDgenpt10_15);
  hPthat10_pthat30_50_maxDgenpt10_15->Add(hPthat0_pthat30_50_maxDgenpt10_15);
  hPthat10_pthat30_50_maxDgenpt10_15->Add(hPthat5_pthat30_50_maxDgenpt10_15);
  hPthat10_pthat30_50_maxDgenpt10_15->Scale(367.362);

  ntHiPthat0->Project("hPthat0_pthat30_50_maxDgenpt15_30","pthat","pthat>15&&pthat<30&&maxDgenpt>15&&maxDgenpt<30");
  divideBinWidthWithoutError(hPthat0_pthat30_50_maxDgenpt15_30);
  ntHiPthat5->Project("hPthat5_pthat30_50_maxDgenpt15_30","pthat","pthat>15&&pthat<30&&maxDgenpt>15&&maxDgenpt<30");
  divideBinWidthWithoutError(hPthat5_pthat30_50_maxDgenpt15_30);
  ntHiPthat10->Project("hPthat10_pthat30_50_maxDgenpt15_30","pthat","pthat>15&&pthat<30&&maxDgenpt>15&&maxDgenpt<30");
  divideBinWidthWithoutError(hPthat10_pthat30_50_maxDgenpt15_30);
  ntHiPthat15->Project("hPthat15_pthat30_50_maxDgenpt15_30","pthat","pthat>15&&pthat<30&&maxDgenpt>15&&maxDgenpt<30");
  divideBinWidthWithoutError(hPthat15_pthat30_50_maxDgenpt15_30);
  hPthat15_pthat30_50_maxDgenpt15_30->Add(hPthat0_pthat30_50_maxDgenpt15_30);
  hPthat15_pthat30_50_maxDgenpt15_30->Add(hPthat5_pthat30_50_maxDgenpt15_30);
  hPthat15_pthat30_50_maxDgenpt15_30->Add(hPthat10_pthat30_50_maxDgenpt15_30);
  hPthat15_pthat30_50_maxDgenpt15_30->Scale(48.9383);

  TH2D *hempty = new TH2D("hempty","",50,0.,50.,10,1.e+0,1.e+9);
  hempty->GetXaxis()->SetTitle("pthat");
  hempty->GetYaxis()->SetTitle("dN/dpthat");
  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(.9);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);
  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogy();
  hempty->Draw();

  hPthat0_pthat0_5_maxDgenpt0_inf->Draw("same");
  hPthat0_pthat5_10_maxDgenpt0_5->Draw("same");
  hPthat0_pthat10_15_maxDgenpt0_5->Draw("same");
  hPthat0_pthat15_30_maxDgenpt0_5->Draw("same");



  return 1;
}
