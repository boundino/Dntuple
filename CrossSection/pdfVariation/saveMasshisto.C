using namespace std;
#include "uti.h"
#include "parameters.h"

Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString weightMC = "1";
TString weight = "pthatweight";
TString seldata;
TString selmc;
TString collisionsystem;
Bool_t  isPbPb;
Float_t centmin,centmax,hiBinmin,hiBinmax;

void saveMasshisto(TString inputdata="",
                   TString inputmc="",
                   TString trgselection="",
                   TString cut="",
                   int isMC=0, int doweight=0, TString collsyst="PP",
                   Float_t centMin=0,
                   Float_t centMax=100,
                   TString outputfile="outfMasshisto/mass")
{
  collisionsystem=collsyst;
  seldata = Form("%s&&%s",trgselection.Data(),cut.Data());
  selmc = Form("%s",cut.Data());
  centmin = centMin;
  centmax = centMax;
  hiBinmin = centMin*2;
  hiBinmax = centMax*2;
  isPbPb = true;
  if(collisionsystem=="PP"||collisionsystem=="PPMB") isPbPb = false;
  if(!doweight) weight="1";

  TFile* inf = new TFile(inputdata.Data());
  TFile* infMC = new TFile(inputmc.Data());

  TTree* nt = (TTree*) inf->Get("ntDkpi");
  nt->AddFriend("ntHlt");
  nt->AddFriend("ntHi");  
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  ntMC->AddFriend("ntHi");
  
  cout<<"  -- Filling histograms"<<endl;
  cout<<"     "<<inputdata<<endl;
  cout<<"     "<<inputmc<<endl;
  for(int i=0;i<nBins;i++)
    {
      cout<<setiosflags(ios::left)<<"   - Processing ptbin "<<setw(3)<<ptBins[i]<<" "<<setw(3)<<ptBins[i+1]<<endl;
      TH1D* h = new TH1D("h","",nbinsmasshisto,minhisto,maxhisto);
      h->Sumw2();
      TH1D* hMCSignal = new TH1D("hMCSignal","",nbinsmasshisto,minhisto,maxhisto);
      hMCSignal->Sumw2();
      TH1D* hMCSwapped = new TH1D("hMCSwapped","",nbinsmasshisto,minhisto,maxhisto);
      hMCSwapped->Sumw2();
      if(isPbPb) nt->Project("h","Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&hiBin>%f&&hiBin<%f)",weight.Data(),seldata.Data(),ptBins[i],ptBins[i+1],hiBinmin,hiBinmax));
      else nt->Project("h","Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f)",weight.Data(),seldata.Data(),ptBins[i],ptBins[i+1]));
      ntMC->Project("hMCSignal","Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23333))",weightMC.Data(),selmc.Data(),ptBins[i],ptBins[i+1]));   
      ntMC->Project("hMCSwapped","Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23344))",weightMC.Data(),selmc.Data(),ptBins[i],ptBins[i+1]));   
      TFile* outf = new TFile(Form("%s_%s_cent_%.0f_%.0f_pt_%.0f_%.0f.root",outputfile.Data(),collisionsystem.Data(),centmin,centmax,ptBins[i],ptBins[i+1]),"recreate");
      outf->cd();
      h->Write();
      hMCSignal->Write();
      hMCSwapped->Write();
      outf->Close();
      delete h;
      delete hMCSignal;
      delete hMCSwapped;
      delete outf;
    }
  cout<<endl;
}

int main(int argc, char *argv[])
{
  if(argc==10)
    {
      saveMasshisto(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), argv[7], atof(argv[8]), atof(argv[9]));
      return 0;
    }
  else if(argc==8)
    {
      saveMasshisto(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), argv[7]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}

