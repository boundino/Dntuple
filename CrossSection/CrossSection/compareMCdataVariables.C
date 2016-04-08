#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include "uti.h"
#include "parameters.h"

void compareMCdataVariables(TString promptfile="MCCutVariablePromptPt.root",TString nonpromptfile="MCCutVariableNonPromptPt.root",TString datafile="DataCutVariablePt.root",TString cutvariable="Dpt",TString label="Dpt", double limitlow=0, double limitup=100){

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);


  TFile* infMCprompt = new TFile(promptfile.Data());
  TH1F* hPtprompt = (TH1F*)infMCprompt->Get("hPt");
  TH1F* hPtpromptOrig= (TH1F*)infMCprompt->Get("hPt");

  TFile* infMCnonprompt = new TFile(nonpromptfile.Data());
  TH1F* hPtnonprompt = (TH1F*)infMCnonprompt->Get("hPt");
  TH1F* hPtnonpromptOrig = (TH1F*)infMCnonprompt->Get("hPt");

  TFile* infData = new TFile(datafile.Data());
  TH1F* hPtData= (TH1F*)infData->Get("hPt");
  TH1F* hPtDataOrig= (TH1F*)infData->Get("hPt");

  hPtpromptOrig->Scale(1./hPtpromptOrig->Integral(1,nBins));
  hPtnonpromptOrig->Scale(1./hPtnonpromptOrig->Integral(1,nBins));    
  hPtDataOrig->Scale(1./hPtDataOrig->Integral(1,nBins));    

  TH1F* hPtMCTot = (TH1F*)hPtpromptOrig->Clone("hPtMCTot");
  TH1F* hPtnonpromptNorm = (TH1F*)hPtnonpromptOrig->Clone("hPtnonpromptNorm");
  double norm=0.15;
  hPtnonpromptNorm->Scale(norm/(hPtnonpromptOrig->Integral(1,nBins)/(hPtpromptOrig->Integral(1,nBins)+hPtnonpromptOrig->Integral(1,nBins))));
  hPtMCTot->Add(hPtnonpromptNorm);
  hPtMCTot->Scale(1./hPtMCTot->Integral(1,nBins));    
  std::cout<<"norm="<<norm<<std::endl;

  TH1F* hRatio= (TH1F*)hPtData->Clone("hRatio");
  hRatio->Divide(hPtMCTot);

  TH2F* hempty=new TH2F("hempty","",100,limitlow,limitup,10,0.01,5);  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("Yield / GeV/c^{2}");
  hempty->GetXaxis()->SetTitle(cutvariable.Data());
  hempty->GetXaxis()->SetTitleOffset(0.9);
  hempty->GetYaxis()->SetTitleOffset(1.1);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  

  TH2F* hemptyRatio=new TH2F("hemptyRatio","",100,limitlow,limitup,10,0.,2);  
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Data/MC");
  hemptyRatio->GetXaxis()->SetTitle(cutvariable.Data());
  hemptyRatio->GetXaxis()->SetTitleOffset(0.9);
  hemptyRatio->GetYaxis()->SetTitleOffset(1.1);
  hemptyRatio->GetXaxis()->SetTitleSize(0.045);
  hemptyRatio->GetYaxis()->SetTitleSize(0.045);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.035);
  hemptyRatio->GetYaxis()->SetLabelSize(0.035);  

  TH2F* hemptyOriginal=new TH2F("hemptyOriginal","",100,limitlow,limitup,10,0.01,5);  
  hemptyOriginal->GetXaxis()->CenterTitle();
  hemptyOriginal->GetYaxis()->CenterTitle();
  hemptyOriginal->GetYaxis()->SetTitle("Yield / GeV/c^{2}");
  hemptyOriginal->GetXaxis()->SetTitle(cutvariable.Data());
  hemptyOriginal->GetXaxis()->SetTitleOffset(0.9);
  hemptyOriginal->GetYaxis()->SetTitleOffset(1.1);
  hemptyOriginal->GetXaxis()->SetTitleSize(0.045);
  hemptyOriginal->GetYaxis()->SetTitleSize(0.045);
  hemptyOriginal->GetXaxis()->SetTitleFont(42);
  hemptyOriginal->GetYaxis()->SetTitleFont(42);
  hemptyOriginal->GetXaxis()->SetLabelFont(42);
  hemptyOriginal->GetYaxis()->SetLabelFont(42);
  hemptyOriginal->GetXaxis()->SetLabelSize(0.035);
  hemptyOriginal->GetYaxis()->SetLabelSize(0.035);  

  TCanvas *canvas = new TCanvas("canvas","",1400,500);
  canvas->Divide(3,1);
  canvas->cd(1);
  gPad->SetLogy();
  hemptyOriginal->Draw();
  hPtpromptOrig->SetLineColor(2);
  hPtpromptOrig->SetLineWidth(2);
  hPtpromptOrig->Draw("same");
  hPtnonpromptOrig->SetLineColor(4);
  hPtnonpromptOrig->SetLineWidth(2);
  hPtnonpromptOrig->Draw("same");
  hPtDataOrig->SetLineColor(1);
  hPtDataOrig->SetLineWidth(2);
  hPtDataOrig->Draw("same");
  TLegend *legendOrig=new TLegend(0.2958166,0.6558707,0.5949297,0.8299148,"");
  legendOrig->SetBorderSize(0);
  legendOrig->SetLineColor(0);
  legendOrig->SetFillColor(0);
  legendOrig->SetFillStyle(1001);
  legendOrig->SetTextFont(42);
  legendOrig->SetTextSize(0.045);
  TLegendEntry *ent_DataOrig=legendOrig->AddEntry(hPtData,"Data (norm=1)","pf");
  ent_DataOrig->SetTextFont(42);
  ent_DataOrig->SetLineColor(1);
  TLegendEntry *ent_MCP=legendOrig->AddEntry(hPtpromptOrig,"MC prompt (norm=1)","pf");
  ent_MCP->SetTextFont(42);
  ent_MCP->SetLineColor(2);
  TLegendEntry *ent_MCNP=legendOrig->AddEntry(hPtnonpromptOrig,"MC non prompt (norm=1)","pf");
  ent_MCNP->SetTextFont(42);
  ent_MCNP->SetLineColor(4);
  legendOrig->Draw("same");
  canvas->cd(2);
  gPad->SetLogy();
  hempty->Draw();
  hPtData->SetLineWidth(2);
  hPtData->SetLineColor(1);  
  hPtData->SetMarkerColor(1);
  hPtData->Draw("same");
  hPtMCTot->SetLineWidth(2);
  hPtMCTot->SetLineColor(2);
  hPtMCTot->SetMarkerColor(2);
  hPtMCTot->Draw("same");
  TLegend *legend=new TLegend(0.2958166,0.6558707,0.5949297,0.8299148,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.045);
  TLegendEntry *ent_Data=legend->AddEntry(hPtData,"Data","pf");
  ent_Data->SetTextFont(42);
  ent_Data->SetLineColor(1);
  TLegendEntry *ent_MC=legend->AddEntry(hPtMCTot,"MC (prompt/tot=0.15)","pf");
  ent_MC->SetTextFont(42);
  ent_MC->SetLineColor(2);
  legend->Draw("same");
  canvas->cd(3);
  hemptyRatio->Draw();
  hRatio->SetMinimum(0);
  hRatio->SetMaximum(2);  
  hRatio->Draw("same");
  canvas->SaveAs(Form("canvasMCDataComp_%s.pdf",label.Data()));

}


int main(int argc, char *argv[])
{
  if((argc != 8))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc ==8)
    compareMCdataVariables(argv[1],argv[2],argv[3],argv[4],argv[5], atof(argv[6]),atof(argv[7]));
  return 0;
}



