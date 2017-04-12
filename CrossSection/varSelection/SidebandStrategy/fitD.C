using namespace std;
#include "uti.h"

Float_t sigregWidth = 0.03;
Float_t sidbndLow = 0.06;
Float_t sidbndHigh = 0.12;
Float_t wfactor = sigregWidth/(sidbndHigh-sidbndLow);

TString collisionsystem;
TString infname;
TString varname;
TString vartex;
Int_t isLarger;
Float_t centmin,centmax;

void fitD(TString collsyst="PbPb", TString varname_="", Int_t varbins=10, Float_t varmin=0.5, Float_t varmax=2, TString vartex_="", Int_t isLarger_=1, Float_t centMin=0, Float_t centMax=100, TString outputfile="outfMasshisto/mass")
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  gStyle->SetOptStat(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.8);

  collisionsystem = collsyst;
  infname = outputfile;
  varname=varname_;
  vartex=vartex_;
  isLarger=isLarger_;
  centmin = centMin;
  centmax = centMax;

  Float_t varstep;
  if(varbins==1) varstep = 0.5;
  else varstep = (varmax-varmin)/(varbins-1);
  TH1F* hMCCut = new TH1F("hMCCut","",varbins,varmin,varmax+varstep);                  hMCCut->Sumw2();
  TH1F* hMCNoCut = new TH1F("hMCNoCut","",varbins,varmin,varmax+varstep);              hMCNoCut->Sumw2();
  TH1F* hDaCutSigreg = new TH1F("hDaCutSigreg","",varbins,varmin,varmax+varstep);      hDaCutSigreg->Sumw2();
  TH1F* hDaNoCutSigreg = new TH1F("hDaNoCutSigreg","",varbins,varmin,varmax+varstep);  hDaNoCutSigreg->Sumw2();
  TH1F* hDaCutSidbnd = new TH1F("hDaCutSidbnd","",varbins,varmin,varmax+varstep);      hDaCutSidbnd->Sumw2();
  TH1F* hDaNoCutSidbnd = new TH1F("hDaNoCutSidbnd","",varbins,varmin,varmax+varstep);  hDaNoCutSidbnd->Sumw2();
  TString tMC;
  for(float i=0;i<varbins+1;i++)
    {
      tMC = "MC";
      TFile* infile = new TFile(Form("%s_%s_cent_%.0f_%.0f_%s_%s_%.0f.root",infname.Data(),collisionsystem.Data(),centmin,centmax,varname.Data(),tMC.Data(),i));
      TH1D* hDaSigreg = (TH1D*)infile->Get("hDaSigreg");    hDaSigreg->SetName(Form("hDaSigreg_%s_%.0f",tMC.Data(),i));
      TH1D* hDaSidbnd = (TH1D*)infile->Get("hDaSidbnd");    hDaSidbnd->SetName(Form("hDaSidbnd_%s_%.0f",tMC.Data(),i));
      TH1D* hMCSignal = (TH1D*)infile->Get("hMCSignal");    hMCSignal->SetName(Form("hMCSignal_%s_%.0f",tMC.Data(),i));
      Double_t yield,yieldErr;
      Float_t ivar = varmin+(i-1)*varstep;
      yield = hMCSignal->IntegralAndError(0,1000,yieldErr);
      if(i==0)
        {
          for(int j=0;j<varbins;j++)
            {
              hMCNoCut->SetBinContent(j+1,yield);
              hMCNoCut->SetBinError(j+1,yieldErr);
            }
        }
      else
        {
          hMCCut->SetBinContent(i,yield);
          hMCCut->SetBinError(i,yieldErr);
        }
      Double_t ySigreg,ySigregErr,ySidbnd,ySidbndErr;
      ySigreg = hDaSigreg->IntegralAndError(0,1000,ySigregErr);
      ySidbnd = hDaSidbnd->IntegralAndError(0,1000,ySidbndErr);
      if(i==0)
        {
          for(int j=0;j<varbins;j++)
            {
              hDaNoCutSigreg->SetBinContent(j+1,ySigreg);
              hDaNoCutSigreg->SetBinError(j+1,ySigregErr);
              hDaNoCutSidbnd->SetBinContent(j+1,ySidbnd);
              hDaNoCutSidbnd->SetBinError(j+1,ySidbndErr);
            }
        }
      else
        {
          hDaCutSigreg->SetBinContent(i,ySigreg);
          hDaCutSigreg->SetBinError(i,ySigregErr);
          hDaCutSidbnd->SetBinContent(i,ySidbnd);
          hDaCutSidbnd->SetBinError(i,ySidbndErr);
        }
    }
  TH1F* hDaCut = (TH1F*)hDaCutSigreg->Clone("hDaCut");
  hDaCut->Add(hDaCutSidbnd,-wfactor);
  TH1F* hDaNoCut = (TH1F*)hDaNoCutSigreg->Clone("hDaNoCut");
  hDaNoCut->Add(hDaNoCutSidbnd,-wfactor);
  
  TCanvas* cMCRatio = new TCanvas("cMCRatio","",600,600);
  TH1F* hMCRatio = (TH1F*)hMCCut->Clone("hMCRatio");
  hMCRatio->SetTitle(Form(";%s;hMCRatio",vartex.Data()));
  hMCRatio->Divide(hMCNoCut);
  hMCRatio->Draw();

  TCanvas* cDaRatio = new TCanvas("cDaRatio","",600,600);
  TH1F* hDaRatio = (TH1F*)hDaCut->Clone("hDaRatio");
  hDaRatio->SetTitle(Form(";%s;hDaRatio",vartex.Data()));
  hDaRatio->Divide(hDaNoCut);
  hDaRatio->Draw();

  TCanvas* chDoubleRatio = new TCanvas("chDoubleRatio","",600,600);
  TH1F* hDoubleRatio = (TH1F*)hDaRatio->Clone("hDoubleRatio");
  hDoubleRatio->SetTitle(Form(";%s;hDoubleRatio",vartex.Data()));
  hDoubleRatio->Divide(hMCRatio);
  hDoubleRatio->Draw();

  cout<<endl;
  cout<<"\\hline"<<endl;
  cout<<"Cut on "<<vartex<<" & $Yield^{i}_{Data}(cut)/Yield^{i}_{Data}(nocut)$ & $Yield^{i}_{MC}(cut)/Yield^{i}_{MC}(nocut)$ & Ratio (Data/MC) \\\\"<<endl;
  cout<<"\\hline"<<endl;
  for(int i=0;i<varbins;i++)
    {
      cout<<setiosflags(ios::fixed)<<setprecision(2)<<(varmin+i*varstep)<<" & ";
      cout<<setiosflags(ios::fixed)<<setprecision(3)<<hDaRatio->GetBinContent(i+1)<<" $\\pm$ "<<hDaRatio->GetBinError(i+1)<<" & "<<hMCRatio->GetBinContent(i+1)<<" $\\pm$ "<<hMCRatio->GetBinError(i+1)<<" & "<<hDoubleRatio->GetBinContent(i+1)<<" $\\pm$ "<<hDoubleRatio->GetBinError(i+1)<<" \\\\"<<endl;
    }
  cout<<"\\hline"<<endl;
  cout<<endl;
  Float_t aDoubleRatio[varbins],aDoubleRatioErr[varbins],aX[varbins],aZero[varbins];
  for(int i=0;i<varbins;i++)
    {
      aDoubleRatio[i] = hDoubleRatio->GetBinContent(i+1);
      aDoubleRatioErr[i] = hDoubleRatio->GetBinError(i+1);
      aX[i] = varmin+i*varstep;
      aZero[i] = 0;
    }
  TGraphErrors* gDoubleRatio = new TGraphErrors(varbins,aX,aDoubleRatio,aZero,aDoubleRatioErr);
  TH2F* hemptyDoubleRatio = new TH2F("hemptyDoubleRatio","",20,varmin-0.5*varstep,varmax+0.5*varstep,10.,0.8,1.2);
  hemptyDoubleRatio->GetXaxis()->SetTitle(Form("%s",vartex.Data()));
  hemptyDoubleRatio->GetYaxis()->SetTitle("(Yield^{Data}_{Cuts}/Yield^{Data}_{NoCuts})/(Yield^{MC}_{Cuts}/Yield^{MC}_{NoCuts})");
  hemptyDoubleRatio->GetXaxis()->SetTitleOffset(1.0);
  hemptyDoubleRatio->GetYaxis()->SetTitleOffset(1.7);
  hemptyDoubleRatio->GetXaxis()->SetTitleSize(0.045);
  hemptyDoubleRatio->GetYaxis()->SetTitleSize(0.045);
  hemptyDoubleRatio->GetXaxis()->SetTitleFont(42);
  hemptyDoubleRatio->GetYaxis()->SetTitleFont(42);
  hemptyDoubleRatio->GetXaxis()->SetLabelFont(42);
  hemptyDoubleRatio->GetYaxis()->SetLabelFont(42);
  hemptyDoubleRatio->GetXaxis()->SetLabelSize(0.04);
  hemptyDoubleRatio->GetYaxis()->SetLabelSize(0.04);
  TLine* lDoubleRatio = new TLine(varmin-0.5*varstep, 1., varmax+0.5*varstep, 1.);
  lDoubleRatio->SetLineWidth(1);
  lDoubleRatio->SetLineStyle(7);
  lDoubleRatio->SetLineColor(1);
  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsystem.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  TCanvas* cDoubleRatio = new TCanvas("cDoubleRatio","",600,600);
  hemptyDoubleRatio->Draw();
  gDoubleRatio->Draw("psame");
  lDoubleRatio->Draw();
  texCms->Draw();
  texCol->Draw();
  cDoubleRatio->SaveAs(Form("plotRatios/%s_cent_%.0f_%.0f_%s_DoubleRatio.pdf",collisionsystem.Data(),centmin,centmax,varname.Data()));

  TFile* outf = new TFile(Form("outfDoubleratio/f%s_cent_%.0f_%.0f_%s_DoubleRatio.root",collisionsystem.Data(),centmin,centmax,varname.Data()),"recreate");
  outf->cd();
  hDoubleRatio->Write();
  outf->Close();
}

int main(int argc, char *argv[])
{
  if(argc==10)
    {
      fitD(argv[1],argv[2],atoi(argv[3]),atof(argv[4]),atof(argv[5]),argv[6],atoi(argv[7]),atof(argv[8]),atof(argv[9]));
      return 0;
    }
  else if(argc==8)
    {
      fitD(argv[1],argv[2],atoi(argv[3]),atof(argv[4]),atof(argv[5]),argv[6],atoi(argv[7]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}

