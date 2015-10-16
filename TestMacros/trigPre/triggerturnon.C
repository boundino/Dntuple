#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <TLatex.h>
#include <TMath.h>
#include <TEfficiency.h>

TString prefilter = "Dgen==23333&&Dtrk1Pt>8.&&Dtrk2Pt>8.&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95";
Double_t BIN_MIN = 0;
Double_t BIN_MAX = 80;
Int_t BIN_NUM = 8;
//void triggerturnon(TString infname="/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151012_HLTemulation_DinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010_EvtBase.root")
void triggerturnon(TString infname="/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151016_DinderMC_20151015_EvtMatching_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010.root")
{
  void plotTurnOn(TTree* inttree, TString triggerpass, TH1D* hinclusive);
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  TH1D* hinclusive = new TH1D("hinclusive",";p_{T} (GeV/c);Matched reco D^{0}",BIN_NUM,BIN_MIN,BIN_MAX);
  root->Project("hinclusive","Dpt",prefilter);
  hinclusive->Sumw2();
  for(int i=0;i<BIN_NUM;i++) cout<<hinclusive->GetBinContent(i+1)<<endl;
  TCanvas* chinclusive = new TCanvas("chinclusive","",500,500);
  hinclusive->Draw();
  hinclusive->SetStats(0);
  chinclusive->SaveAs("triggerturnonPlots/chinclusive.pdf");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1",hinclusive);
  /*
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl",hinclusive);
  */
}

void plotTurnOn(TTree* inttree, TString triggerpass, TH1D* hinclusive)
{
  TH1D* hMBseed = new TH1D(Form("h%s_MBseed",triggerpass.Data()),";Matched reco D^{0} p_{T} (GeV/c);Pass efficiency (MB seed)",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_MBseed",triggerpass.Data()),"Dpt",Form("%s&&%s",prefilter.Data(),triggerpass.Data()));
  hMBseed->Sumw2();
  TEfficiency* pEffMBseed = new TEfficiency(*hMBseed,*hinclusive);
  pEffMBseed->SetTitle(";Matched reco D^{0} p_{T} (GeV/c);Pass efficiency (MB seed)");
  TCanvas* cMBseed = new TCanvas(Form("c%s_MBseed",triggerpass.Data()),"",500,500);
  pEffMBseed->Draw("AP");
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  cMBseed->SaveAs(Form("triggerturnonPlots/c%s_MBseed.pdf",triggerpass.Data()));

  TH2D* hempty = new TH2D(Form("hempty%s",triggerpass.Data()),";Matched reco D^{0} p_{T} (GeV/c);L1 seed / MB seed",BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  TH1D* hL1seedJet8 = new TH1D(Form("h%s_hL1seedJet8",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet8",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet8_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet8->Sumw2();
  TEfficiency* pL1seedJet8 = new TEfficiency(*hL1seedJet8,*hMBseed);
  TH1D* hL1seedJet16 = new TH1D(Form("h%s_hL1seedJet16",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet16",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet16_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet16->Sumw2();
  TEfficiency* pL1seedJet16 = new TEfficiency(*hL1seedJet16,*hMBseed);
  TH1D* hL1seedJet28 = new TH1D(Form("h%s_hL1seedJet28",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet28",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet28_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet28->Sumw2();
  TEfficiency* pL1seedJet28 = new TEfficiency(*hL1seedJet28,*hMBseed);
  TH1D* hL1seedJet40 = new TH1D(Form("h%s_hL1seedJet40",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet40",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet40_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet40->Sumw2();
  TEfficiency* pL1seedJet40 = new TEfficiency(*hL1seedJet40,*hMBseed);
  TH1D* hL1seedJet44 = new TH1D(Form("h%s_hL1seedJet44",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet44",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet44_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet44->Sumw2();
  TEfficiency* pL1seedJet44 = new TEfficiency(*hL1seedJet44,*hMBseed);
  TH1D* hL1seedJet56 = new TH1D(Form("h%s_hL1seedJet56",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet56",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet56_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet56->Sumw2();
  TEfficiency* pL1seedJet56 = new TEfficiency(*hL1seedJet56,*hMBseed);
  TH1D* hL1seedJet92 = new TH1D(Form("h%s_hL1seedJet92",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_hL1seedJet92",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet92_BptxAND",prefilter.Data(),triggerpass.Data()));
  hL1seedJet92->Sumw2();
  TEfficiency* pL1seedJet92 = new TEfficiency(*hL1seedJet92,*hMBseed);
  TCanvas* cL1seed = new TCanvas(Form("c%s_L1seed",triggerpass.Data()),"",500,500);
  hempty->Draw();
  tex->Draw();
  pL1seedJet8->SetMarkerColor(1);
  pL1seedJet8->SetLineColor(1);
  pL1seedJet8->SetLineWidth(2);
  pL1seedJet8->Draw("PSAME");
  pL1seedJet16->SetMarkerColor(2);
  pL1seedJet16->SetLineColor(2);
  pL1seedJet16->SetLineWidth(2);
  pL1seedJet16->Draw("PSAME");
  pL1seedJet28->SetMarkerColor(3);
  pL1seedJet28->SetLineColor(3);
  pL1seedJet28->SetLineWidth(2);
  pL1seedJet28->Draw("PSAME");
  pL1seedJet40->SetMarkerColor(4);
  pL1seedJet40->SetLineColor(4);
  pL1seedJet40->SetLineWidth(2);
  pL1seedJet40->Draw("PSAME");
  pL1seedJet44->SetMarkerColor(5);
  pL1seedJet44->SetLineColor(5);
  pL1seedJet44->SetLineWidth(2);
  pL1seedJet44->Draw("PSAME");
  pL1seedJet56->SetMarkerColor(6);
  pL1seedJet56->SetLineColor(6);
  pL1seedJet56->SetLineWidth(2);
  pL1seedJet56->Draw("PSAME");
  pL1seedJet92->SetMarkerColor(7);
  pL1seedJet92->SetLineColor(7);
  pL1seedJet92->SetLineWidth(2);
  pL1seedJet92->Draw("PSAME");
  cL1seed->SaveAs(Form("triggerturnonPlots/c%s_L1seed.pdf",triggerpass.Data()));

}
