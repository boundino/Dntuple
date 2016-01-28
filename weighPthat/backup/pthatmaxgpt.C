#include "../uti.h"
#define MAX_GEN      6000

void pthatmaxgpt(Float_t samplePthat=50, Bool_t toPlot=false)
{
  const int nBins=6; Double_t ptBins[nBins+1]={0.,5.,10.,15.,30.,50.,100.};
  TFile* inf = new TFile(Form("/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt%.0fp0_Pthat%.0f_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",samplePthat,samplePthat));
  TTree* ntGen = (TTree*)inf->Get("ntGen");
  TTree* ntHi = (TTree*)inf->Get("ntHi");

  cout<<ntGen->GetEntries()<<" "<<ntHi->GetEntries()<<endl;
  Int_t nentries = ntGen->GetEntries();
  TH2D* h = new TH2D("h",";Pthat;Max Gen p_{T} (GeV/c)",nBins,ptBins,nBins,ptBins);

  Int_t Gsize;              ntGen->SetBranchAddress("Gsize",&Gsize);
  Int_t GisSignal[MAX_GEN]; ntGen->SetBranchAddress("GisSignal",GisSignal);
  Float_t Gpt[MAX_GEN];     ntGen->SetBranchAddress("Gpt",Gpt);
  Float_t pthat;            ntHi->SetBranchAddress("pthat",&pthat);
  Float_t qScale;           ntHi->SetBranchAddress("qScale",&qScale);
  for(Int_t i=0;i<nentries;i++)
    {
      ntGen->GetEntry(i);
      ntHi->GetEntry(i);
      Float_t maxpt=0;
      for(Int_t j=0;j<Gsize;j++)
        {
          if(!(GisSignal[j]==9||GisSignal[j]==10)) continue;
          if(Gpt[j]>maxpt) maxpt=Gpt[j];
        }
      //h->Fill(pthat,maxpt);
      h->Fill(pthat,qScale);
    }

  cout<<endl;
  cout<<"             Pthat"<<samplePthat<<" Sample"<<endl;
  cout<<"            ╒"<<"═══════════"<<"╤"<<"═══════════"<<"╤"<<"═══════════"<<"╤"<<"═══════════"<<"╤"<<"═══════════"<<"╤"<<"═══════════"<<"╤"<<"═══════════"<<"╕"<<endl;
  for(Int_t i=0;i<nBins;i++)
    {
      if(i!=0) cout<<"            ├"<<"───────────"<<"┼"<<"───────────"<<"┼"<<"───────────"<<"┼"<<"───────────"<<"┼"<<"───────────"<<"┼"<<"───────────"<<"┼"<<"───────────"<<"┤"<<endl;
      //if(i==3) cout<<" Max Gen pT ";
      if(i==3) cout<<"   qScale   ";
      else cout<<"            ";
      cout<<"| "<<setiosflags(ios::left)<<setw(10)<<Form("%.0f - %.0f",ptBins[nBins-i-1],ptBins[nBins-i]);
      for(Int_t j=0;j<nBins;j++)
        {
          cout<<"| "<<setiosflags(ios::left)<<setw(10)<<h->GetBinContent(j+1,nBins-i);
        }
      cout<<"|"<<endl;
    }
  cout<<"            ╞"<<"═══════════"<<"╪"<<"═══════════"<<"╪"<<"═══════════"<<"╪"<<"═══════════"<<"╪"<<"═══════════"<<"╪"<<"═══════════"<<"╪"<<"═══════════"<<"╡"<<endl;
  cout<<"            |           ";
  for(Int_t j=0;j<nBins;j++)
    {
      cout<<"| "<<setiosflags(ios::left)<<setw(10)<<Form("%.0f - %.0f",ptBins[j],ptBins[j+1]);
    }
  cout<<"|"<<endl;
  cout<<"            ╘"<<"═══════════"<<"╧"<<"═══════════"<<"╧"<<"═══════════"<<"╧"<<"═══════════"<<"╧"<<"═══════════"<<"╧"<<"═══════════"<<"╧"<<"═══════════"<<"╛"<<endl;
  cout<<"                                                   Pthat"<<endl;
  cout<<endl;

  if(toPlot)
    {
      gStyle->SetPadLeftMargin(0.17);
      gStyle->SetPadRightMargin(0.20);
      TCanvas* c = new TCanvas("c","",600,600);
      h->Draw("colz");
    }
}

//TFile* inf = new TFile("/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root");
