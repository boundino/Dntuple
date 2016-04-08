using namespace std;
#include "uti.h"

void plotPnNP(TString collision="PbPb",TString outputfileP="test.root",TString outputfileNP="test.root",Float_t centMin=0.,Float_t centMax=100.)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.8);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1.8,"Y");

  Bool_t isPbPb = true;
  if(collision=="PP"||collision=="PPMB") isPbPb = false;

  TFile* infP = new TFile(Form("%s",outputfileP.Data()));
  TFile* infNP = new TFile(Form("%s",outputfileNP.Data()));

  TH1D* hEffAccP = (TH1D*)infP->Get("hEffAcc");    hEffAccP->SetName("hEffAccP");
  TH1D* hEffP = (TH1D*)infP->Get("hEff");          hEffP->SetName("hEffP");
  TH1D* hEffAccNP = (TH1D*)infNP->Get("hEffAcc");  hEffAccNP->SetName("hEffAccNP");
  TH1D* hEffNP = (TH1D*)infNP->Get("hEff");        hEffNP->SetName("hEffNP");

  hEffAccP->SetTitle(";p_{T} (GeV/c);#alpha");
  hEffAccNP->SetTitle(";p_{T} (GeV/c);#alpha");
  hEffP->SetTitle(";p_{T} (GeV/c);#alpha x #epsilon_{reco} x #epsilon_{sel}");
  hEffNP->SetTitle(";p_{T} (GeV/c);#alpha x #epsilon_{reco} x #epsilon_{sel}");

  hEffAccP->SetMinimum(0.);
  hEffAccP->SetMaximum(1.5);
  hEffP->SetMinimum(0.);
  hEffP->SetMaximum(1.5);
  hEffAccP->SetLineColor(2);
  hEffAccP->SetMarkerColor(2);
  hEffAccP->GetXaxis()->SetTitleOffset(0.95);//0.9
  hEffAccP->GetYaxis()->SetTitleOffset(1.15);//1.
  hEffAccP->GetXaxis()->SetTitleSize(0.055);//0.045
  hEffAccP->GetYaxis()->SetTitleSize(0.055);//0.045
  hEffAccP->GetXaxis()->SetTitleFont(42);
  hEffAccP->GetYaxis()->SetTitleFont(42);
  hEffP->SetLineColor(2);
  hEffP->SetMarkerColor(2);
  hEffP->GetXaxis()->SetTitleOffset(0.95);//0.9
  hEffP->GetYaxis()->SetTitleOffset(1.15);//1.
  hEffP->GetXaxis()->SetTitleSize(0.055);//0.045
  hEffP->GetYaxis()->SetTitleSize(0.055);//0.045
  hEffP->GetXaxis()->SetTitleFont(42);
  hEffP->GetYaxis()->SetTitleFont(42);
  hEffAccNP->SetLineColor(4);
  hEffAccNP->SetMarkerColor(4);
  hEffNP->SetLineColor(4);
  hEffNP->SetMarkerColor(4);

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collision.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);

  TString texper = "%";
  TLatex* texCent = new TLatex(0.57,0.84, Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextAlign(12);
  texCent->SetTextSize(0.045);
  texCent->SetTextFont(42);

  TCanvas* cEffAcc = new TCanvas("cEffAcc","",600,600);
  TLegend* legEffAcc = new TLegend(0.55,0.70,0.90,0.81);
  legEffAcc->SetBorderSize(0);
  legEffAcc->SetFillStyle(0);
  legEffAcc->AddEntry(hEffAccP,"Prompt","pl");
  legEffAcc->AddEntry(hEffAccNP,"Non-prompt","pl");
  hEffAccP->Draw();
  hEffAccNP->Draw("same");
  texCms->Draw();
  texCol->Draw();
  if(isPbPb) texCent->Draw();
  legEffAcc->Draw("same");
  if(!isPbPb) cEffAcc->SaveAs(Form("plotEff/canvasEffAcc_PnNP_%s.pdf",collision.Data()));
  else cEffAcc->SaveAs(Form("plotEff/canvasEffAcc_PnNP_%s_%.0f_%.0f.pdf",collision.Data(),centMin,centMax));

  TCanvas* cEff = new TCanvas("cEff","",600,600);
  TLegend* legEff = new TLegend(0.55,0.70,0.90,0.81);
  legEff->SetBorderSize(0);
  legEff->SetFillStyle(0);
  legEff->AddEntry(hEffP,"Prompt","pl");
  legEff->AddEntry(hEffNP,"Non-prompt","pl");
  hEffP->Draw();
  hEffNP->Draw("same");
  texCms->Draw();
  texCol->Draw();
  if(isPbPb) texCent->Draw();
  legEff->Draw("same");
  if(!isPbPb) cEff->SaveAs(Form("plotEff/canvasEff_PnNP_%s.pdf",collision.Data()));
  else cEff->SaveAs(Form("plotEff/canvasEff_PnNP_%s_%.0f_%.0f.pdf",collision.Data(),centMin,centMax));
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      plotPnNP(argv[1],argv[2],argv[3],atof(argv[4]),atof(argv[5]));
      return 1;
    }
  else if(argc==4)
    {
      plotPnNP(argv[1],argv[2],argv[3]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
