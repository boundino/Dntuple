#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"

void CombineCrossSections(TString fileMB="ROOTfiles/CrossSectionFONLLPPMB.root", TString file="ROOTfiles/CrossSectionFONLLPP.root", Int_t isPbPb=1, Float_t centMin=0., Float_t centMax=100., Int_t isMerged=1)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString texPbPb = "PbPb";
  if(isPbPb==0) texPbPb = "PP";

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

  TCanvas* cSigma = new TCanvas("cSigma","",600,750);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigma->SetFillColor(0);
  cSigma->SetBorderMode(0);
  cSigma->SetBorderSize(2);
  cSigma->SetLeftMargin(0.12);//0.1451613
  cSigma->SetRightMargin(0.03);//0.05443548
  cSigma->SetTopMargin(0.07);//0.08474576
  cSigma->SetBottomMargin(0.15);//0.1165254
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetLogx();
  cSigma->cd();
  TPad* pSigma = new TPad("pSigma","",0,0.25,1,1);
  pSigma->SetFillColor(0);
  pSigma->SetBorderMode(0);
  pSigma->SetBorderSize(2);
  pSigma->SetLeftMargin(0.12);//0.1451613
  pSigma->SetRightMargin(0.03);//0.05443548
  pSigma->SetTopMargin(0.07);//0.08474576
  pSigma->SetBottomMargin(0);
  pSigma->SetLogy();
  pSigma->SetLogx();
  pSigma->Draw();
  pSigma->cd();

  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1.1,1.e10);  
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  if(isPbPb==1) hemptySigma->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitleOffset(1.);
  hemptySigma->GetYaxis()->SetTitleOffset(1.24);//1.3
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

  gaeBplusReferenceMB->SetFillColor(5);//2
  gaeBplusReferenceMB->SetFillStyle(1001);//3001 
  gaeBplusReferenceMB->SetLineWidth(1);//3
  gaeBplusReferenceMB->SetLineColor(4);//2
  gaeBplusReferenceMB->Draw("5same");
  gaeBplusReference->SetFillColor(5);//2
  gaeBplusReference->SetFillStyle(1001);//3001 
  gaeBplusReference->SetLineWidth(1);//3
  gaeBplusReference->SetLineColor(4);//2
  gaeBplusReference->Draw("5same");

  hSigmaPPStatMB->SetLineWidth(2);
  hSigmaPPStatMB->SetMarkerSize(1);//4
  hSigmaPPStatMB->SetMarkerStyle(20);
  if(isMerged==1)
    {
      hSigmaPPStatMB->SetLineColor(1);//kGreen+4
      hSigmaPPStatMB->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      hSigmaPPStatMB->SetLineColor(kTeal+4);//kGreen+4
      hSigmaPPStatMB->SetMarkerColor(kTeal+4);//kGreen+4
    }
  hSigmaPPStatMB->Draw("epsame"); 

  hSigmaPPStat->SetLineWidth(2);
  hSigmaPPStat->SetMarkerSize(1);//4
  hSigmaPPStat->SetMarkerStyle(20);
  if(isMerged==1)
    {
      hSigmaPPStat->SetLineColor(1);//kGreen+4
      hSigmaPPStat->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      hSigmaPPStat->SetLineColor(kAzure+1);//4
      hSigmaPPStat->SetMarkerColor(kAzure+1);//4
    }
  hSigmaPPStat->Draw("epsame"); 

  gaeCrossSystMB->SetFillColor(1);
  gaeCrossSystMB->SetFillStyle(0); 
  gaeCrossSystMB->SetLineWidth(2);
  if(isMerged==1) gaeCrossSystMB->SetLineColor(1);//kGreen+4
  else gaeCrossSystMB->SetLineColor(kTeal+4);
  gaeCrossSystMB->Draw("5same");  

  gaeCrossSyst->SetFillColor(1);
  gaeCrossSyst->SetFillStyle(0); 
  gaeCrossSyst->SetLineWidth(2);
  if(isMerged==1) gaeCrossSyst->SetLineColor(1);//kGreen+4
  else gaeCrossSyst->SetLineColor(kAzure+1);//4
  gaeCrossSyst->Draw("5same");  

  TString texper="%";
  TLatex* texCent = new TLatex(0.55,0.85,Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextFont(42);
  texCent->SetTextSize(0.045);
  if(isPbPb==1) texCent->Draw();

  TLatex* texY = new TLatex(0.55,0.79,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  texY->Draw();

  Float_t systnorm;
  if(isPbPb==1) systnorm = normalizationUncertaintyForPbPb(centMin,centMax);
  else systnorm = normalizationUncertaintyForPP();
  TLatex* texSystnorm = new TLatex(0.55,0.61,Form("Global uncert. %.1f%s",systnorm,texper.Data()));
  texSystnorm->SetNDC();
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.045);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();

  TLegend *legendSigma=new TLegend(0.54,0.66,0.87,0.77,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

  if(isMerged==0)
    {   
      TLegendEntry *ent_SigmaPPMB = legendSigma->AddEntry(hSigmaPPStatMB,"MB","pf");
      ent_SigmaPPMB->SetTextFont(42);
      ent_SigmaPPMB->SetLineColor(2);
      ent_SigmaPPMB->SetMarkerColor(2);
      
      TLegendEntry *ent_SigmaPP = legendSigma->AddEntry(hSigmaPPStat,"triggered","pf");
      ent_SigmaPP->SetTextFont(42);
      ent_SigmaPP->SetLineColor(1);
      ent_SigmaPP->SetMarkerColor(1);
    }
  else
    {
      TLegendEntry *ent_SigmaPPMB = legendSigma->AddEntry(hSigmaPPStatMB,"data","pf");
      ent_SigmaPPMB->SetTextFont(42);
      ent_SigmaPPMB->SetLineColor(2);
      ent_SigmaPPMB->SetMarkerColor(2);
    }
  TLegendEntry *ent_SigmaFONLL = legendSigma->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  ent_SigmaFONLL->SetTextFont(42);
  ent_SigmaFONLL->SetLineColor(5);
  ent_SigmaFONLL->SetMarkerColor(1);
  legendSigma->Draw("same");
   
  TLatex * tlatex1;
  if(isPbPb==0) tlatex1 = new TLatex(0.95,0.96,"25.8 pb^{-1} (5.02 TeV pp)");
  else tlatex1 = new TLatex(0.95,0.96,"404 #mub^{-1} (5.02 TeV PbPb)");
  tlatex1->SetNDC();
  tlatex1->SetTextAlign(32);
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();

  TLatex* texcms = new TLatex(0.15,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.15,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  cSigma->cd();
  TPad* pRatio = new TPad("pRatio","",0,0,1,0.25);
  pRatio->SetLeftMargin(0.12);//0.1451613
  pRatio->SetRightMargin(0.03);//0.05443548
  pRatio->SetTopMargin(0);
  pRatio->SetBottomMargin(0.33);//0.25
  pRatio->SetLogx();
  pRatio->Draw();
  pRatio->cd();

  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,0.,110.,10.,0.,3.2);//50,0.,110.,10.,0.,4
  hemptyRatio->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Data / FONLL");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.05);//0.9
  hemptyRatio->GetYaxis()->SetTitleOffset(0.90);//0.5
  hemptyRatio->GetXaxis()->SetTitleSize(0.15);//0.12
  hemptyRatio->GetYaxis()->SetTitleSize(0.12);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.1);
  hemptyRatio->GetYaxis()->SetLabelSize(0.1);  
  hemptyRatio->Draw();

  TLine* l = new TLine(2.2,1,110,1);//10,1,105,1
  l->SetLineWidth(1);
  l->SetLineStyle(2);

  gaeRatioCrossFONLLunityMB->SetFillColor(5);
  gaeRatioCrossFONLLunityMB->SetFillStyle(1001);
  gaeRatioCrossFONLLunityMB->SetLineWidth(1);
  gaeRatioCrossFONLLunityMB->SetLineColor(4);
  gaeRatioCrossFONLLunityMB->Draw("5same");

  gaeRatioCrossFONLLstatMB->SetMarkerSize(1);
  gaeRatioCrossFONLLstatMB->SetLineWidth(2);
  if(isMerged==1)
    {
      gaeRatioCrossFONLLstatMB->SetLineColor(1);//kGreen+4
      gaeRatioCrossFONLLstatMB->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      gaeRatioCrossFONLLstatMB->SetLineColor(kTeal+4);//kGreen+4
      gaeRatioCrossFONLLstatMB->SetMarkerColor(kTeal+4);//kGreen+4
    }
  gaeRatioCrossFONLLstatMB->Draw("epsame");

  gaeRatioCrossFONLLsystMB->SetLineWidth(3);
  if(isMerged==1) gaeRatioCrossFONLLsystMB->SetLineColor(1);//kGreen+4
  else gaeRatioCrossFONLLsystMB->SetLineColor(kTeal+4);
  gaeRatioCrossFONLLsystMB->Draw("5same");

  gaeRatioCrossFONLLunity->SetFillColor(5);
  gaeRatioCrossFONLLunity->SetFillStyle(1001);
  gaeRatioCrossFONLLunity->SetLineWidth(1);
  gaeRatioCrossFONLLunity->SetLineColor(4);
  gaeRatioCrossFONLLunity->Draw("5same");

  gaeRatioCrossFONLLstat->SetMarkerSize(1);
  gaeRatioCrossFONLLstat->SetLineWidth(2);
  if(isMerged==1)
    {
      gaeRatioCrossFONLLstat->SetLineColor(1);//kGreen+4
      gaeRatioCrossFONLLstat->SetMarkerColor(1);//kGreen+4
    }
  else
    {
      gaeRatioCrossFONLLstat->SetLineColor(kAzure+1);//4
      gaeRatioCrossFONLLstat->SetMarkerColor(kAzure+1);//4
    }
  gaeRatioCrossFONLLstat->Draw("epsame");

  gaeRatioCrossFONLLsyst->SetLineWidth(3);
  if(isMerged==1) gaeRatioCrossFONLLsyst->SetLineColor(1);//kGreen+4
  else gaeRatioCrossFONLLsyst->SetLineColor(kAzure+1);//4
  gaeRatioCrossFONLLsyst->Draw("5same");

  l->Draw("same");
  if(isPbPb==1) cSigma->SaveAs(Form("plotCrossSection/CrossSectionComparison_%s_%.0f_%.0f.pdf",texPbPb.Data(),centMin,centMax));
  else cSigma->SaveAs(Form("plotCrossSection/CrossSectionComparison_%s.pdf",texPbPb.Data()));
}


int main(int argc, char *argv[])
{
  if(argc==7)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
      return 0;
    }
  else if(argc==6)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else if(argc==4)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}

