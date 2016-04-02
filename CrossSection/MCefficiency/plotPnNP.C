using namespace std;
#include "uti.h"

void plotPnNP(TString collision="PbPb",TString outputfileP="test.root",TString outputfileNP="test.root")
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
  hEffAccNP->SetMinimum(0.);
  hEffAccNP->SetMaximum(1.5);
  hEffNP->SetMinimum(0.);
  hEffNP->SetMaximum(1.5);

  hEffAccP->SetLineColor(2);
  hEffAccP->SetMarkerColor(2);
  hEffP->SetLineColor(2);
  hEffP->SetMarkerColor(2);
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

  TCanvas* cEffAcc = new TCanvas("cEffAcc","",600,600);
  TLegend* legEffAcc = new TLegend(0.55,0.73,0.90,0.84);
  legEffAcc->SetBorderSize(0);
  legEffAcc->SetFillStyle(0);
  legEffAcc->AddEntry(hEffAccP,"Prompt","pl");
  legEffAcc->AddEntry(hEffAccNP,"Non-prompt","pl");
  hEffAccP->Draw();
  hEffAccNP->Draw("same");
  texCms->Draw();
  texCol->Draw();
  legEffAcc->Draw("same");
  cEffAcc->SaveAs(Form("canvasEffAcc_PnNP_%s.pdf",collision.Data()));

  TCanvas* cEff = new TCanvas("cEff","",600,600);
  TLegend* legEff = new TLegend(0.55,0.73,0.90,0.84);
  legEff->SetBorderSize(0);
  legEff->SetFillStyle(0);
  legEff->AddEntry(hEffP,"Prompt","pl");
  legEff->AddEntry(hEffNP,"Non-prompt","pl");
  hEffP->Draw();
  hEffNP->Draw("same");
  texCms->Draw();
  texCol->Draw();
  legEff->Draw("same");
  cEff->SaveAs(Form("canvasEff_PnNP_%s.pdf",collision.Data()));

}

int main(int argc, char* argv[])
{
  if(argc==4)
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
