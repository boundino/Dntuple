#include "doubleratioParameter.h"

enum real{MC_MB,Data_MB,MC,Data};
//real isData=MC;
const int nBins=10;  Float_t ptBins[nBins]={5.,6.,7.,8.,9.,10.,11.,12.,13.,14.}; Float_t ptBinsPlus[nBins+1]={5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.};

void saveHist3pMinpt()
{
  real isMC=MC;
  TFile* infMCData = new TFile(infnameData3p[isMC].Data());
  TFile* infMCMC = new TFile(infnameMC3p[isMC].Data());
  TTree* ntMCData = (TTree*)infMCData->Get("ntDD0kpipi");
  TTree* ntMCMC = (TTree*)infMCMC->Get("ntDD0kpipi");
  
  ntMCData->AddFriend("ntHlt");
  if(isMC!=Data_MB||isMC!=Data) ntMCData->AddFriend("ntHi");
  ntMCMC->AddFriend("ntHlt");
  ntMCMC->AddFriend("ntHi");
  
  cout<<"  -- Filling histograms - MC"<<endl;
  cout<<"     "<<infnameData3p[isMC]<<endl;
  cout<<"     "<<infnameMC3p[isMC]<<endl;

  for(int i=0;i<nBins;i++)
    {
      cout<<setiosflags(ios::left)<<"   - Processing ptbin "<<setw(3)<<ptBins[i]<<endl;
      TH1D* h = new TH1D("h","",BINNUM,BINMIN,BINMAX);
      TH1D* hMCSignal = new TH1D("hMCSignal","",BINNUM,BINMIN,BINMAX);
      TH1D* hMCSwapped = new TH1D("hMCSwapped","",BINNUM,BINMIN,BINMAX);
      ntMCData->Project("h","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightdata[isMC].Data(),seldata3p[isMC].Data(),triggerselectiondata[isMC].Data(),ptBins[i]));
      ntMCMC->Project("hMCSignal","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isMC].Data(),selmc3p[isMC].Data(),triggerselectionmc[isMC].Data(),ptBins[i]));
      ntMCMC->Project("hMCSwapped","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isMC].Data(),selswp3p[isMC].Data(),triggerselectionmc[isMC].Data(),ptBins[i]));
      TFile* outf = new TFile(Form("inputfiles/fmass_pp_3p_%s_%.0f.root",texData[isMC].Data(),ptBins[i]),"recreate");
      outf->cd();
      h->Write();
      hMCSignal->Write();
      hMCSwapped->Write();
      outf->Close();
      delete hMCSwapped;
      delete hMCSignal;
      delete h;
      delete outf;
    }
  cout<<endl;
}

int main(int argc, char *argv[])
{
  if(argc!=1)
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  else
    {
      saveHist3pMinpt();
      return 0;
    }
}
