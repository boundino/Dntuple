#include "weighPthat.h"

void weighPthat()
{
  Double_t weight[nBins];
  Double_t nweight[nBins][nBins];
  Double_t sum[nBins];
  for(Int_t i=0;i<nBins;i++) sum[i]=0;
  for(Int_t ipthat=0;ipthat<nBins;ipthat++)
    {
      weight[ipthat]=0;
      for(Int_t j=0;j<nBins;j++) nweight[ipthat][j]=0;
      TFile* inf = new TFile(Form("/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dstar_D0kpi/ntD_EvtBase_20160112_Dfinder_20151229_pp_Pythia8D0kpi_Dstarpt%.0fp0_Pthat%.0f_TuneCUETP8M1_5020GeV_GEN_SIM_20151212_dPt0tkPt1_D0Dstar3p5p.root",pthatBin[ipthat],pthatBin[ipthat]));
      TTree* ntGen = (TTree*)inf->Get("ntGen");
      TTree* ntHi = (TTree*)inf->Get("ntHi");
      Int_t Gsize; ntGen->SetBranchAddress("Gsize",&Gsize);
      Float_t Gpt[MAX_GEN]; ntGen->SetBranchAddress("Gpt",Gpt);
      Float_t pthat; ntHi->SetBranchAddress("pthat",&pthat);
      if(ntGen->GetEntries()!=ntHi->GetEntries())
        {
          cout<<"Error: Gen tree and Hi tree have different event number."<<endl;
          break;
        }
      Int_t nentries = ntGen->GetEntries();
      for(Int_t i=0;i<nentries;i++)
        {
          ntGen->GetEntry(i);
          ntHi->GetEntry(i);
          Float_t maxpt=0;
          for(Int_t j=0;j<Gsize;j++)
            {
              if(Gpt[j]>maxpt) maxpt=Gpt[j];
            }
          for(Int_t j=0;j<nBins-1;j++)
            {
              if(pthat>pthatBin[j]&&pthat<pthatBin[j+1]&&maxpt>pthatBin[j]&&maxpt<pthatBin[j+1]) nweight[ipthat][j]++;
            }
          if(pthat>pthatBin[nBins-1]&&maxpt>pthatBin[nBins-1]) nweight[ipthat][nBins-1]++;
        }
      if(ipthat<nBins-1) weight[ipthat]=(crosssec[ipthat]-crosssec[ipthat+1]-sum[ipthat])/nweight[ipthat][ipthat];
      else weight[ipthat]=(crosssec[ipthat]-sum[ipthat])/nweight[ipthat][ipthat];
      for(Int_t j=ipthat;j<nBins-1;j++)
        {
          sum[j]+=nweight[ipthat][j]*weight[ipthat];
        }
    }
  for(Int_t ipthat=0;ipthat<nBins;ipthat++) cout<<weight[ipthat]<<endl;

}
