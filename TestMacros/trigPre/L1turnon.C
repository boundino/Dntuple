#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <TLatex.h>
#include <TMath.h>
#include <TEfficiency.h>

//TString mvatk = "((Dtrk1Quality&2)&&(Dtrk2Quality&2))";//tight
TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";//highpurity
//TString prefilter = Form("(Dgen==23333||Dgen==23344)&&Dmaxpt&&TMath::Abs(Dy)<2.0&&Dtrk1Pt>8.&&Dtrk2Pt>8.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
TString prefilter = Form("Dgen==23333&&TMath::Abs(Dy)<2.0&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&%s",mvatk.Data());
Bool_t isPbPb = false;
Float_t pthat = 35.;

void L1turnon()
{
  gStyle->SetMarkerSize(0.8);
  void plotTurnOnNL1seed(TTree* inttree, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);
  TString infname;
  if(isPbPb) 
	  //infname = Form("/home/sun229/sl6_PbPb/HFTrig_75x/CMSSW_7_5_3_patch1/src/Dntuple/rootfiles/ntD_20151029_DfinderMC_20151029_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_HLTv16.root",pthat,pthat);
	  infname = Form("/afs/cern.ch/work/j/jisun/HIN/sl6/HFTrig_75x/CMSSW_7_5_3_patch1/src/Dntuple/rootfiles/");
  else 
	  infname = Form("/afs/cern.ch/work/j/jisun/HIN/sl6/HFTrig_75x/CMSSW_7_5_3_patch1/src/Dntuple/CodeForNtupleProduction/ntD_20151029_DfinderMC_20151029_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_HFlowpuv11_MBseed.root",pthat,pthat);
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");

  plotTurnOnNL1seed(root,40,0,80);

}

void plotTurnOnNL1seed(TTree* inttree, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX)
{
  TH1D* hMBseed = new TH1D("h_MBseed",";Matched reco D^{0} p_{T} (GeV/c);Pass efficiency (MB seed)",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_MBseed","Dpt",Form("%s",prefilter.Data()));
  hMBseed->Sumw2();

  TH2D* hempty = new TH2D("hempty",";Matched reco D^{0} p_{T} (GeV/c);L1 seed efficiency",BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);

  TH1D* hL1seedJet8 = new TH1D("h_hL1seedJet8","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet8","Dpt",Form("%s&&L1_SingleJet8_BptxAND",prefilter.Data()));
  hL1seedJet8->Sumw2();
  TEfficiency* pL1seedJet8 = new TEfficiency(*hL1seedJet8,*hMBseed);

  TH1D* hL1seedJet12 = new TH1D("h_hL1seedJet12","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet12","Dpt",Form("%s&&L1_SingleJet12_BptxAND",prefilter.Data()));
  hL1seedJet12->Sumw2();
  TEfficiency* pL1seedJet12 = new TEfficiency(*hL1seedJet12,*hMBseed);

  TH1D* hL1seedJet16 = new TH1D("h_hL1seedJet16","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet16","Dpt",Form("%s&&L1_SingleJet16_BptxAND",prefilter.Data()));
  hL1seedJet16->Sumw2();
  TEfficiency* pL1seedJet16 = new TEfficiency(*hL1seedJet16,*hMBseed);

  TH1D* hL1seedJet20 = new TH1D("h_hL1seedJet20","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet20","Dpt",Form("%s&&L1_SingleJet20_BptxAND",prefilter.Data()));
  hL1seedJet20->Sumw2();
  TEfficiency* pL1seedJet20 = new TEfficiency(*hL1seedJet20,*hMBseed);

  TH1D* hL1seedJet24 = new TH1D("h_hL1seedJet24","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet24","Dpt",Form("%s&&L1_SingleJet24_BptxAND",prefilter.Data()));
  hL1seedJet24->Sumw2();
  TEfficiency* pL1seedJet24 = new TEfficiency(*hL1seedJet24,*hMBseed);

  TH1D* hL1seedJet28 = new TH1D("h_hL1seedJet28","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet28","Dpt",Form("%s&&L1_SingleJet28_BptxAND",prefilter.Data()));
  hL1seedJet28->Sumw2();
  TEfficiency* pL1seedJet28 = new TEfficiency(*hL1seedJet28,*hMBseed);

  TH1D* hL1seedJet32 = new TH1D("h_hL1seedJet32","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet32","Dpt",Form("%s&&L1_SingleJet32_BptxAND",prefilter.Data()));
  hL1seedJet32->Sumw2();
  TEfficiency* pL1seedJet32 = new TEfficiency(*hL1seedJet32,*hMBseed);

  TH1D* hL1seedJet36 = new TH1D("h_hL1seedJet36","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet36","Dpt",Form("%s&&L1_SingleJet36_BptxAND",prefilter.Data()));
  hL1seedJet36->Sumw2();
  TEfficiency* pL1seedJet36 = new TEfficiency(*hL1seedJet36,*hMBseed);

  TH1D* hL1seedJet40 = new TH1D("h_hL1seedJet40","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet40","Dpt",Form("%s&&L1_SingleJet40_BptxAND",prefilter.Data()));
  hL1seedJet40->Sumw2();
  TEfficiency* pL1seedJet40 = new TEfficiency(*hL1seedJet40,*hMBseed);

  TH1D* hL1seedJet44 = new TH1D("h_hL1seedJet44","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet44","Dpt",Form("%s&&L1_SingleJet44_BptxAND",prefilter.Data()));
  hL1seedJet44->Sumw2();
  TEfficiency* pL1seedJet44 = new TEfficiency(*hL1seedJet44,*hMBseed);

  TH1D* hL1seedJet48 = new TH1D("h_hL1seedJet48","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet48","Dpt",Form("%s&&L1_SingleJet48_BptxAND",prefilter.Data()));
  hL1seedJet48->Sumw2();
  TEfficiency* pL1seedJet48 = new TEfficiency(*hL1seedJet48,*hMBseed);

  TH1D* hL1seedJet52 = new TH1D("h_hL1seedJet52","",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project("h_hL1seedJet52","Dpt",Form("%s&&L1_SingleJet52_BptxAND",prefilter.Data()));
  hL1seedJet52->Sumw2();
  TEfficiency* pL1seedJet52 = new TEfficiency(*hL1seedJet52,*hMBseed);

  TCanvas* cL1seed = new TCanvas("c_L1seed","",500,500);
  gPad->SetGridx();
  gPad->SetGridy();
  hempty->Draw();
  pL1seedJet8->SetMarkerColor(9);
  pL1seedJet8->SetLineColor(9);
  pL1seedJet8->Draw("PSAME");
  pL1seedJet12->SetMarkerColor(7);
  pL1seedJet12->SetLineColor(7);
  pL1seedJet12->Draw("PSAME");
  pL1seedJet16->SetMarkerColor(3);
  pL1seedJet16->SetLineColor(3);
  pL1seedJet16->Draw("PSAME");
  pL1seedJet20->SetMarkerColor(5);
  pL1seedJet20->SetLineColor(5);
  pL1seedJet20->Draw("PSAME");
  pL1seedJet24->SetMarkerColor(6);
  pL1seedJet24->SetLineColor(6);
  pL1seedJet24->Draw("PSAME");
  pL1seedJet28->SetMarkerColor(1);
  pL1seedJet28->SetLineColor(1);
  pL1seedJet28->Draw("PSAME");
  pL1seedJet32->SetMarkerColor(4);
  pL1seedJet32->SetLineColor(4);
  pL1seedJet32->Draw("PSAME");
  pL1seedJet36->SetMarkerColor(50);
  pL1seedJet36->SetLineColor(50);
  pL1seedJet36->Draw("PSAME");
  pL1seedJet40->SetMarkerColor(2);
  pL1seedJet40->SetLineColor(2);
  pL1seedJet40->Draw("PSAME");
  pL1seedJet44->SetMarkerColor(28);
  pL1seedJet44->SetLineColor(28);
  pL1seedJet44->Draw("PSAME");
  pL1seedJet48->SetMarkerColor(8);
  pL1seedJet48->SetLineColor(8);
  pL1seedJet48->Draw("PSAME");
  pL1seedJet52->SetMarkerColor(12);
  pL1seedJet52->SetLineColor(12);
  pL1seedJet52->Draw("PSAME");
  cL1seed->SaveAs(Form("L1turnonstudy/c%0.f_L1seed.pdf",pthat));
  cL1seed->SaveAs(Form("L1turnonstudy/c%0.f_L1seed.png",pthat));
}
