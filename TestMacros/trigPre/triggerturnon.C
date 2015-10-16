#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <TLatex.h>
#include <TMath.h>
#include <TEfficiency.h>

TString prefilter = "Dgen==23333&&Dtrk1Pt>8.&&Dtrk2Pt>8.&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95";
Double_t BIN_MIN = 5;
Double_t BIN_MAX = 70;
Int_t BIN_NUM = 20;
void triggerturnon(TString infname="/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151012_HLTemulation_DinderMC_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010_EvtBase.root")
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
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1",hinclusive);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet80Eta2p3_ForDmesons_v1_Prescl",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1",hinclusive);
  plotTurnOn(root,"HLT_PuAK4CaloJet60Eta2p3_ForDmesons_v1_Prescl",hinclusive);
  //plotTurnOn(root,"",hinclusive);
}

void plotTurnOn(TTree* inttree, TString triggerpass, TH1D* hinclusive)
{
  TH1D* htriggerpass = new TH1D(Form("h%s",triggerpass.Data()),";p_{T} (GeV/c);Pass eff (Matched reco)",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s",triggerpass.Data()),"Dpt",Form("%s&&%s",prefilter.Data(),triggerpass.Data()));
  htriggerpass->Sumw2();
  TEfficiency* pEff = new TEfficiency(*htriggerpass,*hinclusive);
  TCanvas* ctriggerpass = new TCanvas(Form("ch%s",triggerpass.Data()),"",500,500);
  pEff->Draw("AP");
  TLatex* tex = new TLatex(0.20,0.90,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.03);
  tex->Draw();
  ctriggerpass->SaveAs(Form("triggerturnonPlots/ch%s.pdf",triggerpass.Data()));
}
