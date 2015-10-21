#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMath.h>
#include <TEfficiency.h>

TString prefilter = "Dgen==23333&&Dtrk1Pt>8.&&Dtrk2Pt>8.";
Double_t BIN_MIN = 0;
Double_t BIN_MAX = 80;
Int_t BIN_NUM = 50;
Float_t pthat = 35;
//void triggerturnon(TString infname="/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151016_DinderMC_20151015_EvtMatching_Pyquen_D0tokaonpion_D0pt15p0_Pthat15_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151010.root")
void variables(TString infname=Form("/mnt/hadoop/cms/store/user/jwang/Dmeson/5p02TeV/ntD_20151018_DfinderMC_20151017_EvtMatching_Pyquen_D0tokaonpion_D0pt%.0fp0_Pthat%.0f_TuneZ2_Unquenched_5020GeV_GENSIM_75x_v2_20151016.root",pthat,pthat))
{
  void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex);
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","TMath::Cos(Dalpha)","cosalpha","cos#alpha");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","DsvpvDistance/DsvpvDisErr","ffls3d","decay length significance");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt20_v1","Dchi2cl","vtxprob","vertex prob");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","TMath::Cos(Dalpha)","cosalpha","cos#alpha");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","DsvpvDistance/DsvpvDisErr","ffls3d","decay length significance");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt40_v1","Dchi2cl","vtxprob","vertex prob");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","TMath::Cos(Dalpha)","cosalpha","cos#alpha");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","DsvpvDistance/DsvpvDisErr","ffls3d","decay length significance");
  plotTurnOn(root,"HLT_DmesonTrackingGlobalPt8_Dpt60_v1","Dchi2cl","vtxprob","vertex prob");

}

void plotTurnOn(TTree* inttree, TString triggerpass, TString variable, TString varname, TString varlatex)
{
  if(varname=="vtxprob")
    {
      BIN_MIN = 0;
      BIN_MAX = 1;
    }
  else if(varname=="ffls3d")
    {
      BIN_MIN = 0;
      BIN_MAX = 50;
    }
  else if(varname=="cosalpha")
    {
      BIN_MIN = 0.9;
      BIN_MAX = 1;
    }
  TH1D* hAll = new TH1D(Form("h%s_%s_All",triggerpass.Data(),varname.Data()),Form(";%s;Probability",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_%s_All",triggerpass.Data(),varname.Data()),variable,prefilter);
  TH1D* hMBseed = new TH1D(Form("h%s_%s_MBseed",triggerpass.Data(),varname.Data()),Form(";%s;Probability",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX);
  inttree->Project(Form("h%s_%s_MBseed",triggerpass.Data(),varname.Data()),variable,Form("%s&&%s",prefilter.Data(),triggerpass.Data()));
  //cout<<hAll->Integral()<<endl;
  hAll->Scale(1./hAll->Integral());
  hMBseed->Scale(1./hMBseed->Integral());
  hAll->SetStats(0);
  hMBseed->SetStats(0);
  hAll->SetMaximum(hMBseed->GetMaximum()*1.3);
  hAll->SetLineWidth(2);
  hAll->SetLineColor(kBlue-7);
  hAll->SetFillColor(kBlue-7);
  hAll->SetFillStyle(3001);
  hMBseed->SetLineWidth(2);
  hMBseed->SetLineColor(kRed);
  hMBseed->SetFillColor(kRed);
  hMBseed->SetFillStyle(3004);
  TCanvas* c = new TCanvas(Form("c%s_%s",triggerpass.Data(),varname.Data()),"",500,500);
  hAll->Draw();
  hMBseed->Draw("same");
  TLatex* tex = new TLatex(0.18,0.96,triggerpass);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  TLegend* leg = new TLegend(0.60,0.82,0.92,0.93);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(hAll,"all","f");
  leg->AddEntry(hMBseed,"pass trigger","f");
  leg->Draw();
  c->SaveAs(Form("triggerturnonPlots/pthat%.0f/c%s_%s.pdf",pthat,triggerpass.Data(),varname.Data()));

}
