#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include "fitD.h"
#include <TCanvas.h>

const int BIN_NUM = 10;
Double_t ptbins[BIN_NUM+1] = {3.5, 4.5, 5.5, 7., 9., 11., 13., 16., 20., 28., 40.};
void efftest()
{
  TFile* infmcMIT = new TFile("/export/d00/scratch/jwang/Dmeson/ntD_20150924_MC_merge_withoutweight_skim.root");
  TFile* infmcPUD = new TFile("/export/d00/scratch/jwang/Dmeson/Dmesonana_hiforest_PbPbD0tokaonpion_Pthat0153050_D0pt1p0_tkpt1p0eta1p1_2760GeV_0803_d2p0_alpha0p2_prob0p05.root");
  TFile* infdataMIT = new TFile("/export/d00/scratch/jwang/Dmeson/ntD_20150924_DfinderData_HIMinBiasUPC_HIRun2011-14Mar2014-v2_20150912_EvtBase_skim.root");
  TFile* infdataPUD = new TFile("/export/d00/scratch/jwang/Dmeson/Dmesonana_Rereco_MBtrig_hfcandv2_d0pt1p0_tk1p0_etacut_tight_d2p5_alpha0p12_prob0p05_6lumi.root");

  TTree* ntdataMITreco = (TTree*)infdataMIT->Get("ntDkpi");
  TTree* ntmcMITreco = (TTree*)infmcMIT->Get("ntDkpi");
  TTree* ntmcMITgen = (TTree*)infmcMIT->Get("ntGen");
  TTree* ntdataPUDreco = (TTree*)infdataPUD->Get("recodmesontree");
  TTree* ntmcPUDreco = (TTree*)infmcPUD->Get("recodmesontree");
  TTree* ntmcPUDgen = (TTree*)infmcPUD->Get("gendmesontree");

  TH1D* hdataMITreco = new TH1D("hdataMITreco","",BIN_NUM,ptbins);
  TH1D* hmcMITreco = new TH1D("hmcMITreco","",BIN_NUM,ptbins);
  TH1D* hmcMITrecoMat = new TH1D("hmcMITrecoMat","",BIN_NUM,ptbins);
  TH1D* hmcMITgen = new TH1D("hmcMITgen","",BIN_NUM,ptbins);
  TH1D* hdataPUDreco = new TH1D("hdataPUDreco","",BIN_NUM,ptbins);
  TH1D* hmcPUDreco = new TH1D("hmcPUDreco","",BIN_NUM,ptbins);
  TH1D* hmcPUDrecoMat = new TH1D("hmcPUDrecoMat","",BIN_NUM,ptbins);
  TH1D* hmcPUDgen = new TH1D("hmcPUDgen","",BIN_NUM,ptbins);

  ntdataMITreco->Project("hdataMITreco","Dpt",Form("%s&&HLT_HIMinBiasHfOrBSC_v1",cut1.Data()));
  ntmcMITreco->Project("hmcMITreco","Dpt",Form("%s&&HLT_HIMinBiasHfOrBSC_v4",cut1.Data()));
  ntmcMITreco->Project("hmcMITrecoMat","Dpt",Form("%s&&HLT_HIMinBiasHfOrBSC_v4&&Dgen==23333",cut1.Data()));
  ntmcMITgen->Project("hmcMITgen","Gpt","(GisSignal==1||GisSignal==2)&&Gy>-1.&&Gy<1.");
  ntdataPUDreco->Project("hdataPUDreco","dcandpt",Form("%s",cutpurdue1.Data()));
  ntmcPUDreco->Project("hmcPUDreco","dcandpt",Form("%s",cutpurdue1.Data()));
  ntmcPUDreco->Project("hmcPUDrecoMat","dcandpt",Form("%s&&(matchedtogen&&nongendoublecounted)",cutpurdue1.Data()));
  ntmcPUDgen->Project("hmcPUDgen","dpt","dy>-1.&&dy<1.");

  TH1D* hmcMITeff = (TH1D*)hmcMITrecoMat->Clone("hmcMITeff");
  TH1D* hmcPUDeff = (TH1D*)hmcPUDrecoMat->Clone("hmcPUDeff");
  hmcMITeff->Divide(hmcMITgen);
  hmcPUDeff->Divide(hmcPUDgen);
  TH1D* hdataMITcorr = (TH1D*)hdataMITreco->Clone("hdataMITcorr");
  TH1D* hdataPUDcorr = (TH1D*)hdataPUDreco->Clone("hdataPUDcorr");
  hdataMITcorr->Divide(hmcMITeff);
  hdataPUDcorr->Divide(hmcPUDeff);

  TCanvas* crecoMat = new TCanvas("crecoMat","",500,500);
  hmcMITrecoMat->SetTitle(";p_{T} (GeV/c);MC Matched reco (opt cuts)");
  hmcMITrecoMat->Draw();
  hmcPUDrecoMat->SetMarkerSize(0.8);
  hmcPUDrecoMat->SetMarkerStyle(20);
  hmcPUDrecoMat->SetMarkerColor(kRed);
  hmcPUDrecoMat->Draw("samep");
  crecoMat->SaveAs("../ResultsTest/crecoMat.pdf");

  TCanvas* creco = new TCanvas("creco","",500,500);
  hmcMITreco->SetTitle(";p_{T} (GeV/c);MC reco (opt cuts)");
  hmcMITreco->Draw();
  hmcPUDreco->SetMarkerSize(0.8);
  hmcPUDreco->SetMarkerStyle(20);
  hmcPUDreco->SetMarkerColor(kRed);
  hmcPUDreco->Draw("samep");
  creco->SaveAs("../ResultsTest/creco.pdf");

  TCanvas* cgen = new TCanvas("cgen","",500,500);
  hmcMITgen->SetTitle(";p_{T} (GeV/c);MC Gen D^{0}");
  hmcMITgen->Draw();
  hmcPUDgen->SetMarkerSize(0.8);
  hmcPUDgen->SetMarkerStyle(20);
  hmcPUDgen->SetMarkerColor(kRed);
  hmcPUDgen->Draw("samep");
  cgen->SaveAs("../ResultsTest/cgen.pdf");

  TCanvas* ceff = new TCanvas("ceff","",500,500);
  hmcMITeff->SetTitle(";p_{T} (GeV/c);Matched reco (opt cuts)/Gen");
  hmcMITeff->Draw();
  hmcPUDeff->SetMarkerSize(0.8);
  hmcPUDeff->SetMarkerStyle(20);
  hmcPUDeff->SetMarkerColor(kRed);
  hmcPUDeff->Draw("samep");
  ceff->SaveAs("../ResultsTest/ceff.pdf");

  TCanvas* craw = new TCanvas("craw","",500,500);
  craw->SetLogy();
  hdataMITreco->SetTitle(";p_{T} (GeV/c);raw data (opt cuts)");
  hdataMITreco->Draw();
  hdataPUDreco->SetMarkerSize(0.8);
  hdataPUDreco->SetMarkerStyle(20);
  hdataPUDreco->SetMarkerColor(kRed);
  hdataPUDreco->Draw("samep");
  craw->SaveAs("../ResultsTest/craw.pdf");

  TCanvas* ccorr = new TCanvas("ccorr","",500,500);
  ccorr->SetLogy();
  hdataMITcorr->SetTitle(";p_{T} (GeV/c);corrected data (opt cuts)");
  hdataMITcorr->Draw();
  hdataPUDcorr->SetMarkerSize(0.8);
  hdataPUDcorr->SetMarkerStyle(20);
  hdataPUDcorr->SetMarkerColor(kRed);
  hdataPUDcorr->Draw("samep");
  ccorr->SaveAs("../ResultsTest/ccorr.pdf");
}
