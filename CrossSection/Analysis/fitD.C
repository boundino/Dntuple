#include "uti.h"
#include "fitD.h"

Double_t luminosity=150.;
Double_t BRchain=0.0388;

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;

TString inputdata="/export/d00/scratch/jwang/Dmeson/ntD_20150916_MC_merge_withoutweight.root";
TString inputmc="/export/d00/scratch/jwang/Dmeson/ntD_20150916_MC_merge_withoutweight.root";
//TString inputdata="/mnt/hadoop/cms/store/user/ginnocen/Dntuple/nt_DfinderData_HIMinBiasUPC_HIRun2011-14Mar2014-v2_20150912_alpha0p15_lxyz2p5_eta1p1_pt1_filtered_20150915.root";
//TString inputdata="/afs/cern.ch/work/g/ginnocen/public/FilesDmeson/Dntuple/nt_DfinderData_HIMinBiasUPC_HIRun2011-14Mar2014-v2_20150912_alpha0p15_lxyz2p5_eta1p1_pt1_ptfiltered.root";
//TString inputmc="/afs/cern.ch/work/g/ginnocen/public/FilesDmeson/Dntuple/ntD_20150914_DinderMC_Pyquen_D0tokaonpion_D0pt1p0_PthatAll_TuneZ2_Unquenched_2760GeV_20150912_EvtBase_alpha0p15.root";
TString weight = "1";

const int nBins=1;  Int_t binsIndex=0;  Double_t ptBins[nBins+1]={3.5,40};
//const int nBins=10; Int_t binsIndex=1;  Double_t ptBins[nBins+1]={3.5,4.5,5.5,7,9,11,13,16,20,28,40};

TString cut = cuts[binsIndex];
TString seldata = Form("%s",cut.Data());
TString selmc = seldata;
TString selmcgen = "GisSignal==1||GisSignal==2&&Gy>-1.&&Gy>1.";

void fitD(TString infname="", TString label="", Bool_t doweight=true)
{
  void clean0 (TH1D* h);
  TF1* fit (TTree* nt, TTree* ntMC, double ptmin, double ptmax);

  if(!doweight) weight="1";
  if(infname=="") infname=inputdata.Data();
  TFile* inf = new TFile(infname.Data());
  TFile* infMC = new TFile(inputmc.Data());

  TTree* nt = (TTree*) inf->Get("ntDkpi");
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  ntGen->AddFriend(ntMC);

  TH1D* hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D* hPtRecoTruth = new TH1D("hPtRecoTruth","",nBins,ptBins);
  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D* hPtGen = new TH1D("hPtGen","",nBins,ptBins);

  for(int i=0;i<nBins;i++)
    {
      TF1* f = fit(nt,ntMC,ptBins[i],ptBins[i+1]);
      double yield = f->Integral(1.7,2.0)/0.005;
      double yieldErr = f->Integral(1.7,2.0)/0.005*f->GetParError(0)/f->GetParameter(0);
      hPt->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
    }  

  ntMC->Project("hPtMC","Dpt",TCut(weight)*(TCut(selmc.Data())&&"Dgen==23333"));
  divideBinWidth(hPtMC);
  ntMC->Project("hPtRecoTruth","Dpt",TCut(seldata.Data())&&"Dgen==23333");
  divideBinWidth(hPtRecoTruth);
  ntGen->Project("hPtGen","Gpt",TCut(weight)*(TCut(selmcgen.Data())));
  divideBinWidth(hPtGen);

  TCanvas* cPt =  new TCanvas("cPt","",600,600);
  cPt->SetLogy();
  hPt->SetXTitle("D^{0} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected dN(D^{0})/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();
  hPtMC->Draw("same hist");
  TLegend* legPt = myLegend(0.55,0.80,0.90,0.94);
  legPt->AddEntry(hPt,"Signal extraction","pl");
  legPt->AddEntry(hPtMC,"Matched reco","lf");
  legPt->Draw("same");  

  hPtMC->Sumw2();
  TH1D* hEff = (TH1D*)hPtMC->Clone("hEff");
  hEff->SetTitle(";D^{0} p_{T} (GeV/c);Efficiency");
  hEff->Sumw2();
  hEff->Divide(hPtGen);
  TCanvas* cEff = new TCanvas("cEff","",600,600);
  hEff->Draw();
  
  TH1D* hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->SetTitle(";D^{0} p_{T} (GeV/c);Corrected dN(D^{0})/dp_{T}");
  hPtCor->Divide(hEff);
  TCanvas* cPtCor=  new TCanvas("cCorResult","",600,600);
  cPtCor->SetLogy();
  hPtCor->Draw();
  hPtGen->Draw("same hist");
  TLegend* legPtCor = myLegend(0.55,0.80,0.90,0.94);
  legPtCor->AddEntry(hPtCor,"Corrected signal","pl");
  legPtCor->AddEntry(hPtGen,"Generated D^{0}","lf");
  legPtCor->Draw("same");  

  TH1D* hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  hPtSigma->SetTitle(";D^{0} p_{T} (GeV/c);d#sigma(D^{0})/dp_{T}");
  hPtSigma->Scale(1./(2*luminosity*BRchain));
  TCanvas* cPtSigma=  new TCanvas("cPtSigma","",600,600);
  cPtSigma->SetLogy();
  hPtSigma->Draw();

  TFile* outf = new TFile(Form("../ResultsMIT/alphaD0%s.root",label.Data()),"recreate");
  outf->cd();
  hPt->Write();
  hEff->Write();
  hPtGen->Write();
  hPtMC->Write();
  hPtCor->Write();
  hPtSigma->Write();
  outf->Close();
  delete outf;

}

void clean0(TH1D* h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

TF1* fit(TTree* nt, TTree* ntMC, Double_t ptmin, Double_t ptmax)
{
  static int count=0;
  count++;

  TCanvas* c= new TCanvas(Form("c%d",count),"",600,600);
  TH1D* h = new TH1D(Form("h-%d",count),"",60,1.7,2.0);
  TH1D* hMCSignal = new TH1D(Form("hMCSignal-%d",count),"",60,1.7,2.0);
  TH1D* hMCSwapped = new TH1D(Form("hMCSwapped-%d",count),"",60,1.7,2.0);
  
  TF1* f = new TF1(Form("f%d",count),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10]))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
  
  nt->Project(Form("h-%d",count),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f)",weight.Data(),seldata.Data(),ptmin,ptmax));   
  ntMC->Project(Form("hMCSignal-%d",count),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23333))",weight.Data(),seldata.Data(),ptmin,ptmax));   
  ntMC->Project(Form("hMCSwapped-%d",count),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23344))",weight.Data(),seldata.Data(),ptmin,ptmax));   

  clean0(h);
  h->SetMaximum(h->GetMaximum()*1.20);
  h->Draw();
  
  // Extract Signal PDF
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
  
  hMCSignal->Fit(Form("f%d",count),"q","",1.7,2.0);
  hMCSignal->Fit(Form("f%d",count),"q","",1.7,2.0);
  f->ReleaseParameter(1);
  hMCSignal->Fit(Form("f%d",count),"L q","",1.7,2.0);
  hMCSignal->Fit(Form("f%d",count),"L q","",1.7,2.0);
  hMCSignal->Fit(Form("f%d",count),"L m","",1.7,2.0);
  
  // Extract k-pi Swapped PDF
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);
  hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);
  hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);
  hMCSwapped->Fit(Form("f%d",count),"L m","",1.7,2.0);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);
  
  // Fit on data
  h->Fit(Form("f%d",count),"q","",1.7,2.0);
  h->Fit(Form("f%d",count),"q","",1.7,2.0);
  f->ReleaseParameter(1);
  h->Fit(Form("f%d",count),"L q","",1.7,2.0);
  h->Fit(Form("f%d",count),"L q","",1.7,2.0);
  h->Fit(Form("f%d",count),"L q","",1.7,2.0);
  h->Fit(Form("f%d",count),"L m","",1.7,2.0);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  
  // function for background shape plotting. take the fit result from f
  TF1* background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(1.7,2.0);
  background->SetLineStyle(2);
  
  // function for signal shape plotting. take the fit result from f
  TF1* mass = new TF1(Form("fmass%d",count),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetLineColor(2);
  mass->SetLineStyle(2);
  
  TF1* massSwap = new TF1(Form("fmassSwap%d",count),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetLineColor(2);
  massSwap->SetLineStyle(2);
  
  h->SetMarkerStyle(24);
  h->SetStats(0);
  h->Draw("e");
  h->SetXTitle("M_{D} (GeV/c^{2})");
  h->SetYTitle("Entries / (5 MeV/c^{2})");
  h->GetXaxis()->CenterTitle	();
  h->GetYaxis()->CenterTitle();
  h->SetTitleOffset(1.,"Y");
  h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
  
  background->Draw("same");   
  mass->SetRange(1.7,2.0);	
  mass->Draw("same");
  mass->SetLineStyle(2);
  mass->SetFillStyle(3004);
  mass->SetFillColor(2);
  massSwap->SetRange(1.7,2.0);
  massSwap->SetLineStyle(4);
  massSwap->SetLineColor(kGreen+2);
  massSwap->SetFillStyle(3005);
  massSwap->SetFillColor(kGreen+2);
  massSwap->Draw("same");
  f->Draw("same");
  
  Double_t yield = mass->Integral(1.7,2.0)/0.005;
  Double_t yieldErr = mass->Integral(1.7,2.0)/0.005*mass->GetParError(0)/mass->GetParameter(0);
  
  // Draw the legend:)   
  TLegend* leg = myLegend(0.20,0.60,0.53,0.94);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry((TObject*)0,"CMS Preliminary","");
  leg->AddEntry((TObject*)0,"PbPb #sqrt{s_{NN}}= 2.76 TeV","");
  leg->AddEntry((TObject*)0,Form("%.1f<p_{T}^{D}<%.1f GeV/c",ptmin,ptmax),"");
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial Background","l");
  leg->Draw();
  TLegend* leg2 = myLegend(0.45,0.80,0.90,0.94);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(h,"D meson","");
  leg2->AddEntry(h,Form("M_{D}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
  leg2->AddEntry(h,Form("N_{D}=%.0f #pm %.0f", yield, yieldErr),"");
  leg2->Draw();
  
  if(nBins==1) c->SaveAs("../ResultsMIT/DMass-inclusive.pdf");
  else c->SaveAs(Form("../ResultsMIT/DMass-%d.pdf",count));
  
  return mass;
}
