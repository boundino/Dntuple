using namespace std;
#include "weighPthat.h"

int weighPthat(TString ifname = "/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_noweight.root",
               TString ofname = "/afs/cern.ch/work/w/wangj/public/RunII/weighPthat/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_withweight.root")
{
  Bool_t isInsidebin(Float_t xpthat, Int_t i);
  cout<<endl;
  cout<<" -- Checking if input and output files are same"<<endl;
  if(ifname==ofname)
    {
      cout<<"    Error: Input file will be overwritten."<<endl;
      return 0;
    }
  cout<<" -- Opening unweighed sample"<<endl;
  TFile* inf = TFile::Open(ifname);
  TTree* ntHi = (TTree*)inf->Get("ntHi");
  Float_t pthat; ntHi->SetBranchAddress("pthat",&pthat);
  Float_t weight[nBins],nweight[nBins];
  for(Int_t j=0;j<nBins;j++)
    {
      weight[j]=0;
      nweight[j]=0;
    }
  Int_t nentries = ntHi->GetEntries();
  cout<<" -- Calculating weights"<<endl;
  for(Int_t i=0;i<nentries;i++)
    {
      ntHi->GetEntry(i);
      if(i%100000==0) cout<<"    Processing event "<<setiosflags(ios::left)<<setw(7)<<i<<" / "<<nentries<<endl;
      for(Int_t j=0;j<nBins;j++)
        {
          if(isInsidebin(pthat,j)) nweight[j]++;
        }
    }
  cout<<" -- Weight results"<<endl;
  for(Int_t j=0;j<nBins;j++)
    {
      if(nweight[j]==0)
        {
          cout<<"    Error: Weight fails."<<endl;
          return 0;
        }
      weight[j] = (crosssec[j]-crosssec[j+1])/nweight[j];
      cout<<"    Pthat"<<setiosflags(ios::left)<<setw(3)<<pthatBin[j]<<": "<<weight[j]<<endl;
    }

  cout<<" -- Building weight branch"<<endl;
  TFile* otf = TFile::Open(ofname,"update");
  TTree* ntHinew = (TTree*)otf->Get("ntHi");
  Float_t pthatweight; 
  TBranch* newBranch = ntHinew->Branch("pthatweight", &pthatweight, "pthatweight/F");
  cout<<" -- Filling weight branch"<<endl;
  for(Int_t i=0;i<nentries;i++)
    {
      ntHi->GetEntry(i);
      if(i%100000==0) cout<<"    Processing event "<<setiosflags(ios::left)<<setw(7)<<i<<" / "<<nentries<<endl;
      pthatweight=0;
      for(Int_t j=0;j<nBins;j++)
        {
          if(isInsidebin(pthat,j)) pthatweight = weight[j];
        }
      newBranch->Fill();
    }
  ntHinew->Write("", TObject::kOverwrite);

  cout<<" -- End"<<endl;
  cout<<endl;
  return 1;
}

Bool_t isInsidebin(Float_t xpthat, Int_t i)
{
  if(i>=nBins)
    {
      cout<<"    Error: invalid input"<<endl;
      return false;
    }
  if(i<(nBins-1)&&xpthat>pthatBin[i]&&xpthat<pthatBin[i+1]) return true;
  else if(i==(nBins-1)&&xpthat>pthatBin[i]) return true;
  else return false;
}

int main(int argc, char *argv[])
{
  if(argc==3)
    {
      weighPthat(argv[1], argv[2]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
