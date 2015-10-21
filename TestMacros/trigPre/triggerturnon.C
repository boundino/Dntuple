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

TString prefilter = "(Dgen==23333||Dgen==23344)&&Dmaxpt&&Dtrk1Pt>8.&&Dtrk2Pt>8.&&(DsvpvDistance/DsvpvDisErr)>2.5&&TMath::Cos(Dalpha)>0.95";
Float_t pthat = 35;
void triggerturnon(TString infname=Form("/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151020_DfinderMC_20151020_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root",pthat,pthat))
{
  void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  void plotTurnOnNL1seed(TTree* inttree, TString triggerpass, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dpt","pt","p_{T} (GeV/c)",8,0,80);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dpt","pt","p_{T} (GeV/c)",8,0,80);
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dpt","pt","p_{T} (GeV/c)",8,0,80);

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dy","y","y",10,-4,4,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dy","y","y",10,-4,4,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dy","y","y",10,-4,4,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Deta","eta","#eta",10,-4,4,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Deta","eta","#eta",10,-4,4,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Deta","eta","#eta",10,-4,4,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dphi","phi","#phi",10,-4,4,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dphi","phi","#phi",10,-4,4,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dphi","phi","#phi",10,-4,4,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk1Pt","maxtrkpt","Higher track p_{T} (GeV/c)",10,8,80,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk1Pt","maxtrkpt","Higher track p_{T} (GeV/c)",10,8,80,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk1Pt","maxtrkpt","Higher track p_{T} (GeV/c)",10,8,80,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk2Pt","mintrkpt","Lower track p_{T} (GeV/c)",10,8,80,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk2Pt","mintrkpt","Lower track p_{T} (GeV/c)",10,8,80,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk2Pt","mintrkpt","Lower track p_{T} (GeV/c)",10,8,80,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk1Eta","maxtrketa","Higher-p_{T} track #eta",10,-3,3,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk1Eta","maxtrketa","Higher-p_{T} track #eta",10,-3,3,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk1Eta","maxtrketa","Higher-p_{T} track #eta",10,-3,3,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dtrk2Eta","mintrketa","Lower-p_{T} track #eta",10,-3,3,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dtrk2Eta","mintrketa","Lower-p_{T} track #eta",10,-3,3,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dtrk2Eta","mintrketa","Lower-p_{T} track #eta",10,-3,3,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length significance",10,0,20,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length significance",10,0,20,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","DsvpvDistance/DsvpvDisErr","ffls3d","3D decay length significance",10,0,20,"&&Dpt>60.");

  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dd0/Dd0Err","ffls2d","2D decay length significance",10,0,20,"&&Dpt>20.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dd0/Dd0Err","ffls2d","2D decay length significance",10,0,20,"&&Dpt>40.");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dd0/Dd0Err","ffls2d","2D decay length significance",10,0,20,"&&Dpt>60.");
  
  /*
  plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1",8,0,80);
  plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1",8,0,80);
  plotTurnOnNL1seed(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1",8,0,80);
  */
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
  if(triggerpass=="HLT_DmesonTrackingGlobalPt8_Dpt20_v1")
    {
      TCanvas* chinclusive = new TCanvas(Form("chinclusive_%s",varname.Data()),"",500,500);
      hinclusive->Draw();
      hinclusive->SetStats(0);
      tex->Draw();
      chinclusive->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/chinclusive_%s.pdf",pthat,varname.Data()));
    }
  TH2D* hempty = new TH2D(Form("hempty_%s_%s",triggerpass.Data(),varname.Data()),Form(";Matched reco D^{0} %s;Pass efficiency (MB seed)",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  TH1D* hMBseed = new TH1D(Form("h%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_MBseed_%s",triggerpass.Data(),varname.Data()),variable,Form("%s%s&&%s",prefilter.Data(),addcut.Data(),triggerpass.Data()));
  hMBseed->Sumw2();
  TEfficiency* pEffMBseed = new TEfficiency(*hMBseed,*hinclusive);
  //pEffMBseed->SetTitle(Form(";Matched reco D^{0} %s;Pass efficiency (MB seed)",varlatex.Data()));
  TCanvas* cMBseed = new TCanvas(Form("c%s_MBseed_%s",triggerpass.Data(),varname.Data()),"",500,500);
  hempty->Draw();
  pEffMBseed->Draw("PSAME");
  tex->Draw();
  cMBseed->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/c%s_MBseed_%s.pdf",pthat,triggerpass.Data(),varname.Data()));
}

void plotTurnOnNL1seed(TTree* inttree, TString triggerpass, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX)
{
  TH1D* hMBseed = new TH1D(Form("h%s_MBseed",triggerpass.Data()),";Matched reco D^{0} p_{T} (GeV/c);Pass efficiency (MB seed)",BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_MBseed",triggerpass.Data()),"Dpt",Form("%s&&%s",prefilter.Data(),triggerpass.Data()));
  hMBseed->Sumw2();

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
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
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
  cL1seed->SaveAs(Form("triggerturnonPlots/pthat%.0f/MBseed/c%s_L1seed.pdf",pthat,triggerpass.Data()));
}
