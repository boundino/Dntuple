using namespace std;
#include "checkXsection.h"

int checkXsection(TString ifname = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt0p0_Pthat0_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root",
                  Int_t iniBin = 0)
{
  cout<<endl;
  TFile* inf = TFile::Open(ifname);
  TTree* ntGen = (TTree*)inf->Get("ntGen");
  TTree* ntHi = (TTree*)inf->Get("ntHi");
  Int_t Gsize; ntGen->SetBranchAddress("Gsize",&Gsize);
  Float_t Gpt[MAX_GEN]; ntGen->SetBranchAddress("Gpt",Gpt);
  Int_t GisSignal[MAX_GEN]; ntGen->SetBranchAddress("GisSignal",GisSignal);
  Float_t pthat; ntHi->SetBranchAddress("pthat",&pthat);

  Float_t nsquare[nBins];
  for(Int_t j=0;j<nBins;j++) nsquare[j]=0;
  if(ntGen->GetEntries()!=ntHi->GetEntries())
    {
      cout<<"    Error: Gen tree and Hi tree have different event number."<<endl;
      return 0;
    }
  Int_t nentries = ntGen->GetEntries();
  for(Int_t i=0;i<nentries;i++)
    {
      ntGen->GetEntry(i);
      ntHi->GetEntry(i);
      Float_t maxpt=0;
      for(Int_t k=0;k<Gsize;k++)
        {
          if((GisSignal[k]==1||GisSignal[k]==2)&&Gpt[k]>maxpt) maxpt=Gpt[k];
        }
      for(Int_t j=0;j<nBins;j++)
        {
          if(pthat>pthatBin[j]&&maxpt>pthatBin[j]) nsquare[j]++;
        }
    }
  cout<<" -- Xsection calculated by Pthat"<<pthatBin[iniBin]<<" sample:"<<endl;
  cout<<"    "<<setiosflags(ios::left)<<setw(30)<<" "<<setw(20)<<Form("XsectionByPthat%.0f",pthatBin[iniBin])<<"  "<<setw(18)<<"XsectionInTable"<<"  "<<setw(11)<<"Difference"<<endl;
  for(Int_t j=iniBin;j<nBins;j++)
    {
      cout<<"    "<<setiosflags(ios::left)<<setw(30)<<Form("N(pthat>%.0f,maxGenDpt>%.0f)",pthatBin[j],pthatBin[j]);
      cout<<setiosflags(ios::left)<<setw(20)<<(nsquare[j]/nsquare[iniBin])*crosssec[iniBin]<<"  "<<setw(18)<<crosssec[j]<<"  "<<setw(11)<<((nsquare[j]/nsquare[iniBin])*crosssec[iniBin]-crosssec[j])*100./crosssec[j]<<"%"<<endl;;
    }

  return 1;
}

int main(int argc, char *argv[])
{
  int x;
  if(argc==3)
    {
      x = atoi(argv[2]);
      checkXsection(argv[1], x);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
