#include "doubleratioParameter.h"

enum real{MC,Data,MC_MB,Data_MB} isData=Data;
const int nBins=5;  Double_t ptBins[nBins+1]={15.,20.,25.,30.,35.,50.};

TString outputfilename = Form("outputfiles/outputfile%s.root",texData[isData].Data());
void studydoubleratio(Bool_t doweight=true)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  void clean0 (TH1D* h);  
  TF1* fitDstar3prongs (TTree* nt, TTree* ntMC, Double_t ptmin, Double_t ptmax);
  TF1* fitDstar5prongs (TTree* nt, Double_t ptmin, Double_t ptmax);

  TFile* infData3prong = new TFile(infnameData3p[isData].Data());
  TFile* infData5prong = new TFile(infnameData5p[isData].Data());
  TFile* infMC3prong = new TFile(infnameMC3p[isData].Data());
  TFile* infMC5prong = new TFile(infnameMC5p[isData].Data());

  TTree* ntData3prong = (TTree*)infData3prong->Get("ntDD0kpipi");
  TTree* ntData5prong = (TTree*)infData5prong->Get("ntDD0kpipipipi");
  TTree* ntMC3prong = (TTree*)infMC3prong->Get("ntDD0kpipi");
  TTree* ntMC5prong = (TTree*)infMC5prong->Get("ntDD0kpipipipi");
  TTree* ntGen3prong = (TTree*)infMC3prong->Get("ntGen");
  TTree* ntGen5prong = (TTree*)infMC5prong->Get("ntGen");
  
  TTree* HltTreeData3prong = (TTree*)infData3prong->Get("ntHlt");
  TTree* HltTreeData5prong = (TTree*)infData5prong->Get("ntHlt");
  ntData3prong->AddFriend(HltTreeData3prong);
  ntData5prong->AddFriend(HltTreeData5prong);
  TTree* HltTreeMC3prong = (TTree*)infMC3prong->Get("ntHlt");
  TTree* HltTreeMC5prong = (TTree*)infMC5prong->Get("ntHlt");
  ntMC3prong->AddFriend(HltTreeMC3prong);
  ntMC5prong->AddFriend(HltTreeMC5prong);
  ntGen3prong->AddFriend(HltTreeMC3prong);
  ntGen5prong->AddFriend(HltTreeMC5prong);

  TH1D* hPt3prong = new TH1D("hPt3prong","",nBins,ptBins);
  TH1D* hPt5prong = new TH1D("hPt5prong","",nBins,ptBins);  
  hPt3prong->Sumw2();
  hPt5prong->Sumw2();
  TH1D* hPtMC3prong = new TH1D("hPtMC3prong","",nBins,ptBins);
  TH1D* hPtMC5prong = new TH1D("hPtMC5prong","",nBins,ptBins);
  hPtMC3prong->Sumw2();
  hPtMC5prong->Sumw2();
  TH1D* hPtGen3prong = new TH1D("hPtGen3prong","",nBins,ptBins);
  TH1D* hPtGen5prong = new TH1D("hPtGen5prong","",nBins,ptBins);
  hPtGen3prong->Sumw2();
  hPtGen5prong->Sumw2();

  for(int i=0;i<nBins;i++)
    {
      TF1* fData3prong = fitDstar3prongs(ntData3prong,ntMC3prong, ptBins[i],ptBins[i+1]);
      TF1* fData5prong = fitDstar5prongs(ntData5prong,ptBins[i],ptBins[i+1]);
      Double_t yieldData3prong = fData3prong->Integral(minmass3prong,maxmass3prong)/binwidth3prong;
      Double_t yieldData3prongErr = fData3prong->Integral(minmass3prong,maxmass3prong)/binwidth3prong*fData3prong->GetParError(0)/fData3prong->GetParameter(0);
      Double_t yieldData5prong = fData5prong->Integral(minmass5prong,maxmass5prong)/binwidth5prong;
      Double_t yieldData5prongErr = fData5prong->Integral(minmass5prong,maxmass5prong)/binwidth5prong*fData5prong->GetParError(0)/fData5prong->GetParameter(0);
      
      hPt3prong->SetBinContent(i+1,yieldData3prong/(ptBins[i+1]-ptBins[i]));
      hPt3prong->SetBinError(i+1,yieldData3prongErr/(ptBins[i+1]-ptBins[i]));
      hPt5prong->SetBinContent(i+1,yieldData5prong/(ptBins[i+1]-ptBins[i]));
      hPt5prong->SetBinError(i+1,yieldData5prongErr/(ptBins[i+1]-ptBins[i]));
    }
  ntMC3prong->Project("hPtMC3prong","Dpt",Form("%s&&%s",selmc3p.Data(),triggerselection[isData].Data()));
  divideBinWidth(hPtMC3prong);
  ntGen3prong->Project("hPtGen3prong","Gpt",Form("%s&&%s",selgen3p.Data(),triggerselection[isData].Data()));
  divideBinWidth(hPtGen3prong);  
  ntMC5prong->Project("hPtMC5prong","Dpt",Form("%s&&%s",selmc5p.Data(),triggerselection[isData].Data()));
  divideBinWidth(hPtMC5prong);
  ntGen5prong->Project("hPtGen5prong","Gpt",Form("%s&&%s",selgen5p.Data(),triggerselection[isData].Data()));
  divideBinWidth(hPtGen5prong);  

  TCanvas* cPt3prong =  new TCanvas("cPt3prong","",600,600);
  cPt3prong->SetLogy();
  hPt3prong->SetXTitle("D p_{T} (GeV/c)");
  hPt3prong->SetYTitle(Form("%s Uncorrected 3-prong N(D*)/dp_{T}",texData[isData].Data()));
  hPt3prong->Draw();
  cPt3prong->SaveAs(Form("plots/pp/c_%s_Pt3prong.pdf",texData[isData].Data()));
  hPt3prong->Scale(scaleMC3p[isData]);
  TCanvas* cPt5prong =  new TCanvas("cPt5prong","",600,600);
  cPt5prong->SetLogy();
  hPt5prong->SetXTitle("D p_{T} (GeV/c)");
  hPt5prong->SetYTitle(Form("%s Uncorrected 5-prong N(D*)/dp_{T}",texData[isData].Data()));
  hPt5prong->Draw();
  cPt5prong->SaveAs(Form("plots/pp/c_%s_Pt5prong.pdf",texData[isData].Data()));
  hPt5prong->Scale(scaleMC5p[isData]);
  TH1D* hRatio = (TH1D*)hPt5prong->Clone("hRatio");
  hRatio->SetTitle(Form(";D p_{T} (GeV/c);%s Raw dN(D*)/dp_{T} 5/3 prong Ratio",texData[isData].Data()));
  hRatio->Divide(hPt3prong);
  TCanvas* cRatio = new TCanvas("cRatio","",600,600);
  hRatio->Draw();
  cRatio->SaveAs(Form("plots/pp/c_%s_Ratio.pdf",texData[isData].Data()));

  TH1D* hEff3prong = (TH1D*)hPtMC3prong->Clone("hEff3prong");
  hEff3prong->SetTitle(Form(";D p_{T} (GeV/c);%s 3-prong Efficiency",texData[isData].Data()));
  hEff3prong->Divide(hPtGen3prong);
  TCanvas* cEff3prong = new TCanvas("cEff3prong","",600,600);
  hEff3prong->Draw();
  cEff3prong->SaveAs("plots/pp/cEff3prong.pdf");
  TH1D* hEff5prong = (TH1D*)hPtMC5prong->Clone("hEff5prong");
  hEff5prong->SetTitle(Form(";D p_{T} (GeV/c);%s 5-prong Efficiency",texData[isData].Data()));
  hEff5prong->Divide(hPtGen5prong);
  TCanvas* cEff5prong = new TCanvas("cEff5prong","",600,600);
  hEff5prong->Draw();
  cEff5prong->SaveAs("plots/pp/cEff5prong.pdf");
  
  TH1D* hPtCor3prong = (TH1D*)hPt3prong->Clone("hPtCor3prong");
  hPtCor3prong->SetTitle(Form(";D p_{T} (GeV/c);%s Corrected 3-prong dN(D*)/dp_{T}",texData[isData].Data()));
  hPtCor3prong->Divide(hEff3prong);
  TCanvas* cPtCor3prong = new TCanvas("cCor3prong","",600,600);
  cPtCor3prong->SetLogy();
  hPtCor3prong->Draw();
  if(isData==0||isData==2)
    {
      hPtGen3prong->SetLineColor(kRed);
      hPtGen3prong->Draw("same hist");
      TLegend* legPtCor3prong = myLegend(0.55,0.70,0.90,0.84);
      legPtCor3prong->AddEntry(hPtCor3prong,"Corrected signal","pl");
      legPtCor3prong->AddEntry(hPtGen3prong,"Generated D*","lf");
      legPtCor3prong->Draw("same");
    }
  cPtCor3prong->SaveAs(Form("plots/pp/c_%s_PtCor3prong.pdf",texData[isData].Data()));
  TH1D* hPtCor5prong = (TH1D*)hPt5prong->Clone("hPtCor3prong");
  hPtCor5prong->SetTitle(Form(";D p_{T} (GeV/c);%s Corrected 5-prong dN(D*)/dp_{T}",texData[isData].Data()));
  hPtCor5prong->Divide(hEff5prong);
  TCanvas* cPtCor5prong = new TCanvas("cCor5prong","",600,600);
  cPtCor5prong->SetLogy();
  hPtCor5prong->SetMinimum(hPtGen5prong->GetMinimum()*0.1);
  hPtCor5prong->Draw();
  if(isData==0||isData==2)
    {
      hPtGen5prong->SetLineColor(kRed);
      hPtGen5prong->Draw("same hist");
      TLegend* legPtCor5prong = myLegend(0.55,0.70,0.90,0.84);
      legPtCor5prong->AddEntry(hPtCor5prong,"Corrected signal","pl");
      legPtCor5prong->AddEntry(hPtGen5prong,"Generated D*","lf");
      legPtCor5prong->Draw("same");
    }
  cPtCor5prong->SaveAs(Form("plots/pp/c_%s_PtCor5prong.pdf",texData[isData].Data()));
  TH1D* hRatioCor = (TH1D*)hPtCor5prong->Clone("hRatioCor");
  hRatioCor->SetTitle(Form(";D p_{T} (GeV/c);%s Corrected dN(D*)/dp_{T} 5/3 prong Ratio",texData[isData].Data()));
  hRatioCor->Divide(hPtCor3prong);
  TCanvas* cRatioCor = new TCanvas("cRatioCor","",600,600);
  hRatioCor->Draw();
  cRatioCor->SaveAs(Form("plots/pp/c_%s_RatioCor.pdf",texData[isData].Data()));

  TFile *outputfile=new TFile(outputfilename.Data(),"recreate");
  outputfile->cd();
  hPt3prong->Write();
  hPt5prong->Write();
  hRatio->Write();
  outputfile->Close();
}

void clean0(TH1D* h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

TF1* fitDstar3prongs(TTree* nt, TTree* ntMC, Double_t ptmin, Double_t ptmax)
{
  static int count3p=0;
  count3p++;
  
  TCanvas* c = new TCanvas(Form("c_3p_%d",count3p),"",600,600);
  TH1D* h = new TH1D(Form("h_3p_%d",count3p),"",60,0.14,0.16);
  TH1D* hMCSignal = new TH1D(Form("hMCSignal_3p_%d",count3p),"",60,0.14,0.16);
  TH1D* hMCSwapped = new TH1D(Form("hMCSwapped_3p_%d",count3p),"",60,0.14,0.16);

  TF1* f = new TF1(Form("f_3p_%d",count3p),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*([12]*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10])+(1-[12])*Gaus(x,[1],[13])/(sqrt(2*3.14159)*[13])))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x+[11]*x*x*x*x",0.14,0.16);
  f->SetLineColor(kRed);
  nt->Project(Form("h_3p_%d",count3p),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f)",weight.Data(),seldata3p.Data(),triggerselection[isData].Data(),ptmin,ptmax));
  ntMC->Project(Form("hMCSignal_3p_%d",count3p),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f&&(Dgen==23333))",weight.Data(),selmc3p.Data(),triggerselection[isData].Data(),ptmin,ptmax));
  ntMC->Project(Form("hMCSwapped_3p_%d",count3p),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f&&(Dgen==23344))",weight.Data(),selswp3p.Data(),triggerselection[isData].Data(),ptmin,ptmax));

  f->FixParameter(7,1.);
  f->FixParameter(1,0.145491);
  f->FixParameter(2,2.e-3);
  f->FixParameter(10,5.e-4);
  f->FixParameter(13,1.e-4);
  f->FixParameter(3,0.);
  f->FixParameter(4,0.);
  f->FixParameter(5,0.);
  f->FixParameter(6,0.);
  f->FixParameter(11,0.);

  f->SetParLimits(9,0,1);
  f->SetParLimits(12,0,1);
  f->SetParLimits(0,0,1000000);
  hMCSignal->Fit(Form("f_3p_%d",count3p),"LL");
  hMCSignal->Fit(Form("f_3p_%d",count3p),"LL");
  hMCSignal->Fit(Form("f_3p_%d",count3p),"LL","",0.142,0.155);
  f->ReleaseParameter(1);
  f->ReleaseParameter(2);
  f->ReleaseParameter(10);
  f->ReleaseParameter(13);
  f->SetParLimits(1,0.144,0.147);
  if(isData==0||isData==2) f->SetParLimits(2,5.e-4,5.e-3);
  else f->SetParLimits(2,5.e-4,7.e-3);
  f->SetParLimits(10,1.e-4,2.e-3);
  if(isData==0||isData==2) f->SetParLimits(13,5.e-5,3.e-4);
  else if(ptmin>20) f->SetParLimits(13,5.e-5,4.e-4);
  else f->SetParLimits(13,5.e-5,5.e-4);
  hMCSignal->Fit(Form("f_3p_%d",count3p),"LL","",0.143,0.147);
  hMCSignal->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);
  hMCSignal->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);

  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(13,f->GetParameter(13));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(12,f->GetParameter(12));
  f->FixParameter(7,0);
  f->SetParLimits(8,2.e-4,2.e-3);

  hMCSwapped->Fit(Form("f_3p_%d",count3p),"L q","",0.14,0.16);
  hMCSwapped->Fit(Form("f_3p_%d",count3p),"L q","",0.14,0.16);

  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);
  f->ReleaseParameter(11);
  h->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);
  h->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);
  f->ReleaseParameter(1);
  h->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);
  h->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);
  h->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);
  h->Fit(Form("f_3p_%d",count3p),"LL","",0.14,0.16);

  TF1* background = new TF1(Form("background_3p_%d",count3p),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetParameter(4,f->GetParameter(11));
  background->SetLineColor(4);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_3p_%d",count3p),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*([6]*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])+(1-[6])*Gaus(x,[1],[7])/(sqrt(2*3.14159)*[7]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(12),f->GetParameter(13));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetParError(6,f->GetParError(12));
  mass->SetParError(7,f->GetParError(13));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
  
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

  background->Draw("same");   
  mass->SetRange(0.142,0.152);	
  mass->Draw("same");
  f->Draw("same");

  Double_t yield = mass->Integral(0.14,0.16)/binwidth3prong;
  Double_t yieldErr = mass->Integral(0.14,0.16)/binwidth3prong*mass->GetParError(0)/mass->GetParameter(0);

  TLatex* tex;
  TLegend* leg = new TLegend(0.60,0.62,0.85,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry((TObject*)0,"D* D^{0}(K#pi)#pi",NULL);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D*^{+}+D*^{-} Signal","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  tex = new TLatex(0.61,0.58,Form("N_{D} = %.0f #pm %.0f",yield,yieldErr));
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

  c->SaveAs(Form("plots/pp/DMass_%s_3prongs-%d.pdf",texData[isData].Data(),count3p));
  
  return mass;
}


TF1* fitDstar5prongs(TTree* nt, Double_t ptmin, Double_t ptmax)
{
  static int count5p=0;
  count5p++;
  
  TCanvas* c = new TCanvas(Form("c_5p_%d",count5p),"",600,600);
  TH1D* h = new TH1D(Form("h_5p_%d",count5p),"",60,0.140,0.160);
  TF1* f = new TF1(Form("f_5p_%d",count5p),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*((1-[8])*TMath::Gaus(x,[6],[7])/(sqrt(2*3.14159)*[7])+[8]*TMath::Gaus(x,[6],[9])/(sqrt(2*3.14159)*[9]))",minmass3prong,maxmass3prong);
  nt->Project(Form("h_5p_%d",count5p),"Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f&&Dpt<%f)",weight.Data(),seldata5p.Data(),triggerselection[isData].Data(),ptmin,ptmax));   
    
  f->SetLineColor(4);
  f->SetParameters(0,0,0,0,0,2e2,1.45491e-1,9e-4,0.1,8e-4);
  f->FixParameter(9,15e-4);
  f->FixParameter(6,0.145491);
  f->FixParameter(7,8e-4);
  f->SetParLimits(8,0,1);
  f->SetParLimits(5,0,100000);
  h->Fit(Form("f_5p_%d",count5p),"LL");
  h->Fit(Form("f_5p_%d",count5p),"LL");
  h->Fit(Form("f_5p_%d",count5p),"LL","",minmass3prong,maxmass3prong);
  f->ReleaseParameter(6);
  f->ReleaseParameter(7);
  f->ReleaseParameter(9);
  f->SetParLimits(6,0.144,0.147);
  f->SetParLimits(7,1e-4,9e-4);
  f->SetParLimits(9,1e-4,9e-4);
  h->Fit(Form("f_5p_%d",count5p),"LL","",0.142,0.148);
  h->Fit(Form("f_5p_%d",count5p),"LL","",0.142,0.16);
  h->Fit(Form("f_5p_%d",count5p),"LL","",0.142,0.16);
  h->Fit(Form("f_5p_%d",count5p),"LL","",0.141,0.16);
  h->Fit(Form("f_5p_%d",count5p),"LL","",0.141,0.16);
  h->Fit(Form("f_5p_%d",count5p),"LL","",0.141,0.16);

  TF1* background = new TF1(Form("background_5p_%d",count5p),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
  background->SetParameter(0,f->GetParameter(0));
  background->SetParameter(1,f->GetParameter(1));
  background->SetParameter(2,f->GetParameter(2));
  background->SetParameter(3,f->GetParameter(3));
  background->SetParameter(4,f->GetParameter(4));
  background->SetLineColor(4);
  background->SetRange(minmass3prong,maxmass3prong);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_5p_%d",count5p),"[0]*((1-[3])*TMath::Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+[3]*TMath::Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))");
  mass->SetParameters(f->GetParameter(5),f->GetParameter(6),f->GetParameter(7),f->GetParameter(8),f->GetParameter(9));
  mass->SetParError(0,f->GetParError(5));
  mass->SetParError(1,f->GetParError(6));
  mass->SetParError(2,f->GetParError(7));
  mass->SetParError(3,f->GetParError(8));
  mass->SetParError(4,f->GetParError(9));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
    
  h->SetXTitle("M_{K#pi#pi#pi#pi}-M_{K#pi#pi#pi} (GeV/c^{2})");
  h->SetYTitle("Entries / (1/3 MeV/c^{2})");
  h->SetStats(0);
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
  mass->SetRange(0.142,0.152);	
  mass->Draw("same");
  f->Draw("same");
  
  Double_t yield = mass->Integral(minmass5prong,maxmass5prong)/binwidth5prong;
  Double_t yieldErr = mass->Integral(minmass5prong,maxmass5prong)/binwidth5prong*mass->GetParError(0)/mass->GetParameter(0);

  TLatex* tex;
  TLegend* leg = new TLegend(0.60,0.62,0.85,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry((TObject*)0,"D* D^{0}(K#pi#pi#pi)#pi",NULL);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D*^{+}+D*^{-} Signal","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  tex = new TLatex(0.61,0.58,Form("N_{D} = %.0f #pm %.0f",yield,yieldErr));
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

  c->SaveAs(Form("plots/pp/DMass_%s_5prongs-%d.pdf",texData[isData].Data(),count5p));
  
  return mass;
}
