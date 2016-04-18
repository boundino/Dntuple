using namespace std;
#include "uti.h"
#include "parameters.h"

Float_t setparam0=100.;
Float_t setparam1=1.865;
Float_t setparam2=0.03;
Float_t setparam10=0.005;
Float_t setparam8=0.1;
Float_t setparam9=0.1;
Float_t fixparam1=1.865;
Float_t minhisto=1.7;
Float_t maxhisto=2.0;
Float_t nbinsmasshisto=60;
Float_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString collisionsystem;
TString infname;
Float_t centmin,centmax;

void fitDincreasewid(TString collsyst="PbPb", Float_t centMin=0, Float_t centMax=100, TString outputfile="outfMasshisto/mass")
{
  collisionsystem = collsyst;
  infname = outputfile;
  centmin = centMin;
  centmax = centMax;

  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  TF1* fit (Float_t ptmin, Float_t ptmax);
  ofstream fout(Form("outYield/increasewid_%s_cent_%.0f_%.0f.dat",collsyst.Data(),centmin,centmax));
  for(int i=0;i<nBins;i++)
    {
      TF1* f = fit(ptBins[i],ptBins[i+1]);
      Float_t yield = f->Integral(minhisto,maxhisto)/binwidthmass;
      fout<<ptBins[i]<<" "<<ptBins[i+1]<<" "<<yield<<endl;
    }
  fout.close();
}

TF1* fit(Float_t ptmin, Float_t ptmax)
{
  TCanvas* c = new TCanvas(Form("c_%.0f_%.0f",ptmin,ptmax),"",600,600);
  TFile* infile = new TFile(Form("%s_%s_cent_%.0f_%.0f_pt_%.0f_%.0f.root",infname.Data(),collisionsystem.Data(),centmin,centmax,ptmin,ptmax));
  TH1D* h = (TH1D*)infile->Get("h");                    h->SetName(Form("h_%.0f_%.0f",ptmin,ptmax));
  TH1D* hMCSignal = (TH1D*)infile->Get("hMCSignal");    hMCSignal->SetName(Form("hMCSignal_%.0f_%.0f",ptmin,ptmax));
  TH1D* hMCSwapped = (TH1D*)infile->Get("hMCSwapped");  hMCSwapped->SetName(Form("hMCSwapped_%.0f_%.0f",ptmin,ptmax));
  TF1* f = new TF1(Form("f_%.0f_%.0f",ptmin,ptmax),"[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);

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
  f->FixParameter(11,0);
  h->GetEntries();
  
  hMCSignal->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  hMCSignal->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L m q","",minhisto,maxhisto);
  
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L m q","",minhisto,maxhisto);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);
  
  h->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"q","",minhisto,maxhisto);
  h->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.85,1.90);
  f->ReleaseParameter(11);
  f->SetParLimits(11,-1,1);
  h->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  h->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  f->FixParameter(11,f->GetParameter(11)+f->GetParError(11));
  h->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L q","",minhisto,maxhisto);
  h->Fit(Form("f_%.0f_%.0f",ptmin,ptmax),"L m","",minhisto,maxhisto);
  
  TF1* background = new TF1(Form("background_%.0f_%.0f",ptmin,ptmax),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(minhisto,maxhisto);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_%.0f_%.0f",ptmin,ptmax),"[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(11));
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
  
  TF1* massSwap = new TF1(Form("fmassSwap_%.0f_%.0f",ptmin,ptmax),"[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8),f->GetParameter(11));
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
  
  Float_t yield = mass->Integral(minhisto,maxhisto)/binwidthmass;
  Float_t yieldErr = mass->Integral(minhisto,maxhisto)/binwidthmass*mass->GetParError(0)/mass->GetParameter(0);
  
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

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();

  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsystem.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  TLatex* texPt = new TLatex(0.22,0.78,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  texPt->SetNDC();
  texPt->SetTextFont(42);
  texPt->SetTextSize(0.04);
  texPt->SetLineWidth(2);
  texPt->Draw();

  TLatex* texY = new TLatex(0.22,0.83,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.04);
  texY->SetLineWidth(2);
  texY->Draw();

  TLatex* texYield = new TLatex(0.22,0.73,Form("N_{D} = %.0f #pm %.0f",yield,yieldErr));
  texYield->SetNDC();
  texYield->SetTextFont(42);
  texYield->SetTextSize(0.04);
  texYield->SetLineWidth(2);
  texYield->Draw();

  c->SaveAs(Form("plotFits/DMass_increasewid_%s_cent_%.0f_%.0f_pt_%.0f_%.0f.pdf",collisionsystem.Data(),centmin,centmax,ptmin,ptmax));
  
  TCanvas* cPull = new TCanvas(Form("cPull_%.0f_%.0f",ptmin,ptmax),"",600,700);
  TH1D* hPull = (TH1D*)h->Clone("hPull");
  for(int i=0;i<h->GetNbinsX();i++)
    {
      Float_t nfit = f->Integral(h->GetBinLowEdge(i+1),h->GetBinLowEdge(i+1)+h->GetBinWidth(i+1))/h->GetBinWidth(i+1);
      if(h->GetBinError(i+1)==0)
        {
          hPull->SetBinContent(i+1,0.);
        }
      else hPull->SetBinContent(i+1,(h->GetBinContent(i+1)-nfit)/h->GetBinError(i+1));
      hPull->SetBinError(i+1,0);
    }
  hPull->SetMinimum(-4.);
  hPull->SetMaximum(4.);
  hPull->SetYTitle("Pull");
  hPull->GetXaxis()->SetTitleOffset(1.);
  hPull->GetYaxis()->SetTitleOffset(0.65);
  hPull->GetXaxis()->SetLabelOffset(0.007);
  hPull->GetYaxis()->SetLabelOffset(0.007);
  hPull->GetXaxis()->SetTitleSize(0.12);
  hPull->GetYaxis()->SetTitleSize(0.12);
  hPull->GetXaxis()->SetLabelSize(0.1);
  hPull->GetYaxis()->SetLabelSize(0.1);
  hPull->GetYaxis()->SetNdivisions(504);
  TLine* lPull = new TLine(1.7, 0, 2., 0);
  lPull->SetLineWidth(1);
  lPull->SetLineStyle(7);
  lPull->SetLineColor(1);
  TPad* pFit = new TPad("pFit","",0,0.3,1,1);
  pFit->SetBottomMargin(0);
  pFit->Draw();
  pFit->cd();
  h->Draw("e");
  background->Draw("same");   
  mass->Draw("same");
  massSwap->Draw("same");
  f->Draw("same");
  leg->Draw("same");
  texCms->Draw();
  texCol->Draw();
  texPt->Draw();
  texY->Draw();
  texYield->Draw();
  cPull->cd();
  TPad* pPull = new TPad("pPull","",0,0,1,0.3);
  pPull->SetTopMargin(0);
  pPull->SetBottomMargin(0.3);
  pPull->Draw();
  pPull->cd();
  hPull->Draw("p");
  lPull->Draw();
  cPull->cd();
  cPull->SaveAs(Form("plotFits/DMass_increasewid_%s_cent_%.0f_%.0f_pt_%.0f_%.0f_Pull.pdf",collisionsystem.Data(),centmin,centmax,ptmin,ptmax));
  
  return mass;
}


int main(int argc, char *argv[])
{
  if(argc==4)
    {
      fitDincreasewid(argv[1],atof(argv[2]),atof(argv[3]));
      return 0;
    }
  else if(argc==2)
    {
      fitDincreasewid(argv[1]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}
