#include "../doubleratioParameter.h"

enum real{MC,Data,MC_MB,Data_MB} isData=Data_MB;
enum prong{threePr,fivePr} nprong=fivePr;
const int nBins=1; Float_t ptBins[nBins+1]={25.,100.};
TString ntname[2] = {"ntDD0kpipi","ntDD0kpipipipi"};
void plotmassspectra(Bool_t doweight=true)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  void clean0 (TH1D* h);
  void plotDstarmass (TTree* nt, Float_t ptmin, Float_t ptmax);

  TString infname;
  if(nprong==threePr) infname = infnameData3p[isData];
  else if(nprong==fivePr) infname = infnameData5p[isData];
  TFile* inf = new TFile(infname);
  TTree* ntD = (TTree*)inf->Get(ntname[nprong]);
  ntD->AddFriend("ntHlt");

  for(int i=0;i<nBins;i++)
    {
      plotDstarmass(ntD,ptBins[i],ptBins[i+1]);
    }
}

void plotDstarmass(TTree* nt, Float_t ptmin, Float_t ptmax)
{
  TCanvas* c= new TCanvas(Form("c_massspectra_%s_%s_%.0f_%.0f",texData[isData].Data(),ntname[nprong].Data(),ptmin,ptmax),"",600,600);
  TH1D* h = new TH1D(Form("h_massspectra_%s_%s_%.0f_%.0f",texData[isData].Data(),ntname[nprong].Data(),ptmin,ptmax),"",60,0.140,0.160);
  nt->Project(Form("h_massspectra_%s_%s_%.0f_%.0f",texData[isData].Data(),ntname[nprong].Data(),ptmin,ptmax),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f)",weight.Data(),seldata3p[isData].Data(),triggerselection[isData].Data(),ptmin,ptmax));   
  h->Sumw2();
  
  if(nprong==threePr) h->SetXTitle("M_{K#pi#pi}-M_{K#pi} (GeV/c^{2})");
  if(nprong==fivePr) h->SetXTitle("M_{K#pi#pi#pi#pi}-M_{K#pi#pi#pi} (GeV/c^{2})");
  h->SetXTitle("M_{K#pi#pi}-M_{K#pi} (GeV/c^{2})");
  h->SetYTitle("Entries / (1/3 MeV/c^{2})");
  h->SetStats(0);
  h->SetAxisRange(1,h->GetMaximum()*1.3,"Y");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitleOffset(1.8);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);
  h->Draw("e");

  TLatex* tex;
  TLegend* leg = new TLegend(0.60,0.77,0.85,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  if(nprong==threePr) leg->AddEntry((TObject*)0,"D* D^{0}(K#pi)#pi",NULL);
  if(nprong==fivePr) leg->AddEntry((TObject*)0,"D* D^{0}(K#pi#pi#pi)#pi",NULL);
  leg->AddEntry(h,"Data","pl");
  leg->Draw("same");

  tex = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  tex->SetNDC();
  tex->SetTextAlign(12);
  tex->SetTextSize(0.04);
  tex->SetTextFont(42);
  tex->Draw();
  tex = new TLatex(0.65,0.93, "PP #sqrt{s_{NN}} = 5.02 TeV");
  tex->SetNDC();
  tex->SetTextAlign(12);
  tex->SetTextSize(0.04);
  tex->SetTextFont(42);
  tex->Draw();
  tex = new TLatex(0.20,0.79,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  tex = new TLatex(0.20,0.84,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();

  c->SaveAs(Form("onlymass/c_massspectra_%s_%s_%.0f_%.0f.pdf",texData[isData].Data(),ntname[nprong].Data(),ptmin,ptmax));
}
