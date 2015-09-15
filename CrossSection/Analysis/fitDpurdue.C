#include "utilities.h"
#include "fitD.h"

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=1.865;
double setparam2=0.0109;
double setparam3=0.1;
double fixparam1=1.865;

TString inputdata="/export/d00/scratch/jwang/Dmeson/Dmesonana_hiforest_PbPbD0tokaonpion_Pthat0153050_D0pt1p0_tkpt1p0eta1p1_2760GeV_0803_d2p0_alpha0p2_prob0p05.root";
TString inputmc="/export/d00/scratch/jwang/Dmeson/Dmesonana_hiforest_PbPbD0tokaonpion_Pthat0153050_D0pt1p0_tkpt1p0eta1p1_2760GeV_0803_d2p0_alpha0p2_prob0p05.root";

const int nBins=1;  Int_t cutIndex=0;  Double_t ptBins[nBins+1]={3.5,40};
//const int nBins=10; Int_t cutIndex=1;  Double_t ptBins[nBins+1]={3.5,4.5,5.5,7,9,11,13,16,20,28,40};

TString cut = cutspurdue[cutIndex];
TString seldata = Form("%s",cut.Data());
TString selmc = seldata;
TString selmcgen="(Dgen==23333||Dgen==23344)";

TString weight = "1";

void clean0(TH1D *h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

TF1* fit(TTree *nt, TTree *ntMC, double ptmin, double ptmax)
{
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",60,1.7,2.0);
   TH1D *hMCSignal = new TH1D(Form("hMCSignal%d",count),"",60,1.7,2.0);
   TH1D *hMCSwapped = new TH1D(Form("hMCSwapped%d",count),"",60,1.7,2.0);

   TF1 *f = new TF1(Form("f%d",count),"[0]*([7]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
   
   // Projection for data  
   nt->Project(Form("h%d",count),"dcandmass",Form("%s*(%s&&dcandpt>%f&&dcandpt<%f)",weight.Data(),seldata.Data(),ptmin,ptmax));   

   // Projection for signal
   ntMC->Project(Form("hMCSignal%d",count),"dcandmass",Form("%s*(%s&&dcandpt>%f&&dcandpt<%f&&(matchedtogen&&nongendoublecounted))",weight.Data(),seldata.Data(),ptmin,ptmax));   

   cout<<"== nCand: "<<h->GetEntries()<<endl;

   clean0(h);
   h->Draw();
   
   // Extract Signal PDF
   f->SetParLimits(4,-1000,1000);
   f->SetParLimits(2,0.005,0.2);
   f->SetParLimits(8,0.02,0.2);
   f->SetParLimits(7,0,0);

   f->SetParameter(0,setparam0);
   f->SetParameter(1,setparam1);
   f->SetParameter(2,setparam2);
   f->FixParameter(8,setparam3);
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
   hMCSignal->Fit(Form("f%d",count),"L q","",1.7,2.0);

   // Extract k-pi Swapped PDF
   f->FixParameter(1,f->GetParameter(1));
   f->FixParameter(2,f->GetParameter(2));
   f->FixParameter(7,0);
   f->SetParameter(8,setparam3);
   f->ReleaseParameter(8);
//   f->FixParameter(8,f->GetParameter(8));

   hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);
   hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);
   hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);
   hMCSwapped->Fit(Form("f%d",count),"L q","",1.7,2.0);

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
   cout <<h->GetEntries()<<endl;

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetParameter(2,f->GetParameter(5));
   background->SetParameter(3,f->GetParameter(6));
   background->SetLineColor(4);
   background->SetRange(1.7,2.0);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass",count),"[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2]))");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetParError(7,f->GetParError(7));
   mass->SetParError(8,f->GetParError(8));
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

   TF1 *mass2 = new TF1(Form("fmass2",count),"[0]*(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4])");
   mass2->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
   mass2->SetParError(0,f->GetParError(0));
   mass2->SetParError(1,f->GetParError(1));
   mass2->SetParError(2,f->GetParError(2));
   mass2->SetParError(7,f->GetParError(7));
   mass2->SetParError(8,f->GetParError(8));
   mass2->SetLineColor(2);
   mass2->SetLineStyle(2);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
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
   mass2->SetRange(1.7,2.0);
   mass2->SetLineStyle(4);
   mass2->SetLineColor(kGreen+2);
   mass2->SetFillStyle(3005);
   mass2->SetFillColor(kGreen+2);
   mass2->Draw("same");
   f->Draw("same");

   double yield = mass->Integral(1.7,2.0)/0.005;
   double yieldErr = mass->Integral(1.7,2.0)/0.005*mass->GetParError(0)/mass->GetParameter(0);


   // Draw the legend:)   
   TLegend *leg = myLegend(0.20,0.5,0.56,0.93);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"PbPb #sqrt{s_{NN}}= 2.76 TeV","");
   leg->AddEntry(h,Form("%.1f<p_{T}^{D}<%.1f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(h,"Data","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(mass2,"K-#pi swapped","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->Draw();
   TLegend *leg2 = myLegend(0.45,0.77,0.9,0.94);
   leg2->AddEntry(h,"D meson","");
   leg2->AddEntry(h,Form("M_{D}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{D}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();

   c->SaveAs(Form("../ResultsD0purdue/DMass-%d.pdf",count));

   return mass;
}

void fitDpurdue(TString infname="",TString label="",bool doweight = 1)
{
  if (doweight==0) weight="1";
  if (infname=="") infname=inputdata.Data();
  TFile *inf = new TFile(infname.Data());
  TFile *infMC = new TFile(inputmc.Data());

  TTree *nt = (TTree*) inf->Get("recodmesontree");
  TTree *ntMC = (TTree*) inf->Get("recodmesontree");
    
  //ntGen->AddFriend(ntMC);
  //ntGen2->AddFriend(ntMC);
 
  TH1D *hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D *hPtRecoTruth = new TH1D("hPtRecoTruth","",nBins,ptBins);
  TH1D *hGenPtSelected = new TH1D("hGenPtSelected","",nBins,ptBins);
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtGen = new TH1D("hPtGen","",nBins,ptBins);
  TH1D *hPtGen2 = new TH1D("hPtGen2","",nBins,ptBins);

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ntMC,ptBins[i],ptBins[i+1]);
      double yield = f->Integral(1.7,2.0)/0.005;
      double yieldErr = f->Integral(1.7,2.0)/0.005*f->GetParError(0)/f->GetParameter(0);
      hPt->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
    }  

  /*  
  TCanvas *c=  new TCanvas("cResult","",600,600);
  c->SetLogy();
  hPt->SetXTitle("D^{0} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected D^{0} dN/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();

  // Matched number of candidates
  ntMC->Project("hPtMC","Dpt",TCut(weight)*(TCut(selmc.Data())&&"Dgen==23333"));
  nt->Project("hPtRecoTruth","Dpt",TCut(seldata.Data())&&"Dgen==23333");
  ntMC2->Project("hPtMC","Dpt",TCut(weight)*(TCut(selmc.Data())&&"Dgen==23333"));
  nt2->Project("hPtRecoTruth","Dpt",TCut(seldata.Data())&&"Dgen==23333");
  
  // Gen number of D meson candidates
  ntGen->Project("hPtGen","Dpt",TCut(weight)*(TCut(selmcgen.Data())));
  ntGen2->Project("hPtGen2","Dpt",(TCut(selmcgen.Data())));
  divideBinWidth(hPtRecoTruth);
  
  hPtRecoTruth->Draw("same hist");
  divideBinWidth(hPtMC);
  divideBinWidth(hPtGen);
  divideBinWidth(hPtGen2);
  
  hPtMC->Sumw2();
  TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
  hPtMC->Sumw2();
  hEff->Divide(hPtGen);
  
  TH1D *hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->Divide(hEff);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  cCor->SetLogy();
  hPtCor->SetYTitle("Corrected D^{0} dN/dp_{T}");
  hPtCor->Draw();
  hPtGen->Draw("same hist");
  hPtGen2->Draw("same hist");

  TH1D *hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  double BRchain=6.09604e-5;

  hPtSigma->Scale(1./(2*luminosity*BRchain));
  hPtSigma->SetYTitle("d#sigma (D^{0})/dp_{T}");

  TCanvas *cSigma=  new TCanvas("cSigma","",600,600);
  cSigma->SetLogy();
  hPtSigma->Draw();

  TFile *outf = new TFile(Form("ResultsD0/alphaD0%s.root",label.Data()),"recreate");
  outf->cd();
  hPt->Write();
  */
  /*hEff->Write();
  hPtGen->Write();
  hPtCor->Write();
  hPtSigma->Write();*/
  //outf->Close();
  //delete outf;

}

