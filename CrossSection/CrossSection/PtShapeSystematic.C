#include "uti.h"
#include "TString.h"
#include "TLegendEntry.h"


void doplot(TString noweight="ROOTfiles/MCstudiesPPMB.root",TString weight="ROOTfiles/MCstudiesPPMBPPMBptreweighted.root",TString label="PPMB"){
  TFile *filenoweight=new TFile(noweight.Data());
  TFile *fileweight=new TFile(weight.Data());
  TH1F*hEffNoWeight=(TH1F*)filenoweight->Get("hEff");
  TH1F*hEffWeight=(TH1F*)fileweight->Get("hEff");

  hEffWeight->Divide(hEffNoWeight);
  hEffWeight->Draw();

  TCanvas*canvas=new TCanvas("canvas","canvas",500.,500);
  canvas->cd();
  hEffWeight->GetXaxis()->CenterTitle();
  hEffWeight->GetYaxis()->CenterTitle();
  hEffWeight->GetXaxis()->SetTitleOffset(1.0);
  hEffWeight->GetYaxis()->SetTitleOffset(1.15);
  hEffWeight->GetXaxis()->SetTitleSize(0.04);
  hEffWeight->GetYaxis()->SetTitleSize(0.04);
  hEffWeight->GetXaxis()->SetTitleFont(42);
  hEffWeight->GetYaxis()->SetTitleFont(42);
  hEffWeight->GetXaxis()->SetLabelFont(42);
  hEffWeight->GetYaxis()->SetLabelFont(42);
  hEffWeight->GetXaxis()->SetLabelSize(0.035);
  hEffWeight->GetYaxis()->SetLabelSize(0.035);  
  hEffWeight->SetMinimum(0.8);
  hEffWeight->SetMaximum(1.2);
  hEffWeight->SetXTitle("Gen p_{T}");
  hEffWeight->SetYTitle("Efficiency p_{T} weight/no weight");
  hEffWeight->Draw();
  canvas->SaveAs(Form("canvasPtreweightedComparison%s.pdf",label.Data()));

}


void PtShapeSystematic(){

 void doplot(TString,TString,TString);
 doplot("ROOTfiles/MCstudiesPP.root","ROOTfiles/MCstudiesPPPPptreweighted.root","PP");
 doplot("ROOTfiles/MCstudiesPPMB.root","ROOTfiles/MCstudiesPPMBPPMBptreweighted.root","PPMB");
 doplot("ROOTfiles/MCstudiesPbPb.root","ROOTfiles/MCstudiesPbPbPbPbptreweighted.root","PbPb");
 doplot("ROOTfiles/MCstudiesPbPbMB.root","ROOTfiles/MCstudiesPbPbMBPbPbMBptreweighted.root","PbPbMB");
 
}


int main(int argc, char *argv[])
{
  PtShapeSystematic();
  return 1;
}
