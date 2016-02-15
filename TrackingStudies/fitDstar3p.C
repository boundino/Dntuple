#include "doubleratioParameter.h"

enum real{MC_MB,Data_MB} isData=MC_MB;
//const int nBins=1;  Float_t ptBins[nBins+1]={7.,9.};
const int nBins=4;  Float_t ptBins[nBins+1]={5.,8.,10.,12.,25.};

void fitDstar3p(Bool_t onlyfit=false, Bool_t genmatchpoint=false)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  void clean0(TH1D* h);  
  TF1* fitDstar(TTree* nt, TTree* ntMC, Float_t ptmin, Float_t ptmax, Bool_t plotgenmatch);

  TFile* infData = new TFile(infnameData3p[isData].Data());
  TFile* infMC = new TFile(infnameMC3p[isData].Data());

  TTree* ntData = (TTree*)infData->Get("ntDD0kpipi");
  TTree* ntMC = (TTree*)infMC->Get("ntDD0kpipi");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  
  ntData->AddFriend("ntHlt");
  if(isData!=Data_MB) ntData->AddFriend("ntHi");
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  ntGen->AddFriend("ntHlt");
  ntGen->AddFriend("ntHi");

  TH1D* hPt = new TH1D("hPt","",nBins,ptBins);
  hPt->Sumw2();
  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  hPtMC->Sumw2();
  TH1D* hPtGen = new TH1D("hPtGen","",nBins,ptBins);
  hPtGen->Sumw2();

  for(int i=0;i<nBins;i++)
    {
      TF1* fData = fitDstar(ntData,ntMC,ptBins[i],ptBins[i+1],genmatchpoint);
      Double_t yieldData = fData->Integral(BINMIN,BINMAX)/BINWID;
      Double_t yieldDataErr = fData->Integral(BINMIN,BINMAX)/BINWID*fData->GetParError(0)/fData->GetParameter(0);      
      hPt->SetBinContent(i+1,yieldData/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldDataErr/(ptBins[i+1]-ptBins[i]));
    }

  if(!onlyfit)
    {
      TCanvas* cPt =  new TCanvas("cPt","",600,600);
      cPt->SetLogy();
      hPt->SetXTitle("D p_{T} (GeV/c)");
      hPt->SetYTitle(Form("%s Uncorrected 3-prong dN(D*)/dp_{T}",texData[isData].Data()));
      hPt->Draw();
      cPt->SaveAs(Form("plots/pp/fitDstar3p/c_%s_Pt.pdf",texData[isData].Data()));

      TH1D* hPtScl = (TH1D*)hPt->Clone("hPtScl");
      hPtScl->Scale(scaleMC3p[isData]);
      TCanvas* cPtScl =  new TCanvas("cPtScl","",600,600);
      cPtScl->SetLogy();
      hPtScl->SetXTitle("D p_{T} (GeV/c)");
      hPtScl->SetYTitle(Form("%s Scaled 3-prong dN(D*)/dp_{T}",texData[isData].Data()));
      hPtScl->Draw();
      cPtScl->SaveAs(Form("plots/pp/fitDstar3p/c_%s_PtScl.pdf",texData[isData].Data()));
      
      ntMC->Project("hPtMC","Dpt",TCut("%s",weightmc[isData].Data())*Form("%s&&%s",selmc3p[isData].Data(),triggerselectionmc[isData].Data()));
      divideBinWidth(hPtMC);
      ntGen->Project("hPtGen","Gpt",TCut("%s",weightmc[isData].Data())*Form("%s&&%s",selgen3p.Data(),triggerselectionmc[isData].Data()));
      divideBinWidth(hPtGen);  
      
      TH1D* hEff = (TH1D*)hPtMC->Clone("hEff");
      hEff->SetTitle(Form(";D p_{T} (GeV/c);%s 3-prong Efficiency",texData[isData].Data()));
      hEff->Divide(hPtGen);
      TCanvas* cEff = new TCanvas("cEff","",600,600);
      hEff->Draw();
      cEff->SaveAs("plots/pp/fitDstar3p/cEff.pdf");
      
      TH1D* hPtCor = (TH1D*)hPt->Clone("hPtCor");
      hPtCor->SetTitle(Form(";D p_{T} (GeV/c);%s Corrected 3-prong dN(D*)/dp_{T}",texData[isData].Data()));
      hPtCor->Divide(hEff);
      TCanvas* cPtCor = new TCanvas("cCor","",600,600);
      cPtCor->SetLogy();
      hPtCor->Draw();
      if(isData==MC_MB)
        {
          hPtGen->SetLineColor(kRed);
          hPtGen->Draw("same hist");
          TLegend* legPtCor = myLegend(0.55,0.70,0.90,0.84);
          legPtCor->AddEntry(hPtCor,"Corrected signal","pl");
          legPtCor->AddEntry(hPtGen,"Generated D*","lf");
          legPtCor->Draw("same");
        }
      cPtCor->SaveAs(Form("plots/pp/fitDstar3p/c_%s_PtCor.pdf",texData[isData].Data()));

      TFile* outputfile = new TFile(Form("outputfiles/output_3p_%s_hPtScl.root",texData[isData].Data()),"recreate");
      outputfile->cd();
      hPt->Write();
      hPtScl->Write();
      hEff->Write();
      hPtCor->Write();
      outputfile->Close();
    }
}

void clean0(TH1D* h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

TF1* fitDstar(TTree* nt, TTree* ntMC, Float_t ptmin, Float_t ptmax, Bool_t plotgenmatch)
{
  TCanvas* c = new TCanvas(Form("c_3p_%.0f_%.0f",ptmin,ptmax),"",600,600);
  TH1D* h = new TH1D(Form("h_3p_%.0f_%.0f",ptmin,ptmax),"",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSignal = new TH1D(Form("hMCSignal_3p_%.0f_%.0f",ptmin,ptmax),"",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSignalplot = new TH1D(Form("hMCSignalplot_3p_%.0f_%.0f",ptmin,ptmax),"",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSwapped = new TH1D(Form("hMCSwapped_3p_%.0f_%.0f",ptmin,ptmax),"",BINNUM,BINMIN,BINMAX);

  TF1* f = new TF1(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"[0]*([4]*([6]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[6])*(Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))+(1-[4])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3]))+[10]*((1-exp((0.13957-x)/[7]))*pow(x/0.13957,[8])+[9]*(x/0.13957-1))",BINMIN,BINMAX);
  nt->Project(Form("h_3p_%.0f_%.0f",ptmin,ptmax),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f)",weightdata[isData].Data(),seldata3p[isData].Data(),triggerselectiondata[isData].Data(),ptmin,ptmax));
  ntMC->Project(Form("hMCSignal_3p_%.0f_%.0f",ptmin,ptmax),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f)",weightmc[isData].Data(),selmc3p[isData].Data(),triggerselectionmc[isData].Data(),ptmin,ptmax));
  ntMC->Project(Form("hMCSwapped_3p_%.0f_%.0f",ptmin,ptmax),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f)",weightmc[isData].Data(),selswp3p[isData].Data(),triggerselectionmc[isData].Data(),ptmin,ptmax));
  for(int ibin=0;ibin<BINNUM;ibin++) hMCSignalplot->SetBinContent(ibin+1,hMCSignal->GetBinContent(ibin+1));
  f->FixParameter(4,1.);
  f->FixParameter(1,0.145491);
  f->FixParameter(10,0.);

  f->SetParLimits(0,0,1.e+5);
  f->SetParLimits(6,0,1.);
  f->SetParLimits(2,1.e-4,1.e-3);
  f->SetParameter(2,2.e-4);
  f->SetParLimits(5,5.e-4,2.e-3);
  f->SetParameter(5,1.e-3);
  hMCSignal->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",BINMIN,BINMAX);
  hMCSignal->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",BINMIN,BINMAX);
  f->ReleaseParameter(1);
  f->SetParLimits(1,minmass,maxmass);
  hMCSignal->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",minmass,maxmass);
  hMCSignal->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",minmass,maxmass);

 
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(5,f->GetParameter(5));
  f->FixParameter(6,f->GetParameter(6));
  f->FixParameter(4,0);
  f->SetParLimits(3,2.e-4,2.e-3);

  hMCSwapped->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"L q","",BINMIN,BINMAX);
  hMCSwapped->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"L q","",BINMIN,BINMAX);

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

  h->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",BINMIN,BINMAX);
  h->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",BINMIN,BINMAX);

  f->ReleaseParameter(1);
  f->SetParLimits(1,minmass,maxmass);
  f->SetParameter(1,f->GetParameter(1));
  h->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",BINMIN,BINMAX);
  h->Fit(Form("f_3p_%.0f_%.0f",ptmin,ptmax),"LL","",BINMIN,BINMAX);

  TF1* background = new TF1(Form("background_3p_%.0f_%.0f",ptmin,ptmax),"[3]*((1-exp((0.13957-x)/[0]))*pow(x/0.13957,[1])+[2]*(x/0.13957-1))");
  background->SetParameters(f->GetParameter(7),f->GetParameter(8),f->GetParameter(9),f->GetParameter(10));
  background->SetRange(BINMIN,BINMAX);
  background->SetLineColor(4);
  background->SetLineWidth(3);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_3p_%.0f_%.0f",ptmin,ptmax),"[0]*([3]*([5]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[5])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4])))");
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
  
  TF1* massSwap = new TF1(Form("fmassSwap_3p_%.0f_%.0f",ptmin,ptmax),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
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

  if(plotgenmatch&&(isData==MC_MB))
    {
      hMCSignalplot->SetMarkerSize(0.8);
      hMCSignalplot->SetMarkerColor(kMagenta+2);
      hMCSignalplot->Draw("psame");
    }

  Double_t yield = mass->Integral(BINMIN,BINMAX)/BINWID;
  Double_t yieldErr = mass->Integral(BINMIN,BINMAX)/BINWID*mass->GetParError(0)/mass->GetParameter(0);
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
  tex = new TLatex(0.20,0.84,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();

  c->SaveAs(Form("plots/pp/fitDstar3p/DMass_%s_%.0f_%.0f.pdf",texData[isData].Data(),ptmin,ptmax));

  return mass;
}
