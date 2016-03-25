using namespace std;
#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString collisionsystem;
TString infname;
TString varname;
TString vartex;
Int_t isLarger;
void fitD(TString collsyst="PbPb", TString varname_="", Int_t varbins=10, Float_t varmin=0.5, Float_t varmax=2,TString vartex_="", Int_t isLarger_=1, TString outputfile="outfMasshisto/mass")
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

  TF1* fit(Float_t varval, Float_t ibin, Int_t isMC);
  
  Float_t varstep;
  if(varbins==1) varstep = 0.5;
  else varstep = (varmax-varmin)/(varbins-1);
  TH1F* hMCCut = new TH1F("hMCCut","",varbins,varmin,varmax+varstep);
  TH1F* hMCNoCut = new TH1F("hMCNoCut","",varbins,varmin,varmax+varstep);
  TH1F* hDaCut = new TH1F("hDaCut","",varbins,varmin,varmax+varstep);
  TH1F* hDaNoCut = new TH1F("hDaNoCut","",varbins,varmin,varmax+varstep);
  for(float i=0;i<varbins+1;i++)
    {
      Float_t yield,yieldErr;
      Float_t ivar = varmin+(i-1)*varstep;
      TF1* fMC = fit(ivar,i,1);
      yield = fMC->Integral(minhisto,maxhisto)/binwidthmass;
      yieldErr = fMC->Integral(minhisto,maxhisto)/binwidthmass*fMC->GetParError(0)/fMC->GetParameter(0);
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
      TF1* fDa = fit(ivar,i,0);
      yield = fDa->Integral(minhisto,maxhisto)/binwidthmass;
      yieldErr = fDa->Integral(minhisto,maxhisto)/binwidthmass*fDa->GetParError(0)/fDa->GetParameter(0);
      if(i==0)
        {
          for(int j=0;j<varbins;j++)
            {
              hDaNoCut->SetBinContent(j+1,yield);
              hDaNoCut->SetBinError(j+1,yieldErr);
            }
        }
      else
        {
          hDaCut->SetBinContent(i,yield);
          hDaCut->SetBinError(i,yieldErr);
        }
    }

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

  Float_t aDoubleRatio[varbins],aDoubleRatioErr[varbins],aX[varbins],aZero[varbins];
  for(int i=0;i<varbins;i++)
    {
      aDoubleRatio[i] = hDoubleRatio->GetBinContent(i+1);
      aDoubleRatioErr[i] = hDoubleRatio->GetBinError(i+1);
      aX[i] = varmin+i*varstep;
      aZero[i] = 0;
    }
  TGraphErrors* gDoubleRatio = new TGraphErrors(varbins,aX,aDoubleRatio,aZero,aDoubleRatioErr);
  TH2F* hemptyDoubleRatio = new TH2F("hemptyDoubleRatio","",20,varmin-0.5*varstep,varmax+0.5*varstep,10.,0.,2.);
  hemptyDoubleRatio->GetXaxis()->SetTitle(Form("%s",vartex.Data()));
  hemptyDoubleRatio->GetYaxis()->SetTitle("(Yield^{Data}_{Cuts}/Yield^{Data}_{NoCuts})/(Yield^{MC}_{Cuts}/Yield^{MC}_{NoCuts})");
  hemptyDoubleRatio->GetXaxis()->SetTitleOffset(1.);
  hemptyDoubleRatio->GetYaxis()->SetTitleOffset(.9);
  hemptyDoubleRatio->GetXaxis()->SetTitleSize(0.045);
  hemptyDoubleRatio->GetYaxis()->SetTitleSize(0.045);
  hemptyDoubleRatio->GetXaxis()->SetTitleFont(42);
  hemptyDoubleRatio->GetYaxis()->SetTitleFont(42);
  hemptyDoubleRatio->GetXaxis()->SetLabelFont(42);
  hemptyDoubleRatio->GetYaxis()->SetLabelFont(42);
  hemptyDoubleRatio->GetXaxis()->SetLabelSize(0.04);
  hemptyDoubleRatio->GetYaxis()->SetLabelSize(0.04);
  TCanvas* cDoubleRatio = new TCanvas("cDoubleRatio","",600,600);
  hemptyDoubleRatio->Draw();
  gDoubleRatio->Draw("psame");
  cDoubleRatio->SaveAs(Form("plotRatios/%s_%s_DoubleRatio.pdf",collisionsystem.Data(),varname.Data()));

  TFile* outf = new TFile(Form("outfDoubleratio/f%s_%s_DoubleRatio.root",collisionsystem.Data(),varname.Data()),"recreate");
  outf->cd();
  hDoubleRatio->Write();
  outf->Close();
}

TF1* fit(Float_t varval, Float_t ibin, Int_t isMC)
{
  TString tMC;
  if(isMC==1) tMC="MC";
  else tMC="Data";
  TCanvas* c = new TCanvas(Form("c_%s_%.0f",tMC.Data(),ibin),"",600,600);
  TFile* infile = new TFile(Form("%s_%s_%s_%s_%.0f.root",infname.Data(),collisionsystem.Data(),varname.Data(),tMC.Data(),ibin));
  TH1D* h = (TH1D*)infile->Get("h");                    h->SetName(Form("h_%s_%.0f",tMC.Data(),ibin));
  TH1D* hMCSignal = (TH1D*)infile->Get("hMCSignal");    hMCSignal->SetName(Form("hMCSignal_%s_%.0f",tMC.Data(),ibin));
  TH1D* hMCSwapped = (TH1D*)infile->Get("hMCSwapped");  hMCSwapped->SetName(Form("hMCSwapped_%s_%.0f",tMC.Data(),ibin));
  TF1* f = new TF1(Form("f_%s_%.0f",tMC.Data(),ibin),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10]))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);

  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.001,0.05);
  f->SetParLimits(2,0.01,0.1);
  f->SetParLimits(8,0.02,0.2);
  f->SetParLimits(7,0,1);
  f->SetParLimits(9,0,1);
  
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(10,setparam10);
  f->SetParameter(9,setparam9);

  f->FixParameter(8,setparam8);
  f->FixParameter(7,1);
  f->FixParameter(1,fixparam1);
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,0);
  f->FixParameter(6,0);
  h->GetEntries();
  
  hMCSignal->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  hMCSignal->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L m","",minhisto,maxhisto);
  
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L m","",minhisto,maxhisto);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);
  
  h->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"q","",minhisto,maxhisto);
  h->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  //f->ReleaseParameter(2);                                     // you need to release these two parameters if you want to perform studies on the sigma shape
  //f->ReleaseParameter(10);                                   // you need to release these two parameters if you want to perform studies on the sigma shape
  h->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  h->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  h->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L q","",minhisto,maxhisto);
  h->Fit(Form("f_%s_%.0f",tMC.Data(),ibin),"L m","",minhisto,maxhisto);
  
  TF1* background = new TF1(Form("background_%s_%.0f",tMC.Data(),ibin),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(minhisto,maxhisto);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_%s_%.0f",tMC.Data(),ibin),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
  
  TF1* massSwap = new TF1(Form("fmassSwap_%s_%.0f",tMC.Data(),ibin),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);
  
  h->SetXTitle("m_{#piK} (GeV/c^{2})");
  h->SetYTitle("Entries / (5 MeV/c^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
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

  background->Draw("same");   
  mass->SetRange(minhisto,maxhisto);	
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  f->Draw("same");
  
  Double_t yield = mass->Integral(minhisto,maxhisto)/binwidthmass;
  Double_t yieldErr = mass->Integral(minhisto,maxhisto)/binwidthmass*mass->GetParError(0)/mass->GetParameter(0);
  
  std::cout<<"YIELD="<<yield<<std::endl;

  TLegend* leg = new TLegend(0.65,0.58,0.82,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  TLatex Tl;
  Tl.SetNDC();
  Tl.SetTextAlign(12);
  Tl.SetTextSize(0.04);
  Tl.SetTextFont(42);
  Tl.DrawLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  Tl.DrawLatex(0.65,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsystem.Data()));

  TLatex* tex;

  if(ibin>0)
    {
      if(isLarger==1) tex = new TLatex(0.22,0.78,Form("%s > %.3f",vartex.Data(),varval));
      else tex = new TLatex(0.22,0.78,Form("%s < %.3f",vartex.Data(),varval));
    }
  else tex = new TLatex(0.22,0.78,Form("No cut on %s",vartex.Data()));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.22,0.83,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.22,0.73,Form("N_{D} = %.0f #pm %.0f",yield,yieldErr));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  c->SaveAs(Form("plotFits/DMass_%s_%s_%s_%.0f.pdf",collisionsystem.Data(),varname.Data(),tMC.Data(),ibin));
  
  return mass;
}


int main(int argc, char *argv[])
{
  if(argc!=8)
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  else
    {
      fitD(argv[1],argv[2],atoi(argv[3]),atof(argv[4]),atof(argv[5]),argv[6],atoi(argv[7]));
      return 0;
    }
}

