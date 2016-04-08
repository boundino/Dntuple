#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void CombinePbPbYield(TString fileMB="ROOTfiles/CrossSectionFONLLPbPbMB.root", TString file="ROOTfiles/CrossSectionFONLLPbPb.root")
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReferenceMB = (TGraphAsymmErrors*)filePPMB->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStatMB = (TH1D*)filePPMB->Get("hPtSigma");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)filePP->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePP->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStat = (TH1D*)filePP->Get("hPtSigma");

  TCanvas* cSigma = new TCanvas("cSigma","",600,600);
  gPad->SetLogy();
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigma->SetFillColor(0);
  cSigma->SetBorderMode(0);
  cSigma->SetBorderSize(2);
  cSigma->SetLeftMargin(0.1451613);
  cSigma->SetRightMargin(0.05443548);
  cSigma->SetTopMargin(0.08474576);
  cSigma->SetBottomMargin(0.1165254);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetLogx();
  cSigma->cd();

  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e4,1.e15);  
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptySigma->GetXaxis()->SetTitleOffset(1.2);
  hemptySigma->GetYaxis()->SetTitleOffset(1.3);
  hemptySigma->GetXaxis()->SetTitleSize(0.045);
  hemptySigma->GetYaxis()->SetTitleSize(0.045);
  hemptySigma->GetXaxis()->SetTitleFont(42);
  hemptySigma->GetYaxis()->SetTitleFont(42);
  hemptySigma->GetXaxis()->SetLabelFont(42);
  hemptySigma->GetYaxis()->SetLabelFont(42);
  hemptySigma->GetXaxis()->SetLabelSize(0.04);
  hemptySigma->GetYaxis()->SetLabelSize(0.04);  
  hemptySigma->SetMaximum(2);
  hemptySigma->SetMinimum(0.);
  hemptySigma->Draw();

  hSigmaPPStatMB->SetLineColor(1);
  hSigmaPPStatMB->SetLineWidth(2);
  hSigmaPPStatMB->Draw("epsame"); 

  hSigmaPPStat->SetLineColor(4);
  hSigmaPPStat->SetLineWidth(2);
  hSigmaPPStat->Draw("epsame"); 

  gaeCrossSystMB->SetFillColor(1);
  gaeCrossSystMB->SetFillStyle(0); 
  gaeCrossSystMB->SetLineWidth(2);
  gaeCrossSystMB->SetLineColor(1);
  gaeCrossSystMB->Draw("5same");  

  gaeCrossSyst->SetFillColor(4);
  gaeCrossSyst->SetFillStyle(0); 
  gaeCrossSyst->SetLineWidth(2);
  gaeCrossSyst->SetLineColor(4);
  gaeCrossSyst->Draw("5same");  

  TLegend *legendSigma=new TLegend(0.5100806,0.5868644,0.8084677,0.7605932,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
  
  TLegendEntry *ent_SigmaPPMB=legendSigma->AddEntry(hSigmaPPStatMB,"PbPb MB","pf");
  ent_SigmaPPMB->SetTextFont(42);
  ent_SigmaPPMB->SetLineColor(2);
  ent_SigmaPPMB->SetMarkerColor(2);
  
  TLegendEntry *ent_SigmaPP=legendSigma->AddEntry(hSigmaPPStat,"PbPb triggered","pf");
  ent_SigmaPP->SetTextFont(42);
  ent_SigmaPP->SetLineColor(1);
  ent_SigmaPP->SetMarkerColor(1);
  legendSigma->Draw();
      
  TLatex * tlatex1=new TLatex(0.1612903,0.8625793,"CMS Preliminary     PbPb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();
  cSigma->SaveAs("CrossSectionComparisonPbPb.pdf");

  }

int main(int argc, char *argv[])
{
  if((argc != 3))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc ==3)
    CombinePbPbYield(argv[1], argv[2]);
  return 0;
}

