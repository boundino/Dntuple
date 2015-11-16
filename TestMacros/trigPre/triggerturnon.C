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

//TString mvatk = "((Dtrk1Quality&2)&&(Dtrk2Quality&2))";//tight
TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";//highpurity
TString prefilter = Form("(Dgen==23333||Dgen==23344)&&DmaxptMatched&&Dtrk1Pt>1.&&Dtrk2Pt>1.&&Dchi2cl>0.05&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95&&%s",mvatk.Data());
Bool_t isPbPb = false;
Float_t pthat = 35.;

void triggerturnon()
{
  void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  void plotTurnOnNL1seed(TTree* inttree, TString triggerpass, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);
  TString infname;
  if(!isPbPb) infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151115_DfinderMC_20151115_EvtMatching_Pythia_D0pt%.0fp0_Pthat%.0f_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_755patch2_v20_MBseed_1116.root",pthat,pthat);
  else infname = Form("/export/d00/scratch/jwang/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151110_50k_L1v4_v15_loosecuts_MBseed_1108.root",pthat,pthat);
  //infname = "/export/d00/scratch/jwang/Dmeson/nt_merged_dntuple.root";
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  root->AddFriend("HltTree");

  if(!isPbPb)
    {
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt8_v1&&L1_SingleJet16_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt15_v1&&L1_SingleJet24_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1&&L1_SingleJet28_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1&&L1_SingleJet40_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1&&L1_SingleJet40_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1&&L1_SingleJet48_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1&&L1_SingleJet48_BptxAND","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      /*
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1",16,0,80);
      */
    }
  else
    {
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt30_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt50_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dpt","pt","p_{T} (GeV/c)",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt30_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt50_v1",16,0,80);
      plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1",16,0,80);
    }
}

void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="")
{
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);

  TH1D* hinclusive = new TH1D(Form("hinclusive_%s_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Candidates",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("hinclusive_%s_%s",triggerpass.Data(),varname.Data()),variable,Form("%s%s",prefilter.Data(),addcut.Data()));
  hinclusive->Sumw2();
  if(triggerpass=="HLT_DmesonTrackingGlobalPt8_Dpt20_v1"||triggerpass=="HLT_DmesonPPTrackingGlobal_Dpt20_v1")
    {
      TCanvas* chinclusive = new TCanvas(Form("chinclusive_%s",varname.Data()),"",500,500);
      hinclusive->Draw();
      hinclusive->SetStats(0);
      tex->Draw();
      if(isPbPb) chinclusive->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/pbpb/chinclusive_%s.pdf",pthat,varname.Data()));
      else chinclusive->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/pp/chinclusive_%s.pdf",pthat,varname.Data()));
    }
  TH2D* hempty = new TH2D(Form("hempty_%s_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Pass efficiency (ZB seed)",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  TH1D* hMBseed = new TH1D(Form("h%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_MBseed_%s",triggerpass.Data(),varname.Data()),variable,Form("%s%s&&%s",prefilter.Data(),addcut.Data(),triggerpass.Data()));
  hMBseed->Sumw2();
  TEfficiency* pEffMBseed = new TEfficiency(*hMBseed,*hinclusive);
  TCanvas* cMBseed = new TCanvas(Form("c%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",500,500);
  hempty->Draw();
  pEffMBseed->Draw("PSAME");
  tex->Draw();
  /*
  if(isPbPb) cMBseed->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/pbpb/c%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));
  else cMBseed->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/pp/c%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));
  */
  cMBseed->SaveAs(Form("triggerturnonPlots/pthat%.0f/ZBseed/pp/c%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));
}

void plotTurnOnNL1seed(TTree* inttree, TString triggerpass, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX)
{
  TH1D* hMBseed = new TH1D(Form("h%s_MBseed",triggerpass.Data()),";Matched reco D^{0} p_{T} (GeV/c);Pass efficiency (MB seed)",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_MBseed",triggerpass.Data()),"Dpt",Form("%s&&%s",prefilter.Data(),triggerpass.Data()));
  hMBseed->Sumw2();
  TH2D* hempty = new TH2D(Form("hempty_%s",triggerpass.Data()),";Matched reco D^{0} p_{T} (GeV/c);L1 seed / MB seed",BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);

  if(isPbPb)
    {
      TH1D* hpbpbL1seedJet16 = new TH1D(Form("h%s_hpbpbL1seedJet16",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet16",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet16_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet16->Sumw2();
      TEfficiency* ppbpbL1seedJet16 = new TEfficiency(*hpbpbL1seedJet16,*hMBseed);
      TH1D* hpbpbL1seedJet28 = new TH1D(Form("h%s_hpbpbL1seedJet28",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet28",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet28_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet28->Sumw2();
      TEfficiency* ppbpbL1seedJet28 = new TEfficiency(*hpbpbL1seedJet28,*hMBseed);
      TH1D* hpbpbL1seedJet32 = new TH1D(Form("h%s_hpbpbL1seedJet32",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet32",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet32_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet32->Sumw2();
      TEfficiency* ppbpbL1seedJet32 = new TEfficiency(*hpbpbL1seedJet32,*hMBseed);
      TH1D* hpbpbL1seedJet36 = new TH1D(Form("h%s_hpbpbL1seedJet36",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet36",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet36_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet36->Sumw2();
      TEfficiency* ppbpbL1seedJet36 = new TEfficiency(*hpbpbL1seedJet36,*hMBseed);
      TH1D* hpbpbL1seedJet40 = new TH1D(Form("h%s_hpbpbL1seedJet40",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet40",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet40_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet40->Sumw2();
      TEfficiency* ppbpbL1seedJet40 = new TEfficiency(*hpbpbL1seedJet40,*hMBseed);
      TH1D* hpbpbL1seedJet44 = new TH1D(Form("h%s_hpbpbL1seedJet44",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet44",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet44_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet44->Sumw2();
      TEfficiency* ppbpbL1seedJet44 = new TEfficiency(*hpbpbL1seedJet44,*hMBseed);
      TH1D* hpbpbL1seedJet48 = new TH1D(Form("h%s_hpbpbL1seedJet48",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet48",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet48_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet48->Sumw2();
      TEfficiency* ppbpbL1seedJet48 = new TEfficiency(*hpbpbL1seedJet48,*hMBseed);
      TH1D* hpbpbL1seedJet52 = new TH1D(Form("h%s_hpbpbL1seedJet52",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet52",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet52_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet52->Sumw2();
      TEfficiency* ppbpbL1seedJet52 = new TEfficiency(*hpbpbL1seedJet52,*hMBseed);
      TH1D* hpbpbL1seedJet56 = new TH1D(Form("h%s_hpbpbL1seedJet56",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet56",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet56_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet56->Sumw2();
      TEfficiency* ppbpbL1seedJet56 = new TEfficiency(*hpbpbL1seedJet56,*hMBseed);
      TH1D* hpbpbL1seedJet64 = new TH1D(Form("h%s_hpbpbL1seedJet64",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hpbpbL1seedJet64",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleS1Jet64_BptxAND",prefilter.Data(),triggerpass.Data()));
      hpbpbL1seedJet64->Sumw2();
      TEfficiency* ppbpbL1seedJet64 = new TEfficiency(*hpbpbL1seedJet64,*hMBseed);
      TCanvas* cpbpbL1seed = new TCanvas(Form("c%s_pbpbL1seed",triggerpass.Data()),"",500,500);
      hempty->Draw();
      tex->Draw();
      ppbpbL1seedJet16->SetMarkerColor(1);
      ppbpbL1seedJet16->SetLineColor(1);
      ppbpbL1seedJet16->SetLineWidth(2);
      ppbpbL1seedJet16->Draw("PSAME");
      ppbpbL1seedJet28->SetMarkerColor(2);
      ppbpbL1seedJet28->SetLineColor(2);
      ppbpbL1seedJet28->SetLineWidth(2);
      ppbpbL1seedJet28->Draw("PSAME");
      ppbpbL1seedJet32->SetMarkerColor(3);
      ppbpbL1seedJet32->SetLineColor(3);
      ppbpbL1seedJet32->SetLineWidth(2);
      ppbpbL1seedJet32->Draw("PSAME");
      ppbpbL1seedJet36->SetMarkerColor(4);
      ppbpbL1seedJet36->SetLineColor(4);
      ppbpbL1seedJet36->SetLineWidth(2);
      ppbpbL1seedJet36->Draw("PSAME");
      ppbpbL1seedJet40->SetMarkerColor(5);
      ppbpbL1seedJet40->SetLineColor(5);
      ppbpbL1seedJet40->SetLineWidth(2);
      ppbpbL1seedJet40->Draw("PSAME");
      ppbpbL1seedJet44->SetMarkerColor(6);
      ppbpbL1seedJet44->SetLineColor(6);
      ppbpbL1seedJet44->SetLineWidth(2);
      ppbpbL1seedJet44->Draw("PSAME");
      ppbpbL1seedJet48->SetMarkerColor(7);
      ppbpbL1seedJet48->SetLineColor(7);
      ppbpbL1seedJet48->SetLineWidth(2);
      ppbpbL1seedJet48->Draw("PSAME");
      ppbpbL1seedJet52->SetMarkerColor(8);
      ppbpbL1seedJet52->SetLineColor(8);
      ppbpbL1seedJet52->SetLineWidth(2);
      ppbpbL1seedJet52->Draw("PSAME");
      ppbpbL1seedJet56->SetMarkerColor(9);
      ppbpbL1seedJet56->SetLineColor(9);
      ppbpbL1seedJet56->SetLineWidth(2);
      ppbpbL1seedJet56->Draw("PSAME");
      ppbpbL1seedJet64->SetMarkerColor(kOrange+7);
      ppbpbL1seedJet64->SetLineColor(kOrange+7);
      ppbpbL1seedJet64->SetLineWidth(2);
      ppbpbL1seedJet64->Draw("PSAME");
      cpbpbL1seed->SaveAs(Form("triggerturnonPlots/pthat%.0f/L1seed/pbpb/c%s_L1seed.pdf",pthat,triggerpass.Data()));
    }
  else
    {
      TH1D* hppL1seedJet8 = new TH1D(Form("h%s_hppL1seedJet8",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet8",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet8_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet8->Sumw2();
      TEfficiency* pppL1seedJet8 = new TEfficiency(*hppL1seedJet8,*hMBseed);
      TH1D* hppL1seedJet12 = new TH1D(Form("h%s_hppL1seedJet12",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet12",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet12_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet12->Sumw2();
      TEfficiency* pppL1seedJet12 = new TEfficiency(*hppL1seedJet12,*hMBseed);
      TH1D* hppL1seedJet16 = new TH1D(Form("h%s_hppL1seedJet16",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet16",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet16_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet16->Sumw2();
      TEfficiency* pppL1seedJet16 = new TEfficiency(*hppL1seedJet16,*hMBseed);
      TH1D* hppL1seedJet20 = new TH1D(Form("h%s_hppL1seedJet20",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet20",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet20_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet20->Sumw2();
      TEfficiency* pppL1seedJet20 = new TEfficiency(*hppL1seedJet20,*hMBseed);
      TH1D* hppL1seedJet24 = new TH1D(Form("h%s_hppL1seedJet24",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet24",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet24_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet24->Sumw2();
      TEfficiency* pppL1seedJet24 = new TEfficiency(*hppL1seedJet24,*hMBseed);
      TH1D* hppL1seedJet28 = new TH1D(Form("h%s_hppL1seedJet28",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet28",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet28_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet28->Sumw2();
      TEfficiency* pppL1seedJet28 = new TEfficiency(*hppL1seedJet28,*hMBseed);
      TH1D* hppL1seedJet32 = new TH1D(Form("h%s_hppL1seedJet32",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet32",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet32_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet32->Sumw2();
      TEfficiency* pppL1seedJet32 = new TEfficiency(*hppL1seedJet32,*hMBseed);
      TH1D* hppL1seedJet36 = new TH1D(Form("h%s_hppL1seedJet36",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet36",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet36_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet36->Sumw2();
      TEfficiency* pppL1seedJet36 = new TEfficiency(*hppL1seedJet36,*hMBseed);
      TH1D* hppL1seedJet40 = new TH1D(Form("h%s_hppL1seedJet40",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet40",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet40_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet40->Sumw2();
      TEfficiency* pppL1seedJet40 = new TEfficiency(*hppL1seedJet40,*hMBseed);
      TH1D* hppL1seedJet44 = new TH1D(Form("h%s_hppL1seedJet44",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet44",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet44_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet44->Sumw2();
      TEfficiency* pppL1seedJet44 = new TEfficiency(*hppL1seedJet44,*hMBseed);
      TH1D* hppL1seedJet48 = new TH1D(Form("h%s_hppL1seedJet48",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet48",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet48_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet48->Sumw2();
      TEfficiency* pppL1seedJet48 = new TEfficiency(*hppL1seedJet48,*hMBseed);
      TH1D* hppL1seedJet52 = new TH1D(Form("h%s_hppL1seedJet52",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet52",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet52_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet52->Sumw2();
      TEfficiency* pppL1seedJet52 = new TEfficiency(*hppL1seedJet52,*hMBseed);
      TH1D* hppL1seedJet60 = new TH1D(Form("h%s_hppL1seedJet60",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet60",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet60_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet60->Sumw2();
      TEfficiency* pppL1seedJet60 = new TEfficiency(*hppL1seedJet60,*hMBseed);
      TH1D* hppL1seedJet68 = new TH1D(Form("h%s_hppL1seedJet68",triggerpass.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
      inttree->Project(Form("h%s_hppL1seedJet68",triggerpass.Data()),"Dpt",Form("%s&&%s&&L1_SingleJet68_BptxAND",prefilter.Data(),triggerpass.Data()));
      hppL1seedJet68->Sumw2();
      TEfficiency* pppL1seedJet68 = new TEfficiency(*hppL1seedJet68,*hMBseed);
      TCanvas* cppL1seed = new TCanvas(Form("c%s_ppL1seed",triggerpass.Data()),"",500,500);
      hempty->Draw();
      tex->Draw();
      pppL1seedJet8->SetMarkerColor(1);
      pppL1seedJet8->SetLineColor(1);
      pppL1seedJet8->SetLineWidth(2);
      pppL1seedJet8->Draw("PSAME");
      pppL1seedJet12->SetMarkerColor(2);
      pppL1seedJet12->SetLineColor(2);
      pppL1seedJet12->SetLineWidth(2);
      pppL1seedJet12->Draw("PSAME");
      pppL1seedJet16->SetMarkerColor(3);
      pppL1seedJet16->SetLineColor(3);
      pppL1seedJet16->SetLineWidth(2);
      pppL1seedJet16->Draw("PSAME");
      pppL1seedJet20->SetMarkerColor(4);
      pppL1seedJet20->SetLineColor(4);
      pppL1seedJet20->SetLineWidth(2);
      pppL1seedJet20->Draw("PSAME");
      pppL1seedJet24->SetMarkerColor(5);
      pppL1seedJet24->SetLineColor(5);
      pppL1seedJet24->SetLineWidth(2);
      pppL1seedJet24->Draw("PSAME");
      pppL1seedJet28->SetMarkerColor(6);
      pppL1seedJet28->SetLineColor(6);
      pppL1seedJet28->SetLineWidth(2);
      pppL1seedJet28->Draw("PSAME");
      pppL1seedJet32->SetMarkerColor(7);
      pppL1seedJet32->SetLineColor(7);
      pppL1seedJet32->SetLineWidth(2);
      pppL1seedJet32->Draw("PSAME");
      pppL1seedJet36->SetMarkerColor(8);
      pppL1seedJet36->SetLineColor(8);
      pppL1seedJet36->SetLineWidth(2);
      pppL1seedJet36->Draw("PSAME");
      pppL1seedJet40->SetMarkerColor(9);
      pppL1seedJet40->SetLineColor(9);
      pppL1seedJet40->SetLineWidth(2);
      pppL1seedJet40->Draw("PSAME");
      pppL1seedJet44->SetMarkerColor(kOrange+7);
      pppL1seedJet44->SetLineColor(kOrange+7);
      pppL1seedJet44->SetLineWidth(2);
      pppL1seedJet44->Draw("PSAME");
      pppL1seedJet48->SetMarkerColor(11);
      pppL1seedJet48->SetLineColor(11);
      pppL1seedJet48->SetLineWidth(2);
      pppL1seedJet48->Draw("PSAME");
      pppL1seedJet52->SetMarkerColor(38);
      pppL1seedJet52->SetLineColor(38);
      pppL1seedJet52->SetLineWidth(2);
      pppL1seedJet52->Draw("PSAME");
      pppL1seedJet60->SetMarkerColor(46);
      pppL1seedJet60->SetLineColor(46);
      pppL1seedJet60->SetLineWidth(2);
      pppL1seedJet60->Draw("PSAME");
      pppL1seedJet68->SetMarkerColor(28);
      pppL1seedJet68->SetLineColor(28);
      pppL1seedJet68->SetLineWidth(2);
      pppL1seedJet68->Draw("PSAME");
      cppL1seed->SaveAs(Form("triggerturnonPlots/pthat%.0f/L1seed/pp/c%s_L1seed.pdf",pthat,triggerpass.Data()));
    }
}







//back up

/*
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Dtrk1Algo","algo","track Algorithm",16,2,18,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","DsvpvDistance","3Dd0","3D decay length",12,0,6,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","DsvpvDistance","3Dd0","3D decay length",12,0,6,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","DsvpvDistance","3Dd0","3D decay length",12,0,6,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","DsvpvDistance","3Dd0","3D decay length",12,0,6,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","DsvpvDistance","3Dd0","3D decay length",12,0,6,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","DsvpvDistance","3Dd0","3D decay length",12,0,6,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","DsvpvDisErr","3Dd0err","3D decay length err",10,0,0.1,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","DsvpvDisErr","3Dd0err","3D decay length err",10,0,0.1,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","DsvpvDisErr","3Dd0err","3D decay length err",10,0,0.1,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","DsvpvDisErr","3Dd0err","3D decay length err",10,0,0.1,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","DsvpvDisErr","3Dd0err","3D decay length err",10,0,0.1,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","DsvpvDisErr","3Dd0err","3D decay length err",10,0,0.1,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","DsvpvDistance_2D/DsvpvDisErr_2D","ffls2d","2D decay length sig",10,0,20,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","DsvpvDistance_2D/DsvpvDisErr_2D","ffls2d","2D decay length sig",10,0,20,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","DsvpvDistance_2D/DsvpvDisErr_2D","ffls2d","2D decay length sig",10,0,20,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","DsvpvDistance_2D/DsvpvDisErr_2D","ffls2d","2D decay length sig",10,0,20,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","DsvpvDistance_2D/DsvpvDisErr_2D","ffls2d","2D decay length sig",10,0,20,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","DsvpvDistance_2D/DsvpvDisErr_2D","ffls2d","2D decay length sig",10,0,20,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","DsvpvDistance_2D","2Dd0","2D decay length",12,0,6,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","DsvpvDistance_2D","2Dd0","2D decay length",12,0,6,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","DsvpvDistance_2D","2Dd0","2D decay length",12,0,6,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","DsvpvDistance_2D","2Dd0","2D decay length",12,0,6,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","DsvpvDistance_2D","2Dd0","2D decay length",12,0,6,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","DsvpvDistance_2D","2Dd0","2D decay length",12,0,6,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","DsvpvDisErr_2D","2Dd0err","2D decay length err",10,0,0.1,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","DsvpvDisErr_2D","2Dd0err","2D decay length err",10,0,0.1,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","DsvpvDisErr_2D","2Dd0err","2D decay length err",10,0,0.1,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","DsvpvDisErr_2D","2Dd0err","2D decay length err",10,0,0.1,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","DsvpvDisErr_2D","2Dd0err","2D decay length err",10,0,0.1,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","DsvpvDisErr_2D","2Dd0err","2D decay length err",10,0,0.1,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Dlxy","lxy","Lxy",8,0,4,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dlxy","lxy","Lxy",8,0,4,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Dlxy","lxy","Lxy",8,0,4,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Dlxy","lxy","Lxy",8,0,4,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Dlxy","lxy","Lxy",8,0,4,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Dlxy","lxy","Lxy",8,0,4,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Deta","eta","#eta",12,-3,3,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Dphi","phi","#phi",16,-4,4,"&&Dpt>60.");
  
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt10_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>10.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt20_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt30_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>30.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt40_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt50_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>50.");
  plotTurnOn(root,"HLT_DmesonPPTrackingGlobal_Dpt60_v1","Dtrk1Dxy","trkdxy","track Dxy",10,0,0.1,"&&Dpt>60.");
*/      


/*
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","hiBin/2.","cent","Centrality",10,0,100,Form("&&Dpt>20.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","hiBin/2.","cent","Centrality",10,0,100,Form("&&Dpt>40.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","hiBin/2.","cent","Centrality",10,0,100,Form("&&Dpt>60.&&%s&&%s",decaylength.Data(),cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,Form("&&Dpt>20.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,Form("&&Dpt>40.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length sig",10,0,20,Form("&&Dpt>60.&&%s",cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Ddxyz/DdxyzErr","ffls3dapp","~ 3D decay length sig",10,0,20,Form("&&Dpt>20.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Ddxyz/DdxyzErr","ffls3dapp","~ 3D decay length sig",10,0,20,Form("&&Dpt>40.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Ddxyz/DdxyzErr","ffls3dapp","~ 3D decay length sig",10,0,20,Form("&&Dpt>60.&&%s",cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dd0/Dd0Err","ffls2d","~ 2D decay length sig",10,0,20,Form("&&Dpt>20.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dd0/Dd0Err","ffls2d","~ 2D decay length sig",10,0,20,Form("&&Dpt>40.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dd0/Dd0Err","ffls2d","~ 2D decay length sig",10,0,20,Form("&&Dpt>60.&&%s",cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","DsvpvDistance","3Dd0","3D decay length",10,0,10,Form("&&Dpt>20.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","DsvpvDistance","3Dd0","3D decay length",10,0,10,Form("&&Dpt>40.&&%s",cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","DsvpvDistance","3Dd0","3D decay length",10,0,10,Form("&&Dpt>60.&&%s",cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","TMath::Cos(Dalpha)","cosalpha","cos#alpha",10,0.9,1,Form("&&Dpt>20.&&%s",decaylength.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","TMath::Cos(Dalpha)","cosalpha","cos#alpha",10,0.9,1,Form("&&Dpt>40.&&%s",decaylength.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","TMath::Cos(Dalpha)","cosalpha","cos#alpha",10,0.9,1,Form("&&Dpt>60.&&%s",decaylength.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk1Pt","maxtrkpt","Higher track p_{T} (GeV/c)",10,8,80,Form("&&Dpt>20.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk1Pt","maxtrkpt","Higher track p_{T} (GeV/c)",10,8,80,Form("&&Dpt>40.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk1Pt","maxtrkpt","Higher track p_{T} (GeV/c)",10,8,80,Form("&&Dpt>60.&&%s&&%s",decaylength.Data(),cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk2Pt","mintrkpt","Lower track p_{T} (GeV/c)",10,8,80,Form("&&Dpt>20.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk2Pt","mintrkpt","Lower track p_{T} (GeV/c)",10,8,80,Form("&&Dpt>40.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk2Pt","mintrkpt","Lower track p_{T} (GeV/c)",10,8,80,Form("&&Dpt>60.&&%s&&%s",decaylength.Data(),cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk1Eta","maxtrketa","Higher-p_{T} track #eta",6,-3,3,Form("&&Dpt>20.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk1Eta","maxtrketa","Higher-p_{T} track #eta",6,-3,3,Form("&&Dpt>40.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk1Eta","maxtrketa","Higher-p_{T} track #eta",6,-3,3,Form("&&Dpt>60.&&%s&&%s",decaylength.Data(),cosalpha.Data()));

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk2Eta","mintrketa","Lower-p_{T} track #eta",6,-3,3,Form("&&Dpt>20.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk2Eta","mintrketa","Lower-p_{T} track #eta",6,-3,3,Form("&&Dpt>40.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk2Eta","mintrketa","Lower-p_{T} track #eta",6,-3,3,Form("&&Dpt>60.&&%s&&%s",decaylength.Data(),cosalpha.Data()));
*/
