using namespace std;
#include "uti.h"

void plotFits(Float_t ptMin=20, Float_t ptMax=40, TString collision="PbPb")
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  TFile* inf = new TFile(Form("outfiles/output%s_%.0f_%.0f.root",collision.Data(),ptMin,ptMax));
  TH1D* hSideband = (TH1D*)inf->Get("hSideband");
  TF1* fSideband = hSideband->GetFunction("fSideband");
  TH1D* hMCPSignal = (TH1D*)inf->Get("hMCPSignal");
  TF1* fMCPSignal = hMCPSignal->GetFunction("fMCPSignal");
  TH1D* hMCNPSignal = (TH1D*)inf->Get("hMCNPSignal");
  TF1* fMCNPSignal = hMCNPSignal->GetFunction("fMCNPSignal");

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
  TLatex* texY = new TLatex(0.52,0.81,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.04);
  TLatex* texPt = new TLatex(0.52,0.76,Form("%.1f < p_{T} < %.1f GeV/c",ptMin,ptMax));
  texPt->SetNDC();
  texPt->SetTextFont(42);
  texPt->SetTextSize(0.04);

  TCanvas* cSideband = new TCanvas("cSideband","",600,600);
  TLegend* legSideband = new TLegend(0.51,0.63,0.90,0.74);
  legSideband->SetBorderSize(0);
  legSideband->SetFillStyle(0);
  legSideband->AddEntry(hSideband,"Sideband","pl");
  legSideband->AddEntry(fSideband,"Fit","l");
  hSideband->Draw();
  texCms->Draw();
  texCol->Draw();
  texY->Draw();
  texPt->Draw();
  legSideband->Draw("same");
  cSideband->SaveAs(Form("plots/Fits/cSideband_%s_%.0f_%.0f.pdf",collision.Data(),ptMin,ptMax));

  TCanvas* cMCPSignal = new TCanvas("cMCPSignal","",600,600);
  TLegend* legMCPSignal = new TLegend(0.51,0.63,0.88,0.74);
  legMCPSignal->SetBorderSize(0);
  legMCPSignal->SetFillStyle(0);
  legMCPSignal->AddEntry(hMCPSignal,"Prompt","pl");
  legMCPSignal->AddEntry(fMCPSignal,"Fit","l");
  hMCPSignal->Draw();
  texCms->Draw();
  texCol->Draw();
  texY->Draw();
  texPt->Draw();
  legMCPSignal->Draw("same");
  cMCPSignal->SaveAs(Form("plots/Fits/cMCPSignal_%s_%.0f_%.0f.pdf",collision.Data(),ptMin,ptMax));

  TCanvas* cMCNPSignal = new TCanvas("cMCNPSignal","",600,600);
  TLegend* legMCNPSignal = new TLegend(0.51,0.63,0.88,0.74);
  legMCNPSignal->SetBorderSize(0);
  legMCNPSignal->SetFillStyle(0);
  legMCNPSignal->AddEntry(hMCNPSignal,"Non-prompt","pl");
  legMCNPSignal->AddEntry(fMCNPSignal,"Fit","l");
  hMCNPSignal->Draw();
  texCms->Draw();
  texCol->Draw();
  texY->Draw();
  texPt->Draw();
  legMCNPSignal->Draw("same");
  cMCNPSignal->SaveAs(Form("plots/Fits/cMCNPSignal_%s_%.0f_%.0f.pdf",collision.Data(),ptMin,ptMax));

}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      plotFits(atof(argv[1]),atof(argv[2]),argv[3]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
