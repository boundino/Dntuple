#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TStyle.h>

TString cuts = "Dy>-1.0&&Dy<1.0&&Dpt>1.&&Dtrk1Pt>1.&&DRestrk1Pt>1.&&DRestrk2Pt>1.";
TString infBkg = "/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160104_DfinderData_pp_20151218_dPt0tkPt1_D0Dstar3p5p.root";
TString cutBkg = Form("%s&&abs(Dmass-2.010)>0.1&&abs(Dmass-2.010)<0.15",cuts.Data());
TString ntD = "ntDD0kpipi"; TString infSgl = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_CandBase_20151231_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root"; TString cutSgl = Form("%s&&Dgen==23333",cuts.Data());

void plotVariables()
{
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.12);

  void plot(TString var, TString varlatex, TString varname, Int_t nbins, Double_t vmin, Double_t vmax);

  plot("Ddtheta","D* #theta","theta", 50, 0., 3.2);
  plot("Dalpha","D* #alpha","alpha", 50, 0., 3.2);
  plot("Dchi2cl","D* vertex prob","vtxprob", 50, 0., 1.);
  plot("DsvpvDistance/DsvpvDisErr","D* 3D decay length sig","ffls3d", 50, 0., 20.);
  plot("DlxyBS/DlxyBSErr","D* lxyBS sig","lxyBSsig", 50, 0., 50);

  plot("DtktkRes_chi2cl","D^{0} vertex prob","resvtxprob", 50, 0., 1.);
  plot("DtktkRes_alpha","D^{0} #alpha","resalpha", 50, 0., 3.2);
  plot("DtktkRes_svpvDistance/DtktkRes_svpvDisErr","D^{0} decay length sig","resffls3d", 50, 0, 20.);

}

void plot(TString var, TString varlatex, TString varname, Int_t nbins, Double_t vmin, Double_t vmax)
{
  cout<<"---- Processing - "<<var<<endl;
  cout<<"  -- Fill histograms"<<endl;
  TFile* ifBkg = new TFile(infBkg);
  TTree* ntBkg = (TTree*)ifBkg->Get(ntD);
  TFile* ifSgl = new TFile(infSgl);
  TTree* ntSgl = (TTree*)ifSgl->Get(ntD);

  TH1D* hBkg = new TH1D(Form("hBkg_%s",varname.Data()),"",nbins,vmin,vmax);
  TH1D* hSgl = new TH1D(Form("hSgl_%s",varname.Data()),"",nbins,vmin,vmax);

  ntBkg->Project(Form("hBkg_%s",varname.Data()),var,cutBkg);
  ntSgl->Project(Form("hSgl_%s",varname.Data()),var,cutSgl);

  cout<<"  -- Calculate normalization"<<endl;
  Double_t normBkg=0,normSgl=0;
  normBkg = hBkg->GetEntries();
  normSgl = hSgl->GetEntries();
  cout<<"     normBkg: "<<normBkg<<" ;   normSgl: "<<normSgl<<endl;

  cout<<"  -- Normalize histograms"<<endl;
  hBkg->Scale(1./normBkg);
  hSgl->Scale(1./normSgl); 

  cout<<"  -- Plot"<<endl;
  hBkg->SetXTitle(varlatex);
  hBkg->SetYTitle("#Probability");
  hBkg->SetTitleOffset(1.5,"Y");
  Double_t hisMax = (hBkg->GetMaximum()>hSgl->GetMaximum())?hBkg->GetMaximum():hSgl->GetMaximum();
  hBkg->SetMaximum(hisMax*1.2);

  hBkg->SetLineColor(kBlue+1);
  hBkg->SetFillStyle(1001);
  hBkg->SetFillColor(kBlue-9);
  hBkg->SetLineWidth(3);
  hBkg->SetStats(0);

  hSgl->SetLineColor(kRed);
  hSgl->SetFillStyle(3004);
  hSgl->SetFillColor(kRed);
  hSgl->SetLineWidth(3);
  hSgl->SetStats(0);

  TCanvas* c = new TCanvas(Form("c_%s",varname.Data()),"",600,600);
  hBkg->Draw();
  hSgl->Draw("same");

  cout<<"  -- Plot legends"<<endl;
  TLatex* tex = new TLatex(0.18,0.935,"5.02TeV pp");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->Draw();
  TLatex* texp;
  if(ntD=="ntDD0kpipi") texp = new TLatex(0.68,0.935,"D* D^{0}(K#pi)#pi");
  if(ntD=="ntDD0kpipipipi") texp = new TLatex(0.65,0.935,"D* D^{0}(K#pi#pi#pi)#pi");
  texp->SetNDC();
  texp->SetTextFont(42);
  texp->SetTextSize(0.055);
  texp->Draw();
  TLegend* leg = new TLegend(0.56,0.70,0.86,0.86);
  leg->AddEntry(hBkg,"Background","f");
  leg->AddEntry(hSgl,"Signal","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");

  cout<<"  -- Save plots"<<endl;
  c->SaveAs(Form("plots/%s/c_%s.pdf",ntD.Data(),varname.Data()));
  cout<<endl;
}

