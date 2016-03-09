using namespace std;
#include "doubleratioParameter.h"
enum reaL{MC_MB,Data_MB,MC,Data}; reaL isData=Data;
void saveHist5pSinglept(TString sptmin="14", TString outfile="fmass.root")
{
  Float_t ptmin = atof(sptmin);
  TFile* infData = new TFile(infnameData5p[isData].Data());
  TFile* infMC = new TFile(infnameMC5p[isData].Data());
  TTree* ntData = (TTree*)infData->Get("ntDD0kpipipipi");
  TTree* ntMC = (TTree*)infMC->Get("ntDD0kpipipipi");
  
  ntData->AddFriend("ntHlt");
  if(isData!=Data_MB||isData!=Data) ntData->AddFriend("ntHi");
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  
  cout<<"  -- Filling histograms - "<<texData[isData]<<endl;
  cout<<"     "<<infnameData5p[isData]<<endl;
  cout<<"     "<<infnameMC5p[isData]<<endl;

  cout<<setiosflags(ios::left)<<"   - Processing ptbin "<<setw(3)<<ptmin<<endl;
  TH1D* h = new TH1D("h","",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSignal = new TH1D("hMCSignal","",BINNUM,BINMIN,BINMAX);
  TH1D* hMCSwapped = new TH1D("hMCSwapped","",BINNUM,BINMIN,BINMAX);
  ntData->Project("h","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightdata[isData].Data(),seldata5p[isData].Data(),triggerselectiondata[isData].Data(),ptmin));
  cout<<"   - h finished"<<endl;
  ntMC->Project("hMCSignal","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isData].Data(),selmc5p[isData].Data(),triggerselectionmc[isData].Data(),ptmin));
  cout<<"   - hMCSignal finished"<<endl;
  ntMC->Project("hMCSwapped","Dmass-DtktkResmass",Form("%s*(%s&&%s&&Dpt>%f)",weightmc[isData].Data(),selswp5p[isData].Data(),triggerselectionmc[isData].Data(),ptmin));
  cout<<"   - hMCSwapped finished"<<endl;
  TFile* outf = new TFile(Form("%s",outfile.Data()),"recreate");
  outf->cd();
  h->Write();
  hMCSignal->Write();
  hMCSwapped->Write();
  outf->Close();
  delete hMCSwapped;
  delete hMCSignal;
  delete h;
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
      saveHist5pSinglept(atof(argv[1]),argv[2]);
      return 0;
    }
}
