using namespace std;
#include "doubleratioParameter.h"

const int nBins=10;  Float_t ptBins[nBins]={5.,6.,7.,8.,9.,10.,11.,12.,13.,14.}; Float_t ptBinsPlus[nBins+1]={5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.};

void fitDstar3pMinpt(TString condition="default")
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  TF1* fitDstar(Float_t ptmin, TString cdt);

  TFile* infMC = new TFile(infnameMC3p[isData].Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDD0kpipi");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  ntGen->AddFriend("ntHlt");
  ntGen->AddFriend("ntHi");
  
  Float_t aZero[nBins];
  for(int i=0;i<nBins;i++) aZero[i]=0;
  Float_t aPt[nBins],aPtErr[nBins],aGen[nBins],aGenErr[nBins];
  TH1F* hPt = new TH1F("hPt","",nBins,ptBinsPlus);
  TH1F* hGen = new TH1F("hGen","",nBins,ptBinsPlus);

  for(int i=0;i<nBins;i++)
    {
      TF1* fData = fitDstar(ptBins[i],condition);
      Float_t yieldData = fData->Integral(BINMIN,BINMAX)/BINWID;
      Float_t yieldDataErr = fData->Integral(BINMIN,BINMAX)/BINWID*fData->GetParError(0)/fData->GetParameter(0);
      aPt[i] = yieldData;
      aPtErr[i] = yieldDataErr;
      hPt->SetBinContent(i+1,aPt[i]);
      hPt->SetBinError(i+1,aPtErr[i]);
      TH1D* hGenFill = new TH1D(Form("hGenFill_%.0f",ptBins[i]),"",1,ptBins[i],1.e+3);
      hGenFill->Sumw2();
      ntGen->Project(Form("hGenFill_%.0f",ptBins[i]),"Gpt",TCut("%s",weightmc[isData].Data())*Form("%s&&%s",selgen3p.Data(),triggerselectionmc[isData].Data()));
      aGen[i] = hGenFill->GetBinContent(1);
      aGenErr[i] = hGenFill->GetBinError(1);
      hGen->SetBinContent(i+1,aGen[i]);
      hGen->SetBinError(i+1,aGenErr[i]);
    }

  TGraphErrors* gPt = new TGraphErrors(nBins,ptBins,aPt,aZero,aPtErr);
  gPt->SetName("gPt");
  TGraphErrors* gGen = new TGraphErrors(nBins,ptBins,aGen,aZero,aGenErr);
  gGen->SetName("gGen");

  TFile* outputfile = new TFile(Form("outputfiles/output_pp_%s_3p_%s.root",condition.Data(),texData[isData].Data()),"recreate");
  outputfile->cd();
  gPt->Write();
  gGen->Write();
  hPt->Write();
  hGen->Write();
  outputfile->Close();
}

TF1* fitDstar(Float_t ptmin,TString cdt)
{
  TCanvas* c = new TCanvas(Form("c_3p_%.0f",ptmin),"",600,600);
  TFile* infile = new TFile(Form("saveHistSinglept/fmass/fmass_pp_%s_3p_%s_%.0f.root",cdt.Data(),texData[isData].Data(),ptmin));
  TH1D* h = (TH1D*)infile->Get("h");                    h->SetName(Form("h_3p_%.0f",ptmin));
  TH1D* hMCSignal = (TH1D*)infile->Get("hMCSignal");    hMCSignal->SetName(Form("hMCSignal_3p_%.0f",ptmin));
  TH1D* hMCSwapped = (TH1D*)infile->Get("hMCSwapped");  hMCSwapped->SetName(Form("hMCSwapped_3p_%.0f",ptmin));

  TF1* f = new TF1(Form("f_3p_%.0f",ptmin),"[0]*([4]*([6]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[6])*(Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))+(1-[4])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3]))+[10]*((1-exp((0.13957-x)/[7]))*pow(x/0.13957,[8])+[9]*(x/0.13957-1))",BINMIN,BINMAX);

  f->FixParameter(4,1.);
  f->FixParameter(1,0.145491);
  f->FixParameter(10,0.);

  f->SetParLimits(0,0,1.e+5);
  f->SetParLimits(6,0,1.);
  f->SetParLimits(2,1.e-4,1.e-3);
  f->SetParameter(2,2.e-4);
  f->SetParLimits(5,5.e-4,2.e-3);
  f->SetParameter(5,1.e-3);
  hMCSignal->Fit(Form("f_3p_%.0f",ptmin),"LL","",BINMIN,BINMAX);
  hMCSignal->Fit(Form("f_3p_%.0f",ptmin),"LL","",BINMIN,BINMAX);
  f->ReleaseParameter(1);
  f->SetParLimits(1,minmass,maxmass);
  hMCSignal->Fit(Form("f_3p_%.0f",ptmin),"LL","",minmass,maxmass);
  hMCSignal->Fit(Form("f_3p_%.0f",ptmin),"LL","",minmass,maxmass);

  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(5,f->GetParameter(5));
  f->FixParameter(6,f->GetParameter(6));
  f->FixParameter(4,0);
  f->SetParLimits(3,2.e-4,2.e-3);

  hMCSwapped->Fit(Form("f_3p_%.0f",ptmin),"L q","",BINMIN,BINMAX);
  hMCSwapped->Fit(Form("f_3p_%.0f",ptmin),"L q","",BINMIN,BINMAX);

  f->FixParameter(4,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(3,f->GetParameter(3));

  f->SetParLimits(7,5.e-4,1.e-2);
  f->SetParameter(7,1.6e-3);
  f->SetParLimits(8,0.,15.);
  f->SetParameter(8,0.35);
  f->SetParLimits(9,-1.e+1,2.e+1);
  f->SetParameter(9,13.);
  f->ReleaseParameter(10);
  f->SetParLimits(10,0.,1.e+5);

  h->Fit(Form("f_3p_%.0f",ptmin),"LL","",BINMIN,BINMAX);
  h->Fit(Form("f_3p_%.0f",ptmin),"LL","",BINMIN,BINMAX);

  /*
  f->ReleaseParameter(1);
  f->SetParLimits(1,minmass,maxmass);
  f->SetParameter(1,f->GetParameter(1));
  h->Fit(Form("f_3p_%.0f",ptmin),"LL","",BINMIN,BINMAX);
  h->Fit(Form("f_3p_%.0f",ptmin),"LL","",BINMIN,BINMAX);
  */

  TF1* background = new TF1(Form("background_3p_%.0f",ptmin),"[3]*((1-exp((0.13957-x)/[0]))*pow(x/0.13957,[1])+[2]*(x/0.13957-1))");
  background->SetParameters(f->GetParameter(7),f->GetParameter(8),f->GetParameter(9),f->GetParameter(10));
  background->SetRange(BINMIN,BINMAX);
  background->SetLineColor(4);
  background->SetLineWidth(3);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_3p_%.0f",ptmin),"[0]*([3]*([5]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[5])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4])))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(4),f->GetParameter(5),f->GetParameter(6));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(4));
  mass->SetParError(4,f->GetParError(5));
  mass->SetParError(5,f->GetParError(6));
  mass->SetRange(BINMIN,BINMAX);
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
  
  TF1* massSwap = new TF1(Form("fmassSwap_3p_%.0f",ptmin),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(4),f->GetParameter(3));
  massSwap->SetRange(BINMIN,BINMAX);
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);

  h->SetXTitle("M_{K#pi#pi}-M_{K#pi} (GeV/c^{2})");
  h->SetYTitle("Entries / (0.4 MeV/c^{2})");
  h->SetStats(0);
  h->SetAxisRange(0,h->GetMaximum()*1.3,"Y");
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
  mass->Draw("same");
  massSwap->Draw("same");
  background->Draw("same");
  f->Draw("same");

  Float_t yield = mass->Integral(BINMIN,BINMAX)/BINWID;
  Float_t yieldErr = mass->Integral(BINMIN,BINMAX)/BINWID*mass->GetParError(0)/mass->GetParameter(0);
  cout<<mass->GetParameter(0)<<" "<<mass->Integral(BINMIN,BINMAX)<<endl;

  TLatex* tex;
  TLegend* leg = new TLegend(0.60,0.57,0.85,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry((TObject*)0,"D* D^{0}(K#pi)#pi",NULL);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D*^{+}+D*^{-} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  tex = new TLatex(0.61,0.52,Form("N_{D} = %.0f #pm %.0f",yield,yieldErr));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();

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
  tex = new TLatex(0.20,0.84,Form("p_{T} > %.1f GeV/c",ptmin));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();

  c->SaveAs(Form("plots/fits/DMass_pp_%s_3p_%s_%.0f.pdf",cdt.Data(),texData[isData].Data(),ptmin));

  return mass;
}

int main(int argc, char *argv[])
{
  if(argc!=2)
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  else
    {
      fitDstar3pMinpt(argv[1]);
      return 0;
    }
}
