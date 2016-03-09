using namespace std;
#include "doubleratioParameter.h"
enum reaL{MC_MB,Data_MB,MC,Data}; reaL isData=Data;
void saveHist3pSinglept(TString sptmin="14", TString outfname="fmass.root")
{
  Float_t ptmin = atof(sptmin);
  TFile* infData = new TFile(infnameData3p[isData].Data());
  TFile* infMC = new TFile(infnameMC3p[isData].Data());
  TTree* ntData = (TTree*)infData->Get("ntDD0kpipi");
  TTree* ntMC = (TTree*)infMC->Get("ntDD0kpipi");
  
  ntData->AddFriend("ntHlt");
  if(isData!=Data_MB||isData!=Data) ntData->AddFriend("ntHi");
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  
  cout<<"  -- Filling histograms - "<<texData[isData]<<endl;
  cout<<"     "<<infnameData3p[isData]<<endl;
  cout<<"     "<<infnameMC3p[isData]<<endl;

  cout<<setiosflags(ios::left)<<"   - Processing ptbin "<<setw(3)<<ptmin<<endl;
  TH1D* h = new TH1D("h","",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSignal = new TH1D("hMCSignal","",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSwapped = new TH1D("hMCSwapped","",BINNUM,BINMIN,BINMAX);
  ntData->Project("h","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightdata[isData].Data(),seldata3p[isData].Data(),triggerselectiondata[isData].Data(),ptmin));
  cout<<"   - h finished"<<endl;
  ntMC->Project("hMCSignal","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isData].Data(),selmc3p[isData].Data(),triggerselectionmc[isData].Data(),ptmin));
  cout<<"   - hMCSignal finished"<<endl;
  ntMC->Project("hMCSwapped","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isData].Data(),selswp3p[isData].Data(),triggerselectionmc[isData].Data(),ptmin));
  cout<<"   - hMCSwapped finished"<<endl;
  TFile* outf = new TFile(Form("%s",outfname.Data()),"recreate");
  outf->cd();
  h->Write();
  hMCSignal->Write();
  hMCSwapped->Write();
  outf->Close();
  delete h;
  delete hMCSignal;
  delete hMCSwapped;
  delete outf;
  cout<<"  -- Finished filling histograms - "<<texData[isData]<<endl;
  cout<<endl;
}

int main(int argc, char *argv[])
{
  if(argc!=3)
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  else
    {
      saveHist3pSinglept(argv[1],argv[2]);
      return 0;
    }
}
