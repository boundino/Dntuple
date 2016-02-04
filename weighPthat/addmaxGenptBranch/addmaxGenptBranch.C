using namespace std;
#include "uti.h"
#define MAX_GEN      6000

int addmaxGenptBranch(TString ifname = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160125_Dfinder_20151229_pp_Pythia8_prompt_D0pt0p0_Pthat0_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt1tkPt1_D0Ds.root",
                      TString ofname = "test.root")
{
  cout<<endl;
  cout<<" -- Checking if input and output files are same"<<endl;
  if(ifname==ofname)
    {
      cout<<"    Error: Input file will be overwritten."<<endl;
      return 0;
    }
  cout<<" -- Opening unweighed sample"<<endl;
  TFile* inf = TFile::Open(ifname);
  TTree* ntGen = (TTree*)inf->Get("ntGen");
  Int_t Gsize; ntGen->SetBranchAddress("Gsize",&Gsize);
  Float_t Gpt[MAX_GEN]; ntGen->SetBranchAddress("Gpt",Gpt);
  Int_t GisSignal[MAX_GEN]; ntGen->SetBranchAddress("GisSignal",GisSignal);

  Int_t nentries = ntGen->GetEntries();
  cout<<" -- Building weight branch"<<endl;
  TFile* otf = TFile::Open(ofname,"update");
  TTree* ntHinew = (TTree*)otf->Get("ntHi");
  Float_t maxDgenpt;
  TBranch* newBr_maxDgenpt = ntHinew->Branch("maxDgenpt", &maxDgenpt, "maxDgenpt/F");

  cout<<" -- Checking event number"<<endl;
  if(ntGen->GetEntries()!=ntHinew->GetEntries())
    {
      cout<<"    Error: Gen tree and Hi tree have different event number."<<endl;
      return 0;
    }
  cout<<" -- Filling weight branch"<<endl;
  for(Int_t i=0;i<nentries;i++)
    {
      ntGen->GetEntry(i);
      if(i%100000==0) cout<<"    Processing event "<<setiosflags(ios::left)<<setw(7)<<i<<" / "<<nentries<<endl;
      Float_t maxpt=0;
      for(Int_t k=0;k<Gsize;k++)
        {
          if((GisSignal[k]==genSignal[0]||GisSignal[k]==genSignal[1])&&Gpt[k]>maxpt) maxpt=Gpt[k];
        }
      maxDgenpt = maxpt;
      newBr_maxDgenpt->Fill();
    }
  ntHinew->Write("", TObject::kOverwrite);

  cout<<" -- Output file location"<<endl;
  cout<<"    "<<ofname<<endl;
  cout<<endl;
  cout<<" -- End"<<endl;
  return 1;
}

int main(int argc, char *argv[])
{
  if(argc==3)
    {
      addmaxGenptBranch(argv[1], argv[2]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
