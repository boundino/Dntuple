using namespace std;
#include "doubleratioParameter.h"

const int nBins=10;  Float_t ptBins[nBins]={5.,6.,7.,8.,9.,10.,11.,12.,13.,14.}; Float_t ptBinsPlus[nBins+1]={5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.};
void saveHist3pMinpt()
{
  TFile* infMCData = new TFile(infnameData3p[isData].Data());
  TFile* infMCMC = new TFile(infnameMC3p[isData].Data());
  TTree* ntMCData = (TTree*)infMCData->Get("ntDD0kpipi");
  TTree* ntMCMC = (TTree*)infMCMC->Get("ntDD0kpipi");
  
  ntMCData->AddFriend("ntHlt");
  if(isData!=Data_MB||isData!=Data) ntMCData->AddFriend("ntHi");
  ntMCMC->AddFriend("ntHlt");
  ntMCMC->AddFriend("ntHi");
  
  cout<<"  -- Filling histograms - MC"<<endl;
  cout<<"     "<<infnameData3p[isData]<<endl;
  cout<<"     "<<infnameMC3p[isData]<<endl;

  for(int i=0;i<nBins;i++)
    {
      cout<<setiosflags(ios::left)<<"   - Processing ptbin "<<setw(3)<<ptBins[i]<<endl;
      TH1D* h = new TH1D("h","",BINNUM,BINMIN,BINMAX);
      TH1D* hMCSignal = new TH1D("hMCSignal","",BINNUM,BINMIN,BINMAX);
      TH1D* hMCSwapped = new TH1D("hMCSwapped","",BINNUM,BINMIN,BINMAX);
      ntMCData->Project("h","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightdata[isData].Data(),seldata3p[isData].Data(),triggerselectiondata[isData].Data(),ptBins[i]));
      ntMCMC->Project("hMCSignal","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isData].Data(),selmc3p[isData].Data(),triggerselectionmc[isData].Data(),ptBins[i]));
      ntMCMC->Project("hMCSwapped","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isData].Data(),selswp3p[isData].Data(),triggerselectionmc[isData].Data(),ptBins[i]));
      TFile* outf = new TFile(Form("inputfiles/fmass_pp_3p_%s_%.0f.root",texData[isData].Data(),ptBins[i]),"recreate");
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
