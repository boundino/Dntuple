#include "uti.h"

/*
TString weight = "1";

double binwidth3prong=(0.160-0.140)/60.;
double binwidth5prong=(0.160-0.140)/60.;
double minmass3prong=0.142;
double maxmass3prong=0.155;
double minmass5prong=0.142;
double maxmass5prong=0.155;

TString infnameData = "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_HeavyFlavor_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root";
TString infnameMC3p = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root";
TString infnameMC5p = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpipipi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpipipi_noweight.root";
TString triggerselection="1";
TString seldata3p=Form("DtktkRes_chi2cl>0.043&&DtktkRes_alpha<0.069&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>0.&&%s",triggerselection.Data());
TString seldata5p=Form("DtktkRes_chi2cl>0.049&&DtktkRes_alpha<0.053&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.45&&%s",triggerselection.Data());

const int nBins=7;  Double_t ptBins[nBins+1]={10.,15.,20.,25.,30.,35.,50.,70.};
*/
TString outputfilename = "outputfile.root";

void plotter(TString mystring="Data")
{ 
  TFile* outputfile=new TFile(outputfilename.Data());
  TH1D* hPt3prong=(TH1D*)outputfile->Get(Form("hPt%s3prong",mystring.Data()));
  TH1D* hPt5prong=(TH1D*)outputfile->Get(Form("hPt%s5prong",mystring.Data()));
  TH1D* hRatio=(TH1D*)outputfile->Get(Form("hRatio%s",mystring.Data()));
  
  TH1D* hPt3prongRelErr=(TH1D*)hPt3prong->Clone(Form("hPt%s3prongRelErr",mystring.Data()));
  TH1D* hPt5prongRelErr=(TH1D*)hPt5prong->Clone(Form("hPt%s5prongRelErr",mystring.Data()));
  TH1D* hRatioRelErr=(TH1D*)hRatio->Clone(Form("hRatio%sRelErr",mystring.Data()));

  for(int i=1;i<hPt3prongRelErr->GetNbinsX()+1;i++)
    {
      hPt3prongRelErr->SetBinContent(i,hPt3prongRelErr->GetBinError(i)/hPt3prongRelErr->GetBinContent(i));
      hPt5prongRelErr->SetBinContent(i,hPt5prongRelErr->GetBinError(i)/hPt5prongRelErr->GetBinContent(i));
      hRatioRelErr->SetBinContent(i,hRatioRelErr->GetBinError(i)/hRatioRelErr->GetBinContent(i));  
      hPt3prongRelErr->SetBinError(i,0.0001);
      hPt5prongRelErr->SetBinError(i,0.0001);
      hRatioRelErr->SetBinError(i,0.0001);
    }
  
  TCanvas* cRatio = new TCanvas("cRatio","",1200,800);
  cRatio->Divide(3,2);
  cRatio->cd(1);
  hPt3prong->SetXTitle("D meson p_{T}");
  hPt3prong->SetYTitle(Form("Raw fit signal %s 3 prong",mystring.Data()));
  hPt3prong->Draw();  
  cRatio->cd(2);
  hPt5prong->SetXTitle("D meson p_{T}");
  hPt5prong->SetYTitle(Form("Raw fit signal %s 3 prong",mystring.Data()));
  hPt5prong->Draw();  
  cRatio->cd(3);
  hRatio->SetXTitle("D meson p_{T}");
  hRatio->SetYTitle(Form("Ratio Raw fit signal %s 5/3 prong",mystring.Data()));
  hRatio->Draw();
  cRatio->cd(4);
  hPt3prongRelErr->GetYaxis()->SetTitleOffset(1.6);
  hPt3prongRelErr->SetXTitle("D meson p_{T}");
  hPt3prongRelErr->SetYTitle(Form("Rel err.  signal %s 3 prong",mystring.Data()));
  hPt3prongRelErr->Draw();  
  cRatio->cd(5);
  hPt5prongRelErr->GetYaxis()->SetTitleOffset(1.6);
  hPt5prongRelErr->SetXTitle("D meson p_{T}");
  hPt5prongRelErr->SetYTitle(Form("Rel err. signal %s 3 prong",mystring.Data()));
  hPt5prongRelErr->Draw();  
  cRatio->cd(6);
  hRatioRelErr->GetYaxis()->SetTitleOffset(1.6);
  hRatioRelErr->SetXTitle("D meson p_{T}");
  hRatioRelErr->SetYTitle(Form("Rel err. Ratio %s 5/3 prong",mystring.Data()));
  hRatioRelErr->Draw();
  cRatio->SaveAs("cRatio.pdf");
}
