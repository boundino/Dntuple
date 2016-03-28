using namespace std;
#include "uti.h"

Double_t minhisto=1.0;
Double_t maxhisto=3.0;
Double_t nbinsmasshisto=50;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

Float_t sigregWidth = 0.03;
Float_t sidbndLow = 0.06;
Float_t sidbndHigh = 0.12;
Float_t wfactor = sigregWidth/(sidbndHigh-sidbndLow);

TString weightMC = "pthatweight";
TString weight;
TString seldata;
TString selmc;
TString collisionsystem;

int saveMasshisto(TString inputdata="",
                  TString inputmc="",
                  TString trgselection="",
                  TString cut="",
                  Int_t isMC=0,
                  TString weightdata="",
                  TString collsyst="",
                  TString varname="",
                  TString variable="",
                  Int_t varbins=10,
                  Float_t varmin=0.5,
                  Float_t varmax=2,
                  Int_t isLarger=0,
                  Float_t ptmin=0,                   
                  TString outputfile="outfMasshisto/mass")
{
  if(varbins<=1)
    {
      cout<<"Error: one bin is invalide"<<endl;
      return 0;
    }
  collisionsystem=collsyst;
  seldata = Form("%s&&%s",trgselection.Data(),cut.Data());
  selmc = Form("%s",cut.Data());
  weight = weightdata;
  TString cutsigreg = Form("fabs(Dmass-1.8648)<%f",sigregWidth);
  TString cutsidbnd = Form("fabs(Dmass-1.8648)>%f&&fabs(Dmass-1.8648)<%f",sidbndLow,sidbndHigh);

  TFile* inf = new TFile(inputdata.Data());
  TFile* infMC = new TFile(inputmc.Data());

  TTree* nt = (TTree*) inf->Get("ntDkpi");
  nt->AddFriend("ntHlt");
  if(isMC==1) nt->AddFriend("ntHi");  
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  ntMC->AddFriend("ntHi");
  
  cout<<"  -- Variable"<<endl;
  cout<<"     "<<varname<<" "<<variable<<endl;
  cout<<"  -- Filling histograms"<<endl;
  cout<<"     "<<inputdata<<endl;
  cout<<"     "<<inputmc<<endl;

  Float_t varstep = (varmax-varmin)/(varbins-1);
  for(float i=0;i<varbins+1;i++)
    {
      Float_t ivar = varmin+(i-1)*varstep;
      if(i==0) cout<<setiosflags(ios::left)<<"   - Processing varbin no cuts"<<endl;
      else cout<<setiosflags(ios::left)<<"   - Processing varbin "<<setw(3)<<ivar<<endl;
      TH1D* hDaSigreg = new TH1D("hDaSigreg","",nbinsmasshisto,minhisto,maxhisto);
      hDaSigreg->Sumw2();
      TH1D* hDaSidbnd = new TH1D("hDaSidbnd","",nbinsmasshisto,minhisto,maxhisto);
      hDaSidbnd->Sumw2();
      TH1D* hMCSignal = new TH1D("hMCSignal","",nbinsmasshisto,minhisto,maxhisto);
      hMCSignal->Sumw2();
      if(i>0)
        {
          if(isLarger==1)
            {
              nt->Project("hDaSigreg","Dmass",Form("%s*(%s&&Dpt>%f&&%s>%f&&%s)",weight.Data(),seldata.Data(),ptmin,variable.Data(),ivar,cutsigreg.Data()));
              nt->Project("hDaSidbnd","Dmass",Form("%s*(%s&&Dpt>%f&&%s>%f&&%s)",weight.Data(),seldata.Data(),ptmin,variable.Data(),ivar,cutsidbnd.Data()));
              ntMC->Project("hMCSignal","Dmass",Form("%s*(%s&&Dpt>%f&&%s>%f&&(Dgen==23333))",weightMC.Data(),selmc.Data(),ptmin,variable.Data(),ivar));   
            }
          else
            {
              nt->Project("hDaSigreg","Dmass",Form("%s*(%s&&Dpt>%f&&%s<%f&&%s)",weight.Data(),seldata.Data(),ptmin,variable.Data(),ivar,cutsigreg.Data()));
              nt->Project("hDaSidbnd","Dmass",Form("%s*(%s&&Dpt>%f&&%s<%f&&%s)",weight.Data(),seldata.Data(),ptmin,variable.Data(),ivar,cutsidbnd.Data()));
              ntMC->Project("hMCSignal","Dmass",Form("%s*(%s&&Dpt>%f&&%s<%f&&(Dgen==23333))",weightMC.Data(),selmc.Data(),ptmin,variable.Data(),ivar));   
            }
        }
      else
        {
          nt->Project("hDaSigreg","Dmass",Form("%s*(%s&&Dpt>%f&&%s)",weight.Data(),seldata.Data(),ptmin,cutsigreg.Data()));
          nt->Project("hDaSidbnd","Dmass",Form("%s*(%s&&Dpt>%f&&%s)",weight.Data(),seldata.Data(),ptmin,cutsidbnd.Data()));
          ntMC->Project("hMCSignal","Dmass",Form("%s*(%s&&Dpt>%f&&(Dgen==23333))",weightMC.Data(),selmc.Data(),ptmin));
        }
      TString tMC;
      if(isMC==1) tMC="MC";
      else tMC="Data";
      TFile* outf = new TFile(Form("%s_%s_%s_%s_%.0f.root",outputfile.Data(),collisionsystem.Data(),varname.Data(),tMC.Data(),i),"recreate");
      outf->cd();
      hDaSigreg->Write();
      hDaSidbnd->Write();
      hMCSignal->Write();
      outf->Close();
      delete hDaSigreg;
      delete hDaSidbnd;
      delete hMCSignal;
      delete outf;
    }
  cout<<endl;
  return 1;
}

int main(int argc, char *argv[])
{
  if(argc!=15)
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  else
    {
      saveMasshisto(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), argv[6], argv[7], argv[8], argv[9], atoi(argv[10]), atof(argv[11]), atof(argv[12]), atoi(argv[13]), atof(argv[14]));
      return 0;
    }
}

